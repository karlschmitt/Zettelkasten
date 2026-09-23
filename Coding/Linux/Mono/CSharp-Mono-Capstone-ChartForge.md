# Capstone Project — Build a Data Chart Generator in C#

This is the capstone of the C# with Mono series. It brings together **everything** from the earlier tutorials into one complete, buildable application:

- Language fundamentals — [Beginner](./CSharp-Mono-Beginner-Tutorial.md)
- OOP, interfaces, generics, LINQ — [Intermediate/OOP](./CSharp-Mono-Intermediate-OOP-Tutorial.md)
- Async, DI, patterns, testing — [Advanced](./CSharp-Mono-Advanced-Tutorial.md)
- 2D drawing — [SkiaSharp](./SkiaSharp-Tutorial.md) / [GDI+](./GDIPlus-Mono-Tutorial.md)

## What we're building

**ChartForge** — a command-line tool that reads numeric data from a CSV file and renders it as a **bar chart** or **line chart** PNG image. It's small enough to finish in a sitting, but real enough to exercise architecture, error handling, async I/O, the Strategy pattern, dependency injection, and graphics rendering — plus unit tests.

```
data.csv  ──►  ChartForge  ──►  chart.png
```

Example run:

```bash
dotnet run -- --input data.csv --output chart.png --type bar --title "Quarterly Sales"
```

---

## Table of Contents

1. [Architecture Overview](#1-architecture-overview)
2. [Project Setup](#2-project-setup)
3. [The Domain Model](#3-the-domain-model)
4. [Reading Data: The CSV Parser](#4-reading-data-the-csv-parser)
5. [Rendering: The Strategy Pattern](#5-rendering-the-strategy-pattern)
6. [The Bar Chart Renderer](#6-the-bar-chart-renderer)
7. [The Line Chart Renderer](#7-the-line-chart-renderer)
8. [Wiring It Together: The App Service](#8-wiring-it-together-the-app-service)
9. [Command-Line Parsing & Main](#9-command-line-parsing--main)
10. [Unit Tests](#10-unit-tests)
11. [Building and Running](#11-building-and-running)
12. [Extension Challenges](#12-extension-challenges)
13. [What You Practiced](#13-what-you-practiced)

---

## 1. Architecture Overview

The design keeps concerns separate so each piece is testable and swappable:

```
                 ┌─────────────────┐
   CSV file ───► │  IDataSource    │  reads & validates data
                 └────────┬────────┘
                          │ Dataset
                          ▼
                 ┌─────────────────┐
                 │  ChartService   │  orchestrates the workflow
                 └────────┬────────┘
                          │ picks a renderer via
                          ▼
                 ┌─────────────────┐
                 │ IChartRenderer  │  ◄── BarChartRenderer
                 └────────┬────────┘  ◄── LineChartRenderer
                          │ PNG bytes
                          ▼
                       chart.png
```

Key ideas applied:

- **Interfaces** (`IDataSource`, `IChartRenderer`) define contracts.
- **Dependency injection** supplies concrete implementations to `ChartService`.
- **Strategy pattern** — the chart type selects a renderer at runtime.
- **Async I/O** for file reading/writing.
- **Records** for immutable domain data.
- **Unit tests** validate the parser and renderer selection without touching disk.

---

## 2. Project Setup

We'll use the modern `dotnet` SDK because it makes multi-file projects, packages, and testing easy. (The pure-Mono `mcs` equivalent is noted at the end of section 11.)

```bash
# Create the solution structure
dotnet new console -n ChartForge
cd ChartForge
dotnet add package SkiaSharp

# On Linux, also add the native assets + fonts (see the SkiaSharp tutorial)
# dotnet add package SkiaSharp.NativeAssets.Linux
```

Your `ChartForge.csproj`:

```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>net8.0</TargetFramework>
    <Nullable>enable</Nullable>
    <ImplicitUsings>enable</ImplicitUsings>
  </PropertyGroup>
  <ItemGroup>
    <PackageReference Include="SkiaSharp" Version="2.88.8" />
  </ItemGroup>
</Project>
```

We'll create these files under the project folder:

```
ChartForge/
├── Dataset.cs          # domain model (records)
├── IDataSource.cs      # data-reading contract + CSV implementation
├── IChartRenderer.cs   # rendering contract
├── BarChartRenderer.cs
├── LineChartRenderer.cs
├── ChartService.cs     # orchestration
└── Program.cs          # CLI entry point
```

---

## 3. The Domain Model

Immutable **records** model the data cleanly. Create `Dataset.cs`:

```csharp
namespace ChartForge;

// A single labelled value, e.g. ("Jan", 120).
public record DataPoint(string Label, double Value);

// The whole dataset with an optional title.
public record Dataset(string Title, IReadOnlyList<DataPoint> Points)
{
    public double Max => Points.Count == 0 ? 0 : Points.Max(p => p.Value);
    public double Min => Points.Count == 0 ? 0 : Points.Min(p => p.Value);
}

// Which chart to draw.
public enum ChartType { Bar, Line }

// All options for one render request.
public record ChartOptions(
    string InputPath,
    string OutputPath,
    ChartType Type,
    string Title,
    int Width = 800,
    int Height = 500);
```

---

## 4. Reading Data: The CSV Parser

Define the contract and a CSV implementation. Create `IDataSource.cs`:

```csharp
namespace ChartForge;

// Contract: turn some source into a validated Dataset.
public interface IDataSource
{
    Task<Dataset> LoadAsync(string path, string title, CancellationToken token = default);
}

// A clear, custom exception for bad data.
public class DataFormatException : Exception
{
    public DataFormatException(string message) : base(message) { }
}

// Reads CSV of the form:  label,value  (one pair per line)
public class CsvDataSource : IDataSource
{
    public async Task<Dataset> LoadAsync(
        string path, string title, CancellationToken token = default)
    {
        if (!File.Exists(path))
            throw new FileNotFoundException($"Input file not found: {path}");

        string[] lines = await File.ReadAllLinesAsync(path, token);
        var points = new List<DataPoint>();

        for (int i = 0; i < lines.Length; i++)
        {
            string line = lines[i].Trim();

            // Skip blank lines and an optional header row.
            if (line.Length == 0) continue;
            if (i == 0 && !LooksLikeData(line)) continue;

            string[] parts = line.Split(',');
            if (parts.Length != 2)
                throw new DataFormatException(
                    $"Line {i + 1}: expected 'label,value' but got '{line}'.");

            string label = parts[0].Trim();
            if (!double.TryParse(parts[1].Trim(),
                    System.Globalization.NumberStyles.Any,
                    System.Globalization.CultureInfo.InvariantCulture,
                    out double value))
            {
                throw new DataFormatException(
                    $"Line {i + 1}: '{parts[1].Trim()}' is not a number.");
            }

            points.Add(new DataPoint(label, value));
        }

        if (points.Count == 0)
            throw new DataFormatException("No data rows found in the file.");

        return new Dataset(title, points);
    }

    // A row is data if its second field parses as a number.
    private static bool LooksLikeData(string line)
    {
        string[] parts = line.Split(',');
        return parts.Length == 2 &&
               double.TryParse(parts[1].Trim(),
                   System.Globalization.NumberStyles.Any,
                   System.Globalization.CultureInfo.InvariantCulture, out _);
    }
}
```

This uses async file I/O, `TryParse` for safe conversion, LINQ (via the record), custom exceptions with helpful messages, and culture-invariant parsing (so `.` is always the decimal separator).

---

## 5. Rendering: The Strategy Pattern

Each chart type is a **strategy** implementing a common interface. Create `IChartRenderer.cs`:

```csharp
namespace ChartForge;

// Contract: turn a Dataset into PNG image bytes.
public interface IChartRenderer
{
    ChartType Type { get; }
    byte[] Render(Dataset data, int width, int height);
}
```

`ChartService` will pick the renderer whose `Type` matches the requested `ChartType` — new chart types can be added without touching existing code (Open/Closed Principle).

---

## 6. The Bar Chart Renderer

Create `BarChartRenderer.cs`. This is where the SkiaSharp graphics skills come in.

```csharp
using SkiaSharp;

namespace ChartForge;

public class BarChartRenderer : IChartRenderer
{
    public ChartType Type => ChartType.Bar;

    public byte[] Render(Dataset data, int width, int height)
    {
        using var surface = SKSurface.Create(new SKImageInfo(width, height));
        var canvas = surface.Canvas;
        canvas.Clear(SKColors.White);

        const int marginLeft = 60, marginBottom = 60, marginTop = 50, marginRight = 30;
        int chartW = width - marginLeft - marginRight;
        int chartH = height - marginTop - marginBottom;

        double maxValue = data.Max <= 0 ? 1 : data.Max;

        using var typeface = SKTypeface.FromFamilyName("DejaVu Sans");
        using var labelFont = new SKFont(typeface, 12);
        using var titleFont = new SKFont(
            SKTypeface.FromFamilyName("DejaVu Sans", SKFontStyle.Bold), 20);
        using var textPaint = new SKPaint { Color = SKColors.Black, IsAntialias = true };
        using var axisPaint = new SKPaint
        {
            Color = SKColors.Black, IsStroke = true, StrokeWidth = 2, IsAntialias = true
        };

        // Title
        canvas.DrawText(data.Title, marginLeft, 30, SKTextAlign.Left, titleFont, textPaint);

        // Axes
        canvas.DrawLine(marginLeft, marginTop, marginLeft, marginTop + chartH, axisPaint);
        canvas.DrawLine(marginLeft, marginTop + chartH,
                        marginLeft + chartW, marginTop + chartH, axisPaint);

        // Bars
        int n = data.Points.Count;
        float slot = chartW / (float)n;
        float barW = slot * 0.6f;

        for (int i = 0; i < n; i++)
        {
            var point = data.Points[i];
            float barH = (float)(point.Value / maxValue * chartH);
            float x = marginLeft + i * slot + (slot - barW) / 2f;
            float y = marginTop + chartH - barH;

            var rect = SKRect.Create(x, y, barW, barH);
            using (var barPaint = new SKPaint { IsAntialias = true })
            {
                barPaint.Shader = SKShader.CreateLinearGradient(
                    new SKPoint(rect.Left, rect.Top),
                    new SKPoint(rect.Left, rect.Bottom),
                    new[] { SKColors.SteelBlue, SKColors.LightSkyBlue },
                    null, SKShaderTileMode.Clamp);
                canvas.DrawRect(rect, barPaint);
            }

            // Value above the bar
            canvas.DrawText(point.Value.ToString("0.#"),
                x + barW / 2f, y - 5, SKTextAlign.Center, labelFont, textPaint);

            // Category label below the axis
            canvas.DrawText(point.Label,
                x + barW / 2f, marginTop + chartH + 20,
                SKTextAlign.Center, labelFont, textPaint);
        }

        using var image = surface.Snapshot();
        using var encoded = image.Encode(SKEncodedImageFormat.Png, 100);
        return encoded.ToArray();
    }
}
```

---

## 7. The Line Chart Renderer

Create `LineChartRenderer.cs` — same contract, different drawing using an `SKPath`.

```csharp
using SkiaSharp;

namespace ChartForge;

public class LineChartRenderer : IChartRenderer
{
    public ChartType Type => ChartType.Line;

    public byte[] Render(Dataset data, int width, int height)
    {
        using var surface = SKSurface.Create(new SKImageInfo(width, height));
        var canvas = surface.Canvas;
        canvas.Clear(SKColors.White);

        const int marginLeft = 60, marginBottom = 60, marginTop = 50, marginRight = 30;
        int chartW = width - marginLeft - marginRight;
        int chartH = height - marginTop - marginBottom;

        double maxValue = data.Max <= 0 ? 1 : data.Max;

        using var typeface = SKTypeface.FromFamilyName("DejaVu Sans");
        using var labelFont = new SKFont(typeface, 12);
        using var titleFont = new SKFont(
            SKTypeface.FromFamilyName("DejaVu Sans", SKFontStyle.Bold), 20);
        using var textPaint = new SKPaint { Color = SKColors.Black, IsAntialias = true };
        using var axisPaint = new SKPaint
        {
            Color = SKColors.Black, IsStroke = true, StrokeWidth = 2, IsAntialias = true
        };
        using var linePaint = new SKPaint
        {
            Color = SKColors.OrangeRed, IsStroke = true, StrokeWidth = 3,
            IsAntialias = true, StrokeCap = SKStrokeCap.Round, StrokeJoin = SKStrokeJoin.Round
        };
        using var dotPaint = new SKPaint { Color = SKColors.DarkRed, IsAntialias = true };

        // Title & axes
        canvas.DrawText(data.Title, marginLeft, 30, SKTextAlign.Left, titleFont, textPaint);
        canvas.DrawLine(marginLeft, marginTop, marginLeft, marginTop + chartH, axisPaint);
        canvas.DrawLine(marginLeft, marginTop + chartH,
                        marginLeft + chartW, marginTop + chartH, axisPaint);

        int n = data.Points.Count;
        float stepX = n > 1 ? chartW / (float)(n - 1) : 0;

        // Build the line path and remember point positions.
        using var path = new SKPath();
        var positions = new SKPoint[n];

        for (int i = 0; i < n; i++)
        {
            float x = marginLeft + i * stepX;
            float y = marginTop + chartH - (float)(data.Points[i].Value / maxValue * chartH);
            positions[i] = new SKPoint(x, y);

            if (i == 0) path.MoveTo(x, y);
            else path.LineTo(x, y);
        }

        canvas.DrawPath(path, linePaint);

        // Draw markers + labels on top.
        for (int i = 0; i < n; i++)
        {
            canvas.DrawCircle(positions[i], 4, dotPaint);
            canvas.DrawText(data.Points[i].Value.ToString("0.#"),
                positions[i].X, positions[i].Y - 10, SKTextAlign.Center, labelFont, textPaint);
            canvas.DrawText(data.Points[i].Label,
                positions[i].X, marginTop + chartH + 20, SKTextAlign.Center, labelFont, textPaint);
        }

        using var image = surface.Snapshot();
        using var encoded = image.Encode(SKEncodedImageFormat.Png, 100);
        return encoded.ToArray();
    }
}
```

Notice both renderers share the same `IChartRenderer` contract, so the rest of the app doesn't care which one it's using — that's polymorphism and the Strategy pattern working together.

---

## 8. Wiring It Together: The App Service

`ChartService` orchestrates the workflow and receives its dependencies via **constructor injection**. Create `ChartService.cs`:

```csharp
namespace ChartForge;

public class ChartService
{
    private readonly IDataSource _dataSource;
    private readonly IReadOnlyList<IChartRenderer> _renderers;

    // Dependencies injected — the service creates nothing itself.
    public ChartService(IDataSource dataSource, IEnumerable<IChartRenderer> renderers)
    {
        _dataSource = dataSource;
        _renderers = renderers.ToList();
    }

    public async Task RunAsync(ChartOptions options, CancellationToken token = default)
    {
        // 1. Load and validate data.
        Dataset data = await _dataSource.LoadAsync(options.InputPath, options.Title, token);
        Console.WriteLine($"Loaded {data.Points.Count} data points from {options.InputPath}.");

        // 2. Select the renderer strategy for the requested chart type.
        IChartRenderer renderer =
            _renderers.FirstOrDefault(r => r.Type == options.Type)
            ?? throw new NotSupportedException($"No renderer for chart type '{options.Type}'.");

        // 3. Render to PNG bytes.
        byte[] png = renderer.Render(data, options.Width, options.Height);

        // 4. Write the output file.
        await File.WriteAllBytesAsync(options.OutputPath, png, token);
        Console.WriteLine($"Wrote {options.Type} chart to {options.OutputPath} ({png.Length} bytes).");
    }
}
```

---

## 9. Command-Line Parsing & Main

Create `Program.cs`. It parses arguments, composes the object graph (poor-man's DI), and handles errors gracefully.

```csharp
using ChartForge;

// --- Compose the dependency graph (composition root) ---
IDataSource dataSource = new CsvDataSource();
IChartRenderer[] renderers = { new BarChartRenderer(), new LineChartRenderer() };
var service = new ChartService(dataSource, renderers);

// --- Parse arguments ---
try
{
    ChartOptions options = ParseArgs(args);
    using var cts = new CancellationTokenSource(TimeSpan.FromSeconds(30));
    await service.RunAsync(options, cts.Token);
    return 0;
}
catch (Exception ex) when (
    ex is DataFormatException or FileNotFoundException or ArgumentException or NotSupportedException)
{
    // Expected, user-facing errors: friendly message, no stack trace.
    Console.Error.WriteLine($"Error: {ex.Message}");
    PrintUsage();
    return 1;
}
catch (Exception ex)
{
    // Unexpected errors.
    Console.Error.WriteLine($"Unexpected error: {ex}");
    return 2;
}

// --- Helpers (local functions) ---
static ChartOptions ParseArgs(string[] args)
{
    var map = new Dictionary<string, string>();
    for (int i = 0; i < args.Length - 1; i += 2)
        map[args[i].TrimStart('-').ToLowerInvariant()] = args[i + 1];

    string input = map.GetValueOrDefault("input")
        ?? throw new ArgumentException("Missing required --input <file.csv>");
    string output = map.GetValueOrDefault("output", "chart.png");
    string title = map.GetValueOrDefault("title", "Chart");
    string typeText = map.GetValueOrDefault("type", "bar").ToLowerInvariant();

    ChartType type = typeText switch
    {
        "bar"  => ChartType.Bar,
        "line" => ChartType.Line,
        _      => throw new ArgumentException($"Unknown chart type '{typeText}'. Use bar or line.")
    };

    int width = int.TryParse(map.GetValueOrDefault("width"), out int w) ? w : 800;
    int height = int.TryParse(map.GetValueOrDefault("height"), out int h) ? h : 500;

    return new ChartOptions(input, output, type, title, width, height);
}

static void PrintUsage()
{
    Console.WriteLine();
    Console.WriteLine("Usage:");
    Console.WriteLine("  dotnet run -- --input <file.csv> [--output chart.png] " +
                      "[--type bar|line] [--title \"My Chart\"] [--width 800] [--height 500]");
}
```

> This `Program.cs` uses **top-level statements** (no explicit `class`/`Main`). The `return` values become the process exit code — useful for scripts and CI.

---

## 10. Unit Tests

Because we programmed to interfaces, we can test the core logic without touching the disk or rendering real images. Create a test project:

```bash
cd ..
dotnet new xunit -n ChartForge.Tests
cd ChartForge.Tests
dotnet add reference ../ChartForge/ChartForge.csproj
```

Add `CoreTests.cs`:

```csharp
using ChartForge;
using Xunit;

public class CsvDataSourceTests
{
    [Fact]
    public async Task LoadAsync_ParsesValidCsv()
    {
        // Arrange: write a temp CSV.
        string path = Path.GetTempFileName();
        await File.WriteAllTextAsync(path, "Jan,10\nFeb,20\nMar,30\n");
        var source = new CsvDataSource();

        // Act
        Dataset data = await source.LoadAsync(path, "Test");

        // Assert
        Assert.Equal(3, data.Points.Count);
        Assert.Equal("Jan", data.Points[0].Label);
        Assert.Equal(30, data.Max);
        File.Delete(path);
    }

    [Fact]
    public async Task LoadAsync_ThrowsOnNonNumericValue()
    {
        string path = Path.GetTempFileName();
        await File.WriteAllTextAsync(path, "Jan,notanumber\n");
        var source = new CsvDataSource();

        await Assert.ThrowsAsync<DataFormatException>(
            () => source.LoadAsync(path, "Test"));
        File.Delete(path);
    }

    [Fact]
    public async Task LoadAsync_ThrowsOnEmptyFile()
    {
        string path = Path.GetTempFileName();
        await File.WriteAllTextAsync(path, "");
        var source = new CsvDataSource();

        await Assert.ThrowsAsync<DataFormatException>(
            () => source.LoadAsync(path, "Test"));
        File.Delete(path);
    }
}

public class ChartServiceTests
{
    // A fake data source — no file system needed.
    private class FakeSource : IDataSource
    {
        public Task<Dataset> LoadAsync(string path, string title, CancellationToken token = default)
            => Task.FromResult(new Dataset(title, new[]
            {
                new DataPoint("A", 1), new DataPoint("B", 2)
            }));
    }

    // A fake renderer that records it was called.
    private class FakeRenderer : IChartRenderer
    {
        public ChartType Type { get; }
        public bool WasCalled { get; private set; }
        public FakeRenderer(ChartType type) => Type = type;
        public byte[] Render(Dataset data, int width, int height)
        {
            WasCalled = true;
            return new byte[] { 1, 2, 3 };
        }
    }

    [Fact]
    public async Task RunAsync_SelectsRendererMatchingChartType()
    {
        var bar = new FakeRenderer(ChartType.Bar);
        var line = new FakeRenderer(ChartType.Line);
        var service = new ChartService(new FakeSource(), new IChartRenderer[] { bar, line });

        string output = Path.GetTempFileName();
        var options = new ChartOptions("ignored.csv", output, ChartType.Line, "T");

        await service.RunAsync(options);

        Assert.True(line.WasCalled);    // the Line strategy was chosen
        Assert.False(bar.WasCalled);    // the Bar strategy was not
        File.Delete(output);
    }
}
```

Run the tests:

```bash
dotnet test
```

These tests demonstrate the payoff of the architecture: the Strategy selection and CSV parsing are verified in milliseconds, with fakes standing in for real dependencies.

---

## 11. Building and Running

Create a sample `data.csv`:

```csv
Month,Sales
Jan,120
Feb,200
Mar,150
Apr,80
May,220
Jun,190
```

Then, from the `ChartForge` project folder:

```bash
# Bar chart
dotnet run -- --input data.csv --output bar.png --type bar --title "Quarterly Sales"

# Line chart
dotnet run -- --input data.csv --output line.png --type line --title "Sales Trend"
```

Open `bar.png` and `line.png` to see your results.

### Pure-Mono alternative

If you prefer classic Mono without the SDK, you can still compile against SkiaSharp, but you must supply the assembly and native library paths manually. The SDK path above is strongly recommended for multi-file projects with NuGet packages. The C# source is identical either way.

---

## 12. Extension Challenges

Grow the project to reinforce your skills:

1. **Add a pie chart renderer** — implement `IChartRenderer` with `Type => ChartType.Pie`, using `canvas.DrawArc(..., useCenter: true, ...)`. Add `Pie` to the enum and register it in `Program.cs`. Notice you don't touch `ChartService` at all — that's the Open/Closed Principle.
2. **Support a JSON data source** — add a `JsonDataSource : IDataSource` and pick it based on the input file extension.
3. **Add gridlines and Y-axis tick labels** to make charts more readable.
4. **Multi-series support** — extend `Dataset` to hold multiple series and draw several lines with a legend.
5. **Async batch mode** — read a folder of CSVs and render them all concurrently with `Task.WhenAll` (see the Advanced tutorial).
6. **Add a `--theme dark` option** — swap the color palette via another strategy.

Each challenge maps to a concept from the series: interfaces, DI, async, records, and drawing.

---

## 13. What You Practiced

This one project exercised the entire curriculum:

| Concept | Where it appears |
|---------|------------------|
| Variables, control flow, loops | Throughout |
| Methods & local functions | `ParseArgs`, helpers in `Program.cs` |
| Classes & encapsulation | Every component |
| Records & immutability | `DataPoint`, `Dataset`, `ChartOptions` |
| Enums | `ChartType` |
| Interfaces | `IDataSource`, `IChartRenderer` |
| Polymorphism | Renderers sharing one contract |
| Generics & collections | `IReadOnlyList<DataPoint>`, dictionaries |
| LINQ | `Max`, `Min`, `FirstOrDefault`, `Select` |
| Exception handling & custom exceptions | `DataFormatException`, `Program.cs` |
| Async/await & cancellation | File I/O, `CancellationTokenSource` |
| Dependency injection | `ChartService` constructor |
| Strategy pattern | Renderer selection by `ChartType` |
| 2D graphics (SkiaSharp) | Both renderers |
| Unit testing with fakes | `ChartForge.Tests` |
| CLI design & exit codes | `Program.cs` |

If you built this end to end and made the tests pass, you've integrated everything from the [Beginner](./CSharp-Mono-Beginner-Tutorial.md), [Intermediate/OOP](./CSharp-Mono-Intermediate-OOP-Tutorial.md), [Advanced](./CSharp-Mono-Advanced-Tutorial.md), and [SkiaSharp](./SkiaSharp-Tutorial.md) tutorials into a single, real application.

Congratulations — you've completed the C# with Mono series! 🎓🚀

# ChartForge

A small command-line tool that reads numeric data from a CSV file and renders it as a **bar** or **line** chart PNG using [SkiaSharp](https://github.com/mono/SkiaSharp).

This is the capstone project for the *C# with Mono* tutorial series. It brings together
records, interfaces, generics, LINQ, async/await, cancellation, dependency injection,
the Strategy pattern, 2D graphics, and unit testing in one runnable application. See the
companion tutorial: `../Tutorials/CSharp-Mono-Capstone-ChartForge.md`.

```
data.csv  ──►  ChartForge  ──►  chart.png
```

## Requirements

- [.NET SDK 8.0](https://aka.ms/dotnet/download) or later.
  (This machine has the .NET *runtimes* but not the SDK — install the SDK to build.)
- On Linux, text rendering needs `fontconfig` and a font (e.g. `fonts-dejavu`).

Check your SDK:

```bash
dotnet --version
```

## Project layout

```
ChartForge.sln
├── ChartForge/                 # the application
│   ├── ChartForge.csproj
│   ├── Program.cs              # CLI entry point (composition root + arg parsing)
│   ├── Dataset.cs              # DataPoint / Dataset records, ChartType enum, ChartOptions
│   ├── IDataSource.cs          # IDataSource contract, CsvDataSource, DataFormatException
│   ├── IChartRenderer.cs       # rendering contract
│   ├── BarChartRenderer.cs     # SkiaSharp bar chart strategy
│   ├── LineChartRenderer.cs    # SkiaSharp line chart strategy
│   ├── ChartService.cs         # orchestration via dependency injection
│   └── data.csv                # sample data
└── ChartForge.Tests/           # xUnit tests
    ├── ChartForge.Tests.csproj
    └── CoreTests.cs            # CSV parsing + renderer-selection tests (uses fakes)
```

## Build

```bash
# From the solution folder (D:\CodingDojo)
dotnet build ChartForge.sln
```

## Run

```bash
cd ChartForge

# Bar chart
dotnet run -- --input data.csv --output bar.png --type bar --title "Quarterly Sales"

# Line chart
dotnet run -- --input data.csv --output line.png --type line --title "Sales Trend"
```

Open `bar.png` / `line.png` to view the result.

### Command-line options

| Option      | Required | Default     | Description                          |
|-------------|----------|-------------|--------------------------------------|
| `--input`   | yes      | —           | Path to the input CSV file.          |
| `--output`  | no       | `chart.png` | Path to write the PNG image.         |
| `--type`    | no       | `bar`       | `bar` or `line`.                     |
| `--title`   | no       | `Chart`     | Chart title text.                    |
| `--width`   | no       | `800`       | Image width in pixels.               |
| `--height`  | no       | `500`       | Image height in pixels.              |

Exit codes: `0` success, `1` user/input error, `2` unexpected error.

## Input format

CSV with one `label,value` pair per line. An optional header row is auto-detected and skipped:

```csv
Month,Sales
Jan,120
Feb,200
Mar,150
```

Values use `.` as the decimal separator (culture-invariant).

## Test

```bash
# From the solution folder
dotnet test
```

The tests use hand-written fakes for `IDataSource` and `IChartRenderer`, so they verify
CSV parsing and Strategy selection in milliseconds without touching the disk or rendering
real images.

## Notes

- On **Windows**, SkiaSharp uses the OS-native libraries, so the base `SkiaSharp` package
  is sufficient. The `SkiaSharp.NativeAssets.Linux` reference is included so the same
  project also builds and runs on Linux; it is harmless on Windows.
- To extend the tool (pie charts, JSON input, dark themes, batch mode), see the
  "Extension Challenges" section of the capstone tutorial.

## License

Sample/educational code — use freely.

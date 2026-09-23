# SkiaSharp 2D Graphics — A Practical Tutorial (GDI+ Companion)

This is the companion to the [GDI+ on Mono tutorial](./GDIPlus-Mono-Tutorial.md). Where GDI+/`System.Drawing` is a mature but increasingly Windows-bound API, **SkiaSharp** is a modern, cross-platform 2D graphics library that runs identically on Windows, Linux, macOS, Android, iOS, and WebAssembly. It's the recommended path for new cross-platform drawing code on .NET.

SkiaSharp is a .NET binding over Google's **Skia** engine — the same renderer used by Chrome, Android, and Flutter. It is fully managed to consume (native Skia binaries ship inside the NuGet package), hardware-friendly, and actively maintained by the Mono/.NET Foundation team.

> **How this relates to GDI+:** the drawing *concepts* transfer directly — you still draw lines, shapes, text, and images onto a surface. The main differences are:
> - Skia uses a single `SKPaint` object to describe **both** stroke and fill (GDI+ splits this into `Pen` and `Brush`).
> - Skia's `SKCanvas` is the drawing surface (equivalent to GDI+ `Graphics`).
> - Colors, points, and rectangles use `SK`-prefixed types (`SKColor`, `SKPoint`, `SKRect`).

---

## Table of Contents

1. [Prerequisites](#1-prerequisites)
2. [Project Setup and Installation](#2-project-setup-and-installation)
3. [Your First SkiaSharp Program](#3-your-first-skiasharp-program)
4. [Core SkiaSharp Concepts](#4-core-skiasharp-concepts)
5. [The SKPaint Object](#5-the-skpaint-object)
6. [Drawing Primitives](#6-drawing-primitives)
7. [Paths](#7-paths)
8. [Gradients and Shaders](#8-gradients-and-shaders)
9. [Drawing Text](#9-drawing-text)
10. [Images and Bitmaps](#10-images-and-bitmaps)
11. [Transformations and Clipping](#11-transformations-and-clipping)
12. [A Complete Example: Rendering a Chart](#12-a-complete-example-rendering-a-chart)
13. [GDI+ to SkiaSharp Cheat Sheet](#13-gdi-to-skiasharp-cheat-sheet)
14. [Troubleshooting](#14-troubleshooting)
15. [Where to Go Next](#15-where-to-go-next)

---

## 1. Prerequisites

- Basic C# knowledge.
- The **.NET SDK** (6.0 or later recommended). Check with:

```bash
dotnet --version
```

- A terminal and a text editor / IDE (VS Code, Rider, Visual Studio).

> Unlike GDI+ on Mono, SkiaSharp does **not** require installing a separate native library by hand — the native Skia binaries are bundled in the NuGet package for each supported platform.

### Linux note

On Linux you typically need a couple of common system libraries that Skia depends on for font handling. On headless servers install:

```bash
# Debian/Ubuntu — fontconfig is needed for text; the rest are common deps
sudo apt update
sudo apt install libfontconfig1
```

If you don't need text rendering, even this may be unnecessary. There is also a `SkiaSharp.NativeAssets.Linux.NoDependencies` package for minimal/container environments.

---

## 2. Project Setup and Installation

Create a new console project and add the SkiaSharp NuGet package:

```bash
dotnet new console -n SkiaDemo
cd SkiaDemo
dotnet add package SkiaSharp
```

For headless Linux/container scenarios you may also want:

```bash
# Full Linux native assets (includes font dependencies)
dotnet add package SkiaSharp.NativeAssets.Linux

# OR the minimal variant with no external .so dependencies
dotnet add package SkiaSharp.NativeAssets.Linux.NoDependencies
```

Your `SkiaDemo.csproj` should look roughly like:

```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>net8.0</TargetFramework>
    <Nullable>enable</Nullable>
  </PropertyGroup>
  <ItemGroup>
    <PackageReference Include="SkiaSharp" Version="2.88.8" />
  </ItemGroup>
</Project>
```

> Pin to a specific version (as shown) rather than an open range so builds stay reproducible. Check the [SkiaSharp NuGet page](https://www.nuget.org/packages/SkiaSharp) for the current stable version.

---

## 3. Your First SkiaSharp Program

Let's reproduce the "red rectangle with a blue border" example from the GDI+ tutorial, so you can compare the two APIs side by side.

Replace `Program.cs` with:

```csharp
using SkiaSharp;

// Create a 400x300 raster surface.
var info = new SKImageInfo(400, 300);
using var surface = SKSurface.Create(info);
SKCanvas canvas = surface.Canvas;

// Fill the whole surface with white.
canvas.Clear(SKColors.White);

// Fill a red rectangle.
var rect = new SKRect(50, 50, 350, 250); // left, top, right, bottom
using (var fill = new SKPaint { Color = SKColors.Red, IsAntialias = true })
{
    canvas.DrawRect(rect, fill);
}

// Draw a blue outline around it.
using (var stroke = new SKPaint
{
    Color = SKColors.Blue,
    IsStroke = true,
    StrokeWidth = 3,
    IsAntialias = true
})
{
    canvas.DrawRect(rect, stroke);
}

// Encode the surface to a PNG file.
using (var image = surface.Snapshot())
using (var data = image.Encode(SKEncodedImageFormat.Png, 100))
using (var stream = File.OpenWrite("output.png"))
{
    data.SaveTo(stream);
}

Console.WriteLine("Saved output.png");
```

Run it:

```bash
dotnet run
```

Open `output.png` — same result as the GDI+ example, but this code runs unchanged on Windows, Linux, and macOS.

> **Key contrast with GDI+:** note how `SKRect` is defined by **left, top, right, bottom** — not `x, y, width, height` like GDI+'s `Rectangle`. Use `SKRect.Create(x, y, width, height)` if you prefer the GDI+ style.

---

## 4. Core SkiaSharp Concepts

| SkiaSharp type | Purpose | GDI+ equivalent |
|----------------|---------|-----------------|
| `SKSurface` | An allocated drawing target (raster or GPU). | (implicit in `Graphics.FromImage`) |
| `SKCanvas` | The drawing surface — every draw call is a method on it. | `Graphics` |
| `SKPaint` | Describes how things are drawn: color, stroke/fill, width, font, anti-alias, shaders. | `Pen` **and** `Brush` combined |
| `SKColor` | An ARGB color. | `Color` |
| `SKPoint` | A floating-point coordinate. | `PointF` |
| `SKRect` | A rectangle (left, top, right, bottom). | `RectangleF` |
| `SKPath` | A composable geometry (lines, curves, arcs). | `GraphicsPath` |
| `SKBitmap` / `SKImage` | Raster image data. | `Bitmap` / `Image` |
| `SKShader` | A fill source: gradient, image, noise, etc. | `LinearGradientBrush`, `TextureBrush` |
| `SKTypeface` / `SKFont` | Typeface and sizing for text. | `Font` |

### Coordinate system

Identical to GDI+: origin `(0, 0)` at the **top-left**, X increases right, Y increases down, units in pixels.

### The `IDisposable` rule (still applies)

`SKSurface`, `SKCanvas` (owned by its surface), `SKPaint`, `SKPath`, `SKBitmap`, `SKImage`, `SKData`, `SKTypeface`, and `SKFont` all wrap native Skia resources. Wrap them in `using` blocks/declarations to release native memory promptly.

---

## 5. The SKPaint Object

`SKPaint` is the heart of SkiaSharp. A single paint controls whether you stroke, fill, or both, plus color, anti-aliasing, and effects.

```csharp
using var paint = new SKPaint
{
    Color        = SKColors.DarkOrange,
    IsAntialias  = true,
    Style        = SKPaintStyle.StrokeAndFill, // Fill | Stroke | StrokeAndFill
    StrokeWidth  = 4,
    StrokeCap    = SKStrokeCap.Round,          // Butt | Round | Square
    StrokeJoin   = SKStrokeJoin.Round          // Miter | Round | Bevel
};
```

`Style` replaces GDI+'s "do I use a Pen or a Brush?" decision:

- `SKPaintStyle.Fill` → like using a `Brush`.
- `SKPaintStyle.Stroke` → like using a `Pen`.
- `SKPaintStyle.StrokeAndFill` → both in one draw call.

### Dashed strokes

```csharp
using var dashed = new SKPaint
{
    Color       = SKColors.Black,
    IsStroke    = true,
    StrokeWidth = 2,
    PathEffect  = SKPathEffect.CreateDash(new float[] { 10, 5 }, phase: 0)
};
```

### Transparency

`SKColor` includes an alpha channel:

```csharp
var translucentRed = new SKColor(255, 0, 0, 128); // R, G, B, A
// or
var alsoTranslucent = SKColors.Red.WithAlpha(128);
```

---

## 6. Drawing Primitives

All examples assume you have an `SKCanvas canvas` and an `SKPaint paint`.

### Lines

```csharp
using var pen = new SKPaint { Color = SKColors.Black, IsStroke = true, StrokeWidth = 2, IsAntialias = true };

canvas.DrawLine(10, 10, 200, 100, pen);

// A connected polyline via a path.
using var poly = new SKPath();
poly.MoveTo(10, 150);
poly.LineTo(60, 120);
poly.LineTo(110, 170);
poly.LineTo(160, 130);
canvas.DrawPath(poly, pen);
```

### Rectangles

```csharp
var r = SKRect.Create(20, 20, 120, 80); // x, y, width, height

using var fill = new SKPaint { Color = SKColors.LightGreen, IsAntialias = true };
using var edge = new SKPaint { Color = SKColors.DarkGreen, IsStroke = true, StrokeWidth = 2, IsAntialias = true };

canvas.DrawRect(r, fill);
canvas.DrawRect(r, edge);

// Rounded rectangle:
canvas.DrawRoundRect(r, rx: 12, ry: 12, fill);
```

### Circles and Ovals

```csharp
using var pen = new SKPaint { Color = SKColors.Purple, IsStroke = true, StrokeWidth = 2, IsAntialias = true };

canvas.DrawCircle(cx: 150, cy: 150, radius: 50, pen);
canvas.DrawOval(SKRect.Create(50, 50, 200, 100), pen);
```

### Arcs

```csharp
using var pen = new SKPaint { Color = SKColors.Orange, IsStroke = true, StrokeWidth = 2, IsAntialias = true };

var oval = SKRect.Create(20, 20, 150, 150);
canvas.DrawArc(oval, startAngle: 0, sweepAngle: 90, useCenter: false, pen);

// useCenter: true draws a pie slice.
using var slice = new SKPaint { Color = SKColors.Gold, IsAntialias = true };
canvas.DrawArc(SKRect.Create(200, 20, 150, 150), 45, 120, useCenter: true, slice);
```

### Polygons

Skia has no direct polygon call — build one with an `SKPath`:

```csharp
using var triangle = new SKPath();
triangle.MoveTo(100, 20);
triangle.LineTo(180, 160);
triangle.LineTo(20, 160);
triangle.Close();

using var fill = new SKPaint { Color = SKColors.SkyBlue, IsAntialias = true };
using var edge = new SKPaint { Color = SKColors.Navy, IsStroke = true, StrokeWidth = 2, IsAntialias = true };

canvas.DrawPath(triangle, fill);
canvas.DrawPath(triangle, edge);
```

---

## 7. Paths

`SKPath` is Skia's equivalent of `GraphicsPath` — a reusable geometry made of line, curve, and arc segments. It's central to Skia because polygons, curves, and complex shapes are all built from paths.

```csharp
using var path = new SKPath();

path.MoveTo(20, 200);                       // start point
path.CubicTo(80, 20, 160, 380, 220, 200);   // Bézier curve (2 control points + end)
path.QuadTo(260, 100, 300, 200);            // quadratic curve (1 control point + end)
path.LineTo(300, 300);
path.Close();                               // connect back to the start

using var paint = new SKPaint { Color = SKColors.Crimson, IsStroke = true, StrokeWidth = 2, IsAntialias = true };
canvas.DrawPath(path, paint);
```

Paths also support fill rules, adding whole shapes (`AddRect`, `AddCircle`, `AddOval`), and boolean operations via `SKPath.Op`.

---

## 8. Gradients and Shaders

In SkiaSharp, gradients and textures are **shaders** assigned to a paint's `Shader` property.

### Linear gradient

```csharp
var rect = SKRect.Create(0, 0, 300, 200);
using var paint = new SKPaint { IsAntialias = true };

paint.Shader = SKShader.CreateLinearGradient(
    start:  new SKPoint(rect.Left, rect.Top),
    end:    new SKPoint(rect.Right, rect.Top),
    colors: new[] { SKColors.Blue, SKColors.Cyan },
    colorPos: null,                       // even distribution
    mode:   SKShaderTileMode.Clamp);

canvas.DrawRect(rect, paint);
```

### Radial gradient

```csharp
using var paint = new SKPaint { IsAntialias = true };
paint.Shader = SKShader.CreateRadialGradient(
    center: new SKPoint(150, 150),
    radius: 100,
    colors: new[] { SKColors.White, SKColors.DarkBlue },
    colorPos: null,
    mode: SKShaderTileMode.Clamp);

canvas.DrawCircle(150, 150, 100, paint);
```

### Image (texture) shader

```csharp
using var texture = SKBitmap.Decode("pattern.png");
using var paint = new SKPaint();
paint.Shader = SKShader.CreateBitmap(
    texture, SKShaderTileMode.Repeat, SKShaderTileMode.Repeat);

canvas.DrawCircle(150, 150, 150, paint);
```

---

## 9. Drawing Text

Modern SkiaSharp draws text with an `SKFont` plus an `SKPaint`.

```csharp
using var typeface = SKTypeface.FromFamilyName("DejaVu Sans", SKFontStyle.Bold);
using var font = new SKFont(typeface, size: 24);
using var paint = new SKPaint { Color = SKColors.Black, IsAntialias = true };

// Note: the y coordinate is the text BASELINE, not the top of the text.
canvas.DrawText("Hello, SkiaSharp!", x: 20, y: 44, SKTextAlign.Left, font, paint);
```

> **Font availability on Linux:** just like GDI+, the font family must exist on the system. Use `SKTypeface.FromFamilyName(null)` for the default, embed a `.ttf` via `SKTypeface.FromFile("font.ttf")`, or install font packages. On headless containers ensure `fontconfig` is present.

### Measuring text

```csharp
float width = font.MeasureText("Some text", out SKRect bounds, paint);
Console.WriteLine($"Advance width: {width}, bounds: {bounds.Width} x {bounds.Height}");
```

### Centering text

```csharp
canvas.DrawText("Centered", x: canvasWidth / 2f, y: 100,
    SKTextAlign.Center, font, paint);
```

`SKTextAlign.Center` handles horizontal centering; for vertical centering, offset `y` using the font metrics (`font.Metrics.Ascent` / `Descent`).

---

## 10. Images and Bitmaps

### Loading and drawing an image

```csharp
using var source = SKBitmap.Decode("photo.jpg");

// Draw at native size at (10, 10).
canvas.DrawBitmap(source, 10, 10);

// Draw scaled into a destination rectangle.
canvas.DrawBitmap(source, SKRect.Create(0, 0, 100, 100));
```

### Manipulating pixels

```csharp
using var bmp = new SKBitmap(256, 256);
for (int y = 0; y < bmp.Height; y++)
    for (int x = 0; x < bmp.Width; x++)
        bmp.SetPixel(x, y, new SKColor((byte)x, (byte)y, 128));

using var img = SKImage.FromBitmap(bmp);
using var data = img.Encode(SKEncodedImageFormat.Png, 100);
using var fs = File.OpenWrite("gradient.png");
data.SaveTo(fs);
```

> For performance-critical pixel work, use `SKBitmap.GetPixels()` to get an `IntPtr` to the raw buffer instead of per-pixel `SetPixel`.

### Saving in different formats

```csharp
image.Encode(SKEncodedImageFormat.Png,  100); // lossless
image.Encode(SKEncodedImageFormat.Jpeg, 90);  // quality 0-100
image.Encode(SKEncodedImageFormat.Webp, 90);
```

---

## 11. Transformations and Clipping

`SKCanvas` maintains a transform matrix and a clip region, both saved/restored with `Save`/`Restore`.

```csharp
int state = canvas.Save();

canvas.Translate(200, 150);   // move origin to center
canvas.RotateDegrees(45);     // rotate 45 degrees
canvas.Scale(1.5f, 1.5f);     // scale up 50%

using var paint = new SKPaint { Color = SKColors.Tomato, IsAntialias = true };
canvas.DrawRect(SKRect.Create(-50, -25, 100, 50), paint);

canvas.RestoreToCount(state); // undo all transforms since Save()
```

### Clipping

```csharp
int s = canvas.Save();

canvas.ClipRect(SKRect.Create(50, 50, 200, 200));
// Everything drawn now is confined to that rectangle.
canvas.DrawCircle(150, 150, 150, paint);

canvas.RestoreToCount(s);
```

You can also clip to an arbitrary `SKPath` with `canvas.ClipPath(path)` — handy for non-rectangular masks that GDI+ makes awkward.

---

## 12. A Complete Example: Rendering a Chart

This mirrors the bar-chart example from the GDI+ tutorial so you can compare the two implementations directly.

Put this in `Program.cs`:

```csharp
using SkiaSharp;

int width = 600, height = 400;
string[] labels = { "Jan", "Feb", "Mar", "Apr", "May" };
int[] values     = { 120, 200, 150, 80, 220 };

var info = new SKImageInfo(width, height);
using var surface = SKSurface.Create(info);
SKCanvas canvas = surface.Canvas;
canvas.Clear(SKColors.White);

// Chart area margins.
int marginLeft = 50, marginBottom = 50, marginTop = 30;
int chartWidth  = width  - marginLeft - 20;
int chartHeight = height - marginBottom - marginTop;

int maxValue = 0;
foreach (var v in values) if (v > maxValue) maxValue = v;

// Axes.
using (var axisPaint = new SKPaint
{
    Color = SKColors.Black, IsStroke = true, StrokeWidth = 2, IsAntialias = true
})
{
    canvas.DrawLine(marginLeft, marginTop, marginLeft, marginTop + chartHeight, axisPaint);      // Y
    canvas.DrawLine(marginLeft, marginTop + chartHeight,
                    marginLeft + chartWidth, marginTop + chartHeight, axisPaint);                 // X
}

// Fonts.
using var typeface = SKTypeface.FromFamilyName("DejaVu Sans");
using var labelFont = new SKFont(typeface, 12);
using var titleFont = new SKFont(SKTypeface.FromFamilyName("DejaVu Sans", SKFontStyle.Bold), 16);
using var textPaint  = new SKPaint { Color = SKColors.Black, IsAntialias = true };
using var titlePaint = new SKPaint { Color = SKColors.DarkSlateGray, IsAntialias = true };

// Bars.
int barCount  = values.Length;
int slotWidth = chartWidth / barCount;
int barWidth  = (int)(slotWidth * 0.6);

for (int i = 0; i < barCount; i++)
{
    int barHeight = (int)((double)values[i] / maxValue * chartHeight);
    float x = marginLeft + i * slotWidth + (slotWidth - barWidth) / 2f;
    float y = marginTop + chartHeight - barHeight;

    var barRect = SKRect.Create(x, y, barWidth, barHeight);

    using (var barPaint = new SKPaint { IsAntialias = true })
    {
        barPaint.Shader = SKShader.CreateLinearGradient(
            new SKPoint(barRect.Left, barRect.Top),
            new SKPoint(barRect.Left, barRect.Bottom),
            new[] { SKColors.SteelBlue, SKColors.LightSkyBlue },
            null, SKShaderTileMode.Clamp);
        canvas.DrawRect(barRect, barPaint);
    }

    // Value label above the bar (centered on the bar).
    string valText = values[i].ToString();
    canvas.DrawText(valText, x + barWidth / 2f, y - 4, SKTextAlign.Center, labelFont, textPaint);

    // Category label below the axis.
    canvas.DrawText(labels[i], x + barWidth / 2f,
        marginTop + chartHeight + 18, SKTextAlign.Center, labelFont, textPaint);
}

// Title.
canvas.DrawText("Monthly Sales", marginLeft, 22, SKTextAlign.Left, titleFont, titlePaint);

// Save.
using (var image = surface.Snapshot())
using (var data = image.Encode(SKEncodedImageFormat.Png, 100))
using (var stream = File.OpenWrite("barchart.png"))
{
    data.SaveTo(stream);
}

Console.WriteLine("Saved barchart.png");
```

Run it:

```bash
dotnet run
```

Open `barchart.png`. The output matches the GDI+ version, but this program is cross-platform with zero manual native setup on Windows/macOS.

---

## 13. GDI+ to SkiaSharp Cheat Sheet

| Task | GDI+ (`System.Drawing`) | SkiaSharp |
|------|-------------------------|-----------|
| Drawing surface | `Graphics` | `SKCanvas` |
| Create off-screen target | `new Bitmap(w, h)` + `Graphics.FromImage` | `SKSurface.Create(new SKImageInfo(w, h))` |
| Outline style | `Pen` | `SKPaint { IsStroke = true }` |
| Fill style | `Brush` | `SKPaint { Style = Fill }` |
| Color | `Color.FromArgb(a, r, g, b)` | `new SKColor(r, g, b, a)` |
| Rectangle | `new Rectangle(x, y, w, h)` | `SKRect.Create(x, y, w, h)` |
| Draw line | `g.DrawLine(pen, x1, y1, x2, y2)` | `canvas.DrawLine(x1, y1, x2, y2, paint)` |
| Fill rect | `g.FillRectangle(brush, rect)` | `canvas.DrawRect(rect, paint)` |
| Draw ellipse | `g.DrawEllipse(pen, rect)` | `canvas.DrawOval(rect, paint)` |
| Circle | `g.DrawEllipse(pen, x, y, d, d)` | `canvas.DrawCircle(cx, cy, r, paint)` |
| Polygon | `g.FillPolygon(brush, points)` | `SKPath` + `canvas.DrawPath` |
| Complex path | `GraphicsPath` | `SKPath` |
| Gradient fill | `LinearGradientBrush` | `SKShader.CreateLinearGradient` |
| Texture fill | `TextureBrush` | `SKShader.CreateBitmap` |
| Text | `g.DrawString(text, font, brush, pt)` | `canvas.DrawText(text, x, y, font, paint)` |
| Anti-alias | `g.SmoothingMode = AntiAlias` | `paint.IsAntialias = true` (per paint) |
| Save/restore state | `g.Save()` / `g.Restore(state)` | `canvas.Save()` / `canvas.RestoreToCount(n)` |
| Translate/rotate/scale | `g.TranslateTransform` etc. | `canvas.Translate` / `RotateDegrees` / `Scale` |
| Save PNG | `bitmap.Save("f.png", ImageFormat.Png)` | `image.Encode(...).SaveTo(stream)` |

**Two big mental shifts:**
1. **One paint, not Pen + Brush.** `SKPaint.Style` decides stroke vs. fill.
2. **Text y is the baseline**, not the top-left corner as in GDI+'s `DrawString`.

---

## 14. Troubleshooting

### `DllNotFoundException: libSkiaSharp`

The native asset for your platform wasn't restored. Ensure the correct package is referenced:

- Windows/macOS: the base `SkiaSharp` package includes natives.
- Linux: add `SkiaSharp.NativeAssets.Linux` (or `...Linux.NoDependencies` for minimal containers).

Then `dotnet restore` and rebuild.

### Text throws or renders nothing on Linux/containers

Skia needs **fontconfig** and at least one installed font.

```bash
sudo apt install libfontconfig1 fontconfig fonts-dejavu
```

In minimal containers, either install fonts or embed a `.ttf` with `SKTypeface.FromFile(...)`.

### Text appears clipped or positioned oddly

Remember `DrawText`'s `y` is the **baseline**. To position by the top edge, offset by the font ascent: `y = top - font.Metrics.Ascent`.

### Jagged edges

Anti-aliasing is per-paint in Skia. Set `IsAntialias = true` on each `SKPaint`.

### Slow pixel loops

Avoid `SKBitmap.SetPixel` in tight loops; use `GetPixels()` for direct buffer access.

---

## 15. Where to Go Next

- **GPU acceleration:** create a GPU-backed surface with `SKSurface.Create(GRContext, ...)` for OpenGL/Vulkan/Metal rendering.
- **UI integration:** use `SkiaSharp.Views` for WinForms, WPF, MAUI, Avalonia, Blazor, and Uno — each provides an `SKCanvasView`/`SKGLView` control with a paint callback.
- **SVG:** the `Svg.Skia` community library renders SVG onto an `SKCanvas`.
- **Animation:** `SkiaSharp.Skottie` plays Lottie/Bodymovin animations.
- **Official resources:** the [SkiaSharp GitHub repo](https://github.com/mono/SkiaSharp) and [API docs](https://learn.microsoft.com/dotnet/api/skiasharp) — the latter has extensive per-type examples.

---

### Quick Reference

```csharp
// Surface + canvas
using var surface = SKSurface.Create(new SKImageInfo(w, h));
var canvas = surface.Canvas;
canvas.Clear(SKColors.White);

// One paint, choose stroke or fill
using var paint = new SKPaint { Color = SKColors.Black, IsAntialias = true };
paint.Style = SKPaintStyle.Stroke;   // or Fill, or StrokeAndFill

// Draw
canvas.DrawLine / DrawRect / DrawCircle / DrawOval / DrawArc / DrawPath(...);
canvas.DrawText(text, x, yBaseline, SKTextAlign.Left, font, paint);

// Export
using var img  = surface.Snapshot();
using var data = img.Encode(SKEncodedImageFormat.Png, 100);
data.SaveTo(File.OpenWrite("out.png"));

// Always dispose native objects (use 'using').
```

Happy (cross-platform) drawing! 🎨

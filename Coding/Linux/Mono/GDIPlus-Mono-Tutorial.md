---
id: 20260923181701
title: Graphics Programming with Mono
author: Karl Schmitt
date: 2026-09-23
keywords: [ Mono, GDI+ ]
---

# Graphics Programming with Mono

## GDI+ Graphics Programming with Mono — A Practical Tutorial

This tutorial walks you through drawing 2D graphics using **GDI+** (the `System.Drawing` namespace) on the **Mono** runtime. GDI+ is a mature 2D graphics API that lets you draw lines, shapes, text, and images onto surfaces such as bitmaps, windows, or off-screen buffers.

> **Note on the current state of `System.Drawing` in Mono / .NET**
> Historically, Mono shipped its own managed reimplementation of `System.Drawing` backed by the native **libgdiplus** library. On modern .NET (Core / 5+), `System.Drawing.Common` became a Windows-only supported package. For cross-platform work today the recommended paths are:
> - Use **Mono + libgdiplus** (this tutorial's focus, still valid for classic Mono/GTK# apps).
> - Or migrate to a cross-platform library such as **SkiaSharp** or **ImageSharp** for new projects.
>
> This tutorial targets the classic Mono `System.Drawing` stack so you can learn GDI+ fundamentals that transfer directly to Windows GDI+ as well.

---

## Table of Contents

1. [Prerequisites](#1-prerequisites)
2. [Installing Mono and libgdiplus](#2-installing-mono-and-libgdiplus)
3. [Your First GDI+ Program](#3-your-first-gdi-program)
4. [Core GDI+ Concepts](#4-core-gdi-concepts)
5. [Drawing Primitives](#5-drawing-primitives)
6. [Working with Pens and Brushes](#6-working-with-pens-and-brushes)
7. [Drawing Text](#7-drawing-text)
8. [Images and Bitmaps](#8-images-and-bitmaps)
9. [Transformations](#9-transformations)
10. [Anti-Aliasing and Quality](#10-anti-aliasing-and-quality)
11. [A Complete Example: Rendering a Chart](#11-a-complete-example-rendering-a-chart)
12. [Troubleshooting](#12-troubleshooting)
13. [Where to Go Next](#13-where-to-go-next)

---

## 1. Prerequisites

- Basic C# knowledge (classes, methods, `using` statements).
- A terminal / command line.
- A text editor or IDE (VS Code, Rider, or MonoDevelop).

---

## 2. Installing Mono and libgdiplus

GDI+ on Mono requires two things: the **Mono runtime** and the native **libgdiplus** library that implements the drawing primitives.

### Linux (Debian / Ubuntu)

```bash
# Add the Mono repository (see https://www.mono-project.com/download/stable/)
sudo apt update
sudo apt install mono-complete libgdiplus
```

### Linux (Fedora)

```bash
sudo dnf install mono-complete libgdiplus
```

### macOS (Homebrew)

```bash
brew install mono
brew install mono-libgdiplus
```

### Windows

On Windows, GDI+ is provided natively by the OS, so `libgdiplus` is not required. Install Mono from the [official installer](https://www.mono-project.com/download/stable/), or simply use .NET Framework / .NET on Windows.

### Verify the installation

```bash
mono --version
```

You should see output similar to:

```
Mono JIT compiler version 6.x.x
```

To confirm `libgdiplus` is discoverable (Linux/macOS):

```bash
# Debian/Ubuntu
dpkg -l | grep libgdiplus
# or locate the shared object
find / -name "libgdiplus*" 2>/dev/null
```

---

## 3. Your First GDI+ Program

Let's draw a red rectangle onto an in-memory bitmap and save it as a PNG file. This is the simplest way to test GDI+ without needing a GUI window.

Create a file named `hello_gdi.cs`:

```csharp
using System;
using System.Drawing;
using System.Drawing.Imaging;

class HelloGdi
{
    static void Main()
    {
        // Create a 400x300 pixel 32-bit ARGB bitmap.
        using (var bitmap = new Bitmap(400, 300))
        using (var g = Graphics.FromImage(bitmap))
        {
            // Fill the whole surface with white.
            g.Clear(Color.White);

            // Draw a filled red rectangle.
            using (var brush = new SolidBrush(Color.Red))
            {
                g.FillRectangle(brush, 50, 50, 300, 200);
            }

            // Draw a blue outline around it.
            using (var pen = new Pen(Color.Blue, 3))
            {
                g.DrawRectangle(pen, 50, 50, 300, 200);
            }

            // Save the result to disk.
            bitmap.Save("output.png", ImageFormat.Png);
        }

        Console.WriteLine("Saved output.png");
    }
}
```

### Compile and run

```bash
# Compile with the Mono C# compiler, referencing System.Drawing.
mcs hello_gdi.cs -r:System.Drawing.dll

# Run it.
mono hello_gdi.exe
```

Open `output.png` — you should see a red rectangle with a blue border on a white background.

> **Tip:** If you get a `TypeInitializationException` mentioning `gdiplus`, it means `libgdiplus` is not installed or not found. See [Troubleshooting](#12-troubleshooting).

---

## 4. Core GDI+ Concepts

GDI+ revolves around a handful of key types, all in `System.Drawing`:

| Type | Purpose |
|------|---------|
| `Graphics` | The drawing surface / "canvas." Every drawing call is a method on a `Graphics` object. |
| `Pen` | Defines how **outlines** (lines, curves, shape borders) are drawn: color, width, dash style. |
| `Brush` | Defines how **areas** are filled: solid color, gradient, texture, hatch. |
| `Bitmap` / `Image` | Raster image data you can draw onto or draw from. |
| `Font` | Typeface + size + style used when rendering text. |
| `Color` | An ARGB color value. |
| `Point` / `PointF` | A coordinate (integer / floating point). |
| `Rectangle` / `RectangleF` | A rectangular region. |

### The coordinate system

- The origin `(0, 0)` is at the **top-left** corner.
- **X** increases to the right, **Y** increases downward.
- Units default to **pixels**.

### The `IDisposable` rule

`Graphics`, `Pen`, `Brush`, `Bitmap`, and `Font` all wrap native resources. **Always** dispose them, ideally with a `using` block, to avoid leaking native memory in libgdiplus.

---

## 5. Drawing Primitives

All of the following assume you have a `Graphics g` instance.

### Lines

```csharp
using (var pen = new Pen(Color.Black, 2))
{
    g.DrawLine(pen, 10, 10, 200, 100);              // from (10,10) to (200,100)
    g.DrawLines(pen, new[] {                          // a connected polyline
        new Point(10, 150),
        new Point(60, 120),
        new Point(110, 170),
        new Point(160, 130)
    });
}
```

### Rectangles

```csharp
using (var pen = new Pen(Color.DarkGreen, 2))
using (var brush = new SolidBrush(Color.LightGreen))
{
    g.FillRectangle(brush, 20, 20, 120, 80);   // filled
    g.DrawRectangle(pen, 20, 20, 120, 80);     // outline
}
```

### Ellipses and Circles

```csharp
using (var pen = new Pen(Color.Purple, 2))
{
    // An ellipse fits inside the bounding rectangle (x, y, width, height).
    g.DrawEllipse(pen, 50, 50, 200, 100);

    // A circle is just an ellipse with equal width and height.
    g.DrawEllipse(pen, 50, 50, 100, 100);
}
```

### Arcs and Pie slices

```csharp
using (var pen = new Pen(Color.Orange, 2))
using (var brush = new SolidBrush(Color.Gold))
{
    // Arc: bounding box + start angle + sweep angle (degrees, clockwise).
    g.DrawArc(pen, 20, 20, 150, 150, startAngle: 0, sweepAngle: 90);

    // Pie: like a slice of a pie chart.
    g.FillPie(brush, 200, 20, 150, 150, startAngle: 45, sweepAngle: 120);
}
```

### Polygons

```csharp
Point[] triangle = {
    new Point(100, 20),
    new Point(180, 160),
    new Point(20, 160)
};

using (var brush = new SolidBrush(Color.SkyBlue))
using (var pen = new Pen(Color.Navy, 2))
{
    g.FillPolygon(brush, triangle);
    g.DrawPolygon(pen, triangle);
}
```

### Curves (Bézier)

```csharp
using (var pen = new Pen(Color.Crimson, 2))
{
    g.DrawBezier(pen,
        new Point(20, 200),   // start
        new Point(80, 20),    // control point 1
        new Point(160, 380),  // control point 2
        new Point(220, 200)); // end
}
```

---

## 6. Working with Pens and Brushes

### Pens

```csharp
using System.Drawing.Drawing2D;

var pen = new Pen(Color.Black, 4)
{
    DashStyle = DashStyle.Dash,          // Solid, Dash, Dot, DashDot, DashDotDot
    StartCap  = LineCap.Round,
    EndCap    = LineCap.ArrowAnchor,
    LineJoin  = LineJoin.Round
};
```

### Solid Brush

```csharp
var solid = new SolidBrush(Color.FromArgb(alpha: 180, red: 255, green: 0, blue: 0));
```

The `alpha` component (0–255) controls transparency — great for overlays.

### Linear Gradient Brush

```csharp
using System.Drawing.Drawing2D;

var rect = new Rectangle(0, 0, 300, 200);
using (var gradient = new LinearGradientBrush(
    rect, Color.Blue, Color.Cyan, LinearGradientMode.Horizontal))
{
    g.FillRectangle(gradient, rect);
}
```

### Hatch Brush

```csharp
using System.Drawing.Drawing2D;

using (var hatch = new HatchBrush(
    HatchStyle.DiagonalCross, Color.DarkGray, Color.White))
{
    g.FillRectangle(hatch, 0, 0, 200, 200);
}
```

### Texture Brush

```csharp
using (var texture = new Bitmap("pattern.png"))
using (var brush = new TextureBrush(texture))
{
    g.FillEllipse(brush, 0, 0, 300, 300);
}
```

---

## 7. Drawing Text

```csharp
using (var font = new Font("DejaVu Sans", 24, FontStyle.Bold))
using (var brush = new SolidBrush(Color.Black))
{
    g.DrawString("Hello, GDI+ on Mono!", font, brush, new PointF(20, 20));
}
```

> **Font availability on Linux:** Windows fonts like *Arial* may not be installed. Use fonts you know exist (e.g. `DejaVu Sans`, `Liberation Sans`) or install the Microsoft core fonts package (`ttf-mscorefonts-installer` on Debian/Ubuntu). List available fonts with `fc-list`.

### Measuring text

```csharp
SizeF size = g.MeasureString("Some text", font);
Console.WriteLine($"Text is {size.Width} x {size.Height} pixels");
```

### Aligning text within a rectangle

```csharp
var layout = new RectangleF(0, 0, 400, 300);
var format = new StringFormat
{
    Alignment     = StringAlignment.Center,  // horizontal
    LineAlignment = StringAlignment.Center   // vertical
};
g.DrawString("Centered", font, brush, layout, format);
```

---

## 8. Images and Bitmaps

### Loading and drawing an existing image

```csharp
using (var source = new Bitmap("photo.jpg"))
{
    // Draw at full size at position (10, 10).
    g.DrawImage(source, 10, 10);

    // Draw scaled into a target rectangle.
    g.DrawImage(source, new Rectangle(0, 0, 100, 100));
}
```

### Manipulating pixels directly

```csharp
using (var bmp = new Bitmap(256, 256))
{
    for (int y = 0; y < bmp.Height; y++)
        for (int x = 0; x < bmp.Width; x++)
            bmp.SetPixel(x, y, Color.FromArgb(x, y, 128));

    bmp.Save("gradient.png", ImageFormat.Png);
}
```

> `SetPixel` / `GetPixel` are simple but slow. For performance-critical pixel work, use `Bitmap.LockBits` to access the raw buffer.

### Saving in different formats

```csharp
bitmap.Save("out.png",  ImageFormat.Png);
bitmap.Save("out.jpg",  ImageFormat.Jpeg);
bitmap.Save("out.bmp",  ImageFormat.Bmp);
bitmap.Save("out.gif",  ImageFormat.Gif);
```

---

## 9. Transformations

GDI+ lets you translate, rotate, and scale the coordinate system before drawing.

```csharp
// Save the current state so we can restore it later.
var state = g.Save();

g.TranslateTransform(200, 150);  // move origin to center
g.RotateTransform(45);           // rotate 45 degrees
g.ScaleTransform(1.5f, 1.5f);    // scale up 50%

using (var brush = new SolidBrush(Color.Tomato))
{
    // Drawn relative to the transformed coordinate system.
    g.FillRectangle(brush, -50, -25, 100, 50);
}

// Undo the transforms.
g.Restore(state);
```

Transforms combine in the order you apply them, which is a common source of confusion — apply translate first, then rotate, then scale for the most intuitive results.

---

## 10. Anti-Aliasing and Quality

By default, edges can look jagged. Adjust the `Graphics` quality properties:

```csharp
using System.Drawing.Drawing2D;
using System.Drawing.Text;

g.SmoothingMode      = SmoothingMode.AntiAlias;          // smooth shape edges
g.TextRenderingHint  = TextRenderingHint.AntiAliasGridFit; // smooth text
g.InterpolationMode  = InterpolationMode.HighQualityBicubic; // smooth image scaling
g.PixelOffsetMode    = PixelOffsetMode.HighQuality;
```

Set these **before** your drawing calls. Anti-aliasing costs some performance but dramatically improves visual quality.

---

## 11. A Complete Example: Rendering a Chart

This program renders a simple bar chart to a PNG. It ties together brushes, pens, text, transforms, and quality settings.

Save as `barchart.cs`:

```csharp
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Drawing.Text;

class BarChart
{
    static void Main()
    {
        int width = 600, height = 400;
        string[] labels = { "Jan", "Feb", "Mar", "Apr", "May" };
        int[] values     = { 120, 200, 150, 80, 220 };

        using (var bmp = new Bitmap(width, height))
        using (var g = Graphics.FromImage(bmp))
        {
            g.SmoothingMode     = SmoothingMode.AntiAlias;
            g.TextRenderingHint = TextRenderingHint.AntiAliasGridFit;
            g.Clear(Color.White);

            // Chart area margins.
            int marginLeft = 50, marginBottom = 50, marginTop = 30;
            int chartWidth  = width  - marginLeft - 20;
            int chartHeight = height - marginBottom - marginTop;

            int maxValue = 0;
            foreach (var v in values) if (v > maxValue) maxValue = v;

            // Draw axes.
            using (var axisPen = new Pen(Color.Black, 2))
            {
                g.DrawLine(axisPen, marginLeft, marginTop,
                                    marginLeft, marginTop + chartHeight);            // Y axis
                g.DrawLine(axisPen, marginLeft, marginTop + chartHeight,
                                    marginLeft + chartWidth, marginTop + chartHeight); // X axis
            }

            // Draw bars.
            int barCount   = values.Length;
            int slotWidth  = chartWidth / barCount;
            int barWidth   = (int)(slotWidth * 0.6);

            using (var labelFont = new Font("DejaVu Sans", 10))
            using (var textBrush = new SolidBrush(Color.Black))
            {
                for (int i = 0; i < barCount; i++)
                {
                    int barHeight = (int)((double)values[i] / maxValue * chartHeight);
                    int x = marginLeft + i * slotWidth + (slotWidth - barWidth) / 2;
                    int y = marginTop + chartHeight - barHeight;

                    var barRect = new Rectangle(x, y, barWidth, barHeight);
                    using (var barBrush = new LinearGradientBrush(
                        barRect, Color.SteelBlue, Color.LightSkyBlue,
                        LinearGradientMode.Vertical))
                    {
                        g.FillRectangle(barBrush, barRect);
                    }

                    // Value label above the bar.
                    string valText = values[i].ToString();
                    var valSize = g.MeasureString(valText, labelFont);
                    g.DrawString(valText, labelFont, textBrush,
                        x + (barWidth - valSize.Width) / 2, y - valSize.Height);

                    // Category label below the axis.
                    var labSize = g.MeasureString(labels[i], labelFont);
                    g.DrawString(labels[i], labelFont, textBrush,
                        x + (barWidth - labSize.Width) / 2,
                        marginTop + chartHeight + 5);
                }
            }

            // Title.
            using (var titleFont = new Font("DejaVu Sans", 16, FontStyle.Bold))
            using (var titleBrush = new SolidBrush(Color.DarkSlateGray))
            {
                g.DrawString("Monthly Sales", titleFont, titleBrush, marginLeft, 5);
            }

            bmp.Save("barchart.png", ImageFormat.Png);
        }

        Console.WriteLine("Saved barchart.png");
    }
}
```

Compile and run:

```bash
mcs barchart.cs -r:System.Drawing.dll
mono barchart.exe
```

Open `barchart.png` to see the finished chart.

---

## 12. Troubleshooting

### `TypeInitializationException` for `System.Drawing.GDIPlus`

libgdiplus is missing or not on the library path.

```bash
# Debian/Ubuntu
sudo apt install libgdiplus

# macOS
brew install mono-libgdiplus
```

If it is installed but still not found, help the loader locate it:

```bash
export LD_LIBRARY_PATH=/usr/lib:/usr/local/lib:$LD_LIBRARY_PATH   # Linux
export DYLD_LIBRARY_PATH=/usr/local/lib:$DYLD_LIBRARY_PATH        # macOS
```

### `DllNotFoundException: gdiplus.dll`

Same root cause — the native library was not found. On non-Windows systems Mono maps `gdiplus.dll` to `libgdiplus`. Confirm the package is installed and reachable.

### Fonts render as blank boxes or throw

The requested font family is not installed. List available fonts:

```bash
fc-list
```

Use a font that appears in the list, or install additional font packages.

### Blurry or jagged output

Set the quality modes described in [Section 10](#10-anti-aliasing-and-quality) before drawing.

### Slow pixel operations

Avoid `GetPixel`/`SetPixel` in tight loops. Use `Bitmap.LockBits` for direct buffer access.

---

## 13. Where to Go Next

- **GTK# + GDI+:** Combine `System.Drawing` with GTK# to build cross-platform desktop UIs, drawing inside a `DrawingArea`'s expose/draw event.
- **Windows Forms on Mono:** Mono's `System.Windows.Forms` uses GDI+ under the hood; override `OnPaint` and use the supplied `Graphics`.
- **SkiaSharp:** For new cross-platform projects, consider [SkiaSharp](https://github.com/mono/SkiaSharp), a modern, hardware-accelerated 2D API that is actively supported.
- **ImageSharp:** A fully managed, cross-platform imaging library with no native dependencies.
- **Official GDI+ docs:** The [`System.Drawing` API reference](https://learn.microsoft.com/dotnet/api/system.drawing) applies almost identically to Mono.

---

### Quick Reference Cheat Sheet

```csharp
// Create a surface
var bmp = new Bitmap(w, h);
var g   = Graphics.FromImage(bmp);

// Outlines use a Pen
g.DrawLine / DrawRectangle / DrawEllipse / DrawArc / DrawPolygon(pen, ...);

// Fills use a Brush
g.FillRectangle / FillEllipse / FillPie / FillPolygon(brush, ...);

// Text
g.DrawString(text, font, brush, point);

// Images
g.DrawImage(image, rect);

// Quality
g.SmoothingMode = SmoothingMode.AntiAlias;

// Always dispose! (use 'using' blocks)
```

Happy drawing! 🎨

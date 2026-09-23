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

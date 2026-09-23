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

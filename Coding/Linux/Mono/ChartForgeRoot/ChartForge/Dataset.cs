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

namespace ChartForge;

// Contract: turn a Dataset into PNG image bytes.
public interface IChartRenderer
{
    ChartType Type { get; }
    byte[] Render(Dataset data, int width, int height);
}

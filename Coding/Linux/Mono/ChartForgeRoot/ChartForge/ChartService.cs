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

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

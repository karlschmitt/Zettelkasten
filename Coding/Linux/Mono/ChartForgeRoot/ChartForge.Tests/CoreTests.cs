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

namespace ChartForge;

// Contract: turn some source into a validated Dataset.
public interface IDataSource
{
    Task<Dataset> LoadAsync(string path, string title, CancellationToken token = default);
}

// A clear, custom exception for bad data.
public class DataFormatException : Exception
{
    public DataFormatException(string message) : base(message) { }
}

// Reads CSV of the form:  label,value  (one pair per line)
public class CsvDataSource : IDataSource
{
    public async Task<Dataset> LoadAsync(
        string path, string title, CancellationToken token = default)
    {
        if (!File.Exists(path))
            throw new FileNotFoundException($"Input file not found: {path}");

        string[] lines = await File.ReadAllLinesAsync(path, token);
        var points = new List<DataPoint>();

        for (int i = 0; i < lines.Length; i++)
        {
            string line = lines[i].Trim();

            // Skip blank lines and an optional header row.
            if (line.Length == 0) continue;
            if (i == 0 && !LooksLikeData(line)) continue;

            string[] parts = line.Split(',');
            if (parts.Length != 2)
                throw new DataFormatException(
                    $"Line {i + 1}: expected 'label,value' but got '{line}'.");

            string label = parts[0].Trim();
            if (!double.TryParse(parts[1].Trim(),
                    System.Globalization.NumberStyles.Any,
                    System.Globalization.CultureInfo.InvariantCulture,
                    out double value))
            {
                throw new DataFormatException(
                    $"Line {i + 1}: '{parts[1].Trim()}' is not a number.");
            }

            points.Add(new DataPoint(label, value));
        }

        if (points.Count == 0)
            throw new DataFormatException("No data rows found in the file.");

        return new Dataset(title, points);
    }

    // A row is data if its second field parses as a number.
    private static bool LooksLikeData(string line)
    {
        string[] parts = line.Split(',');
        return parts.Length == 2 &&
               double.TryParse(parts[1].Trim(),
                   System.Globalization.NumberStyles.Any,
                   System.Globalization.CultureInfo.InvariantCulture, out _);
    }
}

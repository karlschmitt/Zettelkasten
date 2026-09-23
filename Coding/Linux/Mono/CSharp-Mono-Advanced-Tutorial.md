# C# with Mono — Advanced Topics

This is the final tutorial in the series, following the [Beginner](./CSharp-Mono-Beginner-Tutorial.md) and [Intermediate/OOP](./CSharp-Mono-Intermediate-OOP-Tutorial.md) tutorials. It assumes you're comfortable with classes, inheritance, interfaces, generics, and LINQ, and takes you into the topics that separate hobby code from production-quality software: **asynchronous programming, concurrency, modern language features, design patterns, unit testing, reflection, and performance**.

We continue with the Mono workflow. A note upfront: some advanced features (records, pattern matching, nullable reference types, top-level statements) are newer C# language features. Recent Mono versions support many of them; where a modern .NET SDK is required or preferable, it's flagged. If a feature won't compile under your Mono version, use the `dotnet` SDK — the language concepts are identical.

```bash
mcs Program.cs && mono Program.exe
```

---

## Table of Contents

1. [Asynchronous Programming with async/await](#1-asynchronous-programming-with-asyncawait)
2. [Tasks, Parallelism & the Thread Pool](#2-tasks-parallelism--the-thread-pool)
3. [Thread Safety & Synchronization](#3-thread-safety--synchronization)
4. [Cancellation](#4-cancellation)
5. [Modern Language Features](#5-modern-language-features)
6. [Pattern Matching](#6-pattern-matching)
7. [Records & Immutability](#7-records--immutability)
8. [Nullable Reference Types](#8-nullable-reference-types)
9. [Extension Methods & Iterators](#9-extension-methods--iterators)
10. [Design Patterns in C#](#10-design-patterns-in-c)
11. [Dependency Injection](#11-dependency-injection)
12. [Unit Testing](#12-unit-testing)
13. [Reflection & Attributes](#13-reflection--attributes)
14. [Performance & Memory](#14-performance--memory)
15. [Putting It All Together: An Async Web Fetcher with DI & Tests](#15-putting-it-all-together-an-async-web-fetcher-with-di--tests)
16. [Where to Go Next](#16-where-to-go-next)

---

## 1. Asynchronous Programming with async/await

Synchronous code blocks the thread while waiting for slow operations (network, disk, timers). **Asynchronous** code frees the thread to do other work while waiting. C# makes this readable with `async`/`await`.

```csharp
using System;
using System.Threading.Tasks;

class Program
{
    // "async" marks a method that can use "await".
    // "Task" is a promise of a future result (Task<T> for a value).
    static async Task<int> ComputeSlowlyAsync(int input)
    {
        await Task.Delay(1000);      // simulate slow work WITHOUT blocking
        return input * 2;
    }

    static async Task Main()
    {
        Console.WriteLine("Starting...");
        int result = await ComputeSlowlyAsync(21);   // await = "wait without blocking"
        Console.WriteLine($"Result: {result}");      // Result: 42
    }
}
```

### Key rules

- An `async` method returns `Task` (no value), `Task<T>` (a value), or `ValueTask<T>`.
- `await` unwraps a `Task<T>` into its `T`, resuming when the work completes.
- **Never** use `async void` except for event handlers — it can't be awaited and swallows exceptions.
- Async doesn't mean "parallel." It means "doesn't block while waiting."

### Awaiting multiple operations

```csharp
Task<int> a = ComputeSlowlyAsync(10);
Task<int> b = ComputeSlowlyAsync(20);

// Both run concurrently; wait for both to finish.
int[] results = await Task.WhenAll(a, b);
Console.WriteLine(results[0] + results[1]);   // 60, after ~1s (not 2s)
```

---

## 2. Tasks, Parallelism & the Thread Pool

For **CPU-bound** work you can offload to background threads with `Task.Run`, and process collections in parallel.

```csharp
using System;
using System.Threading.Tasks;
using System.Linq;

class Program
{
    static long HeavyCompute(int seed)
    {
        long sum = 0;
        for (int i = 0; i < 10_000_000; i++) sum += (seed + i) % 7;
        return sum;
    }

    static async Task Main()
    {
        // Offload CPU work to a background thread.
        long result = await Task.Run(() => HeavyCompute(3));
        Console.WriteLine(result);

        // Parallel.For runs iterations across multiple cores.
        Parallel.For(0, 4, i =>
        {
            Console.WriteLine($"Iteration {i} on thread {Environment.CurrentManagedThreadId}");
        });

        // PLINQ: parallel LINQ.
        var numbers = Enumerable.Range(1, 1000);
        var sumOfSquares = numbers.AsParallel().Select(n => (long)n * n).Sum();
        Console.WriteLine(sumOfSquares);
    }
}
```

> **Rule of thumb:** use `async`/`await` with `Task.Delay`, I/O, and network calls (I/O-bound); use `Task.Run` / `Parallel` / PLINQ for heavy computation (CPU-bound). Don't wrap I/O in `Task.Run`.

---

## 3. Thread Safety & Synchronization

When multiple threads touch the same data, you get **race conditions**. Protect shared state.

```csharp
using System;
using System.Threading;
using System.Threading.Tasks;

class Program
{
    static int _counter = 0;
    static readonly object _lock = new object();

    static async Task Main()
    {
        var tasks = new Task[10];
        for (int i = 0; i < tasks.Length; i++)
        {
            tasks[i] = Task.Run(() =>
            {
                for (int j = 0; j < 100_000; j++)
                {
                    // Only one thread at a time enters this block.
                    lock (_lock)
                    {
                        _counter++;
                    }
                }
            });
        }

        await Task.WhenAll(tasks);
        Console.WriteLine(_counter);   // reliably 1,000,000
    }
}
```

### Lighter-weight alternatives

```csharp
// Atomic operations for simple counters — no lock needed.
Interlocked.Increment(ref _counter);

// Thread-safe collections (System.Collections.Concurrent):
var bag = new System.Collections.Concurrent.ConcurrentDictionary<string, int>();
bag.AddOrUpdate("key", 1, (k, old) => old + 1);
```

> Without the `lock`/`Interlocked`, `_counter++` is not atomic (read, increment, write), so concurrent threads lose updates and the total comes out wrong.

---

## 4. Cancellation

Long-running async work should be **cancellable** via `CancellationToken`.

```csharp
using System;
using System.Threading;
using System.Threading.Tasks;

class Program
{
    static async Task DoWorkAsync(CancellationToken token)
    {
        for (int i = 0; i < 10; i++)
        {
            token.ThrowIfCancellationRequested();   // bail out if cancelled
            Console.WriteLine($"Working... {i}");
            await Task.Delay(500, token);
        }
    }

    static async Task Main()
    {
        using var cts = new CancellationTokenSource();
        cts.CancelAfter(2000);   // auto-cancel after 2 seconds

        try
        {
            await DoWorkAsync(cts.Token);
        }
        catch (OperationCanceledException)
        {
            Console.WriteLine("Work was cancelled.");
        }
    }
}
```

---

## 5. Modern Language Features

A tour of syntax that makes C# concise. (Most require a recent C#/.NET; use the `dotnet` SDK if Mono rejects any.)

```csharp
// Target-typed new
List<int> numbers = new();

// Object & collection initializers
var person = new Person { Name = "Alice", Age = 30 };
var list = new List<int> { 1, 2, 3 };

// Tuples — group values without a class
(string name, int age) GetPerson() => ("Bob", 25);
var (n, a) = GetPerson();

// Local functions
int Factorial(int x)
{
    int Helper(int k) => k <= 1 ? 1 : k * Helper(k - 1);
    return Helper(x);
}

// Expression-bodied members
int Square(int x) => x * x;

// String interpolation with formatting
double price = 1234.5;
Console.WriteLine($"{price:C}");     // currency
Console.WriteLine($"{price:F2}");    // 1234.50

// Null-coalescing and null-conditional
string name = maybeNull ?? "default";
int? length = text?.Length;          // null if text is null
```

---

## 6. Pattern Matching

Pattern matching makes conditional logic based on type and shape expressive and safe.

```csharp
using System;

abstract record Shape;
record Circle(double Radius) : Shape;
record Rectangle(double Width, double Height) : Shape;
record Triangle(double Base, double Height) : Shape;

class Program
{
    static double Area(Shape shape) => shape switch
    {
        Circle c              => Math.PI * c.Radius * c.Radius,
        Rectangle r           => r.Width * r.Height,
        Triangle t            => 0.5 * t.Base * t.Height,
        _                     => throw new ArgumentException("Unknown shape")
    };

    static string Classify(int n) => n switch
    {
        < 0            => "negative",
        0              => "zero",
        > 0 and < 100  => "small positive",
        _              => "large positive"
    };

    static void Main()
    {
        Console.WriteLine(Area(new Circle(2)));         // ~12.57
        Console.WriteLine(Area(new Rectangle(3, 4)));   // 12
        Console.WriteLine(Classify(42));                 // small positive

        // Type patterns with "is"
        object obj = "hello";
        if (obj is string s && s.Length > 3)
            Console.WriteLine($"Long string: {s}");
    }
}
```

---

## 7. Records & Immutability

**Records** are reference types built for immutable data. They give you value-based equality, concise syntax, and non-destructive copying — for free.

```csharp
using System;

// A positional record: one line defines properties, constructor, equality, ToString.
record Person(string Name, int Age);

class Program
{
    static void Main()
    {
        var alice = new Person("Alice", 30);
        Console.WriteLine(alice);                   // Person { Name = Alice, Age = 30 }

        // Value equality: two records with the same data are equal.
        var alice2 = new Person("Alice", 30);
        Console.WriteLine(alice == alice2);         // True

        // Non-destructive mutation with "with": creates a modified COPY.
        var olderAlice = alice with { Age = 31 };
        Console.WriteLine(olderAlice);              // Person { Name = Alice, Age = 31 }
        Console.WriteLine(alice);                   // unchanged: Age = 30
    }
}
```

Compare to a class, where equality is by reference and you'd write dozens of lines for the same behavior. Prefer records for DTOs, messages, and any value-like data.

---

## 8. Nullable Reference Types

Historically, any reference could be `null`, causing the infamous `NullReferenceException`. **Nullable reference types** (C# 8+) let the compiler track nullability and warn you before you ship a bug.

Enable them per file or project:

```csharp
#nullable enable

class Program
{
    // "string" = never null;  "string?" = may be null.
    static int SafeLength(string? text)
    {
        // The compiler forces you to handle the null case.
        if (text is null) return 0;
        return text.Length;      // safe: null was ruled out above
    }

    static void Main()
    {
        string name = "Alice";     // OK
        // string bad = null;      // Warning: assigning null to non-nullable
        string? maybe = null;      // OK, explicitly nullable

        System.Console.WriteLine(SafeLength(maybe));   // 0
    }
}
```

In a project file you'd set `<Nullable>enable</Nullable>`. This is one of the highest-value features for catching bugs at compile time.

---

## 9. Extension Methods & Iterators

### Extension methods — add methods to existing types

```csharp
using System;

static class StringExtensions
{
    // The "this" on the first parameter makes it an extension method.
    public static bool IsPalindrome(this string s)
    {
        var reversed = new string(s.Reverse().ToArray());
        return string.Equals(s, reversed, StringComparison.OrdinalIgnoreCase);
    }
}

class Program
{
    static void Main()
    {
        // Called as if it were a built-in method on string.
        Console.WriteLine("Racecar".IsPalindrome());   // True
        Console.WriteLine("Hello".IsPalindrome());     // False
    }
}
```

(LINQ is just a big set of extension methods on `IEnumerable<T>`.)

### Iterators with `yield` — lazy sequences

```csharp
using System;
using System.Collections.Generic;

class Program
{
    // Produces values one at a time, on demand — no full list in memory.
    static IEnumerable<long> Fibonacci()
    {
        long a = 0, b = 1;
        while (true)
        {
            yield return a;
            (a, b) = (b, a + b);
        }
    }

    static void Main()
    {
        foreach (long n in Fibonacci().Take(10))
            Console.Write($"{n} ");    // 0 1 1 2 3 5 8 13 21 34
    }
}
```

---

## 10. Design Patterns in C#

Reusable solutions to common design problems. Three of the most useful:

### Strategy — swap algorithms at runtime

```csharp
using System;

interface IShippingStrategy { decimal Cost(decimal weight); }

class StandardShipping : IShippingStrategy { public decimal Cost(decimal w) => w * 1.0m; }
class ExpressShipping : IShippingStrategy { public decimal Cost(decimal w) => w * 2.5m; }

class Order
{
    private readonly IShippingStrategy _strategy;
    public Order(IShippingStrategy strategy) => _strategy = strategy;
    public decimal Ship(decimal weight) => _strategy.Cost(weight);
}

// Usage: choose behavior by injecting a strategy.
var order = new Order(new ExpressShipping());
Console.WriteLine(order.Ship(10));   // 25.0
```

### Factory — centralize object creation

```csharp
interface IAnimal { string Speak(); }
class Dog : IAnimal { public string Speak() => "Woof"; }
class Cat : IAnimal { public string Speak() => "Meow"; }

static class AnimalFactory
{
    public static IAnimal Create(string kind) => kind switch
    {
        "dog" => new Dog(),
        "cat" => new Cat(),
        _     => throw new ArgumentException($"Unknown: {kind}")
    };
}
```

### Observer — publish/subscribe (built into C# via events)

```csharp
class Stock
{
    public event Action<decimal> PriceChanged;
    private decimal _price;
    public decimal Price
    {
        get => _price;
        set { _price = value; PriceChanged?.Invoke(value); }
    }
}

// Subscribers react to changes.
var stock = new Stock();
stock.PriceChanged += p => Console.WriteLine($"Alert: price is {p}");
stock.Price = 99.5m;
```

---

## 11. Dependency Injection

**Dependency Injection (DI)** means giving a class its dependencies from outside rather than creating them internally. This decouples code and makes it testable.

```csharp
using System;

// Depend on an abstraction, not a concrete class.
interface IMessageService { void Send(string message); }

class EmailService : IMessageService
{
    public void Send(string message) => Console.WriteLine($"Email: {message}");
}

class SmsService : IMessageService
{
    public void Send(string message) => Console.WriteLine($"SMS: {message}");
}

// Notifier doesn't know or care WHICH service it gets.
class Notifier
{
    private readonly IMessageService _service;
    public Notifier(IMessageService service) => _service = service;   // injected
    public void Notify(string msg) => _service.Send(msg);
}

class Program
{
    static void Main()
    {
        // Compose the object graph at startup.
        var notifier = new Notifier(new EmailService());
        notifier.Notify("Hello!");        // Email: Hello!

        // Swap the implementation with zero changes to Notifier.
        var smsNotifier = new Notifier(new SmsService());
        smsNotifier.Notify("Hi!");        // SMS: Hi!
    }
}
```

Larger apps use a **DI container** (e.g. `Microsoft.Extensions.DependencyInjection`) to wire these graphs automatically, but the principle is exactly this manual "constructor injection."

---

## 12. Unit Testing

Automated tests verify your code and protect against regressions. The most popular frameworks are **xUnit** and **NUnit**. With the `dotnet` SDK:

```bash
dotnet new xunit -n MyApp.Tests
cd MyApp.Tests
dotnet add reference ../MyApp/MyApp.csproj
dotnet test
```

A test class for a `Calculator`:

```csharp
using Xunit;

public class Calculator
{
    public int Add(int a, int b) => a + b;
    public int Divide(int a, int b) =>
        b == 0 ? throw new DivideByZeroException() : a / b;
}

public class CalculatorTests
{
    [Fact]                              // a single test case
    public void Add_ReturnsSum()
    {
        var calc = new Calculator();
        int result = calc.Add(2, 3);
        Assert.Equal(5, result);
    }

    [Theory]                            // a data-driven test
    [InlineData(2, 3, 5)]
    [InlineData(-1, 1, 0)]
    [InlineData(0, 0, 0)]
    public void Add_WorksForManyInputs(int a, int b, int expected)
    {
        Assert.Equal(expected, new Calculator().Add(a, b));
    }

    [Fact]
    public void Divide_ByZero_Throws()
    {
        var calc = new Calculator();
        Assert.Throws<DivideByZeroException>(() => calc.Divide(1, 0));
    }
}
```

Follow the **Arrange–Act–Assert** pattern: set up inputs, run the code, check the result. Aim to test behavior (public API), not implementation details.

---

## 13. Reflection & Attributes

**Reflection** inspects types at runtime. **Attributes** attach metadata to code that reflection (or frameworks) can read.

```csharp
using System;
using System.Reflection;

// A custom attribute.
[AttributeUsage(AttributeTargets.Method)]
class DescriptionAttribute : Attribute
{
    public string Text { get; }
    public DescriptionAttribute(string text) => Text = text;
}

class Service
{
    [Description("Adds two numbers")]
    public int Add(int a, int b) => a + b;

    public int Secret => 42;
}

class Program
{
    static void Main()
    {
        Type type = typeof(Service);

        // Inspect members.
        Console.WriteLine($"Type: {type.Name}");
        foreach (MethodInfo m in type.GetMethods(BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly))
        {
            var desc = m.GetCustomAttribute<DescriptionAttribute>();
            string note = desc != null ? $" — {desc.Text}" : "";
            Console.WriteLine($"Method: {m.Name}{note}");
        }

        // Create an instance and invoke a method dynamically.
        object instance = Activator.CreateInstance(type);
        object result = type.GetMethod("Add").Invoke(instance, new object[] { 4, 5 });
        Console.WriteLine($"Invoked Add(4,5) = {result}");   // 9
    }
}
```

Reflection powers serializers, DI containers, test runners, and ORMs — but it's slower than direct calls, so use it for framework-level code, not hot paths.

---

## 14. Performance & Memory

### Value vs. reference types and the heap

- **Value types** (`int`, `struct`) live on the stack or inline; copied by value.
- **Reference types** (`class`, arrays, strings) live on the **heap**; the garbage collector (GC) reclaims them.

### Reduce allocations

```csharp
// BAD: string concatenation in a loop creates many temporary strings.
string s = "";
for (int i = 0; i < 10000; i++) s += i;

// GOOD: StringBuilder mutates one buffer.
var sb = new System.Text.StringBuilder();
for (int i = 0; i < 10000; i++) sb.Append(i);
string result = sb.ToString();
```

### Span<T> — slicing without allocating (modern .NET)

```csharp
// Span lets you work with a slice of an array/string without copying.
ReadOnlySpan<char> text = "Hello, World".AsSpan();
ReadOnlySpan<char> hello = text.Slice(0, 5);   // no new string allocated
Console.WriteLine(hello.ToString());           // Hello
```

### Measuring, not guessing

Don't optimize by intuition. Measure with a stopwatch for quick checks, or **BenchmarkDotNet** for rigorous benchmarks:

```csharp
var sw = System.Diagnostics.Stopwatch.StartNew();
// ... code under test ...
sw.Stop();
Console.WriteLine($"Elapsed: {sw.ElapsedMilliseconds} ms");
```

> **Golden rule:** make it correct first, measure to find the real bottleneck, then optimize only that. Premature optimization wastes effort and complicates code.

---

## 15. Putting It All Together: An Async Web Fetcher with DI & Tests

This example combines async/await, interfaces, dependency injection, cancellation, exception handling, and a testable design.

```csharp
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;

// Abstraction so we can swap the real fetcher for a fake one in tests.
interface IPageFetcher
{
    Task<int> GetLengthAsync(string url, CancellationToken token);
}

// Real implementation using HttpClient.
class HttpPageFetcher : IPageFetcher
{
    private readonly HttpClient _client;
    public HttpPageFetcher(HttpClient client) => _client = client;

    public async Task<int> GetLengthAsync(string url, CancellationToken token)
    {
        string content = await _client.GetStringAsync(url, token);
        return content.Length;
    }
}

// Service that depends on the abstraction (DI).
class SiteAnalyzer
{
    private readonly IPageFetcher _fetcher;
    public SiteAnalyzer(IPageFetcher fetcher) => _fetcher = fetcher;

    // Fetch many URLs concurrently and report their sizes.
    public async Task<Dictionary<string, int>> AnalyzeAsync(
        IEnumerable<string> urls, CancellationToken token = default)
    {
        var tasks = urls.Select(async url =>
        {
            try
            {
                int length = await _fetcher.GetLengthAsync(url, token);
                return (url, length);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed {url}: {ex.Message}");
                return (url, -1);
            }
        });

        var results = await Task.WhenAll(tasks);
        return results.ToDictionary(r => r.url, r => r.length);
    }
}

class Program
{
    static async Task Main()
    {
        using var http = new HttpClient();
        var analyzer = new SiteAnalyzer(new HttpPageFetcher(http));

        using var cts = new CancellationTokenSource(TimeSpan.FromSeconds(10));

        var urls = new[]
        {
            "https://example.com",
            "https://www.mono-project.com"
        };

        Dictionary<string, int> sizes = await analyzer.AnalyzeAsync(urls, cts.Token);

        foreach (var kvp in sizes.OrderByDescending(k => k.Value))
            Console.WriteLine($"{kvp.Key} -> {kvp.Value} chars");
    }
}
```

### The corresponding unit test (xUnit)

Because `SiteAnalyzer` depends on the `IPageFetcher` *interface*, we can inject a **fake** and test without any network:

```csharp
using System.Threading;
using System.Threading.Tasks;
using Xunit;

// A hand-written fake — no network involved.
class FakeFetcher : IPageFetcher
{
    public Task<int> GetLengthAsync(string url, CancellationToken token)
        => Task.FromResult(url.Length * 10);   // deterministic, fast
}

public class SiteAnalyzerTests
{
    [Fact]
    public async Task AnalyzeAsync_ReturnsLengthForEachUrl()
    {
        var analyzer = new SiteAnalyzer(new FakeFetcher());
        var result = await analyzer.AnalyzeAsync(new[] { "abc", "abcd" });

        Assert.Equal(30, result["abc"]);   // 3 * 10
        Assert.Equal(40, result["abcd"]);  // 4 * 10
    }
}
```

This is the payoff of everything in the series: an **interface** enables **dependency injection**, which enables **fast, deterministic unit tests**, all wrapped in **concurrent async** code with **cancellation** and **error handling**.

---

## 16. Where to Go Next

You've now covered the C# language end to end. To keep growing:

- **ASP.NET Core:** build web APIs and web apps.
- **Entity Framework Core:** database access with an ORM.
- **BenchmarkDotNet:** rigorous performance measurement.
- **Source generators & Roslyn analyzers:** compile-time code generation and custom rules.
- **Architecture:** clean/hexagonal architecture, CQRS, domain-driven design.
- **CI/CD:** automate builds and tests with GitHub Actions, Azure DevOps, or similar.
- **Modern .NET:** if you've been on Mono, adopt the `dotnet` SDK for the latest runtime performance and language features.
- **Revisit the graphics tutorials** in this folder — [GDI+ on Mono](./GDIPlus-Mono-Tutorial.md) and [SkiaSharp](./SkiaSharp-Tutorial.md) — now that you can architect them with DI, async, and tests.
- **Official docs:** [.NET documentation](https://learn.microsoft.com/dotnet/) and the [C# language reference](https://learn.microsoft.com/dotnet/csharp/language-reference/).

### Quick Reference

```csharp
// Async
async Task<int> GetAsync() { await Task.Delay(100); return 42; }
int[] all = await Task.WhenAll(t1, t2);

// Pattern matching
string label = value switch { < 0 => "neg", 0 => "zero", _ => "pos" };

// Records
record Point(int X, int Y);
var moved = point with { X = 5 };

// Nullable reference types
#nullable enable
string? maybeNull = null;

// yield iterator
IEnumerable<int> Evens() { for (int i = 0; ; i += 2) yield return i; }

// Dependency injection (constructor)
class Svc { public Svc(IDep dep) { } }

// Unit test
[Fact] public void Test() => Assert.Equal(5, calc.Add(2, 3));
```

Happy coding — and welcome to advanced C#! 🚀

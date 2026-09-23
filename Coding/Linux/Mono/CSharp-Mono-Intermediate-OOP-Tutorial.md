# C# with Mono — Intermediate & Object-Oriented Programming

This is the follow-up to the [C# Absolute Beginner tutorial](./CSharp-Mono-Beginner-Tutorial.md). It assumes you're comfortable with variables, loops, methods, and basic classes, and takes you into the concepts that make C# a powerful object-oriented language: **inheritance, interfaces, polymorphism, generics, LINQ, file I/O**, and more.

We continue to use the Mono workflow (`mcs` to compile, `mono` to run). Everything here applies identically to modern .NET.

```bash
mcs Program.cs
mono Program.exe
```

---

## Table of Contents

1. [Encapsulation & Properties](#1-encapsulation--properties)
2. [Inheritance](#2-inheritance)
3. [Polymorphism & Virtual Methods](#3-polymorphism--virtual-methods)
4. [Abstract Classes](#4-abstract-classes)
5. [Interfaces](#5-interfaces)
6. [Enums and Structs](#6-enums-and-structs)
7. [Static Members](#7-static-members)
8. [Generics](#8-generics)
9. [Collections in Depth](#9-collections-in-depth)
10. [LINQ](#10-linq)
11. [Delegates, Events, and Lambdas](#11-delegates-events-and-lambdas)
12. [Exception Handling in Depth](#12-exception-handling-in-depth)
13. [File Input/Output](#13-file-inputoutput)
14. [Putting It All Together: A Library Management System](#14-putting-it-all-together-a-library-management-system)
15. [Design Principles to Grow Into](#15-design-principles-to-grow-into)
16. [Where to Go Next](#16-where-to-go-next)

---

## 1. Encapsulation & Properties

**Encapsulation** means hiding an object's internal data and exposing controlled access to it. This prevents other code from putting the object into an invalid state.

Instead of exposing a public field directly, use a **property** with a `get` and `set`, and validate inside the setter.

```csharp
using System;

class BankAccount
{
    // Private field: the actual stored data, hidden from outside code.
    private decimal _balance;

    // Public property: controlled access to the field.
    public decimal Balance
    {
        get { return _balance; }
        private set { _balance = value; }   // only this class can set it
    }

    public void Deposit(decimal amount)
    {
        if (amount <= 0)
            throw new ArgumentException("Deposit must be positive.");
        _balance += amount;
    }

    public void Withdraw(decimal amount)
    {
        if (amount > _balance)
            throw new InvalidOperationException("Insufficient funds.");
        _balance -= amount;
    }
}

class Program
{
    static void Main()
    {
        var account = new BankAccount();
        account.Deposit(100);
        account.Withdraw(30);
        Console.WriteLine($"Balance: {account.Balance}");   // Balance: 70
        // account.Balance = 1000000;  // Won't compile — set is private!
    }
}
```

### Access modifiers

| Modifier | Who can access it |
|----------|-------------------|
| `public` | Everyone. |
| `private` | Only the same class. |
| `protected` | The same class and any classes that inherit from it. |
| `internal` | Any code in the same assembly (compiled unit). |

---

## 2. Inheritance

**Inheritance** lets one class (the *derived* / *child* class) reuse and extend another (the *base* / *parent* class). Use `:` to inherit.

```csharp
using System;

class Animal
{
    public string Name { get; set; }

    public void Eat()
    {
        Console.WriteLine($"{Name} is eating.");
    }
}

// Dog inherits everything from Animal, and adds its own behavior.
class Dog : Animal
{
    public void Fetch()
    {
        Console.WriteLine($"{Name} fetches the ball.");
    }
}

class Program
{
    static void Main()
    {
        var dog = new Dog();
        dog.Name = "Rex";
        dog.Eat();     // inherited from Animal
        dog.Fetch();   // defined in Dog
    }
}
```

### Calling the base constructor

```csharp
class Animal
{
    public string Name { get; }
    public Animal(string name) => Name = name;
}

class Dog : Animal
{
    public string Breed { get; }

    // ": base(name)" passes arguments up to the Animal constructor.
    public Dog(string name, string breed) : base(name)
    {
        Breed = breed;
    }
}
```

---

## 3. Polymorphism & Virtual Methods

**Polymorphism** ("many forms") lets a base-class reference call the correct derived-class behavior at runtime. Mark a method `virtual` in the base class and `override` it in the child.

```csharp
using System;

class Animal
{
    public string Name { get; set; }

    // "virtual" means child classes may replace this.
    public virtual void Speak()
    {
        Console.WriteLine($"{Name} makes a sound.");
    }
}

class Dog : Animal
{
    public override void Speak() => Console.WriteLine($"{Name} says Woof!");
}

class Cat : Animal
{
    public override void Speak() => Console.WriteLine($"{Name} says Meow!");
}

class Program
{
    static void Main()
    {
        // A list of Animals, but each holds a different concrete type.
        Animal[] animals =
        {
            new Dog { Name = "Rex" },
            new Cat { Name = "Whiskers" },
            new Animal { Name = "Generic" }
        };

        foreach (Animal a in animals)
            a.Speak();   // calls the RIGHT version for each object
    }
}
```

Output:

```
Rex says Woof!
Whiskers says Meow!
Generic makes a sound.
```

This is the heart of OOP: you write code against the general `Animal` type, and the correct specific behavior runs automatically.

---

## 4. Abstract Classes

An **abstract class** is a base class that can't be instantiated on its own — it exists to be inherited. It can define **abstract methods** (no body) that every child *must* implement.

```csharp
using System;

abstract class Shape
{
    // No implementation — each shape must provide its own.
    public abstract double Area();

    // Abstract classes can also have normal (implemented) methods.
    public void Describe() => Console.WriteLine($"This shape has area {Area():F2}.");
}

class Circle : Shape
{
    public double Radius { get; set; }
    public override double Area() => Math.PI * Radius * Radius;
}

class Rectangle : Shape
{
    public double Width { get; set; }
    public double Height { get; set; }
    public override double Area() => Width * Height;
}

class Program
{
    static void Main()
    {
        Shape[] shapes =
        {
            new Circle { Radius = 3 },
            new Rectangle { Width = 4, Height = 5 }
        };

        foreach (Shape s in shapes)
            s.Describe();
        // This shape has area 28.27.
        // This shape has area 20.00.

        // new Shape();  // Error: cannot create an instance of an abstract class
    }
}
```

---

## 5. Interfaces

An **interface** is a pure contract: a list of members a class promises to provide, with no implementation. A class can implement **many** interfaces (unlike inheritance, which allows only one base class).

```csharp
using System;

interface IMovable
{
    void Move();
}

interface IDrawable
{
    void Draw();
}

// A class can implement multiple interfaces.
class Player : IMovable, IDrawable
{
    public string Name { get; set; }

    public void Move() => Console.WriteLine($"{Name} moves.");
    public void Draw() => Console.WriteLine($"{Name} is drawn on screen.");
}

class Program
{
    static void Main()
    {
        Player player = new Player { Name = "Hero" };
        player.Move();
        player.Draw();

        // Treat it purely as its contract:
        IMovable movable = player;
        movable.Move();
    }
}
```

### Abstract class vs. interface — which to use?

| Use an **abstract class** when… | Use an **interface** when… |
|----------------------------------|-----------------------------|
| Classes share common code/state. | You only need to define a capability/contract. |
| There's a clear "is-a" relationship. | Unrelated classes should share a capability. |
| You need constructors or fields. | A class must support multiple contracts. |

> By convention, C# interface names start with a capital `I` (e.g. `IMovable`, `IComparable`).

---

## 6. Enums and Structs

### Enums — a named set of constant values

```csharp
using System;

enum Direction { North, East, South, West }

class Program
{
    static void Main()
    {
        Direction heading = Direction.North;

        if (heading == Direction.North)
            Console.WriteLine("Heading north!");

        Console.WriteLine(heading);          // North
        Console.WriteLine((int)heading);     // 0  (enums are backed by ints)
    }
}
```

### Structs — lightweight value types

A `struct` looks like a class but is a **value type**: it's copied on assignment rather than referenced. Use structs for small, immutable data bundles (points, coordinates, money).

```csharp
struct Point
{
    public int X { get; }
    public int Y { get; }
    public Point(int x, int y) { X = x; Y = y; }
    public override string ToString() => $"({X}, {Y})";
}

// Usage:
Point p1 = new Point(3, 4);
Point p2 = p1;         // p2 is an independent COPY of p1
Console.WriteLine(p1); // (3, 4)
```

> **Class vs. struct:** classes are *reference types* (variables point to the same object); structs are *value types* (each variable holds its own copy). Prefer classes unless you have a small, simple data holder.

---

## 7. Static Members

A `static` member belongs to the **class itself**, not to any individual object. Useful for utilities and shared counters.

```csharp
using System;

class Counter
{
    // Shared across ALL instances.
    public static int TotalCreated = 0;

    public Counter() => TotalCreated++;

    // A static method: called on the class, not an object.
    public static int Square(int n) => n * n;
}

class Program
{
    static void Main()
    {
        new Counter();
        new Counter();
        new Counter();

        Console.WriteLine(Counter.TotalCreated);  // 3
        Console.WriteLine(Counter.Square(5));     // 25 — no object needed
    }
}
```

`Console.WriteLine` and `Math.PI` are static members you've been using all along.

---

## 8. Generics

**Generics** let you write code that works with any type while keeping full type safety. The `<T>` is a placeholder for a type supplied later.

```csharp
using System;

// A generic "box" that can hold a value of any type T.
class Box<T>
{
    private T _value;
    public void Put(T value) => _value = value;
    public T Get() => _value;
}

// A generic method.
class Utils
{
    public static void Swap<T>(ref T a, ref T b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
}

class Program
{
    static void Main()
    {
        Box<int> intBox = new Box<int>();
        intBox.Put(42);
        Console.WriteLine(intBox.Get());   // 42

        Box<string> strBox = new Box<string>();
        strBox.Put("hello");
        Console.WriteLine(strBox.Get());   // hello

        int x = 1, y = 2;
        Utils.Swap(ref x, ref y);
        Console.WriteLine($"{x}, {y}");    // 2, 1
    }
}
```

Generics are why `List<T>`, `Dictionary<K,V>`, and many other collections can work with any type safely.

---

## 9. Collections in Depth

Beyond arrays and `List<T>`, the `System.Collections.Generic` namespace offers specialized collections.

```csharp
using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        // Dictionary: key -> value lookups.
        Dictionary<string, int> ages = new Dictionary<string, int>();
        ages["Alice"] = 30;
        ages["Bob"] = 25;
        Console.WriteLine(ages["Alice"]);          // 30
        if (ages.ContainsKey("Bob"))
            Console.WriteLine($"Bob is {ages["Bob"]}");

        foreach (KeyValuePair<string, int> pair in ages)
            Console.WriteLine($"{pair.Key} = {pair.Value}");

        // HashSet: a collection of unique values.
        HashSet<int> unique = new HashSet<int> { 1, 2, 2, 3, 3, 3 };
        Console.WriteLine(unique.Count);           // 3

        // Queue: first-in, first-out.
        Queue<string> line = new Queue<string>();
        line.Enqueue("first");
        line.Enqueue("second");
        Console.WriteLine(line.Dequeue());         // first

        // Stack: last-in, first-out.
        Stack<string> plates = new Stack<string>();
        plates.Push("bottom");
        plates.Push("top");
        Console.WriteLine(plates.Pop());           // top
    }
}
```

| Collection | Best for |
|------------|----------|
| `List<T>` | Ordered, resizable sequence. |
| `Dictionary<K,V>` | Fast lookup by key. |
| `HashSet<T>` | Unique items, fast membership tests. |
| `Queue<T>` | FIFO processing (first in, first out). |
| `Stack<T>` | LIFO processing (last in, first out). |

---

## 10. LINQ

**LINQ** (Language Integrated Query) lets you query and transform collections with readable, declarative code. Add `using System.Linq;`.

```csharp
using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        List<int> numbers = new List<int> { 5, 2, 8, 1, 9, 3, 7 };

        // Filter: keep only even numbers.
        var evens = numbers.Where(n => n % 2 == 0);
        Console.WriteLine(string.Join(", ", evens));      // 2, 8

        // Transform (project) each element.
        var squares = numbers.Select(n => n * n);
        Console.WriteLine(string.Join(", ", squares));    // 25, 4, 64, ...

        // Sort.
        var sorted = numbers.OrderBy(n => n);
        Console.WriteLine(string.Join(", ", sorted));     // 1, 2, 3, ...

        // Aggregate operations.
        Console.WriteLine(numbers.Max());                 // 9
        Console.WriteLine(numbers.Min());                 // 1
        Console.WriteLine(numbers.Sum());                 // 35
        Console.WriteLine(numbers.Average());             // 5
        Console.WriteLine(numbers.Count(n => n > 4));     // 4

        // Chaining: even numbers, squared, sorted descending.
        var result = numbers
            .Where(n => n % 2 == 0)
            .Select(n => n * n)
            .OrderByDescending(n => n);
        Console.WriteLine(string.Join(", ", result));     // 64, 4
    }
}
```

The `n => n % 2 == 0` syntax is a **lambda** — a compact inline function. `n` is the input, and the part after `=>` is what it returns.

---

## 11. Delegates, Events, and Lambdas

A **delegate** is a type that holds a reference to a method — essentially a "function variable."

```csharp
using System;

class Program
{
    // A delegate type: any method taking two ints and returning an int.
    delegate int MathOp(int a, int b);

    static int Add(int a, int b) => a + b;
    static int Multiply(int a, int b) => a * b;

    static void Main()
    {
        MathOp op = Add;
        Console.WriteLine(op(3, 4));       // 7

        op = Multiply;
        Console.WriteLine(op(3, 4));       // 12

        // A lambda assigned to a delegate.
        MathOp subtract = (a, b) => a - b;
        Console.WriteLine(subtract(10, 3)); // 7

        // Built-in generic delegates: Func (returns a value), Action (returns void).
        Func<int, int> square = x => x * x;
        Action<string> shout = msg => Console.WriteLine(msg.ToUpper());
        Console.WriteLine(square(5));       // 25
        shout("hello");                     // HELLO
    }
}
```

### Events

**Events** build on delegates to let objects notify subscribers when something happens — the basis of most UI and messaging code.

```csharp
using System;

class Button
{
    // An event other code can subscribe to.
    public event Action Clicked;

    public void Click()
    {
        Console.WriteLine("Button pressed.");
        Clicked?.Invoke();   // notify all subscribers (if any)
    }
}

class Program
{
    static void Main()
    {
        var button = new Button();
        button.Clicked += () => Console.WriteLine("Handler 1 ran.");
        button.Clicked += () => Console.WriteLine("Handler 2 ran.");
        button.Click();
    }
}
```

---

## 12. Exception Handling in Depth

The beginner tutorial covered `try`/`catch`. Here's the fuller picture.

```csharp
using System;

class Program
{
    static void Main()
    {
        try
        {
            Process("abc");
        }
        catch (FormatException ex)          // most specific first
        {
            Console.WriteLine($"Format problem: {ex.Message}");
        }
        catch (Exception ex)                // general fallback last
        {
            Console.WriteLine($"Something went wrong: {ex.Message}");
        }
        finally
        {
            // ALWAYS runs — great for cleanup (closing files, connections).
            Console.WriteLine("Done processing.");
        }
    }

    static void Process(string input)
    {
        int value = int.Parse(input);   // throws FormatException for "abc"
        Console.WriteLine(value);
    }
}
```

### Throwing your own exceptions

```csharp
class AgeValidator
{
    public static void Validate(int age)
    {
        if (age < 0)
            throw new ArgumentOutOfRangeException(nameof(age), "Age cannot be negative.");
    }
}
```

### Custom exception types

```csharp
class InsufficientFundsException : Exception
{
    public InsufficientFundsException(string message) : base(message) { }
}
```

Guidelines: catch the **most specific** exception you can, use `finally` for cleanup, and only catch what you can meaningfully handle.

---

## 13. File Input/Output

The `System.IO` namespace reads and writes files.

```csharp
using System;
using System.IO;

class Program
{
    static void Main()
    {
        string path = "notes.txt";

        // Write text (overwrites the file).
        File.WriteAllText(path, "First line\n");

        // Append more.
        File.AppendAllText(path, "Second line\n");

        // Write multiple lines from an array.
        File.WriteAllLines(path, new[] { "Alpha", "Beta", "Gamma" });

        // Read it all back.
        string content = File.ReadAllText(path);
        Console.WriteLine(content);

        // Read line by line.
        string[] lines = File.ReadAllLines(path);
        foreach (string line in lines)
            Console.WriteLine($"> {line}");

        // Check existence and clean up.
        if (File.Exists(path))
            File.Delete(path);
    }
}
```

For large files, use streaming readers/writers so you don't load everything into memory:

```csharp
using (StreamWriter writer = new StreamWriter("big.txt"))
{
    for (int i = 0; i < 1000; i++)
        writer.WriteLine($"Line {i}");
}   // the 'using' block automatically closes/flushes the file

using (StreamReader reader = new StreamReader("big.txt"))
{
    string line;
    while ((line = reader.ReadLine()) != null)
        Console.WriteLine(line);
}
```

---

## 14. Putting It All Together: A Library Management System

This example combines encapsulation, inheritance, interfaces, generics, LINQ, and collections. Save as `Library.cs`.

```csharp
using System;
using System.Collections.Generic;
using System.Linq;

// A contract for anything that can be borrowed.
interface IBorrowable
{
    bool IsAvailable { get; }
    void Borrow();
    void Return();
}

// Base class with shared item data.
abstract class LibraryItem : IBorrowable
{
    public string Title { get; }
    public int Id { get; }
    public bool IsAvailable { get; private set; } = true;

    protected LibraryItem(int id, string title)
    {
        Id = id;
        Title = title;
    }

    public void Borrow()
    {
        if (!IsAvailable)
            throw new InvalidOperationException($"'{Title}' is already borrowed.");
        IsAvailable = false;
    }

    public void Return() => IsAvailable = true;

    // Each item type describes itself differently.
    public abstract string Describe();
}

class Book : LibraryItem
{
    public string Author { get; }
    public Book(int id, string title, string author) : base(id, title) => Author = author;
    public override string Describe() => $"Book: \"{Title}\" by {Author}";
}

class Dvd : LibraryItem
{
    public int Minutes { get; }
    public Dvd(int id, string title, int minutes) : base(id, title) => Minutes = minutes;
    public override string Describe() => $"DVD: \"{Title}\" ({Minutes} min)";
}

// A generic catalog that stores any LibraryItem.
class Catalog<T> where T : LibraryItem
{
    private readonly List<T> _items = new List<T>();

    public void Add(T item) => _items.Add(item);

    public T FindById(int id) => _items.FirstOrDefault(i => i.Id == id);

    public IEnumerable<T> Available() => _items.Where(i => i.IsAvailable);

    public void PrintAll()
    {
        foreach (var item in _items)
        {
            string status = item.IsAvailable ? "available" : "borrowed";
            Console.WriteLine($"[{item.Id}] {item.Describe()} — {status}");
        }
    }
}

class Program
{
    static void Main()
    {
        var catalog = new Catalog<LibraryItem>();
        catalog.Add(new Book(1, "The Pragmatic Programmer", "Hunt & Thomas"));
        catalog.Add(new Book(2, "Clean Code", "Robert C. Martin"));
        catalog.Add(new Dvd(3, "Inception", 148));

        Console.WriteLine("=== Initial catalog ===");
        catalog.PrintAll();

        // Borrow one item.
        var item = catalog.FindById(2);
        item.Borrow();
        Console.WriteLine($"\nBorrowed: {item.Describe()}\n");

        Console.WriteLine("=== Available items ===");
        foreach (var available in catalog.Available())
            Console.WriteLine(available.Describe());

        // Demonstrate error handling.
        try
        {
            item.Borrow();   // already borrowed -> throws
        }
        catch (InvalidOperationException ex)
        {
            Console.WriteLine($"\nError: {ex.Message}");
        }
    }
}
```

Compile and run:

```bash
mcs Library.cs
mono Library.exe
```

Every major concept from this tutorial appears here: an **interface** (`IBorrowable`), an **abstract base class** (`LibraryItem`), **inheritance & polymorphism** (`Book`/`Dvd` overriding `Describe`), **encapsulation** (`IsAvailable` with a private setter), **generics with a constraint** (`Catalog<T> where T : LibraryItem`), **LINQ** (`FirstOrDefault`, `Where`), and **exception handling**.

---

## 15. Design Principles to Grow Into

As your programs get bigger, these principles keep them maintainable:

- **Single Responsibility:** each class should do one thing well.
- **Don't Repeat Yourself (DRY):** extract repeated logic into methods or base classes.
- **Program to interfaces, not implementations:** depend on `IBorrowable`, not `Book`, so code stays flexible.
- **Favor composition over inheritance:** deep inheritance chains get brittle; often it's cleaner for a class to *contain* another than to inherit from it.
- **Encapsulate what varies:** hide details that are likely to change behind stable interfaces.

These are the gateway to the **SOLID** principles and design patterns you'll meet as you advance.

---

## 16. Where to Go Next

- **Async programming:** `async`/`await` and `Task` for non-blocking I/O and concurrency.
- **Design patterns:** Strategy, Factory, Observer, Repository, and more.
- **Unit testing:** try NUnit or xUnit to write automated tests for your classes.
- **Dependency injection:** structuring larger apps for testability and flexibility.
- **Modern .NET:** migrate from Mono to the `dotnet` SDK for the latest language features (records, pattern matching, nullable reference types).
- **Graphics practice:** apply your OOP skills in the [GDI+ on Mono](./GDIPlus-Mono-Tutorial.md) and [SkiaSharp](./SkiaSharp-Tutorial.md) tutorials in this folder.
- **Official docs:** the [C# programming guide](https://learn.microsoft.com/dotnet/csharp/programming-guide/) and [C# language reference](https://learn.microsoft.com/dotnet/csharp/language-reference/).

### Quick Reference

```csharp
// Inheritance + polymorphism
class Base { public virtual void Go() { } }
class Child : Base { public override void Go() { } }

// Abstract + interface
abstract class Shape { public abstract double Area(); }
interface IMovable { void Move(); }

// Generics with a constraint
class Repo<T> where T : class { }

// LINQ
var result = list.Where(x => x > 0).Select(x => x * 2).OrderBy(x => x);

// Delegates / lambdas
Func<int,int> square = x => x * x;
Action<string> log = s => Console.WriteLine(s);

// Exceptions
try { } catch (SpecificException ex) { } finally { }

// File I/O
File.WriteAllText("f.txt", "data");
string text = File.ReadAllText("f.txt");
```

Happy coding! 🚀

# C# with Mono — An Absolute Beginner's Tutorial

Welcome! This tutorial teaches you the **C# programming language** from scratch using the **Mono** runtime. No prior programming experience is assumed. By the end you'll be able to write, compile, and run real C# programs from the command line.

Mono is a free, open-source, cross-platform implementation of the .NET runtime. It lets you compile and run C# programs on **Linux, macOS, and Windows**. It's a great, lightweight way to learn C# because you only need two commands: one to compile (`mcs`) and one to run (`mono`).

> **Which should I use — Mono or .NET?**
> Modern .NET (the `dotnet` SDK) is the mainstream choice today for new projects. Mono is still perfect for learning the language fundamentals, for lightweight scripting, and on platforms where it's already installed. Everything you learn here about the C# *language* applies identically to modern .NET. A short appendix shows the `dotnet` equivalents.

---

## Table of Contents

1. [Installing Mono](#1-installing-mono)
2. [Hello, World!](#2-hello-world)
3. [How Compiling and Running Works](#3-how-compiling-and-running-works)
4. [Variables and Data Types](#4-variables-and-data-types)
5. [Getting Input from the User](#5-getting-input-from-the-user)
6. [Operators and Expressions](#6-operators-and-expressions)
7. [Making Decisions: if / else / switch](#7-making-decisions-if--else--switch)
8. [Loops](#8-loops)
9. [Methods](#9-methods)
10. [Arrays and Lists](#10-arrays-and-lists)
11. [Classes and Objects](#11-classes-and-objects)
12. [Handling Errors](#12-handling-errors)
13. [Putting It All Together: A Number Guessing Game](#13-putting-it-all-together-a-number-guessing-game)
14. [Common Beginner Mistakes](#14-common-beginner-mistakes)
15. [Appendix: Doing the Same with the `dotnet` SDK](#15-appendix-doing-the-same-with-the-dotnet-sdk)
16. [Where to Go Next](#16-where-to-go-next)

---

## 1. Installing Mono

You need the Mono runtime, which includes the C# compiler (`mcs`) and the runtime launcher (`mono`).

### Windows

Download and run the installer from the [official Mono download page](https://www.mono-project.com/download/stable/). After installing, you may need to open a **new** terminal so the `PATH` updates.

### macOS (Homebrew)

```bash
brew install mono
```

### Linux (Debian / Ubuntu)

```bash
sudo apt update
sudo apt install mono-complete
```

### Linux (Fedora)

```bash
sudo dnf install mono-complete
```

### Verify it works

Open a terminal and run:

```bash
mono --version
mcs --version
```

You should see version information for both. If the commands aren't found, the install directory isn't on your `PATH` — reopen your terminal or re-check the install.

---

## 2. Hello, World!

Every programming journey starts here. Create a file named `Hello.cs` in a folder you can find easily (for example `D:\CodingDojo\CSharp`).

```csharp
using System;

class Program
{
    static void Main()
    {
        Console.WriteLine("Hello, World!");
    }
}
```

Now compile and run it:

```bash
mcs Hello.cs
mono Hello.exe
```

You should see:

```
Hello, World!
```

🎉 Congratulations — you just wrote, compiled, and ran a C# program!

### What every line means

| Line | Meaning |
|------|---------|
| `using System;` | Gives us access to built-in tools like `Console`. Think of it as "import the standard toolbox." |
| `class Program` | C# code lives inside **classes**. This one is named `Program`. |
| `static void Main()` | The **entry point** — the very first method that runs when the program starts. |
| `Console.WriteLine(...)` | Prints a line of text to the screen. |
| `;` | Every statement ends with a semicolon. |
| `{ }` | Curly braces group code into blocks. |

> **Case matters!** C# is case-sensitive. `Console` works; `console` does not.

---

## 3. How Compiling and Running Works

C# is a **compiled** language. That means:

1. You write human-readable source code in a `.cs` file.
2. The **compiler** (`mcs`) translates it into an executable `.exe` file containing bytecode.
3. The **runtime** (`mono`) executes that `.exe`.

```
Hello.cs  --(mcs compiles)-->  Hello.exe  --(mono runs)-->  output
```

Useful compiler options:

```bash
mcs Hello.cs                    # produces Hello.exe
mcs Hello.cs -out:greet.exe     # choose the output name
mcs File1.cs File2.cs           # compile multiple files into one program
```

> On Linux/macOS you always launch with `mono Hello.exe`. On Windows you can often run `Hello.exe` directly, but `mono Hello.exe` always works.

---

## 4. Variables and Data Types

A **variable** is a named box that stores a value. In C# you declare a variable by writing its **type**, then its **name**, then optionally a value.

```csharp
using System;

class Program
{
    static void Main()
    {
        int age = 30;                 // whole number
        double price = 19.99;         // number with a decimal point
        bool isStudent = true;        // true or false
        char grade = 'A';             // a single character (single quotes)
        string name = "Alice";        // text (double quotes)

        Console.WriteLine(name);
        Console.WriteLine(age);
        Console.WriteLine(price);
        Console.WriteLine(isStudent);
        Console.WriteLine(grade);
    }
}
```

### The common built-in types

| Type | Stores | Example |
|------|--------|---------|
| `int` | Whole numbers | `42`, `-7` |
| `double` | Decimal numbers | `3.14`, `-0.5` |
| `bool` | True/false | `true`, `false` |
| `char` | One character | `'x'` |
| `string` | Text | `"hello"` |

### String interpolation (combining text and variables)

Put a `$` before the string and wrap variables in `{ }`:

```csharp
string name = "Alice";
int age = 30;
Console.WriteLine($"{name} is {age} years old.");
// Output: Alice is 30 years old.
```

### `var` — let the compiler figure out the type

```csharp
var count = 10;         // compiler knows this is an int
var message = "hi";     // compiler knows this is a string
```

`var` is just a shortcut; the variable still has a fixed type.

---

## 5. Getting Input from the User

Use `Console.ReadLine()` to read a line of text the user types. It always returns a **string**, so convert it if you need a number.

```csharp
using System;

class Program
{
    static void Main()
    {
        Console.Write("What is your name? ");
        string name = Console.ReadLine();

        Console.Write("How old are you? ");
        string ageText = Console.ReadLine();
        int age = int.Parse(ageText);   // convert text to a number

        Console.WriteLine($"Hi {name}! Next year you will be {age + 1}.");
    }
}
```

> `int.Parse` throws an error if the text isn't a valid number. Later you'll see `int.TryParse`, a safer version that doesn't crash.

---

## 6. Operators and Expressions

### Arithmetic

```csharp
int a = 10, b = 3;
Console.WriteLine(a + b);   // 13  addition
Console.WriteLine(a - b);   // 7   subtraction
Console.WriteLine(a * b);   // 30  multiplication
Console.WriteLine(a / b);   // 3   integer division (drops the remainder!)
Console.WriteLine(a % b);   // 1   modulo (the remainder)
```

> **Watch out:** `10 / 3` gives `3`, not `3.33`, because both are integers. To get decimals, make at least one a `double`: `10.0 / 3` → `3.333...`.

### Comparison (results are `bool`)

```csharp
Console.WriteLine(a == b);  // false  equal to
Console.WriteLine(a != b);  // true   not equal to
Console.WriteLine(a > b);   // true   greater than
Console.WriteLine(a <= b);  // false  less than or equal
```

### Logical

```csharp
bool sunny = true, warm = false;
Console.WriteLine(sunny && warm);  // AND: true only if both are true  -> false
Console.WriteLine(sunny || warm);  // OR:  true if either is true       -> true
Console.WriteLine(!sunny);         // NOT: flips it                     -> false
```

---

## 7. Making Decisions: if / else / switch

### if / else if / else

```csharp
using System;

class Program
{
    static void Main()
    {
        Console.Write("Enter your score: ");
        int score = int.Parse(Console.ReadLine());

        if (score >= 90)
            Console.WriteLine("Grade: A");
        else if (score >= 80)
            Console.WriteLine("Grade: B");
        else if (score >= 70)
            Console.WriteLine("Grade: C");
        else
            Console.WriteLine("Grade: F");
    }
}
```

### switch

When you're comparing one value against several fixed options, `switch` is cleaner:

```csharp
int day = 3;

switch (day)
{
    case 1:
        Console.WriteLine("Monday");
        break;
    case 2:
        Console.WriteLine("Tuesday");
        break;
    case 3:
        Console.WriteLine("Wednesday");
        break;
    default:
        Console.WriteLine("Another day");
        break;
}
```

> Don't forget `break;` at the end of each `case` — it stops the switch from "falling through" into the next case.

---

## 8. Loops

Loops repeat a block of code.

### `while` — repeat while a condition is true

```csharp
int i = 1;
while (i <= 5)
{
    Console.WriteLine(i);
    i++;            // i = i + 1;  (without this, the loop never ends!)
}
```

### `for` — when you know how many times

```csharp
for (int j = 1; j <= 5; j++)
{
    Console.WriteLine(j);
}
```

The `for` header has three parts: `initialize; condition; step`.

### `foreach` — loop over a collection

```csharp
string[] fruits = { "apple", "banana", "cherry" };
foreach (string fruit in fruits)
{
    Console.WriteLine(fruit);
}
```

### `break` and `continue`

```csharp
for (int n = 1; n <= 10; n++)
{
    if (n == 5) break;       // stop the loop entirely
    if (n % 2 == 0) continue; // skip the rest, go to the next n
    Console.WriteLine(n);     // prints 1, 3
}
```

---

## 9. Methods

A **method** is a reusable, named block of code. It can take **parameters** (inputs) and **return** a value.

```csharp
using System;

class Program
{
    // A method that takes two ints and returns their sum.
    static int Add(int x, int y)
    {
        return x + y;
    }

    // A method that returns nothing (void) — it just does something.
    static void Greet(string name)
    {
        Console.WriteLine($"Hello, {name}!");
    }

    static void Main()
    {
        int result = Add(3, 4);
        Console.WriteLine(result);   // 7

        Greet("Alice");              // Hello, Alice!
    }
}
```

Breaking down `static int Add(int x, int y)`:

- `static` — belongs to the class itself (fine for now; you'll use this for all `Main`-level methods).
- `int` — the **return type** (the kind of value it gives back). Use `void` if it returns nothing.
- `Add` — the method's name.
- `(int x, int y)` — the parameters it accepts.

---

## 10. Arrays and Lists

### Arrays — a fixed-size collection

```csharp
int[] numbers = { 10, 20, 30, 40 };

Console.WriteLine(numbers[0]);      // 10  (indexes start at 0!)
Console.WriteLine(numbers[3]);      // 40
Console.WriteLine(numbers.Length);  // 4

numbers[1] = 99;                    // change an element
```

> **Zero-based indexing:** the first element is `[0]`, the second is `[1]`, and the last is `[Length - 1]`. Accessing `numbers[4]` here would crash with an `IndexOutOfRangeException`.

### Lists — a resizable collection

Lists can grow and shrink. They live in `System.Collections.Generic`.

```csharp
using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        List<string> names = new List<string>();

        names.Add("Alice");
        names.Add("Bob");
        names.Add("Carol");

        names.Remove("Bob");

        Console.WriteLine(names.Count);   // 2

        foreach (string name in names)
            Console.WriteLine(name);
    }
}
```

---

## 11. Classes and Objects

A **class** is a blueprint. An **object** is a specific thing built from that blueprint. Classes bundle **data** (fields/properties) with **behavior** (methods).

```csharp
using System;

// The blueprint.
class Dog
{
    // Properties (data each dog has).
    public string Name { get; set; }
    public int Age { get; set; }

    // A method (behavior).
    public void Bark()
    {
        Console.WriteLine($"{Name} says: Woof!");
    }
}

class Program
{
    static void Main()
    {
        // Create objects (instances) from the blueprint.
        Dog dog1 = new Dog();
        dog1.Name = "Rex";
        dog1.Age = 3;

        Dog dog2 = new Dog();
        dog2.Name = "Bella";
        dog2.Age = 5;

        dog1.Bark();   // Rex says: Woof!
        dog2.Bark();   // Bella says: Woof!

        Console.WriteLine($"{dog2.Name} is {dog2.Age} years old.");
    }
}
```

### Constructors — set up an object when it's created

A **constructor** is a special method that runs when you use `new`. It has the same name as the class.

```csharp
class Dog
{
    public string Name { get; set; }
    public int Age { get; set; }

    // Constructor.
    public Dog(string name, int age)
    {
        Name = name;
        Age = age;
    }

    public void Bark() => Console.WriteLine($"{Name} says: Woof!");
}

// Usage:
Dog dog = new Dog("Rex", 3);   // much tidier!
dog.Bark();
```

---

## 12. Handling Errors

Some operations can fail at runtime (bad input, missing files, etc.). Wrap risky code in a `try` / `catch` block so your program doesn't crash.

```csharp
using System;

class Program
{
    static void Main()
    {
        Console.Write("Enter a number: ");
        string input = Console.ReadLine();

        try
        {
            int number = int.Parse(input);
            Console.WriteLine($"You entered {number}.");
        }
        catch (FormatException)
        {
            Console.WriteLine("That wasn't a valid number!");
        }
    }
}
```

### A safer alternative: `int.TryParse`

`TryParse` returns `true`/`false` instead of throwing, so you often don't even need `try`/`catch`:

```csharp
Console.Write("Enter a number: ");
string input = Console.ReadLine();

if (int.TryParse(input, out int number))
    Console.WriteLine($"You entered {number}.");
else
    Console.WriteLine("That wasn't a valid number!");
```

---

## 13. Putting It All Together: A Number Guessing Game

This little game uses almost everything you've learned: variables, input, loops, conditionals, and error handling. Save it as `Guess.cs`.

```csharp
using System;

class Program
{
    static void Main()
    {
        Random random = new Random();
        int secret = random.Next(1, 101);   // random number from 1 to 100
        int attempts = 0;
        bool won = false;

        Console.WriteLine("I'm thinking of a number between 1 and 100.");

        while (!won)
        {
            Console.Write("Your guess: ");
            string input = Console.ReadLine();

            // Validate the input safely.
            if (!int.TryParse(input, out int guess))
            {
                Console.WriteLine("Please enter a valid whole number.");
                continue;   // skip the rest and ask again
            }

            attempts++;

            if (guess < secret)
                Console.WriteLine("Too low! Try again.");
            else if (guess > secret)
                Console.WriteLine("Too high! Try again.");
            else
            {
                won = true;
                Console.WriteLine($"Correct! You got it in {attempts} attempts.");
            }
        }
    }
}
```

Compile and play:

```bash
mcs Guess.cs
mono Guess.exe
```

Try changing the range, or adding a maximum number of attempts as an exercise!

---

## 14. Common Beginner Mistakes

| Mistake | Fix |
|---------|-----|
| Forgetting the `;` at the end of a statement | Add the semicolon. |
| Using `=` (assignment) instead of `==` (comparison) in an `if` | `if (x == 5)`, not `if (x = 5)`. |
| Wrong case: `console.writeline` | It's `Console.WriteLine`. C# is case-sensitive. |
| `10 / 3` giving `3` instead of `3.33` | Use a `double`: `10.0 / 3`. |
| Array index out of range | Valid indexes are `0` to `Length - 1`. |
| A `while` loop that never ends | Make sure something inside the loop changes the condition. |
| Forgetting `break;` in a `switch` | Each `case` needs a `break;`. |
| Mismatched `{ }` braces | Every `{` needs a matching `}`. Indent consistently to spot them. |

---

## 15. Appendix: Doing the Same with the `dotnet` SDK

If you have (or later install) the modern .NET SDK, the *language* is identical — only the build commands differ.

```bash
# Create a new console project in a folder called MyApp
dotnet new console -n MyApp
cd MyApp

# Edit Program.cs, then run (compiles and runs in one step):
dotnet run
```

With modern .NET you can also use **top-level statements**, which skip the class and `Main` boilerplate for small programs:

```csharp
// Program.cs — this whole file is a valid program on .NET 6+
Console.WriteLine("Hello, World!");
```

Everything else in this tutorial — variables, loops, methods, classes — works exactly the same.

---

## 16. Where to Go Next

You now know the fundamentals of C#! Here's where to build from here:

- **Object-oriented programming:** inheritance, interfaces, and polymorphism — the next big step after classes.
- **Collections & LINQ:** powerful ways to query and transform lists of data.
- **Exceptions in depth:** creating your own exception types and using `finally`.
- **File I/O:** reading and writing files with `System.IO`.
- **Graphics:** try the companion [GDI+ on Mono](./GDIPlus-Mono-Tutorial.md) and [SkiaSharp](./SkiaSharp-Tutorial.md) tutorials in this folder to start drawing.
- **Official docs:** the [C# language guide](https://learn.microsoft.com/dotnet/csharp/) and the free [.NET / C# tutorials](https://dotnet.microsoft.com/learn/csharp).

### Quick Reference

```csharp
using System;                        // import the standard toolbox

class Program
{
    static void Main()               // program entry point
    {
        // Variables
        int n = 5;
        string s = "text";

        // Output & input
        Console.WriteLine($"n = {n}");
        string line = Console.ReadLine();

        // Decisions
        if (n > 0) { /* ... */ } else { /* ... */ }

        // Loops
        for (int i = 0; i < n; i++) { /* ... */ }
        foreach (var item in someList) { /* ... */ }

        // Call a method
        int total = Add(2, 3);
    }

    static int Add(int a, int b) => a + b;   // a compact method
}
```

Happy coding! 🚀

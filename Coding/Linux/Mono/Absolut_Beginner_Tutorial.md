---
id: 20260923150154
title: Absolute C# Beginner Tutorial
author: Karl Schmitt
date: 2026-09-23
keywords: [ C#, Mono, PowerShell, VSCode ]
---

![Leitfaden für den Programmier-Einstieg](./Images/Leitfaden_für_den_Programmier-Einstieg.png)

> [NOTE!]
> Dieses Tutorial bietet einen **fundierten Einstieg** in die Programmierung mit **C#** unter Verwendung der **Mono-Laufzeitumgebung**. Der Fokus liegt auf einem schlanken Setup für Anfänger, das lediglich **Visual Studio Code**, die **PowerShell** und den **Mono-Compiler** nutzt. Schritt für Schritt werden essenzielle Konzepte wie **Datentypen**, **Kontrollstrukturen**, **Objektorientierung** und **Listen** anhand praktischer Codebeispiele vermittelt. Ergänzend dazu stellt die Quelle einen **Lernpfad** sowie Übungsaufgaben bereit, um das Wissen über die Syntax und die Programmlogik zu festigen. Schließlich erleichtert ein Vergleich mit **Java** erfahrenen Entwicklern den Umstieg auf das Microsoft-Ökosystem.


# C# and Mono — Absolute Beginner Tutorial

This tutorial takes you from **zero C# knowledge** to writing, compiling, and running small C# applications using **Mono**.

We will deliberately keep the toolchain simple:

* 🪟 Windows 11

* 📝 Visual Studio Code

* 💻 PowerShell

* 🟦 C#

* ⚙️ Mono

* ❌ No Visual Studio required

* ❌ No ASP.NET yet

* ❌ No NuGet yet

***

# 1. What is C#?

**C#** (pronounced "C sharp") is a programming language developed by Microsoft.

A very small C# program looks like this:

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

When executed, it produces:

```text
Hello, World!
```

The important idea is:

```text
C# source code
      │
      ▼
   compiler
      │
      ▼
 executable program
      │
      ▼
    output
```

***

# 2. What is Mono?

**Mono** is an open-source implementation of the .NET platform.

Historically, the Microsoft .NET ecosystem was strongly associated with Windows. Mono provided a way to run C#/.NET applications on other platforms, particularly Linux.

Conceptually:

```text
              C# source code
                    │
                    ▼
             Mono C# compiler
                    │
                    ▼
              .NET/Mono code
                    │
                    ▼
                Mono runtime
                    │
                    ▼
              Your application
```

One important distinction:

> **C# is the programming language. Mono is a runtime/toolchain for the .NET ecosystem.**

So don't think of "Mono" as another programming language.

***

# 3. Your first C# project

Let's create a very simple project.

Open PowerShell:

```powershell
mkdir C:\CodingDojo\CSharpMono
cd C:\CodingDojo\CSharpMono
```

Create a source directory:

```powershell
mkdir src
cd src
```

Create the source file:

```powershell
code Program.cs
```

Put this into `Program.cs`:

```csharp
using System;

class Program
{
    static void Main()
    {
        Console.WriteLine("Hello from C#!");
    }
}
```

Save the file.

***

# 4. Understanding the program

Let's examine it line by line.

## `using System;`

```csharp
using System;
```

`System` is a namespace containing many fundamental .NET classes.

For example:

```csharp
Console
```

comes from the `System` namespace.

***

## `class Program`

```csharp
class Program
{
}
```

This defines a class called `Program`.

You can think of a class as a **blueprint for objects and behavior**.

For the moment, simply remember:

```text
class
  │
  └── defines a type
```

***

# 5. The `Main()` method

Inside the class we have:

```csharp
static void Main()
{
}
```

This is the entry point of our application.

In other words:

```text
Program starts
     │
     ▼
Main()
     │
     ▼
first instructions
```

You can compare it with C/C++:

```cpp
int main()
{
}
```

C#:

```csharp
static void Main()
{
}
```

***

# 6. Printing text

We use:

```csharp
Console.WriteLine("Hello from C#!");
```

`Console` represents the console.

`WriteLine()` prints text followed by a newline.

For example:

```csharp
Console.WriteLine("Hello");
Console.WriteLine("World");
```

produces:

```text
Hello
World
```

***

# 7. Compiling your first program

This is where Mono becomes interesting.

Depending on your Mono installation, you may have the C# compiler:

```powershell
mcs
```

Check whether it is available:

```powershell
mcs --version
```

If available, compile:

```powershell
mcs Program.cs
```

You should get something similar to:

```text
Program.cs
Program.exe
```

Check:

```powershell
dir
```

You may see:

```text
Program.cs
Program.exe
```

***

# 8. Running the program

With Mono, you can run the generated executable using:

```powershell
mono Program.exe
```

Output:

```text
Hello from C#!
```

Congratulations! 🎉

You have just completed the fundamental C# development cycle:

```text
       Program.cs
           │
           │ compile
           ▼
      Program.exe
           │
           │ mono
           ▼
     Hello from C#!
```

***

# 9. Variables

Now let's learn about variables.

Create:

```text
Variables.cs
```

with:

```csharp
using System;

class Variables
{
    static void Main()
    {
        string name = "Karl";
        int age = 42;

        Console.WriteLine(name);
        Console.WriteLine(age);
    }
}
```

Compile:

```powershell
mcs Variables.cs
```

Run:

```powershell
mono Variables.exe
```

You might see:

```text
Karl
42
```

***

# 10. C# fundamental data types

Some important types are:

| Type      | Example     |
| --------- | ----------- |
| `int`     | `42`        |
| `long`    | `123456789` |
| `double`  | `3.14159`   |
| `float`   | `3.14f`     |
| `decimal` | `19.99m`    |
| `bool`    | `true`      |
| `char`    | `'A'`       |
| `string`  | `"Hello"`   |

Example:

```csharp
int age = 42;

double temperature = 21.5;

bool learning = true;

char letter = 'A';

string name = "Karl";
```

***

# 11. Strings

Strings are extremely important in C#.

```csharp
string firstName = "Karl";
string lastName = "Schmitt";
```

You can combine them:

```csharp
string fullName = firstName + " " + lastName;

Console.WriteLine(fullName);
```

Output:

```text
Karl Schmitt
```

***

# 12. String interpolation

Modern C# provides a very convenient syntax:

```csharp
string name = "Karl";
int age = 42;

Console.WriteLine($"My name is {name}.");
Console.WriteLine($"I am {age} years old.");
```

Output:

```text
My name is Karl.
I am 42 years old.
```

The `$` means:

> This string can contain expressions inside `{ }`.

For example:

```csharp
Console.WriteLine($"10 + 20 = {10 + 20}");
```

Output:

```text
10 + 20 = 30
```

***

# 13. Arithmetic

C# supports the familiar arithmetic operators:

```csharp
int a = 10;
int b = 3;

Console.WriteLine(a + b);
Console.WriteLine(a - b);
Console.WriteLine(a * b);
Console.WriteLine(a / b);
Console.WriteLine(a % b);
```

The `%` operator is the **remainder operator**.

For example:

```text
10 % 3 = 1
```

because:

```text
10 / 3 = 3 remainder 1
```

***

# 14. Boolean values

A `bool` can contain:

```csharp
true
```

or:

```csharp
false
```

Example:

```csharp
bool isLearning = true;

Console.WriteLine(isLearning);
```

Output:

```text
True
```

Notice that C# displays it as `True`.

***

# 15. Comparisons

You can compare values:

```csharp
int age = 42;

Console.WriteLine(age > 18);
```

Output:

```text
True
```

Important operators:

```text
==    equal
!=    not equal
>     greater than
<     less than
>=    greater than or equal
<=    less than or equal
```

Example:

```csharp
int age = 42;

Console.WriteLine(age == 42);
Console.WriteLine(age != 30);
Console.WriteLine(age > 18);
```

***

# 16. `if`

Now we can make decisions.

```csharp
int age = 42;

if (age >= 18)
{
    Console.WriteLine("Adult");
}
```

The structure is:

```text
if (condition)
{
    statements
}
```

Example:

```csharp
int temperature = 30;

if (temperature > 25)
{
    Console.WriteLine("It's warm.");
}
```

***

# 17. `else`

```csharp
int temperature = 15;

if (temperature > 25)
{
    Console.WriteLine("It's warm.");
}
else
{
    Console.WriteLine("It's not very warm.");
}
```

***

# 18. Multiple conditions

You can use `else if`:

```csharp
int temperature = 20;

if (temperature > 30)
{
    Console.WriteLine("Hot");
}
else if (temperature > 20)
{
    Console.WriteLine("Warm");
}
else if (temperature > 10)
{
    Console.WriteLine("Cool");
}
else
{
    Console.WriteLine("Cold");
}
```

***

# 19. Logical operators

C# has:

```text
&&    AND
||    OR
!     NOT
```

Example:

```csharp
int age = 30;
bool hasTicket = true;

if (age >= 18 && hasTicket)
{
    Console.WriteLine("Welcome!");
}
```

Both conditions must be true.

***

# 20. Loops

Loops allow you to repeat instructions.

## `for`

```csharp
for (int i = 0; i < 5; i++)
{
    Console.WriteLine(i);
}
```

Output:

```text
0
1
2
3
4
```

The structure is:

```text
for (initialization; condition; increment)
```

***

# 21. `while`

Another possibility:

```csharp
int i = 0;

while (i < 5)
{
    Console.WriteLine(i);

    i++;
}
```

Again:

```text
0
1
2
3
4
```

***

# 22. Arrays

An array stores multiple values.

```csharp
string[] names =
{
    "Alice",
    "Bob",
    "Charlie"
};
```

You can access elements using an index:

```csharp
Console.WriteLine(names[0]);
```

Output:

```text
Alice
```

Remember:

> C# arrays start at index `0`.

Therefore:

```text
names[0] → Alice
names[1] → Bob
names[2] → Charlie
```

***

# 23. Looping through an array

You can use `foreach`:

```csharp
string[] names =
{
    "Alice",
    "Bob",
    "Charlie"
};

foreach (string name in names)
{
    Console.WriteLine(name);
}
```

Output:

```text
Alice
Bob
Charlie
```

This is one of the most useful C# constructs.

***

# 24. Methods

A method represents an operation.

```csharp
static void SayHello()
{
    Console.WriteLine("Hello!");
}
```

Then call it:

```csharp
SayHello();
```

Complete example:

```csharp
using System;

class Program
{
    static void Main()
    {
        SayHello();
        SayHello();
    }

    static void SayHello()
    {
        Console.WriteLine("Hello!");
    }
}
```

Output:

```text
Hello!
Hello!
```

***

# 25. Methods with parameters

Methods can receive information.

```csharp
static void SayHello(string name)
{
    Console.WriteLine($"Hello {name}!");
}
```

Call it:

```csharp
SayHello("Alice");
SayHello("Bob");
```

Output:

```text
Hello Alice!
Hello Bob!
```

***

# 26. Methods returning values

A method doesn't have to return `void`.

For example:

```csharp
static int Add(int a, int b)
{
    return a + b;
}
```

Then:

```csharp
int result = Add(10, 20);

Console.WriteLine(result);
```

Output:

```text
30
```

The important concept is:

```text
Add(10, 20)
     │
     ▼
    30
```

***

# 27. Classes and objects

Now we arrive at one of the most important C# concepts:

**Object-oriented programming.**

Create a class:

```csharp
class Person
{
    public string Name;
    public int Age;
}
```

Now create an object:

```csharp
Person person = new Person();

person.Name = "Karl";
person.Age = 42;
```

Then:

```csharp
Console.WriteLine(person.Name);
Console.WriteLine(person.Age);
```

***

# 28. Understanding `new`

This:

```csharp
Person person = new Person();
```

means approximately:

```text
Person
  │
  │ type
  ▼
person
  │
  │ references
  ▼
Person object
```

`new` creates an instance of the class.

***

# 29. Constructors

Classes can have constructors:

```csharp
class Person
{
    public string Name;
    public int Age;

    public Person(string name, int age)
    {
        Name = name;
        Age = age;
    }
}
```

Now:

```csharp
Person person = new Person("Karl", 42);
```

This is much cleaner.

***

# 30. Properties

Modern C# code frequently uses properties rather than public fields.

Instead of:

```csharp
public string Name;
```

you'll often see:

```csharp
public string Name { get; set; }
```

For example:

```csharp
class Person
{
    public string Name { get; set; }

    public int Age { get; set; }
}
```

Then:

```csharp
Person person = new Person();

person.Name = "Karl";
person.Age = 42;
```

***

# 31. A small complete program

Let's put several concepts together.

```csharp
using System;

class Person
{
    public string Name { get; set; }

    public int Age { get; set; }

    public Person(string name, int age)
    {
        Name = name;
        Age = age;
    }

    public void Introduce()
    {
        Console.WriteLine($"Hello! My name is {Name}.");
        Console.WriteLine($"I am {Age} years old.");
    }
}

class Program
{
    static void Main()
    {
        Person person = new Person("Karl", 42);

        person.Introduce();
    }
}
```

Compile:

```powershell
mcs Program.cs
```

Run:

```powershell
mono Program.exe
```

You now have a small object-oriented C# application.

***

# 32. Reading input

Let's make our program interactive.

```csharp
using System;

class Program
{
    static void Main()
    {
        Console.Write("What is your name? ");

        string name = Console.ReadLine();

        Console.WriteLine($"Hello {name}!");
    }
}
```

Run:

```powershell
mcs Program.cs
mono Program.exe
```

Example:

```text
What is your name? Karl
Hello Karl!
```

***

# 33. Converting strings to numbers

`Console.ReadLine()` returns a string.

Suppose the user enters:

```text
42
```

You can convert it:

```csharp
string input = Console.ReadLine();

int number = int.Parse(input);

Console.WriteLine(number + 10);
```

Input:

```text
42
```

Output:

```text
52
```

Later you should learn `TryParse`, which is safer for user input:

```csharp
if (int.TryParse(input, out int number))
{
    Console.WriteLine(number + 10);
}
else
{
    Console.WriteLine("That wasn't a number.");
}
```

***

# 34. Exceptions

Sometimes something goes wrong.

For example:

```csharp
int number = int.Parse("Hello");
```

This causes an exception.

You can handle exceptions using:

```csharp
try
{
    int number = int.Parse("Hello");
}
catch
{
    Console.WriteLine("Something went wrong.");
}
```

More specifically:

```csharp
try
{
    int number = int.Parse("Hello");
}
catch (FormatException)
{
    Console.WriteLine("The input wasn't a valid number.");
}
```

***

# 35. C# collections

Arrays are useful, but C# provides many collection types.

One of the most important is:

```csharp
List<T>
```

Example:

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
        names.Add("Charlie");

        foreach (string name in names)
        {
            Console.WriteLine(name);
        }
    }
}
```

This introduces another important concept:

```text
List<string>
     │
     └── generic collection
```

***

# 36. Generics

You will encounter generics everywhere in modern C#.

For example:

```csharp
List<string>
```

means:

> A list containing strings.

And:

```csharp
List<int>
```

means:

> A list containing integers.

Example:

```csharp
List<int> numbers = new List<int>();

numbers.Add(10);
numbers.Add(20);
numbers.Add(30);
```

***

# 37. LINQ

Later you will encounter one of C#'s most powerful features:

**LINQ — Language Integrated Query.**

For example:

```csharp
List<int> numbers = new List<int>
{
    1, 2, 3, 4, 5, 6
};

var evenNumbers = numbers.Where(n => n % 2 == 0);

foreach (int number in evenNumbers)
{
    Console.WriteLine(number);
}
```

Output:

```text
2
4
6
```

Don't worry if this looks strange now.

For an absolute beginner, the important progression is:

```text
variables
   ↓
conditions
   ↓
loops
   ↓
methods
   ↓
classes
   ↓
objects
   ↓
collections
   ↓
generics
   ↓
LINQ
```

***

# 38. C# learning roadmap

I would recommend learning C# in this order:

```text
┌──────────────────────────────┐
│ 1. C# syntax                 │
├──────────────────────────────┤
│ 2. Variables & data types    │
├──────────────────────────────┤
│ 3. Operators                 │
├──────────────────────────────┤
│ 4. if / else                 │
├──────────────────────────────┤
│ 5. Loops                     │
├──────────────────────────────┤
│ 6. Arrays                    │
├──────────────────────────────┤
│ 7. Methods                   │
├──────────────────────────────┤
│ 8. Classes & objects         │
├──────────────────────────────┤
│ 9. Constructors              │
├──────────────────────────────┤
│ 10. Properties               │
├──────────────────────────────┤
│ 11. Inheritance              │
├──────────────────────────────┤
│ 12. Interfaces               │
├──────────────────────────────┤
│ 13. Exceptions               │
├──────────────────────────────┤
│ 14. Collections              │
├──────────────────────────────┤
│ 15. Generics                 │
├──────────────────────────────┤
│ 16. LINQ                     │
├──────────────────────────────┤
│ 17. Delegates & events       │
├──────────────────────────────┤
│ 18. Lambda expressions       │
├──────────────────────────────┤
│ 19. async / await            │
├──────────────────────────────┤
│ 20. .NET applications        │
└──────────────────────────────┘
```

***

# 39. C# compared with Java

Because you're already working with Java/Spring Boot, you'll find C# surprisingly familiar.

For example, Java:

```java
public class Person {

    private String name;

    public Person(String name) {
        this.name = name;
    }
}
```

C#:

```csharp
public class Person
{
    public string Name { get; set; }

    public Person(string name)
    {
        Name = name;
    }
}
```

The conceptual structure is very similar.

You will recognize:

```text
Java                    C#
────────────────────────────────
class                   class
interface               interface
extends                 :
implements              :
private                 private
public                  public
static                  static
void                    void
int                     int
boolean                 bool
String                  string
List<T>                 List<T>
try/catch               try/catch
```

This means your Java background should make the **C# language itself** considerably easier to learn.

***

# 40. Your first C# exercises

I recommend **not just reading** the tutorial.

Create a directory:

```powershell
mkdir exercises
cd exercises
```

Then work through these.

### Exercise 1 — Hello

Write:

```text
Hello, my name is Karl.
```

***

### Exercise 2 — Variables

Create:

```text
name
age
city
```

and print them.

***

### Exercise 3 — Calculator

Ask the user for two numbers:

```text
First number: 10
Second number: 20

Result: 30
```

***

### Exercise 4 — Even or odd

Ask for a number:

```text
Number: 7

7 is odd.
```

Hint:

```csharp
number % 2
```

***

### Exercise 5 — Counting

Print:

```text
1
2
3
4
5
6
7
8
9
10
```

using a `for` loop.

***

### Exercise 6 — Guessing game

The program contains:

```csharp
int secret = 42;
```

The user guesses the number.

Output:

```text
Guess: 30
Too low!

Guess: 50
Too high!

Guess: 42
Correct!
```

***

### Exercise 7 — Person

Create:

```csharp
class Person
```

with:

```text
Name
Age
```

and a method:

```csharp
Introduce()
```

***

### Exercise 8 — Todo list

Create a:

```csharp
List<string>
```

and allow the user to enter several todo items.

Example:

```text
1. Learn C#
2. Learn Mono
3. Build a small application
```

This is your first little C# application.

***

# 41. A very useful mental model

Since you're learning several programming languages, I recommend separating **language**, **compiler**, **runtime**, and **framework** in your Zettelkasten.

For C#:

```text
                 C#
              programming
                language
                   │
                   ▼
              C# compiler
                   │
                   ▼
              .NET assembly
                   │
                   ▼
            .NET / Mono runtime
                   │
                   ▼
             application
```

This distinction becomes extremely useful when you later encounter:

```text
C#
.NET
.NET SDK
.NET Runtime
Mono
Roslyn
NuGet
ASP.NET Core
```

They are related, but they are **not the same thing**.

***

# 42. Your next step: a C# Mono Bootcamp

After this introductory tutorial, I'd suggest a hands-on bootcamp structured like this:

| Week   | Topic                  | Project                      |
| ------ | ---------------------- | ---------------------------- |
| **1**  | C# fundamentals        | Console programs             |
| **2**  | Conditions & loops     | Number guessing game         |
| **3**  | Methods                | Calculator                   |
| **4**  | Classes & objects      | Person manager               |
| **5**  | Collections & generics | Todo application             |
| **6**  | Exceptions & files     | Text-file manager            |
| **7**  | LINQ & lambdas         | Data analysis tool           |
| **8**  | OOP deeper             | Library management system    |
| **9**  | async/await            | HTTP client                  |
| **10** | Final project          | Complete console application |

And because you're using **PowerShell + VS Code**, we can make the whole thing very hands-on:

```text
PowerShell
    │
    ├── create files
    ├── compile C#
    ├── run programs
    ├── inspect directories
    └── automate builds
             │
             ▼
        Visual Studio Code
             │
             ▼
          C# source
             │
             ▼
            Mono
```

One important modern note: **Mono and Microsoft's current .NET platform are not interchangeable terms.** If your goal is specifically to learn an existing project that uses Mono, this tutorial is appropriate. If you're starting a new C# application today, it is also worth learning the modern **.NET SDK (`dotnet`)** alongside or instead of Mono, because that is the mainstream Microsoft .NET toolchain.

If you'd like, I can next turn this into a **“C# + Mono Absolute Beginner Bootcamp” with 30 days of daily exercises and a final project**, in the same style as your Java, CMake, Docker, and Kubernetes bootcamps.

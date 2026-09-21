---
id: 20260921172342
title: C++ Absolute Beginner Tutorial
author: Karl Schmitt
date: 2026-09-21
---

# C++ Absolute Beginner Tutorial

Absolutely. Since you're working on Windows 11 with **g++ + PowerShell + Visual Studio Code**, I'll make this a completely hands-on **C++ + CMake Absolute Beginner Tutorial**.

The important idea is that we will learn **C++ and CMake together**, but we won't let CMake hide what is actually happening.

## 🚀 C++ and CMake for Absolute Beginner

### 1. What are we going to learn?

By the end, you will understand this complete chain:

```text
C++ source code
      │
      ▼
   g++ compiler
      │
      ▼
 executable program
```

and then:

```text
C++ source code
      │
      ▼
    CMake
      │
      ▼
 build system
      │
      ▼
   g++ compiler
      │
      ▼
 executable program
```

We'll start with tiny programs and gradually build a small C++ application.

***

# 2. What is C++?

C++ is a programming language.

For example:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
```

This program prints:

```text
Hello, World!
```

The source code is normally stored in:

```text
main.cpp
```

The `.cpp` extension means:

> This is a C++ source file.

***

# 3. What is a compiler?

Your computer cannot directly execute:

```cpp
std::cout << "Hello, World!";
```

A compiler translates C++ source code into machine code.

For this tutorial we'll use:

```text
g++
```

Conceptually:

```text
main.cpp
   │
   │ g++
   ▼
program.exe
```

You can check whether `g++` is available:

```powershell
g++ --version
```

You should see something similar to:

```text
g++ (MinGW ...)
Copyright ...
```

***

# 4. Your first C++ program

Create a directory:

```powershell
mkdir CppCMakeTutorial
cd CppCMakeTutorial
```

Create the source file:

```powershell
code main.cpp
```

Put this into `main.cpp`:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello from C++!" << std::endl;

    return 0;
}
```

***

# 5. Compile it manually

Before introducing CMake, let's understand what the compiler actually does.

Run:

```powershell
g++ main.cpp -o hello.exe
```

Now list the directory:

```powershell
dir
```

You should have:

```text
main.cpp
hello.exe
```

Run it:

```powershell
.\hello.exe
```

Output:

```text
Hello from C++!
```

Congratulations! 🎉

You've just compiled and executed a C++ program.

***

# 6. Understanding `main()`

This:

```cpp
int main()
{
    ...
}
```

is the entry point of your program.

Think of it as:

```text
Operating System
       │
       ▼
    main()
       │
       ▼
   your program
```

The operating system starts your program by calling `main()`.

***

# 7. Understanding `std::cout`

This:

```cpp
std::cout
```

means:

> Write something to the console.

For example:

```cpp
std::cout << "Hello";
```

You can write several things:

```cpp
std::cout << "Hello ";
std::cout << "Karl";
```

Output:

```text
Hello Karl
```

Or:

```cpp
std::cout << "Hello " << "Karl" << std::endl;
```

***

# 8. What does `#include <iostream>` mean?

This:

```cpp
#include <iostream>
```

tells the compiler:

> I want to use functionality provided by the C++ input/output library.

That's why we can use:

```cpp
std::cout
```

***

# 9. Variables

Let's create a variable:

```cpp
#include <iostream>

int main()
{
    int age = 42;

    std::cout << age << std::endl;

    return 0;
}
```

Output:

```text
42
```

The important part is:

```cpp
int age = 42;
```

It means:

```text
type       variable      value
 │             │           │
 ▼             ▼           ▼
int           age         42
```

***

# 10. More C++ types

Some basic types:

```cpp
int age = 42;

double temperature = 21.5;

char letter = 'A';

bool running = true;
```

And strings:

```cpp
#include <string>

std::string name = "Karl";
```

A simple program:

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name = "Karl";
    int age = 42;

    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;

    return 0;
}
```

***

# 11. Your first function

Functions allow us to organize our program.

```cpp
#include <iostream>

void sayHello()
{
    std::cout << "Hello!" << std::endl;
}

int main()
{
    sayHello();

    return 0;
}
```

The flow is:

```text
main()
  │
  ▼
sayHello()
  │
  ▼
Hello!
```

***

# 12. Functions with parameters

```cpp
#include <iostream>

void greet(std::string name)
{
    std::cout << "Hello " << name << "!" << std::endl;
}

int main()
{
    greet("Karl");
    greet("Alice");

    return 0;
}
```

Output:

```text
Hello Karl!
Hello Alice!
```

***

# 13. `if`

C++ supports conditional execution:

```cpp
#include <iostream>

int main()
{
    int age = 20;

    if (age >= 18)
    {
        std::cout << "Adult" << std::endl;
    }

    return 0;
}
```

***

# 14. Loops

A `for` loop:

```cpp
#include <iostream>

int main()
{
    for (int i = 1; i <= 5; i++)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
```

Output:

```text
1
2
3
4
5
```

***

# 15. Now: What is CMake?

This is the important part.

You could compile a tiny application with:

```powershell
g++ main.cpp -o hello.exe
```

But real applications become much more complicated.

Imagine:

```text
main.cpp
Person.cpp
Person.h
Calculator.cpp
Calculator.h
Database.cpp
Database.h
...
```

You might eventually need:

```text
g++
compiler options
include directories
libraries
linker options
debug settings
release settings
...
```

Managing this manually becomes unpleasant.

That's where **CMake** comes in.

Think of CMake as a **build-system generator/configuration tool**.

***

# 16. The basic CMake idea

Instead of telling `g++` everything manually:

```text
g++ ...
```

you tell CMake:

```text
Here is my project.

Here is my source code.

Please create a build configuration for it.
```

CMake then generates the files needed to build your project.

Conceptually:

```text
              CMakeLists.txt
                    │
                    ▼
                  CMake
                    │
                    ▼
             Build configuration
                    │
                    ▼
                  g++
                    │
                    ▼
               program.exe
```

***

# 17. Check CMake

In PowerShell:

```powershell
cmake --version
```

You should see something like:

```text
cmake version 4.x.x
```

***

# 18. Create your first CMake project

Let's create:

```text
hello-cmake
│
├── CMakeLists.txt
└── src
    └── main.cpp
```

Create the directories:

```powershell
mkdir hello-cmake
cd hello-cmake

mkdir src
```

Create:

```powershell
code src\main.cpp
```

Put:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello from CMake!" << std::endl;

    return 0;
}
```

***

# 19. Create `CMakeLists.txt`

Now create:

```powershell
code CMakeLists.txt
```

Put this inside:

```cmake
cmake_minimum_required(VERSION 3.20)

project(HelloCMake)

add_executable(hello
    src/main.cpp
)
```

This tiny file is the heart of our CMake project.

***

# 20. Understanding `cmake_minimum_required`

This:

```cmake
cmake_minimum_required(VERSION 3.20)
```

means:

> This project requires at least CMake 3.20.

It prevents CMake from trying to process the project with an unsupported older version.

***

# 21. Understanding `project()`

This:

```cmake
project(HelloCMake)
```

defines the project name.

So:

```text
project name = HelloCMake
```

***

# 22. Understanding `add_executable()`

This is probably the most important CMake command for beginners:

```cmake
add_executable(hello
    src/main.cpp
)
```

It tells CMake:

> Create an executable called `hello` using `src/main.cpp`.

Visualized:

```text
src/main.cpp
     │
     │
     ▼
add_executable()
     │
     ▼
   hello.exe
```

***

# 23. The build directory

A very useful CMake convention is:

> Don't put generated build files into your source directory.

Instead:

```text
hello-cmake
│
├── CMakeLists.txt
├── src
│   └── main.cpp
│
└── build
```

Create it:

```powershell
mkdir build
```

***

# 24. Configure the project

From the project directory:

```powershell
cmake -S . -B build
```

Let's understand this:

```text
cmake
  │
  ├── -S .
  │      │
  │      └── source directory
  │
  └── -B build
         │
         └── build directory
```

In other words:

```text
Source:
.

Build:
build
```

CMake reads:

```text
CMakeLists.txt
```

and creates the build configuration inside:

```text
build\
```

***

# 25. Build the application

Now:

```powershell
cmake --build build
```

CMake invokes the configured compiler/build system.

Eventually you'll get an executable.

Depending on your generator, its exact location can differ.

You can search for it:

```powershell
Get-ChildItem -Path build -Recurse -Filter "*.exe"
```

***

# 26. Run the program

For example, you might find:

```text
build\hello.exe
```

Then:

```powershell
.\build\hello.exe
```

Or, with a multi-configuration generator, the executable might be under something like:

```text
build\Debug\hello.exe
```

Then:

```powershell
.\build\Debug\hello.exe
```

You should see:

```text
Hello from CMake!
```

🎉

You have now created your first CMake-managed C++ application.

***

# 27. The CMake workflow

This workflow is extremely important:

```text
             CMakeLists.txt
                    │
                    ▼
          cmake -S . -B build
                    │
                    ▼
             configuration
                    │
                    ▼
          cmake --build build
                    │
                    ▼
                compiler
                    │
                    ▼
               executable
```

Usually:

```powershell
cmake -S . -B build
cmake --build build
```

***

# 28. Why separate `build` from `src`?

Consider:

```text
hello-cmake
│
├── CMakeLists.txt
├── src
│   └── main.cpp
└── build
```

The source code is:

```text
src/
```

The generated build artifacts are:

```text
build/
```

This separation is very useful.

You can delete the entire build directory:

```powershell
Remove-Item build -Recurse -Force
```

and your source code remains untouched.

Then simply rebuild:

```powershell
cmake -S . -B build
cmake --build build
```

***

# 29. Add a second C++ file

Now let's make the project more realistic.

Change the structure to:

```text
hello-cmake
│
├── CMakeLists.txt
│
├── src
│   ├── main.cpp
│   ├── greeting.cpp
│   └── greeting.h
│
└── build
```

***

# 30. `greeting.h`

Create:

```cpp
#ifndef GREETING_H
#define GREETING_H

#include <string>

std::string createGreeting(const std::string& name);

#endif
```

This is a **header file**.

It tells other C++ files:

> There is a function called `createGreeting`.

***

# 31. `greeting.cpp`

Create:

```cpp
#include "greeting.h"

std::string createGreeting(const std::string& name)
{
    return "Hello " + name + "!";
}
```

This contains the implementation.

***

# 32. `main.cpp`

Now:

```cpp
#include <iostream>

#include "greeting.h"

int main()
{
    std::string message = createGreeting("Karl");

    std::cout << message << std::endl;

    return 0;
}
```

***

# 33. Update CMake

Our `CMakeLists.txt` becomes:

```cmake
cmake_minimum_required(VERSION 3.20)

project(HelloCMake)

add_executable(hello
    src/main.cpp
    src/greeting.cpp
)
```

Notice something important:

```text
greeting.h
```

doesn't need to appear in `add_executable()` for this simple case.

The compiler discovers it through:

```cpp
#include "greeting.h"
```

***

# 34. Reconfigure and rebuild

Run:

```powershell
cmake -S . -B build
```

Then:

```powershell
cmake --build build
```

Run your program.

You should get:

```text
Hello Karl!
```

***

# 35. C++ compilation model

At this point it's useful to understand this picture:

```text
             main.cpp
                │
                │ #include
                ▼
           greeting.h
                │
                │
             greeting.cpp
                │
                ▼
             compiler
                │
                ▼
          object files
                │
                ▼
              linker
                │
                ▼
            hello.exe
```

This distinction between:

* compiler

* linker

* executable

becomes very important as your C++ knowledge grows.

***

# 36. CMake targets

One of the most important CMake concepts is the **target**.

When you write:

```cmake
add_executable(hello
    src/main.cpp
    src/greeting.cpp
)
```

you create a target:

```text
hello
```

Think:

```text
CMake project
     │
     └── target: hello
             │
             ├── main.cpp
             └── greeting.cpp
```

Later you'll encounter:

```cmake
add_library(...)
```

which creates library targets.

***

# 37. Debug and Release builds

Real applications normally have different configurations.

For example:

```text
Debug
Release
```

A Debug build is useful while developing.

A Release build is optimized for distribution.

With a single-configuration generator you might use:

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

and:

```powershell
cmake --build build
```

For Release:

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

The exact workflow depends on the CMake generator you're using.

***

# 38. A more modern CMake example

Eventually you'll want to specify the C++ standard.

For example:

```cmake
cmake_minimum_required(VERSION 3.20)

project(HelloCMake)

add_executable(hello
    src/main.cpp
    src/greeting.cpp
)

target_compile_features(hello PRIVATE cxx_std_17)
```

This tells CMake:

> The `hello` target requires C++17.

You could also use C++20:

```cmake
target_compile_features(hello PRIVATE cxx_std_20)
```

or C++23:

```cmake
target_compile_features(hello PRIVATE cxx_std_23)
```

***

# 39. A small practical project

Let's turn everything we've learned into a little calculator.

Structure:

```text
calculator
│
├── CMakeLists.txt
│
├── src
│   ├── main.cpp
│   ├── calculator.cpp
│   └── calculator.h
│
└── build
```

`calculator.h`:

```cpp
#ifndef CALCULATOR_H
#define CALCULATOR_H

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

#endif
```

`calculator.cpp`:

```cpp
#include "calculator.h"

double add(double a, double b)
{
    return a + b;
}

double subtract(double a, double b)
{
    return a - b;
}

double multiply(double a, double b)
{
    return a * b;
}

double divide(double a, double b)
{
    return a / b;
}
```

`main.cpp`:

```cpp
#include <iostream>

#include "calculator.h"

int main()
{
    double a = 10;
    double b = 5;

    std::cout << "Add:      " << add(a, b) << std::endl;
    std::cout << "Subtract: " << subtract(a, b) << std::endl;
    std::cout << "Multiply: " << multiply(a, b) << std::endl;
    std::cout << "Divide:   " << divide(a, b) << std::endl;

    return 0;
}
```

And:

```cmake
cmake_minimum_required(VERSION 3.20)

project(Calculator)

add_executable(calculator
    src/main.cpp
    src/calculator.cpp
)

target_compile_features(calculator PRIVATE cxx_std_17)
```

Build:

```powershell
cmake -S . -B build
cmake --build build
```

Run the resulting executable.

***

# 40. Your C++ + CMake learning roadmap

I recommend learning the subjects in this order:

### 🟢 Phase 1 — C++ fundamentals

```text
1. Hello World
2. Variables
3. Data types
4. Operators
5. if / else
6. for loops
7. while loops
8. Functions
9. Strings
10. Arrays
```

### 🟢 Phase 2 — C++ core

```text
11. References
12. Pointers
13. const
14. Structs
15. Classes
16. Constructors
17. Destructors
18. Encapsulation
19. Inheritance
20. Polymorphism
```

### 🟢 Phase 3 — Modern C++

```text
21. std::vector
22. std::string
23. std::array
24. auto
25. range-based for
26. nullptr
27. smart pointers
28. lambdas
29. enum class
30. std::optional
```

### 🟢 Phase 4 — CMake

```text
31. CMakeLists.txt
32. project()
33. add_executable()
34. add_library()
35. targets
36. target_sources()
37. target_include_directories()
38. target_link_libraries()
39. compile features
40. Debug / Release
```

### 🟢 Phase 5 — Real projects

```text
41. Multiple libraries
42. Unit testing
43. External dependencies
44. CMake FetchContent
45. Installation
46. Packaging
47. CMake presets
48. Cross-platform builds
49. CI/CD
50. Larger C++ architecture
```

***

# 41. The most important mental model

Coming from Java/Spring Boot, this analogy may help:

| Java         | C++                  |
| ------------ | -------------------- |
| `.java`      | `.cpp`               |
| `javac`      | `g++`                |
| JVM bytecode | native machine code  |
| `main()`     | `main()`             |
| Maven/Gradle | CMake + build system |
| `pom.xml`    | `CMakeLists.txt`     |
| dependency   | library              |
| JAR          | executable/library   |
| package      | namespace            |
| class        | class                |

There is one important difference:

**CMake is not exactly the C++ equivalent of Maven or Gradle.**

CMake primarily describes/configures the build, then generates files for a build tool such as Make, Ninja, or Visual Studio.

So the more accurate picture is:

```text
             CMakeLists.txt
                    │
                    ▼
                  CMake
                    │
          ┌─────────┼─────────┐
          ▼         ▼         ▼
        Ninja      Make    Visual Studio
          │         │         │
          └─────────┼─────────┘
                    ▼
                  g++
                    │
                    ▼
              application.exe
```

That distinction is **very important** when learning CMake.

***

# 42. Your first CMake cheat sheet

### Configure

```powershell
cmake -S . -B build
```

### Build

```powershell
cmake --build build
```

### Clean build

```powershell
Remove-Item build -Recurse -Force

cmake -S . -B build
cmake --build build
```

### Check CMake

```powershell
cmake --version
```

### Check compiler

```powershell
g++ --version
```

### Run executable

```powershell
.\build\hello.exe
```

***

# 🎯 First milestone

If you want to learn this properly rather than simply copy CMake commands, I recommend making your first milestone:

```text
C++ + CMake
     │
     ├── main.cpp
     │
     ├── greeting.h
     │
     ├── greeting.cpp
     │
     └── CMakeLists.txt
```

and being able to explain **every line** in these files.

Once that makes sense, the next natural step is a **C++ + CMake Absolute Beginner Bootcamp**, where we build a small project over several exercises: variables → functions → classes → multiple `.cpp` files → libraries → tests → Debug/Release → CMake targets → a final project.

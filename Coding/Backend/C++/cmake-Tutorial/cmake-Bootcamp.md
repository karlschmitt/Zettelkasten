---
id: 20260909125349
title: CMake Bootcamp — Beginner to Practical
author: Karl Schmitt
date: 2026-09-09
keywords: [ Powershell, C++, g++, cmake, ctest]
---

![C++-Build-System Grundlagen und Praxis](../Images/C++-Build-System_Grundlagen_und_Praxis.png)

> [NOTE!]
> Dieser Text bietet einen **praxisorientierten Leitfaden** für den Einstieg in **CMake** unter Windows 11 mit PowerShell und dem g++ Compiler. Der Autor erläutert den Übergang von manuellen Kompilierbefehlen hin zu einem **zielorientierten Build-System**, das komplexe Projekte effizient verwaltet. Wichtige Konzepte wie die Erstellung von **Executables und Bibliotheken**, das Linken von Abhängigkeiten sowie die Nutzung von **Voreinstellungen** werden Schritt für Schritt erklärt. Zudem wird die Integration von automatisierten Tests mittels **CTest** und eine saubere Projektstrukturierung thematisiert. Das Ziel ist es, Entwicklern ein fundiertes **mentales Modell** für moderne C++-Entwicklungsprozesse zu vermitteln. Ein strukturierter Lernplan rundet die Einführung ab, um den Weg vom Anfänger zum Fortgeschrittenen zu ebnen.


Absolutely. Since you're using **g++ + PowerShell on Windows 11**, let's make this a genuinely hands-on CMake course rather than a generic CMake overview.

We'll start with a tiny C++ program and gradually turn it into a small, properly structured project with libraries, tests, dependencies, Debug/Release builds, and CMake presets.

# CMake Bootcamp — Beginner to Practical

### Windows 11 + g++ + PowerShell

## What you'll build

By the end, we'll have something like:

```text
cmake-demo/
│
├── CMakeLists.txt
├── CMakePresets.json
│
├── src/
│   ├── main.cpp
│   ├── Calculator.cpp
│   └── Calculator.h
│
├── tests/
│   └── CalculatorTest.cpp
│
└── build/
    ├── debug/
    └── release/
```

And you'll understand the complete flow:

```text
                    CMakeLists.txt
                          │
                          ▼
                   CMake configure
                          │
                          ▼
                    Build system
                          │
                          ▼
                        g++
                          │
                          ▼
                 .exe / libraries
                          │
                          ▼
                       ctest
```

***

# Part 1 — Understand Your Toolchain

Before CMake, it's important to understand what you're actually using.

You have:

```text
PowerShell
    │
    ├── cmake
    │
    └── g++
```

They have different jobs.

### PowerShell

Your shell:

```powershell
PS C:\Projects>
```

You use it to execute commands.

### g++

Your compiler:

```powershell
g++ main.cpp -o hello.exe
```

It translates C++ source code into machine code.

### CMake

CMake describes **how your project should be built**.

```text
CMakeLists.txt
       │
       ▼
     CMake
       │
       ▼
 build system
       │
       ▼
      g++
```

This distinction is fundamental.

***

# Part 2 — Check Your Installation

Open PowerShell.

## Check g++

```powershell
g++ --version
```

You should get something similar to:

```text
g++ (GCC) ...
Copyright ...
```

Now:

```powershell
cmake --version
```

You should get:

```text
cmake version ...
```

And:

```powershell
ctest --version
```

You should also get a version.

Your basic toolchain is therefore:

```text
g++
CMake
CTest
PowerShell
```

***

# Part 3 — Compile C++ Without CMake

Before learning CMake, let's see what happens without it.

Create:

```text
hello-cmake/
└── main.cpp
```

`main.cpp`:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello CMake!" << std::endl;
    return 0;
}
```

Compile it directly:

```powershell
g++ main.cpp -o hello.exe
```

Then:

```powershell
.\hello.exe
```

Output:

```text
Hello CMake!
```

So why do we need CMake?

Imagine having:

```text
20 source files
5 libraries
3 external dependencies
100 compiler options
Debug configuration
Release configuration
unit tests
installation
Windows
Linux
macOS
```

A command such as:

```powershell
g++ main.cpp ...
```

quickly becomes unmanageable.

That's where CMake comes in.

***

# Part 4 — Your First CMake Project

Our project becomes:

```text
hello-cmake/
│
├── CMakeLists.txt
└── main.cpp
```

Create `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.20)

project(HelloCMake LANGUAGES CXX)

add_executable(hello main.cpp)
```

There are three important statements here.

***

## `cmake_minimum_required`

```cmake
cmake_minimum_required(VERSION 3.20)
```

This tells CMake which minimum version your project expects.

***

## `project`

```cmake
project(HelloCMake LANGUAGES CXX)
```

This defines the project.

`CXX` means C++.

***

## `add_executable`

```cmake
add_executable(hello main.cpp)
```

This creates a **target** named:

```text
hello
```

The target is an executable.

You can visualize it like this:

```text
main.cpp
   │
   ▼
 hello target
   │
   ▼
hello.exe
```

***

# Part 5 — Configure

Now comes one of the most important CMake concepts.

Don't do:

```powershell
cmake .
```

as your normal workflow.

Instead use an **out-of-source build**:

```powershell
cmake -S . -B build
```

Meaning:

```text
-S .
```

Source directory:

```text
.
```

and:

```text
-B build
```

Build directory:

```text
build/
```

So:

```text
hello-cmake/
│
├── CMakeLists.txt
├── main.cpp
│
└── build/
```

CMake generates its build files inside `build`.

***

# Part 6 — Build

Now:

```powershell
cmake --build build
```

CMake invokes the underlying build system, which invokes `g++`.

Conceptually:

```text
CMake
  │
  ▼
build system
  │
  ▼
g++
  │
  ▼
hello.exe
```

Find the executable:

```powershell
Get-ChildItem build -Recurse -Filter hello.exe
```

Then execute it.

Depending on your generator/configuration, it may be:

```powershell
.\build\Debug\hello.exe
```

or another location.

***

# Part 7 — The Two CMake Commands to Memorize

For now, remember these:

```powershell
cmake -S . -B build
```

and:

```powershell
cmake --build build
```

They mean:

```text
CONFIGURE
   ↓
cmake -S . -B build
   ↓
BUILD
   ↓
cmake --build build
```

This is probably the single most important CMake workflow to learn.

***

# Part 8 — CMake Targets

Now we get to the **heart of modern CMake**.

Instead of thinking:

> "Which compiler command do I need?"

think:

> "What targets does my project contain?"

For example:

```cmake
add_executable(myapp main.cpp)
```

creates:

```text
myapp
```

A library:

```cmake
add_library(calculator Calculator.cpp)
```

creates:

```text
calculator
```

So a project might look like:

```text
              CMake project
                    │
          ┌─────────┴─────────┐
          ▼                   ▼
     calculator              myapp
       library             executable
```

This target-based way of thinking is extremely important.

***

# Part 9 — Create a Library

Let's expand the application.

Our project:

```text
cmake-demo/
│
├── CMakeLists.txt
│
└── src/
    ├── main.cpp
    ├── Calculator.cpp
    └── Calculator.h
```

`Calculator.h`:

```cpp
#pragma once

class Calculator {
public:
    int add(int a, int b);
    int subtract(int a, int b);
};
```

`Calculator.cpp`:

```cpp
#include "Calculator.h"

int Calculator::add(int a, int b) {
    return a + b;
}

int Calculator::subtract(int a, int b) {
    return a - b;
}
```

`main.cpp`:

```cpp
#include <iostream>
#include "Calculator.h"

int main() {

    Calculator calculator;

    std::cout << calculator.add(10, 5) << std::endl;
    std::cout << calculator.subtract(10, 5) << std::endl;

    return 0;
}
```

***

# Part 10 — CMake the Library

Our first version:

```cmake
cmake_minimum_required(VERSION 3.20)

project(CMakeDemo LANGUAGES CXX)

add_library(calculator
    src/Calculator.cpp
)

add_executable(myapp
    src/main.cpp
)

target_include_directories(calculator
    PUBLIC
    src
)

target_link_libraries(myapp
    PRIVATE
    calculator
)
```

Now our dependency graph is:

```text
Calculator.cpp
      │
      ▼
 calculator
   library
      │
      │ PRIVATE
      ▼
    myapp
 executable
      │
      ▼
   main.cpp
```

***

# Part 11 — What Does `target_link_libraries()` Mean?

This line:

```cmake
target_link_libraries(myapp PRIVATE calculator)
```

means:

> `myapp` depends on the `calculator` target.

So CMake understands:

```text
myapp
  │
  └──── depends on ────> calculator
```

This is much better than manually specifying:

```text
calculator.lib
```

or:

```text
-lcalculator
```

CMake knows how to handle the appropriate platform.

***

# Part 12 — `PRIVATE`, `PUBLIC`, `INTERFACE`

You'll see these everywhere.

For example:

```cmake
target_link_libraries(
    myapp
    PRIVATE
    calculator
)
```

### PRIVATE

The dependency belongs to this target.

```text
myapp ─────> calculator
```

Consumers of `myapp` don't inherit it.

***

### PUBLIC

The target needs the dependency, and consumers need it too.

```text
myapp
 │
 └──> calculator
       ▲
       │
    consumer
```

***

### INTERFACE

The target itself doesn't need the dependency for compilation, but consumers do.

This is particularly common with header-only libraries.

***

# Part 13 — Include Directories

This:

```cmake
target_include_directories(
    calculator
    PUBLIC
    src
)
```

tells CMake that headers can be found in:

```text
src/
```

Therefore:

```cpp
#include "Calculator.h"
```

works.

The important lesson is:

> Prefer `target_include_directories()` over global include-directory commands.

Modern CMake is **target oriented**.

***

# Part 14 — C++ Standard

Suppose we want C++20.

A modern target-based approach is:

```cmake
target_compile_features(
    myapp
    PRIVATE
    cxx_std_20
)
```

For example:

```cmake
add_executable(myapp src/main.cpp)

target_compile_features(
    myapp
    PRIVATE
    cxx_std_20
)
```

You can also specify the standard for a library:

```cmake
target_compile_features(
    calculator
    PUBLIC
    cxx_std_20
)
```

***

# Part 15 — Compiler Warnings

For GCC:

```cmake
target_compile_options(
    myapp
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
```

You can do the same for the library:

```cmake
target_compile_options(
    calculator
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
```

Now `g++` receives warning options.

Conceptually:

```text
CMake
  │
  ▼
target_compile_options()
  │
  ▼
g++
  │
  ├── -Wall
  ├── -Wextra
  └── -Wpedantic
```

***

# Part 16 — Debug and Release

A professional project normally has at least:

```text
Debug
Release
```

Debug is for development:

```text
Debug
 ├── debugging information
 └── less optimization
```

Release is for production:

```text
Release
 ├── optimization
 └── production build
```

With a multi-configuration generator, you can do:

```powershell
cmake --build build --config Debug
```

and:

```powershell
cmake --build build --config Release
```

With a single-configuration generator such as Ninja, you normally select the configuration during the configure step.

For example:

```powershell
cmake -S . -B build\debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
```

and:

```powershell
cmake -S . -B build\release -G Ninja -DCMAKE_BUILD_TYPE=Release
```

This is one reason I recommend learning **CMake presets** later in the tutorial.

***

# Part 17 — Tests with CTest

CMake includes a test runner called:

```text
CTest
```

Enable testing:

```cmake
enable_testing()
```

Suppose we create:

```text
tests/
└── CalculatorTest.cpp
```

For a very simple first test:

```cpp
#include <iostream>

int main() {

    int result = 10 + 5;

    if (result != 15) {
        std::cerr << "Test failed!" << std::endl;
        return 1;
    }

    std::cout << "Test passed!" << std::endl;

    return 0;
}
```

CMake:

```cmake
add_executable(calculator_test
    tests/CalculatorTest.cpp
)

add_test(
    NAME CalculatorTest
    COMMAND calculator_test
)
```

Now:

```powershell
cmake --build build
```

Then:

```powershell
ctest --test-dir build
```

You should see something resembling:

```text
Test project ...
    Start 1: CalculatorTest
1/1 Test #1: CalculatorTest ........ Passed

100% tests passed
```

***

# Part 18 — Project Structure

At this point I'd recommend adopting this structure:

```text
cmake-demo/
│
├── CMakeLists.txt
│
├── src/
│   ├── main.cpp
│   ├── Calculator.cpp
│   └── Calculator.h
│
├── tests/
│   └── CalculatorTest.cpp
│
└── build/
```

Notice that:

```text
build/
```

is generated.

You generally **don't commit it to Git**.

Your `.gitignore` can contain:

```text
build/
```

***

# Part 19 — `add_subdirectory()`

As projects become larger, you don't want one giant `CMakeLists.txt`.

You can split the project:

```text
cmake-demo/
│
├── CMakeLists.txt
│
├── src/
│   └── CMakeLists.txt
│
└── tests/
    └── CMakeLists.txt
```

Root:

```cmake
cmake_minimum_required(VERSION 3.20)

project(CMakeDemo LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(tests)
```

Then `src/CMakeLists.txt`:

```cmake
add_library(calculator
    Calculator.cpp
)

add_executable(myapp
    main.cpp
)

target_include_directories(calculator
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(myapp
    PRIVATE
    calculator
)
```

This gives you a modular CMake project.

***

# Part 20 — External Libraries

Soon you'll want to use third-party libraries.

A common CMake mechanism is:

```cmake
find_package(...)
```

For example:

```cmake
find_package(OpenSSL REQUIRED)
```

Then:

```cmake
target_link_libraries(
    myapp
    PRIVATE
    OpenSSL::SSL
)
```

The general pattern is:

```text
find_package()
      │
      ▼
find dependency
      │
      ▼
obtain CMake target
      │
      ▼
target_link_libraries()
```

This is one of the most useful CMake patterns to learn.

***

# Part 21 — CMake Presets

Once you're comfortable with the basics, create:

```text
CMakePresets.json
```

For example:

```json
{
    "version": 6,

    "configurePresets": [
        {
            "name": "debug",
            "generator": "Ninja",
            "binaryDir": "${sourceDir}/build/debug",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug"
            }
        },

        {
            "name": "release",
            "generator": "Ninja",
            "binaryDir": "${sourceDir}/build/release",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release"
            }
        }
    ]
}
```

Now you can use:

```powershell
cmake --preset debug
```

and:

```powershell
cmake --build build/debug
```

For Release:

```powershell
cmake --preset release
```

and:

```powershell
cmake --build build/release
```

This is much nicer than remembering long command lines.

***

# Part 22 — A Useful PowerShell Workflow

For your Windows environment, I'd recommend getting comfortable with this workflow:

```powershell
# Configure
cmake --preset debug

# Build
cmake --build build/debug

# Test
ctest --test-dir build/debug

# Run application
.\build\debug\myapp.exe
```

And:

```powershell
# Release
cmake --preset release

cmake --build build/release

ctest --test-dir build/release
```

***

# Part 23 — Clean Build

One of the nice things about the out-of-source approach is cleaning is easy.

PowerShell:

```powershell
Remove-Item -Recurse -Force build
```

Then:

```powershell
cmake --preset debug
cmake --build build/debug
```

You have a completely fresh build.

You can also keep separate directories:

```text
build/
├── debug/
└── release/
```

which I recommend.

***

# Part 24 — The CMake Mental Model

Here's the mental model I'd like you to keep throughout the course:

```text
                   CMakeLists.txt
                         │
                         ▼
                    CMake project
                         │
                         ▼
                      TARGETS
              ┌──────────┴──────────┐
              ▼                     ▼
         Executables             Libraries
              │                     │
              └─────────┬───────────┘
                        │
                        ▼
                  Dependencies
                        │
            ┌───────────┼───────────┐
            ▼           ▼           ▼
        headers      libraries   compiler
        /includes    /packages   features
                        │
                        ▼
                   Build system
                        │
                        ▼
                        g++
                        │
                        ▼
                  .exe / .dll / .a
```

The most important idea is:

> **Modern CMake is about describing targets and relationships between targets.**

***

# Part 25 — CMake vs. g++

This distinction is worth memorizing.

Without CMake:

```powershell
g++ main.cpp Calculator.cpp -I src -std=c++20 -Wall -Wextra -o myapp.exe
```

With CMake:

```cmake
add_executable(myapp
    src/main.cpp
)

add_library(calculator
    src/Calculator.cpp
)

target_include_directories(
    calculator
    PUBLIC
    src
)

target_link_libraries(
    myapp
    PRIVATE
    calculator
)
```

Then:

```powershell
cmake -S . -B build
cmake --build build
```

CMake generates/manages the appropriate compiler invocation for you.

***

# Part 26 — Your Practical Learning Roadmap

I'd suggest working through CMake in these stages:

### Stage 1 — Absolute Beginner

Learn:

```text
CMakeLists.txt
project()
add_executable()
cmake -S
cmake --build
```

Build:

```text
Hello CMake
```

***

### Stage 2 — Targets

Learn:

```text
add_executable()
add_library()
target_link_libraries()
```

Build:

```text
Application
     │
     ▼
Calculator library
```

***

### Stage 3 — Target Properties

Learn:

```text
target_include_directories()
target_compile_features()
target_compile_options()
```

Build a proper C++20 project.

***

### Stage 4 — Testing

Learn:

```text
enable_testing()
add_test()
ctest
```

Build:

```text
Application
Library
Tests
```

***

### Stage 5 — Project Structure

Learn:

```text
add_subdirectory()
```

Create:

```text
src/
tests/
```

with separate `CMakeLists.txt` files.

***

### Stage 6 — Dependencies

Learn:

```text
find_package()
```

and eventually dependency managers such as:

```text
vcpkg
Conan
FetchContent
```

***

### Stage 7 — Professional CMake

Learn:

```text
CMakePresets.json
install()
export()
packaging
toolchains
cross-compilation
```

***

# Your First CMake Exercise

I'd recommend doing **this exact exercise now**.

Create:

```text
cmake-calculator/
│
├── CMakeLists.txt
│
└── src/
    ├── main.cpp
    ├── Calculator.cpp
    └── Calculator.h
```

Your goal is to produce:

```text
              Calculator.cpp
                     │
                     ▼
              calculator library
                     │
                     ▼
                  myapp
                     │
                     ▼
                myapp.exe
```

And the commands should eventually be:

```powershell
cmake -S . -B build
cmake --build build
```

Then:

```powershell
.\build\...\myapp.exe
```

Once this works, the next logical step is **CMake + GoogleTest + C++ unit testing**, followed by **CMake + external libraries + vcpkg**, which will take you from beginner CMake to something much closer to a real-world C++ project.

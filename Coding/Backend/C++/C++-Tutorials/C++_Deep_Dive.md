---
id: 20260921182244
title: C++ Deep Dive
author: Karl Schmitt
date: 2026-09-21
---

# C++ Deep Dive

Here is a deep-dive, hands-on tutorial for building, compiling, and debugging a robust C++ project on Windows using **CMake**, **g++** (via MinGW-w64), **PowerShell**, and **Visual Studio Code**.



## Phase 1: Environment Setup

Before writing code, ensure your toolchain is accessible via PowerShell.



1. **Install Prerequisites**:



   * **VS Code**: Download and install [Visual Studio Code](https://code.visualstudio.com/?utm_source=gemini).


   * **g++ Compiler**: Install a Windows port of GCC (such as [MinGW-w64](https://www.mingw-w64.org/?utm_source=gemini)).


   * **CMake**: Download and install [CMake](https://cmake.org/?utm_source=gemini), ensuring it is added to your system `PATH`.



2. **Install VS Code Extensions**:

   Open VS Code and install the following extensions from the Extensions marketplace (`Ctrl+Shift+X`):



   * **C/C++** (by Microsoft)


   * **CMake Tools** (by Microsoft)



3. **Verify Installation**: Open **PowerShell** and verify your tools are ready:



   PowerShell

   ```
   g++ --version
   cmake --version
   ```

## Phase 2: Project Layout & Code

We will create a multi-file project structure containing a reusable utility class and a main executable.



### 1. Directory Structure

Create a project folder named `CppDeepDive` and set up this structure:



Plaintext

```
CppDeepDive/
├── CMakeLists.txt
├── include/
│   └── Greeter.h
└── src/
    ├── Greeter.cpp
    └── main.cpp
```

### 2. Writing the Source Files

**`include/Greeter.h`**



C++

```
#pragma once
#include <string>

class Greeter {
public:
    explicit Greeter(std::string name);
    void sayHello() const;
private:
    std::string m_name;
};
```

**`src/Greeter.cpp`**



C++

```
#include "Greeter.h"
#include <iostream>

Greeter::Greeter(std::string name) : m_name(std::move(name)) {}

void Greeter::sayHello() const {
    std::cout << "Hello, " << m_name << "! Welcome to modern C++ with CMake." << std::endl;
}
```

**`src/main.cpp`**



C++

```
#include "Greeter.h"

int main() {
    Greeter greeter("PowerShell & VS Code Explorer");
    greeter.sayHello();
    return 0;
}
```

## Phase 3: The Build Engine (`CMakeLists.txt`)

Create the `CMakeLists.txt` file at the root of your project directory (`CppDeepDive/CMakeLists.txt`). This file dictates how your software compiles.



CMake

```
cmake_minimum_required(VERSION 3.20)
project(CppDeepDive VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define our library target
add_library(GreeterLib src/Greeter.cpp)
target_include_directories(GreeterLib PUBLIC include)

# Define our executable target
add_executable(CppApp src/main.cpp)

# Link the library to our executable
target_link_libraries(CppApp PRIVATE GreeterLib)
```

## Phase 4: Building and Running via PowerShell

You can perform the full build cycle directly inside the PowerShell terminal without relying on IDE extensions.



1. **Create and enter a build directory**:



   PowerShell

   ```
   mkdir build
   cd build
   ```

2. **Configure the project using CMake** (targeting MinGW Makefiles):



   PowerShell

   ```
   cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
   ```

3. **Compile the binaries**:



   PowerShell

   ```
   cmake --build .
   ```

4. **Run the executable**:



   PowerShell

   ```
   .\CppApp.exe
   ```

## Phase 5: Integrating with VS Code

To leverage VS Code's rich UI, IntelliSense, and debugger:



1. Open your project folder in VS Code:



   PowerShell

   ```
   code .
   ```

2. **Configure CMake Tools**:



   * Press `Ctrl+Shift+P` to open the Command Palette.


   * Type and select **`CMake: Scan for Kits`**.


   * Type and select **`CMake: Select a Kit`** and choose your GCC compiler (e.g., `GCC x86_64-...`).



3. **Build via VS Code**:



   * Press `Ctrl+Shift+B` or click the **Build** button in the bottom status bar managed by the CMake extension.



4. **Debugging**:



   * Open `src/main.cpp` and set a breakpoint on the `Greeter greeter(...)` line by clicking to the left of the line number (a red dot appears).


   * Go to the Run & Debug view (`Ctrl+Shift+D`).


   * Select **CMake: Run** or configure a launch target, then press **F5** to start debugging. Execution will gracefully pause at your breakpoint, allowing you to inspect local variables and step through code.



### Follow-up Question

Would you like to explore how to integrate external third-party libraries using a package manager like `vcpkg` into this setup?


# Deep-Dive Development Setup

This section explains how to develop C++ projects on Windows using:

- PowerShell
- g++
- CMake
- Visual Studio Code

---

## 20.1 Install the Required Tools

Open **PowerShell** and install the applications:

```powershell
winget install --id MSYS2.MSYS2
winget install --id Kitware.CMake
winget install --id Ninja-build.Ninja
winget install --id Microsoft.VisualStudioCode
```

Install the VS Code C++ extension:

```powershell
code --install-extension ms-vscode.cpptools
code --install-extension ms-vscode.cmake-tools
```

Restart PowerShell after installation.

---

## 20.2 Install g++ with MSYS2

Open **MSYS2 UCRT64** from the Start menu and run:

```bash
pacman -Syu
```

If MSYS2 asks you to close the terminal, close it, reopen **MSYS2 UCRT64**, and run:

```bash
pacman -Su
```

Install the C++ compiler and build tools:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc \
    mingw-w64-ucrt-x86_64-gdb \
    mingw-w64-ucrt-x86_64-make
```

The compiler is normally installed here:

```text
C:\msys64\ucrt64\bin
```

Add this directory to the Windows `PATH`:

1. Open Start.
2. Search for `Environment Variables`.
3. Select **Edit the system environment variables**.
4. Click **Environment Variables**.
5. Edit the `Path` variable.
6. Add:

```text
C:\msys64\ucrt64\bin
```

Restart VS Code and PowerShell.

Verify the installation:

```powershell
g++ --version
gdb --version
cmake --version
ninja --version
```

---

## 20.3 Create a C++ Project

Create a project folder:

```powershell
New-Item -ItemType Directory -Force `
    -Path "D:\CodingDojo\CppCMakeDemo"

Set-Location "D:\CodingDojo\CppCMakeDemo"

New-Item -ItemType Directory -Force -Path "src"
New-Item -ItemType Directory -Force -Path "include"
New-Item -ItemType Directory -Force -Path "build"
```

Recommended structure:

```text
CppCMakeDemo/
├── CMakeLists.txt
├── include/
│   └── calculator.h
├── src/
│   ├── calculator.cpp
│   └── main.cpp
└── build/
```

The `build` directory contains generated files and compiled output. It should not contain source code.

---

## 20.4 Create a Header File

Create `include/calculator.h`:

```cpp
#pragma once

int add(int first, int second);
int multiply(int first, int second);
```

`#pragma once` prevents the header from being included more than once.

---

## 20.5 Create an Implementation File

Create `src/calculator.cpp`:

```cpp
#include "calculator.h"

int add(int first, int second) {
    return first + second;
}

int multiply(int first, int second) {
    return first * second;
}
```

This file contains the function implementations declared in the header.

---

## 20.6 Create the Main Program

Create `src/main.cpp`:

```cpp
#include <iostream>
#include "calculator.h"

int main() {
    std::cout << "C++ CMake Demo\n";
    std::cout << "2 + 3 = " << add(2, 3) << '\n';
    std::cout << "4 * 5 = " << multiply(4, 5) << '\n';

    return 0;
}
```

---

## 20.7 Create `CMakeLists.txt`

Create `CMakeLists.txt` in the project root:

```cmake
cmake_minimum_required(VERSION 3.20)

project(CppCMakeDemo
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(CppCMakeDemo
    src/main.cpp
    src/calculator.cpp
)

target_include_directories(CppCMakeDemo
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

```

### Important CMake Concepts

```cmake
project(CppCMakeDemo)
```

Defines the project name.

```cmake
add_executable(CppCMakeDemo ...)
```

Creates an executable from the listed source files.

```cmake
target_include_directories(...)
```

Tells the compiler where header files are located.

```cmake
set(CMAKE_CXX_STANDARD 17)
```

Requires C++17.

---

## 20.8 Configure the Project with CMake

Open PowerShell in the project directory:

```powershell
Set-Location "D:\CodingDojo\CppCMakeDemo"
```

Configure the project:

```powershell
cmake -S . -B build -G Ninja `
    -DCMAKE_CXX_COMPILER=g++.exe
```

Explanation:

- `-S .` specifies the source directory.
- `-B build` specifies the build directory.
- `-G Ninja` selects the Ninja build system.
- `-DCMAKE_CXX_COMPILER=g++.exe` selects g++.

---

## 20.9 Build the Project

Build the executable:

```powershell
cmake --build build
```

The executable should be created at:

```text
build\CppCMakeDemo.exe
```

Run it:

```powershell
.\build\CppCMakeDemo.exe
```

Expected output:

```text
C++ CMake Demo
2 + 3 = 5
4 * 5 = 20
```

---

## 20.10 Clean and Rebuild

Delete the build directory:

```powershell
Remove-Item -Recurse -Force build
```

Reconfigure and rebuild:

```powershell
cmake -S . -B build -G Ninja `
    -DCMAKE_CXX_COMPILER=g++.exe

cmake --build build
```

A clean rebuild is useful after changing compilers, generators, or major CMake settings.

---

## 20.11 Use CMake from VS Code

Open the project:

```powershell
code .
```

Install these extensions:

- **C/C++** by Microsoft
- **CMake Tools** by Microsoft

In VS Code:

1. Press `Ctrl+Shift+P`.
2. Run **CMake: Select Configure Preset** or **CMake: Configure**.
3. Select the GCC compiler.
4. Click **Build** in the status bar.
5. Select **CMake: Run Without Debugging**.

CMake Tools usually detects `CMakeLists.txt` automatically.

---

## 20.12 Add a VS Code Build Task

Create `.vscode/tasks.json`:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "CMake Build",
            "type": "shell",
            "command": "cmake --build build",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": [
                "$gcc"
            ]
        }
    ]
}
```

Press `Ctrl+Shift+B` to build the project.

---

## 20.13 Add a Debug Configuration

Create `.vscode/launch.json`:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug CMake Application",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/CppCMakeDemo.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:/msys64/ucrt64/bin/gdb.exe",
            "preLaunchTask": "CMake Build"
        }
    ]
}
```

To debug:

1. Open `src/main.cpp`.
2. Click beside a line number to create a breakpoint.
3. Press `F5`.
4. Choose **Debug CMake Application**.

A breakpoint pauses the program so you can inspect variables and program execution.

---

## 20.14 Debugging Controls

While debugging:

| Key | Action |
|---|---|
| `F5` | Start or continue |
| `F10` | Step over |
| `F11` | Step into |
| `Shift+F11` | Step out |
| `Shift+F5` | Stop debugging |

The **Variables** panel shows current values. The **Call Stack** panel shows which functions led to the current line.

---

## 20.15 Add Compiler Warnings

Update `CMakeLists.txt`:

```cmake
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(CppCMakeDemo PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
```

Warnings can identify:

- Unused variables
- Suspicious conversions
- Missing return statements
- Incorrect code patterns

Warnings should normally be fixed instead of ignored.

---

## 20.16 Add a Build Type

For a debug build:

```powershell
cmake -S . -B build -G Ninja `
    -DCMAKE_BUILD_TYPE=Debug `
    -DCMAKE_CXX_COMPILER=g++.exe
```

For an optimized release build:

```powershell
cmake -S . -B build -G Ninja `
    -DCMAKE_BUILD_TYPE=Release `
    -DCMAKE_CXX_COMPILER=g++.exe
```

Build the selected configuration:

```powershell
cmake --build build
```

Debug builds are easier to inspect. Release builds are optimized for distribution.

---

## 20.17 Common Problems

### `g++ is not recognized`

The compiler directory is not in `PATH`.

Check:

```powershell
$env:Path -split ";"
```

Temporarily add the directory for the current PowerShell session:

```powershell
$env:Path += ";C:\msys64\ucrt64\bin"
```

Then test:

```powershell
g++ --version
```

### `cmake is not recognized`

Restart VS Code and PowerShell after installing CMake. If the problem continues, reinstall CMake and enable the option to add it to `PATH`.

### CMake uses the wrong compiler

Delete the build directory and configure again:

```powershell
Remove-Item -Recurse -Force build

cmake -S . -B build -G Ninja `
    -DCMAKE_CXX_COMPILER=g++.exe
```

CMake stores compiler information in the build directory.

### Header file not found

Make sure the project contains:

```text
include/calculator.h
```

Also verify that `CMakeLists.txt` contains:

```cmake
target_include_directories(CppCMakeDemo
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
```

### Program does not run

Check whether the executable exists:

```powershell
Get-ChildItem .\build
```

Then run it with:

```powershell
.\build\CppCMakeDemo.exe
```

---

## 20.18 A Complete Daily Workflow

From PowerShell:

```powershell
Set-Location "D:\CodingDojo\CppCMakeDemo"

cmake -S . -B build -G Ninja `
    -DCMAKE_CXX_COMPILER=g++.exe

cmake --build build

.\build\CppCMakeDemo.exe
```

After the first configuration, this is often enough:

```powershell
cmake --build build
.\build\CppCMakeDemo.exe
```

The typical workflow is:

1. Edit source code in VS Code.
2. Configure with CMake when project settings change.
3. Build with CMake.
4. Run the executable.
5. Debug with breakpoints when necessary.
6. Fix compiler warnings.
7. Repeat.

---

## 20.19 Recommended Project Rules

Follow these practices:

- Keep source files in `src`.
- Keep headers in `include`.
- Keep generated files in `build`.
- Do not manually compile large projects with long g++ commands.
- Use CMake to manage builds.
- Compile with warnings enabled.
- Use Git to track source code.
- Never commit the `build` directory.
- Use descriptive names.
- Keep functions small and focused.



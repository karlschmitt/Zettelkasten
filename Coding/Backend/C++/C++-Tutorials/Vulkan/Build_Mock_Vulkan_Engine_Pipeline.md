---
id: 20260921212429
title: Build the Mock for Vulkan Pipeline Initialization
author: Karl Schmitt
date: 2026-09-21
---

# Build the Mock for Vulkan Pipeline Initialization

Here is how to set up, compile, and run this program using CMake, g++, and VS Code inside PowerShell.

## Step 1: Organize Your Project Folder

Open PowerShell and run the following commands to create a clean folder for your project:

```powershell
mkdir VulkanPractice
cd VulkanPractice
code .
```

_(This will open the new folder directly inside VS Code)._

## Step 2: Create the Files in VS Code

Inside the VS Code file explorer sidebar, create two files in the root of your `VulkanPractice` folder:

1. `main.cpp`

   * Paste the complete C++ practice code provided in the previous message into this file and save it.

2. `CMakeLists.txt`

   * Paste the following configuration into this file and save it. This tells CMake how to build your program using `g++`.

```cmake
cmake_minimum_required(VERSION 3.10)

# Name of your practice project
project(VulkanPractice CXX)

# Require modern C++ standards (Vulkan heavily relies on modern C++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the final executable name and its source file
add_executable(VulkanPractice main.cpp)
```

## Step 3: Compile and Run via PowerShell

Switch back to your PowerShell window (or open the built-in terminal inside VS Code using \`Ctrl + \`\`) and run these steps sequentially:

## 1. Generate the Build Files

Tell CMake to analyze your `CMakeLists.txt` and prepare the build environment inside a separate folder called `build`:

```powershell
cmake -B build
```

## 2. Compile the Executable

Tell CMake to execute the compilation using your system's underlying compiler (`g++`):

```powershell
cmake --build build
```

_(Once this finishes, you will see a compiled binary file inside your `build` directory)._

## 3. Run the Program

Execute the newly created practice application:

```powershell
./build/VulkanPractice
```

_(If you are on Windows, the command might need to target the subfolder or executable directly, like `./build/Debug/VulkanPractice.exe` or simply `./build/VulkanPractice.exe` depending on your specific CMake generator setup)._

***

## Expected Output

When you run it, your terminal should print out exactly how the mock data structures were routed through memory:

```text
--- Initializing Mock Vulkan Engine ---
Creating window: My First Vulkan App (1920x1080)
-> Validation Layers: ENABLED (Debug mode active)
Engine successfully tied to device: Mock NVIDIA RTX GPU

Initialization complete. Ready to pass data blocks!

Sending vertex buffer data block to GPU...
First coordinate memory address: 0x... (Value: 0)
```

Let me know if you hit any compiler errors or CMake missing paths during these steps, or if you are ready to update this project to handle dynamic memory allocation (the Heap)!


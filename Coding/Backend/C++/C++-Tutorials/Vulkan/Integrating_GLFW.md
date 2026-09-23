---
id: 20260922191807
title: Integrating GLFW
author: Karl Schmitt
date: 2026-09-22
---

# Integrating **GLFW**

Awesome! Your console successfully read your computer's hardware specifications and detected your Intel(R) UHD Graphics card. It even correctly identified it as an Integrated CPU Graphics chip supporting the modern Vulkan 1.4 API baseline.

You have now successfully linked to the official Vulkan SDK, initialized a `VkInstance`, queried your computer's actual hardware components, and torn everything down cleanly without a single memory leak or crash. This is a huge milestone for graphics development!

Let's proceed by integrating GLFW to create an interactive desktop window.

***

## Why GLFW?

Vulkan is a cross-platform graphics API, meaning it doesn't know anything about operating systems. It has no functions to open a "Window" on Windows, Mac, or Linux. Instead, we use a lightweight companion library called GLFW to create the window shell, handle your keyboard/mouse inputs, and give Vulkan a canvas to draw pixels on.

Since the LunarG Vulkan SDK installer handles common dependencies automatically, GLFW can often be linked straight from your machine or fetched easily via CMake. Let's configure your project to pull down and build GLFW directly so everything stays self-contained.

## Step 1: Update `CMakeLists.txt` to Download GLFW

We will use CMake's built-in `FetchContent` module. This tells CMake to automatically download GLFW from GitHub during configuration and compile it perfectly alongside your application using your `g++` compiler.

Replace the contents of your `CMakeLists.txt` file with this:

```cmake
cmake_minimum_required(VERSION 3.14) # FetchContent works best with 3.14+

project(VulkanPractice CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Look for your installed Vulkan SDK
find_package(Vulkan REQUIRED)

# 2. Automatically download and prepare GLFW from GitHub
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com
    GIT_TAG        3.4 # Use stable version 3.4
)
# We only want the core library, we don't need GLFW's own internal tests/docs
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# 3. Define our practice executable
add_executable(VulkanPractice main.cpp)

# 4. Link everything together
target_include_directories(VulkanPractice PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(VulkanPractice PRIVATE Vulkan::Vulkan glfw)
```

***

## Step 2: Write an Interactive Window Program

Let's modify `main.cpp` to initialize GLFW, pop open a real window on your desktop, and run an interactive loop that keeps the window open until you click the close "X" button.

Replace your `main.cpp` code with this:

```cpp
#include <iostream>
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN // Tells GLFW to automatically map to our Vulkan headers
#include <GLFW/glfw3.h>

int main() {
    std::cout << "--- Opening a GLFW Window Shell ---\n\n";

    // 1. Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "CRITICAL: Failed to initialize GLFW!\n";
        return -1;
    }

    // 2. Tell GLFW NOT to open an OpenGL context. 
    // By default, GLFW assumes you want OpenGL. We must explicitly turn it off for Vulkan!
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    // Disable window resizing for now to keep things simple
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // 3. Create the actual desktop window
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "My First Vulkan Window", nullptr, nullptr);

    if (!window) {
        std::cerr << "CRITICAL: Failed to create GLFW window!\n";
        glfwTerminate();
        return -1;
    }

    std::cout << "SUCCESS: Interactive desktop window opened.\n";
    std::cout << "Running application loop. Close the window window to exit...\n";

    // 4. The Main Loop (The heartbeat of your app)
    // This loop keeps running over and over until you click the window's close button
    while (!glfwWindowShouldClose(window)) {
        // Poll for inputs (clicks, keypresses, window dragging) so Windows doesn't think the app is frozen
        glfwPollEvents();
    }

    // 5. Clean Up Always!
    std::cout << "\nWindow close requested. Cleaning up resources...\n";
    
    // Destroy the window handle
    glfwDestroyWindow(window);
    
    // Shut down GLFW completely
    glfwTerminate();

    std::cout << "Application finished safely.\n";
    return 0;
}
```

***

## Step 3: Configure and Build

Because CMake has to download and configure the GLFW source code, the configuration process might take a few moments longer than usual. Run these commands in your PowerShell terminal:

```powershell
# Re-configure CMake to let it pull down GLFW
cmake -B build

# Build the executable along with the newly downloaded GLFW library
cmake --build build

# Run your new windowed application!
./build/VulkanPractice
```

Let me know what happens when you run this!

* Did a blank window titled "My First Vulkan Window" pop up on your screen?
* Once you close the window, should we connect this window directly to your Vulkan instance by creating a Vulkan Window Surface (`VkSurfaceKHR`)?



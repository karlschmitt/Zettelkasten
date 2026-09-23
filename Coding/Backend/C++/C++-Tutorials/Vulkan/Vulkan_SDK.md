---
id: 20260922192539
title: Vulkan SDK
author: Karl Schmitt
date: 2026-09-22
keywords: [ Vulkan, SDK ]
---

# Vulkan SDK

You already have the official Vulkan SDK 1.4.341.1 installed on your system!

Looking at your paths, the installer successfully placed everything you need. You can find the main shortcuts in your Start Menu under `"C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Vulkan SDK 1.4.341.1"`, and the installer framework cached standard helper libraries you will eventually use (like `glm` for math, `vma` for memory allocation, and `sdl2`/`volk`).

Since the SDK is already sitting on your computer, you don't need to download anything else. We can jump straight into configuring your existing CMake project to link directly to your real Vulkan SDK and get a basic application shell running.

## Step 1: Verify the Vulkan Environment Variable

When the Vulkan SDK installs, it typically creates a system environment variable called `VULKAN_SDK` so CMake can automatically find it. Let's make sure your PowerShell can see it.

Open your PowerShell window and run:

```powershell
$env:VULKAN_SDK
```

* If it prints a directory path (like `C:\VulkanSDK\1.4.341.1` or similar): You are perfectly good to go!
* If it returns completely blank: The environment variable wasn't registered to this specific terminal session yet. Simply restart VS Code and open a fresh PowerShell window.

***

## Step 2: Update your `CMakeLists.txt` for Real Vulkan

Now we will tell CMake to find the real Vulkan SDK paths on your hard drive and link them to your project. Replace the contents of your `CMakeLists.txt` file with this configuration:

```cmake
cmake_minimum_required(VERSION 3.10)

project(VulkanPractice CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Instruct CMake to automatically search your computer for the Vulkan SDK
find_package(Vulkan REQUIRED)

add_executable(VulkanPractice main.cpp)

# 2. Tell your compiler where the Vulkan header files (.h) live
target_include_directories(VulkanPractice PRIVATE ${Vulkan_INCLUDE_DIRS})

# 3. Tell your linker to link the actual Vulkan loader library (.lib / .dll)
target_link_libraries(VulkanPractice PRIVATE Vulkan::Vulkan)
```

***

## Step 3: Write a Real Vulkan Instance Test

Let's change your `main.cpp` from a "mock" simulation into actual, real Vulkan API code. This program will talk to the Vulkan loader library on your machine and print out the active version of your installed SDK wrapper.

Replace your `main.cpp` code with this:

```cpp
#include <iostream>
#include <vulkan/vulkan.h> // The real official Vulkan header!

int main() {
    std::cout << "--- Real Vulkan SDK Connection Test ---\n\n";

    // Request the header version currently compiling
    uint32_t version = VK_HEADER_VERSION_COMPLETE;
    
    // Unpack the major, minor, and patch numbers from the binary version variant
    uint32_t major = VK_VERSION_MAJOR(version);
    uint32_t minor = VK_VERSION_MINOR(version);
    uint32_t patch = VK_VERSION_PATCH(version);

    std::cout << "Successfully linked to Vulkan SDK Header!\n";
    std::cout << "Compiled Vulkan Version: " << major << "." << minor << "." << patch << "\n";

    // Try a basic Vulkan API call to check what driver version your system loader supports
    uint32_t loaderInstanceVersion = 0;
    if (vkEnumerateInstanceVersion(&loaderInstanceVersion) == VK_SUCCESS) {
        std::cout << "System Runtime Loader Version: " 
                  << VK_VERSION_MAJOR(loaderInstanceVersion) << "."
                  << VK_VERSION_MINOR(loaderInstanceVersion) << "."
                  << VK_VERSION_PATCH(loaderInstanceVersion) << "\n";
    }

    return 0;
}
```

***

## Step 4: Re-Configure and Run

Because we modified `CMakeLists.txt` to include an external package search, we need to clear the old build cache and tell CMake to re-scan your system. Run these commands in your PowerShell terminal:

```powershell
# Remove old build cache and re-configure
Remove-Item -Recurse -Force build
cmake -B build

# Build and run
cmake --build build
./build/VulkanPractice
```

Once you run this, tell me:

* What compiled version numbers print out in your console?
* Did CMake throw any "Could NOT find Vulkan" errors while re-generating the build?

From here, we can either look at how to initialize a `VkInstance` handle or look into adding a basic windowing tool like GLFW to start drawing pixels.


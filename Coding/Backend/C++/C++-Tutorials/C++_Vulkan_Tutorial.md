---
id: 20260921183713
title: C++ Vulkan Tutorial
author: Karl Schmitt
date: 2026-09-21
keywords: [ C++, g++, Vulkan ]
---

# C++ Vulkan Tutorial

Here is a step-by-step tutorial for setting up and building a minimal Vulkan application using **vcpkg** (in manifest mode), **CMake**, **g++** (MinGW-w64), and **PowerShell**.



## Step 1: Install Prerequisites

1. **Vulkan SDK**: Download and install the \[suspicious link removed] for Windows. This installs the necessary runtime loader, validation layers, and driver support.


2. **vcpkg**: Ensure `vcpkg` is installed and integrated on your system.



## Step 2: Project Structure & Manifest

Create a new directory named `VulkanApp` and set up the following layout:



Plaintext

```
VulkanApp/
├── CMakeLists.txt
├── vcpkg.json
└── src/
    └── main.cpp
```

### 1. `vcpkg.json` (Dependency Manifest)

Create `vcpkg.json` in the root directory to automatically manage libraries:



JSON

```
{
  "name": "vulkan-app",
  "version-string": "1.0.0",
  "dependencies": [
    "vulkan-headers",
    "vulkan-loader",
    "glfw3",
    "glm"
  ]
}
```

### 2. `CMakeLists.txt`

Configure CMake to locate the vcpkg dependencies and link them to your executable:



CMake

```
cmake_minimum_required(VERSION 3.20)
project(VulkanApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages managed by vcpkg
find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(VulkanApp src/main.cpp)

# Link Vulkan, GLFW, and GLM
target_link_libraries(VulkanApp PRIVATE 
    Vulkan::Vulkan 
    glfw 
    glm::glm
)
```

## Step 3: Writing the Application Code (`src/main.cpp`)

This minimal script initializes GLFW, creates a window supporting Vulkan, creates a Vulkan instance, and gracefully cleans up.



C++

```
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

int main() {
    // 1. Initialize GLFW without creating an OpenGL context
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 2. Check Vulkan support and create an instance
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    VkInstance instance;
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        std::cerr << "Failed to create Vulkan instance!" << std::endl;
        return -1;
    }

    std::cout << "Successfully created Vulkan instance!" << std::endl;

    // 3. Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // 4. Cleanup
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
```

* **Verification:** If successful, running the compiled executable will open an 800x600 window and print `"Successfully created Vulkan instance!"` to the console.



## Step 4: Configuring and Building via PowerShell

Open **PowerShell** in your project root directory and build using CMake with the vcpkg toolchain file:



1. **Create and enter build directory**:



   PowerShell

   ```
   mkdir build
   cd build
   ```

2. **Configure with CMake** (replace `$env:VCPKG_ROOT` with your actual vcpkg installation path if it isn't set as an environment variable):



   PowerShell

   ```
   cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release ..
   ```

3. **Compile the project**:



   PowerShell

   ```
   cmake --build .
   ```

4. **Run the executable**:

   PowerShell

   ```
   .\VulkanApp.exe
   ```

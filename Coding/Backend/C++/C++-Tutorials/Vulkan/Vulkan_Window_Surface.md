---
id: 20260922201604
title: Vulkan Window Surface
author: Karl Schmitt
date: 2026-09-22
---

# Vulkan Window Surface

Now that you have a blank desktop window open, the next major step in Vulkan graphics development is creating a Vulkan Window Surface (`VkSurfaceKHR`).

Vulkan is completely platform-agnostic, meaning it has no idea what operating system it is running on. A `VkSurfaceKHR` acts as a cross-platform connection bridge between the Vulkan driver and your operating system's native window system (like Win32 on Windows).

Instead of writing tedious, OS-specific platform code manually, GLFW provides a built-in helper function that handles the connection automatically in a single line.

## Step 1: Update Your Code to Bind Vulkan to the Window

We are going to merge your working `VkInstance` code from earlier with your GLFW window code. Once the instance is created, we will pass it to GLFW to generate our rendering surface handler.

Replace your `main.cpp` with this comprehensive lifecycle setup:

```cpp
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

int main() {
    std::cout << "--- Connecting Vulkan Instance to GLFW Surface ---\n\n";

    // 1. Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "CRITICAL: Failed to initialize GLFW!\n";
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // 2. Open our Desktop Window Shell
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Surface Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "CRITICAL: Failed to create GLFW window!\n";
        glfwTerminate();
        return -1;
    }

    // 3. Vulkan Configuration
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Surface App";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // IMPORTANT SHIFT:
    // Vulkan requires explicit extensions to talk to system windows.
    // GLFW knows exactly which extensions your specific operating system needs!
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;

    // 4. Create the Vulkan Instance
    VkInstance instance = VK_NULL_HANDLE;
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS) {
        std::cerr << "CRITICAL: Failed to create Vulkan Instance! Code: " << result << "\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    std::cout << "SUCCESS: Vulkan Instance created with window extensions active.\n";

    // 5. Create the Cross-Platform Window Surface
    // We allocate a blank handle on the stack.
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    
    // GLFW handles the dirty underlying Win32/X11 API connection calls internally!
    VkResult surfaceResult = glfwCreateWindowSurface(instance, window, nullptr, &surface);
    
    if (surfaceResult != VK_SUCCESS) {
        std::cerr << "CRITICAL: Failed to link Vulkan instance to the GLFW window surface!\n";
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    std::cout << "SUCCESS: Vulkan Surface successfully generated at address: " << surface << "\n\n";

    // 6. Interactive Window Processing Loop
    std::cout << "Running frame loop. Close window to clean up...\n";
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // 7. Ordered Clean Up (Vulkan destruction order matters tremendously!)
    std::cout << "\nShutting down and destroying handles in reverse order...\n";
    
    // Always destroy the window surface BEFORE destroying the instance it relies on
    vkDestroySurfaceKHR(instance, surface, nullptr);
    std::cout << "-> Window Surface destroyed safely.\n";
    
    vkDestroyInstance(instance, nullptr);
    std::cout << "-> Vulkan Instance destroyed safely.\n";
    
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "Application finished safely.\n";

    return 0;
}
```

## Step 2: Compile and Validate Your Engine Context

Since your `CMakeLists.txt` already knows how to link to both Vulkan and GLFW, you only need to run the compilation sequence inside your PowerShell terminal:

```powershell
# Compile the updated engine codebase
cmake --build build

# Launch the surface initialization binary
./build/VulkanPractice
```

***

Let me know what prints to your console once you open and close the window!

Now that you have successfully created a platform surface context, we can transition to the absolute core of Vulkan pipeline initialization. Would you like to proceed with:

* Setting up a Logical Device (`VkDevice`) and selecting graphics queues?
* Enabling Validation Layers so Vulkan prints real-time debugging diagnostics directly into your terminal if you make a mistake?



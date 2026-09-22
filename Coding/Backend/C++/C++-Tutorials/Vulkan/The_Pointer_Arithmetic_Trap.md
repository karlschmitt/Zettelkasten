---
id: 20260921213241
title: The Pointer Arithmetic Trap
author: Karl Schmitt
date: 2026-09-21
---

# The Pointer Arithmetic Trap

Your terminal environment is perfectly set up. You have a cutting-edge version of g++ (15.2.0) and a very recent release of CMake (4.2.1). You are fully equipped to compile modern C++17 or C++20 code without any issues.

Before we move on, there is actually a critical bug in the heap practice code I just gave you. I left it in deliberately to show you how C++ handles pointers differently than Java and JavaScript.

## The Pointer Arithmetic Trap

Take a close look at these lines from the previous `main.cpp` code:

```cpp
myBuffer.pRawDataArray = 1.0f; // X
myBuffer.pRawDataArray[1] = -1.0f; // Y
myBuffer.pRawDataArray[2] = 0.0f;  // Z
```

If you try to compile that, your compiler will throw an error. In Java or JavaScript, `myBuffer.pRawDataArray` would just point to an array object. But in C++, `pRawDataArray` is a raw memory pointer holding a single 64-bit memory address (like `0x7ffeefbff5a0`).

When you write `myBuffer.pRawDataArray = 1.0f;`, C++ doesn't change the data _inside_ the array. Instead, it literally tries to overwrite the memory address itself with the floating-point value `1.0`. The compiler will stop you because you cannot assign a decimal number to a memory address variable.

## The Corrected Code

To modify the actual values sitting on the heap, you must use array brackets `[ ]` to offset from the starting memory address.

Save this corrected, fully working version into your `main.cpp`:

```cpp
#include <iostream>
#include <vector>
#include <string>

// This struct simulates a chunk of raw memory allocated on the GPU heap.
struct MockGPUMemoryBlock {
    float* pRawDataArray = nullptr; // Raw pointer to our data bytes
    size_t dataCount = 0;           // How many items are stored

    // Constructor: Allocates raw memory on the HEAP using 'new'
    MockGPUMemoryBlock(size_t count) {
        dataCount = count;
        pRawDataArray = new float[count];
        std::cout << "[Memory] Allocated " << count * sizeof(float) << " bytes on the Heap.\n";
    }

    // Destructor: Automatically frees the heap memory when the object dies
    ~MockGPUMemoryBlock() {
        if (pRawDataArray != nullptr) {
            delete[] pRawDataArray;
            std::cout << "[Memory] Heap memory successfully freed/cleaned up.\n";
        }
    }
};

int main() {
    std::cout << "--- Starting Heap Memory Practice ---\n\n";

    {
        std::cout << "Entering local scope...\n";

        // Create our mock GPU memory block to hold 3 vertex coordinates
        MockGPUMemoryBlock myBuffer(3);

        // CORRECT SYNTAX: Use index brackets to modify the data at the heap address
        myBuffer.pRawDataArray[0] = 1.0f;  // X coordinate
        myBuffer.pRawDataArray[1] = -1.0f; // Y coordinate
        myBuffer.pRawDataArray[2] = 0.5f;  // Z coordinate

        std::cout << "Data at heap pointer address (" << myBuffer.pRawDataArray << ") is: \n" 
                  << "  X: " << myBuffer.pRawDataArray[0] << "\n"
                  << "  Y: " << myBuffer.pRawDataArray[1] << "\n"
                  << "  Z: " << myBuffer.pRawDataArray[2] << "\n";

        std::cout << "Exiting local scope...\n";
    } // The Destructor triggers right here!

    std::cout << "\nOutside of scope. The memory is officially safe from leaking.\n";

    return 0;
}
```

## Compile and Run

Open your PowerShell window and execute the build commands to test your environment:

```powershell
cmake --build build
./build/VulkanPractice
```

Let me know if the program runs successfully! Once you see how the memory allocates and frees itself in the console, how should we proceed?

* Explore Vulkan Error Handling (learning how Vulkan uses C++ `enums` and return codes to signal if a graphics card failed)
* Begin downloading the Actual Vulkan SDK and setting up a real window using a library like GLFW


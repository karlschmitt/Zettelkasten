---
id 20260921194359
---

# Vulkan Basic Understanding

It is completely normal to feel overwhelmed by this! Vulkan is famously one of the most difficult graphics APIs to learn because it gives you direct, manual control over the graphics card.



Before looking at code, let’s demystify the two big concepts that trip everyone up: **Rendering Pipelines** and **GLSL Shaders**.



## 1. What is a Rendering Pipeline?

Imagine a factory assembly line. Raw materials go in at one end, and a finished product comes out the other. A **rendering pipeline** is simply an assembly line for turning 3D math data into colored pixels on your computer screen.



Because your monitor is flat (2D) and your game world has depth (3D), the computer has to calculate how to flatten, position, light, and color everything.



The pipeline typically flows through these main stages:



1. **Vertex Input (The Raw Data):** You feed the GPU a list of points (vertices) that outline shapes. For a triangle, this is just 3 coordinates $(x, y, z)$.


2. **Vertex Shader (The Position Adjuster):** A small program that takes those 3D points and figures out where they should land on your 2D screen.


3. **Rasterization (The Dot-Connector):** The computer takes the connected vertices and fills the inside space with a grid of tiny squares called **pixels** (or fragments).


4. **Fragment/Pixel Shader (The Painter):** Another small program that decides what color each individual pixel should be (e.g., solid red, or shaded based on a virtual light source).


5. **Output Merger:** The final pixels are drawn onto your screen buffer.



## 2. What are GLSL Shaders?

In the pipeline above, we mentioned "shaders."



* **What they are:** Shaders are tiny, specialized computer programs. Unlike normal C++ code that runs on your computer's main processor (CPU), **shaders run directly on your graphics card (GPU)**.


* **Why they matter:** CPUs are great at doing a few complex tasks one after another. GPUs are like armies of thousands of tiny workers who can do simple tasks all at the exact same time. Shaders are the instructions you give to that army.


* **What is GLSL?** **GLSL** stands for _OpenGL Shading Language_. It is the programming language used to write these GPU scripts. Even though Vulkan isn't OpenGL, Vulkan still uses GLSL (which gets translated into a format called SPIR-V) to tell the GPU how to color and shape things.



## 3. Why Vulkan? (And Why It's Hard)

In older APIs like OpenGL or DirectX 11, the graphics card driver did a lot of heavy lifting behind the scenes. It guessed what you wanted.



**Vulkan says:** _"No guessing. Tell me every single detail."_



To draw a single triangle in Vulkan, you have to manually:



1. Initialize the Vulkan instance and find a compatible GPU.


2. Create a logical device and command queues.


3. Set up a "swapchain" (so your images sync nicely with your window monitor).


4. Compile your GLSL shaders and load them into memory.


5. Define how vertices are laid out in memory.


6. Create a "Render Pass" (telling Vulkan where to draw, like clearing the screen to black).


7. Record command buffers (a to-do list for the GPU).


8. Send it to the GPU and loop it.



Because of this, a basic "Hello Triangle" program in Vulkan is usually around **500 to 1,000 lines of code**.



### Where to go from here?

Since you're just starting out with these concepts, would you like to take a step back and look at a friendly, conceptual guide on how a basic 3D triangle gets drawn, or would you prefer a breakdown of a simple GLSL shader file?

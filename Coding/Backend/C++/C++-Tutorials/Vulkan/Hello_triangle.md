---
id: 20260921194553
title: Vulkan Hello Triangle
author: Karl Schmitt
date: 2026-09-21
---

# Vulkan Hello Triangle

Drawing your very first triangle in Vulkan is a major rite of passage! Because Vulkan doesn't hide anything from you, it takes a bit of setup.



To keep things approachable, let's look at how the two shaders and the C++ code work together to draw a simple, colorful triangle on your screen.



## Step 1: The Two Tiny Shaders

Before writing C++ code, a Vulkan application needs its two shaders (written in GLSL). Create a folder named `shaders` inside your project directory and add these two files:



### 1. The Vertex Shader (`shaders/shader.vert`)

* **What it does:** This script runs once for every vertex (corner) of your triangle. It takes the 3D coordinates and passes them through.



OpenGL Shading Language

```
#version 450

// These are the coordinates for our 3 corners (X, Y, Z)
vec2 positions[3] = vec2[](
    vec2(0.0, -0.5),   // Top center
    vec2(0.5, 0.5),    // Bottom right
    vec2(-0.5, 0.5)    // Bottom left
);

// Colors corresponding to each vertex: Red, Green, Blue
vec3 colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

// Output variables to pass to the fragment shader
layout(location = 0) out vec3 fragColor;

void main() {
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    fragColor = colors[gl_VertexIndex];
}
```

### 2. The Fragment Shader (`shaders/shader.frag`)

* **What it does:** This script takes the colors we passed from the vertex shader and blends them smoothly across the pixels inside the triangle.



OpenGL Shading Language

```
#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 0) out vec4 outColor;

void main() {
    // Output the interpolated color with full opacity (1.0 alpha)
    outColor = vec4(fragColor, 1.0);
}
```

> **Note on Compilation:** In a full production engine, you compile these `.vert` and `.frag` files into binary format (`.spv` files) using Vulkan's `glslc` compiler tool before running your C++ program.
>
>

## Step 2: What the C++ Code Has to Do

To actually execute those shaders and put pixels on the screen, your C++ `main.cpp` needs to perform these core steps in order:



1. **Initialize GLFW & Window:** Open a window and tell GLFW _not_ to create an OpenGL context (since we are using Vulkan).


2. **Create a Vulkan Instance:** Connect your application to the graphics driver.


3. **Pick a Physical Device (GPU):** Find a graphics card on your computer that supports Vulkan.


4. **Create a Logical Device & Queues:** Set up a communication channel with the GPU.


5. **Create a Swapchain:** Set up image buffers so the GPU can draw frames safely without flickering on your monitor.


6. **Create the Graphics Pipeline:** Load your compiled shaders, tell Vulkan how triangles should be rasterized (filled in), and bundle them together into a pipeline state object.


7. **Record Command Buffers:** Write down the instructions for the GPU ("Clear the screen, bind the pipeline, draw 3 vertices").


8. **The Render Loop:** Continuously poll window events, draw frames, and present them to the screen until you close the window.



Because writing all 500+ lines of raw boilerplate C++ code by hand can be a lot to digest at once, most developers learning Vulkan step through the legendary [Vulkan Tutorial website](https://vulkan-tutorial.com/?utm_source=gemini), which walks through every single line of this initialization process.



### Follow-up Question

Would you like a breakdown of how **Command Buffers** work, or how the CPU talks to the GPU asynchronously in Vulkan?

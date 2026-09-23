---
id: 20260922213912
title: Step‑by‑Step Vulkan Roadmap
author: Karl Schmitt
date: 2026-09-22
---

# Step‑by‑Step Vulkan Roadmap

You’ve already nailed the “hello window + surface” part—nice work. Here’s a **practical, step‑by‑step Vulkan roadmap** from where you are now to “real rendering”.

### 1. Instance, surface, and validation layers

* **Goal:** What you already have, plus debug tools.

* **Steps:**

  * Add **validation layers** (`VK_LAYER_KHRONOS_validation`).

  * Add a **debug messenger** (`VK_EXT_debug_utils`) to log Vulkan errors and warnings.

  * Keep your current **GLFW window + surface** setup.

### 2. Physical device selection (GPU picking)

* **Goal:** Choose which GPU to use.

* **Steps:**

  * Enumerate physical devices with `vkEnumeratePhysicalDevices`.

  * For each device, query:

    * **Queue families** (`vkGetPhysicalDeviceQueueFamilyProperties`).

    * **Surface support** (`vkGetPhysicalDeviceSurfaceSupportKHR`).

  * Pick a device that:

    * Supports **graphics** and **present** queues.

    * Supports required **surface formats** and **present modes**.

### 3. Logical device and queues

* **Goal:** Create a device you can submit work to.

* **Steps:**

  * Define **queue create info** for graphics/present queues.

  * Enable required **device extensions** (e.g. `VK_KHR_swapchain`).

  * Call `vkCreateDevice`.

  * Retrieve queue handles with `vkGetDeviceQueue`.

### 4. Swapchain and image views

* **Goal:** Get images you can render into and present.

* **Steps:**

  * Query **surface capabilities**, **formats**, and **present modes**.

  * Choose:

    * Surface format (e.g. `VK_FORMAT_B8G8R8A8_SRGB`).

    * Present mode (e.g. `VK_PRESENT_MODE_FIFO_KHR`).

    * Swapchain extent (window size).

  * Create the **swapchain** (`vkCreateSwapchainKHR`).

  * Get swapchain images (`vkGetSwapchainImagesKHR`).

  * Create **image views** for each image.

### 5. Render pass, framebuffers, and pipeline

* **Goal:** Define how rendering happens.

* **Steps:**

  * Create a **render pass** (color attachment, load/store ops).

  * Create **framebuffers**—one per swapchain image.

  * Write simple **vertex + fragment shaders** (SPIR‑V).

  * Create:

    * **Shader modules** (`vkCreateShaderModule`).

    * **Pipeline layout** (even empty at first).

    * **Graphics pipeline** (fixed‑function stages + shaders).

### 6. Command pool, command buffers, and synchronization

* **Goal:** Record and submit draw commands safely.

* **Steps:**

  * Create a **command pool** for your graphics queue.

  * Allocate **command buffers**.

  * For each frame:

    * Begin command buffer.

    * Begin render pass.

    * Bind pipeline.

    * Issue `vkCmdDraw` (for a hard‑coded triangle).

    * End render pass and command buffer.

  * Create **semaphores** and **fences** for:

    * Image acquisition.

    * Rendering completion.

  * Implement the **frame loop**:

    * Acquire image → record commands → submit → present.

### 7. Cleanup and robustness

* **Goal:** Make it stable and leak‑free.

* **Steps:**

  * Destroy resources in **reverse order**:

    * Pipeline, render pass, framebuffers, swapchain, device, surface, instance.

  * Handle **window resize**:

    * Recreate swapchain and dependent resources.

  * Add **error checking** and assertions everywhere.

### 8. Beyond the triangle

Once the triangle works:

* **Vertex buffers & index buffers**

* **Uniform buffers** (camera, transforms)

* **Descriptor sets & layouts**

* **Textures & samplers**

* **Depth buffering**

* **Multiple passes / post‑processing**

* **Model loading (OBJ, glTF)**

If you like, next step could be: I give you a **concrete “Step 2: physical device selection” code file + matching CMakeLists.txt** so you can continue this journey one commit at a time.

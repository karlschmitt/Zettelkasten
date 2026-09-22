---
id: 20260921201512
title: Vulkan Command Buffer Example
author: Karl Schmittt
date: 2026-09-21
---

# Vulkan Command Buffer Example

Here is a clean, heavily commented C++ code snippet showing how a Vulkan **Command Buffer** is recorded to clear the screen and draw our triangle.



### Command Buffer Recording Code

C++

```
// 1. Define how we want to begin recording our command buffer
VkCommandBufferBeginInfo beginInfo{};
beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
beginInfo.flags = 0;             // Optional flags (e.g., if it can be submitted multiple times)
beginInfo.pInheritanceInfo = nullptr; // Used for secondary command buffers

// Start recording into our command buffer
if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("Failed to begin recording command buffer!");
}

// 2. Define the Render Pass (tells Vulkan where we are drawing and how to clear the screen)
VkRenderPassBeginInfo renderPassInfo{};
renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
renderPassInfo.renderPass = renderPass;     // Your created render pass object
renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex]; // The current window image
renderPassInfo.renderArea.offset = {0, 0};
renderPassInfo.renderArea.extent = swapChainExtent;

// Set the clear color (dark blue background) before drawing
VkClearValue clearColor = {{{0.0f, 0.0f, 0.2f, 1.0f}}};
renderPassInfo.clearValueCount = 1;
renderPassInfo.pClearValues = &clearColor;

// 3. Begin the render pass (this clears the screen)
vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // 4. Bind (activate) our graphics pipeline (which includes our compiled shaders)
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

    // 5. Draw the triangle! (3 vertices, 1 instance)
    vkCmdDraw(commandBuffer, 3, 1, 0, 0);

// 6. End the render pass
vkCmdEndRenderPass(commandBuffer);

// 7. Finish recording the command buffer
if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
    throw std::runtime_error("Failed to record command buffer!");
}
```

### What's Happening Here?

* **`vkBeginCommandBuffer`**: Switches the buffer into "recording mode" so the CPU can write instructions to it.


* **`vkCmdBeginRenderPass`**: Tells Vulkan to target the current window frame and clear it out using our background color (`clearColor`).


* **`vkCmdBindPipeline`**: Activates our shaders and graphics rules so the GPU knows _how_ to draw.


* **`vkCmdDraw(..., 3, 1, ...)`**: The actual command telling the GPU: _"Draw 3 vertices starting from index 0."_


* **`vkEndCommandBuffer`**: Closes the script. This buffer is now ready to be handed off to the GPU queue for execution.



### Follow-up Question

Would you like to explore how the CPU waits for the GPU to finish rendering so your app doesn't crash or run out of memory?

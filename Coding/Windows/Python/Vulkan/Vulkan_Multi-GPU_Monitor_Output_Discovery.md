---
id: 20260923194054
title: Vulkan Multi-GPU and Monitor Output Discovery
author: Karl Schmitt
date: 2026-09-23
---

# Vulkan Multi-GPU and Monitor Output Discovery

This script uses Python and Vulkan WSI extensions to query a multi-GPU system, identifying each graphics card and listing the physical monitors (display endpoints) wired directly into each GPU.

### 🛠️ Dependencies & Execution Requirements

Ensure you are using the LunarG Vulkan SDK and that the `vulkan` wrapper is installed.
```bash
pip install vulkan
```
*Note: Your graphics drivers must support native display queries (`VK_KHR_display`). On some hybrid laptop setups, all displays may register under the integrated card if the discrete card routes its signals via a multiplexer (Muxless).*

### 💻 Multi-GPU Multi-Monitor Inspector Script

Save this script as `vulkan_display_inspector.py`:

```python
import vulkan as vk
import sys

def main():
    # 1. Required Instance Extensions to look at raw hardware monitors
    # We must explicitly request the surface and display capability extensions
    instance_extensions = [
        vk.VK_KHR_SURFACE_EXTENSION_NAME,
        vk.VK_KHR_DISPLAY_EXTENSION_NAME
    ]

    app_info = vk.VkApplicationInfo(
        sType=vk.VK_STRUCTURE_TYPE_APPLICATION_INFO,
        pApplicationName="Multi-GPU Monitor Scanner",
        applicationVersion=vk.VK_MAKE_VERSION(1, 0, 0),
        pEngineName="No Engine",
        engineVersion=vk.VK_MAKE_VERSION(1, 0, 0),
        apiVersion=vk.VK_API_VERSION_1_1
    )

    create_info = vk.VkInstanceCreateInfo(
        sType=vk.VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        pApplicationInfo=app_info,
        enabledExtensionCount=len(instance_extensions),
        ppEnabledExtensionNames=instance_extensions,
        enabledLayerCount=0,
        ppEnabledLayerNames=None
    )

    try:
        instance = vk.vkCreateInstance(create_info, None)
    except vk.VkError as e:
        print(f"❌ Failed to initialize Vulkan Instance (Extensions may be unsupported): {e}")
        return

    # 2. Discover Graphics Cards
    devices = vk.vkEnumeratePhysicalDevices(instance)
    print(f"\n=======================================================")
    print(f"🖥️  System Topology: {len(devices)} Graphics Card(s) Detected")
    print(f"=======================================================")

    device_types = {
        vk.VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: "Integrated GPU",
        vk.VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: "Discrete GPU (Dedicated)",
        vk.VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: "Virtual GPU",
        vk.VK_PHYSICAL_DEVICE_TYPE_CPU: "CPU Processing Unit"
    }

    # Total tracking variables
    total_monitors = 0

    # 3. Iterate through every detected Graphics Card
    for i, device in enumerate(devices):
        props = vk.vkGetPhysicalDeviceProperties(device)
        device_name = props.deviceName.decode('utf-8').strip('\x00')
        device_type = device_types.get(props.deviceType, "Unknown Device Type")
        
        print(f"\n[GPU #{i}]: {device_name}")
        print(f"  🔹 Hardware Architecture: {device_type}")

        # 4. Check for connected Monitor Displays ("Splitters") via this specific GPU
        try:
            # Query the displays directly attached to the video card's execution pipelines
            displays = vk.vkGetPhysicalDeviceDisplayPropertiesKHR(device)
            monitor_count = len(displays)
            total_monitors += monitor_count
            
            print(f"  🔹 Physical Monitor Outputs Found: {monitor_count}")
            
            for m_idx, display in enumerate(displays):
                monitor_name = display.displayName.decode('utf-8').strip('\x00') if display.displayName else "Generic/Unknown Display"
                
                # Fetch supported visual resolution metrics
                width = display.physicalDimensions.width
                height = display.physicalDimensions.height
                
                print(f"     📍 Monitor #{m_idx} -> \"{monitor_name}\"")
                print(f"        Physical Panel Size: {width}mm x {height}mm")
                print(f"        Stereo 3D Capable: {'Yes' if display.isStereoCap else 'No'}")
                
        except vk.VkError as e:
            # Fallback if a specific GPU driver block lacks the WSI query implementation
            print(f"  ⚠️  Could not fetch connected monitors from this device driver ({e}).")

    print(f"\n=======================================================")
    print(f"📊 Summary: {len(devices)} GPU(s) driving {total_monitors} Total Monitor Connection(s).")
    print(f"=======================================================\n")

    # Clean up Vulkan handle allocation
    vk.vkDestroyInstance(instance, None)

if __name__ == "__main__":
    main()
```
---

### 🔍 System Mechanics Explained

* **`VK_KHR_display`**: This bypasses operating system window abstractions (like Windows Desktop Window Manager or X11) to let Vulkan inspect the raw display outputs connected via physical HDMI/DisplayPort sockets.
* **`vkGetPhysicalDeviceDisplayPropertiesKHR`**: Queries the chosen GPU to discover what displays are hanging off its memory controller context.
* **Multi-GPU Routing Reality**: In a standard desktop with 2 dedicated graphics cards, this script will explicitly split the output. It will show exactly which monitors are plugged into GPU 0 and which are plugged into GPU 1. 

---


---
id: 20260923192617
---

# Vulkan GPU Discovery and Queue Families (Python)

**Yes, you can use Python and Vulkan to discover your graphics card and its properties.** In Vulkan terminology, a physical graphics card is represented as a `VkPhysicalDevice`. 

Regarding **"splitters"**, this is not a standard Vulkan term. Depending on what you mean, Vulkan can find:
1. **Queue Families**: The hardware pipelines that split tasks into graphics, compute, or transfer operations.
2. **Multi-GPU / SLI / CrossFire setups**: Handled via Vulkan device groups (`VkPhysicalDeviceGroupProperties`).

Below is a Python script that discovers your connected graphics cards, queries their names, checks if they are dedicated or integrated, and counts their execution **Queue Families** (the physical command pipelines inside the GPU).

### 💻 Python Graphics Card & Hardware Inspector

Save this script as `vulkan_hardware_inspector.py`:

```python
import vulkan as vk
import sys

def main():
    # 1. Initialize a minimal Vulkan instance
    app_info = vk.VkApplicationInfo(
        sType=vk.VK_STRUCTURE_TYPE_APPLICATION_INFO,
        pApplicationName="Hardware Inspector",
        applicationVersion=vk.VK_MAKE_VERSION(1, 0, 0),
        pEngineName="No Engine",
        engineVersion=vk.VK_MAKE_VERSION(1, 0, 0),
        apiVersion=vk.VK_API_VERSION_1_0
    )

    create_info = vk.VkInstanceCreateInfo(
        sType=vk.VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        pApplicationInfo=app_info,
        enabledExtensionCount=0,
        ppEnabledExtensionNames=None,
        enabledLayerCount=0,
        ppEnabledLayerNames=None
    )

    try:
        instance = vk.vkCreateInstance(create_info, None)
    except vk.VkError as e:
        print(f"❌ Failed to initialize Vulkan: {e}")
        return

    # 2. Discover Physical Devices (Graphics Cards)
    # vkEnumeratePhysicalDevices returns a list of available GPUs
    devices = vk.vkEnumeratePhysicalDevices(instance)
    
    print(f"\n🖥️ Found {len(devices)} Vulkan-compatible graphics device(s):\n")

    # Map device type integers to human-readable strings
    device_types = {
        vk.VK_PHYSICAL_DEVICE_TYPE_OTHER: "Other/Unknown",
        vk.VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: "Integrated GPU (CPU-bound)",
        vk.VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: "Discrete GPU (Dedicated Graphics Card)",
        vk.VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: "Virtual GPU",
        vk.VK_PHYSICAL_DEVICE_TYPE_CPU: "CPU (Software Rasterizer)"
    }

    # 3. Inspect each graphics card
    for i, device in enumerate(devices):
        # Fetch general hardware properties (Name, Type, Driver version)
        props = vk.vkGetPhysicalDeviceProperties(device)
        
        # Decode the device name bytes into a Python string
        device_name = props.deviceName.decode('utf-8').strip('\x00')
        device_type = device_types.get(props.deviceType, "Unknown")
        
        print(f"--- [Device #{i}]: {device_name} ---")
        print(f"  🔹 Type: {device_type}")
        print(f"  🔹 Driver Version: {props.driverVersion}")
        print(f"  🔹 API Version Supported: {props.apiVersion}")

        # 4. Check Queue Families ("Splitters" / Hardware Execution Pipelines)
        # These represent how the GPU physically splits up different types of work
        queue_families = vk.vkGetPhysicalDeviceQueueFamilyProperties(device)
        print(f"  🔹 Number of physical Command Queue Families: {len(queue_families)}")
        
        for q_idx, queue in enumerate(queue_families):
            capabilities = []
            if queue.queueFlags & vk.VK_QUEUE_GRAPHICS_BIT:
                capabilities.append("GRAPHICS (Drawing shapes)")
            if queue.queueFlags & vk.VK_QUEUE_COMPUTE_BIT:
                capabilities.append("COMPUTE (Math/AI kernels)")
            if queue.queueFlags & vk.VK_QUEUE_TRANSFER_BIT:
                capabilities.append("TRANSFER (Moving data to VRAM)")
            
            print(f"     📍 Family #{q_idx}: Max {queue.queueCount} simultaneous stream(s)")
            print(f"        Capabilities: {', '.join(capabilities)}")
        print("\n")

    # Clean up the instance
    vk.vkDestroyInstance(instance, None)

if __name__ == "__main__":
    main()
```

---

### 🔍 Explaining the Output Properties

* **`vkEnumeratePhysicalDevices`**: Asks the system drivers for a list of physical graphics processors available on the motherboard.
* **`props.deviceType`**: Lets you instantly filter whether the script is looking at your power-saving Integrated Intel/AMD laptop graphics or your high-performance dedicated NVIDIA/AMD PCIe card.
* **Queue Families**: Inside modern GPUs, architecture is separated into specialized hardware lanes. Some handle drawing triangles to the screen, some manage asynchronous heavy compute operations, and others are optimized for lightning-fast memory copies. This is how Vulkan achieves unparalleled multithreading optimization compared to older APIs.

---
#vulkan #python #graphics-programming #hardware-discovery

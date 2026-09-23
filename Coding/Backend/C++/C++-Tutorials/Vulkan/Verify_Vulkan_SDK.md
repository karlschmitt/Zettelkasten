---
id: 20260922193902
title: Verify Vulkan SDK
author: Karl Schmitt
date: 2026-09-22
---

# Verify Vulkan SDK

The quickest way to verify a **Vulkan SDK installation** is to check that the SDK tools, loader, and drivers are correctly installed and functioning. The most authoritative sources point to **two primary verification methods**: running `vulkaninfo` and running a **sample Vulkan program** such as `vkcube` or a smoke test.

Below is a clear, structured guide based on the most relevant sources.

## ✅ **1. Run: **`vulkaninfo`** (the official verification tool)**

The Vulkan documentation and multiple platform guides state that the simplest and most reliable verification step is running `vulkaninfo`, which is included with the Vulkan SDK and Vulkan tools. It prints detailed information about your Vulkan loader, drivers, and devices.

### **Windows**

If you installed the LunarG Vulkan SDK, you can find:

Code

```
<SDK install path>\Bin\vulkaninfo.exe
```

Run it in PowerShell:

powershell

```
& "C:\VulkanSDK\<version>\Bin\vulkaninfo.exe"
```

If Vulkan is installed correctly, you will see:

* Vulkan instance information

* GPU(s) detected

* Supported extensions

* Driver versions

If it fails, you’ll get an error indicating missing loader or drivers.

## ✅ **2. Run a demo application (e.g.,&#x20;**`vkcube`**)**

The Vulkan SDK includes demo programs such as `vkcube.exe`. Running them verifies that:

* The loader works

* The driver works

* Swapchain creation works

* Rendering works

The VulkanTutorial environment setup explicitly recommends running `vkcube.exe` to verify installation.

### Windows example:

powershell

```
& "C:\VulkanSDK\<version>\Bin\vkcube.exe"
```

If you see a spinning cube, your Vulkan SDK is functioning.

## ✅ **3. Use a smoke test program (optional but thorough)**

A more advanced verification is using a **Vulkan smoke test** tool. It initializes a Vulkan instance, checks surface extensions, and attempts to create a logical device. This is useful if you want deeper confirmation beyond `vkcube`.

This test verifies:

* Loader

* Instance creation

* Physical device enumeration

* Logical device creation

* Surface support

## 🧪 **4. Check that the Vulkan loader and ICDs are present**

The Vulkan stack consists of:

* **Loader** (`vulkan-1.dll` on Windows)

* **ICD (Installable Client Driver)** from your GPU vendor

The Vulkan documentation emphasizes that both must be present for Vulkan to work.

### Windows check:

Look for ICD JSON files in:

Code

```
C:\Windows\System32\DriverStore\FileRepository\
```

Or check the SDK’s loader DLL:

Code

```
C:\VulkanSDK\<version>\Bin\vulkan-1.dll
```

## 🧩 **5. If you installed the SDK for development, verify tools**

The Vulkan SDK includes:

* `glslc` (shader compiler)

* `glslangValidator`

* Validation layers

* Loader

* Headers

The VulkanTutorial documentation confirms these are part of the SDK and should be present in the **Bin**, **Include**, and **Lib** directories.

Check that these exist:

Code

```
C:\VulkanSDK\<version>\Bin\glslc.exe
C:\VulkanSDK\<version>\Bin\glslangValidator.exe
C:\VulkanSDK\<version>\Bin\VK_LAYER_KHRONOS_validation.dll
```

## 🎯 **Summary: The 3-step verification checklist**

1. **Run&#x20;**`vulkaninfo`

   * If it prints GPU and driver info → Vulkan is installed.

2. **Run&#x20;**`vkcube`

   * If the cube renders → Vulkan is working.

3. **Check SDK tools**

   * `glslc`, `glslangValidator`, validation layers → SDK installed correctly.

These steps match the official Vulkan documentation and SDK setup guides.

## Want me to generate a PowerShell script that automatically checks all of this?

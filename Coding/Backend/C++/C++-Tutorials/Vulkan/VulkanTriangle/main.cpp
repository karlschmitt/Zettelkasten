// Vulkan Triangle — complete, self-contained example.
// Mirrors the structure of Cpp-Vulkan-Beginner-DeepDive-Tutorial.md.
//
// Set the environment variable TRIANGLE_AUTOCLOSE=<N> to render N frames and
// then exit cleanly (useful for automated verification / CI). If unset, the
// window stays open until you close it.

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <set>
#include <stdexcept>
#include <vector>

namespace {

constexpr uint32_t WIDTH  = 800;
constexpr uint32_t HEIGHT = 600;
constexpr int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> kValidationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
const std::vector<const char*> kDeviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
constexpr bool kEnableValidation = false;
#else
constexpr bool kEnableValidation = true;
#endif

std::vector<char> readFile(const std::string& path) {
    std::ifstream file(path, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open file: " + path);
    }
    const size_t size = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(size);
    file.seekg(0);
    file.read(buffer.data(), static_cast<std::streamsize>(size));
    return buffer;
}

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT,
        const VkDebugUtilsMessengerCallbackDataEXT* data,
        void*) {
    if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        std::cerr << "[VULKAN] " << data->pMessage << '\n';
    }
    return VK_FALSE;
}

VkResult createDebugUtilsMessengerEXT(
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT* ci,
        const VkAllocationCallbacks* alloc,
        VkDebugUtilsMessengerEXT* out) {
    auto fn = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
    if (fn) return fn(instance, ci, alloc, out);
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void destroyDebugUtilsMessengerEXT(
        VkInstance instance,
        VkDebugUtilsMessengerEXT messenger,
        const VkAllocationCallbacks* alloc) {
    auto fn = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
    if (fn) fn(instance, messenger, alloc);
}

struct QueueFamilyIndices {
    std::optional<uint32_t> graphics;
    std::optional<uint32_t> present;
    bool complete() const { return graphics.has_value() && present.has_value(); }
};

struct SwapchainSupport {
    VkSurfaceCapabilitiesKHR capabilities{};
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

} // namespace

class TriangleApp {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window_ = nullptr;

    VkInstance instance_ = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT debugMessenger_ = VK_NULL_HANDLE;
    VkSurfaceKHR surface_ = VK_NULL_HANDLE;

    VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
    VkDevice device_ = VK_NULL_HANDLE;
    VkQueue graphicsQueue_ = VK_NULL_HANDLE;
    VkQueue presentQueue_ = VK_NULL_HANDLE;

    VkSwapchainKHR swapchain_ = VK_NULL_HANDLE;
    std::vector<VkImage> swapchainImages_;
    VkFormat swapchainFormat_{};
    VkExtent2D swapchainExtent_{};
    std::vector<VkImageView> swapchainImageViews_;
    std::vector<VkFramebuffer> framebuffers_;

    VkRenderPass renderPass_ = VK_NULL_HANDLE;
    VkPipelineLayout pipelineLayout_ = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline_ = VK_NULL_HANDLE;

    VkCommandPool commandPool_ = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> commandBuffers_;

    std::vector<VkSemaphore> imageAvailable_;   // per frame-in-flight
    std::vector<VkSemaphore> renderFinished_;   // per swapchain image
    std::vector<VkFence> inFlight_;             // per frame-in-flight
    uint32_t currentFrame_ = 0;
    long captureFrameNumber_ = -1;      // frame at which to capture, or -1
    std::string capturePath_ = "triangle_out.ppm";
    bool framebufferResized_ = false;

    long autoCloseFrames_ = -1; // -1 = run until window closed
    long framesRendered_ = 0;

    // ---- window ---------------------------------------------------------
    void initWindow() {
        if (const char* env = std::getenv("TRIANGLE_AUTOCLOSE")) {
            autoCloseFrames_ = std::atol(env);
        }
        if (const char* cap = std::getenv("TRIANGLE_CAPTURE")) {
            capturePath_ = cap;
            captureFrameNumber_ = 3; // capture an early, fully-rendered frame
            if (const char* fn = std::getenv("TRIANGLE_CAPTURE_FRAME")) {
                captureFrameNumber_ = std::atol(fn);
            }
        }
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window_ = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Triangle", nullptr, nullptr);
        glfwSetWindowUserPointer(window_, this);
        glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* w, int, int) {
            static_cast<TriangleApp*>(glfwGetWindowUserPointer(w))->framebufferResized_ = true;
        });
    }

    // ---- top-level Vulkan bring-up -------------------------------------
    void initVulkan() {
        createInstance();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapchain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createCommandBuffers();
        createSyncObjects();
    }

    // ---- instance -------------------------------------------------------
    bool checkValidationLayerSupport() {
        uint32_t count = 0;
        vkEnumerateInstanceLayerProperties(&count, nullptr);
        std::vector<VkLayerProperties> available(count);
        vkEnumerateInstanceLayerProperties(&count, available.data());
        for (const char* name : kValidationLayers) {
            bool found = false;
            for (const auto& props : available) {
                if (std::strcmp(name, props.layerName) == 0) { found = true; break; }
            }
            if (!found) return false;
        }
        return true;
    }

    std::vector<const char*> requiredInstanceExtensions() {
        uint32_t glfwCount = 0;
        const char** glfwExts = glfwGetRequiredInstanceExtensions(&glfwCount);
        std::vector<const char*> exts(glfwExts, glfwExts + glfwCount);
        if (kEnableValidation) exts.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        return exts;
    }

    void populateDebugCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& ci) {
        ci = {};
        ci.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        ci.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        ci.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                         VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                         VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        ci.pfnUserCallback = debugCallback;
    }

    void createInstance() {
        if (kEnableValidation && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested but not available");
        }

        VkApplicationInfo app{};
        app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app.pApplicationName = "Vulkan Triangle";
        app.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app.pEngineName = "None";
        app.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app.apiVersion = VK_API_VERSION_1_3;

        auto exts = requiredInstanceExtensions();

        VkInstanceCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        ci.pApplicationInfo = &app;
        ci.enabledExtensionCount = static_cast<uint32_t>(exts.size());
        ci.ppEnabledExtensionNames = exts.data();

        VkDebugUtilsMessengerCreateInfoEXT dbg{};
        if (kEnableValidation) {
            ci.enabledLayerCount = static_cast<uint32_t>(kValidationLayers.size());
            ci.ppEnabledLayerNames = kValidationLayers.data();
            populateDebugCreateInfo(dbg);
            ci.pNext = &dbg;
        }

        if (vkCreateInstance(&ci, nullptr, &instance_) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance");
        }
    }

    void setupDebugMessenger() {
        if (!kEnableValidation) return;
        VkDebugUtilsMessengerCreateInfoEXT ci{};
        populateDebugCreateInfo(ci);
        if (createDebugUtilsMessengerEXT(instance_, &ci, nullptr, &debugMessenger_) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger");
        }
    }

    void createSurface() {
        if (glfwCreateWindowSurface(instance_, window_, nullptr, &surface_) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface");
        }
    }

    // ---- physical device ------------------------------------------------
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice dev) {
        QueueFamilyIndices idx;
        uint32_t count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(dev, &count, nullptr);
        std::vector<VkQueueFamilyProperties> families(count);
        vkGetPhysicalDeviceQueueFamilyProperties(dev, &count, families.data());
        for (uint32_t i = 0; i < count; ++i) {
            if (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) idx.graphics = i;
            VkBool32 present = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(dev, i, surface_, &present);
            if (present) idx.present = i;
            if (idx.complete()) break;
        }
        return idx;
    }

    bool checkDeviceExtensions(VkPhysicalDevice dev) {
        uint32_t count = 0;
        vkEnumerateDeviceExtensionProperties(dev, nullptr, &count, nullptr);
        std::vector<VkExtensionProperties> available(count);
        vkEnumerateDeviceExtensionProperties(dev, nullptr, &count, available.data());
        std::set<std::string> required(kDeviceExtensions.begin(), kDeviceExtensions.end());
        for (const auto& e : available) required.erase(e.extensionName);
        return required.empty();
    }

    SwapchainSupport querySwapchainSupport(VkPhysicalDevice dev) {
        SwapchainSupport s;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, surface_, &s.capabilities);
        uint32_t fc = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface_, &fc, nullptr);
        s.formats.resize(fc);
        vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface_, &fc, s.formats.data());
        uint32_t pc = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface_, &pc, nullptr);
        s.presentModes.resize(pc);
        vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface_, &pc, s.presentModes.data());
        return s;
    }

    bool deviceSuitable(VkPhysicalDevice dev) {
        if (!findQueueFamilies(dev).complete()) return false;
        if (!checkDeviceExtensions(dev)) return false;
        auto s = querySwapchainSupport(dev);
        return !s.formats.empty() && !s.presentModes.empty();
    }

    void pickPhysicalDevice() {
        uint32_t count = 0;
        vkEnumeratePhysicalDevices(instance_, &count, nullptr);
        if (count == 0) throw std::runtime_error("no Vulkan-capable GPU found");
        std::vector<VkPhysicalDevice> devices(count);
        vkEnumeratePhysicalDevices(instance_, &count, devices.data());

        // Prefer a suitable discrete GPU; fall back to any suitable device.
        VkPhysicalDevice fallback = VK_NULL_HANDLE;
        for (auto dev : devices) {
            if (!deviceSuitable(dev)) continue;
            if (fallback == VK_NULL_HANDLE) fallback = dev;
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(dev, &props);
            if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                physicalDevice_ = dev;
                std::cout << "Using discrete GPU: " << props.deviceName << '\n';
                return;
            }
        }
        if (fallback == VK_NULL_HANDLE) throw std::runtime_error("no suitable GPU");
        physicalDevice_ = fallback;
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(physicalDevice_, &props);
        std::cout << "Using GPU: " << props.deviceName << '\n';
    }

    // ---- logical device -------------------------------------------------
    void createLogicalDevice() {
        QueueFamilyIndices idx = findQueueFamilies(physicalDevice_);
        std::set<uint32_t> uniqueFamilies = { idx.graphics.value(), idx.present.value() };

        std::vector<VkDeviceQueueCreateInfo> queueInfos;
        float priority = 1.0f;
        for (uint32_t fam : uniqueFamilies) {
            VkDeviceQueueCreateInfo qi{};
            qi.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            qi.queueFamilyIndex = fam;
            qi.queueCount = 1;
            qi.pQueuePriorities = &priority;
            queueInfos.push_back(qi);
        }

        VkPhysicalDeviceFeatures features{};

        VkDeviceCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        ci.queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size());
        ci.pQueueCreateInfos = queueInfos.data();
        ci.pEnabledFeatures = &features;
        ci.enabledExtensionCount = static_cast<uint32_t>(kDeviceExtensions.size());
        ci.ppEnabledExtensionNames = kDeviceExtensions.data();
        // Note: device-level layers are deprecated and must not be set.
        // Instance layers (enabled in createInstance) cover the whole device.

        if (vkCreateDevice(physicalDevice_, &ci, nullptr, &device_) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device");
        }
        vkGetDeviceQueue(device_, idx.graphics.value(), 0, &graphicsQueue_);
        vkGetDeviceQueue(device_, idx.present.value(), 0, &presentQueue_);
    }

    // ---- swapchain ------------------------------------------------------
    VkSurfaceFormatKHR chooseFormat(const std::vector<VkSurfaceFormatKHR>& formats) {
        for (const auto& f : formats) {
            if (f.format == VK_FORMAT_B8G8R8A8_SRGB &&
                f.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return f;
            }
        }
        return formats[0];
    }

    VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>& modes) {
        for (auto m : modes) {
            if (m == VK_PRESENT_MODE_MAILBOX_KHR) return m;
        }
        return VK_PRESENT_MODE_FIFO_KHR; // always available
    }

    VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& caps) {
        if (caps.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return caps.currentExtent;
        }
        int w, h;
        glfwGetFramebufferSize(window_, &w, &h);
        VkExtent2D actual{ static_cast<uint32_t>(w), static_cast<uint32_t>(h) };
        actual.width  = std::clamp(actual.width,  caps.minImageExtent.width,  caps.maxImageExtent.width);
        actual.height = std::clamp(actual.height, caps.minImageExtent.height, caps.maxImageExtent.height);
        return actual;
    }

    void createSwapchain() {
        SwapchainSupport s = querySwapchainSupport(physicalDevice_);
        VkSurfaceFormatKHR format = chooseFormat(s.formats);
        VkPresentModeKHR present = choosePresentMode(s.presentModes);
        VkExtent2D extent = chooseExtent(s.capabilities);

        uint32_t imageCount = s.capabilities.minImageCount + 1;
        if (s.capabilities.maxImageCount > 0 && imageCount > s.capabilities.maxImageCount) {
            imageCount = s.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR ci{};
        ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        ci.surface = surface_;
        ci.minImageCount = imageCount;
        ci.imageFormat = format.format;
        ci.imageColorSpace = format.colorSpace;
        ci.imageExtent = extent;
        ci.imageArrayLayers = 1;
        ci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                        VK_IMAGE_USAGE_TRANSFER_SRC_BIT; // allow readback for verification

        QueueFamilyIndices idx = findQueueFamilies(physicalDevice_);
        uint32_t families[] = { idx.graphics.value(), idx.present.value() };
        if (idx.graphics != idx.present) {
            ci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            ci.queueFamilyIndexCount = 2;
            ci.pQueueFamilyIndices = families;
        } else {
            ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }
        ci.preTransform = s.capabilities.currentTransform;
        ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        ci.presentMode = present;
        ci.clipped = VK_TRUE;
        ci.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device_, &ci, nullptr, &swapchain_) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swapchain");
        }

        vkGetSwapchainImagesKHR(device_, swapchain_, &imageCount, nullptr);
        swapchainImages_.resize(imageCount);
        vkGetSwapchainImagesKHR(device_, swapchain_, &imageCount, swapchainImages_.data());
        swapchainFormat_ = format.format;
        swapchainExtent_ = extent;
    }

    void createImageViews() {
        swapchainImageViews_.resize(swapchainImages_.size());
        for (size_t i = 0; i < swapchainImages_.size(); ++i) {
            VkImageViewCreateInfo ci{};
            ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            ci.image = swapchainImages_[i];
            ci.viewType = VK_IMAGE_VIEW_TYPE_2D;
            ci.format = swapchainFormat_;
            ci.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            ci.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            ci.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            ci.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            ci.subresourceRange.levelCount = 1;
            ci.subresourceRange.layerCount = 1;
            if (vkCreateImageView(device_, &ci, nullptr, &swapchainImageViews_[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create image view");
            }
        }
    }

    // ---- render pass ----------------------------------------------------
    void createRenderPass() {
        VkAttachmentDescription color{};
        color.format = swapchainFormat_;
        color.samples = VK_SAMPLE_COUNT_1_BIT;
        color.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        color.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        color.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        color.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        color.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        color.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorRef{};
        colorRef.attachment = 0;
        colorRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorRef;

        VkSubpassDependency dep{};
        dep.srcSubpass = VK_SUBPASS_EXTERNAL;
        dep.dstSubpass = 0;
        dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dep.srcAccessMask = 0;
        dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        ci.attachmentCount = 1;
        ci.pAttachments = &color;
        ci.subpassCount = 1;
        ci.pSubpasses = &subpass;
        ci.dependencyCount = 1;
        ci.pDependencies = &dep;

        if (vkCreateRenderPass(device_, &ci, nullptr, &renderPass_) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass");
        }
    }

    // ---- pipeline -------------------------------------------------------
    VkShaderModule createShaderModule(const std::vector<char>& code) {
        VkShaderModuleCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        ci.codeSize = code.size();
        ci.pCode = reinterpret_cast<const uint32_t*>(code.data());
        VkShaderModule module;
        if (vkCreateShaderModule(device_, &ci, nullptr, &module) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module");
        }
        return module;
    }

    void createGraphicsPipeline() {
        auto vertCode = readFile("shaders/vert.spv");
        auto fragCode = readFile("shaders/frag.spv");
        VkShaderModule vert = createShaderModule(vertCode);
        VkShaderModule frag = createShaderModule(fragCode);

        VkPipelineShaderStageCreateInfo vs{};
        vs.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vs.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vs.module = vert;
        vs.pName = "main";

        VkPipelineShaderStageCreateInfo fs{};
        fs.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fs.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fs.module = frag;
        fs.pName = "main";

        VkPipelineShaderStageCreateInfo stages[] = { vs, fs };

        VkPipelineVertexInputStateCreateInfo vertexInput{};
        vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        VkPipelineInputAssemblyStateCreateInfo inputAsm{};
        inputAsm.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAsm.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.scissorCount = 1;

        VkPipelineRasterizationStateCreateInfo raster{};
        raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        raster.polygonMode = VK_POLYGON_MODE_FILL;
        raster.lineWidth = 1.0f;
        raster.cullMode = VK_CULL_MODE_BACK_BIT;
        raster.frontFace = VK_FRONT_FACE_CLOCKWISE;

        VkPipelineMultisampleStateCreateInfo ms{};
        ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineColorBlendAttachmentState blendAttach{};
        blendAttach.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                     VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        blendAttach.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo blend{};
        blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        blend.attachmentCount = 1;
        blend.pAttachments = &blendAttach;

        std::array<VkDynamicState, 2> dynStates = {
            VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR
        };
        VkPipelineDynamicStateCreateInfo dyn{};
        dyn.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dyn.dynamicStateCount = static_cast<uint32_t>(dynStates.size());
        dyn.pDynamicStates = dynStates.data();

        VkPipelineLayoutCreateInfo layoutCi{};
        layoutCi.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        if (vkCreatePipelineLayout(device_, &layoutCi, nullptr, &pipelineLayout_) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout");
        }

        VkGraphicsPipelineCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        ci.stageCount = 2;
        ci.pStages = stages;
        ci.pVertexInputState = &vertexInput;
        ci.pInputAssemblyState = &inputAsm;
        ci.pViewportState = &viewportState;
        ci.pRasterizationState = &raster;
        ci.pMultisampleState = &ms;
        ci.pColorBlendState = &blend;
        ci.pDynamicState = &dyn;
        ci.layout = pipelineLayout_;
        ci.renderPass = renderPass_;
        ci.subpass = 0;

        if (vkCreateGraphicsPipelines(device_, VK_NULL_HANDLE, 1, &ci, nullptr,
                                      &graphicsPipeline_) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline");
        }

        vkDestroyShaderModule(device_, frag, nullptr);
        vkDestroyShaderModule(device_, vert, nullptr);
    }

    void createFramebuffers() {
        framebuffers_.resize(swapchainImageViews_.size());
        for (size_t i = 0; i < swapchainImageViews_.size(); ++i) {
            VkImageView attachments[] = { swapchainImageViews_[i] };
            VkFramebufferCreateInfo ci{};
            ci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            ci.renderPass = renderPass_;
            ci.attachmentCount = 1;
            ci.pAttachments = attachments;
            ci.width = swapchainExtent_.width;
            ci.height = swapchainExtent_.height;
            ci.layers = 1;
            if (vkCreateFramebuffer(device_, &ci, nullptr, &framebuffers_[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer");
            }
        }
    }

    void createCommandPool() {
        QueueFamilyIndices idx = findQueueFamilies(physicalDevice_);
        VkCommandPoolCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        ci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        ci.queueFamilyIndex = idx.graphics.value();
        if (vkCreateCommandPool(device_, &ci, nullptr, &commandPool_) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool");
        }
    }

    void createCommandBuffers() {
        commandBuffers_.resize(MAX_FRAMES_IN_FLIGHT);
        VkCommandBufferAllocateInfo ai{};
        ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        ai.commandPool = commandPool_;
        ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        ai.commandBufferCount = static_cast<uint32_t>(commandBuffers_.size());
        if (vkAllocateCommandBuffers(device_, &ai, commandBuffers_.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers");
        }
    }

    void recordCommandBuffer(VkCommandBuffer cmd, uint32_t imageIndex) {
        VkCommandBufferBeginInfo begin{};
        begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        vkBeginCommandBuffer(cmd, &begin);

        VkClearValue clear{};
        clear.color = {{0.02f, 0.02f, 0.05f, 1.0f}};

        VkRenderPassBeginInfo rp{};
        rp.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        rp.renderPass = renderPass_;
        rp.framebuffer = framebuffers_[imageIndex];
        rp.renderArea.offset = {0, 0};
        rp.renderArea.extent = swapchainExtent_;
        rp.clearValueCount = 1;
        rp.pClearValues = &clear;

        vkCmdBeginRenderPass(cmd, &rp, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline_);

        VkViewport viewport{};
        viewport.width = static_cast<float>(swapchainExtent_.width);
        viewport.height = static_cast<float>(swapchainExtent_.height);
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(cmd, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.extent = swapchainExtent_;
        vkCmdSetScissor(cmd, 0, 1, &scissor);

        vkCmdDraw(cmd, 3, 1, 0, 0);
        vkCmdEndRenderPass(cmd);

        if (vkEndCommandBuffer(cmd) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer");
        }
    }

    void createSyncObjects() {
        imageAvailable_.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinished_.resize(swapchainImages_.size());   // one per swapchain image
        inFlight_.resize(MAX_FRAMES_IN_FLIGHT);

        VkSemaphoreCreateInfo sci{};
        sci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        VkFenceCreateInfo fci{};
        fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fci.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (auto& sem : renderFinished_) {
            if (vkCreateSemaphore(device_, &sci, nullptr, &sem) != VK_SUCCESS) {
                throw std::runtime_error("failed to create render-finished semaphore");
            }
        }
        for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
            if (vkCreateSemaphore(device_, &sci, nullptr, &imageAvailable_[i]) != VK_SUCCESS ||
                vkCreateFence(device_, &fci, nullptr, &inFlight_[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create sync objects");
            }
        }
    }

    // ---- swapchain recreation ------------------------------------------
    void cleanupSwapchain() {
        for (auto fb : framebuffers_) vkDestroyFramebuffer(device_, fb, nullptr);
        for (auto view : swapchainImageViews_) vkDestroyImageView(device_, view, nullptr);
        vkDestroySwapchainKHR(device_, swapchain_, nullptr);
    }

    void recreateSwapchain() {
        int w = 0, h = 0;
        glfwGetFramebufferSize(window_, &w, &h);
        while (w == 0 || h == 0) {
            glfwGetFramebufferSize(window_, &w, &h);
            glfwWaitEvents();
        }
        vkDeviceWaitIdle(device_);
        cleanupSwapchain();
        // Per-image semaphores must match the (possibly new) image count.
        for (auto sem : renderFinished_) vkDestroySemaphore(device_, sem, nullptr);
        renderFinished_.clear();
        createSwapchain();
        createImageViews();
        createFramebuffers();
        VkSemaphoreCreateInfo sci{};
        sci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        renderFinished_.resize(swapchainImages_.size());
        for (auto& sem : renderFinished_) {
            if (vkCreateSemaphore(device_, &sci, nullptr, &sem) != VK_SUCCESS) {
                throw std::runtime_error("failed to recreate render-finished semaphore");
            }
        }
    }

    // ---- render loop ----------------------------------------------------
    void drawFrame() {
        vkWaitForFences(device_, 1, &inFlight_[currentFrame_], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult acquire = vkAcquireNextImageKHR(
            device_, swapchain_, UINT64_MAX,
            imageAvailable_[currentFrame_], VK_NULL_HANDLE, &imageIndex);
        if (acquire == VK_ERROR_OUT_OF_DATE_KHR) { recreateSwapchain(); return; }
        if (acquire != VK_SUCCESS && acquire != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swapchain image");
        }

        vkResetFences(device_, 1, &inFlight_[currentFrame_]);
        vkResetCommandBuffer(commandBuffers_[currentFrame_], 0);
        recordCommandBuffer(commandBuffers_[currentFrame_], imageIndex);

        VkSubmitInfo submit{};
        submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        VkSemaphore waitSems[] = { imageAvailable_[currentFrame_] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submit.waitSemaphoreCount = 1;
        submit.pWaitSemaphores = waitSems;
        submit.pWaitDstStageMask = waitStages;
        submit.commandBufferCount = 1;
        submit.pCommandBuffers = &commandBuffers_[currentFrame_];
        VkSemaphore signalSems[] = { renderFinished_[imageIndex] };
        submit.signalSemaphoreCount = 1;
        submit.pSignalSemaphores = signalSems;

        if (vkQueueSubmit(graphicsQueue_, 1, &submit, inFlight_[currentFrame_]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer");
        }

        // Optional verification capture: while the image is still acquired
        // (before present), read it back to a PPM. Triggered on a chosen frame.
        if (captureFrameNumber_ >= 0 && framesRendered_ == captureFrameNumber_) {
            vkWaitForFences(device_, 1, &inFlight_[currentFrame_], VK_TRUE, UINT64_MAX);
            captureFrame(imageIndex, capturePath_);
        }

        VkPresentInfoKHR present{};
        present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        present.waitSemaphoreCount = 1;
        present.pWaitSemaphores = signalSems;
        VkSwapchainKHR chains[] = { swapchain_ };
        present.swapchainCount = 1;
        present.pSwapchains = chains;
        present.pImageIndices = &imageIndex;

        VkResult res = vkQueuePresentKHR(presentQueue_, &present);
        if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR || framebufferResized_) {
            framebufferResized_ = false;
            recreateSwapchain();
        } else if (res != VK_SUCCESS) {
            throw std::runtime_error("failed to present swapchain image");
        }

        currentFrame_ = (currentFrame_ + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window_)) {
            glfwPollEvents();
            drawFrame();
            ++framesRendered_;
            if (autoCloseFrames_ >= 0 && framesRendered_ >= autoCloseFrames_) {
                std::cout << "Rendered " << framesRendered_
                          << " frames; auto-closing.\n";
                break;
            }
        }
        vkDeviceWaitIdle(device_);
    }

    // ---- verification: read back the last presented image to a PPM ------
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags props) {
        VkPhysicalDeviceMemoryProperties memProps;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice_, &memProps);
        for (uint32_t i = 0; i < memProps.memoryTypeCount; ++i) {
            if ((typeFilter & (1u << i)) &&
                (memProps.memoryTypes[i].propertyFlags & props) == props) {
                return i;
            }
        }
        throw std::runtime_error("no suitable memory type");
    }

    void captureFrame(uint32_t imageIndex, const std::string& path) {
        const uint32_t w = swapchainExtent_.width;
        const uint32_t h = swapchainExtent_.height;
        const VkDeviceSize size = static_cast<VkDeviceSize>(w) * h * 4;

        // Host-visible destination buffer.
        VkBuffer buffer;
        VkBufferCreateInfo bci{};
        bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bci.size = size;
        bci.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        vkCreateBuffer(device_, &bci, nullptr, &buffer);

        VkMemoryRequirements req;
        vkGetBufferMemoryRequirements(device_, buffer, &req);
        VkMemoryAllocateInfo ai{};
        ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        ai.allocationSize = req.size;
        ai.memoryTypeIndex = findMemoryType(req.memoryTypeBits,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        VkDeviceMemory memory;
        vkAllocateMemory(device_, &ai, nullptr, &memory);
        vkBindBufferMemory(device_, buffer, memory, 0);

        // One-time command buffer: transition image, copy to buffer, transition back.
        VkCommandBufferAllocateInfo cbai{};
        cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cbai.commandPool = commandPool_;
        cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cbai.commandBufferCount = 1;
        VkCommandBuffer cmd;
        vkAllocateCommandBuffers(device_, &cbai, &cmd);

        VkCommandBufferBeginInfo begin{};
        begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkBeginCommandBuffer(cmd, &begin);

        VkImage srcImage = swapchainImages_[imageIndex];

        auto barrier = [&](VkImageLayout oldL, VkImageLayout newL,
                           VkAccessFlags srcA, VkAccessFlags dstA,
                           VkPipelineStageFlags srcS, VkPipelineStageFlags dstS) {
            VkImageMemoryBarrier b{};
            b.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
            b.oldLayout = oldL;
            b.newLayout = newL;
            b.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            b.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            b.image = srcImage;
            b.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            b.subresourceRange.levelCount = 1;
            b.subresourceRange.layerCount = 1;
            b.srcAccessMask = srcA;
            b.dstAccessMask = dstA;
            vkCmdPipelineBarrier(cmd, srcS, dstS, 0, 0, nullptr, 0, nullptr, 1, &b);
        };

        barrier(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                VK_ACCESS_MEMORY_READ_BIT, VK_ACCESS_TRANSFER_READ_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);

        VkBufferImageCopy region{};
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.layerCount = 1;
        region.imageExtent = { w, h, 1 };
        vkCmdCopyImageToBuffer(cmd, srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                               buffer, 1, &region);

        barrier(VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                VK_ACCESS_TRANSFER_READ_BIT, VK_ACCESS_MEMORY_READ_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);

        vkEndCommandBuffer(cmd);

        VkSubmitInfo submit{};
        submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit.commandBufferCount = 1;
        submit.pCommandBuffers = &cmd;
        vkQueueSubmit(graphicsQueue_, 1, &submit, VK_NULL_HANDLE);
        vkQueueWaitIdle(graphicsQueue_);
        vkFreeCommandBuffers(device_, commandPool_, 1, &cmd);

        // Map and write a PPM (swapchain is BGRA; swap B/R when writing).
        void* mapped = nullptr;
        vkMapMemory(device_, memory, 0, size, 0, &mapped);
        const uint8_t* pixels = static_cast<const uint8_t*>(mapped);

        std::ofstream out(path, std::ios::binary);
        out << "P6\n" << w << ' ' << h << "\n255\n";
        // Background clear color is dark (~ (5,5,13) in sRGB8). Count pixels that
        // are clearly part of the colored triangle, and sample known regions.
        long trianglePixels = 0;
        // Background clears to sRGB8 ~(39,39,63). Treat pixels close to that as
        // background; anything clearly different is part of the colored triangle.
        auto isBackground = [](int r, int g, int b) {
            return std::abs(r - 39) <= 12 && std::abs(g - 39) <= 12 && std::abs(b - 63) <= 12;
        };
        for (uint32_t i = 0; i < w * h; ++i) {
            int b = pixels[i * 4 + 0];
            int g = pixels[i * 4 + 1];
            int r = pixels[i * 4 + 2];
            out.put(static_cast<char>(r));
            out.put(static_cast<char>(g));
            out.put(static_cast<char>(b));
            if (!isBackground(r, g, b)) ++trianglePixels;
        }
        out.close();

        auto sample = [&](uint32_t x, uint32_t y) {
            uint32_t idx = (y * w + x) * 4;
            return std::to_string(pixels[idx + 2]) + "," +
                   std::to_string(pixels[idx + 1]) + "," +
                   std::to_string(pixels[idx + 0]); // r,g,b
        };
        std::cout << "Capture samples (r,g,b): "
                  << "center=" << sample(w / 2, h / 2) << " "
                  << "topCorner=" << sample(10, 10) << " "
                  << "botLeftTri=" << sample(w / 4, h * 3 / 4) << " "
                  << "botRightTri=" << sample(w * 3 / 4, h * 3 / 4) << '\n';
        vkUnmapMemory(device_, memory);
        vkDestroyBuffer(device_, buffer, nullptr);
        vkFreeMemory(device_, memory, nullptr);

        std::cout << "Captured " << path << " (" << w << "x" << h
                  << "), triangle (non-background) pixels = " << trianglePixels << '\n';
    }

    // ---- cleanup --------------------------------------------------------
    void cleanup() {
        cleanupSwapchain();
        vkDestroyPipeline(device_, graphicsPipeline_, nullptr);
        vkDestroyPipelineLayout(device_, pipelineLayout_, nullptr);
        vkDestroyRenderPass(device_, renderPass_, nullptr);
        for (auto sem : renderFinished_) {
            vkDestroySemaphore(device_, sem, nullptr);
        }
        for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
            vkDestroySemaphore(device_, imageAvailable_[i], nullptr);
            vkDestroyFence(device_, inFlight_[i], nullptr);
        }
        vkDestroyCommandPool(device_, commandPool_, nullptr);
        vkDestroyDevice(device_, nullptr);
        if (kEnableValidation) {
            destroyDebugUtilsMessengerEXT(instance_, debugMessenger_, nullptr);
        }
        vkDestroySurfaceKHR(instance_, surface_, nullptr);
        vkDestroyInstance(instance_, nullptr);
        glfwDestroyWindow(window_);
        glfwTerminate();
    }
};

int main() {
    TriangleApp app;
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    std::cout << "Clean exit.\n";
    return EXIT_SUCCESS;
}

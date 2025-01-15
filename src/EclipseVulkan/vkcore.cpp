// true -> SUCCESS
// false -> FAILURE

#include "vkcore.hpp"

evk::evko evkos{};


uint32_t evk::select_physical_device(std::vector<VkPhysicalDevice> _physical_devices) {
	// Loop through all devices
	for (uint32_t i = 0; i < _physical_devices.size(); i++) {
		// Get Device Property
		VkPhysicalDeviceProperties physical_device_properties{};
		vkGetPhysicalDeviceProperties(_physical_devices[i], &physical_device_properties);

		if (physical_device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) return i;
	}

	return 0;
}

// Initialized Vulkan Instance
void evk::init_instance() {
	// Initialize Volk
	if (volkInitialize() != VK_SUCCESS)
		io::printErrorAndExit("Failed to intialize Vulkan!");

	// Check for Debug and enable extensions if required
#ifndef NDEBUG
	evkos.validationLayers.push_back("VK_LAYER_KHRONOS_validation");
#endif

	// Application Info
	VkApplicationInfo application_info{};
	application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	application_info.pEngineName = "Eclipse Engine";
	application_info.pApplicationName = "Eclipse Engine";
	application_info.applicationVersion = VK_MAKE_VERSION(1, 1, 1);
	application_info.engineVersion = VK_MAKE_VERSION(1, 1, 1);
	application_info.apiVersion = volkGetInstanceVersion();

	// Instance Info
	VkInstanceCreateInfo instance_create_info{};
	instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_create_info.pNext = nullptr;
	instance_create_info.flags = 0;
	instance_create_info.pApplicationInfo = &application_info;
	instance_create_info.enabledLayerCount = static_cast<uint32_t>(evkos.validationLayers.size());
	instance_create_info.ppEnabledLayerNames = evkos.validationLayers.data();
	instance_create_info.enabledExtensionCount = 0;
	instance_create_info.ppEnabledExtensionNames = nullptr;

	if (vkCreateInstance(&instance_create_info, nullptr, &evkos.instance) != VK_SUCCESS)
		io::printErrorAndExit("Failed to create vulkan instance!");

	io::printDebug("Vulkan Instance Created!");

	volkLoadInstance(evkos.instance);
}

void evk::init_physical_devices() {
    // Query Physical Devices
    uint32_t physical_device_count;
    vkEnumeratePhysicalDevices(evkos.instance, &physical_device_count, nullptr);
    if (physical_device_count == 0) {
        io::printErrorAndExit("No physical devices found!");
    }

    std::vector<VkPhysicalDevice> physical_devices(physical_device_count);
    vkEnumeratePhysicalDevices(evkos.instance, &physical_device_count, physical_devices.data());

    // Choose a device
    evkos.physicalDevice = physical_devices[select_physical_device(physical_devices)];

    // Get Device Properties
    VkPhysicalDeviceProperties physical_device_properties;
    vkGetPhysicalDeviceProperties(evkos.physicalDevice, &physical_device_properties);

    // Display Properties [DEBUG ONLY]
    std::string device_type = (physical_device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) ? "Discrete GPU" :
        (physical_device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) ? "Integrated GPU" : "CPU";
    std::string device_api_version = fmt::format("{}.{}.{}", VK_VERSION_MAJOR(physical_device_properties.apiVersion),
        VK_VERSION_MINOR(physical_device_properties.apiVersion),
        VK_VERSION_PATCH(physical_device_properties.apiVersion));
    io::printDebug("Physical Device Selected: {}", physical_device_properties.deviceName);
    io::printDebug("Device Type: {}", device_type);
    io::printDebug("Device API Version: {}", device_api_version);

    // Get Queue Families
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(evkos.physicalDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(evkos.physicalDevice, &queueFamilyCount, queueFamilies.data());

    // Find a queue family that supports graphics
    uint32_t graphicsQueueFamilyIndex = -1;
    for (uint32_t i = 0; i < queueFamilyCount; i++) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            graphicsQueueFamilyIndex = i;
            break;
        }
    }
    if (graphicsQueueFamilyIndex == -1) {
        io::printErrorAndExit("Failed to find a graphics queue family!");
    }

    evkos.graphicsQueueFamilyIndex = graphicsQueueFamilyIndex;

    // Queue Create Info
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo device_queue_create_info{};
    device_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    device_queue_create_info.queueFamilyIndex = evkos.graphicsQueueFamilyIndex;
    device_queue_create_info.queueCount = 1;
    device_queue_create_info.pQueuePriorities = &queuePriority;

    // Device Create Info
    VkDeviceCreateInfo device_create_info{};
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.queueCreateInfoCount = 1;
    device_create_info.pQueueCreateInfos = &device_queue_create_info;
    device_create_info.enabledExtensionCount = 0;
    device_create_info.ppEnabledExtensionNames = nullptr;
    device_create_info.pEnabledFeatures = nullptr;

    if (vkCreateDevice(evkos.physicalDevice, &device_create_info, nullptr, &evkos.device) != VK_SUCCESS) {
        io::printErrorAndExit("Failed to initialize Device!");
    }

    volkLoadDevice(evkos.device);

    vkGetDeviceQueue(evkos.device, evkos.graphicsQueueFamilyIndex, 0, &evkos.graphicsQueue);

    io::printDebug("Created Logical Device!");
}
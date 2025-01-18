#pragma once

#include <volk.h>
#include <vulkan/vulkan.h>
#include <IO.hpp>
#include <vector>

namespace evk {
	struct evko {
		std::vector<const char*> validationLayers;
		VkInstance instance;
		VkPhysicalDevice physicalDevice;
		VkDevice device;
		uint32_t graphicsQueueFamilyIndex;
		VkQueue graphicsQueue;
	};

	uint32_t select_physical_device(std::vector<VkPhysicalDevice> _physical_devices);

	void init_instance();
	void init_physical_devices();

	void cleanup();
};
#include "Initializers.h"

VkApplicationInfo Initializers::ApplicationInfo(VulkanConfiguration& config)
{
	VkApplicationInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.pApplicationName = config.application_name;
	info.pEngineName = config.engine_name;
	info.applicationVersion = config.application_version;
	info.engineVersion = config.engine_version;
	info.apiVersion = config.api_version;

	return info;
}

VkInstanceCreateInfo Initializers::InstanceCreateInfo(VkApplicationInfo& app_info, std::vector<const char*> layers, std::vector<const char*> extensions)
{
	VkInstanceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	//ignore pNext and flags for now
	info.pApplicationInfo = &app_info;
	info.enabledExtensionCount = extensions.size();
	info.enabledLayerCount = layers.size();
	info.ppEnabledExtensionNames = extensions.data(); // rets a pts to beginning of arr
	info.ppEnabledLayerNames = layers.data(); // rets a pts to beginning of arr

	return info;
}

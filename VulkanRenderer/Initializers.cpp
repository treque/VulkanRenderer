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

VkDeviceQueueCreateInfo Initializers::DeviceQueueCreate(uint32_t queue_family_index, float& priority)
{
	VkDeviceQueueCreateInfo queue_create_info{};
	queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_create_info.queueFamilyIndex = queue_family_index;
	queue_create_info.queueCount = 1;
	queue_create_info.pQueuePriorities = &priority;

	return queue_create_info;
}

VkDeviceCreateInfo Initializers::DeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queue_create_infos, VkPhysicalDeviceFeatures& device_features)
{
	VkDeviceCreateInfo create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	create_info.pQueueCreateInfos = queue_create_infos.data();
	create_info.queueCreateInfoCount = (uint32_t)queue_create_infos.size();
	create_info.pEnabledFeatures = &device_features;
	
	return create_info;
}

VkCommandPoolCreateInfo Initializers::CommandPoolCreateInfo(uint32_t queue_family_index, VkCommandPoolCreateFlags flags)
{
	VkCommandPoolCreateInfo pool_info{};
	pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pool_info.queueFamilyIndex = queue_family_index;
	pool_info.flags = flags; 

	return pool_info;
}

VkCommandBufferAllocateInfo Initializers::CommandBufferAllocateInfo(VkCommandPool pool, uint32_t count)
{
	VkCommandBufferAllocateInfo alloc_info{};
	alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc_info.commandPool = pool;
	alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	alloc_info.commandBufferCount = count;

	return alloc_info;
}

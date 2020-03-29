#include "VulkanInstance.h"

VulkanInstance::VulkanInstance(VulkanConfiguration& vulkan_config)
{
	VkApplicationInfo application_info = Initializers::ApplicationInfo(vulkan_config);

	VkInstanceCreateInfo instance_info = Initializers::InstanceCreateInfo(application_info, layers, extensions);

	ErrorCheck(vkCreateInstance(&instance_info, NULL, &instance));
}

VulkanInstance::~VulkanInstance()
{
	vkDestroyInstance(instance, NULL);
}

VkInstance& VulkanInstance::GetInstance()
{
	return instance;
}

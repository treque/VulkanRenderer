#include "BUILD_ORDER.h"

VulkanInstance* instance;
VulkanPhysicalDevice* physical_device;
VulkanDevice* device;
int main()
{
	VulkanConfiguration vulkan_config;
	vulkan_config.application_name = "Vulkan Renderer";
	vulkan_config.application_version = VK_MAKE_VERSION(1, 0, 0);

	instance = new VulkanInstance(vulkan_config);
	// your gpu
	physical_device = VulkanPhysicalDevice::GetPhysicalDevice(instance);
	// the device that contains the gpu
	device = new VulkanDevice(instance, physical_device);

	VkCommandBuffer* commands = new VkCommandBuffer[3];
	device->GetComputeCommand(commands, 3);

	device->FreeComputeCommand(commands, 3);
	delete device;
	delete physical_device;
	delete instance;

	return 0;
}
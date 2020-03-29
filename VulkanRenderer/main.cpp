#include "BUILD_ORDER.h"

VulkanInstance* instance;

int main()
{
	VulkanConfiguration vulkan_config;
	vulkan_config.application_name = "Vulkan Renderer";
	vulkan_config.application_version = VK_MAKE_VERSION(1, 0, 0);

	instance = new VulkanInstance(vulkan_config);
	delete instance;

	return 0;
}
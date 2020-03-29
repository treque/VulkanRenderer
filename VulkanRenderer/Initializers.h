#pragma once
#include "BUILD_ORDER.h"

namespace Initializers
{
	VkApplicationInfo ApplicationInfo(VulkanConfiguration &config);

	VkInstanceCreateInfo InstanceCreateInfo(VkApplicationInfo& app_info, std::vector<const char*> layers, std::vector<const char*> extensions);
}
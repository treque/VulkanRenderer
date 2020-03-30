#pragma once
#include "BUILD_ORDER.h"

class VulkanInstance; // promise that it is impremented. weirdly the linker does not include it first

class VulkanPhysicalDevice
{
public:
	~VulkanPhysicalDevice();

	VkPhysicalDevice& GetPhysicalDevice();
	QueueFamilyIndices& GetQueueFamilyIndices();
	VkPhysicalDeviceProperties& GetPhysicalDeviceProperties();
	VkPhysicalDeviceFeatures& GetPhysicalDeviceFeatures();
	VkPhysicalDeviceMemoryProperties& GetPhysicalDeviceMemoryProperties();

	static VulkanPhysicalDevice* GetPhysicalDevice(VulkanInstance* instance);

private:
	VulkanPhysicalDevice(VulkanInstance* instance, VkPhysicalDevice device, QueueFamilyIndices indices);
	static std::vector<VkPhysicalDevice> GetAvailablePhysicalDevices(VulkanInstance* instance);
	static bool PhysicalDeviceSupported(VkPhysicalDevice& device, QueueFamilyIndices& family_indices);
	static bool SupportsQueueFamily(VkPhysicalDevice& device, QueueFamilyIndices& family_indices);

	VulkanInstance* m_instance;
	VkPhysicalDevice m_device;
	QueueFamilyIndices m_family_indices;
	// things describing whta the gpu can store and whatnot
	VkPhysicalDeviceProperties m_physical_device_properties;
	VkPhysicalDeviceFeatures m_physical_device_features;
	VkPhysicalDeviceMemoryProperties m_physical_device_memory_properties;
};
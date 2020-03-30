#pragma once

#include "BUILD_ORDER.h"

class VulkanPhysicalDevice;

class VulkanDevice
{
public:
	VulkanDevice(VulkanInstance* instance, VulkanPhysicalDevice* physical_device);
	
	VulkanInstance* GetInstance();
	VkDevice* GetDevice();
	VkQueue* GetComputeQueue();

	VkCommandPool GetComputeCommandPool();
	void GetComputeCommand(VkCommandBuffer* buffers, uint32_t count);
	void FreeComputeCommand(VkCommandBuffer* buffers, uint32_t count);

	~VulkanDevice();


private:
	VulkanInstance* m_instance;
	VkDevice m_device;
	VulkanPhysicalDevice* m_vulkan_physical_device;
	VkQueue m_compute_queue;

	VkCommandPool m_compute_command_pool;
};
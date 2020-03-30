#include "VulkanDevice.h"

VulkanDevice::VulkanDevice(VulkanInstance* instance, VulkanPhysicalDevice* physical_device)
{
	m_instance = instance;
	m_vulkan_physical_device = physical_device;

	std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
	float priority = 1.0f;
	queue_create_infos.push_back(Initializers::DeviceQueueCreate(m_vulkan_physical_device->GetQueueFamilyIndices().compute_indices, priority));

	VkDeviceCreateInfo create_info = Initializers::DeviceCreateInfo(queue_create_infos, m_vulkan_physical_device->GetPhysicalDeviceFeatures());

	ErrorCheck(vkCreateDevice(m_vulkan_physical_device->GetPhysicalDevice(), &create_info, nullptr, &m_device));

	vkGetDeviceQueue(m_device, m_vulkan_physical_device->GetQueueFamilyIndices().compute_indices, 0, &m_compute_queue);

	VkCommandPoolCreateInfo compute_pool_info = Initializers::CommandPoolCreateInfo(m_vulkan_physical_device->GetQueueFamilyIndices().compute_indices);
	ErrorCheck(vkCreateCommandPool(m_device, &compute_pool_info, nullptr, &m_compute_command_pool));
}

VulkanInstance* VulkanDevice::GetInstance()
{
	return m_instance;
}

VkDevice* VulkanDevice::GetDevice()
{
	return &m_device;
}

VkQueue* VulkanDevice::GetComputeQueue()
{
	return &m_compute_queue;
}

VkCommandPool VulkanDevice::GetComputeCommandPool()
{
	return m_compute_command_pool;
}

void VulkanDevice::GetComputeCommand(VkCommandBuffer* buffers, uint32_t count)
{
	VkCommandBufferAllocateInfo command_buffer_allocate_info = Initializers::CommandBufferAllocateInfo(m_compute_command_pool, count);

	ErrorCheck(vkAllocateCommandBuffers(m_device, &command_buffer_allocate_info, buffers));

}

void VulkanDevice::FreeComputeCommand(VkCommandBuffer* buffers, uint32_t count)
{
	vkFreeCommandBuffers(m_device, m_compute_command_pool, count, buffers);
}

VulkanDevice::~VulkanDevice()
{
	vkDestroyCommandPool(m_device, m_compute_command_pool, nullptr);

	vkDestroyDevice(m_device, nullptr);
}

#include "VulkanPhysicalDevice.h"

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance* instance, VkPhysicalDevice device, QueueFamilyIndices indices)
{
	m_instance = instance;
	m_device = device;
	m_family_indices = indices;

	vkGetPhysicalDeviceProperties(m_device, &m_physical_device_properties);
	vkGetPhysicalDeviceFeatures(m_device, &m_physical_device_features);
	vkGetPhysicalDeviceMemoryProperties(m_device, &m_physical_device_memory_properties);
}

std::vector<VkPhysicalDevice> VulkanPhysicalDevice::GetAvailablePhysicalDevices(VulkanInstance* instance)
{
	uint32_t device_count = 0;
	// it will figure out how many gpus are in the computer and write it in device count
	vkEnumeratePhysicalDevices(instance->GetInstance(), &device_count, nullptr);

	std::vector<VkPhysicalDevice> devices(device_count);
	vkEnumeratePhysicalDevices(instance->GetInstance(), &device_count, devices.data());

	return devices;
}

bool VulkanPhysicalDevice::PhysicalDeviceSupported(VkPhysicalDevice& device, QueueFamilyIndices& family_indices)
{
	bool supportsQueueFamily = SupportsQueueFamily(device, family_indices);
	
	return supportsQueueFamily;
}

bool VulkanPhysicalDevice::SupportsQueueFamily(VkPhysicalDevice& device, QueueFamilyIndices& family_indices)
{
	uint32_t queue_family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

	std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);

	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());


	uint32_t i = 0;
	for (auto& queue_family : queue_families)
	{
		if (queue_family.queueCount > 0)
		{
			// check if graphics is supported
			if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				family_indices.graphics_indices = i;
			}
			//check if compute is supported
			if (queue_family.queueFlags & VK_QUEUE_COMPUTE_BIT)
			{
				family_indices.compute_indices = i;
			}
		}
		if (family_indices.graphics_indices < UINT32_MAX && family_indices.compute_indices < UINT32_MAX)
		{
			// this means data must have been set to them
			return true;
		}

		i++;
	}
	return false;
}

VulkanPhysicalDevice* VulkanPhysicalDevice::GetPhysicalDevice(VulkanInstance* instance)
{
	std::vector<VkPhysicalDevice> devices = GetAvailablePhysicalDevices(instance);

	VkPhysicalDevice secondary_device = VK_NULL_HANDLE;
	QueueFamilyIndices secondary_queue;

	for (auto& device : devices)
	{
		QueueFamilyIndices queue_family;
		if (PhysicalDeviceSupported(device, queue_family))
		{
			// is it an integrated or physical.  if we discover an integrated card, cache it first
			// then if we don't discover a physical one, then we use the integrated card.
			VkPhysicalDeviceProperties physical_device_properties;
			vkGetPhysicalDeviceProperties(device, &physical_device_properties); // on s'interesse a devicetype

			if (physical_device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				return new VulkanPhysicalDevice(instance, device, queue_family);
			}
			else // cache it if supported and not external
			{
				secondary_device = device;
				secondary_queue = queue_family;
			}
		}
	}

	if (secondary_device == VK_NULL_HANDLE)
	{
		return nullptr;
	}
	else
	{
		return new VulkanPhysicalDevice(instance, secondary_device, secondary_queue);
	}
}

VkPhysicalDevice& VulkanPhysicalDevice::GetPhysicalDevice()
{
	return m_device;
}

QueueFamilyIndices& VulkanPhysicalDevice::GetQueueFamilyIndices()
{
	return m_family_indices;
}

VkPhysicalDeviceProperties& VulkanPhysicalDevice::GetPhysicalDeviceProperties()
{
	return m_physical_device_properties;
}

VkPhysicalDeviceFeatures& VulkanPhysicalDevice::GetPhysicalDeviceFeatures()
{
	return m_physical_device_features;
}

VkPhysicalDeviceMemoryProperties& VulkanPhysicalDevice::GetPhysicalDeviceMemoryProperties()
{
	return m_physical_device_memory_properties;
}

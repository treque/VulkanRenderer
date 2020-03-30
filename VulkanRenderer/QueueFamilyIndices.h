#pragma once
#include "BUILD_ORDER.h"

// compute q family, present q family.. etc
struct QueueFamilyIndices
{
	uint32_t graphics_indices = UINT32_MAX;
	uint32_t compute_indices = UINT32_MAX;
};
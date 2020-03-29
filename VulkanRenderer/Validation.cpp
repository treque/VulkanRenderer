#include "Validation.h"

void ErrorCheck(VkResult res)
{
	if (res != VK_SUCCESS)
	{
		std::cout << "Error" << std::endl;
		std::cout << res << std::endl;
		assert(0 && "There was an error");
	}
}

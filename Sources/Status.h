#ifndef Rx__VkStatusH
#define Rx__VkStatusH

#include <vulkan/vk_enum_string_helper.h>

#define RxStatus_FromVk(r) string_VkResult(r)

#define RxStatus_NoValidation "(Rx) validation layers not supported"

#endif

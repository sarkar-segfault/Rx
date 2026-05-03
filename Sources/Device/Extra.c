#include "Extra.h"  // IWYU pragma: associated

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "../Status.h"

RxStatus RxDevice_ValidationSupported(void) {
#ifndef NDEBUG
  uint32_t count = 0;
  VkResult result = vkEnumerateInstanceLayerProperties(&count, NULL);

  if (result != VK_SUCCESS) return RxStatus_FromVk(result);

  VkLayerProperties *props = calloc(count, sizeof(VkLayerProperties));
  if (!props) return RxStatus_AllocFailed;

  result = vkEnumerateInstanceLayerProperties(&count, props);
  if (result != VK_SUCCESS) return RxStatus_FromVk(result);

  for (uint32_t i = 0; i < count; i++) {
    if (!strcmp(props[i].layerName, "VK_LAYER_KHRONOS_validation")) return RxStatus_Pass;
  }
#endif

  return RxStatus_NoValidation;
}

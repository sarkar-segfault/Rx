#include "Rx/Device.h"  // IWYU pragma: associated

#include <vulkan/vulkan.h>
#include <stdlib.h>

#include "Rx/Status.h"

struct RxDevice {
  VkInstance instance;
  RxDeviceSpec spec;
};

RxStatus RxDevice_Create(RxDevice **device, const RxDeviceSpec spec) {
  if (!device) return RxStatus_BadInput;

  *device = calloc(1, sizeof(RxDevice));
  if (!*device) return RxStatus_AllocFailed;

  VkApplicationInfo appinfo = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = spec.name ? spec.name : "Rx",
    .applicationVersion = VK_MAKE_VERSION(spec.major, spec.minor, spec.micro),
    .pEngineName = "Rx",
    .engineVersion = VK_MAKE_VERSION(Rx_VersionMajor, Rx_VersionMinor, Rx_VersionMicro),
    .apiVersion = VK_API_VERSION_1_0,
  };

  const char *extensions[] = {
    "VK_KHR_surface",
    "VK_KHR_swapchain",
    #ifdef _WIN32
    "VK_KHR_win32_surface",
    #endif
    #ifndef NDEBUG
    "VK_LAYER_KHRONOS_validation"
    #endif
  };

  VkInstanceCreateInfo instinfo = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pApplicationInfo = &appinfo,
    .ppEnabledExtensionNames = extensions,
    .enabledExtensionCount = sizeof(extensions) / sizeof(extensions[0])
  };

  if (vkCreateInstance(&instinfo, NULL, &(*device)->instance) != VK_SUCCESS) {
    RxDevice_Delete(device);
    return RxStatus_Pass;
  }

  return RxStatus_Pass;
}

RxStatus RxDevice_GetSpec(const RxDevice *device, RxDeviceSpec *spec);

RxStatus RxDevice_Delete(RxDevice **device);

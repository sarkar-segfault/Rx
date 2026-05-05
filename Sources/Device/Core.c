#include <stdlib.h>
#include <vulkan/vulkan.h>

#include "../Status.h"
#include "Extra.h"
#include "Rx/Device.h"  // IWYU pragma: associated
#include "Rx/Status.h"

struct RxDevice {
  VkInstance instance;
  RxDeviceSpec spec;
};

RxStatus RxDevice_Create(RxDevice **device, const RxDeviceSpec spec) {
  if (!device) return RxStatus_BadInput;

  *device = calloc(1, sizeof(RxDevice));
  if (!*device) return RxStatus_AllocFailed;

  (*device)->spec = spec;

  VkApplicationInfo appinfo = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pApplicationName = spec.name ? spec.name : "Rx",
      .applicationVersion = VK_MAKE_VERSION(spec.major, spec.minor, spec.micro),
      .pEngineName = "Rx",
      .engineVersion = VK_MAKE_VERSION(Rx_VersionMajor, Rx_VersionMinor, Rx_VersionMicro),
      .apiVersion = VK_API_VERSION_1_0,
  };

  const char *extensions[] = {"VK_KHR_surface",
#ifdef _WIN32
                              "VK_KHR_win32_surface"
#endif
  };

  VkInstanceCreateInfo instinfo = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = &appinfo,
      .ppEnabledExtensionNames = extensions,
      .enabledExtensionCount = sizeof(extensions) / sizeof(extensions[0]),
  };

  if (RxDevice_ValidationSupported() == RxStatus_Pass) {
    const char *layers[] = {"VK_LAYER_KHRONOS_validation"};
    instinfo.enabledLayerCount = sizeof(layers) / sizeof(layers[0]);
    instinfo.ppEnabledLayerNames = layers;
  }

  VkResult result = vkCreateInstance(&instinfo, NULL, &(*device)->instance);
  if (result != VK_SUCCESS) {
    RxDevice_Delete(device);
    return RxStatus_FromVk(result);
  }

  return RxStatus_Pass;
}

RxStatus RxDevice_GetSpec(const RxDevice *device, RxDeviceSpec *spec) {
  if (!device || !spec) return RxStatus_BadInput;

  *spec = device->spec;
  return RxStatus_Pass;
}

RxStatus RxDevice_Delete(RxDevice **device) {
  if (!device || !(*device)) return RxStatus_BadInput;
  RxStatus s = RxStatus_Pass;

  if (!(*device)->instance) {
    s = RxStatus_BadInput;
  } else
    vkDestroyInstance((*device)->instance, NULL);

  free(*device);
  *device = NULL;

  return s;
}

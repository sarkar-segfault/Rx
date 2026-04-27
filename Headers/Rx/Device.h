#ifndef Rx__DeviceH
#define Rx__DeviceH

#include <stdint.h>
#include "_Expose.h"
#include "Status.h"
#include <stdbool.h>

typedef struct RxDevice RxDevice;

typedef struct RxDeviceSpec {
  uint8_t egl_major; // 0 == any
  uint8_t egl_minor; // 0 == any

  uint8_t depth_bits;
  uint8_t stencil_bits;

  uint8_t msaa;
} RxDeviceSpec;

#define RxDeviceSpec_Default ((RxDeviceSpec){0})

Rx__Expose RxStatus RxDevice_Create(RxDevice **device, const RxDeviceSpec spec);

Rx__Expose RxStatus RxDevice_GetDisplay(const RxDevice *device, const void **display);

Rx__Expose RxStatus RxDevice_GetSpec(const RxDevice *device, RxDeviceSpec *spec);

Rx__Expose RxStatus RxDevice_Delete(RxDevice **device);

#endif

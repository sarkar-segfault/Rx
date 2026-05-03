#ifndef Rx__DeviceH
#define Rx__DeviceH

#include <stdbool.h>
#include <stdint.h>

#include "Status.h"
#include "_Expose.h"

typedef struct RxDevice RxDevice;

typedef struct RxDeviceSpec {
  const char *name;
  uint8_t major, minor, micro;
} RxDeviceSpec;

#define RxDeviceSpec_Default ((RxDeviceSpec){.name = "Rx"})

Rx__Expose RxStatus RxDevice_Create(RxDevice **device, const RxDeviceSpec spec);

Rx__Expose RxStatus RxDevice_GetSpec(const RxDevice *device, RxDeviceSpec *spec);

Rx__Expose RxStatus RxDevice_Delete(RxDevice **device);

#endif

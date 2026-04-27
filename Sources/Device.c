#include "Rx/Device.h"  // IWYU pragma: associated

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <stdlib.h>

#include "Rx/Status.h"

struct RxDevice {
  EGLDisplay display;
  EGLConfig config;
  RxDeviceSpec spec;
};

RxStatus RxDevice_Create(RxDevice **device, const RxDeviceSpec spec) {
  if (!device) return RxStatus_BadInput;

  *device = calloc(1, sizeof(RxDevice));
  if (!*device) return RxStatus_AllocFailed;
  (*device)->spec = spec;

  (*device)->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if ((*device)->display == EGL_NO_DISPLAY) {
    RxDevice_Delete(device);
    return RxStatus_GraphicsFail;
  }

  EGLint major, minor;
  if (!eglInitialize((*device)->display, &major, &minor)) {
    RxDevice_Delete(device);
    return RxStatus_GraphicsFail;
  }

  if ((spec.egl_major != 0 && spec.egl_major != major) ||
      (spec.egl_minor != 0 && spec.egl_minor != minor)) {
    RxDevice_Delete(device);
    return RxStatus_Unsatisfied;
  }

  EGLint config[] = {EGL_RENDERABLE_TYPE,
                     EGL_OPENGL_ES2_BIT,

                     EGL_SURFACE_TYPE,
                     EGL_WINDOW_BIT,

                     EGL_RED_SIZE,
                     8,

                     EGL_GREEN_SIZE,
                     8,

                     EGL_BLUE_SIZE,
                     8,

                     EGL_ALPHA_SIZE,
                     8,

                     EGL_DEPTH_SIZE,
                     spec.depth_bits == 0 ? EGL_DONT_CARE : spec.depth_bits,

                     EGL_STENCIL_SIZE,
                     spec.stencil_bits == 0 ? EGL_DONT_CARE : spec.stencil_bits,

                     EGL_SAMPLE_BUFFERS,
                     spec.msaa == 0 ? EGL_DONT_CARE : 1,

                     EGL_SAMPLES,
                     spec.msaa == 0 ? EGL_DONT_CARE : spec.msaa,

                     EGL_NONE};

  EGLint configs;
  if (!eglChooseConfig((*device)->display, config, &(*device)->config, 1, &configs) ||
      configs == 0) {
    RxDevice_Delete(device);
    return RxStatus_Unsatisfied;
  }

  return RxStatus_Pass;
}

RxStatus RxDevice_GetDisplay(const RxDevice *device, const void **display) {
  if (!device || !display) return RxStatus_BadInput;

  *display = device->display;
  return RxStatus_Pass;
}

RxStatus RxDevice_GetSpec(const RxDevice *device, RxDeviceSpec *spec) {
  if (!device || !spec) return RxStatus_BadInput;

  *spec = device->spec;
  return RxStatus_Pass;
}

RxStatus RxDevice_Delete(RxDevice **device) {
  if (!device || !*device) return RxStatus_BadInput;
  RxStatus s = RxStatus_Pass;

  if (!eglTerminate((*device)->display)) s = RxStatus_GraphicsFail;

  free(*device);
  *device = NULL;

  return s;
}

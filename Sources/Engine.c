#include "Rx/Engine.h"  // IWYU pragma: associated

#include <EGL/egl.h>
#include <stdlib.h>

#include "Rx/Status.h"

struct RxEngine {
  EGLDisplay display;
};

RxStatus RxEngine_Create(RxEngine **engine, void *display) {
  if (!display) return RxStatus_BadInput;

  *engine = calloc(1, sizeof(struct RxEngine));
  if (!*engine) return RxStatus_AllocFailed;

  (*engine)->display = display;
  return RxStatus_Pass;
}

RxStatus RxEngine_Delete(RxEngine **engine) {
  if (!engine || !*engine) return RxStatus_BadInput;

  free(*engine);
  *engine = NULL;

  return RxStatus_Pass;
}

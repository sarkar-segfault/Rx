#ifndef Rx__EngineH
#define Rx__EngineH

#include "Status.h"
#include "_Expose.h"

typedef struct RxEngine RxEngine;

Rx__Expose RxStatus RxEngine_Create(RxEngine **engine, void *display);

Rx__Expose RxStatus RxEngine_Delete(RxEngine **engine);

#endif

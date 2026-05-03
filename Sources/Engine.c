#include "Rx/Engine.h"  // IWYU pragma: associated

#include <stdlib.h>

#include "Rx/Status.h"

struct RxEngine;

RxStatus RxEngine_Create(RxEngine **engine, void *display);

RxStatus RxEngine_Delete(RxEngine **engine);

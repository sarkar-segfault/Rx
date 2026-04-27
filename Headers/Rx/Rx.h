#ifndef Rx__H
#define Rx__H

// IWYU pragma: begin_exports
#include "Device.h"
#include "Engine.h"
#include "Status.h"

// IWYU pragma: end_exports

#ifdef NDEBUG
  #define Rx_DebugCheck(s, v)
#else
  #include <stdio.h>  // IWYU pragma: export
  #define Rx_DebugCheck(s, v)         \
    s = v;                       \
    if (s != RxStatus_Pass) {    \
      puts(RxStatus_Strings[s]); \
    }
#endif

#endif

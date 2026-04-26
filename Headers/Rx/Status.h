#ifndef Rx__StatusH
#define Rx__StatusH

#include "_Expose.h"

typedef enum RxStatus { RxStatus_BadInput, RxStatus_AllocFailed, RxStatus_Pass } RxStatus;

Rx__Expose const char *const RxStatus_Strings[RxStatus_Pass];

#endif

#ifndef Rx__StatusH
#define Rx__StatusH

typedef const char *RxStatus;

#define RxStatus_AllocFailed "(Rx) failed to allocate memory"
#define RxStatus_NoEvents "(Rx) no events to pop from ring"
#define RxStatus_BadInput "(Rx) called with bad arguments"
#define RxStatus_Pass NULL

#ifdef NDEBUG
  #define RxStatus_Debug(s, v) s = v;
#else
  #include <stdio.h>  // IWYU pragma: export
  #define Rx_StatusDebug(s, v) \
    s = v;                     \
    puts(RxStatus_Strings[s]);
#endif

#endif

#include "Rx/Status.h" // IWYU pragma: associated

const char *const RxStatus_Strings[RxStatus_Pass] = {
  "called with invalid parameters",
  "failed to allocate object",
  "encountered graphics-related failure",
  "could not satisfy device specification"
};

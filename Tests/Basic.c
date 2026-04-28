#include <stddef.h>
#include <stdio.h>

#include "Vx/Vx.h"
#include "Rx/Rx.h"

int main(void) {
  VxStatus vs;
  RxStatus rs;

  VxContext context;

  Vx_DebugCheck(vs, VxContext_Create(&context));
  VxWindow *window;

  Vx_DebugCheck(vs, VxWindow_Create(&window, context, VxFlag_Visible));
  VxEvent event;

  RxDevice *device;
  Rx_DebugCheck(rs, RxDevice_Create(&device, RxDeviceSpec_Default));

  while (VxWindow_IsOpen(window)) {
    Vx_DebugCheck(vs, VxWindow_PollEvents(window));

    while (VxWindow_PopEvent(window, &event)) {
      switch (event.type) {
        case VxEventType_Close:
          printf("Close\n");
          Vx_DebugCheck(vs, VxWindow_Close(window));
          goto terminate;

        case VxEventType_Resize:
          printf("Resize: %u x %u\n", event.info.size.w, event.info.size.h);
          break;

        case VxEventType_Move:
          printf("Move: %d, %d\n", event.info.pos.x, event.info.pos.y);
          break;

        case VxEventType_Focus:
          printf("Focus gained\n");
          break;

        case VxEventType_Blur:
          printf("Focus lost\n");
          break;

        case VxEventType_Show:
          printf("Window shown\n");
          break;

        case VxEventType_Hide:
          printf("Window hidden\n");
          break;

        case VxEventType_Minimize:
          printf("Minimized\n");
          break;

        case VxEventType_Maximize:
          printf("Maximized\n");
          break;

        case VxEventType_KeyPress:
          printf("Key press: %d (mod: %u)\n", event.info.press.key, event.info.press.mod);
          break;

        case VxEventType_KeyRelease:
          printf("Key release: %d\n", event.info.release);
          break;

        case VxEventType_CharSent:
          printf("Char: %c\n", event.info.sent);
          break;

        case VxEventType_MouseMove:
          printf("Mouse move: %d, %d\n", event.info.pos.x, event.info.pos.y);
          break;

        case VxEventType_MousePress:
          printf("Mouse press: %d\n", event.info.button);
          break;

        case VxEventType_MouseRelease:
          printf("Mouse release: %d\n", event.info.button);
          break;

        case VxEventType_MouseWheel:
          printf("Mouse wheel: %d\n", event.info.delta);
          break;

        case VxEventType_Empty:
          printf("Empty");
          break;

        default:
          printf("Unknown event\n");
          break;
      }
    }
  }

terminate:
  Rx_DebugCheck(rs, RxDevice_Delete(&device));

  Vx_DebugCheck(vs, VxWindow_Delete(&window));
  Vx_DebugCheck(vs, VxContext_Delete(&context));
  return 0;
}

#include <stddef.h>
#include <stdio.h>

#include "Vx/Vx.h"
#include "Rx/Rx.h"

int main(void) {
  VxStatus vs;
  RxStatus rs;

  VxHandle handle;

  VxStatus_Debug(vs, VxHandle_Create(&handle));
  VxWindow *window;

  VxStatus_Debug(vs, VxWindow_Create(&window, handle, VxFlag_Visible));
  VxEvent event;

  RxDevice *device;
  RxStatus_Debug(rs, RxDevice_Create(&device, RxDeviceSpec_Default));

  while (VxWindow_IsOpen(window)) {
    VxStatus_Debug(vs, VxWindow_PollEvents(window));

    while (VxWindow_PopEvent(window, &event) == VxStatus_Pass) {
      switch (event.type) {
        case VxEventType_Close:
          printf("Close\n");
          VxStatus_Debug(vs, VxWindow_Close(window));
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
          printf("Key press: %d (mod: %u)\n", event.info.press.key, event.info.press.mods);
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
  RxStatus_Debug(rs, RxDevice_Delete(&device));

  VxStatus_Debug(vs, VxWindow_Delete(&window));
  VxStatus_Debug(vs, VxHandle_Delete(&handle));
  return 0;
}

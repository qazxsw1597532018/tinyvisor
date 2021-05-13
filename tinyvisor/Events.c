#include "Events.h"

extern EFI_BOOT_SERVICES* gBS;

EFI_EVENT gExitBsEvent = NULL;
EFI_EVENT gSetVaMapEvent = NULL;

VOID NotificationExitBootServices(EFI_EVENT Event, VOID* Context) {
}

VOID NotificationSetVaMap(EFI_EVENT Event, VOID* Context) {
}

EFI_STATUS InitializeEfiEvents() {
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_CHECK(gBS->CreateEvent(EVT_SIGNAL_EXIT_BOOT_SERVICES, TPL_NOTIFY, NotificationExitBootServices, NULL,
                               &gExitBsEvent));
    EFI_CHECK(gBS->CreateEvent(EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE, TPL_NOTIFY, NotificationSetVaMap, NULL,
                               &gSetVaMapEvent));

Cleanup:
    if (Status != EFI_SUCCESS) {
        if (gExitBsEvent) {
            gBS->CloseEvent(gExitBsEvent);
        }

        if (gSetVaMapEvent) {
            gBS->CloseEvent(gSetVaMapEvent);
        }
    }

    return Status;
}

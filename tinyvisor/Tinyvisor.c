#include <Uefi.h>

#include "MemoryManager.h"
#include "Interrupts.h"
#include "Events.h"
#include "Paging.h"
#include "Mtrr.h"
#include "Log.h"
#include "Vmx.h"
#include "Mp.h"

EFI_STATUS EfiMain(EFI_HANDLE Handle, EFI_SYSTEM_TABLE* SystemTable) {
    EFI_STATUS Status = EFI_SUCCESS;
    SetImageParameters(Handle, SystemTable);
    EFI_CHECK(InitializeLogging());
    LOG("Setting up EFI event callbacks...");
    EFI_CHECK(InitializeEfiEvents());
    LOG("Initializing multiprocessing...");
    EFI_CHECK(InitializeMp());
    LOG("Initializing the memory manager...");
    EFI_CHECK(InitializeMemoryManager());
    LOG("Initializing host page tables...");
    InitializeHostPageTables();
    LOG("Initializing host IDT...");
    InitializeHostIdt();
    LOG("Initializing MTRR info...");
    InitializeMtrrInfo();
    LOG("Checking if VMX can be used...");
    EFI_CHECK(IsVmxAvailable());
    LOG("Initialized!");

Cleanup:
    return Status;
}

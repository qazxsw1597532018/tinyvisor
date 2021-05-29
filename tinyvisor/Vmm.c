#include "Vmm.h"
#include "Mp.h"
#include "MemoryManager.h"

EFI_STATUS EnableVmmOnAllProcessors() {
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN ProcessorCount = 0;
    EFI_CHECK(GetProcessorCount(&ProcessorCount));

Cleanup:
    return Status;
}

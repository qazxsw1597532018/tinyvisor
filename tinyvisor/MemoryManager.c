#include "MemoryManager.h"
#include "Mp.h"

#define POOL_SIZE(ProcessorCount) (ProcessorCount * (512 + 64))

extern EFI_BOOT_SERVICES* gBS;

BOOLEAN gMemoryManagerInitialized = FALSE;
VOID* gMemoryManagerBase = NULL;
UINTN gMemoryManagerPageCount = 0;
UINT8* gBitmapBase = NULL;
UINTN gBitmapSize = 0;
SPIN_LOCK gMemoryManagerSpinLock = 0;

EFI_STATUS InitializeMemoryManager() {
    EFI_STATUS Status = EFI_SUCCESS;
    if (gMemoryManagerInitialized) {
        EFI_FAIL(EFI_NOT_READY);
    }

    UINTN ProcessorCount = 0;
    EFI_CHECK(GetProcessorCount(&ProcessorCount));

    EFI_PHYSICAL_ADDRESS AllocationAddress = 0;
    gMemoryManagerPageCount = POOL_SIZE(ProcessorCount);
    EFI_CHECK(gBS->AllocatePages(AllocateAnyPages, EfiRuntimeServicesData, gMemoryManagerPageCount,
                                 &AllocationAddress));
    gMemoryManagerBase = (VOID*)AllocationAddress;
    memset(gMemoryManagerBase, 0, gMemoryManagerPageCount * EFI_PAGE_SIZE);

    AllocationAddress = 0;
    gBitmapSize = (gMemoryManagerPageCount / 8) + ((gMemoryManagerPageCount % 8) ? 1 : 0);
    EFI_CHECK(gBS->AllocatePages(AllocateAnyPages, EfiRuntimeServicesData, EFI_SIZE_TO_PAGES(gBitmapSize),
                                 &AllocationAddress));
    gBitmapBase = (UINT8*)AllocationAddress;
    memset(gBitmapBase, 0, gBitmapSize);

    EFI_CHECK(InitializeSpinLock(&gMemoryManagerSpinLock));
    gMemoryManagerInitialized = TRUE;

Cleanup:
    if (Status != EFI_SUCCESS) {
        if (gBitmapBase) {
            gBS->FreePages((EFI_PHYSICAL_ADDRESS)gBitmapBase, EFI_SIZE_TO_PAGES(gBitmapSize));
        }

        if (gMemoryManagerBase) {
            gBS->FreePages((EFI_PHYSICAL_ADDRESS)gMemoryManagerBase, gMemoryManagerPageCount);
        }
    }

    return Status;
}

EFI_STATUS AllocatePages(UINT32 Count, VOID** Result) {
    EFI_STATUS Status = EFI_SUCCESS;
    if (!Count) {
        EFI_FAIL(EFI_INVALID_PARAMETER);
    }

    EFI_CHECK(AcquireSpinLock(&gMemoryManagerSpinLock));
    BOOLEAN Found = FALSE;
    UINTN PageIndex = 0;
    for (UINTN OuterIndex = 0; OuterIndex < gBitmapSize; OuterIndex++) {
        UINT32 InnerIndex = 0;
        for (; InnerIndex < Count; InnerIndex++) {
            PageIndex = (OuterIndex * 8) + InnerIndex;
            UINT8 Byte = gBitmapBase[PageIndex / 8];
            if (Byte & (1 << (PageIndex % 8))) {
                break;
            }
        }

        if (InnerIndex == Count) {
            Found = TRUE;
            break;
        }
    }

    if (!Found) {
        EFI_FAIL(EFI_OUT_OF_RESOURCES);
    }

    *Result = (VOID*)(((UINT8*)gMemoryManagerBase) + PageIndex);
    for (UINTN Index = 0; Index < (Count / 8); Index++) {
        gBitmapBase[PageIndex + Index] = 0xff;
        PageIndex++;
    }

    for (UINT32 Index = 0; Index < (Count % 8); Index++) {
        gBitmapBase[PageIndex] |= (1 << Index);
    }

Cleanup:
    ReleaseSpinLock(&gMemoryManagerSpinLock);
    return Status;
}

EFI_STATUS FreePages(VOID* Address, UINT32 Count) {
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_CHECK(ReleaseSpinLock(&gMemoryManagerSpinLock));

    UINTN PageIndex = Address - gMemoryManagerBase;
    for (UINTN Index = 0; Index < (Count / 8); Index++) {
        gBitmapBase[PageIndex + Index] = 0;
        PageIndex++;
    }

    gBitmapBase[PageIndex] = (gBitmapBase[PageIndex] >> (Count % 8)) << (Count % 8);

Cleanup:
    ReleaseSpinLock(&gMemoryManagerSpinLock);
    return Status;
}

#include "Mp.h"
#include "Intrinsics.h"

extern EFI_BOOT_SERVICES* gBS;

EFI_MP_SERVICES_PROTOCOL* gMpServicesProtocol = NULL;

EFI_STATUS InitializeSpinLock(SPIN_LOCK* SpinLock) {
    EFI_STATUS Status = EFI_SUCCESS;
    if (!SpinLock) {
        EFI_FAIL(EFI_INVALID_PARAMETER);
    }

    __memory_fence();
    *SpinLock = SPIN_LOCK_RELEASED;
    __memory_fence();

Cleanup:
    return Status;
}

EFI_STATUS AcquireSpinLock(SPIN_LOCK* SpinLock) {
    EFI_STATUS Status = EFI_SUCCESS;
    if (!SpinLock || *SpinLock != SPIN_LOCK_RELEASED) {
        EFI_FAIL(EFI_INVALID_PARAMETER);
    }

    __memory_fence();
    __lock_cmp_xchg8b(SpinLock, SPIN_LOCK_RELEASED, SPIN_LOCK_ACQUIRED);
    while (*SpinLock != SPIN_LOCK_ACQUIRED) {
        __cpu_pause();
        __lock_cmp_xchg8b(SpinLock, SPIN_LOCK_RELEASED, SPIN_LOCK_ACQUIRED);
    }
    __memory_fence();

Cleanup:
    return Status;
}

EFI_STATUS ReleaseSpinLock(SPIN_LOCK* SpinLock) {
    EFI_STATUS Status = EFI_SUCCESS;
    if (!SpinLock || *SpinLock != SPIN_LOCK_ACQUIRED) {
        EFI_FAIL(EFI_INVALID_PARAMETER);
    }

    __memory_fence();
    *SpinLock = SPIN_LOCK_RELEASED;
    __memory_fence();

Cleanup:
    return Status;
}

EFI_STATUS InitializeMp() {
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_GUID MpServiceProtocolGuid = EFI_MP_SERVICES_PROTOCOL_GUID;
    EFI_CHECK(gBS->LocateProtocol(&MpServiceProtocolGuid, NULL, (VOID**)&gMpServicesProtocol));

Cleanup:
    return Status;
}

EFI_STATUS GetCurrentProcessorId(UINTN* Id) {
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_CHECK(gMpServicesProtocol->WhoAmI(gMpServicesProtocol, Id));

Cleanup:
    return Status;
}

EFI_STATUS GetProcessorCount(UINTN* Count) {
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN TotalCount = 0;
    EFI_CHECK(gMpServicesProtocol->GetNumberOfProcessors(gMpServicesProtocol, &TotalCount, Count));

Cleanup:
    return Status;
}
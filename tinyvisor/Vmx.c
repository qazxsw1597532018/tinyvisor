#include "Vmx.h"
#include "Intrinsics.h"
#include "Cpuid.h"
#include "Mp.h"
#include "Msr.h"

EFI_STATUS IsVmxAvailable() {
    EFI_STATUS Status = EFI_SUCCESS;
    UINT32 Registers[4] = { 0 };

    __cpuid(Registers, CPUID_LEAF_NAME);
    if (Registers[1] != CPUID_GENUINEINTEL_EBX || Registers[2] != CPUID_GENUINEINTEL_ECX || Registers[3] !=
        CPUID_GENUINEINTEL_EDX) {
        EFI_FAIL(EFI_UNSUPPORTED);
    }

    __cpuid(Registers, CPUID_LEAF_FEATURES);
    if (!(Registers[2] & CPUID_FEATURE_ECX_VMX)) {
        EFI_FAIL(EFI_UNSUPPORTED);
    }

    IA32_FEATURE_CONTROL_MSR Ia32FeatureControlMsr = { .Packed = __readmsr(MSR_IA32_FEATURE_CONTROL) };
    if (!Ia32FeatureControlMsr.EnableVmxon || !Ia32FeatureControlMsr.Lock) {
        EFI_FAIL(EFI_UNSUPPORTED);
    }

    IA32_VMX_BASIC_MSR Ia32VmxBasicMsr = { .Packed = __readmsr(MSR_IA32_VMX_BASIC) };
    if (Ia32VmxBasicMsr.MemoryType != MSR_IA32_VMX_BASIC_MEMORY_TYPE_WRITE_BACK) {
        EFI_FAIL(EFI_UNSUPPORTED);
    }

    IA32_VMX_EPT_VPID_CAP_MSR Ia32VmxEptVpidCapMsr = { .Packed = __readmsr(MSR_IA32_VMX_EPT_VPID_CAP) };
    if (!Ia32VmxEptVpidCapMsr.PageWalkLength4 ||
        !Ia32VmxEptVpidCapMsr.MemoryTypeWriteBack ||
        !Ia32VmxEptVpidCapMsr.Pde2MbPages ||
        !Ia32VmxEptVpidCapMsr.Invept ||
        !Ia32VmxEptVpidCapMsr.InveptSingleContext ||
        !Ia32VmxEptVpidCapMsr.InveptAllContexts ||
        !Ia32VmxEptVpidCapMsr.Invvpid ||
        !Ia32VmxEptVpidCapMsr.InvvpidSingleContext ||
        !Ia32VmxEptVpidCapMsr.InvvpidAllContexts) {
        EFI_FAIL(EFI_UNSUPPORTED);
    }

    IA32_VMX_MISC_MSR Ia32VmxMiscMsr = { .Packed = __readmsr(MSR_IA32_VMX_MISC) };
    if (!Ia32VmxMiscMsr.StoreEferLmaOnVmExit) {
        EFI_FAIL(EFI_UNSUPPORTED);
    }

    UINTN CurrentProcessorId = 0;
    UINTN ProcessorCount = 0;
    EFI_CHECK(GetCurrentProcessorId(&CurrentProcessorId));
    EFI_CHECK(GetProcessorCount(&ProcessorCount));
    if (CurrentProcessorId == 0 && ProcessorCount > 1 &&
        (Ia32VmxMiscMsr.ActivityStates & MSR_IA32_VMX_BASIC_ACTIVITY_STATE_WAIT_FOR_SIPI)) {
        /**
         * KVM fails here due to it not supporting activity state 3 (Wait-for-SIPI).
         * If you wish to run this on KVM, set your VM to have a single core.
         */
        EFI_FAIL(EFI_UNSUPPORTED);
    }

Cleanup:
    return Status;
}

VOID AdjustCrs() {
    UINT64 Cr = __readcr0();
    Cr &= __readmsr(MSR_IA32_VMX_CR0_FIXED1);
    Cr |= __readmsr(MSR_IA32_VMX_CR0_FIXED0);
    __writecr0(Cr);

    Cr = __readcr4();
    Cr &= __readmsr(MSR_IA32_VMX_CR4_FIXED1);
    Cr |= __readmsr(MSR_IA32_VMX_CR4_FIXED0);
    __writecr4(Cr);
}

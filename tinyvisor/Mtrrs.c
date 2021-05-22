#include "Mtrrs.h"
#include "Msr.h"
#include "Intrinsics.h"

typedef struct _MTRR_RANGE {
    BOOLEAN Fixed;
    IA32_MEMORY_TYPE Type;
    EFI_PHYSICAL_ADDRESS Base;
    EFI_PHYSICAL_ADDRESS End;
} MTRR_RANGE;

struct {
    IA32_MEMORY_TYPE DefaultMemoryType;
    MTRR_RANGE Ranges[IA32_MTRR_COUNT];
} gMtrrInfo;

typedef struct _FIXED_MTRR_RANGE {
    IA32_MSR_ADDRESS Msr;
    EFI_PHYSICAL_ADDRESS Base;
    EFI_PHYSICAL_ADDRESS Size;
} FIXED_MTRR_RANGE;

static CONST FIXED_MTRR_RANGE FIXED_MTRR_RANGE_INFO[] = {
    { MSR_IA32_MTRR_FIX64K_00000, 0x0, 0x10000, },
    { MSR_IA32_MTRR_FIX16K_80000, 0x80000, 0x4000, },
    { MSR_IA32_MTRR_FIX16K_A0000, 0xa0000, 0x4000, },
    { MSR_IA32_MTRR_FIX4K_C0000, 0xc0000, 0x1000, },
    { MSR_IA32_MTRR_FIX4K_C8000, 0xc8000, 0x1000, },
    { MSR_IA32_MTRR_FIX4K_D0000, 0xd0000, 0x1000, },
    { MSR_IA32_MTRR_FIX4K_D8000, 0xd8000, 0x1000, },
    { MSR_IA32_MTRR_FIX4K_E0000, 0xe0000, 0x1000, },
    { MSR_IA32_MTRR_FIX4K_E8000, 0xe8000, 0x1000, },
    { MSR_IA32_MTRR_FIX4K_F0000, 0xf0000, 0x1000, },
    { MSR_IA32_MTRR_FIX4K_F8000, 0xf8000, 0x1000, },
};

VOID InitializeMtrrInfo() {
    IA32_MTRR_DEF_TYPE_REGISTER DefaultMemoryTypeRegister = {
        .Packed = __readmsr(MSR_IA32_MTRR_DEF_TYPE)
    };

    IA32_MTRR_CAPABILITIES_REGISTER MtrrCapabilitiesRegister = {
        .Packed = __readmsr(MSR_IA32_MTRR_CAPABILITIES)
    };

    if (MtrrCapabilitiesRegister.FixedRangeSupported && DefaultMemoryTypeRegister.FixedRangeMtrrEnable) {
        for (UINT32 i = 0; i < COUNT_OF(FIXED_MTRR_RANGE_INFO); i++) {
            IA32_MTRR_FIXED_RANGE_REGISTER FixedRange = {
                .Packed = __readmsr(FIXED_MTRR_RANGE_INFO[i].Msr)
            };

            // TODO: Finish implementation
        }
    }
}

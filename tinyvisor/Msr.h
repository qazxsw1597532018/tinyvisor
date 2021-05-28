#ifndef _TINYVISOR_MSR_H
#define _TINYVISOR_MSR_H

/*******************************
 * Definitions related to MSRs *
 *******************************/

typedef UINT32 IA32_MSR_ADDRESS;

#define MSR_IA32_FEATURE_CONTROL 0x3a
#define MSR_IA32_VMX_BASIC 0x480
#define MSR_IA32_VMX_MISC 0x485
#define MSR_IA32_VMX_CR0_FIXED0 0x486
#define MSR_IA32_VMX_CR0_FIXED1 0x487
#define MSR_IA32_VMX_CR4_FIXED0 0x488
#define MSR_IA32_VMX_CR4_FIXED1 0x489
#define MSR_IA32_VMX_EPT_VPID_CAP 0x48c

#define MSR_IA32_MTRR_FIX64K_BASE 0x
#define MSR_IA32_MTRR_FIX64K_SIZE 0x10000
#define MSR_IA32_MTRR_FIX64K_00000 0x250

#define MSR_IA32_MTRR_FIX16K_BASE 0x80000
#define MSR_IA32_MTRR_FIX16K_SIZE 0x4000
#define MSR_IA32_MTRR_FIX16K_80000 0x258
#define MSR_IA32_MTRR_FIX16K_A0000 0x259

#define MSR_IA32_MTRR_FIX4K_BASE 0xc0000
#define MSR_IA32_MTRR_FIX4K_SIZE 0x1000
#define MSR_IA32_MTRR_FIX4K_C0000 0x268
#define MSR_IA32_MTRR_FIX4K_C8000 0x269
#define MSR_IA32_MTRR_FIX4K_D0000 0x26a
#define MSR_IA32_MTRR_FIX4K_D8000 0x26b
#define MSR_IA32_MTRR_FIX4K_E0000 0x26c
#define MSR_IA32_MTRR_FIX4K_E8000 0x26d
#define MSR_IA32_MTRR_FIX4K_F0000 0x26e
#define MSR_IA32_MTRR_FIX4K_F8000 0x26f

#define MSR_IA32_MTRR_DEF_TYPE 0x2ff
#define MSR_IA32_MTRR_CAPABILITIES 0xfe

#define MSR_IA32_MTRR_PHYSMASK0 0x201
#define MSR_IA32_MTRR_PHYSMASK1 0x203
#define MSR_IA32_MTRR_PHYSMASK2 0x205
#define MSR_IA32_MTRR_PHYSMASK3 0x207
#define MSR_IA32_MTRR_PHYSMASK4 0x209
#define MSR_IA32_MTRR_PHYSMASK5 0x20b
#define MSR_IA32_MTRR_PHYSMASK6 0x20d
#define MSR_IA32_MTRR_PHYSMASK7 0x20f
#define MSR_IA32_MTRR_PHYSMASK8 0x211
#define MSR_IA32_MTRR_PHYSMASK9 0x213

#define MSR_IA32_MTRR_PHYSBASE0 0x200
#define MSR_IA32_MTRR_PHYSBASE1 0x202
#define MSR_IA32_MTRR_PHYSBASE2 0x204
#define MSR_IA32_MTRR_PHYSBASE3 0x206
#define MSR_IA32_MTRR_PHYSBASE4 0x208
#define MSR_IA32_MTRR_PHYSBASE5 0x20a
#define MSR_IA32_MTRR_PHYSBASE6 0x20c
#define MSR_IA32_MTRR_PHYSBASE7 0x20e
#define MSR_IA32_MTRR_PHYSBASE8 0x210
#define MSR_IA32_MTRR_PHYSBASE9 0x212

typedef union _IA32_FEATURE_CONTROL_MSR {
    struct {
        UINT64 Lock : 1;
        UINT64 EnableSmx : 1;
        UINT64 EnableVmxon : 1;
        UINT64 Reserved0 : 5;
        UINT64 EnableLocalSEnter : 7;
        UINT64 EnableGlobalSEnter : 1;
        UINT64 Reserved1 : 16;
        UINT64 Reserved2 : 32;
    };

    UINT64 Packed;
} IA32_FEATURE_CONTROL_MSR;

#define MSR_IA32_VMX_BASIC_MEMORY_TYPE_WRITE_BACK 6

typedef union _IA32_VMX_BASIC_MSR {
    struct {
        UINT64 VmcsRevisionId : 31;
        UINT64 Reserved1 : 1;
        UINT64 VmcsSizeInBytes : 13;
        UINT64 Reserved2 : 3;
        UINT64 VmcsPhysicalAddressWidth : 1;
        UINT64 DualMonitorSupport : 1;
        UINT64 MemoryType : 4;
        UINT64 InsOutsReporting : 1;
        UINT64 VmxControls : 1;
        UINT64 Reserved3 : 8;
    };

    UINT64 Packed;
} IA32_VMX_BASIC_MSR;

#define MSR_IA32_VMX_BASIC_ACTIVITY_STATE_WAIT_FOR_SIPI (1 << 2)

typedef union _IA32_VMX_MISC_MSR {
    struct {
        UINT64 PreemptionTimerTscRelationship : 5;
        UINT64 StoreEferLmaOnVmExit : 1;
        UINT64 ActivityStates : 3;
        UINT64 Reserved1 : 5;
        UINT64 IntelPtAvailableInVmx : 1;
        UINT64 RdmsrCanReadIa32SmbaseMsrInSmm : 1;
        UINT64 Cr3TargetCount : 9;
        UINT64 MaxNumberOfMsr : 3;
        UINT64 SmmMonitorCtlB2 : 1;
        UINT64 VmwriteVmexitInfo : 1;
        UINT64 ZeroLengthInstructionVmentryInjection : 1;
        UINT64 Reserved2 : 1;
        UINT64 MsegId : 32;
    };

    UINT64 Packed;
} IA32_VMX_MISC_MSR;

typedef union _IA32_VMX_EPT_VPID_CAP_MSR {
    struct {
        UINT64 ExecuteOnlyPages : 1;
        UINT64 Reserved1 : 5;
        UINT64 PageWalkLength4 : 1;
        UINT64 Reserved2 : 1;
        UINT64 MemoryTypeUncacheable : 1;
        UINT64 Reserved3 : 5;
        UINT64 MemoryTypeWriteBack : 1;
        UINT64 Reserved4 : 1;
        UINT64 Pde2MbPages : 1;
        UINT64 Pdpte1GbPages : 1;
        UINT64 Reserved5 : 2;
        UINT64 Invept : 1;
        UINT64 EptAccessedAndDirtyFlags : 1;
        UINT64 AdvancedVmexitEptViolationsInformation : 1;
        UINT64 Reserved6 : 2;
        UINT64 InveptSingleContext : 1;
        UINT64 InveptAllContexts : 1;
        UINT64 Reserved7 : 5;
        UINT64 Invvpid : 1;
        UINT64 Reserved8 : 7;
        UINT64 InvvpidIndividualAddress : 1;
        UINT64 InvvpidSingleContext : 1;
        UINT64 InvvpidAllContexts : 1;
        UINT64 InvvpidSingleContextRetainGlobals : 1;
        UINT64 Reserved9 : 20;
    };

    UINT64 Packed;
} IA32_VMX_EPT_VPID_CAP_MSR;
typedef union _IA32_MTRR_DEF_TYPE_REGISTER {
    struct {
        UINT64 DefaultMemoryType : 3;
        UINT64 Reserved1 : 7;
        UINT64 FixedRangeMtrrEnable : 1;
        UINT64 MtrrEnable : 1;
        UINT64 Reserved2 : 52;
    };

    UINT64 Packed;
} IA32_MTRR_DEF_TYPE_REGISTER;

typedef union _IA32_MTRR_CAPABILITIES_REGISTER {
    struct {
        UINT64 VariableRangeCount : 8;
        UINT64 FixedRangeSupported : 1;
        UINT64 Reserved1 : 1;
        UINT64 WcSupported : 1;
        UINT64 SmrrSupported : 1;
        UINT64 Reserved2 : 52;
    };

    UINT64 Packed;
} IA32_MTRR_CAPABILITIES_REGISTER;

typedef union _IA32_MTRR_FIXED_RANGE_REGISTER {
    struct {
        UINT8 Types[8];
    };
    
    UINT64 Packed;
} IA32_MTRR_FIXED_RANGE_REGISTER;

typedef union _IA32_MTRR_PHYSMASK_MSR {
    struct {
        UINT64 Type                                                    : 8;
        UINT64 Reserved1                                               : 3;
        UINT64 Valid                                                   : 1;
        UINT64 PageFrameNumber                                         : 36;
        UINT64 Reserved2                                               : 16;
    };

    UINT64 Packed;
} IA32_MTRR_PHYSMASK_MSR;

typedef union _IA32_MTRR_PHYSBASE_MSR {
    struct {
        UINT64 Type                                                    : 8;
        UINT64 Reserved1                                               : 4;
        UINT64 PageFrameNumber                                         : 36;
        UINT64 Reserved2                                               : 16;
    };
    
    UINT64 Packed;
} IA32_MTRR_PHYSBASE_MSR;

#endif // _TINYVISOR_MSR_H

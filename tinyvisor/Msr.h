#ifndef _TINYVISOR_MSR_H
#define _TINYVISOR_MSR_H

/*******************************
 * Definitions related to MSRs *
 *******************************/

#define MSR_IA32_FEATURE_CONTROL 0x3a
#define MSR_IA32_VMX_BASIC 0x480
#define MSR_IA32_VMX_MISC 0x485
#define MSR_IA32_VMX_CR0_FIXED0 0x486
#define MSR_IA32_VMX_CR0_FIXED1 0x487
#define MSR_IA32_VMX_CR4_FIXED0 0x488
#define MSR_IA32_VMX_CR4_FIXED1 0x489
#define MSR_IA32_VMX_EPT_VPID_CAP 0x48c

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

#endif // _TINYVISOR_MSR_H

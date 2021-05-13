#ifndef TINYVISOR_INTERRUPTS_H
#define TINYVISOR_INTERRUPTS_H

#include <Uefi.h>

#define IDT_ENTRY_COUNT 256

typedef struct _IDT_ENTRY {
    UINT16 PointerLow;
    UINT16 SegmentSelector;
    UINT8 Reserved0;
    UINT8 GateType;
    UINT16 PointerMiddle;
    UINT32 PointerHigh;
    UINT32 Reserved1;
} IDT_ENTRY;

static_assert(sizeof(IDT_ENTRY) == 16, "Bad IDT_ENTRY size");

/**
 * Initializes the IDT that will be used in VMX root operation during runtime
 */
VOID InitializeHostIdt();

#endif // _TINYVISOR_INTERRUPTS_H

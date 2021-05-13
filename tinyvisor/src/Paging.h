#ifndef _TINYVISOR_PAGING_H
#define _TINYVISOR_PAGING_H

#include <Uefi.h>

#define PAGE_ENTRIES_PER_TABLE 512

typedef union _PAGE_TABLE_ENTRY {
    struct {
        UINT64 Present : 1;
        UINT64 Writable : 1;
        UINT64 Supervisor : 1;
        UINT64 WriteThrough : 1;
        UINT64 CacheDisable : 1;
        UINT64 Accessed : 1;
        UINT64 Dirty : 1;
        UINT64 Large : 1;
        UINT64 Global : 1;
        UINT64 Reserved0 : 3;
        UINT64 Address : 40;
        UINT64 Reserved1 : 11;
        UINT64 Nx : 1;
    };

    UINT64 Packed;
} PAGE_TABLE_ENTRY;

typedef union _VIRTUAL_ADDRESS {
    struct {
        UINT64 Offset : 12;
        UINT64 PtIndex : 9;
        UINT64 PdIndex : 9;
        UINT64 PdptIndex : 9;
        UINT64 Pml4Index : 9;
        UINT64 Reserved : 16;
    } Normal;

    struct {
        UINT64 Offset : 21;
        UINT64 PdIndex : 9;
        UINT64 PdptIndex : 9;
        UINT64 Pml4Index : 9;
        UINT64 Reserved : 16;
    } Large;

    struct {
        UINT64 Offset : 30;
        UINT64 PdptIndex : 9;
        UINT64 Pml4Index : 9;
        UINT64 Reserved : 16;
    } Huge;

    UINT64 Packed;
} VIRTUAL_ADDRESS;

typedef struct _HOST_PAGE_TABLES {
    __attribute__((aligned(EFI_PAGE_SIZE))) PAGE_TABLE_ENTRY Pml4[PAGE_ENTRIES_PER_TABLE];
    __attribute__((aligned(EFI_PAGE_SIZE))) PAGE_TABLE_ENTRY Pdpt[1][PAGE_ENTRIES_PER_TABLE];
    __attribute__((aligned(EFI_PAGE_SIZE))) PAGE_TABLE_ENTRY Pd[1][PAGE_ENTRIES_PER_TABLE][PAGE_ENTRIES_PER_TABLE];
} HOST_PAGE_TABLES;

/**
 * Initializes page tables for the host during runtime
 */
VOID InitializeHostPageTables();

#endif // _TINYVISOR_PAGING_H

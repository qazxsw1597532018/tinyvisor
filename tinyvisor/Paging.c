#include "Paging.h"
#include "Utils.h"

HOST_PAGE_TABLES gHostPageTables;

VOID InitializeHostPageTables() {
    // Zero out the structure, so that all PTEs are invalid by default
    memset(&gHostPageTables, 0, sizeof(gHostPageTables));

    // We only care about the first PML4E, as it maps 512GB of memory, which is way more than enough
    gHostPageTables.Pml4[0].Present = TRUE;
    gHostPageTables.Pml4[0].Writable = TRUE;

    // We can use virtual addresses here since UEFI uses identity mapping as well
    gHostPageTables.Pml4[0].Address = ((UINT64)gHostPageTables.Pdpt) >> EFI_PAGE_SHIFT;

    for (UINT32 PdptIndex = 0; PdptIndex < PAGE_ENTRIES_PER_TABLE; PdptIndex++) {
        gHostPageTables.Pdpt[0][PdptIndex].Present = TRUE;
        gHostPageTables.Pdpt[0][PdptIndex].Writable = TRUE;
        gHostPageTables.Pdpt[0][PdptIndex].Address = ((UINT64)gHostPageTables.Pd[0][PdptIndex]) >> EFI_PAGE_SHIFT;

        for (UINT32 PdIndex = 0; PdIndex < PAGE_ENTRIES_PER_TABLE; PdIndex++) {
            gHostPageTables.Pd[0][PdptIndex][PdIndex].Present = TRUE;
            gHostPageTables.Pd[0][PdptIndex][PdIndex].Writable = TRUE;
            gHostPageTables.Pd[0][PdptIndex][PdIndex].Large = TRUE;

            VIRTUAL_ADDRESS Address = {
                    .Large.Offset = 0,
                    .Large.PdIndex = PdIndex,
                    .Large.PdptIndex = PdptIndex,
                    .Large.Pml4Index = 0,
                    .Large.Reserved = 0
            };

            gHostPageTables.Pd[0][PdptIndex][PdIndex].Address = Address.Packed >> EFI_PAGE_SHIFT;
        }
    }
}

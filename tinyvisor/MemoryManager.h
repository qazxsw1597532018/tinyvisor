#ifndef _TINYVISOR_MEMORY_MANAGER_H
#define _TINYVISOR_MEMORY_MANAGER_H

#include <Uefi.h>

/*************************************************************
 * Functions for managing a statically-allocated memory pool *
 *************************************************************/

/**
 * Initializes the memory pool with the given amount of pages
 * @param Pages the amount of pages to allocate
 * @return a status code
 * @note this function can only be called once, and only after InitializeMp
 */
EFI_STATUS InitializeMemoryManager();

/**
 * Allocates the given amount of pages
 * @param Count the desired amount of pages to allocate
 * @param Result a pointer to which the physical address of the pages will be written
 * @return a status code
 */
EFI_STATUS AllocatePages(UINT32 Count, VOID** Result);

/**
 * Frees previously allocated pages at the given address
 * @param Address the address of the allocated pages
 * @param Count amount of allocated pages
 * @return a status code
 */
EFI_STATUS FreePages(VOID* Address, UINT32 Count);

#endif // _TINYVISOR_MEMORY_MANAGER_H

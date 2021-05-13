#ifndef _TINYVISOR_MP_H
#define _TINYVISOR_MP_H

#include <Uefi.h>

/*********************************************
 * Functionality related to multi-processing *
 *********************************************/

typedef volatile UINTN SPIN_LOCK;

#define SPIN_LOCK_RELEASED ((SPIN_LOCK)1)
#define SPIN_LOCK_ACQUIRED ((SPIN_LOCK)2)

/**
 * Initializes a spinlock
 * @param SpinLock a pointer to the spinlock to initialize
 * @return a status code
 */
EFI_STATUS InitializeSpinLock(SPIN_LOCK* SpinLock);

/**
 * Acquires a spinlock
 * @param SpinLock the spinlock to acquire
 * @return a status code
 */
EFI_STATUS AcquireSpinLock(SPIN_LOCK* SpinLock);

/**
 * Releases a spinlock
 * @param SpinLock the spinlock to release
 * @return a status code
 */
EFI_STATUS ReleaseSpinLock(SPIN_LOCK* SpinLock);

/**
 * Locates the MpServices protocol
 * @return a status code
 */
EFI_STATUS InitializeMp();

/**
 * Returns the current processor ID
 * @param Id the pointer to which the processor ID will be written
 * @return a status code
 */
EFI_STATUS GetCurrentProcessorId(UINTN* Id);

/**
 * Returns the total available processor count
 * @param Count the pointer to which the processor count will be written
 * @return a status code
 */
EFI_STATUS GetProcessorCount(UINTN* Count);

#endif // _TINYVISOR_MP_H
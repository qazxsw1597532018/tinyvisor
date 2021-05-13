#ifndef _TINYVISOR_VMX_H
#define _TINYVISOR_VMX_H

#include <Uefi.h>

/*****************************
 * VMX-related functionality *
 *****************************/

/**
 * Checks if VMX is enabled
 * @return EFI_SUCCESS if enabled, EFI_UNSUPPORTED if disabled, anything else to indicate an error
 */
EFI_STATUS IsVmxAvailable();

/**
 * Adjusts CR0 and CR4 to the requirements of VMX
 */
VOID AdjustCrs();

#endif // _TINYVISOR_VMX_H

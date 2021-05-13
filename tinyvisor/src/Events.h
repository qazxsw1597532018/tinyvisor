#ifndef _TINYVISOR_EVENTS_H
#define _TINYVISOR_EVENTS_H

#include <Uefi.h>

/*************************************
 * Definitions related to EFI events *
 *************************************/

/**
 * Registers callbacks for EFI events such as someone calling ExitBootServices
 * @return a status code
 */
EFI_STATUS InitializeEfiEvents();

#endif // _TINYVISOR_EVENTS_H

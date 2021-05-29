#ifndef _TINYVISOR_VMM_H
#define _TINYVISOR_VMM_H

#include <Uefi.h>

/********************************
 * VMM logic and initialization *
 ********************************/

typedef struct _VMM_SHARED_CONTEXT {

} VMM_SHARED_CONTEXT;

typedef struct _VMM_PER_PROCESSOR_CONTEXT {

} VMM_PER_PROCESSOR_CONTEXT;

EFI_STATUS EnableVmmOnAllProcessors();

#endif // _TINYVISOR_VMM_H

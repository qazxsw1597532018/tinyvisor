#ifndef _TINYVISOR_CPUID_H
#define _TINYVISOR_CPUID_H

/*****************************
 * CPUID-related definitions *
 *****************************/

#define CPUID_GENUINEINTEL_EBX 'uneG'
#define CPUID_GENUINEINTEL_EDX 'Ieni'
#define CPUID_GENUINEINTEL_ECX 'letn'

#define CPUID_FEATURE_ECX_VMX 0x20

#define CPUID_LEAF_NAME 0
#define CPUID_LEAF_FEATURES 1

#endif // _TINYVISOR_CPUID_H

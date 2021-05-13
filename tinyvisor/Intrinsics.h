#ifndef _TINYVISOR_INTRINSICS_H
#define _TINYVISOR_INTRINSICS_H

/**********************************
 * Definition of AMD64 intrinsics *
 **********************************/

typedef struct _IA32_DESCRIPTOR {
    unsigned __int16 Limit;
    unsigned __int64 Base;
} __attribute__((packed)) IA32_DESCRIPTOR;

static_assert(sizeof(IA32_DESCRIPTOR) == 10, "Invalid IA32_DESCRIPTOR size!");

static __inline__ __attribute__((always_inline)) void __cpuid(unsigned __int32 __info[4], unsigned __int32 __level) {
    __asm__ __volatile__ ("cpuid": "=a"(__info[0]), "=b"(__info[1]), "=c"(__info[2]), "=d"(__info[3]) : "a"(__level),
            "c"(0));
}

static __inline__ __attribute__((always_inline)) unsigned __int64 __readmsr(unsigned __int32 msr) {
    unsigned __int32 edx = 0;
    unsigned __int32 eax = 0;
    __asm__ __volatile__ ("rdmsr" : "=d"(edx), "=a"(eax) : "c"(msr));
    return (((unsigned __int64)edx) << 32) | (unsigned __int64)eax;
}

static __inline__ __attribute__((always_inline)) void __writemsr(unsigned __int32 msr, unsigned __int64 value) {
    __asm__ __volatile__ ("wrmsr" :: "c" (msr), "A" (value));
}

static __inline__ __attribute__((always_inline)) unsigned __int64 __readcr0() {
    unsigned __int64 __cr0_val;
    __asm__ __volatile__ ("mov %%cr0, %0" : "=r"(__cr0_val) :: "memory");
    return __cr0_val;
}

static __inline__ __attribute__((always_inline)) void __writecr0(unsigned __int64 __cr0_val) {
    __asm__ __volatile__ ("mov %0, %%cr0" :: "r"(__cr0_val) : "memory");
}

static __inline__ __attribute__((always_inline)) unsigned __int64 __readcr4() {
    unsigned __int64 __cr4_val;
    __asm__ __volatile__ ("mov %%cr4, %0" : "=r"(__cr4_val) :: "memory");
    return __cr4_val;
}

static __inline__ __attribute__((always_inline)) void __writecr4(unsigned __int64 __cr4_val) {
    __asm__ __volatile__ ("mov %0, %%cr4" :: "r"(__cr4_val) : "memory");
}

static __inline__ __attribute__((always_inline)) unsigned __int16 __readcs() {
    unsigned __int16 __cs_val;
    __asm__ __volatile__ ("mov %%cs, %0" : "=a"(__cs_val));
    return __cs_val;
}

static __inline__ __attribute__((always_inline)) unsigned __int16 __str() {
    unsigned __int16 __tr = 0;
    __asm__ __volatile__ ("str %0" : "=r"(__tr) :: "memory");
    return __tr;
}

static __inline __attribute__((always_inline)) void __ltr(unsigned __int16 __tr) {
    __asm__ __volatile__ ("ltr %0" :: "r"(__tr) : "memory");
}

static __inline__ __attribute__((always_inline)) unsigned __int16 __sldt() {
    unsigned __int16 __ldtr = 0;
    __asm__ __volatile__ ("sldt %0" : "=r"(__ldtr) :: "memory");
    return __ldtr;
}

static __inline __attribute__((always_inline)) void __lgdt(const IA32_DESCRIPTOR* gdtr) {
    __asm__ __volatile__ ("lgdt %0" :: "r"(gdtr) : "memory");
}

static __inline__ __attribute__((always_inline)) unsigned __int64 __readeflags(void) {
    return __builtin_ia32_readeflags_u64();
}

static __inline__ __attribute__((always_inline)) void __writeeflags(unsigned __int64 __f) {
    __builtin_ia32_writeeflags_u64(__f);
}

static __inline__ __attribute__((always_inline)) void __memory_fence() {
    __asm__ __volatile__ ("":::"memory");
}

static __inline __attribute__((always_inline)) void __cpu_pause() {
    __asm__ __volatile__ ("pause");
}

static __inline__ __attribute__((always_inline)) void __lock_cmp_xchgw(volatile UINT16* Value, UINT16 CompareValue,
                                                                       UINT16 ExchangeValue) {
    __asm__ __volatile__ ("lock cmpxchgw %2, %1" : "+a"(CompareValue), "+m"(*Value) : "q"(ExchangeValue) : "memory",
            "cc");
}

static __inline__ __attribute__((always_inline)) void __lock_cmp_xchgl(volatile UINT32* Value, UINT32 CompareValue,
                                                                       UINT32 ExchangeValue) {
    __asm__ __volatile__ ("lock cmpxchgl %2, %1" : "+a"(CompareValue), "+m"(*Value) : "q"(ExchangeValue) : "memory",
            "cc");
}

static __inline__ __attribute__((always_inline)) void __lock_cmp_xchg8b(volatile UINT64* Value, UINT64 CompareValue,
                                                                        UINT64 ExchangeValue) {
    __asm__ __volatile__ ("lock cmpxchg8b (%1)" : "+A"(CompareValue) : "S"(Value), "b"((UINT32)ExchangeValue),
            "c"((UINT32)(ExchangeValue >> 32)) : "memory", "cc");
}

#endif // _TINYVISOR_INTRINSICS_H

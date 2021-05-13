#include "Interrupts.h"
#include "Intrinsics.h"
#include "Log.h"

IDT_ENTRY gHostIdt[IDT_ENTRY_COUNT];

extern VOID Isr0();
extern VOID Isr1();
extern VOID Isr2();
extern VOID Isr3();
extern VOID Isr4();
extern VOID Isr5();
extern VOID Isr6();
extern VOID Isr7();
extern VOID Isr8();
extern VOID Isr9();
extern VOID Isr10();
extern VOID Isr11();
extern VOID Isr12();
extern VOID Isr13();
extern VOID Isr14();
extern VOID Isr15();
extern VOID Isr16();
extern VOID Isr17();
extern VOID Isr18();
extern VOID Isr19();
extern VOID Isr20();
extern VOID Isr21();
extern VOID Isr22();
extern VOID Isr23();
extern VOID Isr24();
extern VOID Isr25();
extern VOID Isr26();
extern VOID Isr27();
extern VOID Isr28();
extern VOID Isr29();
extern VOID Isr30();
extern VOID Isr31();
extern VOID Isr32();
extern VOID Isr33();
extern VOID Isr34();
extern VOID Isr35();
extern VOID Isr36();
extern VOID Isr37();
extern VOID Isr38();
extern VOID Isr39();
extern VOID Isr40();
extern VOID Isr41();
extern VOID Isr42();
extern VOID Isr43();
extern VOID Isr44();
extern VOID Isr45();
extern VOID Isr46();
extern VOID Isr47();
extern VOID Isr48();
extern VOID Isr49();
extern VOID Isr50();
extern VOID Isr51();
extern VOID Isr52();
extern VOID Isr53();
extern VOID Isr54();
extern VOID Isr55();
extern VOID Isr56();
extern VOID Isr57();
extern VOID Isr58();
extern VOID Isr59();
extern VOID Isr60();
extern VOID Isr61();
extern VOID Isr62();
extern VOID Isr63();
extern VOID Isr64();
extern VOID Isr65();
extern VOID Isr66();
extern VOID Isr67();
extern VOID Isr68();
extern VOID Isr69();
extern VOID Isr70();
extern VOID Isr71();
extern VOID Isr72();
extern VOID Isr73();
extern VOID Isr74();
extern VOID Isr75();
extern VOID Isr76();
extern VOID Isr77();
extern VOID Isr78();
extern VOID Isr79();
extern VOID Isr80();
extern VOID Isr81();
extern VOID Isr82();
extern VOID Isr83();
extern VOID Isr84();
extern VOID Isr85();
extern VOID Isr86();
extern VOID Isr87();
extern VOID Isr88();
extern VOID Isr89();
extern VOID Isr90();
extern VOID Isr91();
extern VOID Isr92();
extern VOID Isr93();
extern VOID Isr94();
extern VOID Isr95();
extern VOID Isr96();
extern VOID Isr97();
extern VOID Isr98();
extern VOID Isr99();
extern VOID Isr100();
extern VOID Isr101();
extern VOID Isr102();
extern VOID Isr103();
extern VOID Isr104();
extern VOID Isr105();
extern VOID Isr106();
extern VOID Isr107();
extern VOID Isr108();
extern VOID Isr109();
extern VOID Isr110();
extern VOID Isr111();
extern VOID Isr112();
extern VOID Isr113();
extern VOID Isr114();
extern VOID Isr115();
extern VOID Isr116();
extern VOID Isr117();
extern VOID Isr118();
extern VOID Isr119();
extern VOID Isr120();
extern VOID Isr121();
extern VOID Isr122();
extern VOID Isr123();
extern VOID Isr124();
extern VOID Isr125();
extern VOID Isr126();
extern VOID Isr127();
extern VOID Isr128();
extern VOID Isr129();
extern VOID Isr130();
extern VOID Isr131();
extern VOID Isr132();
extern VOID Isr133();
extern VOID Isr134();
extern VOID Isr135();
extern VOID Isr136();
extern VOID Isr137();
extern VOID Isr138();
extern VOID Isr139();
extern VOID Isr140();
extern VOID Isr141();
extern VOID Isr142();
extern VOID Isr143();
extern VOID Isr144();
extern VOID Isr145();
extern VOID Isr146();
extern VOID Isr147();
extern VOID Isr148();
extern VOID Isr149();
extern VOID Isr150();
extern VOID Isr151();
extern VOID Isr152();
extern VOID Isr153();
extern VOID Isr154();
extern VOID Isr155();
extern VOID Isr156();
extern VOID Isr157();
extern VOID Isr158();
extern VOID Isr159();
extern VOID Isr160();
extern VOID Isr161();
extern VOID Isr162();
extern VOID Isr163();
extern VOID Isr164();
extern VOID Isr165();
extern VOID Isr166();
extern VOID Isr167();
extern VOID Isr168();
extern VOID Isr169();
extern VOID Isr170();
extern VOID Isr171();
extern VOID Isr172();
extern VOID Isr173();
extern VOID Isr174();
extern VOID Isr175();
extern VOID Isr176();
extern VOID Isr177();
extern VOID Isr178();
extern VOID Isr179();
extern VOID Isr180();
extern VOID Isr181();
extern VOID Isr182();
extern VOID Isr183();
extern VOID Isr184();
extern VOID Isr185();
extern VOID Isr186();
extern VOID Isr187();
extern VOID Isr188();
extern VOID Isr189();
extern VOID Isr190();
extern VOID Isr191();
extern VOID Isr192();
extern VOID Isr193();
extern VOID Isr194();
extern VOID Isr195();
extern VOID Isr196();
extern VOID Isr197();
extern VOID Isr198();
extern VOID Isr199();
extern VOID Isr200();
extern VOID Isr201();
extern VOID Isr202();
extern VOID Isr203();
extern VOID Isr204();
extern VOID Isr205();
extern VOID Isr206();
extern VOID Isr207();
extern VOID Isr208();
extern VOID Isr209();
extern VOID Isr210();
extern VOID Isr211();
extern VOID Isr212();
extern VOID Isr213();
extern VOID Isr214();
extern VOID Isr215();
extern VOID Isr216();
extern VOID Isr217();
extern VOID Isr218();
extern VOID Isr219();
extern VOID Isr220();
extern VOID Isr221();
extern VOID Isr222();
extern VOID Isr223();
extern VOID Isr224();
extern VOID Isr225();
extern VOID Isr226();
extern VOID Isr227();
extern VOID Isr228();
extern VOID Isr229();
extern VOID Isr230();
extern VOID Isr231();
extern VOID Isr232();
extern VOID Isr233();
extern VOID Isr234();
extern VOID Isr235();
extern VOID Isr236();
extern VOID Isr237();
extern VOID Isr238();
extern VOID Isr239();
extern VOID Isr240();
extern VOID Isr241();
extern VOID Isr242();
extern VOID Isr243();
extern VOID Isr244();
extern VOID Isr245();
extern VOID Isr246();
extern VOID Isr247();
extern VOID Isr248();
extern VOID Isr249();
extern VOID Isr250();
extern VOID Isr251();
extern VOID Isr252();
extern VOID Isr253();
extern VOID Isr254();
extern VOID Isr255();
extern VOID NmiIsr();

VOID* Isrs[] = {
    Isr0,
    Isr1,
    Isr2,
    Isr3,
    Isr4,
    Isr5,
    Isr6,
    Isr7,
    Isr8,
    Isr9,
    Isr10,
    Isr11,
    Isr12,
    Isr13,
    Isr14,
    Isr15,
    Isr16,
    Isr17,
    Isr18,
    Isr19,
    Isr20,
    Isr21,
    Isr22,
    Isr23,
    Isr24,
    Isr25,
    Isr26,
    Isr27,
    Isr28,
    Isr29,
    Isr30,
    Isr31,
    Isr32,
    Isr33,
    Isr34,
    Isr35,
    Isr36,
    Isr37,
    Isr38,
    Isr40,
    Isr41,
    Isr39,
    Isr42,
    Isr43,
    Isr44,
    Isr45,
    Isr46,
    Isr47,
    Isr48,
    Isr49,
    Isr50,
    Isr51,
    Isr52,
    Isr53,
    Isr54,
    Isr55,
    Isr56,
    Isr57,
    Isr58,
    Isr59,
    Isr60,
    Isr61,
    Isr62,
    Isr63,
    Isr64,
    Isr65,
    Isr66,
    Isr67,
    Isr68,
    Isr69,
    Isr70,
    Isr71,
    Isr72,
    Isr73,
    Isr74,
    Isr75,
    Isr76,
    Isr77,
    Isr78,
    Isr79,
    Isr80,
    Isr81,
    Isr82,
    Isr83,
    Isr84,
    Isr85,
    Isr86,
    Isr87,
    Isr88,
    Isr89,
    Isr90,
    Isr91,
    Isr92,
    Isr93,
    Isr94,
    Isr95,
    Isr96,
    Isr97,
    Isr98,
    Isr99,
    Isr100,
    Isr101,
    Isr102,
    Isr103,
    Isr104,
    Isr105,
    Isr106,
    Isr107,
    Isr108,
    Isr109,
    Isr110,
    Isr111,
    Isr112,
    Isr113,
    Isr114,
    Isr115,
    Isr116,
    Isr117,
    Isr118,
    Isr119,
    Isr120,
    Isr121,
    Isr122,
    Isr123,
    Isr124,
    Isr125,
    Isr126,
    Isr127,
    Isr128,
    Isr129,
    Isr130,
    Isr131,
    Isr132,
    Isr133,
    Isr134,
    Isr135,
    Isr136,
    Isr137,
    Isr138,
    Isr139,
    Isr140,
    Isr141,
    Isr142,
    Isr143,
    Isr144,
    Isr145,
    Isr146,
    Isr147,
    Isr148,
    Isr149,
    Isr150,
    Isr151,
    Isr152,
    Isr153,
    Isr154,
    Isr155,
    Isr156,
    Isr157,
    Isr158,
    Isr159,
    Isr160,
    Isr161,
    Isr162,
    Isr163,
    Isr164,
    Isr165,
    Isr166,
    Isr167,
    Isr168,
    Isr169,
    Isr170,
    Isr171,
    Isr172,
    Isr173,
    Isr174,
    Isr175,
    Isr176,
    Isr177,
    Isr178,
    Isr179,
    Isr180,
    Isr181,
    Isr182,
    Isr183,
    Isr184,
    Isr185,
    Isr186,
    Isr187,
    Isr188,
    Isr189,
    Isr190,
    Isr191,
    Isr192,
    Isr193,
    Isr194,
    Isr195,
    Isr196,
    Isr197,
    Isr198,
    Isr199,
    Isr200,
    Isr201,
    Isr202,
    Isr203,
    Isr204,
    Isr205,
    Isr206,
    Isr207,
    Isr208,
    Isr209,
    Isr210,
    Isr211,
    Isr212,
    Isr213,
    Isr214,
    Isr215,
    Isr216,
    Isr217,
    Isr218,
    Isr219,
    Isr220,
    Isr221,
    Isr222,
    Isr223,
    Isr224,
    Isr225,
    Isr226,
    Isr227,
    Isr228,
    Isr229,
    Isr230,
    Isr231,
    Isr232,
    Isr233,
    Isr234,
    Isr235,
    Isr236,
    Isr237,
    Isr238,
    Isr239,
    Isr240,
    Isr241,
    Isr242,
    Isr243,
    Isr244,
    Isr245,
    Isr246,
    Isr247,
    Isr248,
    Isr249,
    Isr250,
    Isr251,
    Isr252,
    Isr253,
    Isr254,
    Isr255,
};

VOID ExceptionHandler() {

}

VOID InitializeHostIdt() {
    memset(gHostIdt, 0, sizeof(gHostIdt));

    for (UINT32 i = 0; i < COUNT_OF(gHostIdt); i++) {
        gHostIdt[i].PointerLow = (UINT64)Isrs[i] & 0xffff;
        gHostIdt[i].PointerMiddle = ((UINT64)Isrs[i] >> 16) & 0xffff;
        gHostIdt[i].PointerHigh = (UINT64)Isrs[i] >> 32;
        gHostIdt[i].GateType = 0x8e;
        gHostIdt[i].SegmentSelector = __readcs();
    }

    gHostIdt[2].PointerLow = (UINT64)NmiIsr & 0xffff;
    gHostIdt[2].PointerMiddle = ((UINT64)NmiIsr >> 16) & 0xffff;
    gHostIdt[2].PointerHigh = (UINT64)NmiIsr >> 32;
}

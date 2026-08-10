#include "common.h"

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EDC04);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EDC2C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EDC70);

void func_801EDCFC(void) {

    extern s16 D_801F7C12;
    D_801F7C12 = -1;
}


s16 func_801EDD10(void) {

    extern s16 D_801F800C;
    return D_801F800C;
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EDD20);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EDD98);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EDDF4);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EDE38);

            typedef struct { s8 c[8]; } Blk8_8012C890_801EDF64;

/* func_801EDF64 @ 0x8017C24C -- ov_MAIN_012 (7 ins).
 *
 * NOTE ON TARGET IDENTITY (tier-2): the dispatched entry ("483 ins, ov_SC06_032") does not
 * exist. ov_SC06_032's func_801EDF64 is a 952-ins renderer, already MATCHED/closed in
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c -- and "ov_SC06_032_jr_8017C24C" is a CARVE-REGION
 * name, not a member function (that region holds only func_801902EC/func_80191070).
 * The only genuinely unmatched func_801EDF64 in the tree is this ov_MAIN_012 one -- a
 * distinct 7-ins function that merely shares the VRAM address (overlay collision).
 *
 * Codegen note (§31 cse_expr): the target materialises the symbol address ONCE
 * (lui+addiu -> $v1) and does both the lhu and the sh off that base. Writing the global
 * directly (D_80115112 = D_80115112 + 1) instead emits TWO luis (%hi for the load, %hi for
 * the store) -> 8 ins, LENGTH-DRIFT. Taking the address into a pointer local forces the
 * single-base form. The nop at idx3 is the lhu load-delay slot (maspsx).
 *
 * D_80115112: u16 frame/state counter (same symbol used in ov_SC03_099_jr_80140608).
 */


void func_801EDF64(void)
{

    extern unsigned short D_80115112;
    unsigned short *p = &D_80115112;
    *p = *p + 1;
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EDF80);

            typedef struct { s8 c[8]; } Blk8_8012C890_801EE060;

/* func_801EE060 @ 0x8017C24C -- ov_MAIN_012 (7 ins).
 *
 * NOTE ON TARGET IDENTITY (tier-2): the dispatched entry ("483 ins, ov_SC06_032") does not
 * exist. ov_SC06_032's func_801EE060 is a 952-ins renderer, already MATCHED/closed in
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c -- and "ov_SC06_032_jr_8017C24C" is a CARVE-REGION
 * name, not a member function (that region holds only func_801902EC/func_80191070).
 * The only genuinely unmatched func_801EE060 in the tree is this ov_MAIN_012 one -- a
 * distinct 7-ins function that merely shares the VRAM address (overlay collision).
 *
 * Codegen note (§31 cse_expr): the target materialises the symbol address ONCE
 * (lui+addiu -> $v1) and does both the lhu and the sh off that base. Writing the global
 * directly (D_80115112 = D_80115112 + 1) instead emits TWO luis (%hi for the load, %hi for
 * the store) -> 8 ins, LENGTH-DRIFT. Taking the address into a pointer local forces the
 * single-base form. The nop at idx3 is the lhu load-delay slot (maspsx).
 *
 * D_80115112: u16 frame/state counter (same symbol used in ov_SC03_099_jr_80140608).
 */


void func_801EE060(void)
{

    extern unsigned short D_80115112;
    unsigned short *p = &D_80115112;
    *p = *p + 1;
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EE07C);

INCLUDE_RODATA("asm/md_SC05_026/nonmatchings/md_SC05_026", D_801ED988);

INCLUDE_RODATA("asm/md_SC05_026/nonmatchings/md_SC05_026", D_801EDA60);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EE0D4);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EE730);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EE8E0);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EEBD0);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EEC54);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EEFBC);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EF448);

u32 func_801EF960(s32 a0, s32 a1) {
    s32 t0;
    s32 a2;
    s32 a3;
    t0 = 0;
    a2 = a0;
    a3 = 0;
    while (a2 >= 10) {
        a0 = a0 / 10;
        t0 = t0 | ((a2 - (a0 * 2 + a0 * 8)) << a3);
        a2 = a0;
        a3 += 4;
    }
    t0 = t0 | (a2 << a3);
    return t0 << a1;
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EF9C8);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EFA40);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EFC30);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EFC58);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EFF44);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EFF6C);


extern s32 func_800167F0(s32 a0);

s32 func_801EFFC4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EFFE8);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F003C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F00F4);



void func_801F0114(void *a0) {

    extern void (*D_801F19D8[])(void);
    D_801F19D8[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0150);



void func_801F01BC(void *a0) {

    extern void (*D_801F1A64[])(void);
    D_801F1A64[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F01F8);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0220);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0288);

void func_801F02E0(void) {
}



void func_801F02E8(void *a0) {

    extern void (*D_801F1A74[])(void);
    D_801F1A74[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0324);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0344);

void func_801F03AC(void) {
}

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F03B4);



void func_801F0478(void *a0) {

    extern void (*D_801F1A80[])(void);
    D_801F1A80[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F04B4);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F04DC);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F06D4);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0714);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0748);



void func_801F0894(void *a0) {

    extern void (*D_801F1BD0[])(void);
    D_801F1BD0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F08D0);



void func_801F08E0(void) {

    extern s32 D_801F8328;
    D_801F8328 = 1;
}




s32 func_801F08F4(void) {

    extern s32 D_801F8328;
    return D_801F8328;
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0904);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F098C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0A14);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0A98);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0BB4);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0C4C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0D88);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0E0C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0E24);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0E6C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0E9C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0EEC);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0F2C);

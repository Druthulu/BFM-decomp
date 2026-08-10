#include "common.h"

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801EF6E4);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801EF70C);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801EF750);

void func_801EF7DC(void) {

    extern s16 D_801F96BA;
    D_801F96BA = -1;
}


s16 func_801EF7F0(void) {

    extern s16 D_801F9AB4;
    return D_801F9AB4;
}


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801EF800);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801EF878);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801EF8D4);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801EF918);

            typedef struct { s8 c[8]; } Blk8_8012C890_801EFA44;

/* func_801EFA44 @ 0x8017C24C -- ov_MAIN_012 (7 ins).
 *
 * NOTE ON TARGET IDENTITY (tier-2): the dispatched entry ("483 ins, ov_SC06_032") does not
 * exist. ov_SC06_032's func_801EFA44 is a 952-ins renderer, already MATCHED/closed in
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c -- and "ov_SC06_032_jr_8017C24C" is a CARVE-REGION
 * name, not a member function (that region holds only func_801902EC/func_80191070).
 * The only genuinely unmatched func_801EFA44 in the tree is this ov_MAIN_012 one -- a
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


void func_801EFA44(void)
{

    extern unsigned short D_80115112;
    unsigned short *p = &D_80115112;
    *p = *p + 1;
}


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801EFA60);

            typedef struct { s8 c[8]; } Blk8_8012C890_801EFB40;

/* func_801EFB40 @ 0x8017C24C -- ov_MAIN_012 (7 ins).
 *
 * NOTE ON TARGET IDENTITY (tier-2): the dispatched entry ("483 ins, ov_SC06_032") does not
 * exist. ov_SC06_032's func_801EFB40 is a 952-ins renderer, already MATCHED/closed in
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c -- and "ov_SC06_032_jr_8017C24C" is a CARVE-REGION
 * name, not a member function (that region holds only func_801902EC/func_80191070).
 * The only genuinely unmatched func_801EFB40 in the tree is this ov_MAIN_012 one -- a
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


void func_801EFB40(void)
{

    extern unsigned short D_80115112;
    unsigned short *p = &D_80115112;
    *p = *p + 1;
}


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801EFB5C);

INCLUDE_RODATA("asm/md_SC03_076/nonmatchings/md_SC03_076", D_801EF468);

INCLUDE_RODATA("asm/md_SC03_076/nonmatchings/md_SC03_076", D_801EF540);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801EFBB4);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F0210);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F03C0);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F06B0);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F0734);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F0A9C);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F0F28);

u32 func_801F1440(s32 a0, s32 a1) {
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


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F14A8);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1520);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1710);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1738);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1A24);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1A4C);


extern s32 func_800167F0(s32 a0);

s32 func_801F1AA4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1AC8);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1B1C);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1BAC);



void func_801F1BCC(void *a0) {

    extern void (*D_801F3480[])(void);
    D_801F3480[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1C08);



void func_801F1C74(void *a0) {

    extern void (*D_801F350C[])(void);
    D_801F350C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1CB0);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1CD8);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1D40);

void func_801F1D98(void) {
}



void func_801F1DA0(void *a0) {

    extern void (*D_801F351C[])(void);
    D_801F351C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1DDC);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1DFC);

void func_801F1E64(void) {
}

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1E6C);



void func_801F1F30(void *a0) {

    extern void (*D_801F3528[])(void);
    D_801F3528[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1F6C);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F1F94);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F218C);



void func_801F22D8(void *a0) {

    extern void (*D_801F3678[])(void);
    D_801F3678[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F2314);



void func_801F2324(void) {

    extern s32 D_801F9DD0;
    D_801F9DD0 = 1;
}




s32 func_801F2338(void) {

    extern s32 D_801F9DD0;
    return D_801F9DD0;
}


INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F2348);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F23D0);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F2458);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F24DC);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F25F8);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F2690);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F27CC);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F2850);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F2868);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F28B0);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F28E0);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F2930);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F2970);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F29B0);

INCLUDE_ASM("asm/md_SC03_076/nonmatchings/md_SC03_076", func_801F29E0);

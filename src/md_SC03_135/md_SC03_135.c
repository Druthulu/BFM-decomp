#include "common.h"

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E2864);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E288C);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E28D0);

void func_801E295C(void) {

    extern s16 D_801EA556;
    D_801EA556 = -1;
}


s16 func_801E2970(void) {

    extern s16 D_801EA950;
    return D_801EA950;
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E2980);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E29F8);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E2A54);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E2A98);

            typedef struct { s8 c[8]; } Blk8_8012C890_801E2BC4;

/* func_801E2BC4 @ 0x8017C24C -- ov_MAIN_012 (7 ins).
 *
 * NOTE ON TARGET IDENTITY (tier-2): the dispatched entry ("483 ins, ov_SC06_032") does not
 * exist. ov_SC06_032's func_801E2BC4 is a 952-ins renderer, already MATCHED/closed in
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c -- and "ov_SC06_032_jr_8017C24C" is a CARVE-REGION
 * name, not a member function (that region holds only func_801902EC/func_80191070).
 * The only genuinely unmatched func_801E2BC4 in the tree is this ov_MAIN_012 one -- a
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


void func_801E2BC4(void)
{

    extern unsigned short D_80115112;
    unsigned short *p = &D_80115112;
    *p = *p + 1;
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E2BE0);

            typedef struct { s8 c[8]; } Blk8_8012C890_801E2CC0;

/* func_801E2CC0 @ 0x8017C24C -- ov_MAIN_012 (7 ins).
 *
 * NOTE ON TARGET IDENTITY (tier-2): the dispatched entry ("483 ins, ov_SC06_032") does not
 * exist. ov_SC06_032's func_801E2CC0 is a 952-ins renderer, already MATCHED/closed in
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c -- and "ov_SC06_032_jr_8017C24C" is a CARVE-REGION
 * name, not a member function (that region holds only func_801902EC/func_80191070).
 * The only genuinely unmatched func_801E2CC0 in the tree is this ov_MAIN_012 one -- a
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


void func_801E2CC0(void)
{

    extern unsigned short D_80115112;
    unsigned short *p = &D_80115112;
    *p = *p + 1;
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E2CDC);

INCLUDE_RODATA("asm/md_SC03_135/nonmatchings/md_SC03_135", D_801E25E8);

INCLUDE_RODATA("asm/md_SC03_135/nonmatchings/md_SC03_135", D_801E26C0);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E2D34);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E3390);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E3540);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E3830);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E38B4);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E3C1C);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E40A8);

u32 func_801E45C0(s32 a0, s32 a1) {
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


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4628);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E46A0);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4890);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E48B8);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4BA4);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4BCC);


extern s32 func_800167F0(s32 a0);

s32 func_801E4C24(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4C48);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4C9C);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4D3C);



void func_801E4D5C(void *a0) {

    extern void (*D_801E65E8[])(void);
    D_801E65E8[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4D98);



void func_801E4E04(void *a0) {

    extern void (*D_801E6674[])(void);
    D_801E6674[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4E40);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4E68);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4ED0);

void func_801E4F28(void) {
}



void func_801E4F30(void *a0) {

    extern void (*D_801E6684[])(void);
    D_801E6684[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4F6C);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4F8C);

void func_801E4FF4(void) {
}

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E4FFC);



void func_801E50C0(void *a0) {

    extern void (*D_801E6690[])(void);
    D_801E6690[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E50FC);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5124);


s32 func_801E531C(void) {
    return 39;
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5324);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5358);



void func_801E54A4(void *a0) {

    extern void (*D_801E67E0[])(void);
    D_801E67E0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E54E0);



void func_801E54F0(void) {

    extern s32 D_801EAC6C;
    D_801EAC6C = 1;
}




s32 func_801E5504(void) {

    extern s32 D_801EAC6C;
    return D_801EAC6C;
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5514);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E559C);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5624);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E56A8);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E57C4);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E585C);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5998);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5A1C);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5A34);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5A7C);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5AAC);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5AFC);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E5B3C);

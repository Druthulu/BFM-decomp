#include "common.h"

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7DA4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7DCC);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7E10);

void func_801E7E9C(void) {

    extern s16 D_801F1D8A;
    D_801F1D8A = -1;
}


s16 func_801E7EB0(void) {

    extern s16 D_801F2184;
    return D_801F2184;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7EC0);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7F38);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7F94);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7FD8);

            typedef struct { s8 c[8]; } Blk8_8012C890_801E8104;

/* func_801E8104 @ 0x8017C24C -- ov_MAIN_012 (7 ins).
 *
 * NOTE ON TARGET IDENTITY (tier-2): the dispatched entry ("483 ins, ov_SC06_032") does not
 * exist. ov_SC06_032's func_801E8104 is a 952-ins renderer, already MATCHED/closed in
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c -- and "ov_SC06_032_jr_8017C24C" is a CARVE-REGION
 * name, not a member function (that region holds only func_801902EC/func_80191070).
 * The only genuinely unmatched func_801E8104 in the tree is this ov_MAIN_012 one -- a
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


void func_801E8104(void)
{

    extern unsigned short D_80115112;
    unsigned short *p = &D_80115112;
    *p = *p + 1;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E8120);

            typedef struct { s8 c[8]; } Blk8_8012C890_801E8200;

/* func_801E8200 @ 0x8017C24C -- ov_MAIN_012 (7 ins).
 *
 * NOTE ON TARGET IDENTITY (tier-2): the dispatched entry ("483 ins, ov_SC06_032") does not
 * exist. ov_SC06_032's func_801E8200 is a 952-ins renderer, already MATCHED/closed in
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c -- and "ov_SC06_032_jr_8017C24C" is a CARVE-REGION
 * name, not a member function (that region holds only func_801902EC/func_80191070).
 * The only genuinely unmatched func_801E8200 in the tree is this ov_MAIN_012 one -- a
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


void func_801E8200(void)
{

    extern unsigned short D_80115112;
    unsigned short *p = &D_80115112;
    *p = *p + 1;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E821C);

INCLUDE_RODATA("asm/md_SC04_027/nonmatchings/md_SC04_027", D_801E7B28);

INCLUDE_RODATA("asm/md_SC04_027/nonmatchings/md_SC04_027", D_801E7C00);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E8274);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E88D0);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E8A80);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E8D70);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E8DF4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E915C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E95E8);

u32 func_801E9B00(s32 a0, s32 a1) {
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


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E9B68);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E9BE0);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E9DD0);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E9DF8);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA0E4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA10C);


extern s32 func_800167F0(s32 a0);

s32 func_801EA164(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA188);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA1DC);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA27C);



void func_801EA29C(void *a0) {

    extern void (*D_801EBB50[])(void);
    D_801EBB50[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA2D8);



void func_801EA344(void *a0) {

    extern void (*D_801EBBDC[])(void);
    D_801EBBDC[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA380);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA3A8);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA410);

void func_801EA468(void) {
}



void func_801EA470(void *a0) {

    extern void (*D_801EBBEC[])(void);
    D_801EBBEC[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA4AC);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA4CC);

void func_801EA534(void) {
}

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA53C);



void func_801EA600(void *a0) {

    extern void (*D_801EBBF8[])(void);
    D_801EBBF8[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA63C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA664);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA85C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA88C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA8C0);



void func_801EAA0C(void *a0) {

    extern void (*D_801EBD48[])(void);
    D_801EBD48[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAA48);



void func_801EAA58(void) {

    extern s32 D_801F24A0;
    D_801F24A0 = 1;
}




s32 func_801EAA6C(void) {

    extern s32 D_801F24A0;
    return D_801F24A0;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAA7C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAB04);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAB8C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAC10);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAD2C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EADC4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAF00);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAF84);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAF9C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAFE4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EB014);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EB064);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EB0A4);

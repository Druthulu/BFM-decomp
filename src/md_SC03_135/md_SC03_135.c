#include "common.h"

void func_801E2864(void) {
    extern void func_80016714(s8 *a0, s32 a1);
    extern u16 D_801EA554;
    func_80016714(&D_801EA554, 8);
}


s32 func_801E288C(void) {

    extern s16 D_801EA554;
    extern void (*D_801E5B7C[])(void);
    extern s16 D_801EA556;

    D_801E5B7C[D_801EA554]();
    return (unsigned)D_801EA556 >> 31;
}


extern s32 func_80029504(void);
extern void func_801E2980(s32 arg0, s32 arg1);

void func_801E28D0(void) {

    extern s16 D_801EA55C;
    extern unsigned short D_801EA554;
    s32 v;
    unsigned short *p;

    v = func_80029504();
    if ((u32)(v - 5) >= 0x4B5) {
        if (v != 0x6A4) {
            D_801EA55C = 1;
        } else {
            D_801EA55C = 2;
        }
    } else {
        D_801EA55C = 0;
    }
    func_801E2980(1, D_801EA55C);
    p = &D_801EA554;
    *p = *p + 1;
}


void func_801E295C(void) {

    extern s16 D_801EA556;
    D_801EA556 = -1;
}


s16 func_801E2970(void) {

    extern s16 D_801EA950;
    return D_801EA950;
}


void func_801E2980(s32 arg0, s32 arg1)
{
    extern u8 D_800B9A15;
    extern u8 D_800B9A13;
    extern u16 D_80115110;
    extern s16 D_80115126;
    extern s16 D_801EA958;
    extern s16 D_801EA954;
    extern unsigned short D_80115112;
    extern void *D_8011DB24;
    extern void func_801E29F8(void);
    extern s32 func_8002D4C8(s32, s32);

    D_800B9A15 = 1;
    D_800B9A13 = 5;
    D_80115110 = 4;
    D_80115126 = arg0;
    D_801EA958 = arg1;
    D_801EA954 = arg1;
    D_80115112 = 0;
    D_8011DB24 = func_801E29F8;
    func_8002D4C8(0x1E, 0);
}


extern u16 D_80115116;
extern unsigned short D_80115112;
extern void (*D_801E65D0[])(void);
extern void func_80141C04(void);

void func_801E29F8(void) {

    extern u16 D_80115112;
    extern u16 D_80115116;
    extern void (*D_801E65D0[])(void);
    u16 i;
    i = D_80115112;
    D_801E65D0[i]();
    func_80141C04();
    D_80115116++;
}


void func_801E2A54(void)
{
    extern u16 D_80115112;
    extern void func_800D24A0(s32);
    extern void func_801E2A98(void);
    extern void func_8002AF18(void);
    u16 *p = &D_80115112;

    func_800D24A0(5);
    func_801E2A98();
    func_8002AF18();
    *p = *p + 1;
}


void func_801E2A98(void) {
    extern u32 D_801EAC3C;
    extern u8 D_801EAC4C[];
    extern s16 D_801EA954;
    extern s16 D_801EA950;
    extern s16 D_801EA95C;
    extern s16 D_80115118;
    extern s16 D_8011512C;
    extern s32 D_801E63B0;
    extern s32 D_801E6448;
    extern s16 D_80115126;
    extern s32 D_80115130[];
    extern s32 D_801E64F4[];
    extern s32 D_80115134;
    extern u8 D_80115138[];

    s16 i;

    D_801EAC3C = 0;
    for (i = 0; i < 8; i++) {
        D_801EAC4C[i] = 0xFF;
    }
    D_801EA950 = 0;
    D_801EA95C = 0;
    D_80115118 = 0;
    if (D_801EA954 == 0) {
        D_8011512C = 0;
        D_801E6448 = D_801E63B0;
    } else {
        D_8011512C = 9;
        D_801E6448 = 0x1A;
    }
    i = 0;
    D_80115130[0] = 0;
    D_80115134 = D_801E64F4[D_80115126];
    for (i = 0; i < 6; i++) {
        D_80115138[i] = *(u16 *)(D_80115134 + i * 32);
        ((s16 *)D_80115130)[20 + i] = *(u16 *)(D_80115134 + i * 32 + 2);
    }
}


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


void func_801E2BE0(void)
{
    extern s16 D_800B9A02;
    extern s16 D_801EA954;
    extern s32 D_801151D0;
    extern u8 D_801151C8[];
    extern u32 D_801EAC3C;
    extern u32 D_801EAC40;
    extern u16 D_801EAC44[];
    extern u32 D_801EAC54;
    extern s16 D_80115126;
    extern u16 D_80115112;
    extern u8 D_800B9A15;
    extern s16 D_801EA950;
    s32 pad0;
    s32 var_s0;
    u16 *p;

    (void)&pad0;
    D_801151D0 = *(u32 *)(D_801151C8 + *(u16 *)&D_800B9A02 * 4);
    if (D_801EA954 == 0) {
        D_801EAC54 = func_8002B0B4(D_801EAC3C, D_801EAC40, D_801EAC44);
        if (D_80115126 == 0) {
            func_801E38B4();
        } else {
            func_801E3C1C();
        }
    }
    var_s0 = func_801E2D34();
    func_801E3390();
    if ((var_s0 << 16) != 0) {
        D_801EA950 = var_s0;
        D_800B9A15 = 0;
        p = &D_80115112;
        *p += 1;
    }
}


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




extern void func_800D2624(void);

void func_801E2CDC(void) {

    extern short D_800B9A02;
    extern u16 D_80115114;
    extern u16 D_80115112;
    u16 v0 = (*(u16 *)&D_800B9A02);
    u16 v1 = D_80115114;

    v0 ^= 0x1;

    if (v1 == v0) {
        func_800D2624();
    } else {
        D_80115112++;
    }
}


INCLUDE_RODATA("asm/md_SC03_135/nonmatchings/md_SC03_135", D_801E25E8);

INCLUDE_RODATA("asm/md_SC03_135/nonmatchings/md_SC03_135", D_801E26C0);

INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E2D34);

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



extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);

s32 func_801E4C9C(s32 param_1) {
    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0 && func_80029524() == 0) {
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


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


extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E4ED0(void *arg0) {

    extern u8 D_801E6644[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E6644));
        func_80171A1C(arg0);
    }
}


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


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E50C0(void *a0);

void func_801E4FFC(void) {

    extern s32 D_80126950;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern s16 D_801274E8;
    extern s16 D_801274EA;
    extern s16 D_801274EC;

    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x82;
    D_80126968 = 0xFB1;
    D_8012696A = 0x7C7;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x36;
    D_8012697A = 0;
    func_8012A018((s32)func_801E50C0, 0);
    func_801E50C0(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801E50C0(void *a0) {

    extern void (*D_801E6690[])(void);
    D_801E6690[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_135/nonmatchings/md_SC03_135", func_801E50FC);


/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801E5124;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801E5124;

extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801E5124(s32 param_1, s16 *param_2) {

    extern s32 D_80126B58;
    extern s16 D_801E6694[];
    extern u16 D_801E6698[];

    MATRIX_801EDED4_801E5124  m1;
    SVECTOR_801EDED4_801E5124 svec_in;
    SVECTOR_801EDED4_801E5124 svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801E6694[t];
        *(s16 *)(param_1 + 0x2E) = D_801E6698[*(u8 *)(param_1 + 5)];
    }

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  0xA);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 0xA);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 0xA);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 0xA);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 0xA);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0xA);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0xA);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0xA);

    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)param_2[0];
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)param_2[1];
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)param_2[2];
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(param_1 + 0x28) + param_2[0];
    m1.t[1] = *(s16 *)(param_1 + 0x2A) + param_2[1];
    m1.t[2] = *(s16 *)(param_1 + 0x2C) + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}



s32 func_801E531C(void) {
    return 39;
}




extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_801E5324(void) {

    extern u8 D_800AF040[];
    func_8001ABBC(0, 0, D_800AF040, 0, 0);
}


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

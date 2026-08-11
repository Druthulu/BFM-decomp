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




extern void func_800D2624(void);

void func_801EE07C(void) {

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

extern void func_8014B00C(void);
extern void func_80029344(void);
void func_801EFF44(void) {
    func_8014B00C();
    func_80029344();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EFF6C);


extern s32 func_800167F0(s32 a0);

s32 func_801EFFC4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801EFFE8);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F003C);

extern void func_800D1EBC(void);
void func_801F00F4(void) {
    func_800D1EBC();
}




void func_801F0114(void *a0) {

    extern void (*D_801F19D8[])(void);
    D_801F19D8[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0150);



void func_801F01BC(void *a0) {

    extern void (*D_801F1A64[])(void);
    D_801F1A64[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(void);
void func_801F01F8(void) {
    ((void (*)(void))func_80171A1C)();
    func_80175414();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0220);


extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801F0288(void *arg0) {

    extern u8 D_801F1A34[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801F1A34));
        func_80171A1C(arg0);
    }
}


void func_801F02E0(void) {
}



void func_801F02E8(void *a0) {

    extern void (*D_801F1A74[])(void);
    D_801F1A74[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801F0324(void) {
    ((void (*)(void))func_80171A1C)();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0344);

void func_801F03AC(void) {
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801F0478(void *a0);

void func_801F03B4(void) {

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
    func_8012A018((s32)func_801F0478, 0);
    func_801F0478(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801F0478(void *a0) {

    extern void (*D_801F1A80[])(void);
    D_801F1A80[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F04B4);


/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801F04DC;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801F04DC;

extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801F04DC(s32 param_1, s16 *param_2) {

    extern s32 D_80126B58;
    extern s16 D_801F1A84[];
    extern u16 D_801F1A88[];

    MATRIX_801EDED4_801F04DC  m1;
    SVECTOR_801EDED4_801F04DC svec_in;
    SVECTOR_801EDED4_801F04DC svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801F1A84[t];
        *(s16 *)(param_1 + 0x2E) = D_801F1A88[*(u8 *)(param_1 + 5)];
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


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F06D4);



extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_801F0714(void) {

    extern u8 D_800AF040[];
    func_8001ABBC(0, 0, D_800AF040, 0, 0);
}


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


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801F0BB4(void *a0) {
    extern s32 D_801F7BE4;
    extern s32 D_801B9A0C;
    extern s32 D_801F1A8C;
    extern s32 D_801F1ABC;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F7BE4);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801B9A0C);
        func_8012E8E0((s32)a0, (s32)&D_801F1A8C);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801F1ABC);
    }
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0C4C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0D88);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0E0C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0E24);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0E6C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0E9C);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0EEC);

INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026", func_801F0F2C);

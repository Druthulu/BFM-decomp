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




extern void func_800D2624(void);

void func_801E821C(void) {

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

extern void func_8014B00C(void);
extern void func_80029344(void);
void func_801EA0E4(void) {
    func_8014B00C();
    func_80029344();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA10C);


extern s32 func_800167F0(s32 a0);

s32 func_801EA164(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA188);



extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);

s32 func_801EA1DC(s32 param_1) {
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


extern void func_800D1EBC(void);
void func_801EA27C(void) {
    func_800D1EBC();
}




void func_801EA29C(void *a0) {

    extern void (*D_801EBB50[])(void);
    D_801EBB50[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA2D8);



void func_801EA344(void *a0) {

    extern void (*D_801EBBDC[])(void);
    D_801EBBDC[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801EA380(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA3A8);


extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EA410(void *arg0) {

    extern u8 D_801EBBAC[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801EBBAC));
        func_80171A1C(arg0);
    }
}


void func_801EA468(void) {
}



void func_801EA470(void *a0) {

    extern void (*D_801EBBEC[])(void);
    D_801EBBEC[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801EA4AC(void) {
    ((void (*)(void))func_80171A1C)();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA4CC);

void func_801EA534(void) {
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801EA600(void *a0);

void func_801EA53C(void) {

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
    func_8012A018((s32)func_801EA600, 0);
    func_801EA600(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801EA600(void *a0) {

    extern void (*D_801EBBF8[])(void);
    D_801EBBF8[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA63C);


/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801EA664;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801EA664;

extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801EA664(s32 param_1, s16 *param_2) {

    extern s32 D_80126B58;
    extern s16 D_801EBBFC[];
    extern u16 D_801EBC00[];

    MATRIX_801EDED4_801EA664  m1;
    SVECTOR_801EDED4_801EA664 svec_in;
    SVECTOR_801EDED4_801EA664 svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801EBBFC[t];
        *(s16 *)(param_1 + 0x2E) = D_801EBC00[*(u8 *)(param_1 + 5)];
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



u8 func_801EA85C(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0x16;
}




extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_801EA88C(void) {

    extern u8 D_800AF040[];
    func_8001ABBC(0, 0, D_800AF040, 0, 0);
}


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


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801EAD2C(void *a0) {
    extern s32 D_801F1D5C;
    extern s32 D_801B9A50;
    extern s32 D_801EBC04;
    extern s32 D_801EBC34;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F1D5C);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801B9A50);
        func_8012E8E0((s32)a0, (s32)&D_801EBC04);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801EBC34);
    }
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EADC4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAF00);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAF84);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAF9C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAFE4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EB014);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EB064);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EB0A4);

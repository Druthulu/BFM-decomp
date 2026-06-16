#include "common.h"

extern void func_80128288(void);

void func_80128158(void) {
    func_80128288();
}


extern void func_801285E4(void);

void func_80128178(void) {
    func_801285E4();
}


extern void func_80128678(void);

void func_80128198(void) {
    func_80128678();
}


extern void func_80128714(void);

void func_801281B8(void) {
    func_80128714();
}


extern void func_8013E67C(void);

void func_801281D8(void) {
    func_8013E67C();
}


extern void func_8013E558(void);

void func_801281F8(void) {
    func_8013E558();
}


extern s32 D_801D7F90;

s32 func_80128218(void) {
    return D_801D7F90;
}


extern void func_80128A28(void);

void func_80128228(void) {
    func_80128A28();
}


extern void func_80128AF4(void);

void func_80128248(void) {
    func_80128AF4();
}


extern void func_801282EC(void);

void func_80128268(void) {
    func_801282EC();
}


extern u16 D_800B99F6;
extern void (*D_80186DB4[])(void);

void func_80128288(void) {
    u32 v1;
    v1 = D_800B99F6;
    if (v1 < 9) {
        D_80186DB4[v1]();
    }
}


extern void func_80011B7C(int);

void func_801282CC(void) {
    func_80011B7C(0x11);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801282EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012832C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128420);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801284B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801284F0);

extern void func_80146074(void);
extern void func_80011C10(void);

void func_8012853C(void) {
    func_80146074();
    func_80011C10();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128564);

extern u8 D_800B9A11;

void func_801285D4(void) {
    D_800B9A11 = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801285E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128678);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128714);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801287B8);

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern s32 D_801D7F90;
extern u8 D_800AEFD0;

void func_801288B0(void) {
    func_8001ABBC(0, 0, &D_800AEFD0, D_801D7F90, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801288E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128940);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128998);

extern s32 D_801D7F90;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

void func_801289F0(void) {
    func_8001ABBC(0, 0, &D_800AECB8, D_801D7F90, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128A28);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128AF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128C14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128C98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128CFC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128D60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128DB4);

void func_80128EA8(s32 a0, s32 a1, s32 a2) {
    *(s32 *)(a1 + 0x0) = a2;                       /* sw a2, 0x0(a1) */
    *(s16 *)(a1 + 0x4) = 0;                         /* sh zero, 0x4(a1) */
    *(s16 *)(a1 + 0x6) = (*(s32 *)(a2 + 0x4)) & 0x3F; /* lw; andi 0x3F; sh 0x6(a1) */
    *(s16 *)(a0 + 0x28) = *(u16 *)(a2 + 0x0);      /* lhu 0x0(a2); sh 0x28(a0) */
    *(s16 *)(a0 + 0x2A) = *(u16 *)(a2 + 0x2);      /* lhu 0x2(a2); sh 0x2A(a0) */
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128ED8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80128FAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80129010);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801290DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012913C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801291C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80129220);

extern s16 D_8011DB2C;

void func_80129248(s16 a0) {
    D_8011DB2C = a0;
}


extern s16 D_8011DB30;

void func_80129258(void) {
    s16 *p = &D_8011DB30;
    s32 i = 0x7F;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0x38);
        i--;
    } while (i >= 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012927C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801292C8);

struct vec {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
};

void func_8012931C(struct vec *a0) {
    a0->unk4 += a0->unk10;
    a0->unk8 += a0->unk14;
    a0->unkC += a0->unk18;
}


void func_80129350(s32 a0, s32 a1) {
    *(s32 *)(a0 + 0x4) = *(s32 *)(a1 + 0x4);
    *(s32 *)(a0 + 0x8) = *(s32 *)(a1 + 0x8);
    *(s32 *)(a0 + 0xC) = *(s32 *)(a1 + 0xC);
}


void func_80129374(s32 a0, s32 a1) {
    *(s32 *)(a0 + 0x10) = *(s32 *)(a1 + 0x10);
    *(s32 *)(a0 + 0x14) = *(s32 *)(a1 + 0x14);
    *(s32 *)(a0 + 0x18) = *(s32 *)(a1 + 0x18);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80129398);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80129428);

extern s16 D_80114EE0;

void func_8012943C(void) {
    D_80114EE0 = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012944C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012956C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801298F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801299C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80129C40);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80129CF8);

extern void func_8012A018(s32 a, s32 b);

void func_80129FF4(void) {
    func_8012A018(0, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A018);

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;

void func_8012A048(void *a0, s32 a1, u8 a2) {
    *(s32 *)((s32)a0 + 0x0) = a1;
    *(u8 *)((s32)a0 + 0x4) = a2;
    *(s32 *)((s32)a0 + 0x9C) = 0;
    *(s16 *)((s32)a0 + 0xA0) = 0;
    *(s16 *)((s32)a0 + 0xA2) = 0;
    D_80126940 = D_80126B5E;
    D_80126942 = D_80126B62;
    D_80126944 = D_80126B66;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A094);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A0E0);

extern s8 D_801150D6;

void func_8012A100(s8 a0) {
    D_801150D6 = a0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A110);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A1BC);

extern s8 D_801152C0;

void func_8012A2F4(void) {
    D_801152C0 = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A304);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A328);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A418);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A464);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A4BC);

extern void func_8012A598(void *a0);

void func_8012A568(void (*a0)(void)) {
    func_8012A598(a0);
    a0();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A598);

extern void func_8012A62C(s32);

void func_8012A5F8(void (*a0)(void), s32 a1) {
    func_8012A62C(a1 & 0xFF);
    a0();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A62C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A68C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A6D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A758);

extern s32 ratan2(s32 a0, s32 a1);

s16 func_8012A79C(s16 *a0, s16 *a1) {
    s16 x0 = a0[0];
    s16 x1 = a1[0];
    s16 y0 = a0[2];
    s16 y1 = a1[2];
    return ratan2(x0 - x1, y0 - y1);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A7D4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A828);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A860);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A8B0);

extern void func_8012AAAC(void);

void func_8012A8E8(void) {
    func_8012AAAC();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A908);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012A988);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012AAAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012ACA0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012ACE0);

void func_8012AD44(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x2) = a1;
    *(s16*)((s32)a0 + 0x34) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012AD50);

void func_8012AD64(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x34) = a1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012AD6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012AD80);

void func_8012ADE4(u8 *a0) {
    *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
    *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
    *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012AE00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012AF0C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B030);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B0B4);

extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8012B14C(s32 a0, s32 a1) {
    func_800484EC(*(s32 *)((s32)a0 + 0x20) + 0x34, a1, (s32)a0 + 0x10);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B178);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B1B4);

void func_8012B200(u8 *a0) {
    *(s32 *)(a0 + 0x18) = 0;
    *(s32 *)(a0 + 0x14) = 0;
    *(s32 *)(a0 + 0x10) = 0;
    *(s32 *)(a0 + 0x4C) = 0;
    *(s32 *)(a0 + 0x48) = 0;
    *(s32 *)(a0 + 0x44) = 0;
}


void func_8012B21C(void *a0) {
    *(s32 *)((s32)a0 + 0x18) = 0;
    *(s32 *)((s32)a0 + 0x14) = 0;
    *(s32 *)((s32)a0 + 0x10) = 0;
    *(s32 *)((s32)a0 + 0x4C) = 0;
    *(s32 *)((s32)a0 + 0x44) = 0;
    *(s32 *)((s32)a0 + 0x48) = 0xC000;
}


void func_8012B23C(s32 a0) {
    *(s32 *)(a0 + 0x18) = 0;
    *(s32 *)(a0 + 0x14) = 0;
    *(s32 *)(a0 + 0x10) = 0;
    *(s32 *)(a0 + 0x4C) = 0;
    *(s32 *)(a0 + 0x44) = 0;
    *(s32 *)(a0 + 0x48) = 0x18000;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B260);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B2CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B370);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B414);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B4B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B608);

extern s32 ratan2(s32 a0, s32 a1);

s32 func_8012B6D4(s16 *a0, s16 *a1) {
    s16 ax = a0[5];
    s16 bx = a1[5];
    s16 by = a1[1];
    s16 ay = a0[1];
    return (ratan2(ax - bx, by - ay) - 0x400) & 0xFFF;
}


extern s32 ratan2(s32 a0, s32 a1);

s32 func_8012B70C(s16 *a0, s16 *a1) {
    s16 ax = a0[2];
    s16 bx = a1[2];
    s16 by = a1[0];
    s16 ay = a0[0];
    return (ratan2(ax - bx, by - ay) - 0x400) & 0xFFF;
}


extern s32 ratan2(s32 x, s32 y);

s32 func_8012B744(void *a0, void *a1) {
    s32 ang;
    ang = ratan2(*(s16 *)((s32)a0 + 0xA) - *(s16 *)((s32)a1 + 0x4),
                 *(s16 *)((s32)a1 + 0x0) - *(s16 *)((s32)a0 + 0x2));
    return (ang - 0x400) & 0xFFF;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B77C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B864);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B8A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012B8E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BA10);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BB3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BC60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BCCC);

extern void func_80013350(s32 a0, void *a1);
extern u8 D_80126B5C;

void func_8012BD14(s32 a0) {
    func_80013350(a0 + 4, &D_80126B5C);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BD3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BDBC);

extern void func_8012BE98(s32 a0, u16 *a1);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

void func_8012BE54(s32 a0) {
    u16 sp[3];
    sp[0] = D_80126B5E;
    sp[1] = D_80126B62;
    sp[2] = D_80126B66;
    func_8012BE98(a0, sp);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BE98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BEE8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BF10);

void func_8012BF4C(s32 *a0, s32 a1) {
    *(s32*)((s32)a0 + 0x1C) = a1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BF54);

/* func_8012BF68: lhu 0x5C; andi 0x7FFF; sh 0x5C; jr (sh in delay slot)
 * void form: no return value => no extra andi v0,0xffff truncation past the mask. */
void func_8012BF68(void *a0) {
    *(u16 *)((s32)a0 + 0x5C) &= 0x7FFF;
}


extern s16 D_80126CB0;

s32 func_8012BF7C(s16 *a0) {
    s32 diff;

    diff = a0[7] - D_80126CB0;
    if (diff < 0) {
        diff = -diff;
    }
    return diff >= 0x360;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012BFA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C044);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C098);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C0EC);

extern void func_8001D074(s32 a, s32 b);

void func_8012C194(void) {
    func_8001D074(0x3E, 0x7D);
}


extern void func_8001CFDC(s32 a, s32 b);

void func_8012C1B8(void) {
    func_8001CFDC(0x26, 0x85);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C1DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C218);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C284);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C2D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C31C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C354);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C438);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C51C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C588);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C658);

extern void func_8012C890(s32 a0, s32 a1, s32 a2);

void func_8012C724(s32 a0, s32 a1) {
    *(u16 *)((s32)a0 + 0xA) |= 0x8000;
    func_8012C890(a0, a1, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C750);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C820);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012C890);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012CAE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012CB64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012CBA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012CBCC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012CBF4);

extern void func_8012CC88(s32 a, s32 b, s32 c);

void func_8012CC1C(s32 arg0, s32 arg1) {
    func_8012CC88(arg0, 0, arg1);
}


extern void func_8012CC88(s32 a, s32 b, s32 c);

void func_8012CC40(s32 arg0, s32 arg1) {
    func_8012CC88(arg0, 1, arg1);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012CC64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012CC88);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012CE2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012CEB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012CFA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012D098);

extern void func_8012D098(int, int);

void func_8012D38C(int a0) {
    func_8012D098(a0, 0);
}


void func_8012D3AC(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012D3B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012D4B4);

void func_8012D5DC(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012D5E4);

extern void func_8012D664(void *a0);

void func_8012D624(s32 a0) {
    u16 sp[3];
    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA);
    sp[2] = *(u16 *)(a0 + 0xE);
    func_8012D664((void *)sp);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012D664);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012D714);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012DB84);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012DBD0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012DDA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012DE2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012DEB8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012DF34);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012DFBC);

void func_8012DFCC(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012DFD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E014);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E138);

s32 func_8012E27C(void) {
    return 1;
}


void func_8012E284(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E28C);

extern u8 D_800AF648;
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);

void func_8012E32C(void) {
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E364);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E470);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E4C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E504);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E544);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E57C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E5CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E688);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E778);

void func_8012E88C(u8 *a0) {
    s32 *p = *(s32 **)(a0 + 0x20);
    p[1] = p[1] & 0x7FFFFFFF;
}


void func_8012E8A8(u8 *a0) {
    s32 *p = *(s32 **)(a0 + 0x20);
    p[1] = p[1] | 0x80000000;
}


void func_8012E8C4(u8 *a0) {
    s32 *p = *(s32 **)(a0 + 0x20);
    p[1] = p[1] ^ 0x80000000;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E8E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012E9C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012EA90);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012EC04);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012EECC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012EF34);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012EF70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012EFB8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F038);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F0BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F14C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F1A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F214);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F274);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F2E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F374);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F40C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F49C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F568);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F5F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F68C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F75C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F7B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F828);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F87C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F8C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F91C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012F968);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012FB54);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012FC30);

extern void func_80131CA8(int a0, int a1);

void func_8012FCA4(int a0) {
    func_80131CA8(a0, 0x1B);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012FCC4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012FDA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012FE70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012FF00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012FF4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8012FF98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013001C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130088);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801300F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801301E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130278);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130314);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130360);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801303A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801303EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130438);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130514);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801305CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130650);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130740);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801307B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130858);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130898);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801308DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130974);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130A18);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130AC4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130AF0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130C08);

extern void (*D_80186EAC[])(void);

void func_80130D0C(void *a0) {
    D_80186EAC[*(u8 *)((s32)a0 + 0xC1)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80130D48);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131170);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801312D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131340);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801319E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131A34);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131AC8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131B14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131C78);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131CA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131CF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131D68);

struct S80131E00 {
    char pad[0xB0];
    s32 field_B0;
};

extern void (*D_80186FEC[])(struct S80131E00 *a0);

void func_80131E00(struct S80131E00 *a0, s32 a1) {
    a0->field_B0 = a1;
    D_80186FEC[a1](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131E38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131E7C);

void func_80131EE4(void) {
}

extern void (*D_80187044[])(void);

void func_80131EEC(void *a0) {
    D_80187044[*(u16 *)((s32)a0 + 0x2)]();
}


extern void (*D_8018708C[])(void);

void func_80131F28(void *a0) {
    D_8018708C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131F64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131FA0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80131FDC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80132018);

void func_801320D0(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801320D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80132144);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801321B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013221C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80132288);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013240C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801325B8);

void func_8013277C(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80132784);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80132DC4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80132E6C);

void func_80132EC4(void *a0, s16 a1) {
    while (*(s32 *)a0 != 0) {
        *(s16 *)((s32)a0 + 4) = a1;
        a0 = (void *)((s32)a0 + 8);
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80132EF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80132F40);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80133060);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801330E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80133298);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013339C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013361C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801336E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013373C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80133784);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80133AB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80133CD4);

typedef struct { s16 x, y, z; } Vec3s;

s32 func_80134310(Vec3s *a0, Vec3s *a1, s32 a2) {
    return a0->x * a1->x + a0->y * a1->y + a0->z * a1->z + a2;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013435C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801343C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80134510);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801345F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801347A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80134A28);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80134A74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80134C20);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80134FB8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80135004);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80135168);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80135260);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80135480);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80135888);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80135A4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80135D20);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80135EB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80136334);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801365B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80136824);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80136A94);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80136BC4);

extern void func_80136C3C(void);

void func_80136C1C(void) {
    func_80136C3C();
}


void func_80136C3C(void) {
}

void func_80136C44(void) {
}

void func_80136C4C(void) {
}

extern unsigned short D_800B99F0;
extern void (*D_801870C8[])(void);

void func_80136C54(void)
{
    D_801870C8[D_800B99F0]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80136C90);

void func_80136D00(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80136D08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80136DFC);

void func_80136EC4(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80136ECC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80136F3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80137030);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80137178);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801372B0);

extern void func_80137614(s32 a0, s32 a1, s32 a2);

void func_801375EC(s32 a0, s16 a1) {
    func_80137614(a0, a1, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80137614);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013767C);

extern void func_801376E8(int a0, int a1);

void func_801376C8(int a0) {
    func_801376E8(a0, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801376E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801377B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80137840);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801378F0);

extern s16 D_8012752E;

void func_801379D8(void) {
    D_8012752E = 1;
}


extern s16 D_8012752E;

void func_801379EC(void) {
    D_8012752E = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801379FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80137B80);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80137BD8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80137D08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80137DD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80137FD8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801380E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801387B8);

/* func_80138948: sh 7 @0x4; sb 0 @0x1F; sb 0 @0xD (store order = source order). */
void func_80138948(void *a0) {
    *(s16 *)((s32)a0 + 0x4)  = 7;
    *(s8  *)((s32)a0 + 0x1F) = 0;
    *(s8  *)((s32)a0 + 0xD)  = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013895C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80138AB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80138B88);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80138BE0);

void func_80138C30(void *a0) {
    if (*(s16 *)((s32)a0 + 4) == 4) {
        *(s16 *)((s32)a0 + 4) = 2;
    } else {
        *(u32 *)((s32)a0 + 8) |= 0x800;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80138C60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80138D58);

extern s32 func_80014E80(s32 a0, s32 a1);

s16 func_80138DB8(s32 a0, u8 a1, s32 a2) {
    return (s16)func_80014E80(a1, a2);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80138DE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80138ED0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013914C);

extern void func_80139634(void *);
extern void func_80139DC8(void);

void func_801391F0(void *a0) {
    *(s16 *)((s32)a0 + 0x12) = 0;
    *(s16 *)((s32)a0 + 0x14) = 0;
    *(s16 *)((s32)a0 + 0x16) = 0;
    func_80139634(a0);
    func_80139DC8();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139220);

extern void func_801395D4(void *);

void func_801392C8(void *a0) {
    func_801395D4(a0);
    *(s8 *)((s32)a0 + 0x1E) = 0;
    *(s16 *)((s32)a0 + 0x4) = 5;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801392FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801395D4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139634);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139680);

extern void func_8001931C(void);
extern s16 D_8012752C;

void func_80139788(void) {
    func_8001931C();
    D_8012752C = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801397B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139914);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139954);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801399A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801399F0);

extern s32 D_80127520;

void func_80139A34(s32 a0) {
    D_80127520 = a0;
}


extern s32 D_80127530[4];

void func_80139A44(s32 a0, u16 a1) {
    if (a1 < 4) {
        D_80127530[a1] = a0;
    }
}


extern s16 D_80127540[4];

void func_80139A68(s32 a0, u16 a1) {
    if (a1 < 4) {
        D_80127540[a1] = (s16)a0;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139A8C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139B18);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139BE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139C7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139D04);

extern s16 D_8012811A;

void func_80139DC8(void) {
    s32 i = 0x287;
    s16 *p = &D_8012811A;
    do {
        *p = 0;
        i--;
        p = (s16 *)((s32)p - 2);
    } while (i >= 0);
}


void func_80139DEC(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139DF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139E84);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139F0C);

struct obj {
    u8 pad0[0x4];
    s16 unk4;
    u8 pad6[0x2];
    s32 unk8;
};

void func_80139FBC(struct obj *a0) {
    if (a0->unk8 & 0x800) {
        a0->unk8 &= ~0x800;
        a0->unk4 = 2;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80139FE8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A0A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A164);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A1E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A250);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A2BC);

void func_8013A378(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A380);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A448);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A4C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A530);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A860);

void func_8013A8B0(s32 *a0) {
    *(s16*)((s32)a0 + 0x0) = 0;
    *(s32*)((s32)a0 + 0x4) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A8BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A8FC);

extern void func_8013A9F8(s32 a0, s32 a1);

void func_8013A9B4(s32 a0, s32 a1) {
    *(s16 *)(a1 + 0x2) = 0;
    *(s32 *)(a1 + 0x4) = a0;
    *(s32 *)(a0 + 0x40) = a1;
    *(s16 *)(a1 + 0x0) = 1;
    *(s16 *)(a1 + 0xC) = 0;
    *(s16 *)(a1 + 0xE) = 0;
    func_8013A9F8(a1, *(u16 *)(a0 + 0x18));
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013A9F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013AA24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013AB54);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013AD38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013AF20);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013B204);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013B274);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013B568);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013B598);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013B6A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013B7AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013B7F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013B83C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013BC7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013BCDC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013BD34);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013BD74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013C08C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013C0F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013C360);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013C414);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013C938);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013C964);

extern void func_80016714(void *a0, s32 a1);
extern s32 D_801D9568;
extern s32 D_801269D4;
extern s32 D_801269C8;

void func_8013C98C(void) {
    func_80016714(&D_801D9568, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013C9C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013CA14);

extern s32 D_801D958C;
extern s32 D_801D9580;
extern s32 D_801D9584;
extern s32 D_801D9590;

void func_8013CABC(void) {
    D_801D958C = 1;
    D_801D9580 = 1;
    D_801D9584 = 0;
    D_801D9590 = 1;
}


extern s32 D_801D9580;
extern s32 D_801D9584;
extern s32 D_801D9588;
extern s32 D_801D958C;
extern s32 D_801D9590;

void func_8013CAE8(void) {
    D_801D9580 = 1;
    D_801D958C = 0;
    D_801D9584 = 0;
    D_801D9588 = -1;
    D_801D9590 = 0;
}


extern s32 D_801D958C;
extern s32 D_801D9590;
extern s32 D_801D95B8;
extern s32 D_801D95BC;

void func_8013CB20(void)
{
    D_801D95B8 = D_801D9590;
    D_801D95BC = D_801D958C;
    D_801D9590 = 1;
    D_801D958C = 0;
}


extern s32 D_801D95B8;
extern s32 D_801D95BC;
extern s32 D_801D9590;
extern s32 D_801D958C;

void func_8013CB5C(void) {
    D_801D9590 = D_801D95B8;
    D_801D958C = D_801D95BC;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013CB84);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013CF68);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D064);

extern void func_8013D9B0(void);
extern s32 D_801D958C;

s32 func_8013D13C(void) {
    func_8013D9B0();
    return D_801D958C;
}


extern s32 D_801D9598;

void func_8013D164(void) {
    D_801D9598 = 1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D178);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D330);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D3D4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D53C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D8FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D9B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013DBE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013DD68);

extern s32 D_801D9594;

s32 func_8013E054(void) {
    return D_801D9594;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E064);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E0FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E194);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E22C);

extern s16 D_80126CB0;

s32 func_8013E298(s16 *a0) {
    s32 diff;

    diff = a0[2] - D_80126CB0;
    if (diff < 0) {
        diff = -diff;
    }
    return (u32)(diff - 0x2C1) < 0x3F;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E2C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E370);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E410);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E448);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E4B4);

extern void func_800D24A0(s32 a0);
extern void func_80141788(void);
extern void *D_8011DB24;

void func_8013E558(void) {
    func_800D24A0(2);
    D_8011DB24 = (void *)func_80141788;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E588);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E5E8);

extern void func_800D24A0(s32 a0);
extern void func_8013E5E8(void);
extern void *D_8011DB24;

void func_8013E67C(void) {
    func_800D24A0(0);
    D_8011DB24 = (void *)func_8013E5E8;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E6AC);

extern void func_800D24A0(s32 arg);
extern void func_8013E6AC(void);

void func_8013E814(void) {
    func_800D24A0(0);
    func_8013E6AC();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E83C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E958);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013EA54);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013EB7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013ED6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013EE10);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013EF88);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013F138);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013F1BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013F244);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013F350);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013FAF8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013FFD8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014032C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140608);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801407F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140958);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140D68);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140E6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140F00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141100);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801412A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801415C0);

extern u8 D_80115148[];
extern u8 D_80115149[];
extern u8 D_80115158[];

s16 func_8014168C(s16 a0) {
    s32 i = a0 * 2;
    return D_80115148[i] + D_80115149[i] * D_80115158[i];
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801416D4);

extern unsigned short D_80115112;
extern void (*D_80187F10[])(void);

void func_80141788(void)
{
    D_80187F10[D_80115112]();
}


extern void func_8001903C(void);
extern u16 D_80115112;

void func_801417C4(void) {
    u16 *p = &D_80115112;
    func_8001903C();
    *p = *p + 1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801417F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141874);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801418F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141A60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141B90);

void func_80141C04(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141C0C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141C50);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141CA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142414);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142454);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801424E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801425CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142608);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801426D4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142740);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142778);

void func_801427DC(void) {
}

void func_801427E4(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801427EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142838);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801428CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014292C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142978);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801429C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142A10);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142A80);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142B2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142BB4);

void func_80142C7C(void) {
}

void func_80142C84(s32 a0) {
    *(s32 *)(a0 + 0x14) = 0xFFF40000;
    *(s32 *)(a0 + 0x48) = 0x20000;
    *(s16 *)(a0 + 0x102) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142C9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142D38);

s32 func_80142DB8(s32 *a0) {
    return *(u16*)((s32)a0 + 0x5C) & 0x1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142DC4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142E38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142EC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142F68);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142FFC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014305C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801430F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143188);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801431E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801432FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143390);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801433F0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143458);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014350C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014358C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143640);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801437D8);

extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_80143970(s32 a0) {
    return func_8012C588(0x1B, a0);
}


extern void func_8012C658(s32 a0, s32 a1, s32 a2);

void func_80143994(s32 a0, s32 a1) {
    func_8012C658(0x1B, (s16)a1, a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801439C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801439FC);

extern void (*D_80188440[])(void *);

void func_80143B30(void *a0)
{
    D_80188440[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143B6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143BDC);

extern void (*D_8018844C[])(void *);

void func_80143C38(void *a0)
{
    D_8018844C[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143C74);

extern void (*D_80188454[])(void *);

void func_80143C98(void *a0)
{
    D_80188454[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143CD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143D28);

extern void (*D_8018849C[])(void *);

void func_80143E68(void *a0)
{
    D_8018849C[*(u16 *)((s32)a0 + 0x2)](a0);
}


void func_80143EA4(void) {
}

void func_80143EAC(void) {
}

void func_80143EB4(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143EBC);

extern void (*D_801884B0[])(void *);

void func_80144054(void *a0)
{
    D_801884B0[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144090);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801442F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144364);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144458);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144558);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014462C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801446A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014477C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144880);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144988);

extern void (*D_801884C0[])(void *);

void func_801449C8(void *a0)
{
    D_801884C0[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_80144A04(s32 *a0);

void func_80144A04(s32 *a0) {
    void (*fp)(void);
    fp = (void (*)(void))*(s32 *)((s32)a0 + 0xDC);
    fp();
}


extern void (*D_801884C8[])(void *);

void func_80144A2C(void *a0)
{
    D_801884C8[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144A68);

void func_80144A90(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144A98);

extern void func_80144B14(void);

void func_80144AEC(s32 *a0) {
    s32 old;
    old = *(s32 *)((s32)a0 + 0xDC);
    *(s32 *)((s32)a0 + 0xDC) = (s32)&func_80144B14;
    *(s16 *)((s32)a0 + 0x0) = 0x83;
    *(s16 *)((s32)a0 + 0x2) = 1;
    *(s32 *)((s32)a0 + 0xCC) = old;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144B14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144B9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801457A4);

void func_801458E0(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801458E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145934);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145A2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145B24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145BF8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145C54);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145CEC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145EE8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146014);

void func_80146074(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014607C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146128);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146360);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801463A0);

extern s32 D_80127098;
extern s32 D_80127094;
extern s32 D_80127090;
void func_80146534(void) {
    D_80127098 = 0;
    D_80127094 = 0;
    D_80127090 = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146554);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146578);

extern void func_8001CFDC(s32, s32);

void func_8014659C(void) {
    func_8001CFDC(6, 0x16);
}


extern void func_8001D074(s32, s32);

void func_801465C0(void) {
    func_8001D074(0x16, 0x3E);
}


extern void func_8001CFDC(s32, s32);

void func_801465E4(void) {
    func_8001CFDC(0x16, 0x26);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146608);

extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp5, s32 sp6, s32 sp7, s32 sp8);

void func_801466B4(u16 a0, s32 a1, s32 a2, s32 a3, s32 arg5) {
    func_801466F0(a0, a1, 0, 0, 0, a2, a3, arg5);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801466F0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146750);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014680C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801468C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146924);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146994);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801469C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146A6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146AB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146AFC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146B9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146C3C);

void func_80146C98(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x2) = a1;
}


/* func_80146CA0: lhu 0x2; addiu +1; sh 0x2; jr (sh in delay slot)
 * void form avoids a trailing andi v0,0xffff that a returned u16 value could force. */
void func_80146CA0(void *a0) {
    *(u16 *)((s32)a0 + 0x2) += 1;
}


/* func_80146CB4: lhu 0x2; addiu -1; sh 0x2; jr (sh in delay slot)
 * void form avoids a trailing andi v0,0xffff that a returned u16 value could force. */
void func_80146CB4(void *a0) {
    *(u16 *)((s32)a0 + 0x2) -= 1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146CC8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146D30);

void func_80146D80(s32 *a0) {
    *(s32*)((s32)a0 + 0x18) = 0;
    *(s32*)((s32)a0 + 0x14) = 0;
    *(s32*)((s32)a0 + 0x10) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146D90);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146DB8);

void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3) {
    *(s32*)((s32)a0 + 0x24) = a1;
    *(s32*)((s32)a0 + 0x28) = a2;
    *(s32*)((s32)a0 + 0x2C) = a3;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146DF8);

void func_80146E90(s32 *a0, s32 a1) {
    *(s32*)((s32)a0 + 0x1C) = a1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146E98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146EC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146F58);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146FC4);

void func_8014704C(s32 *a0) {
    *(s8*)((s32)a0 + 0x4C) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147054);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147060);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014706C);

void func_80147078(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x0) = a1;
    *(s16*)((s32)a0 + 0x2) = 0;
}


void func_80147084(s32 *a0) {
    *(s8*)((s32)a0 + 0x221) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014708C);

void func_80147098(s32 *a0) {
    *(s8*)((s32)a0 + 0x220) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801470A0);

void func_801470AC(s32 *a0) {
    *(s8*)((s32)a0 + 0x222) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801470B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801470C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147118);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147264);

extern s16 D_80126BB8;
extern s16 D_80126BBA;
extern s16 D_80126BBC;

void func_80147290(void) {
    D_80126BB8 = 0x1000;
    D_80126BBA = 0x1000;
    D_80126BBC = 0x1000;
}


/* func_801472B4: lhu 0x7E; andi 0xFFFD; sh 0x7E; jr (sh in delay slot)
 * void form: no return value => no extra truncation past the mask op. */
void func_801472B4(void *a0) {
    *(u16 *)((s32)a0 + 0x7E) &= 0xFFFD;
}


struct S {
    u8  pad0[0x7E]; /* 0x0..0x7D */
    u16 f7E;        /* 0x7E */
};

s32 func_801472C8(struct S *a0) {
    return a0->f7E = a0->f7E | 0x2;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801472DC);

extern void *D_8012707C;

void func_801472F0(void *a0) {
    D_8012707C = a0;
}


extern void func_80147364(u16, s32);

void func_80147300(u16 arg0) {
    func_80147364(arg0, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147324);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147364);

void func_801473DC(s32 *a0) {
    *(s32*)((s32)a0 + 0x18) = 0;
    *(s32*)((s32)a0 + 0x14) = 0;
    *(s32*)((s32)a0 + 0x10) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801473EC);

void func_80147460(s32 a0) {
    *(s32 *)(a0 + 0x8) += *(s32 *)(a0 + 0x34);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147478);

void func_801474D8(s32 *a0) {
    *(s16*)((s32)a0 + 0x136) = 0;
    *(s16*)((s32)a0 + 0x134) = 0;
    *(s16*)((s32)a0 + 0x132) = 0;
    *(s16*)((s32)a0 + 0x130) = 0;
}


void func_801474EC(s32 *a0) {
    *(s16 *)((s32)a0 + 0x11C) = 0;
    *(s16 *)((s32)a0 + 0x11A) = 0;
    *(s16 *)((s32)a0 + 0x118) = 0;
    *(s16 *)((s32)a0 + 0x124) = 0;
    *(s16 *)((s32)a0 + 0x122) = 0;
    *(s16 *)((s32)a0 + 0x120) = 0;
    *(s16 *)((s32)a0 + 0x12C) = 0;
    *(s16 *)((s32)a0 + 0x12A) = 0;
    *(s16 *)((s32)a0 + 0x128) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147514);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147628);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147718);

void func_80147788(void *a0, s32 a1) {
    void *v1 = *(void **)((s32)a0 + 0x20);
    *(s16 *)((s32)v1 + 0x10) = (*(u16 *)((s32)v1 + 0x10) + a1) & 0xFFF;
}


void func_801477A8(void *a0, s32 a1) {
    void *v1 = *(void **)((s32)a0 + 0x20);
    *(s16 *)((s32)v1 + 0x12) = (*(u16 *)((s32)v1 + 0x12) + a1) & 0xFFF;
}


void func_801477C8(void *a0, s32 a1) {
    void *v1 = *(void **)((s32)a0 + 0x20);
    *(s16 *)((s32)v1 + 0x14) = (*(u16 *)((s32)v1 + 0x14) + a1) & 0xFFF;
}


void func_801477E8(s32 *a0, s32 a1) {
    a0[0xD] = a1;
    if (a1 < -0x1F0000) {
        a0[0xD] = -0x1F0000;
    } else if (a1 > 0x1F0000) {
        a0[0xD] = 0x1F0000;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147814);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147860);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801478B8);

extern void func_80147948(int a0, int a1, int a2);

void func_80147928(int a0, int a1) {
    func_80147948(a0, a1, 0x1F0000);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147948);

extern void func_801479BC(int a0, int a1, int a2);

void func_8014799C(int a0, int a1) {
    func_801479BC(a0, a1, 0x1F0000);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801479BC);

extern void func_80147A30(int a0, int a1, int a2);

void func_80147A10(int a0, int a1) {
    func_80147A30(a0, a1, 0x1F0000);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147A30);

extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80147A84(s32 arg0) {
    func_80147AD4(arg0, 0, 0, 0);
}


extern void func_80147C30(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80147AAC(s32 arg0) {
    func_80147C30(arg0, 0, 0, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147AD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147B18);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147B5C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147C30);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147CC8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147D38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147DC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147E44);

extern void func_80147F78(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80147F50(s32 arg0) {
    func_80147F78(arg0, 0, 0, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147F78);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148038);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148094);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801483E8);

extern void func_801485B8(s32 a0, s32 a1, s32 a2);
extern s32 *D_80126B78;

void func_801484B0(s32 a0, s32 a1) {
    func_801485B8(*(s32 *)((s32)D_80126B78 + 0x20) - 0x10, a0, a1);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801484E8);

extern void func_801485B8(s32 a0, s32 a1, s32 a2);
extern s32 *D_80126B78;

void func_80148534(s32 a0, s32 a1) {
    func_801485B8(*(s32 *)((s32)D_80126B78 + 0x20) - 0x8, a0, a1);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014856C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801485B8);

/* func_80148634: ori v0,0x8080; sh 0 @0xAA; sh 0 @0xAC; sh 0x8080 @0xAE
 * 0x8080 loaded via ori (positive 16-bit imm) => store an unsigned 16-bit value. */
void func_80148634(void *a0) {
    *(u16 *)((s32)a0 + 0xAA) = 0;
    *(u16 *)((s32)a0 + 0xAC) = 0;
    *(u16 *)((s32)a0 + 0xAE) = 0x8080;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148648);

u16 func_801487F4(s32 *a0) {
    return *(u16*)((s32)a0 + 0xAA);
}


u16 func_80148800(s32 *a0) {
    return *(u16*)((s32)a0 + 0xAC);
}


u8 func_8014880C(s32 *a0) {
    return *(u8*)((s32)a0 + 0xAE);
}


u16 func_80148818(s32 *a0) {
    return *(u16*)((s32)a0 + 0xAE) >> 8;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148824);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801488A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014891C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148980);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801489E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148A48);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148AAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148AFC);

s32 func_80148C18(void) {
    return 0;
}


s32 func_80148C20(s32 a0, s16 a1) {
    s32 *p = *(s32 **)((s32)a0 + 0x20);
    *(s16*)((s32)p + 0x12) = a1;
    return 1;
}


s32 func_80148C34(s32 a0, s32 a1) {
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (a1 + 0x400) & 0xFFF;
    return 1;
}


s32 func_80148C4C(s32 a0, s32 a1) {
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (a1 + 0x200) & 0xFFF;
    return 1;
}


s32 func_80148C64(s32 a0, s32 a1) {
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (a1 + 0x800) & 0xFFF;
    return 1;
}


s32 func_80148C7C(void) {
    return 0;
}


s32 func_80148C84(s32 a0, s32 a1) {
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (a1 + 0x600) & 0xFFF;
    return 1;
}


typedef struct { char pad[0x12]; s16 field_0x12; } Obj;

s32 func_80148C9C(s32 a0, s32 a1) {
    Obj *p = *(Obj **)((s32)a0 + 0x20);
    p->field_0x12 = (a1 + 0x400) & 0xFFF;
    return 1;
}


/* func_80148CB4: addiu a1,-0x400; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1
 * v0 = *(a0+0x20) deref; store (a1-0x400)&0xFFF as halfword at v0+0x12; return 1. */
s32 func_80148CB4(s32 a0, s32 a1) {
    s32 v0 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v0 + 0x12) = (a1 - 0x400) & 0xFFF;
    return 1;
}


/* func_80148CCC: addiu a1,-0x200; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1 */
s32 func_80148CCC(s32 a0, s32 a1) {
    s32 v0 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v0 + 0x12) = (a1 - 0x200) & 0xFFF;
    return 1;
}


s32 func_80148CE4(void) {
    return 0;
}


s32 func_80148CEC(void) {
    return 0;
}


/* func_80148CF4: addiu a1,-0x600; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1 */
s32 func_80148CF4(s32 a0, s32 a1) {
    s32 v0 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v0 + 0x12) = (a1 - 0x600) & 0xFFF;
    return 1;
}


/* func_80148D0C: addiu a1,-0x400; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1 */
s32 func_80148D0C(s32 a0, s32 a1) {
    s32 v0 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v0 + 0x12) = (a1 - 0x400) & 0xFFF;
    return 1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148D24);

s32 func_80148D3C(void) {
    return 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148D44);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148E54);

s32 func_80148F60(void) {
    return -1;
}


s32 func_80148F68(s32 a0) {
    return (s16)a0;
}


s32 func_80148F74(s32 a0) {
    return (a0 + 0x400) & 0xFFF;
}


s32 func_80148F80(s32 a0) {
    return (a0 + 0x200) & 0xFFF;
}


s32 func_80148F8C(s32 a0) {
    return (a0 + 0x800) & 0xFFF;
}


s32 func_80148F98(void) {
    return -1;
}


s32 func_80148FA0(s32 a0) {
    return (a0 + 0x600) & 0xFFF;
}


s32 func_80148FAC(s32 a0) {
    return (a0 + 0x400) & 0xFFF;
}


s32 func_80148FB8(s32 a0) {
    return (a0 - 0x400) & 0xFFF;
}


s32 func_80148FC4(s32 a0) {
    return (a0 - 0x200) & 0xFFF;
}


s32 func_80148FD0(void) {
    return -1;
}


s32 func_80148FD8(void) {
    return -1;
}


s32 func_80148FE0(s32 a0) {
    return (a0 - 0x600) & 0xFFF;
}


s32 func_80148FEC(s32 a0) {
    return (a0 - 0x400) & 0xFFF;
}


s32 func_80148FF8(s32 a0) {
    return (a0 - 0x800) & 0xFFF;
}


s32 func_80149004(void) {
    return -1;
}


void func_8014900C(s32 *a0) {
    *(u16*)((s32)a0 + 0x3C) |= 0x8000;
}


void func_80149020(s32 *a0) {
    *(u16*)((s32)a0 + 0x3C) &= 0x7FFF;
}


void func_80149034(s32 *a0) {
    *(u16*)((s32)a0 + 0x3C) |= 0x4000;
}


void func_80149048(s32 *a0) {
    *(u16*)((s32)a0 + 0x3C) &= 0xBFFF;
}


void func_8014905C(u8 *a0) {
    *(s16 *)(a0 + 0x104) = 0;
    *(s16 *)(a0 + 0x102) = 0;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x10C) = 0;
    *(s16 *)(a0 + 0x10A) = 0;
    *(s16 *)(a0 + 0x108) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149078);

void func_801490E0(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x108) = a1;
}


void func_801490E8(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x10A) = a1;
}


void func_801490F0(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x10C) = a1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801490F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149184);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801491C4);

void func_80149204(s32 *a0) {
    *(s32*)((s32)a0 + 0x1E4) = 0;
    *(s32*)((s32)a0 + 0x1DC) = 0;
}


void func_80149210(s32 a0, s32 a1) {
    *(s32 *)((s32)a0 + 0x1E4) = a1 | (a1 << 16);
    *(s16 *)((s32)a0 + 0x1E4) = a1;
    *(s16 *)((s32)a0 + 0x1E6) = a1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149228);

s32 func_80149284(s32 *a0, s32 a1) {
    return *(s32*)((s32)a0 + 0x1DC) & a1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149290);

extern void func_8012F14C(s32);

void func_80149350(s32 arg0) {
    func_8012F14C(*(s32 *)(arg0 + 0x20) + 0x34);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149374);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801493D0);

extern void func_8012F038(s32);

void func_8014942C(s32 arg0) {
    func_8012F038(*(s32 *)(arg0 + 0x20) + 0x34);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149450);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801494CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149544);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149584);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801495C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014964C);

s32 func_801496D4(void *a0) {
    s32 v0 = 0;
    if (*(s32 *)((s32)a0 + 0x178)) {
        return v0;
    }
    v0 = *(u16 *)((s32)a0 + 0xAC) & 0x40;
    if (v0) {
        v0 = 1;
    }
    return v0;
}


extern void func_8015AD08(void);

void func_80149704(void) {
    func_8015AD08();
}


extern void func_8015ACC4(void);

void func_80149724(void) {
    func_8015ACC4();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149744);

extern void func_8015F7A0(void);

void func_80149788(void) {
    func_8015F7A0();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801497A8);

extern void func_801653B8(void);

void func_80149864(void) {
    func_801653B8();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149884);

extern void func_80160B00(void);

void func_801498C0(void) {
    func_80160B00();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801498E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149954);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149A64);

s32 func_80149AA8(s32 *a0) {
    s32 v0;
    if (a0[0x44 / 4] & 0x404) {
        v0 = 0;
    } else {
        v0 = *(u16 *)((s32)a0 + 0xAC) & 0x80;
        v0 = v0 != 0;
    }
    return v0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149AD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149B14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149B54);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149BAC);

void func_80149BEC(s32 a0) {
    u8 v = *(u8 *)(a0 + 0x223);
    if (v != 0) {
        *(u8 *)(a0 + 0x223) = v - 1;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149C08);

extern void func_801577C8(void);

void func_80149C94(void) {
    func_801577C8();
}


extern void func_80157D20(void);

void func_80149CB4(void) {
    func_80157D20();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149CD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149D10);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149D9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149DD8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149E94);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149F2C);

void func_80149FA8(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149FB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A048);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A1B0);

extern void func_8015D4B4(void);

void func_8014A218(void) {
    func_8015D4B4();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A238);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A2E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A380);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A3E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A454);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A4B4);

extern void func_8015EDD4(void);

void func_8014A4FC(void) {
    func_8015EDD4();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A51C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A59C);

void func_8014A638(s32 arg0) {
    s16 v;
    if (*(s32 *)((s32)arg0 + 0x44) & 0x10) {
        v = *(u16 *)((s32)arg0 + 0x188) - 4;
        *(s16 *)((s32)arg0 + 0x188) = v;
        if (v < 0) {
            *(s16 *)((s32)arg0 + 0x188) = 0;
        }
    }
}


s32 func_8014A674(s32 *a0) {
    return *(u8*)((s32)a0 + 0x1BC) < 1;
}


void func_8014A680(s32 a0) {
    u8 v = *(u8 *)(a0 + 0x1BC);
    if (v != 0) {
        *(u8 *)(a0 + 0x1BC) = v - 1;
    }
}


s32 func_8014A69C(s32 *a0) {
    return *(u8*)((s32)a0 + 0x1BD) == 0;
}


void func_8014A6A8(s32 a0) {
    u8 v = *(u8 *)(a0 + 0x1BD);
    if (v != 0) {
        *(u8 *)(a0 + 0x1BD) = v - 1;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A6C4);

void func_8014A71C(s32 a0) {
    u8 v = *(u8 *)(a0 + 0x1BE);
    if (v != 0) {
        *(u8 *)(a0 + 0x1BE) = v - 1;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A738);

extern void func_8015E184(void);

void func_8014A830(void) {
    func_8015E184();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A850);

extern u8 D_80078EC0;

void func_8014AA04(s32 a0) {
    D_80078EC0 = a0 | (D_80078EC0 & 0x80);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014AA28);

extern void func_8014AB7C(void);

void func_8014AB5C(void) {
    func_8014AB7C();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014AB7C);

extern void func_8014AC10(void);

void func_8014ABF0(void) {
    func_8014AC10();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014AC10);

void func_8014ACC0(s32 a0, s32 a1) {
    s16 v0;
    v0 = *(u16 *)((s32)a0 + 0x1C8) - a1;
    *(s16 *)((s32)a0 + 0x1C8) = v0;
    if (v0 < 0) {
        *(s16 *)((s32)a0 + 0x1C8) = 0;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014ACE8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014AD30);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014AD7C);

extern s32 D_80078E8C;

void func_8014ADA8(s32 a0, s32 a1) {
    s32 v0;
    v0 = D_80078E8C + a1;
    D_80078E8C = v0;
    if (0x1869F < (u32)v0) {
        D_80078E8C = 0x1869F;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014ADE0);

extern void func_8014B034(s32 arg0);

void func_8014B00C(s32 arg0) {
    func_8014B034(arg0 * 60);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B034);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B084);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B12C);

s32 func_8014B154(s32 *a0) {
    return *(s32*)((s32)a0 + 0x44) & 0x80;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B160);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B190);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B2A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B2D0);

extern s32 D_80078E94;
extern s32 D_80078ECC;

void func_8014B2F8(void) {
    D_80078E94 = 0;
    D_80078ECC = 0;
}


extern void func_8014B33C(void);
extern s32 D_80078ECC;

void func_8014B310(void) {
    func_8014B33C();
    D_80078ECC = 0x80000000;
}


extern s32 D_80078E94;

void func_8014B33C(void) {
    D_80078E94 = 0x80000000;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B350);

extern s32 D_80078E98;

void func_8014B4C4(void) {
    D_80078E98 = 0;
}


extern void func_80166244(void);
extern s32 D_80078E98;

void func_8014B4D4(void *a0) {
    *(u16 *)((s32)a0 + 0x1C8) = 0;
    D_80078E98 = 0x80000000;
    func_80166244();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B504);

extern u8 D_80126D1C;
extern s32 D_80126D74;

void func_8014B598(s32 a0, s32 a1) {
    D_80126D1C = a0;
    D_80126D74 = a1;
}


void func_8014B5B0(s32 *a0) {
    *(s8*)((s32)a0 + 0x1C4) = 0;
}


u8 func_8014B5B8(s32 *a0) {
    return *(u8*)((s32)a0 + 0x1C4);
}


void func_8014B5C4(s32 *a0, s32 a1, s32 a2) {
    *(s8*)((s32)a0 + 0x1C7) = a1 | a2;
}


void func_8014B5D0(s32 *a0) {
    *(s8*)((s32)a0 + 0x1C7) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B5D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B6F0);

extern s32 D_80078E9C;

void func_8014B768(s32 a0, s32 a1) {
    D_80078E9C -= a1;
    if (*(s16 *)((s32)&D_80078E9C + 2) < 0) {
        D_80078E9C = 0;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B7A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014B944);

extern u16 D_80078EB2;
extern s16 D_80078EB4;

void func_8014BB0C(void) {
    D_80078EB4 = D_80078EB2;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014BB24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014BC0C);

extern u16 D_80078EB2;
extern void func_8014BC80(s32 a0, s32 a1);

void func_8014BC44(s32 a0, s32 a1) {
    if (*(s32 *)((s32)a0 + 0x44) & 0x2000000) {
        a1 = D_80078EB2;
    }
    func_8014BC80(a0, a1);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014BC80);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014BCC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014BCEC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014BD24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014BD60);

extern u16 D_80078EB6;
extern s16 D_80078EB8;

void func_8014BD98(s32 a0, u16 a1) {
    D_80078EB8 = a1;
    if (D_80078EB6 < a1) {
        D_80078EB8 = D_80078EB6;
    }
}


extern u16 D_80078EB6;
extern s16 D_80078EB8;

void func_8014BDC8(void) {
    D_80078EB8 = D_80078EB6;
}


void func_8014BDE0(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014BDE8);

extern void func_80029124(s32, s32);

void func_8014BE78(void) {
    func_80029124(0x12F, 1);
}


extern void func_80029124(s32, s32);

void func_8014BE9C(void) {
    func_80029124(0x12F, 0);
}


extern void func_80029124(s32 a0, s32 a1);
extern u8 D_80078EC0;

void func_8014BEC0(void) {
    D_80078EC0 |= 1;
    func_80029124(0x80, 1);
}


extern s32 func_80029178(s32 arg);

u8 func_8014BEF8(void) {
    return func_80029178(0x80);
}


extern void func_800291A0(s32, s32);

void func_8014BF18(s32 a0) {
    if (a0 < 0) {
        a0 = 0;
    }
    func_800291A0(0xCF, a0 & 0xFF);
}


extern void func_800291A0(s32, s32);

void func_8014BF48(void) {
    func_800291A0(0xCF, 0);
}


extern s32 func_800291B4(s32 arg);

u8 func_8014BF6C(void) {
    return func_800291B4(0xCF);
}


extern void func_800291A0(s32, s32);

void func_8014BF8C(u8 arg0) {
    func_800291A0(0xD0, arg0);
}


extern void func_800291A0(s32, s32);

void func_8014BFB0(void) {
    func_800291A0(0xD0, 0);
}


extern s32 func_800291B4(s32 arg);

u8 func_8014BFD4(void) {
    return func_800291B4(0xD0);
}


void func_8014BFF4(s32 a0, s32 a1) {
    if (*(u8 *)(a0 + 0x4E) == 0) {
        *(u8 *)(a0 + 0x4E) = a1;
    }
}


extern void func_80146AFC(void *a0);

struct S8014C010 {
    s16 h0;
    s16 h1;
    s16 h2;
    s16 h3;
    s32 w8;
    s32 wC;
    s32 w10;
};

void func_8014C010(s32 a0, s32 a1) {
    struct S8014C010 sp;
    sp.w8 = a0;
    sp.h0 = 2;
    sp.h1 = 0;
    sp.h2 = 0;
    sp.h3 = 0;
    sp.wC = a1;
    sp.w10 = 0;
    func_80146AFC(&sp);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C050);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C088);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C0C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C118);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C168);

extern void func_8014C1C8(s32 arg0, s32 arg1, void *arg2);
extern u8 D_8018875C[];

void func_8014C1A0(s32 arg0, s32 arg1) {
    func_8014C1C8(arg0, arg1, D_8018875C);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C1C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C278);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C2B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C308);

extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);

s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3) {
    return func_8014C43C(a0, a1, a2, a3, *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12));
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C3D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C43C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C4AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C568);

extern s32 ratan2(s32 dx, s32 dy);

s32 func_8014C59C(void *a0, void *a1) {
    s32 dx = *(s16 *)((s32)a0 + 0x6) - *(s16 *)((s32)a1 + 0x6);
    s32 dy = *(s16 *)((s32)a0 + 0xE) - *(s16 *)((s32)a1 + 0xE);
    return ratan2(dx, dy) & 0xFFF;
}


extern u8 D_80188764;
extern s32 func_8014C5FC(s32 a0, s32 a1, void *a2);

s16 func_8014C5D0(s32 a0, s32 a1) {
    return func_8014C5FC(a0, a1, &D_80188764);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C5FC);

extern u8 D_80126D17;

void func_8014C6AC(void) {
    D_80126D17 = 1;
}


extern u8 D_80126D17;

void func_8014C6C0(void) {
    D_80126D17 = 0;
}


extern u8 D_80126D1E;

void func_8014C6D0(void) {
    D_80126D1E = 0;
}


extern u8 D_80126D1E;

void func_8014C6E0(void) {
    D_80126D1E = 1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C6F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C860);

extern void func_80015978(s32 a0, s32 *a1);
extern void func_8014C8C8(s32 a0, s32 *a1);

void func_8014C88C(s32 a0) {
    s32 sp10;
    func_80015978(a0 + 4, &sp10);
    func_8014C8C8(a0, &sp10);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C8C8);

struct UnalignedPair {
    int a;
    int b;
} __attribute__((packed, aligned(1)));

void func_8014C8F0(s32 arg0) {
    *(struct UnalignedPair *)(arg0 + 0x15c) = *(struct UnalignedPair *)(arg0 + 0x90);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C918);

extern s32 D_80126B50;

void func_8014C968(void) {
    D_80126B50 = 0;
}


extern s32 D_80126B50;

void func_8014C978(void) {
    D_80126B50 = 1;
}


extern s32 D_80126B50;

s32 func_8014C98C(void) {
    return D_80126B50;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C99C);

s32 func_8014CA00(s32 a0) {
    s32 *p = *(s32 **)((s32)a0 + 0x78);
    return *(s16*)((s32)p + 0x2C);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014CA14);

u16 func_8014CA70(s32 a0, s32 a1) {
    s32 base = *(s32 *)((s32)a0 + 0x78);
    return *(u16 *)((a1 << 1) + base + 0x14);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014CA88);

u16 func_8014CAE4(s32 *a0, s32 a1) {
    s32 base = a0[0x78 / 4];
    return *(u16 *)(base + a1 * 2 + 0x1C);
}


extern s32 D_80126B9C;

s32 func_8014CAFC(void) {
    return D_80126B9C & 0x400;
}


extern s32 D_80126B9C;

s32 func_8014CB0C(void) {
    return D_80126B9C & 0x80;
}


extern s32 D_80078E94;

s32 func_8014CB1C(void) {
    return D_80078E94;
}


extern u8 D_80126D1F;

s32 func_8014CB2C(void) {
    s32 v1 = D_80126D1F;
    if (v1 & 0x80) {
        v1 = (v1 & 0x7F) | 0x80000000;
    }
    return v1;
}


extern u8 D_80078EC0;

s32 func_8014CB58(void) {
    return D_80078EC0 & 0x7F;
}


extern u8 D_80126D1D;

void func_8014CB68(void)
{
    D_80126D1D = 1;
}


extern s32 D_80126B9C;

s32 func_8014CB7C(void) {
    return D_80126B9C & 0x800;
}


extern s32 D_80126B9C;

s32 func_8014CB8C(void) {
    return D_80126B9C & 0x1000;
}


struct Packed8 {
    int a;
    int b;
} __attribute__((packed));

extern struct Packed8 D_80126C98;
extern short D_80126C9E;

void func_8014CB9C(struct Packed8 *a0)
{
    D_80126C98 = *a0;
    D_80126C9E = 1;
}


extern s32 D_80126CDC;

void func_8014CBD8(void) {
    D_80126CDC = 0;
}


extern s16 D_80126CC4;

void func_8014CBE8(void) {
    D_80126CC4 = 0;
}


void func_8014CBF8(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x174);
    if (v1 != 0) {
        if (*(u16 *)(v1 + 0) != 0) {
            *(s32 *)((s32)a0 + 0x174) = 0;
            *(s8 *)(v1 + 0x74) = 0;
        }
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014CC28);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014CCB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014CD0C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014CD80);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014CF04);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D04C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D0A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D12C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D2A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D3E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D438);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D4C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D610);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D738);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D790);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D820);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014DCE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014DD8C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014DF3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014DF94);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E048);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E284);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E434);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E48C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E514);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E5B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E6A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E6F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E790);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E83C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E934);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E98C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014EA4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014ED28);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014ED80);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014EE14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F1F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F24C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F2E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F3E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F468);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F4C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F6F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F74C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FA04);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FA70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FBC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FC18);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FCFC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FD54);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FDF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FE60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FFDC);

extern s32 func_80134510(s32 arg);

s32 func_80150150(s32 a, s32 b) {
    return func_80134510(b) != 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150170);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801502EC);

extern s32 func_80134510(s32 arg);

s32 func_80150460(s32 a, s32 b) {
    return func_80134510(b) != 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150480);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801504D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150528);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801505FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801506A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150820);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015086C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801508B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801508F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015094C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150A70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150B28);

void func_80150B9C(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150BA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150BC8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150C48);

extern int func_80151184(int arg, int a1, int a2);

int func_80150CA0(int arg) {
    return func_80151184(arg, 0xE001, 0x10);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150CC4(s32 a) {
    func_80150EC4(a, 0);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150CE4(s32 a) {
    func_80150EC4(a, 1);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150D04(s32 a) {
    func_80150EC4(a, 2);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150D24(s32 a) {
    func_80150EC4(a, 3);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150D44(s32 a) {
    func_80150EC4(a, 4);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150D64(s32 a) {
    func_80150EC4(a, 5);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150D84(s32 a) {
    func_80150EC4(a, 6);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150DA4(s32 a) {
    func_80150EC4(a, 7);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150DC4(s32 a) {
    func_80150EC4(a, 8);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150DE4(s32 a) {
    func_80150EC4(a, 9);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150E04(s32 a) {
    func_80150EC4(a, 10);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150E24(s32 a) {
    func_80150EC4(a, 11);
}


extern void func_80150EC4(s32 a, s32 b);

void func_80150E44(s32 a) {
    func_80150EC4(a, 12);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150E64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150E84);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150EA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150EC4);

void func_80150F78(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150F80);

extern int func_80151184(int arg, int a1, int a2);

int func_80150FB4(int arg) {
    return func_80151184(arg, 0x8, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150FD8);

extern int func_80151184(int arg, int a1, int a2);

int func_80151014(int arg) {
    return func_80151184(arg, 0xC00B, 0x20);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151038);

extern int func_80151184(int arg, int a1, int a2);

int func_80151070(int arg) {
    return func_80151184(arg, 0xE003, 0x10);
}


extern int func_80151184(int arg, int a1, int a2);

int func_80151094(int arg) {
    return func_80151184(arg, 0xC00D, 0x18);
}


void func_801510B8(void) {
}

void func_801510C0(void) {
}

extern int func_80151184(int arg, int a1, int a2);

int func_801510C8(int arg) {
    return func_80151184(arg, 0x4018, 0x20);
}


extern int func_80151184(int arg, int a1, int a2);

int func_801510EC(int arg) {
    return func_80151184(arg, 0xE016, 0x10);
}


extern s32 func_8012DB84(void);

s32 func_80151110(void) {
    return func_8012DB84();
}


void func_80151130(void) {
}

extern int func_80151184(int arg, int a1, int a2);

int func_80151138(int arg) {
    return func_80151184(arg, 0xC01F, 0x10);
}


void func_8015115C(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x16C) = a1;
}


extern s32 func_80151184(s32 a0, s32 a1, s32 a2);

s32 func_80151164(s32 a0, s32 a1) {
    return func_80151184(a0, a1, 0xA);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151184);

void func_801511A8(u8 *a0) {
    u16 v = *(u16 *)(a0 + 0x3C);
    *(s16 *)(a0 + 0x3E) = 0;
    *(s16 *)(a0 + 0x40) = 0;
    *(s16 *)(a0 + 0x42) = 0;
    *(u16 *)(a0 + 0x3C) = v & 0xFFFE;
}


void func_801511C4(u8 *a0) {
    *(u16 *)(a0 + 0xF0) = *(u16 *)(a0 + 0x3E);
    *(u16 *)(a0 + 0xF2) = *(u16 *)(a0 + 0x40);
    *(u16 *)(a0 + 0xF4) = *(u16 *)(a0 + 0x42);
}


extern int func_80151204(int arg, int a1);

int func_801511E0(int arg) {
    return func_80151204(arg, *(short *)((int)arg + 0xF2));
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151204);

extern void func_8014ACE8(void *a0, s32 a1, s32 a2);

void func_80151238(void *a0) {
    s16 v0 = *(s16 *)((s32)a0 + 0xF2);
    if (v0 != 0) {
        func_8014ACE8(a0, 5, (s32)v0 & 0x7FFF);
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015126C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151664);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801516F0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015173C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151780);

void func_80151878(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151880);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801518D8);

extern s32 func_80151944(void);

s32 func_80151924(void) {
    return func_80151944();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151944);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151980);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801519C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151AE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151B98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151C54);

extern void (*D_8018883C[])(void *);

void func_80151D24(void *a0)
{
    D_8018883C[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151D60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151DB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151E78);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151ECC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151F38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151FB4);

extern void (*D_80188860[])(void *);

void func_80152058(void *a0)
{
    D_80188860[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152094);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801520DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152194);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015220C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152254);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801522CC);

extern void (*D_80188874[])(void *);

void func_80152370(void *a0)
{
    D_80188874[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801523AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801523F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152500);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801525F4);

extern void (*D_80188890[])(void *);

void func_80152698(void *a0)
{
    D_80188890[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801526D4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152714);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152790);

extern void (*D_801888A8[])(void *);

void func_8015282C(void *a0)
{
    D_801888A8[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152868);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801528B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015294C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152A08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152A50);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152AC8);

extern void (*D_801888BC[])(void *);

void func_80152B6C(void *a0)
{
    D_801888BC[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152BA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152BF0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152C40);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152C80);

extern void (*D_801888D8[])(void *);

void func_80152D24(void *a0)
{
    D_801888D8[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152D60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152DA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152E4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152EFC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152F44);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152FBC);

extern void (*D_801888EC[])(void *);

void func_80153060(void *a0)
{
    D_801888EC[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015309C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801530E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153150);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801531BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153204);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015327C);

extern void (*D_80188900[])(void *);

void func_80153320(void *a0)
{
    D_80188900[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015335C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801533A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153410);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153490);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801534D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153550);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801535F4);

extern void (*D_8011DB28)(s32 a0);

void func_8015369C(s32 a0) {
    if (D_8011DB28 != 0) {
        D_8011DB28(a0 + 0xA0);
    }
    *(u8 *)(a0 + 0xDE) = 0x5A;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801536DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153800);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153978);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801539F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153B58);

extern s32 D_801151FC;

s32 func_80153BD8(s32 a0) {
    return (a0 ^ D_801151FC) == 0;
}


extern s32 D_801151FC;
extern s32 D_80127518;

s32 func_80153BF0(s32 a0) {
    if (a0 == D_801151FC) {
        D_80127518 = 0;
        return 1;
    }
    return 0;
}


extern s32 D_80127518;
extern s32 D_801151FC;

void func_80153C18(void) {
    D_80127518 = 0;
    D_801151FC = 0;
}


extern u16 D_8011F748;

void func_80153C30(void)
{
    D_8011F748 = 1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153C44);

extern s16 D_8011DB0C;
extern s16 D_8011DB1A;

void func_80153C74(s16 a0, s16 a1) {
    D_8011DB0C = a0;
    D_8011DB1A = a1;
}


extern s32 D_80115210;

void func_80153C8C(void) {
    D_80115210 = 0;
}


extern s32 D_80115210;

void func_80153C9C(void) {
    D_80115210 = D_80115210 + 1;
}


extern s32 D_80115210;

s32 func_80153CBC(void) {
    return D_80115210;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153CCC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153D34);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153D7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153E00);

extern void func_80151664(void);
extern s32 D_80127518;

void func_8015410C(void) {
    D_80127518 = 0;
    func_80151664();
}


void func_80154134(u8 *a0) {
    *(s32 *)(a0 + 0xB4) = 0;
    *(s16 *)(a0 + 0xBA) = 0;
    *(s16 *)(a0 + 0xB8) = 0;
    a0[0xBD] = 0;
    a0[0xBC] = 0;
    a0[0xDC] = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154150);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154190);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801541D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154218);

extern void func_801542A4(void);

void func_80154274(s32 *a0, s32 a1) {
    if (*(s32 *)((s32)a0 + 0xB4) != a1) {
        func_801542A4();
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801542A4);

extern void func_8015430C(void);

void func_801542DC(s32 *a0, s32 a1) {
    if (*(s32 *)((s32)a0 + 0xB4) != a1) {
        func_8015430C();
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015430C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154358);

extern void func_8015444C(void *a0, s32 *a1, s32 *a2, s32 *a3);

void func_80154418(void *a0) {
    s32 sp10 = 0;
    s32 sp14 = 0;
    s32 sp18 = 0;
    func_8015444C(a0, &sp10, &sp14, &sp18);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015444C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801549F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154A74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154AB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154AE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154B20);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154B4C);

void func_80154B7C(u8 *a0, s32 a1) {
    *(s32 *)(a0 + 0xD0) = a1;
    *(s16 *)(a0 + 0xD6) = 1;
    *(s16 *)(a0 + 0xD4) = 1;
    a0[0xD8] = 0;
    a0[0xD9] = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154B98);

void func_80154BC8(void *a0, s32 a1, s32 a2) {
    *(s32 *)((s32)a0 + 0xD0) = a1;
    *(s16 *)((s32)a0 + 0xD6) = 1;
    *(s16 *)((s32)a0 + 0xD4) = 1;
    *(s8 *)((s32)a0 + 0xD8) = a2;
    *(s8 *)((s32)a0 + 0xD9) = a2;
}


void func_80154C24(s32 a0, s32 *a1, s32 *a2);
void func_80154F9C(s32 a0);

void func_80154BE4(s32 a0) {
    s32 sp10;
    s32 sp14;
    sp10 = 0;
    sp14 = 0;
    func_80154C24(a0, &sp10, &sp14);
    func_80154F9C(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154C24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154ED8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154F9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801550FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155150);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801552F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155344);

s32 func_80155394(s32 *a0)
{
    return (a0[0x11] |= 0x20000000);
}


void func_801553A8(s32 *a0) {
    *(s32 *)((s32)a0 + 0x44) &= 0xDFFFFFFF;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801553C0);

void func_80155440(s32 *a0) {
    *(s32 *)((s32)a0 + 0x44) &= 0xEFFFFFFF;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155458);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801554B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155518);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015554C);

extern void (*D_8018898C[])(void *);

void func_80155580(void *a0)
{
    D_8018898C[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801555BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801555F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155800);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155A44);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155B20);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155B9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155C0C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155C64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155D70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155E30);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155EA4);

void func_80155F58(void) {
}

extern s32 func_80155F80(void);

s32 func_80155F60(void) {
    return func_80155F80();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155F80);

extern int func_80155FF8(int arg, int a1);

int func_80155FB0(int arg, int a1) {
    return func_80155FF8(arg, a1 | 0x10000);
}


extern int func_80155FF8(int arg, int a1);

int func_80155FD4(int arg, int a1) {
    return func_80155FF8(arg, a1 | 0x20000);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155FF8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156044);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015616C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156370);

typedef struct { s32 a, b, c; } S801563EC;

extern S801563EC D_80188B80[];

S801563EC *func_801563EC(u16 idx) {
    return &D_80188B80[idx];
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015640C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801564B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801565C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156600);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156648);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156670);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801567BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156848);

void func_80156A14(s32 *a0) {
    *(s8*)((s32)a0 + 0xDA) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156A1C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156A88);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156B74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156ECC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156FA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157158);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801571C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801574DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157510);

extern void (*D_80188E00[])(void *);

void func_80157544(void *a0)
{
    D_80188E00[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157580);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801575E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801576A8);

extern s32 func_8015773C(u8 *a0);

s32 func_8015771C(u8 *a0) {
    a0[0x1AA] = 0;
    return func_8015773C(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015773C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157788);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801577C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157808);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157880);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801578C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015795C);

extern void func_80161D20(s32 a0, s32 a1);
extern void func_8014C010(s32 a0, s32 a1);

void func_80157A8C(s32 a0) {
    func_80161D20(a0, *(u16 *)(a0 + 0x16E));
    func_8014C010(a0, 1);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157AC8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157B74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157BC8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157CCC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157D20);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157D74);

extern void (*D_80188E68[])(void *);

void func_80157DC4(void *a0)
{
    D_80188E68[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157E00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157E38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157EA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157F64);

extern void (*D_80188E70[])(void *);

void func_80157FC4(void *a0)
{
    D_80188E70[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158000);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158038);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801580B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801581AC);

extern void (*D_80188E7C[])(void *);

void func_8015824C(void *a0)
{
    D_80188E7C[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158288);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801582C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158344);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158434);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158548);

void func_801585A4(s32 *a0) {
    *(s16*)((s32)a0 + 0x244) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801585AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801585EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158638);

void func_80158794(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015879C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158814);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158880);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801588CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158AB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158AE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158BB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158C40);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158CD8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158D60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158E24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158F00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158FA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159070);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159120);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801592CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015934C);

typedef struct {
    u8 pad[0x12];
    u16 field12;
} S801593E4;

typedef struct {
    u8 pad[0x20];
    S801593E4 *p20;
} A801593E4;

void func_801593E4(A801593E4 *a0) {
    S801593E4 *v1 = a0->p20;
    v1->field12 = (v1->field12 + 0x16) & 0xFFF;
}


s32 func_80159404(s32 a0, s32 a1) {
    s32 a2 = *(s32 *)((s32)a0 + 0x20);
    u16 v1 = *(u16 *)((s32)a0 + 0x236);
    u16 v0 = *(u16 *)((s32)a2 + 0x12);
    *(u16 *)((s32)a2 + 0x12) = (v0 + v1) & 0xFFF;
    return (*(s32 *)((s32)a0 + 0x234) -= a1);
}


s32 func_80159434(s32 a0, s32 a1) {
    s32 a2 = *(s32 *)((s32)a0 + 0x20);
    u16 v1 = *(u16 *)((s32)a0 + 0x23A);
    u16 v0 = *(u16 *)((s32)a2 + 0x10);
    *(u16 *)((s32)a2 + 0x10) = (v0 - v1) & 0xFFF;
    return (*(s32 *)((s32)a0 + 0x238) += a1);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159464);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801594E8);

extern void (*D_80189108[])(void *);

void func_80159698(void *a0)
{
    D_80189108[*(u8 *)((s32)a0 + 0x15)](a0);
}


s32 func_801596D4(void *a0) {
    *(s32 *)((s32)a0 + 0x28) = 0x10;
    *(u8 *)((s32)a0 + 0x15) = *(u8 *)((s32)a0 + 0x15) + 1;
    return 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801596F0);

s32 func_80159874(void) {
    return 0;
}


extern void func_800167B8(s32 a0);

s32 func_8015987C(s32 a0) {
    func_800167B8(4);
    *(u8 *)(a0 + 0x15) = *(u8 *)(a0 + 0x15) + 1;
    return 0;
}


extern int func_800167F0(int arg);

int func_801598BC(void) {
    return (func_800167F0(4) & 0xFFFF) != 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801598E0);

extern void (*D_801891AC[])(void *);

void func_80159968(void *a0)
{
    D_801891AC[*(u8 *)((s32)a0 + 0x4D)](a0);
}


extern void (*D_801891B8[])(void *);

void func_801599A4(void *a0)
{
    D_801891B8[*(u16 *)a0](a0);
}


extern void func_80159A20(void *a0);

void func_801599E0(void *a0) {
    func_80159A20(a0);
    *(u8 *)((s32)a0 + 0x4D) += 1;
}


void func_80159A18(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159A20);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159B08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159B3C);

extern void (*D_80189300[])(void *);

void func_80159B70(void *a0)
{
    D_80189300[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159BAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159BE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159C84);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015A1C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015A1FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015A230);

extern void (*D_80189308[])(void *);

void func_8015A264(void *a0)
{
    D_80189308[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015A2A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015A2D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015A3C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015AB7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015ABD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015AC48);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015AC90);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015ACC4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015AD08);

extern void (*D_80189310[])(void *);

void func_8015AD3C(void *a0)
{
    D_80189310[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015AD78);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015ADB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015AE2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015B6F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015B7B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015B858);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015B8F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015B950);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015BD8C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015BDD0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015BE04);

extern void (*D_8018932C[])(void);

struct Obj {
    short unk0;
    unsigned short idx;
};

void func_8015BE38(struct Obj *a0) {
    D_8018932C[a0->idx]();
}


extern s32 func_8015BE94(void);

s32 func_8015BE74(void) {
    return func_8015BE94();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015BE94);

extern s32 func_8015AE2C(void);

s32 func_8015BEC4(void) {
    return func_8015AE2C();
}


extern s32 func_8015B950(void);

s32 func_8015BEE4(void) {
    return func_8015B950();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015BF04);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015BF48);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015BF7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015BFB0);

extern void (*D_80189338[])(void *);

void func_8015BFF4(void *a0)
{
    D_80189338[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C030);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C08C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C0C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C128);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C32C);

void func_8015C6A4(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C6AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C6E0);

extern void (*D_80189344[])(void *);

void func_8015C714(void *a0)
{
    D_80189344[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C750);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C788);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C7E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C944);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CA28);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CB94);

void func_8015CBCC(void) {
}

void func_8015CBD4(void) {
}

void func_8015CBDC(void) {
}

void func_8015CBE4(void) {
}

void func_8015CBEC(void) {
}

void func_8015CBF4(void) {
}

void func_8015CBFC(void) {
}

void func_8015CC04(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CC0C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CC40);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CC74);

extern s32 func_8015CCD0(void);

s32 func_8015CCB0(void) {
    return func_8015CCD0();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CCD0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CD20);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CF24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CF58);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CF8C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CFC0);

extern void func_8015D01C(void);

void func_8015CFFC(void) {
    func_8015D01C();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D01C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D104);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D1B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D380);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D414);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D480);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D4B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D4E8);

extern void func_80154A74(s32 a0, s32 a1);

void func_8015D524(s32 arg0) {
    func_80154A74(arg0, 0x11);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D544);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D57C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D5E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D738);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DA5C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DA90);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DAC4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DAF8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DB34);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DB6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DBD4);

extern void func_80154A74(int, int);
extern int func_8015DD74(int);

int func_8015DC84(int a0) {
    func_80154A74(a0, 0x11);
    return func_8015DD74(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DCB8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DD74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DDF0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DE24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DE58);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DE94);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DECC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DF34);

extern void func_80154A74(int, int);
extern int func_8015E0D4(int);

int func_8015DFE4(int a0) {
    func_80154A74(a0, 0x11);
    return func_8015E0D4(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E018);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E0D4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E150);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E184);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E1B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E1F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E22C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E288);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E344);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E40C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E4B0);

extern void func_8013C9C4(void *a0);
extern s32 D_80189490;

void func_8015E588(void) {
    func_8013C9C4(&D_80189490);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E5B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E698);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E714);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E84C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E880);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E8B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E8E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E924);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E95C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E9B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EA3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015ED6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EDA0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EDD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EE08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EE44);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EE7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EEE0);

void func_8015EF9C(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EFA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EFD8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F00C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F048);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F080);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F118);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F260);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F2BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F2F0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F324);

extern void func_8015F380(void);

void func_8015F360(void) {
    func_8015F380();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F380);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F448);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F738);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F76C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F7A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F7D4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F810);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F848);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F89C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F948);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F9A4);

extern void func_80154A74(s32 a0, s32 a1);

void func_8015FA24(s32 arg0) {
    func_80154A74(arg0, 0x11);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FA44);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FA78);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FAAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FAE8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FBE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FCC8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FD74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FDCC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FE70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FF20);

extern u8 D_800B9A17;

void func_8016004C(s32 a0) {
    *(s32 *)((s32)a0 + 0x184) = 0;
    *(s16 *)((s32)a0 + 0x18A) = 0;
    *(s16 *)((s32)a0 + 0x188) = 0;
    *(s32 *)((s32)a0 + 0x44) &= ~0x10;
    D_800B9A17 = 1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016007C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801600D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160104);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160138);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160174);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801601AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801601E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160244);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801602A4);

void func_8016032C(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160334);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160368);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016039C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801603D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160410);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160534);

extern void func_80149048(s32 *a0);

void func_801607B8(s32 *a0) {
    a0[0x11] &= ~1;
    func_80149048(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801607E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160818);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016084C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160888);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801608C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160920);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801609B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160A28);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160A74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160ACC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160B00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160B34);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160B70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160BB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160C28);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160CB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160D10);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160DEC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160E3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160E70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160EA4);

extern void func_80160F00(void);

void func_80160EE0(void) {
    func_80160F00();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160F00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160F70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160FE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161034);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161094);

void func_801610FC(void) {
}

extern s32 func_80161208(void);

s32 func_80161104(void) {
    return func_80161208() == 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161124);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161208);

extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016130C(void *a0, s32 a1);

void func_80161240(void *a0) {
    func_8016130C(a0, func_801612B8(a0, 1));
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161278);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801612B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016130C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161374);

extern s32 func_801615C4(void *a0, s32 a1);
extern void func_8016163C(void *a0, s32 a1);

void func_80161418(void *a0) {
    func_8016163C(a0, func_801615C4(a0, 0));
}


extern s32 func_801615C4(void *a0, s32 a1);
extern void func_80161774(void *a0, s32 a1);

void func_80161450(void *a0) {
    func_80161774(a0, func_801615C4(a0, 0));
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161488);

extern s32 func_801615C4(void *a0, s32 a1);
extern void func_80161888(void *a0, s32 a1);

void func_801614E4(void *a0) {
    func_80161888(a0, func_801615C4(a0, 0));
}


extern s32 func_801615C4(void *a0, s32 a1);
extern void func_8016191C(void *a0, s32 a1);

void func_8016151C(void *a0) {
    func_8016191C(a0, func_801615C4(a0, 0));
}


extern s32 func_801615C4(void *a0, s32 a1);
extern void func_8016163C(void *a0, s32 a1);

void func_80161554(void *a0) {
    func_8016163C(a0, func_801615C4(a0, 1));
}


extern s32 func_801615C4(void *a0, s32 a1);
extern void func_80161774(void *a0, s32 a1);

void func_8016158C(void *a0) {
    func_80161774(a0, func_801615C4(a0, 1));
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801615C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016163C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161774);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161888);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016191C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016197C);

extern u8 D_80078EC0;

s32 func_801619A4(s32 *a0) {
    if (*(s16 *)((s32)a0 + 0x1C8) == 0) {
        return 0;
    }
    return D_80078EC0 & 0x7F;
}


extern u8 D_80078EC0;

s32 func_801619D0(void *a0) {
    s32 v0;
    if (*(s16 *)((s32)a0 + 0x1C8) == 0) {
        v0 = 0;
    } else {
        v0 = ((D_80078EC0 & 0x7F) ^ 3) == 0;
    }
    return v0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161A00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161A30);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161A60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161A90);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161B18);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161B84);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161BE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161C24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161C98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161CD0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161D20);

extern void func_80161E08(s32);
extern s32 func_80162438(s32);

s32 func_80161D58(s32 a0) {
    func_80161E08(a0);
    return func_80162438(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161D88);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161E08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801620C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162120);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016216C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801621CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801622C4);

extern void (*D_8018967C[])(void);

void func_80162330(void *a0) {
    D_8018967C[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016236C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801623B8);

extern s32 func_800167F0(s32 a0);

s32 func_80162414(void) {
    return (func_800167F0(4) & 0xffff) != 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162438);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801626B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162714);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162760);

extern void func_80016714(void *a0, s32 a1);
extern s32 D_8011F750;

void func_801627C0(void) {
    func_80016714(&D_8011F750, 0x58);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801627E8);

extern void (*D_801896C4[])(void);

void func_80162834(void *a0) {
    D_801896C4[*(u8 *)((s32)a0 + 0x1)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162870);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801628F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162968);

void func_80162AC0(s32 *a0, s8 a1) {
    *(s8*)((s32)a0 + 0x0) = a1;
    *(s8*)((s32)a0 + 0x1) = 0;
}


s32 func_80162ACC(u8 *a0)
{
    s32 v = a0[1] + 1;
    a0[1] = v;
    return v;
}


s32 func_80162AE0(u8 *a0)
{
    s32 v = a0[1] - 1;
    a0[1] = v;
    return v;
}


extern void func_80016714(void *a0, s32 a1);
extern s32 D_8011F9D0;

void func_80162AF4(void) {
    func_80016714(&D_8011F9D0, 0x820);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162B1C);

void func_80162CC4(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162CCC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162D28);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162D88);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162DE8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162E48);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162EA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162F08);

extern void func_80147948(s32 a0, s32 a1, s32 a2);

void func_80162F60(s32 arg0, s32 arg1) {
    func_80147948(arg0, arg1, 0x7F0000);
}


extern void func_801479BC(s32 a0, s32 a1, s32 a2);

void func_80162F80(s32 arg0, s32 arg1) {
    func_801479BC(arg0, arg1, 0x7F0000);
}


extern void func_80147A30(s32 a0, s32 a1, s32 a2);

void func_80162FA0(s32 arg0, s32 arg1) {
    func_80147A30(arg0, arg1, 0x7F0000);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162FC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162FF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801630C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163194);

extern void func_8016325C(s32 a0, s32 a1, s32 a2, s32 a3);

void func_80163234(s32 a0) {
    func_8016325C(a0, 0, 0, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016325C);

extern s32 D_80115100;

s32 func_801632E0(void) {
    return D_80115100;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801632F0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163328);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801633A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163408);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016345C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801634D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163534);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163664);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801636D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163764);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016380C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801638A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163950);

extern void (*D_801896CC[])(void);

void func_80163A58(void *a0) {
    D_801896CC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163A94);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163C2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163EC8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164270);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801642AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016432C);

void func_80164410(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164418);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164530);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164744);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801647A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164864);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164930);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164A74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164ACC);

extern void (*D_8018972C[])(void);

void func_80164BA0(void *a0) {
    D_8018972C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164BDC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164CD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164D4C);

extern void func_80162CCC(void);

void func_80164DB0(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164DD0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164E40);

extern s32 (*D_8018973C[])();

s32 func_80164EA4(s16 *a0) {
    return D_8018973C[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164EE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164F44);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165024);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165064);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801650C4);

void func_80165124(void *a0) {
    *(s8 *)((s32)a0 + 0x50) = *(u16 *)((s32)a0 + 0x62);
    *(s8 *)((s32)a0 + 0x51) = *(u16 *)((s32)a0 + 0x62);
    *(s8 *)((s32)a0 + 0x52) = *(u16 *)((s32)a0 + 0x62);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165140);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801651B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165240);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016533C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165374);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801653B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801653F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801654A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165580);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801655E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165624);

extern u8 D_801897FC[];

u8 func_80165658(s32 a0, s32 a1) {
    return D_801897FC[a1 & 0x7F];
}


extern s32 D_8018981C[];
extern s32 D_80078EC8;

void func_80165670(s32 a0, s32 a1) {
    D_80078EC8 = D_8018981C[a1 & 0x7F];
}


extern s32 D_80078EC8;

void func_80165694(s32 arg0) {
    if (*(s32 *)((s32)arg0 + 0x1F8) & 0x80FFFFFF) {
        return;
    }
    if (D_80078EC8 != 0) {
        D_80078EC8 = D_80078EC8 - 1;
    }
}


extern u8 D_80189898[];

u8 func_801656D0(s32 a0, s32 a1) {
    return D_80189898[a1 & 0x7F];
}


extern u8 D_801898B8[];

u8 func_801656E8(s32 a0, s32 a1) {
    return D_801898B8[a1 & 0x7F];
}


extern u8 D_801898D8[];

u8 func_80165700(s32 a0, s32 a1) {
    return D_801898D8[a1 & 0x7F];
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165718);

extern u8 D_80078EC1;
extern void func_800CAF6C(void);

void func_80165770(void) {
    if (D_80078EC1 == 0xC) {
        func_800CAF6C();
    }
}


extern void func_801657D8(void);
extern u8 D_80078EC3;

void func_801657A0(void) {
    if (D_80078EC3 == 0) {
        D_80078EC3 = 1;
        func_801657D8();
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801657D8);

extern u8 D_80078EC3;
extern void func_80165874(void);

void func_80165840(void) {
    if (D_80078EC3 != 0) {
        D_80078EC3 = 0;
        func_80165874();
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165874);

extern s8 D_80078EC4;

void func_801658DC(void) {
    D_80078EC4 = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801658EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165900);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165910);

extern s32 D_8012672C;
extern s32 D_8012811C;
extern s32 D_80126B08;

void func_80165938(void) {
    D_8012672C = 0;
    D_8012811C = 0;
    D_80126B08 = 0;
}


extern s32 D_8012672C;

void func_80165958(void) {
    D_8012672C = D_8012672C + 1;
}


extern s32 D_8012672C;

s32 func_80165978(void) {
    return D_8012672C;
}


extern s32 D_8012811C;

void func_80165988(void) {
    D_8012811C = D_8012811C + 1;
}


extern s32 D_8012811C;

s32 func_801659A8(void) {
    return D_8012811C;
}


extern s32 D_80126B08;

void func_801659B8(void)
{
    D_80126B08 = 1;
}


extern s32 D_80126B08;

s32 func_801659CC(void) {
    return D_80126B08;
}


extern s32 (*D_801898F8[])();

s32 func_801659DC(u8 *a0) {
    return D_801898F8[a0[0x1A0]]();
}


void func_80165A18(void) {
}

extern void func_80165A78(s32);
extern s32 func_80165A50(s32);

s32 func_80165A20(s32 a0) {
    func_80165A78(a0);
    return func_80165A50(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165A50);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165A78);

extern u8 D_80078EC1;
extern void (*D_80189974[])(void);

void func_80165AC8(void) {
    D_80189974[D_80078EC1 & 0x7F]();
}


void func_80165B08(void) {
}

void func_80165B10(void) {
}

void func_80165B18(void) {
}

void func_80165B20(void) {
}

extern void (*D_801899F0[])(void);

void func_80165B28(void *a0) {
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_801899F0[*(u8 *)((s32)a0 + 0x197)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165B6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165BB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165BFC);

extern void func_80154A74(s32 a0, s32 a1);

void func_80165C58(s32 arg0) {
    func_80154A74(arg0, 0x11);
}


extern void func_80016714(void *a0, s32 a1);
extern s32 D_8011D030;

void func_80165C78(void) {
    func_80016714(&D_8011D030, 0xA50);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165CA0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165E2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165E90);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165FA4);

extern s32 (*D_801899FC[])();

s32 func_80166018(s16 *a0) {
    return D_801899FC[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166054);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801661CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166244);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016629C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801662F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016634C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801663A4);

extern s32 (*D_80189A04[])();

s32 func_801663FC(s16 *a0) {
    return D_80189A04[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166438);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801665B4);

extern s32 (*D_80189ACC[])();

s32 func_80166618(s16 *a0) {
    return D_80189ACC[(u16)a0[1]]();
}


extern s32 (*D_80189ADC[])();

s32 func_80166654(s16 *a0) {
    return D_80189ADC[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166690);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166994);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166F58);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016706C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801670E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80167540);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80167714);

extern s32 (*D_80189AEC[])();

s32 func_801678B4(s16 *a0) {
    return D_80189AEC[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801678F0);

extern s32 (*D_80189AF8[])();

s32 func_80167A9C(s16 *a0) {
    return D_80189AF8[(u16)a0[1]]();
}


void func_80167AD8(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80167AE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80167DBC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168070);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801681FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016829C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168328);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801683D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168430);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801684B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168540);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801685EC);

void func_80168640(s32 a0) {
    *(s32 *)(a0 + 0x1C) = 0x20;
    *(u16 *)(a0 + 0x12) = 0;
    *(u16 *)(a0 + 0x10) = 0x80;
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168664);

extern s32 (*D_80189B10[])();

s32 func_80168744(s16 *a0) {
    return D_80189B10[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168780);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801687CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168828);

extern s32 (*D_80189B18[])();

s32 func_801689D8(s16 *a0) {
    return D_80189B18[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168A14);

extern void func_80146C3C(void);

void func_80168A88(void) {
    func_80146C3C();
}


extern s32 (*D_80189B20[])();

s32 func_80168AA8(s16 *a0) {
    return D_80189B20[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168AE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168B70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168BDC);

extern s32 (*D_80189B28[])();

s32 func_80168D58(s16 *a0) {
    return D_80189B28[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168D94);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168EC4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168F40);

typedef int (*DispatchFn)();

extern DispatchFn D_80189B30[];

s32 func_8016901C(void *a0) {
    return D_80189B30[*(u16 *)((s32)a0 + 2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169058);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801691B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169228);

extern void (*D_80189B38[])(void);

void func_801693CC(void *a0) {
    D_80189B38[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169408);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016951C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169584);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801696D8);

extern void (*D_80189B40[])(void);

void func_80169830(void *a0) {
    D_80189B40[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016986C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801699D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169A4C);

extern void (*D_80189BF4[])(void);

void func_80169B80(void *a0) {
    D_80189BF4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169BBC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169E44);

extern void (*D_80189BFC[])(void);

void func_80169F00(void *a0) {
    D_80189BFC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169F3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169FE0);

extern void (*D_80189C34[])(void);

void func_8016A020(void *a0) {
    D_80189C34[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 D_80078EC0;

void func_8016A05C(void *a0) {
    s32 v0;
    if (D_80078EC0 & 0x7F) {
        v0 = *(u16 *)((s32)a0 + 2) + 1;
    } else {
        v0 = 2;
    }
    *(s16 *)((s32)a0 + 2) = v0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016A08C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016A1CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016A290);

extern void (*D_80189C40[])(void);

void func_8016A700(void *a0) {
    D_80189C40[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016A73C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016A890);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016A8FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016AA50);

extern void (*D_80189C88[])(void);

void func_8016AB30(void *a0) {
    D_80189C88[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016AB6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016AE5C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016AFB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B114);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B234);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B3F4);

extern s32 func_8016B448(s32, s32);

s32 func_8016B428(s32 a0) {
    return func_8016B448(a0, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B448);

extern void (*D_80189D04[])(void);

void func_8016B4BC(void *a0) {
    D_80189D04[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B4F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B5C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B6BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B834);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B91C);

typedef struct {
    u8 pad6[0x6];
    u16 h6;
    u16 h8;
    u16 hA;
} SrcB964;

typedef struct {
    u8 pad8[0x8];
    u16 h8;
    u16 hA;
    u16 hC;
} DstB964;

void func_8016B964(SrcB964 *a0, DstB964 *a1) {
    a1->h8 = a0->h6;
    a1->hA = a0->hA;
    a1->hC = 3;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B984);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B9F8);

extern s32 func_8016BA68(s32, s32);

s32 func_8016BA48(s32 a0) {
    return func_8016BA68(a0, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BA68);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BADC);

extern void (*D_80189D54[])(void);

void func_8016BBA4(void *a0) {
    D_80189D54[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BBE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BCC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BD78);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BEA0);

void func_8016BF34(void *a0) {
    *(s16 *)((s32)a0 + 0x12) = *(u16 *)((s32)a0 + 0x6);
    *(s16 *)((s32)a0 + 0x16) = *(u16 *)((s32)a0 + 0xA);
    *(s16 *)((s32)a0 + 0x1A) = *(u16 *)((s32)a0 + 0xE);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BF50);

extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D9B50;

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {
    func_8016BFD0(a0, a1, a2, a3, &D_801D9B50);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BFD0);

extern void (*D_80189D84[])(void);

void func_8016C14C(void *a0) {
    D_80189D84[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C188);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C2C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C374);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C49C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C74C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C83C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C998);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016CB84);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016CBC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016CF04);

extern void (*D_80189DA8[])(void);

void func_8016D19C(void *a0) {
    D_80189DA8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D1D8);

extern void (*D_80189DB0[])(void);

void func_8016D428(void *a0) {
    D_80189DB0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D464);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D4DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D5EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D64C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D688);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D778);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D848);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D984);

extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);

s32 func_8016DA04(s32 a0) {
    return func_80146994(0x31, a0, 0, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DA30);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DA7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DB34);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DBD8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DC20);

extern void (*D_80189E4C[])(void);

void func_8016DEA4(void *a0) {
    D_80189E4C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DEE0);

extern void (*D_80189E54[])(void);

void func_8016DF20(void *a0) {
    D_80189E54[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DF5C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E1CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E26C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E2E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E358);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E3CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E460);

extern void (*D_80189EA8[])(void);

void func_8016E5B8(void *a0) {
    D_80189EA8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E5F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E688);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E6E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E728);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E778);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E7C8);

extern void func_80016714(void *a0, s32 a1);
extern s32 D_80115218;

void func_8016E8F0(void) {
    func_80016714(&D_80115218, 0x80);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E918);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E95C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E9EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EAC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EB3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EBA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EC0C);

extern void func_80146C3C(void);

void func_8016ED6C(void) {
    func_80146C3C();
}


extern s32 D_80126D70;
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);

void func_8016ED8C(s32 a0, s32 a1, s32 a2) {
    func_8016EDEC(a0, a1, a2);
    D_80126D70 = a2;
}


extern s32 D_80126D70;
extern void func_8016EE40(s32 a0, s32 a1, s32 a2);

void func_8016EDBC(s32 a0, s32 a1, s32 a2) {
    func_8016EE40(a0, a1, a2);
    D_80126D70 = a2;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EDEC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EE40);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EE94);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EF78);

extern s32 func_8016EFC8(s32);

s32 func_8016EFA8(s32 a0) {
    return func_8016EFC8(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EFC8);

void func_8016F094(s32 *a0) {
    *(s32 *)((s32)a0 + 0x1F8) &= 0xFBFFFFFF;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F0AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F0E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F14C);

extern s32 D_80126D50;

s32 func_8016F1AC(void) {
    return D_80126D50 & 0x80FFFFFF;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F1C4);

extern u8 D_80126D1A;

void func_8016F250(void)
{
    D_80126D1A = 1;
}


extern s32 D_80126D50;

void func_8016F264(void) {
    D_80126D50 &= 0xFEFFFFFF;
}


extern s32 D_80126D50;

void func_8016F288(void) {
    D_80126D50 = D_80126D50 | 0x1000000;
}


extern s32 D_80126D50;

void func_8016F2A8(void) {
    D_80126D50 = D_80126D50 | 0x2000000;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F2C8);

extern s32 D_80126D50;

void func_8016F2EC(void) {
    D_80126D50 = D_80126D50 | 0x8000000;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F30C);

extern s32 D_80126D50;

void func_8016F330(void) {
    D_80126D50 = D_80126D50 | 0x10000000;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F350);

extern u8 D_800B9A17;

void func_8016F374(void)
{
    D_800B9A17 = 1;
}


extern u8 D_800B9A17;

void func_8016F388(void) {
    D_800B9A17 = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F398);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F410);

extern s32 func_80029178(s32 a0);

s32 func_8016F44C(s32 a0) {
    return (func_80029178(a0 + 0x125) & 0xff) != 0;
}


extern void func_80029124(s32 a0, s32 a1);

void func_8016F470(s32 a0) {
    func_80029124(a0 + 0x125, 0);
}


extern void func_80175414(s32);
extern s32 func_8016F4C4(s32);

s32 func_8016F494(s32 a0) {
    func_80175414(a0);
    return func_8016F4C4(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F4C4);

void func_8016F4F4(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F4FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F540);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F578);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F5B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F5E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F610);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F648);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F680);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F6B0);

extern void (*D_80189F70[])(void);

void func_8016F6E0(void *a0) {
    D_80189F70[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F71C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F764);

extern void (*D_80189F78[])(void);

void func_8016F798(void *a0) {
    D_80189F78[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F7D4);

extern void func_80171928(void *);

void func_8016F804(void *a0) {
    if (*(u8 *)((s32)a0 + 0x1C2) != 0) {
        *(u8 *)((s32)a0 + 0x1C2) = 0;
        func_80171928(a0);
    }
}


extern void (*D_80189F80[])(void);

void func_8016F834(void *a0) {
    D_80189F80[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F870);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F8AC);

extern void (*D_80189F88[])(void);

void func_8016F8E4(void *a0) {
    D_80189F88[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F920);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F95C);

extern void (*D_80189F90[])(void);

void func_8016F9C4(void *a0) {
    D_80189F90[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FA00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FA44);

extern void (*D_80189F98[])(void);

void func_8016FA84(void *a0) {
    D_80189F98[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FAC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FB10);

extern void func_80171928(void *a0);

void func_8016FB50(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x20);
    u16 v0 = *(u16 *)((s32)a0 + 0x132);
    *(s16 *)((s32)a0 + 0x136) = 0;
    *(s16 *)(v1 + 0x12) = v0;
    func_80171928(a0);
}


extern void (*D_80189FA4[])(void);

void func_8016FB7C(void *a0) {
    D_80189FA4[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FBB8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FC24);

extern void func_80171928(void *a0);

void func_8016FC64(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x20);
    u16 v0 = *(u16 *)((s32)a0 + 0x132);
    *(s16 *)((s32)a0 + 0x136) = 0;
    *(s16 *)(v1 + 0x12) = v0;
    func_80171928(a0);
}


extern void (*D_80189FB0[])(void);

void func_8016FC90(u8 *a0)
{
    D_80189FB0[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FCCC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FD08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FD7C);

extern void (*D_80189FBC[])(void);

void func_8016FDB4(u8 *a0)
{
    D_80189FBC[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FDF0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FE2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FE78);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FED0);

extern void (*D_80189FCC[])(void);

void func_8016FF30(u8 *a0)
{
    D_80189FCC[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FF6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016FFA8);

extern void (*D_80189FDC[])(void);

void func_8016FFDC(u8 *a0)
{
    D_80189FDC[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170018);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170068);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801700B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170100);

extern void (*D_80189FE4[])(void);

void func_80170150(u8 *a0)
{
    D_80189FE4[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017018C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801701C8);

extern void (*D_80189FEC[])(void);

void func_80170240(u8 *a0)
{
    D_80189FEC[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017027C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801702B8);

extern void (*D_80189FF4[])(void);

void func_801702FC(u8 *a0)
{
    D_80189FF4[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170338);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170374);

extern void (*D_80189FFC[])(void);

void func_801703E0(u8 *a0)
{
    D_80189FFC[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017041C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017044C);

extern void (*D_8018A004[])(void);

void func_801704B0(u8 *a0)
{
    D_8018A004[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801704EC);

extern u16 D_800AE6DC;
extern void func_80171928(void *a0);

void func_8017051C(void *a0) {
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = D_800AE6DC;
    func_80171928(a0);
}


extern void (*D_8018A00C[])(void);

void func_80170548(u8 *a0)
{
    D_8018A00C[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170584);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801705C0);

extern void (*D_8018A014[])(void);

void func_801705F8(u8 *a0)
{
    D_8018A014[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170634);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170670);

extern void (*D_8018A01C[])(void);

void func_801706AC(u8 *a0)
{
    D_8018A01C[a0[0x216]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801706E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170718);

extern void (*D_8018A024[])(void *);

void func_80170748(void *a0) {
    D_8018A024[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170784);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801707D4);

extern void (*D_8018A02C[])(void *);

void func_80170810(void *a0) {
    D_8018A02C[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017084C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801708B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170928);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170970);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801709B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170A00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170A48);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170A90);

extern void (*D_8018A034[])(void *);

void func_80170AD8(void *a0) {
    D_8018A034[*(u8 *)((s32)a0 + 0x216)](a0);
}


extern void func_801719A4(int a0, int a1);
extern void func_80170B48(int a0);

void func_80170B14(int a0) {
    func_801719A4(a0, 1);
    func_80170B48(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170B48);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170B90);

extern void (*D_8018A03C[])(void *);

void func_80170BD8(void *a0) {
    D_8018A03C[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170C14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170C44);

extern void (*D_8018A044[])(void *);

void func_80170C74(void *a0) {
    D_8018A044[*(u8 *)((s32)a0 + 0x215)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170CB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170CF0);

extern void (*D_8018A04C[])(void *);

void func_80170D68(void *a0) {
    D_8018A04C[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170DA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170DE0);

extern void (*D_8018A054[])(void *);

void func_80170E34(void *a0) {
    D_8018A054[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170E70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170EAC);

extern void (*D_8018A05C[])(void *);

void func_80170EFC(void *a0) {
    D_8018A05C[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170F38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170F74);

extern void (*D_8018A064[])(void *);

void func_80170FB0(void *a0) {
    D_8018A064[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170FEC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171028);

extern void (*D_8018A06C[])(void *);

void func_80171064(void *a0) {
    D_8018A06C[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801710A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801710DC);

extern void (*D_8018A074[])(void *);

void func_80171120(void *a0) {
    D_8018A074[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017115C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017118C);

extern void (*D_8018A07C[])(void *);

void func_801711C0(void *a0) {
    D_8018A07C[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801711FC);

extern void func_801718AC(void *a0);
extern void *D_8011F738;

void func_80171238(void) {
    func_801718AC(D_8011F738);
}


extern s32 (*D_8018A084[])(void *);

s32 func_80171260(void *a0) {
    return D_8018A084[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017129C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171384);

extern s32 (*D_8018A08C[])(void *);

s32 func_801714E4(void *a0) {
    return D_8018A08C[*(u8 *)((s32)a0 + 0x216)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171520);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017162C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801716AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801717A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801717F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171824);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171854);

extern void func_80171928(void *a0);
extern s32 D_80126B58;

void func_80171884(void) {
    func_80171928(&D_80126B58);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801718AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171904);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171928);

void func_8017196C(s32 *a0, s8 a1) {
    *(s8*)((s32)a0 + 0x214) = a1;
    *(s8*)((s32)a0 + 0x215) = 0;
    *(s8*)((s32)a0 + 0x216) = 0;
}


s32 func_8017197C(u8 *a0)
{
    s32 v = a0[0x215] + 1;
    a0[0x216] = 0;
    a0[0x215] = v;
    return v;
}


s32 func_80171990(u8 *a0)
{
    s32 v = a0[0x216] + 1;
    a0[0x216] = v;
    return v;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801719A4);

void func_80171A04(s32 *a0) {
    *(s8*)((s32)a0 + 0x217) = 1;
}


void func_80171A10(s32 *a0) {
    *(s8*)((s32)a0 + 0x217) = 2;
}


void func_80171A1C(u8 *a0) {
    a0[0x215] = 0;
    a0[0x216] = 0;
    a0[0x214] = a0[0x214] + 1;
}


void func_80171A34(s32 *a0, s8 a1) {
    *(s8*)((s32)a0 + 0x214) = a1;
    *(s8*)((s32)a0 + 0x215) = 0;
    *(s8*)((s32)a0 + 0x216) = 0;
}


s32 func_80171A44(u8 *a0)
{
    s32 v = a0[0x215] + 1;
    a0[0x216] = 0;
    a0[0x215] = v;
    return v;
}


s32 func_80171A58(u8 *a0) {
    s32 v0 = a0[0x216] + 1;
    a0[0x216] = v0;
    return v0;
}


s32 func_80171A6C(u8 *a0) {
    s32 v0 = a0[0x216] - 1;
    a0[0x216] = v0;
    return v0;
}


void func_80171A80(s32 *a0, s32 a1) {
    *(s32*)((s32)a0 + 0x200) = a1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171A88);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171AB0);

extern s32 func_8014C568(void *a0);

void func_80171B10(void *a0) {
    s32 ret = func_8014C568(a0);
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = ret;
}


void func_80171B44(s32 *a0) {
    *(s8*)((s32)a0 + 0x20C) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171B4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171C64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171CC4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171D1C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171D78);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171E08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171EC8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171FFC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017209C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172170);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801722CC);

void func_80172304(s32 *a0) {
    *(s16*)((s32)a0 + 0xAA) = 0x40;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172310);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172358);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801723C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172414);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017248C);

extern s32 func_80013450(s32);

s32 func_801724EC(s32 a0) {
    return func_80013450(a0 + 4) < 0x10;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017250C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172560);

void func_80172588(s32 *a0) {
    *(s32*)((s32)a0 + 0x1F4) = 0;
}


s32 func_80172590(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x1;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}


s32 func_801725A4(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x2;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}


s32 func_801725B8(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x4;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}


s32 func_801725CC(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x8;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}


s32 func_801725E0(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x10;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}


s32 func_801725F4(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x20;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}


s32 func_80172608(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x40;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}


s32 func_8017261C(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x80;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}


s32 func_80172630(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x100;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}


s32 func_80172644(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x200;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}


s32 func_80172658(s32 *a0) {
    return *(s32*)((s32)a0 + 0x1F4) & 0x1;
}


s32 func_80172664(s32 *a0) {
    return *(s32*)((s32)a0 + 0x1F4) & 0x2;
}


s32 func_80172670(s32 *a0) {
    return *(s32*)((s32)a0 + 0x1F4) & 0x4;
}


s32 func_8017267C(s32 *a0) {
    return *(s32*)((s32)a0 + 0x1F4) & 0x8;
}


s32 func_80172688(s32 *a0) {
    return *(s32*)((s32)a0 + 0x1F4) & 0x10;
}


s32 func_80172694(s32 *a0) {
    return *(s32*)((s32)a0 + 0x1F4) & 0x20;
}


s32 func_801726A0(s32 *a0) {
    return *(s32*)((s32)a0 + 0x1F4) & 0x40;
}


s32 func_801726AC(s32 *a0) {
    return *(s32*)((s32)a0 + 0x1F4) & 0x80;
}


s32 func_801726B8(s32 *a0) {
    return *(s32*)((s32)a0 + 0x1F4) & 0x100;
}


s32 func_801726C4(s32 *a0) {
    return *(s32*)((s32)a0 + 0x1F4) & 0x200;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801726D0);

extern void (*D_80127088)(void);

void func_80172710(void) {
    D_80127088();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172738);

extern s32 func_80174650(s32);

s32 func_80172760(s32 a0) {
    return func_80174650(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172780);

extern s32 (*D_8018A09C[])(void *);

s32 func_801727D0(void *a0) {
    return D_8018A09C[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017280C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172844);

void func_8017288C(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172894);

extern s32 (*D_8018A0A8[])(void *);

s32 func_801728E4(void *a0) {
    return D_8018A0A8[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172920);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172958);

void func_801729A8(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801729B0);

extern s32 (*D_8018A0B4[])(void *);

s32 func_801729F0(void *a0) {
    return D_8018A0B4[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172A2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172A8C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172ACC);

void func_80172B0C(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172B14);

extern s32 (*D_8018A0C4[])(void *);

s32 func_80172B44(void *a0) {
    return D_8018A0C4[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172B80);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172BC8);

void func_80172C48(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172C50);

extern s32 (*D_8018A0D0[])(void *);

s32 func_80172CA0(void *a0) {
    return D_8018A0D0[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172CDC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172D14);

void func_80172D60(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172D68);

extern s32 (*D_8018A0DC[])(void *);

s32 func_80172DAC(void *a0) {
    return D_8018A0DC[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172DE8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172E20);

void func_80172E8C(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172E94);

extern void func_8017303C(void *);
extern u8 D_800D59EC[];

void func_80172ED4(void) {
    func_8017303C(D_800D59EC);
}


extern void func_8017303C(void *);
extern u8 D_800D599C[];

void func_80172EFC(void) {
    func_8017303C(D_800D599C);
}


extern void func_8017303C(void *);
extern u8 D_800D5934[];

void func_80172F24(void) {
    func_8017303C(D_800D5934);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172F4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172F9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172FEC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017303C);

extern s32 (*D_8018A0E8[])(void *);

s32 func_80173078(void *a0) {
    return D_8018A0E8[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801730B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801730FC);

void func_8017316C(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173174);

extern s32 (*D_8018A0F4[])(void *);

s32 func_8017319C(void *a0) {
    return D_8018A0F4[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801731D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173220);

void func_80173294(void) {
}

extern void func_80174684(void *);
extern void func_801732C4(void);

void func_8017329C(void) {
    func_80174684(func_801732C4);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801732C4);

extern void func_80174684(void *);
extern void func_8017331C(void);

void func_801732F4(void) {
    func_80174684(func_8017331C);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017331C);

extern void func_80174684(void *);
extern void func_80173374(void);

void func_8017334C(void) {
    func_80174684(func_80173374);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173374);

extern void func_80174684(void *);
extern void func_8017331C(void);

void func_801733A4(void) {
    func_80174684(func_8017331C);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801733CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801733FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173460);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801734BC);

extern s32 (*D_8018A100[])(void *);

s32 func_80173544(void *a0) {
    return D_8018A100[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173580);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801735B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801735EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173648);

void func_801736A8(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801736B0);

extern s32 (*D_8018A114[])(void *);

s32 func_801736FC(void *a0) {
    return D_8018A114[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173738);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173770);

void func_801737B0(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801737B8);

extern s32 (*D_8018A120[])(void *);

s32 func_801737E8(void *a0) {
    return D_8018A120[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173824);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017385C);

void func_801738D4(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801738DC);

extern s32 (*D_8018A12C[])(void *);

s32 func_8017390C(void *a0) {
    return D_8018A12C[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173948);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173980);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801739D8);

void func_80173A20(void) {
}

extern s32 D_8012750C;
extern void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

void func_80173A28(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5) {
    func_80173A60(a0, a1, a2, a3, a4);
    D_8012750C = a5;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173A60);

extern s32 (*D_8018A13C[])(void *);

s32 func_80173B4C(void *a0) {
    return D_8018A13C[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173B88);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173BC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173C64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173CB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173E1C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173EF8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174158);

extern s32 func_8014BCEC(s32, s32);

s32 func_80174188(s32 a0) {
    return func_8014BCEC(a0, 0x19);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801741A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801741EC);

void func_80174274(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017427C);

extern s32 (*D_8018A15C[])(void *);

s32 func_801742A4(void *a0) {
    return D_8018A15C[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801742E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174318);

void func_80174354(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017435C);

extern s32 (*D_8018A168[])(void *);

s32 func_80174384(void *a0) {
    return D_8018A168[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801743C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801743F0);

void func_80174430(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174438);

extern s32 (*D_8018A174[])(void *);

s32 func_80174474(void *a0) {
    return D_8018A174[*(u8 *)((s32)a0 + 0x214)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801744B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801744E0);

void func_80174524(void) {
}

extern void func_80174684(void *);
extern void func_80174554(void);

void func_8017452C(void) {
    func_80174684(func_80174554);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174554);

extern void func_80174684(void *);
extern void func_801745AC(void);

void func_80174584(void) {
    func_80174684(func_801745AC);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801745AC);

extern void func_80174604(void);
extern void func_80174684(void *);

void func_801745DC(void) {
    func_80174684(func_80174604);
}


extern s32 D_801150F8;
extern void func_80174630(void);

void func_80174604(void) {
    D_801150F8 = 1;
    func_80174630();
}


extern s32 D_801270BC;

void func_80174630(void) {
    D_801270BC = D_801270BC | 0x1;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174650);

extern s32 D_801270BC;

void func_80174674(void) {
    D_801270BC = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174684);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801746A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801746DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174714);

extern s32 D_801270BC;

s32 func_80174754(void) {
    return D_801270BC;
}


extern s16 D_8011F9C8;

s16 func_80174764(void) {
    return D_8011F9C8;
}


extern s16 D_80126938;

s16 func_80174774(void) {
    return D_80126938;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174784);

extern s32 func_8016F0AC(s32);

s32 func_801747AC(s32 a0) {
    return func_8016F0AC(a0);
}


extern s32 (*D_8018A180[])(void *);

s32 func_801747CC(void *a0) {
    return D_8018A180[*(u8 *)((s32)a0 + 0x214)](a0);
}


s32 func_80174808(u8 *a0) {
    s32 v = (s32)a0[0x214] + 1;
    a0[0x214] = (u8)v;
    return v;
}


void func_8017481C(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174824);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017484C);

extern s32 (*D_8018A188[])(void *);

s32 func_80174888(void *a0) {
    return D_8018A188[*(u8 *)((s32)a0 + 0x214)](a0);
}


void func_801748C4(s32 a0) {
    u8 v = *(u8 *)(a0 + 0x214) + 1;
    *(s32 *)(a0 + 0x44) |= 0x4000000;
    *(u8 *)(a0 + 0x214) = v;
}


void func_801748E4(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801748EC);

extern s32 (*D_8018A190[])(void *);

s32 func_8017496C(void *a0) {
    return D_8018A190[*(u8 *)((s32)a0 + 0x4)](a0);
}


extern s32 func_801749C8(s32);

s32 func_801749A8(s32 a0) {
    return func_801749C8(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801749C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174B6C);

void func_80174BBC(void *a0) {
    *(s32 *)((s32)a0 + 0xC) = 0x12C;
    *(s32 *)((s32)a0 + 0x14) = 0x12C;
    *(s16 *)((s32)a0 + 0x20) = 0x155;
    *(s16 *)((s32)a0 + 0x22) = 0x800;
    *(s16 *)((s32)a0 + 0x24) = 0;
    *(s16 *)((s32)a0 + 0x2E) = 0;
    *(s16 *)((s32)a0 + 0x30) = -0x28;
    *(s16 *)((s32)a0 + 0x32) = 0;
    *(s32 *)((s32)a0 + 0x54) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174BF4);

extern s32 func_80174CB0(s32, s32);

s32 func_80174C60(s32 a0) {
    return func_80174CB0(a0, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174C80);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174CB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174E9C);

extern u16 D_80126980;
s32 func_80174ED4(void) {
    return (s16)(D_80126980 & 0x8000);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174EF0);

extern s32 (*D_8018A19C[])(void *);

s32 func_80174F28(void *a0) {
    return D_8018A19C[*(u8 *)((s32)a0 + 0x4)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174F64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174FBC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175014);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017509C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175114);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175150);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175184);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801751D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175218);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175268);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801752BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175308);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175414);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175454);

extern u8 D_8011F7A8;

void func_80175494(void) {
    D_8011F7A8 = 2;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801754A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017553C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175590);

extern s16 D_800B9A02;
extern void func_801757A0(s32);

void func_80175624(void *a0) {
    func_801757A0(D_800B9A02);
    *((u8 *)a0 + 1) = *((u8 *)a0 + 1) + 1;
}


extern short D_800B9A02;
extern void func_801757E0(int);

void func_80175668(void) {
    func_801757E0(D_800B9A02);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175690);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801756E4);

void func_80175798(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801757A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801757E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175820);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801758FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801759D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175AB8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175DA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80176144);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80176218);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80176734);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80176D00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80176D94);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80176FF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801770E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177340);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017742C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801775E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801776EC);

void *func_80177784(void *a0, s32 a1, s32 a2, s32 a3) {
    *(u32 *)((s32)a0 + 0x0) = (((s32)a0 - 0x14) & 0xFFFFFF) | 0x3000000;
    *(u32 *)((s32)a0 + 0x4) = 0x74808080;
    *(s32 *)((s32)a0 + 0x8) = a1;
    *(s32 *)((s32)a0 + 0xC) = a2;
    return (void *)((s32)a0 + 0x14);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801777BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801778A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177940);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177AD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177B5C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177DA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177EA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177F84);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178004);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178298);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801783D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178438);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017849C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178608);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017869C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178744);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801787D4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178840);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801788B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178970);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801789AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178B18);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178B70);

void func_80178BF8(s32 a0, s32 a1);
void func_80178CBC(s32 a0, s32 a1);

void func_80178BB8(s32 a0, s32 a1) {
    func_80178BF8(a0, a1);
    func_80178CBC(a0, a1);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178BF8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178CBC);

extern short D_801DAB2C;
extern void func_80174714(void);

void func_80178D18(void) {
    D_801DAB2C = 0;
    func_80174714();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178D40);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179B28);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179B74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179D30);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179D78);

extern void func_80179B74(short *);

void func_80179DCC(short a0) {
    short sp10[2];
    sp10[1] = a0;
    sp10[0] = 2;
    func_80179B74(sp10);
}


extern void func_80179B74(s16 *a0);

void func_80179DF8(void) {
    s16 local;

    local = 0;
    func_80179B74(&local);
}


extern void func_80179B74(short *);

void func_80179E1C(short a0) {
    short sp10[2];
    sp10[1] = a0;
    sp10[0] = 3;
    func_80179B74(sp10);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179E48);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179E74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179EA0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179EE8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179F14);

extern void func_80179B74(short *);

void func_80179F44(void) {
    short sp10;
    sp10 = 0x18;
    func_80179B74(&sp10);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179F6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179F98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179FEC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017A040);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017A094);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017A0C4);

extern void func_80179B74(short *);

void func_8017A0F4(void) {
    short sp10;
    sp10 = 0x7;
    func_80179B74(&sp10);
}


extern void func_80179B74(short *);

void func_8017A11C(void) {
    short sp10;
    sp10 = 0x8;
    func_80179B74(&sp10);
}


extern s32 D_801DA75C;
extern void func_80179B74(s16 *a0);

void func_8017A144(s32 a0) {
    s16 sp10;
    sp10 = 0x1B;
    func_80179B74(&sp10);
    D_801DA75C = a0;
}


extern void func_80179B74(short *);

void func_8017A180(void) {
    short sp10;
    sp10 = 0x9;
    func_80179B74(&sp10);
}


extern void func_80179B74(short *);

void func_8017A1A8(void) {
    short sp10;
    sp10 = 0xA;
    func_80179B74(&sp10);
}


extern void func_80179B74(short *);

void func_8017A1D0(void) {
    short sp10;
    sp10 = 0xB;
    func_80179B74(&sp10);
}


extern void func_80179B74(short *);

void func_8017A1F8(void) {
    short sp10;
    sp10 = 0xC;
    func_80179B74(&sp10);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017A220);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017A248);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017A270);

extern void func_80179B74(short *);

void func_8017A298(void) {
    short sp10;
    sp10 = 0xE;
    func_80179B74(&sp10);
}


extern void func_80179B74(short *);

void func_8017A2C0(void) {
    short sp10;
    sp10 = 0xF;
    func_80179B74(&sp10);
}


extern void func_80179B74(short *);

void func_8017A2E8(void) {
    short sp10;
    sp10 = 0x10;
    func_80179B74(&sp10);
}


extern void func_80179B74(short *);

void func_8017A310(void) {
    short sp10;
    sp10 = 0x11;
    func_80179B74(&sp10);
}


extern void func_80179B74(short *);

void func_8017A338(void) {
    short sp10;
    sp10 = 0x19;
    func_80179B74(&sp10);
}


extern void func_80179B74(short *);

void func_8017A360(void) {
    short sp10;
    sp10 = 0x1E;
    func_80179B74(&sp10);
}


extern void func_80179B74(short *);

void func_8017A388(void) {
    short sp10;
    sp10 = 0x1A;
    func_80179B74(&sp10);
}


extern s16 D_801DA718;

s32 func_8017A3B0(void) {
    switch (D_801DA718) {
    case 0:
        return 1;
    case 1:
        return 0;
    default:
        return 1;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017A3D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017A4AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017AD0C);

extern s32 func_8017AD0C(s32);

s32 func_8017ADE8(s32 a0) {
    return func_8017AD0C(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017AE08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017AE2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B0E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B1D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B238);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B368);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B490);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B614);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B7A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B824);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B880);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B8E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B940);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BA3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BB34);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BC38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BCA0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BCF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BD50);

extern s32 (*D_8018A4FC[])(void *);

s32 func_8017BE60(void *a0) {
    return D_8018A4FC[*(u8 *)((s32)a0 + 0x4)](a0);
}


void func_8017BE9C(void) {
}

void func_8017BEA4(void) {
}

void func_8017BEAC(void) {
}

void func_8017BEB4(void) {
}

extern s32 (*D_8018A520[])(void *);

s32 func_8017BEBC(void *a0) {
    return D_8018A520[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BEF8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C0BC);

extern s32 (*D_8018A528[])(void *);

s32 func_8017C150(void *a0) {
    return D_8018A528[*(u16 *)((s32)a0 + 2)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C18C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C230);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C294);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C66C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C710);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C908);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C974);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017D840);

extern u8 D_8012694C;

void func_8017D8DC(void) {
    D_8012694C = 1;
}


extern u8 D_8012694C;

void func_8017D8F0(void) {
    D_8012694C = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017D900);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017D98C);

extern s32 (*D_8018A530[])(void *);

s32 func_8017DA08(void *a0) {
    return D_8018A530[*(u8 *)((s32)a0 + 4)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DA44);

extern s32 func_8017DAEC(s32);

s32 func_8017DACC(s32 a0) {
    return func_8017DAEC(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DAEC);

extern s32 (*D_8018A588[])(void *);

s32 func_8017DCB0(void *a0) {
    return D_8018A588[*(u8 *)((s32)a0 + 0x15)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DCEC);

extern s32 func_800167F0(s32 a0);

s32 func_8017DD3C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


extern s32 (*D_8018A590[])(void *);

s32 func_8017DD60(void *a0) {
    return D_8018A590[*(u8 *)((s32)a0 + 0x15)](a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DD9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DDE8);

extern void func_800D1EBC(void);

void func_8017DE64(void) {
    func_800D1EBC();
}


extern void (*D_8018A740[])();

void func_8017DE84(void *arg0) {
    D_8018A740[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DEC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DEFC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DF5C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DFD8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E0B4);

extern void (*D_8018A754[])();

void func_8017E0EC(void *arg0) {
    D_8018A754[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E128);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E170);

extern void func_8016F0E4(void);

void func_8017E1B4(void) {
    func_8016F0E4();
}


extern void (*D_8018A760[])();

void func_8017E1D4(void *arg0) {
    D_8018A760[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}


s32 func_8017E210(u8 *a0) {
    s32 v = (s32)a0[0x214] + 1;
    a0[0x214] = (u8)v;
    return v;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E224);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E298);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E350);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E3EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E460);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E4B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E51C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E604);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E668);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E6BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E6F4);

extern void (*D_8018A790[])();

void func_8017E748(void *arg0) {
    D_8018A790[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E784);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E7DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E830);

extern void (*D_8018A79C[])();

void func_8017E868(void *arg0) {
    D_8018A79C[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E8A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E924);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E974);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E9C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EA2C);

extern s32 (*D_8018A7B0[])();

s32 func_8017EA5C(s16 *a0) {
    return D_8018A7B0[(u16)a0[1]]();
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_8017EA98(s32 *a0) {
    a0[7] = 0x10;
    func_8012AD44(a0, 1);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EAC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EB2C);

extern s32 (*D_8018A7B8[])();

s32 func_8017EC40(s16 *a0) {
    return D_8018A7B8[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EC7C);

extern s32 (*D_8018A7F0[])();

s32 func_8017ED4C(s16 *a0) {
    return D_8018A7F0[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017ED88);

extern s32 (*D_8018A7F8[])();

s32 func_8017EDE4(s16 *a0) {
    return D_8018A7F8[(u16)a0[1]]();
}


extern s32 func_8012AD50(void *a0);

void func_8017EE20(void *a0) {
    *(s32 *)((s32)a0 + 0x1C) = 1;
    func_8012AD50(a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EE44);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EEC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EF50);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F024);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F0B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F114);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F240);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F290);

extern s32 (*D_8018A87C[])();

s32 func_8017F3E8(s16 *a0) {
    return D_8018A87C[(u16)a0[1]]();
}


extern s32 (*D_8018A89C[])();

s32 func_8017F424(s16 *a0) {
    return D_8018A89C[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F460);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F5BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F694);

extern s32 (*D_8018A904[])();

s32 func_8017F6D8(s16 *a0) {
    return D_8018A904[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F714);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F780);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F7E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017FAAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017FD14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", listCdBuffer);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801800F8);

extern s32 (*D_8018AA1C[])();

s32 func_8018021C(s16 *a0) {
    return D_8018AA1C[(u16)a0[1]]();
}


extern s32 (*D_8018AA24[])();

s32 func_80180258(s16 *a0) {
    return D_8018AA24[(u16)a0[1]]();
}


extern void func_8002D4C8(s32 a0, s32 a1);

void func_80180294(void *a0) {
    u16 v0 = *(u16 *)((s32)a0 + 0x2);
    *(s32 *)((s32)a0 + 0x1C) = 0x96;
    *(u16 *)((s32)a0 + 0x2) = v0 + 1;
    func_8002D4C8(0x401, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801802CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018031C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801803B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018047C);

void func_80180588(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180590);

extern s32 D_801270C8;
extern void func_8017F714(void);

void func_801806A8(void) {
    if (D_801270C8 == 1) {
        func_8017F714();
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801806D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801807B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180898);

extern void func_8002D4C8(s32 a0, s32 a1);

void func_801808DC(void *a0) {
    *(s16 *)((s32)a0 + 0x2) = 1;
    *(s16 *)((s32)a0 + 0xFC) = 0x96;
    func_8002D4C8(0x401, 0);
}


extern void func_80180930(void);

void func_80180910(void) {
    func_80180930();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180930);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801809BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180AD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180B64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180C90);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180F10);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018103C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80181948);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80181B58);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80181B9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80181BE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80181F08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801820DC);

void func_80182254(s32 a0) {
    *(s16 *)(a0 + 0x2) = 4;
    *(s16 *)(a0 + 0x98) = 0;
    *(s32 *)(a0 + 0x1C) = 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182268);

void func_801822E4(u8 *a0) {
    *(s16 *)(a0 + 0x2) = 0xC;
    *(s32 *)(a0 + 0x1C) = 6;
    *(s16 *)(a0 + 0x5C) = 0;
}


void func_801822FC(void *a0) {
    u16 v = *(u16 *)((s32)a0 + 0x70);
    *(s16 *)((s32)a0 + 0x2) = 5;
    *(s16 *)((s32)a0 + 0x98) = 0;
    *(s32 *)((s32)a0 + 0x1C) = 0x10;
    if ((s8)(v >> 8) == 5) {
        *(u16 *)((s32)a0 + 0x70) = (v & 0xFF) | 0x100;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182338);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801823A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182420);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801824D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801827A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018281C);

void func_8018294C(void *a0) {
    *(s16 *)((s32)a0 + 0x2) = 7;
    *(s16 *)((s32)a0 + 0x98) = 0;
    *(s32 *)((s32)a0 + 0x1C) = 0x1E;
    *(s16 *)((s32)a0 + 0x5C) = 0;
}


extern void func_80182988(void);

void func_80182968(void) {
    func_80182988();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182988);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801829E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182A24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182C9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182E30);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182E7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182FD0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018301C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018308C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183324);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183834);

extern void func_8012E364(void);

void func_80183A50(void) {
    func_8012E364();
}


extern s32 func_8012E470(s32);
extern void func_8012E4C8(s32);

void func_80183A70(s32 arg0) {
    if (func_8012E470(arg0)) {
        func_8012E4C8(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183AA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183AF0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183BAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183C50);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183CF4);

void func_80183DD8(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183DE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183F4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183FB8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018414C);

void func_80184238(void *a0) {
    *(s16 *)((s32)a0 + 0x2) = 3;
    *(s16 *)((s32)a0 + 0x34) = 0;
    *(s32 *)((s32)a0 + 0x18) = 0;
    *(s16 *)((s32)a0 + 0x5C) = 0x800;
}


void func_80184254(s32 a0) {
    *(s16 *)(a0 + 0x2) = 3;
    *(s16 *)(a0 + 0x34) = 1;
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0x1C) = 0x1B;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184278);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801842C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801843C0);

s32 func_80184484(void) {
    return 1;
}


extern void func_8012C098(void);

void func_8018448C(void) {
    func_8012C098();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801844AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801844F4);

extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801973C4;

void func_80184554(s32 a0) {
    *(s16 *)(a0 + 0x2) = 2;
    func_8012A828(a0, &D_801973C4);
    *(s32 *)(a0 + 0x1C) = 0x14;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184594);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801845EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018469C);

void func_801846F8(s32 a0) {
    *(s16 *)(a0 + 0x2) = 5;
    *(s32 *)(a0 + 0x1C) = 0x14;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018470C);

extern s32 (*D_8018AF90[])();

s32 func_80184890(s16 *a0) {
    return D_8018AF90[(u16)a0[1]]();
}


extern s32 (*D_8018AFB8[])();

s32 func_801848CC(s16 *a0) {
    return D_8018AFB8[(u16)a0[1]]();
}


extern s32 (*D_8018B000[])();

s32 func_80184908(s16 *a0) {
    return D_8018B000[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184944);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801849A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184A00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184A68);

extern s32 func_8012BEE8(s32);
extern void func_80184594(s32);

void func_80184AEC(s32 arg0) {
    if (func_8012BEE8(arg0)) {
        func_80184594(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184B24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184BB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184C0C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184CCC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184D50);

extern s32 D_801DA908;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_80184ED8(s32 a0, s32 a1) {
    D_801DA908 = a1;
    return func_8012C588(0x85, a0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184F08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018514C);

extern s32 (*D_801991C4[])();

s32 func_801853EC(s16 *a0) {
    return D_801991C4[(u16)a0[1]]();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185428);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801855A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801855DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185618);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801856F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185814);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185870);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801858AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185970);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801859AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185A94);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185AD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185B5C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185BA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185E68);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186078);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186330);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801863B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186434);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186574);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801865EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801867E0);

typedef struct { u8 b[8]; } Blk8;
extern Blk8 D_801D5610;

void func_8018681C(s32 a0) {
    if (*(s16 *)((s32)a0 + 0x70) == 4) {
        *(Blk8 *)((s32)a0 + 0x50) = D_801D5610;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186860);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186938);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186A04);

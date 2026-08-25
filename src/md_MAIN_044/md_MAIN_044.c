#include "common.h"

void func_800CCB20(void) {
}

extern void func_80149020(s32 a0);
extern void (*D_800CE1E4[])(s32);

void func_800CCB28(s32 param_1) {
    s32 s0 = param_1;
    s32 idx;
    func_80149020(s0);
    idx = *(u16 *)(s0 + 2) - 2;
    D_800CE1E4[idx](s0);
}


INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CCB78);

extern void (*D_800CE1F4[])(s32);
extern void func_800CCE68(void);
extern s32 func_801619D0(s32 a0);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147324(s32 a0);

void func_800CCBE4(s32 param_1) {
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CE1F4[*(u16 *)(param_1 + 2)](param_1);
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) |= *(s32 *)(*(s32 *)(iVar1 + 0x20) + 4) & 0x80000000;
    if (func_801619D0(iVar1) == 0) {
        ((void (*)(s32))func_800CCE68)(param_1);
        func_80146994(0x3A, iVar1, 0, 0);
        func_80147324(0xA13);
    }
}


extern u8 D_800CEBEC;
extern void func_8014659C(void);
extern void func_8001C810(s32, void *);
extern void func_800CCF58();
extern void func_800CCE88(s32);
extern s32 func_80146CA0(void *);
extern void func_800CCE68();

void func_800CCCA0(s32 param_1) {
    register s32 p1 __asm__("$17"); /* $s1 */
    register s32 iVar1 __asm__("$16"); /* $s0 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001C810(iVar1, &D_800CEBEC);
        *(u32 *)(iVar1 + 4) |= 0x40010000;
        func_800CCF58(iVar1, 0);
        func_800CCE88(p1);
        *(s16 *)(p1 + 0x60) = 0;
        ((s32 (*)(void *))func_80146CA0)(p1);
    } else {
        ((void (*)(s32))func_800CCE68)(p1);
    }
}


INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CCD2C);

INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CCDB0);

extern void func_80162CCC(void);
void func_800CCE68(void) {
    func_80162CCC();
}


void func_800CCE88(s32 param_1) {
    s32 s2 = *(s32 *)(param_1 + 0x4C);
    s32 a0 = *(s32 *)(s2 + 0x20);
    s32 s1 = *(s32 *)(param_1 + 0x20);
    s32 s0 = s1 + 0x34;
    *(s16 *)(param_1 + 0x6) = *(s32 *)(a0 + 0x48);
    *(s16 *)(param_1 + 0xA) = *(s32 *)(a0 + 0x4C) - 0x20;
    *(s16 *)(param_1 + 0xE) = *(s32 *)(a0 + 0x50);
    func_80013F3C((void *)s0);
    RotMatrixY(*(s16 *)(s1 + 0x12), (void *)s0);
    func_80048D9C((void *)s0, (void *)(*(s32 *)(s2 + 0x20) + 0x34));
    func_80020F34(s0, s1 + 0x18);
    *(u16 *)(s1 + 0x2C) |= 1;
}


INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CCF30);

INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CCF58);

INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CCF68);

extern void (*D_800CE204[])(void);
extern s32 func_801619D0(s32 a0);
extern void func_800CD178(void);

void func_800CCFC8(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CE204[*(u16 *)(param_1 + 2)]();
    if (func_801619D0(iVar1) == 0) {
        ((void (*)(s32))func_800CD178)(param_1);
    }
}




extern s32 func_80146CA0(void *a0);
    void func_800CD030(s32 *a0) {
        *(s16 *)((s32)a0 + 0x60) = 0;
        ((void (*)(void))func_80146CA0)();
    }


extern u16 D_800B99DA;
extern u16 func_801487F4(s32*);
extern s32 func_80146608(s32, s32, s32, s32, s16, s32, s32, s32, s32);
extern s32 func_80146CA0(void*);
extern void func_80147324(s32);

void func_800CD050(s32 arg0) {
    s32 acc;
    s32 i;
    s32 ptr;

    ptr = *(s32*)(arg0 + 0x4C);
    if (!(func_801487F4((s32*)ptr) & 0x90)) {
        func_80146CA0(arg0);
        return;
    }
    *(u16*)(arg0 + 0x60) -= 1;
    if (*(s16*)(arg0 + 0x60) < 0) {
        *(u16*)(arg0 + 0x60) = 0;
    }
    if (D_800B99DA & 3) {
        return;
    }
    acc = 0;
    for (i = 0; i < 3; i++) {
        acc |= func_80146608(9, ptr, 0, -30, 0, (*(s32*)(arg0 + 0x50))++, 0, 12, 1);
    }
    if ((*(s16*)(arg0 + 0x60) == 0) && (acc != 0)) {
        func_80147324(0x747);
        *(u16*)(arg0 + 0x60) = 0xF;
    }
}


extern void func_80162CCC(void);
void func_800CD178(void) {
    func_80162CCC();
}




void func_800CD198(void *a0) {

    extern void (*D_800CE220[])(void);
    D_800CE220[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146578(void);
extern void func_8001CC3C(s32, void *, s32, s32);
extern void func_80149374(s32, s32);
extern void func_800CD5EC(void *);
extern void func_800CD834(void *);
extern void func_80146DB8(void *, void *);
extern void func_80146E90(s32*, s32);
extern s32 func_80146CA0(void *);
extern void func_800CD494(void *);
extern u8 D_800CE1E8[];
extern u8 D_800CE230[];

typedef struct { u16 x, y, z, w; } V8;

void func_800CD1D4(s32 *s1) {
    s32 *s0;
    s32 *s2;
    s32 v0;

    s2 = (s32 *)s1[0x13];
    s0 = (s32 *)((s32 (*)(void))func_80146578)();
    *(s32 *)(s1 + 8) = (s32)s0;
    if (s0 != NULL) {
        func_8001CC3C((s32)s0, D_800CE1E8, 0x238, 0x180);
        *(u8 *)((s32)s0 + 0x27) = 0x21;
        *(s32 *)(s0 + 1) |= 0x40000000;
        func_80149374((s32)s2, (s32)(s1 + 1));
        func_800CD5EC(s1);
        v0 = *(s32 *)((s32)s2 + 0x20);
        *(V8 *)((s32)s0 + 0x10) = *(V8 *)((s32)v0 + 0x10);
        *(u16 *)((s32)s1 + 0x60) = *(u16 *)((s32)s2 + 0x100);
        *(u16 *)((s32)s1 + 0x62) = *(u16 *)((s32)s2 + 0x102);
        *(u16 *)((s32)s1 + 0x64) = *(u16 *)((s32)s2 + 0x104);
        func_800CD834(s1);
        func_80146DB8(s1, D_800CE230);
        ((void (*)(void *, s32))func_80146E90)(s1, 0x20);
        *(u16 *)((s32)s1 + 0x5E) = 0;
        func_80146CA0(s1);
    } else {
        func_800CD494(s1);
    }
}


INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CD2EC);

INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CD494);

extern s32 func_80146E98(s32 a0);
extern void func_80162CCC(void);
extern void func_800CD7A8();
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4);
extern void func_80162FC0(s32 *a0);

void func_800CD508(s32 param_1) {
    register s32 obj __asm__("$17") = param_1;   /* $s1 */
    register s32 bufp __asm__("$16");            /* $s0 */
    u8 dead[0x20];
    char buf[0x20];
    s32 ret;

    ret = ((s32 (*)(void))func_80146E98)();
    if (ret != 0) {
        ((void (*)(s32))func_80162CCC)(obj);
    } else {
        bufp = (s32)buf;
        ((void (*)(s32, void *))func_800CD7A8)(obj, bufp);
        ((void (*)(s32, s32, s32, s32, void *))func_80163194)(obj, 0, 0x20000, 0, bufp);
        ((void (*)(s32 *))func_80162FC0)((s32 *)obj);
    }
}


extern s32 func_801469C8(s32, void *, s32, s32, u16, s32, s32, s32);

void func_800CD57C(void *arg0) {
    if (((s32 (*)(void *, void *, s32, s32, s32, s32, s32, s32))func_801469C8)(
            (void *)0x27, arg0,
            *(s16 *)((char *)arg0 + 6),
            *(s16 *)((char *)arg0 + 0xA),
            *(s16 *)((char *)arg0 + 0xE),
            *(s32 *)((char *)arg0 + 0x50) & 7,
            0, 8) != 0) {
        (*(s32 *)((char *)arg0 + 0x50)) += 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CD5EC);

#include "common.h"

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_80015A2C(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80015954(s32 a0, s32 a1);

typedef struct { s32 w0, w1, w2, w3, w4, w5, w6, w7; } W8_;

void func_800CD63C(s32 a0, s32 a1)
{
    s16 sp10[3];
    s32 sp18[2];
    W8_ sp20;
    s32 t;
    s32 r;

    t = 0x20 - *(s32 *)(a0 + 0x1C);
    r = func_8004787C(*(s16 *)(a0 + 0x66));
    sp10[0] = ((((t << 17) >> 16) * r) / 4096);
    r = func_80047948(*(s16 *)(a0 + 0x66));
    sp10[1] = ((((t << 17) >> 16) * r) / 4096);
    sp10[2] = 0;

    sp20 = *(W8_ *)a1;

    func_80015A2C(a0 + 0x58, (s32)&sp20 + 0x14);
    func_8012F14C((s32)&sp20, (s32)sp10, (s32)sp18);
    func_80015954((s32)sp18, a0 + 4);

    *(u16 *)(a0 + 0x66) = (*(u16 *)(a0 + 0x66) + 0xE3) & 0xFFF;
}


extern void func_80015978(s32 a0, s32 *a1);

void func_800CD758(s32 param_1) {
    func_80015978(param_1 + 4, param_1 + 0x58);
}


extern void func_80015954(s32 a0, s32 a1);

void func_800CD780(s32 param_1) {
    func_80015954(param_1 + 0x58, param_1 + 4);
}


extern void func_80013F3C(s32 a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);

void func_800CD7A8(s32 a0, s32 a1) {
    s32 q = *(s32 *)(a0 + 0x20);
    func_80013F3C(a1);
    func_800126C4(a1, *(s16 *)(a0 + 0x60));
    func_800123F0(a1, *(s16 *)(a0 + 0x64));
    func_80012558(a1, *(s16 *)(a0 + 0x62));
    func_80012558(a1, *(s16 *)(q + 0x12));
    func_800126C4(a1, *(s16 *)(q + 0x10));
    func_800123F0(a1, *(s16 *)(q + 0x14));
}


void func_800CD834(void *a0) {
    s32 v0 = *(s32 *)((s32)a0 + 0x20);
    *(s16 *)(v0 + 0x18) = *(s16 *)(v0 + 0x1A) = 0;
}


INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CD848);

extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80135260(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801202A0[];

typedef struct {
    u16 unk00;
    u8 pad02[0x1E];
    s32 unk20;
    u8 pad24[0x34];
    s32 unk58;
    u8 pad5C[0xB0];
} Ent_CD894;

s32 func_800CD894(void *a0) {
    u8 sp10[8];
    s32 sp18;
    s32 i;
    register s32 tag __asm__("$2");
    Ent_CD894 *base = (Ent_CD894 *)D_801202A0;

    __builtin_memcpy(sp10, (u8 *)a0 + 0x44, 8);
    func_80015978((s32)a0 + 4, &sp18);
    for (i = 0; i < 0x60; i++) {
        Ent_CD894 *e = base + i;
        tag = 0x200;
        if (e->unk00 == tag) {
            s32 f58 = e->unk58;
            if (f58 != 0) {
                s32 f20 = e->unk20;
                if (f20 != 0 && func_80135260(f20, f58, sp10, &sp18) != 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}




void func_800CD948(void *a0) {

    extern void (*D_800CE24C[])(void);
    D_800CE24C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146C3C(void *a0);
extern s32 D_800CE240;

void func_800CD984(s32 a0) {
    s32 a2;

    a2 = func_800D21C4(a0, (s32)&D_800CE240, 0x21);
    if (a2 != 0) {
        *(s32 *)(a2 + 4) |= 0x40000000;
        *(s32 *)(a0 + 0x20) = a2;
        *(s16 *)(a2 + 0x28) = 0x230;
        *(s16 *)(a2 + 0x2A) = 0x1C0;
        func_80146E90((s32 *)a0, 2);
        *(u16 *)(a0 + 2) += 1;
    } else {
        func_80146C3C((void *)a0);
    }
}


extern s32 func_80146E98(s32 a0);
extern s32 func_80146C3C(void *a0);
void func_800CDA0C(int param_1)
{
    if (((int (*)(void))func_80146E98)() != 0) {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}




void func_800CDA44(void *a0) {

    extern void (*D_800CE254[])(void);
    D_800CE254[*(u16 *)((s32)a0 + 0x2)]();
}


extern void *func_800D2294(s32 a0, s32 a1);
extern void func_800233CC(void *a0, u16 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146C3C(void *a0);
extern s32 rand(void);

void func_800CDA80(int param_1)
{
    extern unsigned char D_800CEBF4[];
    void *ptr;
    s32 base;
    s32 r;

    base = (int)D_800CEBF4 + *(s32 *)(param_1 + 0x2c) * 0x40;
    ptr = func_800D2294(param_1, base);
    *(s32 *)(param_1 + 0x20) = ptr;
    if (ptr != 0) {
        r = rand();
        func_800233CC(base, (r & 0x1F) | 0x20);
        *(u32 *)((int)ptr + 4) |= 0x50000000;
        *(s32 *)base = ((r & 0x3F) + 0x40) << 16;
        *(s32 *)(base + 4) = 0;
        func_80146E90((s32 *)param_1, 4);
        *(u16 *)(param_1 + 2) += 1;
    } else {
        func_80146C3C(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CDB4C);

INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CDBA8);

extern void func_800CE004();
void func_800CDDA8(void) {
    func_800CE004();
}




void func_800CDDC8(void *a0) {

    extern void (*D_800CE25C[])(void);
    D_800CE25C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CDE04);

extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_800D22E4(s32 a0);
extern s32 func_80135168(u16 a0, u16 *a1, u16 *a2);
extern void func_80015954(s32 a0, s32 a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80146C3C(void *a0);

void func_800CE004(s32 param_1)
{
    u16 sp20[4];
    u16 sp28[4];
    s32 *p;
    s32 *q;

    *(s32 *)(param_1 + 0x30) = *(s32 *)(param_1 + 0x1C) * 8;
    func_80169A4C(param_1, param_1 + 0x38);
    if (--*(s32 *)(param_1 + 0x1C) == 0)
        goto L_c3c;
    p = (s32 *)(param_1 + 4);
    func_80015978((s32)p, (s32 *)sp20);
    func_800D22E4(param_1);
    q = (s32 *)sp28;
    func_80015978((s32)p, q);
    if ((s16)func_80135168(1, sp20, sp28) == 0)
        goto L_ret0;
    func_80015954((s32)q, (s32)p);
    if (*(u8 *)((s32)q + 6) != 2)
        goto L_cnt;
    if (*(u32 *)(param_1 + 0x2C) < 0x1E01)
        goto L_c3c;
    func_80146A6C(0x11, (void *)param_1, *(s16 *)(param_1 + 6),
                  (s16)(*(u16 *)(param_1 + 0xA) - 8),
                  *(s16 *)(param_1 + 0xE), 0, 0);
    goto L_c3c;

L_cnt:
    *(u16 *)(param_1 + 2) += 1;
    return;
L_ret0:
    *(s32 *)(param_1 + 0x14) += 0x10000;
    return;
L_c3c:
    func_80146C3C((void *)param_1);
}


INCLUDE_ASM("asm/md_MAIN_044/nonmatchings/md_MAIN_044", func_800CE134);



void func_800CE188(void *a0) {

    extern void (*D_800CE268[])(void);
    D_800CE268[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800CE134(void);
void func_800CE1C4(void) {
    func_800CE134();
}


INCLUDE_RODATA("asm/md_MAIN_044/nonmatchings/md_MAIN_044", D_800CCB1C);

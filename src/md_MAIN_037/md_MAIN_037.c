#include "common.h"

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CAE0C);

extern s32 func_800183E0(s32 *a0);

void func_800CAE70(void) {
    extern s32 D_800CB6FC;
    extern s32 D_800CB73C;
    extern s32 D_800CB6BC;
    extern s32 D_800CB95C;

    func_800183E0(&D_800CB6FC);
    func_800183E0(&D_800CB73C);
    D_800CB95C = 0;
    func_800183E0(&D_800CB6BC);
}




void func_800CAEC0(void *a0) {

    extern void (*D_800CB610[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB610[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAF4C(u8 *a0);
void func_800CAF04(u8 *a0) {
    if (func_80161104()) {
        func_800CAF4C(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


#include "common.h"

extern M2C_UNK D_800D57F4;
extern void func_80154274(s32 *a0, s32 a1);
extern void func_801655E4(s32 a0);

void func_800CAF4C(u8 *a0) {
    func_80154274((s32 *)a0, (s32)&D_800D57F4);
    func_801655E4((s32)a0);
    *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
}


extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp4, s32 sp5, s32 sp6, s32 sp7);
extern s32 func_80161208();  /* canonical no-proto (§17a-1) */

void func_800CAF94(void *a0) {
    u16 flag;

    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        if (flag & 0x4000) {
            func_801466F0(0x1E, (s32)a0, 0, -0x40, 0, 0, 0, 0);
        }
        func_80161208(a0);
    }
}


void func_800CB014(void *a0) {
    *(u32 *)((s32)a0 + 0x44) &= ~2;
}


#include "common.h"

extern u8 D_80078EC1;
extern void (*D_800CB634[])(void);
extern void func_800CB358(void);

void func_800CB028(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x19) {
        index = *(u16 *)(a0 + 2);
        D_800CB634[index]();

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))func_800CB358)(a0);
    } else {
        ((void (*)(s32))func_800CB358)(a0);
    }
}


extern void func_8014659C(void);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_800CB358(void);
extern u32 D_800CB61C[];

void func_800CB09C(s32 a0) {
    s32 iVar1;
    s32 iVar2;
    u16 uVar1;

    iVar1 = *(s32 *)(a0 + 0x4C);
    iVar2 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(a0 + 0x20) = iVar2;
    if (iVar2 != 0) {
        func_8001CA1C(iVar2, (s32)&D_800CB61C);
        uVar1 = *(u16 *)(*(s32 *)(iVar1 + 0x20) + 0x12);
        *(u16 *)(iVar2 + 0x12) = uVar1;
        func_80149374(iVar1, a0 + 4);
        func_80146DE8((s32 *)a0, 0, 0xFFF40000, 0xFFE80000);
        func_80146E90((s32 *)a0, 0x3C);
        func_80147324(0x912);
        func_80146CA0((void *)a0);
    } else {
        ((void (*)(s32))func_800CB358)(a0);
    }
}


extern void func_80162FF4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80162FC0(void *a0);
extern s32 func_80146E98(s32 a0);
extern s32 func_80163950(s32 a0);
extern s32 func_8016380C(void *a0, s32 a1);
extern void func_80016714(s8 *a0, s32 a1);
extern void func_80146578(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80147324(s32 a0);
extern void func_80146CA0(void *a0);
extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328(void *a0);
extern void func_800CB358(void);
extern u8 D_800CB628[];

void func_800CB150(void *a0) {
    s32 sp20;
    s32 flags;
    s32 sh;
    s32 t;

    func_80162FF4((s32)a0, 0, 0x40000, 0);
    func_80162FC0(a0);
    if (func_80146E98((s32)a0) != 0) {
        func_80146CA0(a0);
        return;
    }
    flags = func_80163950((s32)a0) != 0;
    sh = flags << 13;
    t = sh | func_8016380C(a0, (s32)&sp20);
    if (t == 0) {
        goto tail;
    }
    if (t != 0x8000) {
        goto alloc;
    }
    *(s32 *)((s32)a0 + 0x2C) = 0;
    *(s32 *)((s32)a0 + 0x24) = 0;
    goto tail;
alloc:
    func_80016714(*(s8 **)((s32)a0 + 0x20), 0x84);
    *(s32 *)((s32)a0 + 0x20) = 0;
    t = ((s32 (*)(void))func_80146578)();
    *(s32 *)((s32)a0 + 0x20) = t;
    if (t != 0) {
        func_8001CB6C((u8 *)t, (s32)D_800CB628, 0x1A0, 0x100);
        *(u8 *)((s32)t + 0x27) = 0x1B;
        *(u16 *)((s32)t + 0x10) = 0x400;
        func_80146E90((s32 *)a0, 0x20);
        for (t = 0; t < 4; t++) {
            func_80146A6C(0x45, a0, *(s16 *)((s32)a0 + 6), *(s16 *)((s32)a0 + 0xA),
                          *(s16 *)((s32)a0 + 0xE), t, 0);
        }
        func_80147324(0x913);
        func_80146CA0(a0);
        return;
    }
    ((void (*)(s32))func_800CB358)(a0);
tail:
    func_80163408((s32)a0, 0x27, 0, 0x80);
    ((void (*)(s32))func_80163328)(a0);
}


extern void func_800CB378(s32 a0);

void func_800CB2A8(s32 a0) {
    s32 v1;
    u16 v0;

    v1 = *(s32 *)(a0 + 0x20);
    v0 = *(u16 *)(v1 + 0x1A);
    v0 = v0 + 0x80;
    *(u16 *)(v1 + 0x1A) = v0;
    *(u16 *)(v1 + 0x18) = v0;
    if (func_80146E98((s32)a0) != 0) {
        func_80146CA0((void *)a0);
    } else {
        func_800CB378(a0);
    }
}


extern void func_800CB358(void);

void func_800CB30C(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    s16 v = *(u16 *)(p + 0x1A) - 0x300;
    *(u16 *)(p + 0x1A) = v;
    *(u16 *)(p + 0x18) = v;
    if (v < 0) {
        ((void (*)(s32))func_800CB358)(a0);
    }
}


extern void func_80162CCC(void);
void func_800CB358(void) {
    func_80162CCC();
}


extern u8 D_801202A0[];
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);

void func_800CB378(s32 a0) {
    u8 *p;
    s16 buf[4];
    s32 s1;
    s1 = a0;
    p = D_801202A0;
    if (p < p + 0x6480) {
        do {
            if (func_8014C308(s1, (s32)p, 0x27, 0x80) != 0) {
                if (func_8014C278(s1, (s32)p, 0x60) != 0) {
                    func_80015978((s32)(p + 4), (s32 *)buf);
                    buf[3] = 0;
                    func_8014C3A4((void *)s1, (s32)p, 0x27, (s32)buf);
                }
            }
            p += 0x10C;
        } while (p < D_801202A0 + 0x6480);
    }
}



extern void func_80146C3C(void);

void func_800CB424(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB654[])(void);
    if (D_80078EC1 == 0x19) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB654[v0]();
    } else {
        func_80146C3C();
    }
}


extern void func_801465C0(void);
extern void func_80146C3C(void);
extern void func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);

extern u8 D_800CB648;
extern s32 D_800CB65C[1];
extern s32 D_800CB660[1];
extern s32 D_800CB664[1];

void func_800CB480(s32 arg0)
{
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    if (iVar1 == 0) {
        ((void (*)(s32))func_80146C3C)(arg0);
    } else {
        *(s32 *)(arg0 + 0x20) = iVar1;
        func_8001CC3C(iVar1, (s32)&D_800CB648, 0x1B8, 0x100);
        *(u8 *)(iVar1 + 0x27) = 0x1A;
        *(u16 *)(iVar1 + 0x1A) = 0x2000;
        *(u16 *)(iVar1 + 0x18) = 0x2000;
        *(s32 *)(arg0 + 0x10) = *(s32 *)((s32)&D_800CB65C + (*(s32 *)(arg0 + 0x2C)) * 0x10);
        *(s32 *)(arg0 + 0x14) = *(s32 *)((s32)&D_800CB660 + (*(s32 *)(arg0 + 0x2C)) * 0x10);
        *(s32 *)(arg0 + 0x18) = *(s32 *)((s32)&D_800CB664 + (*(s32 *)(arg0 + 0x2C)) * 0x10);
        *(s32 *)(arg0 + 0x1C) = 0x10;
        (*(u16 *)(arg0 + 2))++;
    }
}


extern void func_80146C3C(void);

void func_800CB55C(s32 *arg0) {
    arg0[1] += arg0[4];
    arg0[3] += arg0[6];
    arg0[5] += 0xC000;
    arg0[2] += arg0[5];
    if (--arg0[7] == -1) {
        ((void (*)(s32))func_80146C3C)((s32)arg0);
    }
}


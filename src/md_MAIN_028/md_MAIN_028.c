#include "common.h"

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CBE94[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBE94[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CAEC0);

void func_800CB0D8(s32 a0) {
    typedef struct { u8 pad[0x50]; s32 f50; } Struct80078E78;
    extern Struct80078E78 D_80078E78;
    extern s32 D_80078EC8;
    extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_80165A20(s32);
    register s32 v __asm__("$16");
    register Struct80078E78 *p __asm__("$19");
    s32 q;

    v = a0;
    p = &D_80078E78;
    if ((D_80078EC8 & 0x1F) == 0) {
        func_801466F0(0xE, v, 0, 0, 0, ((((rand() % 16) + 0x10) << 12) / 360), 0, 1);
        func_801466F0(0xE, v, 0, 0, 0, -((((rand() % 16) + 0x10) << 12) / 360), 0, 1);
    }
    if ((p->f50 & 0x3F) == 0) {
        if (rand() & 1) {
            q = ((((rand() % 16) + 0x10) << 12) / 360);
            func_801466F0(0xE, v, 0, 0, 0, q, 1, 1);
        } else {
            q = -((((rand() % 16) + 0x10) << 12) / 360);
            func_801466F0(0xE, v, 0, 0, 0, q, 1, 1);
        }
    }
    if (p->f50 == 0) {
        func_80165A20(v);
    }
}


extern void func_80147364(s32 a, s32 b);
void func_800CB32C(void) {
    func_80147364(0x4, 0x838);
}


extern u8 D_80078EC1;
extern void (*D_800CBEB8[])();
extern s32 func_800CB600();

void func_800CB350(int param_1)
{
    s32 pad[2];

    if (D_80078EC1 != 21) {
        func_800CB600();
    } else {
        D_800CBEB8[*(u16 *)(param_1 + 2)]();
    }
}


extern void func_80146578(void);
extern void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3);
extern void func_8001CB00(s32 a0, void *a1, s32 a2, s32 a3);
extern void func_80149374(s32 a0, s32 a1);
extern void func_8014964C(s32 a0, s32 a1);
extern void func_800CB620();
extern void func_80146CA0(void *a0);
extern s32 func_800CB600();
extern u8 D_800CBEA0[];
extern void (*D_800CBEAC[])(void);

void func_800CB3AC(s32 a0) {
    s32 s2;
    s32 s1;

    s2 = *(s32 *)(a0 + 0x4C);
    s1 = ((s32 (*)(void))func_80146578)();
    *(s32 *)(a0 + 0x20) = s1;
    if (s1 != 0) {
        if (*(s32 *)(a0 + 0x54) == 0) {
            func_8001CC3C(s1, D_800CBEA0, 0x1A8, 0x100);
            func_80149374(s2, a0 + 4);
        } else {
            func_8001CB00(s1, D_800CBEAC, 0x1A0, 0x100);
            *(u16 *)(s1 + 0x2C) = 1;
            func_8014964C(s2, a0 + 4);
        }
        *(u8 *)(s1 + 0x27) = 0x19;
        *(u16 *)(a0 + 0x18) = 0;
        func_800CB620(a0);
        func_80146CA0((void *)a0);
    } else {
        func_800CB600(a0);
    }
}


extern u16 D_800B99DA;
extern s32 func_800CB6D4(s32 a0);
extern void func_800CB684(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 rand(void);

void func_800CB484(s32 *a0) {
    u16 *p = *(u16 **)((u8 *)a0 + 0x20);
    if (*(s32 *)((u8 *)a0 + 0x54) != 0) {
        if (D_800B99DA & 1) {
            p[0x15] = 0x100;
        } else {
            p[0x15] = 0x120;
        }
    }
    if (func_800CB6D4((s32)a0) != 0) {
        s16 v = *(u16 *)((u8 *)a0 + 0x18);
        *(u16 *)((u8 *)a0 + 0x18) = v + 1;
        if (v >= 4) {
            func_800CB684((s32)a0, 0x200);
            func_80146CA0(a0);
            return;
        }
        if (*(s32 *)((u8 *)a0 + 0x54) != 0 && (rand() & 3) == 0) {
            func_80146E90(a0, 0x20);
            *(u16 *)((u8 *)a0 + 2) = 3;
        } else {
            func_800CB684((s32)a0, 0x80);
        }
    }
}


extern s32 func_800CB6D4(s32 a0);
extern s32 func_800CB600();
void func_800CB564(int param_1)
{
    if (((int (*)(void))func_800CB6D4)() != 0) {
        ((void (*)(int))func_800CB600)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB59C);

    extern void func_80162CCC(void);
    s32 func_800CB600(void)
{
        func_80162CCC();
    }


INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB620);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB684);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB6D4);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB8A0);

extern u8 D_80078EC1;
extern void (*D_800CBEE0[])();
extern void func_80146C3C();

void func_800CBA74(int param_1)
{
    if (D_80078EC1 != 21) {
        func_80146C3C();
    } else {
        D_800CBEE0[*(u16 *)(param_1 + 2)]();
    }
}


typedef struct { s32 w[4]; } Blk_800CBAD0;

void func_800CBAD0(s32 a0) {
    extern void func_800CB8A0(s32 a0);

    s32 s;
    s32 v;

    s = *(s32 *)(a0 + 0x34);
    if (*(s32 *)(a0 + 0x2C) & 0x8000) {
        goto L_inc;
    }
    if ((*(s32 *)(a0 + 0x1C))++ < 8) {
        *(u16 *)(a0 + 0x28) += 0x120;
    } else {
        *(s32 *)(a0 + 0x1C) = 0;
        *(u16 *)(a0 + 2) = 4;
    }
    v = *(s32 *)(s + 0x20);
    *(Blk_800CBAD0 *)(a0 + 0x38) = *(Blk_800CBAD0 *)(v + 0x34);
    *(Blk_800CBAD0 *)(a0 + 0x48) = *(Blk_800CBAD0 *)(v + 0x44);
    func_800CB8A0(a0);
    return;

L_inc:
    *(u16 *)(a0 + 2) += 1;
}


void func_800CBBA0(void *a0) {
    typedef struct { s32 w[4]; } S16;
    extern void func_800CB8A0(s32 a0);
    s32 a1;
    s32 n;
    s32 m;
    s32 v0;
    a1 = *(s32 *)((s32)a0 + 0x34);
    if ((*(s32 *)((s32)a0 + 0x1C))++ < 10) {
        *(u16 *)((s32)a0 + 0x28) += 0x120;
    } else {
        n = *(u16 *)((s32)a0 + 2);
        n += 1;
        *(u16 *)((s32)a0 + 0x12) = (s16)*(u16 *)(a1 + 0x12) >> 1;
        m = *(u16 *)(a1 + 0x1A);
        *(s32 *)((s32)a0 + 0x30) = 0x20;
        *(s32 *)((s32)a0 + 0x1C) = -0xC0;
        *(u16 *)((s32)a0 + 0x2A) = 0x500;
        *(u16 *)((s32)a0 + 2) = n;
        *(u16 *)((s32)a0 + 0x1A) = (s16)m >> 1;
    }
    v0 = *(s32 *)(a1 + 0x20);
    *(S16 *)((s32)a0 + 0x38) = *(S16 *)(v0 + 0x34);
    *(S16 *)((s32)a0 + 0x48) = *(S16 *)(v0 + 0x44);
    func_800CB8A0((s32)a0);
}


void func_800CBC7C(s32 param_1) {
    extern void func_800CB8A0();
    extern s32 rand(void);
    s32 iVar2;
    s32 iVar3;

    if (*(s16 *)(param_1 + 0x28) > *(s16 *)(param_1 + 0x2A)) {
        iVar2 = *(s32 *)(param_1 + 0x1C);
        if (iVar2 <= 0) {
            goto LAB_800CBCFC;
        }
        *(u16 *)(param_1 + 0x2A) = (rand() & 0x180) + 0x500;
        iVar2 = -0xA0;
    } else {
        iVar2 = *(s32 *)(param_1 + 0x1C);
        if (iVar2 >= 0) {
            goto LAB_800CBCFC;
        }
        *(u16 *)(param_1 + 0x2A) = (rand() & 0x180) + 0x800;
        iVar2 = 0xA0;
    }
    *(s32 *)(param_1 + 0x1C) = iVar2;
LAB_800CBCFC:
    *(u16 *)(param_1 + 0x28) = *(u16 *)(param_1 + 0x28) + *(s32 *)(param_1 + 0x1C);
    *(s32 *)(param_1 + 0x4C) = *(s32 *)(param_1 + 0x4C) + *(s16 *)(param_1 + 0x12);
    *(s32 *)(param_1 + 0x50) -= 3;
    *(s32 *)(param_1 + 0x54) = *(s32 *)(param_1 + 0x54) + *(s16 *)(param_1 + 0x1A);
    func_800CB8A0(param_1);
    iVar3 = *(s32 *)(param_1 + 0x30);
    *(s32 *)(param_1 + 0x30) = iVar3 - 1;
    if (iVar3 == 0) {
        *(u16 *)(param_1 + 2) += 1;
    }
}


void func_800CBD78(s32 param_1) {
    extern void func_800CB8A0();
    s16 var;

    var = *(u16 *)(param_1 + 0x28) - 0x100;
    *(u16 *)(param_1 + 0x28) = var;
    if (var > 0) {
        *(s32 *)(param_1 + 0x50) -= 3;
        func_800CB8A0(param_1);
    } else {
        func_80146C3C();
    }
}


typedef struct { s32 w[4]; } Struct16;

extern void func_800CB8A0(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_800CBDD0(s32 a0) {
    s32 s1;
    s32 v0;
    s32 var1C;

    s1 = *(s32 *)(a0 + 0x34);
    v0 = *(s32 *)(s1 + 0x20);
    *(Struct16 *)(a0 + 0x38) = *(Struct16 *)(v0 + 0x34);
    *(Struct16 *)(a0 + 0x48) = *(Struct16 *)(v0 + 0x44);
    func_800CB8A0(a0);
    var1C = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = var1C;
    if (var1C == -1) {
        func_80146A6C(0x35, (void *)s1, 0, 0, 0, 0x8000, 0);
        *(s32 *)(a0 + 0x1C) = 0x18;
    }
}


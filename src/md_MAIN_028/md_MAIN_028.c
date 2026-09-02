#include "common.h"

#include "common.h"

extern s32 func_800183E0(s32 *a0);

void func_800CAE0C(void) {
    extern s32 D_800CBF54;
    extern s32 D_800CBF14;

    func_800183E0(&D_800CBF54);
    func_800183E0(&D_800CBF14);
}




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


#include "common.h"

extern s32 rand(void);
extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147324(s32);
extern s32 func_80146994(s32, s32, s32, s32);
extern void func_801655E4(s32);
extern s32 func_80165910(void);

void func_800CAEC0(s32 a0) {
    if (func_80165910() == 0) {
        func_801655E4(a0);
    }
    func_80146994(0x35, a0, 0, 0);
    func_80147324(0x838);
    func_801466F0(0xE, a0, 0, 0, 0, ((((rand() % 16) + 0x10) << 12) / 360), 0, 1);
    func_801466F0(0xE, a0, 0, 0, 0, -((((rand() % 16) + 0x10) << 12) / 360), 0, 1);
    func_801466F0(0xE, a0, 0, 0, 0, ((((rand() % 16) + 0x10) << 12) / 360), 1, 1);
    func_801466F0(0xE, a0, 0, 0, 0, -((((rand() % 16) + 0x10) << 12) / 360), 1, 1);
    *(u8 *)(a0 + 0x197) += 1;
}


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


extern u16 D_800B99DA;
extern s32 func_80146E98(s32 a0);
extern void func_800CB684(s32 a0, s32 a1);

void func_800CB59C(s32 a0) {
    s32 ptr;
    s32 v;

    v = D_800B99DA & 1;
    ptr = *(s32 *)((s32)a0 + 0x20);
    if (v == 0) {
        v = 0x160;
    } else {
        v = 0x140;
    }
    *(u16 *)(ptr + 0x2A) = v;
    if (func_80146E98((s32)a0) != 0) {
        func_800CB684((s32)a0, 0x100);
        *(u16 *)((s32)a0 + 2) = 1;
    }
}


    extern void func_80162CCC(void);
    s32 func_800CB600(void)
{
        func_80162CCC();
    }


void func_800CB620(s32 arg0) {
    s32 v;
    *(u16 *)(arg0 + 0x10) = *(u16 *)(arg0 + 6);
    *(u16 *)(arg0 + 0x12) = *(u16 *)(arg0 + 0xA);
    *(u16 *)(arg0 + 0x14) = *(u16 *)(arg0 + 0xE);
    v = rand() & 0x1F;
    v <<= 7;
    *(u16 *)(arg0 + 0x64) = v;
    *(u16 *)(arg0 + 0x66) = v;
    func_800CB684(arg0, 0x200);
    func_800CB6D4(arg0);
}


void func_800CB684(s32 a0, s32 a1) {
    extern s32 rand(void);
    *(u16 *)(a0 + 0x60) = a1 + (rand() & 0x7F);
    *(u16 *)(a0 + 0x62) = a1 + (rand() & 0x7F);
}


#include "common.h"

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 ratan2(s32 a0, s32 a1);

s32 func_800CB6D4(s32 a0) {
    s32 s1;
    s16 tmp[3];
    s32 v0;
    s16 v1;
    s32 sum;
    s16 diff;

    s1 = *(s32 *)(a0 + 0x20);

    v0 = func_80047948(*(s16 *)(a0 + 0x64));
    v1 = *(s16 *)(a0 + 0x60);
    tmp[0] = (v1 * v0) / 4096;

    if (*(s32 *)(a0 + 0x54) == 0) {
        tmp[1] = 0;
        v0 = func_8004787C(*(s16 *)(a0 + 0x64));
        v1 = *(s16 *)(a0 + 0x62);
        tmp[2] = (v1 * v0) / 4096;
    } else {
        v0 = func_8004787C(*(s16 *)(a0 + 0x64));
        v1 = *(s16 *)(a0 + 0x62);
        tmp[1] = (v1 * v0) / 4096;
        tmp[2] = 0;
    }

    v0 = func_80012F74(*(s16 *)(a0 + 0x6), (s16)(*(u16 *)(a0 + 0x10) + (u16)tmp[0]), 0xA, 1);
    *(s16 *)(a0 + 0x6) = v0;

    v0 = func_80012F74(*(s16 *)(a0 + 0xA), (s16)(*(u16 *)(a0 + 0x12) + (u16)tmp[1]), 0xA, 1);
    *(s16 *)(a0 + 0xA) = v0;

    v0 = func_80012F74(*(s16 *)(a0 + 0xE), (s16)(*(u16 *)(a0 + 0x14) + (u16)tmp[2]), 0xA, 1);
    *(s16 *)(a0 + 0xE) = v0;

    v0 = ratan2(*(s16 *)(a0 + 0x6) - *(s16 *)(a0 + 0x44), *(s16 *)(a0 + 0x46) - *(s16 *)(a0 + 0xA));
    *(u16 *)(s1 + 0x14) = (v0 - 0x200) & 0xFFF;

    {
        s32 f50 = *(s32 *)(a0 + 0x50);
        sum = *(u16 *)(a0 + 0x64) + f50;
    }
    *(u16 *)(a0 + 0x64) = sum;
    if (*(s32 *)(a0 + 0x50) >= 0) {
        diff = sum - *(u16 *)(a0 + 0x66);
    } else {
        diff = *(u16 *)(a0 + 0x66) - sum;
    }

    if (diff < 0x1001) {
        return 0;
    }
    *(u16 *)(a0 + 0x64) = *(u16 *)(a0 + 0x66);
    return 1;
}


void func_800CB8A0(void *a0) {
    extern s32 func_80017DC4(void *a0, void *a1);
    extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
    extern void func_800D20C0(void *a0, void *a1, s32 a2);
    extern void func_800D23D0(void *a0);
    extern void func_80017E68(void *a0, void *a1);
    extern void RotMatrixYXZ(void *a0, void *a1);
    extern void func_80048D9C(void *a0, void *a1);
    extern s32 func_80017758(void *a0, void *a1);
    extern u8 D_800CBECC[];

    s16 vecA[4];
    s16 rot[4];
    u8 info[0x38];
    u8 s2vec[0x20];
    s16 mtx[16];
    u16 fld;
    u16 fld2;
    s16 ang;
    u8 *tbl;
    s8 last;
    s16 i;

    fld = *(u16 *)((s32)a0 + 0x28);
    vecA[2] = fld;
    vecA[1] = fld;
    vecA[0] = fld;
    func_80017DC4(vecA, s2vec);

    vecA[2] = 0;
    vecA[0] = 0;
    vecA[1] = -0x2C;
    func_8012F14C((s32)a0 + 0x38, (s32)vecA, (s32)vecA);

    func_800D20C0(vecA, rot, 5);
    func_800D23D0(rot);

    *(s16 *)(info + 0x0C) = 0;
    *(s16 *)(info + 0x0A) = 0;
    *(s16 *)(info + 0x08) = 0;
    *(s16 *)(info + 0x1C) = 0;
    *(s16 *)(info + 0x14) = 0;
    *(s16 *)(info + 0x04) = 0;

    fld2 = *(u16 *)((s32)a0 + 0x28);

    *(u8 *)(info + 0x26) = 0;
    *(u8 *)(info + 0x22) = 0;
    *(u8 *)(info + 0x21) = 0;
    *(u8 *)(info + 0x20) = 0;
    *(u8 *)(info + 0x2A) = 0;
    *(u8 *)(info + 0x29) = 0;
    *(u8 *)(info + 0x28) = 0;
    *(u8 *)(info + 0x2E) = 0;
    *(u8 *)(info + 0x2D) = 0;
    *(u8 *)(info + 0x2C) = 0;
    *(u32 *)(info + 0x30) = 0x50000000;

    ang = (s16)fld2 >> 6;
    ang = ang + 0x60;
    *(s8 *)(info + 0x25) = (s8)ang;
    *(s8 *)(info + 0x24) = (s8)ang;
    func_80017E68(vecA, s2vec);

    RotMatrixYXZ(rot, mtx);
    func_80048D9C(s2vec, mtx);

    tbl = D_800CBECC;
    for (i = 0; i < 4; i++) {
        *(s16 *)(info + 0x00) = (s8)*tbl; tbl++;
        *(s16 *)(info + 0x02) = (s8)*tbl; tbl++;
        *(s16 *)(info + 0x10) = (s8)*tbl; tbl++;
        *(s16 *)(info + 0x12) = (s8)*tbl; tbl++;
        *(s16 *)(info + 0x18) = (s8)*tbl; tbl++;
        last = (s8)*tbl; tbl--;
        *(s16 *)(info + 0x1A) = last;
        func_80017758(info, s2vec);
    }
}


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
    extern void func_800CB8A0();

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
    extern void func_800CB8A0();
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

extern void func_800CB8A0();
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


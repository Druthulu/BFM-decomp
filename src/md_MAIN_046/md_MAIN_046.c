#include "common.h"

void func_800CCB20(void) {
}

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CCB28);

extern void func_80147324(s32 a0);
extern void func_8014B5C4(s32 *a0, s32 a1, s32 a2);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_800CCB78(void *a0) {
    func_80147324(0x8E3);
    func_8014B5C4((s32 *)a0, 5, 0);
    func_801466F0(0x13, (s32)a0, 0, 0, 0, 0, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 0, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 1, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 2, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 3, 0, 0);
    *(s16 *)((s32)a0 + 0x1C8) = 0xFF;
    func_801599A4(a0);
    func_80159B3C(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CCD50(void);
void func_800CCC8C(s32 *a0) {
    func_80147078(a0, 33);
    ((void (*)(void *))func_800CCD50)(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CCCF4(void *a0);
void func_800CCCC0(s32 *a0) {
    func_80147078(a0, 33);
    func_800CCCF4(a0);
}




void func_800CCCF4(void *a0) {

    extern void (*D_800CE044[])(void);
    D_800CE044[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800CCD50(void);
void func_800CCD30(void) {
    func_800CCD50();
}


void func_800CCD50(void) {
    register void *a0 __asm__("$4");
    extern void func_80154274(s32 *a0, s32 a1);
    extern void func_80146D90(s32 a0);
    extern void func_800CCDB0(s32 *a0);
    extern M2C_UNK D_800CE010;
    s32 s0;
    s32 v0;
    u16 v1;

    s0 = (s32)a0;
    func_80154274((s32 *)s0, (s32)&D_800CE010);
    v0 = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(v0 + 0x12);
    *(u16 *)(s0 + 0x246) = 0x200;
    *(u16 *)(s0 + 0x244) = v1;
    func_80146D90(s0);
    func_800CCDB0((s32 *)s0);
    *(u16 *)(s0 + 0x240) = 0;
    func_80147324(0x8E4);
}


void func_800CCDB0(s32 *a0) {
    *(s32 *)((s32)a0 + 0x23C) = 0;
    *(s32 *)((s32)a0 + 0x238) = 0;
    *(s32 *)((s32)a0 + 0x234) = 0;
    *(s16 *)((s32)a0 + 2) = 1;
}


void func_800CCDC8(s32 *param_1)
{
    s32 v1;
    s32 v0;

    if (func_800CD240() != 0) return;
    func_800CD288(param_1);
    if (func_800CD494(param_1) != 0) return;
    v0 = func_800CD5CC(param_1);
    if (v0 != 0)
        func_800CD6A4(param_1, v0);
    v1 = func_801612B8(param_1, 0);
    if ((v1 & 0x4000) != 0) {
        func_800CCFA8(param_1);
        return;
    }
    if (v1 == 0 || v1 == 0x8000) {
        func_801477E8(param_1, 0);
        func_80146CA0(param_1);
        return;
    }
    if (func_801496D4(param_1) != 0) {
        func_800CCEB8(param_1);
        return;
    }
    func_801483E8(param_1);
    *(s32 *)((u8 *)param_1 + 0x44) |= 0x1000;
}


extern void func_801477E8(s32 *a0, s32 a1);

void func_800CCEB8(void *arg0) {
    func_801477E8((s32 *)arg0, 0xFFEA0000);
    *(s16 *)((s32)arg0 + 2) = 2;
}


#include "common.h"

extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_800CD494(void *a0);
extern void func_800CD5CC(void *a0);
extern void func_8016151C(void *a0);

void func_800CCEEC(void *arg0) {
    s32 v1;
    s32 v0;

    if (func_800CD240() != 0) {
        return;
    }
    func_800CD288(arg0);
    if (((s32 (*)(void *))func_800CD494)(arg0) != 0) {
        return;
    }
    func_80148038((s32)arg0, 0x1A000);
    func_80147460((s32)arg0);
    v0 = ((s32 (*)(void *))func_800CD5CC)(arg0);
    if (v0 != 0) {
        func_800CD6A4(arg0, v0);
    }
    v1 = ((s32 (*)(void *))func_8016151C)(arg0);
    if ((v1 & 0x4000) != 0) {
        func_800CCFA8(arg0);
        return;
    }
    if (v1 != 0) {
        *(s16 *)((s32)arg0 + 2) = 1;
        return;
    }
    *(s32 *)((s32)arg0 + 0x44) |= 0x1000;
}


extern s16 D_801152B0;
extern s16 D_801152B4;

void func_800CCFA8(s32 *a0) {
    s32 t = D_801152B0 << 6;
    *(s32 *)((s32)a0 + 0x238) = 0x80000;
    *(s32 *)((s32)a0 + 0x234) = t;
    *(s32 *)((s32)a0 + 0x23C) = D_801152B4 << 6;
    *(s16 *)((s32)a0 + 2) = 3;
}


extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80147F50(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_800CD494(void *a0);
extern void func_800CD5CC(void *a0);
extern void func_8016151C(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern s16 D_801152B0;
extern s16 D_801152B4;

void func_800CCFDC(void *arg0) {
    s32 ret;

    if (func_800CD240(arg0) != 0) {
        return;
    }
    func_80146DE8((s32 *)arg0, *(s32 *)((s32)arg0 + 0x234), *(s32 *)((s32)arg0 + 0x238), *(s32 *)((s32)arg0 + 0x23C));
    func_80147F50((s32)arg0);
    func_801473EC((s32 *)arg0);
    func_80148038((s32)arg0, 0x1A000);
    func_80147460((s32)arg0);
    if (((s32 (*)(void *))func_800CD494)(arg0) != 0) {
        return;
    }
    func_800CD5CC(arg0);
    ret = ((s32 (*)(void *))func_8016151C)(arg0);
    if (ret & 0x4000) {
        *(s32 *)((s32)arg0 + 0x234) = D_801152B0 << 6;
        *(s32 *)((s32)arg0 + 0x238) = 0x80000;
        *(s32 *)((s32)arg0 + 0x23C) = D_801152B4 << 6;
        *(s16 *)((s32)arg0 + 2) = 3;
    } else if (ret != 0) {
        func_80146E90((s32 *)arg0, 8);
        func_80146CA0(arg0);
    } else {
        *(s32 *)((s32)arg0 + 0x44) |= 0x1000;
    }
}


extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80147F50(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_800CD494(void *a0);
extern void func_800CD5CC(void *a0);
extern s32 func_801612B8(void *a0, s32 a1);
extern s32 func_80146E98(s32 a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern s16 D_801152B0;
extern s16 D_801152B4;

void func_800CD0DC(void *arg0) {
    s32 ret;

    if (func_800CD240() != 0) {
        return;
    }
    func_80146DE8((s32 *)arg0, *(s32 *)((s32)arg0 + 0x234), *(s32 *)((s32)arg0 + 0x238), *(s32 *)((s32)arg0 + 0x23C));
    func_80147F50((s32)arg0);
    func_801473EC((s32 *)arg0);
    if (((s32 (*)(void *))func_800CD494)(arg0) != 0) {
        return;
    }
    func_800CD5CC(arg0);
    ret = func_801612B8(arg0, 0);
    if (func_80146E98((s32)arg0) != 0) {
        if (ret & 0x4000) {
            *(s32 *)((s32)arg0 + 0x234) = D_801152B0 << 6;
            *(s32 *)((s32)arg0 + 0x238) = 0x80000;
            *(s32 *)((s32)arg0 + 0x23C) = D_801152B4 << 6;
            *(s16 *)((s32)arg0 + 2) = 3;
        } else if (ret == 0 || ret == 0x8000) {
            func_801477E8((s32 *)arg0, 0xFFEA0000);
            *(s16 *)((s32)arg0 + 2) = 2;
        } else {
            *(s32 *)((s32)arg0 + 0x23C) = 0;
            *(s32 *)((s32)arg0 + 0x238) = 0;
            *(s32 *)((s32)arg0 + 0x234) = 0;
            *(s16 *)((s32)arg0 + 2) = 1;
        }
    } else {
        *(s32 *)((s32)arg0 + 0x44) |= 0x1000;
    }
}


extern void func_801553C0(s32 a0);
extern void func_801553A8(s32 *a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_800CD1F4(s32 *a0) {
    func_801553C0((s32)a0);
    func_801553A8(a0);
    func_80154A74((s32)a0, 0x11);
    *(s32 *)((u8 *)a0 + 0x44) &= ~0x1000;
}


extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

s32 func_800CD240(void *arg0) {
    s32 s0;

    s0 = (s32)arg0;
    __asm__ __volatile__("" : "=r"(s0) : "0"(s0));
    if (*(s16 *)(s0 + 0x1C8) != 0) {
        return 0;
    }
    func_801599A4((void *)s0);
    func_80159B3C((void *)s0);
    return 1;
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD288);

extern void func_800CDA14(s32 a0);

void func_800CD494(void *a0) {
    register s32 rv __asm__("$2");
    s32 s0;
    s32 s1;
    u16 v0;
    u16 v1;

    s0 = (s32)a0;
    s1 = *(s32 *)(s0 + 0x20);
    *(s32 *)(s0 + 0x44) |= 2;
    v0 = func_80148800((s32 *)a0);
    if (v0 & 0x90) {
        *(u16 *)(s0 + 0x240) = 0;
        func_80147324(0x8E4);
    }
    v0 = func_801487F4((s32 *)s0);
    if (v0 & 0x90) {
        func_800CDA14(s0);
        v0 = *(u16 *)(s0 + 0x246);
        v0 = v0 + 8;
        *(u16 *)(s0 + 0x246) = v0;
        if ((s16)v0 >= 0x201) {
            *(u16 *)(s0 + 0x246) = 0x200;
        }
        v0 = *(u16 *)(s0 + 0x240);
        v1 = *(u16 *)(s0 + 0x246);
        v0 = v0 + v1;
        *(u16 *)(s0 + 0x240) = v0;
        if ((s16)v0 >= 0x1000) {
            *(u16 *)(s0 + 0x240) = 0;
            func_80147324(0x8E4);
        }
    } else {
        v0 = *(u16 *)(s0 + 0x246);
        v0 = v0 - 0x20;
        *(u16 *)(s0 + 0x246) = v0;
        if ((s16)v0 <= 0) {
            *(u16 *)(s0 + 0x246) = 0;
        }
    }
    v0 = *(u16 *)(s0 + 0x244);
    v1 = *(u16 *)(s0 + 0x246);
    v0 = v0 + v1;
    v0 = v0 & 0xFFF;
    *(u16 *)(s0 + 0x244) = v0;
    *(u16 *)(s1 + 0x12) = v0;
    if (*(s16 *)(s0 + 0x246) == 0) {
        func_801599A4((void *)s0);
        func_80159B3C((void *)s0);
        rv = 1;
    } else {
        rv = 0;
    }
    __asm__ __volatile__("" : : "r"(rv));
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD5CC);

extern void func_8001382C(s32 a0, void *a1, void *a2);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 D_800CE058[3];

void func_800CD6A4(void *arg0, void *arg1) {
    s32 sp10[4];
    s32 ret;

    ret = func_8014C59C(arg0, arg1);
    func_8001382C((ret + 0x800) & 0xFFF, D_800CE058, sp10);
    *(s32 *)((s32)arg0 + 0x234) = sp10[0];
    *(s32 *)((s32)arg0 + 0x238) = sp10[1];
    *(s32 *)((s32)arg0 + 0x23C) = sp10[2];
}


extern s16 D_800CE8D4;
extern void (*D_800CE080[])(void);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8014ACC0(s32 a0, s32 a1);
extern s32 func_80161A30(s32 a0);
extern void func_800CD94C(void);

void func_800CD708(s32 param_1)
{
    s32 s0;
    s32 iVar1;
    s0 = *(s32 *)(param_1 + 0x4C);
    D_800CE080[*(u16 *)(param_1 + 2)]();

    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) |= (*(s32 *)(*(s32 *)(s0 + 0x20) + 4)) & 0x80000000;

    *(s16 *)(param_1 + 0x60) = 0;

    iVar1 = *(s32 *)(s0 + 0x20);
    D_800CE8D4 = func_80012ABC(D_800CE8D4, *(s16 *)(iVar1 + 0x12), 0xA);

    func_8014ACC0(s0, 1);
    if (func_80161A30(s0) != 0) {
        return;
    }
    ((void (*)(s32))func_800CD94C)(param_1);
}


extern s32 func_8014659C(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_800CD96C(s32 a0);
extern void func_80146CA0(void *a0);
extern s32 D_800CE8CC;
extern s16 D_800CE8D4;
extern void func_800CD94C(void);

void func_800CD7D8(s32 a0) {
    s32 s0;
    s32 s2;
    s2 = *(s32 *)(a0 + 0x4C);
    s0 = func_8014659C();
    *(s32 *)(a0 + 0x20) = s0;
    if (s0 != 0) {
        func_8001C214(s0, (s32)&D_800CE8CC);
        *(s32 *)(s0 + 4) |= 0x50000000;
        *(s16 *)(s0 + 0x1C) = 0;
        *(s16 *)(s0 + 0x1A) = 0;
        *(s16 *)(s0 + 0x18) = 0;
        func_800CD96C(a0);
        D_800CE8D4 = *(u16 *)(*(s32 *)(s2 + 0x20) + 0x12);
        func_80146CA0((void *)a0);
    } else {
        ((void (*)(s32))func_800CD94C)(a0);
    }
}


extern s32 rand(void);
extern void func_800CD96C(s32 a0);

void func_800CD884(void *arg0) {
    s32 s0;
    u16 w;
    u16 t2;

    s0 = *(s32 *)((s32)arg0 + 0x20);
    if (*(s16 *)((s32)arg0 + 0x60) != 0) {
        w = *(u16 *)(s0 + 0x18) + 0x100;
        *(u16 *)(s0 + 0x18) = w;
        if ((s16)w > 0x1000) {
            if ((rand() & 1) != 0) {
                *(u16 *)(s0 + 0x18) = 0x1000;
            } else {
                *(u16 *)(s0 + 0x18) = 0x1333;
            }
        }
    } else {
        w = *(u16 *)(s0 + 0x18) - 0x100;
        *(u16 *)(s0 + 0x18) = w;
        if ((s16)w < 0) {
            *(u16 *)(s0 + 0x18) = 0;
        }
    }
    t2 = *(u16 *)(s0 + 0x18);
    *(u16 *)(s0 + 0x1C) = t2;
    *(u16 *)(s0 + 0x1A) = t2;
    *(u16 *)(s0 + 0x12) += 0x1C7;
    func_800CD96C((s32)arg0);
}


extern void func_80162CCC(void);
void func_800CD94C(void) {
    func_80162CCC();
}


void func_800CD96C(s32 param_1) {
    extern void func_80013F3C(void *a0);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_80048D9C(void *a0, void *a1);
    extern void func_80020F34(s32 a0, s32 a1);

    s32 work;
    s32 hdr;
    s32 model;

    work = *(s32 *)(param_1 + 0x4C);
    hdr = *(s32 *)(work + 0x20);
    model = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 6) = *(s32 *)(hdr + 0x48);
    *(s16 *)(param_1 + 0xA) = *(s32 *)(hdr + 0x4C) - 0x20;
    *(s16 *)(param_1 + 0xE) = *(s32 *)(hdr + 0x50);
    func_80013F3C((void *)(model + 0x34));
    RotMatrixY(*(s16 *)(model + 0x12), (void *)(model + 0x34));
    func_80048D9C((void *)(model + 0x34), (void *)(*(s32 *)(work + 0x20) + 0x34));
    func_80020F34(model + 0x34, model + 0x18);
    *(u16 *)(model + 0x2C) |= 1;
}


extern s32 func_8014C088(s32 a0, s32 a1);

void func_800CDA14(s32 a0) {
    s32 v1;

    v1 = func_8014C088(a0, 0x13);
    if (v1 != 0) {
        *(s16 *)(v1 + 0x60) = 1;
    }
}


void func_800CDA44(s32 *a0) {
    *(s16 *)((s32)a0 + 0x1C8) = 0;
}


extern s32 func_80161A30(s32 a0);
extern void (*D_800CE0AC[])(void);
extern void func_800CDBD4(void);

void func_800CDA4C(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CE0AC[*(u16 *)(param_1 + 2)]();
    if (func_80161A30(iVar1) == 0) {
        ((void (*)(s32))func_800CDBD4)(param_1);
    }
}


typedef struct { u32 a; u32 b; } U8x __attribute__((packed, aligned(1)));

extern s32 func_80146578(void);
extern void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_800CDBD4();
extern void func_800CDBF4();

extern u8 D_800CE068[];
extern u8 D_800CE08C[];

void func_800CDAB4(s32 *param_1) {
    s32 s0;
    s32 v0;

    s0 = func_80146578();
    *(s32 *)((s32)param_1 + 0x20) = s0;
    if (s0 != 0) {
        func_8001CC3C(s0, D_800CE068, 0x234, 0x1C0);
        *(u8 *)((s32)s0 + 0x27) = 0x26;
        *(u16 *)((s32)s0 + 0x1A) = 0x2000;
        *(u16 *)((s32)s0 + 0x18) = 0x2000;
        *(u32 *)((s32)s0 + 4) |= 0x8000000;
        v0 = *(s32 *)((s32)param_1 + 0x50) * 8;
        *(U8x *)((s32)param_1 + 0x60) = *(U8x *)(&D_800CE08C[v0]);
        func_80146E90(param_1, 0);
        ((void (*)(s32 *))func_800CDBF4)(param_1);
        func_80146CA0(param_1);
    } else {
        ((void (*)(s32 *))func_800CDBD4)(param_1);
    }
}


extern void func_800CDBF4();
extern void func_800CDCA8();
void func_800CDBA4(s32 a0) {
    func_800CDBF4();
    ((void (*)(s32))func_800CDCA8)(a0);
}


extern void func_80162CCC(void);
void func_800CDBD4(void) {
    func_80162CCC();
}


extern void func_80049CAC(s32 a0, s32 a1);
extern void ApplyMatrixSV(void *m0, void *m1, void *m2);
extern void func_80015954(s32 a0, s32 a1);
extern s16 D_800CE0B8[4];

void func_800CDBF4(s32 s0) {
    u16 sp10[3];
    u16 sp18[16];
    s32 *outer;
    s32 *inner;
    s32 t;

    outer = *(s32 **)(s0 + 0x4C);
    *(u16 *)(s0 + 0x62) = (*(u16 *)(s0 + 0x62) + *(u16 *)(s0 + 0x66)) & 0xFFF;
    func_80049CAC(s0 + 0x60, sp18);
    ApplyMatrixSV(sp18, D_800CE0B8, sp10);
    inner = *(s32 **)((s32)outer + 0x20);
    sp10[0] = sp10[0] + inner[18];
    t = sp10[1] - 0x20;
    sp10[1] = t + inner[19];
    sp10[2] = sp10[2] + inner[20];
    func_80015954(sp10, s0 + 4);
}


extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146E98(s32 a0);

void func_800CDCA8(void *arg0) {
    s16 *ptr = *(s16 **)((s32)arg0 + 0x20);
    s32 val;

    if (func_80146E98((s32)arg0) != 0) {
        if ((rand() & 0x1F) == 0) {
            func_80146E90((s32 *)arg0, (rand() & 0x1F) | 0x20);
        }
        val = *(u16 *)((s32)ptr + 0x12);
        val += 0x38;
    } else {
        val = *(u16 *)((s32)ptr + 0x12);
        val += 0x155;
    }
    *(u16 *)((s32)ptr + 0x12) = val & 0xFFF;
}


extern s32 func_80161A30(s32 a0);
extern void (*D_800CE0C0[])(void);
extern void func_800CDF64(void);

void func_800CDD34(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CE0C0[*(u16 *)(param_1 + 2)]();
    if (func_80161A30(iVar1) == 0) {
        ((void (*)(s32))func_800CDF64)(param_1);
    }
}


extern s32 func_80146578(void);
extern void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_8014ACC0(s32 a0, s32 a1);
extern void func_800CDF64(void);

void func_800CDD9C(s32 param_1) {
    extern u8 D_800CE068[];
    extern s16 D_800CE8D4;
    register s32 iVar1 __asm__("$18");
    register s32 iVar2 __asm__("$16");
    u16 d;
    u16 x;

    iVar1 = *(s32 *)(param_1 + 0x4C);
    iVar2 = func_80146578();
    *(s32 *)(param_1 + 0x20) = iVar2;
    if (iVar2 != 0) {
        func_8001CC3C(iVar2, D_800CE068, 0x200, 0x100);
        *(u8 *)(iVar2 + 0x27) = 8;
        *(u32 *)(iVar2 + 4) = *(u32 *)(iVar2 + 4) | 0x50000000;
        func_80149374(iVar1, param_1 + 4);
        d = D_800CE8D4;
        x = *(u16 *)(*(s32 *)(iVar1 + 0x20) + 0x10);
        *(u16 *)(iVar2 + 0x12) = d;
        *(u16 *)(iVar2 + 0x10) = x;
        *(u16 *)(iVar2 + 0x14) = *(u16 *)(*(s32 *)(iVar1 + 0x20) + 0x14);
        *(u16 *)(param_1 + 0x60) = *(u16 *)(iVar1 + 0x100);
        *(u16 *)(param_1 + 0x62) = *(u16 *)(iVar1 + 0x102);
        *(u16 *)(param_1 + 0x64) = *(u16 *)(iVar1 + 0x104);
        *(u16 *)(iVar2 + 0x1A) = 0x1000;
        *(u16 *)(iVar2 + 0x18) = 0x1000;
        func_80146DE8((s32 *)param_1, 0, 0, 0xFFE00000);
        func_80146E90((s32 *)param_1, 8);
        func_80146CA0((void *)param_1);
        func_8014ACC0(iVar1, 1);
    } else {
        ((void (*)(s32))func_800CDF64)(param_1);
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_800CDF84(s32, s32);
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80162FC0(void *a0);
extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328(void *a0);
extern s32 func_801632F0(void *a0);

void func_800CDEB4(void *arg0) {
    s32 *s1;
    u16 var;
    s32 sp18[8];

    s1 = *(s32 **)((u8 *)arg0 + 0x20);
    if (func_80146E98((s32)arg0) != 0) {
        func_80146CA0(arg0);
    } else {
        ((void (*)(void *, void *))func_800CDF84)(arg0, sp18);
        func_80163194((s32)arg0, 0, 0, 0, (s32)sp18);
        func_80162FC0(arg0);
        var = *(u16 *)((u8 *)s1 + 0x1A) + 0x100;
        *(u16 *)((u8 *)s1 + 0x1A) = var;
        *(u16 *)((u8 *)s1 + 0x18) = var;
        func_80163408((s32)arg0, 0x23, 0x80, 8);
        func_80163328(arg0);
        func_801632F0(arg0);
    }
}


extern void func_80162CCC(void);
void func_800CDF64(void) {
    func_80162CCC();
}


extern void func_80013F3C(s32 a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);

void func_800CDF84(s32 a0, s32 a1)
{
    s32 q;
    q = *(s32 *)(a0 + 0x20);
    func_80013F3C(a1);
    func_800126C4(a1, *(s16 *)(a0 + 0x60));
    func_800123F0(a1, *(s16 *)(a0 + 0x64));
    func_80012558(a1, *(s16 *)(a0 + 0x62));
    func_80012558(a1, *(s16 *)(q + 0x12));
    func_800126C4(a1, *(s16 *)(q + 0x10));
    func_800123F0(a1, *(s16 *)(q + 0x14));
}


INCLUDE_RODATA("asm/md_MAIN_046/nonmatchings/md_MAIN_046", D_800CCB1C);

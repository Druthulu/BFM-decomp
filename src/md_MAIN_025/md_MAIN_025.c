#include "common.h"

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CAE14);



void func_800CAE5C(void *a0) {

    extern void (*D_800CBE7C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBE7C[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAED8();
void func_800CAEA0(void *a0) {
    func_800CAED8(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


extern u8 D_800CBD2C[];
void func_800CAED8(u8 *a0) {
    func_80154274(a0, D_800CBD2C);
    func_800CBB70(a0);
    *(u8 *)(a0 + 0xBF) = 0;
    *(u8 *)(a0 + 0xBE) = 0;
    func_801655E4(a0);
    func_80146E90(a0, 0x12);
    *(u8 *)(a0 + 0x197) += 1;
}


void func_800CAF3C(void *a0) {
    extern s32 func_80146E98(s32 a0);
    if (func_80146E98((s32)a0) != 0) {
        *(u8 *)((s32)a0 + 0x197) += 1;
    }
}


extern u16 func_80148800(s32 *param_1);
extern void func_800CB028(s32 param_1);

void func_800CAF7C(s32 *param_1)
{
    u32 v0;
    u8 v1;

    if (func_80148800(param_1) & 0x20) {
        func_800CB028((s32)param_1);
    } else {
        v1 = *(u8 *)((s32)param_1 + 0xBF);
        switch (v1) {
        case 0:
            v0 = *(u8 *)((s32)param_1 + 0xBE) + 4;
            *(u8 *)((s32)param_1 + 0xBE) = v0;
            if ((v0 & 0xFF) >= 0x50) {
                *(u8 *)((s32)param_1 + 0xBF) = *(u8 *)((s32)param_1 + 0xBF) + 1;
            }
            break;
        case 1:
            if (*(u8 *)((s32)param_1 + 0xBE) == 0) {
                func_800CB028((s32)param_1);
            } else {
                *(u8 *)((s32)param_1 + 0xBE) -= 4;
            }
            break;
        }
    }
}


INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB028);

extern void func_801466F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
extern void func_80147324(s32 arg0);

void func_800CB068(void *a0) {
    u16 bits = *(u16 *)((s32)a0 + 0xB8);
    if (bits & 0x4000) {
        func_801466F0(10, (s32)a0, 0, 0, 0, *(u8 *)((s32)a0 + 0xBE), 0, 0);
        func_80147324(0x649);
    } else if (bits & 0x8000) {
        *(u8 *)((s32)a0 + 0x197) += 1;
    }
}


extern s32 D_8011F9D0[];

void func_800CB0E4(void *a0) {
    u16 *p = (u16 *)D_8011F9D0;
    u16 *end = (u16 *)(D_8011F9D0 + 0x208);

    if (p < end) {
        do {
            if (*p == 10) {
                return;
            }
            p += 0x34;
        } while (p < end);
    }
    *(u16 *)((s32)a0 + 0xB8) = *(u16 *)((s32)a0 + 0xBA);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


extern void func_801599A4(u8 *a0);
extern void func_80159B3C(void *a0);
void func_800CB138(u8 *a0) {
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
    }
}


extern void func_800CBBF8();
void func_800CB180(void) {
    func_800CBBF8();
}


INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB1A0);

void func_800CB23C(void *a0) {
    extern u8 D_800CBE98[];
    extern void func_8014659C(void);
    extern void func_8001CA1C(void *a0, void *a1);
    extern void func_80149374(s32 a0, s32 a1);
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
    extern void func_80146E90(s32 *a0, s16 a1);
    extern void func_80146CA0(void *a0);
    extern void func_800CB758(void *a0);
    extern void func_800CB6CC(void *a0);

    s32 s1;
    s32 v0;

    s1 = *(s32 *)((s32)a0 + 0x4C);
    v0 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 != 0) {
        func_8001CA1C((void *)v0, D_800CBE98);
        func_80149374(s1, (s32)a0 + 4);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = *(u16 *)(s1 + 0x100);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) = *(u16 *)(s1 + 0x104);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12);
        func_80146DE8((s32 *)a0, 0, 0x80000, 0xFFF00000);
        func_80146E90((s32 *)a0, 0x60);
        func_800CB758(a0);
        func_80146CA0(a0);
    } else {
        func_800CB6CC(a0);
    }
}


INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB300);

extern void func_8016634C(void *a0);
extern void func_80147364(u16 a0, s32 a1);
extern void func_80162CCC();

void func_800CB6CC(void *a0) {
    func_8016634C(a0);
    func_80147364(4, 0x649);
    func_80162CCC(a0);
}


#include "common.h"

extern s32 func_80146E98(s32 a0);
extern void func_80162CCC();

void func_800CB708(void *a0) {
    if (func_80146E98((s32)a0) != 0) {
        func_80162CCC(a0);
        return;
    }
    *(u16 *)((s32)a0 + 0xA) += 2;
}


INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB758);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB760);

s32 func_800CB7B0(s32 arg0) {
    s32 x;
    s32 t;
    s32 u;

    func_80015978(arg0 + 4, &x);
    if ((func_8012EFB8(&x, &x) & 0xFFFFEFFF) == 0) {
        t = *(s16 *) &x;
        if (t < 0) {
            t = -t;
        }
        if (t < 201) {
            u = *((s16 *) &x + 1);
            if (u >= 0) {
                if (u >= 161) {
                    goto epilogue;
                }
                return 0;
            } else {
                if (-u < 161) {
                    return 0;
                }
                goto epilogue;
            }
        } else {
            goto epilogue;
        }
    } else {
        goto epilogue;
    }
epilogue:
    return 1;
}


extern u8 D_80078EC1;
extern void (*D_800CBF2C[])();
extern void func_800CBBF8();

void func_800CB848(int param_1)
{
    if (D_80078EC1 != 15) {
        func_800CBBF8();
    } else {
        D_800CBF2C[*(u16 *)(param_1 + 2)]();
    }
}


void func_800CB8A4(void *a0) {
    extern void func_80146578(void);
    extern void func_8001CEC0(s32 a0, void *a1);
    extern void func_8001CB00(s32 a0, void *a1, s32 a2, s32 a3);
    extern void func_800CBB50(void *a0);
    extern u8 D_800CBECC[];
    extern u8 D_800CBF20[];

    s32 s0;
    void *s1;

    s1 = a0;
    *(s32 *)((s32)s1 + 0x20) = 0;
    *(s32 *)((s32)s1 + 0x4C) = 0;
    s0 = ((s32 (*)(void))func_80146578)();
    if (s0) {
        *(s32 *)((s32)s1 + 0x20) = s0;
        func_8001CEC0(s0, D_800CBECC);
        *(u16 *)(s0 + 0x2C) = 1;
        *(s32 *)(s0 + 4) |= 0x80000000;
        *(s16 *)((s32)s1 + 6) = -0x28;
        *(s16 *)((s32)s1 + 0xA) = -0x40;
        s0 = ((s32 (*)(void))func_80146578)();
        if (s0) {
            *(s32 *)((s32)s1 + 0x10) = s0;
            func_8001CB00(s0, D_800CBF20, 0x1A0, 0x170);
            func_800CBB50(s0);
            *(u16 *)(s0 + 0x18) = 0;
            func_80146E90(s1, 6);
            func_80146CA0(s1);
        }
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_8001CBDC(s32 a0, void *a1, s32 a2, s32 a3);
extern void func_800CBB50(void *a0);
extern void func_80146CA0(void *a0);

void func_800CB968(void *a0) {
    extern u8 D_800CBF20[];
    void *s0;
    void *s2;
    s32 v0;

    s2 = *(void **)((s32)a0 + 0x20);
    s0 = *(void **)((s32)a0 + 0x10);
    v0 = func_80146E98((s32)a0);
    if (v0 != 0) {
        if (s0 != 0) {
            func_8001CBDC((s32)s0, D_800CBF20, 0x1A0, 0x170);
            func_800CBB50(s0);
            *(s32 *)((s32)s2 + 4) &= 0x7FFFFFFF;
        }
        func_80146CA0(a0);
    } else {
        if (s0 != 0) {
            *(u16 *)((s32)s0 + 0x18) += 0x2AA;
        }
    }
}


extern u8 D_80126C16;
void func_800CBA14(void *a0) {
    *(u16 *)((s32)a0 + 6) = D_80126C16 - 0x28;
}


extern void func_80146E90(s32 *a0, s16 a1);
extern void func_80146CA0(void *a0);
void func_800CBA2C(s32 *a0) {
    func_80146E90(a0, 8);
    func_80146CA0(a0);
}


void func_800CBA60(void *a0) {
    extern s32 func_80146E98(s32 a0);
    extern void func_8001CB00(s32 a0, void *a1, s32 a2, s32 a3);
    extern void func_800CBB50(void *a0);
    extern void func_80146E90(s32 *a0, s16 a1);
    extern void func_80146CA0(void *a0);
    extern u8 D_800CBF20[];
    void *s2;
    void *s0;

    s2 = *(void **)((s32)a0 + 0x20);
    s0 = *(void **)((s32)a0 + 0x10);
    if (func_80146E98((s32)a0) != 0) {
        if (s0 != 0) {
            func_8001CB00((s32)s0, D_800CBF20, 0x1A0, 0x170);
            func_800CBB50(s0);
        }
        *(s32 *)((s32)s2 + 4) |= 0x80000000;
        func_80146E90((s32 *)a0, 4);
        func_80146CA0(a0);
    }
}


INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CBAF4);

void func_800CBB50(void *a0) {
    *(u8 *)((s32)a0 + 0x27) = 0x1A;
    *(s16 *)((s32)a0 + 0x2C) = 1;
    *(s16 *)((s32)a0 + 0x8) = 0;
    *(s16 *)((s32)a0 + 0xA) = -0x40;
}


extern void func_801466B4(u16 a0, s32 a1, s32 a2, s32 a3, s32 arg5);

void func_800CBB70(void *a0) {
    func_801466B4(0x27, a0, 0, 0, 0);
}


extern s32 func_8014C088(s32 a0, s32 a1);
extern void func_80146C98(s32 *a0, s16 a1);

void func_800CBBA0(s32 param_1) {
    s32 ret;
    ret = func_8014C088(param_1, 0x27);
    if (ret == 0) {
        return;
    }
    if (*(u16 *)(ret + 2) >= 2) {
        func_80146C98((s32 *)ret, 3);
    } else {
        func_800CBBF8();
    }
}


void func_800CBBF8(void) {
    extern s32 D_8011F9D0[];
    extern void func_80016714(s8 *a0, s32 a1);
    extern void func_80162CCC(void);
    u8 *p;

    for (p = (u8 *)&(*(s32 *)D_8011F9D0); p < (u8 *)&(*(s32 *)D_8011F9D0) + 0x820; p += 0x68) {
        if (*(u16 *)p == 0x27) {
            if (*(s32 *)(p + 0x10) != 0) {
                func_80016714(*(s8 **)(p + 0x10), 0x38);
            }
            ((void (*)(u8 *))func_80162CCC)(p);
        }
    }
}


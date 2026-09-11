#include "common.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_801F03C0;
typedef struct { u32 w[38]; } Blk152_8017DF40_801F1738;
typedef struct { u8 b[4]; } Blk4_8017DF40_801F1738;
typedef struct { u8 c[8]; } Blk8;
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801F1F94;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801F1F94;
extern void func_801EF750(void);
extern void func_801EF7DC(void);
extern s16 func_801EF7F0(void);
extern s32 func_801EF800(s32 a0, s32 a1);
extern u16 D_80115116;
extern unsigned short D_80115112;
extern void (*D_801F3468[])(void);
extern void func_80141C04(void);
extern void func_801EF878(void);
extern void func_801EFA44(void);
extern void func_801EFA60(void);
extern void func_801EFB40(void);
extern void func_800D2624(void);
extern void func_801EFB5C(void);
extern s32 func_80024054(u8 *, u8 *);
extern s32 func_800D2650(s32, u8 *, s16, s16, s32, s32);
extern s32 func_800D27DC(s32, s32, void *, s16, s32);
extern s32 func_800D29F8(s32, s32, void *, s16, s32);
extern s32 func_801F06B0(s32, s16, s16, s16, s32 *);
extern s32 func_801F03C0(s32 ot, u8 *s, s16 c);
extern u32 func_801F1440(s32 a0, s32 a1);
extern void func_801F14A8();
extern void func_80016714(void *a0, s32 a1);
extern s32 D_801F9AC4;
extern void func_801F1710(void);
extern void func_801F1738(s32 arg0);
extern void func_8014B00C(s32 arg0);
extern void func_80029344(void);
extern void func_801F1A24(void);
extern u8 D_801F34DC[];
void func_800167B8(int);
void func_80175414(s32 _arg0);
extern int func_801F1A4C(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801F1AA4(void);
extern s32 func_801F1B1C(s32 param_1);
extern void func_800D1EBC(void);
extern void func_801F1BAC(void);
extern void func_801F1BCC(void *a0);
extern s32 func_801F1C08(void *a0);
extern void func_801F1C74(void *a0);
extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
extern void func_801F1CB0(void);
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void *);
extern void func_801F1CD8(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_801F1D40(void *arg0);
extern void func_801F1D98(void);
extern void func_801F1DA0(void *a0);
extern void func_801F1DDC(void);
extern void func_801F1DFC(u32 arg0);
extern void func_801F1E64(void);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801F1F30(void *a0);
extern void func_801F1E6C(void);
extern void func_801F1F94(s32 param_1, s16 *param_2);
extern void func_801F1F6C(s32 param_1);
extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
/* ==== end §8b carried decl layer ==== */







extern s32 D_80126B10;
extern u8 D_801F35C4[];
extern u8 D_801F3630[];
extern u8 D_801F3648[];
extern s32 func_801789AC(u8 *a0);
extern void func_80178CBC(u8 *a0, u8 *a1);
extern s16 func_80188F10(void);
extern void func_80188F20(s32 a0);
extern void func_80174438(s32 a0);
extern void func_801EF6E4(void);
extern s16 func_801EF70C(void);

void func_801F218C(u8 *a0) {
    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        switch (func_801789AC(a0)) {
        case 2:
            func_80178CBC(a0, D_801F3630);
            *(u16 *)(a0 + 0x34) = 0;
            break;
        case 1:
            *(u16 *)(a0 + 0x34) = 2;
            func_80188F20(4);
            break;
        case 3:
            func_80178CBC(a0, D_801F3648);
            *(u16 *)(a0 + 0x34) = 3;
            break;
        }
        break;
    case 1:
        break;
    case 2:
        if (func_80188F10() != 0) {
            func_801EF6E4();
            *(u16 *)(a0 + 0x34) = 4;
        } else {
            func_80178CBC(a0, D_801F35C4);
            *(u16 *)(a0 + 0x34) = 0;
        }
        break;
    case 3:
        if (func_801789AC(a0) != 0) {
            func_80174438(D_80126B10);
            *(u16 *)(a0 + 0x34) = 1;
        }
        break;
    case 4:
        if (func_801EF70C() != 0) {
            *(u16 *)(a0 + 0x34) = 2;
            func_80188F20(4);
        }
        break;
    }
}




void func_801F22D8(void *a0) {

    extern void (*D_801F3678[])(void);
    D_801F3678[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801F2314(void) {
    extern s32 D_801F9DD0;
    D_801F9DD0 = 0;
}




void func_801F2324(void) {

    extern s32 D_801F9DD0;
    D_801F9DD0 = 1;
}




s32 func_801F2338(void) {

    extern s32 D_801F9DD0;
    return D_801F9DD0;
}


s32 func_801F2348(void) {
    extern s32 func_80029504(void);
    extern s32 func_80029178(s32);
    extern u8 D_801F375C[];
    extern u8 D_801F379C[];
    extern s32 D_801EF3EC;
    s32 x;
    s32 t;
    s32 p;
    s32 v;

    x = func_80029504();
    if ((u32)(x - 200) < 100) {
        t = 0;
    } else if (x < 300 || (func_80029178(250) & 0xFF) == 0) {
        t = 1;
    } else {
        t = 0;
    }
    if (t != 0) {
        p = D_801EF3EC;
        v = (s32)&D_801F375C;
    } else {
        p = D_801EF3EC;
        v = (s32)&D_801F379C;
    }
    *(s32 *)(p + 4) = v;
    return v;
}


s32 func_801F23D0(void) {
    extern s32 func_80029504(void);
    extern s32 func_80029178(s32);
    extern u8 D_801F3830[];
    extern u8 D_801F3864[];
    extern s32 D_801EF3EC;
    s32 x;
    s32 t;
    s32 p;
    s32 v;

    x = func_80029504();
    if ((u32)(x - 200) < 100) {
        t = 0;
    } else if (x < 300 || (func_80029178(250) & 0xFF) == 0) {
        t = 1;
    } else {
        t = 0;
    }
    if (t != 0) {
        p = D_801EF3EC;
        v = (s32)&D_801F3830;
    } else {
        p = D_801EF3EC;
        v = (s32)&D_801F3864;
    }
    *(s32 *)(p + 4) = v;
    return v;
}


extern s32 func_80029504(void);
extern s32 func_80029178(s32);
extern void func_80029124(s32, s32);

s32 func_801F2458(void) {
    s32 x;
    s32 t;

    x = func_80029504();
    if ((u32)(x - 200) < 100) {
        t = 0;
        goto join;
    }
    if (x < 300) {
        t = 1;
        goto join;
    }
    if (func_80029178(250) & 0xFF) {
        t = 0;
        goto join;
    }
    __asm__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
    t = 1;
join:
    if (t != 0 && (func_80029178(276) & 0xFF) == 0) {
        func_80029124(276, 1);
        return 1;
    }
    return 0;
}


void func_801F24DC(s32 a0) {
    extern s32 func_80029504(void);
    extern s32 func_80029178(s32 arg);
    extern s32 func_801877C0(void);
    extern s32 func_80187890(void);
    extern s32 func_80187904(void);
    extern void func_80187960(void);
    extern s32 D_801F35EC[];
    extern s32 D_801F3600[];
    extern s32 D_801F361C[];
    extern s32 D_801F3D68;
    extern s32 D_801F3DB4;

    s32 v1 = func_80029504();
    if (v1 < 0x258) {
        s32 flag;
        v1 = func_80029504();
        if ((u32)(v1 - 0xC8) >= 0x64U) {
            if (v1 < 0x12C || (func_80029178(0xFA) & 0xFF) == 0) {
                flag = 1;
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
        if (flag) {
            *(s32 *)(a0 + 0xE4) = D_801F35EC[func_801877C0()];
        } else {
            if (func_80029504() < 0x12CU) {
                *(s32 *)(a0 + 0xE4) = (s32)&D_801F3D68;
            } else {
                *(s32 *)(a0 + 0xE4) = (s32)&D_801F3DB4;
            }
        }
    } else if (v1 < 0x384) {
        *(s32 *)(a0 + 0xE4) = D_801F3600[func_80187890()];
    } else {
        *(s32 *)(a0 + 0xE4) = D_801F361C[func_80187904()];
        func_80187960();
    }
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801F25F8(void *a0) {
    extern s32 D_801F968C;
    extern s32 D_801C3790;
    extern s32 D_801F3534;
    extern s32 D_801F3564;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F968C);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801C3790);
        func_8012E8E0((s32)a0, (s32)&D_801F3534);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801F3564);
    }
}


extern void func_801F28B0(void);
extern s32 func_80029504(void);
extern s32 func_801F2850(s32, s32, s32);
extern void func_801F2868(s32, s32, s32);
extern void func_801F28E0(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_801F2930(void);
extern void func_801F2970(void);

s32 *func_801F2690(void) {
    extern u8 D_80078EB1;
    extern u8 D_80078E78[];
    extern u32 D_801F3BDC;
    extern u32 D_801F3D00;
    extern s32 D_801F9DD4;
    extern s32 D_801F9F54;
    s32 v;
    u8 *p;

    p = D_80078E78;
    func_801F28B0();
    v = func_80029504();

    if (v >= 0xC8) {
        if (v < 0x258) {
            if (func_801F2850(D_80078EB1, 0xD, 0x18)) {
                if ((u32)(v - 0x136) < 0x46) {
                    func_801F2868(0xA, (s32)&D_801F3BDC, (s32)func_801F2930);
                    func_80029124(0x112, 1);
                } else {
                    func_801F2868(0xA, 0, 0);
                }
            } else {
                func_801F2868(0xA, 0, 0);
            }
            if (func_801F2850(p[0x39], 0xD, 0x18)) {
                if ((u32)(v - 0x136) < 0x46) {
                    func_801F2868(0xB, (s32)&D_801F3D00, (s32)func_801F2970);
                } else {
                    func_801F2868(0xB, 0, 0);
                }
            } else {
                func_801F2868(0xB, 0, 0);
            }
        } else {
            func_801F2868(0xA, 0, 0);
            func_801F2868(0xB, 0, 0);
        }
    } else {
        func_801F2868(0xA, 0, 0);
        func_801F2868(0xB, 0, 0);
    }
    func_801F28E0();
    if (D_801F9F54 == 0) {
        return 0;
    }
    return &D_801F9DD4;
}


extern s32 *func_801F2690(void);
extern s32 D_801F9F54;
extern s32 D_801F9DDC[];
extern s32 D_801F9DD8[];

s32 func_801F27CC(s32 a0) {
    s32 s0 = a0;
    s32 v0;
    s32 v1;
    ((s32 (*)(void))func_801F2690)();
    v0 = D_801F9F54;
    if (v0 > 0) {
        v1 = 0;
        a0 = v0 << 4;
        do {
            if (*(s32 *)((s32)&D_801F9DDC + v1) == s0) {
                v0 = *(s32 *)((s32)&D_801F9DD8 + v1);
                goto end;
            }
            v1 += 0x10;
        } while (v1 < a0);
    }
    v0 = 0;
end:
    return v0;
}


s32 func_801F2850(s32 a0, s32 a1, s32 a2) {
    return (a0 >= a1) && (a0 < a2);
}


void func_801F2868(s32 arg0, s32 arg1, s32 arg2) {

    extern s32 D_801F9F54;
    extern s32 D_801F9DDC[];
    extern s32 D_801F9DD8[];
    extern s32 D_801F9DE0[];
    s32 i;

    i = D_801F9F54;
    D_801F9DDC[i * 4] = arg0;
    D_801F9DD8[i * 4] = arg1;
    D_801F9DE0[i * 4] = arg2;
    D_801F9F54 = i + 1;
}


extern void func_80016714(void *a0, s32 a1);
extern s32 D_801F9DD4;
extern s32 D_801F9F54;

void func_801F28B0(void) {
    func_80016714(&D_801F9DD4, 0x180);
    D_801F9F54 = 0;
}


void func_801F28E0(void)
{
    typedef struct { s32 next; u8 pad[0xC]; } Node_801F28E0;
    extern s32 D_801F9DD4;
    extern s32 D_801F9F54;
    Node_801F28E0 *p;
    s32 i;

    p = (Node_801F28E0 *)&D_801F9DD4;
    for (i = 0; i < D_801F9F54 - 1; ) {
        p->next = (s32)(p + 1);
        i++;
        p = p + 1;
    }
}


extern s32 func_80029504(void);
extern void func_80029514(s32 arg0);
extern void func_80029124(s32 a0, s32 a1);

void func_801F2930(void) {
    func_80029124(0xFD, 0x1);
    if (((s32 (*)(void))func_80029504)() == 0x136) {
        ((void (*)(s32))func_80029514)(0x140);
    }
}


extern s32 func_80029504(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

void func_801F2970(void) {
    func_80029124(0xFE, 0x1);
    if (((s32 (*)(void))func_80029504)() == 0x136) {
        ((void (*)(s32))func_80029514)(0x140);
    }
}



u8 func_801F29B0(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0x16;
}




extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_801F29E0(void) {

    extern u8 D_800AF040[];
    func_8001ABBC(0, 0, D_800AF040, 0, 0);
}



#include "common.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_801E3540;
typedef struct { u32 w[38]; } Blk152_8017DF40_801E48B8;
typedef struct { u8 b[4]; } Blk4_8017DF40_801E48B8;
typedef struct { u8 c[8]; } Blk8;
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801E5124;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801E5124;
extern s32 func_801E288C(void);
extern s32 func_80029504(void);
extern void func_801E2980(s32 arg0, s32 arg1);
extern void func_801E28D0(void);
extern void func_801E295C(void);
extern s16 func_801E2970(void);
extern u16 D_80115116;
extern unsigned short D_80115112;
extern void (*D_801E65D0[])(void);
extern void func_80141C04(void);
extern void func_801E29F8(void);
extern void func_801E2BC4(void);
extern void func_801E2BE0(void);
extern void func_801E2CC0(void);
extern void func_800D2624(void);
extern void func_801E2CDC(void);
extern s32 func_80024054(u8 *, u8 *);
extern s32 func_800D2650(s32, u8 *, s16, s16, s32, s32);
extern s32 func_800D27DC(s32, s32, void *, s16, s32);
extern s32 func_800D29F8(s32, s32, void *, s16, s32);
extern s32 func_801E3830(s32, s16, s16, s16, s32 *);
extern s32 func_801E3540(s32 ot, u8 *s, s16 c);
extern u32 func_801E45C0(s32 a0, s32 a1);
extern void func_801E4890(void);
extern void func_801E48B8(s32 arg0);
extern void func_8014B00C(s32 arg0);
extern void func_80029344(void);
extern void func_801E4BA4(void);
extern u8 *D_80126B10;
extern u8 D_801E6644[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);
extern int func_801E4BCC(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801E4C24(void);
extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);
extern s32 func_801E4C9C(s32 param_1);
extern void func_800D1EBC(void);
extern void func_801E4D3C(void);
extern void func_801E4D5C(void *a0);
extern s32 func_801E4D98(void *a0);
extern void func_801E4E04(void *a0);
extern void func_80171A1C(void*);
extern void func_801E4E40(void);
extern s32 func_80171D78(u32, void *);
extern void func_801E4E68(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);
extern void func_801E4ED0(void *arg0);
extern void func_801E4F28(void);
extern void func_801E4F30(void *a0);
extern void func_801E4F6C(void *a0);
extern void func_801E4F8C(u32 arg0);
extern void func_801E4FF4(void);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E50C0(void *a0);
extern void func_801E4FFC(void);
extern void func_801E5124(s32 param_1, s16 *param_2);
extern void func_801E50FC(s32 param_1);
extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_801E531C(void);
extern void func_8001ABBC(u32, u32, void *, u32, u32);
extern void func_801E5324(void);
/* ==== end §8b carried decl layer ==== */







extern u8 *D_80126B10;
extern u8 D_801E672C[];
extern u8 D_801E6798[];
extern u8 D_801E67B0[];
extern s32 func_801789AC(u8 *a0);
extern void func_80178CBC(u8 *a0, u8 *a1);
extern s16 func_80185B78(void);
extern void func_80185B88(s32 a0);
extern void func_80174438(s32 a0);
extern void func_801E2864(void);
extern s32 func_801E288C(void);

void func_801E5358(u8 *a0) {
    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        switch (func_801789AC(a0)) {
        case 2:
            func_80178CBC(a0, D_801E6798);
            *(u16 *)(a0 + 0x34) = 0;
            break;
        case 1:
            *(u16 *)(a0 + 0x34) = 2;
            func_80185B88(4);
            break;
        case 3:
            func_80178CBC(a0, D_801E67B0);
            *(u16 *)(a0 + 0x34) = 3;
            break;
        }
        break;
    case 1:
        break;
    case 2:
        if (func_80185B78() != 0) {
            func_801E2864();
            *(u16 *)(a0 + 0x34) = 4;
        } else {
            func_80178CBC(a0, D_801E672C);
            *(u16 *)(a0 + 0x34) = 0;
        }
        break;
    case 3:
        if (func_801789AC(a0) != 0) {
            func_80174438((*(s32 *)&D_80126B10));
            *(u16 *)(a0 + 0x34) = 1;
        }
        break;
    case 4:
        if (((s16 (*)(void))func_801E288C)() != 0) {
            *(u16 *)(a0 + 0x34) = 2;
            func_80185B88(4);
        }
        break;
    }
}




void func_801E54A4(void *a0) {

    extern void (*D_801E67E0[])(void);
    D_801E67E0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

void func_801E54E0(void) {
    extern s32 D_801EAC6C;
    D_801EAC6C = 0;
}




void func_801E54F0(void) {

    extern s32 D_801EAC6C;
    D_801EAC6C = 1;
}




s32 func_801E5504(void) {

    extern s32 D_801EAC6C;
    return D_801EAC6C;
}


s32 func_801E5514(void) {
    extern s32 func_80029504(void);
    extern s32 func_80029178(s32);
    extern u8 D_801E67E8[];
    extern u8 D_801E6828[];
    extern s32 D_801E256C;
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
        p = D_801E256C;
        v = (s32)&D_801E67E8;
    } else {
        p = D_801E256C;
        v = (s32)&D_801E6828;
    }
    *(s32 *)(p + 4) = v;
    return v;
}


extern s32 func_80029504(void);
extern s32 func_80029178(s32);

void func_801E559C(void) {
    extern s32 D_801E256C;
    extern u8 D_801E68BC[];
    extern u8 D_801E68F0[];

    s32 t;
    s32 flag;

    t = func_80029504();
    if ((u32)(t - 200) < 100u) {
        flag = 0;
    } else if (t < 300 || (func_80029178(250) & 0xFF) == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag) {
        *(s32 *)(*(s32 *)&D_801E256C + 4) = (s32)D_801E68BC;
    } else {
        *(s32 *)(*(s32 *)&D_801E256C + 4) = (s32)D_801E68F0;
    }
}


#include "common.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) =================== */






extern s32 func_801E288C(void);
extern s32 func_80029504(void);
extern void func_801E2980(s32 arg0, s32 arg1);
extern void func_801E28D0(void);
extern void func_801E295C(void);
extern s16 func_801E2970(void);
extern u16 D_80115116;
extern unsigned short D_80115112;
extern void (*D_801E65D0[])(void);
extern void func_80141C04(void);
extern void func_801E29F8(void);
extern void func_801E2BC4(void);
extern void func_801E2BE0(void);
extern void func_801E2CC0(void);
extern void func_800D2624(void);
extern void func_801E2CDC(void);
extern s32 func_80024054(u8 *, u8 *);
extern s32 func_800D2650(s32, u8 *, s16, s16, s32, s32);
extern s32 func_800D27DC(s32, s32, void *, s16, s32);
extern s32 func_800D29F8(s32, s32, void *, s16, s32);
extern s32 func_801E3830(s32, s16, s16, s16, s32 *);
extern s32 func_801E3540(s32 ot, u8 *s, s16 c);
extern u32 func_801E45C0(s32 a0, s32 a1);
extern void func_801E4890(void);
extern void func_801E48B8(s32 arg0);
extern void func_8014B00C(s32 arg0);
extern void func_80029344(void);
extern void func_801E4BA4(void);
extern u8 *D_80126B10;
extern u8 D_801E6644[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);
extern int func_801E4BCC(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801E4C24(void);
extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);
extern s32 func_801E4C9C(s32 param_1);
extern void func_800D1EBC(void);
extern void func_801E4D3C(void);
extern void func_801E4D5C(void *a0);
extern s32 func_801E4D98(void *a0);
extern void func_801E4E04(void *a0);
extern void func_80171A1C(void*);
extern void func_801E4E40(void);
extern s32 func_80171D78(u32, void *);
extern void func_801E4E68(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);
extern void func_801E4ED0(void *arg0);
extern void func_801E4F28(void);
extern void func_801E4F30(void *a0);
extern void func_801E4F6C(void *a0);
extern void func_801E4F8C(u32 arg0);
extern void func_801E4FF4(void);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E50C0(void *a0);
extern void func_801E4FFC(void);
extern void func_801E5124(s32 param_1, s16 *param_2);
extern void func_801E50FC(s32 param_1);
extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_801E531C(void);
extern void func_8001ABBC(u32, u32, void *, u32, u32);
extern void func_801E5324(void);

extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);

s32 func_801E5624(void) {
    s32 v1 = func_80029504();
    s32 flag;

    if ((u32)(v1 - 0xC8) >= 0x64U) {
        if (v1 < 0x12C || (func_80029178(0xFA) & 0xFF) == 0) {
            flag = 1;
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }

    if (flag != 0) {
        if ((func_80029178(0x114) & 0xFF) == 0) {
            func_80029124(0x114, 1);
            return 1;
        }
    }
    return 0;
}


extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern s32 func_80184428(void);
extern s32 func_801844F8(void);
extern s32 func_8018456C(void);
extern void func_801845C8(void);

void func_801E56A8(s32 a0) {
    extern s32 D_801E6754[];
    extern s32 D_801E6768[];
    extern s32 D_801E6784[];
    extern s32 D_801E6DF4;
    extern s32 D_801E6E40;

    s32 flag;

    s32 v1 = func_80029504();

    if (v1 < 0x258) {
        s32 u = func_80029504();

        if ((u32)(u - 0xC8) >= 0x64) {
            if (u >= 0x12C) {
                if (func_80029178(0xFA) & 0xFF) {
                    goto zero;
                }
            } else {
                goto one;
            }
        } else {
            goto zero;
        }
        flag = 1;
        goto eval;
    zero:
        flag = 0;
        goto eval;
    one:
        flag = 1;
    eval:
        if (flag != 0) {
            s32 v0 = func_80184428();
            *(s32 *)(a0 + 0xE4) = D_801E6754[v0];
        } else {
            s32 w = func_80029504();
            if ((u32)w < 0x12C) {
                *(s32 *)(a0 + 0xE4) = (s32)&D_801E6DF4;
            } else {
                *(s32 *)(a0 + 0xE4) = (s32)&D_801E6E40;
            }
        }
    } else if (v1 < 0x384) {
        s32 v0 = func_801844F8();
        *(s32 *)(a0 + 0xE4) = D_801E6768[v0];
    } else {
        s32 v0 = func_8018456C();
        *(s32 *)(a0 + 0xE4) = D_801E6784[v0];
        func_801845C8();
    }
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801E57C4(void *a0) {
    extern s32 D_801CEA24;
    extern s32 D_801BEAF8;
    extern s32 D_801E669C;
    extern s32 D_801E66CC;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801CEA24);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801BEAF8);
        func_8012E8E0((s32)a0, (s32)&D_801E669C);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801E66CC);
    }
}


void *func_801E585C(void) {
    typedef struct { s32 x, y, z; } SV4;
    extern u8 D_80078EB1;
    extern u8 D_80078E78[];
    extern u32 D_801E6C68;
    extern u32 D_801E6D8C;
    extern s32 D_801EADF0;
    extern void func_801E5A7C(void);
    extern s32 func_80029504(void);
    extern s32 func_801E5A1C(s32, s32, s32);
    extern void func_801E5A34(s32, s32, s32);
    extern void func_80029124(s32 a0, s32 a1);
    extern void func_801E5AAC(void);
    extern void func_801E5AFC(void);
    extern void func_801E5B3C(s32 a0);
    extern SV4 D_801EAC70;
    s32 v;
    u8 *p;

    p = D_80078E78;
    func_801E5A7C();
    v = func_80029504();

    if (v >= 0xC8) {
        if (v < 0x258) {
            if (func_801E5A1C(D_80078EB1, 0xD, 0x18)) {
                if ((u32)(v - 0x136) < 0x46) {
                    func_801E5A34(0xA, (s32)&D_801E6C68, (s32)func_801E5AFC);
                    func_80029124(0x112, 1);
                } else {
                    func_801E5A34(0xA, 0, 0);
                }
            } else {
                func_801E5A34(0xA, 0, 0);
            }
            if (func_801E5A1C(p[0x39], 0xD, 0x18)) {
                if ((u32)(v - 0x136) < 0x46) {
                    func_801E5A34(0xB, (s32)&D_801E6D8C, (s32)func_801E5B3C);
                } else {
                    func_801E5A34(0xB, 0, 0);
                }
            } else {
                func_801E5A34(0xB, 0, 0);
            }
        } else {
            func_801E5A34(0xA, 0, 0);
            func_801E5A34(0xB, 0, 0);
        }
    } else {
        func_801E5A34(0xA, 0, 0);
        func_801E5A34(0xB, 0, 0);
    }
    func_801E5AAC();
    if (D_801EADF0 == 0) {
        return 0;
    }
    return &D_801EAC70;
}


s32 func_801E5998(s32 a0) {
    extern s32 D_801EADF0;
    extern s32 D_801EAC78;
    extern s32 D_801EAC74;
    s32 s0;
    s32 v0;
    s32 v1;
    s32 limit;
    func_801E585C();
    s0 = a0;
    v0 = D_801EADF0;
    if (v0 > 0) {
        v1 = 0;
        limit = v0 * 16;
        do {
            if (*(s32 *)((s32)&D_801EAC78 + v1) == s0) {
                return *(s32 *)((s32)&D_801EAC74 + v1);
            }
            v1 += 16;
        } while (v1 < limit);
    }
    return 0;
}


s32 func_801E5A1C(s32 a0, s32 a1, s32 a2) {
    return (a0 >= a1) && (a0 < a2);
}


void func_801E5A34(s32 a0, s32 a1, s32 a2) {
    extern s32 D_801EADF0;
    extern s32 D_801EAC74[][4];
    extern s32 D_801EAC78[][4];
    extern s32 D_801EAC7C[][4];
    s32 n = D_801EADF0;
    D_801EAC78[n][0] = a0;
    D_801EAC74[n][0] = a1;
    D_801EAC7C[n][0] = a2;
    D_801EADF0 = n + 1;
}


extern s32 D_801EAC70;
extern s32 D_801EADF0;
extern void func_80016714(void *a0, s32 a1);

void func_801E5A7C(void) {
    func_80016714(&D_801EAC70, 0x180);
    D_801EADF0 = 0;
}


void func_801E5AAC(void)
{
    typedef struct { s32 next; u8 pad[0xC]; } Node_801E5AAC;
    extern s32 D_801EAC70;
    extern s32 D_801EADF0;
    Node_801E5AAC *p;
    s32 i;

    p = (Node_801E5AAC *)&D_801EAC70;
    for (i = 0; i < D_801EADF0 - 1; ) {
        p->next = (s32)(p + 1);
        i++;
        p = p + 1;
    }
}


extern s32 func_80029504(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

void func_801E5AFC(void) {
    func_80029124(0xFD, 0x1);
    if (((s32 (*)(void))func_80029504)() == 0x136) {
        ((void (*)(s32))func_80029514)(0x140);
    }
}


extern s32 func_80029504(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

void func_801E5B3C(void) {
    func_80029124(0xFE, 0x1);
    if (((s32 (*)(void))func_80029504)() == 0x136) {
        ((void (*)(s32))func_80029514)(0x140);
    }
}



#include "common.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_801EE8E0;
typedef struct { u32 w[38]; } Blk152_8017DF40_801EFC58;
typedef struct { u8 b[4]; } Blk4_8017DF40_801EFC58;
typedef struct { u8 c[8]; } Blk8;
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801F04DC;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801F04DC;
extern void func_801EDC04(void);
extern s32 func_801EDC2C(void);
extern s32 func_80029504(void);
extern void func_801EDD20(s32 a0, s32 a1);
extern void func_801EDC70(void);
extern void func_801EDCFC(void);
extern s16 func_801EDD10(void);
extern u16 D_80115116;
extern unsigned short D_80115112;
extern void (*D_801F19C0[])(void);
extern void func_80141C04(void);
extern void func_801EDD98(void);
extern s32 D_801F82F8;
extern u8 D_801F8308[];
extern void (*D_801F8010)();
extern s16 D_801F800C;
extern s16 D_801F8018;
extern s16 D_80115118;
extern s16 D_8011512C;
extern s32 D_801F1838;
extern s32 D_80115130;
extern s32 D_80115134;
extern s32 D_801F18E4[];
extern s16 D_80115126;
extern u8 D_80115138[];
extern s32 D_801F17A0;
extern void func_801EDE38(void);
extern void func_801EDF64(void);
extern void func_801EDF80(void);
extern void func_801EE060(void);
extern void func_800D2624(void);
extern void func_801EE07C(void);
extern s32 func_80024054(u8 *, u8 *);
extern s32 func_800D2650(s32, u8 *, s16, s16, s32, s32);
extern s32 func_800D27DC(s32, s32, void *, s16, s32);
extern s32 func_800D29F8(s32, s32, void *, s16, s32);
extern s32 func_801EEBD0(s32, s16, s16, s16, s32 *);
extern s32 func_801EE8E0(s32 ot, u8 *s, s16 c);
extern s32 func_801EEBD0(s32 a0, s16 a1, s16 a2, s16 a3, s32 *out);
extern u32 func_801EF960(s32 a0, s32 a1);
extern void func_801EF9C8();
extern void func_801EFC30(void);
extern void func_801EFC58(s32 arg0);
extern void func_8014B00C(void);
extern void func_80029344(void);
extern void func_801EFF44(void);
extern u8 *D_80126B10;
extern u8 D_801F1A34[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);
extern int func_801EFF6C(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801EFFC4(void);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_800D0C48(s32);
extern s32 func_800D1E28(void);
extern s32 func_801F003C(s32 param_1);
extern void func_800D1EBC(void);
extern void func_801F00F4(void);
extern void func_801F0114(void *a0);
extern s32 func_801F0150(u8 *a0);
extern void func_801F01BC(void *a0);
extern void func_80171A1C(void*);
extern void func_801F01F8(void);
extern s32 func_80171D78(u32, void *);
extern void func_801F0220(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);
extern void func_801F0288(void *arg0);
extern void func_801F02E0(void);
extern void func_801F02E8(void *a0);
extern void func_801F0324(void);
extern void func_801F0344(u32 arg0);
extern void func_801F03AC(void);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801F0478(void *a0);
extern void func_801F03B4(void);
extern void func_801F04B4(s32 param_1);
extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_801F04DC(s32 param_1, s16 *param_2);
extern void func_8001ABBC(u32, u32, void *, u32, u32);
extern void func_801F0714(void);
/* ==== end §8b carried decl layer ==== */


void func_801F0748(void *param_1) {

    extern s32 func_801789AC(s32 a0);
    extern void func_80178CBC(s32 a0, s32 a1);
    extern void func_801EDC04(void);
    extern s32 func_80186150(void);
    extern void func_80186160(s32 a0);
    extern void func_80174438(s32 a0);
    extern u8 *D_80126B10;

    extern s32 D_801F1B88;
    extern s32 D_801F1BA0;
    extern s32 D_801F1B1C;

    switch (*(u16 *)((s32)param_1 + 0x34)) {
    case 0: {
        s32 v0 = func_801789AC((s32)param_1);
        switch (v0) {
        case 1:
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80186160(4);
            break;
        case 2:
            func_80178CBC((s32)param_1, (s32)&D_801F1B88);
            *(u16 *)((s32)param_1 + 0x34) = 0;
            break;
        case 3:
            func_80178CBC((s32)param_1, (s32)&D_801F1BA0);
            *(u16 *)((s32)param_1 + 0x34) = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2:
        if ((func_80186150() << 16) != 0) {
            func_801EDC04();
            *(u16 *)((s32)param_1 + 0x34) = 4;
        } else {
            func_80178CBC((s32)param_1, (s32)&D_801F1B1C);
            *(u16 *)((s32)param_1 + 0x34) = 0;
        }
        break;
    case 3:
        if (func_801789AC((s32)param_1) != 0) {
            func_80174438((s32)D_80126B10);
            *(u16 *)((s32)param_1 + 0x34) = 1;
        }
        break;
    case 4:
        if ((func_801EDC2C() << 16) != 0) {
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80186160(4);
        }
        break;
    }
}




void func_801F0894(void *a0) {

    extern void (*D_801F1BD0[])(void);
    D_801F1BD0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_026/nonmatchings/md_SC05_026_jr_801F0748", func_801F08D0);



void func_801F08E0(void) {

    extern s32 D_801F8328;
    D_801F8328 = 1;
}




s32 func_801F08F4(void) {

    extern s32 D_801F8328;
    return D_801F8328;
}


void func_801F0904(void) {

    extern s32 func_80029504(void);
    extern s32 func_80029178(s32);
    extern s32 D_801ED90C;
    extern u8 D_801F1BD8[];
    extern u8 D_801F1C18[];

    s32 r;
    s32 f;

    r = func_80029504();

    if ((u32)(r - 0xC8) < 0x64U) {
        f = 0;
    } else if (r < 0x12C || (func_80029178(0xFA) & 0xFF) == 0) {
        f = 1;
    } else {
        f = 0;
    }

    if (f != 0) {
        *(s32 *)(D_801ED90C + 4) = (s32)D_801F1BD8;
    } else {
        *(s32 *)(D_801ED90C + 4) = (s32)D_801F1C18;
    }
}


extern s32 func_80029504(void);
extern s32 func_80029178(s32);

void func_801F098C(void) {
    extern s32 D_801ED90C;
    extern u8 D_801F1CAC[];
    extern u8 D_801F1CE0[];
    s32 r;
    s32 f;

    r = func_80029504();

    if ((u32)(r - 0xC8) < 0x64) {
        f = 0;
    } else if (r >= 0x12C) {
        if ((func_80029178(0xFA) & 0xFF) != 0) {
            goto isCAC;
        }
        f = 1;
    } else {
        f = 1;
    }
    goto join;
isCAC:
    f = 0;
join:
    if (f != 0) {
        *(s32 *)(D_801ED90C + 4) = (s32)D_801F1CAC;
    } else {
        *(s32 *)(D_801ED90C + 4) = (s32)D_801F1CE0;
    }
}


extern s32 func_80029178(s32);
extern s32 func_80029504(void);
extern void func_80029124(s32 a0, s32 a1);

s32 func_801F0A14() {
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
extern s32 func_80184A00(void);
extern s32 func_80184AD0(void);
extern s32 func_80184B44(void);
extern void func_80184BA0(void);

void func_801F0A98(s32 a0) {
    extern s32 D_801F1B44[];
    extern s32 D_801F1B58[];
    extern s32 D_801F1B74[];
    extern s32 D_801F21E4;
    extern s32 D_801F2230;

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
            *(s32 *)(a0 + 0xE4) = D_801F1B44[func_80184A00()];
        } else {
            if (func_80029504() < 0x12CU) {
                *(s32 *)(a0 + 0xE4) = (s32)&D_801F21E4;
            } else {
                *(s32 *)(a0 + 0xE4) = (s32)&D_801F2230;
            }
        }
    } else if (v1 < 0x384) {
        *(s32 *)(a0 + 0xE4) = D_801F1B58[func_80184AD0()];
    } else {
        *(s32 *)(a0 + 0xE4) = D_801F1B74[func_80184B44()];
        func_80184BA0();
    }
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801F0BB4(void *a0) {
    extern s32 D_801F7BE4;
    extern s32 D_801B9A0C;
    extern s32 D_801F1A8C;
    extern s32 D_801F1ABC;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F7BE4);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801B9A0C);
        func_8012E8E0((s32)a0, (s32)&D_801F1A8C);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801F1ABC);
    }
}


extern void func_801F0E6C(void);
extern s32 func_80029504(void);
extern void func_80029124(s32, s32);
extern s32 func_801F0E0C(s32, s32, s32);
extern void func_801F0E24(s32, s32, s32);
extern void func_801F0EEC(void);
extern void func_801F0F2C(void);
extern void func_801F0E9C(void);

void func_801F0C4C(void) {
    extern u8 D_80078EB1;
    extern u8 D_80078E78[];
    extern u8 D_801F2058[];
    extern u8 D_801F217C[];
    extern s32 D_801F84AC;
    extern s32 D_801F832C;
    register u8 *p __asm__("$17");
    register s32 v __asm__("$16");
    register s32 t2 __asm__("$2");
    register s32 flg __asm__("$3");
    register s32 *res __asm__("$2");

    func_801F0E6C();
    p = D_80078E78;
    v = func_80029504();

    if (v < 200) goto Lzero;
    if (v >= 600) goto Lzero;

    if (func_801F0E0C(D_80078EB1, 13, 24)) {
        t2 = (u32)(v - 310) < 70;
        if (t2) {
            func_801F0E24(10, (s32)D_801F2058, (s32)func_801F0EEC);
            func_80029124(274, 1);
        } else {
            func_801F0E24(10, 0, 0);
        }
    } else {
        func_801F0E24(10, 0, 0);
    }

    if (func_801F0E0C(p[57], 13, 24)) {
        t2 = (u32)(v - 310) < 70;
        if (t2) {
            func_801F0E24(11, (s32)D_801F217C, (s32)func_801F0F2C);
            goto Lcont;
        }
    }
    goto Lshared;

Lzero:
    func_801F0E24(10, 0, 0);

Lshared:
    func_801F0E24(11, 0, 0);

Lcont:
    func_801F0E9C();

    res = 0;
    flg = D_801F84AC;
    if (flg != 0) {
        res = (s32 *)&D_801F832C;
    }
    __asm__ __volatile__("" : : "r"(res));
}


extern void func_801F0C4C();
extern s32 D_801F84AC;
extern s32 D_801F8334[][4];
extern s32 D_801F8330[][4];

s32 func_801F0D88(s32 a0) {
    s32 s0;
    s32 cnt;
    s32 off;
    s0 = a0;
    func_801F0C4C();
    cnt = D_801F84AC;
    if (cnt > 0) {
        off = 0;
        do {
            if (*(s32 *)((s32)((s32 *)D_801F8334) + off) == s0) {
                return *(s32 *)((s32)((s32 *)D_801F8330) + off);
            }
            off += 16;
        } while (off < cnt * 16);
    }
    return 0;
}


s32 func_801F0E0C(s32 a0, s32 a1, s32 a2) {
    return (a0 >= a1) && (a0 < a2);
}


extern s32 D_801F8330[][4];
extern s32 D_801F8334[][4];
extern s32 D_801F8338[][4];
extern s32 D_801F84AC;

void func_801F0E24(s32 arg0, s32 arg1, s32 arg2) {
    D_801F8334[D_801F84AC][0] = arg0;
    D_801F8330[D_801F84AC][0] = arg1;
    D_801F8338[D_801F84AC][0] = arg2;
    D_801F84AC++;
}


extern s32 D_801F832C;
extern s32 D_801F84AC;
extern void func_80016714(void *a0, s32 a1);

void func_801F0E6C(void) {
    func_80016714(&D_801F832C, 0x180);
    D_801F84AC = 0;
}


extern s32 D_801F832C;
extern s32 D_801F84AC;

void func_801F0E9C(void) {
    typedef struct { s32 next; u8 pad[0xC]; } Node_801F0E9C;
    Node_801F0E9C *p;
    s32 i;

    p = (Node_801F0E9C *)&D_801F832C;
    for (i = 0; i < D_801F84AC - 1; ) {
        p->next = (s32)(p + 1);
        i++;
        p = p + 1;
    }
}


extern s32 func_80029504(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

void func_801F0EEC(void) {
    func_80029124(0xFD, 0x1);
    if (((s32 (*)(void))func_80029504)() == 0x136) {
        ((void (*)(s32))func_80029514)(0x140);
    }
}


extern s32 func_80029504(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

void func_801F0F2C(void) {
    func_80029124(0xFE, 0x1);
    if (((s32 (*)(void))func_80029504)() == 0x136) {
        ((void (*)(s32))func_80029514)(0x140);
    }
}



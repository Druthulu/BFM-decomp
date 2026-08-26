#include "common.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_801E8A80;
typedef struct { u32 w[38]; } Blk152_8017DF40_801E9DF8;
typedef struct { u8 b[4]; } Blk4_8017DF40_801E9DF8;
typedef struct { u8 c[8]; } Blk8;
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801EA664;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801EA664;
extern void func_801E7DA4(void);
extern s32 func_801E7DCC(void);
extern s32 func_80029504(void);
extern void func_801E7E10(void);
extern void func_801E7E9C(void);
extern s16 func_801E7EB0(void);
extern void func_801E7EC0(s32 a0, s32 a1);
extern u16 D_80115116;
extern unsigned short D_80115112;
extern void (*D_801EBB38[])(void);
extern void func_80141C04(void);
extern void func_801E7F38(void);
extern void func_801E7FD8(void);
extern void func_801E8104(void);
extern s32 D_801151D0;
extern u8 D_801151C8[];
extern u8 D_800B9A15;
extern s16 D_80115126;
extern s16 D_800B9A02;
extern s16 D_801F2184;
extern s16 D_801F2188;
extern s32 D_801F2470;
extern s32 D_801F2474;
extern u8 D_801F2478[];
extern s32 D_801F2488;
extern s32 func_8002B0B4(s32, s32, void *);
extern void func_801E8DF4(void);
extern void func_801E915C(void);
extern s32 func_801E8274(void);
extern void func_801E88D0(void);
extern void func_801E8120(void);
extern void func_801E8200(void);
extern void func_800D2624(void);
extern void func_801E821C(void);
extern s32 func_80024054(u8 *, u8 *);
extern s32 func_800D2650(s32, u8 *, s16, s16, s32, s32);
extern s32 func_800D27DC(s32, s32, void *, s16, s32);
extern s32 func_800D29F8(s32, s32, void *, s16, s32);
extern s32 func_801E8D70(s32, s16, s16, s16, s32 *);
extern s32 func_801E8A80(s32 ot, u8 *s, s16 c);
extern u8 D_80115158[];
extern s32 func_801E8D70(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s32 *arg4);
extern u32 func_801E9B00(s32 a0, s32 a1);
extern void func_801E9B68(unsigned int val, short n, unsigned short *dst, short flag);
extern void func_80016714(s8 *a0, s32 a1);
extern s8 D_801F2194;
extern void func_801E9DD0(void);
extern void func_801E9DF8(s32 arg0);
extern void func_8014B00C(void);
extern void func_80029344(void);
extern void func_801EA0E4(void);
extern u8 D_801EBBAC[];
void func_800167B8(int);
void func_80175414(s32 _arg0);
extern int func_801EA10C(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801EA164(void);
extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);
extern s32 func_801EA1DC(s32 param_1);
extern void func_800D1EBC(void);
extern void func_801EA27C(void);
extern void func_801EA29C(void *a0);
extern s32 func_801EA2D8(void *a0);
extern void func_801EA344(void *a0);
extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
extern void func_801EA380(void);
extern s32 func_80171D78(u32, void *);
extern void func_801EA3A8(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);
extern void func_801EA410(void *arg0);
extern void func_801EA468(void);
extern void func_801EA470(void *a0);
extern void func_801EA4AC(void);
extern void func_801EA4CC(u32 arg0);
extern void func_801EA534(void);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801EA600(void *a0);
extern void func_801EA53C(void);
extern void func_801EA63C(s32 arg0);
extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_801EA664(s32 param_1, s16 *param_2);
extern u8 func_801EA85C(u32 a0);
extern void func_8001ABBC(u32, u32, void *, u32, u32);
extern void func_801EA88C(void);
/* ==== end §8b carried decl layer ==== */


#include "common.h"

extern s32 func_801789AC(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);
extern u8 *D_80126B10;
extern s16 func_80186450(void);
extern void func_80186460(s32 a0);

void func_801EA8C0(void *param_1) {

    extern s32 D_801EBD00;
    extern s32 D_801EBD18;
    extern s32 D_801EBC94;

    switch (*(u16 *)((s32)param_1 + 0x34)) {
    case 0: {
        s32 v0 = func_801789AC((s32)param_1);
        switch (v0) {
        case 1:
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80186460(4);
            break;
        case 2:
            func_80178CBC((s32)param_1, (s32)&D_801EBD00);
            *(u16 *)((s32)param_1 + 0x34) = 0;
            break;
        case 3:
            func_80178CBC((s32)param_1, (s32)&D_801EBD18);
            *(u16 *)((s32)param_1 + 0x34) = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2:
        if (func_80186450() != 0) {
            func_801E7DA4();
            *(u16 *)((s32)param_1 + 0x34) = 4;
        } else {
            func_80178CBC((s32)param_1, (s32)&D_801EBC94);
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
        if ((func_801E7DCC() << 16) != 0) {
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80186460(4);
        }
        break;
    }
}




void func_801EAA0C(void *a0) {

    extern void (*D_801EBD48[])(void);
    D_801EBD48[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027_jr_801EA8C0", func_801EAA48);



void func_801EAA58(void) {

    extern s32 D_801F24A0;
    D_801F24A0 = 1;
}




s32 func_801EAA6C(void) {

    extern s32 D_801F24A0;
    return D_801F24A0;
}


s32 func_801EAA7C(void) {
    extern s32 func_80029504(void);
    extern s32 func_80029178(s32);
    extern u8 D_801EBD50[];
    extern u8 D_801EBD90[];
    extern s32 D_801E7AAC;
    s32 x;
    s32 t;
    s32 p;
    s32 v;

    x = func_80029504();
    if ((u32)(x - 200) < 100) {
        t = 0;
        goto join;
    }
    __asm__("");
    if (x < 300) {
        t = 1;
        goto join;
    }
    __asm__("");
    if (func_80029178(250) & 0xFF) {
        t = 0;
        goto join;
    }
    __asm__("");
    t = 1;
join:
    if (t != 0) {
        p = D_801E7AAC;
        v = (s32)&D_801EBD50;
    } else {
        p = D_801E7AAC;
        v = (s32)&D_801EBD90;
    }
    *(s32 *)(p + 4) = v;
    return v;
}


void func_801EAB04(void) {
    extern s32 D_801E7AAC;
    extern s32 D_801EBE24;
    extern s32 D_801EBE58;
    s32 r;
    s32 v;

    r = func_80029504();
    v = ((u32)(r - 0xC8) < 0x64) ? 0 :
        ((r < 0x12C) ? 1 :
         (((func_80029178(0xFA) & 0xFF) == 0) ? ({ __asm__ __volatile__("" ::: "memory"); 1; }) : 0));
    if (v) {
        *(s32 *)(D_801E7AAC + 4) = (s32)&D_801EBE24;
    } else {
        *(s32 *)(D_801E7AAC + 4) = (s32)&D_801EBE58;
    }
}


extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32, s32);

s32 func_801EAB8C(void) {
    s32 val = func_80029504();
    s32 flag;

    if ((u32)(val - 200) >= 100) {
        if (val < 300 || !(func_80029178(250) & 0xFF)) {
            flag = 1;
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }

    if (flag == 0) {
        return 0;
    }
    if (func_80029178(276) & 0xFF) {
        return 0;
    }
    func_80029124(276, 1);
    return 1;
}


extern s32 func_80029504(void);
extern s32 func_80029178(s32);
extern s32 func_80184D00(void);
extern s32 func_80184DD0(void);
extern s32 func_80184E44(void);
extern void func_80184EA0(void);
extern s32 D_801EBCBC[];
extern s32 D_801EBCD0[];
extern s32 D_801EBCEC[];
extern s32 D_801EC35C;
extern s32 D_801EC3A8;

void func_801EAC10(s32 a0) {
    s32 v0, v1 = func_80029504();
    if (v1 < 0x258) {
        v1 = func_80029504();
        if ((u32)(v1 - 0xC8) < 0x64) {
            v0 = 0;
        } else if (v1 < 0x12C) {
            v0 = 1;
        } else {
            v0 = func_80029178(0xFA) & 0xFF;
            if (v0 != 0) {
                v0 = 0;
            } else {
                v0 = 1;
            }
        }
        if (v0 != 0) {
            *(s32 *)(a0 + 0xE4) = D_801EBCBC[func_80184D00()];
        } else if ((u32)func_80029504() < 0x12C) {
            *(s32 *)(a0 + 0xE4) = (s32)&D_801EC35C;
        } else {
            *(s32 *)(a0 + 0xE4) = (s32)&D_801EC3A8;
        }
    } else if (v1 < 0x384) {
        *(s32 *)(a0 + 0xE4) = D_801EBCD0[func_80184DD0()];
    } else {
        *(s32 *)(a0 + 0xE4) = D_801EBCEC[func_80184E44()];
        func_80184EA0();
    }
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801EAD2C(void *a0) {
    extern s32 D_801F1D5C;
    extern s32 D_801B9A50;
    extern s32 D_801EBC04;
    extern s32 D_801EBC34;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F1D5C);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801B9A50);
        func_8012E8E0((s32)a0, (s32)&D_801EBC04);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801EBC34);
    }
}


extern void func_801EAFE4(void);
extern s32 func_80029504(void);
extern s32 func_801EAF84(s32, s32, s32);
extern void func_801EAF9C(s32, s32, s32);
extern void func_80029124(s32, s32);
extern void func_801EB064(void);
extern void func_801EB0A4(void);
extern void func_801EB014(void);

s32 func_801EADC4(void) {

    extern u8 D_80078EB1;
    extern u8 D_80078E78[];
    extern u8 D_801EC1D0[];
    extern u8 D_801EC2F4[];
    extern s32 D_801F2624;
    extern s32 D_801F24A4;

    u8 *p;
    s32 var;

    func_801EAFE4();
    p = D_80078E78;
    var = func_80029504();

    if (var < 200)
        goto L;
    if (var >= 600)
        goto L;

    if (func_801EAF84(D_80078EB1, 13, 24) && (u32)(var - 0x136) < 0x46) {
        ((void (*)(s32, void *, void *))func_801EAF9C)(10, D_801EC1D0, func_801EB064);
        func_80029124(0x112, 1);
    } else {
        ((void (*)(s32, void *, void *))func_801EAF9C)(10, 0, 0);
    }

    if (func_801EAF84(p[0x39], 13, 24) && (u32)(var - 0x136) < 0x46) {
        ((void (*)(s32, void *, void *))func_801EAF9C)(11, D_801EC2F4, func_801EB0A4);
    } else {
        ((void (*)(s32, void *, void *))func_801EAF9C)(11, 0, 0);
    }
    goto M;

L:
    ((void (*)(s32, void *, void *))func_801EAF9C)(10, 0, 0);
    ((void (*)(s32, void *, void *))func_801EAF9C)(11, 0, 0);

M:
    func_801EB014();
    if (!D_801F2624) {
        return 0;
    }
    return (s32)((u8 *)&D_801F24A4);
}


extern s32 D_801F24AC[];
extern s32 D_801F24A8[];
extern s32 D_801F2624;
extern s32 func_801EADC4();

s32 func_801EAF00(void *a0) {
    s32 n;
    s32 i;
    s32 end;

    func_801EADC4();
    n = D_801F2624;
    if (n > 0) {
        i = 0;
        end = n * 16;
        do {
            if (*(s32 *)((char *)D_801F24AC + i) == (s32)a0) {
                return *(s32 *)((char *)D_801F24A8 + i);
            }
            i += 16;
        } while (i < end);
    }
    return 0;
}


s32 func_801EAF84(s32 arg0, s32 arg1, s32 arg2) {
    return (arg1 <= arg0) && (arg0 < arg2);
}


void func_801EAF9C(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 D_801F2624;
    extern s32 D_801F24AC[];
    extern s32 D_801F24A8[];
    extern s32 D_801F24B0[];
    s32 i;

    i = D_801F2624;
    D_801F24AC[i * 4] = arg0;
    D_801F24A8[i * 4] = arg1;
    D_801F24B0[i * 4] = arg2;
    D_801F2624 = i + 1;
}


extern s32 D_801F24A4;
extern s32 D_801F2624;
extern void func_80016714(s8*, s32);

void func_801EAFE4(void) {
    ((void (*)(void *, s32))func_80016714)(&D_801F24A4, 0x180);
    D_801F2624 = 0;
}


void func_801EB014(void) {
    extern s32 D_801F2624;
    extern u32 D_801F24A4;
    s32 n;
    s32 i;
    u32 *p;
    u32 *next;
    p = &D_801F24A4;
    n = D_801F2624 - 1;
    for (i = 0; i < n; i++) {
        next = p + 4;
        *p = (u32)next;
        p = next;
    }
}


extern s32 func_80029504(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

void func_801EB064(void) {
    func_80029124(0xFD, 0x1);
    if (((s32 (*)(void))func_80029504)() == 0x136) {
        ((void (*)(s32))func_80029514)(0x140);
    }
}


extern s32 func_80029504(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

void func_801EB0A4(void) {
    func_80029124(0xFE, 0x1);
    if (((s32 (*)(void))func_80029504)() == 0x136) {
        ((void (*)(s32))func_80029514)(0x140);
    }
}



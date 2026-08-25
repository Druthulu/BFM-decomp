#include "common.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct { u8 c[8]; } Blk8;
typedef struct { short vx, vy, vz, pad; } SVECTOR;
typedef struct { short m[3][3]; long t[3]; } MATRIX;
extern u8 *D_80126B10;
extern u8 D_801EE620[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);
extern int func_801ED9B0(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801EDA08(void);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EDCF4(void *arg0);
extern s32 func_801EDA2C(s32 param_1);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029504(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_800D0C48(s32);
extern s32 func_800D1E28(void);
extern s32 func_801EDA78(s32 param_1);
extern void func_800D1EBC(void);
extern void func_801EDB30(void);
extern void func_801EDB50(void *a0);
extern void func_801EDB8C(void *a0);
extern void func_801EDBC8(void *a0);
extern void func_80171A1C(void*);
extern void func_801EDC04(void);
extern s32 func_80171D78(u32, void *);
extern void func_801EDC2C(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);
extern void func_801EDC94(void *arg0);
extern void func_801EDCEC(void);
extern void func_801EDCF4(void *a0);
extern void func_801EDD30(void);
extern void func_801EDD50(u32 arg0);
extern void func_801EDDB8(void);
extern void func_801EDE84(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_801EDEE8(s32 param_1, s16 *param_2);
extern u8 func_801EE080();
/* ==== end §8b carried decl layer ==== */


extern s32 func_801789AC(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);
extern s32 func_80186150(void);
extern void func_80186160(s32 a0);
extern u8 *D_80126B10;

void func_801EE0C0(void *param_1) {

    extern s32 D_801EE75C;
    extern s32 D_801EE774;
    extern s32 D_801EE6F8;
    extern s32 D_801EE970[];

    switch (*(u16 *)((s32)param_1 + 0x34)) {
    case 0: {
        s32 v0 = func_801789AC((s32)param_1);
        switch (v0) {
        case 1:
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80186160(2);
            break;
        case 2:
            func_80178CBC((s32)param_1, (s32)&D_801EE75C);
            *(u16 *)((s32)param_1 + 0x34) = 0;
            break;
        case 3:
            func_80178CBC((s32)param_1, (s32)&D_801EE774);
            *(u16 *)((s32)param_1 + 0x34) = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2: {
        s16 v0 = func_80186150();
        if (v0 != 0) {
            func_80178CBC((s32)param_1, D_801EE970[v0]);
            *(u16 *)((s32)param_1 + 0x34) = 4;
        } else {
            func_80178CBC((s32)param_1, (s32)&D_801EE6F8);
            *(u16 *)((s32)param_1 + 0x34) = 0;
        }
        break;
    }
    case 3:
        if (func_801789AC((s32)param_1) != 0) {
            func_80174438((s32)D_80126B10);
            *(u16 *)((s32)param_1 + 0x34) = 1;
        }
        break;
    case 4:
        if (func_801789AC((s32)param_1) != 0) {
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80186160(2);
        }
        break;
    }
}




void func_801EE21C(void *a0) {

    extern void (*D_801EE988[])(void);
    D_801EE988[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027_jr_801EE0C0", func_801EE258);



void func_801EE268(void) {

    extern s32 D_801F599C;
    D_801F599C = 1;
}




s32 func_801EE27C(void) {

    extern s32 D_801F599C;
    return D_801F599C;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EE28C(void) {
        if ((func_80029178(0x111) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x111, 1);
            return 1;
        }
        return 0;
    }


extern s32 func_80029504(void);
extern s32 func_80184AD0(void);
extern s32 func_80184B44(void);
extern void func_80184BA0(void);

void func_801EE2C8(s32 a0) {

    extern s32 D_801EE718[];
    extern s32 D_801EE72C[];
    extern s32 D_801EE748[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        extern s32 D_801F5994;
        s32 t = D_801F5994;
        s32 idx;

        if (t < 0x14) {
            idx = 0;
        } else if (t < 0x46) {
            idx = 1;
        } else if (t < 0x64) {
            idx = 2;
        } else if (t < 0x82) {
            idx = 3;
        } else {
            idx = 4;
        }
        *(s32 *)(a0 + 0xE4) = D_801EE718[idx];
    } else if (v1 < 0x384) {
        s32 v0 = func_80184AD0();
        *(s32 *)(a0 + 0xE4) = D_801EE72C[v0];
    } else {
        s32 v0 = func_80184B44();
        *(s32 *)(a0 + 0xE4) = D_801EE748[v0];
        func_80184BA0();
    }
}


extern void func_80029514(int);
void func_801EE3A4(void) {
    func_80029514(0x181);
}


extern void func_8018CDB0(void);
void func_801EE3C4(void) {
    func_8018CDB0();
}


void func_801EE3E4(void) {
    extern s16 D_801ED838;
    extern s16 D_801ED90C;
    extern u8 D_801EE878[];
    extern u8 D_801EE8B0[];
    extern u8 D_801EE8E4[];

    switch (D_801ED838) {
    case 0:
        *(s32 *)(*(s32 *)&D_801ED90C + 4) = (s32)D_801EE878;
        break;
    case 1:
        *(s32 *)(*(s32 *)&D_801ED90C + 4) = (s32)D_801EE8B0;
        break;
    case 2:
        *(s32 *)(*(s32 *)&D_801ED90C + 4) = (s32)D_801EE8E4;
        break;
    }
}


extern s32 D_801ED90C;
extern s32 D_801ED83C;

void func_801EE470(void) {
    *(s32 *)(D_801ED90C + 4) = D_801ED83C;
}


void func_801EE488(void) {
    extern s32 D_801ED90C;
    extern s32 D_801ED844;
    extern s32 D_801ED840;
    extern s32 D_801EE8E0;

    *(s32 *)(D_801ED90C + 4) = D_801ED844;
    D_801EE8E0 = D_801ED840;
}


void func_801EE4B8(void) {
    extern s32 D_801ED90C;
    extern s16 D_801ED838;
    extern u8 D_801EE878[];
    extern u8 D_801EE898[];

    func_8018CDB0();
    if (D_801ED838 == 0) {
        *(s32 *)(D_801ED90C + 4) = (s32)D_801EE878;
    } else {
        *(s32 *)(D_801ED90C + 4) = (s32)D_801EE898;
    }
}


extern s32 D_801BA404;
extern s32 D_801EE670;
extern s32 D_801EE6A0;
extern s32 D_801F5964;
extern s32 D_801F5994;
extern s32 D_801F5998;
extern s32 func_80029504(void);
extern s32 func_8012C1B8(void);
extern void func_8001C214(s32, s32);
extern void func_8012A828(s32, s32);
extern void func_8012CAE4(void *);
extern void func_8012E8E0(s32, s32);
extern void func_80178B18(s32, s32);

void func_801EE514(void *a0) {
    extern s32 D_801F5964;
    extern s32 D_801BA404;
    extern s32 D_801EE670;
    extern s32 D_801EE6A0;
    extern s32 D_801F5998;
    extern s32 D_801F5994;
    s32 v0;
    s32 ptr;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F5964);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s32 *)&D_801F5998 = 0;
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801BA404);
        func_8012E8E0((s32)a0, (s32)&D_801EE670);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801EE6A0);
        v0 = func_80029504();
        *(s32 *)&D_801F5994 = v0;
    }
}



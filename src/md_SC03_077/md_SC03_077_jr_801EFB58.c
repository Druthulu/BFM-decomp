#include "common.h"

#include "common.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct { u8 c[8]; } Blk8;
typedef struct { short vx, vy, vz, pad; } SVECTOR;
typedef struct { short m[3][3]; long t[3]; } MATRIX;
extern u8 D_801F00E8[];
void func_800167B8(int);
void func_80175414(s32 _arg0);
extern int func_801EF490(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801EF4E8(void);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EF7CC(void *arg0);
extern s32 func_801EF50C(s32 param_1);
extern void func_800D1EBC(void);
extern void func_801EF608(void);
extern void func_801EF628(void *a0);
extern void func_801EF664(void *a0);
extern void func_801EF6A0(void *a0);
extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
extern void func_801EF6DC(void);
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void *);
extern void func_801EF704(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_801EF76C(void *arg0);
extern void func_801EF7C4(void);
extern void func_801EF7CC(void *a0);
extern void func_801EF808(void);
extern void func_801EF828(u32 arg0);
extern void func_801EF890(void);
extern void func_801EF95C(void *a0);
extern void func_801EF9C0(s32 param_1, s16 *param_2);
extern void func_801EF998(s32 param_1);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
/* ==== end §8b carried decl layer ==== */


extern s32 func_801789AC(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);
extern s32 func_80188F10(void);
extern void func_80188F20(s32 a0);

void func_801EFB58(void *param_1) {

    extern s32 D_801F0224;
    extern s32 D_801F023C;
    extern s32 D_801F0438[];
    extern s16 D_801F01C0;
    extern u8 *D_80126B10;

    switch (*(u16 *)((s32)param_1 + 0x34)) {
    case 0: {
        s32 v0 = func_801789AC((s32)param_1);
        switch (v0) {
        case 1:
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80188F20(2);
            break;
        case 2:
            func_80178CBC((s32)param_1, (s32)&D_801F0224);
            *(u16 *)((s32)param_1 + 0x34) = 0;
            break;
        case 3:
            func_80178CBC((s32)param_1, (s32)&D_801F023C);
            *(u16 *)((s32)param_1 + 0x34) = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2: {
        s32 v0 = (s16)func_80188F10();
        if (v0 != 0) {
            func_80178CBC((s32)param_1, (s32)D_801F0438[v0]);
            *(u16 *)((s32)param_1 + 0x34) = 4;
        } else {
            func_80178CBC((s32)param_1, (s32)&D_801F01C0);
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
            func_80188F20(2);
        }
        break;
    }
}




void func_801EFCB4(void *a0) {

    extern void (*D_801F0450[])(void);
    D_801F0450[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801EFCF0(void) {
    extern s32 D_801F7464;
    D_801F7464 = 0;
}




void func_801EFD00(void) {

    extern s32 D_801F7464;
    D_801F7464 = 1;
}




s32 func_801EFD14(void) {

    extern s32 D_801F7464;
    return D_801F7464;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EFD24(void) {
        if ((func_80029178(0x111) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x111, 1);
            return 1;
        }
        return 0;
    }


extern s32 func_80029504(void);
extern s32 func_80187890(void);
extern s32 func_80187904(void);
extern void func_80187960(void);

void func_801EFD60(s32 a0) {

    extern s32 D_801F01E0[];
    extern s32 D_801F01F4[];
    extern s32 D_801F0210[];
    extern s32 D_801F745C;

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0;
        if (D_801F745C < 0x14) {
            v0 = 0;
        } else if (D_801F745C < 0x46) {
            v0 = 1;
        } else if (D_801F745C < 0x64) {
            v0 = 2;
        } else if (D_801F745C < 0x82) {
            v0 = 3;
        } else {
            v0 = 4;
        }
        *(s32 *)(a0 + 0xE4) = D_801F01E0[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_80187890();
        *(s32 *)(a0 + 0xE4) = D_801F01F4[v0];
    } else {
        s32 v0 = func_80187904();
        *(s32 *)(a0 + 0xE4) = D_801F0210[v0];
        func_80187960();
    }
}


extern void func_80029514(int);
void func_801EFE3C(void) {
    func_80029514(0x181);
}


extern void func_8018D0E4(void);
void func_801EFE5C(void) {
    func_8018D0E4();
}


void func_801EFE7C(void) {
    extern s16 D_801EF318;
    extern s32 D_801EF3EC;
    extern u8 D_801F0340[];
    extern u8 D_801F0378[];
    extern u8 D_801F03AC[];

    switch (D_801EF318) {
    case 0:
        *(s32 *)(*(s32 *)&D_801EF3EC + 4) = (s32)D_801F0340;
        break;
    case 1:
        *(s32 *)(*(s32 *)&D_801EF3EC + 4) = (s32)D_801F0378;
        break;
    case 2:
        *(s32 *)(*(s32 *)&D_801EF3EC + 4) = (s32)D_801F03AC;
        break;
    }
}


void func_801EFF08(void) {
    extern s32 D_801EF3EC;
    extern s32 D_801EF31C;
    *(s32 *)(D_801EF3EC + 4) = D_801EF31C;
}


void func_801EFF20(void) {
    extern s32 D_801EF3EC;
    extern s32 D_801EF324;
    extern s32 D_801EF320;
    extern s32 D_801F03A8;

    *(s32 *)(D_801EF3EC + 4) = D_801EF324;
    D_801F03A8 = D_801EF320;
}


void func_801EFF50(void) {
    extern s32 D_801EF3EC;
    extern s16 D_801EF318;
    extern u8 D_801F0340[];
    extern u8 D_801F0360[];
    s32 p;
    s32 v;

    func_8018D0E4();
    if (D_801EF318 == 0) {
        p = D_801EF3EC;
        v = (s32)&D_801F0340;
    } else {
        p = D_801EF3EC;
        v = (s32)&D_801F0360;
    }
    *(s32 *)(p + 4) = v;
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *);
extern void func_8001C214(s32, s32);
extern void func_8012A828(s32, s32);
extern void func_8012E8E0(s32, s32);
extern void func_80178B18(s32, s32);
extern s32 func_80029504(void);

void func_801EFFAC(void *a0) {
    extern s32 D_801F742C;
    extern s32 D_801C4188;
    extern s32 D_801F0138;
    extern s32 D_801F0168;
    extern s32 D_801F7460;
    extern s32 D_801F745C;
    s32 v0;
    s32 ptr;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F742C);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s32 *)&D_801F7460 = 0;
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801C4188);
        func_8012E8E0((s32)a0, (s32)&D_801F0138);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801F0168);
        v0 = func_80029504();
        *(s32 *)&D_801F745C = v0;
    }
}



u8 func_801F005C(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xD;
}



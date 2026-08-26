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
extern u8 D_801E8798[];
void func_800167B8(int);
void func_80175414(s32 _arg0);
extern int func_801E7B50(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801E7BA8(void);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E7E7C(void *arg0);
extern s32 func_801E7BCC(s32 param_1);
extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);
extern s32 func_801E7C18(s32 param_1);
extern void func_800D1EBC(void);
extern void func_801E7CB8(void);
extern void func_801E7CD8(void *a0);
extern void func_801E7D14(void *a0);
extern void func_801E7D50(void *a0);
extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
extern void func_801E7D8C(void);
extern s32 func_80171D78(u32, void *);
extern void func_801E7DB4(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);
extern void func_801E7E1C(void *arg0);
extern void func_801E7E74(void);
extern void func_801E7E7C(void *a0);
extern void func_801E7EB8(void);
extern void func_801E7ED8(u32 arg0);
extern void func_801E7F40(void);
extern void func_801E800C(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_801E8070(s32 param_1, s16 *param_2);
extern u8 func_801E8208(u32 a0);
/* ==== end §8b carried decl layer ==== */


void func_801E8238(void *arg0) {

    extern s32 func_801789AC(s32 a0);
    extern void func_80178CBC(s32 a0, s32 a1);
    extern void func_80174438(s32 a0);
    extern void func_80186460(s32 a0);
    extern s16 func_80186450(void);
    extern u8 *D_80126B10;
    extern s32 D_801E88D4;
    extern s32 D_801E88EC;
    extern s32 D_801E8870;
    extern s32 D_801E8AE8[];

    switch (*(u16 *)((s32)arg0 + 0x34)) {
    case 0: {
        s32 v1 = func_801789AC((s32)arg0);
        switch (v1) {
        case 1:
            *(u16 *)((s32)arg0 + 0x34) = 2;
            func_80186460(2);
            break;
        case 2:
            func_80178CBC((s32)arg0, (s32)&D_801E88D4);
            *(u16 *)((s32)arg0 + 0x34) = 0;
            break;
        case 3:
            func_80178CBC((s32)arg0, (s32)&D_801E88EC);
            *(u16 *)((s32)arg0 + 0x34) = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2: {
        s16 v0 = func_80186450();
        if (v0 != 0) {
            func_80178CBC((s32)arg0, (s32)D_801E8AE8[v0]);
            *(u16 *)((s32)arg0 + 0x34) = 4;
        } else {
            func_80178CBC((s32)arg0, (s32)&D_801E8870);
            *(u16 *)((s32)arg0 + 0x34) = 0;
        }
        break;
    }
    case 3:
        if (func_801789AC((s32)arg0) != 0) {
            func_80174438((s32)D_80126B10);
            *(u16 *)((s32)arg0 + 0x34) = 1;
        }
        break;
    case 4:
        if (func_801789AC((s32)arg0) != 0) {
            *(u16 *)((s32)arg0 + 0x34) = 2;
            func_80186460(2);
        }
        break;
    }
}




void func_801E8394(void *a0) {

    extern void (*D_801E8B00[])(void);
    D_801E8B00[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801E83D0(void) {

    extern s32 D_801EFB14;
    D_801EFB14 = 0;
}




void func_801E83E0(void) {

    extern s32 D_801EFB14;
    D_801EFB14 = 1;
}




s32 func_801E83F4(void) {

    extern s32 D_801EFB14;
    return D_801EFB14;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E8404(void) {
        if ((func_80029178(0x111) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x111, 1);
            return 1;
        }
        return 0;
    }


void func_801E8440(s32 a0) {

    extern s32 D_801E8890[];
    extern s32 D_801E88A4[];
    extern s32 D_801E88C0[];
    extern s32 D_801EFB0C;
    extern s32 func_80184DD0(void);
    extern s32 func_80184E44(void);
    extern void func_80184EA0(void);

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 idx;

        if (D_801EFB0C < 20) {
            idx = 0;
        } else if (D_801EFB0C < 70) {
            idx = 1;
        } else if (D_801EFB0C < 100) {
            idx = 2;
        } else if (D_801EFB0C < 130) {
            idx = 3;
        } else {
            idx = 4;
        }
        *(s32 *)(a0 + 0xE4) = D_801E8890[idx];
    } else if (v1 < 0x384) {
        *(s32 *)(a0 + 0xE4) = D_801E88A4[func_80184DD0()];
    } else {
        *(s32 *)(a0 + 0xE4) = D_801E88C0[func_80184E44()];
        func_80184EA0();
    }
}


extern void func_80029514(int);
void func_801E851C(void) {
    func_80029514(0x181);
}


extern void func_8018CDEC(void);
void func_801E853C(void) {
    func_8018CDEC();
}


void func_801E855C(void) {
    extern s32 D_801E7AAC;
    extern s32 D_801E79D8;
    extern s32 D_801E89F0;
    extern s32 D_801E8A28;
    extern s32 D_801E8A5C;

    switch (*(s16 *)&D_801E79D8) {
    case 0:
        *(s32 *)(D_801E7AAC + 4) = (s32)&D_801E89F0;
        break;
    case 1:
        *(s32 *)(D_801E7AAC + 4) = (s32)&D_801E8A28;
        break;
    case 2:
        *(s32 *)(D_801E7AAC + 4) = (s32)&D_801E8A5C;
        break;
    }
}


typedef struct { char s[10]; } S10_80136C90;

void func_801E85E8(void) {
    extern s32 D_801E7AAC;
    extern S10_80136C90 D_801E79DC;
    *(s32 *)(D_801E7AAC + 4) = *(s32 *)&D_801E79DC;
}


void func_801E8600(void) {
    extern s32 D_801E7AAC;
    extern s32 D_801E79E4;
    extern s32 D_801E79E0;
    extern s32 D_801E8A58;
    *(s32 *)(D_801E7AAC + 4) = D_801E79E4;
    D_801E8A58 = D_801E79E0;
}


extern void func_8018CDEC(void);
extern s32 D_801E7AAC;
extern s32 D_801E89F0;
extern s32 D_801E8A10;
extern s16 D_801E79D8;

void func_801E8630(void) {
    func_8018CDEC();
    if (D_801E79D8 == 0) {
        *(s32 *)(*(s32 *)&D_801E7AAC + 4) = (s32)&D_801E89F0;
    } else {
        *(s32 *)(*(s32 *)&D_801E7AAC + 4) = (s32)&D_801E8A10;
    }
}


extern s32 D_801BA448;
extern s32 D_801E87E8;
extern s32 D_801E8818;
extern s32 D_801EFADC;
extern s32 D_801EFB0C;
extern s32 D_801EFB10;
extern s32 func_80029504(void);
extern s32 func_8012C1B8(void);
extern void func_8001C214(s32, s32);
extern void func_8012A828(s32, s32);
extern void func_8012CAE4(void *);
extern void func_8012E8E0(s32, s32);
extern void func_80178B18(s32, s32);

void func_801E868C(void *a0) {
    extern s32 D_801EFADC;
    extern s32 D_801BA448;
    extern s32 D_801E87E8;
    extern s32 D_801E8818;
    extern s32 D_801EFB10;
    extern s32 D_801EFB0C;
    s32 v0;
    s32 ptr;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801EFADC);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s32 *)&D_801EFB10 = 0;
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801BA448);
        func_8012E8E0((s32)a0, (s32)&D_801E87E8);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801E8818);
        v0 = func_80029504();
        *(s32 *)&D_801EFB0C = v0;
    }
}



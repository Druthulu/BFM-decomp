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
extern u8 D_801E3230[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);
extern int func_801E2610(u8 *arg);
extern s32 func_800167F0(s32 a0);
extern s32 func_801E2668(void);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E293C(void *arg0);
extern s32 func_801E268C(s32 param_1);
extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);
extern s32 func_801E26D8(s32 param_1);
extern void func_800D1EBC(void);
extern void func_801E2778(void);
extern void func_801E2798(void *a0);
extern void func_801E27D4(void *a0);
extern void func_801E2810(void *a0);
extern void func_80171A1C(void*);
extern void func_801E284C(void);
extern s32 func_80171D78(u32, void *);
extern void func_801E2874(u32 arg0);
extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);
extern void func_801E28DC(void *arg0);
extern void func_801E2934(void);
extern void func_801E293C(void *a0);
extern void func_801E2978(void);
extern void func_801E2998(u32 arg0);
extern void func_801E2A00(void);
extern void func_801E2ACC(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_801E2B30(s32 param_1, s16 *param_2);
extern s32 func_801E2CC8(void);
/* ==== end §8b carried decl layer ==== */


extern s32 func_801789AC(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);
extern void func_80185B88(s32 a0);
extern s16 func_80185B78(void);
extern u8 *D_80126B10;

void func_801E2CD0(void *param_1) {

    extern s32 D_801E336C;
    extern s32 D_801E3384;
    extern s32 D_801E3308;
    extern s32 D_801E3580[];

    switch (*(u16 *)((s32)param_1 + 0x34)) {
    case 0: {
        s32 v1 = func_801789AC((s32)param_1);
        switch (v1) {
        case 1:
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80185B88(2);
            break;
        case 2:
            func_80178CBC((s32)param_1, (s32)&D_801E336C);
            *(u16 *)((s32)param_1 + 0x34) = 0;
            break;
        case 3:
            func_80178CBC((s32)param_1, (s32)&D_801E3384);
            *(u16 *)((s32)param_1 + 0x34) = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2: {
        s32 v0 = func_80185B78();
        if (v0 != 0) {
            func_80178CBC((s32)param_1, (s32)D_801E3580[v0]);
            *(u16 *)((s32)param_1 + 0x34) = 4;
        } else {
            func_80178CBC((s32)param_1, (s32)&D_801E3308);
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
            func_80185B88(2);
        }
        break;
    }
}




void func_801E2E2C(void *a0) {

    extern void (*D_801E3598[])(void);
    D_801E3598[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136_jr_801E2CD0", func_801E2E68);



void func_801E2E78(void) {

    extern s32 D_801EA5AC;
    D_801EA5AC = 1;
}




s32 func_801E2E8C(void) {

    extern s32 D_801EA5AC;
    return D_801EA5AC;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E2E9C(void) {
        if ((func_80029178(0x111) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x111, 1);
            return 1;
        }
        return 0;
    }


extern s32 func_80029504(void);
extern s32 func_801844F8(void);
extern s32 func_8018456C(void);
extern void func_801845C8(void);

void func_801E2ED8(s32 a0) {

    extern s32 D_801EA5A4;
    extern s32 D_801E3328[];
    extern s32 D_801E333C[];
    extern s32 D_801E3358[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 x = D_801EA5A4;
        s32 idx;
        if (x < 0x14) {
            idx = 0;
        } else if (x < 0x46) {
            idx = 1;
        } else if (x < 0x64) {
            idx = 2;
        } else if (x < 0x82) {
            idx = 3;
        } else {
            idx = 4;
        }
        *(s32 *)(a0 + 0xE4) = D_801E3328[idx];
    } else if (v1 < 0x384) {
        s32 v0 = func_801844F8();
        *(s32 *)(a0 + 0xE4) = D_801E333C[v0];
    } else {
        s32 v0 = func_8018456C();
        *(s32 *)(a0 + 0xE4) = D_801E3358[v0];
        func_801845C8();
    }
}


extern void func_80029514(int);
void func_801E2FB4(void) {
    func_80029514(0x181);
}


extern void func_8018A788(void);
void func_801E2FD4(void) {
    func_8018A788();
}


#include "common.h"

extern s16 D_801E2498;
extern s32 D_801E256C;
extern s32 D_801E3488;
extern void *D_801E34C0[];
extern void *D_801E34F4[];

void func_801E2FF4(void) {
    switch (D_801E2498) {
    case 0:
        *(s32 *)(*(s32 *)&D_801E256C + 4) = (s32)((void *)&D_801E3488);
        break;
    case 1:
        *(s32 *)(*(s32 *)&D_801E256C + 4) = (s32)D_801E34C0;
        break;
    case 2:
        *(s32 *)(*(s32 *)&D_801E256C + 4) = (s32)D_801E34F4;
        break;
    }
}


void func_801E3080(void) {
    extern s32 D_801E256C;
    extern s32 D_801E249C;
    *(s32 *)(D_801E256C + 4) = D_801E249C;
}


void func_801E3098(void) {
    extern s32 D_801E256C;
    extern s32 D_801E24A4;
    extern s32 D_801E24A0;
    extern s32 D_801E34F0;

    *(s32 *)(*(s32 *)&D_801E256C + 4) = D_801E24A4;
    D_801E34F0 = D_801E24A0;
}


extern void func_8018A788(void);
extern s16 D_801E2498;
extern s32 D_801E256C;
extern s32 D_801E3488;
extern s32 D_801E34A8;

void func_801E30C8(void) {
    func_8018A788();
    if (D_801E2498 == 0) {
        *(s32 *)(D_801E256C + 4) = (s32)&D_801E3488;
    } else {
        *(s32 *)(D_801E256C + 4) = (s32)&D_801E34A8;
    }
}


extern s32 D_801BF4F0;
extern s32 D_801E3280;
extern s32 D_801E32B0;
extern s32 D_801EA574;
extern s32 D_801EA5A4;
extern s32 D_801EA5A8;
extern s32 func_80029504(void);
extern s32 func_8012C1B8(void);
extern void func_8001C214(s32, s32);
extern void func_8012A828(s32, s32);
extern void func_8012CAE4(void *);
extern void func_8012E8E0(s32, s32);
extern void func_80178B18(s32, s32);

void func_801E3124(void *a0) {
    extern s32 D_801EA574;
    extern s32 D_801BF4F0;
    extern s32 D_801E3280;
    extern s32 D_801E32B0;
    extern s32 D_801EA5A8;
    extern s32 D_801EA5A4;
    s32 v0;
    s32 ptr;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801EA574);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s32 *)&D_801EA5A8 = 0;
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801BF4F0);
        func_8012E8E0((s32)a0, (s32)&D_801E3280);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801E32B0);
        v0 = func_80029504();
        *(s32 *)&D_801EA5A4 = v0;
    }
}



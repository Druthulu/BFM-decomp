#include "common.h"
#include "../shared/engine_prelude.h"

extern u8 *D_80126B10;
extern u8 D_801E30FC[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801E25FC(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801E30FC;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

#define SHARED_FN func_801E2654
#include "../shared/multi/cls_511a8b68802b.h"
#undef SHARED_FN



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E2928(void *arg0);

#include "../shared/slot_801E25E8/func_801E2678.h"




extern void func_800D1E28(void);
extern s32 guess_RequestSound(s32, s32);
extern void func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern void func_800D0C48(s32);

#define SHARED_FN func_801E26C4
#include "../shared/multi/cls_250b43160334.h"
#undef SHARED_FN


extern s32 func_800D1EBC(void);
#define SHARED_FN func_801E2764
#include "../shared/multi/cls_37f67f3adb2e.h"
#undef SHARED_FN




void func_801E2784(void *a0) {

    extern void (*D_801E30A0[])(void);
    D_801E30A0[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801E27C0(void *a0) {

    extern void (*D_801E30A8[])(void);
    D_801E30A8[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801E27FC(void *a0) {

    extern void (*D_801E312C[])(void);
    D_801E312C[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
#define SHARED_FN func_801E2838
#include "../shared/multi/cls_b9caea59f74f.h"
#undef SHARED_FN


INCLUDE_RODATA("asm/md_SC03_133/nonmatchings/md_SC03_133", D_801E25E8);


const Blk8 D_801E25EC = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

#define SHARED_FN func_801E2860
#include "../shared/slot_801E25E8/cls_b059d3822cce.h"
#undef SHARED_FN



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E28C8(void *arg0) {

    extern u8 D_801E30FC[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E30FC));
        func_80171A1C(arg0);
    }
}


void func_801E2920(void) {
}



void func_801E2928(void *a0) {

    extern void (*D_801E313C[])(void);
    D_801E313C[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
#define SHARED_FN func_801E2964
#include "../shared/multi/cls_88741b5adb4e.h"
#undef SHARED_FN



const Blk8 D_801E25F4 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

#define SHARED_FN func_801E2984
#include "../shared/slot_801E25E8/cls_7649e7f887e6.h"
#undef SHARED_FN


void func_801E29EC(void) {
}


extern void guess_SetMainCameraHandler(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E2AB8(void *a0);

#include "../shared/slot_801E25E8/func_801E29F4.h"




void func_801E2AB8(void *a0) {

    extern void (*D_801E3148[])(void);
    D_801E3148[((Unkstruct_80126948 *)a0)->unk4]();
}


#include "../shared/slot_801E25E8/func_801E2AF4.h"


/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */

extern u16  guess_GetPadPressed(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void RotMatrixZYX(s32 a0, s32 a1);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);

void func_801E2B1C(s32 param_1, s16 *param_2) {

    extern s32 guess_g_PlayerActor;
    extern s16 D_801E314C[];
    extern u16 D_801E3150[];

    MATRIX_801EDED4_801E2B1C  m1;
    SVECTOR_801EDED4_801E2B1C svec_in;
    SVECTOR_801EDED4_801E2B1C svec_out;
    u8 t;

    if (guess_GetPadPressed(&guess_g_PlayerActor) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801E314C[t];
        *(s16 *)(param_1 + 0x2E) = D_801E3150[*(u8 *)(param_1 + 5)];
    }

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  0xA);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 0xA);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 0xA);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 0xA);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 0xA);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0xA);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0xA);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0xA);

    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)param_2[0];
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)param_2[1];
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)param_2[2];
    RotMatrixZYX(param_1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(param_1 + 0x28) + param_2[0];
    m1.t[1] = *(s16 *)(param_1 + 0x2A) + param_2[1];
    m1.t[2] = *(s16 *)(param_1 + 0x2C) + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))guess_RotTransSVWithMatrix)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}



#define SHARED_FN func_801E2D14
#include "../shared/multi/cls_5a794f51671b.h"
#undef SHARED_FN




void func_801E2D1C(void *a0) {

    extern void (*D_801E3288[])(void);
    D_801E3288[((Unkstruct_80126B58 *)a0)->unk2]();
}


void func_801E2D58(void) {
    extern u8 D_80078EB1;
    extern s32 D_801E256C;
    extern s32 D_801E906C;
    extern s32 D_801E3290[];
    extern s32 D_801E32C0[];

    D_801E906C = 0;
    if (D_80078EB1 >= 0x12) {
        ((Unkstruct_801E2D50 *)D_801E256C)->unk4 = (s32)D_801E32C0;
    } else {
        ((Unkstruct_801E2D50 *)D_801E256C)->unk4 = (s32)D_801E3290;
    }
}




void func_801E2DA4(void) {

    extern s32 D_801E906C;
    D_801E906C = 1;
}




s32 func_801E2DB8(void) {

    extern s32 D_801E906C;
    return D_801E906C;
}





extern s32 guess_TestGameFlag(s32 arg);
    extern void guess_SetGameFlag(s32, s32);
#define SHARED_FN func_801E2DC8
#include "../shared/multi/cls_388042195473.h"
#undef SHARED_FN


void func_801E2E04(s32 a0) {
    extern s32 D_801E31FC[];
    extern s32 D_801E37C0;
    extern s32 D_801E3210[];
    extern s32 D_801E322C[];

    s32 v1 = guess_GetStoryProgress();

    if (v1 < 0xC8) {
        s32 v0 = func_80184428();
        ((Unkstruct_801E2E04 *)a0)->unkE4 = D_801E31FC[v0];
    } else if (v1 < 0x384) {
        if ((u32)(v1 - 0x136) < 0x122) {
            ((Unkstruct_801E2E04 *)a0)->unkE4 = (s32)&D_801E37C0;
        } else {
            s32 v0 = func_801844F8();
            ((Unkstruct_801E2E04 *)a0)->unkE4 = D_801E3210[v0];
        }
    } else {
        s32 v0 = func_8018456C();
        ((Unkstruct_801E2E04 *)a0)->unkE4 = D_801E322C[v0];
        func_801845C8();
    }
}


#include "common.h"

extern s32 func_801789AC(s32 arg0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);
extern void func_80185B88(s32 a0);
extern u8 *D_80126B10;

void func_801E2EC0(void *a0) {

    extern s32 D_801E3240;
    extern s32 D_801E3258;
    extern s32 D_801E31DC;

    switch (((Unkstruct_801E2EC0 *)a0)->unk34) {
    case 0: {
        s32 v0 = func_801789AC((s32)a0);
        switch (v0) {
        case 1:
            ((Unkstruct_801E2EC0 *)a0)->unk34 = 2;
            func_80185B88(1);
            break;
        case 2:
            func_80178CBC((s32)a0, (s32)&D_801E3240);
            ((Unkstruct_801E2EC0 *)a0)->unk34 = 0;
            break;
        case 3:
            func_80178CBC((s32)a0, (s32)&D_801E3258);
            ((Unkstruct_801E2EC0 *)a0)->unk34 = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2:
        func_80178CBC((s32)a0, (s32)&D_801E31DC);
        ((Unkstruct_801E2EC0 *)a0)->unk34 = 0;
        break;
    case 3:
        if (func_801789AC((s32)a0) != 0) {
            func_80174438((s32)D_80126B10);
            ((Unkstruct_801E2EC0 *)a0)->unk34 = 1;
        }
        break;
    }
}


extern s32 guess_AllocModelObject(void);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32 a0, s32 a1);
extern void guess_StartActorSequence(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801E2FF4(void *a0) {
    extern s32 D_801E904C;
    extern s16 D_801E3154;
    extern s16 D_801E3156;
    extern s16 D_801E3158;
    extern s16 D_801BEBF8;
    extern s32 D_801E3184;
    s32 v0;
    s32 v1;

    v0 = guess_AllocModelObject();
    ((Unkstruct_800B5CB8 *)a0)->unk20 = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn(a0);
    } else {
        guess_InitModelObject(v0, (s32)&D_801E904C);
        v1 = ((Unkstruct_800B5CB8 *)a0)->unk68;
        CAST_ALIAS(s16, (s32)a0, 0x6) = D_801E3154;
        CAST_ALIAS(s16, (s32)a0, 0xA) = D_801E3156;
        ((Unkstruct_800B5CB8 *)a0)->unkE = D_801E3158;
        *(s16 *)(v1 + 0xC) = 0x7FFF;
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 1;
        guess_StartActorSequence((s32)a0, (s32)&D_801BEBF8);
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 0;
        func_80178B18((s32)a0, (s32)&D_801E3184);
    }
}


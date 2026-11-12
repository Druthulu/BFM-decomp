#include "common.h"

#include "common.h"

extern u8 D_801E85B4[];

void func_800167B8(int);
void func_80175414(s32 _arg0);

int func_801E7B34(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801E85B4;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

#define SHARED_FN func_801E7B8C
#include "../shared/multi/cls_511a8b68802b.h"
#undef SHARED_FN



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E7E60(void *arg0);

s32 func_801E7BB0(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E7E60, 0x1000000);
    ((Unkstruct_801E2670 *)param_1)->unk15 = ((Unkstruct_801E2670 *)param_1)->unk15 + 1;
    ((Unkstruct_801E2670 *)param_1)->unk28 = 16;
    return 0;
}




extern void func_800D1E28(void);
extern s32 guess_RequestSound(s32, s32);
extern void func_8001BFD0(void);
extern s32 guess_GetGameVarByte(s32);
extern s32 func_80029524(void);
extern void func_800D0C48(s32);

#define SHARED_FN func_801E7BFC
#include "../shared/multi/cls_250b43160334.h"
#undef SHARED_FN


extern s32 func_800D1EBC(void);
#define SHARED_FN func_801E7C9C
#include "../shared/multi/cls_37f67f3adb2e.h"
#undef SHARED_FN




void func_801E7CBC(void *a0) {

    extern void (*D_801E8558[])(void);
    D_801E8558[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801E7CF8(void *a0) {

    extern void (*D_801E8560[])(void);
    D_801E8560[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801E7D34(void *a0) {

    extern void (*D_801E85E4[])(void);
    D_801E85E4[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
#define SHARED_FN func_801E7D70
#include "../shared/multi/cls_b9caea59f74f.h"
#undef SHARED_FN


extern const Blk8_md_SC03_076 D_801E7B2C;
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

#define SHARED_FN func_801E7D98
#include "../shared/slot_801E7B28/cls_db39c5710d91.h"
#undef SHARED_FN



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E7E00(void *arg0) {

    extern u8 D_801E85B4[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E85B4));
        func_80171A1C(arg0);
    }
}


void func_801E7E58(void) {
}



void func_801E7E60(void *a0) {

    extern void (*D_801E85F4[])(void);
    D_801E85F4[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
#define SHARED_FN func_801E7E9C
#include "../shared/multi/cls_88741b5adb4e.h"
#undef SHARED_FN



extern const Blk8_md_SC03_076 D_801E7B2C;
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

#define SHARED_FN func_801E7EBC
#include "../shared/slot_801E7B28/cls_db39c5710d91.h"
#undef SHARED_FN


void func_801E7F24(void) {
}


extern void guess_SetMainCameraHandler(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E7FF0(void *a0);

void func_801E7F2C(void) {

    extern s32 D_80126950;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 guess_g_MainCameraPitchTarget;
    extern s16 guess_g_MainCameraYawTarget;
    extern s16 guess_g_MainCameraRollTarget;
    extern s16 guess_g_MainCameraRefOffsetTargetX;
    extern s16 guess_g_MainCameraRefOffsetTargetY;
    extern s16 guess_g_MainCameraRefOffsetTargetZ;
    extern u8 guess_g_MainCamera[];
    extern s16 D_801274E8;
    extern s16 D_801274EA;
    extern s16 D_801274EC;

    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x82;
    guess_g_MainCameraPitchTarget = 0xFB1;
    guess_g_MainCameraYawTarget = 0x7C7;
    guess_g_MainCameraRollTarget = 0;
    guess_g_MainCameraRefOffsetTargetX = 0;
    guess_g_MainCameraRefOffsetTargetY = -0x36;
    guess_g_MainCameraRefOffsetTargetZ = 0;
    guess_SetMainCameraHandler((s32)func_801E7FF0, 0);
    func_801E7FF0(guess_g_MainCamera);
    func_8012A094((s32)guess_g_MainCamera);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801E7FF0(void *a0) {

    extern void (*D_801E8600[])(void);
    D_801E8600[((Unkstruct_80126948 *)a0)->unk4]();
}


extern void func_801E8054(s32 param_1, s16 *param_2);

void func_801E802C(s32 arg0) {
    extern s16 D_801274E8;

    func_801E8054(arg0, &D_801274E8);
}



/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */

extern u16  guess_GetPadPressed(s32 *a0);
extern s32  guess_EaseToward(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void RotMatrixZYX(s32 a0, s32 a1);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);

void func_801E8054(s32 param_1, s16 *param_2) {

    extern s32 guess_g_PlayerActor;
    extern s16 D_801E8604[];
    extern u16 D_801E8608[];

    MATRIX_801EDED4_801E8054  m1;
    SVECTOR_801EDED4_801E8054 svec_in;
    SVECTOR_801EDED4_801E8054 svec_out;
    u8 t;

    if (guess_GetPadPressed(&guess_g_PlayerActor) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801E8604[t];
        *(s16 *)(param_1 + 0x2E) = D_801E8608[*(u8 *)(param_1 + 5)];
    }

    *(s32 *)(param_1 + 0x8)  = (s16)guess_EaseToward((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  0xA);
    *(s32 *)(param_1 + 0x10) = (s16)guess_EaseToward((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 0xA);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 0xA);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 0xA);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 0xA);
    *(s16 *)(param_1 + 0x28) = guess_EaseToward((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0xA);
    *(s16 *)(param_1 + 0x2A) = guess_EaseToward((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0xA);
    *(s16 *)(param_1 + 0x2C) = guess_EaseToward((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0xA);

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



u8 func_801E824C(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xD;
}




void func_801E827C(void *a0) {

    extern void (*D_801E8708[])(void);
    D_801E8708[((Unkstruct_80126B58 *)a0)->unk2]();
}


void func_801E82B8(void) {

    extern s32 D_801EECE4;
    D_801EECE4 = 0;
}




void func_801E82C8(void) {

    extern s32 D_801EECE4;
    D_801EECE4 = 1;
}




s32 func_801E82DC(void) {

    extern s32 D_801EECE4;
    return D_801EECE4;
}




extern s32 guess_GetStoryProgress(void);
extern s32 func_80184D00(s32);
extern s32 func_80184DD0(void);
extern s32 func_80184E44(void);
extern void func_80184EA0(void);

void func_801E82EC(s32 a0) {

    extern s32 D_801E867C[];
    extern s32 D_801E8690[];
    extern s32 D_801E86AC[];

    s32 v1 = guess_GetStoryProgress();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_80184D00)();
        ((Unkstruct_801E2D84 *)a0)->unkE4 = D_801E867C[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_80184DD0();
        ((Unkstruct_801E2D84 *)a0)->unkE4 = D_801E8690[v0];
    } else {
        s32 v0 = func_80184E44();
        ((Unkstruct_801E2D84 *)a0)->unkE4 = D_801E86AC[v0];
        func_80184EA0();
    }
}



extern s32 func_801789AC(s32 arg0);
extern s32 func_80186460(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);

void func_801E838C(void *a0) {

    extern u8 *D_80126B10;

    extern s32 D_801E86C0;
    extern s32 D_801E86D8;
    extern s32 D_801E865C;

    switch (((Unkstruct_801E2E24 *)a0)->unk34) {
    case 0: {
        s32 v0 = func_801789AC((s32)a0);
        switch (v0) {
        case 1:
            ((Unkstruct_801E2E24 *)a0)->unk34 = 2;
            func_80186460(3);
            break;
        case 2:
            func_80178CBC((s32)a0, (s32)&D_801E86C0);
            ((Unkstruct_801E2E24 *)a0)->unk34 = 0;
            break;
        case 3:
            func_80178CBC((s32)a0, (s32)&D_801E86D8);
            ((Unkstruct_801E2E24 *)a0)->unk34 = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2:
        func_80178CBC((s32)a0, (s32)&D_801E865C);
        ((Unkstruct_801E2E24 *)a0)->unk34 = 0;
        break;
    case 3:
        if (func_801789AC((s32)a0) != 0) {
            func_80174438((s32)D_80126B10);
            ((Unkstruct_801E2E24 *)a0)->unk34 = 1;
        }
        break;
    }
}



extern s32 guess_AllocModelObject(void);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32 a0, s32 a1);
extern void guess_StartActorSequence(s32 a0, s32 a1);
extern void guess_SetObjectPosAndYaw(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801E84C0(void *a0) {
    extern s32 D_801EECB8;
    extern s32 D_801B9A50;
    extern s32 D_801E860C;
    extern s32 D_801E8614;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))guess_AllocModelObject)();
    ((Unkstruct_800B5CB8 *)a0)->unk20 = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn(a0);
    } else {
        guess_InitModelObject(v0, (s32)&D_801EECB8);
        ptr = ((Unkstruct_800B5CB8 *)a0)->unk68;
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 1;
        guess_StartActorSequence((s32)a0, (s32)&D_801B9A50);
        guess_SetObjectPosAndYaw((s32)a0, (s32)&D_801E860C);
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 0;
        func_80178B18((s32)a0, (s32)&D_801E8614);
    }
}


INCLUDE_RODATA("asm/md_SC04_024/nonmatchings/md_SC04_024", D_801E7B28);

INCLUDE_RODATA("asm/md_SC04_024/nonmatchings/md_SC04_024", D_801E7B2C);

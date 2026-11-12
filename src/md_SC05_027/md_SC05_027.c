#include "common.h"

extern u8 *D_80126B10;
extern u8 D_801EE620[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801ED9B0(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801EE620;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

#define SHARED_FN func_801EDA08
#include "../shared/multi/cls_511a8b68802b.h"
#undef SHARED_FN



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EDCF4(void *arg0);

s32 func_801EDA2C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EDCF4, 0x1000000);
    ((Unkstruct_801E2670 *)param_1)->unk15 = ((Unkstruct_801E2670 *)param_1)->unk15 + 1;
    ((Unkstruct_801E2670 *)param_1)->unk28 = 16;
    return 0;
}


extern void func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 guess_GetStoryProgress(void);
extern s32 guess_RequestSound(s32, s32);
extern void func_800D0C48(s32);
extern void func_800D1E28(void);

#define SHARED_FN func_801EDA78
#include "../shared/slot_801ED988/cls_2a4b688c54b1.h"
#undef SHARED_FN


extern s32 func_800D1EBC(void);
#define SHARED_FN func_801EDB30
#include "../shared/multi/cls_37f67f3adb2e.h"
#undef SHARED_FN




void func_801EDB50(void *a0) {

    extern void (*D_801EE5C4[])(void);
    D_801EE5C4[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801EDB8C(void *a0) {

    extern void (*D_801EE5CC[])(void);
    D_801EE5CC[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801EDBC8(void *a0) {

    extern void (*D_801EE650[])(void);
    D_801EE650[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
#define SHARED_FN func_801EDC04
#include "../shared/multi/cls_b9caea59f74f.h"
#undef SHARED_FN


INCLUDE_RODATA("asm/md_SC05_027/nonmatchings/md_SC05_027", D_801ED988);

const Blk8_md_SC03_076 D_801ED98C = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

#define SHARED_FN func_801EDC2C
#include "../shared/slot_801ED988/cls_630164eaff26.h"
#undef SHARED_FN



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EDC94(void *arg0) {

    extern u8 D_801EE620[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801EE620));
        func_80171A1C(arg0);
    }
}


void func_801EDCEC(void) {
}



void func_801EDCF4(void *a0) {

    extern void (*D_801EE660[])(void);
    D_801EE660[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
#define SHARED_FN func_801EDD30
#include "../shared/multi/cls_88741b5adb4e.h"
#undef SHARED_FN



const Blk8_md_SC03_076 D_801ED994 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

#define SHARED_FN func_801EDD50
#include "../shared/slot_801ED988/cls_8ece44014e55.h"
#undef SHARED_FN


void func_801EDDB8(void) {
}

void func_801EDDC0(void) {
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
    extern void guess_SetMainCameraHandler(s32 a0, s32 a1);
    extern void func_8012A094(s32 a0);
    extern void func_801EDE84(void *a0);

    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x82;
    guess_g_MainCameraPitchTarget = 0xFB1;
    guess_g_MainCameraYawTarget = 0x7C7;
    guess_g_MainCameraRollTarget = 0;
    guess_g_MainCameraRefOffsetTargetX = 0;
    guess_g_MainCameraRefOffsetTargetY = -0x50;
    guess_g_MainCameraRefOffsetTargetZ = 0;
    guess_SetMainCameraHandler((s32)func_801EDE84, 0);
    func_801EDE84(guess_g_MainCamera);
    func_8012A094((s32)guess_g_MainCamera);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801EDE84(void *a0) {

    extern void (*D_801EE66C[])(void);
    D_801EE66C[((Unkstruct_80126948 *)a0)->unk4]();
}


void func_801EDEC0(s32 param_1) {
    extern s16 D_801274E8;
    extern void func_801EDEE8(s32 param_1, s16 *param_2);
    func_801EDEE8(param_1, &D_801274E8);
}


extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void RotMatrixZYX(s32 a0, s32 a1);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);

#define SHARED_FN func_801EDEE8
#include "../shared/multi/cls_89463c3facc6.h"
#undef SHARED_FN




u8 func_801EE080(a0)
u32 a0;
{
    if ((u32)(a0 - 0x460) < 0x32) {
        return 0x89;
    }
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xD;
}

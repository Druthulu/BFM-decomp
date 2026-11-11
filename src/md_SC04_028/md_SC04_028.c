#include "common.h"

#include "common.h"

extern u8 D_801E8798[];

void func_800167B8(int);
void func_80175414(s32 _arg0);

int func_801E7B50(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801E8798;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

#define SHARED_FN func_801E7BA8
#include "../shared/multi/cls_511a8b68802b.h"
#undef SHARED_FN



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E7E7C(void *arg0);

s32 func_801E7BCC(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E7E7C, 0x1000000);
    ((Unkstruct_801E2670 *)param_1)->unk15 = ((Unkstruct_801E2670 *)param_1)->unk15 + 1;
    ((Unkstruct_801E2670 *)param_1)->unk28 = 16;
    return 0;
}




extern void func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern void func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern void func_800D0C48(s32);

#define SHARED_FN func_801E7C18
#include "../shared/multi/cls_250b43160334.h"
#undef SHARED_FN


extern s32 func_800D1EBC(void);
#define SHARED_FN func_801E7CB8
#include "../shared/multi/cls_37f67f3adb2e.h"
#undef SHARED_FN




void func_801E7CD8(void *a0) {

    extern void (*D_801E873C[])(void);
    D_801E873C[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801E7D14(void *a0) {

    extern void (*D_801E8744[])(void);
    D_801E8744[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801E7D50(void *a0) {

    extern void (*D_801E87C8[])(void);
    D_801E87C8[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
#define SHARED_FN func_801E7D8C
#include "../shared/multi/cls_b9caea59f74f.h"
#undef SHARED_FN


INCLUDE_RODATA("asm/md_SC04_028/nonmatchings/md_SC04_028", D_801E7B28);

const Blk8_md_SC03_076 D_801E7B2C = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

#define SHARED_FN func_801E7DB4
#include "../shared/slot_801E7B28/cls_db39c5710d91.h"
#undef SHARED_FN



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E7E1C(void *arg0) {

    extern u8 D_801E8798[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E8798));
        func_80171A1C(arg0);
    }
}


void func_801E7E74(void) {
}



void func_801E7E7C(void *a0) {

    extern void (*D_801E87D8[])(void);
    D_801E87D8[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
#define SHARED_FN func_801E7EB8
#include "../shared/multi/cls_88741b5adb4e.h"
#undef SHARED_FN



const Blk8_md_SC03_076 D_801E7B34 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

#define SHARED_FN func_801E7ED8
#include "../shared/slot_801E7B28/cls_8843d2e74e11.h"
#undef SHARED_FN


void func_801E7F40(void) {
}

extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E800C(void *a0);

void func_801E7F48(void) {

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
    guess_g_MainCameraRefOffsetTargetY = -0x50;
    guess_g_MainCameraRefOffsetTargetZ = 0;
    func_8012A018((s32)func_801E800C, 0);
    func_801E800C(guess_g_MainCamera);
    func_8012A094((s32)guess_g_MainCamera);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801E800C(void *a0) {

    extern void (*D_801E87E4[])(void);
    D_801E87E4[((Unkstruct_80126948 *)a0)->unk4]();
}


extern void func_801E8070(s32 param_1, s16 *param_2);

void func_801E8048(s32 param_1) {
    extern s16 D_801274E8;
    func_801E8070(param_1, &D_801274E8);
}


extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);

#define SHARED_FN func_801E8070
#include "../shared/multi/cls_89463c3facc6.h"
#undef SHARED_FN



u8 func_801E8208(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xD;
}

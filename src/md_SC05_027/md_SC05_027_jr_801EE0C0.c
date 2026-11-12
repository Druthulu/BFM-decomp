#include "common.h"

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
extern void func_8001BFD0(void);
extern s32 guess_GetGameVarByte(s32);
extern s32 guess_GetStoryProgress(void);
extern s32 guess_RequestSound(s32, s32);
extern void func_800D0C48(s32);
extern void func_800D1E28(void);
extern s32 func_801EDA78(s32 param_1);
extern s32 func_800D1EBC(void);
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
extern s32 guess_EaseToward(s32 a0, s32 a1, s32 a2);
extern void RotMatrixZYX(s32 a0, s32 a1);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);
extern void func_801EDEE8(s32 param_1, s16 *param_2);
extern u8 func_801EE080(u32 a0);


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

    switch (((Unkstruct_801EE0C0 *)param_1)->unk34) {
    case 0: {
        s32 v0 = func_801789AC((s32)param_1);
        switch (v0) {
        case 1:
            ((Unkstruct_801EE0C0 *)param_1)->unk34 = 2;
            func_80186160(2);
            break;
        case 2:
            func_80178CBC((s32)param_1, (s32)&D_801EE75C);
            ((Unkstruct_801EE0C0 *)param_1)->unk34 = 0;
            break;
        case 3:
            func_80178CBC((s32)param_1, (s32)&D_801EE774);
            ((Unkstruct_801EE0C0 *)param_1)->unk34 = 3;
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
            ((Unkstruct_801EE0C0 *)param_1)->unk34 = 4;
        } else {
            func_80178CBC((s32)param_1, (s32)&D_801EE6F8);
            ((Unkstruct_801EE0C0 *)param_1)->unk34 = 0;
        }
        break;
    }
    case 3:
        if (func_801789AC((s32)param_1) != 0) {
            func_80174438((s32)D_80126B10);
            ((Unkstruct_801EE0C0 *)param_1)->unk34 = 1;
        }
        break;
    case 4:
        if (func_801789AC((s32)param_1) != 0) {
            ((Unkstruct_801EE0C0 *)param_1)->unk34 = 2;
            func_80186160(2);
        }
        break;
    }
}




void func_801EE21C(void *a0) {

    extern void (*D_801EE988[])(void);
    D_801EE988[((Unkstruct_80126B58 *)a0)->unk2]();
}


#include "common.h"

void func_801EE258(void) {
    extern s32 D_801F599C;
    D_801F599C = 0;
}




void func_801EE268(void) {

    extern s32 D_801F599C;
    D_801F599C = 1;
}




s32 func_801EE27C(void) {

    extern s32 D_801F599C;
    return D_801F599C;
}





extern s32 guess_TestGameFlag(s32 arg);
    extern void guess_SetGameFlag(s32, s32);
#define SHARED_FN func_801EE28C
#include "../shared/multi/cls_842ac2428050.h"
#undef SHARED_FN


extern s32 guess_GetStoryProgress(void);
extern s32 func_80184AD0(void);
extern s32 func_80184B44(void);
extern void func_80184BA0(void);

void func_801EE2C8(s32 a0) {

    extern s32 D_801EE718[];
    extern s32 D_801EE72C[];
    extern s32 D_801EE748[];

    s32 v1 = guess_GetStoryProgress();

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
        ((Unkstruct_801EE2C8 *)a0)->unkE4 = D_801EE718[idx];
    } else if (v1 < 0x384) {
        s32 v0 = func_80184AD0();
        ((Unkstruct_801EE2C8 *)a0)->unkE4 = D_801EE72C[v0];
    } else {
        s32 v0 = func_80184B44();
        ((Unkstruct_801EE2C8 *)a0)->unkE4 = D_801EE748[v0];
        func_80184BA0();
    }
}


extern void func_80029514(int);
#define SHARED_FN func_801EE3A4
#include "../shared/multi/cls_72bf727d40d3.h"
#undef SHARED_FN


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
    CAST_WIDTH(s32, D_801ED90C, 4) = D_801ED83C;
}


void func_801EE488(void) {
    extern s32 D_801ED90C;
    extern s32 D_801ED844;
    extern s32 D_801ED840;
    extern s32 D_801EE8E0;

    CAST_WIDTH(s32, D_801ED90C, 4) = D_801ED844;
    D_801EE8E0 = D_801ED840;
}


void func_801EE4B8(void) {
    extern s32 D_801ED90C;
    extern s16 D_801ED838;
    extern u8 D_801EE878[];
    extern u8 D_801EE898[];

    func_8018CDB0();
    if (D_801ED838 == 0) {
        CAST_WIDTH(s32, D_801ED90C, 4) = (s32)D_801EE878;
    } else {
        CAST_WIDTH(s32, D_801ED90C, 4) = (s32)D_801EE898;
    }
}


extern s32 D_801BA404;
extern s32 D_801EE670;
extern s32 D_801EE6A0;
extern s32 D_801F5964;
extern s32 D_801F5994;
extern s32 D_801F5998;
extern s32 guess_GetStoryProgress(void);
extern s32 guess_AllocModelObject(void);
extern void guess_InitModelObject(s32, s32);
extern void guess_StartActorSequence(s32, s32);
extern void guess_FreeActorDuringSpawn(void *);
extern void guess_SetObjectPosAndYaw(s32, s32);
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

    v0 = guess_AllocModelObject();
    ((Unkstruct_800B5CB8 *)a0)->unk20 = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn(a0);
    } else {
        guess_InitModelObject(v0, (s32)&D_801F5964);
        ptr = ((Unkstruct_800B5CB8 *)a0)->unk68;
        *(s32 *)&D_801F5998 = 0;
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 1;
        guess_StartActorSequence((s32)a0, (s32)&D_801BA404);
        guess_SetObjectPosAndYaw((s32)a0, (s32)&D_801EE670);
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 0;
        func_80178B18((s32)a0, (s32)&D_801EE6A0);
        v0 = guess_GetStoryProgress();
        *(s32 *)&D_801F5994 = v0;
    }
}



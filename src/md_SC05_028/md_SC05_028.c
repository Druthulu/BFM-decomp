#include "common.h"

extern u8 *D_80126B10;
extern u8 D_801EE394[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801ED99C(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801EE394;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

#define SHARED_FN func_801ED9F4
#include "../shared/multi/cls_511a8b68802b.h"
#undef SHARED_FN



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EDCE0(void *arg0);

#include "../shared/slot_801ED988/func_801EDA18.h"


extern void func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 guess_GetStoryProgress(void);
extern void func_8002D4C8(s32, s32);
extern void func_800D0C48(s32);
extern void func_800D1E28(void);

#define SHARED_FN func_801EDA64
#include "../shared/slot_801ED988/cls_2a4b688c54b1.h"
#undef SHARED_FN


extern s32 func_800D1EBC(void);
#define SHARED_FN func_801EDB1C
#include "../shared/multi/cls_37f67f3adb2e.h"
#undef SHARED_FN




void func_801EDB3C(void *a0) {

    extern void (*D_801EE338[])(void);
    D_801EE338[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801EDB78(void *a0) {

    extern void (*D_801EE340[])(void);
    D_801EE340[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801EDBB4(void *a0) {

    extern void (*D_801EE3C4[])(void);
    D_801EE3C4[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
#define SHARED_FN func_801EDBF0
#include "../shared/multi/cls_b9caea59f74f.h"
#undef SHARED_FN


INCLUDE_RODATA("asm/md_SC05_028/nonmatchings/md_SC05_028", D_801ED988);


const Blk8_md_SC03_076 D_801ED98C = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};

extern int func_80171D78(u32, void *);
extern void func_80171A1C(void*);

#define SHARED_FN func_801EDC18
#include "../shared/slot_801ED988/cls_630164eaff26.h"
#undef SHARED_FN



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EDC80(void *arg0) {

    extern u8 D_801EE394[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801EE394));
        func_80171A1C(arg0);
    }
}


void func_801EDCD8(void) {
}



void func_801EDCE0(void *a0) {

    extern void (*D_801EE3D4[])(void);
    D_801EE3D4[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
#define SHARED_FN func_801EDD1C
#include "../shared/multi/cls_88741b5adb4e.h"
#undef SHARED_FN


const Blk8_md_SC03_076 D_801ED994 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

#define SHARED_FN func_801EDD3C
#include "../shared/slot_801ED988/cls_8ece44014e55.h"
#undef SHARED_FN


void func_801EDDA4(void) {
}


extern void guess_SetMainCameraHandler(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801EDE70(void *a0);

#include "../shared/slot_801ED988/func_801EDDAC.h"




void func_801EDE70(void *a0) {

    extern void (*D_801EE3E0[])(void);
    D_801EE3E0[((Unkstruct_80126948 *)a0)->unk4]();
}


#include "../shared/slot_801ED988/func_801EDEAC.h"



/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */

extern u16  guess_GetPadPressed(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void RotMatrixZYX(s32 a0, s32 a1);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);

void func_801EDED4(s32 param_1, s16 *param_2) {

    extern s32 guess_g_PlayerActor;
    extern s16 D_801EE3E4[];
    extern u16 D_801EE3E8[];

    MATRIX_801EDED4_801EDED4  m1;
    SVECTOR_801EDED4_801EDED4 svec_in;
    SVECTOR_801EDED4_801EDED4 svec_out;
    u8 t;

    if (guess_GetPadPressed(&guess_g_PlayerActor) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801EE3E4[t];
        *(s16 *)(param_1 + 0x2E) = D_801EE3E8[*(u8 *)(param_1 + 5)];
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




u8 func_801EE0CC(a0)
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
    return 0x17;
}




void func_801EE10C(void *a0) {

    extern void (*D_801EE4EC[])(void);
    D_801EE4EC[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern s32 D_801EE408[];
extern s32 D_801EE41C[];
extern s32 D_801EE438[];
extern s32 guess_GetStoryProgress(void);
extern s32 func_80184A00(s32);
extern s32 func_80184AD0(void);
extern s32 func_80184B44(void);

void func_801EE148(s32 a0) {

    extern s32 D_801EE408[];
    extern s32 D_801EE41C[];
    extern s32 D_801EE438[];

    s32 v1 = guess_GetStoryProgress();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_80184A00)();
        ((Unkstruct_801E2D58 *)a0)->unkE4 = D_801EE408[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_80184AD0();
        ((Unkstruct_801E2D58 *)a0)->unkE4 = D_801EE41C[v0];
    } else {
        s32 v0 = func_80184B44();
        ((Unkstruct_801E2D58 *)a0)->unkE4 = D_801EE438[v0];
    }
}




extern s32 func_8014CB1C(void);

#define SHARED_FN func_801EE1E8
#include "../shared/multi/cls_5e981265ebca.h"
#undef SHARED_FN





extern void func_8014B2A8(void);
extern void func_8002D4C8(s32 a0, s32 a1);

#define SHARED_FN func_801EE208
#include "../shared/multi/cls_4ab0fc7a4435.h"
#undef SHARED_FN


extern s32 func_801789AC(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);
extern u8 *D_80126B10;

void func_801EE234(void *param_1) {

    extern s32 D_801EE4DC;

    switch (((Unkstruct_801EE234 *)param_1)->unk34) {
    case 0:
        if (((s32 (*)(void))func_801789AC)() != 0) {
            func_80178CBC((s32)param_1, (s32)&D_801EE4DC);
            ((Unkstruct_801EE234 *)param_1)->unk34 = 1;
        }
        break;
    case 1:
        if (func_801789AC((s32)param_1) != 0) {
            func_80174438((s32)D_80126B10);
            ((Unkstruct_801EE234 *)param_1)->unk34 = 2;
        }
        break;
    case 2:
        break;
    }
}


extern s32 func_801844BC(void *a0, void *a1);
extern void guess_StartActorSequence(s32 a0, void *a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801EE2C8(void *param_1) {

    extern s32 D_801EE3F4;
    extern s32 D_801BA244;
    extern s32 D_801EE3EC;
    extern s32 D_801EE474;

    if (func_801844BC(param_1, &D_801EE3F4) != 0) {
        ((Unkstruct_800B5CB8 *)param_1)->unk2 = 1;
        guess_StartActorSequence((s32)param_1, &D_801BA244);
        func_8012E8E0((s32)param_1, (s32)&D_801EE3EC);
        ((Unkstruct_800B5CB8 *)param_1)->unk34 = 0;
        func_80178B18((s32)param_1, (s32)&D_801EE474);
    }
}


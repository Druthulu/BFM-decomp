#include "common.h"
#include "../shared/engine_prelude.h"

extern u8 D_801E35C4[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801E25FC(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801E35C4;
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

    extern void (*D_801E3568[])(void);
    D_801E3568[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801E27C0(void *a0) {

    extern void (*D_801E3570[])(void);
    D_801E3570[((Unkstruct_80159698_2 *)a0)->unk15]();
}




void func_801E27FC(void *a0) {

    extern void (*D_801E361C[])(void);
    D_801E361C[((Unkstruct_80172CA0_2 *)a0)->unk214]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
#define SHARED_FN func_801E2838
#include "../shared/multi/cls_b9caea59f74f.h"
#undef SHARED_FN


INCLUDE_RODATA("asm/md_SC03_134/nonmatchings/md_SC03_134", D_801E25E8);


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

    extern u8 D_801E35C4[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E35C4));
        func_80171A1C(arg0);
    }
}


void func_801E2920(void) {
}



void func_801E2928(void *a0) {

    extern void (*D_801E362C[])(void);
    D_801E362C[((Unkstruct_80172CA0_2 *)a0)->unk214]();
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

    extern void (*D_801E3638[])(void);
    D_801E3638[((Unkstruct_80126948 *)a0)->unk4]();
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
    extern s16 D_801E363C[];
    extern u16 D_801E3640[];

    MATRIX_801EDED4_801E2B1C  m1;
    SVECTOR_801EDED4_801E2B1C svec_in;
    SVECTOR_801EDED4_801E2B1C svec_out;
    u8 t;

    if (guess_GetPadPressed(&guess_g_PlayerActor) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801E363C[t];
        *(s16 *)(param_1 + 0x2E) = D_801E3640[*(u8 *)(param_1 + 5)];
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

    extern void (*D_801E37B0[])(void);
    D_801E37B0[((Unkstruct_80126B58 *)a0)->unk2]();
}


void func_801E2D58(void) {
    extern u8 D_80078EBA;
    extern s32 D_801E256C;
    extern s32 D_801E9E34;
    extern s32 D_801E39F4[];
    extern s32 D_801E39B4[];

    D_801E9E34 = 0;
    if (D_80078EBA == 4) {
        ((Unkstruct_801E2D50 *)D_801E256C)->unk4 = (s32)D_801E39F4;
    } else {
        ((Unkstruct_801E2D50 *)D_801E256C)->unk4 = (s32)D_801E39B4;
    }
}




void func_801E2DA4(void) {

    extern s32 D_801E9E34;
    D_801E9E34 = 1;
}




s32 func_801E2DB8(void) {

    extern s32 D_801E9E34;
    return D_801E9E34;
}


extern s32 guess_TestGameFlag(s32 arg);
extern void guess_SetGameFlag(s32, s32);
extern s32 guess_GetStoryProgress(void);

s32 func_801E2DC8(void) {
    if ((guess_TestGameFlag(0xF5) & 0xFF) != 0) {
        return 0;
    }
    if ((u32)(guess_GetStoryProgress() - 0xC8) < 0x190) {
        guess_SetGameFlag(0xF5, 1);
        guess_SetGameFlag(0x10F, 1);
        return 1;
    }
    return 0;
}





extern s32 guess_TestGameFlag(s32 arg);
    extern void guess_SetGameFlag(s32, s32);
#define SHARED_FN func_801E2E2C
#include "../shared/multi/cls_e848cc87e719.h"
#undef SHARED_FN




extern s32 guess_GetStoryProgress(void);
extern s32 func_80184428(s32);
extern s32 func_801844F8(void);
extern s32 func_8018456C(void);
extern void func_801845C8(void);

void func_801E2E68(s32 a0) {

    extern s32 D_801E3724[];
    extern s32 D_801E3738[];
    extern s32 D_801E3754[];

    s32 v1 = guess_GetStoryProgress();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_80184428)();
        ((Unkstruct_801E2D84 *)a0)->unkE4 = D_801E3724[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_801844F8();
        ((Unkstruct_801E2D84 *)a0)->unkE4 = D_801E3738[v0];
    } else {
        s32 v0 = func_8018456C();
        ((Unkstruct_801E2D84 *)a0)->unkE4 = D_801E3754[v0];
        func_801845C8();
    }
}



extern s32 func_801789AC(s32 a0);
extern void func_80185B88(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);

void func_801E2F08(void *param_1) {

    extern u8 *D_80126B10;

    extern s32 D_801E3768;
    extern s32 D_801E3780;
    extern s32 D_801E3704;

    switch (((Unkstruct_801E2F08 *)param_1)->unk34) {
    case 0: {
        s32 v0 = func_801789AC((s32)param_1);
        switch (v0) {
        case 1:
            ((Unkstruct_801E2F08 *)param_1)->unk34 = 2;
            func_80185B88(0);
            break;
        case 2:
            func_80178CBC((s32)param_1, (s32)&D_801E3768);
            ((Unkstruct_801E2F08 *)param_1)->unk34 = 0;
            break;
        case 3:
            func_80178CBC((s32)param_1, (s32)&D_801E3780);
            ((Unkstruct_801E2F08 *)param_1)->unk34 = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2:
        func_80178CBC((s32)param_1, (s32)&D_801E3704);
        ((Unkstruct_801E2F08 *)param_1)->unk34 = 0;
        break;
    case 3:
        if (func_801789AC((s32)param_1) != 0) {
            func_80174438((s32)D_80126B10);
            ((Unkstruct_801E2F08 *)param_1)->unk34 = 1;
        }
        break;
    }
}


extern s32 guess_GetStoryProgress(void);
extern s32 guess_AllocModelObject(void);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32 a0, s32 a1);
extern void guess_StartActorSequence(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801E303C(void *a0) {
    extern s32 D_801E988C;
    extern s32 D_801E3644;
    extern s16 D_801BEBF8;
    extern s32 D_801E369C;
    s32 v0;

    if ((u32)(guess_GetStoryProgress() - 0x122) < 0xA) {
        guess_FreeActorDuringSpawn(a0);
        return;
    }

    v0 = guess_AllocModelObject();
    ((Unkstruct_800B5CB8 *)a0)->unk20 = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn(a0);
    } else {
        guess_InitModelObject(v0, (s32)&D_801E988C);
        *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk68 + 0xC) = 0x7FFF;
        func_8012E8E0((s32)a0, (s32)&D_801E3644);
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 1;
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 0;
        guess_StartActorSequence((s32)a0, (s32)&D_801BEBF8);
        func_80178B18((s32)a0, (s32)&D_801E369C);
    }
}



extern s32 func_8012BA10(s32 a0, s32 a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void guess_StartActorSequence(s32 a0, s32 a1);
extern s32 func_801789AC(s32 a0);
extern void func_80178D18(s32 a0);

void func_801E30EC(void *param_1) {

    extern s32 D_801E37E8[];
    extern s32 D_801E37DC[];
    extern s32 D_801E37F4[];

    switch (((Unkstruct_800B5CB8 *)param_1)->unkFC) {
    case 0: {
        s32 v0 = func_8012BA10((s32)param_1, 0x10);
        s32 cur;
        s32 target;
        ((Unkstruct_800B5CB8 *)*(s32 *)((s32)param_1 + 0x20))->unk12 =
            (((Unkstruct_800B5CB8 *)*(s32 *)((s32)param_1 + 0x20))->unk12 + v0) & 0xFFF;
        cur = ((Unkstruct_800B5CB8 *)param_1)->unk90;
        target = D_801E37E8[((Unkstruct_800B5CB8 *)param_1)->unk70];
        if (cur != target) {
            guess_StartActorSequence((s32)param_1, target);
        }
        break;
    }
    case 1: {
        s32 v0 = func_8012BA10((s32)param_1, 0x10);
        s32 cur;
        s32 target;
        ((Unkstruct_800B5CB8 *)*(s32 *)((s32)param_1 + 0x20))->unk12 =
            (((Unkstruct_800B5CB8 *)*(s32 *)((s32)param_1 + 0x20))->unk12 + v0) & 0xFFF;
        cur = ((Unkstruct_800B5CB8 *)param_1)->unk90;
        target = D_801E37DC[((Unkstruct_800B5CB8 *)param_1)->unk70];
        if (cur != target) {
            guess_StartActorSequence((s32)param_1, target);
        }
        break;
    }
    case 2: {
        s32 v0 = func_8012B608(*(s16 *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12), 0x600, 8);
        s32 cur;
        s32 target;
        ((Unkstruct_800B5CB8 *)*(s32 *)((s32)param_1 + 0x20))->unk12 =
            (((Unkstruct_800B5CB8 *)*(s32 *)((s32)param_1 + 0x20))->unk12 + v0) & 0xFFF;
        cur = ((Unkstruct_800B5CB8 *)param_1)->unk90;
        target = D_801E37DC[((Unkstruct_800B5CB8 *)param_1)->unk70];
        if (cur != target) {
            guess_StartActorSequence((s32)param_1, target);
        }
        break;
    }
    case 3: {
        s32 cur = ((Unkstruct_800B5CB8 *)param_1)->unk90;
        s32 target = D_801E37F4[((Unkstruct_800B5CB8 *)param_1)->unk70];
        if (cur != target) {
            guess_StartActorSequence((s32)param_1, target);
        }
        break;
    }
    }

    if (((Unkstruct_800B5CB8 *)param_1)->unk70 == 0) {
        if (func_801789AC((s32)param_1) != 0) {
            func_80178D18((s32)param_1);
            ((Unkstruct_800B5CB8 *)param_1)->unk70 = 2;
        }
    }
}



extern s32 guess_GetStoryProgress(void);
extern s32 guess_SpawnActor(s32 a0, s32 a1, s32 a2);
extern s32 guess_AllocModelObject(void);
extern void guess_FreeActorDuringSpawn(void *a0);
extern void guess_InitModelObject(s32 a0, s32 a1);
extern void guess_StartActorSequence(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(u8 *a0);
extern s32 func_80178B18(s32 a0, s32 a1);


void func_801E3290(void *a0) {

    extern s32 D_801E9E3C;
    extern s32 D_801E9E38;
    extern s32 D_801E37D0[];
    extern s32 D_801E37B8[][2];
    extern s32 D_801E37E8[];
    extern s32 D_801E389C;
    s32 v0;
    s32 cur;
    s32 target;

    if ((u32)(guess_GetStoryProgress() - 0x122) >= 0xA) {
        guess_FreeActorDuringSpawn(a0);
        return;
    }

    if (((Unkstruct_800B5CB8 *)a0)->unk70 == 0) {
        D_801E9E3C = guess_SpawnActor(0x1C1, 1, 0);
        D_801E9E38 = guess_SpawnActor(0x1C1, 2, 0);
    }

    v0 = guess_AllocModelObject();
    ((Unkstruct_800B5CB8 *)a0)->unk20 = v0;
    if (v0 == 0) {
        guess_FreeActorDuringSpawn(a0);
        return;
    }

    guess_InitModelObject(v0, D_801E37D0[((Unkstruct_800B5CB8 *)a0)->unk70]);
    *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk68 + 0xC) = 0x7FFF;
    func_8012E8E0((s32)a0, (s32)&D_801E37B8[((Unkstruct_800B5CB8 *)a0)->unk70]);
    ((Unkstruct_800B5CB8 *)a0)->unk2 = 1;
    func_8012E8E0((s32)a0, (s32)&D_801E37B8[((Unkstruct_800B5CB8 *)a0)->unk70]);
    func_8012E88C((u8 *)a0);

    cur = ((Unkstruct_800B5CB8 *)a0)->unk90;
    target = D_801E37E8[((Unkstruct_800B5CB8 *)a0)->unk70];
    if (cur != target) {
        guess_StartActorSequence((s32)a0, target);
    }

    if (((Unkstruct_800B5CB8 *)a0)->unk70 != 0) {
        func_80178B18((s32)a0, (s32)&D_801E389C);
    }
}




void func_801E33E8(void *a0) {

    extern void (*D_801E39AC[])(void);
    D_801E39AC[((Unkstruct_80126B58 *)a0)->unk2]();
}


void func_801E3424(s32 param_1) {
    extern s32 D_801E9E38;
    extern s32 D_801E9E3C;
    struct S_801E3424 { u8 pad[0xFC]; s16 f; } *a, *b;
    a = (struct S_801E3424 *) D_801E9E38;
    b = (struct S_801E3424 *) D_801E9E3C;
    *(s16 *)(param_1 + 0xFC) = 1;
    a->f = 0;
    b->f = 0;
}


extern s32 D_801E9E38;
extern s32 D_801E9E3C;

void func_801E3448(a0_)
s32 a0_;
{

    extern s32 D_801E9E38;
    extern s32 D_801E9E3C;

    s32 c = 1;
    s32 a0 = a0_;
    s32 p1 = D_801E9E38;

    *(s16 *)((s32)a0 + 0xFC) = 0;
    a0 = D_801E9E3C;
    do { ((Unkstruct_800B5CB8 *)p1)->unkFC = c; } while (0);
    *(s16 *)((s32)a0 + 0xFC) = 0;
}


void func_801E346C(s32 a0_) {

    extern s32 D_801E9E38;
    extern s32 D_801E9E3C;

    s32 c = 2;
    s32 a0 = a0_;
    s32 p1 = D_801E9E38;

    *(s16 *)((s32)a0 + 0xFC) = 0;
    a0 = D_801E9E3C;
    do { ((Unkstruct_800B5CB8 *)p1)->unkFC = c; } while (0);
    *(s16 *)((s32)a0 + 0xFC) = 0;
}


void func_801E3490(s32 arg0) {
    extern s32 D_801E9E38;
    extern s32 D_801E9E3C;
    s32 ptr1 = D_801E9E38;
    s32 ptr2 = D_801E9E3C;
    *(s16 *)(arg0 + 0xFC) = 0;
    ((Unkstruct_800B5CB8 *)ptr1)->unkFC = 0;
    ((Unkstruct_800B5CB8 *)ptr2)->unkFC = 1;
}


void func_801E34B4(s32 param_1) {
    extern s32 D_801E9E38;
    extern s32 D_801E9E3C;
    s32 ptr1 = D_801E9E38;
    s32 ptr2 = D_801E9E3C;

    *(s16 *)(param_1 + 0xFC) = 0;
    ((Unkstruct_800B5CB8 *)ptr1)->unkFC = 0;
    ((Unkstruct_800B5CB8 *)ptr2)->unkFC = 0;
}


void func_801E34D4(s32 arg0) {
    extern s32 D_801E9E38;
    extern s32 D_801E9E3C;
    Unkstruct_800B5CB8 *p = (Unkstruct_800B5CB8 *)D_801E9E38;
    ((Unkstruct_800B5CB8 *)arg0)->unkFC = 1;
    {
        Unkstruct_800B5CB8 *q = (Unkstruct_800B5CB8 *)D_801E9E3C;
        p->unkFC = 3;
        q->unkFC = 3;
    }
}


#define SHARED_FN func_801E34FC
#include "../shared/multi/cls_007c9ae9fe6e.h"
#undef SHARED_FN




extern void guess_SetGameFlag(s32 arg0, s32 arg1);
#define SHARED_FN func_801E3538
#include "../shared/multi/cls_09920ec2ce21.h"
#undef SHARED_FN


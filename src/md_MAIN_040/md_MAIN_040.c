#include "common.h"

#include "common.h"

extern s32 func_800183E0(s32 a0);

void func_800CAE0C(void) {
    extern s32 D_800CB9F4;
    extern s32 D_800CB9B4;

    func_800183E0((s32)&D_800CB9F4);
    func_800183E0((s32)&D_800CB9B4);
}




void func_800CAE44(void *a0) {

    extern void (*D_800CB8C8[])(void);
    ((Unkstruct_800CAE34 *)a0)->unk44 |= 8;
    D_800CB8C8[((Unkstruct_800CAE34 *)a0)->unk197]();
}


extern s32 func_80161104(void);
extern void func_800CAED0(u8 *a0);
#include "../shared/slot_800CAE08/func_800CAE88__34360208.h"


extern void guess_SetAnimScript(s32 *a0, s32 a1);
extern void func_801655E4(void *a0);
extern M2C_UNK D_800D57F4;

#define SHARED_FN func_800CAED0
#include "../shared/slot_800CAE08/cls_957305eb2210.h"
#undef SHARED_FN


#include "common.h"

extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void guess_SpawnObject(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 a4, s32 a5, s32 a6, s32 a7);
extern s32 func_80161208();  /* canonical no-proto */

void func_800CAF18(void *a0) {
    u16 flag;

    flag = ((Unkstruct_80126B58 *)a0)->unkB8;
    if (flag == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        if (flag & 0x4000) {
            guess_SpawnObject(0x20, (s32)a0, 0, -0x40, 0, 0, 0, 0);
        }
        if (func_80161208(a0) == 0) {
            ((Unkstruct_80126B58 *)a0)->unk44 |= 2;
        }
    }
}


#define SHARED_FN func_800CAFB0
#include "../shared/slot_800CAE08/cls_a0930d00ac46.h"
#undef SHARED_FN


#include "common.h"

extern u8 D_80078EC1;
extern void (*D_800CB8D4[])(void);
extern void guess_FreeObjectAndSubObject_6(void);

void func_800CAFC4(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x1D) {
        index = *(u16 *)(a0 + 2);
        D_800CB8D4[index]();

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))guess_FreeObjectAndSubObject_6)(a0);
    } else {
        ((void (*)(s32))guess_FreeObjectAndSubObject_6)(a0);
    }
}


void func_800CB038(void *a0) {
    extern s32 D_800CBD74;
    extern s32 func_8014659C(void);
    extern void guess_InitModelObject(s32 a0, s32 a1);
    extern void guess_TransformPosByObjMatrix(s32 a0, s32 a1);
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
    extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
    extern void guess_PlaySoundUnlessSkipped(s32 a0);
    extern void guess_NextStep(void *a0);
    extern void guess_FreeObjectAndSubObject_6(void);

    void *s2 = *(void **)((s32)a0 + 0x4C);
    s32 s1 = ((s32 (*)(void))func_8014659C)();
    ((Unkstruct_80126B58 *)a0)->unk20 = s1;
    if (s1 != 0) {
        guess_InitModelObject(s1, (s32)&D_800CBD74);
        *(u16 *)(s1 + 0x12) = *(u16 *)(((Unkstruct_80126B58 *)s2)->unk20 + 0x12);
        guess_TransformPosByObjMatrix((s32)s2, (s32)a0 + 4);
        func_80146DE8((s32 *)a0, 0, -0xC0000, -0x100000);
        guess_SetWaitTimer_2((s32 *)a0, 100);
        memcpy((void *)((s32)a0 + 0x58), (void *)(s1 + 0x10), 8);
        ((Unkstruct_80126B58 *)a0)->unk60 = 2;
        guess_PlaySoundUnlessSkipped(0x8F3);
        guess_NextStep(a0);
    } else {
        ((void (*)(s32))guess_FreeObjectAndSubObject_6)(a0);
    }
}


void func_800CB114(void *a0) {
    extern void func_80162FF4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80162FC0(s32 a0);
    extern s32 guess_TickWaitTimer_2(s32 a0);
    extern void guess_FreeObjectAndSubObject_6(void);
    extern s32 func_80163950(s32 a0);
    extern s32 func_801638A0(s32 a0, s32 *a1);
    extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
    extern void guess_PlaySoundUnlessSkipped(s32 a0);
    extern void guess_NextStep(void *a0);
    extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80163328(s32 a0);
    extern s32 func_801632F0(s32 a0);
    extern void func_80162D28(s32 a0);

    s32 vec[2];
    s32 save[2];
    void *obj;
    s32 f;
    s32 w;

    obj = CAST_SIGN(void *, (s32)a0, 0x20);
    memcpy(save, (void *)(obj + 0x10), 8);
    memcpy((void *)(obj + 0x10), (void *)((s32)a0 + 0x58), 8);
    func_80162FF4((s32)a0, 0, 0x20000, 0);
    func_80162FC0((s32)a0);
    *(u16 *)save = *(u16 *)save + 0x71;
    *(u16 *)((s32)save + 4) = *(u16 *)((s32)save + 4) + 0x71;
    memcpy((void *)(obj + 0x10), save, 8);
    if (guess_TickWaitTimer_2((s32)a0) != 0) {
        ((void (*)(s32))guess_FreeObjectAndSubObject_6)(a0);
        return;
    }
    f = (func_80163950((s32)a0) != 0) << 13;
    f |= func_801638A0((s32)a0, vec);
    if (f == 0) {
        goto L274;
    }
    if ((f & 0x6000) == 0) {
        goto L250;
    }
    w = ((Unkstruct_80126B58 *)a0)->unk60;
    w = w - 1;
    ((Unkstruct_80126B58 *)a0)->unk60 = w;
    if ((s16)w == -1) {
        goto L250;
    }
    {
        s32 v = ((Unkstruct_80126B58 *)a0)->unk28;
        ((Unkstruct_80126B58 *)a0)->unk28 = -(v / 2);
    }
    goto L274;
L250:
    guess_SetWaitTimer_2((s32 *)a0, 8);
    guess_PlaySoundUnlessSkipped(0x8E7);
    guess_NextStep(a0);
    return;
L274:
    func_80163408((s32)a0, 0x2A, 0, 0x20);
    func_80163328((s32)a0);
    f = func_801632F0((s32)a0);
    if (f == 2) {
        goto L2E4;
    }
    if ((u32)f < 3) {
        if (f == 1) {
            goto L2CC;
        }
        goto L2E4;
    }
    if (f != 4) {
        goto L2E4;
    }
L2CC:
    guess_SetWaitTimer_2((s32 *)a0, 8);
    guess_PlaySoundUnlessSkipped(0x8E7);
    guess_NextStep(a0);
L2E4:
    func_80162D28((s32)a0);
}


void func_800CB304(void *a0) {
    extern s32 guess_SpawnSmallObject(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern s32 guess_TickWaitTimer_2(s32 a0);
    extern void guess_NextStep(void *a0);
    extern void func_800CB3DC(void *a0);
    s32 pad[2];
    s32 var_s2;
    s32 i;

    if (pad == NULL) {}
    var_s2 = ((Unkstruct_80126B58 *)a0)->unk20;
    for (i = 0; i < 6; i++) {
        guess_SpawnSmallObject(0x4D, a0, ((Unkstruct_80126B58 *)a0)->unk6, ((Unkstruct_80126B58 *)a0)->unkA,
                      ((Unkstruct_80126B58 *)a0)->unkE, i, 1);
    }
    if (guess_TickWaitTimer_2((s32)a0) != 0) {
        guess_NextStep(a0);
    } else {
        u16 var_v0;
        var_v0 = *(u16 *)(var_s2 + 0x1C);
        var_v0 = var_v0 - 0x80;
        *(u16 *)(var_s2 + 0x1C) = var_v0;
        *(u16 *)(var_s2 + 0x1A) = var_v0;
        *(u16 *)(var_s2 + 0x18) = var_v0;
        func_800CB3DC(a0);
    }
}


extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D58)
/* guess_FreeObjectAndSubObject_6: zeroes object a0 (0x68 bytes) and its +0x20 sub-object (0x84 bytes when that one's first halfword is 1, else 0x38)
 * Confidence medium, code inference: func_80162CCC(a0): p = +0x20; p -> guess_ZeroMemory(p, *p == 1 ? 0x84 : 0x38); guess_ZeroMemory(a0, 0x68); spawn steps call it when allocation fails
 * Names ledger: config/names.tsv guess_FreeObjectAndSubObject_6 */
void guess_FreeObjectAndSubObject_6(void) {
    func_80162CCC();
}


#include "common.h"

extern u8 guess_g_ObjectTable[];
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);

void func_800CB3DC(s32 a0) {
    u8 *p;
    s16 buf[4];
    p = guess_g_ObjectTable;
    if (p < p + 0x6480) {
        do {
            if (func_8014C308(a0, (s32)p, 0x2A, 0x20) != 0) {
                if (func_8014C278(a0, (s32)p, 0x80) != 0) {
                    func_80015978((s32)(p + 4), (s32 *)buf);
                    buf[3] = 0;
                    func_8014C3A4((void *)a0, (s32)p, 0x2A, (s32)buf);
                }
            }
            p += 0x10C;
        } while (p < guess_g_ObjectTable + 0x6480);
    }
}



extern s32 guess_FreeSmallObject();  // K&R: 0 of 1 args (P37 rung D t4_D58)

void func_800CB488(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB948[])(void);
    if (D_80078EC1 == 0x1d) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB948[v0]();
    } else {
        guess_FreeSmallObject();
    }
}


    /* 8B, align 2 -> lwl/lwr+swl/swr copy */
  /* 0x20, align 4 */
     /* 0x10, align 4 -> plain lw/sw copy */

extern void *guess_AllocSpriteObject(void);
extern void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3);
extern void guess_StartPairSequence(s32 a0, s32 a1, s32 a2);
extern void RotMatrixZYX(s32 a0, s32 a1);
extern void ApplyMatrixLV(s32 a0, s32 a1, s32 a2);
extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
extern s32 guess_FreeSmallObject();  // K&R: 0 of 1 args (P37 rung D t4_D58)
extern int rand(void);

extern u8 D_800CB8EC[];
extern u8 D_800CB8F8[];
extern SV_800CB4E4 D_800CB954[];
extern V32_800CB4E4 D_800CB984;

void func_800CB4E4(s32 param_1) {
    SV_800CB4E4 rot;
    MTX_800CB4E4 m;
    V32_800CB4E4 vel;
    s32 obj;
    s32 node;

    obj = ((s32 (*)(void))guess_AllocSpriteObject)();
    ((Unkstruct_80126B58 *)param_1)->unk20 = obj;

    if (((Unkstruct_80126B58 *)param_1)->unk20 != 0) {
        func_8001CC3C(obj, D_800CB8EC, 0, 0);
        node = obj;
        *(u8 *)(node + 0x27) = 0x90;
        *(u16 *)(node + 0x18) = *(u16 *)(node + 0x1a) = 0x3000;
        *(s32 *)(node + 0x4) |= 0x50000000;
        guess_StartPairSequence(node, param_1 + 0x24, (s32)D_800CB8F8);

        vel = D_800CB984;
        rot = D_800CB954[((Unkstruct_80126B58 *)param_1)->unk2C];

        if (((Unkstruct_80126B58 *)param_1)->unk30 != 0) {
            rot.vx += ((rand() & 0x3f) << 4) - 0x200;
            rot.vy += ((rand() & 0x3f) << 4) - 0x200;
            rot.vz += ((rand() & 0x3f) << 4) - 0x200;
            vel.vx = ((rand() & 0x1f) - 0x10) * 3 << 15;
            vel.vy = ((rand() & 0x1f) - 0x10) * 3 << 15;
            vel.vz = ((rand() & 0x1f) - 0x10) * 3 << 15;
        }

        RotMatrixZYX((s32)&rot, (s32)&m);
        ApplyMatrixLV((s32)&m, (s32)&vel, (s32)&vel);

        ((Unkstruct_80126B58 *)param_1)->unk10 = vel.vx;
        ((Unkstruct_80126B58 *)param_1)->unk14 = vel.vy;
        ((Unkstruct_80126B58 *)param_1)->unk18 = vel.vz;

        guess_SetWaitTimer_2((s32 *)param_1, 4);
        ((Unkstruct_80126B58 *)param_1)->unk2 = ((Unkstruct_80126B58 *)param_1)->unk2 + 1;
    } else {
        ((void (*)(s32))guess_FreeSmallObject)(param_1);
    }
}


extern s32 guess_StepPairSequence(s32 param_1, s32 *param_2);
extern void func_800CB840(s32 param_1);
extern void func_800CB8A8(void*, s16);
extern s32 guess_TickWaitTimer_2(s32 param_1);
extern void guess_SetWaitTimer_2(s32 *param_1, s32 param_2);

void func_800CB710(s32 param_1) {
    s32 node;

    node = ((Unkstruct_80126B58 *)param_1)->unk20;
    guess_StepPairSequence(node, (s32 *)(param_1 + 0x24));
    *(u8 *)(node + 0x27) = CAST_WIDTH(u8, param_1, 0x28) - 0x70;
    func_800CB840(param_1);
    ((void (*)(s32, s32))func_800CB8A8)(param_1, 0x30);
    if (guess_TickWaitTimer_2(param_1) != 0) {
        ((Unkstruct_80126B58 *)param_1)->unk10 = ((Unkstruct_80126B58 *)param_1)->unk10 >> 2;
        ((Unkstruct_80126B58 *)param_1)->unk14 = ((Unkstruct_80126B58 *)param_1)->unk14 >> 2;
        ((Unkstruct_80126B58 *)param_1)->unk18 = ((Unkstruct_80126B58 *)param_1)->unk18 >> 2;
        guess_SetWaitTimer_2((s32 *)param_1, 8);
        ((Unkstruct_80126B58 *)param_1)->unk2 = ((Unkstruct_80126B58 *)param_1)->unk2 + 1;
    }
}


extern s32 guess_StepPairSequence(s32 param_1, s32 *param_2);
extern void func_800CB840(s32 param_1);
extern void func_800CB8A8(void*, s16);
extern s32 guess_TickWaitTimer_2(s32 param_1);
extern s32 guess_FreeSmallObject();  // K&R: 0 of 1 args (P37 rung D t4_D58)
extern void func_800CB874(s32 param_1);

void func_800CB7B8(s32 param_1) {
    s32 p;
    s32 node;

    p = param_1;
    node = ((Unkstruct_800CB7B8 *)p)->unk20;
    func_800CB874(param_1);
    guess_StepPairSequence(node, (s32 *)(p + 0x24));
    *(u8 *)(node + 0x27) = ((Unkstruct_800CB7B8 *)p)->unk28 - 0x70;
    ((void (*)(s32, s32))func_800CB8A8)((void *)p, 0x40);
    ((Unkstruct_800CB7B8 *)p)->unk14 -= 0x4000;
    func_800CB840(p);
    if (guess_TickWaitTimer_2(p) != 0) {
        ((void (*)(s32))guess_FreeSmallObject)(p);
    }
}


void func_800CB840(s32 param_1) {
    CAST_WIDTH(s32, param_1, 0x4) += ((Unkstruct_80126B58 *)param_1)->unk10;
    CAST_WIDTH(s32, param_1, 0x8) += ((Unkstruct_80126B58 *)param_1)->unk14;
    CAST_WIDTH(s32, param_1, 0xC) += ((Unkstruct_80126B58 *)param_1)->unk18;
}


void func_800CB874(s32 arg0)
{
    u8 *p;
    s16 t;
    s16 d;
    u8 x;

    p = CAST_SIGN(u8 *, arg0, 0x20);
    t = p[0x24];
    d = t - 4;
    if (d < 0)
        t = 0;
    else
        t = d;
    x = t;
    p[0x26] = x;
    p[0x25] = x;
    p[0x24] = x;
}


void func_800CB8A8(void *arg0, s16 arg1) {
    u16 *ptr = *(u16 **)((s32)arg0 + 0x20);
    ptr[13] = ptr[13] - arg1;
    ptr[12] = ptr[13];
}


#include "common.h"

extern s32 guess_AllocRenderWorkRecord(s32 *a0);
void func_800CAE14(void) {

    extern s32 D_800CBF60;
    extern s32 D_800CBF20;
    guess_AllocRenderWorkRecord(&D_800CBF60);
    guess_AllocRenderWorkRecord(&D_800CBF20);
}




void func_800CAE4C(void *a0) {

    extern void (*D_800CBE34[])(void);
    ((Unkstruct_800CAE34 *)a0)->unk44.u |= 8;
    D_800CBE34[((Unkstruct_800CAE34 *)a0)->unk197]();
}


extern s32 func_80161104(void);
extern void func_800CAED8(u8 *a0);
void func_800CAE90(u8 *a0) {
    if (func_80161104()) {
        func_800CAED8(a0);
        ((Unkstruct_80126B58 *)a0)->unk197 = ((Unkstruct_80126B58 *)a0)->unk197 + 1;
    }
}


void func_800CAED8(u8 *a0) {
    extern s32 D_8011F9D0;
    extern M2C_UNK D_800D57F4;
    extern void guess_SetAnimScript(s32 *a0, s32 a1);
    extern void func_801655E4(void *a0);
    extern void func_801599A4(void *a0);
    extern void func_80159B3C(void *a0);
    s32 count = 0;
    s32 i;

    for (i = 0; i < 0x14; i++) {
        if (*(u16 *)((s32)&D_8011F9D0 + i * 0x68) == 0x25) {
            count++;
        }
    }

    if (count >= 6) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        guess_SetAnimScript((s32 *)a0, &D_800D57F4);
        func_801655E4(a0);
        ((Unkstruct_80126B58 *)a0)->unk197 = ((Unkstruct_80126B58 *)a0)->unk197 + 1;
    }
}


extern s32 D_80062BE8;
extern s32 guess_SpawnObject(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void guess_StartPadVibration(void *a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80161208(void *a0);

void func_800CAF80(void *a0) {
    u16 flag;

    flag = ((Unkstruct_80126B58 *)a0)->unkB8.u;
    if (flag == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        if (flag & 0x4000) {
            guess_SpawnObject(0x25, (s32)a0, 0, -0x40, 0, 1, 0, 0);
            guess_StartPadVibration(&D_80062BE8);
        }
        if (func_80161208(a0) == 0) {
            CAST_SIGN(s32, (u8 *)a0, 0x44) |= 2;
        }
    }
}


#define SHARED_FN func_800CB02C
#include "../shared/slot_800CAE08/cls_a0930d00ac46.h"
#undef SHARED_FN


extern u8 D_80078EC1;
extern void (*D_800CBE40[])(void);
extern void guess_FreeObjectAndSubObject_10(void);

void func_800CB040(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x1C) {
        index = *(u16 *)(a0 + 2);
        D_800CBE40[index]();

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))guess_FreeObjectAndSubObject_10)(a0);
    } else {
        ((void (*)(s32))guess_FreeObjectAndSubObject_10)(a0);
    }
}


extern s32 func_8014659C(void);
extern void guess_NextStep(void *a0);
extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
extern void guess_TransformPosByObjMatrix(s32 a0, s32 a1);
extern void guess_FreeObjectAndSubObject_10(void);


void func_800CB0B4(s32 param_1) {
    extern void guess_InitModelObject(s32 a0, s32 a1);
    extern s32 D_800CC444;

    s32 iVar2 = *(s32 *)(param_1 + 0x4c);
    s32 obj;

    obj = ((s32 (*)(void))func_8014659C)();
    ((Unkstruct_80126B58 *)param_1)->unk20.val = obj;
    if (obj != 0) {
        guess_InitModelObject(obj, (s32)&D_800CC444);
        *(u16 *)(obj + 0x10) = ((Unkstruct_80126B58 *)iVar2)->unk20.m->head.unk10.w.unk10.u;
        {
            s32 prod;
            prod = (((Unkstruct_80126B58 *)param_1)->unk50 - 1) * 0x155;
            *(u16 *)(obj + 0x12) =
                (((Unkstruct_80126B58 *)iVar2)->unk20.m->head.unk10.w.unk12.u + prod) & 0xFFF;
        }
        *(u16 *)(obj + 0x14) = ((Unkstruct_80126B58 *)iVar2)->unk20.m->head.unk10.w.unk14.u;
        CAST_WIDTH(u16, param_1, 0x58) = ((Unkstruct_80126B58 *)iVar2)->unk100;
        *(u16 *)(param_1 + 0x5A) = ((Unkstruct_80126B58 *)iVar2)->unk102;
        CAST_WIDTH(u16, param_1, 0x5C) = ((Unkstruct_80126B58 *)iVar2)->unk104;
        guess_TransformPosByObjMatrix(iVar2, param_1 + 4);
        {
            s32 dstp;
            s32 srcp;
            dstp = ((Unkstruct_80126B58 *)param_1)->unk20.val;
            srcp = ((Unkstruct_80126B58 *)iVar2)->unk20.val;
            *(Blk16_956C *)(dstp + 0x34) = *(Blk16_956C *)(srcp + 0x34);
            *(Blk16_956C *)(dstp + 0x44) = *(Blk16_956C *)(srcp + 0x44);
        }
        func_80146DE8(param_1, 0, 0, 0xFFF00000);
        func_800CB4CC((void *)param_1);
        guess_SetWaitTimer_2((s32 *)param_1, 0x28);
        guess_PlaySoundUnlessSkipped(0x8E8);
        guess_NextStep((void *)param_1);
    } else {
        ((void (*)(s32))guess_FreeObjectAndSubObject_10)(param_1);
    }
}


extern void guess_NextStep(void *a0);
extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
extern s32  guess_TickWaitTimer_2(s32 a0);
extern s32  guess_SpawnSmallObject(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void guess_SetStep(s32 *a0, s32 a1);
extern void guess_PlaySoundUnlessSkipped(s32 a0);
extern s32  func_800CB6F4(int param_1, int param_2);
extern void func_800CB5CC(void *a0);
extern s32  func_800CB4D4(s32 a0);
extern void func_80013F3C(void *a0);
extern void func_80012558(void *a0, s32 a1);
extern void func_800126C4(void *a0, s32 a1);
extern void func_800123F0(void *a0, s32 a1);
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern void guess_AddVelocityToPos_2(s32 a0);
extern s32  func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328(s32 a0);
extern s32  func_801632F0(s32 a0);



void func_800CB228(s32 param_1) {
    s32 *obj;
    Mtx40 m;

    obj = CAST_SIGN(s32 *, param_1, 0x20);
    if (KR_AS(s32, func_800CB6F4)(param_1) == 0) {
        guess_SetStep((s32 *)param_1, 3);
        return;
    }
    func_800CB5CC((void *)param_1);
    func_80013F3C(&m);
    func_80012558(&m, *(s16 *)(param_1 + 0x5A));
    func_800126C4(&m, CAST_WIDTH(s16, param_1, 0x58));
    func_800123F0(&m, CAST_WIDTH(s16, param_1, 0x5C));
    func_80012558(&m, *(s16 *)((s8 *)obj + 0x12));
    func_800126C4(&m, *(s16 *)((s8 *)obj + 0x10));
    func_800123F0(&m, *(s16 *)((s8 *)obj + 0x14));
    func_80163194(param_1, 0, 0, -0x3000, &m);
    guess_AddVelocityToPos_2(param_1);
    *(Blk16_956C *)((s8 *)obj + 0x34) = *(Blk16_956C *)&m.w[0];
    *(Blk16_956C *)((s8 *)obj + 0x44) = *(Blk16_956C *)&m.w[4];
    if (guess_TickWaitTimer_2(param_1) != 0) {
        guess_SetWaitTimer_2((s32 *)param_1, 8);
        guess_NextStep((void *)param_1);
        return;
    }
    if (((Unkstruct_80126B58 *)param_1)->unk1C == 0x27) {
        ((Unkstruct_80126B58 *)param_1)->unk54 = func_800CB4D4(param_1);
    }
    func_800CB5CC((void *)param_1);
    func_80163408(param_1, 0x2B, 0, 0x40);
    func_80163328(param_1);
    switch ((u32)func_801632F0(param_1)) {
    case 1:
    case 2:
    case 4:
        guess_SetWaitTimer_2((s32 *)param_1, 4);
        obj[1] |= 0x80000000;
        guess_PlaySoundUnlessSkipped(0xA7D);
        guess_NextStep((void *)param_1);
        return;
    }
    if ((((Unkstruct_80126B58 *)param_1)->unk1C & 1) == 0) {
        guess_SpawnSmallObject(0x50, (void *)param_1, 0, 0, 0x20, 0, 0);
    }
}


extern s32 guess_TickWaitTimer_2(s32 a0);
extern void guess_NextStep(void *a0);
extern s32 guess_SpawnSmallObject(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_800CB424(void *a0)
{
    s32 i;

    if (guess_TickWaitTimer_2((s32)a0) != 0) {
        guess_NextStep(a0);
        return;
    }
    for (i = 0; i < 4; i++) {
        guess_SpawnSmallObject(0x4E, a0, ((Unkstruct_80126B58 *)a0)->unk6.s, ((Unkstruct_80126B58 *)a0)->unkA.s,
                      ((Unkstruct_80126B58 *)a0)->unkE.s, i, 1);
    }
}


extern void guess_ClearObjectAndSubObject(u8 *);
/* guess_FreeObjectAndSubObject_10: zeroes object a0 (0x68 bytes) and its +0x20 sub-object (0x84 bytes when that one's first halfword is 1, else 0x38)
 * Confidence medium, code inference: guess_ClearObjectAndSubObject(a0): p = +0x20; p -> guess_ZeroMemory(p, *p == 1 ? 0x84 : 0x38); guess_ZeroMemory(a0, 0x68); spawn steps call it when allocation fails
 * Names ledger: config/names.tsv guess_FreeObjectAndSubObject_10 */
void guess_FreeObjectAndSubObject_10(void) {
    KR_AS(void, guess_ClearObjectAndSubObject)();
}


void func_800CB4CC(void *a0)
{
    ((Unkstruct_80126B58 *)a0)->unk54 = 0;
}


#include "common.h"

s32 func_800CB4D4(s32 a0) {
    extern u8 guess_g_ObjectTable[]; // Names ledger: config/names.tsv guess_g_ObjectTable
    extern u8 guess_g_BoxHitCenterX[]; // Names ledger: config/names.tsv guess_g_BoxHitCenterX
    extern void guess_CopyVec3HighHalves(s32 a0, s32 *a1);
    extern s32 func_8012E778(s32 a0, s32 a1);
    extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_80013328(s32 *a0, s32 *a1);

    u8 *p;
    u8 *q;
    s32 buf[2];
    s32 best;
    u8 *bestp;
    s16 r;

    bestp = 0;
    best = 0x7FFFFFFF;
    p = guess_g_ObjectTable;
    while (p < guess_g_ObjectTable + 0x6480) {
        if (((Unkstruct_801202A0 *)p)->unk0 != 0x282) {
            q = p + 4;
            guess_CopyVec3HighHalves((s32)q, buf);
            if (func_8012E778((s32)p, 0x8C00B4) == 1) {
                if (func_8014C308(a0, (s32)p, 0x2B, 0x40) != 0) {
                    r = func_80013328((s32 *)(a0 + 4), (s32 *)q);
                    if (r < best) {
                        best = r;
                        bestp = p;
                    }
                }
            }
        }
        p += 0x10C;
    }
    return (s32)bestp;
}


void func_800CB5CC(void *a0) {
    if (((Unkstruct_80126B58 *)a0)->unk54 != 0) {
        if (func_8014C308((s32)a0, ((Unkstruct_80126B58 *)a0)->unk54, 0x2B, 0x40) != 0) {
            func_800CB61C(a0, ((Unkstruct_80126B58 *)a0)->unk54);
        }
    }
}


void func_800CB61C(s32 a0, s32 a1)
{
    extern u8 D_800CAE0C[8];
    extern s32 func_8014C5FC(s32, s32, void *);
    extern s32 func_8014C59C(void *, void *);
    extern s32 func_80012DBC(s32, s32, s32, s32);

    s32 s2 = ((Unkstruct_80126B58 *)a0)->unk20.val;
    Blk8 buf;
    s32 r1, r2, x, y;

    buf = *(Blk8 *)D_800CAE0C;
    if (*(u16 *)a1 == 0x2CE) {
        buf.vy = -0x1AB;
    }
    r1 = func_8014C59C((void *)a0, (void *)a1);
    x = func_80012DBC(*(s16 *)(s2 + 0x12), (s16)r1, 0x10, 1);
    *(s16 *)(s2 + 0x12) = x;
    r2 = func_8014C5FC(a0, a1, &buf);
    y = func_80012DBC(*(s16 *)(s2 + 0x10), (s16)r2, 0x10, 1);
    *(s16 *)(s2 + 0x10) = y;
}







extern u8 guess_g_CameraWsMatrix; // Names ledger: config/names.tsv guess_g_CameraWsMatrix

s32 func_800CB6F4(int param_1, int param_2)
{
    u8 *r0;
    int iVarX;
    int iVarY;
    int sp[6];
    sp[0] = (int)((Unkstruct_80126B58 *)param_1)->unk6.s;
    sp[1] = (int)((Unkstruct_80126B58 *)param_1)->unkA.s;
    sp[2] = (int)((Unkstruct_80126B58 *)param_1)->unkE.s;
    r0 = &guess_g_CameraWsMatrix;
    gte_SetRotMatrix(r0);
    gte_SetTransMatrix(r0);
    gte_ldlv0(sp);
    gte_rtps();
    gte_stsxy((int *)sp + 4);
    iVarX = *(short *)((int)sp + 0x10);
    if (iVarX >= 0) {
        if (iVarX < 0xAB) goto cy;
        goto ret0;
    }
    if (-iVarX >= 0xAB) goto ret0;
cy:
    iVarY = *(short *)((int)sp + 0x12);
    if (iVarY >= 0) {
        if (iVarY < 0x81) goto c1;
        goto ret0;
    }
    if (-iVarY >= 0x81) goto ret0;
c1:
    return 1;
ret0:
    return 0;
}



extern s32 guess_FreeSmallObject(u8 *a0);

void func_800CB804(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBEAC[])(void);
    if (D_80078EC1 == 0x1c) {
        u16 v0 = ((Unkstruct_8011D030 *)arg0)->unk2.u;
        D_800CBEAC[v0]();
    } else {
        KR_AS(s32, guess_FreeSmallObject)();
    }
}



extern void *guess_AllocSpriteObject(void);
extern void func_8001CC3C(s32, s32, s32, s32);
extern void guess_StartPairSequence(s32 a0, s32 a1, s32 a2);
extern s32 guess_FreeSmallObject(u8 *a0);
extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
extern MATRIX *RotMatrixZYX(s32 a0, s32 a1);
extern VECTOR *ApplyMatrixLV(s32 a0, s32 a1, s32 a2);
extern int rand(void);

extern SV D_800CBE50[];
extern u8 D_800CBE5C[];
extern V32 D_800CBEE8;
extern SV D_800CBEB8[];

void func_800CB860(s32 param_1) {
    SV rot;
    MTX_md_MAIN_039 m;
    V32 vel;
    s32 p;
    s32 pb;

    p = ((s32 (*)(void))guess_AllocSpriteObject)();
    pb = p;
    ((Unkstruct_80126B58 *)param_1)->unk20.val = p;

    if (p != 0) {
        ((void (*)(s32, void *, s32, s32))func_8001CC3C)(p, D_800CBE50, 0, 0);
        *(u8 *)(p + 0x27) = 0x90;
        *(s16 *)(p + 0x18) = *(s16 *)(p + 0x1a) = 0x2000;
        *(s32 *)(p + 4) |= 0x50000000;
        guess_StartPairSequence(p, param_1 + 0x24, D_800CBE5C);

        vel = D_800CBEE8;
        rot = D_800CBEB8[((Unkstruct_80126B58 *)param_1)->unk2C];

        if (((Unkstruct_80126B58 *)param_1)->unk30 != 0) {
            rot.vx += ((rand() & 0x3f) << 4) - 0x200;
            rot.vy += ((rand() & 0x3f) << 4) - 0x200;
            rot.vz += ((rand() & 0x3f) << 4) - 0x200;
            vel.a = ((rand() & 0x1f) - 0x10) * 0x18000;
            vel.b = ((rand() & 0x1f) - 0x10) * 0x18000;
            vel.c = ((rand() & 0x1f) - 0x10) * 0x18000;
        }

        RotMatrixZYX((s32)&rot, (s32)&m);
        ApplyMatrixLV((s32)&m, (s32)&vel, (s32)&vel);

        ((Unkstruct_80126B58 *)param_1)->unk10.val = vel.a;
        ((Unkstruct_80126B58 *)param_1)->unk14 = vel.b;
        ((Unkstruct_80126B58 *)param_1)->unk18.val = vel.c;

        *(u8 *)(pb + 0x24) = 0xC0;
        *(u8 *)(pb + 0x25) = 0xC0;
        *(u8 *)(pb + 0x26) = 0x40;

        guess_SetWaitTimer_2((s32 *)param_1, 4);
        ((Unkstruct_80126B58 *)param_1)->unk2.u = ((Unkstruct_80126B58 *)param_1)->unk2.u + 1;
    } else {
        ((void (*)(s32))guess_FreeSmallObject)(param_1);
    }
}


extern void guess_AddVelocityToPos_5(s32 a0);
extern void func_800CBC40(void*, s32);
extern s32 guess_TickWaitTimer_2(s32 a0);
extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
extern s32 guess_StepPairSequence(s32 param_1, s32 *param_2);

void func_800CBAAC(s32 param_1)
{
    s32 s0;

    s0 = ((Unkstruct_80126B58 *)param_1)->unk20.val;
    guess_StepPairSequence(s0, (s32 *)(param_1 + 0x24));
    *(s8 *)(s0 + 0x27) = CAST_WIDTH(u8, param_1, 0x28) - 0x70;
    guess_AddVelocityToPos_5(param_1);
    ((void (*)(s32, s32))func_800CBC40)(param_1, 0x30);
    if (guess_TickWaitTimer_2(param_1) != 0) {
        ((Unkstruct_80126B58 *)param_1)->unk10.val >>= 2;
        ((Unkstruct_80126B58 *)param_1)->unk14 >>= 2;
        ((Unkstruct_80126B58 *)param_1)->unk18.val >>= 2;
        guess_SetWaitTimer_2((s32 *)param_1, 8);
        ((Unkstruct_80126B58 *)param_1)->unk2.u = CAST_SIGN(s16, param_1, 2) + 1;
    }
}


extern s32 guess_StepPairSequence(s32 param_1, s32 *param_2);
extern s32 guess_TickWaitTimer_2(s32 a0);
extern void guess_AddVelocityToPos_5(s32 a0);
extern void func_800CBC10(void*);
extern void func_800CBC40(void*, s32);
extern s32 guess_FreeSmallObject(u8 *a0);

void func_800CBB54(param_1)
s32 param_1;
{
    s32 p;
    s32 node;

    p = param_1;
    node = ((Unkstruct_8011D030 *)p)->unk20;
    ((void (*)(s32))func_800CBC10)(param_1);
    guess_StepPairSequence(node, (s32 *)(p + 0x24));
    *(u8 *)(node + 0x27) = ((Unkstruct_8011D030 *)p)->unk28.b - 0x70;
    ((void (*)(s32, s32))func_800CBC40)((void *)p, 0x40);
    ((Unkstruct_8011D030 *)p)->unk14.val -= 0x4000;
    guess_AddVelocityToPos_5(p);
    if (guess_TickWaitTimer_2(p) != 0) {
        ((void (*)(s32))guess_FreeSmallObject)(p);
    }
}


/* guess_AddVelocityToPos_5: adds the velocity words +0x10, +0x14, +0x18 of a0 to its position words +0x4, +0x8, +0xC
 * Confidence medium, xref chain: +0x4 += +0x10, +0x8 += +0x14, +0xC += +0x18; guess_SetVelocityXZFromLocal writes +0x10/+0x18
 * Names ledger: config/names.tsv guess_AddVelocityToPos_5 */
void guess_AddVelocityToPos_5(s32 a0) {
    CAST_WIDTH(s32, a0, 4) += ((Unkstruct_80126B58 *)a0)->unk10.val;
    CAST_WIDTH(s32, a0, 8) += ((Unkstruct_80126B58 *)a0)->unk14;
    CAST_WIDTH(s32, a0, 0xC) += ((Unkstruct_80126B58 *)a0)->unk18.val;
}


void func_800CBC10(void *arg0) {
    u8 *a0 = (u8 *)arg0;
    a0 = *(u8 **)(a0 + 0x20);
    a0[0x24] -= 4;
    a0[0x25] -= 4;
    a0[0x26] -= 4;
}


void func_800CBC40(void *arg0, s32 arg1) {
    void *v1 = *(void **)((s32)arg0 + 0x20);
    u16 v0 = ((Unkstruct_800CBC40 *)v1)->unk1A - arg1;
    ((Unkstruct_800CBC40 *)v1)->unk1A = v0;
    ((Unkstruct_800CBC40 *)v1)->unk18 = v0;
}



extern s32 guess_FreeSmallObject(u8 *a0);

void func_800CBC60(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBEF8[])(void);
    if (D_80078EC1 == 0x1c) {
        u16 v0 = ((Unkstruct_8011D030 *)arg0)->unk2.u;
        D_800CBEF8[v0]();
    } else {
        KR_AS(s32, guess_FreeSmallObject)();
    }
}


extern void *guess_AllocSpriteObject(void);
extern void func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void guess_TransformPosByObjMatrix(s32 a0, s32 a1);
extern void guess_StartPairSequence(s32 a0, s32 a1, s32 a2);
extern s32 guess_FreeSmallObject(u8 *a0);

void func_800CBCBC(void *a0)
{
    extern u8 D_800D387C[];
    extern u8 D_800D3888[];
    void *s1;
    void *s0;
    s32 pad[14];

    s1 = *(void **)((u8 *)a0 + 0x34);
    s0 = ((void *(*)(void))guess_AllocSpriteObject)();
    *(void **)((u8 *)a0 + 0x20) = s0;

    if (s0 != NULL) {
        func_8001CC3C((s32)s0, (s32)&D_800D387C, 0, 0);

        ((Unkstruct_800B5BD8 *)s0)->head.unk24.b.unk27.u = 0x9C;
        ((Unkstruct_800B5BD8 *)s0)->head.unk18.w.unk1A.u = 0x2000;
        ((Unkstruct_800B5BD8 *)s0)->head.unk18.w.unk18.u = 0x2000;
        ((Unkstruct_800B5BD8 *)s0)->head.unk24.b.unk24.u = 0xFF;
        ((Unkstruct_800B5BD8 *)s0)->head.unk24.b.unk25.u = 0;
        ((Unkstruct_800B5BD8 *)s0)->head.unk24.b.unk26 = 0;
        CAST_WIDTH(s32, (u8 *)s0, 4) |= 0x50000000;

        guess_TransformPosByObjMatrix((s32)s1, (s32)((u8 *)a0 + 4));
        guess_StartPairSequence((s32)s0, (s32)((u8 *)a0 + 0x24), (s32)&D_800D3888);

        *(u16 *)((u8 *)a0 + 2) = *(u16 *)((u8 *)a0 + 2) + 1;
    } else {
        ((void (*)(void *))guess_FreeSmallObject)(a0);
    }
}


extern s32 guess_FreeSmallObject(u8 *a0);
extern s32 guess_StepPairSequence(s32 param_1, s32 *param_2);

void func_800CBD90(void *arg0) {
    s32 q;
    u8 a;
    u8 b;
    u16 h;

    q = *(s32 *)((s32)arg0 + 0x20);

    a = ((Unkstruct_800B5BD8 *)q)->head.unk24.b.unk24.u - 0x20;
    ((Unkstruct_800B5BD8 *)q)->head.unk24.b.unk24.u = a;
    if (a < 0x80) {
        ((Unkstruct_800B5BD8 *)q)->head.unk24.b.unk24.u = 0x80;
    }

    b = ((Unkstruct_800B5BD8 *)q)->head.unk24.b.unk25.u + 0x20;
    ((Unkstruct_800B5BD8 *)q)->head.unk24.b.unk25.u = b;
    if (b > 0x80) {
        ((Unkstruct_800B5BD8 *)q)->head.unk24.b.unk25.u = 0x80;
    }

    h = ((Unkstruct_800B5BD8 *)q)->head.unk18.w.unk1A.u + 0x400;
    ((Unkstruct_800B5BD8 *)q)->head.unk24.b.unk26 = ((Unkstruct_800B5BD8 *)q)->head.unk24.b.unk25.u;
    ((Unkstruct_800B5BD8 *)q)->head.unk18.w.unk1A.u = h;
    ((Unkstruct_800B5BD8 *)q)->head.unk18.w.unk18.u = h;

    if (guess_StepPairSequence(q, (s32 *)((s32)arg0 + 0x24)) != 0) {
        ((void (*)(void *))guess_FreeSmallObject)(arg0);
    }
}


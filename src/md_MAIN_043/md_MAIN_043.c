#include "common.h"

void func_800CCB20(void *a0) {
    extern void guess_SetAnim(s32 a0, s32 a1);
    extern void guess_SaveGroundedPos(u8 *a0);
    extern void guess_ClearStoodOnActor(void *a0);
    extern void guess_ClearTiltVectors(s32 *a0);
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
    extern void guess_SetVertSpeed(s32 *a0, s32 a1);
    extern s32 func_800CCEA0(void *a0);

    guess_SetAnim((s32)a0, 0xF);
    guess_SaveGroundedPos((u8 *)a0);
    guess_ClearStoodOnActor(a0);
    guess_ClearTiltVectors((s32 *)a0);
    func_80146DE8((s32 *)a0, 0, 0, 0);
    guess_SetVertSpeed((s32 *)a0, 0xffee0000);
    func_800CCEA0(a0);
}


void func_800CCB8C(void *a0) {

    extern void (*D_800CD6DC[])(void);
    s32 e;

    e = *(u16 *)((s32)a0 + 0x2) - 2;
    D_800CD6DC[e]();
}


void func_800CCBCC(s32 a0)
{
    extern void guess_AddVertSpeed(s32 a0, s32 a1);
    extern void guess_ApplyVertSpeed(s32 a0);
    extern void guess_AddMoveVectorThenSetVelocity(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
    extern void guess_ApplyVelocity(s32 *a0);
    extern void func_8014ED28();
    extern void guess_ClearMoveVector(s32 a0);
    extern void func_8016151C(void *a0);
    extern s32 func_801725A4(u8 *a0);
    extern void guess_SetVertSpeed(s32 *a0, s32 a1);
    extern void guess_SetAnimScript(s32 *a0, s32 a1);
    extern void guess_NextStep(void *a0);
    extern s32 func_800CCEAC(void *a0);
    extern u8 D_800D53C0[];

    guess_AddVertSpeed(a0, 0x1A000);
    guess_ApplyVertSpeed(a0);
    guess_AddMoveVectorThenSetVelocity(a0, 0, 0, 0);
    guess_ApplyVelocity((s32 *)a0);
    if (((s32 (*)(s32))func_8014ED28)(a0) != 0) {
        guess_ClearMoveVector(a0);
    }
    func_8016151C((void *)a0);
    func_801725A4((u8 *)a0);
    if (((Unkstruct_80126B58 *)a0)->unk34 > 0) {
        guess_SetVertSpeed((s32 *)a0, 0x40000);
        guess_SetAnimScript((s32 *)a0, (s32)D_800D53C0);
        guess_NextStep((void *)a0);
    } else {
        func_800CCEAC((void *)a0);
    }
}


void func_800CCC88(void *a0) {
    extern void func_8014ED28(s32);
    extern void guess_ClearMoveVector(s32);
    extern void func_8016151C(void *);
    extern s32 func_801725A4(u8 *);
    extern void guess_SetAnimScript(s32 *, s32);
    extern void guess_NextStep(void *);
    extern s16 D_800D5404[];

    if (((int (*)(int))func_8014ED28)((s32)a0) != 0) {
        guess_ClearMoveVector((s32)a0);
    }
    func_8016151C(a0);
    func_801725A4((u8 *)a0);
    if (((Unkstruct_80126B58 *)a0)->unkB8 & 0x8000) {
        guess_SetAnimScript((s32 *)a0, (s32)&D_800D5404);
        guess_NextStep(a0);
    }
    func_800CCEAC(a0);
}


void func_800CCD04(void *a0) {
    extern void guess_AddVertSpeed(s32 a0, s32 a1);
    extern void guess_ApplyVertSpeed(s32 a0);
    extern void guess_AddMoveVectorThenSetVelocity(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void guess_ApplyVelocity(s32 *a0);
    extern void func_8014ED28(s32);
    extern void guess_ClearMoveVector(s32 a0);
    extern void func_80161450(void *a0);
    extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
    extern void guess_NextStep(void *a0);
    extern s32 func_801725A4(u8 *a0);
    s32 s1;

    guess_AddVertSpeed((s32)a0, 0x1A000);
    guess_ApplyVertSpeed((s32)a0);
    guess_AddMoveVectorThenSetVelocity((s32)a0, 0, 0, 0);
    guess_ApplyVelocity((s32 *)a0);
    if (((int (*)(int))func_8014ED28)((s32)a0) != 0) {
        guess_ClearMoveVector((s32)a0);
    }
    s1 = ((int (*)(int))func_80161450)(a0);
    if ((s1 & 5) != 0) {
        func_800CCE24(a0);
        guess_SetWaitTimer_2((s32 *)a0, 0x10);
        guess_NextStep(a0);
    }
    if (s1 == 0) {
        func_801725A4((u8 *)a0);
        func_800CCEAC(a0);
    }
}


extern s32 guess_TickWaitTimer_2(s32 arg0);
extern void func_801599A4(void *arg0);
extern void func_80159B3C(void *arg0);
extern s32 func_80161208();

void func_800CCDC4(s32 a0)
{
    CAST_SIGN(s32, a0, 0x44) |= 2;
    if (guess_TickWaitTimer_2(a0) != 0) {
        func_801599A4((void *)a0);
        func_80159B3C((void *)a0);
    } else {
        func_80161208((void *)a0);
    }
}


extern void func_8014B5C4(s32 *a0, s32 a1, s32 a2);
extern void func_8013C9C4(void *a0);
extern void guess_SpawnObject(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void guess_SpawnSmallObjectType2(s32 *a0, s32 a1);
extern void guess_PlaySoundUnlessSkipped(s32 a0);
extern s32 D_800D3414;

void func_800CCE24(void *a0) {
    s32 s0;

    s0 = (s32)a0;
    func_8014B5C4((s32 *)s0, 2, 0);
    func_8013C9C4(&D_800D3414);
    guess_SpawnObject(5, s0, 0, 0, 0, 0, 0, 1);
    guess_SpawnSmallObjectType2((s32 *)s0, 1);
    guess_PlaySoundUnlessSkipped(0x47D);
}


s32 func_800CCEA0(void *a0) {
    ((Unkstruct_80126B58 *)a0)->unk234 = 150;
    return 150;
}


s32 func_800CCEAC(void *a0)
{
    extern void func_801599A4(void *a0);
    extern void func_80159B3C(void *a0);
    extern s16 currentLocationId;

    if (currentLocationId == 0x306F) {
        if (((Unkstruct_80126B58 *)a0)->unk234 != 0) {
            (((Unkstruct_80126B58 *)a0)->unk234)--;
            return 0;
        }
        func_801599A4(a0);
        func_80159B3C(a0);
        return 1;
    }
    return 0;
}




void func_800CCF14(void *a0) {

    extern void (*D_800CD6EC[])(void);
    D_800CD6EC[((Unkstruct_80126B58 *)a0)->unk2]();
}


void func_800CCF50(void *a0) {

    extern s32 func_80146578(void);
    extern void func_8001CD50(s32 a0, s32 a1);
    extern void guess_TransformPosByObjMatrix(s32 a0, s32 a1);
    extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
    extern void func_800CD1F4(void *a0, void *a1);
    extern s32 func_800CD258(void *a0, void *a1);
    extern void func_800CD27C(s32 a0);
    extern void guess_NextStep(void *);
    extern void guess_FreeObjectAndSubObject_23(void);
    extern u8 D_800CD704[];
    extern u8 D_800CD744[];

    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;

    s2 = *(s32 *)(a0 + 0x4C);
    s0 = (s32)((void *(*)(void))func_80146578)();
    s3 = (s32)&D_800CD704;
    ((Unkstruct_80126B58 *)a0)->unk20 = s0;

    if (s0 != 0) {
        func_8001CD50(s0, s3);
        *(s32 *)(s0 + 0x34) = (s32)&D_800CD744;
        *(s32 *)(s0 + 4) |= 0x50000000;
        *(u16 *)(s0 + 0x1C) = 0;
        guess_TransformPosByObjMatrix(s2, a0 + 4);
        *(u16 *)(s0 + 0x10) = ((Unkstruct_80126B58 *)s2)->unk100;
        *(u16 *)(s0 + 0x14) = ((Unkstruct_80126B58 *)s2)->unk104;
        *(u16 *)(s0 + 0x12) = *(u16 *)(((Unkstruct_80126B58 *)s2)->unk20 + 0x12);
        guess_SetWaitTimer_2((s32 *)a0, 0x10);
        ((Unkstruct_80126B58 *)a0)->unk60 = 0;
        ((Unkstruct_80126B58 *)a0)->unk62 = 0;
        func_800CD1F4((void *)a0, (void *)s3);
        func_800CD258((void *)a0, (void *)s3);
        func_800CD27C(a0);
        guess_NextStep((void *)a0);
    } else {
        ((void (*)(void *))guess_FreeObjectAndSubObject_23)((void *)a0);
    }
}


s32 func_800CD258(void *a0, void *a1);
void func_800CD27C(s32 a0);
void func_800CD31C(s32 arg0);


void func_800CD054(void *a0) {
    extern void guess_SpawnObject(s32 a0, s32 a1, s32 a2, s32 a3,
                              s32 a4, s32 a5, s32 a6, s32 a7);
    extern void guess_PlaySoundUnlessSkipped(s32 a0);
    extern s32 func_80012FC8(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 guess_TickWaitTimer_2(s32 a0);
    extern void guess_NextStep(void *a0);
    extern u8 D_800CD704[];
    u8 *dp;
    s32 s1;
    s32 w;
    s32 v0;
    s32 v1;

    s1 = ((Unkstruct_80126B58 *)a0)->unk20;
    dp = D_800CD704;
    func_800CD258(a0, dp);
    func_800CD27C((s32)a0);
    if ((CAST_SIGN(u32, (s32)a0, 0x1C) & 7) == 0) {
        guess_SpawnObject(6, (s32)a0, 0, 0, 0, CAST_SIGN(s16, (s32)a0, 0x62), 0, 1);
        w = ((Unkstruct_80126B58 *)a0)->unk62 + 1;
        ((Unkstruct_80126B58 *)a0)->unk62 = w;
        if ((s16)w >= 8) {
            ((Unkstruct_80126B58 *)a0)->unk62 = 0;
        }
        guess_PlaySoundUnlessSkipped(0x47E);
    }
    v0 = func_80012FC8(*(s16 *)(s1 + 0x1A), 0x5000, 0xA, 1);
    v1 = *(u16 *)(s1 + 0x1A) + v0;
    *(u16 *)(s1 + 0x1A) = v1;
    *(u16 *)(s1 + 0x18) = v1;
    v1 = ((Unkstruct_80126B58 *)a0)->unk60;
    v1 += 0x20;
    ((Unkstruct_80126B58 *)a0)->unk60 = v1;
    v0 = *(u16 *)(s1 + 0x1C) + v1;
    *(u16 *)(s1 + 0x1C) = v0;
    if ((s16)v0 >= 0x1000) {
        *(u16 *)(s1 + 0x1C) = 0x1000;
    }
    *(u16 *)(s1 + 0x1E) = *(u16 *)(s1 + 0x1C) | 0x4000;
    if (*(s16 *)(s1 + 0x1C) == 0x1000) {
        *(u16 *)(s1 + 0x1C) = 0;
        ((Unkstruct_80126B58 *)a0)->unk60 = 0;
        *(S4_800CD054 *)(dp + 4) = *(S4_800CD054 *)(dp + 0xC);
    }
    v0 = guess_TickWaitTimer_2((s32)a0);
    if (v0 != 0) {
        guess_NextStep(a0);
    } else {
        func_800CD31C((s32)a0);
    }
}


extern void guess_ClearObjectAndSubObject();  // K&R: 0 of 1 args (P37 rung D t4_D44)
/* guess_FreeObjectAndSubObject_23: zeroes object a0 (0x68 bytes) and its +0x20 sub-object (0x84 bytes when that one's first halfword is 1, else 0x38)
 * Confidence medium, code inference: guess_ClearObjectAndSubObject(a0): p = +0x20; p -> guess_ZeroMemory(p, *p == 1 ? 0x84 : 0x38); guess_ZeroMemory(a0, 0x68); spawn steps call it when allocation fails
 * Names ledger: config/names.tsv guess_FreeObjectAndSubObject_23 */
void guess_FreeObjectAndSubObject_23(void) {
    guess_ClearObjectAndSubObject();
}


extern void guess_BuildCircle12Points(void *arg0, u16 arg1);

void func_800CD1F4(void *a0, void *a1) {
    void *s0;

    s0 = a1;
    if (((Unkstruct_80126B58 *)a0)->unk50 == 0) {
        guess_BuildCircle12Points(s0, 0x40);
    } else {
        guess_BuildCircle12Points(s0, 0x30);
    }
    *(u8 *)((s32)s0 + 0) = 0;
    *(u8 *)((s32)s0 + 1) = 0;
    *(u8 *)((s32)s0 + 2) = 0;
    *(u8 *)((s32)s0 + 4) = 0;
    *(u8 *)((s32)s0 + 5) = 0;
    *(u8 *)((s32)s0 + 6) = 0;
}


s32 func_800CD258(void *a0, void *a1) {
    s32 v;
    *(u8 *)((s32)a1 + 8) = 0;
    *(u8 *)((s32)a1 + 9) = 0;
    *(u8 *)((s32)a1 + 10) = 0;
    v = (CAST_SIGN(u32, (s32)a0, 0x1C)) << 3;
    *(u8 *)((s32)a1 + 14) = 0;
    *(u8 *)((s32)a1 + 12) = v;
    *(u8 *)((s32)a1 + 13) = v;
    return v;
}




extern void func_80013F3C(s32 a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);

void func_800CD27C(s32 a0) {
    MtxBuf_800CD27C buf;
    s32 obj;

    obj = ((Unkstruct_80126B58 *)a0)->unk20;
    func_80013F3C((s32)&buf);
    func_800126C4((s32)&buf, *(s16 *)(obj + 0x10));
    func_800123F0((s32)&buf, *(s16 *)(obj + 0x14));
    func_80012558((s32)&buf, *(s16 *)(obj + 0x12));
    func_800126C4((s32)&buf, 0x400);
    *(Mtx_800CD27C *)(*(s32 *)(obj + 0x34)) = buf.mt;
}


extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern void guess_CopyVec3HighHalves(s32 a0, s32 *a1);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern u8 guess_g_ObjectTable[]; // Names ledger: config/names.tsv guess_g_ObjectTable

void func_800CD31C(s32 arg0) {
    u8 sp10[8];
    u8 *p = guess_g_ObjectTable;

    if (p < guess_g_ObjectTable + 0x6480) {
        u8 *end = p + 0x6480;
        do {
            if (func_8014C308(arg0, (s32)p, 0x22, 0)) {
                if (func_8014C278(arg0, (s32)p, 0x80)) {
                    guess_CopyVec3HighHalves((s32)(p + 4), (s32 *)sp10);
                    *(u16 *)(sp10 + 6) = 0;
                    func_8014C3A4((void *)arg0, (s32)p, 0x22, (s32 *)sp10);
                }
            }
            p += 0x10C;
        } while (p < end);
    }
}




void func_800CD3C8(void *a0) {

    extern void (*D_800CD6F8[])(void);
    D_800CD6F8[((Unkstruct_80126B58 *)a0)->unk2]();
}


void func_800CD404(void *a0) {
    extern s32 func_80146578(void);
    extern void func_8001CD50(s32 a0, s32 a1);
    extern void guess_SetWaitTimer_2(s32 *a0, s32 a1);
    extern void guess_NextStep(void *);
    extern void func_800CD670(s32 a0, void *a1);
    extern void guess_FreeObjectAndSubObject_25(void);
    extern void func_800CD6D4(void);
    extern s32 D_800D3428;
    extern u8 D_800CD764[];
    extern u8 D_800CD964[];


    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;

    s32 v;

    s2 = *(s32 *)(a0 + 0x4C);
    {
        s32 base;
        s32 val;
        base = (s32)&D_800CD764;
        val = ((Unkstruct_80126B58 *)a0)->unk50 << 6;
        s3 = val + base;
    }
    func_8013C9C4(&D_800D3428);
    s0 = (s32)((void *(*)(void))func_80146578)();
    ((Unkstruct_80126B58 *)a0)->unk20 = s0;

    if (s0 != 0) {
        func_8001CD50(s0, s3);
        *(u16 *)(s0 + 0x1E) = 0xCCC;
        *(s32 *)(s0 + 4) |= 0x50000000;
        *(u16 *)(s0 + 0x18) = 0;
        *(u16 *)(s0 + 0x1A) = 0;
        {
            s32 dstp;
            s32 srcp;
            dstp = (((Unkstruct_80126B58 *)a0)->unk50 << 5) + (s32)&D_800CD964;
            *(s32 *)(s0 + 0x34) = dstp;
            srcp = ((Unkstruct_80126B58 *)*(s32 *)(a0 + 0x4C))->unk20;
            srcp = *(s32 *)(srcp + 0x34);
            *(Block32 *)dstp = *(Block32 *)srcp;
        }
        ((Unkstruct_80126B58 *)a0)->unk6 = CAST_SIGN(u16, s2, 6);
        v = CAST_SIGN(u16, s2, 0xA);
        ((Unkstruct_80126B58 *)a0)->unkA = v;
        ((Unkstruct_80126B58 *)a0)->unk60 = v;
        ((Unkstruct_80126B58 *)a0)->unkE = CAST_SIGN(u16, s2, 0xE);
        ((Unkstruct_80126B58 *)a0)->unk62 = ((Unkstruct_80126B58 *)s2)->unk1C;
        guess_SetWaitTimer_2((s32 *)a0, 0x20);
        func_800CD670(a0, (void *)s3);
        ((void (*)(void *, void *))func_800CD6D4)((void *)a0, (void *)s3);
        guess_NextStep((void *)a0);
    } else {
        ((void (*)(void *))guess_FreeObjectAndSubObject_25)((void *)a0);
    }
}


extern void func_800CD6D4(void);
extern s32 func_80012FC8(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 rsin(s32 a0);
extern s32 guess_TickWaitTimer_2(s32 a0);
extern void guess_NextStep(void *a0);
extern u8 D_800CD764[];

void func_800CD57C(void *arg0) {
    s32 s0;
    s32 v0;
    s32 t;

    s0 = ((Unkstruct_80126B58 *)arg0)->unk20;
    ((void (*)(void *, void *))func_800CD6D4)(
        arg0,
        (void *)(D_800CD764 + (((Unkstruct_80126B58 *)arg0)->unk50 << 6)));
    v0 = func_80012FC8(*(s16 *)(s0 + 0x1A), 0x5000, 0xA, 1);
    t = *(u16 *)(s0 + 0x1A) + v0;
    *(u16 *)(s0 + 0x1A) = t;
    *(u16 *)(s0 + 0x18) = t;
    {
        s32 x;
        x = (s16)t;
        v0 = rsin(x / 10);
    }
    {
        s32 adj;
        s32 v1;
        v1 = CAST_SIGN(s16, (s32)arg0, 0x62);
        v0 = v0 * 2;
        v1 = v1 * v0;
        adj = v1 / 0x1000;
        ((Unkstruct_80126B58 *)arg0)->unkA = ((Unkstruct_80126B58 *)arg0)->unk60 - adj;
    }
    v0 = guess_TickWaitTimer_2((s32)arg0);
    if (v0 != 0) {
        guess_NextStep(arg0);
    }
}


extern void guess_ClearObjectAndSubObject();  // K&R: 0 of 1 args (P37 rung D t4_D44)
/* guess_FreeObjectAndSubObject_25: zeroes object a0 (0x68 bytes) and its +0x20 sub-object (0x84 bytes when that one's first halfword is 1, else 0x38)
 * Confidence medium, code inference: guess_ClearObjectAndSubObject(a0): p = +0x20; p -> guess_ZeroMemory(p, *p == 1 ? 0x84 : 0x38); guess_ZeroMemory(a0, 0x68); spawn steps call it when allocation fails
 * Names ledger: config/names.tsv guess_FreeObjectAndSubObject_25 */
void guess_FreeObjectAndSubObject_25(void) {
    guess_ClearObjectAndSubObject();
}


extern void guess_BuildCircle12Points(void *arg0, u16 arg1);

void func_800CD670(s32 arg0, void *arg1)
{
    s32 t;

    guess_BuildCircle12Points(arg1, 0x40);
    *(u8 *)(arg1 + 0) = 0;
    *(u8 *)(arg1 + 1) = 0;
    *(u8 *)(arg1 + 2) = 0;
    t = CAST_SIGN(s16, arg0, 0x62) * 12;
    *(u8 *)(arg1 + 6) = 0;
    *(u8 *)(arg1 + 5) = t;
    *(u8 *)(arg1 + 4) = t;
}


void func_800CD6D4(void) {
}

INCLUDE_RODATA("asm/md_MAIN_043/nonmatchings/md_MAIN_043", D_800CCB1C);

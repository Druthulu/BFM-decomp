#include "common.h"
#include "../shared/engine_prelude.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB2D4;
    func_800183E0(&D_800CB2D4);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB29C[])(void);
    ((Unkstruct_800CAE34 *)a0)->unk44 |= 8;
    D_800CB29C[((Unkstruct_800CAE34 *)a0)->unk197]();
}


#include "../shared/slot_800CAE08/func_800CAE78__a79b87ee.h"


extern M2C_UNK D_800CB26C;
extern void guess_SetAnimScript(s32 *a0, s32 a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void guess_SetVertSpeed(s32 *a0, s32 a1);
extern void func_801655E4(s32 a0);
extern void func_80156648(s32 *a0);
extern void guess_SpawnObject(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);

void func_800CAEC0(u8 *a0) {
    guess_SetAnimScript((s32 *)a0, (s32)&D_800CB26C);
    func_80146DE8((s32 *)a0, 0, 0, 0xFFEE0000);
    guess_SetVertSpeed((s32 *)a0, 0xFFF40000);
    func_801655E4((s32)a0);
    func_80156648((s32 *)a0);
    a0[0x1AA] = 1;
    guess_SpawnObject(0x18, (s32)a0, 0, 0, 0, 0, 0, 1);
    a0[0x197] = a0[0x197] + 1;
}


void func_800CAF60(void *a0) {
    extern void guess_SetVelocityFromMoveVector(s32 a0);
    extern void guess_ApplyVelocity(s32 *a0);
    extern void guess_AddVertSpeed(s32 a0, s32 a1);
    extern void guess_ApplyVertSpeed(s32 a0);
    extern s32  func_80161418(void *a0);
    extern s32  func_80155FD4(s32 a0, s32 a1);

    ((Unkstruct_80126B58 *)a0)->unk44 |= 2;
    guess_SetVelocityFromMoveVector((s32)a0);
    guess_ApplyVelocity((s32 *)a0);
    guess_AddVertSpeed((s32)a0, 0x20000);
    guess_ApplyVertSpeed((s32)a0);
    if (func_80161418(a0) == 0) {
        func_80155FD4((s32)a0, ((Unkstruct_80126B58 *)a0)->unk1AA);
    }
}


void func_800CAFD0(void *a0) {
    extern u8 D_8011F9D0[];
    extern void func_80162CCC();  // K&R: 0/1 of 1 args (P37 rung D t4_D44)
    s32 i;
    u8 *ptr;

    for (i = 0; i < 0x14; i++) {
        ptr = D_8011F9D0 + (i * 0x68);
        if (*(u16 *)ptr == 0x18) {
            func_80162CCC(ptr);
        }
    }

    *(u32 *)((s32)a0 + 0x44) &= ~2;
}



extern void guess_FreeObjectAndSubObject_2(void);

void func_800CB054(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB2A8[])(void);
    if (D_80078EC1 == 0x9) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB2A8[v0]();
    } else {
        guess_FreeObjectAndSubObject_2();
    }
}


#include "common.h"


extern s32 func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void guess_TransformPosByObjMatrix(s32 a0, s32 a1);
extern void guess_NextStep(void *a0);
extern void guess_FreeObjectAndSubObject_2(void);

void func_800CB0B0(void *arg0) {
    extern u16 D_800CC3C4;
    s32 s0;
    s32 s2;
    s32 flag;
    s32 src;

    s2 = *(s32 *)((s32)arg0 + 0x4C);
    s0 = ((s32 (*)(void))func_8014659C)();
    ((Unkstruct_80126B58 *)arg0)->unk20 = s0;
    if (s0 != 0) {
        func_8001C810(s0, (s32)&D_800CC3C4);
        flag = *(s32 *)(s0 + 4);
        flag |= 0x50000000;
        *(s32 *)(s0 + 4) = flag;
        guess_TransformPosByObjMatrix(s2, (s32)arg0 + 4);
        src = ((Unkstruct_80126B58 *)s2)->unk20;
        *(func_800CB0B0_Blk16 *)(s0 + 0x34) = *(func_800CB0B0_Blk16 *)(src + 0x34);
        *(func_800CB0B0_Blk16 *)(s0 + 0x44) = *(func_800CB0B0_Blk16 *)(src + 0x44);
        guess_NextStep(arg0);
    } else {
        ((void (*)(void *))guess_FreeObjectAndSubObject_2)(arg0);
    }
}


#include "common.h"


extern void guess_TransformPosByObjMatrix(s32 a0, s32 a1);

void func_800CB188(void *arg0) {
    extern u16 guess_g_FrameCounter;
    s32 s0;
    s32 s1;
    s32 v0;
    s32 v1;

    s0 = ((Unkstruct_800CB188 *)arg0)->unk4C;
    s1 = ((Unkstruct_800CB188 *)arg0)->unk20;
    ((Unkstruct_800CB188 *)arg0)->unkC = 0;
    ((Unkstruct_800CB188 *)arg0)->unk8 = 0;
    ((Unkstruct_800CB188 *)arg0)->unk4 = 0;
    guess_TransformPosByObjMatrix(s0, (s32)arg0 + 4);
    v0 = *(s32 *)(s0 + 0x20);
    *(func_800CB188_Blk16 *)(s1 + 0x34) = *(func_800CB188_Blk16 *)(v0 + 0x34);
    *(func_800CB188_Blk16 *)(s1 + 0x44) = *(func_800CB188_Blk16 *)(v0 + 0x44);
    v1 = ((Unkstruct_800CB188_2 *)s1)->unk4 & 0x7FFFFFFF;
    CAST_ALIAS(s32, s1, 4) = v1;
    if (guess_g_FrameCounter & 1) {
        ((Unkstruct_800CB188_2 *)s1)->unk4 = v1 | 0x80000000;
    }
}


extern void func_80162CCC();  // K&R: 0/1 of 1 args (P37 rung D t4_D44)
/* guess_FreeObjectAndSubObject_2: zeroes object a0 (0x68 bytes) and its +0x20 sub-object (0x84 bytes when that one's first halfword is 1, else 0x38)
 * Confidence medium, code inference: func_80162CCC(a0): p = +0x20; p -> guess_ZeroMemory(p, *p == 1 ? 0x84 : 0x38); guess_ZeroMemory(a0, 0x68); spawn steps call it when allocation fails
 * Names ledger: config/names.tsv guess_FreeObjectAndSubObject_2 */
void guess_FreeObjectAndSubObject_2(void) {
    func_80162CCC();
}


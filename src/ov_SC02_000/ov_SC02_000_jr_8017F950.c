#include "common.h"


void func_8017F950(s32 arg0)
{
    extern void guess_StartPadVibration(void *a0);
    extern void guess_StartActorSequence(Unkstruct_801202A0 *a0, void * a1);
    extern void guess_ClearVelocityAndSetGravity(Unkstruct_801202A0 *a0);
    extern void guess_UpdateActorModelMatrix(s32 a0);
    extern void func_8012E9C0(s32 a0);
    extern s32 guess_SpawnActorType1C(s32 a0, s32 a1);
    extern void func_8017FC9C(s32 a0);
    extern void func_8017FCB0(s32 a0);
    extern void func_8017FD2C(s32 a0);
    extern void func_8017FD44(s32 a0);
    extern void func_8017FD80(s32 a0);
    extern void func_8017FDE8(s32 a0);
    extern void func_8017FE68(s32 a0);
    extern void func_801801EC(s32 a0);
    extern void func_80180A64(s32 a0);
    extern u8 D_80062BDC;
    extern char D_801A681C[];
    extern St801D9204 D_801E6A00;
    St801D9204 local = D_801E6A00;

    if (((Unkstruct_801202A0 *)arg0)->unk5E.b == 5) {
        guess_StartPadVibration(&D_80062BDC);
    }
    if (CAST_WIDTH(u16, arg0, 0x5E) == 0x1F) {
        func_80180A64(arg0);
        return;
    }
    ((Unkstruct_801202A0 *)arg0)->unkC1.s = 0;
    func_8012E9C0(arg0);
    ((Unkstruct_801202A0 *)arg0)->unk76.s = CAST_SIGN(u16, arg0, 0x76) - CAST_SIGN(u16, arg0, 0x60);
    ((Unkstruct_801202A0 *)arg0)->unk5C.u &= 0xFFFE;
    ((Unkstruct_800B5CB8 *)*(s32 *)(arg0 + 0x20))->unk12 = (((Unkstruct_801202A0 *)arg0)->unk62 + 0x800) & 0xFFF;
    guess_UpdateActorModelMatrix(arg0);
    guess_ClearVelocityAndSetGravity(arg0);
    ((Unkstruct_801202A0 *)arg0)->unk2.s = 3;
    guess_SpawnActorType1C(arg0, 0);
    switch (((Unkstruct_801202A0 *)arg0)->unk5E.b) {
    case 13:
        func_8017FC9C(arg0);
        return;
    case 14:
        func_8017FCB0(arg0);
        return;
    case 10:
        func_8017FD44(arg0);
        return;
    case 9:
        func_8017FD80(arg0);
        return;
    case 17:
        func_8017FDE8(arg0);
        return;
    case 33:
        func_8017FD2C(arg0);
        return;
    case 15:
        if (((Unkstruct_801202A0 *)arg0)->unk76.s > 0) {
            func_801801EC(arg0);
            return;
        }
        break;
    default:
        if (((Unkstruct_801202A0 *)arg0)->unk76.s > 0) {
            ((Unkstruct_801202A0 *)arg0)->unk34.u = 0;
            ((Unkstruct_801202A0 *)arg0)->unk1C.s = 0x10;
            guess_StartActorSequence(arg0, D_801A681C);
            return;
        }
        break;
    }
    func_8017FE68(arg0);
}


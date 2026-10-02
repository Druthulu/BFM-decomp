#include "common.h"


void func_8017F950(s32 arg0)
{
    extern void func_80019064(void *a0);
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8012B23C(s32 a0);
    extern void func_8012B2CC(s32 a0);
    extern void func_8012E9C0(s32 a0);
    extern s32 func_80143B6C(s32 a0, s32 a1);
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

    if (((Unkstruct_800B5CB8 *)arg0)->unk5E == 5) {
        func_80019064(&D_80062BDC);
    }
    if (CAST_WIDTH(u16, arg0, 0x5E) == 0x1F) {
        func_80180A64(arg0);
        return;
    }
    ((Unkstruct_800B5CB8 *)arg0)->unkC1 = 0;
    func_8012E9C0(arg0);
    ((Unkstruct_800B5CB8 *)arg0)->unk76 = CAST_SIGN(u16, arg0, 0x76) - CAST_SIGN(u16, arg0, 0x60);
    ((Unkstruct_800B5CB8 *)arg0)->unk5C &= 0xFFFE;
    ((Unkstruct_800B5CB8 *)*(s32 *)(arg0 + 0x20))->unk12 = (((Unkstruct_800B5CB8 *)arg0)->unk62 + 0x800) & 0xFFF;
    func_8012B2CC(arg0);
    func_8012B23C(arg0);
    ((Unkstruct_800B5CB8 *)arg0)->unk2 = 3;
    func_80143B6C(arg0, 0);
    switch (((Unkstruct_800B5CB8 *)arg0)->unk5E) {
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
        if (((Unkstruct_800B5CB8 *)arg0)->unk76 > 0) {
            func_801801EC(arg0);
            return;
        }
        break;
    default:
        if (((Unkstruct_800B5CB8 *)arg0)->unk76 > 0) {
            ((Unkstruct_800B5CB8 *)arg0)->unk34 = 0;
            ((Unkstruct_800B5CB8 *)arg0)->unk1C = 0x10;
            func_8012A828(arg0, D_801A681C);
            return;
        }
        break;
    }
    func_8017FE68(arg0);
}


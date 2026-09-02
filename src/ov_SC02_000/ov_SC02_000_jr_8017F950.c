#include "common.h"


void func_8017F950(s32 arg0)
{
    typedef struct { u32 w[4]; } St801D9204;
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

    if (*(u8 *)(arg0 + 0x5E) == 5) {
        func_80019064(&D_80062BDC);
    }
    if (*(u16 *)(arg0 + 0x5E) == 0x1F) {
        func_80180A64(arg0);
        return;
    }
    *(u8 *)(arg0 + 0xC1) = 0;
    func_8012E9C0(arg0);
    *(u16 *)(arg0 + 0x76) = *(u16 *)(arg0 + 0x76) - *(u16 *)(arg0 + 0x60);
    *(u16 *)(arg0 + 0x5C) &= 0xFFFE;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = (*(u16 *)(arg0 + 0x62) + 0x800) & 0xFFF;
    func_8012B2CC(arg0);
    func_8012B23C(arg0);
    *(s16 *)(arg0 + 2) = 3;
    func_80143B6C(arg0, 0);
    switch (*(u8 *)(arg0 + 0x5E)) {
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
        if (*(s16 *)(arg0 + 0x76) > 0) {
            func_801801EC(arg0);
            return;
        }
        break;
    default:
        if (*(s16 *)(arg0 + 0x76) > 0) {
            *(u16 *)(arg0 + 0x34) = 0;
            *(s32 *)(arg0 + 0x1C) = 0x10;
            func_8012A828(arg0, D_801A681C);
            return;
        }
        break;
    }
    func_8017FE68(arg0);
}


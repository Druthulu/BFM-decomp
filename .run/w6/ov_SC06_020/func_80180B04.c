#include "common.h"

extern void func_80181064(s32 a0);
extern s32  func_8012DBD0(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80180EF0(s32 a0, s32 a1);
extern void func_8012CC64(s32 a0, s32 a1);
extern s32  func_80143B6C(s32 a0, s32 a1);
extern s32  func_8012CBA4(s32 a0);
extern s32  func_8012CBF4(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_80131C78(s32 a0);
extern void func_80131E00();
extern void func_80183FD0(s32 a0, s32 a1);


void func_80180B04(s32 a0) {

    extern u8 D_8019EBBC;
    u16 sp10[4];
    s32 s1;

    if (*(s16 *)(a0 + 0xA) >= 0x10) {
        func_80181064(a0);
        return;
    }

    if (*(s32 *)(a0 + 0x10) != 0 || *(s32 *)(a0 + 0x18) != 0) {
        func_8012DBD0(a0, 0x50,
                      *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800, 0x1D);
    }

    switch (*(u8 *)(a0 + 0xC2)) {
    case 0:
        func_80180EF0(a0, (s32)&D_8019EBBC);
        *(u8 *)(a0 + 0xC2) += 1;
    case 1:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x29) {
            func_80131E00(a0, 0xD);
            return;
        }
        s1 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&D_8019EBBC);
        if (s1 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (s1 & 0x4000) {
            func_8012B23C(a0);
            *(u8 *)(a0 + 0xC2) = 4;
        } else if (s1 & 0x2000) {
            *(u8 *)(a0 + 0xC2) = 2;
            func_80143B6C(a0, 1);
            *(s32 *)(a0 + 0x14) = 0xFFF30000;
            *(s32 *)(a0 + 0x1C) = 0;
            func_80183FD0(a0, 0x9B8);
        }
        break;

    case 2:
        {
            s32 s2;

            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
            *(s32 *)(a0 + 0x1C) += 1;
            if (*(s32 *)(a0 + 0x1C) >= 0x29) {
                func_80131E00(a0, 0xD);
                return;
            }
            s2 = *(s32 *)(a0 + 0x14);
            s1 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&D_8019EBBC);
            if (s1 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (s1 & 0x4000) {
                func_8012B23C(a0);
                *(u8 *)(a0 + 0xC2) = 4;
            } else if (s1 & 0x2000) {
                func_80143B6C(a0, 1);
                *(s32 *)(a0 + 0x14) = (-s2) / 3;
                *(s32 *)(a0 + 0x1C) = 0;
                *(u8 *)(a0 + 0xC2) = 3;
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            }
        }
        break;

    case 3:
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) * 15 / 16;
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) * 15 / 16;
        if (*(u8 *)(a0 + 0xC3) & 1) {
            s1 = func_8012CBA4(a0);
            if (s1 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (!(s1 & 0x6000)) {
                func_80131E00(a0, 0xD);
                return;
            }
        } else {
            s1 = func_8012CBF4(a0);
            if (s1 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (s1 & 0x4000) {
                func_8012B23C(a0);
                *(u8 *)(a0 + 0xC2) = 4;
                break;
            } else if (s1 & 0x2000) {
                *(u8 *)(a0 + 0xC3) |= 1;
                func_80183FD0(a0, 0x9B8);
            }
        }
        if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
            func_80143B6C(a0, 1);
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) < 0x11) {
            break;
        }
        if (!(s1 & 0x6000)) {
            func_80131E00(a0, 0xD);
            return;
        }
        if (*(s16 *)(a0 + 0x76) <= 0) {
            func_80131E00(a0, 6);
        } else {
            func_80131C78(a0);
        }
        break;

    case 4:
        s1 = func_8012CBA4(a0);
        if (s1 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (s1 & 0x2000) {
            if (*(s16 *)(a0 + 0x76) <= 0) {
                func_80131E00(a0, 6);
            } else {
                func_80131C78(a0);
            }
        } else {
            if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
                func_80143B6C(a0, 1);
            }
            *(s32 *)(a0 + 0x1C) += 1;
            if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
                func_80131E00(a0, 0xD);
                return;
            }
        }
        break;
    }
}

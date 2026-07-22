// @class: schedule
// @stuck: close=9 — only the case-7 sp20[] setup window (0x80192380..0x801923A4): gcc's list scheduler picks the D_80126B62 lui 2nd (its extra `addiu -0x38` gives that chain +1 priority) where the target picks D_80126B66 2nd (LUID/program order); everything else (710/710 ins, frame 0x40, $s0/$s1, jtbl, 3 entity loops, 8 sync blocks, cross-jumped L4AC tail) is byte-identical.
#include "common.h"

extern u8 D_801202A0[];
extern u8 D_801D11F8[];
extern u8 D_801D1220[];
extern u8 D_80126B5C[];
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_800B99D8;

extern s32 func_8012C658(s32, s32, s32);
extern void func_8012B2CC(s32);
extern void func_8012F14C(s32, void *, void *);
extern void func_8012B77C(void *, void *, void *);
extern void func_8018D40C(s32);
extern void func_8018D514(s32);
extern s32 func_8012BE54(s32);
extern void func_8002D4C8(s32, s32);
extern void func_8004914C(s32);
extern void func_800491AC(s32);
extern void RotTransSV(void *, void *, void *);
extern void func_8018FE0C(void *, void *, s32);
extern s32 rand(void);

#define ENT_LOOP()                                                             \
    p = (s32)D_801202A0;                                                       \
    i = 0;                                                                     \
    do {                                                                       \
        if (*(u16 *)p == 0x318 && p != arg0 &&                                 \
            (*(s16 *)(p + 0x70) == 0 || *(s16 *)(p + 0x70) == 6) &&            \
            *(u16 *)(p + 0x34) == 6 && *(s32 *)(p + 0x1C) < 0x11) {            \
            *(s32 *)(p + 0x1C) += 0x10;                                        \
        }                                                                      \
        p += 0x10C;                                                            \
        i += 1;                                                                \
    } while (i < 0x60);

#define SYNC(srcoff, dstoff)                                                   \
    src = *(s32 *)(arg0 + srcoff);                                             \
    func_8012B2CC(src);                                                        \
    mp = D_801D11F8;                                                           \
    __asm__("" : "=r"(mp) : "0"(mp));                                          \
    func_8012F14C(*(s32 *)(src + 0x20) + 0x34, mp, sp10);                      \
    dst = *(s32 *)(arg0 + dstoff);                                             \
    *(s16 *)(dst + 6) = sp10[0];                                               \
    *(s16 *)(dst + 0xA) = sp10[1];                                             \
    *(s16 *)(dst + 0xE) = sp10[2];                                             \
    *(s16 *)(*(s32 *)(dst + 0x20) + 0x10) =                                    \
        *(u16 *)(dst + 0xFC) + *(u16 *)(*(s32 *)(src + 0x20) + 0x10);          \
    *(s16 *)(*(s32 *)(dst + 0x20) + 0x12) =                                    \
        *(u16 *)(dst + 0xFE) + *(u16 *)(*(s32 *)(src + 0x20) + 0x12);

#define SYNC_LAST()                                                            \
    src = *(s32 *)(arg0 + 0xD4);                                               \
    func_8012B2CC(src);                                                        \
    mp = D_801D11F8;                                                           \
    __asm__("" : "=r"(mp) : "0"(mp));                                          \
    func_8012F14C(*(s32 *)(src + 0x20) + 0x34, mp, sp10);                      \
    *(s16 *)(arg0 + 6) = sp10[0];                                              \
    *(s16 *)(arg0 + 0xA) = sp10[1];                                            \
    *(s16 *)(arg0 + 0xE) = sp10[2];

#define BLIT()                                                                 \
    func_8012B77C(sp10, (void *)(arg0 + 4), D_80126B5C);                       \
    tv = *(s32 *)sp10;                                                         \
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x10) = (s16)tv;                          \
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = (s16)(tv >> 16);

void func_80191C50(s32 arg0) {
    s16 sp10[4];
    s16 sp18[4];
    s16 sp20[4];
    s16 sp28[4];
    register s32 src __asm__("$16");
    register s32 dst __asm__("$3");
    s32 obj;
    s32 p;
    s32 i;
    s32 c4, c5, c6a, c6b, c7, c8, c9a, c9b, c10, c11;
    s16 sv;
    s32 mode;
    void *mp;
    void *bp;
    void *bp2;
    void *rp;
    register s32 tv __asm__("$2");

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        return;
    case 1:
        obj = func_8012C658(0x318, 2, arg0);
        if (obj == 0) {
            return;
        }
        *(u16 *)(*(s32 *)(obj + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
        *(s16 *)(obj + 0xA) += 0x120;
        *(s32 *)(arg0 + 0xCC) = obj;
        *(u16 *)(arg0 + 0x34) += 1;
        *(u32 *)(*(s32 *)(obj + 0x20) + 4) |= 0x80000000;
    case 2:
        obj = func_8012C658(0x318, 2, arg0);
        if (obj == 0) {
            return;
        }
        *(s16 *)(obj + 0xA) += 0xC0;
        *(s32 *)(arg0 + 0xD0) = obj;
        *(u16 *)(arg0 + 0x34) += 1;
        *(u32 *)(*(s32 *)(obj + 0x20) + 4) |= 0x80000000;
    case 3:
        obj = func_8012C658(0x318, 2, arg0);
        if (obj == 0) {
            return;
        }
        *(s16 *)(obj + 0xA) += 0x60;
        *(u16 *)(arg0 + 0x34) = 10;
        *(s32 *)(arg0 + 0xD4) = obj;
        *(s32 *)(arg0 + 0x1C) = 2;
        return;
    case 4:
        obj = *(s32 *)(arg0 + 0xCC);
        *(s16 *)(obj + 0xA) -= 0x30;
        c4 = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = c4;
        if (c4 < 1) {
            *(s32 *)(arg0 + 0x1C) = 2;
            *(s16 *)(arg0 + 0xAE) = 0;
            *(u16 *)(arg0 + 0x34) += 1;
        }
        break;
    case 5:
        obj = *(s32 *)(arg0 + 0xCC);
        *(s16 *)(*(s32 *)(obj + 0x20) + 0x10) += 0x40;
        if (*(s16 *)(*(s32 *)(obj + 0x20) + 0x10) >= 0x200) {
            *(u16 *)(arg0 + 0x34) = 9;
        }
        obj = *(s32 *)(arg0 + 0xD0);
        *(s16 *)(obj + 0xFC) -= 0x40;
        obj = *(s32 *)(arg0 + 0xD4);
        *(s16 *)(obj + 0xFC) -= 0x40;
        break;
    case 6:
        func_8018D40C(*(s32 *)(arg0 + 0xCC));
        SYNC(0xCC, 0xD0)
        func_8018D514(*(s32 *)(arg0 + 0xD0));
        SYNC(0xD0, 0xD4)
        func_8018D514(*(s32 *)(arg0 + 0xD4));
        SYNC_LAST()
        BLIT()
        if ((*(s32 *)(arg0 + 0x1C) & 0xF) == 0) {
            *(s16 *)(arg0 + 0xFC) = rand() % 0x180 + 0x180;
        }
        c6a = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = c6a;
        if (c6a != 0) {
            return;
        }
        *(s32 *)(arg0 + 0x1C) = 0x10;
        c6b = func_8012BE54(arg0);
        if (c6b > 0x8FFFF) {
            return;
        }
        ENT_LOOP()
        *(s32 *)(arg0 + 0x1C) = 0x3C;
        *(u16 *)(arg0 + 0x34) += 1;
        func_8002D4C8(0x9BB, 0);
        return;
    case 7:
        c7 = func_8012BE54(arg0);
        if (c7 > 0x8FFFF) {
            goto L4AC;
        }
        ENT_LOOP()
        SYNC(0xCC, 0xD0)
        SYNC(0xD0, 0xD4)
        SYNC_LAST()
        BLIT()
        c7 = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = c7;
        if (c7 == 0) {
            *(u16 *)(arg0 + 0x34) += 1;
            *(s16 *)(arg0 + 0xDC) = D_80126B5E;
            *(s16 *)(arg0 + 0xDE) = D_80126B62 - 0x38;
            sv = D_80126B66;
            *(s32 *)(arg0 + 0x1C) = 0xF;
            *(s16 *)(arg0 + 0xE0) = sv;
            func_8002D4C8(0x9BC, 0);
            func_8012C658(0x318, 3, arg0);
            return;
        }
        sp20[0] = D_80126B5E;
        sp20[2] = D_80126B66;
        sp20[1] = D_80126B62 - 0x38;
        func_8004914C(*(s32 *)(arg0 + 0x20) + 0x34);
        func_800491AC(*(s32 *)(arg0 + 0x20) + 0x34);
        rp = D_801D1220;
        __asm__("" : "=r"(rp) : "0"(rp));
        bp = sp18;
        __asm__("" : "=r"(bp) : "0"(bp));
        RotTransSV(rp, bp, sp28);
        mode = 0x202080;
        if ((D_800B99D8 & 1) != 0) {
            mode = 0xE0;
        }
        bp2 = sp18;
        __asm__("" : "=r"(bp2) : "0"(bp2));
        func_8018FE0C(bp2, sp20, mode);
        return;
    case 8:
        c8 = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = c8;
        if (c8 == 0) {
            goto L4AC;
        }
        ENT_LOOP()
        break;
    L4AC:
        *(u16 *)(arg0 + 0x34) = 6;
        *(s32 *)(arg0 + 0x1C) = 0x96;
        return;
    case 9:
        obj = *(s32 *)(arg0 + 0xCC);
        *(s16 *)(*(s32 *)(obj + 0x20) + 0x10) -= 0x40;
        *(u16 *)(*(s32 *)(obj + 0x20) + 0x10) &= 0xFFF;
        if (*(s16 *)(*(s32 *)(obj + 0x20) + 0x10) == 0) {
            c9b = *(s32 *)(arg0 + 0x1C) - 1;
            *(s32 *)(arg0 + 0x1C) = c9b;
            if (c9b != 0) {
                *(u16 *)(arg0 + 0x34) = 5;
            } else {
                *(u16 *)(arg0 + 0x34) = 6;
                *(s32 *)(arg0 + 0x1C) = 0x1E;
            }
        }
        obj = *(s32 *)(arg0 + 0xD0);
        *(s16 *)(obj + 0xFC) += 0x40;
        obj = *(s32 *)(arg0 + 0xD4);
        *(s16 *)(obj + 0xFC) += 0x40;
        break;
    case 10:
        obj = *(s32 *)(arg0 + 0xCC);
        *(s16 *)(obj + 0xA) -= 0x30;
        c10 = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = c10;
        if (c10 < 1) {
            *(s32 *)(arg0 + 0x1C) = 2;
            *(u16 *)(arg0 + 0x34) += 1;
        }
        obj = *(s32 *)(arg0 + 0xD0);
        goto L5F8;
    case 11:
        obj = *(s32 *)(arg0 + 0xCC);
        *(s16 *)(obj + 0xA) -= 0x30;
        c11 = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = c11;
        if (c11 < 1) {
            *(u16 *)(arg0 + 0x34) = 4;
            *(s32 *)(arg0 + 0x1C) = 2;
        }
    L5F8:
        *(u32 *)(*(s32 *)(obj + 0x20) + 4) &= 0x7FFFFFFF;
        break;
    default:
        return;
    }
    SYNC(0xCC, 0xD0)
    SYNC(0xD0, 0xD4)
    SYNC_LAST()
}

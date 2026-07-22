// @class: regalloc-order
// @stuck: none — MATCH (673 ins)
#include "common.h"

extern s32 func_8012BE54(s32);
extern void func_8001C214(s32, void *);
extern void func_8012A828(s32, void *);
extern s32 func_8012C658(s32, s32, s32);
extern void func_8018D40C(s32);
extern void func_8012B2CC(s32);
extern void func_8012F14C(s32, void *, void *);
extern void func_8018D514(s32);
extern void func_8012B77C(void *, void *, void *);
extern s32 rand(void);
extern void func_8002D4C8(s32, s32);
extern void func_8004914C(s32);
extern void func_800491AC(s32);
extern void RotTransSV(void *, void *, void *);
extern void func_8018FE0C(void *, void *, s32);

extern u8 D_801D16C0[];
extern u8 D_801D11B4[];
extern u8 D_801D109C[];
extern u8 D_801D11F8[];
extern u8 D_80126B5C[];
extern u8 D_801202A0[];
extern u8 D_801D1220[];
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_800B99D8;

#define XFER(SRCOFF, DSTOFF)                                                                      \
    src = *(s32 *)(arg0 + SRCOFF);                                                                \
    func_8012B2CC(src);                                                                           \
    mp = D_801D11F8;                                                                              \
    __asm__ __volatile__("" : "=r"(mp) : "0"(mp));                                                \
    func_8012F14C(*(s32 *)(src + 0x20) + 0x34, mp, sp10);                       \
    dst = *(s32 *)(arg0 + DSTOFF);                                                                \
    *(u16 *)(dst + 6) = sp10[0];                                                                  \
    *(u16 *)(dst + 0xA) = sp10[1];                                                                \
    *(u16 *)(dst + 0xE) = sp10[2];                                                                \
    *(u16 *)(*(s32 *)(dst + 0x20) + 0x10) =                                                       \
        *(u16 *)(dst + 0xFC) + *(u16 *)(*(s32 *)(src + 0x20) + 0x10);                             \
    *(u16 *)(*(s32 *)(dst + 0x20) + 0x12) =                                                       \
        *(u16 *)(dst + 0xFE) + *(u16 *)(*(s32 *)(src + 0x20) + 0x12);

#define XFERLAST(SRCOFF)                                                                          \
    src = *(s32 *)(arg0 + SRCOFF);                                                                \
    func_8012B2CC(src);                                                                           \
    mp = D_801D11F8;                                                                              \
    __asm__ __volatile__("" : "=r"(mp) : "0"(mp));                                                \
    func_8012F14C(*(s32 *)(src + 0x20) + 0x34, mp, sp10);                       \
    *(u16 *)(arg0 + 6) = sp10[0];                                                                 \
    *(u16 *)(arg0 + 0xA) = sp10[1];                                                               \
    *(u16 *)(arg0 + 0xE) = sp10[2];

#define SCAN()                                                                                    \
    p = (u8 *)D_801202A0;                                                                         \
    i = 0;                                                                                        \
    do {                                                                                          \
        if (*(u16 *)p == 0x318 && p != (u8 *)arg0 &&                                              \
            (*(s16 *)(p + 0x70) == 0 || *(s16 *)(p + 0x70) == 6) &&                               \
            *(u16 *)(p + 0x34) == 6 && *(s32 *)(p + 0x1C) < 0x11) {                               \
            *(s32 *)(p + 0x1C) = *(s32 *)(p + 0x1C) + 0x10;                                       \
        }                                                                                         \
        p += 0x10C;                                                                               \
        i += 1;                                                                                   \
    } while (i < 0x60);

void func_8019059C(s32 _arg0) {
    register s32 arg0 __asm__("$17");
    register s32 src __asm__("$16");
    register s32 dst __asm__("$3");
    s32 r;
    s32 iv;
    register s32 tmp __asm__("$2");
    s32 col;
    s32 n34;
    s32 sv;
    s32 sw2;
    s32 sv2;
    s32 sw3;
    s16 nv;
    u8 *p;
    s32 i;
    s32 cnt;
    register s32 e5 __asm__("$4");
    u8 *mp;
    u8 *mm;
    u16 *m18;
    u16 *m18b;
    u16 sp10[4];
    u16 sp18[4];
    s16 sp20[4];
    u16 sp28[4];

    arg0 = _arg0;
    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        if (func_8012BE54(arg0) > 0x3FFFF) {
            return;
        }
        iv = 0x200;
        *(u16 *)(arg0 + 0x34) = 9;
        func_8001C214(*(s32 *)(arg0 + 0x20), D_801D16C0);
        *(s32 *)(arg0 + 0x58) = (s32)((u32)D_801D109C | 0x40000000 | 0x20000000);
        func_8012A828(arg0, D_801D11B4);
        *(u8 *)(arg0 + 0x75) = 8;
        *(u16 *)(arg0 + 0xAE) = 0;
        do {
            r = func_8012C658(0x318, 1, arg0);
            if (r != 0) {
                *(u16 *)(*(s32 *)(r + 0x20) + 0x12) = iv;
                *(s32 *)(r + 0x1C) = 0x18;
                *(u16 *)(r + 0xFC) = *(u16 *)(arg0 + 0x36);
            }
            iv += 0x400;
        } while (iv < 0x1000);
        tmp = 0x32;
        goto L80191000;
    case 9:
        *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) - 1;
        r = func_8012C658(0x318, 9, arg0);
        if (r == 0) {
            return;
        }
        *(s32 *)(arg0 + 0xD8) = r;
        *(u16 *)(arg0 + 0x34) = 1;
        *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;
        /* fallthrough */
    case 1:
        *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) - 1;
        r = func_8012C658(0x318, 2, arg0);
        if (r == 0) {
            return;
        }
        *(u16 *)(r + 0xA) = *(u16 *)(r + 0xA) - 0x60;
        *(u16 *)(*(s32 *)(r + 0x20) + 0x10) = 0xC00;
        *(s32 *)(arg0 + 0xCC) = r;
        n34 = *(u16 *)(arg0 + 0x34) + 1;
        *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;
        *(u16 *)(arg0 + 0x34) = n34;
        /* fallthrough */
    case 2:
        *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) - 1;
        r = func_8012C658(0x318, 2, arg0);
        if (r == 0) {
            return;
        }
        *(u16 *)(r + 0xFC) = 0x600;
        *(s32 *)(arg0 + 0xD0) = r;
        n34 = *(u16 *)(arg0 + 0x34) + 1;
        *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;
        *(u16 *)(arg0 + 0x34) = n34;
        /* fallthrough */
    case 3:
        *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) - 1;
        r = func_8012C658(0x318, 2, arg0);
        if (r == 0) {
            return;
        }
        *(u16 *)(r + 0xFC) = 0x600;
        *(s32 *)(arg0 + 0xD4) = r;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        return;
    case 4:
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt < 1) {
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        }
        break;
    case 5:
        e5 = *(s32 *)(arg0 + 0xCC);
        *(u16 *)(*(s32 *)(e5 + 0x20) + 0x10) = *(u16 *)(*(s32 *)(e5 + 0x20) + 0x10) + 0x40;
        e5 = *(s32 *)(arg0 + 0xD0);
        *(u16 *)(e5 + 0xFC) = *(u16 *)(e5 + 0xFC) - 0x60;
        e5 = *(s32 *)(arg0 + 0xD4);
        nv = *(u16 *)(e5 + 0xFC) - 0x60;
        *(s16 *)(e5 + 0xFC) = nv;
        if (nv == 0) {
            e5 = *(s32 *)(arg0 + 0xCC);
            *(s32 *)(arg0 + 0x1C) = 0x96;
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            *(u16 *)(*(s32 *)(e5 + 0x20) + 0x10) = 0;
        }
        break;
    case 6:
        func_8018D40C(*(s32 *)(arg0 + 0xCC));
        XFER(0xCC, 0xD0)
        func_8018D514(*(s32 *)(arg0 + 0xD0));
        XFER(0xD0, 0xD4)
        func_8018D514(*(s32 *)(arg0 + 0xD4));
        XFERLAST(0xD4)
        func_8012B77C(sp10, (void *)(arg0 + 4), D_80126B5C);
        tmp = *(s32 *)sp10;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x10) = tmp;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = tmp >> 16;
        if ((*(s32 *)(arg0 + 0x1C) & 0xF) == 0) {
            *(u16 *)(arg0 + 0xFC) = rand() % 0xA0 + 0x100;
        }
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt != 0) {
            return;
        }
        *(s32 *)(arg0 + 0x1C) = 0x10;
        if (func_8012BE54(arg0) > 0x8FFFF) {
            return;
        }
        SCAN()
        *(s32 *)(arg0 + 0x1C) = 0x3C;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        func_8002D4C8(0x9BB, 0);
        return;
    case 7:
        if (func_8012BE54(arg0) > 0x8FFFF) {
            tmp = 6;
            goto L80190FF8;
        }
        SCAN()
        XFER(0xCC, 0xD0)
        XFER(0xD0, 0xD4)
        XFERLAST(0xD4)
        func_8012B77C(sp10, (void *)(arg0 + 4), D_80126B5C);
        tmp = *(s32 *)sp10;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x10) = tmp;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = tmp >> 16;
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt == 0) {
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            *(u16 *)(arg0 + 0xDC) = D_80126B5E;
            tmp = D_80126B62 - 0x38;
            *(u16 *)(arg0 + 0xDE) = tmp;
            dst = D_80126B66;
            tmp = 0xF;
            *(s32 *)(arg0 + 0x1C) = tmp;
            *(u16 *)(arg0 + 0xE0) = dst;
            func_8012C658(0x318, 3, arg0);
            func_8002D4C8(0x9BC, 0);
            return;
        }
        sv = D_80126B5E;
        sp20[0] = sv;
        sw2 = D_80126B66;
        sp20[2] = sw2;
        sv = D_80126B62 - 0x38;
        sp20[1] = sv;
        func_8004914C(*(s32 *)(arg0 + 0x20) + 0x34);
        func_800491AC(*(s32 *)(arg0 + 0x20) + 0x34);
        mm = D_801D1220;
        __asm__ __volatile__("" : "=r"(mm) : "0"(mm));
        m18 = sp18;
        __asm__ __volatile__("" : "=r"(m18) : "0"(m18));
        RotTransSV(mm, m18, sp28);
        col = 0x202080;
        if ((D_800B99D8 & 1) != 0) {
            col = 0xE0;
        }
        m18b = sp18;
        __asm__ __volatile__("" : "=r"(m18b) : "0"(m18b));
        func_8018FE0C(m18b, sp20, col);
        return;
    case 8:
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt == 0) {
            goto L80190FF4;
        }
        SCAN()
        break;
    default:
        return;
    }

    XFER(0xCC, 0xD0)
    XFER(0xD0, 0xD4)
    XFERLAST(0xD4)
    return;

L80190FF4:
    tmp = 6;
L80190FF8:
    *(u16 *)(arg0 + 0x34) = tmp;
    tmp = 0x96;
L80191000:
    *(s32 *)(arg0 + 0x1C) = tmp;
}

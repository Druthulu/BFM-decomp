#include "common.h"

extern u8 D_8011F7F0;
extern u8 D_8018A1DC[];
typedef struct { s32 unk0; s32 count; s32 buf; } AFEntry;
extern AFEntry D_800AF630[];
extern u8 D_800B9A13;
extern u16 D_8018A238;
extern u16 D_8018A22C[];
extern u8 D_8018A2CC[];
extern u8 D_8018A2B8[];
extern s32 D_8018A2E4[];
extern u8 D_800D45D4;
extern u8 D_800D43D4;
extern u8 D_800D4414;

extern s32 *func_8017742C(s32 *a0, s16 a1, s16 a2, s32 a3);
extern void func_8005A600(s32 *a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_800183E0(void *a0, void *a1);

void func_80175DA8(s16 arg0) {
    register u8 *base __asm__("$18");
    u8 *s1;
    u8 *src = D_8018A1DC;
    u8 *s0;
    s32 i;
    register s32 t __asm__("$3");
    s32 cond;

    base = &D_8011F7F0;
    s1 = base - 0x48;
    s0 = (u8 *)(D_800AF630[arg0].buf + (D_800AF630[arg0].count << 2));
    *(s32 *)(s1 + arg0 * 4 + 0x28) = (s32)s0;
    i = 0;
    do {
        *(u32 *)s0 = (((u32)s0 - 0x14) & 0xFFFFFF) | 0x4000000;
        *(u32 *)(s0 + 4) = *(u32 *)src;
        __asm__("" : "=r"(i) : "0"(i));
        src += 4;
        if ((s16)i < 2) {
            *(s16 *)(s0 + 8) = *(u16 *)src + *(u16 *)(s1 + 0xC);
            src += 2;
            *(s16 *)(s0 + 0xA) = *(u16 *)src + *(u16 *)(s1 + 0xE);
            src += 2;
        } else if ((s16)i == 2) {
            *(s16 *)(s0 + 8) = *(u16 *)src + *(u16 *)(s1 + 0x10);
            src += 2;
            *(s16 *)(s0 + 0xA) = *(u16 *)src + *(u16 *)(s1 + 0x12);
            src += 2;
        } else {
            *(s16 *)(s0 + 8) = *(u16 *)src + *(u16 *)(s1 + 0x14);
            src += 2;
            *(s16 *)(s0 + 0xA) = *(u16 *)src + *(u16 *)(s1 + 0x16);
            src += 2;
        }
        *(u32 *)(s0 + 0xC) = *(u32 *)src;
        src += 4;
        t = i + 1;
        cond = (s16)t < 5;
        i = t;
        *(u32 *)(s0 + 0x10) = *(u32 *)src;
        src += 4;
        s0 += 0x14;
    } while (cond);

    *(u8 *)(s1 + 7) = D_800B9A13;
    s0 = (u8 *)func_8017742C((s32 *)s0,
                             (s16)(*(u16 *)(s1 + 0x10) - 0x98),
                             (s16)(*(u16 *)(s1 + 0x12) + 9),
                             i);
    func_8005A600((s32 *)s0, 0, 0, 0x16, 0);
    *(u32 *)s0 = (((u32)s0 - 0x14) & 0xFFFFFF) | 0x2000000;
    *(s32 *)(s1 + arg0 * 4 + 0x30) = (s32)s0;
    s0 += 0x14;
    D_800AF630[arg0].count +=
        ((s32)s0 - *(s32 *)(s1 + arg0 * 4 + 0x28)) >> 2;
    s0 = (u8 *)*(s32 *)(s1 + arg0 * 4 + 0x28);
    if (base[0x48] != 0) {
        *(u8 *)(s0 + 0xD) = 0;
    } else {
        *(u8 *)(s0 + 0xD) = 0xA0;
    }

    {
        void *arg;
        u8 *q = (u8 *)*(s32 *)(s1 + arg0 * 4 + 0x28);
        s32 c;
        *(s16 *)(q + 0x22) = 0x6CD6;
        c = base[0x48];
        if (c & 0x80) {
            arg = &D_800D45D4;
            *(s16 *)(q + 0x20) = D_8018A238;
        } else {
            u16 *p = &D_8018A22C[0];
            if ((c & 0xFF) != 0) {
                p = (u16 *)((u8 *)&D_8018A22C[0] + ((c & 0xFF) - 1) * 2);
            }
            *(s16 *)(q + 0x20) = *p;
            arg = (void *)D_8018A2E4[base[0x48]];
        }
        func_800183E0(arg, q);
    }

    {
        u8 *q = (u8 *)*(s32 *)(s1 + arg0 * 4 + 0x28);
        s32 h = *(u16 *)(base + 0x2E) << 16;
        if (h != 0) {
            *(u8 *)(q + 0x49) = D_8018A2CC[h >> 20];
        } else {
            *(u8 *)(q + 0x49) = 0xA0;
        }
    }

    {
        u8 *q = (u8 *)*(s32 *)(s1 + arg0 * 4 + 0x28);
        void *arg;
        u16 w = *(u16 *)(base + 0x40);
        if (w < 0x64) {
            *(u8 *)(q + 0x5D) = D_8018A2B8[w / 5];
        } else {
            *(u8 *)(q + 0x5D) = 0;
        }
        {
            s32 flag = *(s16 *)(base + 0x1E) & 0x8000;
            __asm__("");
            arg = &D_800D43D4;
            if (flag) {
                arg = &D_800D4414;
            }
        }
        func_800183E0(arg, q);
    }
}

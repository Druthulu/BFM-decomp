#include "common.h"

typedef struct { s32 a, b, c, d; } Blk16;

typedef struct {
    u8 pad0[0x1C];
    s16 f1C;
    s16 f1E;
    u8 pad20[0x14];
    u16 f34;
    u16 f36;
    u16 f38;
    u16 f3A;
    u8 pad3C[2];
    s16 f3E;
    u16 f40;
    u16 f42;
    u8 pad44[0x10];
} Ent;

extern s16 D_80114EE0;
extern u8 D_800B9A78[];
extern u8 D_801D9484[];
extern u8 D_801D9485[];
extern u8 D_801D9486[];
extern u8 D_801D9488[];
extern u8 D_801D9489[];
extern u8 D_801D948A[];
extern u8 D_801DAAA0;
extern u8 D_800AF630[];
extern u8 D_800A6518[];

extern void func_801299C8();
extern void func_80015B6C(s32, s16, s32, s16, s32, s32, s32, s32, s32, s32);
extern void GsSortBg(s32 *, void *, u16, s32 *);
extern void GsSortFastBg(s32 *, void *, u16, s32 *);

void func_8012956C(void) {
    register s32 *sp10 __asm__("$21");
    register u8 *afbase __asm__("$22");
    register s32 *sp0 __asm__("$23");
    Ent *base;
    s32 i;
    s16 a1;
    register u32 temp_a3 __asm__("$7");
    register u32 arg0 __asm__("$4");
    register u32 s __asm__("$2");
    register u32 s2 __asm__("$3");
    register u32 t6 __asm__("$8");
    s32 code;

    sp10 = (s32 *)0x1F800010;
    sp0 = (s32 *)0x1F800000;
    afbase = (u8 *)&D_800AF630;
    if (D_80114EE0 == 0) {
        return;
    }
    base = (Ent *)&D_800B9A78;
    __asm__("" : "=r"(base) : "0"(base));
    i = 0;
    do {
        s32 idx = i * 8 + 4;
        code = base->f34;
        if (code == 0x7FFE) {
            goto case_7FFE;
        }
        if (code < 0x7FFF) {
            a1 = i + 3;
            if (code == 0x7FFD) {
                goto case_7FFD;
            }
            goto do_default;
        }
        a1 = i + 3;
        if (code != 0x7FFF) {
            goto do_default;
        }
        goto next;
    case_7FFD:
        if (i == 0) {
            func_801299C8(D_801DAAA0, 1, base);
        }
        func_80015B6C(-0xA0, -0x74, 0x140, 0x8C,
                      D_801D9488[0], D_801D9488[1], D_801D9488[2],
                      D_801D9488[4], D_801D9488[5], D_801D9488[6]);
        func_80015B6C(-0xA0, 0x18, 0x140, 0x3C,
                      D_801D9488[4], D_801D9488[5], D_801D9488[6],
                      D_801D9488[8], D_801D9488[9], D_801D9488[0xA]);
        func_80015B6C(-0xA0, 0x54, 0x140, 0x28,
                      D_801D9488[8], D_801D9488[9], D_801D9488[0xA],
                      D_801D9488[0xC], D_801D9488[0xD], D_801D9488[0xE]);
        goto next;
    case_7FFE:
        func_801299C8(D_801DAAA0, (s16)(i * 2), base);
        func_80015B6C(-0xA0, *(s16 *)&base->f3A, 0x140, base->f3E,
                      D_801D9484[idx], D_801D9485[idx], D_801D9486[idx],
                      D_801D9488[idx], D_801D9489[idx], D_801D948A[idx]);
        goto next;
    do_default:
        __asm__("");
        arg0 = D_801DAAA0;
        s = base->f40;
        temp_a3 = base->f38;
        s += temp_a3;
        base->f1C = s;
        s2 = base->f42;
        t6 = base->f3A;
        s2 += t6;
        base->f1E = s2;
        func_801299C8(arg0, a1, base, temp_a3);
        *(Blk16 *)sp0 = *(Blk16 *)base;
        {
            s32 *dst = sp10;
            s32 *src = (s32 *)((u8 *)base + 0x10);
            s32 *end = (s32 *)((u8 *)base + 0x30);
            do {
                *(Blk16 *)dst = *(Blk16 *)src;
                src += 4;
                dst += 4;
            } while (src != end);
            *dst = *src;
            sp10[5] = (s32)sp0;
            if (base->f36 == 0) {
                GsSortFastBg(sp10, &D_800A6518[(*(u16 *)(afbase + 0xA3D2)) * 0x14], base->f34, dst);
            } else {
                GsSortBg(sp10, &D_800A6518[(*(u16 *)(afbase + 0xA3D2)) * 0x14], base->f34, dst);
            }
        }
    next:
        base += 1;
        i += 1;
    } while (i < 2);
}

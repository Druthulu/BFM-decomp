"""Per-case C bodies for func_80183814.  Spawn-template sites are the single line
`/*TEMPLATE(K,S,B)*/`; build.py expands them from the byte-verified mktmpl.py."""

HEADER = r'''#include "common.h"

extern s32 func_8004787C(s32 a0);
extern void func_8017FDF8(s32 a0);
extern void func_8017F9AC(s32 a0, void *a1);
extern void func_8017D8A4(s32 a0, void *a1, void *a2, s32 a3, s32 a4);
extern void func_800599B8(void *a0, s32 a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8017F5D4(s32 a0);
extern void func_801805D4(s32 a0, void *a1);
extern void func_8001C214(s32 a0, void *a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80016224(s32 a0, s32 a1);
extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);
extern void func_8012F14C(s32 *a0, s32 a1, s16 *a2);
extern s32 func_8012C51C(s16 *a0, s32 a1);
extern s32 rand(void);
extern s32 func_80178970(s32 a0);
extern void func_80178D18(s32 a0);
extern void func_801802EC(s32 a0);
extern void func_80180924(s32 a0);
extern void func_80180CFC(s32 a0, void *a1);
extern void func_80181148(s32 a0);
extern void func_8018163C(s32 a0);
extern void func_80181924(s32 a0, void *a1);
extern void func_80182268(s32 a0, s32 a1);
extern void func_801823F8(s32 a0);
extern void func_801826E0(s32 a0, s32 a1);
extern void func_801828A4(s32 a0);
extern void func_80182B8C(s32 a0, s32 a1);
extern void func_80181E64(s32 a0, s32 a1);
extern void func_80182000(s32 a0, s32 a1);
extern void func_80182158(s32 a0);
extern void func_80181C74(s32 a0, s32 a1);
extern void func_80182D4C(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, void *a2);
extern s32 func_80143C74(s32 a0, s32 a1);

extern u8 D_8018E27C;
extern u8 D_8018E288;
extern u8 D_8018E294;
extern u8 D_8018E2A0;
extern u8 D_8018E2DC;
extern u8 D_8018E2E8;
extern u8 D_8018E2F4;
extern u8 D_8018E300;
extern u8 D_8018DFC0;
extern u8 D_8018DFC8;
extern u8 D_8018DFD0;
extern u8 D_8018DFD8;
extern u8 D_8018DFE0;
extern u8 D_8018DFE8;
extern u8 D_8018DFF0;
extern u8 D_8018DFF8;
extern u8 D_8018E000;
extern u8 D_8018E008;
extern u8 D_8018E010;
extern u8 D_8018E018;
extern s32 D_8018E034[];
extern u8 D_8018DF10;
extern s32 D_801BFCB4;
extern s32 D_801BFCBC;
extern s32 D_801BFCC4;
extern u8 D_801BF540;
extern u8 D_801BF588;
extern u8 D_801BFCCC;
extern s32 *D_801BF5CC;
extern u8 D_801BF630;
extern u8 D_801BFCDC;
extern u8 D_801BF658;
extern u8 D_801BFCE4;
extern u8 D_801BF68C;
extern u8 D_801BFCEC;
extern u8 D_801CAA38;
extern u8 D_8018E020;
extern u8 D_8018E028;
extern u8 D_8018E030;
extern u8 D_8018E3A8;
extern u8 D_801BF60C;
extern s32 D_801BFCD4;
extern s16 *D_801C1E14;
extern s16 *D_801C1E18;
extern u8 D_801BF6CC;
extern u8 D_801CA678;
extern s32 *D_801BF604;
extern s32 *D_801BF650;
extern s16 *D_801C1EA0;
extern s16 *D_801C1EA4;
extern s16 *D_801C1EA8;
extern s32 D_801F61C0[];

'''

PREAMBLE = r'''void func_80183814(void *a0) {
    s32 sp18[8];
    s16 sp38[4];
    s16 sp40[10];
    s32 s3;
    s32 s0;
    s32 s1;
    s32 s4;
    s32 s5;
    s32 c;
    s32 r;
    s32 t;
    s32 idx;
    s32 ok;
    s32 *p;
    s32 *q;

    s0 = func_8004787C(*(s16 *)((s32)a0 + 0xFC));
    s3 = s0 + (func_8004787C(*(s16 *)((s32)a0 + 0xFE)) >> 4);
    *(u16 *)((s32)a0 + 0xFE) = (*(u16 *)((s32)a0 + 0xFE) + 0x300) & 0xFFF;
    if (*(u16 *)((s32)a0 + 0x34) < 0x11) {
        *(s32 *)((s32)a0 + 0x8) =
            (*(s16 *)((s32)a0 + 0x8A) << 16) +
            (func_8004787C(*(s16 *)((s32)a0 + 0x104)) << 7);
        *(u16 *)((s32)a0 + 0x104) = *(u16 *)((s32)a0 + 0x104) + 0x40;
    }

    switch (*(u16 *)((s32)a0 + 0x34)) {
'''

TAIL = r'''    }

    if (func_80178970((s32)a0) != 0) {
        func_80178D18((s32)a0);
        *(s16 *)((s32)a0 + 0x2) = 3;
    }
}
'''

# ---------------------------------------------------------------- the "audio ramp"
# 6 copies of the func_8004787C / func_800599B8 ramp.  SYM = &D_8018DFxx, K = index bias.


def ramp(syms, ks, first_direct, guard, div=455):
    o = []
    for n, (sym, k) in enumerate(zip(syms, ks)):
        last = (n == len(syms) - 1)
        o.append('        r = func_8004787C(*(s16 *)((s32)a0 + 0xFC));\n')
        o.append('        c = (s16) * (u16 *)((s32)a0 + 0x102);\n')
        o.append('        if (r >= c) {\n')
        o.append('            s32 t, idx;\n')
        o.append('            t = (s16)(c / %d);\n' % div)
        o.append('            if (t >= 10) {\n')
        o.append('                t = 9;\n')
        o.append('            }\n')
        if n == 0 and first_direct:
            o.append('            func_800599B8(&%s, D_8018E034[t]);\n' % sym)
        else:
            o.append('            idx = t + %s;\n' % k)
            o.append('            func_800599B8(&%s, D_8018E034[idx]);\n' % sym)
        if last:
            o.append('            ok = 1;\n        } else {\n            ok = 0;\n        }\n')
            o.append('        if (ok != 0) {\n')
            o.append('            *(u16 *)((s32)a0 + 0x102) = '
                     '*(u16 *)((s32)a0 + 0x102) + %s;\n' % guard)
            o.append('        }\n')
        else:
            o.append('        }\n')
    return ''.join(o)


RAMP_A = ramp(['D_8018DFC0', 'D_8018DFC8', 'D_8018DFD0', 'D_8018DFD8',
               'D_8018DFE0', 'D_8018DFE8'],
              ['0', '9', '0x12', '0x1B', '0x24', '0x2D'], True, '0x1C7')
RAMP_B = ramp(['D_8018DFF0', 'D_8018DFF8', 'D_8018E000', 'D_8018E008',
               'D_8018E010', 'D_8018E018'],
              ['0x36', '0x3F', '0x48', '0x51', '0x5A', '0x63'], False, '0x1C7')
RAMP_409 = ramp(['D_8018E030', 'D_8018E020', 'D_8018E028'],
                ['0x7E', '0x6C', '0x75'], False, '0x199', div=409)
RAMP_B199 = ramp(['D_8018DFF0', 'D_8018DFF8', 'D_8018E000', 'D_8018E008',
                  'D_8018E010', 'D_8018E018'],
                 ['0x36', '0x3F', '0x48', '0x51', '0x5A', '0x63'], False, '0x199')

# ---------------------------------------------------------------- cases

C00 = r'''        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 8;
        func_8017F9AC(s3, a0);
        func_8017D8A4(D_801BFCB4 + 0x3C, &D_8018E27C, &D_8018E27C + 0x30, s3, 1);
        func_8017D8A4(D_801BFCB4 + 0x48, &D_8018E288, &D_8018E288 + 0x30, s3, 1);
        func_8017D8A4(D_801BFCB4 + 0x54, &D_8018E294, &D_8018E294 + 0x30, s3, 1);
        func_8017D8A4(D_801BFCB4 + 0x60, &D_8018E2A0, &D_8018E2A0 + 0x30, s3, 1);
        func_8017FDF8(func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
''' + RAMP_A + r'''        if (*(s16 *)((s32)a0 + 0xFC) != 0x200) {
            break;
        }
        s1 = 0;
        do {
            s0 = func_8012C658(0x3AC, 0, (s32)a0);
            if (s0 != 0) {
                *(u16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) - 0x2D;
                *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x47;
                *(u16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) - 5;
            }
            s1 += 1;
        } while (s1 < 0x10);
        func_8002D4C8(0xBBE, 0);
        func_8017F5D4(0x1000);
        func_8017D8A4(D_801BFCB4 + 0x3C, &D_8018E27C, &D_8018E27C + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCB4 + 0x48, &D_8018E288, &D_8018E288 + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCB4 + 0x54, &D_8018E294, &D_8018E294 + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCB4 + 0x60, &D_8018E2A0, &D_8018E2A0 + 0x30, 0x1000, 1);
        *(u16 *)((s32)a0 + 0x34) = 1;
        func_801805D4(s3, a0);
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF540);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801BFCBC);
        func_8017D8A4(D_801BFCBC + 0x3C, &D_8018E2DC - 0x60, &D_8018E2DC - 0x30, s3, 1);
        func_8017D8A4(D_801BFCBC + 0x48, &D_8018E2E8 - 0x60, &D_8018E2E8 - 0x30, s3, 1);
        func_8017D8A4(D_801BFCBC + 0x54, &D_8018E2F4 - 0x60, &D_8018E2F4 - 0x30, s3, 1);
'''

C01 = r'''        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 8;
        func_801805D4(s3, a0);
        func_8017D8A4(D_801BFCBC + 0x3C, &D_8018E27C, &D_8018E27C + 0x30, s3, 1);
        func_8017D8A4(D_801BFCBC + 0x48, &D_8018E288, &D_8018E288 + 0x30, s3, 1);
        func_8017D8A4(D_801BFCBC + 0x54, &D_8018E294, &D_8018E294 + 0x30, s3, 1);
        func_8017FDF8(func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
''' + RAMP_A + r'''        if (*(s16 *)((s32)a0 + 0xFC) < 0x400) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0xA;
        func_801802EC(0x1000);
        func_8017D8A4(D_801BFCBC + 0x3C, &D_8018E27C, &D_8018E27C + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCBC + 0x48, &D_8018E288, &D_8018E288 + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCBC + 0x54, &D_8018E294, &D_8018E294 + 0x30, 0x1000, 1);
        func_8017FDF8(0x1000);
'''

C02 = r'''        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 3;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(u16 *)((s32)a0 + 0x102) = 0x1C7;
        func_8002D4C8(0xBB6, 0);
'''

C03 = r'''        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 8;
        func_80180CFC(s3, a0);
        func_8017D8A4(D_801BFCBC + 0x84, &D_8018E2DC, &D_8018E2DC + 0x30, s3, 1);
        func_8017D8A4(D_801BFCBC + 0x90, &D_8018E2E8, &D_8018E2E8 + 0x30, s3, 1);
        func_8017D8A4(D_801BFCBC + 0x9C, &D_8018E2F4, &D_8018E2F4 + 0x30, s3, 1);
        func_8017D8A4(D_801BFCBC + 0xA8, &D_8018E300, &D_8018E300 + 0x30, s3, 1);
        func_80181148(func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
''' + RAMP_B + r'''        if (*(s16 *)((s32)a0 + 0xFC) < 0x200) {
            break;
        }
        s1 = 0;
        do {
            s0 = func_8012C658(0x3AC, 0, (s32)a0);
            if (s0 != 0) {
                *(u16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + 0x2D;
                *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x47;
                *(u16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) - 5;
            }
            s1 += 1;
        } while (s1 < 0x10);
        func_8002D4C8(0xBBE, 0);
        func_80180924(0x1000);
        func_8017D8A4(D_801BFCBC + 0x84, &D_8018E2DC, &D_8018E2DC + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCBC + 0x90, &D_8018E2E8, &D_8018E2E8 + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCBC + 0x9C, &D_8018E2F4, &D_8018E2F4 + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCBC + 0xA8, &D_8018E300, &D_8018E300 + 0x30, 0x1000, 1);
        *(u16 *)((s32)a0 + 0x34) = 4;
        func_80181924(s3, a0);
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF588);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801BFCC4);
        func_8017D8A4(D_801BFCC4 + 0x84, &D_8018E27C + 0x60, &D_8018E27C + 0x90, s3, 1);
        func_8017D8A4(D_801BFCC4 + 0x90, &D_8018E288 + 0x60, &D_8018E288 + 0x90, s3, 1);
        func_8017D8A4(D_801BFCC4 + 0x9C, &D_8018E294 + 0x60, &D_8018E294 + 0x90, s3, 1);
'''

C04 = r'''        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 8;
        func_80181924(s3, a0);
        func_8017D8A4(D_801BFCC4 + 0x84, &D_8018E2DC, &D_8018E2DC + 0x30, s3, 1);
        func_8017D8A4(D_801BFCC4 + 0x90, &D_8018E2E8, &D_8018E2E8 + 0x30, s3, 1);
        func_8017D8A4(D_801BFCC4 + 0x9C, &D_8018E2F4, &D_8018E2F4 + 0x30, s3, 1);
        func_80181148(func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
''' + RAMP_B199 + r'''        if (*(s16 *)((s32)a0 + 0xFC) < 0x400) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 5;
        *(s32 *)((s32)a0 + 0x1C) = 0xA;
        func_8018163C(0x1000);
        func_8017D8A4(D_801BFCC4 + 0x84, &D_8018E2DC, &D_8018E2DC + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCC4 + 0x90, &D_8018E2E8, &D_8018E2E8 + 0x30, 0x1000, 1);
        func_8017D8A4(D_801BFCC4 + 0x9C, &D_8018E2F4, &D_8018E2F4 + 0x30, 0x1000, 1);
        func_80181148(0x1000);
'''

C05 = r'''        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 6;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF5CC);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801BFCCC);
        func_8012C658(0x3AC, 1, (s32)a0);
        *(u16 *)((s32)a0 + 0x102) = 0x1C7;
        func_8002D4C8(0xBB9, 0);
        func_8002D4C8(0xC6F, 0);
'''

C07 = r'''        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 8;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_8002D4C8(0xBBC, 0);
'''

C10 = r'''        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 0xB;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF630);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801BFCDC);
        func_8002D4C8(0xBBF, 0);
'''

# the "morph/lerp" inline block used by cases 6 and 11
MORPH = r'''        {
            s32 *mp;
            s16 *md;
            s16 *msa;
            s16 *msb;
            s32 mn;
            s16 *pa;
            s16 *pb;

            mp = %(HDR)s;
            msb = %(SB)s;
            msa = %(SA)s;
            if (mp[1] == 1) {
                md = (s16 *)mp[3];
            } else {
                md = (s16 *)((u8 *)mp + ((((u32)mp[3] >> 2) << 2) + 0xC));
            }
            mn = mp[4];
            pb = msb;
            pa = msa;
            while (mn != 0) {
                md[0] = pb[0] + (((pa[0] - pb[0]) * %(F)s) >> 12);
                md[1] = pb[1] + (((pa[1] - pb[1]) * %(F)s) >> 12);
                md[2] = pb[2] + (((pa[2] - pb[2]) * %(F)s) >> 12);
                md += 4;
                pb += 4;
                pa += 4;
                mn--;
            }
        }
'''

C08 = r'''        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 8;
        func_80181E64(func_8004787C(*(s16 *)((s32)a0 + 0xFC)), (s32)a0);
        func_80182000((s32)a0, func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
        func_80182158(func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
''' + RAMP_409 + r'''        if (*(s16 *)((s32)a0 + 0xFC) < 0x200) {
            break;
        }
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF60C);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801BFCD4);
        func_8012C658(0x3AC, 2, (s32)a0);
        func_8012C658(0x3AC, 3, (s32)a0);
        *(u16 *)((s32)a0 + 0x34) = 9;
        func_80181E64(func_8004787C(*(s16 *)((s32)a0 + 0xFC)), (s32)a0);
        func_8017D8A4(D_801BFCD4, &D_8018E3A8, &D_8018E3A8 + 0xB4,
                      func_8004787C(*(s16 *)((s32)a0 + 0xFC)), 1);
'''

C09 = (r'''        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 8;
        func_80181E64(func_8004787C(*(s16 *)((s32)a0 + 0xFC)), (s32)a0);
        func_8017D8A4(D_801BFCD4, &D_8018E3A8, &D_8018E3A8 + 0xB4,
                      func_8004787C(*(s16 *)((s32)a0 + 0xFC)), 1);
        func_80182158(func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
''' + RAMP_409 + r'''        if (*(s16 *)((s32)a0 + 0xFC) >= 0x400) {
            *(u16 *)((s32)a0 + 0x34) = 0xA;
            *(s32 *)((s32)a0 + 0x1C) = 0xA;
            t = 0x1000;
''' + MORPH % dict(HDR='D_801BF5CC', SB='D_801C1E14', SA='D_801C1E18', F='t') +
       r'''            func_8017D8A4(D_801BFCD4, &D_8018E3A8, &D_8018E3A8 + 0xB4, 0x1000, 1);
            func_80182158(0x1000);
        }
        s0 = func_8012C658(0x3AC, 6, (s32)a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) - 0x20;
            *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x140;
            *(u16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) - 0x40;
            *(s16 *)(s0 + 0x12) = (rand() & 7) - 4;
            *(s16 *)(s0 + 0x16) = 0;
            *(s16 *)(s0 + 0x1A) = -((rand() & 7) + 0xA);
        }
        s0 = func_8012C658(0x3AC, 6, (s32)a0);
        if (s0 == 0) {
            break;
        }
        *(u16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) - 0x20;
        *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x140;
        *(u16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + 0x40;
        *(s16 *)(s0 + 0x12) = (rand() & 7) - 4;
        *(s16 *)(s0 + 0x16) = 0;
        *(s16 *)(s0 + 0x1A) = (rand() & 7) + 0xA;
''')

C06 = (r'''        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 8;
''' + MORPH % dict(HDR='D_801BF604', SB='D_801C1EA0', SA='D_801C1EA4', F='s3') +
       r'''        func_80181C74((s32)a0, s3);
        if (*(s16 *)((s32)a0 + 0xFC) < 0x400) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 7;
        *(s32 *)((s32)a0 + 0x1C) = 0xA;
        t = 0x1000;
''' + MORPH % dict(HDR='D_801BF604', SB='D_801C1EA0', SA='D_801C1EA4', F='t') +
       r'''        func_80181C74((s32)a0, 0x1000);
''')

C11 = (r'''        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 0x10;
        t = func_8004787C(*(s16 *)((s32)a0 + 0xFC));
''' + MORPH % dict(HDR='D_801BF650', SB='D_801C1EA4', SA='D_801C1EA8', F='t') +
       r'''        func_80182268((s32)a0, func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
        if (*(s16 *)((s32)a0 + 0xFC) >= 0x400) {
            *(u16 *)((s32)a0 + 0x34) = 0xC;
            *(s32 *)((s32)a0 + 0x1C) = 0x1E;
            t = 0x1000;
''' + MORPH % dict(HDR='D_801BF650', SB='D_801C1EA4', SA='D_801C1EA8', F='t') +
       r'''            func_80182268((s32)a0, 0x1000);
        }
/*TEMPLATE(0x8,0,8)*/
''')

C12 = r'''        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        *(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1;
/*TEMPLATE(0x8,0,8)*/
        if (*(s32 *)((s32)a0 + 0x1C) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 0xD;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF658);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801BFCE4);
        func_8002D4C8(0xBBD, 0);
'''

C13 = r'''        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 0x60;
        func_801823F8(func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
        func_801826E0((s32)a0, func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
        if (*(s16 *)((s32)a0 + 0xFC) >= 0x400) {
            *(u16 *)((s32)a0 + 0x34) = 0xE;
            *(s32 *)((s32)a0 + 0x1C) = 0x1E;
            func_801823F8(0x1000);
            func_801826E0((s32)a0, 0x1000);
        }
/*TEMPLATE(0x1,0,4)*/
/*TEMPLATE(0x2,4,8)*/
/*TEMPLATE(0xB,8,0xC)*/
'''

C14 = r'''/*TEMPLATE(0x1,0,4)*/
/*TEMPLATE(0x2,4,8)*/
/*TEMPLATE(0xB,8,0xC)*/
        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 0xF;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF68C);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801BFCEC);
        func_8002D4C8(0xBBD, 0);
'''

C15 = r'''        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) + 0x60;
        func_801828A4(func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
        func_80182B8C((s32)a0, func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
        if (*(s16 *)((s32)a0 + 0xFC) >= 0x400) {
            *(u16 *)((s32)a0 + 0x34) = 0x10;
            *(s32 *)((s32)a0 + 0x1C) = 0x1E;
            func_801828A4(0x1000);
            func_80182B8C((s32)a0, 0x1000);
        }
/*TEMPLATE(0x6,0,4)*/
/*TEMPLATE(0x7,4,8)*/
/*TEMPLATE(0x8,8,0xC)*/
'''

C16 = r'''/*TEMPLATE(0x6,0,4)*/
/*TEMPLATE(0x7,4,8)*/
/*TEMPLATE(0x8,8,0xC)*/
        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 0x11;
        *(s16 *)((s32)a0 + 0xFC) = 0;
'''

C17 = r'''        if (*(s16 *)((s32)a0 + 0xA) < -0x402) {
            *(s16 *)((s32)a0 + 0xA) = *(s16 *)((s32)a0 + 0xA) + 1;
        }
        *(u16 *)((s32)a0 + 0xFC) = *(u16 *)((s32)a0 + 0xFC) + 0x10;
        func_80182D4C((s32)a0, func_8004787C(*(s16 *)((s32)a0 + 0xFC)));
        if (*(s16 *)((s32)a0 + 0xFC) >= 0x400) {
            *(u16 *)((s32)a0 + 0x34) = 0x12;
            *(s32 *)((s32)a0 + 0x1C) = 3;
            func_80182D4C((s32)a0, 0x1000);
            func_8002D4C8(0xBC0, 0);
        }
/*TEMPLATE(0xD,0,6)*/
/*TEMPLATE(0xE,6,8)*/
/*TEMPLATE(0x1,8,0xA)*/
/*TEMPLATE(0x2,0xA,0xB)*/
/*TEMPLATE(0x6,0xB,0xD)*/
/*TEMPLATE(0x7,0xD,0xE)*/
/*TEMPLATE(0x8,0xE,0x10)*/
'''

C18 = r'''/*TEMPLATE(0xE,0,3)*/
/*TEMPLATE(0x1,3,5)*/
/*TEMPLATE(0x2,5,8)*/
/*TEMPLATE(0x6,8,0xB)*/
/*TEMPLATE(0x7,0xB,0xD)*/
/*TEMPLATE(0x8,0xD,0x10)*/
        if (*(s32 *)((s32)a0 + 0x1C) < 7) {
            func_80016224(0xFF, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 0x13;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_8001C214(*(s32 *)((s32)a0 + 0x20), &D_801BF6CC);
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
        func_8012A828((s32)a0, &D_801CA678);
        *(s32 *)((s32)a0 + 0x1C) = 0x79;
'''

C19 = r'''/*TEMPLATE(0xC,0,6)*/
        if (*(s32 *)((s32)a0 + 0x94) < 0x2E) {
            s0 = func_80143C74((s32)a0, 0);
            if (s0 != 0) {
                *(u16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) - (rand() & 0x3F);
                *(u16 *)(s0 + 0xA) = (*(s16 *)(s0 + 0xA) - 0x8B) - (rand() & 0x3F);
                *(u16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) - 0x9E;
                *(s32 *)(s0 + 0x10) = ((rand() & 0xFF) - 0x80) << 10;
                *(s32 *)(s0 + 0x18) = ((rand() & 0xFF) - 0x80) << 10;
                *(s16 *)(s0 + 0x16) = -((rand() & 3) + 4);
                func_80128EA8(*(s32 *)(s0 + 0x20), s0 + 0xD0, &D_8018DF10);
                func_8012C658(0x3AC, 6, s0);
                func_8012C658(0x3AC, 6, s0);
            }
        }
        if (*(s32 *)((s32)a0 + 0x94) == 0x45 || *(s32 *)((s32)a0 + 0x94) == 0x50) {
            func_8002D4C8(0xBBA, 0);
        }
        if (*(s32 *)((s32)a0 + 0x94) == 0x49 || *(s32 *)((s32)a0 + 0x94) == 0x56) {
            func_8002D4C8(0xBBB, 0);
        }
        if ((*(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1) != 0) {
            break;
        }
        *(u16 *)((s32)a0 + 0x34) = 0x14;
        func_8012A828((s32)a0, &D_801CAA38);
'''

C20 = r'''/*TEMPLATE(0xC,0,4)*/
/*TEMPLATE(0x9,4,6)*/
/*TEMPLATE(0xA,6,7)*/
/*TEMPLATE(0xB,7,0xA)*/
/*TEMPLATE(0xD,0xA,0xC)*/
/*TEMPLATE(0xE,0xC,0xD)*/
/*TEMPLATE(0xF,0xD,0x10)*/
'''

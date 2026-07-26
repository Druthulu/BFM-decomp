#!/usr/bin/env python3
"""Emit the byte-verified 72-ins spawn template body for a given (KIND, START, BOUND).

VERIFIED 2026-07-26 against target instance @801880C8 (KIND=9,START=4,BOUND=6):
body identical for all 67 non-prologue instructions under a register-blind mask.
Three levers were required and each is load-bearing (drop-one measured):
  1. running POINTER walk, counter init FIRST:
     `for (s4 = START, q = &D_801F61C0[START]; s4 < BOUND; s4++, q++)`.
     Array indexing `D_801F61C0[s4]` does NOT strength-reduce under -G0
     (the MIPS lo_sum address form blocks loop.c's giv), costing +3 ins/instance.
  2. `rand() % (u32)s0`  -> `divu`.  Signed `%` emits `div` plus gcc's
     -1/0x80000000 overflow trap, costing +5 ins/instance.
  3. else-branch spelled `(s32)((u8 *)p + ((X) + 0xC))`.  Writing
     `(s32)p + (X + 0xC)` lets combine reassociate to `(p+0xC) + X`,
     which folds one instruction away and fills the bne delay slot.
"""
import sys

BODY = '''        s5 = {K};
        func_8012EC04((s32)a0, {K}, sp18);
        for (s4 = {S}, q = &D_801F61C0[{S}]; s4 < {B}; s4++, q++) {{
            if (*q % 80 == 0) {{
                p = ((s32 **)(*(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x24)))[{K}];
                if (p[1] == 1) {{
                    s1 = p[3];
                }} else {{
                    s1 = (s32)((u8 *)p + ((((u32)p[3] >> 2) << 2) + 0xC));
                }}
                s0 = p[4] - 1;
                s1 = s1 + (rand() % (u32)s0) * 8;
                func_8012F14C(sp18, s1, sp38);
                sp40[3] = 0x3C5;
                sp40[7] = s5;
                sp40[5] = 0;
                sp40[4] = 0;
                *(s32 *)&sp40[8] = s1;
                sp40[6] = 0x7FFF;
                sp40[0] = sp38[0];
                sp40[1] = sp38[1];
                sp40[2] = sp38[2];
                func_8012C51C(sp40, (s32)a0);
            }}
        }}
'''


def tmpl(k, s, b, indent=8):
    if isinstance(k, str):
        k = int(k, 0)
    if isinstance(s, str):
        s = int(s, 0)
    if isinstance(b, str):
        b = int(b, 0)
    t = BODY.format(K='0x%X' % k, S=s, B=b)
    if indent != 8:
        pad = ' ' * (indent - 8)
        t = '\n'.join((pad + l if l.strip() else l) for l in t.splitlines()) + '\n'
    return t


# program-order table of every template instance, per case
TABLE = {
    11: [(0x8, 0, 8)],
    12: [(0x8, 0, 8)],
    13: [(0x1, 0, 4), (0x2, 4, 8), (0xB, 8, 0xC)],
    14: [(0x1, 0, 4), (0x2, 4, 8), (0xB, 8, 0xC)],
    15: [(0x6, 0, 4), (0x7, 4, 8), (0x8, 8, 0xC)],
    16: [(0x6, 0, 4), (0x7, 4, 8), (0x8, 8, 0xC)],
    17: [(0xD, 0, 6), (0xE, 6, 8), (0x1, 8, 0xA), (0x2, 0xA, 0xB),
         (0x6, 0xB, 0xD), (0x7, 0xD, 0xE), (0x8, 0xE, 0x10)],
    18: [(0xE, 0, 3), (0x1, 3, 5), (0x2, 5, 8), (0x6, 8, 0xB),
         (0x7, 0xB, 0xD), (0x8, 0xD, 0x10)],
    19: [(0xC, 0, 6)],
    20: [(0xC, 0, 4), (0x9, 4, 6), (0xA, 6, 7), (0xB, 7, 0xA),
         (0xD, 0xA, 0xC), (0xE, 0xC, 0xD), (0xF, 0xD, 0x10)],
}

if __name__ == '__main__':
    a = sys.argv[1:]
    if len(a) == 1:                      # a case number -> all its templates
        for x in TABLE[int(a[0])]:
            sys.stdout.write(tmpl(*x))
    else:
        for i in range(0, len(a), 3):
            sys.stdout.write(tmpl(a[i], a[i + 1], a[i + 2]))

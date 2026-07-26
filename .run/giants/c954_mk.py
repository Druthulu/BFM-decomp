#!/usr/bin/env python3
"""Variant generator for func_8017C954.

usage: c954_mk.py <base.c> <out.c> <lever> [lever ...]

Every lever is a list of (old, new) string replacements applied to the base text.
Each replacement is ASSERTED to apply (count must match) so a "neutral" reading
can never be a silent no-op.  Unknown lever name -> hard error.
"""
import sys

# ---------------------------------------------------------------- levers
L = {}

# --- declaration-order levers -------------------------------------------
L['nprim_first'] = [("""    s32 nparts;
    s32 j;
    u32 nprim;
    u32 i;""", """    u32 nprim;
    s32 nparts;
    s32 j;
    u32 i;""")]

L['nprim_first_part'] = [("""    s32 nparts;
    s32 j;
    u32 nprim;
    u32 i;
    Part *part;""", """    u32 nprim;
    s32 nparts;
    Part *part;
    s32 j;
    u32 i;""")]

L['col_after_lim'] = []  # identity (b1 already has it)

L['col_first'] = [("""    s32 lim;
    u32 colA;
    u32 colB;""", """    u32 colA;
    u32 colB;
    s32 lim;""")]

L['col_last'] = [("""    s32 lim;
    u32 colA;
    u32 colB;
    s32 nparts;""", """    s32 lim;
    s32 nparts;"""),
                 ("""    s16 my, mny, mx, mn;""", """    s16 my, mny, mx, mn;
    u32 colA;
    u32 colB;""")]

L['de_last'] = [("""    s16 my, mny, mx, mn;
    s32 d;
    u32 e;""", """    s16 my, mny, mx, mn;"""),
                ("""    s32 lim;
    u32 colA;""", """    s32 lim;
    s32 d;
    u32 e;
    u32 colA;""")]

# --- prologue statement-order levers ------------------------------------
L['ot_last'] = [("""    pkt = D_800A5E60;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    d = D_801DCCA0;""", """    pkt = D_800A5E60;
    d = D_801DCCA0;"""),
                ("""    colB = (e << 16) | (e << 8) | e;
    part =""", """    colB = (e << 16) | (e << 8) | e;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    part =""")]

L['ot_first'] = [("""    pkt = D_800A5E60;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];""",
                  """    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    pkt = D_800A5E60;""")]

L['ot_hoist'] = [("""    pkt = D_800A5E60;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];""", """    pkt = D_800A5E60;"""),
                 ("""    lim = func_800491EC()""", """    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    lim = func_800491EC()""")]

# --- prim/nprim read order ----------------------------------------------
L['prim_first'] = [("""                    prim = (Prim *)part->prim;
                    nprim = part->nprim;""", """                    nprim = part->nprim;
                    prim = (Prim *)part->prim;""")]

# --- misc ---------------------------------------------------------------
L['e_shift'] = [("    e = d * 2;", "    e = d << 1;")]
L['e_signed'] = [("""    u32 e;""", """    s32 e;"""),
                 ("    if (e > 0xFF) e = 0xFF;", "    if ((u32)e > 0xFF) e = 0xFF;")]


def main():
    base, out = sys.argv[1], sys.argv[2]
    src = open(base).read()
    for name in sys.argv[3:]:
        if name not in L:
            raise SystemExit("unknown lever: %s" % name)
        for old, new in L[name]:
            n = src.count(old)
            if n != 1:
                raise SystemExit("lever %s: pattern count %d (want 1):\n%s" % (name, n, old[:200]))
            src = src.replace(old, new, 1)
    open(out, 'w').write(src)
    print("wrote %s  (levers: %s)" % (out, ' '.join(sys.argv[3:]) or 'none'))


main()

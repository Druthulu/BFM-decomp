#!/usr/bin/env python3
"""Rewrite staged member drafts to the §37/§124 DEFINITION-SIDE ASM-LABEL ALIAS form.

WHY (byte-diagnosed, P30 S38 — the dominant sweep residue, 208 of ~398 conflicts):
A remapped member's definition can carry a signature that NO C declaration can reconcile with the
fleet's. Measured on family 0x80146ab4 (18 ins, ×138):

    draft def : void func_80146A6C(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6)
    TU decl   : extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

The narrow params are the wall: C's DEFAULT ARGUMENT PROMOTION means `s16`/`u16` cannot agree with
an `s32` prototype, and the `()` no-prototype escape is ILLEGAL precisely when a param promotes. So
neither side can move — `cast_call_sites` is the wrong axis (it fixes CALLEE decls, not the
definition's own signature) and `--fix-def-sig` cannot help either (measured: 0/138, error
unchanged).

THE ESCAPE (S33-proven on func_80147364: definition `(u16,u16)` vs 4,046 fleet decls, banked ×137
first try; 1,725 in-tree precedents): give the DEFINITION a private C identifier and bind the
emitted SYMBOL with a GNU asm label. The TU's declaration then simply never meets the definition,
so its type is irrelevant — ZERO blast radius on every caller.

    void aF80146A6C(<the byte-true params>) __asm__("func_80146A6C");
    void aF80146A6C(<the byte-true params>) { ... }

Byte-neutral by construction: the emitted symbol and the body are unchanged; only the C spelling of
the definition differs. The whole-binary byte-gate remains the sole arbiter (G3/P9).

Usage: alias_defs.py <staged_dir> <out_dir>
"""
import sys, os, re, glob, shutil

SRC, OUT = sys.argv[1], sys.argv[2]
shutil.rmtree(OUT, ignore_errors=True)

# `<type> func_<ADDR>(<params>)` at column 0, followed by the body brace — the definition head.
DEF = re.compile(r'^([A-Za-z_][\w \*]*?)\b(func_([0-9A-Fa-f]{8}))\s*\(([^;{]*)\)\s*\{', re.M)

n_in = n_out = 0
for p in sorted(glob.glob(os.path.join(SRC, '*', 'func_*.c'))):
    n_in += 1
    ov = os.path.basename(os.path.dirname(p))
    txt = open(p).read()
    m = DEF.search(txt)
    if not m:
        continue
    ret, sym, addr, params = m.group(1).strip(), m.group(2), m.group(3), m.group(4)
    alias = 'aF' + addr.upper()
    if alias in txt:                       # already aliased
        continue
    head = f'{ret} {alias}({params})'
    new = txt[:m.start()] + f'{head} __asm__("{sym}");\n{head}\n{{' + txt[m.end():]
    d = os.path.join(OUT, ov)
    os.makedirs(d, exist_ok=True)
    open(os.path.join(d, os.path.basename(p)), 'w').write(new)
    n_out += 1

print(f"alias_defs: {n_out} of {n_in} draft(s) rewritten to the def-side alias -> {OUT}")

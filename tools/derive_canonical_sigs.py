#!/usr/bin/env python3
"""Derive a byte-neutral canonical signature for each Phase-17 conflict callee (the canonical-sig layer).

Input: .run/conflict_callees.json (from census_conflict_callees.py) — the undeclared-stub callees that
parallel hand-matching agents would declare inconsistently (hand-matching-process.md §7c). For each we
emit ONE canonical `extern s32 func_X(s32 a0, ...);` to seed src/shared/engine_core.h, so gen_harvest_targets
feeds every drafting agent the SAME signature and the one-big-TU build stops conflicting.

Canonical form = WIDEST byte-neutral (hand-matching-process.md §3a):
  - return `s32`  : void->s32 is byte-neutral (no explicit return => identical epilogue); s32 is REQUIRED
                    where a caller uses $v0. So s32 is universally safe.
  - params `s32`  : widest scalar; a matched body casts int->ptr (`*(T*)(a0+off)`, the demo idiom) and a
                    caller narrows in the call expression. s32 never blocks a match; the byte-gate validates.
  - ARITY is the only value that must be exact (a wrong count => "too few/many arguments" at a caller, or a
                    def/extern arity clash for a circular target). Derived two ways and cross-checked:
      (G) Ghidra-C cache .run/ghidra_c/func_<A>.c  (FUN_<a>(...) param count) — the static oracle (G1).
      (A) asm read-before-write of $a0..$a3 in asm/<src>/nonmatchings/<src>/func_<A>.s — an a-reg whose
          FIRST-touching instruction uses it as a SOURCE is an incoming param; dest-only first touch
          (lui/lw/move/ALU-dest) = scratch, not a param. Arity = highest param index + 1 (contiguous).

The whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9): a wrong arity just fails the
gate and is fixed per-callee. This only shapes the drafting / seeds the canonical decls.

Usage:
  tools/derive_canonical_sigs.py [--source ov_SC01_077] [--in .run/conflict_callees.json]
"""
import argparse, json, os, re, glob

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AREGS = ['a0', 'a1', 'a2', 'a3']

# instruction operand roles restricted to what we need: is the FIRST a-reg touch a source (=> param)?
LOAD = {'lw', 'lh', 'lhu', 'lb', 'lbu', 'lwl', 'lwr', 'll', 'lwc1', 'lwc2', 'ldc1', 'ldc2'}      # rt=dest, base=src
STORE = {'sw', 'sh', 'sb', 'swl', 'swr', 'sc', 'swc1', 'swc2', 'sdc1', 'sdc2'}                    # rt=src, base=src
DEST_FIRST = {'lui', 'li', 'move', 'addu', 'addiu', 'subu', 'and', 'andi', 'or', 'ori', 'xor',    # rd/rt=dest, rest=src
              'xori', 'nor', 'slt', 'sltu', 'slti', 'sltiu', 'sll', 'srl', 'sra', 'sllv', 'srlv',
              'srav', 'mul', 'mult', 'negu', 'neg', 'not', 'mflo', 'mfhi', 'movn', 'movz', 'sub',
              'add', 'rotr', 'clz', 'seb', 'seh', 'mfc1', 'mfc2', 'la'}
SRC_ALL = {'beq', 'bne', 'beqz', 'bnez', 'blez', 'bgtz', 'bltz', 'bgez', 'bgezal', 'bltzal',       # all regs are src
           'jr', 'jalr', 'multu', 'divu', 'div', 'mtlo', 'mthi', 'mtc1', 'mtc2', 'teq', 'tne',
           'beql', 'bnel', 'cache'}


def reg_tokens(operand_str):
    return re.findall(r'\$([a-z0-9]+)', operand_str)


def a_role(mnem, ops):
    """return (a_sources, a_dest) restricted to a0..a3 for one instruction."""
    regs = reg_tokens(ops)
    a_in_order = [r for r in regs if r in AREGS]
    if not a_in_order:
        return set(), set()
    if mnem in LOAD:
        dest = {regs[0]} & set(AREGS) if regs else set()
        src = set(a_in_order) - dest
    elif mnem in STORE:
        dest, src = set(), set(a_in_order)
    elif mnem in DEST_FIRST:
        dest = {regs[0]} & set(AREGS) if regs else set()
        src = set(a_in_order) - dest
    elif mnem in SRC_ALL:
        dest, src = set(), set(a_in_order)
    else:                                   # unknown: be conservative -> treat as sources (flags a param)
        dest, src = set(), set(a_in_order)
    return src, dest


INSN_RE = re.compile(r'\*/\s+([a-z][a-z0-9.]*)\s+(.*)$')   # after the `... XXXX */` comment


def asm_arity(s_path):
    """highest read-before-write a-reg index +1; returns (arity, note)."""
    if not os.path.exists(s_path):
        return None, 'no-asm'
    first = {}                              # areg -> 'param' | 'scratch'
    for line in open(s_path):
        m = INSN_RE.search(line)
        if not m:
            continue
        mnem, ops = m.group(1), m.group(2)
        src, dest = a_role(mnem, ops)
        for r in AREGS:
            if r in first:
                continue
            if r in src:
                first[r] = 'param'
            elif r in dest:
                first[r] = 'scratch'
    arity = 0
    for i, r in enumerate(AREGS):
        if first.get(r) == 'param':
            arity = i + 1
    # contiguity note: a param above a scratch/untouched gap (loose-typed) -> flag
    gap = any(first.get(AREGS[j]) != 'param' for j in range(arity - 1)) if arity else False
    return arity, ('gap' if gap else 'ok')


GHIDRA_SIG_RE = re.compile(r'^\s*[A-Za-z_].*\bFUN_[0-9a-f]+\s*\((.*?)\)\s*$', re.M)


def ghidra_arity(addr):
    p = os.path.join(REPO, f'.run/ghidra_c/func_{addr}.c')
    if not os.path.exists(p):
        return None
    m = GHIDRA_SIG_RE.search(open(p).read())
    if not m:
        return None
    params = m.group(1).strip()
    if params in ('', 'void'):
        return 0
    return len([x for x in params.split(',') if x.strip()])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--source', default='ov_SC01_077')
    ap.add_argument('--in', dest='infile', default='.run/conflict_callees.json')
    args = ap.parse_args()
    asm_dir = os.path.join(REPO, f'asm/{args.source}/nonmatchings/{args.source}')
    conf = json.load(open(os.path.join(REPO, args.infile)))

    print(f'{"callee":>16} {"kind":>14} {"ghidra":>6} {"asm":>4} {"note":>6} {"->arity":>7}  canonical')
    rows = []
    for c in conf:
        addr = c['addr']
        g = ghidra_arity(addr)
        a, note = asm_arity(os.path.join(asm_dir, f'func_{addr}.s'))
        # reconcile: prefer asm (callee's own consumption); if asm gap or asm<ghidra, trust the larger
        cand = [x for x in (g, a) if x is not None]
        arity = max(cand) if cand else 0
        if g is not None and a is not None and g != a:
            note = f'G{g}/A{a}'
        params = 'void' if arity == 0 else ', '.join('s32 a%d' % i for i in range(arity))
        sig = f'extern s32 func_{addr}({params});'
        rows.append({'callee': c['callee'], 'addr': addr, 'arity': arity, 'kind': c['kind'],
                     'ghidra': g, 'asm': a, 'note': note, 'sig': sig})
        print(f'  func_{addr} {c["kind"]:>14} {str(g):>6} {str(a):>4} {note:>6} {arity:>7}  {sig}')

    out = os.path.join(REPO, '.run/canonical_sigs.json')
    json.dump(rows, open(out, 'w'), indent=1)
    print(f'\nwrote {out}  ({len(rows)} canonical sigs)')
    print('disagreements (G!=A) to eyeball:',
          ', '.join(r['callee'] for r in rows if r['note'].startswith('G')) or 'none')


if __name__ == '__main__':
    main()

#!/usr/bin/env python3
"""fragment_check.py — refuse drafts that SUBSUME another symbol (the enclosing-function trap).

WHY (P31 S52, cookbook §176i/§179). splat labels every address the symbol table names, including
addresses that are not functions at all: a bare epilogue tail (`lw $ra; lw $s2..$s0; addiu $sp;
jr $ra`), a jump-only branch target with no prologue, an interior label another function branches
to. Those symbols live INSIDE a real function's address range.

Convert that real function to C and the build breaks in two ways, neither of which any C-level
check can see:
  * `symbol 'SYS_OBJ_8F4' is already defined` — the fragment's own .s is still assembled while the
    C body emits the same bytes, defining the symbol twice;
  * ``undefined reference `.L80050F24'`` — the reverse: a neighbour branches to a label inside the
    function you just replaced, and converting it deleted the label.

Both are LINK/assemble-time and both cost a full rebuild to discover. This test costs milliseconds:
a function is unsafe to convert if any OTHER symbol's address lies strictly inside
`[addr, addr + 4*nins)`.

Measured cost of not having it: one wave-Q gate spent ~3 HOURS bisecting a 45-draft slate in which
NO subset could ever pass, because the failure was not draft-content at all. The bisect printed
nothing the whole time, because it only reports when it isolates a single rejected draft.

Usage:
  fragment_check.py <slate.json> [--binary main] [--prune out.json]
Exit 0 = no draft subsumes a symbol; 1 = at least one does.
"""
import argparse, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus


def interior_symbols(binary):
    """Return (stubs_by_name, addr->[names]) for the binary."""
    stubs = {st.symbol: st for st in corpus.stubs(binary).values()}
    byaddr = {}
    for name, addr in corpus.symbols(binary).items():
        byaddr.setdefault(addr, []).append(name)
    # splat-derived stub addresses are symbols too even when absent from the symbol files
    for st in stubs.values():
        byaddr.setdefault(st.addr, []).append(st.symbol)
    return stubs, byaddr


ASM_DEF = re.compile(r'^\s*"?\s*(?:\.globl|\.ent)\s+(\w+)|^\s*"\s*(\w+):', re.M)


def defines_foreign_symbol(slate, binary='main'):
    """Drafts that DEFINE a symbol another stub owns — the second half of this trap, and the one
    that actually bit wave Q.

    An agent that works out that a trailing epilogue really belongs to ITS function (splat having
    attributed those bytes to the next symbol) may write raw inline asm that emits the label
    itself: `.globl SYS_OBJ_8F4` / `SYS_OBJ_8F4:`. `match_one` is happy -- the bytes are right --
    but that symbol still has its OWN .s, so assembly fails with `symbol already defined`.

    The reasoning is sound and the fix is real; it just cannot ride in a batch while the fragment's
    stub still exists. Either bank the fragment and its parent together (removing the stub), or
    leave the function alone."""
    stubs = {st.symbol for st in corpus.stubs(binary).values()}
    out = []
    for e in slate:
        try:
            text = open(e['draft']).read()
        except OSError:
            continue
        defined = {m.group(1) or m.group(2) for m in ASM_DEF.finditer(text)}
        foreign = sorted(d for d in defined if d and d != e['fn'] and d in stubs)
        if foreign:
            out.append({'fn': e['fn'], 'defines': foreign})
    return out


def check(slate, binary='main'):
    stubs, byaddr = interior_symbols(binary)
    findings = []
    for e in slate:
        st = stubs.get(e['fn'])
        if not st:
            continue
        n = corpus.s_ins_count(st.asm_path) if hasattr(corpus, 's_ins_count') else None
        if not n:
            continue
        lo, hi = st.addr, st.addr + 4 * n
        inside = sorted((a, nm) for a, nms in byaddr.items() if lo < a < hi for nm in nms)
        if inside:
            findings.append({
                'fn': e['fn'], 'addr': '0x%08X' % lo, 'nins': n,
                'subsumes': [{'addr': '0x%08X' % a, 'symbol': nm} for a, nm in inside],
            })
    return findings


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('slate')
    ap.add_argument('--binary', default='main')
    ap.add_argument('--prune', help='write a slate with the offending drafts removed')
    a = ap.parse_args()

    slate = json.load(open(a.slate))
    bad = check(slate, a.binary)
    foreign = defines_foreign_symbol(slate, a.binary)
    print(f'{len(slate)} drafts checked against {a.binary} symbol space')
    for f in bad:
        syms = ', '.join(f"{s['symbol']}@{s['addr']}" for s in f['subsumes'][:4])
        print(f"  [FAIL] {f['fn']} ({f['addr']}, {f['nins']} ins) SUBSUMES {len(f['subsumes'])} "
              f"symbol(s): {syms}")
    for f in foreign:
        print(f"  [FAIL] {f['fn']} DEFINES another stub's symbol in asm: {', '.join(f['defines'])} "
              f"— that symbol still has its own .s (assembler: 'already defined')")
    if not bad and not foreign:
        print('  clean — no draft subsumes or redefines another symbol')
    if a.prune:
        names = {f['fn'] for f in bad} | {f['fn'] for f in foreign}
        json.dump([e for e in slate if e['fn'] not in names], open(a.prune, 'w'), indent=1)
        print(f'  pruned slate ({len(slate) - len(names)} drafts) -> {a.prune}')
    sys.exit(1 if (bad or foreign) else 0)


if __name__ == '__main__':
    main()

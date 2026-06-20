#!/usr/bin/env python3
"""canon_resident_calls.py — rewrite `func_<ADDR>` references in a harvest draft to the
CURATED resident symbol name when that address has one (Phase 19 / T2 recovery).

The link-miss recovery class. Overlay drafts call resident EXE/engine functions by their
`func_<ADDR>` name, but ~927 resident functions carry a *curated* name in config/symbols.us.txt
(e.g. 0x8004CFEC = `ratan2`). The linker resolves the curated name, NOT `func_8004CFEC`, so a
draft that calls `func_8004CFEC(...)` compiles fine but fails to LINK
(`undefined reference to func_8004CFEC`) -> the whole-binary byte-gate (correctly) reverts it.

This pass maps every address that has a `// func` curated (non-`func_`) name in the stacked
symbol files (symbols.us + symbols.resident + symbols.<ov>) and rewrites each `func_<ADDR>`
token at such an address to that name, in both the extern declaration and the call. A pure
draft-text transform (like sig_unify): the body bytes are unchanged (same call target, same
address) -> the whole-binary `harvest_verify` byte-gate remains the sole arbiter (G3/P9).

Proven on func_8017209C (calls ratan2 @0x8004CFEC). Run BEFORE sig_unify in the recovery
pipeline:  draft -> canon_resident_calls -> sig_unify -> harvest_verify --chunk 1

Usage:
  tools/canon_resident_calls.py --overlay ov_SC01_077 --in .run/drafts-X --out .run/drafts-X-cn
  tools/canon_resident_calls.py --symbols config/symbols.us.txt,... --in ... --out ...
"""
import argparse, os, re, glob

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# `name = 0xADDR; // func`  (curated function symbols; data is `// data` and uses D_ refs, not func_)
SYM_RE = re.compile(r'^\s*([A-Za-z_]\w*)\s*=\s*0x([0-9A-Fa-f]+)\s*;\s*//\s*func\b')
FUNC_TOK = re.compile(r'\bfunc_([0-9A-Fa-f]{8})\b')


def load_name_map(symbol_paths):
    """addr(int) -> curated name, for every `// func` symbol whose name is NOT func_<ADDR>.
    Later files in the stack override earlier (overlay-local wins), mirroring splat's stacking."""
    out = {}
    for p in symbol_paths:
        if not os.path.exists(p):
            continue
        for ln in open(p):
            m = SYM_RE.match(ln)
            if not m:
                continue
            name, addr = m.group(1), int(m.group(2), 16)
            if name.lower() != f'func_{addr:08x}':   # skip auto func_ names (no-op rewrites)
                out[addr] = name
    return out


def rewrite(text, name_map):
    n = [0]

    def repl(m):
        addr = int(m.group(1), 16)
        nm = name_map.get(addr)
        if nm and nm != m.group(0):
            n[0] += 1
            return nm
        return m.group(0)

    return FUNC_TOK.sub(repl, text), n[0]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--overlay', default='ov_SC01_077')
    ap.add_argument('--symbols', help='comma-separated symbol files (default: us + resident + overlay)')
    ap.add_argument('--in', dest='indir', required=True)
    ap.add_argument('--out', dest='outdir', required=True)
    a = ap.parse_args()

    if a.symbols:
        sym_paths = [os.path.join(REPO, p) for p in a.symbols.split(',')]
    else:
        sym_paths = [os.path.join(REPO, p) for p in (
            'config/symbols.us.txt', 'config/symbols.resident.txt',
            f'config/symbols.{a.overlay}.txt')]
    name_map = load_name_map(sym_paths)

    os.makedirs(os.path.join(REPO, a.outdir), exist_ok=True)
    drafts = touched = total = 0
    for p in sorted(glob.glob(os.path.join(REPO, a.indir, '*.c'))):
        new, k = rewrite(open(p).read(), name_map)
        open(os.path.join(REPO, a.outdir, os.path.basename(p)), 'w').write(new)
        drafts += 1
        if k:
            touched += 1
            total += k
    print(f'curated func names: {len(name_map)}; drafts: {drafts}; '
          f'rewritten: {touched} draft(s), {total} ref(s)')


if __name__ == '__main__':
    main()

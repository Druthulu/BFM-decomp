#!/usr/bin/env python3
"""decl_prior.py — the FLEET's consensus declaration for every symbol, as a wave-card field.

WHY THIS EXISTS (P31 S54, cookbook §196). Wave-V token accounting: drafting is 88.3% of a wave's
output tokens, repair 8.4%, reconcile 3.2% -- so the leverage is in what a drafter has to GUESS
before its first compile, not in the plumbing afterwards. Two of those guesses are answered
somewhere in the tree and nowhere on the card:

  * CALLEE ARITY AND RETURN TYPE. §195-A proved there is no positive tell in the asm: an argument
    that dies at the call is allocated straight into $aN, so its only def is a plain load and every
    use reads $aN -- the walk cannot distinguish it from a scratch register, in EITHER direction.
    The prescribed procedure is a two-arity A/B, i.e. an extra compile per ambiguous callee. But
    some other TU in the fleet has usually already banked a function that calls it, and that
    declaration is evidence.
  * GLOBAL TYPE. The Reconcile phase and every CONFLICTING-EXTERN drop exist because N drafters
    independently invent a spelling for one D_ symbol. The fleet has usually settled it already.

This is the same shape of fix as §193-A (`seed_ref`) and §194-E (`tu_ref`): the answer was in the
tree, the card just never carried it. It is fully deterministic -- no agent, no tokens.

THE EVIDENCE HIERARCHY, strongest first (each row is emitted with its count so the agent can weigh):
  1. DEF      -- a banked DEFINITION's own signature. The function exists; this is its real shape.
  2. TU       -- the destination TU's own declaration. Authoritative for THIS draft by wave law 2
                 regardless of what the fleet says, because that is the file it must compile in.
  3. FLEET    -- the modal `extern` spelling across all other TUs, with its count and its rivals.

Usage:
  decl_prior.py --build                 # (re)build .run/decl_prior.json from src/**/*.c
  decl_prior.py --query func_8012BEE8   # what the fleet says about one symbol
  decl_prior.py --for-asm <file.s> [--tu <path>]   # every symbol a target references
"""
import argparse, collections, glob, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl
import gate_main as gm

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX = os.path.join(REPO, '.run', 'decl_prior.json')

# Symbols reach a .s in exactly three shapes (§194-E: an uppercase-word regex reads the comment
# column's hex WORDS as symbol names -- 34 "symbols" for one function, 31 of them hex).
_ASM_SYM = re.compile(r'\b(?:jal\s+(\w+)|%[hl][io]\(([\w+]+)\))')
_DEF = re.compile(r'^[A-Za-z_][\w \t\*]*?\b(\w+)\s*\(([^;{]*)\)\s*\{', re.M)


def asm_symbols(path):
    """{symbol} referenced by a target .s, from its jal targets and %hi/%lo operands."""
    try:
        raw = _ASM_SYM.findall(open(path, errors='replace').read())
    except OSError:
        return set()
    return {(a or b).split('+')[0] for a, b in raw if (a or b)}


def build(verbose=True):
    """symbol -> {'def': [sig, n], 'ext': [[sig, n], ...]} over every committed .c."""
    defs, exts = collections.defaultdict(collections.Counter), collections.defaultdict(collections.Counter)
    files = sorted(glob.glob(os.path.join(REPO, 'src', '**', '*.c'), recursive=True))
    for p in files:
        txt = cdecl._mask(open(p, errors='replace').read())      # R33: the one masking oracle
        for d in gm.DECL.findall(txt):
            s = gm.sym_of(d)
            if s:
                exts[s][str(gm.norm_sig(gm.typesig(d)))] += 1
        for m in _DEF.finditer(txt):
            name, params = m.group(1), m.group(2)
            if name in ('if', 'for', 'while', 'switch', 'return', 'sizeof'):
                continue
            ret = txt[max(0, m.start()):m.start(1)].strip()
            defs[name][str(gm.norm_sig(gm.typesig('%s %s(%s)' % (ret, name, params))))] += 1
    out = {}
    for s in set(defs) | set(exts):
        row = {}
        if defs.get(s):
            sig, n = defs[s].most_common(1)[0]
            row['def'] = [sig, n]
        if exts.get(s):
            row['ext'] = [[sig, n] for sig, n in exts[s].most_common(3)]
        out[s] = row
    os.makedirs(os.path.dirname(INDEX), exist_ok=True)
    json.dump({'symbols': out, 'files': len(files)}, open(INDEX, 'w'))
    if verbose:
        print(f"decl_prior: {len(files)} files -> {len(out):,} symbols "
              f"({sum(1 for r in out.values() if 'def' in r):,} with a banked DEFINITION) -> {INDEX}")
    return out


def load():
    if not os.path.isfile(INDEX):
        return build(verbose=False)
    return json.load(open(INDEX))['symbols']


def tu_decls(tu_path):
    """symbol -> sig for the destination TU's OWN declarations (wave law 2: authoritative here)."""
    out = {}
    try:
        txt = cdecl._mask(open(tu_path, errors='replace').read())
    except (OSError, TypeError):
        return out
    for d in gm.DECL.findall(txt):
        s = gm.sym_of(d)
        if s:
            out[s] = str(gm.norm_sig(gm.typesig(d)))
    return out


def for_asm(asm_path, tu_path=None, idx=None, limit=14):
    """[{sym, tu, def, fleet, rivals}] for the symbols a target references. Rows the destination TU
    already declares are marked `tu` and need no fleet evidence -- law 2 settles them."""
    idx = idx if idx is not None else load()
    mine = tu_decls(tu_path) if tu_path else {}
    rows = []
    for s in sorted(asm_symbols(asm_path)):
        r = idx.get(s)
        if not r and s not in mine:
            continue
        row = {'sym': s}
        if s in mine:
            row['tu'] = mine[s]
        if r and r.get('def'):
            row['def'] = r['def'][0]
        if r and r.get('ext'):
            row['fleet'] = r['ext'][0][0]
            row['n'] = r['ext'][0][1]
            if len(r['ext']) > 1:
                row['rivals'] = ['%s x%d' % (sig, n) for sig, n in r['ext'][1:]]
        rows.append(row)
    # A row the TU already settles is not news; put the genuinely-informative ones first.
    rows.sort(key=lambda x: (('tu' in x), -(x.get('n') or 0)))
    return rows[:limit]


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--build', action='store_true')
    ap.add_argument('--query')
    ap.add_argument('--for-asm')
    ap.add_argument('--tu')
    a = ap.parse_args()
    if a.build:
        build()
    elif a.query:
        print(json.dumps(load().get(a.query, {}), indent=1))
    elif a.for_asm:
        for r in for_asm(a.for_asm, a.tu):
            print(json.dumps(r))
    else:
        ap.print_help()

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
# §204-E: the `\b` must bind to the `jal` arm ONLY. Prefixing the whole alternation demands a
# word boundary immediately before `%`, and in a .s that position always follows a space -- so
# the %hi/%lo arm could never match and the card's promised GLOBAL-TYPE row was 0 of 1,210 across
# four waves. NC on the 75 wave-Z targets: jal 306 -> 306 (zero regressions), data 0 -> 299.
_ASM_SYM = re.compile(r'(?:\bjal\s+(\w+)|%[hl][io]\(([\w+]+)\))')
_DEF = re.compile(r'^[A-Za-z_][\w \t\*]*?\b(\w+)\s*\(([^;{]*)\)\s*\{', re.M)


def asm_symbols(path):
    """{symbol} referenced by a target .s, from its jal targets and %hi/%lo operands."""
    try:
        raw = _ASM_SYM.findall(open(path, errors='replace').read())
    except OSError:
        return set()
    return {(a or b).split('+')[0] for a, b in raw if (a or b)}


OVERLAY_WINDOW = 0x80170000   # >= this, a func_ADDR name is per-overlay and NOT fleet-unique


def _binary_of(path):
    """src/<binary>/<file>.c -> <binary>; src/800.c and friends -> 'main'."""
    rel = os.path.relpath(path, os.path.join(REPO, 'src'))
    parts = rel.split(os.sep)
    return parts[0] if len(parts) > 1 else 'main'


def _is_overlay_window(sym):
    """A func_ADDR / D_ADDR symbol in the overlay load window is a DIFFERENT object per overlay."""
    m = re.match(r'(?:func|D)_([0-9A-Fa-f]{8})$', sym)
    return bool(m) and int(m.group(1), 16) >= OVERLAY_WINDOW


def build(verbose=True):
    """symbol -> {'def': {binary: [sig, n]}, 'ext': [[sig, n], ...]}.

    DEFS ARE KEYED BY BINARY (P31 S55, cookbook §201 — §150-B applied to this index). Overlay
    functions are named by VRAM address and 134 overlays load at the same window, so a bare
    `defs[name]` counter mixes N UNRELATED functions: measured over the tree, 3,911 of 9,861
    symbols with a definition are defined in more than one binary, 1,219 of those disagree on
    ARITY, and 818 of the disagreements are a top-two TIE that `most_common` broke by sorted-file
    order — i.e. the lowest-numbered overlay silently won. On wave Y's five binaries the card
    printed 65 DEF rows for overlay-window symbols and 26 of them (40%) were another overlay's
    function. Byte-proven cost: applying one such row's arity to `func_8017E83C` took it from
    MATCH (114 ins) to 113 ins / 83 mismatched."""
    defs = collections.defaultdict(lambda: collections.defaultdict(collections.Counter))
    exts = collections.defaultdict(collections.Counter)
    files = sorted(glob.glob(os.path.join(REPO, 'src', '**', '*.c'), recursive=True))
    for p in files:
        b = _binary_of(p)
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
            defs[name][b][str(gm.norm_sig(gm.typesig('%s %s(%s)' % (ret, name, params))))] += 1
    out = {}
    for s in set(defs) | set(exts):
        row = {}
        if defs.get(s):
            row['def'] = {b: list(c.most_common(1)[0]) for b, c in defs[s].items()}
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


def for_asm(asm_path, tu_path=None, idx=None, limit=14, binary=None):
    """[{sym, tu, def, fleet, rivals}] for the symbols a target references. Rows the destination TU
    already declares are marked `tu` and need no fleet evidence -- law 2 settles them.

    `binary` is the TARGET's binary and is required for a trustworthy `def` row on overlay-window
    symbols (§201); without it, such rows are withheld with a `def_absent` reason."""
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
            # §201: a DEF row is authoritative only from the TARGET'S OWN binary when the symbol
            # lives in the overlay window — otherwise it is another overlay's function wearing the
            # same address-derived name (§150-B / §164-77: a fleet plurality carries ZERO authority
            # for a per-overlay symbol). Resident/shared/main symbols are fleet-unique and fine.
            d = r['def']
            if binary and binary in d:
                row['def'] = d[binary][0]
            elif not _is_overlay_window(s):
                sig, n = sorted(d.values(), key=lambda x: -x[1])[0]
                row['def'] = sig
                row['def_n'] = n
            elif len(d) == 1 and not binary:
                row['def'] = list(d.values())[0][0]
            else:
                # Say WHY there is no def row rather than silently omitting it.
                row['def_absent'] = ('%d other binar%s define this address; none is yours'
                                     % (len(d), 'y' if len(d) == 1 else 'ies'))
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

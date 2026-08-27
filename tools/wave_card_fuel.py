#!/usr/bin/env python3
"""tools/wave_card_fuel.py — the per-target CARD FUEL an agent pack carries, as ONE oracle (R33).

These helpers were defined inside `build_wave_atlas.py`, which parses argv at import and so cannot
be reused as a library. Extracted VERBATIM (P31 S63) so `build_wave_atlas` and the Claude wave's
`tools/t5_cards.py` compute the SAME fuel rather than two copies that drift:

  home_tu(binary, fn)      the stub's home .c (the gate group key)
  _tu_bodies(tu_path)      {fn: body} for every function DEFINED (banked) in a TU
  tu_neighbours(...)       already-banked functions in the target's OWN TU, ranked by symbols
                           shared with the target's .s relocations (§194-E, the highest-yield
                           source measured; wave t5a's agents rediscovered it by hand and said so)

Why it exists (byte-measured, P31 S63): `claude_wave_packs` looked cards up by BARE FUNCTION NAME,
and overlays share names at equal addresses — so ALL 48 of wave t5a's targets (and 15 of T4's 20)
received ANOTHER binary's card: wrong twin, wrong TU neighbours, wrong declarations. Nine agents
reported it independently. The fix is a (binary, fn) key — which, for never-carded K-class work,
means there is no card at all. So the fuel has to be BUILT for the target itself, from here."""
import os, sys
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, 'tools'))
import corpus

_open = {}
def _stubmap(binary):
    if binary not in _open:
        # corpus.stubs() is addr -> Stub; the NAME lives on the record
        _open[binary] = {st.symbol: st for st in corpus.stubs(binary).values()}
    return _open[binary]
def is_open(binary, fn):
    return fn in _stubmap(binary)
def home_tu(binary, fn):
    """The stub's home .c — this is the GATE GROUP KEY (gate_lane groups by (binary, src))."""
    st = _stubmap(binary).get(fn)
    return st.path if st else None
_TU_BODIES = {}
def _tu_bodies(tu_path):
    """{fn: body_text} for every function DEFINED in a TU (banked C only -- stubs are INCLUDE_ASM).

    Brace-matched from each definition so a symbol is attributed to the function that uses it, not
    to the file. Memoized per TU: a wave draws many cards from one .c."""
    if tu_path in _TU_BODIES:
        return _TU_BODIES[tu_path]
    out = {}
    try:
        txt = open(tu_path, errors='replace').read()
    except (OSError, TypeError):
        _TU_BODIES[tu_path] = out
        return out
    import re as _re
    for m in _re.finditer(r'^[A-Za-z_][\w \t\*]*?\b(\w+)\s*\([^;{]*\)\s*\{', txt, _re.M):
        i, depth = m.end() - 1, 0
        while i < len(txt):
            if txt[i] == '{': depth += 1
            elif txt[i] == '}':
                depth -= 1
                if depth == 0: break
            i += 1
        out[m.group(1)] = txt[m.start():i + 1]
    _TU_BODIES[tu_path] = out
    return out
_SYM = None
def tu_neighbours(binary, fn, tu_path, asm_file, topn=2):
    """Banked functions in the card's OWN TU, ranked by symbols shared with the target's asm.

    The symbols are read from the TARGET's .s (its relocation operands), so this is evidence about
    the function being drafted, not about the file. See §194-E for why the card needs this at all."""
    global _SYM
    if not tu_path or not asm_file:
        return []
    import re as _re
    if _SYM is None:
        # OPERANDS ONLY. A splat .s carries the encoded WORD in a comment column, so a naive
        # "[A-Z]\w{3,}" reads `D8FFBD27` and `CC00228E` as symbol names and the overlap score
        # becomes noise (measured: 34 "symbols" for one function, 31 of them hex words).
        # Symbols reach the .s in exactly three shapes: a jal target, and %hi()/%lo() operands.
        _SYM = _re.compile(r'\b(?:jal\s+(\w+)|%[hl][io]\(([\w+]+)\))')
    try:
        raw = _SYM.findall(open(asm_file, errors='replace').read())
    except OSError:
        return []
    want = {(a or b).split('+')[0] for a, b in raw if (a or b)}
    want.discard(fn)
    if not want:
        return []
    scored = []
    for other, body in _tu_bodies(tu_path).items():
        if other == fn:
            continue
        shared = [s for s in want if s in body]
        if len(shared) >= 2:
            scored.append((len(shared), other, sorted(shared)[:6]))
    scored.sort(key=lambda x: -x[0])
    if not scored:
        # FALL BACK TO THE BEST SINGLE SHARED SYMBOL rather than emitting nothing. One shared
        # callee is weak evidence, but the card reports the count so the agent can weigh it, and a
        # weak same-TU lead still beats the zero-locality state §194-E measured.
        weak = sorted(((len([s for s in want if s in body]), other)
                       for other, body in _tu_bodies(tu_path).items() if other != fn), reverse=True)
        if weak and weak[0][0] == 1:
            o = weak[0][1]
            body = _tu_bodies(tu_path)[o]
            return [{'fn': o, 'shared': 1, 'symbols': [s for s in sorted(want) if s in body][:6]}]
    return [{'fn': o, 'shared': n, 'symbols': syms} for n, o, syms in scored[:topn]]

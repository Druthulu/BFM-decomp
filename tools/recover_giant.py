#!/usr/bin/env python3
"""recover_giant.py — the canonical-extern recovery for a "close=0 gate-rejected" giant (cookbook §28).

A giant draft that is match_one-MATCH but fails the WHOLE-binary gate with `conflicting types for
func_X` is a PURE-EXTERN PLUMBING wall: its self-contained file-scope externs guessed sigs that
clash with engine_core.h's canonical decls of the same callees (the giant calls already-matched
engine functions). sig_unify/cast_call_sites don't canonicalize these. This tool does:

  1. strip // comments + scalar-typedef redefinitions; uppercase func_<hex> to the splat convention.
  2. for each callee that has a `DEFINE_func_X()` in engine_core.h, rewrite the draft's extern to
     that macro's exact definition signature (`extern <ret> func_X(<params>);`).
  3. move ALL externs (callee + D_ data) BLOCK-scope, just inside the function body's opening brace,
     so find_site/compiles_standalone/dedup_propagate lift the body + its internal externs as ONE
     unit (file-scope externs are excluded from the lifted body -> false "not self-contained" skip).

Then gate it: `harvest_verify` (banks whole-binary, the sole arbiter G3/P9) -> `dedup_propagate` ×134.
This ONLY fixes the pure-extern-plumbing wall (§28 case 1). A struct-type collision (`conflicting
types for S8`, case 3), a masked residual (compiles but wrong bytes, case 2 -> permuter), or a
regressed draft (match_one DIFF, case 4 -> re-derive) are NOT addressed here — the gate decides.

Usage: tools/recover_giant.py <func_NAME> <in_draft.c> <out_draft.c>
"""
import re, sys, os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EC = os.path.join(REPO, "src/shared/engine_core.h")


def canon_sig(name, ec):
    """The canonical definition signature `<ret> func_X(<params>)` from DEFINE_func_X in engine_core.h."""
    m = re.search(r'#define DEFINE_%s\(\)(.*?)\{' % re.escape(name), ec, re.S)
    if not m:
        return None
    for raw in m.group(1).split('\\\n'):
        line = raw.strip().rstrip('\\').strip()
        if not line or line.startswith('extern') or line.startswith('#'):
            continue
        mm = re.match(r'([A-Za-z_].*\b%s\s*\(.*\))\s*\{?\s*$' % re.escape(name), line)
        if mm:
            return mm.group(1).strip()
    return None


def recover(fn, src, ec):
    s = re.sub(r'^[ \t]*//.*\n', '', src, flags=re.M)
    s = re.sub(r'^[ \t]*typedef\b.*\b(u8|u16|u32|u64|s8|s16|s32|s64|f32|f64)[ \t]*;[ \t]*\n', '', s, flags=re.M)
    s = re.sub(r'func_([0-9A-Fa-f]+)', lambda m: 'func_' + m.group(1).upper(), s)
    lines = s.split('\n')
    externs = [l for l in lines if l.strip().startswith('extern')]
    rest = [l for l in lines if not l.strip().startswith('extern')]

    def canon_extern(line):
        m = re.search(r'\b(func_[0-9A-F]+)\b', line)
        if not m:
            return line.strip()          # D_ data extern — keep as-is
        cs = canon_sig(m.group(1), ec)
        return ('extern ' + cs + ';') if cs else line.strip()

    externs = [canon_extern(l) for l in externs]
    di = next((i for i, l in enumerate(rest)
               if re.match(r'^[A-Za-z_][\w \*]*\b' + re.escape(fn) + r'\s*\(', l) and ';' not in l), None)
    if di is None:
        raise SystemExit(f"recover_giant: could not find the definition of {fn} in the draft")
    bi = di
    while bi < len(rest) and '{' not in rest[bi]:
        bi += 1
    new = rest[:bi + 1] + ['    ' + e for e in externs] + rest[bi + 1:]
    return '\n'.join(new), len(externs)


def main():
    if len(sys.argv) != 4:
        raise SystemExit(__doc__)
    fn, inp, outp = sys.argv[1], sys.argv[2], sys.argv[3]
    out, n = recover(fn, open(inp).read(), open(EC).read())
    os.makedirs(os.path.dirname(outp) or ".", exist_ok=True)
    open(outp, 'w').write(out)
    print(f"recovered {fn}: {n} externs canonicalized + block-scoped -> {outp}")


if __name__ == "__main__":
    main()

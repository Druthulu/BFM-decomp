#!/usr/bin/env python3
"""pregate_check.py — validate a main-EXE slate WITHOUT building it (~2s instead of ~5min).

WHY THIS EXISTS (P31 S52). Wave P drafted at 97% -- 58 of 60 functions byte-correct on the first
pass, zero symbol errors -- and then cost A DOZEN CLEAN REBUILDS to bank. Not one of those
rebuilds failed on a matching problem. Every single one failed on N independently-written drafts
having to agree with each other and with a translation unit none of them can see, and EVERY ONE OF
THOSE FAILURES WAS A TEXTUAL PROPERTY OF THE SUBSTITUTED FILE. We were paying five minutes of
`make` to be told something a grep could have said instantly.

`gate_main`'s own `resolve_conflicts` cannot answer this, and not because it is careless: it
inspects the DRAFTS, while the compiler sees the FILE THEY LAND IN -- after typedef stripping and
renaming, at each draft's own insertion offset, interleaved with declarations the file already had.
Those transformations happen at substitution time, *after* the conflict check has passed. So this
tool checks the artifact itself: `substitute(..., write=False)` into memory, then assert.

THE FIVE CHECKS, each earned by a real rebuild lost this session (cookbook §176h):
  1. TYPEDEF-USED-ABOVE-DEFINITION -- src/800.c defines `Rec14` at line 7336 while stubs wanting
     it sit at 7272; a stripped duplicate leaves the name undefined there (gcc: implicit-int, then
     a collision reported at the *real* declaration, nowhere near the cause).
  2. TYPE-NEVER-DEFINED -- a typedef deleted outright vanishes from any check that only looks at
     names which ARE defined. (That was the hole in my own first control. R32 inside the R32 fix.)
  3. DUPLICATE-TYPEDEF -- same name defined twice with different bodies.
  4. CONFLICTING-EXTERN -- one symbol declared with two incompatible signatures in the final text,
     whoever contributed them (file, draft A, draft B).
  5. DEF-VS-DECL -- a function DEFINITION contradicting a prototype visible in the same file (the
     DEF-side wall, §20 / wave law 3): `s32 func_8001ABBC(...)` under `extern void func_...`.

Comments are MASKED (via cdecl, the project's single masking oracle) before any use-site scan: an
unmasked scan reported 7 phantom "used before defined" hits, all of them agents' prose.

Usage:
  pregate_check.py <slate.json>            # report; exit 1 if any FAIL
  pregate_check.py <slate.json> --quiet    # exit code only
Leaves the working tree untouched.
"""
import argparse, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl
import gate_main as gm

IDENT = r'[A-Za-z_]\w*'


def _depth_map(masked):
    """Brace depth at every offset, computed on COMMENT/STRING-MASKED text.

    Scope matters and ignoring it makes this tool a liar: the project deliberately uses
    BLOCK-SCOPE `extern` blocks (the §16/§17 local-block idiom, and the fix for a symbol whose
    file-scope type disagrees), and a declaration inside one function cannot conflict with a
    definition elsewhere. My first version compared every declaration in the file regardless of
    depth and reported 4 hard failures on a slate that had just built BYTE-IDENTICAL -- the exact
    over-refusal R39 exists to prevent, in the tool written to prevent it."""
    depth, out = 0, bytearray(len(masked) + 1)
    for i, ch in enumerate(masked):
        if ch == '{':
            depth += 1
        elif ch == '}':
            depth = max(0, depth - 1)
        out[i] = min(depth, 255)
    return out


def _norm_sig(sig):
    """`void f()` and `void f(void)` are not a conflict worth blocking a rebuild over: C89 calls
    the first an unspecified parameter list, and gcc-2.7.2 accepts the pair. Normalize both to
    (). Signedness, pointer depth and array-vs-scalar are left alone -- those are real."""
    ret, params = sig
    if isinstance(params, tuple) and params in ((), ('',), ('void',)):
        params = ()
    return (ret, params)


def _typedefs(text):
    """name -> (offset, normalized_body) for every typedef the text defines."""
    out = {}
    for pat in (gm.TYPEDEF_BLOCK, gm.TYPEDEF_PLAIN):
        for m in pat.finditer(text):
            out.setdefault(m.group(1), []).append((m.start(), ' '.join(m.group(0).split())))
    return out


def _func_defs(text):
    """Function definitions in the text -> {name: (offset, typesig)}."""
    out = {}
    for m in re.finditer(r'^[ \t]*([A-Za-z_][\w \t\*]*?)\b(%s)\s*\(([^;{]*)\)\s*\{' % IDENT,
                         text, re.M):
        ret, name, params = m.group(1).strip(), m.group(2), m.group(3)
        if name in ('if', 'for', 'while', 'switch', 'return', 'sizeof'):
            continue
        out[name] = (m.start(), gm.typesig('%s %s(%s)' % (ret, name, params)))
    return out


def check_text(path, text):
    """Return a list of (severity, code, message) for one substituted file."""
    findings = []
    masked = cdecl._mask(text)          # R33: the one comment/string masking oracle
    depth = _depth_map(masked)
    tds = _typedefs(text)

    # 3. duplicate typedef with a different body
    for name, defs in tds.items():
        bodies = {b for _, b in defs}
        if len(bodies) > 1:
            findings.append(('FAIL', 'DUPLICATE-TYPEDEF',
                             f'{path}: `{name}` defined {len(defs)}x with different bodies '
                             f'(offsets {[o for o, _ in defs]})'))

    # 1. typedef used above its definition
    for name, defs in tds.items():
        first_def = min(o for o, _ in defs)
        uses = [m.start() for m in re.finditer(r'\b%s\b' % re.escape(name), masked)]
        early = [u for u in uses if u < first_def]
        if early:
            findings.append(('FAIL', 'TYPEDEF-USED-ABOVE-DEFINITION',
                             f'{path}: `{name}` used at offset {min(early)} but first defined at '
                             f'{first_def} — a stripped duplicate whose survivor sits below'))

    # 2. a type named in a declaration that nothing in this file defines
    known = set(tds) | gm.TYPES | set(gm._ALIASES) | set(gm._ALIASES.values())
    header_types = set()
    for hp in ('include', 'src/shared'):
        for root, _dirs, files in os.walk(hp):
            for f in files:
                if f.endswith('.h'):
                    try:
                        h = open(os.path.join(root, f), errors='ignore').read()
                    except OSError:
                        continue
                    header_types |= set(_typedefs(h))
                    header_types |= set(re.findall(r'\btypedef\s+[^;]*?\(\s*\*\s*(%s)\s*\)' % IDENT, h))
    # function-pointer typedefs are not matched by the block/plain patterns; pick them up here too
    known |= header_types | set(re.findall(r'\btypedef\s+[^;]*?\(\s*\*\s*(%s)\s*\)' % IDENT, text))
    for m in re.finditer(r'^\s*extern\s+(?:const\s+|volatile\s+)*(%s)\b' % IDENT, masked, re.M):
        t = m.group(1)
        if t not in known and not t.startswith(('func_', 'D_')):
            findings.append(('WARN', 'TYPE-NEVER-DEFINED',
                             f'{path}: `extern {t} ...` at offset {m.start()} — `{t}` is not '
                             f'defined in this file or any project header (PsyQ SDK type?)'))

    # 4. one symbol declared two incompatible ways anywhere in the final text
    decls = {}
    for m in gm.DECL.finditer(text):
        if depth[m.start()]:            # block-scope decl: private to its function
            continue
        d = m.group(1)
        s = gm.sym_of(d)
        if not s:
            continue
        sig = _norm_sig(gm.typesig(d))
        if s in decls and decls[s][1] != sig:
            findings.append(('FAIL', 'CONFLICTING-EXTERN',
                             f'{path}: `{s}` declared {decls[s][1]} at offset {decls[s][0]} and '
                             f'{sig} at offset {m.start()}'))
        else:
            decls.setdefault(s, (m.start(), sig))

    # 5. definition vs a visible prototype
    for name, (off, sig) in _func_defs(text).items():
        sig = _norm_sig(sig)
        if name in decls and decls[name][1] != sig:
            # SEVERITY CALIBRATED AGAINST THE COMPILER, not against C89 pedantry. Measured on the
            # wave-P slate that built BYTE-IDENTICAL: gcc-2.7.2 accepted `void f(void*,s32)` vs a
            # `void f(s8*,s32)` definition, and even `G3P *f(...)` vs `G4P *f(...)`. What it
            # REJECTED was func_8001ABBC declared `void` and defined `s32` -- a void/non-void
            # return split. So that is the only FAIL; everything else is a WARN worth reading but
            # not worth blocking a rebuild over (R39: an over-refusal costs verified-correct work).
            d_ret, m_ret = decls[name][1][0], sig[0]
            voidness = (d_ret == 'void') != (m_ret == 'void')
            findings.append(('FAIL' if voidness else 'WARN', 'DEF-VS-DECL',
                             f'{path}: `{name}` DEFINED {sig} at offset {off} but DECLARED '
                             f'{decls[name][1]} at offset {decls[name][0]} — the DEF-side wall; '
                             f'adopt the declaration and cast at the use site (§176d)'))
    return findings


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('slate')
    ap.add_argument('--quiet', action='store_true')
    a = ap.parse_args()

    slate = json.load(open(a.slate))
    kept, dropped = gm.resolve_conflicts(slate)
    _n, texts = gm.substitute(kept, write=False)

    findings = []
    for path, text in sorted(texts.items()):
        findings += check_text(path, text)

    fails = [f for f in findings if f[0] == 'FAIL']
    if not a.quiet:
        print(f'slate {len(slate)} -> {len(kept)} after resolve_conflicts '
              f'({len(dropped)} dropped); checking {len(texts)} substituted file(s)')
        for sev, code, msg in findings:
            print(f'  [{sev}] {code}: {msg}')
        if not findings:
            print('  clean — no textual defect found; the batch is worth a rebuild')
        elif not fails:
            print(f'  {len(findings)} warning(s), no hard failure — worth a rebuild')
        else:
            print(f'\n{len(fails)} FAILURE(S) — fix these BEFORE spending a clean rebuild.')
    sys.exit(1 if fails else 0)


if __name__ == '__main__':
    main()

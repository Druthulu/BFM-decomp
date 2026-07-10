#!/usr/bin/env python3
"""Def-side-wall reconcile (Phase-25 T5b/T7 lever).

A drafter writes an isolation-MATCH giant body with Ghidra-derived TYPED parameters
(void func(u32 *a0, s16 *a2)). Placed in the real overlay TU it hits `conflicting types`:
the TU's callers reference the function through the CANONICAL signature declared in
src/shared/engine_core.h (extern void func(s32, s32, void*)) — or, absent that, through
gcc-2.7.2's implicit K&R `int func()` from a call site above the definition. The gate's
sig_unify can't reach the engine_core.h decl (it lives inside a DEFINE_ macro) so the
draft never banks.

This reconciles the DEF to the canonical signature, BYTE-NEUTRALLY:
  1. strip the draft's redefinitions of types already in src/shared/engine_types.h
     (identical-definition typedefs — a redef is a hard error in gcc-2.7.2 / C89);
  2. rewrite the def signature to the canonical (return type + positional param types;
     arity-grow adds unused params so an implicit-int caller with N args still matches);
  3. cast each type-changed param AT ITS USES — never via an intermediate local, which
     introduces a fresh pseudo and shifts register allocation (proven: cast-locals broke
     func_8013B274, at-use casts banked it byte-identical).

The whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9) — a wrong
reconcile simply fails to bank. Canonical form comes from engine_core.h when present,
else the implicit-int-compatible `s32 func(s32,...)` (matches K&R `int func()`).

Usage:
  tools/canon_sig_reconcile.py --fn func_8013B274 --draft .run/drafts-t5-batch2/func_8013B274.c \
      --out .run/t5b2-recon/func_8013B274.c [--sig 'void func_8013B274(s32 a0, s32 a1, void *a2)']
"""
import re, os, argparse

EC = 'src/shared/engine_core.h'
ET = 'src/shared/engine_types.h'


def ambient_typedefs():
    """name -> normalized single-line 'typedef struct {...} name;' from engine_types.h."""
    et = open(ET).read()
    out = {}
    for m in re.finditer(r'typedef\s+struct\s*\{[^}{]*\}\s*([A-Za-z_]\w*)\s*;', et):
        out[m.group(1)] = re.sub(r'\s+', ' ', m.group(0)).strip()
    return out


def canonical_from_engine_core(fn):
    """Return the canonical 'ret ... fn(params)' decl string from engine_core.h, or None."""
    ec = open(EC).read()
    m = re.search(r'extern\s+([^;]*?\b' + re.escape(fn) + r'\s*\(([^;]*)\))\s*;', ec)
    return (re.sub(r'\s+', ' ', m.group(1)).strip()) if m else None


def split_params(param_str):
    """Split a C parameter list on top-level commas -> ['s32 a0', 's16 *a2', ...]."""
    param_str = param_str.strip()
    if param_str in ('', 'void'):
        return []
    out, depth, cur = [], 0, ''
    for ch in param_str:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip()); cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def parse_param(p):
    """'s16 *a2' -> ('s16 *', 'a2').  'void' / unnamed -> (p, None)."""
    m = re.match(r'^(.*?)([A-Za-z_]\w*)\s*$', p.strip())
    if not m:
        return (p.strip(), None)
    typ, name = m.group(1).strip(), m.group(2)
    # a bare type token with no name (e.g. 's32', 'void *') -> name is None
    if typ == '' and name in ('void', 's32', 'u32', 'int', 's16', 'u16', 's8', 'u8', 'char', 'long'):
        return (name, None)
    return (typ, name)


def parse_sig(sig, fn):
    """'void func_X(s32 a0, s16 *a2)' -> (ret, [(type,name),...])."""
    m = re.match(r'^(.*?)\b' + re.escape(fn) + r'\s*\((.*)\)\s*$', sig.strip(), re.S)
    if not m:
        raise ValueError(f'cannot parse sig: {sig!r}')
    ret = m.group(1).strip()
    params = [parse_param(p) for p in split_params(m.group(2))]
    return ret, params


def cast_uses(body, name, orig_type):
    """Blanket-wrap EVERY body use of `name` in `((orig_type)name)`. This preserves the
    original semantics of every use — pointer arithmetic (`name + 1` keeps orig stride),
    index (`name[i]`), deref (`*name`), member (`name->f`), pass-through, AND already-cast
    uses (`(P_TAG*)name` -> `(P_TAG*)((orig)name)`, same bits) — all byte-neutral (a cast
    emits no code). Targeted patterns missed arithmetic (void*+1 != s16*+1); blanket is
    correct and safe (\\b avoids substrings; the def line is in `head`, not `body`)."""
    ot = orig_type.strip()
    return re.sub(r'\b' + re.escape(name) + r'\b', '((' + ot + ')' + name + ')', body)


def strip_conflicting_externs(draft, ambient):
    """Remove the draft's redundant `extern` decls — the `conflicting types` source. The TU's
    #includes (common.h + engine_core.h) and its per-TU canonical-sig layer already declare
    these; the draft's Ghidra-typed re-declaration conflicts. Strip an extern when its symbol
    is in `ambient` (declared by engine_core.h/engine_types.h or the target TU), and always
    strip a `memcpy` extern (the TU's macros / gcc builtin provide it — a mismatched prototype
    triggers `conflicting types for built-in memcpy`). A genuinely-draft-local extern (symbol
    NOT ambient) is kept; the byte-gate is the sole arbiter (G3/P9)."""
    def drop_fn(m):
        return '' if m.group(1) in ambient else m.group(0)
    # extern function decls (func_XXXX or memcpy/library)
    draft = re.sub(r'^\s*extern\s+[^;\n]*?\b(func_[0-9A-Fa-f]+)\s*\([^;\n]*\)\s*;\s*\n',
                   drop_fn, draft, flags=re.M)
    draft = re.sub(r'^\s*extern\s+[^;\n]*?\bmemcpy\s*\([^;\n]*\)\s*;\s*\n', '', draft, flags=re.M)
    # extern DATA decls (one line may declare several: `extern s16 D_a, D_b;`)
    def drop_data(m):
        names = re.findall(r'\b(D_[0-9A-Fa-f]+)\b', m.group(0))
        return '' if names and all(n in ambient for n in names) else m.group(0)
    draft = re.sub(r'^\s*extern\s+[^;\n]*\bD_[0-9A-Fa-f]+[^;\n]*;\s*\n', drop_data, draft, flags=re.M)
    return draft


def ambient_symbol_names(tu_path=None):
    """Every func_/D_ symbol declared by engine_core.h/engine_types.h (and the target TU, if
    given) — the set whose draft re-declarations are redundant + conflict-prone."""
    names = set()
    for p in (EC, ET, tu_path):
        if p and os.path.exists(p):
            txt = open(p).read()
            names |= set(re.findall(r'\b(func_[0-9A-Fa-f]+)\b', txt))
            names |= set(re.findall(r'\b(D_[0-9A-Fa-f]+)\b', txt))
    return names


def reconcile(fn, draft, canon_sig=None, tu_path=None):
    amb = ambient_typedefs()
    # 1) strip ambient-dup typedefs (identical definition only -> byte-neutral)
    def strip_td(m):
        name = m.group(1); norm = re.sub(r'\s+', ' ', m.group(0)).strip()
        return '' if (name in amb and amb[name] == norm) else m.group(0)
    draft = re.sub(r'typedef\s+struct\s*\{[^}{]*\}\s*([A-Za-z_]\w*)\s*;\n?', strip_td, draft)

    # 1b) strip the draft's redundant externs (func/data/memcpy) that engine_core.h/the TU declares
    draft = strip_conflicting_externs(draft, ambient_symbol_names(tu_path))

    # locate the definition signature (ret fn(params) {)
    dm = re.search(r'\n((?:[A-Za-z_][\w ]*?\*?\s*)\b' + re.escape(fn) + r'\s*\([^;{]*\))\s*\n?\{', draft)
    if not dm:
        raise ValueError(f'no definition of {fn} found in draft')
    draft_sig = dm.group(1)
    dret, dparams = parse_sig(draft_sig, fn)

    # 2) determine canonical
    canon_sig = canon_sig or canonical_from_engine_core(fn)
    if not canon_sig:
        # implicit-int-compatible fallback: s32 return + s32 params, keep draft arity
        cret, cparams = 's32', [('s32', None)] * len(dparams)
    else:
        cret, cparams = parse_sig(canon_sig, fn)

    # 3) build the new param list (keep DRAFT names; use CANONICAL types positionally),
    #    and record which positions changed type (need at-use casts).
    new_params, changed = [], []
    for i in range(max(len(dparams), len(cparams))):
        dt, dn = dparams[i] if i < len(dparams) else (None, None)
        ct, cn = cparams[i] if i < len(cparams) else (None, None)
        if dt is None:                       # arity grow: canonical has an extra param
            new_params.append(f'{ct} _unused{i}'); continue
        if ct is None:                       # canonical shorter (rare) — keep draft param as-is
            new_params.append(f'{dt} {dn}' if dn else dt); continue
        ntd = re.sub(r'\s+', ' ', dt).strip()
        ntc = re.sub(r'\s+', ' ', ct).strip()
        if dn is None:
            new_params.append(ct); continue
        new_params.append(f'{ct} {dn}' if not ct.endswith('*') else f'{ct}{dn}')
        if ntc != ntd:
            changed.append((dn, dt))

    new_sig = f'{cret} {fn}(' + ', '.join(new_params) + ')'

    # split body from the def line so casts only touch the body
    head, body = draft[:dm.start(1)], draft[dm.end(1):]
    for name, orig_type in changed:
        body = cast_uses(body, name, orig_type)

    return head + new_sig + body


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--fn', required=True)
    ap.add_argument('--draft', required=True)
    ap.add_argument('--out', required=True)
    ap.add_argument('--sig', default=None, help='explicit canonical sig (else engine_core.h / implicit-int)')
    ap.add_argument('--tu', default=None, help='target TU .c (its already-declared symbols are treated as ambient)')
    a = ap.parse_args()
    out = reconcile(a.fn, open(a.draft).read(), a.sig, a.tu)
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    open(a.out, 'w').write(out)
    canon = a.sig or canonical_from_engine_core(a.fn) or '(implicit-int s32-form)'
    print(f'{a.fn}: reconciled -> {a.out}  [canonical: {canon}]')


if __name__ == '__main__':
    main()

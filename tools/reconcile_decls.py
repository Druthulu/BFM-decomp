#!/usr/bin/env python3
"""reconcile_decls.py — the DATA-symbol analog of cast_call_sites.py (Phase 24 T7b, cookbook §33).

A freshly-matched giant / wave draft byte-matches STANDALONE with its own guessed decls, but to bank
×1 in the overlay TU (and then propagate ×134 via a shared `DEFINE_func_*` macro) its callee/data
externs must be FLEET-CANONICAL — otherwise `conflicting types` vs engine_core.h / sibling decls
(a COMPILE error, not a byte miss). `cast_call_sites.py` handles this for callee FUNCTIONS
(decl->canonical + fn-ptr cast at the call). This tool does the same for DATA symbols `D_XXXX`:
rewrite the draft's `extern <T_draft> D_x...;` -> the fleet-canonical decl, and inject a byte-neutral
cast at each ACCESS so the load/store opcode is unchanged. gcc-2.7.2 folds the compile-time
pointer/scalar cast of a known symbol, so the body bytes are identical.

This is a PURE draft-text transform (like sig_unify / cast_call_sites / canon_resident_calls): the
whole-binary `harvest_verify` byte-gate remains the sole arbiter (G3/P9) — a wrong reconcile just
fails the gate and reverts, so it trial-and-errors safely. It does NOT touch callee FUNCTION decls
(that's cast_call_sites/sig_unify — compose them). It changes only the draft's OWN data externs +
the access sites; it never edits the fleet's canonical decls.

Byte-neutral cast taxonomy (proven by hand on func_80129CF8; the intended type is what the DRAFT
declared, the canonical is the fleet's — cast every use to reproduce the intended access):
  draft array Ed[]  vs canonical array Ec[]      -> decl Ec[];   D_x[i] -> ((Ed*)D_x)[i]; D_x -> (Ed*)D_x
  draft array Ed[]  vs canonical struct/scalar   -> decl canon;  D_x    -> (Ed*)&D_x  (address-of the object)
  draft scalar Td   vs canonical scalar Tc       -> decl Tc;     D_x    -> *(Td*)&D_x (forces the Td-width opcode)
  draft ptr  P* D_x vs canonical scalar Tc       -> decl Tc;     write D_x=v -> D_x=(Tc)(v); read D_x -> (P*)D_x

Pipeline (cookbook §33):
  draft -> canon_resident_calls -> cast_call_sites -> reconcile_decls -> sig_unify -> harvest_verify --chunk 1
                                    (callee funcs)     (data symbols)     (def sig)   (the byte-gate)

Usage:
  tools/reconcile_decls.py --overlay ov_SC01_077 --src-file src/ov_SC01_077/ov_SC01_077_a.c \
        --in .run/drafts-giant --out .run/drafts-giant-rc
  tools/reconcile_decls.py --print-canon D_80126948          # inspect the oracle's pick for one symbol
"""
import argparse, os, re, glob, importlib.util, collections

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def _load(mod, rel):
    spec = importlib.util.spec_from_file_location(mod, os.path.join(REPO, rel))
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


_ght = _load('ght', 'tools/gen_harvest_targets.py')   # reuse collect_data_decls / the D_ regexes

# `extern <type> D_XXXX;` or `extern <type> D_XXXX[];` (optional trailing /* comment */). <type> may
# carry a trailing `*` (pointer) which we fold into the element type.
DATA_DECL_LINE_RE = re.compile(
    r'^([ \t]*)extern\s+([A-Za-z_][\w \t]*?)\s*(\*?)\s*\b(D_[0-9A-Fa-f]+)\b\s*(\[\s*\])?\s*;'
    r'[ \t]*(?:/\*[^\n]*\*/)?[ \t]*$')


# ---------------------------------------------------------------- the canonical-type ORACLE (T2)
def canonical_data_map(extra_src=None):
    """Fleet-majority canonical decl per data symbol. Returns {D_name: 'extern <decl>;'}.

    Precedence: an engine_core.h macro decl is AUTHORITATIVE (it's the shared/propagated set every
    overlay co-instantiates — conforming to it is what avoids the per-overlay macro conflict). Else
    the plurality vote across all overlays + resident (ties -> the lexicographically-first spelling,
    deterministic). This is the picker the design-doc flagged as missing (gen_harvest_targets read
    only engine_core.h + ONE overlay, first-seen-wins, and never saw a fleet disagreement)."""
    ec = os.path.join(REPO, 'src/shared/engine_core.h')
    # 1. engine_core.h — authoritative (a symbol declared inside any DEFINE_ macro)
    ec_decls = _ght.collect_data_decls([ec])                      # {D_name: 'extern ...;'} first-seen
    # 2. plurality across the fleet (all overlays + resident) for symbols engine_core.h lacks
    votes = collections.defaultdict(collections.Counter)
    fleet = (glob.glob(os.path.join(REPO, 'src/ov_*/*.c'))
             + [os.path.join(REPO, 'src/resident/resident.c')])
    if extra_src:
        fleet.append(os.path.join(REPO, extra_src))
    for p in fleet:
        if not os.path.exists(p):
            continue
        txt = open(p).read()
        for m in _ght.DATA_DECL_RE.finditer(txt):
            decl = re.sub(r'\s+', ' ', m.group(1)).strip()
            nm = re.search(r'D_[0-9A-Fa-f]+', decl)
            if nm:
                votes[nm.group(0)][f'extern {decl};'] += 1
    canon = {}
    names = set(ec_decls) | set(votes)
    for nm in names:
        if nm in ec_decls:
            canon[nm] = ec_decls[nm]                              # authoritative
        else:
            # plurality; tie -> lexicographically-first decl spelling (deterministic)
            best = sorted(votes[nm].items(), key=lambda kv: (-kv[1], kv[0]))[0][0]
            canon[nm] = best
    return canon


def parse_data_decl(decl):
    """'extern u8 D_x[];' -> (name, elem='u8', is_array=True, is_ptr=False).
       'extern struct BigCopy D_x;' -> (name, 'struct BigCopy', False, False).
       'extern s32 *D_x;' -> (name, 's32', False, is_ptr=True)."""
    m = DATA_DECL_LINE_RE.match(decl) or DATA_DECL_LINE_RE.match('    ' + decl.strip())
    if not m:
        return None
    _indent, base, star, name, arr = m.group(1), m.group(2), m.group(3), m.group(4), m.group(5)
    return name, re.sub(r'\s+', ' ', base).strip(), bool(arr), bool(star)


def _norm_type(elem, is_array, is_ptr):
    """Spelling-insensitive key for 'do these decls differ' — collapse int-family aliases (same
    width+conv, casting them is a no-op), normalise whitespace. Array vs ptr vs scalar are distinct."""
    e = re.sub(r'\s+', ' ', elem).strip()
    e = re.sub(r'\b(s32|u32|int|unsigned int|unsigned|long|unsigned long|u_long)\b', 'int', e)
    kind = 'arr' if is_array else ('ptr' if is_ptr else 'sca')
    return (e, kind)


def _base_ptr_expr(name, ielem, canon_is_array):
    """The draft's intended array/base pointer, expressed under the canonical storage decl.
    canonical array  -> the array decays: (Ed*)D_x
    canonical struct/scalar -> take its address: (Ed*)&D_x"""
    return f'(({ielem} *){name})' if canon_is_array else f'(({ielem} *)&{name})'


def data_access_subs(name, idecl, cdecl):
    """One (compiled-regex, replacement-fn) that reproduces the DRAFT's intended access to `name`
    under the CANONICAL storage decl in a SINGLE pass (re.sub never re-scans its own output, so a
    symbol appearing in several forms on one line can't double-wrap). [] if type-compatible, None if
    unparseable. The regex captures an optional leading `&` and a following `[` to pick the form."""
    ip = parse_data_decl(idecl)
    cp = parse_data_decl(cdecl)
    if not ip or not cp:
        return None                                   # unparseable -> caller logs, leaves as-is
    _, ielem, iarr, iptr = ip
    _, celem, carr, cptr = cp
    if _norm_type(ielem, iarr, iptr) == _norm_type(celem, carr, cptr):
        return []                                     # already compatible
    rx = re.compile(rf'(&?)\b{re.escape(name)}\b(\s*\[)?')
    if iarr:
        base = _base_ptr_expr(name, ielem, carr)      # (Ed*)D_x  or  (Ed*)&D_x  (canon array vs not)
        def repl(m):
            amp, idx = m.group(1), m.group(2)
            if idx:                                   # D_x[i] / &D_x[i]  -> [&]base[i]
                return f'{amp}{base}{idx}'
            return base                               # bare D_x / &D_x -> base (array address IS the base ptr)
    else:
        # scalar (signedness/width) OR ptr-vs-scalar: force the intended-width/type access via a
        # cast-lvalue `*(<intended> *)&D_x` (valid as both lvalue and rvalue; ptr-intended -> `ielem **`).
        star = ' *' if iptr else ''
        acc = f'(*({ielem}{star} *)&{name})'
        def repl(m):
            amp, idx = m.group(1), m.group(2)
            return f'{amp}{acc}{idx or ""}'
    return [(rx, repl)]


# ---------------------------------------------------------------- the transform (T3)
def transform(text, canon):
    """Return (new_text, n_data_reconciled, notes). For each data symbol the draft declares with a
    type differing from the fleet-canonical: rewrite the decl -> canonical + cast every access."""
    lines = text.split('\n')
    plan = {}            # D_name -> (canonical_decl_line, [subs])
    decl_idx = {}        # D_name -> line index of its decl
    notes = []
    for i, ln in enumerate(lines):
        m = DATA_DECL_LINE_RE.match(ln)
        if not m:
            continue
        indent, name = m.group(1), m.group(4)
        idecl = ln.strip()
        if name not in canon:
            continue                                  # no fleet decl -> draft's is the only one, keep
        cdecl = canon[name]
        subs = data_access_subs(name, idecl, cdecl)
        if subs is None:
            notes.append(f'{name}: UNPARSEABLE decl, left as-is'); continue
        if not subs:
            continue                                  # already compatible -> nothing to do
        plan[name] = (f'{indent}{cdecl}', subs)
        decl_idx[name] = i

    if not plan:
        return text, 0, notes

    out = []
    for i, ln in enumerate(lines):
        dname = next((n for n, j in decl_idx.items() if j == i), None)
        if dname is not None:
            out.append(plan[dname][0])                # replace the decl line with the canonical decl
            continue
        if DATA_DECL_LINE_RE.match(ln):               # some OTHER data decl -> never cast in a decl
            out.append(ln); continue
        for name, (_c, subs) in plan.items():          # body line -> rewrite this symbol's accesses
            for rx, rep in subs:
                ln = rx.sub(rep, ln)
        out.append(ln)
    return '\n'.join(out), len(plan), notes


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--overlay', default='ov_SC01_077')
    ap.add_argument('--src-file', dest='src_file', default=None,
                    help='overlay .c whose local decls also vote (default: none; the fleet scan '
                         'already covers all overlays)')
    ap.add_argument('--in', dest='indir')
    ap.add_argument('--out', dest='outdir')
    ap.add_argument('--print-canon', metavar='D_XXXX', help='print the oracle pick for one symbol and exit')
    a = ap.parse_args()

    canon = canonical_data_map(a.src_file)
    if a.print_canon:
        print(canon.get(a.print_canon, f'(no fleet decl for {a.print_canon})'))
        return
    if not (a.indir and a.outdir):
        ap.error('need --in and --out (or --print-canon)')

    os.makedirs(os.path.join(REPO, a.outdir), exist_ok=True)
    drafts = touched = total = 0
    for p in sorted(glob.glob(os.path.join(REPO, a.indir, '*.c'))):
        new, k, notes = transform(open(p).read(), canon)
        open(os.path.join(REPO, a.outdir, os.path.basename(p)), 'w').write(new)
        drafts += 1
        if k:
            touched += 1; total += k
        for n in notes:
            print(f'  [{os.path.basename(p)}] {n}')
    print(f'canonical data decls: {len(canon)}; drafts: {drafts}; '
          f'reconciled: {touched} draft(s), {total} data symbol(s)')


if __name__ == '__main__':
    main()

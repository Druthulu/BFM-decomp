#!/usr/bin/env python3
"""Generate a callee-signature-aware harvest target manifest for the shared-core harvest.

Phase 15 / T6 (cookbook §12, §14b). For a source overlay (default ov_SC01_077), enumerate the
still-INCLUDE_ASM functions, compute each one's cross-overlay reach (how many of the 134 overlays
hold a byte-identical copy, via h_exact), and — the key move that breaks the extern-type-conflict
wall (§14b) — PRE-RESOLVE every callee's C signature from the already-written source (engine_core.h
DEFINE macros + inline defs in the source overlay's .c). An agent drafting a wrapper then reuses the
EXACT signature of every C-defined callee (no guessing → no `conflicting types` build failure); a
callee that is still a stub takes any consistent extern (the asm provides the symbol).

Output: JSON list of {addr, name, nins, ncalls, reach, callees:[{addr,status,signature}]} ranked by
leverage (reach*nins desc). Whole-binary harvest_verify remains the sole byte-gate (G3/P9); this only
shapes the drafting.

Usage:
  tools/gen_harvest_targets.py [--source ov_SC01_077] [--min-reach 2] [--min-nins 1]
      [--max-nins 150] [--require-calls] [--limit N] [--out .run/t6_targets.json]
"""
import argparse, json, re, sys, glob, os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

INCLUDE_ASM_RE = re.compile(r'INCLUDE_ASM\([^)]*,\s*(func_[0-9A-Fa-f]+)\s*\)')
# an inline function definition line: "<type...> func_XXXX(<params>) {" at COLUMN 0 with a
# type-only prefix (word chars / spaces / `*` only — NO parens or operators). The old
# `^\s*([A-Za-z_].*?\b...` matched an INDENTED call expression like
# `    if (func_X(...) == 0x2000 && ...) {` as a "definition" → a garbled callee "signature"
# that agents paste verbatim as an extern → PARSE error at the gate (Phase-19 T3 batch-1 bug).
# Column-0 + `[\w \t\*]` before func_X excludes both the indentation and the `if (` paren.
INLINE_DEF_RE = re.compile(r'^([A-Za-z_][\w \t\*]*?\bfunc_[0-9A-Fa-f]+\s*\([^;{]*\))\s*\{', re.M)
DEFINE_HDR_RE = re.compile(r'^#define\s+DEFINE_(func_[0-9A-Fa-f]+)\(\)\s*\\?\s*$', re.M)
# inside a DEFINE macro body, the signature line (may be preceded by `extern ...;` lines).
# `[\s\\]*` (NOT `\s*`) between the `)` and the `{`: a macro whose opening brace sits on its OWN
# continuation line has a line-continuation BACKSLASH between them —
#     s32 func_80148824(void *arg0) \
#     { \
# and `\s` does not match `\`. The old `\s*{` therefore silently dropped every own-line-brace macro:
# 186 of 1801 (10%) of engine_core.h's shared signatures were MISSING from the canonical-callee
# oracle that cast_call_sites / sig_unify / gen_harvest_targets resolve against — so a draft calling
# one of them kept its own guessed sig, hit `conflicting types` against the TU's real definition, and
# the "recovery" pass reported nothing to fix. (Phase 26 session 8; the same brace-placement class as
# the §19 find_site bug and scope_data_externs' own-line-brace bug — see cookbook §40.)
SIG_IN_BODY_RE = re.compile(r'([A-Za-z_][^\\]*?\b(func_[0-9A-Fa-f]+)\s*\([^;{]*\))[\s\\]*\{')


def load_sig(path):
    """addr-int -> record. Sig addrs/calls are lowercase hex without 0x in `calls`, addr has 0x."""
    out = {}
    if not os.path.exists(path):
        return out
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            r = json.loads(line)
            out[int(r['addr'], 16)] = r
    return out


def collect_define_sigs(header_path):
    """engine_core.h: DEFINE_func_X -> signature string '<type> func_X(<params>)'."""
    sigs = {}
    if not os.path.exists(header_path):
        return sigs
    # line-by-line: a macro is `#define DEFINE_func_X() \` + continuation lines (each ending `\`)
    # until the first that does not. The sig line `<type> func_X(...) {` lives in that block
    # (possibly preceded by `extern ...;` continuation lines). Reading txt[start:].splitlines()
    # broke on the leading-empty split artifact — iterate explicit line indices instead.
    lines = open(header_path).read().splitlines()
    hdr = re.compile(r'^#define\s+DEFINE_(func_[0-9A-Fa-f]+)\(\)')
    i = 0
    while i < len(lines):
        m = hdr.match(lines[i])
        if not m:
            i += 1
            continue
        name = m.group(1)
        body, j = [], i
        while j < len(lines):
            body.append(lines[j])
            if not lines[j].rstrip().endswith('\\'):
                break
            j += 1
        sm = SIG_IN_BODY_RE.search('\n'.join(body))
        if sm and sm.group(2) == name:
            sigs[int(name[5:], 16)] = re.sub(r'\s+', ' ', sm.group(1)).strip()
        i = j + 1
    return sigs


EXTERN_DECL_RE = re.compile(
    r'extern\s+([A-Za-z_][^;]*?\bfunc_[0-9A-Fa-f]+\s*\([^;]*\))\s*;')
# extern declaration of a DATA symbol already written in the banked code
DATA_DECL_RE = re.compile(
    r'extern\s+([A-Za-z_][\w\s\*]*?\bD_[0-9A-Fa-f]+\s*(?:\[\s*\])?)\s*;')
# a D_XXXX reference inside a target's .s (via %hi/%lo)
ASM_DATA_REF_RE = re.compile(r'\b(D_[0-9A-Fa-f]+)\b')


def collect_data_decls(paths):
    """addr-keyed canonical `extern <type> D_XXXX...;` from banked code (first-seen wins;
    the banked set is build-consistent so all agree). Returns {D_name: 'extern <type> D_..;'}."""
    out = {}
    for p in paths:
        if not os.path.exists(p):
            continue
        for m in DATA_DECL_RE.finditer(open(p).read()):
            decl = re.sub(r'\s+', ' ', m.group(1)).strip()
            nm = re.search(r'D_[0-9A-Fa-f]+', decl)
            if nm:
                out.setdefault(nm.group(0), f'extern {decl};')
    return out


def collect_extern_sigs(paths):
    """Harvest `extern <type> func_X(<params>);` declarations already written anywhere
    (engine_core.h macros, the overlay .c). A STUB callee with no body still has an
    authoritative signature if some other draft already declared it — every new draft must
    reuse THAT signature or gcc errors `conflicting types`. addr-int -> normalized sig.
    If two decls disagree, the first wins (s32==int for codegen; real disagreements are rare
    and surface in the byte-gate)."""
    sigs = {}
    for p in paths:
        if not os.path.exists(p):
            continue
        for m in EXTERN_DECL_RE.finditer(open(p).read()):
            sig = re.sub(r'\s+', ' ', m.group(1)).strip()
            nm = re.search(r'func_([0-9A-Fa-f]+)', sig)
            if nm:
                a = int(nm.group(1), 16)
                sigs.setdefault(a, sig)
    return sigs


def collect_inline_sigs(c_path):
    """source overlay .c: inline-defined func sigs (077-local matches not yet propagated)."""
    sigs = {}
    txt = open(c_path).read()
    for m in INLINE_DEF_RE.finditer(txt):
        sig = re.sub(r'\s+', ' ', m.group(1)).strip()
        nm = re.search(r'func_[0-9A-Fa-f]+', sig)
        if nm:
            sigs[int(nm.group(0)[5:], 16)] = sig
    return sigs


def collect_stubs(c_path):
    txt = open(c_path).read()
    return {int(n[5:], 16) for n in INCLUDE_ASM_RE.findall(txt)}


def main():
    import frozen; frozen.refuse("gen_harvest_targets.py", "tools/share_census.py", "it collects harvest targets from the macro header engine_core.h (gone)")  # Phase 35 T6: FROZEN
    ap = argparse.ArgumentParser()
    ap.add_argument('--source', default='ov_SC01_077')
    ap.add_argument('--min-reach', type=int, default=2)
    ap.add_argument('--min-nins', type=int, default=1)
    ap.add_argument('--max-nins', type=int, default=150)
    ap.add_argument('--require-calls', action='store_true',
                    help='only functions with >=1 jal callee (the call-heavy shared core, T6)')
    ap.add_argument('--limit', type=int, default=0)
    ap.add_argument('--asm-dir', default=None,
                    help='dir of per-fn .s (default asm/<source>/nonmatchings/<source>); '
                         'scanned for D_XXXX data refs to resolve their canonical decls')
    ap.add_argument('--out', default='.run/t6_targets.json')
    args = ap.parse_args()

    src_sig_path = os.path.join(REPO, f'.run/sig.{args.source}.jsonl')
    src_sig = load_sig(src_sig_path)
    if not src_sig:
        sys.exit(f'no source sig at {src_sig_path}')

    c_path = os.path.join(REPO, f'src/{args.source}/{args.source}.c')
    stubs = collect_stubs(c_path)
    define_sigs = collect_define_sigs(os.path.join(REPO, 'src/shared/engine_core.h'))
    inline_sigs = collect_inline_sigs(c_path)
    # a callee may also be a DEFINE in the source .c (DEFINE_func_X()) -> resolves to engine_core sig
    defined_sigs = {}
    defined_sigs.update(define_sigs)
    defined_sigs.update(inline_sigs)  # inline defs win if both (same body anyway)
    # extern declarations already written anywhere (for stub callees with no body)
    extern_sigs = collect_extern_sigs([
        os.path.join(REPO, 'src/shared/engine_core.h'), c_path])
    # canonical DATA-symbol declarations already written (the §14c(c) conflict source)
    data_decls = collect_data_decls([
        os.path.join(REPO, 'src/shared/engine_core.h'), c_path])
    asm_dir = args.asm_dir or os.path.join(
        REPO, f'asm/{args.source}/nonmatchings/{args.source}')

    # global reach map: h_exact -> count of overlay binaries holding it
    reach = {}
    for p in glob.glob(os.path.join(REPO, '.run/sig.ov_*.jsonl')):
        seen = set()
        with open(p) as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                h = json.loads(line)['h_exact']
                seen.add(h)
        for h in seen:
            reach[h] = reach.get(h, 0) + 1

    targets = []
    for addr, rec in src_sig.items():
        if addr not in stubs:
            continue
        nins = rec['nins']
        if nins < args.min_nins or nins > args.max_nins:
            continue
        calls = rec.get('calls', [])
        if args.require_calls and not calls:
            continue
        rch = reach.get(rec['h_exact'], 1)
        if rch < args.min_reach:
            continue
        callees = []
        for ch in calls:
            caddr = int(ch, 16)
            sym = f'func_{caddr:08X}'  # canonical uppercase (splat/asm/INCLUDE_ASM convention)
            if caddr in defined_sigs:
                callees.append({'sym': sym, 'status': 'defined',
                                'signature': defined_sigs[caddr]})
            elif caddr in extern_sigs:
                # stub callee, but already extern-declared elsewhere -> MUST reuse that sig
                callees.append({'sym': sym, 'status': 'declared',
                                'signature': extern_sigs[caddr]})
            else:
                instub = caddr in stubs
                callees.append({'sym': sym,
                                'status': 'stub' if instub else 'extern',
                                'signature': None})
        # scan the target's .s for D_XXXX data refs; resolve canonical decls (avoids §14c(c))
        data = []
        sp = os.path.join(asm_dir, f'func_{addr:08X}.s')
        if os.path.exists(sp):
            seen = set()
            for dm in ASM_DATA_REF_RE.finditer(open(sp).read()):
                d = dm.group(0)
                if d in seen:
                    continue
                seen.add(d)
                if d in data_decls:
                    data.append({'sym': d, 'decl': data_decls[d]})
                else:
                    data.append({'sym': d, 'decl': None})  # new; agent infers from .s
        targets.append({
            'addr': rec['addr'], 'name': f'func_{addr:08X}', 'nins': nins,
            'ncalls': len(calls), 'reach': rch,
            'leverage': rch * nins, 'callees': callees, 'data': data,
        })

    targets.sort(key=lambda t: (t['leverage'], t['reach'], t['nins']), reverse=True)
    if args.limit:
        targets = targets[:args.limit]

    outp = os.path.join(REPO, args.out)
    os.makedirs(os.path.dirname(outp), exist_ok=True)
    with open(outp, 'w') as f:
        json.dump(targets, f, indent=1)

    # summary to stderr
    n = len(targets)
    leaves = sum(1 for t in targets if t['ncalls'] == 0)
    callh = n - leaves
    def cc(st):
        return sum(1 for t in targets for c in t['callees'] if c['status'] == st)
    print(f'targets: {n}  (leaf {leaves} / call-heavy {callh})', file=sys.stderr)
    print(f'callees: {cc("defined")} defined-sig + {cc("declared")} extern-declared (reuse EXACT) / '
          f'{cc("stub")} undeclared-stub / {cc("extern")} extern (resident/EXE, conflict-free)',
          file=sys.stderr)
    dres = sum(1 for t in targets for d in t.get('data', []) if d['decl'])
    dnew = sum(1 for t in targets for d in t.get('data', []) if not d['decl'])
    print(f'data refs: {dres} resolved-to-canonical-decl / {dnew} new (agent infers from .s)',
          file=sys.stderr)
    if targets:
        print(f'leverage range: {targets[0]["leverage"]} (reach {targets[0]["reach"]} x '
              f'{targets[0]["nins"]} ins) .. {targets[-1]["leverage"]}', file=sys.stderr)
        # reach histogram
        from collections import Counter
        rc = Counter(t['reach'] for t in targets)
        buckets = {'134': 0, '100-133': 0, '50-99': 0, '10-49': 0, '2-9': 0}
        for r, c in rc.items():
            if r >= 134: buckets['134'] += c
            elif r >= 100: buckets['100-133'] += c
            elif r >= 50: buckets['50-99'] += c
            elif r >= 10: buckets['10-49'] += c
            else: buckets['2-9'] += c
        print('reach buckets: ' + '  '.join(f'{k}:{v}' for k, v in buckets.items()), file=sys.stderr)
    print(f'wrote {outp}', file=sys.stderr)


if __name__ == '__main__':
    main()

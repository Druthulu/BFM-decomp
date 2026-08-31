#!/usr/bin/env python3
"""blocker_probe.py — WHY does a byte-correct draft fail the whole-binary gate?  Read-only.

A crack wave produces drafts that `match_one` calls MATCH but the whole-binary gate rejects
(~92% draft-correct, ~27% bank — the SESSION-15 efficiency audit).  Those are byte-correct
bodies stranded by a DECLARATION conflict, not wrong instructions.  This says which one, per
function, and it does so with TWO INDEPENDENT ORACLES because a single oracle that is
structurally blind to a class of error cannot be fixed by making it stricter (R34):

  ORACLE A — static.  Parses the draft and everything the TU declares (`cdecl`, the
      coverage-asserting C-declaration parser) and asks cc1's OWN compatibility question via
      `cdecl.compatible`.  It is fast, it names the exact pair of declarations, and it is the
      only oracle that can attribute a conflict to a SOURCE (the TU's own text vs a
      `DEFINE_func_*` macro body in the shared header) — which is what decides the blast
      radius of any fix.  It CANNOT see: anything order-dependent that cc1 resolves
      differently, and any error that is not a declaration conflict.
  ORACLE B — the real cc1.  Shells out to `tools/rtu_match.py`, which compiles the WHOLE split
      TU with the draft spliced and `INCLUDE_ASM` neutralised.  It is the ground truth for
      "does this compile", and it additionally reports MATCH/DIFF for the spliced body in its
      REAL ambient context.  It CANNOT see: link-time errors (undefined reference — the §58a
      Ghidra-name class), and it is relocation-masked, so it can over-claim MATCH.

Neither is the arbiter.  The whole-binary byte-gate is (G3/P9).  What this tool produces is the
CEILING and the routing: which recovery transform each stranded draft needs, and — from the
disagreement column — how much the static classifier can be trusted at all.  A prior static
classifier (`.run/diag_plumbing.py`, deleted by this tool) compared declaration TEXT, so
`extern u8 D_X;` vs `extern unsigned char D_X;` read as a conflict though `common.h` makes them
the same type and cc1 accepts both silently.  Text equality is never the question; `compatible`
is.

  tools/blocker_probe.py --binary ov_SC07_006 --drafts .run/drafts-s15,.run/drafts-s14r
  tools/blocker_probe.py --binary ov_SC07_006 --drafts .run/drafts-s15 --fns func_80161374 -v

Writes NOTHING outside --work (and --json).  Never touches src/.
"""
import argparse, concurrent.futures, json, os, re, subprocess, sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, HERE)
import cdecl
import corpus

ENGINE_CORE = os.path.join(REPO, 'src/shared/engine_core.h')
DRAFT_RE = re.compile(r'^func_[0-9A-Fa-f]{8}\.c$')      # wave dirs also hold scratch: _b.c, try2.c …
PY = os.path.join(REPO, '.venv/bin/python')

# A blocker class -> the recovery tier it implies.  This is the routing the pass exists to produce.
#   T0 draft-only     : rewrite the draft; per-binary gate is sufficient
#   T1 binary-local   : edit src/<binary>/**; per-binary gate is sufficient (cannot reach another binary)
#   T2 fleet-shared   : edit src/shared/**; R22 clean-fleet is MANDATORY (§61, §63 UPDATE)
TIER = {
    'callee_decl':     'T0',   # cast_call_sites / reconcile_tu — rewrite the draft's own externs
    'data_decl':       'T0',
    'local_type':      'T0',   # rename/drop the draft's duplicate type (the LIFT is only for propagation)
    'self_decl_tu':    'T1',   # normalize_self_decls on the overlay's own TU
    'self_decl_hdr':   'T1',   # de-macroize the one instantiation in the overlay's own TU (§63 escape)
    'parse':           '--',
}


# ---------------------------------------------------------------------------------------------
# ORACLE A — static
# ---------------------------------------------------------------------------------------------
def macro_scope(tu_text, header_path=ENGINE_CORE):
    """{name: (Declarator, macro)} contributed by the `DEFINE_func_*` macros this TU instantiates.

    ATTRIBUTION ONLY — not detection.  `cdecl.tu_scope` runs real cpp (the §8c law), so it already
    expands these instantiations and is authoritative about whether a conflict EXISTS.  What it
    cannot tell you is WHERE the conflicting declaration lives, and that decides which transform
    applies: a declaration in the TU's own text is rewritten in place (normalize_self_decls),
    whereas one inside an instantiated shared-header macro body is escaped by de-macroizing that
    single instantiation (§63's unexplored "per-overlay-local decl").  Both are binary-local; they
    are not the same edit.  Mis-attributing one as the other routes the fix at the wrong file."""
    inst = set(re.findall(r'\b(DEFINE_func_[0-9A-Fa-f]+)\s*\(', tu_text))
    if not inst:
        return {}
    text = open(header_path, errors='replace').read()
    out = {}
    # ONE DEFINITION PER MACRO NAME — THE LAST, BECAUSE THAT IS THE ONE CPP EXPANDS.
    # `src/shared/engine_core.h` holds 1,037 duplicate `DEFINE_func_*` definitions, and FOUR of them
    # have DIFFERENT bodies (DEFINE_func_8013FFD8 / _8013F350 / _80181538 / _801808C4).  cpp uses
    # the last definition of a redefined macro; reading them all in header order made the DEAD first
    # copy the attributed one, so this oracle named a declaration the compiler never expanded — and
    # pointed any fix at a copy where editing silently no-ops.  An oracle that disagrees with the
    # compiler is not a stricter oracle, it is a wrong one (R34).
    last_def = {}
    for m in re.finditer(r'^#define\s+(DEFINE_func_[0-9A-Fa-f]+)\s*\(', text, re.M):
        if m.group(1) in inst:
            last_def[m.group(1)] = m
    for name, m in last_def.items():
        i, body = m.end(), []                            # gather the \-continued logical line
        while i < len(text):
            nl = text.find('\n', i)
            if nl < 0:
                body.append(text[i:]); break
            line = text[i:nl]
            body.append(line.rstrip('\\'))
            if not line.rstrip().endswith('\\'):
                break
            i = nl + 1
        for stmt in re.findall(r'\bextern\b[^;{}]*;', '\n'.join(body)):
            try:
                for d in cdecl.parse(stmt):
                    # first-wins ACROSS distinct macros is unchanged: several macros a TU
                    # instantiates may each declare the same symbol, and all those declarations
                    # really are in the TU.  Only the REDEFINED-macro selection above changed.
                    out.setdefault(d.name, (d, name))
            except cdecl.CDeclError:
                continue                                 # a macro body line cdecl cannot read
    return out


def draft_types(text):
    """Type names the draft DEFINES (typedef aliases + struct/union tags)."""
    names = set(re.findall(r'\btypedef\b[^;]*?\b(\w+)\s*(?:\[[^\]]*\])?\s*;', text, re.S))
    names |= set(re.findall(r'\b(?:struct|union)\s+(\w+)\s*\{', text))
    return {n for n in names if n}


def static_verdict(fn, stub, draft_text):
    """[(klass, detail)] — every declaration in the draft that cc1 would refuse, named."""
    tu_path = os.path.join(REPO, stub.path)
    try:
        ddecls = cdecl.declarations(cdecl.split_statements(draft_text), path='<draft>')
    except cdecl.CDeclError as e:
        return [('parse', 'draft: %s' % str(e).split('\n')[0][:110])]
    try:
        tu = cdecl.tu_scope(tu_path)                     # full scope: a decl BELOW conflicts too
    except cdecl.CDeclError as e:
        return [('parse', 'tu: %s' % str(e).split('\n')[0][:110])]

    tu_text = open(tu_path, errors='replace').read()
    macro = macro_scope(tu_text)

    def whence(name):
        """'tu' | 'hdr:<macro>' — where the conflicting declaration physically lives.  A literal
        declaration in the TU's own text wins: it is the one an in-place rewrite can reach."""
        if re.search(r'^[^/\n]*\b%s\b[^;\n]*;' % re.escape(name), tu_text, re.M):
            return 'tu'
        return 'hdr:' + macro[name][1] if name in macro else 'tu'

    out = []
    for d in ddecls:
        other = tu.get(d.name)
        if other is None or (cdecl.compatible(other, d) and cdecl.compatible(d, other)):
            continue
        src = whence(d.name)
        if d.is_definition and d.name == fn:
            out.append(('self_decl_hdr' if src.startswith('hdr') else 'self_decl_tu',
                        '%s declares %s | def is %s' % (src, other.type, d.type)))
        elif 'typedef' in (d.storage, other.storage):
            # cc1 forbids redeclaring a typedef AT ALL, even identically (`compatible` encodes it).
            # This is a TYPE conflict, not a data conflict: the fix is to rename/drop the draft's
            # copy, which is draft-only — routing it as `data_decl` would send it at the wrong tool.
            out.append(('local_type', '%s: %s declares %s | draft %s' % (d.name, src, other.type, d.type)))
        else:
            klass = 'callee_decl' if d.kind == 'func' else 'data_decl'
            out.append((klass, '%s: %s declares %s | draft %s' % (d.name, src, other.type, d.type)))

    dup = draft_types(draft_text) & (set(cdecl.typedef_names(tu_path))
                                     | set(re.findall(r'\b(?:struct|union)\s+(\w+)\s*\{', tu_text)))
    for t in sorted(dup):
        out.append(('local_type', 'draft redefines type %r the TU already defines' % t))
    return out


# ---------------------------------------------------------------------------------------------
# ORACLE B — the real cc1, over the whole TU
# ---------------------------------------------------------------------------------------------
_WARN = re.compile(r'\bwarning:')
_ERR = re.compile(r'\berror\b|conflicting types|redefinition of|redeclar|parse error|'
                  r'storage size|undefined|has no type or storage class', re.I)


def first_error(errfile):
    """The FIRST non-warning error line.  These TUs emit hundreds of benign `type mismatch with
    previous external decl' warnings, so the tail rtu_match prints inline is usually 100% warnings
    and the real cause is invisible in it (§58's red-herring, one level down)."""
    try:
        lines = open(errfile, errors='replace').read().splitlines()
    except OSError:
        return ''
    for ln in lines:
        if not _WARN.search(ln) and _ERR.search(ln):
            return re.sub(r'^\S*t\.c:', 'tu:', ln.strip())[:120]
    return ''


def cc1_verdict(fn, stub, draft_path, work):
    """('MATCH'|'DIFF'|'CC1-FAIL'|'ERR', detail) from the real whole-TU compile."""
    split = os.path.splitext(os.path.basename(stub.path))[0]
    wd = os.path.join(work, fn)
    err = os.path.join(wd, 'err.txt')
    # PASS THE TU PATH **AND THE ASM SUBDIR**, do not reconstruct either. `stub.path.split('/')[1]` is the overlay layout
    # (src/<binary>/<split>.c); for main the sources are LOOSE FILES in src/, so that expression
    # yields '800.c' as the "source dir" and rtu_match built src/800.c/800.c. Every main draft came
    # back ERR with an empty detail — indistinguishable from a bad draft (measured S68, 4 of 4).
    # The asm subdir has the SAME defect one layer down: rtu_match derives
    # `asm/<source>/nonmatchings/<split>` and produced `asm/src/nonmatchings/800`, while main's real
    # subdir is `asm/nonmatchings/800`. The Stub already carries both facts; reconstruct neither.
    cmd = [PY, os.path.join(HERE, 'rtu_match.py'), fn,
           '--split', split, '--source', stub.path.split('/')[1], '--tu', stub.path,
           '--asm-subdir', stub.asm_dir,
           '--c', draft_path, '--work', wd, '--stderr-out', err, '--maxdiff', '4']
    if corpus.is_o0(stub.path):
        cmd.append('--o0')
    p = subprocess.run(cmd, capture_output=True, cwd=REPO, text=True)
    o = p.stdout
    if 'MATCH (' in o:
        return 'MATCH', re.search(r'MATCH \((\d+) ins\)', o).group(1) + ' ins'
    if o.startswith('DIFF'):
        m = re.search(r'mine=(\d+) ins, target=(\d+) ins, (\d+) mismatched', o)
        return 'DIFF', ('%s/%s ins, %s mismatched' % (m.group(1), m.group(2), m.group(3)) if m else '')
    if 'CC1 FAIL' in o:
        return 'CC1-FAIL', first_error(err) or o.splitlines()[-1][:120]
    return 'ERR', (o.strip().splitlines() or [''])[0][:120]


# ---------------------------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--binary', required=True)
    ap.add_argument('--drafts', required=True, help='comma-separated wave dirs')
    ap.add_argument('--fns', default=None, help='comma-separated subset')
    ap.add_argument('--work', default='.run/recover/probe')
    ap.add_argument('--jobs', type=int, default=8)
    ap.add_argument('--json', default=None)
    ap.add_argument('-v', '--verbose', action='store_true', help='every blocker, not just the first')
    a = ap.parse_args()

    stubs = {s.symbol: s for s in corpus.stubs(a.binary).values()}   # R33: derived, never a hand map
    want = set(a.fns.split(',')) if a.fns else None

    drafts, dup = {}, []
    for d in a.drafts.split(','):
        for b in sorted(os.listdir(os.path.join(REPO, d))):
            if not DRAFT_RE.match(b):
                continue
            fn = b[:-2]
            if want and fn not in want:
                continue
            if fn in drafts:
                dup.append(fn)
            drafts[fn] = os.path.join(REPO, d, b)

    # R32: name what is excluded and why.  A stranded draft that quietly vanishes from the
    # denominator is exactly how a recovery rate gets manufactured.
    stranded = {fn: p for fn, p in drafts.items() if fn in stubs}
    banked = sorted(set(drafts) - set(stranded))
    print('drafts=%d  stranded(still INCLUDE_ASM)=%d  already-banked(excluded)=%d%s'
          % (len(drafts), len(stranded), len(banked), '  dup-across-dirs=%d' % len(dup) if dup else ''))
    if banked:
        print('  excluded as banked: ' + ' '.join(banked))
    if not stranded:
        return 1

    work = os.path.join(REPO, a.work)
    os.makedirs(work, exist_ok=True)
    rows = {}

    def one(fn):
        stub = stubs[fn]
        text = open(stranded[fn], errors='replace').read()
        return fn, static_verdict(fn, stub, text), cc1_verdict(fn, stub, stranded[fn], work)

    with concurrent.futures.ThreadPoolExecutor(max_workers=a.jobs) as ex:
        for fn, st, (cc, det) in ex.map(one, sorted(stranded)):
            # Blockers STACK (cc1 only ever reveals the first).  The tier a function needs is the
            # MAX over all of them: one T1 blocker among four T0s still makes the fix binary-local.
            tiers = sorted(TIER.get(k, '--') for k, _ in st) if st else []
            rows[fn] = {'static': st, 'cc1': cc, 'cc1_detail': det, 'tu': stubs[fn].path,
                        'tier': tiers[-1] if tiers else '--'}

    # ---- the disagreement table (the finding), not the agreement rate -------------------------
    print('\n%-16s %-4s %-14s %-26s %s' % ('fn', 'tier', 'static', 'real cc1', 'agree'))
    print('-' * 108)
    agree = dis_static_only = dis_cc1_only = 0
    for fn in sorted(rows):
        r = rows[fn]
        sk = r['static'][0][0] if r['static'] else 'none'
        blocked_static = bool(r['static']) and sk != 'parse'
        blocked_cc1 = r['cc1'] == 'CC1-FAIL'
        if blocked_static == blocked_cc1:
            verdict, _ = 'yes', 0
            agree += 1
        elif blocked_static:
            verdict = 'STATIC-ONLY'
            dis_static_only += 1
        else:
            verdict = 'CC1-ONLY'
            dis_cc1_only += 1
        print('%-16s %-4s %-14s %-26s %s' % (fn, r['tier'], sk, '%s %s' % (r['cc1'], r['cc1_detail'])[:26],
                                             verdict))
        if a.verbose:
            for k, d in r['static']:
                print('%22s %-14s %s' % ('', k, d))

    n = len(rows)
    ccf = sum(1 for r in rows.values() if r['cc1'] == 'CC1-FAIL')
    mat = sum(1 for r in rows.values() if r['cc1'] == 'MATCH')
    dif = sum(1 for r in rows.values() if r['cc1'] == 'DIFF')
    print('-' * 108)
    print('n=%d   real cc1: CC1-FAIL=%d  DIFF=%d  MATCH=%d' % (n, ccf, dif, mat))
    print('agreement=%d   STATIC-ONLY(false positives)=%d   CC1-ONLY(static blind)=%d'
          % (agree, dis_static_only, dis_cc1_only))
    by = {}
    for r in rows.values():
        for k, _ in (r['static'] or []):
            by[k] = by.get(k, 0) + 1
    if by:
        print('static blockers by class: ' + '  '.join('%s=%d(%s)' % (k, v, TIER.get(k, '--'))
                                                       for k, v in sorted(by.items())))
    print('\nCEILING: a draft that CC1-FAILs is recoverable if its blocker class has a transform;\n'
          '         a draft that already DIFFs in its real TU is NOT an integration problem (G3/P9).')

    if a.json:
        json.dump(rows, open(os.path.join(REPO, a.json), 'w'), indent=1, sort_keys=True)
        print('wrote %s' % a.json)
    return 0


if __name__ == '__main__':
    sys.exit(main())

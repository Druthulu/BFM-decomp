#!/usr/bin/env python3
"""Gate a BATCH of main-EXE drafts the only way main can be gated: a CLEAN rebuild.

WHY THIS EXISTS (P31, 2026-08-15). `gate_lane`/`gate_stage` build INCREMENTALLY. That is fine
for overlays, but main's `make extract` runs the EXE-only `psyq_integrate` + `ld_interleave`
steps which REWRITE THE LINKER SCRIPT. An incremental build after a source change re-runs that
on an already-rewritten `.ld` and produces a FALSE DIFF -- exactly the trap R22's own rationale
describes. This cost the campaign a night: 4 byte-correct main drafts gated 0/4, and I wrote up
a nonexistent "linker defect" before the null-draft control exposed it (with NO draft
substituted at all, `make build BINARY=main` still produced the same wrong hash).

So main is gated like this instead:
    substitute every draft -> make extract BINARY=main -> make build BINARY=main -> compare SHA
ONE clean build verifies the WHOLE BATCH, which is what makes this cheap: 34 functions banked in
a single rebuild. On failure the batch is bisected so one bad draft cannot sink the rest.

TWO MAIN-SPECIFIC HAZARDS THIS TOOL HANDLES:

1. IN-TU CROSS-DRAFT DECLARATION CONFLICTS. Batching N drafts into one .c means their `extern`s
   must agree WITH EACH OTHER, not merely with the file: wave J hit `D_800A4ED4` declared s16 by
   one draft and u16 by another, and `func_8001C9D0` as void / void* / s32 across three. C
   rejects the TU. We resolve greedily (keep in order, drop the incompatible) and REPORT the
   dropped set -- those drafts are usually correct and recoverable with a cast-at-use.
   Compatibility compares TYPE SIGNATURES ONLY: parameter NAMES are irrelevant, and a checker
   that compares them wrongly discards good work (R39 -- I made exactly that mistake first).

2. STALE .s AFTER A REVERT. Once a function becomes C, splat stops emitting its .s. If you then
   revert src/, `corpus.stubs()` raises because the tree and source disagree. Always
   `make extract BINARY=main` BEFORE resolving stubs.

Usage:
  gate_main.py <slate.json> [--apply] [--no-bisect]
     slate.json: [{"fn": ..., "draft": ...}, ...]   (binary is assumed main)
     default is a DRY RUN that reports what would be substituted and any conflicts.
     --apply performs the substitution + clean rebuild and leaves banked drafts in the tree.
"""
import argparse, collections, functools, json, re, subprocess, sys
sys.path.insert(0, 'tools')
import corpus

# stdout is BUFFERED when redirected to a file -- a long run then looks hung with an
# empty log (measured: 16 min of silence during a bisect). Always flush.
print = functools.partial(print, flush=True)

GOOD = '143dbb89f34491258bbc27810d0a12ec8b43a8dd'
TYPES = {'void','char','short','int','long','unsigned','signed','float','double','const',
         'volatile','s8','u8','s16','u16','s32','u32','f32','s64','u64','struct','union'}
DECL = re.compile(r'^\s*extern\s+([^;]+?)\s*;\s*$', re.M)

def sym_of(d):
    m = re.search(r'\b(D_[0-9A-Fa-f]{8}|func_[0-9A-Fa-f]{8}|[A-Za-z_]\w*)\s*(?:\[|\()', d)
    if m: return m.group(1)
    m = re.search(r'\b(D_[0-9A-Fa-f]{8}|func_[0-9A-Fa-f]{8})\b', d)
    return m.group(1) if m else None

def typesig(d):
    """Type signature only. Parameter NAMES do not affect C compatibility (R39: comparing them
    dropped 2 good drafts before I fixed it) -- but the DECLARATOR SUFFIX absolutely does.

    `u8 D_x` and `u8 D_x[]` are INCOMPATIBLE; an earlier version of this function split on the
    symbol and kept only the prefix, so both reduced to ('u8', None) and a real conflict slipped
    through into the build (wave K, D_80078D98: one draft scalar, two array -> compile error
    AFTER the batch had reported BYTE-IDENTICAL). Too-coarse and too-strict are both defects."""
    d = ' '.join(d.split()); sym = sym_of(d) or ''
    m = re.search(r'\((.*)\)\s*$', d)
    ret = d.split(sym)[0].strip() if sym and sym in d else d
    if not m:
        # data decl: keep the declarator suffix ('' vs '[]' vs '[N]' -> normalized to '[]')
        tail = d.split(sym, 1)[1].strip() if sym and sym in d else ''
        tail = '[]' if tail.startswith('[') else tail
        return (ret, tail)
    params = tuple(' '.join(t for t in re.findall(r'[A-Za-z_]\w*|\*', p) if t in TYPES or t == '*')
                   for p in m.group(1).split(','))
    return (ret, params)

def run(cmd, **kw):
    return subprocess.run(cmd, shell=True, capture_output=True, text=True, **kw)

def sha():
    r = run("sha1sum build/us/SLUS_007.26")
    return r.stdout.split()[0] if r.returncode == 0 and r.stdout else None

def resolve_conflicts(slate):
    """Drop drafts whose externs contradict (a) the destination TU's OWN existing declarations,
    or (b) an earlier draft landing in the SAME file.

    Two defects fixed here after the S52 recovery pass (both cost verified-correct drafts):

    (a) THE TABLE STARTED EMPTY. Only draft-vs-draft was compared, so a draft contradicting a
        declaration ALREADY IN the .c sailed through to the rebuild and only surfaced as a
        compile error + bisect. Real case: src/800.c carries `extern void func_8001C9D0(void);`
        (from banked func_8001C2C4) while three wave-J drafts declared it (s32) / (void *).
        The TU is the arbiter (wave law 2) -- so the TU seeds the table.
    (b) ONE NAMESPACE FOR ALL FILES. `seen` was global across the slate, so two drafts landing in
        DIFFERENT .c files could not legally disagree about a symbol -- but they can; separate
        TUs are separate namespaces. Now keyed per destination file (R39: a refusal check that
        discards good work is worse than one that lets a failure through).

    Recovery for a real (a)-class drop is the call-site cast: adopt the TU's declaration verbatim
    and cast at the use site -- including through a function pointer when the TU's prototype takes
    no argument and your call passes one:  ((void (*)(s32))func_8001C9D0)(a0)  (byte-identical;
    verified on all 3 of the above)."""
    stubs = {st.symbol: st for st in corpus.stubs('main').values()}
    kept, dropped = [], []
    seen_by_file, from_tu = {}, {}

    def table(path):
        if path not in seen_by_file:
            t = {}
            try:
                for d in DECL.findall(open(path).read()):
                    s = sym_of(d)
                    if s: t[s] = typesig(d)
            except OSError:
                pass
            seen_by_file[path] = t
            from_tu[path] = set(t)          # so the report can say WHO it clashed with
        return seen_by_file[path]

    for e in slate:
        st = stubs.get(e['fn'])
        path = st.path if st else '<unknown>'
        seen = table(path)
        ds = [(sym_of(d), typesig(d)) for d in DECL.findall(open(e['draft']).read())]
        ds = [(s, t) for s, t in ds if s]
        clash = [(s, seen[s], t) for s, t in ds if s in seen and seen[s] != t]
        if clash:
            sym = clash[0][0]
            dropped.append({'fn': e['fn'], 'symbol': sym, 'file': path,
                            'against': 'the TU itself' if sym in from_tu.get(path, ()) else 'an earlier draft',
                            'kept': str(clash[0][1]), 'this': str(clash[0][2])})
            continue
        for s, t in ds: seen[s] = t
        kept.append(e)
    return kept, dropped

TYPEDEF_BLOCK = re.compile(
    r'^[ \t]*typedef\s+(?:struct|union|enum)?[^;{]*\{[^{}]*\}\s*(\w+)\s*;[ \t]*\n', re.M)
TYPEDEF_PLAIN = re.compile(r'^[ \t]*typedef\s+[\w\s\*]+?\s(\w+)\s*;[ \t]*\n', re.M)

def strip_dup_typedefs(body, already):
    """Drop typedefs the destination TU (or an earlier body in this batch) already defines.

    Each draft is written to compile STANDALONE, so it carries its own `typedef struct {...}
    SVECTOR;`. Once one such function is banked, that typedef lives in the .c forever and every
    later draft defining its own collides -- a C89 duplicate-typedef error, not a byte miss.
    `harvest_verify` already does this; wave L lost a verified-correct draft because this tool
    did not. Returns (body, names_defined_now)."""
    defined = set()
    for pat in (TYPEDEF_BLOCK, TYPEDEF_PLAIN):
        out, pos = [], 0
        for m in pat.finditer(body):
            name = m.group(1)
            if name in already:
                out.append(body[pos:m.start()]); pos = m.end()   # drop the duplicate
            else:
                defined.add(name)
        out.append(body[pos:])
        body = ''.join(out)
    return body, defined

def substitute(entries):
    """Replace each INCLUDE_ASM stub line with its draft body. Returns count."""
    stubs = {st.symbol: st for st in corpus.stubs('main').values()}
    byfile = collections.defaultdict(list)
    for e in entries:
        st = stubs.get(e['fn'])
        if st: byfile[st.path].append((e['fn'], st.asm_dir, e['draft']))
    n = 0
    for path, items in byfile.items():
        t = open(path).read()
        # names the destination file already defines, plus anything a shared header provides
        seen = set(TYPEDEF_BLOCK.findall(t)) | set(TYPEDEF_PLAIN.findall(t))
        for fn, asmdir, draft in items:
            body = "\n".join(l for l in open(draft).read().splitlines()
                             if not l.strip().startswith('#include'))
            body, newly = strip_dup_typedefs(body, seen)
            seen |= newly
            old = f'INCLUDE_ASM("{asmdir}", {fn});'
            if old in t:
                t = t.replace(old, body); n += 1
        open(path, 'w').write(t)
    return n

def clean_build():
    """The ONLY trustworthy main verification: extract (rewrites the .ld) then build.

    DELETE THE OUTPUT FIRST, AND CHECK THE RETURN CODE. sha() reads build/us/SLUS_007.26 off
    disk; if `make build` FAILS (e.g. a compile error) the PREVIOUS successful binary is still
    sitting there, so sha() returns the GOOD hash and this tool reports BYTE-IDENTICAL for a
    build that never ran -- a FALSE PASS. That is exactly how it once claimed "43 banked" on a
    batch whose TU did not compile; the clean-fleet R22 caught it afterwards. A verifier that
    can pass without building is worse than no verifier."""
    run("rm -f build/us/SLUS_007.26")
    run("make extract BINARY=main")
    r = run("make build BINARY=main")
    if r.returncode != 0:
        return None, r                      # build failed -> no hash, and never a pass
    return sha(), r

def try_batch(entries):
    run("git checkout -- src/")
    run("make extract BINARY=main")          # regenerate .s for the reverted stubs (hazard 2)
    substitute(entries)
    got, r = clean_build()
    return got == GOOD, got, r

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('slate'); ap.add_argument('--apply', action='store_true')
    ap.add_argument('--no-bisect', action='store_true')
    a = ap.parse_args()

    slate = json.load(open(a.slate))
    kept, dropped = resolve_conflicts(slate)
    print(f"slate {len(slate)} -> {len(kept)} compatible, {len(dropped)} dropped for in-TU decl conflict")
    for d in dropped:
        print(f"  DROP {d['fn']}: {d['symbol']} clashes with {d.get('against','?')} "
              f"in {d.get('file','?')}  kept={d['kept']}  this={d['this']}")
    if dropped:
        print("  (dropped drafts are usually CORRECT -- recover with a cast-at-use: adopt the")
        print("   other declaration verbatim and adapt at the use site, e.g. (&D_x)[i].)")
    if not a.apply:
        print("\nDRY RUN. Re-run with --apply to substitute and clean-rebuild.")
        return

    ok, got, r = try_batch(kept)
    if ok:
        print(f"\nBANKED {len(kept)} main functions -- {got} BYTE-IDENTICAL")
        json.dump([e['fn'] for e in kept], open('.run/gate_main_banked.json', 'w'))
        return
    # A COMPILE error names its own culprit -- read it instead of bisecting. Bisection here costs
    # a FULL CLEAN REBUILD per step (~2-4 min), so it is worst-case hours; the compiler already
    # told us the symbol and line. (Measured the hard way: a 41-draft bisect ran 28+ min with no
    # output.) Only a byte MISMATCH with a clean compile genuinely needs bisection.
    err = (r.stderr or '') + (r.stdout or '')
    m = re.search(r'^(.*?):(\d+): previous declaration of `([^\']+)\'', err, re.M)
    if m:
        print(f"\nCOMPILE conflict on `{m.group(3)}' at {m.group(1)}:{m.group(2)} —"
              f" NOT bisecting; drop or reconcile the drafts declaring it and re-run.")
        offenders = [e['fn'] for e in kept
                     if re.search(rf"\b{re.escape(m.group(3))}\b", open(e['draft']).read())]
        print("  drafts declaring it:", offenders)
        run("git checkout -- src/")
        return
    print(f"\nbatch FAILED (sha {got}); {'not bisecting' if a.no_bisect else 'bisecting'}")
    if a.no_bisect:
        run("git checkout -- src/"); return
    good = []
    lo = kept
    while lo:
        half = max(1, len(lo)//2)
        head, lo = lo[:half], lo[half:]
        ok, got, _ = try_batch(good + head)
        if ok: good += head
        elif len(head) == 1:
            print(f"  reject {head[0]['fn']}")
        else:
            lo = head + lo   # split further
    ok, got, _ = try_batch(good)
    print(f"\nBANKED {len(good)} of {len(kept)} after bisection -- {got}"
          f"{' BYTE-IDENTICAL' if ok else ' *** STILL MISMATCHED ***'}")
    json.dump([e['fn'] for e in good], open('.run/gate_main_banked.json', 'w'))

if __name__ == '__main__':
    main()

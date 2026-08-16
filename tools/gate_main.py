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
# Same trailing-comment blindness as the typedef patterns had: `;\s*$` misses
# `extern u8 D_800A4640[];   /* the flag table */`, so the destination TU's own declaration went
# UNSEEN and a contradicting draft reached the compiler. Seventh instance of one root cause in
# this file -- a pattern that anchors on end-of-line silently under-reports on commented code,
# and agents comment nearly everything they declare.
DECL = re.compile(r'^\s*extern\s+([^;]+?)\s*;[ \t]*(?://[^\n]*|/\*(?:[^*]|\*(?!/))*\*/[ \t]*)?$',
                  re.M)

def sym_of(d):
    m = re.search(r'\b(D_[0-9A-Fa-f]{8}|func_[0-9A-Fa-f]{8}|[A-Za-z_]\w*)\s*(?:\[|\()', d)
    if m: return m.group(1)
    m = re.search(r'\b(D_[0-9A-Fa-f]{8}|func_[0-9A-Fa-f]{8})\b', d)
    return m.group(1) if m else None

# The project's scalar typedefs. `short` and `s16` are THE SAME TYPE, so two drafts spelling one
# symbol both ways do not conflict -- but a textual comparison calls them different and drops a
# good draft (R39 over-refusal; wave O hit it with `extern short D_800B9A02`). Signedness is NOT
# normalized away: u16 vs s16 is a genuine conflict and must stay one.
_ALIASES = {
    'char': 's8', 'signed char': 's8', 'unsigned char': 'u8',
    'short': 's16', 'signed short': 's16', 'short int': 's16',
    'unsigned short': 'u16', 'unsigned short int': 'u16',
    'int': 's32', 'signed int': 's32', 'long': 's32', 'long int': 's32', 'signed long': 's32',
    'unsigned': 'u32', 'unsigned int': 'u32', 'unsigned long': 'u32', 'float': 'f32',
}


def _alias(t):
    """Normalize a type string's spelling, preserving qualifiers, pointers and signedness."""
    t = ' '.join(t.split())
    t = re.sub(r'^\s*extern\b', '', t).strip()
    quals = []
    for q in ('const', 'volatile'):
        if re.match(r'\b%s\b' % q, t) or (' %s ' % q) in (' ' + t + ' '):
            quals.append(q)
            t = re.sub(r'\b%s\b' % q, '', t).strip()
    stars = ''
    while t.endswith('*'):
        stars = '*' + stars
        t = t[:-1].strip()
    t = ' '.join(t.split())
    t = _ALIASES.get(t, t)
    return ' '.join(quals + ([t + stars] if stars else [t])).strip()


def typesig(d):
    """Type signature only. Parameter NAMES do not affect C compatibility (R39: comparing them
    dropped 2 good drafts before I fixed it) -- but the DECLARATOR SUFFIX absolutely does.

    `u8 D_x` and `u8 D_x[]` are INCOMPATIBLE; an earlier version of this function split on the
    symbol and kept only the prefix, so both reduced to ('u8', None) and a real conflict slipped
    through into the build (wave K, D_80078D98: one draft scalar, two array -> compile error
    AFTER the batch had reported BYTE-IDENTICAL). Too-coarse and too-strict are both defects."""
    d = ' '.join(d.split()); sym = sym_of(d) or ''
    m = re.search(r'\((.*)\)\s*$', d)
    ret = _alias(d.split(sym)[0].strip() if sym and sym in d else d)
    if not m:
        # data decl: keep the declarator suffix ('' vs '[]' vs '[N]' -> normalized to '[]')
        tail = d.split(sym, 1)[1].strip() if sym and sym in d else ''
        tail = '[]' if tail.startswith('[') else tail
        return (ret, tail)
    params = tuple(_alias(' '.join(t for t in re.findall(r'[A-Za-z_]\w*|\*', p) if t in TYPES or t == '*'))
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
        body = open(e['draft']).read()
        ds = [(sym_of(d), typesig(d)) for d in DECL.findall(body)]
        ds = [(s, t) for s, t in ds if s]
        # A DRAFT'S OWN DEFINITION IS A DECLARATION TOO (§20 / wave law 3, the DEF-side wall).
        # Only `extern` lines were being compared, so a draft defining `s32 func_X(...)` against a
        # TU (or sibling draft) prototyping it `void func_X(...)` sailed past the checker and blew
        # up mid-build -- one wasted clean rebuild per occurrence, three of them in wave P alone.
        dm = re.search(r'^\s*([A-Za-z_][\w \t\*]*?)\s*\b%s\s*\(([^;{]*)\)\s*\{' % re.escape(e['fn']),
                       body, re.M)
        if dm:
            ds.append((e['fn'], typesig('%s %s(%s)' % (dm.group(1).strip(), e['fn'], dm.group(2)))))
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

# A TRAILING COMMENT MUST NOT DEFEAT THESE. Both patterns used to demand `;[ \t]*\n`, so
# `typedef struct { s16 vx, vy, vz, pad; } SVEC2;   /* 0x08 */` matched NEITHER the destination
# file's copy nor the draft's -- the TU's definition went unseen, the draft's duplicate was never
# stripped, and the build died on a C89 duplicate typedef. Agents comment their struct sizes as a
# matter of habit, so this was hitting the commonest possible spelling. (S52, cost 1 rebuild.)
_EOL = r'[ \t]*(?://[^\n]*|/\*(?:[^*]|\*(?!/))*\*/[ \t]*)?\n'
TYPEDEF_BLOCK = re.compile(
    r'^[ \t]*typedef\s+(?:struct|union|enum)?[^;{]*\{[^{}]*\}\s*(\w+)\s*;' + _EOL, re.M)
TYPEDEF_PLAIN = re.compile(r'^[ \t]*typedef\s+[\w\s\*]+?\s(\w+)\s*;' + _EOL, re.M)

def strip_dup_typedefs(body, already, suffix=''):
    """Make a draft's typedef names unique against the destination TU and the rest of the batch.

    Each draft is written to compile STANDALONE, so it carries its own `typedef struct {...}
    SVECTOR;`. Once one such function is banked, that typedef lives in the .c forever and every
    later draft defining its own collides -- a C89 duplicate-typedef error, not a byte miss.

    BODY-AWARE (S52). Two wrong strategies were tried before this one, each costing a rebuild:

      * STRIP every duplicate -- assumes the surviving definition sits ABOVE the insertion point.
        It need not: the destination file's `Rsc24` lived BELOW where a draft was substituted, so
        dropping the draft's copy left the name undefined there, gcc fell back to implicit-int,
        and the file's later declaration collided ("previous declaration of D_800A4640").
      * RENAME every duplicate -- wrong when several drafts share an IDENTICAL typedef, because
        giving each its own name makes their `extern <T> D_x[]` declarations mutually
        incompatible. I shipped that one and it broke three drafts at once.

    So decide by BODY, not by name:
      * identical definition already known -> STRIP this copy and reuse the existing name;
      * same name, DIFFERENT definition    -> RENAME this draft's copy (private to the draft, so
        it cannot change an emitted byte).
    `already` maps name -> normalized definition text. Returns (body, names_now_defined)."""
    # SINGLE PASS, NO RESCAN. An earlier version re-scanned after each edit; the rescan then found
    # the definition it had just RENAMED, saw the new name already in `defined` with identical
    # text, and STRIPPED it -- leaving references to a type that no longer existed
    # ("parse error before `*'"). Decide every typedef once, against a snapshot, then apply.
    defined, spans, renames = {}, [], {}
    hits = []
    for pat in (TYPEDEF_BLOCK, TYPEDEF_PLAIN):
        hits.extend(pat.finditer(body))
    for m in sorted(hits, key=lambda x: x.start()):
        name, text = m.group(1), ' '.join(m.group(0).split())
        known = already.get(name, defined.get(name))
        if known is None:
            defined[name] = text
        elif known == text:
            spans.append((m.start(), m.end()))          # exact duplicate, reuse the visible one
        else:
            new = '%s_%s' % (name, suffix)              # same name, different shape
            renames[name] = new
            defined[new] = text.replace(name, new)
    for s, e in sorted(spans, reverse=True):
        body = body[:s] + body[e:]
    for old, new in renames.items():
        body = re.sub(r'\b%s\b' % re.escape(old), new, body)
    return body, defined

def substitute(entries):
    """Replace each INCLUDE_ASM stub line with its draft body. Returns count."""
    stubs = {st.symbol: st for st in corpus.stubs('main').values()}
    byfile = collections.defaultdict(list)
    for e in entries:
        st = stubs.get(e['fn'])
        if st: byfile[st.path].append((st.addr, e['fn'], st.asm_dir, e['draft']))
    n = 0
    for path, items in byfile.items():
        t = open(path).read()
        # What the destination file already defines: name -> normalized definition text, so a
        # draft carrying an IDENTICAL typedef can reuse it (strip) while a draft carrying a
        # DIFFERENT shape under the same name gets renamed instead of silently colliding.
        # ...and WHERE it defines them. A typedef may only be reused by a draft substituted BELOW
        # it; the file's own copy is frequently further down the .c than the stub being replaced
        # (src/800.c defines `Rec14`/`Rsc24` hundreds of lines after the INCLUDE_ASM lines that
        # now want them). Reusing one from below yields `parse error before '*'` at the draft.
        # So the visible set is recomputed per draft against its own insertion offset.
        def defs_above(text, at):
            """Typedefs defined strictly ABOVE offset `at` in the CURRENT text.

            Recomputed per draft on purpose: `t` grows with every substitution, so offsets
            captured once go stale and understate where a definition really sits -- which would
            mark a below-the-draft typedef as reusable, the exact bug this guards against. It also
            naturally picks up typedefs contributed by drafts already substituted above."""
            out = {}
            for p in (TYPEDEF_BLOCK, TYPEDEF_PLAIN):
                for mm in p.finditer(text):
                    if mm.start() < at:
                        out.setdefault(mm.group(1), ' '.join(mm.group(0).split()))
            return out
        # PROCESS IN FILE ORDER (= address order), not slate order. strip_dup_typedefs keeps the
        # FIRST definition it sees and drops later duplicates, so if the drafts are walked in
        # slate order the surviving typedef can end up BELOW a draft that uses it -> "syntax error
        # before D_800A651C" at the earlier draft's line. Each stub is substituted at its own
        # position in the .c, so the walk must follow those positions. (S52, cost 2 rebuilds.)
        for _addr, fn, asmdir, draft in sorted(items):
            body = "\n".join(l for l in open(draft).read().splitlines()
                             if not l.strip().startswith('#include'))
            old = f'INCLUDE_ASM("{asmdir}", {fn});'
            if old not in t:
                continue
            at = t.index(old)
            body, _newly = strip_dup_typedefs(body, defs_above(t, at), suffix=fn.split('_')[-1])
            t = t[:at] + body + t[at + len(old):]
            n += 1
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
    # A BUILD failure (sha None) is not a byte mismatch, and bisecting it costs a full clean
    # rebuild per step to rediscover what the compiler/linker already printed. The named-culprit
    # path above only recognizes ONE error shape ("previous declaration of"); everything else --
    # undefined reference, redefinition, conflicting types, parse error -- used to fall straight
    # through to a silent bisect. So: always SHOW the error, and try to name the offending drafts
    # for the common shapes first. (S52: a 46-draft bisect started on an error the log never
    # printed. R32/R35 -- an instrument must report what it saw, not just that it failed.)
    if got is None:
        # SELECT the error lines; do NOT tail the stream. `err` is stderr+stdout concatenated, so
        # a blind tail shows only make's trailing "CC ..." progress chatter and hides the actual
        # message (S52: the first version of this printer did exactly that and reported nothing
        # useful). Grep both streams for the shapes that mean failure.
        pat = re.compile(r'error|Error|undefined|conflict|redefinition|parse error|No rule|\*\*\*'
                         r'|previous declaration|warning: .*implicit', re.I)
        hits = [l for l in (err.splitlines()) if pat.search(l)]
        print("\nBUILD FAILED (no binary produced). Error lines from the build:")
        for l in (hits[:40] or ["(no line matched the error patterns — showing stderr tail)"]):
            print("   ", l)
        if not hits:
            for l in [x for x in (r.stderr or '').splitlines() if x.strip()][-25:]:
                print("   ", l)
        for pat, label in ((r"undefined reference to `([^']+)'", "undefined reference"),
                           (r"redefinition of `([^']+)'", "redefinition"),
                           (r"conflicting types for `([^']+)'", "conflicting types")):
            syms = set(re.findall(pat, err))
            for s in syms:
                owners = [e['fn'] for e in kept
                          if re.search(rf"\b{re.escape(s)}\b", open(e['draft']).read())]
                print(f"  {label} `{s}' -> drafts referencing it: {owners or '(none in slate)'}")
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

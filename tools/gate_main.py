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
import argparse, collections, fcntl, functools, json, os, re, subprocess, sys
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

# A DECLARATOR KEYWORD IS NEVER THE SYMBOL (P31 S54). The old single regex took the FIRST
# identifier followed by '[' or '(', wherever it sat -- so a pointer-to-function declaration,
#     extern void (*D_801923D0[])(void *);
# reported its symbol as `void`, because `void (` matches first by POSITION. Every such
# declaration in a TU then "collided" with every other one under the name `void`: 192 phantom
# CONFLICTING-EXTERN failures on one overlay TU the first time pregate_check could see overlays.
# Project symbols are matched by NAME first, keywords are excluded from the generic branch, and
# the parenthesised declarator is read explicitly.
_NOT_A_SYMBOL = {
    'void', 'char', 'short', 'int', 'long', 'float', 'double', 'signed', 'unsigned',
    'const', 'volatile', 'struct', 'union', 'enum', 'static', 'extern', 'register', 'typedef',
    's8', 'u8', 's16', 'u16', 's32', 'u32', 's64', 'u64', 'f32', 'f64',
    # THE ASM-LABEL ALIAS (P31 S55, second instance of the §192 defect class). The project's own
    # §37/§124 idiom spells a renamed symbol `extern s32 gVecX __asm__("D_80126B5C");`, and the
    # generic branch below matched `__asm__` -- an identifier followed by '(' -- before ever
    # reaching the real one. Every aliased declaration then "conflicted" with every other under the
    # name `__asm__`: measured on wave Y's ov_SC02_017 slate, 1 byte-verified draft DROPPED and 2
    # phantom CONFLICTING-EXTERN failures, on an idiom this very session used to recover work.
    '__asm__', 'asm', '__volatile__', '__attribute__',
}


def sym_of(d):
    m = re.search(r'\b(D_[0-9A-Fa-f]{8}|func_[0-9A-Fa-f]{8})\s*(?:\[|\()', d)
    if m: return m.group(1)
    m = re.search(r'\b([A-Za-z_]\w*)\s*(?:\[|\()', d)
    if m and m.group(1) not in _NOT_A_SYMBOL: return m.group(1)
    m = re.search(r'\(\s*\*+\s*([A-Za-z_]\w*)', d)          # T (*NAME)(...) / T (*NAME[])(...)
    if m and m.group(1) not in _NOT_A_SYMBOL: return m.group(1)
    # `T NAME __asm__("LABEL")` -- the declared identifier is the one BEFORE the asm label, and the
    # label itself is the LINK name, not a C symbol (§37/§124).
    m = re.search(r'\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*__asm__\s*\(', d)
    if m and m.group(1) not in _NOT_A_SYMBOL: return m.group(1)
    m = re.search(r'\b(D_[0-9A-Fa-f]{8}|func_[0-9A-Fa-f]{8})\b', d)
    return m.group(1) if m else None

# The project's scalar typedefs. `short` and `s16` are THE SAME TYPE, so two drafts spelling one
# symbol both ways do not conflict -- but a textual comparison calls them different and drops a
# good draft (R39 over-refusal; wave O hit it with `extern short D_800B9A02`). Signedness is NOT
# normalized away: u16 vs s16 is a genuine conflict and must stay one.
def _common_h_aliases():
    """The project's OWN scalar typedefs, read from include/common.h rather than restated here (R33).

    `typedef s32 M2C_UNK;` makes `extern s32 D_x;` and `extern M2C_UNK D_x;` the SAME declaration,
    but a textual comparison calls them a CONFLICTING-EXTERN and refuses a byte-verified draft --
    measured on ov_SC03_028, where both spellings already coexist in a TU that compiles today
    (R39 over-refusal). Only aliases of a scalar we already canonicalize are folded in; anything
    else (struct typedefs) is deliberately left alone."""
    out, scalars = {}, {'s8', 'u8', 's16', 'u16', 's32', 'u32', 's64', 'u64', 'f32', 'f64'}
    try:
        txt = open(os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                                'include', 'common.h')).read()
    except OSError:
        return out
    for m in re.finditer(r'^\s*typedef\s+([A-Za-z_]\w*)\s+([A-Za-z_]\w*)\s*;', txt, re.M):
        base, name = m.group(1), m.group(2)
        if base in scalars and name not in scalars:
            out[name] = base
    return out


_ALIASES = {
    'char': 's8', 'signed char': 's8', 'unsigned char': 'u8',
    'short': 's16', 'signed short': 's16', 'short int': 's16',
    'unsigned short': 'u16', 'unsigned short int': 'u16',
    'int': 's32', 'signed int': 's32', 'long': 's32', 'long int': 's32', 'signed long': 's32',
    'unsigned': 'u32', 'unsigned int': 'u32', 'unsigned long': 'u32', 'float': 'f32',
}
_ALIASES.update(_common_h_aliases())      # M2C_UNK -> s32, M2C_UNK16 -> s16, ... (derived, not restated)


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

UNSPEC = '?'          # an UNSPECIFIED parameter list -- `void f();`, not `void f(void);`


def norm_sig(sig):
    """Normalize a `typesig` for COMPATIBILITY comparison, keeping the one distinction C89 makes.

    `extern void f();` declares an UNSPECIFIED parameter list, and C89 6.5.4.3 forms a composite
    type with any prototype whose parameters survive the default promotions -- gcc-2.7.2 accepts
    the pair, and this project's TUs are full of it (§37/§124, the no-prototype escape). But
    `extern void f(void);` declares EXACTLY ZERO parameters, and that against `f(s32)` is a hard
    error. Collapsing both to () -- as pregate_check did until P31 S54 -- makes the tool report 40
    phantom failures on one overlay TU that compiles today, while still missing nothing.

    So: unspecified -> UNSPEC (a wildcard for `sig_conflict`), explicit (void) -> ()."""
    ret, params = sig
    if isinstance(params, tuple):
        if params in ((), ('',)):
            params = UNSPEC
        elif params == ('void',):
            params = ()
    return (ret, params)


def sig_conflict(a, b):
    """True when two normalized signatures cannot both describe one symbol.

    Return types must agree (S53: even G3P* vs G4P* was rejected by gcc). Parameter lists conflict
    only when BOTH are specified and differ."""
    a, b = norm_sig(a), norm_sig(b)
    if a[0] != b[0]:
        return True
    pa, pb = a[1], b[1]
    if pa == UNSPEC or pb == UNSPEC:
        return False
    return pa != pb


def run(cmd, **kw):
    return subprocess.run(cmd, shell=True, capture_output=True, text=True, **kw)

def sha():
    r = run("sha1sum build/us/SLUS_007.26")
    return r.stdout.split()[0] if r.returncode == 0 and r.stdout else None

_STUBS_BY_BIN = {}


def _stubs_for(binary):
    """symbol -> Stub for ONE binary, memoized.

    WHY THIS EXISTS (P31 S54, R36/R33). `resolve_conflicts` and `substitute` both hardcoded
    `corpus.stubs('main')`, so every non-main entry resolved to no stub: `resolve_conflicts` compared
    it against the '<unknown>' pseudo-file and `substitute` skipped it silently. The visible symptom
    was `pregate_check` printing "checking 0 substituted file(s) ... clean" for an OVERLAY slate --
    a green light from a checker that had examined nothing, which is the exact R32 defect class this
    project keeps re-finding. Overlay slates are the majority of wave work (every wave since O), and
    4 of the 5 rejection classes measured in §181 are precisely what these two functions detect.

    The slate shape already carries the answer: gate_lane's records have a 'binary' field. Absent
    (every historical main slate), it defaults to 'main', so the main path is byte-identical."""
    b = binary or 'main'
    if b not in _STUBS_BY_BIN:
        _STUBS_BY_BIN[b] = {st.symbol: st for st in corpus.stubs(b).values()}
    return _STUBS_BY_BIN[b]


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
        st = _stubs_for(e.get('binary')).get(e['fn'])
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
        clash = [(s, seen[s], t) for s, t in ds if s in seen and sig_conflict(seen[s], t)]
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

FORWARD_TD = re.compile(r'^typedef\s+(?:struct|union|enum)\s+(\w+)\s+\1\s*;$')


def _norm_td(text):
    """Normalize a typedef definition for COMPARISON: strip comments, then collapse whitespace.

    WHY (P31 S53, R35). Two structurally identical typedefs must compare EQUAL so one can be reused
    (stripped) instead of renamed. Without comment-stripping the comparison is a documentation test:
    agents annotate every field with its address (`s32 unk04;  /* 0x80076248 */`) and the TU usually
    does not, so an identical layout gets renamed to `Slot16A_80037028` — and the draft's
    `extern Slot16A_80037028 D_80076240[];` then conflicts with the file's own declaration of that
    symbol. Cost: a byte-verified draft blocked, twice, on prose.
    """
    text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
    text = re.sub(r'//[^\n]*', ' ', text)
    return ' '.join(text.split())


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
        name, text = m.group(1), _norm_td(m.group(0))
        known = already.get(name, defined.get(name))
        if known is None:
            defined[name] = text
        elif known == text or FORWARD_TD.match(text):
            # exact duplicate, OR a FORWARD declaration (`typedef struct X X;`) whose full
            # definition the file already provides. A forward typedef is not a competing shape --
            # it is the same type, deliberately incomplete so the draft compiles standalone for
            # match_one. Renaming it (the old behaviour) turned two CORRECT pointer-only drafts
            # into `extern Owner4EE8_8002C8F4 *D_800A4EE8;`, which then contradicted the file's own
            # `extern Owner4EE8 *D_800A4EE8;` — a conflict manufactured entirely by this tool.
            # Stripping is safe because hoist_typedefs has already lifted the real definition above
            # every insertion point (P31 S53).
            spans.append((m.start(), m.end()))          # reuse the visible/hoisted definition
        else:
            new = '%s_%s' % (name, suffix)              # same name, different shape
            renames[name] = new
            defined[new] = text.replace(name, new)
    for s, e in sorted(spans, reverse=True):
        body = body[:s] + body[e:]
    for old, new in renames.items():
        body = re.sub(r'\b%s\b' % re.escape(old), new, body)
    return body, defined

IDENT_RE = re.compile(r'\b[A-Za-z_]\w*\b')


def hoist_typedefs(t, wanted):
    """Move the FILE's own definitions of `wanted` typedef names above the include block.

    WHY (P31 S53, cookbook §181 class 2). `strip_dup_typedefs` may only reuse a definition that is
    visible ABOVE the insertion point, because stripping a draft's copy when the survivor sits below
    leaves the name undefined there. Its fallback was to KEEP the draft's copy -- but two definitions
    of one typedef name is a C89 error wherever they sit, so both horns were wrong and SEVEN
    byte-verified wave-R drafts were parked on it.

    The third option is this one: hoist the file's own definition to the top. A typedef emits no
    code, so moving one is byte-neutral by construction -- and that claim is not taken on faith, it
    is checked by the clean rebuild every gate already runs (the SHA is the control).

    Renaming the draft's copy instead was considered and rejected: the draft's `extern <T> D_x[];`
    would then disagree with the file's declaration of the same symbol, trading a duplicate-typedef
    error for a conflicting-types error (the trap already recorded in strip_dup_typedefs' docstring).

    REFUSES rather than guesses when a definition's body depends on another type: the dependency is
    pulled into the hoist set too (in file order), and if a dependency cannot be located as a
    file-level typedef it is left alone and the name is simply not hoisted. Returns (text, hoisted).
    """
    anchor = 0
    for m in re.finditer(r'^#include[^\n]*\n', t, re.M):
        anchor = m.end()
    if not anchor:
        return t, []

    defs = {}                                   # name -> (start, end, text)
    for p in (TYPEDEF_BLOCK, TYPEDEF_PLAIN):
        for m in p.finditer(t):
            defs.setdefault(m.group(1), (m.start(), m.end(), m.group(0)))

    # dependency closure: a hoisted body may name another file-level typedef, which must precede it
    need, seen = list(wanted), set()
    while need:
        name = need.pop()
        if name in seen or name not in defs:
            continue
        seen.add(name)
        for ident in IDENT_RE.findall(defs[name][2]):
            if ident != name and ident in defs:
                need.append(ident)

    movable = sorted((defs[n] for n in seen if defs[n][0] > anchor), key=lambda d: d[0])
    if not movable:
        return t, []

    block = ''.join(d[2].rstrip('\n') + '\n' for d in movable)
    out = t
    for start, end, _txt in sorted(movable, key=lambda d: -d[0]):
        out = out[:start] + out[end:]           # remove from the bottom up so offsets hold
    return (out[:anchor] + '/* hoisted by gate_main so drafts above can reuse them (§181) */\n'
            + block + out[anchor:],
            [n for n in seen if defs[n][0] > anchor])


def substitute(entries, write=True, transform=None):
    """Replace each INCLUDE_ASM stub line with its draft body.

    write=False produces the substituted text WITHOUT touching the tree, which is what
    tools/pregate_check.py needs: every batch failure this project has hit is a textual property
    of the file that will be compiled, so it can be checked in ~2s instead of a 5-minute rebuild.
    Returns (count, {path: text}).

    Per-binary since P31 S54 (see `_stubs_for`): an entry's own 'binary' selects its stub map, and
    an entry whose symbol is in NO stub map is reported loudly instead of being dropped on the floor
    (R32 -- a silent skip here is what made pregate_check green on overlay slates).

    `transform(body, tu_path, binary) -> body` is an optional per-draft rewrite applied BEFORE the
    typedef strip. It exists because main and the overlays are banked by different drivers with
    different draft transforms: gate_main uses the hoist/strip logic below, while gate_lane ->
    gate_stage -> harvest_verify strips every typedef the target TU already provides
    (`cdecl.strip_provided_typedefs`). A checker that models the wrong driver reports failures the
    real gate would never see -- pregate_check passes the overlay transform for non-main entries."""
    byfile = collections.defaultdict(list)
    unresolved = []
    for e in entries:
        b = e.get('binary') or 'main'
        st = _stubs_for(b).get(e['fn'])
        if st: byfile[st.path].append((st.addr, e['fn'], st.asm_dir, e['draft'], b))
        else:   unresolved.append((b, e['fn']))
    if unresolved:
        print("  substitute: %d entr%s resolved to NO stub (not open in that binary?): %s"
              % (len(unresolved), 'y' if len(unresolved) == 1 else 'ies',
                 ', '.join('%s:%s' % u for u in unresolved[:8])))
    n, texts = 0, {}
    for path, items in byfile.items():
        t = open(path).read()
        # Hoist first, so `defs_above` can see the file's own copy for every draft below it.
        # Only names the incoming drafts actually define are candidates -- we never reorganize a
        # file for types nobody in this slate needs.
        want = set()
        for _addr, _fn, _asmdir, draft, _b in items:
            body_txt = open(draft).read()
            for p in (TYPEDEF_BLOCK, TYPEDEF_PLAIN):
                want |= {m.group(1) for m in p.finditer(body_txt)}
        if want:
            t, hoisted = hoist_typedefs(t, want)
            if hoisted:
                print(f"  hoisted {len(hoisted)} typedef(s) to the top of {path}: "
                      f"{', '.join(sorted(hoisted))}")
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
                        out.setdefault(mm.group(1), _norm_td(mm.group(0)))
            return out
        # PROCESS IN FILE ORDER (= address order), not slate order. strip_dup_typedefs keeps the
        # FIRST definition it sees and drops later duplicates, so if the drafts are walked in
        # slate order the surviving typedef can end up BELOW a draft that uses it -> "syntax error
        # before D_800A651C" at the earlier draft's line. Each stub is substituted at its own
        # position in the .c, so the walk must follow those positions. (S52, cost 2 rebuilds.)
        for _addr, fn, asmdir, draft, binary in sorted(items):
            body = "\n".join(l for l in open(draft).read().splitlines()
                             if not l.strip().startswith('#include'))
            if transform:
                body = transform(body, path, binary)
            old = f'INCLUDE_ASM("{asmdir}", {fn});'
            if old not in t:
                continue
            at = t.index(old)
            body, _newly = strip_dup_typedefs(body, defs_above(t, at), suffix=fn.split('_')[-1])
            t = t[:at] + body + t[at + len(old):]
            n += 1
        texts[path] = t
        if write:
            open(path, 'w').write(t)
    return n, texts

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

    # THE main GATE LOCK. gate_stage takes a per-binary flock, and that lock IS the entire safety
    # argument for gating overlays in parallel — but main never had one. Two gate_main runs both
    # substitute into the SAME src/800c.c and clean-rebuild the SAME build/us tree, interleaving
    # writes while each reads a hash the other produced. Observed P31 S58: a wave re-gate and the
    # live campaign's gate ran main concurrently for six minutes before a human spotted it.
    # Blocking, not LOCK_NB: the second run should WAIT and then do its work — a batch of verified
    # drafts is expensive to reproduce, so refusing it would be worse than queueing it.
    # R36's principle: assert it, do not remember it.
    _repo = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    os.makedirs(os.path.join(_repo, ".run/auto"), exist_ok=True)
    _lock_path = os.path.join(_repo, ".run/auto/gate.main.lock")
    _lock = open(_lock_path, "w")
    try:
        fcntl.flock(_lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except BlockingIOError:
        print("another gate_main holds .run/auto/gate.main.lock — WAITING for it "
              "(main cannot be gated by two processes at once)", flush=True)
        fcntl.flock(_lock, fcntl.LOCK_EX)
    _lock.write(f"{os.getpid()}\n"); _lock.flush()

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

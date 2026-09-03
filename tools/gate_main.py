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
import argparse
import hashlib
import time, collections, fcntl, functools, glob, json, os, re, subprocess, sys
sys.path.insert(0, 'tools')
import corpus
import draft_prechecks as DP

# stdout is BUFFERED when redirected to a file -- a long run then looks hung with an
# empty log (measured: 16 min of silence during a bisect). Always flush.
print = functools.partial(print, flush=True)

GOOD = '143dbb89f34491258bbc27810d0a12ec8b43a8dd'
TYPES = {'void','char','short','int','long','unsigned','signed','float','double','const',
         'volatile','s8','u8','s16','u16','s32','u32','f32','s64','u64','struct','union'}
_TAG_KW = {'struct', 'union', 'enum'}   # see typesig: a tag keyword is not a type this model can see
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
    # A TAG KEYWORD IS NOT A TYPE THIS MODEL CAN SEE (P31 S72). The filter keeps only tokens in
    # TYPES, which DISCARDS every typedef name -- so `Ent30D80 *` and `Rec14 *` both reduce to
    # '*', and the model has always been blind to what a pointer points at. But `struct` IS in
    # TYPES, so `struct Ent30D80 *` reduced to 'struct*' and "conflicted" with `Ent30D80 *`, its
    # own typedef. Measured: src/800.c declares func_80031988 BOTH ways and compiles today (gcc is
    # the arbiter and it agrees they are one type), yet this checker DROPPED the byte-verified
    # draft -- an R39 over-refusal, and one of the six that S71 then recorded as a "proven
    # gate-reject". Dropping the tag keywords loosens NOTHING the typedef path had not already
    # loosened: it makes the two spellings of one type compare equal, which is the whole point.
    params = tuple(_alias(' '.join(t for t in re.findall(r'[A-Za-z_]\w*|\*', p)
                                   if (t in TYPES and t not in _TAG_KW) or t == '*'))
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


def main_tus():
    """The files this tool may write or revert: the EXE's own TUs, i.e. TOP-LEVEL src/*.c only.

    `git checkout -- src/` was a blanket revert of every lane's in-flight work: measured P31 S58,
    a main bisect reverted 61 just-banked overlay functions (the reason ox_campaign commits
    overlay banks before its main batch). main's stubs live in top-level src/*.c and nowhere
    else, so that is all this tool is allowed to touch (S59)."""
    return sorted(glob.glob('src/*.c'))

_STUBS_BY_BIN = {}
_HDR_DEFS = {}      # destination .c -> typedefs its #includes provide (see header_defs)


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



def live_text(txt):
    """The part of a TU the compiler actually sees: drop every `#ifdef NON_MATCHING` branch.

    WHY (P31 S72/S73). `resolve_conflicts` and the COMPILE-conflict analysis both scan `extern`
    lines with no notion of the preprocessor, so a declaration parked in the DEAD half of an
    `#ifdef NON_MATCHING` / `#else` / `#endif` pair reads as a live constraint. It is not compiled
    and constrains nothing. Measured twice in one gate: `func_80018714` and `func_800377D8` each
    carry a stale `(void)` declaration in a dead branch while the LIVE definition takes a pointer /
    a u8, and both caused a byte-verified draft to be dropped or mis-blamed. R39: a refusal check
    that discards good work is worse than one that lets a failure through."""
    out, dead, depth = [], False, 0
    for ln in txt.split('\n'):
        st = ln.strip()
        if st.startswith('#ifdef NON_MATCHING'):
            dead, depth = True, 1; out.append(''); continue
        if dead and st.startswith('#else') and depth == 1:
            dead = False; out.append(''); continue
        if dead and st.startswith('#endif') and depth == 1:
            dead, depth = False, 0; out.append(''); continue
        out.append('' if dead else ln)
    return '\n'.join(out)

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
                for d in DECL.findall(live_text(open(path).read())):
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


HOIST_MARK = '/* hoisted by gate_main so drafts above can reuse them (§181) */\n'


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

    # IDEMPOTENCE. The block is inserted AT `anchor`, so anything hoisted previously still starts
    # AFTER `anchor` on the next call and would be hoisted again — removed and re-inserted with a
    # fresh marker line every time. That is not theoretical: the P31 S58 main probe emitted
    # "hoisted 2 typedef(s)" 150 TIMES across 38 minutes without ever reaching a verdict, and the
    # working tree at kill time held a duplicated marker comment. A repair that cannot recognise
    # its own prior work cannot converge.
    #
    # Everything between the marker and the end of the contiguous block that follows it is already
    # hoisted; exclude those definitions from consideration.
    hoisted_end = anchor
    mk = t.find(HOIST_MARK)
    if mk != -1:
        hoisted_end = max(anchor, mk + len(HOIST_MARK))
        for _n, (st, en, _tx) in defs.items():
            if mk <= st <= hoisted_end + 4:      # contiguous run directly under the marker
                hoisted_end = max(hoisted_end, en)

    movable = sorted((defs[n] for n in seen if defs[n][0] > hoisted_end), key=lambda d: d[0])
    if not movable:
        return t, []

    block = ''.join(d[2].rstrip('\n') + '\n' for d in movable)
    out = t
    for start, end, _txt in sorted(movable, key=lambda d: -d[0]):
        out = out[:start] + out[end:]           # remove from the bottom up so offsets hold
    # Reuse the EXISTING marker if there is one, so repeated runs never stack marker comments.
    mark = '' if HOIST_MARK in out else HOIST_MARK
    return (out[:anchor] + mark + block + out[anchor:],
            [n for n in seen if defs[n][0] > hoisted_end])


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
        # TYPEDEFS ARRIVE THROUGH `#include`, NOT ONLY FROM THE .c (P31 S72). `defs_above` scans
        # the destination .c alone, so a typedef the TU gets from a HEADER is invisible to the
        # stripper and every draft carrying its own copy dies with `redefinition of 'X'`. That was
        # latent until the src/800.c split moved 19 shared typedefs into src/800_shared.h, at
        # which point func_80031988's draft — byte-correct, and one of the eleven — failed to
        # compile for that reason alone. Header-provided definitions are seeded exactly like
        # in-file ones, so an IDENTICAL copy is stripped and a DIFFERENT shape is renamed.
        def header_defs(path):
            if path in _HDR_DEFS:
                return _HDR_DEFS[path]
            out, seen_h = {}, set()
            queue = [path]
            while queue:                       # follow quoted includes transitively
                cur = queue.pop()
                try:
                    txt = open(cur, errors='replace').read()
                except OSError:
                    continue
                if cur != path:
                    for p in (TYPEDEF_BLOCK, TYPEDEF_PLAIN):
                        for mm in p.finditer(txt):
                            out.setdefault(mm.group(1), _norm_td(mm.group(0)))
                for m in re.finditer(r'^\s*#\s*include\s+"([^"]+)"', txt, re.M):
                    for cand in (os.path.join(os.path.dirname(cur), m.group(1)),
                                 os.path.join('include', m.group(1)),
                                 os.path.join('src', m.group(1))):
                        if os.path.exists(cand) and cand not in seen_h:
                            seen_h.add(cand); queue.append(cand); break
            _HDR_DEFS[path] = out
            return out

        def defs_above(text, at):
            """Typedefs defined strictly ABOVE offset `at` in the CURRENT text.

            Recomputed per draft on purpose: `t` grows with every substitution, so offsets
            captured once go stale and understate where a definition really sits -- which would
            mark a below-the-draft typedef as reusable, the exact bug this guards against. It also
            naturally picks up typedefs contributed by drafts already substituted above."""
            out = dict(header_defs(path))
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
    # `-j`. `make build BINARY=main` without it is SINGLE-THREADED on a 32-core box; the
    # Makefile's own JOBS knob is parallelism ACROSS binaries, which a one-binary build never
    # reaches (memory `pass-j-to-every-build`, measured 6.1x elsewhere and byte-identical). A gate
    # is run hundreds of times a session, so this is the difference between a probe you take and a
    # probe you talk yourself out of.
    r = run(f"make build BINARY=main -j{os.cpu_count() or 8}")
    # A TOOL THAT REFUSES IS NOT A WARNING (P31 S75). `jtbl_rodata_pads.py` aborts via `sys.exit`
    # with a message carrying none of the words this gate's failure analysis looks for
    # (error/undefined/conflict/...), so a carve refusal surfaced as "only warnings" and the real
    # cause of a rejected bank was invisible in the log. Name it explicitly.
    _refusal = re.search(r'^(?:\S*(?:jtbl_rodata_pads|jtbl_carve|corpus|jr_isolate_all)\S*):.*$',
                         (r.stdout or '') + (r.stderr or ''), re.M)
    if _refusal:
        print(f"  [gate] A TOOL REFUSED during the build — this is the cause, not a warning:\n"
              f"         {_refusal.group(0).strip()[:300]}")
    if r.returncode != 0:
        # `make build BINARY=main` runs the SHA check itself, so rc!=0 does NOT mean "no
        # binary": a linked-but-MISMATCHED build also exits nonzero. Returning None here routed
        # every byte mismatch into the compile-failure analysis, whose conflict regex then
        # matched a WARNING the baseline prints on every build (`previous implicit declaration
        # of func_800143AC` — src/800.c calls it before its decl), so m04's chunks all died with
        # "COMPILE conflict ... drafts declaring it: []" on slates that compiled fine (S59).
        # The binary was deleted above, so its presence now proves the link ran: report the
        # real hash and let the caller see an honest mismatch.
        if os.path.exists("build/us/SLUS_007.26"):
            return sha(), r
        return None, r                      # build truly failed -> no hash, and never a pass
    return sha(), r

FAILDIR = '.run/gate_main_fail'
PROGRESS = '.run/gate_main_progress.json'


def _draft_fp(e):
    """Fingerprint the DRAFT a verdict was measured against (R56).

    A gate verdict is a measurement of ONE draft body. If that draft is re-generated between a
    killed run and its resume, the recorded PASS says nothing about the new bytes -- so the
    journal stores the content hash and a resume silently drops any entry whose draft moved."""
    try:
        return hashlib.sha256(open(e.get('draft', ''), 'rb').read()).hexdigest()[:16]
    except OSError:
        return ''


def _save_progress(slate_path, good, rejected, steps):
    """Write every proven verdict THE MOMENT IT EXISTS (P31 S75 checkpoint item 3).

    try_batch is stateless and the bisect loop held `good` only in memory, writing
    .run/gate_main_banked.json once at the very end. A 34-minute bisection that is killed --
    timeout, Ctrl-C, a supervisor -- therefore lost every match it had already PROVEN, and each
    of those proofs cost a full clean EXE rebuild (~2-4 min). The verdicts are the expensive
    artifact here, not the substitution: re-substituting a known-good set costs one rebuild,
    re-DISCOVERING it costs the whole bisection again.

    Written atomically (tmp + os.replace) because the thing this protects against is being killed,
    and a half-written journal is worse than none. R42 in the small: durable the moment it exists,
    not at a convenient stopping point."""
    os.makedirs(os.path.dirname(PROGRESS), exist_ok=True)
    tmp = PROGRESS + '.tmp'
    with open(tmp, 'w') as fh:
        json.dump({'slate': os.path.abspath(slate_path),
                   'ts': time.time(),
                   'steps': steps,
                   'good': [{'fn': e['fn'], 'draft': e.get('draft', ''), 'fp': _draft_fp(e)}
                            for e in good],
                   'rejected': rejected}, fh, indent=1)
    os.replace(tmp, PROGRESS)


def _load_progress(slate_path, kept):
    """Reuse verdicts a killed run already paid for. Returns (good_entries, rejected_fns).

    Three guards, each one a way this could silently lie:
      * the journal must belong to THIS slate (a stale one from another run is not evidence);
      * every entry is re-keyed against `kept` by fn, so a draft dropped by resolve_conflicts
        since the kill cannot sneak back in;
      * the draft's content hash must still match (R56 -- the verdict measured those bytes).
    A resumed `good` set is re-verified as one batch by the loop's final try_batch anyway, so a
    wrong reuse cannot bank anything: it can only cost one rebuild."""
    if not os.path.exists(PROGRESS):
        return [], []
    try:
        j = json.load(open(PROGRESS))
    except (ValueError, OSError):
        return [], []
    if j.get('slate') != os.path.abspath(slate_path):
        return [], []
    by_fn = {e['fn']: e for e in kept}
    good, stale = [], []
    for rec in j.get('good', []):
        e = by_fn.get(rec['fn'])
        if e is None:
            continue
        if rec.get('fp') and rec['fp'] != _draft_fp(e):
            stale.append(rec['fn']); continue
        good.append(e)
    if stale:
        print(f"  (resume: {len(stale)} recorded pass(es) DISCARDED — the draft changed since: "
              f"{', '.join(stale[:8])})")
    return good, [f for f in j.get('rejected', []) if f in by_fn]


def _preserve_and_localize(entries, got):
    """Snapshot the RED image + its map, then name the symbols that actually diverged.

    WHY THIS EXISTS (P31 S72). Every red verdict this gate has ever produced was two hashes and
    nothing else -- and the R40 baseline control that runs immediately after a failure REBUILDS
    THE TREE GREEN, overwriting `build/us/SLUS_007.26` and its map. The one artifact that could
    say WHERE the image moved was destroyed, every time, before anyone could look at it.

    That is not a cosmetic gap. S71 substituted 11 main drafts one at a time, saw 7 come back with
    a different hash, and recorded all 11 as "PROVEN gate-rejects". A hash cannot distinguish
    "your body is wrong" from "your body is perfect and the substitution changed a CALLER" -- the
    §376 shape, where the TU keeps a stale `extern void f(void*)` while the definition is
    `void f(s32)`, so every call site's argument codegen moves. Six of those eleven are that
    class, and this gate's own pre-check names them (see resolve_conflicts) -- but the four that
    reached a build were judged with no instrument that could tell the two apart.

    So: copy the image and the map aside FIRST, attribute per byte, and print the verdict. With a
    single-entry slate the verdict is the routing decision (body reject vs plumbing reject)."""
    try:
        import main_diff_locate as MDL
    except Exception as e:                                   # never let diagnostics sink a gate
        print(f"  (diff localization unavailable: {e})")
        return
    tag = entries[0]['fn'] if len(entries) == 1 else f"batch{len(entries)}"
    d = os.path.join(FAILDIR, f"{tag}_{(got or 'nobin')[:8]}")
    os.makedirs(d, exist_ok=True)
    for f in ('build/us/SLUS_007.26', 'build/us/SLUS_007.26.map'):
        if os.path.exists(f):
            run(f"cp {f} {d}/")
    built = os.path.join(d, 'SLUS_007.26')
    mp = os.path.join(d, 'SLUS_007.26.map')
    if not (os.path.exists(built) and os.path.exists(mp) and os.path.exists(MDL.REF)):
        print(f"  (red image preserved at {d}, but localization inputs are incomplete)")
        return
    try:
        sections, syms = MDL.parse_map(mp)
        per, ndiff, _sz = MDL.attribute(open(built, 'rb').read(), open(MDL.REF, 'rb').read(),
                                        sections, syms)
    except Exception as e:
        print(f"  (red image preserved at {d}; localization failed: {e})")
        return
    rows = sorted(per.values(), key=lambda x: -x['bytes'])
    print(f"  RED IMAGE PRESERVED -> {d}")
    print(f"  {ndiff} differing byte(s) across {len(rows)} symbol(s):")
    for e in rows[:12]:
        a = f"0x{e['first_addr']:08x}" if e['first_addr'] is not None else '?'
        print(f"      {e['bytes']:>6}  {a}  {e['symbol']}")
    if len(rows) > 12:
        print(f"      ... {len(rows)-12} more ({sum(x['bytes'] for x in rows[12:])} bytes)")
    if len(entries) == 1:
        fn = entries[0]['fn']
        verdict, msg = MDL.classify(per, fn, ndiff)
        print(f"  VERDICT {fn}: {verdict} — {msg}")

def assert_main_tus_clean():
    """Refuse to START if main's TUs carry uncommitted work this gate would destroy.

    CALLED ONCE, BEFORE ANY SUBSTITUTION — never inside try_batch. `try_batch` runs repeatedly
    during bisection, and its OWN first substitution makes the tree dirty, so a check placed there
    cannot distinguish the operator's unsaved work from the gate's own in-flight edit: it aborts the
    bisection on iteration two. (P31 S75 — I put it there first and did exactly that.) A guard must
    be able to tell the state it PROTECTS from the state it CREATES.

    What it protects against, measured twice the same session: the SaveLoadRoutine decompile (1,179
    ins, byte-identical) sat uncommitted in src/800_b.c while a gate ran; and a §265 verbatim body
    converted to a stub is UNCOMMITTED BY CONSTRUCTION, so the checkout restored the __asm__ block
    NEXT TO the substituted C — 9 jump tables instead of 5, jtbl_rodata_pads refused, and the gate
    REJECTED a byte-identical bank. A destructive step that cannot be undone must ASK (R42)."""
    dirty = run("git status --porcelain -- " + " ".join(main_tus())).stdout.strip()
    if dirty and not os.environ.get("GATE_MAIN_ALLOW_DIRTY"):
        sys.exit("gate_main: main's TUs have UNCOMMITTED changes and this gate will `git checkout`\n"
                 "them before substituting, which would DESTROY that work:\n\n" + dirty +
                 "\n\nCommit it (R42 — banked work is committed the moment it exists) or stash it.\n"
                 "Pass --allow-dirty / GATE_MAIN_ALLOW_DIRTY=1 only if you intend to discard it.")


def try_batch(entries):
    # (uncommitted-work guard: assert_main_tus_clean(), called once from main())
    run("git checkout -- " + " ".join(main_tus()))
    run("make extract BINARY=main")          # regenerate .s for the reverted stubs (hazard 2)
    substitute(entries)
    got, r = clean_build()
    ok = got == GOOD
    if not ok and got is not None and entries:
        _preserve_and_localize(entries, got)
    return ok, got, r

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('slate', nargs='?'); ap.add_argument('--apply', action='store_true')
    ap.add_argument('--no-bisect', action='store_true')
    ap.add_argument('--no-resume', action='store_true',
                    help='ignore .run/gate_main_progress.json and re-test every draft from '
                         'scratch (default is to reuse verdicts a killed run already paid for)')
    ap.add_argument('--allow-dirty', action='store_true',
                    help='proceed even though main TUs have uncommitted changes THIS GATE WILL '
                         'DESTROY (it git-checkouts them before substituting). Default is to refuse.')
    ap.add_argument('--assert-baseline', action='store_true',
                    help='no slate: clean-build the committed tree with NO draft substituted; '
                         'exit 0 green / 3 red. The lane runs this before spending tokens (S59).')
    a = ap.parse_args()
    if getattr(a, 'allow_dirty', False):
        os.environ["GATE_MAIN_ALLOW_DIRTY"] = "1"
    if not a.assert_baseline:
        assert_main_tus_clean()          # ONCE, before any substitution
    if not a.assert_baseline and not a.slate:
        ap.error('a slate file is required unless --assert-baseline')

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

    # REVERT MY OWN SUBSTITUTION IF I DIE. gate_main writes unverified draft bodies into main's
    # sources and only reverts them on paths it reaches deliberately. Killed mid-run — timeout,
    # Ctrl-C, a supervisor's kill — the substitution simply stays in src/, and the next lane's
    # R42 auto-commit ("commit a dirty tree rather than revert it") ADOPTS it as if it were banked
    # work. That is not hypothetical: P31 S58 committed 10 ungated bodies into src/800.c and
    # src/800c.c that way, main built to the wrong SHA for NINE HOURS, and R22 quietly ran 212/213
    # the whole time. R42 is right for a per-binary gate that leaves PROVEN banks uncommitted; it
    # is wrong for this tool, whose output is unverified by construction until the SHA matches.
    import atexit, signal as _signal
    _banked_ok = {'done': False}

    def _revert_if_unbanked():
        if _banked_ok['done']:
            return
        dirty = subprocess.run("git status --porcelain -- " + " ".join(main_tus()), shell=True,
                               capture_output=True, text=True).stdout.strip()
        if dirty:
            print("gate_main: aborting with an UNVERIFIED substitution in main's TUs — reverting "
                  "them (never passed the byte-gate, so no bank is lost; overlay files are NOT "
                  "touched — S59).", flush=True)
            subprocess.run("git checkout -- " + " ".join(main_tus()), shell=True)

    atexit.register(_revert_if_unbanked)
    for _sig in (_signal.SIGTERM, _signal.SIGINT, _signal.SIGHUP):
        _signal.signal(_sig, lambda *_a: sys.exit(130))

    if a.assert_baseline:
        # THE R40 CONTROL AS A FIRST-CLASS MODE (S59). From 14:57 to 18:43 on 2026-08-24 the
        # committed baseline built RED (an overlay-lane auto-commit adopted a mid-flight
        # substitution) and the main lane burned four 200-card draft rounds against it — every
        # verdict false. One clean rebuild before spending tokens is the cheapest insurance the
        # lane can buy, and it runs under the same lock as any gate.
        ok0, got0, _r0 = try_batch([])
        _banked_ok['done'] = True                    # nothing substituted; tree left clean
        if ok0:
            print(f"BASELINE GREEN — {got0} BYTE-IDENTICAL")
            sys.exit(0)
        print(f"*** BASELINE RED — HEAD builds to {got0}, want {GOOD}, with NO draft "
              f"substituted. Nothing can bank until the committed baseline is fixed "
              f"(find the adopting commit: git log -- 'src/*.c').")
        sys.exit(3)

    slate = json.load(open(a.slate))

    # A DRAFT THAT CONTAINS ITS OWN `INCLUDE_ASM` IS A NO-OP, AND A NO-OP PASSES FOR FREE

    # (P31 S71). Substituting it puts the stub straight back: nothing changes, the clean

    # build is trivially byte-identical, and the function is reported banked while its stub

    # is still in src/. Measured on func_8002B0B4, whose 'draft' is a documentation wrapper

    # ending in the INCLUDE_ASM line. Rare (5 of 2,749 stored drafts) but SILENT, so refuse

    # at slate load — before any mode, dry run included (R43).

    _noop = [e['fn'] for e in slate

             if os.path.exists(e.get('draft',''))

             and re.search(r'^\s*INCLUDE_ASM\(', open(e['draft'], errors='replace').read(), re.M)]

    if _noop:

        raise SystemExit('gate_main: REFUSED — %d draft(s) still contain their own '

                         'INCLUDE_ASM, so substituting them changes nothing and the build '

                         'passes for free: %s' % (len(_noop), ', '.join(_noop)))

    # THE SAME NO-OP, WEARING C's CLOTHES (P31 S76). A §265 verbatim body is the function's own
    # assembly in a file-scope `__asm__` string; `tools/asm_verbatim.py` writes them as `<fn>.c`
    # into the same draft directories as real drafts. Substituting one assembles the bytes it was
    # copied from, so match_one prints MATCH and this gate goes GREEN -- both truthfully -- while
    # nothing has been decompiled. S75 saw it once from an agent and concluded "no byte gate can"
    # catch it; that is true of the BYTE check and false of a slate-load refusal. S76 then did it
    # at scale: 9 functions converted from verbatim bodies to stubs *so they could be decompiled*,
    # then "banked" from stored drafts that were those same verbatim blocks. 9 of 9 MATCH, and
    # progress.py moved by exactly zero. Refuse at load, like the INCLUDE_ASM no-op above (R43).
    _verb = [e['fn'] for e in slate
             if os.path.exists(e.get('draft', ''))
             and DP.is_verbatim_asm_draft(open(e['draft'], errors='replace').read(), e['fn'])]
    if _verb:
        raise SystemExit("gate_main: REFUSED — %d draft(s) are the target's own assembly in a "
                         "file-scope __asm__ (a §265 verbatim body), not a decompile. They would "
                         "pass this gate for free and bank nothing: %s"
                         % (len(_verb), ', '.join(_verb)))

    kept, dropped = resolve_conflicts(slate)
    print(f"slate {len(slate)} -> {len(kept)} compatible, {len(dropped)} dropped for in-TU decl conflict")
    for d in dropped:
        print(f"  DROP {d['fn']}: {d['symbol']} clashes with {d.get('against','?')} "
              f"in {d.get('file','?')}  kept={d['kept']}  this={d['this']}")
    if dropped:
        print("  (dropped drafts are usually CORRECT -- recover with a cast-at-use: adopt the")
        print("   other declaration verbatim and adapt at the use site, e.g. (&D_x)[i].)")
        # A DROP IS A ROUTE, NOT A VERDICT (P31 S72). This list is the §376 pile: the draft's
        # definition disagrees with a forward declaration the TU already carries, which is a
        # PLUMBING problem with a named fix chain -- not evidence about the body. Printed-only,
        # it kept getting read as a rejection: S71 recorded six of these as "PROVEN gate-rejects,
        # §376 in its purest form -- do not re-slate", and they were never re-slated. Writing it
        # to disk with the chain spelled out makes the recovery the obvious next command instead
        # of a paragraph someone has to remember.
        json.dump(dropped, open('.run/gate_main_dropped.json', 'w'), indent=1)
        print(f"  -> .run/gate_main_dropped.json ({len(dropped)} to reconcile). The chain is:")
        print(f"       tools/fix_arity_callers.py --apply --any-proto --funcs "
              f"{','.join(d['fn'] for d in dropped)} \\\n"
              f"           --drafts <dir> --journal .run/<id>/arity.json")
        print(f"       tools/cast_self_callers.py --binary main --funcs <same> --drafts <dir> "
              f"--apply --journal .run/<id>/cast.json")
        print(f"       tools/gate_main.py <slate> --apply        # the byte-gate arbitrates")
    if not a.apply:
        print("\nDRY RUN. Re-run with --apply to substitute and clean-rebuild.")
        return

    ok, got, r = try_batch(kept)
    if ok:
        print(f"\nBANKED {len(kept)} main functions -- {got} BYTE-IDENTICAL")
        _banked_ok['done'] = True
        json.dump([e['fn'] for e in kept], open('.run/gate_main_banked.json', 'w'))
        return
    # A COMPILE error names its own culprit -- read it instead of bisecting. Bisection here costs
    # a FULL CLEAN REBUILD per step (~2-4 min), so it is worst-case hours; the compiler already
    # told us the symbol and line. (Measured the hard way: a 41-draft bisect ran 28+ min with no
    # output.) Only a byte MISMATCH with a clean compile genuinely needs bisection.
    err = (r.stderr or '') + (r.stdout or '')

    # R40 — EXONERATE THE INSTRUMENT BEFORE JUDGING THE DRAFTS (S59). From 14:57 to 18:43 on
    # 2026-08-24 the committed baseline built RED (an overlay-lane auto-commit, commit:2693, had
    # adopted a mid-flight substitution), and this gate judged four 200-card draft rounds against
    # it: 0 banked, ~50 clean rebuilds burned, every rejection a false verdict. One control
    # rebuild answers the only question that matters first: does HEAD, with NO draft substituted,
    # still build byte-identical? If not, nothing in this slate can bank, and bisecting would
    # only reject innocent drafts one by one until MAX_STEPS.
    base_ok, base_got, _rb = try_batch([])
    if not base_ok:
        print(f"\n*** BASELINE RED — HEAD builds to {base_got}, want {GOOD}, with NO draft "
              f"substituted. Every per-draft verdict from this tree would be FALSE; the slate "
              f"is untouched and reusable. Fix the committed baseline first "
              f"(find the adopting commit: git log -- 'src/*.c'). NOT bisecting.")
        _banked_ok['done'] = True       # the control substituted nothing; the tree is clean
        sys.exit(3)

    if got is None:
        # A COMPILE error names its own culprit — read it instead of bisecting (a bisect step is
        # a full clean rebuild). Two conditions gate this shortcut since S59:
        #   * ERROR-shaped lines only, never `warning:` forms. gcc 2.7.2 WARNS about an
        #     implicit-decl mismatch the baseline itself carries (src/800.c:479 calls
        #     func_800143AC before its decl on EVERY build), and matching the warning here blamed
        #     slates that never mentioned the symbol — every m04 chunk died with
        #     "COMPILE conflict on func_800143AC ... drafts declaring it: []".
        #   * a draft in THIS slate must actually name the symbol. An empty offender list means
        #     the conflict pre-exists in the TU or arose indirectly; "drop the drafts declaring
        #     it" is unactionable then, and the honest path is the error report + bisect below.
        # (The S58 case this shortcut was built for — a slate draft calling a symbol with no
        # prototype — still hits it: the draft names the symbol, so offenders is non-empty.)
        m = (re.search(r'^(.*?):(\d+): previous declaration of `([^\']+)\'', err, re.M)
             or re.search(r'^(.*?):(\d+): previous implicit declaration of `([^\']+)\'',
                          err, re.M)
             or re.search(r'^(.*?):(\d+): conflicting types for `([^\']+)\'', err, re.M))
        offenders = ([e['fn'] for e in kept
                      if re.search(rf"\b{re.escape(m.group(3))}\b", open(e['draft']).read())]
                     if m else [])
        if m and offenders:
            print(f"\nCOMPILE conflict on `{m.group(3)}' at {m.group(1)}:{m.group(2)} —"
                  f" NOT bisecting; drop or reconcile the drafts declaring it and re-run.")
            print("  drafts declaring it:", offenders)
            run("git checkout -- " + " ".join(main_tus()))
            return
        if m:
            print(f"\n(note: a decl conflict on `{m.group(3)}' at {m.group(1)}:{m.group(2)} is "
                  f"in the build log but NO draft in this slate names it — pre-existing in the "
                  f"TU; falling through to the error report + bisect.)")
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
        run("git checkout -- " + " ".join(main_tus())); return
    # THE OLD LOOP COULD NOT TERMINATE. On a failing multi-element chunk it did `lo = head + lo`,
    # restoring `lo` to exactly its previous value — so the next iteration recomputed the SAME
    # `head`, failed identically, and restored again. Forever. Combined with a non-idempotent
    # typedef hoist that re-ran each step, the P31 S58 main probe spun 150 times over 38 minutes on
    # 8 drafts and never produced a verdict.
    #
    # This is an explicit-stack bisect: a failing chunk is SPLIT and both halves pushed, so the
    # work strictly decreases and termination is structural. MAX_STEPS is a backstop, not the
    # mechanism — if it ever trips, something is wrong that bisection cannot fix, and it says so
    # loudly instead of burning clean rebuilds in silence.
    MAX_STEPS = int(os.environ.get('GATE_MAIN_MAX_STEPS', '24'))
    good, rejected, steps = [], [], 0
    # RESUME WHAT A KILLED RUN ALREADY PROVED. Each entry in `good` cost a full clean EXE rebuild;
    # before the journal, a kill threw all of them away and the next run rediscovered them from
    # scratch. `good` is re-verified as a batch by the final try_batch below, so resuming can
    # never bank something unproven -- at worst it wastes one rebuild.
    if not a.no_resume:
        good, rejected = _load_progress(a.slate, kept)
        if good or rejected:
            print(f"  RESUMING from {PROGRESS}: {len(good)} already proven, "
                  f"{len(rejected)} already rejected — not re-testing them "
                  f"(--no-resume to start clean).")
    _done = {e['fn'] for e in good} | set(rejected)
    stack = [[e for e in kept if e['fn'] not in _done]] if _done else [kept]
    if _done and not stack[0]:
        stack = []
    while stack:
        if steps >= MAX_STEPS:
            print(f"\n*** BISECT ABORTED after {MAX_STEPS} rebuilds with {len(stack)} chunk(s) "
                  f"unresolved. Each step is a full clean EXE rebuild, so this is a bounded "
                  f"failure, not progress. Banking the {len(good)} proven so far and stopping; "
                  f"raise GATE_MAIN_MAX_STEPS only if you know why it is not converging.")
            break
        chunk = stack.pop()
        steps += 1
        ok, got, _ = try_batch(good + chunk)
        if ok:
            good += chunk
            _save_progress(a.slate, good, rejected, steps)   # durable the moment it is proven
        elif len(chunk) == 1:
            rejected.append(chunk[0]['fn'])
            print(f"  reject {chunk[0]['fn']}")
            _save_progress(a.slate, good, rejected, steps)
        else:
            mid = len(chunk) // 2
            stack.append(chunk[mid:])
            stack.append(chunk[:mid])
    ok, got, _ = try_batch(good)
    _banked_ok['done'] = True
    # COUNT THE BANKS FROM THE SOURCE, NOT FROM THE SLATE (R32/R53, P31 S71).
    # `len(good)` is "what we decided to keep", which is NOT "what actually got substituted". A
    # draft whose stub pattern does not match is a SILENT NO-OP: nothing changes, the build is
    # trivially identical, the batch passes, and the function is reported banked while its
    # INCLUDE_ASM is still sitting in src/. Measured here: the bisect said "BANKED 5 of 6" and
    # `func_8002B0B4`'s stub was still in src/800.c — 4 real banks. The stub's ABSENCE is the bank
    # oracle everywhere else in this project; use it here too.
    still = []
    for e in good:
        pat = 'INCLUDE_ASM("asm/nonmatchings/%s", %s)' % ('', e['fn'])
        hit = subprocess.run(['grep', '-rlF', ', %s);' % e['fn'], '--include=*.c', 'src/'],
                             capture_output=True, text=True)
        for f in hit.stdout.split():
            for ln in open(f, errors='replace'):
                if 'INCLUDE_ASM' in ln and (', %s);' % e['fn']) in ln:
                    still.append((e['fn'], f)); break
    applied = [e['fn'] for e in good if e['fn'] not in {f for f, _ in still}]
    print(f"\nBANKED {len(applied)} of {len(kept)} after bisection in {steps} rebuild(s) -- {got}"
          f"{' BYTE-IDENTICAL' if ok else ' *** STILL MISMATCHED ***'}")
    if rejected:
        print(f"  rejected: {rejected}")
    if still:
        print(f"  *** {len(still)} draft(s) in the accepted set NEVER APPLIED (stub still in src) — "
              f"a no-op substitution passes the build for free and is NOT a bank:")
        for fn, f in still:
            print(f"      {fn}  ({f})")
    json.dump(applied, open('.run/gate_main_banked.json', 'w'))
    # The run CONCLUDED, so the journal has served its purpose. Leaving it would make the next
    # run over a re-drafted slate resume from verdicts about bodies that no longer exist -- the
    # fingerprint check would catch it, but a stale file that is always ignored teaches the
    # operator to ignore the mechanism. Keep it only when the bisect was cut short, which is
    # exactly when a resume is worth something.
    if steps < MAX_STEPS and not stack:
        for _f in (PROGRESS, PROGRESS + '.tmp'):
            if os.path.exists(_f):
                os.remove(_f)

if __name__ == '__main__':
    main()

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

# gcc-2.7.2 built-ins: a conflicting redeclaration of one of these is a WARNING (verified against
# the pinned cc1, P31 S54), so it must not block a rebuild. Anything else is a hard error.
_BUILTINS = {
    'memcpy', 'memset', 'memcmp', 'strcpy', 'strncpy', 'strcmp', 'strncmp', 'strlen', 'strcat',
    'strncat', 'strchr', 'strrchr', 'abs', 'labs', 'fabs', 'alloca', 'sqrt', 'sin', 'cos',
    'printf', 'sprintf', 'fprintf', 'putchar', 'puts', 'exit',
}

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


STRUCT_EXTERN = re.compile(
    r'^[ \t]*extern\s+(?:const\s+|volatile\s+)*(struct|union)\s*\{([^{}]*)\}\s*(\**)\s*(\w+)\s*(?:\[[^\]]*\])?\s*;',
    re.M | re.S)


def _norm_sig(sig):
    """Delegates to the single normalization oracle in gate_main (R33).

    It used to collapse `void f()` AND `void f(void)` to the same (), which is right about the
    first (C89's unspecified parameter list, compatible with any prototype) and wrong about the
    second (exactly zero parameters, incompatible with `f(s32)`). Since this tool could only ever
    see main's TUs, the difference never showed; the first overlay slate it ran on produced 40
    phantom CONFLICTING-EXTERN failures against a file that compiles today. Use `gm.sig_conflict`
    for comparisons -- `!=` on these tuples is not the compatibility relation."""
    return gm.norm_sig(sig)


def _typedefs(text, depth=None):
    """name -> [(offset, normalized_body)] for every FILE-SCOPE typedef the text defines.

    BLOCK SCOPE IS A SCOPE (P31 S54, R39). Two functions may each declare their own
    `typedef struct {...} Ent_801DFBF8;` INSIDE their bodies -- that is legal C and the project's
    drafts do it constantly (it is how a draft stays self-contained for match_one without touching
    the TU's namespace). Counting those as definitions produced a DUPLICATE-TYPEDEF FAIL against
    a slate whose drafts were each independently byte-verified. `depth` is the brace-depth map the
    caller already computed; passing it restricts the scan to depth 0."""
    out = {}
    for pat in (gm.TYPEDEF_BLOCK, gm.TYPEDEF_PLAIN):
        for m in pat.finditer(text):
            if depth is not None and depth[m.start()]:
                continue
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
    # SCAN THE MASKED TEXT, NEVER THE RAW TEXT (P31 S53, R35). This originally read
    # `_typedefs(text)`, so a typedef quoted in a COMMENT counted as a definition: src/800.c's own
    # bank note at line 2409 quotes `typedef struct { s32 a; s32 b[4]; } OtBlk_80016450;` inside a
    # /* */ block, and the tool reported DUPLICATE-TYPEDEF against a file that has compiled
    # byte-identically for weeks. Seven of nine FAILs on a real wave-R slate were comment-borne.
    # The masking oracle was already computed one line above and simply was not used here; because
    # _mask is length-preserving, every reported offset stays valid.
    tds = _typedefs(masked, depth)

    # 3. duplicate typedef -- ANY redefinition, identical body or not.
    # C89 has no "compatible redefinition" allowance for typedefs: `typedef struct {...} T;` twice
    # is an error even when the two are character-identical. My first version only flagged
    # DIFFERING bodies and therefore missed the very case this tool was built to catch -- a draft
    # whose typedef was renamed to match the TU's, giving two identical definitions of
    # `OtBlk_80016450`, which the compiler rejected on the next rebuild. Measured, not reasoned.
    for name, defs in tds.items():
        if len(defs) > 1:
            same = len({b for _, b in defs}) == 1
            findings.append(('FAIL', 'DUPLICATE-TYPEDEF',
                             f'{path}: `{name}` defined {len(defs)}x at offsets '
                             f'{[o for o, _ in defs]} ({"identical bodies -- still illegal in C89"
                                                        if same else "DIFFERENT bodies"})'))

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
    # BRACE-BODIED EXTERNS FIRST (P31 S53). gm.DECL is single-line, so a draft declaring
    #     extern struct { u8 pad[0x34]; s32 (*field_0x34)(s32); } *D_80072780;
    # was invisible to this check while a sibling declared the same symbol `void *` — the clash
    # surfaced only as a compile error, one rebuild later (§183.5). Bodies are flat here (no nested
    # braces), and the normalized body is part of the signature so two IDENTICAL struct declarations
    # do not read as a conflict.
    for m in STRUCT_EXTERN.finditer(masked):
        if depth[m.start()]:
            continue
        body = ' '.join(m.group(2).split())
        sig = (f'{m.group(1)}{{{body}}}{m.group(3)}', '')
        decls.setdefault(m.group(4), (m.start(), sig))
    for m in gm.DECL.finditer(text):
        if depth[m.start()]:            # block-scope decl: private to its function
            continue
        d = m.group(1)
        s = gm.sym_of(d)
        if not s:
            continue
        sig = _norm_sig(gm.typesig(d))
        if s in decls and gm.sig_conflict(decls[s][1], sig):
            # A BUILT-IN IS A WARNING, NOT AN ERROR -- measured, not assumed (P31 S54). Every
            # overlay TU in the fleet declares memcpy twice (`(void*, const void*, u32)` near the
            # top, `(void*, void*, s32)` further down) and every one of them COMPILES TODAY. Probed
            # against the pinned cc1: two conflicting declarations of `memcpy` give
            # "warning: conflicting types for built-in function `memcpy'" and exit 0, while the same
            # pair on a non-builtin name gives "conflicting types for `myfun'". Reporting these as
            # FAIL sent the reconcile lane hunting a defect the compiler does not have (R39).
            findings.append(('WARN' if s in _BUILTINS else 'FAIL', 'CONFLICTING-EXTERN',
                             f'{path}: `{s}` declared {decls[s][1]} at offset {decls[s][0]} and '
                             f'{sig} at offset {m.start()}'))
        else:
            decls.setdefault(s, (m.start(), sig))

    # 5. definition vs a visible prototype
    for name, (off, sig) in _func_defs(masked).items():   # masked, not raw — see the note above
        sig = _norm_sig(sig)
        if name in decls and gm.sig_conflict(decls[name][1], sig):
            # SEVERITY CALIBRATED AGAINST THE COMPILER, not against C89 pedantry. Measured on the
            # wave-P slate that built BYTE-IDENTICAL: gcc-2.7.2 accepted `void f(void*,s32)` vs a
            # `void f(s8*,s32)` definition, and even `G3P *f(...)` vs `G4P *f(...)`. What it
            # REJECTED was func_8001ABBC declared `void` and defined `s32` -- a void/non-void
            # return split. So that is the only FAIL; everything else is a WARN worth reading but
            # not worth blocking a rebuild over (R39: an over-refusal costs verified-correct work).
            # RECALIBRATED (P31 S53). The rule was "only a void/non-void split is fatal", measured on
            # the wave-P slate. S53 refuted the generalization: `func_80027F4C` DEFINED `G4P *` under
            # a visible `G3P *` declaration -- both non-void -- and gcc-2.7.2 REJECTED it
            # ("previous declaration of func_80027F4C", src/800.c:9225), costing a rebuild after this
            # tool had reported only a WARN. So ANY return-type disagreement is a FAIL; parameter
            # disagreements stay a WARN, which is still the calibration the wave-P bytes support.
            d_ret, m_ret = decls[name][1][0], sig[0]
            voidness = d_ret != m_ret
            findings.append(('FAIL' if voidness else 'WARN', 'DEF-VS-DECL',
                             f'{path}: `{name}` DEFINED {sig} at offset {off} but DECLARED '
                             f'{decls[name][1]} at offset {decls[name][0]} — the DEF-side wall; '
                             f'adopt the declaration and cast at the use site (§176d)'))
    return findings


def _typedef_use_before_def(text):
    defs = {}
    for st in cdecl.split_statements(text):
        if not re.match(r'\s*typedef\b', st.text):
            continue
        try:
            ds = cdecl.parse(st.text)
        except Exception:                      # noqa: BLE001 - a parse miss must not sink the check
            continue
        for d in ds:
            if getattr(d, 'storage', None) == 'typedef' and d.name and d.name not in defs:
                defs[d.name] = st.start
    # Search for the first use in a COMMENT-BLANKED copy, offsets preserved. The first draft of
    # this check searched the raw text and flagged a typedef named in its own explanatory comment
    # (R39 negative control: 1 false positive on md_MAIN_034 AFTER it banked). A checker that
    # refuses a good slate over prose is worse than no checker -- it discards work silently.
    blanked = _blank_comments(text)
    bad = []
    for name, pos in sorted(defs.items(), key=lambda kv: kv[1]):
        m = re.search(r'\b%s\b' % re.escape(name), blanked)
        if m and m.start() < pos:
            bad.append((name, m.start(), pos))
    return bad


def _blank_comments(text):
    """Replace /*...*/ and //... with spaces, preserving every byte offset."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        if text.startswith('/*', i):
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != '\n':
                    out[k] = ' '
            i = j
        elif text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = ' '
            i = j
        else:
            i += 1
    return ''.join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('slate')
    ap.add_argument('--quiet', action='store_true')
    a = ap.parse_args()

    slate = json.load(open(a.slate))
    kept, dropped = gm.resolve_conflicts(slate)

    # MODEL THE DRIVER THAT WILL ACTUALLY BANK THIS SLATE (P31 S54). main goes through gate_main's
    # hoist/strip; an overlay goes gate_lane -> gate_stage -> harvest_verify, which strips every
    # typedef its target TU already provides. Without this, the first overlay slates this tool could
    # see reported DUPLICATE-TYPEDEF for exactly the duplicates the real gate removes.
    def _driver_transform(body, tu_path, binary):
        if binary == 'main':
            return body
        return cdecl.strip_provided_typedefs(body, cdecl.typedef_names(tu_path))

    _n, texts = gm.substitute(kept, write=False, transform=_driver_transform)

    # ---- §203: A DEDUPED TYPEDEF MUST PRECEDE EVERY SPLICE POINT (P31 S56).
    # The transform above is faithful to the driver, and that is exactly the hazard: when two
    # slate-mates share a type, harvest_verify strips the duplicate from BOTH drafts, and the one
    # surviving definition sits wherever its owner splices. If the OTHER function is earlier in
    # ADDRESS order, its externs reference a type the file has not defined yet, and the whole batch
    # loses that draft to `parse error before '<symbol>'` -- a PLUMBING failure that reads like a
    # codegen residual. Measured: wave Z's md_MAIN_034 group banked 6 of 7 exactly this way; the
    # drop cost a gate cycle, three oracles and a wrong first fix to diagnose (cookbook §203).
    # Cheap to detect here, because we already hold the post-transform text.
    order_defects = []
    for _tu, _text in (texts.items() if isinstance(texts, dict) else texts):
        for name, use_at, def_at in _typedef_use_before_def(_text):
            line = _text.count('\n', 0, use_at) + 1
            dline = _text.count('\n', 0, def_at) + 1
            order_defects.append((_tu, name, line, dline))
    for tu, name, uline, dline in order_defects:
        print(f'[DROP-RISK] §203 USE-BEFORE-TYPEDEF: {tu}: `{name}` is used at line {uline} but '
              f'defined at line {dline}. Two slate-mates share this type and the earlier-addressed '
              f'one lost its copy to strip_provided_typedefs. FIX: hoist the typedef to the top of '
              f'the TU (above every splice point); do NOT rename it in one draft -- that gives one '
              f'symbol two types and the failure just moves.')

    # R32 COVERAGE ASSERTION (P31 S54). Until `gate_main` learned per-binary stub maps, an OVERLAY
    # slate resolved to zero stubs and this tool printed "checking 0 substituted file(s) ... clean"
    # -- a green light from a checker that had examined nothing, on exactly the slates (overlay
    # waves) that carry most of the work. A checker that checked nothing must never read as a pass.
    if kept and not texts:
        print(f'REFUSING: {len(kept)} kept draft(s) but 0 substituted files — every entry resolved '
              f'to no stub. Does each slate record carry its "binary"? Is the binary extracted '
              f'(make extract BINARY=...)? This is not a clean result.')
        sys.exit(2)

    findings = []
    for path, text in sorted(texts.items()):
        findings += check_text(path, text)

    fails = [f for f in findings if f[0] == 'FAIL']
    if not a.quiet:
        print(f'slate {len(slate)} -> {len(kept)} after resolve_conflicts '
              f'({len(dropped)} dropped); checking {len(texts)} substituted file(s)')
        # A DROP IS THE HEADLINE, NOT A FOOTNOTE (P31 S54). The drop reasons were computed and
        # thrown away, so a slate that lost EVERY draft to declaration conflicts still printed
        # "clean — the batch is worth a rebuild". They are the §183 playbook's actual worklist.
        for d in dropped:
            print(f'  [DROP] {d["fn"]}: `{d["symbol"]}` clashes with {d["against"]} in '
                  f'{d["file"]} — kept {d["kept"]} vs this {d["this"]}')
        for sev, code, msg in findings:
            print(f'  [{sev}] {code}: {msg}')
        if not findings and not dropped:
            print('  clean — no textual defect found; the batch is worth a rebuild')
        elif not findings:
            print(f'  no textual defect in what SURVIVED, but {len(dropped)} draft(s) were dropped '
                  f'above — reconcile those before gating (they are unbanked work, not noise)')
        elif not fails:
            print(f'  {len(findings)} warning(s), no hard failure — worth a rebuild')
        else:
            print(f'\n{len(fails)} FAILURE(S) — fix these BEFORE spending a clean rebuild.')
    # exit 1 also when the slate was emptied: 0 kept is not a pass, it is total refusal.
    sys.exit(1 if (fails or (slate and not kept)) else 0)


if __name__ == '__main__':
    main()

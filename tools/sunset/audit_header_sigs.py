#!/usr/bin/env python3
"""audit_header_sigs.py — find `src/shared/*.h` declarations that contradict the banked DEFINITION
(Phase 29 T67, cookbook §112).

WHY THIS EXISTS
---------------
A `DEFINE_func_*()` macro forward-declares the functions its body calls. That declaration is visible
in EVERY overlay that instantiates the macro — so when it disagrees with the function's byte-true
definition, the whole family becomes untemplatable and the failure wears a compiler wall's clothes:

    engine_core.h : void func_8014D610(s32 a0, void *a1, void *a2)
    byte truth    : s32  func_8014D610(s32 p1, s32 p2, u16 *p3)
    -> `conflicting types`, x137 members, booked as a compile failure

Three of these were found ONE AT A TIME in Phase 29 (func_80156044 int-vs-void, func_8016163C
void-vs-s32, func_8014D610 both axes). Each was worth ~137 members once corrected, and each cost a
diagnose/fix/re-sweep cycle to find. This audits all of them in one pass instead.

WHAT IS AND IS NOT A DEFECT
---------------------------
Per-overlay byte-true signatures legitimately DIFFER under the engine's loose typing (§16) — a
defining TU owns its own declarations (T49). So a header decl disagreeing with ONE overlay's
definition proves nothing. What this reports is the header decl compared against the definitions that
actually exist, with the disagreement CLASSIFIED and the §85 return-axis precondition measured, so a
human decides which to correct.

CORRECTING A HEADER DECL IS FLEET-SHARED BLAST RADIUS (§61/§63): R22 is mandatory, and the proven
discipline is two steps — the header change ALONE must rebuild 140/140 byte-identical, and only then
the sweep (T48/T63/T64).

Usage:
    tools/audit_header_sigs.py                 # rank by unblock value (live stubs)
    tools/audit_header_sigs.py --all           # every disagreement, not just the ranked head
    tools/audit_header_sigs.py --json out.json
"""
import argparse
import collections
import glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl                                                    # noqa: E402
from family_remap import _def_head_at                           # noqa: E402  (the §110 predicate)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HEADERS = ("src/shared/engine_core.h", "src/shared/engine_types.h")
FN_RE = re.compile(r'\bfunc_[0-9A-Fa-f]{8}\b')
DECL_RE = re.compile(r'extern\s+([A-Za-z_][\w \*]*?)\s*(func_[0-9A-Fa-f]{8})\s*\(([^)]*)\)\s*;')


def macro_owners():
    """{fn: {DEFINE_func_M, ...}} — which macro bodies declare each function.

    THE DECL IS ONLY VISIBLE WHERE ITS MACRO IS INSTANTIATED (Phase 29 T69). This is the fact that
    makes the "other in-scope decls" precondition tractable. A `DEFINE_func_M()` macro body contains
    `extern <sig> func_X(...);`, so correcting that decl can only collide inside a TU that BOTH
    instantiates `DEFINE_func_M()` AND carries its own incompatible declaration of func_X.

    Without this, the precondition compares against every decl in the corpus and blocks everything:
    `func_80161774` has 1,063 TUs carrying the old spelling, none of which instantiate its macro —
    and correcting it gated 140/140 and banked 137 members. Measuring the intersection instead of the
    population is the whole difference between a usable gate and a useless one."""
    owners = collections.defaultdict(set)
    for h in HEADERS:
        p = os.path.join(REPO, h)
        if not os.path.exists(p):
            continue
        cur = None
        for ln in open(p):
            m = re.match(r'\s*#define\s+(DEFINE_func_[0-9A-Fa-f]+)\s*\(', ln)
            if m:
                cur = m.group(1)
            elif cur and not ln.rstrip().endswith("\\"):
                d = DECL_RE.search(ln)
                if d:
                    owners[d.group(2)].add(cur)
                cur = None
                continue
            if cur:
                d = DECL_RE.search(ln)
                if d:
                    owners[d.group(2)].add(cur)
    return owners


def called_in_headers():
    """{fn} — functions the shared-header macro bodies actually CALL.

    THE ARITY PRECONDITION ONLY APPLIES TO A CALL (Phase 29 T72, cookbook §113). It exists because
    the macro's own call site passes the header's arity, so correcting a `(void)` decl for a 1-param
    definition breaks it. But a macro that only takes the ADDRESS of a function has no call site and
    no arity constraint — the FULL retype is available. `func_80144B14` was blocked on that reasoning
    and its macro does `*(s32 *)((s32)a0 + 0xDC) = (s32)&func_80144B14;`. Correcting it fully gated
    140/140 and banked 137 members.

    Declarations are stripped first: `extern void func_X(void);` is not a call, and a scan that
    counts it as one classifies EVERY declared function as called (measured — it did)."""
    called = set()
    for h in HEADERS:
        p = os.path.join(REPO, h)
        if not os.path.exists(p):
            continue
        uses = re.sub(r'extern\b[^;]*;', ' ', open(p).read())
        for m in re.finditer(r'(?<![&\w])(func_[0-9A-Fa-f]{8})\s*\(', uses):
            called.add(m.group(1))
    return called


def header_decls():
    """{fn: [(sig_text, header, lineno)]} — every extern decl of a func_ in the shared headers.

    ALL occurrences, not the first: a function can be declared by several DEFINE_ macros, and they
    are allowed to disagree with each other (that is itself worth seeing)."""
    out = collections.defaultdict(list)
    for h in HEADERS:
        p = os.path.join(REPO, h)
        if not os.path.exists(p):
            continue
        text = open(p).read()
        for m in DECL_RE.finditer(text):
            ret, fn, params = m.group(1).strip(), m.group(2), " ".join(m.group(3).split())
            line = text.count("\n", 0, m.start()) + 1
            out[fn].append((f"{ret} {fn}({params})", h, line))
    return out


def scan_corpus(wanted):
    """One pass over src/**/*.c returning ({fn: [defs]}, {fn: [decls]}).

    DEFINITIONS decide the byte truth. DECLARATIONS are the second precondition (below): a header
    correction is only safe when nothing ELSE in scope disagrees.

    A definition head is decided by §110's `_def_head_at` (what follows the parameter list), not by
    "the line ends in `;`" — the test that let a declaration sharing a line with a definition be
    mistaken for one."""
    defs = collections.defaultdict(list)
    decls = collections.defaultdict(list)      # fn -> [(sig, path, line, {macros this TU uses})]
    for path in glob.glob(os.path.join(REPO, "src/**/*.c"), recursive=True):
        try:
            text = open(path, errors="replace").read()
        except OSError:
            continue
        if not FN_RE.search(text):
            continue
        rel = os.path.relpath(path, REPO)
        used = set(re.findall(r'\b(DEFINE_func_[0-9A-Fa-f]+)\s*\(', text))
        for i, ln in enumerate(text.split("\n"), 1):
            for m in FN_RE.finditer(ln):
                fn = m.group(0)
                if fn not in wanted:
                    continue
                par = ln.find("(", m.end())
                if par < 0:
                    continue
                pre_tail = ln[:m.start()].rsplit(";", 1)[-1]
                if not re.fullmatch(r'\s*[A-Za-z_][\w \*]*', pre_tail):
                    continue                                  # a call site
                sig = ln[ln.rfind(";", 0, m.start()) + 1:].strip().rstrip("{").strip()
                if _def_head_at(ln, par):
                    defs[fn].append((sig, rel, i))
                elif "extern" in pre_tail:
                    decls[fn].append((sig.rstrip(";").strip(), rel, i, used))
    return defs, decls


def parse_sig(s):
    """The cdecl Declarator for a signature string, or None.

    Returns the DECLARATOR, not a (ret, params) tuple, because every comparison in this tool must be
    `cdecl.compatible` — TYPE IDENTITY, not type SPELLING (Phase 29 T69). The first cut compared the
    rendered strings, so `s32` vs `int` and `u32` vs `unsigned int` counted as disagreements. That
    made the "other in-scope decls" precondition block ALL SIX corrections that had just gated
    140/140 and banked 685 members — a precondition that would have prevented the work it was written
    to protect. The genuine incompatibility (func_80147364: `s32` vs `u16` parameter) survives
    `compatible`; the spelling noise does not."""
    try:
        return cdecl.parse(s.rstrip("; ") + ";")[0]
    except Exception:
        return None


def same(a, b):
    """Type-identity comparison of two Declarators (None-safe)."""
    if a is None or b is None:
        return False
    try:
        return bool(cdecl.compatible(a, b))
    except Exception:
        return False


def consumers_of(fn):
    import conform_decls
    try:
        return len(conform_decls.consumers(fn))
    except Exception:
        return -1


def live_stubs(fn):
    """How many binaries still carry this fn as an INCLUDE_ASM stub — the unblock value."""
    pat = re.compile(rf'INCLUDE_ASM\("[^"]*",\s*{fn}\);')
    n = 0
    for ov in sorted(os.listdir(os.path.join(REPO, "src"))):
        d = os.path.join(REPO, "src", ov)
        if not os.path.isdir(d):
            continue
        if any(pat.search(open(c, errors="replace").read())
               for c in glob.glob(os.path.join(d, "*.c"))):
            n += 1
    return n


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--all", action="store_true", help="list every disagreement, not just the head")
    ap.add_argument("--json")
    ap.add_argument("--top", type=int, default=25)
    a = ap.parse_args()

    decls = header_decls()
    print(f"header decls: {sum(len(v) for v in decls.values())} across {len(decls)} functions",
          flush=True)
    defs, dcl = scan_corpus(set(decls))
    mowners = macro_owners()
    hcalled = called_in_headers()
    print(f"definitions found for {len(defs)} of them", flush=True)

    findings = []
    for fn, ds in sorted(decls.items()):
        dfs = defs.get(fn)
        if not dfs:
            continue                                          # never defined -> nothing to compare
        hsig = ds[0][0]
        hp = parse_sig(hsig)
        if not hp:
            continue
        # A function is only interesting if EVERY definition disagrees with the header the same way.
        # One overlay disagreeing is loose typing (§16, T49); all of them disagreeing means the
        # header is the outlier.
        parsed = [(parse_sig(s), s, p, l) for s, p, l in dfs]
        parsed = [x for x in parsed if x[0]]
        if not parsed:
            continue
        if any(same(x[0], hp) for x in parsed):
            continue                                          # some definition agrees -> not a defect
        ret_diff = all(x[0].base != hp.base for x in parsed)
        par_diff = all(list(x[0].params or []) != list(hp.params or []) for x in parsed)
        if not (ret_diff or par_diff):
            continue
        kind = "BOTH" if (ret_diff and par_diff) else ("RETURN" if ret_diff else "PARAMS")
        truth = parsed[0][0]

        # ---- PRECONDITION 1: ARITY (Phase 29 T67, found by gating). A header decl of `(void)` for a
        # function DEFINED with a parameter cannot simply be retyped: the DEFINE_ macro's own call
        # site passes the header's arity, so correcting the decl breaks it with "too few arguments".
        # Those need the §99 no-prototype treatment, not a retype.
        # §113: an arity difference only blocks when the macro CALLS the function.
        arity_ok = (len(truth.params or []) == len(hp.params or [])
                    or fn not in hcalled)

        # ---- PRECONDITION 2: NO DISAGREEING IN-SCOPE DECL (Phase 29 T67, found by a FAILED gate).
        # A first batch of 7 corrections failed 2/140 with `conflicting types for func_80147364` —
        # 9 header sites rewritten, but the overlays' own TUs still declared it the old way. Correct
        # the header alone and those become conflicts. Such a function needs a conform_decls pass
        # first, so it is reported UNSAFE with the count of sites that would have to move.
        # Only a TU that INSTANTIATES one of the macros carrying this decl can collide with it.
        owners = mowners.get(fn, set())
        bad_decls = []
        for s, p, l, used in dcl.get(fn, []):
            if not (used & owners):               # the corrected decl is not visible in this TU
                continue
            q = parse_sig(s)
            if q and not same(q, truth):          # INCOMPATIBLE, not merely spelled differently
                bad_decls.append(f"{p}:{l}")

        findings.append(dict(fn=fn, kind=kind, header=hsig, header_sites=len(ds),
                             defs=sorted({x[1] for x in parsed}),
                             def_where=f"{parsed[0][2]}:{parsed[0][3]}",
                             arity_ok=arity_ok, bad_decls=len(bad_decls),
                             bad_decl_where=bad_decls[:3],
                             safe=bool(arity_ok and not bad_decls)))

    for f in findings:
        f["live_stubs"] = live_stubs(f["fn"])
        f["consumers"] = consumers_of(f["fn"]) if f["kind"] in ("RETURN", "BOTH") else 0
        if f["consumers"] > 0:                     # §85: a consumed return is not byte-neutral
            f["safe"] = False
            f["blocker"] = f"§85: {f['consumers']} caller(s) consume the return"
        elif not f["arity_ok"]:
            f["blocker"] = "ARITY: header/def arity differ AND the macro CALLS it — §99 no-prototype"
        elif f["bad_decls"]:
            f["blocker"] = f"DECLS: {f['bad_decls']} disagreeing decl(s) in src/ — conform_decls first"
        else:
            f["blocker"] = ""
    findings.sort(key=lambda f: (not f["safe"], -f["live_stubs"], f["fn"]))
    safe = [f for f in findings if f["safe"]]

    print(f"\n=== {len(findings)} header decl(s) contradict every known definition ===")
    print(f"    {len(safe)} SAFE to correct now · {len(findings) - len(safe)} blocked\n")
    print(f"{'function':<16}{'kind':<8}{'stubs':>6}  {'status':<52} header -> definition")
    shown = findings if a.all else findings[:a.top]
    for f in shown:
        st = "SAFE" if f["safe"] else f["blocker"]
        print(f"{f['fn']:<16}{f['kind']:<8}{f['live_stubs']:>6}  {st:<52} {f['header']}")
        print(f"{'':<84}-> {f['defs'][0]}")
    if not a.all and len(findings) > a.top:
        print(f"... {len(findings) - a.top} more (--all)")
    print(f"\nSAFE subset: {len(safe)} function(s), {sum(f['live_stubs'] for f in safe)} stubbed binaries")
    print("Preconditions enforced: §85 (no caller consumes a changed return) · ARITY (header==def, or")
    print("the macro's own call site breaks) · DECLS (nothing else in src/ declares it differently).")
    print("Correcting a shared header is fleet-shared (§61/§63): R22 mandatory, two steps —")
    print("  header change ALONE must rebuild 140/140, THEN sweep.")
    if a.json:
        json.dump(findings, open(a.json, "w"), indent=1)
        print(f"wrote {a.json}")


if __name__ == "__main__":
    main()

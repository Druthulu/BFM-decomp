#!/usr/bin/env python3
"""conform_decls.py — conform every fleet DECLARATION of a function to its byte-true DEFINITION.

WHY (§58b): when a draft reaches `match_one` MATCH, **the draft's signature is byte-TRUTH** — it is
the shape that produced the target's instructions. The `extern` in `engine_core.h` and in each
overlay TU is a stub-era GUESS, written before anyone knew. So the fix for `conflicting types for
func_X` is to move the DECLS, never the draft.

WHY A TOOL (Phase 29 SESSION-21): this was applied by hand three times in one session
(func_8014D2A0, func_8014D820, func_8012AAAC) and it is the single dominant gate-failure class —
7 of 7 plain drafts and 3 of the first 4 jtbl drafts. Doing it by hand is how a half-axis happens.

THE TWO LAWS THIS ENCODES
=========================
1. **ALL-OR-NOTHING (§85).** A declaration axis rewritten at only some sites is a GUARANTEED break,
   not a smaller win: the source overlay carries its own local `extern`s, so widening the shared
   header alone conflicts with them by construction. Every site is rewritten, and a completion
   assertion (R32) proves none survived — a count, not a hope.
2. **THE RETURN AXIS HAS A PRECONDITION (§85).** Widening `void` -> `s32` is byte-neutral only if
   NO caller consumes the return value. That is checked and the run REFUSES if any does, because a
   consumed return changes the caller's codegen.

The whole-binary byte-gate remains the sole arbiter (G3/P9): this only removes a declaration
conflict so the gate can judge the BODY. A wrong signature still fails to bank.

Usage:
  tools/conform_decls.py --fn func_XXXX --draft <draft.c> [--check] [--apply]
"""
import argparse, glob, os, re, sys
import importlib.util as _ilu


def _load(mod, rel):
    _spec = _ilu.spec_from_file_location(mod, os.path.join(
        os.path.dirname(os.path.dirname(os.path.abspath(__file__))), rel))
    _m = _ilu.module_from_spec(_spec)
    _spec.loader.exec_module(_m)
    return _m


cdecl = _load('cdecl', 'tools/cdecl.py')   # for _mask: comments/strings are never rewritten (H5)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = [os.path.join(REPO, p) for p in ("src",)]


def sources():
    out = []
    for root in SRC:
        out += glob.glob(os.path.join(root, "**", "*.c"), recursive=True)
        out += glob.glob(os.path.join(root, "**", "*.h"), recursive=True)
    return out


# Default argument promotions (C89 6.3.2.2). A K&R definition promotes each narrow parameter, so a
# PROTOTYPE in scope must declare the PROMOTED type or gcc rejects the pair with
# `argument 'x' doesn't match prototype`. This is not a style choice — it is why the fleet's existing
# prototype for the §43 K&R function func_801330E0 reads `s32 a2` for a parameter the definition
# declares `s16`, and why emitting the declared (unpromoted) type would RE-CREATE the narrow-param
# conflict this tool exists to remove.
_PROMOTE = {"s8": "s32", "u8": "s32", "char": "s32", "s16": "s32", "u16": "s32",
            "short": "s32", "signed char": "s32", "unsigned char": "s32",
            "unsigned short": "s32", "float": "f64"}


def _promote(ty):
    ty = re.sub(r"\s+", " ", ty.strip())
    return ty if "*" in ty else _PROMOTE.get(ty, ty)


# The fleet's typedefs (include/common.h): `int` IS `s32`, `unsigned int` IS `u32`. Comparing the
# LITERAL return spelling therefore reports a phantom return-axis change for every decl written in
# stock C types — and the §85 precondition below then refuses a conform that changes no return type
# at all. Measured on func_80128ED8 (Phase 30 S47): 1,592 decl sites, return `s32` on both sides,
# REFUSED because 11 sites spell it `int` and 2 omit `extern`.
_RET_ALIAS = {"int": "s32", "signed": "s32", "signed int": "s32", "long": "s32",
              "signed long": "s32", "unsigned": "u32", "unsigned int": "u32",
              "unsigned long": "u32", "short": "s16", "unsigned short": "u16",
              "char": "s8", "signed char": "s8", "unsigned char": "u8"}


def _norm_ret(ty):
    ty = re.sub(r"\s+", " ", ty.replace("extern", " ").strip())
    stars = ty.count("*")
    base = re.sub(r"\s+", " ", ty.replace("*", "").strip())
    return _RET_ALIAS.get(base, base) + "*" * stars


ENGINE_HDR = os.path.join(REPO, "src", "shared", "engine_core.h")


def _defining_macro_span(txt, fn):
    """(start, end) char offsets of `#define DEFINE_<fn>()` including its backslash continuations.

    The deduped body lives inside this span and is byte-truth; everything OUTSIDE it in the same
    header is an ordinary declaration belonging to some other macro, and must move with the axis."""
    m = re.search(rf"^[ \t]*#define[ \t]+DEFINE_{re.escape(fn)}\(\)", txt, re.M)
    if not m:
        return None
    k = m.end()
    while True:
        nl = txt.find("\n", k)
        if nl == -1:
            return (m.start(), len(txt))
        if not txt[k:nl].rstrip().endswith("\\"):
            return (m.start(), nl)
        k = nl + 1


def _ret_of(decl, fn):
    """The return type of one declaration FORM, normalized. `extern` is optional — a decl inside a
    header macro may omit it, and a literal-prefix match silently reads that as a return change."""
    m = re.match(rf"\s*(?:extern\s+)?(.*?)\b{re.escape(fn)}\s*\(", decl)
    return _norm_ret(m.group(1)) if m else None


def def_signature(draft_path, fn):
    """(return_type, params_text) of the draft's DEFINITION — the byte-true shape.

    Handles BOTH definition forms. The K&R arm is not optional: §43 (`s16` parameter declared
    K&R-style, producing the in-place `sll $a2,$a2,16` tell) is a documented, load-bearing idiom in
    this codebase for exactly the narrow-param class, so a tool that only parses ANSI definitions
    refuses precisely the drafts that most need it — silently reading as "nothing to conform" for a
    whole idiom family (R32 coverage, Phase 29 SESSION-22)."""
    txt = open(draft_path, errors="replace").read()
    m = re.search(rf"^([A-Za-z_][\w \t\*]*?)\b{fn}\s*\(([^;{{]*)\)\s*\{{", txt, re.M)
    if m:
        return m.group(1).strip(), m.group(2).strip()

    # K&R:  void fn(a, b, c)\n  void *a;\n  s16 *b;\n  s16 c;\n  {
    m = re.search(rf"^([A-Za-z_][\w \t\*]*?)\b{fn}\s*\(\s*([A-Za-z_]\w*(?:\s*,\s*[A-Za-z_]\w*)*)\s*\)"
                  rf"\s*((?:[^;{{}}]*;\s*)+)\{{", txt, re.M)
    if m:
        names = [n.strip() for n in m.group(2).split(",")]
        declared = {}
        for stmt in m.group(3).split(";"):
            stmt = stmt.strip()
            if not stmt:
                continue
            d = re.match(r"^(.*?)([A-Za-z_]\w*)\s*$", stmt.replace("*", "* "))
            if d:
                declared[d.group(2)] = re.sub(r"\s+\*", " *", d.group(1)).strip()
        missing = [n for n in names if n not in declared]
        if missing:                      # an undeclared K&R param defaults to int — but say so (R32)
            print(f"note: K&R parameter(s) {', '.join(missing)} have no declaration; "
                  f"defaulting to s32 per C89", file=sys.stderr)
        params = ", ".join(f"{_promote(declared.get(n, 's32'))} {n}" for n in names)
        return m.group(1).strip(), params

    sys.exit(f"conform_decls: no DEFINITION of {fn} in {draft_path} "
             f"(a declaration alone is not byte-truth — refusing to guess)")


def strip_names(params):
    """`s32 a0, void *a1` -> `s32, void *` — compare shapes, not parameter spellings."""
    if params.strip() in ("", "void"):
        return params.strip()
    out = []
    for p in params.split(","):
        p = p.strip()
        p = re.sub(r"\b[A-Za-z_]\w*\s*$", "", p).strip()      # drop a trailing identifier
        out.append(re.sub(r"\s+", " ", p))
    return ", ".join(out)


def consumers(fn):
    """Call sites whose VALUE is used — the §85 return-axis precondition.

    Classified by POSITION, not by surface pattern. The three patterns this replaced
    (`= fn(`, `return fn(`, `if (fn(`) missed every consumer that does not put the call
    immediately after the operator, and this codebase casts constantly:

        s0 = (s32 *)func_80144A04((s32 *)a1);      <- engine_core.h:29159, MISSED
        foo(func_x(a));                            <- argument position, MISSED
        if (a && func_x(b))                        <- not the first operand, MISSED

    Under-reporting here is the dangerous direction: it CLEARS a return-axis change that is
    not byte-neutral. Measured in Phase 30 S47 — func_80144A04 was conformed s32 -> void on a
    "0 callers consume" verdict and broke ov_SC01_000 with `void value not ignored as it ought
    to be`. So the test is inverted: a call is DISCARDED only when it stands alone as a
    complete statement; everything else counts as a consumer."""
    call = re.compile(rf"(?<![_\w]){re.escape(fn)}\s*\(")
    hits = []
    for p in sources():
        try:
            txt = open(p, errors="replace").read()
        except OSError:
            continue
        masked = cdecl._mask(txt)                  # never read comments/strings (H5)
        for m in call.finditer(masked):
            ls = masked.rfind("\n", 0, m.start()) + 1
            le = masked.find("\n", m.start())
            line = txt[ls: le if le != -1 else len(txt)]
            before = masked[ls:m.start()].strip().rstrip("\\").strip()
            if "extern" in before or re.match(rf"^[A-Za-z_][\w \t\*]*$", before) and "(" not in before:
                continue                           # a declaration or definition, not a call
            # walk to the matching ')' and look at what follows
            k, depth = m.end(), 1
            while k < len(masked) and depth:
                depth += (masked[k] == "(") - (masked[k] == ")")
                k += 1
            after = masked[k:k + 4].lstrip()
            discarded = before in ("", "{", "}", ";", "else") and after.startswith(";")
            if not discarded:
                hits.append((os.path.relpath(p, REPO), line.strip()[:100]))
    return hits


def main():
    import frozen; frozen.refuse("conform_decls.py", "the types phase (Phase 37)", "it conforms the fleet's declarations to engine_core.h (gone)")  # Phase 35 T6: FROZEN
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--fn", required=True)
    ap.add_argument("--draft", required=True)
    ap.add_argument("--check", action="store_true", help="dry run (default)")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--cast-zero-arg-calls", action="store_true",
                    help="fix the arity precondition it would otherwise REFUSE on: cast every\n                          0-arg CALL SITE to the 0-arg fn-ptr shape (§17a-1), then exit so the\n                          conform can be re-run. gcc folds the cast of a known symbol to a\n                          direct jal, so the caller's bytes are unchanged; the gate arbitrates.")
    a = ap.parse_args()

    ret, params = def_signature(a.draft, a.fn)
    canon_plain = f"{ret} {a.fn}({params});"
    canon = "extern " + canon_plain
    print(f"byte-true definition: {ret} {a.fn}({params})")

    # `extern` is OPTIONAL: a file-scope prototype without it is equally a declaration, and the
    # `;` terminator is what separates a declaration from a definition (which ends in `{`).
    # Requiring `extern` made this tool report "no declaration of func_8013BD74 found" for a TU that
    # declares it on line 23 as `void func_8013BD74(void *a0, s32 a1);` — a silent miss that reads
    # exactly like "nothing to do" (R32). The leading `extern` is PRESERVED where present, so the
    # rewrite never changes a declaration's linkage.
    # `[^;{\n]*` — NOT `[^;]*` (Phase 29 SESSION-22, byte-witnessed on ov_SC07_006).
    # `[^;]*` matches NEWLINES, so a match starting at a DEFINITION line
    #     s32 func_8014CF04(s32 param_1, void *param_2, void *param_3) {
    # ran straight past the brace and through the body to the first `;` it found — the register-pin
    # declaration on the next line — and replaced BOTH with a prototype. The definition was deleted,
    # the binary failed to link (`undefined reference to func_8014CF04`), and R22 caught it at
    # 139/140 while the per-binary gate on ov_SC01_077 had said BYTE-IDENTICAL. Excluding `\n` and
    # `{` makes a definition unmatchable by construction; a multi-line prototype simply is not
    # matched, and the R32 completion assertion below then reports it rather than mangling it.
    decl_re = re.compile(rf"(extern\s+)?[A-Za-z_][\w \t\*]*?\b{a.fn}\s*\([^;{{\n]*\);")
    # A DEFINITION of the target, for the guard below: the same head, followed by `{` not `;`.
    def_re = re.compile(rf"(?:[A-Za-z_][\w \t\*]*?)\b{a.fn}\s*\([^;{{\n]*\)\s*\{{")

    def _canon_for(m):
        return (m.group(1) or "") + f"{ret} {a.fn}({params});"

    def _decl_spans(txt):
        """Declaration matches, found on MASKED text so a comment or string literal can never be
        rewritten (H5 — this tool mangled three comment lines before the mask went in), with the
        spans applied to the ORIGINAL. `cdecl._mask` is length-preserving precisely so that offsets
        into the mask are valid offsets into the source (R33: reuse it, do not write a third one)."""
        return [(m.start(), m.end(), _canon_for(m)) for m in decl_re.finditer(cdecl._mask(txt))]
    forms, total = {}, 0
    for p in sources():
        try:
            txt = open(p, errors="replace").read()
        except OSError:
            continue
        for m in decl_re.finditer(txt):
            forms[m.group(0)] = forms.get(m.group(0), 0) + 1
            total += 1
    if not total:
        sys.exit(f"conform_decls: no `extern` declaration of {a.fn} found — nothing to conform")
    print(f"declaration sites: {total}")
    for f, n in sorted(forms.items(), key=lambda kv: -kv[1]):
        mark = "  (already canonical)" if f in (canon, canon_plain) else ""
        print(f"  {n:>5}  {f}{mark}")

    # ---- THE ARITY PRECONDITION (Phase 29 SESSION-21, learned by breaking 138 binaries) ----
    # Conforming a decl from `(void)` to a signature that TAKES parameters is not a decl-only
    # change: it makes every existing 0-ARG CALL SITE a hard `too few arguments` error the moment a
    # prototype is in scope. That is fleet-wide, and the per-binary gate CANNOT see it — ov_SC01_077
    # gated BYTE-IDENTICAL while 138 other binaries failed to compile, exactly the §63/§85 shape.
    #
    # func_8012AAAC needed 137 call-site casts to absorb this; func_8015B950 would need ~926. So the
    # tool REFUSES and names the cost, rather than leaving a half-axis that only R22 can discover.
    if strip_names(params) not in ("", "void"):
        zero_arg = re.compile(rf"(?<![\w>.]){a.fn}\(\)\s*;")
        callers = []
        for p in sources():
            try:
                txt = open(p, errors="replace").read()
            except OSError:
                continue
            for m in zero_arg.finditer(txt):
                ls = txt.rfind("\n", 0, m.start()) + 1
                le = txt.find("\n", m.start())
                line = txt[ls: le if le != -1 else len(txt)]
                if "extern" in line:
                    continue                      # a declaration, not a call
                callers.append(os.path.relpath(p, REPO))
        if callers and a.cast_zero_arg_calls:
            # THE TOOL THAT DIAGNOSES SHOULD BE ABLE TO FIX (Phase 29 SESSION-22). This is the
            # documented §17a-1 remedy the refusal message already prescribes; doing it by hand
            # across 138 files is exactly how a half-axis happens. PLAN -> VALIDATE -> WRITE,
            # same as the decl axis: a partial cast set is a fleet-wide compile break.
            rx = re.compile(rf"(?<![\w>.]){a.fn}\(\)")
            plan2, n2 = [], 0
            for p in sorted(set(os.path.join(REPO, c) for c in callers)):
                txt = open(p, errors="replace").read()
                out, k = [], 0
                for line in txt.split("\n"):
                    if rx.search(line) and "extern" not in line:
                        line = rx.sub(f"(({ret} (*)(void)){a.fn})()", line); k += 1
                    out.append(line)
                if k:
                    plan2.append((p, "\n".join(out))); n2 += k
            if not a.apply:
                print(f"\nwould cast {n2} zero-arg call site(s) across {len(plan2)} file(s) "
                      f"to (({ret} (*)(void)){a.fn})()  — pass --apply to write")
                return 0
            for p, new in plan2:
                open(p, "w").write(new)
            print(f"cast {n2} zero-arg call site(s) across {len(plan2)} file(s). "
                  f"Re-run WITHOUT --cast-zero-arg-calls to conform the declarations. "
                  f"This edits {len(plan2)} binaries — R22 is mandatory before committing.")
            return 0
        if callers:
            print(f"\n*** REFUSED: the byte-true signature takes parameters, but {len(callers)} "
                  f"0-ARG CALL SITE(s) exist across {len(set(callers))} file(s). Conforming the "
                  f"decl alone turns every one into `too few arguments` — a fleet-wide COMPILE "
                  f"break the per-binary gate cannot see (measured: 138/140 binaries).",
                  file=sys.stderr)
            print(f"    Fix the call sites FIRST — cast each to the 0-arg shape "
                  f"(((void (*)(void)){a.fn})(), §17a-1; gcc folds the cast of a known symbol to a "
                  f"direct jal) — then re-run. Files: {', '.join(sorted(set(callers))[:3])}"
                  + (" …" if len(set(callers)) > 3 else ""), file=sys.stderr)
            return 2

    # ---- THE SCALAR-NARROWING WARNING (Phase 29 SESSION-21, byte-proven) ----
    # A POINTER type change in a decl is caller-neutral (passing a pointer is passing a pointer —
    # func_80179B74 conformed 1,600 sites s16*/short* -> u16* and stayed byte-identical fleet-wide).
    # A SCALAR WIDTH change is NOT: narrowing `s32 a0` -> `u16 param_1` changes argument promotion,
    # so callers emit different code. Measured on func_80175DA8 — with the decls reverted the gate
    # says PLUMBING (`conflicting types`), with the conform applied it says **DIFF**. The conform
    # did not fix the draft; it changed the callers.
    #
    # This is NOT a refusal: the draft's signature is still byte-truth for the CALLEE, and the
    # whole-binary gate is the arbiter. It is a warning that the usual "decls are free" intuition
    # does not hold here, so a DIFF after this conform means re-examine the CALLERS (the §17a-1
    # pair — keep the caller decl compatible and cast at the call site) rather than the body.
    NARROW = {"u8": 1, "s8": 1, "char": 1, "u16": 2, "s16": 2, "short": 2}
    old_shapes = {strip_names(re.search(rf"\(([^;]*)\)\s*;", f).group(1)) for f in forms
                  if re.search(rf"\(([^;]*)\)\s*;", f)}
    new_shape = strip_names(params)
    narrowing = []
    for old in old_shapes:
        for o, n in zip([x.strip() for x in old.split(",")], [x.strip() for x in new_shape.split(",")]):
            if "*" in o or "*" in n:
                continue                                  # pointer change: caller-neutral
            nb = NARROW.get(n.replace("unsigned ", "u").replace("signed ", "s"))
            if nb and o not in ("", "void") and o != n:
                narrowing.append(f"{o} -> {n}")
    if narrowing:
        print(f"\n⚠  SCALAR-NARROWING in the parameter list ({', '.join(sorted(set(narrowing)))}). "
              f"Unlike a pointer-type change this is NOT caller-neutral — argument promotion at "
              f"every call site changes, so callers emit different code (byte-proven on "
              f"func_80175DA8: PLUMBING before the conform, DIFF after). Applying is still valid — "
              f"the draft's signature is byte-truth for the CALLEE and the whole-binary gate "
              f"arbitrates — but if the gate then reports DIFF, examine the CALLERS (§17a-1: keep "
              f"their decl compatible and cast at the call site), not the body.")

    # §85 precondition — only matters when the RETURN type changes.
    # Compare NORMALIZED return types, not spellings: a typedef alias (`int` for `s32`) or a missing
    # `extern` is not a return-axis change. A genuine void -> s32 widening still trips this.
    _want = _norm_ret(ret)
    ret_changes = any((_r := _ret_of(f, a.fn)) is not None and _r != _want for f in forms)
    if ret_changes:
        cs = consumers(a.fn)
        if cs:
            print(f"\n*** REFUSED: {len(cs)} caller(s) CONSUME the return value, so widening the "
                  f"return type is NOT byte-neutral (§85 precondition):", file=sys.stderr)
            for p, l in cs[:5]:
                print(f"    {p}: {l}", file=sys.stderr)
            return 2
        print("§85 precondition: 0 callers consume the return => widening is byte-neutral")

    if not a.apply:
        print("\n(dry run — pass --apply to rewrite)")
        return 0

    # PLAN -> VALIDATE -> WRITE. Never write as you go: this axis spans ~1,748 files, and aborting
    # halfway through leaves a HALF-AXIS, which §85 says is a guaranteed break rather than a smaller
    # win. Planning first means a refusal costs nothing and leaves the tree untouched.
    plan, changed, defining = [], 0, []
    for p in sources():
        try:
            txt = open(p, errors="replace").read()
        except OSError:
            continue
        # A TU THAT DEFINES THE FUNCTION OWNS ITS OWN DECLARATIONS — SKIP THE WHOLE FILE.
        # (Phase 29 SESSION-22, byte-witnessed on ov_SC07_006; the Phase-16 loose-typing wall.)
        # This engine gives ONE address DIFFERENT byte-true signatures in different overlays:
        # ov_SC01_077 needs `(s32, void*, void*)` while ov_SC07_006's own banked definition needs
        # `(s32, s32, void*)`, and that file carries a local decl explicitly marked
        #     /* de-macroized: per-overlay-local decl (byte-true sig); do NOT re-macroize */
        # Conforming it to the fleet-wide canonical produced `conflicting types` against the very
        # definition below it — the tool overwrote a deliberate, byte-true, per-overlay exception.
        # A fleet-wide axis is only meaningful for TUs that CONSUME the symbol; a TU that DEFINES it
        # is byte-truth for itself and must be left entirely alone.
        # ...EXCEPT the shared macro library, which is not a TU at all (Phase 30 S47, byte-witnessed).
        # `engine_core.h` holds ~1,600 DEFINE_func_* macro DEFINITIONS plus thousands of unrelated
        # macro-local `extern`s. Skipping it whole because it "defines" the function leaves every one
        # of those externs at the OLD spelling while all 1,514 fleet sites move to the new one — a
        # half-axis in the one file every overlay includes, i.e. the exact fleet-wide break §85 warns
        # about. Measured on func_80128ED8: 10 stale externs survived the "axis complete" assertion.
        # The narrow truth is that the DEFINING MACRO owns its own body — not that the file does.
        _is_engine_hdr = os.path.abspath(p) == os.path.abspath(ENGINE_HDR)
        protect = _defining_macro_span(txt, a.fn) if _is_engine_hdr else None
        if def_re.search(cdecl._mask(txt)) and not _is_engine_hdr:
            defining.append(os.path.relpath(p, REPO))
            continue
        spans = _decl_spans(txt)
        if protect:                                   # conform around the definition, not past it
            lo, hi = protect
            spans = [s for s in spans if not (s[0] < hi and s[1] > lo)]
        if not spans:
            continue
        new = txt
        for s, e, rep in reversed(spans):          # right-to-left keeps earlier offsets valid
            new = new[:s] + rep + new[e:]
        if new == txt:
            continue
        # THE GUARD (R32, and the reason this run exists): a DEFINITION must never be rewritten.
        # A binary that has already BANKED this function carries its definition, and that definition
        # is byte-truth there — conforming it away silently turns a matched function back into an
        # unresolved symbol (`undefined reference`), which only R22 can see.
        if len(def_re.findall(cdecl._mask(new))) != len(def_re.findall(cdecl._mask(txt))):
            print(f"\n*** REFUSED: the rewrite would DESTROY a definition of {a.fn} in "
                  f"{os.path.relpath(p, REPO)}. Nothing has been written — the plan is discarded "
                  f"whole. This is the ov_SC07_006 class: that binary has already BANKED the "
                  f"function, so its definition is byte-truth there and must be left alone.",
                  file=sys.stderr)
            return 2
        plan.append((p, new))
        changed += len(spans)
    for p, new in plan:                            # validated -> commit the whole axis at once
        open(p, "w").write(new)
    touched = len(plan)
    if defining:
        print(f"skipped {len(defining)} file(s) that DEFINE {a.fn} — a defining TU owns its own "
              f"declarations (per-overlay byte-true signatures differ; §16 loose typing): "
              f"{', '.join(defining[:4])}{' …' if len(defining) > 4 else ''}")
    # R32: the axis is complete or it is a guaranteed break — assert, never assume.
    left = 0
    for p in sources():
        try:
            txt = open(p, errors="replace").read()
        except OSError:
            continue
        if def_re.search(cdecl._mask(txt)):
            continue          # a DEFINING TU is a deliberate exception, not a missed site — the
                              # all-or-nothing invariant (§85) is over the CONSUMING TUs. Counting
                              # the exception here made the tool report a false HALF-AXIS and refuse
                              # a complete, correct rewrite. An assertion must be exact about its
                              # DOMAIN, or it cries wolf on its own by-design behaviour (R32).
        left += sum(1 for m in decl_re.finditer(cdecl._mask(txt)) if m.group(0) != _canon_for(m))
    print(f"rewrote {changed} declaration sites across {touched} files")
    print(f"non-canonical declarations remaining: {left}  "
          f"{'OK (axis complete)' if left == 0 else '*** HALF-AXIS — DO NOT BUILD ***'}")
    return 0 if left == 0 else 1


if __name__ == "__main__":
    sys.exit(main())

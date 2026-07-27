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

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = [os.path.join(REPO, p) for p in ("src",)]


def sources():
    out = []
    for root in SRC:
        out += glob.glob(os.path.join(root, "**", "*.c"), recursive=True)
        out += glob.glob(os.path.join(root, "**", "*.h"), recursive=True)
    return out


def def_signature(draft_path, fn):
    """(return_type, params_text) of the draft's DEFINITION — the byte-true shape."""
    txt = open(draft_path, errors="replace").read()
    m = re.search(rf"^([A-Za-z_][\w \t\*]*?)\b{fn}\s*\(([^;{{]*)\)\s*\{{", txt, re.M)
    if not m:
        sys.exit(f"conform_decls: no DEFINITION of {fn} in {draft_path} "
                 f"(a declaration alone is not byte-truth — refusing to guess)")
    return m.group(1).strip(), m.group(2).strip()


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
    """Call sites whose VALUE is used — the §85 return-axis precondition."""
    pats = [re.compile(rf"=\s*{fn}\s*\("), re.compile(rf"return\s+{fn}\s*\("),
            re.compile(rf"(?:if|while|switch)\s*\(\s*{fn}\s*\(")]
    hits = []
    for p in sources():
        try:
            txt = open(p, errors="replace").read()
        except OSError:
            continue
        for pat in pats:
            for m in pat.finditer(txt):
                ls = txt.rfind("\n", 0, m.start()) + 1
                le = txt.find("\n", m.start())
                hits.append((os.path.relpath(p, REPO), txt[ls: le if le != -1 else len(txt)].strip()[:100]))
    return hits


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--fn", required=True)
    ap.add_argument("--draft", required=True)
    ap.add_argument("--check", action="store_true", help="dry run (default)")
    ap.add_argument("--apply", action="store_true")
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
    decl_re = re.compile(rf"(extern\s+)?[A-Za-z_][\w \t\*]*?\b{a.fn}\s*\([^;]*\);")

    def _canon_for(m):
        return (m.group(1) or "") + f"{ret} {a.fn}({params});"
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

    # §85 precondition — only matters when the RETURN type changes.
    ret_changes = any(not re.match(rf"extern\s+{re.escape(ret)}\s", f) for f in forms)
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

    changed = touched = 0
    for p in sources():
        try:
            txt = open(p, errors="replace").read()
        except OSError:
            continue
        new, n = decl_re.subn(_canon_for, txt)
        if n and new != txt:
            open(p, "w").write(new)
            changed += n
            touched += 1
    # R32: the axis is complete or it is a guaranteed break — assert, never assume.
    left = 0
    for p in sources():
        try:
            txt = open(p, errors="replace").read()
        except OSError:
            continue
        left += sum(1 for m in decl_re.finditer(txt) if m.group(0) != _canon_for(m))
    print(f"rewrote {changed} declaration sites across {touched} files")
    print(f"non-canonical declarations remaining: {left}  "
          f"{'OK (axis complete)' if left == 0 else '*** HALF-AXIS — DO NOT BUILD ***'}")
    return 0 if left == 0 else 1


if __name__ == "__main__":
    sys.exit(main())

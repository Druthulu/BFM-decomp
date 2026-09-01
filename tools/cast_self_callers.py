#!/usr/bin/env python3
"""tools/cast_self_callers.py — the §378 SELF-CALLER cast: let a TU keep calling the function it is
about to define. (P31 S69, byte-proven on ov_SC04_010/func_8017D6CC)

THE MIRROR OF `cast_call_sites.py`. That tool fixes the DRAFT calling a conflicting CALLEE. This one
fixes the opposite direction — the TU's OWN already-banked code calling the function the draft is
about to define — which nothing in the toolkit handled, and which is the terminal blocker of the
whole "it already matches standalone" pile (§376).

THE THREE-STEP FAILURE, measured on all 28 members of that pile in S69:

    1. The TU carries a forward decl written for a call site:   extern void func_X(void);
       The draft's real signature is                            void func_X(void *a0);
       => `conflicting types for func_X'                        (a COMPILE error, not a byte miss)

    2. `fix_arity_callers --any-proto` no-protos that decl:     extern void func_X();
       Now the DRAFT'S DEFINITION is the prototype in scope, and the TU's own call is checked
       against it:
       => `too few arguments to function func_X'                (the SAME site, a NEW error)

    3. Cast the call site to a no-proto function pointer:       ((void (*)())func_X)();
       gcc-2.7.2 folds a cast of a KNOWN FUNCTION SYMBOL back to a direct `jal func_X` with the
       arguments already in place (the §20 mechanism), so the caller's bytes are unchanged and the
       byte-gate — the sole arbiter (G3/P9) — accepts it.

WHY A NO-PROTO CAST AND NOT A TYPED ONE. The call site's argument list is what must survive; its
TYPES are not knowable from the call text. A no-proto pointer type accepts any argument list and
applies the default promotions — which is EXACTLY what the site did before the draft arrived, when
it was calling through a no-proto extern. A typed cast would need types we would have to invent,
and inventing one is how §20's cheaper levers each produced a byte MISS rather than a compile error.

WHAT IT REFUSES (R43). A call site that is already cast; the definition line itself; any
declaration (`extern`/`DEFINE_`); and — loudly — a function whose return type cannot be read off
the draft, because guessing it changes the call's value category.

    cast_self_callers.py --binary ov_SC04_010 --funcs func_8017D6CC --drafts <dir> --apply \
        --journal .run/<id>/<binary>.json
    cast_self_callers.py --undo-journal .run/<id>/<binary>.json --keep func_A,func_B
"""
import argparse
import glob
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# `<ret> <fn>(` at the head of a definition. Deliberately permissive on the return type (s32, void *,
# unsigned char, …) and anchored at line start so a call inside a body can never match.
DEF_RE = r"^[ \t]*((?:[A-Za-z_][\w]*[ \t\*]+)+?)%s[ \t]*\("


def src_files(binary):
    if binary == "main":
        return sorted(glob.glob(os.path.join(REPO, "src", "*.c")))
    return sorted(glob.glob(os.path.join(REPO, "src", binary, "*.c")))


def draft_signature(draft_path, fn):
    """The return type AND parameter list as the DRAFT spells them — never guessed (R43)."""
    try:
        text = open(os.path.join(REPO, draft_path)).read()
    except OSError as e:
        return None, None, "draft unreadable: %s" % e
    m = re.search(DEF_RE % re.escape(fn), text, re.M)
    if not m:
        return None, None, "no definition of %s found in %s" % (fn, draft_path)
    ret = " ".join(m.group(1).split()).strip()
    if ret.endswith("*"):
        ret = ret.rstrip("* ") + " *"
    # the parameter list, verbatim between the definition's parentheses (depth-aware for fn-ptr params)
    i = text.index("(", m.end() - 1)
    depth, j = 0, i
    while j < len(text):
        if text[j] == "(":
            depth += 1
        elif text[j] == ")":
            depth -= 1
            if depth == 0:
                break
        j += 1
    params = " ".join(text[i + 1:j].split()) or "void"
    return ret, params, None


def is_declaration(line, fn):
    s = line.strip()
    if s.startswith("extern ") or s.startswith("DEFINE_") or "DEFINE_%s" % fn in s:
        return True
    # `void func_X(void);` — a bare forward declaration ends in `);`
    return bool(re.match(r"^[A-Za-z_][\w \t\*]*\b%s[ \t]*\([^;]*\)[ \t]*;[ \t]*$" % re.escape(fn), s))


def cast_sites(binary, fn, ret, apply_=False):
    """Rewrite `fn(` -> `((<ret> (*)())fn)(` at every genuine CALL site in the binary's own src."""
    edits = []
    call_re = re.compile(r"(?<![\w.>])%s[ \t]*\(" % re.escape(fn))
    for path in src_files(binary):
        try:
            lines = open(path).read().splitlines(keepends=True)
        except OSError:
            continue
        changed = False
        for i, line in enumerate(lines):
            if fn not in line or is_declaration(line, fn):
                continue
            if re.search(DEF_RE % re.escape(fn), line):      # the definition itself
                continue
            if "(*)()" in line and fn in line:               # already cast
                continue
            if "INCLUDE_ASM" in line:
                continue
            new = call_re.sub("((%s (*)())%s)(" % (ret, fn), line)
            if new != line:
                edits.append({"file": os.path.relpath(path, REPO), "line": i + 1,
                              "before": line, "after": new})
                lines[i] = new
                changed = True
        if changed and apply_:
            open(path, "w").write("".join(lines))
    return edits


def sync_decls(binary, fn, ret, params, apply_=False):
    """Rewrite every forward DECLARATION of `fn` to the draft's exact signature.

    WHY THIS EXISTS ON TOP OF `--any-proto` (P31 S69, byte-proven main/func_80036D58).
    A no-proto declaration is ILLEGAL against a definition whose parameter is affected by the
    default argument promotions — C89 requires promotion-stable parameter types when one of the
    two declarations has no prototype. `void func_X(s16)` is exactly that case, so
    `fix_arity_callers --any-proto` cannot reach it and correctly skips it as "narrow-param",
    leaving `conflicting types' standing through every gate.

    Once the CALL SITES ARE CAST (the step above), a declaration emits no code at all, so syncing
    it to the draft's own spelling is byte-neutral — and it is the only spelling guaranteed not to
    conflict. Run this AFTER cast_sites, never instead of it: without the casts, a synced narrow
    prototype would convert the arguments at the call site and move the caller's bytes.
    """
    edits = []
    decl_re = re.compile(r"^([ \t]*(?:extern[ \t]+)?)([A-Za-z_][\w \t\*]*?\b)%s[ \t]*\([^;{]*\)[ \t]*;"
                         % re.escape(fn))
    want = "%s %s(%s);" % (ret, fn, params)
    for path in src_files(binary):
        try:
            lines = open(path).read().splitlines(keepends=True)
        except OSError:
            continue
        changed = False
        for i, line in enumerate(lines):
            if fn not in line:
                continue
            m = decl_re.match(line)
            if not m:
                continue
            new = m.group(1) + want + "\n"   # group(1) already carries the indent AND any `extern `
            if new == line:
                continue
            edits.append({"file": os.path.relpath(path, REPO), "line": i + 1,
                          "before": line, "after": new})
            lines[i] = new
            changed = True
        if changed and apply_:
            open(path, "w").write("".join(lines))
    return edits


def undo(journal_path, keep):
    j = json.load(open(journal_path))
    kept = {k.strip() for k in keep.split(",") if k.strip()}
    reverted = 0
    by_file = {}
    for e in j["edits"]:
        if e["fn"] in kept:
            continue
        by_file.setdefault(e["file"], []).append(e)
    for f, es in by_file.items():
        path = os.path.join(REPO, f)
        text = open(path).read()
        for e in es:
            if e["after"] in text:
                text = text.replace(e["after"], e["before"], 1)
                reverted += 1
        open(path, "w").write(text)
    print("reverted %d edit(s) across %d file(s); kept %d fn(s)"
          % (reverted, len(by_file), len(kept)))
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary")
    ap.add_argument("--funcs", help="comma-separated func_XXXXXXXX list")
    ap.add_argument("--drafts", help="dir holding <fn>.c drafts (for the return type)")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--sync-decls", dest="sync_decls", action="store_true",
                    help="ALSO rewrite every forward declaration to the draft's exact signature — the "
                         "narrow-param case --any-proto cannot legally reach (§378a). Run WITH the "
                         "casts, never instead of them.")
    ap.add_argument("--journal", help="record before/after for --undo-journal")
    ap.add_argument("--undo-journal", dest="undo_journal")
    ap.add_argument("--keep", default="", help="(undo) comma-separated fns whose edits are KEPT")
    a = ap.parse_args()

    if a.undo_journal:
        return undo(a.undo_journal, a.keep)
    if not (a.binary and a.funcs and a.drafts):
        ap.error("--binary, --funcs and --drafts are required")

    fns = [f.strip() for f in a.funcs.split(",") if f.strip()]
    all_edits, refused = [], []
    for fn in fns:
        draft = os.path.join(a.drafts, fn + ".c")
        ret, params, err = draft_signature(draft, fn)
        if ret is None:
            refused.append("%s: %s" % (fn, err))
            continue
        edits = cast_sites(a.binary, fn, ret, apply_=a.apply)
        if a.sync_decls:
            edits += sync_decls(a.binary, fn, ret, params, apply_=a.apply)
        for e in edits:
            e["fn"] = fn
        all_edits.extend(edits)
        print("  [self-cast] %-16s ret=%-8s %d call site(s)%s"
              % (fn, ret, len(edits), "" if a.apply else " (dry)"))
    if refused:
        print("REFUSED %d (R43 — a guessed return type changes the call's value category):"
              % len(refused), file=sys.stderr)
        for r in refused:
            print("  " + r, file=sys.stderr)
    if a.journal:
        os.makedirs(os.path.dirname(os.path.join(REPO, a.journal)) or ".", exist_ok=True)
        json.dump({"binary": a.binary, "edits": all_edits},
                  open(os.path.join(REPO, a.journal), "w"), indent=1)
        print("journal: %d edit(s) -> %s" % (len(all_edits), a.journal))
    print("%s %d call-site cast(s) for %d function(s); %d refused. Re-run the byte-gate now."
          % ("applied" if a.apply else "would apply", len(all_edits), len(fns) - len(refused), len(refused)))
    return 0


if __name__ == "__main__":
    sys.exit(main())

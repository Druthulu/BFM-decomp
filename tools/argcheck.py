#!/usr/bin/env python3
"""argcheck — every call site whose in-scope declaration is NARROWER than the callee's real definition.

WHY THIS EXISTS (P36 S102, the burst of 20). Six T7 agents, working independently on different functions and never
seeing each other's results, each reached score 0 by restoring an argument the source had dropped: a7 (a cast at the
call), a8 (a widened function-pointer-array prototype), a11 (a dispatch-table call given its object pointer), a12 (a
call given the value it loads), a13 (a definition given its two parameters), a25 (a call re-issued at the callee's real
four-argument arity). In every one the register pin was hired to fake the instruction the missing argument would have
emitted, and the mechanisms were different each time — combine's `added_sets_2` gate (`combine.c:1458`), a copy
preference applied ahead of first-fit (`global.c:1535/1589` → `:997-1030`) whose argument copy degenerates into a
self-move deleted at `toplev.c:3142`, reorg's liveness half (`reorg.c:3374`, the use added to
`CALL_INSN_FUNCTION_USAGE` at `:428`) — but the CLASS is one, and no candidate generator can reach it: every family in
`delever.recipe_candidates` rewrites statements and declarations, none edits a call's ARGUMENT LIST.

So this is a static filter, not a search. It answers, for the whole tree at once, the question each of those agents had
to answer by hand with one grep: does this call site's declaration agree with the callee's real definition?

WHAT IT REPORTS, and what the scope column does and does not mean. The scope says which FIX is available, not whether
the body can be banked:
  * ANY scope — the CAST route is bankable body-only, because the cast lives inside the definition: agent a7 closed
    `func_8013BC7C` with `((void (*)(void *))f)(p)` against a FILE-scope `(void)` declaration, and a25 re-issued a call
    at the callee's real four-argument arity the same way.
  * BLOCK scope — the declaration itself can also be widened in the same edit as the body (a8's
    `extern void (*D_80192FD0[])(u8 *);`), which is the more readable spelling.
  * FILE scope — widening the DECLARATION belongs to the types phase, because gcc 2.7.2 rejects a conflicting
    block-scope redeclaration outright; three such are already recorded by name (`func_80136824`, `func_80168828`,
    `func_80157D20`).

KNOWN BLIND SPOT, measured against the six agent cracks this was built from. It finds a7, a12 and a25 and it CANNOT find
a13: `func_80157D20` is declared `(void)` in 131 of its 138 defining sites AND defined `(void)`, so no declaration
disagrees with any definition — the missing parameters exist only in the target's bytes, where the prologue copies two
argument registers. A declaration comparison is blind to a definition that is uniformly wrong; only the residual sees
those. So this census is a lower bound on the class, and the residual remains the oracle.

The real arity is read from the DEFINITION, wherever it lives: a `.c` under `src/`, or a shared body header under
`src/shared/` (P35's one-source-per-function shape). A definition is the ground truth; a declaration is a claim.
"""
import argparse, collections, json, pathlib, re, sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import lever_census as lc

REPO = pathlib.Path(__file__).resolve().parent.parent
NAME = r"[A-Za-z_]\w*"
DEF = re.compile(r"^[A-Za-z_][\w \t*]*?\b(" + NAME + r")\s*\(([^;{]*)\)\s*\{", re.M)
DECL = re.compile(r"\bextern\s+[A-Za-z_][\w \t*]*?\b(" + NAME + r")\s*\(([^;)]*)\)\s*;")


def arity(params):
    """The number of declared parameters. `void` and an empty list are both 0, but they are NOT the same claim: an empty
    list is K&R "unspecified", which gcc accepts against any call, while `(void)` is a positive assertion of none."""
    p = params.strip()
    if p == "" or p == "void":
        return 0
    depth, n = 0, 1
    for ch in p:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif ch == "," and depth == 0:
            n += 1
    return n


def definitions():
    """{name: (arity, params, where)} from every DEFINITION in the tree."""
    out = {}
    for f in sorted(list((REPO / "src").glob("**/*.c")) + list((REPO / "src" / "shared").glob("**/*.h"))):
        rel = str(f.relative_to(REPO))
        try:
            txt = f.read_text(errors="surrogateescape")
        except OSError:
            continue
        masked = lc.sc.mask_text(txt)
        for m in DEF.finditer(masked):
            name, params = m.group(1), m.group(2)
            if name in ("if", "for", "while", "switch", "return", "sizeof"):
                continue
            out.setdefault(name, (arity(params), params.strip(), rel))
    return out


def scan(defs, only_needed_argpins=True):
    """[row] — one row per narrower-than-real declaration, with the scope that decides whether it is bankable."""
    rows = []
    for f in sorted(list((REPO / "src").glob("**/*.c")) + list((REPO / "src" / "shared").glob("**/*.h"))):
        rel = str(f.relative_to(REPO))
        try:
            txt = f.read_text(errors="surrogateescape")
        except OSError:
            continue
        if "extern" not in txt:
            continue
        masked = lc.sc.mask_text(txt)
        lines = masked.split("\n")
        # the bodies of this TU, and which of them hold a NEEDED pin on an argument register
        argpin_fns = set()
        if "!FAKE" in txt:
            for s in lc.walk_file(txt, rel, rel.endswith(".h"))["sites"]:
                if s["cls"] in "AB" and s["kind"] == "pin" and s.get("detail") in ("$4", "$5", "$6", "$7"):
                    argpin_fns.add(s.get("fn"))
        spans = [(m.group(1), masked[:m.start()].count("\n") + 1,
                  masked[:m.end()].count("\n") + 1) for m in DEF.finditer(masked)]
        def fn_at(ln):
            for name, a, _ in spans:
                if a <= ln:
                    last = name
                else:
                    break
            return last if spans and spans[0][1] <= ln else None
        depth = 0
        for i, l in enumerate(lines):
            for m in DECL.finditer(l):
                callee, params = m.group(1), m.group(2)
                real = defs.get(callee)
                if real is None:
                    continue
                dec = arity(params)
                if dec >= real[0]:
                    continue
                if params.strip() == "" and real[0] > 0:
                    kind = "K&R-empty"          # accepts any call; not itself an error, but m2c then calls it with none
                else:
                    kind = "narrow"
                holder = fn_at(i + 1)
                rows.append(dict(tu=rel, line=i + 1, callee=callee, declared=dec, real=real[0],
                                 real_params=real[1], defined_in=real[2], scope="block" if depth > 0 else "file",
                                 kind=kind, in_fn=holder,
                                 argpin=bool(holder and holder in argpin_fns)))
            depth += l.count("{") - l.count("}")
            depth = max(depth, 0)
    return rows


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json", help="write the rows here")
    ap.add_argument("--argpin-only", action="store_true", help="only bodies holding a NEEDED $4-$7 pin")
    a = ap.parse_args()
    defs = definitions()
    rows = scan(defs)
    if a.argpin_only:
        rows = [r for r in rows if r["argpin"]]
    by_callee = collections.Counter(r["callee"] for r in rows)
    by_scope = collections.Counter(r["scope"] for r in rows)
    by_kind = collections.Counter(r["kind"] for r in rows)
    pinned = [r for r in rows if r["argpin"]]
    print(f"argcheck: {len(defs)} definitions read; {len(rows)} declaration(s) narrower than the definition, "
          f"over {len(by_callee)} callee(s)")
    print(f"  by scope: {dict(by_scope)}   (the CAST route is body-only at either scope; only widening the "
          f"DECLARATION needs block scope)")
    print(f"  by kind:  {dict(by_kind)}")
    print(f"  in a body that still holds a NEEDED $4-$7 pin: {len(pinned)} row(s) in "
          f"{len({(r['tu'], r['in_fn']) for r in pinned})} body/bodies — the targeted draw")
    for c, n in by_callee.most_common(12):
        ex = next(r for r in rows if r["callee"] == c)
        print(f"    {c:16s} {n:5d} site(s)  declared {ex['declared']} vs real {ex['real']}  ({ex['defined_in']})")
    if a.json:
        pathlib.Path(a.json).write_text(json.dumps(rows, indent=1))
        print(f"  rows -> {a.json}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

#!/usr/bin/env python3
"""recover_route.py — given a gate's DROP verdict, name the tool that actually applies. (P31 S77)

WHY THIS EXISTS, WITH THE MEASUREMENT.  `gate_main` writes every dropped draft to
`.run/gate_main_dropped.json` and then prints ONE chain for all of them:

    tools/fix_arity_callers.py --apply --any-proto --funcs <all dropped> ...
    tools/cast_self_callers.py --binary main --funcs <same> ...

That is the SELF-declaration chain (§378), and it is correct for exactly one of the three drop
classes.  The playbook already records what the others cost:

  * CALLEE (`conflicting types for func_8012AD44`, a DIFFERENT function): §378 does NOT transfer.
    `cast_self_callers` reads the return type off the draft and cannot cast a callee, so
    `--any-proto` runs UNPROTECTED and changes argument conversion at every call site.
    MEASURED (S69): 60 decls no-protoed, **binary RED**, reverted.
  * DATA (`D_800A5E60`, `D_80072960`): neither tool in the printed chain touches a data extern at
    all.  The fix is to adopt the TU's spelling into the DRAFT (`sync_tu_decls`) or, when the draft
    genuinely needs an incompatible type, demote it to block scope (§8d / §481).

MEASURED COST OF THE WRONG ROUTE, THIS SESSION.  `func_8006252C` was dropped on a clash with
`func_8006252C` ITSELF.  Following the shape of the printed chain I reached for
`scope_demote_drafts` first: it aliased `D_80078D08` through `__asm__`, the build FAILED, and the
draft looked broken.  The actual blocker was the self-declaration, one command away.  Three tools,
wrong order, one of them destructive — because the report named a chain instead of a route.

WHAT THIS DOES NOT DO.  It does not predict which tool will WIN.  For a DATA clash there are two
plausible fixes and the difference is whether the draft can live with the TU's type at all — not
something a classifier can know.  So a route is an ORDERED LADDER and **the byte gate remains the
sole arbiter (G3/P9)**; the ladder just stops you running the destructive one first.

REFUSALS COME FIRST (R43/R61a).  A verbatim draft and a NEAR are not declaration problems, and
routing them to a declaration tool wastes a clean rebuild to learn what two cheap checks already
know.

    tools/recover_route.py .run/gate_main_dropped.json --drafts .run/<wave>/<arm>
    tools/recover_route.py --fn func_X --symbol D_Y --kept "..." --this "..."
"""
import argparse
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, HERE)

SELF, CALLEE, DATA = 'SELF', 'CALLEE', 'DATA'


def symbol_kind(fn, symbol, kept='', this=''):
    """SELF / CALLEE / DATA for the symbol a gate named in a DROP.

    The signature strings are `typesig` tuples rendered by gate_main, e.g.
        function     : ('void', ('void',))          -> a declarator WITH a parameter list
        fn-pointer   : ('s32 (*', ('* void',))      -> an OBJECT whose type is pointer-to-function
        plain data   : ('s16', '[]')                -> no parameter list at all
    A `(*` in the base type is what separates a pointer-to-function OBJECT from a FUNCTION, and it
    is the distinction that decides the tool: `cast_self_callers` casts CALL SITES and is
    meaningless for an object."""
    if symbol == fn:
        return SELF
    blob = '%s %s' % (kept, this)
    looks_callable = ('(' in blob and ')' in blob and '(*' not in blob) or bool(re.search(r'\(\s*\(', blob))
    if looks_callable and symbol.startswith('func_'):
        return CALLEE
    if symbol.startswith('func_') and not blob.strip():
        return CALLEE
    return DATA


def refusal(fn, draft, binary='main', asm_subdir=None):
    """A reason this drop should not be routed to a declaration tool at all, or None."""
    if not draft or not os.path.exists(draft):
        return None
    try:
        import draft_prechecks as DP
        if DP.is_verbatim_asm_draft(open(draft, errors='replace').read(), fn):
            return ("VERBATIM — the draft is the target's own asm in a file-scope __asm__ (§265/§478). "
                    "It is not a decompile, no declaration fix applies, and the gate refuses it for "
                    "free. REDRAFT or accept it as a §265 bank via asm_verbatim.py.")
    except Exception:
        pass
    return None


def route(fn, symbol, kept='', this='', draft=None, binary='main', tu=None):
    """(kind, [ordered commands]) — the ladder to try, cheapest/safest first."""
    stop = refusal(fn, draft)
    if stop:
        return 'REFUSED', [], stop
    kind = symbol_kind(fn, symbol, kept, this)
    d = os.path.dirname(draft) if draft else '<drafts dir>'
    if kind == SELF:
        cmds = [
            "tools/cast_self_callers.py --binary %s --funcs %s --drafts %s --sync-decls --apply "
            "--journal .run/<id>/cast.json" % (binary, fn, d),
            "make check BINARY=%s     # LAW 1: byte-neutral with NO draft substituted" % binary,
            "git commit               # the gate checks out the TUs / pins a worktree",
            "tools/gate_main.py <slate> --apply",
            "tools/cast_self_callers.py --undo-journal .run/<id>/cast.json --keep <banked>",
        ]
        why = ("the clash names the function being banked, so the CALL SITES must change too — "
               "this is the only class §378 covers, and it banked 16 of 16 in S77 (§477).")
    elif kind == CALLEE:
        cmds = [
            "tools/sync_tu_decls.py --binary %s --fn %s --draft %s/%s.c --rounds 6 --apply"
            % (binary, fn, d, fn),
        ]
        why = ("the clash names a DIFFERENT function, so §378 does NOT transfer: cast_self_callers "
               "reads the return type off the draft and cannot cast a callee, and --any-proto would "
               "run unprotected over every call site (S69: 60 decls no-protoed, binary RED). Adopt "
               "the TU's spelling into the DRAFT instead — including from its DEFINITION header.")
    else:
        cmds = [
            "tools/sync_tu_decls.py --binary %s --fn %s --draft %s/%s.c --rounds 6 --apply"
            % (binary, fn, d, fn),
            "tools/scope_demote_drafts.py --overlay %s --in <dir> --out <dir> --src-file %s"
            % (binary, tu or '<tu>.c'),
        ]
        why = ("a DATA symbol: neither tool in gate_main's printed chain touches one. Try adopting "
               "the TU's spelling first; if the draft genuinely needs an incompatible type, demote "
               "it to BLOCK scope — legal because `conflicting types' is a SAME-SCOPE error and "
               "across scopes it is only a warning (§481/§8d). The byte gate decides which.")
    return kind, cmds, why


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("dropped", nargs="?", default=".run/gate_main_dropped.json")
    ap.add_argument("--drafts", default=None, help="dir holding <fn>.c, so the refusal checks can run")
    ap.add_argument("--binary", default="main")
    ap.add_argument("--fn"); ap.add_argument("--symbol")
    ap.add_argument("--kept", default=""); ap.add_argument("--this", default="")
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()

    if a.fn and a.symbol:
        rows = [{"fn": a.fn, "symbol": a.symbol, "kept": a.kept, "this": a.this}]
    else:
        p = a.dropped if os.path.isabs(a.dropped) else os.path.join(REPO, a.dropped)
        if not os.path.exists(p):
            sys.exit("recover_route: no %s — run a gate first (it writes the drop ledger)." % a.dropped)
        rows = json.load(open(p))

    out = []
    for r in rows:
        draft = os.path.join(a.drafts, r["fn"] + ".c") if a.drafts else None
        kind, cmds, why = route(r["fn"], r.get("symbol", ""), r.get("kept", ""), r.get("this", ""),
                                draft=draft, binary=a.binary, tu=r.get("file"))
        out.append({"fn": r["fn"], "symbol": r.get("symbol"), "kind": kind, "why": why, "cmds": cmds})

    if a.json:
        print(json.dumps(out, indent=1)); return 0
    for o in out:
        print("\n%-16s %-14s clash on %s" % (o["fn"], o["kind"], o["symbol"]))
        print("   why: %s" % o["why"])
        for c in o["cmds"]:
            print("     %s" % c)
    if out:
        print("\n%d drop(s) routed. The byte gate remains the sole arbiter — a route is the order to "
              "TRY, never a prediction of which one wins." % len(out))
    return 0


if __name__ == "__main__":
    sys.exit(main())

#!/usr/bin/env python3
"""sync_tu_decls.py — bank a draft the gate refuses by copying the TU's OWN declarations into it.

WHY THIS EXISTS (P31 S76). The dominant reason a byte-correct draft does not bank is not codegen —
it is that the draft and its destination TU spell a shared symbol differently, and gcc-2.7.2 rejects
the redeclaration. `gate_main`'s pre-check already NAMES the offending symbol and which side it kept:

    DROP func_8005EC00: D_800729DC clashes with the TU itself in src/800c3.c
                        kept=('u32','')  this=('void*','')

That is a complete instruction. The TU holds the authoritative spelling (it is what the rest of the
binary compiles against); the draft's guess does not. So the fix needs no judgement at all: copy the
TU's `extern` line verbatim into the draft, re-gate, and repeat for whatever it names next.

MEASURED. Done by hand this session it banked `func_8005EB28` in one round and `func_8005EC00` in
two — both had been stuck across multiple slates, and both are byte-identical afterwards. The
conflicts are usually a CASCADE: banking one function gives the TU a real definition, which then
contradicts the stale `extern` every later draft in that TU still carries. Every bank changes the
declaration environment for every draft that follows it.

WHAT IT DOES NOT DO. It only resolves conflicts where the TU already declares the symbol. A draft
whose OWN signature disagrees with the TU (`self_decl_tu` — the TU declares the function being
banked) needs `cast_self_callers --sync-decls`, because the call SITES must change too. This tool
refuses that class loudly rather than mangling it (R43).

THE BYTE GATE REMAINS THE SOLE ARBITER (G3/P9): every round ends in a real gate run, and a draft that
stops conflicting but does not match is reported as a mismatch, never as a bank.

    tools/sync_tu_decls.py --binary main --fn func_8005EC00 --draft <path> [--rounds 6] [--apply]
"""
import argparse
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = os.path.join(REPO, ".venv/bin/python")
if not os.path.exists(PY):
    PY = sys.executable

DROP_RE = re.compile(r"DROP \S+: (?P<sym>[A-Za-z_]\w*) clashes with (?P<side>the TU itself|an earlier draft)"
                     r" in (?P<tu>\S+)")
# The gate reports a conflict TWO ways and this tool must read both (P31 S76): the slate-load
# pre-check emits `DROP … clashes with …`, but a conflict only the compiler sees arrives after the
# build as `COMPILE conflict on `SYM' at FILE:LINE`. Handling only the first left five drafts
# looking unrecoverable when their blocker was the same class, one symbol deeper.
COMPILE_RE = re.compile(r"COMPILE conflict on `(?P<sym>[A-Za-z_]\w*)' at (?P<tu>[^:]+):\d+")


def tu_decl(tu_path, sym):
    """The TU's own `extern … sym …;` line, verbatim — the authoritative spelling."""
    pat = re.compile(r"^\s*extern\b[^;\n]*\b%s\b[^;\n]*;\s*$" % re.escape(sym), re.M)
    try:
        m = pat.search(open(os.path.join(REPO, tu_path), errors="replace").read())
    except OSError:
        return None
    return m.group(0).strip() if m else None


def replace_decl(text, sym, decl):
    """Swap the draft's declaration of `sym` for the TU's. Returns (text, changed)."""
    pat = re.compile(r"^\s*extern\b[^;\n]*\b%s\b[^;\n]*;\s*$" % re.escape(sym), re.M)
    if not pat.search(text):
        return text, False
    return pat.sub(decl, text, count=1), True


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary", required=True)
    ap.add_argument("--fn", required=True)
    ap.add_argument("--draft", required=True)
    ap.add_argument("--rounds", type=int, default=6)
    ap.add_argument("--apply", action="store_true",
                    help="actually gate (and therefore bank on success); without it, only report "
                         "which declarations would be synced")
    a = ap.parse_args()

    if a.binary != "main":
        sys.exit("sync_tu_decls: only `main` is supported — main is the binary whose gate names the "
                 "conflicting symbol. For an overlay use gate_stage + cast_self_callers (R43: "
                 "refusing an input this tool cannot handle rather than mishandling it).")

    # A DECLARATION FIX CANNOT RESCUE A BODY THAT DIFFERS (P31 S76). Five of the first sixteen
    # candidates compiled once their declarations were synced and then failed the byte gate — they
    # were NEARs all along (closeness 12-89), and a `CC1-FAIL` classification only says the
    # declaration blocked COMPILATION, never that the body underneath is correct. Check the body
    # first so a gate is not spent learning what match_one already knows (R37: probe before costing).
    # PASS --asm-subdir OR THE ORACLE JUDGES A DIFFERENT FUNCTION (§238). match_one defaults to
    # `asm/resident/nonmatchings/resident` and says so in a warning; without the subdir this guard
    # scored the wrong target, returned no verdict, and let a NEAR through — the exact hazard the
    # guard exists to catch, in the guard itself. Derive it from the stub oracle.
    sys.path.insert(0, os.path.join(REPO, "tools"))
    import corpus
    _hit = [v for v in corpus.stubs(a.binary).values() if v.symbol == a.fn]
    if not _hit:
        sys.exit("sync_tu_decls: %s is not an open stub in %s — nothing to bank." % (a.fn, a.binary))
    _mo = subprocess.run([PY, os.path.join(REPO, "tools/match_one.py"), a.fn, "--c", a.draft,
                          "--json", "--asm-subdir", _hit[0].asm_dir],
                         cwd=REPO, capture_output=True, text=True)
    try:
        _cl = json.loads(_mo.stdout.strip().splitlines()[-1]).get("closeness")
    except Exception:
        _cl = None
    if _cl not in (0, None):
        sys.exit("sync_tu_decls: REFUSED — %s is a NEAR (closeness %s). Syncing declarations makes "
                 "it COMPILE, not MATCH; the byte gate would reject it anyway. Fix the body first."
                 % (a.fn, _cl))

    work = os.path.join(REPO, ".run", "sync_tu_decls", a.fn)
    os.makedirs(work, exist_ok=True)
    draft = os.path.join(work, a.fn + ".c")
    with open(a.draft, errors="replace") as fh:
        open(draft, "w").write(fh.read())
    slate = os.path.join(work, "slate.json")
    json.dump([{"fn": a.fn, "draft": draft}], open(slate, "w"))

    synced = []
    for rnd in range(1, a.rounds + 1):
        r = subprocess.run([PY, os.path.join(REPO, "tools/gate_main.py"), slate]
                           + (["--apply"] if a.apply else []),
                           cwd=REPO, capture_output=True, text=True,
                           env={**os.environ, "GATE_MAIN_MAX_STEPS": "6"})
        out = (r.stdout or "") + (r.stderr or "")
        if re.search(r"^BANKED [1-9]", out, re.M):
            print("BANKED %s after %d declaration sync(s): %s"
                  % (a.fn, len(synced), ", ".join(synced) or "none"))
            return 0
        m = DROP_RE.search(out) or COMPILE_RE.search(out)
        if not m:
            # No conflict left to fix — the residual is a real mismatch or another class entirely.
            tail = [l for l in out.splitlines()
                    if re.search(r"BANKED|STILL MISMATCHED|COMPILE conflict|REFUSED", l)]
            print("no declaration conflict named; stopping after %d sync(s)." % len(synced))
            for l in tail[:3]:
                print("   ", l.strip())
            return 1
        sym, tu = m.group("sym"), m.group("tu")
        side = m.groupdict().get("side") or "the TU itself"
        if sym == a.fn:
            print("REFUSED: the conflict is on %s ITSELF (self_decl_tu) — the TU declares the "
                  "function being banked, so the CALL SITES must change too. That is "
                  "cast_self_callers --sync-decls, not this tool." % sym)
            return 2
        decl = tu_decl(tu, sym)
        if not decl:
            print("stopping: %s clashes with %s but %s has no `extern` line to copy."
                  % (sym, side, tu))
            return 1
        txt, changed = replace_decl(open(draft, errors="replace").read(), sym, decl)
        if not changed:
            print("stopping: the draft has no declaration of %s to replace." % sym)
            return 1
        open(draft, "w").write(txt)
        synced.append(sym)
        print("round %d: %s  ->  %s" % (rnd, sym, decl))

    print("gave up after %d rounds (%d synced)." % (a.rounds, len(synced)))
    return 1


if __name__ == "__main__":
    sys.exit(main())

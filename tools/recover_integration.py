#!/usr/bin/env python3
"""recover_integration.py — Phase-24 T6 batch integration-recovery for leaf-MATCH-but-gate-rejected fns.

A wave logs many functions as `match_one` MATCH (byte-correct body) yet whole-binary-gate REJECTED —
"declaration/TU plumbing". The gate_stage pipeline (canon_resident_calls -> cast_call_sites ->
sig_unify) recovers the CALLEE-side conflicts, but NOT the dominant residual: a CALLER (in
engine_core.h OR the overlay's OWN inline src) declares the banked fn with a conflicting prototype
(`extern void func_X(void)` / a narrower arg type) vs the real def. gcc: `conflicting types for
func_X`. (Proven this phase on func_8014E048 (s16*->u16*) + the flagship straggler ov_SC02_005.)

THE MISSING STEP: `fix_arity_callers --any-proto --binary <bin>` (extended T6 to scan the overlay src,
not just engine_core.h) no-protos every conflicting caller decl -> compatible with any promotion-safe
def, byte-NEUTRAL (the call emits identical code). Then gate_stage banks + propagates. This driver
batches it and REVERTS the caller edits for anything that doesn't bank (so the shared header/src carry
no-proto only where it bought a match). The whole-binary byte-gate is the sole arbiter (G3/P9).

  recover_integration.py [--auto | --funcs f,g | --from-file L] [--binary ov_SC01_077]
                         [--limit N] [--commit] [--no-propagate]

--auto pulls leaf-MATCH candidates from the backlog (status capped / near-close-0, reach>=2), filtered
to those STILL a stub in the binary AND STILL match_one-MATCH on their best draft (drift-safe, R14).
"""
import argparse, glob, json, os, re, shutil, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import backlog, gate_stage

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = ".venv/bin/python"


def sh(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, **kw)


def stub_map(binary):
    """{func_<ADDR>: (src_rel, asm_subdir)} for every INCLUDE_ASM stub across this binary's split .c
    files (main + _a/_o0/_o0b/_after). The asm subdir is read from the stub LINE, so a fn in a split
    (the post-whale _after region — 263 of ov_SC01_077's stubs) is drift-checked + gated against its
    OWN .s/.c. Fixes the §39 split gap that made --auto silently skip every split-file candidate."""
    m = {}
    for cf in sorted(glob.glob(os.path.join(REPO, f"src/{binary}/{binary}*.c"))):
        rel = os.path.relpath(cf, REPO)
        for asm_sub, fn in re.findall(r'INCLUDE_ASM\("([^"]+)",\s*(func_[0-9A-Fa-f]+)\)', open(cf).read()):
            m[fn] = (rel, asm_sub)
    return m


def auto_candidates(binary, limit):
    """leaf-MATCH-but-unbanked candidates from the backlog, drift-checked against current src + drafts."""
    seen = {}
    for r in backlog.load_best():
        if r.get("name"):
            seen[r["name"]] = r
    smap = stub_map(binary)
    out = []
    for r in sorted(seen.values(), key=lambda r: -(r.get("reach") or 0)):
        fn = r.get("name"); d = r.get("best_draft")
        if fn not in smap or not d or not os.path.exists(os.path.join(REPO, d)):
            continue
        if (r.get("reach") or 0) < 2 or r.get("closeness") not in (0, None):
            continue
        # drift-check: still a leaf MATCH on the recorded draft? (per-fn asm subdir -> split-aware)
        rr = sh([PY, "tools/match_one.py", fn, "--c", d, "--asm-subdir", smap[fn][1]], timeout=180)
        if (rr.stdout.strip().splitlines() or ["?"])[0].startswith("MATCH"):
            out.append((fn, d))
        if len(out) >= limit:
            break
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--auto", action="store_true", help="pull leaf-MATCH candidates from the backlog")
    ap.add_argument("--funcs", help="comma-separated func_XXXX list (their best_draft is used)")
    ap.add_argument("--from-file", help="file with one func_XXXX per line")
    ap.add_argument("--binary", default="ov_SC01_077")
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--no-propagate", action="store_true")
    a = ap.parse_args()
    os.chdir(REPO)

    # ---- assemble the (fn, draft) work list
    seen = {r["name"]: r for r in backlog.load_best() if r.get("name")}
    work = []
    if a.auto:
        work = auto_candidates(a.binary, a.limit)
    else:
        names = []
        if a.funcs:
            names += [x.strip() for x in a.funcs.split(",") if x.strip()]
        if a.from_file:
            names += [l.strip() for l in open(a.from_file) if l.strip()]
        for fn in names:
            d = (seen.get(fn) or {}).get("best_draft")
            if d and os.path.exists(d):
                work.append((fn, d))
    if not work:
        print("no candidates"); return
    fns = [fn for fn, _ in work]
    print(f"[recover] {len(fns)} candidate(s): {', '.join(fns[:8])}{'…' if len(fns) > 8 else ''}")

    # ---- stage drafts
    dd = ".run/recover_drafts"
    shutil.rmtree(os.path.join(REPO, dd), ignore_errors=True)
    os.makedirs(os.path.join(REPO, dd))
    for fn, d in work:
        shutil.copy(os.path.join(REPO, d), os.path.join(REPO, dd, fn + ".c"))

    # ---- snapshot the TU files (engine_core.h + the overlay's own src). Restored EXACTLY between
    # passes — `fix_arity_callers --revert` is LOSSY for --any-proto (it rewrites `()`->`(void)`, not
    # back to the original `(a,b,c)`), which corrupts a non-bank whose caller passed args. So we
    # snapshot/restore verbatim instead. (Bug caught by the clean-rebuild verify, R22.)
    tu_files = [os.path.join(REPO, "src/shared/engine_core.h")] + \
        sorted(glob.glob(os.path.join(REPO, f"src/{a.binary}/{a.binary}*.c")))
    snapshot = {f: open(f).read() for f in tu_files}

    def restore():
        for f, t in snapshot.items():
            open(f, "w").write(t)

    listf = os.path.join(REPO, ".run/recover_fns.txt")

    smap = stub_map(a.binary)

    def reconcile_and_gate(targets, propagate, commit):
        """no-proto the targets' conflicting caller decls, then gate each SPLIT-file group separately —
        harvest_verify substitutes into ONE --src/--asm-subdir per call, so _after/_a/_o0 drafts must be
        gated against their own split (§39). run_gate self-filters the drafts dir to each split's stubs;
        its per-group propagate is idempotent (dedup_propagate skips registered addrs)."""
        open(listf, "w").write("\n".join(targets) + "\n")
        r = sh([PY, "tools/fix_arity_callers.py", "--apply", "--any-proto", "--binary", a.binary,
                "--from-file", ".run/recover_fns.txt", "--drafts", dd])
        print("  " + (r.stdout.strip().splitlines()[-1] if r.stdout.strip() else "(fix_arity_callers: no output)"))
        groups = sorted({smap[fn] for fn in targets if fn in smap})
        verified, fleet, propagated = [], None, 0
        for src_rel, asm_sub in groups:
            s = gate_stage.run_gate(dd, binary=a.binary, src=src_rel, asm=asm_sub, src_file=src_rel,
                                    source_tag="t6-recover", propagate=propagate, commit=commit)
            verified += s.get("verified", [])
            propagated += (s.get("propagated") or 0)
            fleet = s.get("fleet_pct", fleet)
        return {"verified": verified, "fleet_pct": fleet, "propagated": propagated}

    # ---- PASS 1: reconcile+gate ALL candidates (no propagate) to find the bankable set.
    print("[recover] pass 1 — find bankable set")
    s1 = reconcile_and_gate(fns, propagate=False, commit=False)
    banked = sorted(s1.get("verified", []))
    print(f"[recover] pass 1 banked {len(banked)}/{len(fns)}")
    restore()   # exact — undo pass-1's caller edits AND the substituted defs

    if not banked:
        print(json.dumps({"banked": [], "propagated": 0, "fleet": s1.get("fleet_pct")})); return

    # ---- PASS 2: from the clean snapshot, reconcile+gate ONLY the winners (so no non-bank corruption),
    # then propagate. This is the state that gets committed.
    print("[recover] pass 2 — re-bank winners + propagate")
    # stage only the winners' drafts
    for p in glob.glob(os.path.join(REPO, dd, "*.c")):
        if os.path.basename(p)[:-2] not in banked:
            os.remove(p)
    s2 = reconcile_and_gate(banked, propagate=not a.no_propagate, commit=a.commit)
    banked2 = sorted(s2.get("verified", []))
    print(f"[recover] pass 2 banked {len(banked2)}/{len(banked)}  propagated groups +{s2.get('propagated')}  "
          f"fleet {s2.get('fleet_pct')}%")
    print(json.dumps({"banked": banked2, "propagated": s2.get("propagated"), "fleet": s2.get("fleet_pct")}))


if __name__ == "__main__":
    main()

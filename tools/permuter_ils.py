#!/usr/bin/env python3
"""permuter_ils.py — iterated-local-search wrapper over decomp-permuter (Phase 24 T7 §G).

A COLD `run_masked` plateaus at the base score over ~10k iters, but WARM-RESTARTING base.c from the
best byte-waypoint each cycle (fresh -j) descends where cold stalls (proven on func_80148094: 72 -> 36
over ~8 restarts; the big drops come from FRESH restarts, not continuing a plateaued run). The final
score-0 hit is a CANDIDATE — bank it only through the whole-binary byte-gate (harvest_verify), since
intermediate waypoints can be semantically divergent (the permuter rewrites stores for byte-proximity).

  python3 tools/permuter_ils.py func_80148094 --draft .run/t7b/close/func_80148094.c \
      --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077 --klass REGALLOC --cycles 10 --secs 180 --j 12
On a score-0 winner -> .run/permuter-winners/<fn>.c (then winner_to_draft + gate whole-binary).
"""
import argparse, functools, glob, os, re, shutil, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import p16_permute as P

# stdout is BUFFERED when redirected to a log; an 8-cycle run then shows an EMPTY log for 20 minutes
# (S80: eight parallel runs, no evidence of progress -- R55). Always flush.
print = functools.partial(print, flush=True)


def best_waypoint(pd):
    """(score, dir) of the lowest-score output-<score>-<n>/source.c across ALL cycles; None if none.
    output-0-* is the true byte-match; output-<N>-* are intermediate bests (masked-diff score N)."""
    cands = []
    for d in glob.glob(f"{pd}/output-*"):
        m = re.match(r"output-(\d+)-", os.path.basename(d))
        if m and os.path.exists(os.path.join(d, "source.c")):
            cands.append((int(m.group(1)), d))
    return sorted(cands)[0] if cands else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("fn")
    ap.add_argument("--draft", required=True, help="seed C draft (externs + def)")
    ap.add_argument("--asm-subdir", default=P.ASM)
    ap.add_argument("--klass", default="REGALLOC")
    ap.add_argument("--cycles", type=int, default=10)
    ap.add_argument("--secs", type=int, default=180, help="per-cycle time box")
    ap.add_argument("--j", type=int, default=12)
    ap.add_argument("--winners", default=".run/permuter-winners")
    ap.add_argument("--pd", help="scratch dir for this run (default .run/permuter/<fn>) — key it by alias+fn when "
                                 "several runs share a function NAME (R48)")
    a = ap.parse_args()

    draft = open(a.draft).read()
    pd = P.setup(a.fn, draft, asm_subdir=a.asm_subdir, klass=a.klass, outdir=a.pd)
    if not pd:
        print("ILS setup FAILED (target .s didn't assemble?)"); sys.exit(1)
    print(f"ILS {a.fn}: {a.cycles} cycles x {a.secs}s @ -j{a.j}, klass={a.klass}")

    prev = None
    refused = os.path.join(pd, "PERMUTER_REFUSED.txt")
    for cyc in range(1, a.cycles + 1):
        if os.path.exists(refused):
            os.remove(refused)
        P.run_permuter(pd, a.secs, a.j)              # writes output-*/ ; kills stragglers
        if os.path.exists(refused):
            # NOT-JUDGED IS NOT A VERDICT (R61a). A refused cycle permuted nothing; reporting it as
            # "(unchanged)" for the remaining cycles is how S79's func_80020DA4 run showed 8 cycles of
            # work that were 1 cycle + 7 no-ops. Stop, say so, exit non-zero.
            print(f"ILS ABORTED at cycle {cyc}: the permuter REFUSED base.c (see {refused}); "
                  f"best so far={prev}")
            sys.exit(2)
        bw = best_waypoint(pd)
        if bw is None:
            print(f"  cycle {cyc}: no waypoint (no improvement over base yet)")
            continue
        score, d = bw
        tag = " (unchanged)" if prev is not None and score >= prev else ""
        print(f"  cycle {cyc}: best score = {score}{tag}  [{os.path.basename(d)}]")
        if score == 0:
            os.makedirs(a.winners, exist_ok=True)
            dst = os.path.join(a.winners, a.fn + ".c")
            shutil.copy(os.path.join(d, "source.c"), dst)
            print(f"  WINNER score 0 -> {dst}  (gate whole-binary before banking)")
            return
        # WARM RESTART. The permuter DECODES the b64 pragma carrier when it serializes a candidate, so a
        # waypoint's source.c holds the raw `register … __asm__("$N")` pins / `__asm__` statements again.
        # Copying it verbatim made every cycle after the first a parser refusal on any pinned seed
        # (P31 S79: func_80020DA4 = 1 real cycle + 7 silent no-ops). Re-hide before restarting, and assert
        # the function definition survived the re-hide (R32).
        wp = P.hide_asm(open(os.path.join(d, "source.c")).read())
        if not P.defines_fn(wp, a.fn):
            print(f"ILS ABORTED at cycle {cyc}: re-hiding the waypoint lost the definition of {a.fn} "
                  f"(inspect {d}/source.c)"); sys.exit(2)
        open(f"{pd}/base.c", "w").write(wp)
        prev = score
    print(f"ILS done: best={prev} (no score-0; seed for Fable5 or a longer run)")


if __name__ == "__main__":
    main()

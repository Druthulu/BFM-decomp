#!/usr/bin/env python3
"""sweep_parallel.py — gate PRE-STAGED draft dirs across DISTINCT binaries in parallel.

WHY THIS EXISTS. `bulk_harvest` already contains exactly the right gate farm (Phase B: a
ProcessPoolExecutor over distinct binaries, per-binary flock, per-worker result files,
compute_fleet=False), but it is welded to Phase A — LLM drafting via `lora_grind`/`api_draft`. Every
FAMILY sweep produces its drafts a completely different way (`family_sweep --stage-only`, which
templates a matched exemplar onto its siblings), so the farm was unreachable from that path.

Consequence, measured in Phase-29 SESSION-20: every family sweep that session ran SERIALLY —
`for ov in …; do gate_stage …; done` — for 389, 268 and 104 members respectively. On a 32-thread box
that is roughly an 8-16x throughput loss, and it was not an architectural limit; the parallel tool
simply was not reachable from the staging path. This adapter closes that gap. It adds NO new gate
logic: it calls the same `gate_stage.run_gate` with the same per-binary lock discipline.

SAFETY — the invariants that make parallel gating sound here, all pre-existing:
  * DISTINCT binaries only. Each worker takes `.run/auto/gate.<bin>.lock`, and `build/<bin>/**` trees
    are isolated, so two binaries never race. Two workers on the SAME binary is the thing the lock
    prevents; this driver never schedules that (one job per binary).
  * propagate=False, commit=False — the caller owns propagation and commits (§55b's law: gate with
    --no-propagate per group, commit, THEN one targeted dedup_propagate).
  * compute_fleet=False in the workers; the fleet % is a serial tail computation.
  * The whole-binary byte-gate remains the sole arbiter (G3/P9). Parallelism changes THROUGHPUT, not
    the verdict — a wrong draft is still reverted by its own binary's gate.
  * A shared-state stage (the ARITY pre-pass, a type-lift) is NOT binary-local. Run
    `tools/blast_radius.py` after any sweep: if it reports T2, the per-binary gates were necessary
    but NOT sufficient and R22 is mandatory (§63/§85).

  tools/sweep_parallel.py --drafts .run/sweep -j 12
  tools/sweep_parallel.py --drafts .run/sweep -j 12 --only ov_SC01_000,ov_SC01_001
"""
import argparse
import glob
import os
import sys
from concurrent.futures import ProcessPoolExecutor, as_completed

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
import backlog          # noqa: E402
import gate_stage       # noqa: E402

BULK = ".run/auto/bulk"


def _worker(job):
    """Gate ONE binary's pre-staged drafts. Forked child: per-worker backlog + result paths so
    workers never cross-read, per-binary lock so distinct binaries do not serialize."""
    b = job["binary"]
    os.makedirs(os.path.join(REPO, BULK), exist_ok=True)
    backlog.JSONL = os.path.join(BULK, "%s.backlog.jsonl" % b)
    backlog.MD = os.path.join(BULK, "%s.backlog.md" % b)
    try:
        r = gate_stage.run_gate(
            job["draftdir"], binary=b, propagate=False, commit=False,
            source_tag="sweep-parallel", lock_path=".run/auto/gate.%s.lock" % b,
            verified_out="%s/%s.verified.txt" % (BULK, b),
            failed_out="%s/%s.failed.txt" % (BULK, b),
            compute_fleet=False)
        return {"binary": b, "banked": r.get("verified", []), "drafts": r.get("drafts", 0)}
    except Exception as e:                       # a worker crash must not be silent (R32)
        return {"binary": b, "banked": [], "drafts": 0, "error": repr(e)}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--drafts", default=".run/sweep",
                    help="dir of per-binary draft dirs: <drafts>/<binary>/func_*.c")
    ap.add_argument("-j", "--jobs", type=int, default=12)
    ap.add_argument("--only", default=None, help="comma-separated binaries to gate")
    a = ap.parse_args()
    os.chdir(REPO)

    only = set(a.only.split(",")) if a.only else None
    jobs, skipped, refused_main = [], [], []
    for d in sorted(glob.glob(os.path.join(a.drafts, "*"))):
        if not os.path.isdir(d):
            continue
        b = os.path.basename(d)
        # A real binary has a splat config (R33/R36). This ALSO filters gate_stage's own intermediate
        # ladder dirs (-cn/-cast/-rc/-s2in/-uni), which a bare glob picks up as if they were binaries
        # — the phantom-PARTIAL bug measured in SESSION-20.
        # MAIN IS NOT GATEABLE HERE, AND SILENTLY TRYING IS WORSE THAN REFUSING.
        #
        # gate_stage builds INCREMENTALLY. main's `make extract` runs psyq_integrate +
        # ld_interleave, which REWRITE the linker script, so an incremental build after a source
        # change re-runs that on an already-rewritten .ld and yields a FALSE DIFF (gate_main.py's
        # docstring documents the night this cost). This driver accepted main anyway — the
        # `"us.exe" if b == "main"` branch below was written to LET IT IN — so every main draft
        # that reached here was gated by a path that cannot bank it. Measured P31 S58: wave `ab`
        # drew 105 main cards and banked 0 of 105, while its 115 non-main cards banked 94 (82%).
        # The drafts were fine. Route main to tools/gate_main.py (one clean rebuild per BATCH).
        if b == "main":
            refused_main.append(b); continue
        if not os.path.exists("config/splat.%s.yaml" % b):
            skipped.append(b); continue
        if only and b not in only:
            continue
        if not glob.glob(os.path.join(d, "*.c")):
            continue
        jobs.append({"binary": b, "draftdir": d})

    if skipped:
        print(f"skipped {len(skipped)} non-binary dirs (ladder scratch): {', '.join(skipped[:6])}"
              f"{' …' if len(skipped) > 6 else ''}")
    if refused_main:
        print("REFUSED: main drafts were staged here. main cannot be gated incrementally — "
              "route them to tools/gate_main.py. Nothing was gated for main.")
    print(f"gating {len(jobs)} binaries with -j {a.jobs}")

    banked = failed = 0
    with ProcessPoolExecutor(max_workers=a.jobs) as ex:
        futs = {ex.submit(_worker, j): j["binary"] for j in jobs}
        for i, f in enumerate(as_completed(futs), 1):
            r = f.result()
            n = len(r["banked"])
            banked += n
            failed += max(0, r["drafts"] - n)
            if r.get("error"):
                print(f"  [{i}/{len(jobs)}] {r['binary']}: ERROR {r['error']}")
            elif n < r["drafts"]:
                print(f"  [{i}/{len(jobs)}] {r['binary']}: {n}/{r['drafts']}")
    print(f"\nSWEEP DONE: banked={banked} notbanked={failed} over {len(jobs)} binaries")
    print("NEXT: tools/blast_radius.py — if it reports T2, R22 is MANDATORY (§63/§85).")
    return 0


if __name__ == "__main__":
    sys.exit(main())

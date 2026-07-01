#!/usr/bin/env python3
"""bulk_harvest.py — Phase 23 T10: the phase-separated + parallel-gate harvester (the saturation factory).

Rebuilds the LLM harvest for THROUGHPUT. lora_grind interleaves draft->gate PER binary, which
serializes the whole-binary byte-gate AND idles the GPU during every ~30s gate. bulk_harvest phase-
separates so the GPU and the 16 cores each run flat-out in their own phase:

  A. BULK-DRAFT (GPU, serial)    — draft every fresh <=N-ins stub across the target binaries in ONE
                                   api_draft pass (GPU busy continuously; reuses lora_grind.draft).
                                   (vLLM batched serving, the next lever, drops in here unchanged —
                                   same OpenAI endpoint — and is what makes THIS phase fast.)
  B. BULK-GATE (CPU, parallel)   — ProcessPoolExecutor over DISTINCT binaries; each worker byte-gates
                                   its binary's drafts via gate_stage.run_gate(propagate=False,
                                   commit=False, per-binary lock, per-worker scratch, compute_fleet=
                                   False). build/<bin>/** + src/<bin>/*.c are per-binary isolated, so
                                   distinct-binary builds never collide; propagation (the ONLY writer
                                   of the shared engine_core.h / overlay .c) is deferred to phase C.
  C. DEDUPE + COMMIT (serial)    — dedup_propagate --auto-from each binary that banked a reach>=2 fn
                                   (the x reach multiplier), merge the per-worker backlogs, ONE commit.

The whole-binary byte-gate (gate_stage/harvest_verify, G3/P9) is the sole arbiter — a wrong draft can
NEVER bank (it reverts to the INCLUDE_ASM stub). The model only affects THROUGHPUT, never correctness.
On-demand + bounded (STOP sentinel); NOT a 24/7 daemon. lora_grind.py stays the serial fallback.

One phase-separated cycle per invocation (draft --count -> parallel-gate -> dedupe -> commit -> exit);
each fn is drafted once and marked in the shared .run/auto/lora_grind_tried.json, so re-invoking picks
fresh untried stubs (RESUMABLE). A large campaign = loop the invocation.

Usage:
  API_BASE=http://127.0.0.1:1234/v1 MODEL=bfm-match-7b-v3 \
    tools/bulk_harvest.py --binary-glob 'ov_SC03_*' --count 80 --workers 8 --measure
"""
import argparse, fnmatch, glob, json, multiprocessing, os, re, shutil, subprocess, sys, time
from concurrent.futures import ProcessPoolExecutor, as_completed

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lora_grind as lg
import gate_stage
import backlog

REPO = lg.REPO
PY = ".venv/bin/python"
AUTODIR = os.path.join(REPO, ".run/auto")
BULK = os.path.join(AUTODIR, "bulk")                 # per-binary draft subdirs + per-worker scratch
STOP = lg.STOP
HB = os.path.join(AUTODIR, "bulk_harvest_heartbeat.json")
STATS = os.path.join(AUTODIR, "bulk_harvest_stats.json")


def log(m):
    print("[bulk_harvest] " + m, flush=True)


def sh(cmd, timeout=None):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)


def endpoint_up(api_base):
    """Cheap GET /models so a dead server fails LOUD (else every draft returns None -> silent 0 banked)."""
    import urllib.request
    try:
        urllib.request.urlopen(api_base.rstrip("/") + "/models", timeout=10).read()
        return True
    except Exception:
        return False


# ---- Phase B worker (top-level so ProcessPoolExecutor can pickle it; fork inherits module state) ----
def _gate_worker(job):
    """Byte-gate ONE binary's drafts (main .c + any _a/_o0 split). Runs in a forked child: point the
    backlog + harvest result files at PER-WORKER paths so parallel workers never cross-read, take a
    PER-BINARY lock so distinct binaries don't serialize, propagate=False/commit=False (phase C owns
    those), compute_fleet=False (phase C computes it once). Returns {binary, banked:[...], drafts:int}."""
    b = job["binary"]
    backlog.JSONL = os.path.join(BULK, "%s.backlog.jsonl" % b)   # module-global read at call time
    backlog.MD = os.path.join(BULK, "%s.backlog.md" % b)
    vout, fout = ".run/auto/bulk/%s.verified.txt" % b, ".run/auto/bulk/%s.failed.txt" % b
    lock = ".run/auto/gate.%s.lock" % b
    common = dict(binary=b, good_sha=job["good_sha"], propagate=False, commit=False,
                  source_tag="bulk-harvest", lock_path=lock, verified_out=vout, failed_out=fout,
                  compute_fleet=False)
    banked, drafts = [], 0
    r = gate_stage.run_gate(job["draftdir"], **common)
    banked += r.get("verified", []); drafts = max(drafts, r.get("drafts", 0))
    for src, asm, src_file in job["splits"]:            # split-file gate (only ov_SC01_077 today; no-op for SC03)
        r = gate_stage.run_gate(job["draftdir"], src=src, asm=asm, src_file=src_file, **common)
        banked += r.get("verified", [])
    return {"binary": b, "banked": banked, "drafts": drafts}


def select_binaries(a):
    bins = lg.binaries()
    if a.binaries:
        only = set(a.binaries.split(","))
        bins = [b for b in bins if b in only]
    if a.binary_glob:
        bins = [b for b in bins if fnmatch.fnmatch(b, a.binary_glob)]
    return bins


def pick_targets(bins, a, tried):
    """Fresh open <=max-nins stubs across `bins`, DEDUPED by fn name to its representative gate site
    (a reach>=2 fn is gated once there, then propagated x reach in phase C; a reach-1 fn's only site is
    its own overlay). ROUND-ROBIN across binaries (one per binary per pass) so the batch SPREADS —
    otherwise --count would fill from one overlay and phase B would gate with a single worker. Capped
    at --count."""
    queues = []
    for b in bins:
        stubs = lg.open_stubs(b, a.max_nins, tried, a.min_reach, a.min_nins)
        if stubs:
            queues.append((b, iter(stubs)))
    seen, picked, active = set(), [], queues
    while active and (not a.count or len(picked) < a.count):
        nxt = []
        for b, it in active:
            t = next(it, None)
            while t is not None and t["name"] in seen:      # a reach>=2 fn already claimed by an earlier binary
                t = next(it, None)
            if t is None:
                continue                                     # binary exhausted -> drop from the rotation
            seen.add(t["name"])
            picked.append(dict(t, binary=b))
            nxt.append((b, it))
            if a.count and len(picked) >= a.count:
                return picked
        active = nxt
    return picked


def split_drafts_by_binary(picked, drafts_dir):
    """Copy each drafted <fn>.c from the flat draft dir into .run/auto/bulk/<binary>/ so each worker's
    run_gate sees ONLY its binary's stubs (avoids the negative-control warning + cross-banking).
    Returns the count actually staged (== drafts that api_draft produced)."""
    staged = 0
    for t in picked:
        src = os.path.join(drafts_dir, t["name"] + ".c")
        if not os.path.exists(src):
            continue                                    # api_draft produced nothing for this fn -> skip
        bd = os.path.join(BULK, t["binary"])
        os.makedirs(bd, exist_ok=True)
        shutil.copy(src, os.path.join(bd, t["name"] + ".c"))
        staged += 1
    return staged


def build_jobs(picked):
    jobs = []
    for b in sorted(set(t["binary"] for t in picked)):
        bd = os.path.join(BULK, b)
        if not glob.glob(os.path.join(bd, "*.c")):
            continue
        splits = []
        for sp in glob.glob(os.path.join(REPO, "src/%s/%s_*.c" % (b, b))):
            name = os.path.basename(sp)[:-2]            # ov_SC01_077_a / _o0
            sub = "asm/%s/nonmatchings/%s" % (b, name)
            if os.path.isdir(os.path.join(REPO, sub)):
                splits.append(("src/%s/%s.c" % (b, name), sub, name + ".c"))
        jobs.append({"binary": b, "draftdir": os.path.relpath(bd, REPO),
                     "good_sha": lg.good_sha(b), "splits": splits})
    return jobs


def merge_backlogs():
    """Fold each worker's per-binary backlog JSONL into the main .run/backlog.jsonl, then render once
    (the main process kept the default backlog paths; only the forked workers were redirected)."""
    n = 0
    for p in glob.glob(os.path.join(BULK, "*.backlog.jsonl")):
        with open(p) as f:
            lines = [l for l in f if l.strip()]
        if lines:
            with open(backlog.JSONL, "a") as out:
                out.writelines(lines)
            n += len(lines)
    if n:
        backlog.render()
    return n


def fleet_pct():
    try:
        r = sh([PY, "tools/progress.py", "--fleet"], timeout=180)
        m = re.search(r"byte-identical\s+:\s+\d+\s*/\s*\d+\s*=\s*([\d.]+)%", r.stdout)
        return float(m.group(1)) if m else None
    except Exception:
        return None


def git_commit(banked_by_bin, propagated, fp):
    add = ["src/shared/engine_core.h", "src/shared/engine_types.h", "config/dedup.us.yaml"]
    for b in banked_by_bin:
        add += [os.path.relpath(p, REPO) for p in glob.glob(os.path.join(REPO, "src/%s/%s*.c" % (b, b)))]
    add += [os.path.relpath(p, REPO) for p in glob.glob(os.path.join(REPO, "src/ov_*/*.c"))]  # propagation
    sh(["git", "add"] + sorted(set(add)))
    total = sum(len(v) for v in banked_by_bin.values())
    msg = "feat(%s): bulk_harvest — +%d fns across %d binaries, %d propagated (fleet %s%%)" % (
        os.environ.get("GATE_PHASE", "decomp"), total, len(banked_by_bin), propagated, fp)
    sh(["git", "commit", "-q", "-m", msg])
    return sh(["git", "rev-parse", "--short", "HEAD"]).stdout.strip()


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--count", type=int, default=80, help="unique fns to draft+gate this cycle (0 = all available)")
    ap.add_argument("--binary-glob", default="*", help="fnmatch over binary aliases, e.g. 'ov_SC03_*'")
    ap.add_argument("--binaries", default=None, help="explicit comma-list (intersected with --binary-glob)")
    ap.add_argument("--max-nins", type=int, default=15)
    ap.add_argument("--min-nins", type=int, default=1)
    ap.add_argument("--min-reach", type=int, default=1)
    ap.add_argument("--workers", type=int, default=8, help="parallel gate workers (each runs one make build)")
    ap.add_argument("--iters", type=int, default=3, help="api_draft self-correct iterations per fn")
    ap.add_argument("--measure", action="store_true", help="print the draft/gate timing + bank-rate breakdown")
    ap.add_argument("--no-commit", action="store_true", help="gate + dedupe but do NOT git commit (dry)")
    a = ap.parse_args()

    api_base, model = os.environ.get("API_BASE"), os.environ.get("MODEL")
    if not api_base or not model:
        log("set API_BASE and MODEL (the served fine-tuned model)"); sys.exit(2)
    if not endpoint_up(api_base):
        log("serving endpoint %s is DOWN (start tools/serve_local.py) — aborting" % api_base); sys.exit(3)
    os.makedirs(BULK, exist_ok=True)
    if os.path.exists(STOP):
        log("STOP sentinel present — remove .run/auto/STOP to run"); sys.exit(0)

    tried = set(json.load(open(lg.TRIED))) if os.path.exists(lg.TRIED) else set()
    bins = select_binaries(a)
    picked = pick_targets(bins, a, tried)
    if not picked:
        log("no fresh open <=%d-ins stubs in %d binaries (all tried?)" % (a.max_nins, len(bins))); return 0
    log("targets: %d unique fns across %d binaries (glob=%s, <=%d ins)" %
        (len(picked), len(set(t["binary"] for t in picked)), a.binary_glob, a.max_nins))

    # clear stale per-binary draft subdirs (keep the tried-set; RESUMABLE)
    for d in glob.glob(os.path.join(BULK, "*")):
        shutil.rmtree(d, ignore_errors=True) if os.path.isdir(d) else os.remove(d)

    # ---- Phase A: bulk-draft (GPU, serial) ----
    t0 = time.time()
    drafts_dir = lg.draft(picked, api_base, model, a.iters)     # flat: <fn>.c per target
    staged = split_drafts_by_binary(picked, drafts_dir)
    draft_secs = time.time() - t0
    log("phase A: drafted+staged %d/%d in %.0fs (%.1fs/fn)" %
        (staged, len(picked), draft_secs, draft_secs / max(1, len(picked))))
    tried |= {t["name"] for t in picked}                        # mark tried even if a draft failed (don't re-grind)
    json.dump(sorted(tried), open(lg.TRIED, "w"))

    jobs = build_jobs(picked)
    if not jobs or os.path.exists(STOP):
        log("nothing staged / STOP — no gate phase"); return 0

    # ---- Phase B: bulk-gate (CPU, parallel over distinct binaries) ----
    t1 = time.time()
    banked_by_bin, gated = {}, 0
    ctx = multiprocessing.get_context("fork")                   # inherit imported modules + __main__ funcs
    with ProcessPoolExecutor(max_workers=a.workers, mp_context=ctx) as ex:
        futs = {ex.submit(_gate_worker, j): j["binary"] for j in jobs}
        for fut in as_completed(futs):
            res = fut.result()
            gated += res["drafts"]
            if res["banked"]:
                banked_by_bin[res["binary"]] = res["banked"]
                log("  + %s: banked %d (%s)" % (res["binary"], len(res["banked"]), " ".join(res["banked"])))
    gate_secs = time.time() - t1
    total_banked = sum(len(v) for v in banked_by_bin.values())

    # ---- Phase C: dedupe (reach>=2 only) + merge backlogs + one commit ----
    propagated = 0
    for b, fns in banked_by_bin.items():
        if any((lg.reach_of(b, fn) or 1) >= 2 for fn in fns):
            before = gate_stage._dedup_group_count()
            sh([PY, "tools/dedup_propagate.py", "--auto-from", b, "--min-reach", "2"], timeout=3600)
            propagated += max(0, gate_stage._dedup_group_count() - before)
    merge_backlogs()
    fp = fleet_pct()
    commit_sha = None
    if total_banked and not a.no_commit:
        commit_sha = git_commit(banked_by_bin, propagated, fp)

    json.dump({"ts": int(time.time()), "drafted": staged, "gated": gated, "banked": total_banked,
               "propagated": propagated, "fleet_pct": fp, "commit": commit_sha}, open(STATS, "w"), indent=1)
    json.dump({"ts": int(time.time()), "banked": total_banked, "fleet_pct": fp, "tried": len(tried)},
              open(HB, "w"))

    rate = 100.0 * total_banked / max(1, gated)
    log("DONE: gated %d, BANKED %d (%.0f%% bank-rate), %d propagated, fleet %s%%%s" %
        (gated, total_banked, rate, propagated, fp, "  commit " + commit_sha if commit_sha else "  (no commit)"))
    if a.measure:
        log("MEASURE: draft %.0fs (%.1fs/fn serial GPU) | gate %.0fs (%.1fs/fn amortized, %d workers) | "
            "bank-rate %d/%d = %.1f%%" % (draft_secs, draft_secs / max(1, len(picked)), gate_secs,
                                          gate_secs / max(1, gated), a.workers, total_banked, gated, rate))
    return total_banked


if __name__ == "__main__":
    main()

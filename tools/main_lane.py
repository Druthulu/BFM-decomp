#!/usr/bin/env python3
"""main_lane.py — the SECOND drafting lane, for the EXE (`main`), on its own gate cadence.

WHY A SEPARATE LANE (P31 S59, Drew's call). `main` is excluded from every wave draw
(`draw_wave` passes `--exclude-bins main`) for a good reason: its gate is a CLEAN WHOLE-EXE
rebuild that bisects on failure, and putting that on the critical path of a loop whose other gates
take minutes cost the campaign three measured stalls (39 min unfinished on 29 drafts, 25 on 8,
65+ on 8, while later waves queued behind it). So main sat outside the loop entirely — **1,713 open
stubs, no lane, no cadence** — while the overlay lane ran at roughly a quarter of the API ceiling
(mean 55 req/min against a 200-230 knee) because CARD SUPPLY, not throughput, is its constraint.

Two populations, one idle half of a rate limit: main gets its own lane rather than a bigger wave.

WHAT THIS LANE DOES, AND WHAT IT DELIBERATELY DOES NOT
    draw (main only) -> draft -> reloc pre-filter -> ONE gate_main batch -> commit -> repeat.
  * It NEVER gates through `sweep_parallel` or `gate_stage`. Both build INCREMENTALLY, and main's
    `make extract` re-runs `psyq_integrate`/`ld_interleave`, which rewrite the linker script — an
    incremental build after a source change then produces a FALSE DIFF. `sweep_parallel` used to
    accept main anyway: wave `ab` drew 105 main cards and banked 0 of 105 while its 115 non-main
    cards banked 94, and the whole wave read as a drafting failure (that is R43's origin).
  * It gates in BATCHES because one clean rebuild verifies the whole slate — that is what makes
    main affordable at all (34 functions banked in a single rebuild, measured). The reloc
    pre-filter is what keeps a batch from bisecting: a draft that names symbols the target never
    references cannot bank and must not enter the slate.
  * It COMMITS the moment a batch is green (R42). `gate_main` does not commit — it substitutes and
    verifies, and its output is unverified by construction until the SHA matches, which is exactly
    why the overlay gater REFUSES to adopt dirty main sources.
  * Parked drafts come first. `.run/main_queue/*.json` holds main drafts the overlay waves produced
    before main was excluded (170 of them today) — free work, already drafted, never gated.

CONCURRENCY. `gate_main` takes `.run/auto/gate.main.lock` (blocking) so two main gates can never
interleave into `src/800.c`. This lane adds no lock of its own; it just never runs two gates at
once, and the overlay lanes are untouched by construction — different binaries, different gate.

  tools/main_lane.py --once            # one cycle, for a supervised trial
  tools/main_lane.py                   # loop forever (the lane script's mode)
"""
import argparse
import glob
import json
import os
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ox_campaign as OX                                                   # noqa: E402

REPO = OX.REPO if hasattr(OX, "REPO") else os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = ".venv/bin/python"
LEDGER = ".run/main_lane_ledger.jsonl"


def log(msg):
    print(f"[{time.strftime('%H:%M:%S')}] [main-lane] {msg}", flush=True)


def next_tag():
    """m00, m01, … — a 3-character namespace so it can never collide with the overlay lane's
    2-letter wave tags (its `used` set globs `.run/wave_??_cards.json`)."""
    used = {os.path.basename(p)[5:8] for p in glob.glob(".run/wave_m??_cards.json")}
    for i in range(100):
        t = f"m{i:02d}"
        if t not in used:
            return t
    return None


def parked_slate():
    """Main drafts the overlay waves parked before main was excluded — free, already drafted."""
    out = []
    for p in sorted(glob.glob(".run/main_queue/*.json")):
        try:
            rows = json.load(open(p))
        except Exception:
            continue
        for r in rows:
            d = r.get("draft") or r.get("c")
            if d and os.path.exists(d):
                out.append({"fn": r.get("fn") or r.get("name"), "draft": d, "src": p})
    seen, uniq = set(), []
    for r in out:                                   # a function can be parked by two waves
        if r["fn"] and r["fn"] not in seen:
            seen.add(r["fn"]); uniq.append(r)
    return uniq


def draw(tag, n, lo, hi):
    """Draw main-only cards. The quotas are OFF: tells and jtbl-carve are overlay lanes, and main's
    jtbl members are `main-manual` by the island probe's own classification."""
    cards = f".run/wave_{tag}_cards.json"
    if os.path.exists(cards):
        log(f"{tag}: cards already drawn, reusing")
        return cards
    r = OX.sh(f"{PY} tools/build_wave_atlas.py {cards} {n} --min-ins {lo} --max-ins {hi} "
              f"--only-bins main --one-per-gid --retry-unbanked --tells-quota 0 --jtbl-quota 0",
              timeout=3600, quiet=False)
    if not os.path.exists(cards):
        log(f"{tag}: draw produced no cards ({(r.stderr or '')[-200:]})")
        return None
    return cards


def gate_batch(tag, slate):
    """One clean whole-EXE rebuild for the whole slate; bisects internally on failure."""
    if not slate:
        return 0, []
    sp = f".run/main_slate_{tag}.json"
    json.dump([{"fn": s["fn"], "draft": s["draft"]} for s in slate], open(sp, "w"), indent=1)
    log(f"{tag}: gating {len(slate)} draft(s) — ONE clean whole-EXE rebuild, bisect on failure")
    t0 = time.time()
    r = OX.sh(f"{PY} tools/gate_main.py {sp} --apply", timeout=14400, quiet=False)
    mins = (time.time() - t0) / 60.0
    out = (r.stdout or "") + (r.stderr or "")
    banked = [s["fn"] for s in slate if f"BANKED {s['fn']}" in out or f"banked {s['fn']}" in out]
    if not banked:                                  # fall back to the tree: what stopped being a stub
        try:
            import corpus
            corpus.stubs.cache_clear() if hasattr(corpus.stubs, "cache_clear") else None
            open_now = {s.name if hasattr(s, "name") else s for s in corpus.stubs("main")}
            banked = [s["fn"] for s in slate if s["fn"] not in open_now]
        except Exception:
            pass
    log(f"{tag}: gate finished in {mins:.1f} min — {len(banked)} banked of {len(slate)}")
    return len(banked), banked


def commit_banks(tag, banked):
    """R42: commit the moment a batch is green. Named paths only — other lanes bank into this tree
    at the same time and a blanket `git add -A` would adopt their in-flight work as ours."""
    if not banked:
        return
    OX.sh("git add src/*.c config/symbols.us.txt 2>/dev/null || true")
    msg = (f"feat(decomp): main lane {tag} — {len(banked)} banked\\n\\n"
           f"One clean whole-EXE rebuild verified the batch (gate_main). Functions:\\n"
           + "\\n".join(f"  {f}" for f in sorted(banked)[:40])
           + ("\\n  …" if len(banked) > 40 else ""))
    OX.sh(f"git commit -q -m {json.dumps(msg)} || true")
    log(f"{tag}: committed {len(banked)} bank(s)")


def cycle(a, tag):
    """One draw→draft→filter→gate→commit pass. Returns the number banked."""
    parked = parked_slate() if not a.no_parked else []
    if parked:
        log(f"{tag}: {len(parked)} PARKED draft(s) from earlier overlay waves — gating those first "
            f"(already drafted, never gated)")
        batch = parked[:a.batch]
        n, banked = gate_batch(tag, batch)
        commit_banks(tag, banked)
        for r in {x["src"] for x in batch}:         # consume the queue file once its rows are gated
            done = {x["fn"] for x in batch}
            try:
                rows = [x for x in json.load(open(r))
                        if (x.get("fn") or x.get("name")) not in done]
                json.dump(rows, open(r, "w"), indent=1)
            except Exception:
                pass
        return n

    cards = draw(tag, a.cards, a.min_ins, a.max_ins)
    if not cards:
        return 0
    targets = OX.shard_targets(tag, cards, a.workers)
    if not targets:
        log(f"{tag}: no valid targets"); return 0
    log(f"{tag}: {len(targets)} main card(s) -> drafting with {a.workers} worker cap")
    procs = OX.draft(tag, OX.parse_lanes(a.models, a.model, a.workers), a.maxtok, a.max_turns,
                     wave_lane="main")
    drafts, trunc = OX.collect_drafts(tag, procs)   # (paths, truncated-turn count)
    log(f"{tag}: {len(drafts)} draft(s) produced ({trunc} truncated)")
    keep, counts = OX.reloc_filter(tag, drafts, cards)
    log(f"{tag}: reloc_identity {counts} -> slate {len(keep)}")
    slate = [{"fn": k["fn"], "draft": k["draft"]} for k in keep][:a.batch]
    n, banked = gate_batch(tag, slate)
    commit_banks(tag, banked)
    with open(LEDGER, "a") as f:
        f.write(json.dumps({"t": time.time(), "tag": tag, "cards": len(targets),
                            "drafts": len(drafts), "slate": len(slate), "banked": n,
                            "reloc": counts}) + "\n")
    return n


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--cards", type=int, default=200)
    ap.add_argument("--workers", type=int, default=150,
                    help="worker cap for THIS lane (default 150). The overlay lane runs ~313 agents "
                         "at ~190 req/min against a measured 429 knee of 200-230; this lane is "
                         "sized to use the headroom, not to compete for it.")
    ap.add_argument("--batch", type=int, default=40,
                    help="drafts per gate_main invocation (default 40). One clean rebuild verifies "
                         "the whole slate; a failure bisects, so a bigger batch is cheaper only "
                         "while the reloc pre-filter keeps the failure rate low.")
    ap.add_argument("--min-ins", type=int, default=5)
    ap.add_argument("--max-ins", type=int, default=200)
    ap.add_argument("--models", default="stealth/ox-alpha:150")
    ap.add_argument("--model", default="stealth/ox-alpha")
    ap.add_argument("--maxtok", type=int, default=int(os.environ.get("MAXTOK", "8000")))
    ap.add_argument("--max-turns", type=int, default=24)
    ap.add_argument("--no-parked", action="store_true", help="skip the .run/main_queue backlog")
    ap.add_argument("--once", action="store_true")
    a = ap.parse_args()

    os.chdir(REPO)
    while not os.path.exists(".run/ox_campaign.stop"):
        tag = next_tag()
        if not tag:
            log("out of main-lane tags"); return
        try:
            cycle(a, tag)
        except Exception as e:                       # a lane must survive its own bad cycle
            log(f"{tag}: cycle failed: {type(e).__name__}: {e}")
        if a.once:
            return
        time.sleep(20)


if __name__ == "__main__":
    main()

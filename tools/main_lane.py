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
import re
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


MAX_RETRY = 2


def parked_slate():
    """Main drafts waiting to be gated: the overlay waves' parked queue, plus this lane's own
    failures (a failed batch is evidence, not garbage — with bisecting, most of a failed slate is
    innocent). A draft that has failed MAX_RETRY times is left in the failed file and skipped, so a
    permanently-unbankable body cannot spin the lane forever."""
    out = []
    for p in sorted(glob.glob(".run/main_queue/*.json") + [".run/main_queue_failed.json"]):
        if not os.path.exists(p):
            continue
        try:
            rows = json.load(open(p))
        except Exception:
            continue
        for r in rows:
            d = r.get("draft") or r.get("c")
            if d and os.path.exists(d) and int(r.get("tries", 0)) < MAX_RETRY:
                out.append({"fn": r.get("fn") or r.get("name"), "draft": d, "src": p,
                            "tries": int(r.get("tries", 0))})
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


def _stub_removals():
    """Functions whose INCLUDE_ASM line disappeared from main's sources in the WORKING TREE.

    This is the ground truth for "what did this run bank", and it is deliberately not a tool's
    self-report: the first version of this function asked `corpus.stubs('main')` whether each name
    was still a stub, and `corpus.stubs` returns a dict keyed by ADDRESS (int). Comparing a function
    NAME against a set of ints is always True, so the lane reported 12 banked of 12 from a gate that
    had banked nothing and committed nothing. A check that is true about the wrong thing is worse
    than no check — it is the exact defect class R32/R40 exist for, and it took 17 seconds to
    produce a confident lie."""
    r = OX.sh("git diff --unified=0 -- src/*.c | grep '^-INCLUDE_ASM' || true")
    out = []
    for line in (r.stdout or "").splitlines():
        i = line.rfind(",")
        if i > 0:
            out.append(line[i + 1:].strip().rstrip(");").strip())
    return [x for x in out if x.startswith(("func_", "D_")) or x]


def _main_sha_green():
    """The arbiter (G3/P9): main builds byte-identical. Held under main's own gate lock so this can
    never race a gate_main."""
    r = OX.sh("( flock -w 3600 9 || exit 1; make check BINARY=main 2>&1 | tail -3 ) "
              "9>.run/auto/gate.main.lock", timeout=7200)
    out = (r.stdout or "") + (r.stderr or "")
    return ("BYTE-IDENTICAL" in out), out.strip().splitlines()[-1] if out.strip() else ""


def _gate_once(tag, slate):
    """Substitute this slate, clean-rebuild, and return (banked_names, gate_main's output)."""
    sp = f".run/main_slate_{tag}.json"
    json.dump([{"fn": s["fn"], "draft": s["draft"]} for s in slate], open(sp, "w"), indent=1)
    t0 = time.time()
    r = OX.sh(f"{PY} tools/gate_main.py {sp} --apply", timeout=14400, quiet=False)
    out = ((r.stdout or "") + (r.stderr or "")).strip()
    banked = _stub_removals()
    log(f"{tag}: {len(slate)} draft(s) -> {len(banked)} banked in {(time.time()-t0)/60:.1f} min")
    return banked, out


def gate_batch(tag, slate, depth=0):
    """One clean whole-EXE rebuild for the slate, BISECTING on a compile conflict.

    gate_main bisects byte MISMATCHES but deliberately refuses to bisect a COMPILE conflict: it
    names the symbol and stops, because a decl clash is not a wrong body (§236). That is right for
    a tool whose caller might be a human, and wrong for an unattended lane — the first live batch
    hit `COMPILE conflict on func_80017778` where the symbol was in the TU, not in any draft, so
    there was nothing to drop and 40 innocent drafts died with it. Halving costs one rebuild per
    level and a main rebuild here measures ~18 s, so the lane bisects rather than discards.

    Nothing is credited until BOTH the stubs are gone from the tree AND main builds byte-identical.
    """
    if not slate:
        return 0, []
    log(f"{tag}: gating {len(slate)} draft(s)"
        + (f" (bisect depth {depth})" if depth else " — ONE clean whole-EXE rebuild"))
    banked, out = _gate_once(tag, slate)

    if banked:
        green, line = _main_sha_green()
        if not green:
            log(f"{tag}: REFUSING to credit {len(banked)} substitution(s) — main is NOT "
                f"byte-identical ({line}). Left for a human; gate_main reverts its own aborts.")
            return 0, []
        log(f"{tag}: {len(banked)} banked, main byte-identical — {line}")
        # COMMIT HERE, not at the end of the cycle (R42). A bisect can run for many levels, and
        # deferring left byte-proven functions sitting uncommitted in src/ the whole time — exactly
        # the window in which a blind revert by any other tool destroys them. The tree is verified
        # byte-identical on this line; that is the moment it is safe and the moment it is durable.
        commit_banks(tag, banked)
        return len(banked), banked

    if "COMPILE conflict" in out and len(slate) > 1 and depth < 4:
        mid = len(slate) // 2
        log(f"{tag}: compile conflict with nothing to drop — bisecting {len(slate)} into "
            f"{mid}+{len(slate)-mid}")
        n1, b1 = gate_batch(f"{tag}a", slate[:mid], depth + 1)
        n2, b2 = gate_batch(f"{tag}b", slate[mid:], depth + 1)
        return n1 + n2, b1 + b2

    tail = "\n      ".join(out.splitlines()[-4:])
    log(f"{tag}: nothing banked. gate_main's last words:\n      {tail}")
    return 0, []


def commit_banks(tag, banked):
    """R42: commit the moment a batch is green. Named paths only — other lanes bank into this tree
    at the same time and a blanket `git add -A` would adopt their in-flight work as ours."""
    if not banked:
        return
    OX.sh("git add src/*.c config/symbols.us.txt 2>/dev/null || true")
    # -F a file, never -m with a shell-quoted string: json.dumps() escapes newlines and em-dashes,
    # so the first version of this committed a message reading "main lane m00 \\u2014 11 banked\\n\\n…"
    # as ONE literal line.
    mp = f".run/main_commit_{tag}.txt"
    with open(mp, "w") as f:
        f.write(f"feat(decomp): main lane {tag} — {len(banked)} banked\n\n"
                f"One clean whole-EXE rebuild verified the batch (gate_main), and main re-checked\n"
                f"BYTE-IDENTICAL against config/check.us.sha before anything was credited.\n\n"
                + "\n".join(f"  {f_}" for f_ in sorted(banked)[:60])
                + ("\n  …" if len(banked) > 60 else "") + "\n")
    OX.sh(f"git commit -q -F {mp} || true")
    log(f"{tag}: committed {len(banked)} bank(s)")


def cycle(a, tag):
    """One draw→draft→filter→gate→commit pass. Returns the number banked."""
    parked = parked_slate() if not a.no_parked else []
    if parked:
        log(f"{tag}: {len(parked)} PARKED draft(s) from earlier overlay waves — gating those first "
            f"(already drafted, never gated)")
        batch = parked[:a.batch]
        n, banked = gate_batch(tag, batch)      # gate_batch commits each verified sub-batch (R42)
        failed = [x for x in batch if x["fn"] not in set(banked)]
        if failed:
            fp = ".run/main_queue_failed.json"
            try:
                prev = json.load(open(fp))
            except Exception:
                prev = []
            seen = {x.get("fn") for x in prev}
            bumped = {x["fn"]: int(x.get("tries", 0)) + 1 for x in failed}
            for row in prev:                                  # count a repeat failure
                if row.get("fn") in bumped:
                    row["tries"] = bumped.pop(row["fn"])
            prev += [{"fn": x["fn"], "draft": x["draft"], "tag": tag, "t": time.time(),
                      "tries": bumped[x["fn"]]}
                     for x in failed if x["fn"] in bumped and x["fn"] not in seen]
            json.dump(prev, open(fp, "w"), indent=1)
            log(f"{tag}: {len(failed)} draft(s) did not bank -> parked in {fp} with their tag "
                f"(recoverable; a failed draft is evidence, not garbage)")
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
    n, banked = gate_batch(tag, slate)          # gate_batch commits each verified sub-batch (R42)
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

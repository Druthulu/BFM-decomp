#!/usr/bin/env python3
"""ox_campaign.py — the unattended overnight wave loop (P31 S58).

ONE WAVE = draw -> draft -> reloc pre-filter -> parallel gate -> commit -> ledger. The loop repeats
until --waves is exhausted, the credit floor is hit, or .run/ox_campaign.stop appears.

WHY EACH STEP IS WHERE IT IS
  * reloc_identity BEFORE the gate. match_one masks jal/HI16/LO16, so it scores a wrong-symbol draft
    as MATCH (§174 law 1c). Measured this session on the S57 sub-50 pile: reloc_identity predicted
    4 of the 5 gate rejections for free, before any rebuild. Gating a draft it refuses is a rebuild
    spent to learn something a deterministic check already knew.
  * sweep_parallel, not gate_lane. gate_lane walks (binary, TU) groups SERIALLY — right when many
    drafts share one destination TU, wrong for a wide slate. Measured: 7 binaries / 10 drafts in 53s
    parallel vs ~25 min for 19 binaries serial.
  * The gate step is serial across waves BY CONSTRUCTION. Two sweeps could schedule the same binary,
    and the per-binary flock would then serialize them anyway — with two writers in one src/ tree.
  * MAXTOK is set explicitly. api_draft's 512 default is a LOCAL-model output cap; a reasoning model
    emitting a whole C function truncates every turn (measured 348 of 918 turns finish=length, all
    reported as "no compiling draft"). R40: that is a harness verdict wearing a model's name.

WORKER STEP-UP. Concurrency rises only on EVIDENCE: a wave that recorded zero 429s earns +step
workers, a wave that recorded any drops back to the last clean level. Measured start point: 24
workers sustained 167 req/min with 0 429s on a non-free-tier key.

  tools/ox_campaign.py --waves 8 --workers 24 --max-workers 64
"""
import argparse
import collections
import fcntl
import glob
import json
import os
import re
import shutil
import string
import subprocess
import sys
import threading
import time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
PY = ".venv/bin/python"
LEDGER = ".run/ox_campaign_ledger.jsonl"
STOP = ".run/ox_campaign.stop"
RATE = ".run/api_rate.jsonl"


def log(msg):
    print(f"[{time.strftime('%H:%M:%S')}] {msg}", flush=True)


def sh(cmd, timeout=None, quiet=True):
    r = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=timeout)
    if not quiet and r.returncode != 0:
        log(f"  ! rc={r.returncode}: {(r.stderr or r.stdout)[-300:]}")
    return r


def unstage_main_tus():
    """Drop TOP-LEVEL src/*.c from the index before an overlay/maintenance commit (S59).

    A concurrent gate_main substitution in main's TUs is unverified by construction, and this
    campaign's blanket `git add -A src/` adopted one mid-flight at 14:57:01 (commit:2693): main
    built RED until 18:43 and the main lane banked 0 from four 200-card draft rounds — every
    rejection a false verdict. main's TUs have exactly ONE writer (gate_main) and ONE committer
    (main_lane, after the whole-EXE SHA re-checks green); every other lane must neither commit
    NOR revert them (after a GREEN gate, byte-proven work legitimately sits there uncommitted)."""
    files = sorted(glob.glob('src/*.c'))
    if files:
        sh("git reset -q -- " + " ".join(files))


def credits_left():
    """Remaining OpenRouter credit, or None if unreadable. Never fatal — telemetry, not a gate."""
    key = ""
    try:
        for line in open(".env"):
            if line.startswith("open_router_key="):
                key = line.split("=", 1)[1].strip(); break
    except OSError:
        return None
    if not key:
        return None
    r = sh(f'curl -s -H "Authorization: Bearer {key}" https://openrouter.ai/api/v1/auth/key')
    try:
        return json.loads(r.stdout)["data"]["limit_remaining"]
    except Exception:
        return None


def mem_snapshot():
    """Free/available memory in MB. Recorded per wave so a LOCAL bottleneck stays distinguishable
    from a provider one: at 256 agents (~70 MB each) the box is carrying ~18 GB of ~30 GB, and if
    it starts swapping, requests/minute collapses for a reason that has nothing to do with any
    rate limit — and would otherwise read as 'we found the ceiling'."""
    try:
        info = {}
        for line in open("/proc/meminfo"):
            k, _, v = line.partition(":")
            info[k] = int(v.split()[0]) // 1024
        return {"mem_avail_mb": info.get("MemAvailable"), "swap_used_mb":
                (info.get("SwapTotal", 0) - info.get("SwapFree", 0))}
    except Exception:
        return {}


def rate_slice(t0):
    """The wave's OWN request numbers, and — the part that matters for scaling — whether any 429s
    were a BURST or SUSTAINED.

    A provider burst is not our ceiling. `upstream_provider_shared_pool` saturates because everyone
    on that provider is hitting it at once, then it resumes; backing off permanently on a burst
    throttles us to someone else's transient. Two things distinguish a real ceiling from a burst:

      * ATTRIBUTION. A PLATFORM 429 is OpenRouter refusing OUR account — that is our limit, full
        stop. A PROVIDER 429 is the upstream pool, and says nothing about our account.
      * PERSISTENCE. A burst occupies one or two clock minutes. A ceiling holds minute after minute.
        `sustained_min` is the LONGEST RUN of consecutive minutes each containing a 429.

    Returned alongside is `req_per_min`, because the honest ceiling test is not 429 counts at all:
    it is whether adding workers still buys throughput.
    """
    posts, h429 = [], []
    src = collections.Counter()
    try:
        for line in open(RATE):
            line = line.strip()
            if not line:
                continue
            try:
                r = json.loads(line)
            except json.JSONDecodeError:
                continue
            if r.get("t", 0) < t0:
                continue
            if r.get("ev") == "POST":
                posts.append(r)
            elif r.get("ev") == "429":
                h429.append(r)
                src[r.get("src", "?")] += 1
    except OSError:
        pass
    span = (posts[-1]["t"] - posts[0]["t"]) if len(posts) > 1 else 0
    rpm = round(60.0 * len(posts) / span, 1) if span > 30 else 0.0
    mins = sorted({int(r["t"] // 60) for r in h429})
    longest = run = 0
    for i, m in enumerate(mins):
        run = run + 1 if i and m == mins[i - 1] + 1 else 1
        longest = max(longest, run)
    platform = sum(v for k, v in src.items() if str(k).startswith("PLATFORM"))
    per_model = {}
    for r in posts:
        per_model.setdefault(r.get("model", "?"), [0, 0])[0] += 1
    for r in h429:
        per_model.setdefault(r.get("model", "?"), [0, 0])[1] += 1
    return {"requests": len(posts), "h429": len(h429), "h429_src": dict(src),
            "platform_429": platform, "sustained_min": longest, "req_per_min": rpm,
            "per_model": {k: {"req": v[0], "h429": v[1]} for k, v in per_model.items()}}


def draw_wave(tag, n, band, levers=None):
    lo, hi = band
    cards = f".run/wave_{tag}_cards.json"
    if os.path.exists(cards):
        log(f"  wave {tag}: cards already drawn, reusing")
        return cards
    # ';' inside a lane spec becomes ',' here: commas already separate LANES in --lanes, so a
    # multi-lever lane has to use a different inner separator.
    lv = f" --levers {levers.replace(';', ',')}" if levers else ""
    # --retry-unbanked: a drawn-but-unbanked card is unfinished work, not spent work. Without it
    # the pool bleeds: 1,785 cards / 72,961 instructions were locked out across 11 waves while the
    # drafting lane starved (wave ak asked for 1,400 cards and its band could supply 497).
    # main IS EXCLUDED FROM WAVE DRAWS. Not because its functions are unwanted — 1,041 open stubs
    # is real territory — but because its gate is a CLEAN WHOLE-EXE REBUILD that bisects on failure,
    # and that does not belong on the critical path of a loop whose other gates take minutes.
    # Measured P31 S58, three times: 39 min unfinished on a 29-draft batch, 25 min on a chunk of 8,
    # then 65+ min on another chunk of 8 while waves `an` and `ao` sat queued behind it. Main needs
    # its own cadence (drafts accumulate, gate them in one batch when nothing else is waiting), and
    # a wave that cannot bank main should not spend agents drafting it either.
    # MAX_BINS 24 -> 160 (P31 S60, measured). Concentrating a wave into 24 gate groups was a
    # CPU-economy choice: each group is one whole-binary rebuild. The CPU is not the scarce
    # resource — a live gate runs at load 2.7 of 32 cores (8%), one harvest_verify at --chunk 1 —
    # while the DRAFTING fleet, the thing actually bounded by the free-model clock, sat at ~200
    # agents because the draw handed it 196 cards out of 699 available distinct-gid candidates in
    # 224 gate groups. req/min is agents-in-flight x ~0.8, so the draw was setting the campaign's
    # throughput. Raise the cap to take essentially the whole pool; MAX_BINS overrides it.
    bins = os.environ.get("MAX_BINS", "160")
    r = sh(f"{PY} tools/build_wave_atlas.py {cards} {n} --min-ins {lo} --max-ins {hi} "
           f"--max-bins {bins} --one-per-gid --retry-unbanked --exclude-bins main{lv}",
           timeout=3600, quiet=False)
    if not os.path.exists(cards):
        log(f"  wave {tag}: DRAW FAILED — {(r.stderr or r.stdout)[-300:]}")
        return None
    for line in r.stdout.splitlines():
        if line.startswith("-> wave"):
            log(f"  {line.strip()}")
    return cards


def shard_targets(tag, cards_path, workers):
    cards = json.load(open(cards_path))
    cards = cards if isinstance(cards, list) else cards.get("cards", [])
    targets = [{"name": c["fn"], "addr": c["addr"], "nins": c["nins"], "binary": c["binary"],
                "sub": c["sub"], "asm": f"{c['sub']}/{c['fn']}.s", "tu": c.get("tu"),
                "ghidra_c": f".run/ghidra_c/{c['fn']}.c"} for c in cards]
    targets = [t for t in targets if os.path.isfile(t["asm"])]     # R32: assert, do not assume
    for i in range(workers):
        json.dump(targets[i::workers], open(f".run/wave_{tag}_targets.{i}.json", "w"), indent=1)
    return targets


# PER-LANE AGENT BUDGETS (P31 S59, measured). The turn/cost caps were one global pair, and the
# tells lane's cards are 2.4x the default lane's size (median 89-95 instructions vs 37-39) and stack
# 3-5 idioms each: 98 of 270 final tells attempts ended AT the turn cap and 36% of failures ended at
# a cap of some kind — i.e. they ran out of budget mid-work rather than failing. A budget that fits
# a 38-instruction card starves a 95-instruction one. {lane: (max_turns, max_cost_per_fn)}.
LANE_BUDGET = {'tells': (40, 0.40)}
LANE_BUDGET_DEFAULT = (None, 0.15)          # None = the campaign's --max-turns


def draft(tag, lanes, maxtok, max_turns, ramp_seconds=float(os.environ.get('RAMP_SECONDS', '240')),
          wave_lane=None):
    """Draft one wave across SEVERAL MODEL LANES at once.

    Concurrency on ONE model is spent (P31 S58, measured): every 429 we have ever recorded is
    `upstream_provider_shared_pool` — the provider's pool, never OpenRouter refusing the account —
    and wave `ae` at 48 workers achieved 43.5 req/min against peaks of 109-159 at 24-36. More
    workers on a saturated pool buy LESS throughput. Independent pools do not share that ceiling,
    so the remaining headroom is breadth across providers, not depth on one.

    `lanes` is [(model, workers, extra_env), ...]. Shards are dealt out contiguously so each lane
    owns a known slice, and every request already carries its model in the telemetry — so the
    per-lane 429 rate is measurable after the fact instead of assumed.
    """
    _t, _cost = LANE_BUDGET.get(wave_lane or '', LANE_BUDGET_DEFAULT)
    _turns = _t if _t is not None else max_turns
    if _t is not None:
        log(f"  lane {wave_lane}: budget {_turns} turns / ${_cost:.2f} per function "
            f"(default {max_turns}/$0.15)")
    outdir = f".run/wave_{tag}"
    shutil.rmtree(outdir, ignore_errors=True)
    os.makedirs(outdir, exist_ok=True)
    key = ""
    for line in open(".env"):
        if line.startswith("open_router_key="):
            key = line.split("=", 1)[1].strip(); break
    # INTERLEAVE the lanes across shard indices, do not hand each lane a contiguous BLOCK.
    #
    # shard_targets deals `targets[i::workers]`, so when a wave holds fewer cards than there are
    # workers, only the LOW shard indices get any targets. With contiguous blocks (ox 0-85,
    # deepseek 86-127) a 73-card wave therefore gave ox all 73 shards and deepseek ZERO — one whole
    # provider pool idle, which is the exact opposite of why the second lane exists. Measured on
    # wave `al`: "lane deepseek: 0 shards". Round-robin by lane proportion keeps both pools fed at
    # any wave size.
    # Build the order by SMALLEST-RATIO scheduling, not by concatenating blocks. `[0]*86 + [1]*42`
    # is still one contiguous run of ox followed by one of deepseek — modulo-indexing it changes
    # nothing, and a 73-card wave still lands entirely on ox. Picking, at each position, the lane
    # furthest behind its own share yields ox,ox,ds,ox,ox,ds,... so ANY prefix holds the ratio.
    counts = [max(0, n) for _model, n, _e in lanes]
    total = sum(counts)
    order, assigned = [], [0] * len(lanes)
    for _ in range(total):
        li = min((l for l in range(len(lanes)) if counts[l]),
                 key=lambda l: (assigned[l] + 1) / counts[l])
        order.append(li)
        assigned[li] += 1
    if not order:
        order = [0]
    assign = {}
    for idx in range(len(order)):
        assign[idx] = order[idx % len(order)]

    # RAMP OVER A FIXED WINDOW, not a fixed per-shard delay. A constant 0.06s stagger spreads 220
    # starts over 13s and 572 over 34s — so the bigger the wave, the harder it hits the pool, which
    # is backwards. Measured P31 S58 at 572 ox shards: 64% 429s in the launch minute decaying to
    # 0.0% by minute 9, i.e. the pool absorbs 572 concurrent agents fine and simply cannot absorb
    # them ARRIVING at once. Dividing a fixed ramp window by the shard count makes big waves ramp
    # gently and leaves small ones effectively instant.
    n_shards = sum(1 for i in range(len(order))
                   if os.path.exists(f".run/wave_{tag}_targets.{i}.json"))
    # Capped at 0.5s/shard: dividing a fixed window by a SMALL shard count inverts the problem —
    # a 9-shard wave would take the full 240s to launch nine agents. The cap means small waves start
    # promptly and only large ones actually consume the ramp window.
    stagger = min(ramp_seconds / n_shards, 0.5) if n_shards > 1 else 0
    if n_shards > 50:
        log(f"  ramping {n_shards} shards over {ramp_seconds:.0f}s ({stagger:.2f}s apart)")

    procs = []
    started = collections.Counter()
    for idx in range(len(order)):
        tf = f".run/wave_{tag}_targets.{idx}.json"
        if not os.path.exists(tf) or not json.load(open(tf)):
            continue
        model, _n, extra = lanes[assign[idx]]
        env = dict(os.environ, API_BASE="https://openrouter.ai/api/v1", API_KEY=key,
                   MODEL=model, MAXTOK=str(maxtok), **extra)
        fh = open(f"{outdir}/shard{idx}.log", "w")
        procs.append(subprocess.Popen(
            [PY, "-u", "tools/api_agent.py", "--targets", tf, "--cards",
             f".run/wave_{tag}_cards.json", "--out", f"{outdir}/shard{idx}",
             "--max-turns", str(_turns), "--max-cost", "1.0", "--max-cost-per-fn", str(_cost)],
            stdout=fh, stderr=subprocess.STDOUT, env=env))
        started[model] += 1
        # STAGGER THE LAUNCH. Every shard issues its first request immediately, so starting N at
        # once is an N-wide burst against one provider pool. Measured P31 S58 at 818 shards: the
        # first 5-minute bucket took 961 of the run's 964 429s (19.0%), and every bucket after it
        # was 0.0%. That burst was read as "ox's capacity ceiling at 9.8%" — it was the harness
        # knocking on the door 818 times in one second. Spreading startup over ~STAGGER seconds
        # costs nothing (agents run for minutes) and removes the spike entirely.
        if stagger:
            time.sleep(stagger)
    json.dump({str(k): lanes[v][0] for k, v in assign.items()},
              open(f"{outdir}/lane_map.json", "w"), indent=1)   # so per-lane stats stay derivable
    for model, cnt in started.items():
        log(f"  lane {model}: {cnt} shards")
    log(f"  {len(procs)} shards drafting across {len(lanes)} model lane(s)")
    return procs


def collect_drafts(tag, procs,
                   straggler_grace=int(os.environ.get('STRAGGLER_GRACE', '120')),
                   done_frac=0.95):
    """Wait for this wave's shards — but do NOT let a handful of stragglers idle the whole fleet.

    A wave queues only when every shard exits, so its TAIL is dead time: measured P31 S58, wave
    `ai` sat at 2 live agents of 220 for 34 minutes while the gater had nothing queued and 218
    shards' drafts sat finished on disk. The fleet was at 1% utilisation waiting for 1% of the work.

    Once `done_frac` of shards have exited, the rest get `straggler_grace` seconds and then the wave
    is queued WITHOUT killing them: their drafts still land in the same directory, and a later
    re-gate or --gate-only picks them up. Nothing is discarded — only the BLOCKING is dropped.

    GRACE IS SHORT ON PURPOSE (120s, was 600s). The trade is not "discard work vs keep it" — the
    stragglers keep running and their drafts still land either way. It is "how long does the WHOLE
    FLEET idle to shorten one wave's tail". Measured P31 S58 on wave `aq`: 85/89 shards done, and
    600s of grace meant ten minutes at 2 live agents. Five times shorter costs nothing real.
    """
    deadline = None
    while True:
        alive = [p for p in procs if p.poll() is None]
        if not alive:
            break
        done = len(procs) - len(alive)
        if done >= done_frac * len(procs):
            if deadline is None:
                deadline = time.time() + straggler_grace
                log(f"  {tag}: {done}/{len(procs)} shards done — {len(alive)} straggler(s) get "
                    f"{straggler_grace}s, then the wave queues without them")
            elif time.time() > deadline:
                log(f"  {tag}: queueing with {len(alive)} straggler(s) still running "
                    f"(their drafts will land and can be re-gated)")
                break
        time.sleep(5)
    outdir = f".run/wave_{tag}"
    drafts = sorted(glob.glob(f"{outdir}/shard*/*.c"))
    trunc = int(sh(f"grep -h 'finish=length' {outdir}/shard*.log 2>/dev/null | wc -l").stdout or 0)
    return drafts, trunc


def wait_for_tail(tag, procs,
                  done_frac=float(os.environ.get('TAIL_DONE_FRAC', '0.80'))):
    """Block until `done_frac` of a wave's shards have exited — then RETURN, tail still running.

    THE TAIL MUST NOT IDLE THE FLEET (P31 S60, measured). collect_drafts() blocks through the whole
    straggler grace before the wave queues and the next one starts, so with STRAGGLER_GRACE=700 the
    drafter sat on 4-13 live agents for ELEVEN MINUTES FORTY SECONDS at the end of every wave —
    cd 22:32->22:43, cc 23:06->23:18, ce 23:53->00:04, cf 00:37->00:48, four for four. Against a
    ~44-minute wave cycle that is 27% of the campaign's wall clock at 2-5% fleet utilisation, and
    the API rate collapsed from ~65 req/min to 2-5 in each trough.

    The grace itself is right and stays (a straggler mid-generation needs one full turn, §S59: a
    shorter grace guillotines agents mid-thought and COSTS drafts). What was wrong is BLOCKING on
    it. The wave now hands its tail to finish_wave_async() and the next wave draws and ramps
    immediately, so the grace overlaps the next wave instead of the void.

    DONE_FRAC 0.95 -> 0.80 (P31 S60, second pass). Overlapping at 95% still left a real trough:
    25% of the minutes after the first fix ran under 20 req/min, because the last 5% of a wave
    is its SLOWEST 5% — the long generations — and one wave's 12 stragglers cannot fill a fleet.
    Handing off at 80% starts the next ramp while ~40 agents are still working, so the fleet is
    never carried by a handful of agents. Nothing is cut short: the stragglers keep their full
    grace in the finisher thread and their drafts still land in the wave.
    """
    while True:
        alive = [p for p in procs if p.poll() is None]
        if not alive:
            return []
        done = len(procs) - len(alive)
        if done >= done_frac * len(procs):
            log(f"  {tag}: {done}/{len(procs)} shards done — {len(alive)} straggler(s) keep their "
                f"full grace while the NEXT wave starts; {tag} queues when they land")
            return alive
        time.sleep(5)


def finish_wave_async(tag, procs, cards, ntargets, t0, workers, band, lane,
                      straggler_grace=int(os.environ.get('STRAGGLER_GRACE', '120'))):
    """Wait out this wave's stragglers in a thread, then collect the drafts and queue the wave.

    Nothing here touches src/, config/ or any lock — it globs the wave's own directory and writes
    one marker — so it is safe beside a live drafting wave. If the drafter is restarted while a
    tail is outstanding the marker is never written and the drafts sit on disk, exactly as they did
    when a kill interrupted collect_drafts(); `--gate-only <tag>` picks them up.
    """
    def run():
        deadline = time.time() + straggler_grace
        while time.time() < deadline and any(p.poll() is None for p in procs):
            time.sleep(5)
        alive = [p for p in procs if p.poll() is None]
        outdir = f".run/wave_{tag}"
        drafts = sorted(glob.glob(f"{outdir}/shard*/*.c"))
        trunc = int(sh(f"grep -h 'finish=length' {outdir}/shard*.log 2>/dev/null | wc -l").stdout or 0)
        json.dump({"tag": tag, "cards": cards, "targets": ntargets, "drafts": len(drafts),
                   "trunc": trunc, "t0": t0, "workers": workers, "band": list(band),
                   "lane": lane["name"]}, open(f"{READY}/{tag}.json", "w"), indent=1)
        tail = f" · {len(alive)} straggler(s) still running" if alive else ""
        log(f"  DRAFT {tag} done: {len(drafts)} drafts ({trunc} truncated){tail} -> queued for the gater")
    t = threading.Thread(target=run, name=f"finish-{tag}", daemon=True)
    t.start()
    return t


def reloc_filter(tag, drafts, cards_path):
    """Keep only drafts whose relocations name the SAME symbols the target .s does."""
    cards = json.load(open(cards_path))
    cards = cards if isinstance(cards, list) else cards.get("cards", [])
    binof = {c["fn"]: c["binary"] for c in cards}
    batch = []
    for d in drafts:
        fn = os.path.basename(d)[:-2]
        if fn in binof:
            batch.append({"fn": fn, "binary": binof[fn], "draft": d})
    if not batch:
        return [], {}
    bp = f".run/wave_{tag}_reloc_in.json"
    op = f".run/wave_{tag}_reloc_out.json"
    json.dump(batch, open(bp, "w"), indent=1)
    sh(f"{PY} tools/reloc_identity.py --batch {bp} -j 12 --out {op}", timeout=7200)
    try:
        res = json.load(open(op))
    except Exception:
        return batch, {"(reloc_identity produced no output — gating unfiltered)": len(batch)}
    status = {r["fn"]: r.get("status") for r in res}
    counts = collections.Counter(status.values())
    # NOT-A-STUB IS NOT A PASS — it means reloc_identity found nothing to check because the
    # function is ALREADY BANKED. Gating those re-stages a draft body over source that already
    # byte-matches: pure waste at best, and at worst it perturbs a banked function inside a group
    # and takes the group's genuinely-new drafts down with it. Wave `an` carried 480 NOT-A-STUB of
    # 697 "gated" and banked 0. Only AGREE is a pass. (R43: refuse input the step cannot use.)
    keep = [b for b in batch if status.get(b["fn"]) == "AGREE"]

    # CAPTURE THE PRE-FILTER REJECTS (P31 S59). Everything that reaches the GATE and fails gets a
    # backlog row with its closeness, class and best draft (gate_stage) — but a draft the reloc
    # pre-filter drops never reaches the gate, so it was recorded NOWHERE and simply sat on disk.
    # That is 45% of all drafts (569 of 1,261 over eight waves), and 13% of the MISMATCH? rejects
    # have a body that ALREADY MATCHES — only the symbol names are wrong, which is the deterministic
    # `aprop_symfix` stale-symbol class that banked 4 of 4 earlier this session. A rejected draft is
    # evidence, not garbage; index it so a recovery pass can find it without re-drafting.
    try:
        det = {r["fn"]: r for r in res}
        with open(".run/reloc_rejects.jsonl", "a") as fh:
            for b in batch:
                st = status.get(b["fn"])
                if st in (None, "AGREE", "NOT-A-STUB"):
                    continue
                d = det.get(b["fn"], {})
                fh.write(json.dumps({
                    "t": time.time(), "wave": tag, "fn": b["fn"], "binary": b["binary"],
                    "draft": b["draft"], "status": st,
                    "shape": d.get("shape"),          # MATCH here = right body, wrong symbols
                    "checked": d.get("checked"), "aligned": d.get("aligned"),
                    "mismatches": (d.get("mismatches") or [])[:6],
                }) + "\n")
    except Exception as e:                            # telemetry must never break a gate
        log(f"  (reject capture skipped: {type(e).__name__}: {e})")
    n_banked_already = sum(1 for b in batch if status.get(b["fn"]) == "NOT-A-STUB")
    if n_banked_already:
        counts = dict(counts, _already_banked_excluded=n_banked_already)
    return keep, dict(counts)


def gate_main_batch(tag, mains):
    """main is gated by ONE CLEAN REBUILD of the whole EXE, never incrementally.

    gate_stage/sweep_parallel build incrementally, and main's extract rewrites the linker script,
    so an incremental main gate returns a FALSE DIFF. Measured P31 S58: wave `ab` drew 105 main
    cards and banked 0 of them while its non-main cards banked 82% — 105 competent drafts thrown
    away by the harness, and the failure read as a drafting problem. tools/gate_main.py does the
    substitute -> extract -> build -> compare cycle once for the entire batch.
    """
    if not mains:
        return 0, []
    slate = f".run/wave_{tag}_main_slate.json"
    json.dump([{"fn": m["fn"], "draft": m["draft"], "binary": "main"} for m in mains],
              open(slate, "w"), indent=1)
    log(f"  main: {len(mains)} drafts -> gate_main.py (one clean EXE rebuild)")
    r = sh(f"{PY} tools/gate_main.py {slate} --apply", timeout=14400)
    banked = []
    try:
        banked = json.load(open(".run/gate_main_banked.json"))
    except Exception:
        pass
    tail = [l for l in (r.stdout or "").splitlines() if "BANKED" in l or "MISMATCH" in l]
    log(f"  main: {tail[-1].strip() if tail else 'no verdict line'}")
    return len(banked), banked


def config_sane(min_ratio=0.8):
    """Refuse to commit a config file that COLLAPSED, and restore it from HEAD.

    P31 S60, the most expensive defect of the campaign: config/overlays.mk — the 5,077-line
    registry defining all 141 overlay binaries — was committed as a ZERO-LINE file by
    commit:2863 ("ox wave dk overlays — 2 banked"). Two failures, neither sufficient alone:
    some writer rewrites that file in place with no tmp+rename while lanes edit it
    concurrently (the version before the deletion already carried a stray partial line), and
    THIS committer swept the wreckage in, because "the tree is dirty at gate entry" cannot
    tell a truncated config from an intended edit.

    While it was empty: main could not build at all (its object glob prunes siblings via
    $(<bin>_ASM_DIR), so every overlay's nonmatchings/*.s fell into MAIN's OBJS and was
    assembled standalone), the main lane correctly refused to gate against a RED baseline
    with 1,288 stubs behind it, and overlay gates collapsed — GATE do banked 0 of 236 gated.

    R42 says commit a dirty tree rather than revert it, and that stands for src/: a per-binary
    gate leaves PROVEN banks uncommitted and reverting destroys them. A config file is the
    opposite case — it holds no proven state that exists only in the worktree, and a collapsed
    one is never intended. P28's registry died the same way (H5: never silently drop content
    on a rewrite); this enforces the rule instead of remembering it.
    """
    bad = []
    for path in ("config/overlays.mk", "config/dedup.us.yaml"):
        full = os.path.join(REPO, path)
        if not os.path.exists(full):
            continue
        with open(full, errors="replace") as fh:
            now = sum(1 for _ in fh)
        was = sh(f"git show HEAD:{path}").stdout.count("\n")
        if was and now < was * min_ratio:
            sh(f"git checkout HEAD -- {path}")
            bad.append(f"{path}: {now} lines vs {was} at HEAD — RESTORED, not committed")
    for b in bad:
        log(f"  *** CONFIG COLLAPSE REFUSED — {b}")
    return not bad


def gate(tag, keep, jobs, run_id=None):
    # Any main drafts that slipped through (an older wave's cards) are PARKED for the periodic main
    # batch rather than gated inline — see draw_wave's note on why main is off the critical path.
    mains = [k for k in keep if k["binary"] == "main"]
    keep = [k for k in keep if k["binary"] != "main"]
    if mains:
        os.makedirs(".run/main_queue", exist_ok=True)
        json.dump([{"fn": m["fn"], "draft": m["draft"], "binary": "main"} for m in mains],
                  open(f".run/main_queue/{tag}.json", "w"), indent=1)
        log(f"  main: {len(mains)} drafts PARKED to .run/main_queue/{tag}.json "
            f"(gate them with tools/gate_main.py when no wave is waiting)")
        mains = []
    # PER-RUN staging dir. Reusing `.run/sweep_<tag>` let a KILLED gate's staged drafts survive
    # into the next gate of the same tag: measured wave `an` staging 697 drafts into a directory
    # that held 3,186, so every per-binary group carried stale bodies and failed as a group —
    # 208 reloc-AGREE drafts banked 0. rmtree is not enough when a crashed or concurrent run may
    # have written the same path; a unique path makes the contamination impossible, not unlikely.
    d = f".run/sweep_{tag}" + (f".{run_id}" if run_id else "")
    shutil.rmtree(d, ignore_errors=True)
    for b in keep:
        bd = os.path.join(d, b["binary"])
        os.makedirs(bd, exist_ok=True)
        shutil.copy(b["draft"], os.path.join(bd, b["fn"] + ".c"))
    if not glob.glob(d + "/*/*.c"):
        return gate_main_batch(tag, mains)
    # NEVER blind-revert a dirty tree. `git checkout -- src/ config/` at gate entry was written for
    # "a failed gate left residue", but it cannot tell residue from REAL BANKED WORK that simply has
    # not been committed yet — and a concurrent lane (the free A-prop sweep) leaves exactly that:
    # sweep_parallel gates with commit=False, so hundreds of banked functions sit uncommitted by
    # design. Running this loop against that tree would have destroyed them. Commit first, ask
    # questions never.
    dirty = sh("git status --porcelain -- src/ config/").stdout.strip()
    if dirty:
        n_files = len(dirty.splitlines())
        # R42 CARVE-OUT: never adopt main's sources. R42 says commit a dirty tree rather than
        # revert it, because a per-binary gate leaves PROVEN banks uncommitted and reverting
        # destroys them. main is the exception: gate_main writes UNVERIFIED bodies into src/800*.c
        # and src/*.c, so a dirty main source is not banked work — it is an abandoned batch.
        # Measured P31 S58: two auto-commits adopted 10 such bodies, main built to the wrong SHA
        # for nine hours, and R22 ran 212/213 without anyone noticing the guarantee was partial.
        main_dirty = [l.split()[-1] for l in dirty.splitlines()
                      if re.match(r'^\s*[MARD?]+\s+src/[^/]+\.c$', l)]
        if main_dirty:
            # NEITHER COMMIT NOR REVERT main's TUs (S59). The old carve-out REVERTED them here —
            # and lost a TOCTOU race with the live gate_main, whose substitute() re-wrote
            # src/800.c between our checkout and the `git add -A` below: auto-commit commit:2693
            # adopted two unverified bodies at 14:57:01 (14 s after a main bisect chunk banked —
            # exactly one chunk cadence), main built RED until 18:43, and the main lane burned
            # four 200-card draft rounds against it, banking zero. Reverting is not safe either:
            # after a GREEN gate, byte-proven work sits uncommitted in these files until
            # main_lane commits it moments later. One writer (gate_main), one committer
            # (main_lane); this lane leaves main's TUs alone in both directions.
            log(f"  leaving dirty main TU(s) alone — gate_main/main_lane own them: {main_dirty}")
        log(f"  tree dirty at gate entry ({n_files} files) — committing it rather than reverting")
        config_sane()
        sh("git add -A src/ config/")
        unstage_main_tus()
        r = sh('git commit -q -m "chore(decomp): commit in-tree banked work before the next gate\n\n'
               'Uncommitted src/ changes found at gate entry. These are banked functions from a lane '
               'that gates with commit=False, not residue — preserved, not reverted. Top-level '
               'src/*.c (main TUs) are excluded by construction (S59)."')
        leftover = [l for l in sh("git status --porcelain -- src/ config/").stdout.splitlines()
                    if l.strip() and not re.match(r'^\s*[MARD?]+\s+src/[^/]+\.c$', l)]
        if r.returncode != 0 and leftover:
            log("  ! could not commit the dirty tree — REFUSING to gate (would risk real work)")
            return 0, []
    t0 = time.time()
    r = sh(f"{PY} tools/sweep_parallel.py --drafts {d} -j {jobs}", timeout=28800, quiet=False)
    banked = []
    for f in glob.glob(".run/auto/bulk/*.verified.txt"):
        if os.path.getmtime(f) >= t0:
            banked += [l.strip() for l in open(f) if l.strip()]
    # COMMIT THE OVERLAY BANKS BEFORE main RUNS. gate_main substitutes into src/ and REVERTS on a
    # failing batch, and it cannot distinguish its own substitution from the overlay work that
    # sweep_parallel left uncommitted (it gates with commit=False by design). Measured P31 S58 on
    # wave aj: 61 overlay functions banked, gate_main then bisected the main batch for 95 minutes
    # and reverted all 61 — every one back to an INCLUDE_ASM stub, verified against corpus.stubs.
    # Nothing was lost permanently (the drafts survive in .run/wave_<tag>/) but the gate cycle was.
    # Uncommitted banked work is fragile; commit it the moment it exists.
    if banked:
        config_sane()
        sh("git add -A src/ config/")
        unstage_main_tus()
        sh(f'git commit -q -m "feat(decomp): ox wave {tag} overlays — {len(banked)} banked\n\n'
           f'Committed before the main batch: gate_main reverts on failure and would take these '
           f'with it."')
        log(f"  committed {len(banked)} overlay banks before the main batch")

    # main batches are CHUNKED. gate_main bisects on failure and each bisection step is a full
    # clean EXE rebuild (~2-4 min), so one bad draft in a 29-draft batch is hours. Chunks of 8
    # bound that to a few rebuilds per chunk, and a poisoned chunk cannot stall the rest.
    mn, mb = 0, []
    for i in range(0, len(mains), 8):
        chunk = mains[i:i + 8]
        cn, cb = gate_main_batch(f"{tag}_m{i//8}", chunk)
        mn += cn
        mb += cb
    return len(banked) + mn, banked + mb


def commit(tag, n, banked):
    if not sh("git status --porcelain -- src/ config/").stdout.strip():
        return None
    config_sane()
    sh("git add -A src/ config/")
    unstage_main_tus()
    msg = (f"feat(decomp): ox wave {tag} — {n} banked\\n\\n"
           f"Card-fuelled ox drafts, reloc_identity pre-filtered, gated via sweep_parallel.\\n"
           f"{' '.join(banked[:40])}{' …' if len(banked) > 40 else ''}")
    r = sh(f'git commit -q -m "{msg}"')
    return sh("git rev-parse --short HEAD").stdout.strip() if r.returncode == 0 else None


def parse_lanes(spec, single_model, workers):
    """'model:n[:K=V;K=V],...' -> [(model, n, env)]. Absent spec = one lane on `single_model`.

    When a spec IS given its per-lane counts are proportions, rescaled to the campaign's current
    worker total — so the step-up/hold policy keeps governing total concurrency and the spec only
    decides how that total is SPLIT between pools.
    """
    if not spec:
        return [(single_model, workers, {})]
    lanes, total = [], 0
    for part in spec.split(","):
        bits = part.split(":")
        model, n = bits[0], int(bits[1])
        env = {}
        if len(bits) > 2 and bits[2]:
            for kv in bits[2].split(";"):
                if "=" in kv:
                    k, v = kv.split("=", 1); env[k] = v
        lanes.append([model, n, env]); total += n
    if total and total != workers:
        scaled = [[m, max(1, round(n * workers / total)), e] for m, n, e in lanes]
        lanes = scaled
    return [(m, n, e) for m, n, e in lanes]


READY = ".run/ready"
DRAWLOCK = ".run/auto/draw.lock"


def _drawlock():
    """Serializes DRAW against GATE — never against drafting.

    build_wave_atlas reads corpus.stubs(), which misreports substituted drafts while a gate is
    mid-flight and would silently skip real stubs as already-banked. Drafting touches neither, so
    it runs unlocked and uninterrupted, which is the entire point of the split.
    """
    os.makedirs(".run/auto", exist_ok=True)
    fh = open(DRAWLOCK, "w")
    fcntl.flock(fh, fcntl.LOCK_EX)
    return fh


def _drawlock_nb():
    """Non-blocking draw lock. Returns None if a gate holds it — the caller must NOT wait."""
    os.makedirs(".run/auto", exist_ok=True)
    fh = open(DRAWLOCK, "w")
    try:
        fcntl.flock(fh, fcntl.LOCK_EX | fcntl.LOCK_NB)
        return fh
    except BlockingIOError:
        fh.close()
        return None


def _predrawn(skip_tag):
    """A wave whose cards exist but which has never been drafted — free work while a gate runs."""
    for p in sorted(glob.glob(".run/wave_??_cards.json"), key=os.path.getmtime):
        t = os.path.basename(p)[5:7]
        if t == skip_tag:
            continue
        if os.path.exists(f"{READY}/{t}.json"):        # already drafted and queued
            continue
        if glob.glob(f".run/wave_{t}/shard*/*.c"):     # already has drafts
            continue
        return t, p
    return None


def run_drafter(a):
    """THE LANE THAT MUST NEVER STOP. Draw -> shard -> draft -> publish a ready marker. Forever.

    WHY THIS IS SEPARATE (P31 S58, measured): over five hours the drafting fleet was IDLE 53% of
    the time — 162 minutes — and 139 of those were a single stretch where the supervisor was killed
    to pick up a code change. Gating cost 18 minutes across the same window. So the dominant loss
    was never gate contention, and a worktree gate lane would have addressed the small half. What
    actually costs a free-model window is coupling the drafting lane's LIFETIME to a process you
    need to restart. Split apart, the gater can be killed, edited and relaunched at will while 640+
    agents keep drafting.
    """
    tags = [x + y for x in string.ascii_lowercase for y in string.ascii_lowercase]
    bands = [tuple(int(x) for x in b.split("-")) for b in a.bands.split(",")]
    lane_specs = ([{"name": n, "levers": lv or None}
                   for n, _, lv in (p.partition(":") for p in a.lanes.split(","))]
                  if a.lanes else [{"name": "default", "levers": None}])
    os.makedirs(READY, exist_ok=True)
    # ROTATION INDEX DERIVED FROM DISK, not from a counter that resets on restart. With `w = 0` at
    # every launch, a lane list of [default, tells] only ever reaches index 0 unless the process
    # survives a full wave — and across a day of restarts (code fixes, two power cuts) the `tells`
    # lane was never once drawn, while holding 86,602 instructions nobody had touched. Same class
    # as R33: derive from the invariant (waves on disk) rather than from in-process state.
    w = len(glob.glob(".run/wave_??_cards.json"))
    log(f"drafter: resuming rotation at index {w} -> lane "
        f"{lane_specs[w % len(lane_specs)]['name']}, band {bands[w % len(bands)]}")
    while not os.path.exists(STOP):
        # Bound the run-ahead on DRAWING only. Drawing 40 waves while the gater lags would strand
        # them all as "already-waved"; DRAFTING a wave whose cards already exist strands nothing.
        # Conflating the two stopped the fleet dead: with queue_depth=2 and two waves queued, the
        # drafter slept while `aa` and `ai` sat pre-drawn and undrafted (measured P31 S58).
        backlogged = len(glob.glob(f"{READY}/*.json")) >= a.queue_depth
        if backlogged:
            pre = _predrawn(None)
            if not pre:
                log(f"  gater backlogged ({a.queue_depth}+ waves) and nothing pre-drawn — waiting")
                time.sleep(60)
                continue
        cr = credits_left()
        if cr is not None and cr < a.credit_floor:
            log(f"drafter: credit floor (${cr:.2f}) — stopping"); break
        used = {os.path.basename(p)[5:7] for p in glob.glob(".run/wave_??_cards.json")}
        tag = next((t for t in tags if t not in used), None)
        if not tag:
            log("drafter: out of wave tags"); break
        lane, band = lane_specs[w % len(lane_specs)], bands[w % len(bands)]
        w += 1
        log(f"=== DRAFT {tag} · lane {lane['name']} · band {band[0]}-{band[1]} · "
            f"{a.workers} workers ===")
        # NON-BLOCKING draw. The gater holds this lock for its WHOLE gate (substituted drafts make
        # corpus.stubs() lie), so a blocking acquire here parks the entire drafting fleet for the
        # duration of every gate — measured 7 minutes idle with 0 agents while wave `an` gated, and
        # it would recur on every wave. Drafting is the clock-limited resource; it must never wait
        # on gating. If the lock is busy we draft a wave that was PRE-DRAWN earlier instead, and
        # only sleep when there is genuinely nothing drawn to work on.
        lk = None if backlogged else _drawlock_nb()
        if lk is None:
            pre = _predrawn(tag)
            if pre:
                tag, cards = pre
                log(f"  gate in progress — drafting PRE-DRAWN wave {tag} instead of waiting")
            else:
                # DRAW ANYWAY (P31 S59). The blocking wait here dates from when a draw during a gate
                # was genuinely unsafe: corpus.stubs() misreports for a binary whose sources carry a
                # substituted draft (R35), so the draw refused outright. Since 15:23 build_wave_atlas
                # EXCLUDES exactly the binaries whose per-binary gate lock is held and draws from the
                # rest — the hazard is handled at the right granularity, and this wait now protects
                # nothing while starving the one resource that is clock-limited.
                # Measured 23:20: the maintenance lane held the draw lock for a multi-minute sweep,
                # the pre-draw buffer happened to be empty, and the drafting fleet sat at 13 agents /
                # 3 req/min printing this line every 30 s.
                log("  draw lock busy and nothing pre-drawn — drawing anyway "
                    "(mid-gate binaries are excluded by the draw itself)")
                cards = draw_wave(tag, a.cards_per_wave, band, lane.get("levers"))
        else:
            cards = draw_wave(tag, a.cards_per_wave, band, lane.get("levers"))
            lk.close()
        if not cards:
            log(f"  {tag}: draw failed — retrying next cycle"); time.sleep(30); continue
        targets = shard_targets(tag, cards, a.workers)
        t0 = time.time()
        procs = draft(tag, parse_lanes(a.models, a.model, a.workers), a.maxtok, a.max_turns,
                      wave_lane=lane['name'])

        # PRE-DRAW THE NEXT WAVE **AFTER** THE SHARDS ARE RUNNING, never before. Drawing takes
        # minutes of CPU (build_wave_atlas over the whole atlas), and doing it between the draw and
        # the launch left the fleet at 8 agents while a card job ran — the pre-draw, whose entire
        # purpose is to prevent idle, was causing it. Now it overlaps the drafting it exists to feed.
        nxt = next((t for t in tags
                    if t not in {os.path.basename(q)[5:7]
                                 for q in glob.glob(".run/wave_??_cards.json")}), None)
        if nxt:
            nlane = lane_specs[w % len(lane_specs)]
            nband = bands[w % len(bands)]
            lk2 = _drawlock_nb()
            if lk2 is not None:
                log(f"  pre-drawing {nxt} (lane {nlane['name']}, band {nband[0]}-{nband[1]}) "
                    f"while {tag} drafts")
                draw_wave(nxt, a.cards_per_wave, nband, nlane.get("levers"))
                lk2.close()

        wait_for_tail(tag, procs)
        finish_wave_async(tag, procs, cards, len(targets), t0, a.workers, band, lane)
    log("drafter: finished")


def run_gater(a):
    """Consume ready waves: reloc pre-filter -> gate -> commit -> harvest -> ledger. Restartable
    at any moment; the drafter neither knows nor cares."""
    os.makedirs(READY, exist_ok=True)
    while not os.path.exists(STOP):
        ready = sorted(glob.glob(f"{READY}/*.json"), key=os.path.getmtime)
        if not ready:
            time.sleep(20)
            continue
        meta = json.load(open(ready[0]))
        tag = meta["tag"]
        t0 = meta.get("t0", time.time())
        drafts = sorted(glob.glob(f".run/wave_{tag}/shard*/*.c"))
        log(f"=== GATE {tag} · {len(drafts)} drafts ===")
        keep, counts = reloc_filter(tag, drafts, meta["cards"])
        log(f"  reloc_identity: {counts} -> gating {len(keep)}")
        lk = _drawlock()
        try:
            n, banked = gate(tag, keep, a.gate_jobs, run_id=str(os.getpid()))
        finally:
            lk.close()
        sha = commit(tag, n, banked)
        hp = f".run/idiom_candidates.{tag}.md"
        hr = sh(f"{PY} tools/idiom_harvest.py --waves {tag} --out {hp}", timeout=1800)
        hl = (hr.stdout or "").strip().splitlines()
        log(f"  harvest: {hl[-1] if hl else 'FAILED'}")
        rs = rate_slice(t0)
        row = {"wave": tag, "t": t0, "wall_min": round((time.time() - t0) / 60, 1),
               "workers": meta.get("workers"), "band": meta.get("band"), "lane": meta.get("lane"),
               "targets": meta.get("targets"), "drafts": len(drafts),
               "truncated_turns": meta.get("trunc"), "reloc": counts, "gated": len(keep),
               "banked": n, "commit": sha, "harvest": hl[-1] if hl else None,
               "credit_left": credits_left(), **mem_snapshot(), **rs}
        with open(LEDGER, "a") as fh:
            fh.write(json.dumps(row) + "\n")
        log(f"  GATE {tag}: banked {n}/{len(keep)} gated of {len(drafts)} drafts · "
            f"{rs['requests']} req · {rs['h429']} 429 · {row['wall_min']}min · {sha}")
        os.remove(ready[0])
    log("gater: finished")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--waves", type=int, default=8)
    ap.add_argument("--workers", type=int, default=24)
    ap.add_argument("--max-workers", type=int, default=64)
    ap.add_argument("--step", type=int, default=8, help="worker increase after a 429-free wave")
    ap.add_argument("--cards-per-wave", type=int, default=220)
    ap.add_argument("--max-ins", type=int, default=50, help="ignored when --bands is set")
    ap.add_argument("--bands", default="5-50,50-120,120-400,400-2000",
                    help="comma-separated MIN-MAX instruction bands, rotated one per wave. Sub-50 is "
                         "73.5%% of the OPEN COUNT but the mass is elsewhere: groups with a >=120-ins "
                         "exemplar hold 141,724 instructions (28%% of the frontier) against the sub-50 "
                         "pool's much smaller mass. A campaign that only ever draws sub-50 optimises "
                         "the function counter and leaves the instruction counter alone — and ox has "
                         "already cracked 611 instructions in one sitting, so the band is not a "
                         "capability limit.")
    ap.add_argument("--maxtok", type=int, default=8000)
    ap.add_argument("--model", default="stealth/ox-alpha", help="single-lane shorthand; --models wins")
    ap.add_argument("--models", default=None,
                    help="MODEL:WORKERS[:ENV=V;ENV=V],... — run several provider pools at once, e.g. "
                         "'stealth/ox-alpha:32,deepseek/deepseek-v4-flash-0731:16:REASON_EFFORT=high'. "
                         "Total workers = the sum, and --workers/--step scaling applies to that sum.")
    ap.add_argument("--max-turns", type=int, default=24)
    ap.add_argument("--gate-jobs", type=int, default=10)
    ap.add_argument("--credit-floor", type=float, default=2.0)
    ap.add_argument("--lanes", default=None,
                    help="NAME:LEVERS,... rotated one per wave. Default is the historical single "
                         "lane. The 'tell' levers were EXCLUDED from every wave ab..ah by "
                         "build_wave_atlas's default and hold 86,602 instructions "
                         "(extend-tell 76,972 · swaprepeat-tell 9,211 · s16-div-tell 419) — more "
                         "than most of what the default lane has left. jtbl/o0/cc1 are NOT here on "
                         "purpose: jtbl needs a carve before its drafts are bankable at all "
                         "(tools/idiom_serial.py), and o0/cc1 gate differently — drafting them into "
                         "this loop would produce verified drafts that cannot bank, which is "
                         "exactly the trap that cost S57 its whole jtbl result.")
    ap.add_argument("--sustained", type=int, default=3,
                    help="consecutive minutes carrying a provider 429 before it counts as a real "
                         "ceiling rather than a burst (default 3)")
    ap.add_argument("--start-tag", default=None, help="two-letter tag to start from (default: next free)")
    ap.add_argument("--drafter", action="store_true",
                    help="run ONLY the drafting lane, forever. Never stop this process to ship a "
                         "code change — that is what cost 139 of 162 idle minutes on 2026-08-23.")
    ap.add_argument("--gater", action="store_true",
                    help="run ONLY the gate/commit/harvest lane, forever. Safe to kill and restart "
                         "at any moment; drafting is unaffected.")
    ap.add_argument("--queue-depth", type=int, default=2,
                    help="how many drafted-but-ungated waves the drafter may run ahead")
    ap.add_argument("--gate-only", default=None, metavar="TAG",
                    help="skip drawing and drafting: pre-filter and gate the drafts ALREADY sitting "
                         "in .run/wave_<TAG>/shard*/, then commit. For a wave drafted outside the "
                         "loop (or one whose gate step was interrupted) — the drafts are on disk and "
                         "re-drafting them would spend the model again to reproduce what exists.")
    a = ap.parse_args()

    if a.drafter:
        return run_drafter(a)
    if a.gater:
        return run_gater(a)
    if a.gate_only:
        tag = a.gate_only
        t0 = time.time()
        cards = f".run/wave_{tag}_cards.json"
        drafts = sorted(glob.glob(f".run/wave_{tag}/shard*/*.c"))
        log(f"gate-only wave {tag}: {len(drafts)} drafts on disk")
        keep, counts = reloc_filter(tag, drafts, cards)
        log(f"  reloc_identity: {counts} -> gating {len(keep)}")
        n, banked = gate(tag, keep, a.gate_jobs)
        sha = commit(tag, n, banked)
        rs = rate_slice(t0)
        row = {"wave": tag, "t": t0, "wall_min": round((time.time() - t0) / 60, 1),
               "workers": 0, "targets": len(drafts), "drafts": len(drafts), "truncated_turns": None,
               "reloc": counts, "gated": len(keep), "banked": n, "commit": sha,
               "mode": "gate-only", "credit_left": credits_left(), **rs}
        with open(LEDGER, "a") as fh:
            fh.write(json.dumps(row) + "\n")
        log(f"  WAVE {tag} (gate-only): banked {n}/{len(keep)} gated of {len(drafts)} drafts · {sha}")
        return 0

    tags = [x + y for x in string.ascii_lowercase for y in string.ascii_lowercase]
    used = {os.path.basename(p)[5:7] for p in glob.glob(".run/wave_??_cards.json")}
    pending = [t for t in tags if t not in used]
    if a.start_tag:
        pending = tags[tags.index(a.start_tag):]

    bands = [tuple(int(x) for x in b.split("-")) for b in a.bands.split(",")]
    if a.lanes:
        lane_specs = []
        for part in a.lanes.split(","):
            nm, _, lv = part.partition(":")
            lane_specs.append({"name": nm, "levers": lv or None})
    else:
        lane_specs = [{"name": "default", "levers": None}]
    log(f"lanes: {[l['name'] for l in lane_specs]}")
    workers, last_clean = a.workers, a.workers
    prev_rpm, stalls = 0.0, 0
    inflight = None
    log(f"campaign: {a.waves} waves x {a.cards_per_wave} cards, {workers} workers, model {a.model}")
    for w in range(a.waves):
        if os.path.exists(STOP):
            log("STOP file present — ending campaign"); break
        cr = credits_left()
        if cr is not None and cr < a.credit_floor:
            log(f"credit floor reached (${cr:.2f} < ${a.credit_floor}) — ending campaign"); break
        # PIPELINED: wave N+1 DRAFTS while wave N GATES (docs/concurrency-design.md lane D || G).
        # Drafting writes only .run/ and match_one works in per-pid scratch; gating writes src/.
        # Serially, every gate left 640 agents idle — ak's gate ran 8 minutes with zero drafting,
        # and on a clock-limited free-model window that is the single largest waste in the loop.
        #
        # The DRAW must still happen BEFORE the gate starts: build_wave_atlas reads corpus.stubs(),
        # which misreports substituted drafts mid-gate and would silently skip them as
        # already-banked. So the order is: draw N+1 -> start N+1 drafting -> gate N.
        if inflight is None:
            tag = pending[w] if w < len(pending) else tags[len(used) + w]
            lane = lane_specs[w % len(lane_specs)]
            band = bands[w % len(bands)]
            log(f"=== WAVE {tag} ({w+1}/{a.waves}) · {workers} workers · "
                f"${cr if cr is None else round(cr,2)} credit ===")
            log(f"  lane {lane['name']} · band {band[0]}-{band[1]} instructions")
            cards = draw_wave(tag, a.cards_per_wave, band, lane.get("levers"))
            if not cards:
                log("  draw failed — skipping wave"); continue
            targets = shard_targets(tag, cards, workers)
            log(f"  {len(targets)} targets sharded")
            procs = draft(tag, parse_lanes(a.models, a.model, workers), a.maxtok, a.max_turns,
                          wave_lane=lane['name'])
            inflight = (tag, cards, targets, procs, time.time())

        tag, cards, targets, procs, t0 = inflight
        inflight = None
        drafts, trunc = collect_drafts(tag, procs)
        log(f"  WAVE {tag}: {len(drafts)} drafts produced ({trunc} truncated turns)")

        # Start the NEXT wave drafting before gating this one — this is the whole point.
        if w + 1 < a.waves and not os.path.exists(STOP):
            ntag = pending[w + 1] if w + 1 < len(pending) else tags[len(used) + w + 1]
            nlane = lane_specs[(w + 1) % len(lane_specs)]
            nband = bands[(w + 1) % len(bands)]
            log(f"=== WAVE {ntag} ({w+2}/{a.waves}) drafting AHEAD · lane {nlane['name']} · "
                f"band {nband[0]}-{nband[1]} ===")
            ncards = draw_wave(ntag, a.cards_per_wave, nband, nlane.get("levers"))
            if ncards:
                ntargets = shard_targets(ntag, ncards, workers)
                nprocs = draft(ntag, parse_lanes(a.models, a.model, workers), a.maxtok, a.max_turns,
                               wave_lane=nlane['name'])
                inflight = (ntag, ncards, ntargets, nprocs, time.time())
            else:
                log(f"  wave {ntag}: draw failed — next cycle will redraw")
        keep, counts = reloc_filter(tag, drafts, cards)
        log(f"  reloc_identity: {counts} -> gating {len(keep)}")
        n, banked = gate(tag, keep, a.gate_jobs)
        sha = commit(tag, n, banked)
        rs = rate_slice(t0)
        row = {"wave": tag, "t": t0, "wall_min": round((time.time() - t0) / 60, 1),
               "workers": workers, "targets": len(targets), "drafts": len(drafts),
               "truncated_turns": trunc, "reloc": counts, "gated": len(keep),
               "banked": n, "commit": sha, "credit_left": credits_left(),
               **mem_snapshot(), **rs}
        with open(LEDGER, "a") as fh:
            fh.write(json.dumps(row) + "\n")
        log(f"  WAVE {tag}: banked {n}/{len(keep)} gated of {len(drafts)} drafts · "
            f"{rs['requests']} req @ {rs['req_per_min']}/min · {rs['h429']} 429 "
            f"(sustained {rs['sustained_min']} min) · {row['wall_min']}min · {sha}")

        # HARVEST BEFORE THE NEXT DRAW (Drew, 2026-08-23 — "that's how our whole system works").
        # R16's flywheel only turns if the lesson reaches the knowledge base BEFORE the next wave
        # is drafted; otherwise every wave re-learns what the last one already paid for. Waves
        # ab..ag banked 1,262 functions and emitted 211 "the cookbook did not cover this" notes,
        # none of which reached docs/ — that is the failure this step exists to prevent. Only
        # notes from BYTE-GATE-BANKED functions are harvested (idiom_harvest derives banked-ness
        # from corpus.stubs; a match_one MATCH that the gate rejected can carry a WRONG lesson).
        hp = f".run/idiom_candidates.{tag}.md"
        hr = sh(f"{PY} tools/idiom_harvest.py --waves {tag} --out {hp}", timeout=1800)
        hline = (hr.stdout or "").strip().splitlines()
        log(f"  harvest: {hline[-1] if hline else 'FAILED — ' + (hr.stderr or '')[-160:]}")
        row["harvest"] = hline[-1] if hline else None

        # SCALING DECISION. Three ways to stop, and only three:
        #   1. PLATFORM 429 — OpenRouter refusing this account. That IS the ceiling.
        #   2. SUSTAINED provider 429s — >= --sustained consecutive minutes carrying one. A burst
        #      that resumes is not this, and must not be treated as this.
        #   3. THROUGHPUT STALL — more workers stopped buying requests/minute. The honest test:
        #      the ceiling can be reached with zero 429s if the provider simply serves us slower.
        if rs["platform_429"]:
            log(f"  PLATFORM 429 x{rs['platform_429']} — that is OUR account limit. "
                f"Holding at {last_clean}.")
            workers = last_clean
        elif rs["sustained_min"] >= a.sustained:
            log(f"  provider 429s SUSTAINED across {rs['sustained_min']} consecutive minutes "
                f"(>= {a.sustained}) — treating as a real ceiling, holding at {last_clean}")
            workers = last_clean
        elif prev_rpm and rs["req_per_min"] and rs["req_per_min"] < prev_rpm * 1.10:
            stalls += 1
            log(f"  throughput {rs['req_per_min']}/min vs {prev_rpm}/min at fewer workers "
                f"— +10% not bought (stall {stalls}/2)")
            if stalls >= 2:
                log(f"  two consecutive stalls — ceiling found near {workers} workers, holding")
                workers = last_clean
            else:
                last_clean = workers
                workers = min(a.max_workers, workers + a.step)
        else:
            stalls = 0
            if rs["h429"]:
                log(f"  {rs['h429']} 429s but only a burst ({rs['h429_src']}) — NOT our limit, "
                    f"continuing to scale")
            last_clean = workers
            workers = min(a.max_workers, workers + a.step)
            log(f"  stepping workers to {workers}")
        if rs["req_per_min"]:
            prev_rpm = rs["req_per_min"]
    log("campaign finished")


if __name__ == "__main__":
    sys.exit(main() or 0)

#!/usr/bin/env python3
"""lora_grind.py — the free local-model MASS-RUN (the LoRA draft source for the grinder flywheel).

Rotates over every binary with open small stubs, drafts each with the fine-tuned local model
(tools/api_draft.py LEAN, served by LM Studio on the GPU), and banks the byte-matches through the
shared gate_stage (sole arbiter, G3/P9). Near-misses land in the backlog -> grinder.py (the permuter)
closes the regalloc/schedule residuals the LoRA leaves -> SYNERGY. Banks grow the corpus for the next
retrain; the classified near-miss histogram (written to the stats file) is the readout of which idioms
the model still misses -> the corpus-v3/v4 priority list (the data-driven flywheel).

LLM cost: $0 (local). Runs unattended for days alongside grinder.py under auto_supervisor.sh.
SAFE EXIT: touch .run/auto/STOP (tools/auto_stop.sh) — finishes the current batch+gate, exits 0.
HEARTBEAT: .run/auto/lora_grind_heartbeat.json. STATS: .run/auto/lora_grind_stats.json.

Env: API_BASE, MODEL (the served fine-tuned model). Usage:
  API_BASE=http://192.168.1.113:1234/v1 MODEL=bfm-local/bfm-match-7b-v2 \
    tools/lora_grind.py [--max-nins 15] [--batch 12] [--iters 3] [--propagate-every 8] [--once]
"""
import argparse, glob, json, os, re, subprocess, sys, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gate_stage, backlog

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AUTODIR = os.path.join(REPO, ".run/auto")
STOP = os.path.join(AUTODIR, "STOP")
HB = os.path.join(AUTODIR, "lora_grind_heartbeat.json")
STATS = os.path.join(AUTODIR, "lora_grind_stats.json")
TRIED = os.path.join(AUTODIR, "lora_grind_tried.json")
DRAFTS = os.path.join(AUTODIR, "lora_grind_drafts")
STUB_RE = re.compile(r'INCLUDE_ASM\([^,]+,\s*(func_[0-9A-Fa-f]+)\)')


def log(m):
    print("[lora_grind] " + m, flush=True)


def binaries():
    """every binary with a locked good-sha (config/check.<b>.sha)."""
    return sorted(os.path.basename(f)[6:-4] for f in glob.glob(os.path.join(REPO, "config/check.*.sha")))


def good_sha(b):
    p = os.path.join(REPO, "config/check.%s.sha" % b)
    return open(p).read().split()[0] if os.path.exists(p) else None  # bare hash (sha1sum format)


_SIGS = None


def _load_sigs():
    """Lazy {overlay -> {addr_int -> h_exact}} from the 134 .run/sig.ov_*.jsonl (make sig-overlays).
    The SAME data dedup_propagate reaches from, so a reach>=N fn here is exactly one it will stamp
    ×reach after the bank (and a fn the sigs miss wouldn't propagate anyway → correctly excluded)."""
    global _SIGS
    if _SIGS is None:
        _SIGS = {}
        for p in glob.glob(os.path.join(REPO, ".run/sig.ov_*.jsonl")):
            ov = os.path.basename(p)[4:-6]            # sig.ov_SC01_000.jsonl -> ov_SC01_000
            d = {}
            for line in open(p):
                line = line.strip()
                if not line:
                    continue
                r = json.loads(line)
                nm = r.get("name", "")
                if nm.startswith("func_"):
                    try:
                        d[int(nm[5:], 16)] = r.get("h_exact")
                    except ValueError:
                        pass
            _SIGS[ov] = d
    return _SIGS


def reach_of(binary, fn):
    """#overlays byte-identical (h_exact) to `binary` at fn's addr; None if binary/fn isn't signed.
    reach>=2 = a shared fn that propagates ×reach via dedup_propagate after it banks (the fleet lever)."""
    sigs = _load_sigs()
    try:
        addr = int(fn[5:], 16)
    except ValueError:
        return None
    h = sigs.get(binary, {}).get(addr)
    if not h:
        return None
    return sum(1 for ov in sigs if sigs[ov].get(addr) == h)


def nins(s_path):
    return sum(1 for l in open(s_path)
               if re.match(r'\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s*\*/', l))


def open_stubs(b, max_nins, tried, min_reach=1, min_nins=1):
    """still-INCLUDE_ASM funcs for binary b (main + split .c) whose .s exists and is in
    [min_nins, max_nins] ins. min_nins>1 skips the (often saturated) smallest band so a later pass can
    target a fresh larger band without re-grinding the small failures.
    min_reach>1 keeps only fns byte-identical across >= min_reach overlays (the propagation multiplier)
    and ranks high-reach-first; min_reach=1 keeps all, smallest-first (no reach cost)."""
    stubbed = set()
    for cf in glob.glob(os.path.join(REPO, "src/%s/%s*.c" % (b, b))):
        stubbed |= set(STUB_RE.findall(open(cf).read()))
    out = []
    for fn in stubbed:
        if fn in tried:
            continue
        for sd in glob.glob(os.path.join(REPO, "asm/%s/nonmatchings/*/%s.s" % (b, fn))):
            n = nins(sd)
            if min_nins <= n <= max_nins:
                rch = reach_of(b, fn) if min_reach > 1 else None
                if min_reach > 1 and (rch is None or rch < min_reach):
                    break                               # below the reach threshold (or unsigned) -> skip
                out.append({"name": fn, "addr": "0x" + fn[5:].lower(), "nins": n, "reach": rch,
                            "class": "WAVE", "asm": os.path.relpath(sd, REPO), "ghidra_c": ""})
                break
    if min_reach > 1:
        out.sort(key=lambda t: (-(t.get("reach") or 0), t["nins"]))   # leverage: high-reach, then small
    else:
        out.sort(key=lambda t: t["nins"])
    return out


def draft(targets, api_base, model, iters):
    """run the fine-tuned model (LEAN) over a batch -> DRAFTS dir; returns the dir."""
    os.makedirs(DRAFTS, exist_ok=True)
    for f in glob.glob(os.path.join(DRAFTS, "*.c")):
        os.remove(f)
    tf = os.path.join(AUTODIR, "lora_grind_targets.json")
    json.dump(targets, open(tf, "w"))
    env = dict(os.environ, LEAN="1", NORMALIZE_ASM="0", API_BASE=api_base, MODEL=model, TEMP="0.2")
    subprocess.run([".venv/bin/python", "tools/api_draft.py", "--targets", tf,
                    "--out", os.path.relpath(DRAFTS, REPO), "--iters", str(iters)],
                   cwd=REPO, env=env, capture_output=True, timeout=3600)
    return DRAFTS


def gate_binary(b, draftdir):
    """gate_stage the drafts for binary b — main .c, then any split (_a/_o0) with --src-file.
    propagate=False here (the loop runs a periodic propagate sweep); commit=True banks to git."""
    banked = []
    gs = good_sha(b)
    if not gs:
        return banked
    # main
    r = gate_stage.run_gate(os.path.relpath(draftdir, REPO), binary=b, good_sha=gs,
                            propagate=False, source_tag="lora-grind", commit=True)
    banked += r.get("verified", [])
    # split files
    for split in glob.glob(os.path.join(REPO, "src/%s/%s_*.c" % (b, b))):
        name = os.path.basename(split)[:-2]          # e.g. ov_SC01_077_a
        sub = "asm/%s/nonmatchings/%s" % (b, name)
        if not os.path.isdir(os.path.join(REPO, sub)):
            continue
        r = gate_stage.run_gate(os.path.relpath(draftdir, REPO), binary=b,
                                src="src/%s/%s.c" % (b, name), asm=sub, good_sha=gs,
                                propagate=False, source_tag="lora-grind", commit=True,
                                src_file=name + ".c")
        banked += r.get("verified", [])
    return banked


def near_class_hist():
    """the backlog's open near-miss histogram by residual class — the 'missing idioms' signal."""
    import collections
    h = collections.Counter()
    for r in backlog.load_best():
        if r.get("status") == "near":
            h[(r.get("klass") or "other").split()[0]] += 1
    return dict(h)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--max-nins", type=int, default=15)
    ap.add_argument("--min-nins", type=int, default=1,
                    help="skip stubs smaller than N ins — target a fresh larger band without re-grinding "
                         "the (often saturated) small failures; default 1 = no floor")
    ap.add_argument("--min-reach", type=int, default=1,
                    help="only draft fns byte-identical across >= N overlays — the x reach propagation "
                         "multiplier (the fleet lever); default 1 = all open stubs, smallest-first")
    ap.add_argument("--batch", type=int, default=12)
    ap.add_argument("--iters", type=int, default=3)
    ap.add_argument("--propagate-every", type=int, default=8, help="run a fleet propagate sweep every N batches")
    ap.add_argument("--idle-secs", type=int, default=120)
    ap.add_argument("--binaries", default=None, help="comma-list to restrict (default: all)")
    ap.add_argument("--max-batches", type=int, default=0, help="stop after N batches (0 = unbounded)")
    ap.add_argument("--once", action="store_true")
    a = ap.parse_args()
    only = set(a.binaries.split(",")) if a.binaries else None
    api_base = os.environ.get("API_BASE")
    model = os.environ.get("MODEL")
    if not api_base or not model:
        log("set API_BASE and MODEL (the served fine-tuned model)"); sys.exit(2)
    os.makedirs(AUTODIR, exist_ok=True)
    tried = set(json.load(open(TRIED))) if os.path.exists(TRIED) else set()
    total_banked = 0
    batch_i = 0
    propagated_since = set()
    last_fp = None

    while True:
        if os.path.exists(STOP):
            log("STOP — exiting"); break
        did_work = False
        for b in binaries():
            if os.path.exists(STOP):
                break
            if only and b not in only:
                continue
            if a.max_batches and batch_i >= a.max_batches:
                break
            stubs = open_stubs(b, a.max_nins, tried, a.min_reach, a.min_nins)
            if not stubs:
                continue
            did_work = True
            batch = stubs[:a.batch]
            log("%s: drafting %d/%d open <=%d-ins stubs" % (b, len(batch), len(stubs), a.max_nins))
            draft(batch, api_base, model, a.iters)
            banked = gate_binary(b, DRAFTS)
            tried |= {t["name"] for t in batch}
            json.dump(sorted(tried), open(TRIED, "w"))
            total_banked += len(banked)
            propagated_since.add(b)
            batch_i += 1
            if banked:
                log("%s: BANKED %d (%s)  [total %d]" % (b, len(banked), " ".join(banked), total_banked))
            # periodic fleet propagate sweep (the multiplier) — every N batches
            if batch_i % a.propagate_every == 0 and propagated_since:
                for pb in sorted(propagated_since):
                    subprocess.run([".venv/bin/python", "tools/dedup_propagate.py", "--auto-from", pb,
                                    "--min-reach", "2"], cwd=REPO, capture_output=True, timeout=3600)
                propagated_since.clear()
                log("propagate sweep done")
            # heartbeat + flywheel stats. progress.py --fleet is ~14s (a full 136-binary scan), so
            # compute it only on propagate-sweep batches (else carry the last value) — running it every
            # batch dominated the throughput on small batches (the SC01-dregs 1-stub batches).
            fp = last_fp
            if batch_i % a.propagate_every == 0:
                try:
                    rr = subprocess.run([".venv/bin/python", "tools/progress.py", "--fleet"],
                                        cwd=REPO, capture_output=True, text=True, timeout=120)
                    mm = re.search(r'byte-identical\s+:\s+\d+\s*/\s*\d+\s*=\s*([\d.]+)%', rr.stdout)
                    fp = float(mm.group(1)) if mm else last_fp
                except Exception:
                    pass
                last_fp = fp
            json.dump({"ts": int(time.time()), "binary": b, "total_banked": total_banked,
                       "fleet_pct": fp, "tried": len(tried)}, open(HB, "w"))
            json.dump({"total_banked": total_banked, "tried": len(tried), "fleet_pct": fp,
                       "near_by_class": near_class_hist()}, open(STATS, "w"), indent=1)
        if a.once or not did_work or (a.max_batches and batch_i >= a.max_batches):
            log("stopping (--once / --max-batches / no work); banked %d total" % total_banked)
            break
    return total_banked


if __name__ == "__main__":
    main()

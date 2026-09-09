#!/usr/bin/env python3
"""auto_driver.py — Phase 16 autonomous struct-harvest driver (LLM-free, set-and-go).

Loops the non-giant shared-stub worklist of ov_SC01_077 and, for each function:
  m2c --valid-syntax  ->  draft (byte-faithful M2C_FIELD; common.h defines the macro)
  match_one           ->  fast relocation-masked prefilter (rank: direct-match / near-miss / structural)
  decomp-permuter     ->  (time-boxed) close a near-miss by regalloc/schedule search   [optional]
  harvest_verify      ->  WHOLE-BINARY byte-gate (the SOLE arbiter, G3/P9) on the batch
  dedup_propagate     ->  propagate each banked match fleet-wide (up to 134 overlays)
  git commit          ->  checkpoint (explicit pathspec; NEVER git-checkout the overlay, §14c)

Runs pass after pass until the worklist is dry OR a safe-exit is requested. The byte-gate
guarantees nothing wrong is ever banked, no matter how long it runs unattended.

SAFE EXIT (Drew): `touch .run/auto/STOP` (or tools/auto_stop.sh) -> the driver finishes the
current function's gate+propagate+commit, writes a final heartbeat, and exits 0 cleanly; the
supervisor sees STOP and does not relaunch. Checked at every function/batch boundary.

HEARTBEAT: .run/auto/heartbeat.json — {ts, pass, current, banked_total, fleet_pct, last_commit, state}.

Usage:
  python3 tools/auto_driver.py [--batch 40] [--permute-secs 0] [--max-nins 150] [--once]
"""
import argparse, json, os, re, subprocess, sys, time, glob, shutil, signal
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import p16_permute  # reuse the validated permuter setup/run (M2C_FIELD->cast expander, scratch, run)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OV = "ov_SC01_077"
SRC = f"src/{OV}/{OV}.c"
ASM = f"asm/{OV}/nonmatchings/{OV}"
GOOD_SHA = "d19c9580a02dc63ba1f0e7e0c770f3b10de35635"
OUT = f"build/{OV}/{OV}"
AUTODIR = ".run/auto"
STOP = f"{AUTODIR}/STOP"
HEARTBEAT = f"{AUTODIR}/heartbeat.json"
DRAFTS = f"{AUTODIR}/drafts"
PY = ".venv/bin/python"
INS_RE = re.compile(r"/\* [0-9A-Fa-f]+ [0-9A-Fa-f]{8} [0-9A-Fa-f]{8} \*/")
NONFAITHFUL = re.compile(r"M2C_ERROR|M2C_BREAK|MULT_HI|MULTU_HI|\bCLZ\b|M2C_TRAP|GLUE_F64|BSWAP|REVERSE_BITS|ROTATE_RIGHT")


def sh(cmd, timeout=None):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)


def log(msg):
    print(f"[{time.strftime('%H:%M:%S')}] {msg}", flush=True)


def stop_requested():
    return os.path.exists(os.path.join(REPO, STOP))


def nins_of(fn):
    p = os.path.join(REPO, ASM, fn + ".s")
    if not os.path.exists(p):
        return 0
    return len(INS_RE.findall(open(p, errors="replace").read()))


def worklist(max_nins):
    """Current INCLUDE_ASM stubs in the overlay .c, non-giant (nins<=max_nins), leaf/small-first."""
    src = open(os.path.join(REPO, SRC)).read()
    stubs = re.findall(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)", src)
    sized = [(fn, nins_of(fn)) for fn in stubs]
    sized = [(fn, n) for fn, n in sized if 0 < n <= max_nins]
    sized.sort(key=lambda x: x[1])  # smallest first (highest yield, cheapest gate)
    return [fn for fn, n in sized]


def m2c_draft(fn):
    s = os.path.join(REPO, ASM, fn + ".s")
    if not os.path.exists(s):
        return None
    try:
        out = sh([PY, "tools/m2c/m2c.py", "-t", "mipsel-gcc-c", "--valid-syntax", "-f", fn, s], timeout=90).stdout
    except subprocess.TimeoutExpired:
        return None
    if not out.strip() or "OSError" in out or NONFAITHFUL.search(out):
        return None  # untyped/GTE/special -> defer
    return out


def match_one_score(fn, cpath):
    """Return ('match',0) | ('near', n_mismatch) | ('fail', -1)."""
    r = sh([PY, "tools/match_one.py", fn, "--c", cpath, "--asm-subdir", ASM], timeout=120)
    first = (r.stdout.strip().splitlines() or ["?"])[0]
    if first.startswith("MATCH"):
        return ("match", 0)
    m = re.search(r"(\d+) mismatched", first)
    if m:
        return ("near", int(m.group(1)))
    return ("fail", -1)


def write_heartbeat(state, pass_n, current, banked, fleet_pct, last_commit):
    os.makedirs(os.path.join(REPO, AUTODIR), exist_ok=True)
    json.dump({"ts": time.strftime("%Y-%m-%d %H:%M:%S"), "pass": pass_n, "current": current,
               "banked_total": banked, "fleet_pct": fleet_pct, "last_commit": last_commit,
               "state": state}, open(os.path.join(REPO, HEARTBEAT), "w"), indent=1)


def fleet_pct():
    try:
        r = sh([PY, "tools/progress.py", "--fleet"], timeout=120)
        m = re.search(r"byte-identical\s+:\s+\d+\s*/\s*\d+\s*=\s*([\d.]+)%", r.stdout)
        return float(m.group(1)) if m else None
    except Exception:
        return None


def git_commit(msg):
    sh(["git", "add", SRC, "src/shared", "config/dedup.us.yaml"])   # P35 T6: the share writes headers under src/shared/
    sh(["git", "commit", "-q", "-m", msg])
    return sh(["git", "rev-parse", "--short", "HEAD"]).stdout.strip()


def sig_unify(draft_dir):
    """Canonicalize each draft's callee externs + own def-signature to the banked set.
    ESSENTIAL (Phase-15 §14b/§14c + Phase-16 finding): without this the whole-binary gate
    fails on extern/data type conflicts even when match_one (relocation-masked) says MATCH."""
    uni = draft_dir + "-uni"
    r = sh([PY, "tools/sig_unify.py", "--overlay", OV, "--in", draft_dir, "--out", uni], timeout=600)
    return uni if os.path.isdir(os.path.join(REPO, uni)) else draft_dir


def byte_gate(draft_dir):
    """sig_unify then harvest_verify the drafts; returns list of verified fn names (the SOLE arbiter)."""
    gated = sig_unify(draft_dir)
    r = sh([PY, "tools/harvest_verify.py", "--binary", OV, "--src", SRC, "--asm-subdir", ASM,
            "--out", OUT, "--good-sha", GOOD_SHA, "--drafts", gated, "--chunk", "8"], timeout=7200)
    m = re.search(r"VERIFIED:\s*(.*)", r.stdout)
    if not m or "(none)" in m.group(1):
        return []
    return [w for w in m.group(1).split() if w.startswith("func_")]


def propagate():
    sh([PY, "tools/share_body.py", "--apply", "--bucket", "new", "--batches", "1"], timeout=3600)   # P35 T6: the include-at-site share


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--batch", type=int, default=40, help="functions per gate batch")
    ap.add_argument("--permute-secs", type=int, default=0, help="permuter budget per near-miss (0=skip)")
    ap.add_argument("--permute-j", type=int, default=8, help="permuter -j (RAM-bound on the 15GiB box)")
    ap.add_argument("--max-nins", type=int, default=150, help="exclude giants (>this)")
    ap.add_argument("--once", action="store_true", help="one pass then exit (for trials)")
    a = ap.parse_args()
    os.chdir(REPO)
    os.makedirs(AUTODIR, exist_ok=True)
    if stop_requested():
        log("STOP sentinel present at startup; remove it to run. Exiting.")
        return
    banked = 0
    last_commit = sh(["git", "rev-parse", "--short", "HEAD"]).stdout.strip()
    pass_n = 0
    log(f"auto_driver start (batch={a.batch}, permute={a.permute_secs}s, max_nins={a.max_nins})")
    while True:
        if stop_requested():
            log("STOP requested — exiting cleanly."); write_heartbeat("stopped", pass_n, None, banked, fleet_pct(), last_commit); return
        pass_n += 1
        wl = worklist(a.max_nins)
        log(f"pass {pass_n}: {len(wl)} non-giant shared stubs remain")
        if not wl:
            log("worklist DRY — all gettable non-giant work done."); write_heartbeat("dry", pass_n, None, banked, fleet_pct(), last_commit); return
        pass_banked = 0
        for i in range(0, len(wl), a.batch):
            if stop_requested():
                log("STOP requested at batch boundary — exiting cleanly."); write_heartbeat("stopped", pass_n, None, banked, fleet_pct(), last_commit); return
            batch = wl[i:i + a.batch]
            # build candidate drafts for this batch
            if os.path.exists(os.path.join(REPO, DRAFTS)):
                shutil.rmtree(os.path.join(REPO, DRAFTS))
            os.makedirs(os.path.join(REPO, DRAFTS), exist_ok=True)
            cand = 0
            for fn in batch:
                write_heartbeat("drafting", pass_n, fn, banked, None, last_commit)
                draft = m2c_draft(fn)
                if draft is None:
                    continue
                cpath = os.path.join(REPO, DRAFTS, fn + ".c")
                open(cpath, "w").write(draft)
                # prefilter; permuter (time-boxed) on near-misses — the key yield lever
                kind, score = match_one_score(fn, cpath)
                if kind == "fail":
                    os.remove(cpath); continue  # won't compile standalone -> drop (gate would revert anyway)
                if kind == "near" and a.permute_secs > 0:
                    write_heartbeat("permuting", pass_n, fn, banked, None, last_commit)
                    pd = p16_permute.setup(fn, draft)
                    if pd:
                        win = p16_permute.run_permuter(pd, a.permute_secs, a.permute_j)
                        if win:
                            # draft = externs + permuted body (common.h provides scalars/macros in the TU)
                            open(cpath, "w").write(p16_permute.winner_to_draft(open(win).read()))
                cand += 1
            if cand == 0:
                continue
            write_heartbeat("gating", pass_n, f"batch@{i}", banked, None, last_commit)
            verified = byte_gate(DRAFTS)
            if verified:
                propagate()
                banked += len(verified); pass_banked += len(verified)
                fp = fleet_pct()
                last_commit = git_commit(
                    f"feat(phase-16): auto-harvest pass {pass_n} batch@{i} — +{len(verified)} fns (fleet {fp}%)")
                log(f"  batch@{i}: banked {len(verified)} (total {banked}); fleet {fp}%; commit {last_commit}")
                write_heartbeat("running", pass_n, f"batch@{i}", banked, fp, last_commit)
        log(f"pass {pass_n} complete: banked {pass_banked}")
        if a.once or pass_banked == 0:
            log("once/no-progress -> exiting."); write_heartbeat("done", pass_n, None, banked, fleet_pct(), last_commit); return


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""gate_main_parallel.py — discover main's bankable drafts CONCURRENTLY, bank them ONCE, serially.

WHY THIS EXISTS. `gate_main.py` is the only trustworthy verifier for the EXE (its extract rewrites
the linker script, so an incremental build returns a FALSE PASS — see `gate-main-only-with-gate-main`
and R22), and it is strictly serial: one global flock, one repo tree, and a full clean EXE rebuild
per bisect step. A slate whose first batch fails rediscovers the good drafts one rebuild at a time.

MEASURE IT BEFORE YOU SELL IT (R41 — a rate ships with its denominator). One full gate cycle
(git checkout + make extract + rm binary + make build -j + SHA) is **16 s**, measured 2026-09-03 in
both the main tree and a worktree, not the "1-2 minutes" this file first claimed on my say-so. So
MAX_STEPS=24 is ~6.4 min of worst-case serial bisection, and four workers take that to roughly
90 s. That is a real speedup and an honest one — it is not the hour I first wrote down, and the
S75 checkpoint's "34-minute bisection" was a much larger slate, not this per-step cost.

The durability fix in gate_main (its progress journal) is what makes a long bisection survivable;
this tool is what makes it short. They are separate improvements and neither implies the other.

The serialization is an artifact of the SHARED TREE, not of the verification. Give each worker its
own `git worktree` and the discovery parallelizes perfectly — which is the standing house default
for gating (`parallel-gate-via-worktrees`, `gating-speed-playbook`: a slow gate is a BUG).

THE CORRECTNESS ARGUMENT, because "parallel byte-gate" should make a reader suspicious:

  * A worker's PASS is a real, whole-binary, clean-build byte match — it runs `gate_main.py` itself,
    unmodified, in a tree pinned at HEAD with only its own chunk substituted. Nothing here
    re-implements a gate (`verdict-names-its-instrument`: never re-implement a gate you have).
  * A worker's PASS is NOT a bank. Two chunks that each pass alone can fail together — a duplicate
    typedef, a decl conflict, two drafts declaring the same extern differently. So the union of
    every worker's proven set is handed to ONE authoritative `gate_main.py --apply` in the real
    tree, which substitutes, clean-builds, and bisects if the union disagrees. That final run is
    the only thing that ever banks, and it is the same gate as before.
  * Therefore parallelism can only make the final serial pass CHEAPER (it arrives pre-filtered) or,
    at worst, no better. It cannot make a wrong bank possible: the arbiter never changed (G3).

THE ONE HAZARD THAT IS NOT OBVIOUS: `asm/` MUST NOT BE SHARED. parallel_gate symlinks it (442 MB,
and an overlay gate only ever READS it). But main's verification is `make extract BINARY=main`,
which WRITES asm/ — through the symlink, into the main tree, while other workers are reading it.
main owns only 6.2 MB of that 442 MB (asm/nonmatchings, asm/data, asm/*.s), so this provisioner
COPIES main's subtree and symlinks the other 214 binaries' directories read-only. That is the same
trick the jtbl unlock uses (`gating-speed-playbook`), applied to the writer instead of the carver.

NEGATIVE-CONTROL IT BEFORE YOU BELIEVE IT (`parallel-gate-via-worktrees`): `--negative-control`
provisions one worktree, substitutes NOTHING, and clean-builds. If an UNMODIFIED tree does not
produce the known-good SHA, every verdict this tool could produce would be false, and it says so
and exits rather than letting the misprovisioning read as a wave of bad drafts (R40).

USAGE
  tools/gate_main_parallel.py --negative-control          # do this first, once per environment
  tools/gate_main_parallel.py <slate.json> --jobs 4       # dry: discover, report, do not bank
  tools/gate_main_parallel.py <slate.json> --jobs 4 --apply
"""
import argparse
import fcntl
import json
import os
import shutil
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor, as_completed

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import parallel_gate as PG                      # worktree provisioning — reused, never re-derived

REPO = PG.REPO
PY = PG.PY
WT_ROOT = os.path.join(REPO, ".run/gmp")
LOCK = os.path.join(REPO, ".run/auto/gate.main.parallel.lock")

# main's own asm subtree: what `make extract BINARY=main` WRITES, and therefore what a worker may
# not share. Everything else under asm/ belongs to the 214 overlays and is read-only here.
MAIN_ASM_DIRS = ("nonmatchings", "data")

# Read-only gitignored inputs the BUILD resolves through .run/. A fresh worktree has none of them,
# and their absence does not fail loudly — it makes carve owners read UNOWNED, which surfaces as a
# refusal attributed to the draft (measured twice: P31 S69 and again S74, five sessions apart,
# because two provisioners kept no shared list). Copy the small ones; a copy cannot be written back
# through, and this list is exactly the set the Makefile itself names (`grep -o '\.run/[^ ]*'`).
RUN_INPUT_GLOBS = ("sig.*.jsonl", "sig-modules.txt", "sig-overlays.txt", "seeds.*.txt",
                   "atlas.json", "banked_func_*.json", "fuel_manifest.json")

# THE SDK OBJECT TREE, and the reason the first negative control failed. `psyq_integrate` links the
# real PsyQ objects in place of the libcd/libgs/libetc/libgpu/libmcrd asm stubs, reading them from
# `.run/obj40/` — 11 MB, gitignored, SDK-derived, absent in a fresh worktree. The Makefile calls the
# integration "conditional ... a fresh clone without them builds byte-identically via the stubs",
# and that is NO LONGER TRUE for main: src/800_c.c is decompiled C that CALLS `CdReadyCallback`, so
# without the objects the link fails outright rather than falling back. Measured here — the control
# died with three `undefined reference to CdReadyCallback` and an empty build/psyq/.
# Read-only during a build (only tools/psyq_build_libs.sh writes them), so a symlink is correct.
RUN_INPUT_DIRS = ("obj40", "s59_o0")


def log(msg):
    print(f"[gmp {time.strftime('%H:%M:%S')}] {msg}", flush=True)


def provision(idx, pin):
    """A worktree that can run main's FULL extract+build without touching the shared tree."""
    # make_worktree reads parallel_gate's MODULE-LEVEL WT_ROOT, so calling it unqualified would
    # place our worktrees in `.run/pgate/wt<i>` — the same slots parallel_gate reuses, silently
    # destroying a concurrent overlay fan-out's tree (`git worktree remove --force` is its first
    # act). Point it at our own root for the duration. Measured: the first run of this tool put
    # its worktree in .run/pgate/wt0 while claiming .run/gmp/wt0 in its own logs.
    _saved, PG.WT_ROOT = PG.WT_ROOT, WT_ROOT
    try:
        wt = PG.make_worktree(idx, pin)
    finally:
        PG.WT_ROOT = _saved

    # 1. Un-share asm/. make_worktree symlinked it; main's extract writes it.
    link = os.path.join(wt, "asm")
    if os.path.islink(link):
        os.unlink(link)
    os.makedirs(link, exist_ok=True)
    src_asm = os.path.join(REPO, "asm")
    for e in os.listdir(src_asm):
        s, d = os.path.join(src_asm, e), os.path.join(link, e)
        if os.path.lexists(d):
            continue
        if e in MAIN_ASM_DIRS or (os.path.isfile(s) and e.endswith(".s")):
            (shutil.copytree if os.path.isdir(s) else shutil.copy2)(s, d)   # WRITABLE COPY
        else:
            os.symlink(s, d)                                                # read-only overlay asm

    # 2. The .run/ read-only inputs (see RUN_INPUT_GLOBS). The worker writes its OWN .run files
    #    (its progress journal, its preserved red images), so .run itself stays a real directory.
    import glob as _glob
    os.makedirs(os.path.join(wt, ".run"), exist_ok=True)
    for pat in RUN_INPUT_GLOBS:
        for s in _glob.glob(os.path.join(REPO, ".run", pat)):
            d = os.path.join(wt, ".run", os.path.basename(s))
            if not os.path.lexists(d) and os.path.isfile(s):
                shutil.copy2(s, d)
    for sub in RUN_INPUT_DIRS:
        s, d = os.path.join(REPO, ".run", sub), os.path.join(wt, ".run", sub)
        if os.path.isdir(s) and not os.path.lexists(d):
            os.symlink(s, d)

    # 3. splat's extracted asset objects. The link line pulls build/assets/main/*.o; without them
    #    the compile succeeds and the LINK dies late, reading exactly like a bad draft.
    a_src = os.path.join(REPO, "build/assets/main")
    if os.path.isdir(a_src):
        a_dst = os.path.join(wt, "build/assets/main")
        os.makedirs(a_dst, exist_ok=True)
        for f in os.listdir(a_src):
            sp = os.path.join(a_src, f)
            if os.path.isfile(sp):
                shutil.copy2(sp, os.path.join(a_dst, f))
    return wt


def assert_isolated(wt):
    """A worker that can write the shared asm/ is a corrupter, not a worker. Prove it cannot."""
    a = os.path.join(wt, "asm")
    if os.path.islink(a):
        raise SystemExit(f"gmp: {a} is still a SYMLINK — a main extract there would write the "
                         f"shared asm/ while other workers read it. Refusing.")
    for d in MAIN_ASM_DIRS:
        p = os.path.join(a, d)
        if os.path.islink(p):
            raise SystemExit(f"gmp: {p} is a symlink into the shared tree. Refusing.")


def run_worker(wt, chunk, slate_path, logpath, timeout, jobs_inner):
    """Run the REAL gate_main inside `wt` over `chunk`. Returns the set of fns it proved."""
    os.makedirs(os.path.dirname(logpath), exist_ok=True)
    # Absolute draft paths: drafts live under .run/ (gitignored), so a worktree has none of them.
    # They are read-only inputs, so pointing at the main tree's copy is correct.
    payload = []
    for e in chunk:
        e = dict(e)
        if e.get("draft"):
            e["draft"] = os.path.abspath(os.path.join(REPO, e["draft"]))
        payload.append(e)
    json.dump(payload, open(slate_path, "w"), indent=1)

    env = dict(os.environ)
    # A bisect of k drafts needs at most ~2k-1 rebuilds; the global default of 24 either truncates
    # a big chunk or lets a pathological one burn the wall clock. R46: a budget is part of the
    # harness, not a constant.
    env["GATE_MAIN_MAX_STEPS"] = str(max(8, 2 * len(chunk) + 2))
    env["MAKEFLAGS"] = f"-j{jobs_inner}"
    cmd = [PY, os.path.join(wt, "tools/gate_main.py"), slate_path, "--apply"]
    with open(logpath, "w") as lf:
        lf.write("$ " + " ".join(cmd) + f"\n(cwd={wt})\n\n")
        lf.flush()
        try:
            subprocess.run(cmd, cwd=wt, stdout=lf, stderr=subprocess.STDOUT,
                           timeout=timeout, env=env)
        except subprocess.TimeoutExpired:
            lf.write(f"\n*** TIMEOUT after {timeout}s — killed.\n")

    # COUNT FROM THE ARTIFACT, NOT FROM THE EXIT CODE (R53). gate_main writes the fns whose stub it
    # verified is GONE from src/; that stub-absence oracle is the project's bank oracle everywhere.
    # A timeout is not a total loss: the progress journal holds every verdict already proven.
    proven = set()
    banked = os.path.join(wt, ".run/gate_main_banked.json")
    if os.path.exists(banked):
        try:
            proven |= set(json.load(open(banked)))
        except (ValueError, OSError):
            pass
    prog = os.path.join(wt, ".run/gate_main_progress.json")
    if os.path.exists(prog):
        try:
            proven |= {g["fn"] for g in json.load(open(prog)).get("good", [])}
        except (ValueError, OSError, KeyError):
            pass
    return proven


def negative_control(pin, jobs_inner):
    """An UNMODIFIED worktree must build main byte-identical, or nothing here means anything."""
    log("negative control: provisioning one worktree and building main with NO draft substituted")
    wt = provision(0, pin)
    assert_isolated(wt)
    logp = os.path.join(REPO, ".run/gmp/negctl.log")
    os.makedirs(os.path.dirname(logp), exist_ok=True)
    cmd = [PY, os.path.join(wt, "tools/gate_main.py"), "--assert-baseline"]
    with open(logp, "w") as lf:
        r = subprocess.run(cmd, cwd=wt, stdout=lf, stderr=subprocess.STDOUT,
                           env={**os.environ, "MAKEFLAGS": f"-j{jobs_inner}"})
    tail = open(logp).read()[-600:]
    if r.returncode == 0:
        log("NEGATIVE CONTROL PASSED — an unmodified worktree builds main byte-identical. "
            "Provisioning is sound.")
        return True
    log("*** NEGATIVE CONTROL FAILED. An unmodified worktree does NOT build byte-identical, so "
        "every verdict this tool could produce would be a statement about the PROVISIONING, not "
        "about any draft (R40). Fix this before running a slate.")
    print(tail)
    return False


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("slate", nargs="?", help="the same slate JSON gate_main.py takes")
    ap.add_argument("--jobs", type=int, default=4, help="concurrent worktrees (default 4)")
    ap.add_argument("--apply", action="store_true",
                    help="after discovery, run the authoritative gate_main in the real tree")
    ap.add_argument("--timeout", type=int, default=3600, help="per-worker seconds (default 3600)")
    ap.add_argument("--negative-control", action="store_true",
                    help="provision one worktree, substitute nothing, prove it builds green")
    ap.add_argument("--keep", action="store_true", help="do not remove worktrees at the end")
    a = ap.parse_args()

    os.makedirs(os.path.dirname(LOCK), exist_ok=True)
    lk = open(LOCK, "w")
    try:
        fcntl.flock(lk, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except BlockingIOError:
        sys.exit("gmp: another gate_main_parallel holds the lock (worktree slots collide).")

    # The workers are pinned to HEAD, so uncommitted main work would be INVISIBLE to them: every
    # verdict would describe a tree the operator is not looking at. gate_main's own guard says the
    # same thing about destruction; this one is about relevance.
    dirty = subprocess.run("git status --porcelain -- " + " ".join(_main_tus()), shell=True,
                           cwd=REPO, capture_output=True, text=True).stdout.strip()
    if dirty:
        sys.exit("gmp: main's TUs have uncommitted changes, but workers are pinned to HEAD and "
                 "would never see them — every verdict would describe a different tree.\n\n"
                 + dirty + "\n\nCommit it first (R42).")

    pin = subprocess.run("git rev-parse HEAD", shell=True, cwd=REPO,
                         capture_output=True, text=True).stdout.strip()
    inner = max(2, (os.cpu_count() or 8) // max(1, a.jobs))

    if a.negative_control:
        sys.exit(0 if negative_control(pin, inner) else 3)

    if not a.slate:
        ap.error("a slate file is required unless --negative-control")
    slate = json.load(open(a.slate))
    n = min(a.jobs, len(slate))
    if n == 0:
        sys.exit("gmp: empty slate.")
    # Round-robin so every chunk carries a similar mix of sizes; a chunk's cost is one rebuild if
    # it passes and a bisect if it does not, so balancing COUNT is what matters.
    chunks = [slate[i::n] for i in range(n)]
    log(f"slate {len(slate)} -> {n} chunk(s) of ~{len(chunks[0])}, {inner} make-jobs each, "
        f"pinned at {pin[:9]}")

    outdir = os.path.join(REPO, ".run/gmp")
    os.makedirs(outdir, exist_ok=True)
    wts = []
    for i in range(n):
        wt = provision(i, pin)
        assert_isolated(wt)
        wts.append(wt)
    log(f"{n} worktree(s) provisioned (asm/ copied per worker: main's 6.2 MB of 442 MB)")

    proven, t0 = set(), time.time()
    with ThreadPoolExecutor(max_workers=n) as ex:
        futs = {ex.submit(run_worker, wts[i], chunks[i],
                          os.path.join(wts[i], "chunk.json"),
                          os.path.join(outdir, f"wt{i}.log"), a.timeout, inner): i
                for i in range(n)}
        for f in as_completed(futs):
            i = futs[f]
            try:
                got = f.result()
            except Exception as e:                       # a worker crash is not a draft verdict
                log(f"worker {i} RAISED {e!r} — its chunk is undecided, not rejected")
                got = set()
            proven |= got
            log(f"worker {i} done: {len(got)} proven  (log .run/gmp/wt{i}.log)")

    log(f"discovery finished in {time.time()-t0:.0f}s — {len(proven)} of {len(slate)} proven "
        f"in isolation")
    json.dump(sorted(proven), open(os.path.join(outdir, "proven.json"), "w"), indent=1)

    if not a.keep:
        for i in range(len(wts)):
            subprocess.run(["git", "worktree", "remove", "--force", wts[i]], cwd=REPO,
                           capture_output=True)

    if not proven:
        log("nothing proven — not running the authoritative pass.")
        return
    final = [e for e in slate if e["fn"] in proven]
    fp = os.path.join(outdir, "final_slate.json")
    json.dump(final, open(fp, "w"), indent=1)
    if not a.apply:
        log(f"DRY RUN. The authoritative pass is:\n"
            f"    tools/gate_main.py {fp} --apply")
        return

    # THE ONLY STEP THAT BANKS. Same gate, same tree, same arbiter as before this tool existed —
    # it just arrives pre-filtered, so its bisect (if any) starts from a much smaller set.
    log(f"authoritative pass: gate_main.py over the {len(final)} proven in the REAL tree")
    r = subprocess.run([PY, os.path.join(REPO, "tools/gate_main.py"), fp, "--apply"], cwd=REPO)
    sys.exit(r.returncode)


def _main_tus():
    sys.path.insert(0, os.path.join(REPO, "tools"))
    import gate_main as G
    return G.main_tus()


if __name__ == "__main__":
    main()

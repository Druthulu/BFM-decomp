#!/usr/bin/env python3
"""parallel_gate.py — gate MANY binaries CONCURRENTLY in isolated git worktrees, merge only the
passing drafts back into the main tree, and commit ONCE (P31 S65).

WHY THIS EXISTS
---------------
`gate_stage.py` is single-threaded BY HARNESS, not by nature. The build is already per-binary
(`build/<bin>/*.o`, its own `.ld`, its own SHA check), so N binaries could compile at once. What
serializes them is SHARED MUTABLE STATE, all of it in the working tree:

  * the splice writes `src/<bin>/*.c` in the one checkout;
  * `assert_write_set` measures a GLOBAL `git status`, so a concurrent run's writes read as this
    run's blast-radius violation;
  * the commit is a deliberately broad `git add -u src/` (it must be — propagation legitimately
    touches many overlays, and a narrower glob once DROPPED four R22-verified banks).

Measured cost of that serialization on 2026-08-29: a 109-binary h_norm sweep ran ~1 min/binary on a
32-core box at load 1.4 — about 4% utilisation — while an `xargs -P 4` attempt over the SAME tree
corrupted it (one aborted run's stage edits were swept into a concurrent run's commit, 696 broken
lines into ov_MAIN_012, check-all 212/213).

THE FIX IS ISOLATION, NOT LOCKING. Each worker gets its own `git worktree` (own index, own
`src/`, own `build/`), so the three shared-state problems above simply do not exist. Workers NEVER
commit and never touch the main tree. The orchestrator then applies only the drafts the gate
ACCEPTED, commits once, and runs ONE R22 clean-fleet sweep over the merged result — so the
whole-binary byte gate remains the sole arbiter (G3/P9) and the final state is verified as a whole,
not as N independent claims.

WHAT A WORKER NEEDS (measured, not guessed)
-------------------------------------------
  * tracked sources: come free with the worktree (src/, include/, config/, tools/, Makefile)
  * `asm/`      -> SYMLINK to the main tree. A gate never writes it (only `make extract` does), and
                   it is 453 MB — copying it per worker would be the whole cost of the exercise.
  * `.venv/`    -> SYMLINK (gitignored, so absent in a fresh worktree; gate_stage shells `.venv/bin/python`)
  * `build/<bin>/{<bin>.ld,undefined_syms_auto.txt,undefined_funcs_auto.txt}` -> COPY (1.9 MB/binary).
                   These are splat-extract outputs, untracked, and the link step needs them. Copying
                   them is what lets a worker skip `make extract` entirely.

MERGE SAFETY
------------
Every worktree is created from ONE pinned commit. Before adopting a worker's file the orchestrator
asserts the main tree's copy still matches that pinned version — if anything else changed that
binary meanwhile, the file is REFUSED rather than clobbered (the failure mode this whole tool exists
to prevent). Adopting is per-BINARY and per-FILE, never a blanket add.

  parallel_gate.py --plan plan.json [--workers 8] [--commit] [--r22] [--keep]
      plan.json: [{"binary": "ov_SC03_099", "drafts": "/abs/path/to/dir"}, ...]
"""
import argparse, json, os, re, shutil, subprocess, sys, time
from concurrent.futures import ThreadPoolExecutor, as_completed

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = os.path.join(REPO, ".venv/bin/python")
WT_ROOT = os.path.join(REPO, ".run/pgate")
GEN = ("{b}.ld", "undefined_syms_auto.txt", "undefined_funcs_auto.txt")


def sh(cmd, cwd=REPO, timeout=None):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=cwd, timeout=timeout)


def head_commit():
    return sh(["git", "rev-parse", "HEAD"]).stdout.strip()


def make_worktree(idx, pin):
    """One reusable worktree per worker slot, pinned to `pin` so the merge check has a baseline."""
    wt = os.path.join(WT_ROOT, "wt%d" % idx)
    if os.path.exists(wt):
        sh(["git", "worktree", "remove", "--force", wt])
    os.makedirs(WT_ROOT, exist_ok=True)
    r = sh(["git", "worktree", "add", "--detach", wt, pin])
    if r.returncode:
        raise SystemExit("[pgate] worktree add failed: %s" % (r.stderr or r.stdout)[-300:])
    # read-only, huge, gitignored: asm/ (453 MB of .s), the venv gate_stage shells, expected/.
    # A gate never writes them — only `make extract` does — so symlinks are correct and copying
    # would dominate the cost.
    for link in ("asm", ".venv", "expected"):
        tgt, dst = os.path.join(REPO, link), os.path.join(wt, link)
        if os.path.exists(tgt) and not os.path.exists(dst):
            os.symlink(tgt, dst)
    # DIRECTORIES THAT MIX TRACKED AND UNTRACKED CONTENT cannot be symlinked wholesale: the worktree
    # already has the tracked half, so `ln -s` would nest the link INSIDE it (measured, twice). Link
    # the MISSING ENTRIES instead. extracted/retail holds 3 tracked files in git and the multi-GB
    # ROM payload only on disk; the OBJCOPY size/pad step stats that payload.
    link_missing(os.path.join(REPO, "extracted/retail"), os.path.join(wt, "extracted/retail"))
    # UNTRACKED GENERATED HEADERS. splat writes these into include/ and they are gitignored, so a
    # fresh worktree has none of them and `as` dies with "can't open macro.inc for reading" on the
    # very first .data.o — which surfaces as every draft "failed" and reads exactly like a wave of
    # bad drafts (measured: 4 binaries, 10 drafts, 0 banked, before this line existed). Copy, do not
    # symlink: they are small and a worker must never be able to write the main tree's copy.
    for f in ("macro.inc", "gte_macros.inc", "labels.inc", "include_asm.h"):
        srcf = os.path.join(REPO, "include", f)
        if os.path.exists(srcf):
            shutil.copy2(srcf, os.path.join(wt, "include", f))
    # THE TOOLCHAIN ITSELF. `tools/maspsx` is a git SUBMODULE (a worktree creates the directory and
    # leaves it EMPTY) and `tools/bin/**` (cc1) + parts of `tools/psyq` are gitignored binaries. The
    # directories therefore EXIST but are short, which is why a naive "is it missing?" check passes
    # and the build then dies with "cc1: No such file or directory". Link the CONTENTS, per entry,
    # so an existing-but-empty dir is repaired rather than skipped.
    for sub in ("bin", "maspsx", "psyq"):
        link_missing(os.path.join(REPO, "tools", sub), os.path.join(wt, "tools", sub))
    return wt


def link_missing(s_dir, d_dir):
    """Symlink every entry of s_dir that d_dir lacks. Never replaces an existing entry, so a
    directory holding BOTH tracked files (present in the worktree) and gitignored ones (present only
    in the main tree) is repaired entry-by-entry."""
    if not os.path.isdir(s_dir):
        return
    os.makedirs(d_dir, exist_ok=True)
    for e in os.listdir(s_dir):
        dst = os.path.join(d_dir, e)
        if not os.path.lexists(dst):
            os.symlink(os.path.join(s_dir, e), dst)


def stage_generated(wt, binary):
    """Copy splat's untracked per-binary outputs so the worker can LINK without re-extracting."""
    src, dst = os.path.join(REPO, "build", binary), os.path.join(wt, "build", binary)
    os.makedirs(dst, exist_ok=True)
    missing = []
    for pat in GEN:
        f = pat.format(b=binary)
        s = os.path.join(src, f)
        if os.path.exists(s):
            shutil.copy2(s, os.path.join(dst, f))
        else:
            missing.append(f)
    # EXTRACTED ASSET OBJECTS. The link line pulls build/assets/<bin>/*.o (splat's binary-data
    # objects, e.g. trailing.o). Without them the compile succeeds and the LINK dies with
    # "cannot find build/assets/<bin>/trailing.o" — a failure that arrives late and, again, reads
    # as a bad draft. 8 KB per binary; copy them.
    a_src, a_dst = os.path.join(REPO, "build/assets", binary), os.path.join(wt, "build/assets", binary)
    if os.path.isdir(a_src):
        os.makedirs(a_dst, exist_ok=True)
        for f in os.listdir(a_src):
            sp = os.path.join(a_src, f)
            if os.path.isfile(sp):
                shutil.copy2(sp, os.path.join(a_dst, f))
    return missing


def stubs_of(wt, binary):
    """{fn} still INCLUDE_ASM in THIS tree — the bank oracle (a bank REMOVES a stub)."""
    r = sh([PY, "-c",
            "import sys;sys.path.insert(0,'tools');import corpus;"
            "print('\\n'.join(sorted(s.symbol for s in corpus.stubs(%r).values())))" % binary],
           cwd=wt)
    if r.returncode:
        return None
    return set(r.stdout.split())


_JTBL_RE = re.compile(r"jtbl_[0-9A-Fa-f]{8}")


def _drafts_carry_jtbl(binary, drafts):
    """Does any draft in this job reference a jump table? (same predicate harvest_verify carves on)"""
    try:
        import corpus
        stubs = corpus.stubs(binary)
    except Exception:
        return False
    try:
        names = {os.path.basename(f)[:-2] for f in os.listdir(drafts) if f.endswith(".c")}
    except OSError:
        return False
    for st in stubs.values():
        if st.symbol in names:
            try:
                if _JTBL_RE.search(open(os.path.join(REPO, st.asm_path), errors="replace").read()):
                    return True
            except OSError:
                continue
    return False


def isolate_asm(wt, binary):
    """Give this worker a WRITABLE asm/ for ONE binary so a jtbl carve can re-extract safely.

    THE PROBLEM THIS REMOVES (P31 S67). `harvest_verify`'s jtbl carve runs `make extract`, and the
    worktree's `asm/` is a SYMLINK to the main tree — so a carving worker would rewrite the MAIN
    tree's asm while 11 other workers read it. That is why jtbl drafts were routed to a SERIAL lane,
    and why one 16-binary batch took ~1 hour to protect a single jtbl draft.

    THE FIX IS CHEAP, and the numbers are why: `asm/` is 448 MB, but ONE binary's subtree is
    3.6-5.0 MB. So replace the blanket symlink with a real directory that SYMLINKS every other
    binary (read-only, free) and holds a real COPY of just this binary. `make extract BINARY=<b>`
    then writes only inside the worktree. ~5 MB per worker; nothing serial remains.

    Idempotent: a reused worker slot re-isolates for its new binary.
    """
    link = os.path.join(wt, "asm")
    real = os.path.join(REPO, "asm")
    if os.path.islink(link):
        os.unlink(link)
    elif os.path.isdir(link):
        shutil.rmtree(link, ignore_errors=True)
    os.makedirs(link, exist_ok=True)
    for entry in os.listdir(real):
        src, dst = os.path.join(real, entry), os.path.join(link, entry)
        if entry == binary:
            shutil.copytree(src, dst, symlinks=True)      # the ONE writable copy
        elif not os.path.exists(dst):
            os.symlink(src, dst)                          # everything else stays shared
    return True


def gate_one(idx, pin, job):
    binary, drafts = job["binary"], job["drafts"]
    t0 = time.time()
    wt = job.get("_wt")
    try:
        missing = stage_generated(wt, binary)
        # A CARVING JOB NEEDS ITS OWN asm/ (see isolate_asm). Without this the job is unsafe in a
        # worktree and had to run serially; with it, jtbl parallelises like everything else.
        if _drafts_carry_jtbl(binary, drafts):
            isolate_asm(wt, binary)
        before = stubs_of(wt, binary)
        if before is None:
            return {"binary": binary, "banked": [], "error": "corpus refused in worktree"}
        r = sh([PY, "tools/gate_stage.py", "--drafts", drafts, "--binary", binary,
                "--no-propagate", "--source-tag", "pgate"], cwd=wt, timeout=3600)
        after = stubs_of(wt, binary)
        banked = sorted(before - after) if after is not None else []
        files = {}
        if banked:                       # capture the worker's resulting TU text for the merge
            for rel in sh(["git", "status", "--porcelain", "--", "src/%s/" % binary],
                          cwd=wt).stdout.splitlines():
                p = rel[3:].strip()
                if p:
                    files[p] = open(os.path.join(wt, p)).read()
        return {"binary": binary, "banked": banked, "files": files, "secs": round(time.time() - t0, 1),
                "missing_generated": missing,
                "rc": r.returncode, "tail": (r.stdout or r.stderr)[-200:] if not banked else ""}
    except Exception as e:
        return {"binary": binary, "banked": [], "error": "%s: %s" % (type(e).__name__, str(e)[:160])}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--plan", required=True, help="JSON [{binary, drafts}, ...]")
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--r22", action="store_true", help="clean-fleet verify after the merge (do it)")
    ap.add_argument("--keep", action="store_true", help="keep worktrees for inspection")
    ap.add_argument("--no-merge", action="store_true",
                    help="gate in the worktrees and REPORT only; never write the main tree. The "
                         "dirty-tree precondition applies to the MERGE, not to gating — a worker "
                         "is isolated by construction — so this mode runs safely alongside another "
                         "gate/sweep and is how you measure the speedup without waiting for a quiet tree.")
    a = ap.parse_args()

    if not a.no_merge:
        dirty = sh(["git", "status", "--porcelain", "--", "src/", "config/"]).stdout.strip()
        if dirty:
            sys.exit("REFUSED: src/ or config/ is dirty — commit or inspect first (R42):\n" + dirty[:400])

    jobs = json.load(open(a.plan))
    jobs = [j for j in jobs if os.path.isdir(j["drafts"]) and
            any(f.endswith(".c") for f in os.listdir(j["drafts"]))]
    if not jobs:
        sys.exit("no jobs with drafts")
    pin = head_commit()
    nw = max(1, min(a.workers, len(jobs)))
    print("[pgate] %d binaries, %d workers, pinned at %s" % (len(jobs), nw, pin[:9]), flush=True)

    wts = [make_worktree(i, pin) for i in range(nw)]
    results, t0 = [], time.time()
    try:
        # one worktree per SLOT, handed round-robin: a worker is reused across jobs, never shared
        # concurrently (each future owns its slot for its whole run).
        slot_q = list(range(nw))
        def run(job, slot):
            job["_wt"] = wts[slot]
            return gate_one(slot, pin, job)
        with ThreadPoolExecutor(max_workers=nw) as ex:
            futs = {}
            for i, job in enumerate(jobs):
                futs[ex.submit(run, job, i % nw)] = job["binary"]
            for f in as_completed(futs):
                r = f.result(); results.append(r)
                print("[pgate] %-14s banked %-3d %s" % (r["binary"], len(r["banked"]),
                      r.get("error") or ("%.0fs" % r.get("secs", 0))), flush=True)
    finally:
        if not a.keep:
            for wt in wts:
                sh(["git", "worktree", "remove", "--force", wt])

    total = sum(len(r["banked"]) for r in results)
    print("[pgate] %d banked across %d binaries in %.0fs wall (workers=%d)"
          % (total, sum(1 for r in results if r["banked"]), time.time() - t0, nw), flush=True)

    # ---- MERGE: adopt only files whose main-tree copy is still the pinned version (never clobber)
    adopted, refused = [], []
    if a.no_merge:
        print("[pgate] --no-merge: main tree untouched; %d file(s) held in .run/pgate_results.json"
              % sum(len(r.get("files") or {}) for r in results), flush=True)
        json.dump(results, open(os.path.join(REPO, ".run/pgate_results.json"), "w"), indent=1)
        return
    for r in results:
        for p, text in (r.get("files") or {}).items():
            base = sh(["git", "show", "%s:%s" % (pin, p)]).stdout
            cur = open(os.path.join(REPO, p)).read() if os.path.exists(os.path.join(REPO, p)) else None
            if cur != base:
                refused.append(p); continue
            open(os.path.join(REPO, p), "w").write(text)
            adopted.append(p)
    print("[pgate] merged %d file(s); REFUSED %d (main tree moved under them): %s"
          % (len(adopted), len(refused), " ".join(refused[:5])), flush=True)

    if a.r22 and adopted:
        print("[pgate] R22 clean-fleet verify …", flush=True)
        sh(["make", "clean"], timeout=1800)
        sh(["make", "extract-all", "JOBS=32"], timeout=7200)
        c = sh(["make", "check-all", "JOBS=32"], timeout=7200)
        line = [l for l in c.stdout.splitlines() if l.startswith("check-all:")]
        print("[pgate] %s" % (line[-1] if line else "check-all produced no summary"), flush=True)
        if not line or "0 failed" not in line[-1]:
            sys.exit("[pgate] ABORT — fleet NOT green after merge; files left in tree for inspection (R42)")

    if a.commit and adopted:
        sh(["git", "add", "--"] + adopted)
        msg = ("feat(decomp): parallel gate — %d fns across %d binaries (%d workers)\n\n%s"
               % (total, sum(1 for r in results if r["banked"]), nw,
                  "\n".join("  %-14s %s" % (r["binary"], " ".join(r["banked"]))
                            for r in results if r["banked"])[:3000]))
        sh(["git", "-c", "user.name=Drew T", "-c", "user.email=50529377+Druthulu@users.noreply.github.com",
            "commit", "-q", "-m", msg])
        print("[pgate] committed %s" % head_commit()[:9], flush=True)

    json.dump(results, open(os.path.join(REPO, ".run/pgate_results.json"), "w"), indent=1)


if __name__ == "__main__":
    main()

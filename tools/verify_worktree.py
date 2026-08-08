#!/usr/bin/env python3
"""verify_worktree.py — Stage 2 of docs/concurrency-design.md: the clean-R22 lane.

WHAT IT DOES
    Checks a COMMIT out into its own git worktree, provisions the untracked build deps, and runs
    the full clean fleet verify (`make extract-all && make check-all`) there — so R22 no longer
    blocks the main tree. Writes .run/verify/<sha>.json with the verdict and toolchain provenance.

WHAT A GREEN RESULT LICENSES (say exactly this, no more)
    "Commit <sha>: clean-fleet N/N byte-identical from a pristine checkout of its TRACKED SOURCE,
     built against a supplied extraction; every non-stub function in <sha> is matched (G3/P9).
     No claim about any later commit or any working tree."

    The "supplied extraction" clause is not hedging — it is measured. Only 3 files under extracted/
    are tracked; the ROM payloads are gitignored and provisioned by symlink (see provision()).
    No commit here is self-sufficient, so no tool can honestly claim "a fresh clone builds".

WHY IT IS STRICTLY STRONGER THAN A MAIN-TREE R22
    `make check-all` in the main tree compiles whatever the OBJS glob finds — INCLUDING untracked
    stray .c files. So main-tree green does NOT prove the commit is complete; this project has
    already hit exactly that ("a clone of such a bank commit failed to build", gate_stage.py).
    A worktree's src/ holds ONLY the commit's tracked content, so a source file someone forgot to
    `git add` fails here BY CONSTRUCTION. That — not "a fresh clone builds" — is the guarantee.

DISK (measured, not assumed)
    The design proposed a sparse checkout to save ~1 GB (ghidra/). Measured free space is ~941 GB,
    so we take the FULL checkout: simpler, and it removes the R34 obligation to validate a sparse
    green against a full green. Revisit only if disk becomes scarce.

TOOLCHAIN PROVENANCE
    cc1 is extracted from the COMMITTED tarball and verified against the COMMITTED
    tools/bin/CHECKSUMS.sha256. Note the oracle is output bytes, not the toolchain: a "wrong" cc1
    that still reproduces the bytes does not invalidate a match; one that diverges yields a false
    FAILURE — which is why the checksum runs BEFORE the build (R35: fix the instrument first).

USAGE
    tools/verify_worktree.py                 # verify HEAD
    tools/verify_worktree.py --sha <sha>     # verify a specific commit
    tools/verify_worktree.py --keep          # leave the worktree in place for inspection
"""
import argparse
import hashlib
import json
import os
import shutil
import subprocess
import sys
import time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_WT = os.path.join(os.path.dirname(REPO), "bfm-verify")
CC1_DIR = "tools/bin/gcc-2.7.2-psx"
CC1_TAR = "tools/bin/gcc-2.7.2-psx.tar.gz"
CHECKSUMS = "tools/bin/CHECKSUMS.sha256"


def run(cmd, cwd, timeout=None, quiet=False):
    r = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, timeout=timeout)
    if not quiet and r.returncode != 0:
        sys.stderr.write(f"[verify] $ {' '.join(cmd)} -> rc={r.returncode}\n"
                         f"{(r.stderr or r.stdout)[-1500:]}\n")
    return r


def sha256(p):
    h = hashlib.sha256()
    with open(p, "rb") as fh:
        for b in iter(lambda: fh.read(1 << 16), b""):
            h.update(b)
    return h.hexdigest()


def provision(wt, prov):
    """Install the untracked build deps a pristine checkout lacks. Returns None or an error string."""
    # 1. .venv — read-only at build time, so a symlink to the main clone's venv is sound.
    v = os.path.join(wt, ".venv")
    if not os.path.exists(v):
        os.symlink(os.path.join(REPO, ".venv"), v)
    prov["venv"] = "symlink -> main clone"

    # 2. cc1 — from the COMMITTED tarball, checksum-verified against the COMMITTED record (R35).
    tar = os.path.join(wt, CC1_TAR)
    if not os.path.exists(tar):
        return f"missing {CC1_TAR} in the checkout (is it tracked at this sha?)"
    want = None
    cs = os.path.join(wt, CHECKSUMS)
    if os.path.exists(cs):
        for ln in open(cs):
            if "gcc-2.7.2-psx.tar.gz" in ln:
                want = ln.split()[0]
    got = sha256(tar)
    prov["cc1_tarball_sha256"] = got
    if want and want != got:
        return f"cc1 tarball sha256 MISMATCH: recorded {want}, got {got}"
    prov["cc1_checksum"] = "verified" if want else "NO RECORD IN CHECKSUMS.sha256"
    d = os.path.join(wt, CC1_DIR)
    if not os.path.isdir(d):
        os.makedirs(d, exist_ok=True)
        r = run(["tar", "xzf", os.path.abspath(tar), "-C", d], cwd=wt, timeout=300)
        if r.returncode != 0:
            return "cc1 extraction failed"
    if not os.path.exists(os.path.join(d, "cc1")):
        return f"cc1 binary absent after extraction ({CC1_DIR}/cc1)"

    # 3. extracted/ — the ROM payloads every splat target_path points at.
    #
    # MEASURED 2026-08-07, and it BOUNDS WHAT THIS TOOL CAN CLAIM: only 3 files under extracted/
    # are tracked (the EXE + 2 manifests). The 760 MB of .CD.dir payloads are gitignored — correctly,
    # they are ROM-derived and regenerable from the (also gitignored, multi-GB) disc dump. So a
    # pristine checkout extracts NOTHING: the first honest run of this tool failed 212/212.
    #
    # ⇒ NO COMMIT IN THIS REPO IS SELF-SUFFICIENT, by design. A green from this tool therefore
    #   certifies "the commit's tracked source, built against a supplied extraction" — NOT "a fresh
    #   clone builds". The design doc's phrasing ("a pristine checkout of exactly C's tracked
    #   content") overstated it; corrected here and in docs/concurrency-design.md.
    #
    # The symlink is sound: extracted/ is deterministic and manifest-verified (Phase 2), identical
    # for every commit, and READ-ONLY during a build. What the worktree still proves over a
    # main-tree R22 is the part that actually bit us — untracked stray .c files in src/ cannot
    # contribute, because the OBJS glob only sees the commit's tracked sources.
    ex = os.path.join(wt, "extracted")
    if not os.path.exists(os.path.join(ex, "retail", "MAIN.CD.dir")):
        src_ex = os.path.join(REPO, "extracted")
        if not os.path.isdir(os.path.join(src_ex, "retail", "MAIN.CD.dir")):
            return ("extracted/ payloads absent in BOTH the worktree and the main clone — "
                    "run tools/bfm_extract/extract.py first")
        # Keep the commit's own tracked files; link only the untracked bulk beside them.
        for name in sorted(os.listdir(os.path.join(src_ex, "retail"))):
            if not name.endswith(".CD.dir") and not name.endswith(".CD"):
                continue
            dst = os.path.join(ex, "retail", name)
            if not os.path.exists(dst):
                os.makedirs(os.path.dirname(dst), exist_ok=True)
                os.symlink(os.path.join(src_ex, "retail", name), dst)
    prov["extracted"] = "symlinked .CD/.CD.dir bulk -> main clone (untracked, ROM-derived)"

    # 4. maspsx — a pinned submodule. Record the gitlink the COMMIT expects and what we provide.
    want_sm = None
    r = run(["git", "ls-tree", "HEAD", "tools/maspsx"], cwd=wt, quiet=True)
    if r.returncode == 0 and r.stdout.split():
        want_sm = r.stdout.split()[2]
    prov["maspsx_expected"] = want_sm
    if not os.path.exists(os.path.join(wt, "tools/maspsx/maspsx.py")):
        r = run(["git", "submodule", "update", "--init", "tools/maspsx"], cwd=wt, timeout=600)
        if r.returncode != 0 or not os.path.exists(os.path.join(wt, "tools/maspsx/maspsx.py")):
            # Fall back to the main clone's checkout, but record that we did (provenance, not silence).
            shutil.rmtree(os.path.join(wt, "tools/maspsx"), ignore_errors=True)
            os.symlink(os.path.join(REPO, "tools/maspsx"), os.path.join(wt, "tools/maspsx"))
            prov["maspsx"] = "symlink -> main clone (submodule init failed)"
        else:
            prov["maspsx"] = "submodule checkout"
    else:
        prov["maspsx"] = "present in checkout"
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sha", default=None, help="commit to verify (default: HEAD)")
    ap.add_argument("--worktree", default=DEFAULT_WT)
    ap.add_argument("--keep", action="store_true", help="leave the worktree in place")
    ap.add_argument("--jobs", default=None, help="JOBS= for extract-all/check-all")
    a = ap.parse_args()

    sha = a.sha or run(["git", "rev-parse", "HEAD"], cwd=REPO, quiet=True).stdout.strip()
    short = sha[:9]
    t0 = time.time()
    prov = {}
    out = {"sha": sha, "verdict": "ERROR", "provenance": prov}
    os.makedirs(os.path.join(REPO, ".run/verify"), exist_ok=True)
    outp = os.path.join(REPO, f".run/verify/{short}.json")

    def finish(verdict, **kw):
        out.update(verdict=verdict, wall_s=round(time.time() - t0, 1), **kw)
        with open(outp, "w") as fh:
            json.dump(out, fh, indent=1)
        print(json.dumps({k: v for k, v in out.items() if k != "provenance"}))
        print(f"[verify] -> {os.path.relpath(outp, REPO)}")
        return 0 if verdict == "GREEN" else 1

    print(f"[verify] commit {short} -> worktree {a.worktree}", flush=True)
    if os.path.exists(a.worktree):                      # reuse: detach onto the target sha, then clean
        r = run(["git", "checkout", "--detach", sha], cwd=a.worktree)
        if r.returncode != 0:
            return finish("ERROR", error="could not re-checkout the existing worktree")
        run(["make", "clean"], cwd=a.worktree, timeout=1800, quiet=True)
    else:
        r = run(["git", "worktree", "add", "--detach", a.worktree, sha], cwd=REPO, timeout=1800)
        if r.returncode != 0:
            return finish("ERROR", error="git worktree add failed")

    err = provision(a.worktree, prov)
    if err:
        return finish("ERROR", error=f"provisioning: {err}")
    print(f"[verify] provisioned: {prov}", flush=True)

    jobs = ["JOBS=" + a.jobs] if a.jobs else []
    r = run(["make", "extract-all"] + jobs, cwd=a.worktree, timeout=14400)
    if r.returncode != 0:
        return finish("RED", stage="extract-all", tail=(r.stderr or r.stdout)[-1200:])
    r = run(["make", "check-all"] + jobs, cwd=a.worktree, timeout=14400)
    txt = r.stdout + r.stderr
    fails = [l.split()[-1] for l in txt.splitlines() if l.startswith("[FAIL]") and l.split()]
    summary = next((l for l in txt.splitlines() if l.startswith("check-all:")), "")
    if r.returncode != 0 or fails:
        return finish("RED", stage="check-all", summary=summary, failed=fails[:40])
    if not a.keep:
        run(["git", "worktree", "remove", "--force", a.worktree], cwd=REPO, timeout=600, quiet=True)
    # The emitted claim is what gets quoted, so it must be the CORRECTED one — not the docstring's
    # earlier over-claim. extracted/ is provisioned (see provision() step 3), so "pristine checkout"
    # would be false: this certifies the commit's TRACKED SOURCE against a supplied extraction.
    return finish("GREEN", summary=summary,
                  licenses=(f"Commit {short}: clean-fleet byte-identical from a pristine checkout of "
                            "its TRACKED SOURCE, built against a supplied extraction (extracted/ is "
                            "gitignored ROM data, symlinked in). Every non-stub function in the commit "
                            "is matched (G3/P9). Proves no untracked stray .c contributed. No claim "
                            "about any later commit, any working tree, or a from-scratch clone."))


if __name__ == "__main__":
    sys.exit(main())

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
  * the commit is broad BY NECESSITY (propagation legitimately touches many overlays, and a
    narrower glob once DROPPED four R22-verified banks). NOTE, corrected P31 S69: THIS TOOL does
    NOT use `git add -u src/` — that is `gate_stage`'s form. Here the orchestrator adds exactly the
    ADOPTED paths (`git add -- <adopted>`), which is why the merge-safety check decides what gets
    committed. A stale reading of this very line sent the first diagnosis of the untracked-carve-file
    bug in the wrong direction; the cause was the baseline comparison, not the add.

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
import argparse, functools, json, os, re, shutil, subprocess, sys, time
from concurrent.futures import ThreadPoolExecutor, as_completed

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = os.path.join(REPO, ".venv/bin/python")
WT_ROOT = os.path.join(REPO, ".run/pgate")
# The per-binary generated link inputs. DO NOT hard-code `build/<bin>/<bin>.ld` — that is the
# OVERLAY convention and it is wrong for `main`, whose Makefile variables put the linker script at
# `build/us/SLUS_007.26.ld` and its two undefined_*_auto.txt at the REPO ROOT. Hard-coding it made
# every main draft fail in a worktree and report as an honest gate rejection: measured S68, main
# banked 0 of 3 with `missing_generated: [main.ld, undefined_syms_auto.txt,
# undefined_funcs_auto.txt]` recorded in the results JSON and acted on by nobody — R32's corrected
# form, a loud failure that nobody counts is exactly as invisible as a silent one, and the same
# shape as R43's `sweep_parallel accepted main and banked 0/105`.
# Ask the Makefile, which already declares <b>_LD_SCRIPT / <b>_UNDEF_SYMS / <b>_UNDEF_FUNCS per
# binary (R33: derive from the invariant, do not re-derive it).
GEN_VARS = ("LD_SCRIPT", "UNDEF_SYMS", "UNDEF_FUNCS")


@functools.lru_cache(maxsize=None)
def generated_paths(binary):
    """(repo-relative path, ...) of <binary>'s generated link inputs, per the Makefile itself."""
    r = sh(["make", "--no-print-directory", "--eval=__pgate-%: ; @echo \"$($*)\""]
           + ["__pgate-" + v for v in GEN_VARS] + ["BINARY=" + binary])
    out = [ln.strip() for ln in r.stdout.splitlines() if ln.strip()]
    if r.returncode or len(out) != len(GEN_VARS):
        raise SystemExit("[pgate] cannot resolve generated paths for %r from the Makefile "
                         "(rc=%d, got %r) — refusing to gate a binary whose link inputs are "
                         "unknown (R43)" % (binary, r.returncode, out))
    return tuple(out)


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
    """Copy splat's untracked per-binary outputs so the worker can LINK without re-extracting.

    Paths come from the Makefile (see generated_paths) and are mirrored at the SAME repo-relative
    location inside the worktree, so main's root-level undefined_*_auto.txt land at the root and an
    overlay's land under build/<bin>/ — without this function needing to know which is which."""
    missing = []
    for rel in generated_paths(binary):
        s = os.path.join(REPO, rel)
        d = os.path.join(wt, rel)
        if os.path.exists(s):
            os.makedirs(os.path.dirname(d) or wt, exist_ok=True)
            shutil.copy2(s, d)
        else:
            missing.append(rel)
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
    # THE SIGNATURE REGISTRY (P31 S69, Fable-3). `jr_isolate_all.jr_inventory` resolves every
    # committed `.rodata` carve's owner through `family_remap.reloc_targets`, whose `nins_of`
    # reads the gitignored `.run/sig.<binary>.jsonl`. A fresh worktree has no `.run/sig.*`, so
    # inside a worker EVERY carve reads UNOWNED, jr_inventory R32-aborts, harvest_verify prints
    # `isolate FAILED`, and the draft is booked CARVE-REFUSED — an instrument verdict about the
    # worktree, not the function. Measured on ov_SC02_000/func_8017F950 (a RELOC-ONLY twin whose
    # body rtu-MATCHes 117/117): dry-run isolation passes in the main tree and aborts in the
    # worktree with 30 phantom UNOWNED carves; linking this one file is the difference. Read-only
    # input, so a symlink is correct (the registry is regenerated only by the main tree).
    sig = os.path.join(REPO, ".run", "sig.%s.jsonl" % binary)
    if os.path.exists(sig):
        os.makedirs(os.path.join(wt, ".run"), exist_ok=True)
        dst = os.path.join(wt, ".run", "sig.%s.jsonl" % binary)
        if not os.path.lexists(dst):
            os.symlink(sig, dst)
    else:
        missing.append(".run/sig.%s.jsonl (jtbl isolation cannot resolve carve owners without it)" % binary)
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


# A jtbl carve writes THREE kinds of output, and the merge must carry all three or none:
#   1. src/<bin>/*.c          per-binary, adopted like any bank
#   2. config/splat.<bin>.yaml per-binary, adopted whole (baseline-checked)
#   3. config/overlays.mk      SHARED — adopt ONLY this binary's block (see ovl_block)
# Carrying 1 without 2+3 is what turned a green worker into 13 red binaries of 213 in P31 S67
# (reverted in commit:3396): the C body referenced a carve the config never described.
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


def ovl_block(text, binary):
    """This binary's block of config/overlays.mk, or None.

    Blocks are delimited by `# --- <binary> (...) ---` headers and run to the next such header.
    Splicing ONE block is what makes a SHARED file safe to merge from a worker: two workers touching
    different binaries edit disjoint regions, and a worker can never widen its blast radius to
    another binary's carve state.
    """
    hdr = re.compile(r"^# --- (\S+) ", re.M)
    marks = [(m.start(), m.group(1)) for m in hdr.finditer(text)]
    for i, (pos, name) in enumerate(marks):
        if name == binary:
            end = marks[i + 1][0] if i + 1 < len(marks) else len(text)
            return text[pos:end]
    return None


def splice_ovl_block(main_text, binary, block):
    """Replace this binary's block in the main overlays.mk. Returns None if the block is absent."""
    cur = ovl_block(main_text, binary)
    if cur is None:
        return None
    return main_text.replace(cur, block, 1)


def gate_one(idx, pin, job):
    binary, drafts = job["binary"], job["drafts"]
    t0 = time.time()
    wt = job.get("_wt")
    try:
        missing = stage_generated(wt, binary)
        if missing:
            # REFUSE, never gate anyway (R43). A worker missing its linker script or its
            # undefined_*_auto.txt cannot LINK, so every draft comes back rejected and the batch
            # reads as an honest wave of bad drafts. Measured S68: main banked 0 of 3 this exact
            # way, and the `missing_generated` field that recorded it was consumed by nobody.
            return {"binary": binary, "banked": [], "files": {}, "ovl": None,
                    "secs": round(time.time() - t0, 1), "missing_generated": missing, "rc": None,
                    "error": "REFUSED — generated link inputs absent from the worktree: %s "
                             "(run `make extract BINARY=%s` in the main tree first)"
                             % (", ".join(missing), binary)}
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
        files, ovl = {}, None
        if banked:                       # capture the worker's resulting TU text for the merge
            for rel in sh(["git", "status", "--porcelain", "--", "src/%s/" % binary],
                          cwd=wt).stdout.splitlines():
                p = rel[3:].strip()
                if p:
                    files[p] = open(os.path.join(wt, p)).read()
            # CARVE STATE. The per-binary splat yaml is adopted whole; overlays.mk is SHARED, so we
            # carry only this binary's BLOCK and splice it (never a blanket file adopt — the
            # `carve-state-files-never-blanket-add` rule).
            yml = "config/splat.%s.yaml" % binary
            if os.path.exists(os.path.join(wt, yml)):
                wtxt = open(os.path.join(wt, yml)).read()
                if wtxt != sh(["git", "show", "%s:%s" % (pin, yml)]).stdout:
                    files[yml] = wtxt
            wov = os.path.join(wt, "config/overlays.mk")
            if os.path.exists(wov):
                blk = ovl_block(open(wov).read(), binary)
                if blk is not None and blk != ovl_block(
                        sh(["git", "show", "%s:config/overlays.mk" % pin]).stdout, binary):
                    ovl = blk
        # THE FAILURE CLASSES ARE PART OF THE RESULT, NOT DEBRIS IN A TRUNCATED TAIL (P31 S69).
        # `tail` is the last 200 chars — the JSON summary line — so `failed by class: PLUMBING=1`,
        # printed EARLIER by harvest_verify, never survived. gater_lane's in-tree retry therefore
        # could not tell "the worktree was blind" from "cc1 emitted a real diagnostic naming the
        # function", and retried all 22 binaries serially for nothing (measured S69: ~20 min).
        # THE VERDICT LAYER LIVES IN THE WORKTREE'S OWN .run/ AND DIES WITH IT (P31 S69, R47).
        # `harvest_verify` writes `<stem>.classified.txt` — ONE ROW PER FUNCTION with the exact cc1
        # diagnostic. `.run/` is not symlinked into a worktree, so those rows were lost and survived
        # only because gater_lane re-ran the whole binary IN-TREE afterwards, purely as a side effect.
        # Copy them out, and derive the class summary FROM THEM.
        #
        # THE FIRST ATTEMPT AT THIS PARSED `failed by class:` OUT OF THE WORKER'S STDOUT AND WAS
        # INERT: the worker is `gate_stage`, which does not print that line — harvest_verify does,
        # one level down. `classes` came back empty for all 17 binaries of the batch and the retry
        # gate that consumed it never fired once. A field that is always empty makes its consumer a
        # no-op, silently (R54); reading the artifact the tool actually writes cannot drift that way.
        verdicts, cls = [], ""
        wrun = os.path.join(wt, ".run")
        if os.path.isdir(wrun):
            for name in sorted(os.listdir(wrun)):
                if name.startswith("harvest_failed") and name.endswith(".classified.txt"):
                    try:
                        rows = [ln.rstrip("\n") for ln in open(os.path.join(wrun, name)) if ln.strip()]
                    except OSError:
                        continue
                    verdicts.extend(rows)
                    try:
                        shutil.copy(os.path.join(wrun, name),
                                    os.path.join(REPO, ".run/gate_lane/%s.pgate.classified.txt" % binary))
                    except OSError:
                        pass
        # A row is `<fn>\t<CLASS>: <diagnostic>`. The CLASS alone is not enough to decide whether the
        # worktree was blind — `CC1-FAIL(no-diagnostic)` is the blind signature, `CC1-FAIL: <file>:<line>:
        # <message>` is a real compile error — so keep the whole row and let the consumer judge.
        classes = []
        for row in verdicts:
            part = row.split("\t", 1)[-1]
            classes.append(part.split(":", 1)[0].strip())
        cls = " ".join(sorted(set(classes)))
        return {"binary": binary, "banked": banked, "files": files, "ovl": ovl,
                "secs": round(time.time() - t0, 1),
                "missing_generated": missing, "classes": cls, "verdicts": verdicts,
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
    adopted, refused, new_files = [], [], []
    if a.no_merge:
        print("[pgate] --no-merge: main tree untouched; %d file(s) held in .run/pgate_results.json"
              % sum(len(r.get("files") or {}) for r in results), flush=True)
        json.dump(results, open(os.path.join(REPO, ".run/pgate_results.json"), "w"), indent=1)
        return
    for r in results:
        for p, text in (r.get("files") or {}).items():
            # BASELINE CHECK — and a NEW file is not a moved one (P31 S69).
            # A jtbl carve SPLITS a TU, so the worker legitimately creates
            # `src/<bin>/<bin>_jr_<addr>.c` that exists neither at the pin nor in the main tree.
            # The original form compared `git show`'s stdout (EMPTY STRING when the path is not at
            # the pin) against `None` (absent from the main tree) — and `None != ""`, so EVERY
            # carve-created file was refused as "main tree moved under them" and left UNTRACKED.
            # Nothing failed locally (the file is on disk, R22 passes), but the yaml naming its
            # subseg IS committed, so a fresh clone got the config without the source. Eight files
            # accumulated that way in one session and only surfaced because the dirty-tree guard
            # refused a later run. Distinguish "not at the pin" from "empty at the pin" via the
            # RETURN CODE, so absent-in-both compares equal and adopts.
            shown = sh(["git", "show", "%s:%s" % (pin, p)])
            base = shown.stdout if shown.returncode == 0 else None
            cur = open(os.path.join(REPO, p)).read() if os.path.exists(os.path.join(REPO, p)) else None
            if cur != base:
                refused.append(p); continue
            if base is None:
                new_files.append(p)
            open(os.path.join(REPO, p), "w").write(text)
            adopted.append(p)
        # CARVE STATE, per binary, on the SHARED overlays.mk: splice only this binary's block, and
        # only if that block still equals the pinned baseline. Two workers carving different binaries
        # therefore edit disjoint regions and can never clobber each other (the same refusal
        # discipline as the per-file adopt above, at block granularity).
        if r.get("ovl"):
            b = r["binary"]
            ovp = os.path.join(REPO, "config/overlays.mk")
            main_text = open(ovp).read()
            pinned_blk = ovl_block(sh(["git", "show", "%s:config/overlays.mk" % pin]).stdout, b)
            if ovl_block(main_text, b) != pinned_blk:
                refused.append("config/overlays.mk[%s]" % b); continue
            spliced = splice_ovl_block(main_text, b, r["ovl"])
            if spliced is None:
                refused.append("config/overlays.mk[%s: block absent]" % b); continue
            open(ovp, "w").write(spliced)
            if "config/overlays.mk" not in adopted:
                adopted.append("config/overlays.mk")
    if new_files:
        print("[pgate] %d NEW file(s) created by a carve, now tracked: %s"
              % (len(new_files), " ".join(new_files)), flush=True)
    print("[pgate] merged %d file(s); REFUSED %d (main tree moved under them): %s"
          % (len(adopted), len(refused), " ".join(refused[:5])), flush=True)

    if a.r22 and adopted:
        # THE SAME EXCLUSIVITY GUARD AS tools/r22_verify.sh, because the destructive operation is
        # HERE too. `make clean` deletes asm/ and build/, and drafting agents READ asm/ — they never
        # write src/, so a dirty-tree check does not see them. Measured FOUR times in S68: agents
        # reporting "asm/<binary> is MISSING from the tree" mid-draft, one surviving only because it
        # found an old snapshot. Putting the guard only on the standalone script left this path —
        # the one actually used most — unguarded. A guard belongs where the operation is (R54).
        # Liveness from the RECORDED ledger, never from scratch-dir mtimes: a `.run/*wave*` glob
        # blew past ARG_MAX and made the heuristic silently PASS on a live lane, and even fixed it
        # could not tell a thinking agent from a finished one.
        _lf = sh([sys.executable, "tools/lane_inflight.py", "list"])
        busy = _lf.stdout.strip() if _lf.returncode else ""
        if busy and not os.environ.get("R22_FORCE"):
            print("[pgate] R22 SKIPPED — drafting agents are live and read asm/ (a clean would pull "
                  "it out from under them):\n%s\n[pgate] the merge IS committed; run "
                  "tools/r22_verify.sh once the lane drains, or set R22_FORCE=1."
                  % "\n".join("    " + l for l in busy.splitlines()), flush=True)
            # RECORD THE DEBT. A skipped fleet check that nobody tracks is the same failure mode as
            # a loud error nobody counts (R32): it reads as "verified" at session close. This file
            # is the countable form — the session checkpoint must quote it, and it is deleted only
            # by an R22 that actually runs green.
            with open(os.path.join(REPO, ".run/R22_DEBT"), "a") as fh:
                fh.write("%s deferred after commit of %s (%d file(s))\n"
                         % (time.strftime("%H:%M:%S"), head_commit()[:9], len(adopted)))
            a.r22 = False
    if a.r22 and adopted:
        print("[pgate] R22 clean-fleet verify …", flush=True)
        sh(["make", "clean"], timeout=1800)
        sh(["make", "extract-all", "JOBS=32"], timeout=7200)
        c = sh(["make", "check-all", "JOBS=32"], timeout=7200)
        line = [l for l in c.stdout.splitlines() if l.startswith("check-all:")]
        print("[pgate] %s" % (line[-1] if line else "check-all produced no summary"), flush=True)
        if not line or "0 failed" not in line[-1]:
            sys.exit("[pgate] ABORT — fleet NOT green after merge; files left in tree for inspection (R42)")
        # a green fleet clears every deferred check — that is what the debt file was waiting for
        try:
            os.remove(os.path.join(REPO, ".run/R22_DEBT"))
            print("[pgate] cleared .run/R22_DEBT (fleet verified green)", flush=True)
        except OSError:
            pass

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

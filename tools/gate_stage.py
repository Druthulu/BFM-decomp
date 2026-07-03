#!/usr/bin/env python3
"""gate_stage.py — Phase 21 shared deterministic bank/log stage.

The single entrypoint the worker Workflow AND the grinder daemon both call after producing
candidate drafts. Runs the proven Phase-19/20 recovery pipeline, byte-gates, propagates the
byte-matches fleet-wide, and logs every non-match to the backlog ledger — then prints ONE
compact JSON summary (so the orchestrator's context stays lean).

  drafts dir
    -> canon_resident_calls   (func_<ADDR> -> curated resident name; link-miss recovery)
    -> cast_call_sites        (per-site fn-ptr cast for callee-conflicts; §17a-1 cap tool)
    -> sig_unify              (unify callee externs + own def-sig to canonical)
    -> harvest_verify --chunk 1   (THE byte-gate; sole arbiter G3/P9 — banks byte-matches, reverts the rest)
    -> dedup_propagate --auto-from   (lift each banked match -> engine_core.h macro -> x reach overlays)
    -> backlog.append_record(...)    (every non-match: closeness + class + best draft, for hand-finishing)

Each transform is a pure draft-text rewrite; only harvest_verify mutates the byte-locked tree
(and it reverts anything that isn't byte-identical). A wrong draft can never bank.

Usage:
  tools/gate_stage.py --drafts .run/drafts-X [--binary ov_SC01_077] [--source-tag worker|grinder]
      [--src ...] [--asm-subdir ...] [--good-sha ...] [--no-propagate] [--commit]
Prints a JSON summary; importable as run_gate(...)->dict.
"""
import argparse, fcntl, glob, json, os, re, shutil, subprocess, sys, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import backlog

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = ".venv/bin/python"
# ov_SC01_077 defaults (the canonical harvest binary)
OV = "ov_SC01_077"
DEF_SRC = f"src/{OV}/{OV}.c"
DEF_ASM = f"asm/{OV}/nonmatchings/{OV}"
DEF_OUT = f"build/{OV}/{OV}"
DEF_SHA = "d19c9580a02dc63ba1f0e7e0c770f3b10de35635"
DEDUP_YAML = "config/dedup.us.yaml"
_MANIFEST = None


def sh(cmd, timeout=None):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)


def _isdir(p):
    return os.path.isdir(os.path.join(REPO, p))


def _check_sha(binary):
    """The bare locked SHA1 for a binary (config/check.<bin>.sha is sha1sum format '<sha>  <name>')."""
    p = os.path.join(REPO, f"config/check.{binary}.sha")
    return open(p).read().split()[0] if os.path.exists(p) else None


def _xform(tool, ov, indir, suffix, extra=None):
    """Run a draft-dir transform; return its out dir, or the in dir if the tool no-ops/fails."""
    out = indir + suffix
    cmd = [PY, f"tools/{tool}", "--overlay", ov, "--in", indir, "--out", out] + (extra or [])
    r = sh(cmd, timeout=900)
    return out if _isdir(out) else indir


def _gate1(binary, src, asm, out, good_sha, d, verified_out=None, failed_out=None):
    """Whole-binary byte-gate (G3/P9, sole arbiter) on draft-dir d; return the verified func list.
    harvest_verify reads the CURRENT src as its baseline (so verified fns ACCUMULATE across calls —
    a stage-1 winner is no longer a stub for stage 2), substitutes + KEEPS byte-matches, reverts the
    rest. --chunk 1 so one compile-fail can't sink a chunk (§20). verified_out/failed_out are
    per-WORKER paths (default the shared .run/harvest_*.txt) so bulk_harvest can gate distinct
    binaries in parallel without cross-reading each other's results."""
    vo = verified_out or ".run/harvest_verified.txt"
    fo = failed_out or ".run/harvest_failed.txt"
    sh([PY, "tools/harvest_verify.py", "--binary", binary, "--src", src, "--asm-subdir", asm,
        "--out", out, "--good-sha", good_sha, "--drafts", d, "--chunk", "1",
        "--verified-out", vo, "--failed-out", fo], timeout=7200)
    vp = os.path.join(REPO, vo)
    return [w for w in (open(vp).read().split() if os.path.exists(vp) else []) if w.startswith("func_")]


def _manifest_class(name):
    global _MANIFEST
    if _MANIFEST is None:
        p = os.path.join(REPO, ".run/fuel_manifest.json")
        _MANIFEST = {t["name"]: t for t in json.load(open(p))["targets"]} if os.path.exists(p) else {}
    return _MANIFEST.get(name, {})


def _dedup_group_count():
    p = os.path.join(REPO, DEDUP_YAML)
    if not os.path.exists(p):
        return 0
    return len(re.findall(r"^\s*-\s*id:", open(p).read(), re.M)) or \
        len(re.findall(r"^[A-Za-z]", open(p).read(), re.M))


def match_one_closeness(fn, cpath, asm):
    """('match',0) | ('near', n) | ('fail', None) via match_one (relocation-masked)."""
    try:
        r = sh([PY, "tools/match_one.py", fn, "--c", cpath, "--asm-subdir", asm], timeout=180)
    except subprocess.TimeoutExpired:
        return ("fail", None)
    first = (r.stdout.strip().splitlines() or ["?"])[0]
    if first.startswith("MATCH"):
        return ("match", 0)
    m = re.search(r"(\d+) mismatch", first)
    return ("near", int(m.group(1))) if m else ("fail", None)


def run_gate(drafts, binary=OV, src=None, asm=None, out=None, good_sha=None,
             propagate=True, source_tag="worker", commit=False, src_file=None,
             lock_path=None, verified_out=None, failed_out=None, compute_fleet=True):
    # Serialize: the grinder and the orchestrator both call this, and it mutates the shared
    # build tree + git. One gate at a time (blocking flock) — never two builds/commits racing.
    # lock_path: pass a PER-BINARY lock (.run/auto/gate.<bin>.lock) so bulk_harvest can gate
    # DISTINCT binaries concurrently (their build/<bin>/** trees are isolated); default = the
    # global lock (serial), so grinder/orchestrator/lora_grind are unaffected. verified_out/
    # failed_out/compute_fleet likewise default to today's behavior; bulk_harvest overrides them
    # per-worker + skips the in-gate fleet% (computed once in its serial tail).
    # src_file: the overlay SPLIT .c the drafts target (ov_SC01_077_a.c / _o0.c). When set, BOTH cast
    # and sig_unify canonicalize against THAT file's decls (via --src-file; sig_unify.py:151 reads the
    # split file's stubs so split-file drafts are NOT dropped). dedup_propagate is already split-aware.
    # Default None = main .c.
    os.makedirs(os.path.join(REPO, ".run/auto"), exist_ok=True)
    _lock = open(os.path.join(REPO, lock_path or ".run/auto/gate.lock"), "w")
    fcntl.flock(_lock, fcntl.LOCK_EX)
    try:
        return _run_gate_locked(drafts, binary, src, asm, out, good_sha, propagate, source_tag,
                                commit, src_file, verified_out, failed_out, compute_fleet)
    finally:
        fcntl.flock(_lock, fcntl.LOCK_UN); _lock.close()


def _run_gate_locked(drafts, binary, src, asm, out, good_sha, propagate, source_tag, commit,
                     src_file=None, verified_out=None, failed_out=None, compute_fleet=True):
    # Resolve per-binary paths when unset — binary-agnostic, no silent ov_SC01_077 default an
    # overlay could inherit (the Phase-9 "required-no-default" discipline; the lora_grind mass-run's
    # 0/222 Bug-B). good_sha is normalized to the BARE hash: config/check.<bin>.sha is sha1sum format
    # "<sha>  <name>", but harvest_verify compares it against a bare sha1() — passing the whole line
    # never matches, so banking is 0 for EVERY binary incl. ov_SC01_077 (the 0/12 Bug-A).
    src = src or f"src/{binary}/{binary}.c"
    asm = asm or f"asm/{binary}/nonmatchings/{binary}"
    out = out or f"build/{binary}/{binary}"
    good_sha = (good_sha or _check_sha(binary) or DEF_SHA).split()[0]
    draft_fns = sorted(os.path.basename(p)[:-2] for p in
                       glob.glob(os.path.join(REPO, drafts, "*.c")))
    if not draft_fns:
        return {"drafts": 0, "banked": 0, "propagated": 0, "near": 0, "failed": 0, "verified": []}
    # Negative control (P9 / Phase-9): the drafts MUST be INCLUDE_ASM stubs SOMEWHERE in this
    # binary's sources (main + any _a/_o0 split — a split-only batch is legitimately gated by the
    # per-split run_gate call, so check the UNION, mirroring lora_grind.open_stubs' glob). If a
    # non-empty draft set overlaps ZERO of them, it's a binary/src mismatch (the silent-077-default
    # Bug-B) — warn loudly so a 0 can never again masquerade as "nothing matched".
    bin_stubs = set()
    for cf in glob.glob(os.path.join(REPO, f"src/{binary}/{binary}*.c")):
        bin_stubs |= set(re.findall(r'INCLUDE_ASM\([^,]+,\s*(func_[0-9A-Fa-f]+|DsMix)\)', open(cf).read()))
    if bin_stubs and not (set(draft_fns) & bin_stubs):
        print(f"[gate] WARNING: 0/{len(draft_fns)} drafts are INCLUDE_ASM stubs in {binary} — "
              f"binary/src mismatch (drafts for a different binary?); banking will be 0", file=sys.stderr)

    # Recovery is CANON-FIRST, sig_unify FALLBACK (§19/§25): sig_unify can REGRESS an already-byte-
    # correct draft (e.g. a hand-pinned crack — it rewrites the def-sig to a banked caller's wrong
    # canonical). So gate canon+cast FIRST (stage 1: already-correct drafts bank), then sig_unify
    # ONLY the stage-1 failures (stage 2: def-side near-misses recover) without regressing stage-1
    # winners. --src-file makes cast/sig_unify read the SPLIT .c (_a/_o0) so those drafts aren't
    # dropped. Each transform is a no-op-safe draft rewrite; the byte-gate is the sole arbiter (G3/P9).
    cast_extra = (["--src-file", src_file] if src_file else None)
    d1 = _xform("canon_resident_calls.py", binary, drafts, "-cn")
    d1 = _xform("cast_call_sites.py", binary, d1, "-cast", extra=cast_extra)
    verified = _gate1(binary, src, asm, out, good_sha, d1, verified_out, failed_out)

    d = d1
    fails1 = [f for f in draft_fns if f not in verified]
    if fails1:                                       # stage 2: sig_unify the stage-1 failures, re-gate
        s2in = drafts + "-s2in"
        abs_s2in = os.path.join(REPO, s2in)
        shutil.rmtree(abs_s2in, ignore_errors=True); os.makedirs(abs_s2in)
        for f in fails1:
            p = os.path.join(REPO, d1, f + ".c")
            if os.path.exists(p):
                shutil.copy(p, os.path.join(abs_s2in, f + ".c"))
        d = _xform("sig_unify.py", binary, s2in, "-uni", extra=cast_extra)
        verified += _gate1(binary, src, asm, out, good_sha, d, verified_out, failed_out)

    # 5 propagate the banked matches fleet-wide
    propagated = 0
    prop_error = None
    if verified and propagate:
        before = _dedup_group_count()
        pr = sh([PY, "tools/dedup_propagate.py", "--auto-from", binary, "--min-reach", "2",
                 "--recover"], timeout=3600)
        propagated = max(0, _dedup_group_count() - before)
        # Surface a REAL failure: dedup_propagate exits non-zero on a byte-gate revert (a false-reach
        # straggler poisoned the all-or-nothing batch) — distinct from the benign "nothing to propagate"
        # empty-plan no-op. A swallowed revert previously hid a real ×134 gain (cont.4); never again.
        pout = (pr.stdout or "") + (pr.stderr or "")
        if pr.returncode != 0 and "nothing to propagate" not in pout:
            errlog = os.path.join(REPO, ".run/auto/last_propagate_error.log")
            try:
                open(errlog, "w").write(pout)
            except OSError:
                pass
            prop_error = [l for l in pout.strip().splitlines() if l.strip()][-3:] or [f"exit {pr.returncode}"]
            print(f"[gate] WARNING: dedup_propagate exited {pr.returncode} ({propagated} groups added); "
                  f"see {errlog}", file=sys.stderr)

    # 6 log every non-match to the backlog (closeness + RESIDUAL class + best draft for the human).
    # The drafter stamps `// @class: <gcc-quirk class>` and `// @stuck: <note>` into the draft (so the
    # residual class travels WITH the file) — use those for the learning flywheel; else fall back to the
    # manifest class. This is what makes class-grouped waves (wave_targets.py --class) possible.
    near = failed = 0
    for fn in [f for f in draft_fns if f not in verified]:
        cpath = os.path.join(REPO, d, fn + ".c")
        body = open(cpath).read() if os.path.exists(cpath) else ""
        kind, close = match_one_closeness(fn, cpath, asm) if body else ("fail", None)
        meta = _manifest_class(fn)
        cm = re.search(r"//\s*@class:\s*(.+)", body)
        sm = re.search(r"//\s*@stuck:\s*(.+)", body)
        rclass = cm.group(1).strip() if cm else None       # the worker's self-reported residual class
        note = sm.group(1).strip() if sm else None
        if kind == "match":   # match_one says MATCH but the whole-binary gate rejected -> plumbing/TU conflict
            status, where = "near", note or "match_one MATCH but gate rejected (declaration/TU plumbing)"
        elif kind == "near":
            status, where = "near", note or f"{meta.get('lever') or meta.get('class') or 'residual'}: {close} mismatch"
            near += 1
        else:
            status, where = "failed", note or "won't compile standalone (loose-typing / missing decl)"
            failed += 1
        draft_path = backlog.save_draft(fn, body) if body else None
        backlog.append_record({"addr": meta.get("addr"), "name": fn, "reach": meta.get("reach"),
                               "klass": rclass or meta.get("class"), "nins": meta.get("nins"), "status": status,
                               "closeness": close, "where_stuck": where, "best_draft": draft_path,
                               "binary": binary, "source": source_tag})   # binary: lets the grinder gate non-077 near-misses
    backlog.render()

    fp = None
    if compute_fleet:
        try:
            r = sh([PY, "tools/progress.py", "--fleet"], timeout=180)
            mm = re.search(r"byte-identical\s+:\s+\d+\s*/\s*\d+\s*=\s*([\d.]+)%", r.stdout)
            fp = float(mm.group(1)) if mm else None
        except Exception:
            pass

    commit_sha = None
    if commit and verified:
        sh(["git", "add", src, "src/shared/engine_core.h", DEDUP_YAML] +
           glob.glob(os.path.join(REPO, "src/ov_*/*.c")))
        sh(["git", "commit", "-q", "-m",
            f"feat({os.environ.get('GATE_PHASE', 'decomp')}): {source_tag} gate — +{len(verified)} fns x{propagated} propagated (fleet {fp}%)"])
        commit_sha = sh(["git", "rev-parse", "--short", "HEAD"]).stdout.strip()

    return {"drafts": len(draft_fns), "banked": len(verified), "propagated": propagated,
            "near": near, "failed": failed, "fleet_pct": fp, "verified": verified,
            "prop_error": prop_error, "commit": commit_sha}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--drafts", required=True)
    ap.add_argument("--binary", default=OV)
    ap.add_argument("--src", default=None)
    ap.add_argument("--asm-subdir", default=None)
    ap.add_argument("--out", default=None)
    ap.add_argument("--good-sha", default=None)
    ap.add_argument("--source-tag", default="worker")
    ap.add_argument("--src-file", default=None,
                    help="overlay SPLIT .c the drafts target (ov_SC01_077_a.c/_o0.c): cast + sig_unify "
                         "canonicalize against it (via --src-file, so split-file drafts aren't dropped). "
                         "Use with --src/--asm-subdir pointing at the split.")
    ap.add_argument("--no-propagate", action="store_true")
    ap.add_argument("--commit", action="store_true")
    a = ap.parse_args()
    b = a.binary
    summary = run_gate(a.drafts, binary=b,
                       src=a.src or f"src/{b}/{b}.c",
                       asm=a.asm_subdir or f"asm/{b}/nonmatchings/{b}",
                       out=a.out or f"build/{b}/{b}",
                       good_sha=a.good_sha or DEF_SHA,
                       propagate=not a.no_propagate, source_tag=a.source_tag, commit=a.commit,
                       src_file=a.src_file)
    print(json.dumps(summary))


if __name__ == "__main__":
    main()

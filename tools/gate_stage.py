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


def _xform(tool, ov, indir, suffix, extra=None):
    """Run a draft-dir transform; return its out dir, or the in dir if the tool no-ops/fails."""
    out = indir + suffix
    cmd = [PY, f"tools/{tool}", "--overlay", ov, "--in", indir, "--out", out] + (extra or [])
    r = sh(cmd, timeout=900)
    return out if _isdir(out) else indir


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


def run_gate(drafts, binary=OV, src=DEF_SRC, asm=DEF_ASM, out=DEF_OUT, good_sha=DEF_SHA,
             propagate=True, source_tag="worker", commit=False, src_file=None):
    # Serialize: the grinder and the orchestrator both call this, and it mutates the shared
    # build tree + git. One gate at a time (blocking flock) — never two builds/commits racing.
    # src_file: the overlay SPLIT .c the drafts target (ov_SC01_077_a.c / _o0.c). When set, cast
    # canonicalizes against THAT file's decls and sig_unify is SKIPPED (it reads main .c only and
    # would DROP split-file drafts). dedup_propagate is already split-aware. Default None = main .c.
    os.makedirs(os.path.join(REPO, ".run/auto"), exist_ok=True)
    _lock = open(os.path.join(REPO, ".run/auto/gate.lock"), "w")
    fcntl.flock(_lock, fcntl.LOCK_EX)
    try:
        return _run_gate_locked(drafts, binary, src, asm, out, good_sha, propagate, source_tag, commit, src_file)
    finally:
        fcntl.flock(_lock, fcntl.LOCK_UN); _lock.close()


def _run_gate_locked(drafts, binary, src, asm, out, good_sha, propagate, source_tag, commit, src_file=None):
    draft_fns = sorted(os.path.basename(p)[:-2] for p in
                       glob.glob(os.path.join(REPO, drafts, "*.c")))
    if not draft_fns:
        return {"drafts": 0, "banked": 0, "propagated": 0, "near": 0, "failed": 0, "verified": []}

    # 1-3 deterministic recovery transforms (each a no-op-safe draft rewrite)
    d = _xform("canon_resident_calls.py", binary, drafts, "-cn")
    d = _xform("cast_call_sites.py", binary, d, "-cast",
               extra=(["--src-file", src_file] if src_file else None))
    if not src_file:                          # sig_unify reads main .c stubs/decls -> it would DROP
        d = _xform("sig_unify.py", binary, d, "-uni")   # split-file (_a/_o0) drafts; skip for those

    # 4 the byte-gate (sole arbiter); --chunk 1 so one compile-fail can't sink a chunk (§20)
    sh([PY, "tools/harvest_verify.py", "--binary", binary, "--src", src, "--asm-subdir", asm,
        "--out", out, "--good-sha", good_sha, "--drafts", d, "--chunk", "1"], timeout=7200)
    vp = os.path.join(REPO, ".run/harvest_verified.txt")
    verified = [w for w in (open(vp).read().split() if os.path.exists(vp) else []) if w.startswith("func_")]

    # 5 propagate the banked matches fleet-wide
    propagated = 0
    if verified and propagate:
        before = _dedup_group_count()
        sh([PY, "tools/dedup_propagate.py", "--auto-from", binary, "--min-reach", "2"], timeout=3600)
        propagated = max(0, _dedup_group_count() - before)

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
                               "source": source_tag})
    backlog.render()

    fp = None
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
            f"feat(phase-21): {source_tag} gate — +{len(verified)} fns x{propagated} propagated (fleet {fp}%)"])
        commit_sha = sh(["git", "rev-parse", "--short", "HEAD"]).stdout.strip()

    return {"drafts": len(draft_fns), "banked": len(verified), "propagated": propagated,
            "near": near, "failed": failed, "fleet_pct": fp, "verified": verified, "commit": commit_sha}


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
                    help="overlay SPLIT .c the drafts target (ov_SC01_077_a.c/_o0.c): cast canonicalizes "
                         "against it + sig_unify is skipped. Use with --src/--asm-subdir pointing at the split.")
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

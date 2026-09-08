#!/usr/bin/env python3
"""gate_wave.py — gate a whole wave the fast way: split on jtbl, run both lanes CONCURRENTLY. (P31 S67)

WHY THIS EXISTS (measured, S67, and it cost an hour).  `parallel_gate` cannot host a jtbl-bearing
draft: `harvest_verify`'s carve runs `make extract`, and a worker's worktree `asm/` is a SYMLINK to
the main tree (`parallel_gate.py:77` states the invariant — "a gate never writes them, only
`make extract` does").  Knowing that, I gated a 16-binary wave SERIALLY to protect the ONE jtbl
function in it.  Numbers from that run:

    4 binaries through parallel_gate (4 workers) : 103 s wall   (87 / 87 / 88 / 102 s each)
    the same 4 serially                          : ~6 min
    the full 16 serially                         : ~1 hour, for 1 jtbl draft

Applying a true rule to the wrong scope is the defect.  The predicate is per-DRAFT and it is cheap:
`jtbl_carve --probe` runs the real planner (since S67), so the split costs one probe per target.

WHY THE SPLIT PRECEDES THE RUN, rather than triaging failures afterwards.  A jtbl draft in a
parallel worker does NOT fail cleanly — it re-extracts through the shared `asm/` symlink and writes
the MAIN tree while nine other workers read it.  "Run everything parallel and re-run what failed"
can therefore poison the whole batch instead of isolating one draft.  Split first, then triage what
the filter missed (R32: verify the pre-filter against the outcome; never assume it was complete).

    tools/gate_wave.py --drafts .run/S67_ov --workers 8 --commit [--r22]
      <drafts>/<binary>/<fn>.c   — the layout gate_stage and parallel_gate both take
"""
import argparse
import concurrent.futures as cf
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, HERE)
PY = os.path.join(REPO, ".venv/bin/python")
_JTBL_RE = re.compile(r"jtbl_[0-9A-Fa-f]{8}")

import corpus  # noqa: E402
import progress  # noqa: E402


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=REPO, capture_output=True, text=True, **kw)


def has_jtbl(binary, fn):
    """Does this function's target .s reference a jump table?

    The SAME predicate `harvest_verify._fn_has_jtbl` uses to decide whether to carve — one
    definition of the question, so the router and the gate cannot disagree (R33/R34).
    """
    st = next((s for s in corpus.stubs(binary).values() if s.symbol == fn), None)
    if st is None:
        return False                      # already banked; the gate will no-op it
    try:
        return bool(_JTBL_RE.search(open(os.path.join(REPO, st.asm_path), errors="replace").read()))
    except OSError:
        return False


def split(drafts_root):
    """(parallel_plan, serial_items) — parallel is a plan.json for parallel_gate; serial is
    [(binary, [fn...])] for gate_stage."""
    par, ser = [], []
    known = set(progress.BINARIES)
    unknown = []
    for binary in sorted(os.listdir(os.path.join(REPO, drafts_root))):
        d = os.path.join(REPO, drafts_root, binary)
        if not os.path.isdir(d):
            continue
        # THE LADDER LEAVES ITS OWN OUTPUT DIRS BESIDE THE DRAFTS. `gate_stage._xform` writes
        # `<drafts>-cn`, `-cn-cast`, `-cn-cast-rc`, `-cn-cast-rc-sd` as SIBLINGS inside this root,
        # so a plain listdir reports 20 "binaries" for a 16-binary wave and would gate transformed
        # intermediates as if they were fresh work. Validate the name against the corpus and refuse
        # what is not a binary (R32: assert the denominator; R43: refuse, never mishandle).
        if binary not in known:
            unknown.append(binary)
            continue
        fns = sorted(f[:-2] for f in os.listdir(d) if f.endswith(".c"))
        if not fns:
            continue
        jt = [f for f in fns if has_jtbl(binary, f)]
        # A binary goes SERIAL if ANY of its drafts carries a table: the gate runs per binary, and
        # one carving draft is enough to make the whole worker unsafe.
        (ser if jt else par).append((binary, fns, jt))
    if unknown:
        print("  skipped %d non-binary dir(s) (ladder intermediates): %s"
              % (len(unknown), " ".join(sorted(unknown)[:6])), file=sys.stderr)
    plan = [{"binary": b, "drafts": os.path.join(REPO, drafts_root, b)} for b, _, _ in par]
    return plan, ser, par


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--drafts", required=True, help="<dir>/<binary>/<fn>.c")
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--r22", action="store_true")
    ap.add_argument("--source-tag", default="wave")
    ap.add_argument("--plan-only", action="store_true")
    a = ap.parse_args()

    plan, ser, par = split(a.drafts)
    n_par = sum(len(f) for _, f, _ in par)
    n_ser = sum(len(f) for _, f, _ in ser)
    print("split: %d binaries / %d drafts PARALLEL · %d binaries / %d drafts SERIAL (jtbl)"
          % (len(plan), n_par, len(ser), n_ser))
    for b, fns, jt in ser:
        print("   serial %-16s %s   (jtbl: %s)" % (b, " ".join(fns), " ".join(jt)))
    if a.plan_only:
        return 0
    if not plan and not ser:
        print("REFUSING: no drafts found under %s" % a.drafts, file=sys.stderr)
        return 2

    plan_path = os.path.join(REPO, ".run/gate_wave_plan.json")
    with open(plan_path, "w") as fh:
        json.dump(plan, fh, indent=1)

    def run_parallel():
        # STREAM, DO NOT CAPTURE (R55: a lane that runs unattended must leave evidence). Capturing
        # both lanes and printing at the end left the log at ZERO BYTES for the whole run, so there
        # was no way to tell "working" from "hung" — the same ambiguity that cost 40 minutes to a
        # self-matching pgrep waiter earlier in this session.
        if not plan:
            print("[gate_wave] (no parallel lane)", flush=True)
            return
        cmd = [PY, "-u", "tools/parallel_gate.py", "--plan", ".run/gate_wave_plan.json",
               "--workers", str(a.workers)]
        if a.commit:
            cmd.append("--commit")
        with subprocess.Popen(cmd, cwd=REPO, stdout=subprocess.PIPE,
                              stderr=subprocess.STDOUT, text=True, bufsize=1) as p:
            for line in p.stdout:
                print("[par] " + line.rstrip(), flush=True)

    def run_serial():
        for i, (b, _, _) in enumerate(ser, 1):
            print("[ser] %d/%d %s ..." % (i, len(ser), b), flush=True)
            cmd = [PY, "tools/gate_stage.py", "--binary", b,
                   "--drafts", os.path.join(a.drafts, b), "--source-tag", a.source_tag]
            if a.commit:
                cmd.append("--commit")
            r = sh(cmd, timeout=7200)
            print("[ser] %d/%d %s rc=%d %s"
                  % (i, len(ser), b, r.returncode, (r.stdout or "").strip()[-200:]), flush=True)

    # BOTH LANES AT ONCE (Drew, S67: no lane should idle). They are safe together — parallel_gate's
    # workers are isolated by construction and it adopts a file only if the main tree's copy still
    # matches the pinned baseline, REFUSING rather than clobbering if the serial lane moved it.
    with cf.ThreadPoolExecutor(max_workers=2) as ex:
        fp, fs = ex.submit(run_parallel), ex.submit(run_serial)
        fp.result(); fs.result()          # both stream as they go; nothing to print here

    if a.r22:
        print("[gate_wave] R22 clean-fleet ...")
        r = sh(["make", "clean"], timeout=3600)
        r = sh(["make", "extract-all"], timeout=14400)
        r = sh(["make", "check-all"], timeout=14400)
        tail = ((r.stdout or "") + (r.stderr or "")).strip().splitlines()[-3:]
        print("\n".join(tail))
        if r.returncode:
            print("R22 FAILED — do not report banks as done (R22/R50)", file=sys.stderr)
            return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())

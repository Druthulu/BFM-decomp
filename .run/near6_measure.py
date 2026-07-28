#!/usr/bin/env python3
"""near6_measure.py — re-measure the 6 WAVE22 NEAR drafts against the bytes (R14/R35).

The checkpoint's closeness numbers (217/11/10/9/7/6) came from wave subagent summaries. Before any
of them is used to route CPU, each is recomputed here through the EXISTING validated path
(tools/match_one.py --json, which itself runs tools/residual_class over the two instruction
streams) — never a second copy of the pipeline (R33).

Inputs are DERIVED from .run/wave22_targets.json (the wave's own per-target record: stub, asm
subdir, -O0 flag) — the two silent-artefact generators autopsy.py warns about.

Every one of the 6 is reported, including failures: a target that cannot be measured is printed
with its reason, never dropped (R32).
"""
import json
import os
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = sys.executable

NEAR6 = ["func_80176734", "func_80177B5C", "func_80140958",
         "func_80140D68", "func_8012E364", "func_80132F40"]

CHECKPOINT = {"func_80176734": 217, "func_80177B5C": 11, "func_80140958": 10,
              "func_80140D68": 9, "func_8012E364": 7, "func_80132F40": 6}


def load_targets():
    with open(os.path.join(REPO, ".run/wave22_targets.json")) as f:
        return {t["fn"]: t for t in json.load(f)}


def measure(fn, tgt):
    draft = ".run/wave22/%s.c" % fn
    row = {"fn": fn, "logged": CHECKPOINT[fn], "draft": draft,
           "asm_subdir": tgt["asm_subdir"], "o0": bool(tgt.get("o0"))}
    if not os.path.exists(os.path.join(REPO, draft)):
        row["status"] = "NO-DRAFT"
        return row
    cmd = [PY, "tools/match_one.py", fn, "--c", draft,
           "--asm-subdir", tgt["asm_subdir"], "--json"]
    if tgt.get("o0"):
        cmd.append("--o0")
    try:
        p = subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=300)
    except subprocess.TimeoutExpired:
        row["status"] = "TIMEOUT"
        return row
    lines = [ln for ln in p.stdout.strip().splitlines() if ln.strip()]
    try:
        j = json.loads(lines[-1])
    except Exception:
        row["status"] = "NOBUILD"
        row["note"] = (lines[0] if lines else
                       (p.stderr.strip().splitlines() or ["?"])[0])[:160]
        return row
    v = j.get("verdict") or {}
    row.update({"status": j.get("status"), "closeness": j.get("closeness"),
                "nins": j.get("nins"), "klass": v.get("klass"), "bucket": v.get("bucket"),
                "profile": v.get("profile"), "detail": v.get("detail"),
                "disagree": v.get("closeness_disagree")})
    return row


def main():
    targets = load_targets()
    missing = [f for f in NEAR6 if f not in targets]
    todo = [(f, targets[f]) for f in NEAR6 if f in targets]
    with ThreadPoolExecutor(max_workers=6) as ex:
        rows = list(ex.map(lambda a: measure(*a), todo))
    for f in missing:
        rows.append({"fn": f, "status": "NOT-IN-TARGETS", "logged": CHECKPOINT[f]})

    order = {f: i for i, f in enumerate(NEAR6)}
    rows.sort(key=lambda r: order[r["fn"]])
    print("%-16s %5s %6s %6s %-16s %-11s %-9s %s" %
          ("fn", "nins", "logged", "now", "klass", "bucket", "profile", "status"))
    for r in rows:
        print("%-16s %5s %6s %6s %-16s %-11s %-9s %s" % (
            r["fn"], r.get("nins", "?"), r.get("logged", "?"), r.get("closeness", "?"),
            r.get("klass", "-"), r.get("bucket", "-"), r.get("profile", "-"),
            r.get("status", "?") + (" | " + r["note"] if r.get("note") else "")))
    print()
    for r in rows:
        if r.get("detail"):
            print("  %s: %s" % (r["fn"], r["detail"]))
        if r.get("disagree"):
            print("  %s: ORACLE DISAGREEMENT %s" % (r["fn"], r["disagree"]))
    with open(os.path.join(REPO, ".run/near6_measure.json"), "w") as f:
        json.dump(rows, f, indent=1)
    print("\n-> .run/near6_measure.json")


if __name__ == "__main__":
    main()

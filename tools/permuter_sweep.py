#!/usr/bin/env python3
"""permuter_sweep.py — hand a wave's NEARs to the permuter, but ONLY the ones worth the CPU. (P31 S77)

THE GAP.  A drafting agent's brief tells it to STOP at a plateaued permuter-class residual rather
than grind one — correct, because an agent grinding a register permutation burns tokens for nothing.
The consequence is that every `SCHEDULE-REORDER` / `DELAY-SLOT` / `REGALLOC-PERM` residual lands
un-attempted, and the local permuter costs no tokens at all.  In S77 that hand-off happened only
when I remembered to do it.

WHAT IS ACTUALLY MEASURED, AND WHAT IS NOT.  §479 went through TWO corrections in one session and
this tool lives on the far side of both.  v1 said "≤4 mismatched is a permuter one-shot" on 3/3.
Five more runs made it **3 of 8** — a residual of 1 FAILED while a residual of 4 BANKED, so **the
mismatch count predicts nothing**:

    banked : func_80021174 (2) · func_80040DE8 (2) · func_80024054 (4)
    failed : func_8005F290 (1) · func_80015608 (3) · func_80039DEC (3)
             func_8005F0C8 (3) · func_8005ECC0 (2)

v2 then claimed the predictor was "prior-attempt history".  **Building this tool refuted that too.**
`journal_notes` — the same index the packs use — reports prior attempts for ALL EIGHT, winners
included (2, 3, 3 for the three that banked).  The signal actually eyeballed was the DRAFT HEADER
narrative; the two are different corpora, and the winners simply came from a recovery pile whose
files carry no header journal.  That is provenance, not evidence.

So: **there is no validated predictor.**  The honest selector is the two NECESSARY conditions — a
small residual, and a class the permuter can actually search — with an expected yield around 3 in 8.
Prior-attempt counts are PRINTED as information, never enforced.  `--skip-ground` exists as a
labelled experiment; promote it only if someone measures it discriminating over several waves.
(R14/R35: this paragraph exists because a negative control was run against a claim already written
into the cookbook.)

    tools/permuter_sweep.py --wave .run/S77w --dry           # what it would run, and why not
    tools/permuter_sweep.py --wave .run/S77w --apply
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, HERE)
PY = os.path.join(REPO, ".venv/bin/python")
if not os.path.exists(PY):
    PY = sys.executable

# match_one buckets the permuter can actually search.  A STRUCTURAL or LENGTH-DRIFT residual is a
# different animal and a permuter run on one is measured waste.
PERMUTER_CLASSES = ("SCHEDULE-REORDER", "DELAY-SLOT", "REGALLOC-PERM", "SCHEDULE", "REGALLOC")


def wave_results(wave):
    """{fn: result} from the workflow journals for this wave's targets."""
    tg = {t["name"]: t for t in json.load(open(os.path.join(REPO, wave, "targets.json")))}
    base = os.path.expanduser(
        "~/.claude/projects/-home-musashi-bfm-decomp/*/subagents/workflows/*/journal.jsonl")
    # SCOPE THE JOURNALS TO *THIS* WAVE (P31 S77). The glob spans every session's workflows, and a
    # bare `out[fn] = x` is last-write-wins over an UNORDERED glob — so an older wave's row for the
    # same function silently replaced this one, carrying its stale `draft_path`. Measured: the sweep
    # reported func_8002AC98 at closeness 73 and func_80015608 at 65, while both drafts in THIS
    # wave measure 1 and 3. That is R48 (never key by bare function name) inside a brand-new tool.
    # Two guards: read journals NEWEST LAST so recency wins, and keep only rows whose draft is
    # actually under this wave's directory.
    wave_abs = os.path.abspath(os.path.join(REPO, wave))
    out = {}
    for j in sorted(glob.glob(base), key=lambda f: os.path.getmtime(f)):
        for line in open(j, errors="replace"):
            try:
                r = json.loads(line)
            except Exception:
                continue
            if r.get("type") != "result":
                continue
            v = r.get("value") or r.get("result") or {}
            for x in (v if isinstance(v, list) else [v]):
                if not (isinstance(x, dict) and x.get("fn") in tg):
                    continue
                dp = x.get("draft_path") or ""
                if dp and not os.path.abspath(dp).startswith(wave_abs):
                    continue                      # a different wave's row for the same name
                out[x["fn"]] = x
    return tg, out


def has_prior_attempts(binary, fn):
    """How many prior-attempt notes the journal index holds for this function.

    INFORMATIONAL ONLY. It reads as a predictor and is not one: measured over the 8 known permuter
    runs it reports history for all 8, winners included. Printed, never enforced (see the module
    docstring)."""
    try:
        import journal_notes as jn
        rows = jn.notes_for(jn.load(), binary, fn)
        return len(rows or [])
    except Exception:
        return 0


def residual_class(fn, draft, asm_subdir):
    """(closeness, class) from match_one — the same oracle the wave used."""
    r = subprocess.run([PY, os.path.join(REPO, "tools/match_one.py"), fn, "--c", draft,
                        "--asm-subdir", asm_subdir], cwd=REPO, capture_output=True, text=True)
    txt = (r.stdout or "") + (r.stderr or "")
    m = re.search(r"(\d+) mismatched", txt)
    k = re.search(r"class:\s*(\S+)", txt)
    if re.search(r"^MATCH\b", txt, re.M):
        return 0, "MATCH"
    return (int(m.group(1)) if m else None), (k.group(1) if k else "?")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--wave", required=True)
    ap.add_argument("--max-closeness", type=int, default=4,
                    help="cheap cap, NOT the predictor (see the docstring's 3-of-8 table)")
    ap.add_argument("--cycles", type=int, default=1)
    ap.add_argument("--secs", type=int, default=150)
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--skip-ground", action="store_true",
                    help="UNVALIDATED EXPERIMENT: skip drafts with prior-attempt history. Measured "
                         "NOT to discriminate (all 8 known runs have history, winners included), so "
                         "it is OFF by default and cannot silently discard good work (R39)")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--dry", action="store_true", help="explicit no-op alias; dry is the default")
    a = ap.parse_args()

    tg, res = wave_results(a.wave)
    picked, skipped = [], []
    for fn, r in sorted(res.items()):
        if r.get("status") != "NEAR":
            continue
        t = tg[fn]
        draft = r.get("draft_path") or os.path.join(REPO, a.wave, t.get("arm", ""), fn + ".c")
        if not os.path.exists(draft):
            skipped.append((fn, "no draft on disk")); continue
        prior = has_prior_attempts(t.get("binary", "main"), fn)
        close, klass = residual_class(fn, draft, t["sub"])
        if close is None:
            skipped.append((fn, "no residual from match_one")); continue
        if close > a.max_closeness:
            skipped.append((fn, "closeness %d > cap %d" % (close, a.max_closeness))); continue
        if not any(k in klass for k in PERMUTER_CLASSES):
            skipped.append((fn, "class %s is not a permuter bucket" % klass)); continue
        if prior and a.skip_ground:
            skipped.append((fn, "prior history %d (--skip-ground, UNVALIDATED)" % prior))
            continue
        picked.append({"fn": fn, "draft": draft, "sub": t["sub"], "close": close, "klass": klass,
                       "prior": prior})

    print("permuter_sweep: %d NEAR -> %d picked, %d skipped"
          % (sum(1 for r in res.values() if r.get("status") == "NEAR"), len(picked), len(skipped)))
    for s in skipped:
        print("   skip %-16s %s" % s)
    for p in picked:
        print("   RUN  %-16s closeness %-3d %-18s prior=%d" % (p["fn"], p["close"], p["klass"], p["prior"]))
    if not a.apply:
        print("\nDRY RUN. Re-run with --apply. A winner is a CANDIDATE — gate it whole-binary before banking.")
        return 0

    for p in picked:
        print("\n=== %s" % p["fn"], flush=True)
        subprocess.run([PY, os.path.join(REPO, "tools/permuter_ils.py"), p["fn"],
                        "--draft", p["draft"], "--asm-subdir", p["sub"], "--klass", "SCHEDULE",
                        "--cycles", str(a.cycles), "--secs", str(a.secs), "--j", str(a.jobs)],
                       cwd=REPO)
    print("\nWinners land in .run/permuter-winners/. They are CANDIDATES: gate whole-binary (G3/P9).")
    return 0


if __name__ == "__main__":
    sys.exit(main())

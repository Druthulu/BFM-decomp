#!/usr/bin/env python3
"""idiom_harvest.py — pull the idioms a wave LEARNED out of its shard logs (P31 S58).

WHY THIS EXISTS. Waves ab..ah banked 1,262 functions and produced 211 explicit
"the cookbook did NOT cover this" findings, and not one reached `docs/matching-cookbook.md`.
R16 makes the feedback loop mandatory ("after each match, feed the GENERALIZABLE lesson back into
BOTH the cookbook AND the tooling"), and the flywheel is the whole reason the bank rate climbs
wave over wave. A campaign that drafts the next wave without harvesting the last one is spending
the models to re-learn what it already knows. Drew, 2026-08-23: harvest after each wave lands,
BEFORE the next wave's cards are drawn — "that's how our whole system works."

WHAT IT TRUSTS. Only notes from functions the WHOLE-BINARY BYTE-GATE accepted. `api_agent` writes
its note beside a `match_one` verdict, and match_one masks relocations — a wrong-symbol draft
reports MATCH and its "lesson" is then a lesson about a function we did not actually reproduce.
Banked-ness is derived from `corpus.stubs()` (R33: derive from the invariant, do not re-parse):
a function that is no longer an INCLUDE_ASM stub in its binary is banked, by construction.

  tools/idiom_harvest.py --waves ab,ac,ad,ae,af,ag --out .run/idiom_candidates.md
  tools/idiom_harvest.py --waves ah                    # the per-wave campaign call
"""
import argparse
import ast
import glob
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
sys.path.insert(0, "tools")
import corpus                                                     # noqa: E402

VERDICT = re.compile(r"^  (func_[0-9A-Fa-f]+|[A-Za-z_]\w*): (\S.*?) after (\d+) oracle call\(s\), "
                     r"\$[\d.]+, (\{.*)$")
# The phrases a model reaches for when it believes it found something the cookbook lacks. Kept
# broad on purpose: a false candidate costs a line in a review file, a missed one costs the idiom.
NOVEL = re.compile(r"cookbook did ?n[o']?t|cookbook DID NOT|not (?:already )?(?:in|covered|flagged)"
                   r"|new (?:micro-)?idiom|NEW IDIOM|undocumented|no section covers", re.I)


def wave_binaries(tag):
    """fn -> binary for every card in the wave, so banked-ness can be checked per binary."""
    p = f".run/wave_{tag}_cards.json"
    if not os.path.exists(p):
        return {}
    c = json.load(open(p))
    c = c if isinstance(c, list) else c.get("cards", [])
    return {x["fn"]: x["binary"] for x in c}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--waves", required=True, help="comma-separated wave tags")
    ap.add_argument("--out", default=".run/idiom_candidates.md")
    ap.add_argument("--all-verdicts", action="store_true",
                    help="include notes from drafts the byte-gate REJECTED (off by default: an "
                         "unbanked draft's lesson is unproven and may be actively wrong)")
    a = ap.parse_args()

    stub_cache = {}

    def is_banked(fn, binary):
        if not binary:
            return None
        if binary not in stub_cache:
            try:
                stub_cache[binary] = {s.symbol for s in corpus.stubs(binary).values()}
            except Exception:
                stub_cache[binary] = None
        stubs = stub_cache[binary]
        return None if stubs is None else (fn not in stubs)

    rows, seen = [], set()
    n_verdicts = n_notes = 0
    for tag in a.waves.split(","):
        binof = wave_binaries(tag)
        for p in sorted(glob.glob(f".run/wave_{tag}/shard*.log")):
            for line in open(p, errors="ignore"):
                m = VERDICT.match(line.rstrip("\n"))
                if not m:
                    continue
                n_verdicts += 1
                fn, verdict, calls, blob = m.group(1), m.group(2), int(m.group(3)), m.group(4)
                try:
                    d = ast.literal_eval(blob)
                except (ValueError, SyntaxError):
                    continue
                note = (d.get("notes") or "").strip() if isinstance(d, dict) else ""
                if not note:
                    continue
                n_notes += 1
                banked = is_banked(fn, binof.get(fn))
                if not a.all_verdicts and banked is not True:
                    continue
                if not NOVEL.search(note):
                    continue
                key = note[:160]
                if key in seen:
                    continue
                seen.add(key)
                rows.append({"wave": tag, "fn": fn, "binary": binof.get(fn, "?"),
                             "oracle_calls": calls, "banked": banked, "note": note})

    rows.sort(key=lambda r: (-len(r["note"]), r["fn"]))
    with open(a.out, "w") as fh:
        fh.write(f"# Idiom candidates — waves {a.waves}\n\n")
        fh.write(f"Parsed {n_verdicts} verdict lines, {n_notes} carried a note. "
                 f"**{len(rows)} novel-idiom candidates** from BYTE-GATE-BANKED functions"
                 f"{' (plus rejected drafts: --all-verdicts)' if a.all_verdicts else ''}.\n\n"
                 "Each note is the drafting model's own claim. It is EVIDENCE, not a cookbook "
                 "entry: the function is byte-proven, the explanation is not. Verify the tell "
                 "against the .s before writing a section.\n\n")
        for r in rows:
            fh.write(f"\n## {r['fn']} · {r['binary']} · wave {r['wave']} · "
                     f"{r['oracle_calls']} oracle call(s)\n\n{r['note']}\n")
    print(f"verdict lines {n_verdicts} · notes {n_notes} · novel candidates {len(rows)} -> {a.out}")
    # R32: assert the denominator rather than reporting a bare count.
    if n_verdicts == 0:
        sys.exit("R32: 0 verdict lines parsed — wrong wave tag or the log format moved")
    return 0


if __name__ == "__main__":
    sys.exit(main() or 0)

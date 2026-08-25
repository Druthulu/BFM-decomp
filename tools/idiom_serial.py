#!/usr/bin/env python3
"""idiom_serial.py — the SERIAL idiom-learning lane (P31 S58, Drew's design).

The wide ox campaign (tools/ox_campaign.py) is parallel and stateless: every shard starts from the
same knowledge and nothing one shard learns reaches another. That is the right shape for a pool of
independent functions and the WRONG shape for a wall class, where the whole point is that cracking
member N teaches you something that makes member N+1 cheaper.

Measured precedent (P31 S57): ox spent 40 turns / 5 oracle calls learning the jtbl exemplar, then
took 11 turns / 3 oracle calls on a WITHIN-FAMILY sibling — and 56 turns / 0 compiles on a
cross-family one. Learning transfers inside a family and dies at its border. So the lane is serial
BY FAMILY: crack the exemplar, distill what was learned, feed that forward, crack the next.

THE LOOP, per target:
  1. prepare  — lever-specific. jtbl-carve => tools/jtbl_carve.py + `make extract` for that binary,
                because a verified match_one is NOT a bankable card until the table is carved.
  2. draft    — ONE api_agent run on ONE function, with --cards fuel AND --brief carrying every
                idiom banked so far this run. This is the compounding channel.
  3. gate     — the whole-binary byte-gate is the sole arbiter (G3/P9). Nothing else counts.
  4. distill  — on a MATCH only, a second api_agent call asks the model for the generalizable idiom
                and appends it to the notes file that step 2 reads next time.

Targets come from the frontier atlas, largest leverage first. md_* jtbl members are EXCLUDED by
default: `jtbl_carve` refuses leading-island modules (byte-measured P30 S48), so they cost a
preparation failure every time. ov_* is where the carve works — 169 of the 245 jtbl members.

  tools/idiom_serial.py --lever jtbl-carve --n 6
  tools/idiom_serial.py --lever extend-tell --n 4 --min-ins 120
"""
import argparse
import glob
import json
import os
import re
import shutil
import subprocess
import sys
import time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
PY = ".venv/bin/python"
NOTES = ".run/idioms_learned.md"
LEDGER = ".run/idiom_serial_ledger.jsonl"


def log(m):
    print(f"[{time.strftime('%H:%M:%S')}] {m}", flush=True)


def sh(cmd, timeout=None):
    return subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=timeout)


def env_for_api():
    key = ""
    for line in open(".env"):
        if line.startswith("open_router_key="):
            key = line.split("=", 1)[1].strip(); break
    return dict(os.environ, API_BASE="https://openrouter.ai/api/v1", API_KEY=key,
                MODEL=os.environ.get("MODEL", "stealth/ox-alpha"),
                MAXTOK=os.environ.get("MAXTOK", "8000"))


def pick_targets(lever, n, min_ins, allow_md):
    a = json.load(open(".run/atlas.json"))
    groups = a["groups"] if isinstance(a, dict) and "groups" in a else a
    out = []
    for g in groups:
        if g.get("lever") != lever:
            continue
        ex = g["exemplar"]
        if ex["nins"] < min_ins:
            continue
        if not allow_md and ex["b"].startswith("md_"):
            continue
        # MAIN IS NEVER A SERIAL-LANE TARGET (P31 S60). main gates through tools/gate_main.py on
        # the main lane's own cadence — a clean whole-EXE rebuild with bisection — so this lane
        # cannot bank it however good the draft is, and a main target burns a slot to learn that.
        # Measured on the lane's first tells run: target [2/6] was func_8001382C @ main.
        if ex["b"] == "main":
            continue
        out.append({"gid": g["gid"], "name": ex["name"], "binary": ex["b"], "addr": ex["a"],
                    "nins": ex["nins"], "group_ins": g["ins"], "inst": g["inst"],
                    "lever": lever})
    out.sort(key=lambda x: -x["group_ins"])       # leverage first: the whole family's mass
    return out[:n]


def prepare(t):
    """Lever-specific preparation. Returns (ok, note)."""
    if t["lever"] != "jtbl-carve":
        return True, "no preparation needed"
    r = sh(f"{PY} tools/jtbl_carve.py {t['binary']} --func {t['name']}", timeout=1800)
    blob = (r.stdout + r.stderr).strip()
    if r.returncode != 0 or "LEADING-ISLAND" in blob or "NON-CONTIGUOUS" in blob:
        # Report the LAST meaningful lines, not the first. jtbl_carve prints informational
        # progress before it fails, so `splitlines()[0]` reported `trimmed 1 trailing .align pad
        # word(s) — 13 real entries` — an INFO line — as the refusal reason for ov_SC06_029, while
        # the actual cause was never shown. A Traceback likewise begins "Traceback (most recent
        # call last):", which names nothing. The last lines carry the exception and the message.
        lines = [l for l in blob.splitlines() if l.strip()]
        why = " | ".join(lines[-3:])[:400] if lines else f"rc={r.returncode}"
        cls = ("LEADING-ISLAND" if "LEADING-ISLAND" in blob else
               "NON-CONTIGUOUS" if "NON-CONTIGUOUS" in blob else
               "CRASH" if "Traceback" in blob else "REFUSED")
        return False, f"carve {cls}: {why}"
    r = sh(f"make --no-print-directory extract BINARY={t['binary']}", timeout=3600)
    if r.returncode != 0:
        sh(f"{PY} tools/jtbl_carve.py {t['binary']} --revert")
        return False, "make extract failed after carve (carve reverted)"
    return True, "carved + re-extracted"


def revert_prepare(t):
    if t["lever"] == "jtbl-carve":
        sh(f"{PY} tools/jtbl_carve.py {t['binary']} --revert")
        sh(f"make --no-print-directory extract BINARY={t['binary']}", timeout=3600)


def build_brief(t):
    """The accumulating brief — every idiom banked so far, plus this target's framing."""
    learned = open(NOTES).read() if os.path.exists(NOTES) else ""
    head = (f"You are cracking ONE function to byte-identical MIPS: {t['name']} in {t['binary']}, "
            f"{t['nins']} instructions, lever {t['lever']}.\n"
            f"Its group holds {t['inst']} members / {t['group_ins']} instructions, so what you learn "
            f"here is worth far more than this one function.\n\n"
            "The .s is the ONLY ground truth. match_one masks jal/HI16/LO16 relocations, so it "
            "verifies instruction SHAPE, not symbol IDENTITY — a wrong-symbol draft reports a clean "
            "MATCH. Check the symbols yourself against the .s.\n")
    if learned.strip():
        head += ("\n--- IDIOMS ALREADY LEARNED IN THIS RUN (each one was byte-confirmed; use them) ---\n"
                 + learned + "\n--- end idioms ---\n")
    return head


def distill(t, outdir, env):
    """Ask for the generalizable idiom and append it to the notes the next target will read."""
    brief = (f"You just matched {t['name']} ({t['binary']}, {t['nins']} instructions) to "
             "byte-identical output. Write the GENERALIZABLE idiom you used, for a decompilation "
             "cookbook read by other agents.\n\n"
             "Rules: describe the asm TELL that identifies this pattern, the C construct that "
             "reproduces it, and the boundary — when it does NOT apply. Name one thing you tried "
             "that FAILED and why. No narration of your session; write it as a reusable rule. "
             "Under 300 words. Reply with the note itself, no preamble.")
    bp = f"{outdir}/distill_brief.txt"
    open(bp, "w").write(brief)
    tf = f"{outdir}/distill_target.json"
    json.dump([{"name": t["name"], "addr": t["addr"], "nins": t["nins"], "binary": t["binary"],
                "sub": t.get("sub", ""), "asm": t.get("asm", ""), "tu": t.get("tu")}], open(tf, "w"))
    r = subprocess.run([PY, "-u", "tools/api_agent.py", "--targets", tf, "--brief", bp,
                        "--out", f"{outdir}/distill", "--max-turns", "4", "--max-cost", "0.50"],
                       capture_output=True, text=True, env=env, timeout=3600)
    text = ""
    for p in sorted(glob.glob(f"{outdir}/distill/*.txt")) + sorted(glob.glob(f"{outdir}/distill/*.md")):
        text = open(p).read(); break
    if not text:
        tail = [l for l in r.stdout.splitlines() if l.strip()]
        text = "\n".join(tail[-25:])
    with open(NOTES, "a") as fh:
        fh.write(f"\n\n## {t['name']} ({t['binary']}, {t['nins']} ins, lever {t['lever']})\n"
                 f"_banked {time.strftime('%Y-%m-%d %H:%M')} — group worth {t['group_ins']} ins_\n\n"
                 f"{text.strip()}\n")
    return len(text.strip())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--lever", default="jtbl-carve")
    ap.add_argument("--n", type=int, default=6, help="how many targets to work, serially")
    ap.add_argument("--min-ins", type=int, default=60)
    ap.add_argument("--max-turns", type=int, default=60)
    ap.add_argument("--allow-md", action="store_true",
                    help="include md_* members (jtbl_carve refuses leading-island modules — off by default)")
    a = ap.parse_args()

    # R43 (P31 S59): jtbl-carve moved to tools/jtbl_lane.py. This lane's prepare() carves the
    # UNSPLICED function — the §61b-refuted order (the same-subseg non-contiguity is only
    # detectable with the body in the object, so the pre-carve "succeeds" with a spec that fails
    # when the body lands) — and it cannot auto-isolate (the S58 ledger: 8 attempts, 0 banks).
    # jtbl_lane defers the carve to harvest_verify's gate-time prep and probes feasibility
    # read-only instead. Refuse rather than mishandle.
    if a.lever == "jtbl-carve":
        sys.exit("idiom_serial: the jtbl-carve lever is handled by tools/jtbl_lane.py (P31 S59) —"
                 " this lane's pre-draft carve runs the §61b-refuted order and cannot isolate.\n"
                 "  tools/jtbl_lane.py --census        # ranked work-list\n"
                 "  tools/jtbl_lane.py --n 6           # serial carve→draft→bank")

    targets = pick_targets(a.lever, a.n, a.min_ins, a.allow_md)
    if not targets:
        sys.exit(f"no {a.lever} targets at >={a.min_ins} ins (allow_md={a.allow_md})")
    log(f"serial idiom lane: {len(targets)} targets, lever {a.lever}, "
        f"{sum(t['group_ins'] for t in targets)} group-instructions of leverage")
    env = env_for_api()

    for i, t in enumerate(targets, 1):
        log(f"=== [{i}/{len(targets)}] {t['name']} @ {t['binary']} · {t['nins']} ins · "
            f"group {t['inst']} members / {t['group_ins']} ins ===")
        row = {"t": time.time(), "target": t, "stage": "prepare"}
        # Do NOT blind-revert. A concurrent lane (the campaign gates with commit=False) leaves
        # real banked work uncommitted, and `git checkout --` cannot tell it from residue. Commit
        # it instead; refuse to proceed if that fails. Same footgun as ox_campaign.gate().
        if sh("git status --porcelain -- src/ config/").stdout.strip():
            log("  tree dirty at entry — committing it rather than reverting")
            sh("git add -A src/ config/")
            sh("git reset -q -- src/*.c")   # S59: main TUs — one writer (gate_main), one committer (main_lane)
            # A CONTENDED INDEX IS NOT A DIRTY TREE (P31 S60). Six campaign lanes plus the
            # re-gate runner commit continuously, so `git commit` here loses the index.lock race
            # routinely — and the lane then refused, on its first tells run, over a tree that was
            # perfectly fine. Retry the commit a few times before concluding anything; the refusal
            # is for FOREIGN DIRT this lane must not adopt, not for a lock held for two seconds.
            for _try in range(6):
                if not sh("git status --porcelain -- src/ config/").stdout.strip():
                    break
                sh("git add -A src/ config/")
                sh("git reset -q -- src/*.c")
                if sh('git commit -q -m "chore(decomp): commit in-tree banked work before the '
                      'serial lane"').returncode == 0:
                    break
                time.sleep(5)
            if any(l.strip() and not re.match(r'^\s*[MARD?]+\s+src/[^/]+\.c$', l)
                   for l in sh("git status --porcelain -- src/ config/").stdout.splitlines()):
                log("  ! foreign dirt in src/ or config/ that this lane must not adopt — refusing")
                return 1

        ok, note = prepare(t)
        log(f"  prepare: {note}")
        if not ok:
            row.update(outcome="prepare-failed", note=note)
            open(LEDGER, "a").write(json.dumps(row) + "\n"); continue

        outdir = f".run/idiom_serial/{t['name']}"
        shutil.rmtree(outdir, ignore_errors=True); os.makedirs(outdir, exist_ok=True)
        sub = os.path.dirname(sh(f"ls asm/{t['binary']}/nonmatchings/*/{t['name']}.s 2>/dev/null "
                                 "| head -1").stdout.strip())
        t["sub"], t["asm"] = sub, f"{sub}/{t['name']}.s"
        t["tu"] = None
        if not sub:
            row.update(outcome="no-asm", note="target .s not found after prepare")
            open(LEDGER, "a").write(json.dumps(row) + "\n"); revert_prepare(t); continue

        bp = f"{outdir}/brief.txt"; open(bp, "w").write(build_brief(t))
        tf = f"{outdir}/target.json"; json.dump([t], open(tf, "w"), indent=1)
        log(f"  drafting (max {a.max_turns} turns, brief carries "
            f"{os.path.getsize(NOTES) if os.path.exists(NOTES) else 0} bytes of learned idioms)")
        # NO --cards HERE (P31 S60). .run/aprop_cards.json is a FAMILY-card file — rows are
        # {family, members, seed, ...} with no per-function key — while api_agent's --cards wants
        # per-function wave cards. It crashed the agent at turn 0 on every target since this line
        # was written, which is why the lane's ledger held 8 rows and had "never yet run on tells".
        # The serial lane's fuel is its --brief (the target plus every idiom distilled so far this
        # run), which is the compounding channel the wide fan-out lacks; it needs no wave card.
        subprocess.run([PY, "-u", "tools/api_agent.py", "--targets", tf,
                        "--brief", bp, "--out", f"{outdir}/draft",
                        "--max-turns", str(a.max_turns), "--max-cost", "2.0"],
                       stdout=open(f"{outdir}/draft.log", "w"), stderr=subprocess.STDOUT,
                       env=env, timeout=14400)

        cfile = f"{outdir}/draft/{t['name']}.c"
        if not os.path.isfile(cfile):
            row.update(outcome="no-draft")
            open(LEDGER, "a").write(json.dumps(row) + "\n"); revert_prepare(t); continue

        gd = f"{outdir}/gate/{t['binary']}"; os.makedirs(gd, exist_ok=True)
        shutil.copy(cfile, f"{gd}/{t['name']}.c")
        t0 = time.time()
        sh(f"{PY} tools/sweep_parallel.py --drafts {outdir}/gate -j 2", timeout=7200)
        banked = any(os.path.getmtime(f) >= t0 and t["name"] in open(f).read()
                     for f in glob.glob(".run/auto/bulk/*.verified.txt"))
        if banked:
            sh("git add -A src/ config/")
            sh("git reset -q -- src/*.c")   # S59: main TUs — one writer, one committer
            sh(f'git commit -q -m "feat(decomp): serial idiom lane — {t["name"]} '
               f'({t["nins"]} ins, {t["lever"]}, group worth {t["group_ins"]})"')
            nb = distill(t, outdir, env)
            log(f"  BANKED + distilled {nb} chars of idiom -> {NOTES}")
            row.update(outcome="banked", idiom_chars=nb,
                       commit=sh("git rev-parse --short HEAD").stdout.strip())
        else:
            log("  not banked — reverting preparation")
            revert_prepare(t)
            row.update(outcome="gate-failed")
        open(LEDGER, "a").write(json.dumps(row) + "\n")
    log("serial lane finished")


if __name__ == "__main__":
    sys.exit(main() or 0)

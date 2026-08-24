#!/usr/bin/env python3
"""jtbl_lane.py — carve → draft → bank for jump-table functions (P31 S59).

WHY A LANE, AND WHY THE CARVE IS *NOT* IN IT. A jtbl function's table lives in `.rodata`; while
the function is an INCLUDE_ASM stub the table is emitted from the stub's `.s`, and the moment the
function is matched cc1 emits it itself — so the table must be CARVED into its own config piece
before a draft can bank. Every earlier attempt to put that carve anywhere but the gate failed the
same way:

  * PRE-DRAW / PRE-DRAFT carving (idiom_serial's S58 `prepare()`) runs the §61b-REFUTED order:
    the same-subseg non-contiguity that requires isolation is only DETECTABLE once the body is in
    the object, so an unspliced carve "succeeds" with a spec that fails when the body lands — and
    it cannot auto-isolate at all (the S58 ledger: 8 attempts, 0 banks, 6 prepare-failures).
  * A pre-drawn carve also sits in config/ as a STUB-OWNED piece for the whole draft lifetime:
    §129b-stranded (jr_inventory refuses every later isolation in the binary), and the campaign's
    R42 commit-dirty-trees-at-gate-entry step would COMMIT that poisoned state.

  THE CARVE THEREFORE HAPPENS INSIDE THE BYTE-GATE, per draft, splice-first, snapshot-reverted on
  rejection — `harvest_verify._jtbl_prep_one` (§61b/§61d/§62, byte-proven), which as of S59 also
  performs the §260 leading-island split for md_* modules. This lane's own "prepare" step is a
  READ-ONLY structural probe (jtbl_carve.island_probe): it decides *whether the gate can reach the
  table at all*, and refuses the rest by name (R43).

WHAT THE LANE DOES, per target, serially:
  1. probe    — refuse main (tools/gate_main.py, manual cadence), island-blocked (stack order),
                island-pads (needs §8e pads for modules.mk), -O0-stranded (§261) — each named.
  2. draft    — `--draft-dir` (any drafter's output, the campaign's included), else one
                api_agent run (the idiom_serial drafting flow, jtbl-briefed).
  3. gate     — gate_stage.run_gate on THIS binary only, holding the campaign's own per-binary
                flock (.run/auto/gate.<bin>.lock) and the fleet shared lock (run_gate takes it
                EXCLUSIVE while the arity pre-pass is enabled), propagate=False commit=False —
                the exact sweep_parallel worker call, so the lane and the campaign cannot race.
                The gate's harvest_verify does the carve (tail merge/isolate or island split),
                the §62 post-carve reconcile, the whole-binary SHA verdict, and the snapshot
                restore on rejection.
  4. commit   — on a bank, `git add src/<bin>/ config/splat.<bin>.yaml config/overlays.mk` and
                commit immediately (R42: banked work is committed the moment it exists; the add
                is scoped to the binary's own paths, never `-A` across the tree). A failed gate
                commits nothing, and the lane asserts the gate left no residue (R32).

ONE JTBL TARGET PER GATE INVOCATION. §61c's standing constraint: the per-draft undo is byte-
proven one table-bearing draft at a time; a second one in the same invocation repartitions
shared source under the first one's snapshot. The lane stages exactly one draft per run_gate
call, so the unproven batch case is unreachable by construction.

  tools/jtbl_lane.py --census                                   # read-only ranked work-list
  tools/jtbl_lane.py --targets func_8017DCC0@ov_SC03_014 --draft-dir .run/mydrafts
  tools/jtbl_lane.py --n 6 --min-ins 40                         # atlas-fed, api-drafted, serial
"""
import argparse
import fcntl
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
sys.path.insert(0, os.path.join(REPO, "tools"))
import backlog          # noqa: E402
import gate_stage       # noqa: E402
import jtbl_carve       # noqa: E402  (island_probe — the read-only classifier)

PY = ".venv/bin/python"
RUN = ".run/jtbl_lane"
LEDGER = ".run/jtbl_lane_ledger.jsonl"
BANKABLE = ("tail", "covered", "island-end")


def log(m):
    print(f"[{time.strftime('%H:%M:%S')}] {m}", flush=True)


def sh(cmd, timeout=None):
    return subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=timeout)


def _o0_stranded(asm_path, subseg):
    """§261: an -O0 function in an -O2 object cannot bank however good the draft.

    Same oracle as build_wave_atlas._o0_unbankable and match_one's derivation (the two other
    sites; neither is importable — build_wave_atlas parses argv at module level): the frame-
    pointer prologue `sw $fp` + `addu $fp,$sp,$zero` (21F0A003) inside the first instructions,
    anchored at `glabel` so a migrated jump table ahead of the code is not read as the prologue."""
    if "_o0" in subseg or subseg == "boot":
        return False                                    # the build compiles this object -O0
    try:
        head, started = [], False
        for ln in open(os.path.join(REPO, asm_path)):
            if not started:
                started = bool(re.match(r"\s*glabel\s", ln))
                continue
            m = re.match(r"\s*/\* [0-9A-Fa-f]+ [0-9A-Fa-f]{8} ([0-9A-Fa-f]{8}) \*/\s*(\S.*)?", ln)
            if m:
                head.append((m.group(1).upper(), (m.group(2) or "").strip()))
            if len(head) >= 8:
                break
    except OSError:
        return False
    setup = any(w == "21F0A003" or re.match(r"addu\s+\$fp,\s*\$sp,\s*\$zero", t) for w, t in head)
    save = any(re.match(r"sw\s+\$fp,", t) for _w, t in head)
    return setup and save


def probe(binary, fn):
    """(bankable, kind, detail) — the R43 router. Every refusal names its owner."""
    kind, detail = jtbl_carve.island_probe(binary, fn)
    if kind not in BANKABLE:
        return False, kind, detail
    s = sorted(glob.glob(os.path.join(REPO, f"asm/{binary}/nonmatchings/*/{fn}.s")))
    if s:
        sub = os.path.basename(os.path.dirname(s[-1]))
        if _o0_stranded(os.path.relpath(s[-1], REPO), sub):
            return False, "o0-stranded", ("-O0 prologue in an -O2 object (§261) — needs the "
                                          "-O0 cluster carve (rollout_o0), not this lane")
    return True, kind, detail


def atlas_targets(n, min_ins, max_ins):
    a = json.load(open(".run/atlas.json"))
    out = []
    for g in a["groups"]:
        if g.get("lever") != "jtbl-carve":
            continue
        for m in g.get("members", []):
            if not (min_ins <= (m.get("nins") or 0) <= max_ins):
                continue
            out.append({"fn": m["name"], "binary": m["b"], "addr": m.get("a"),
                        "nins": m.get("nins"), "gid": g["gid"], "group_ins": g["ins"],
                        "inst": g["inst"]})
    out.sort(key=lambda t: -t["group_ins"])            # leverage first (the family's whole mass)
    picked, seen_bin = [], set()
    for t in out:
        if len(picked) >= n:
            break
        if t["binary"] in seen_bin:                    # one jtbl target per binary per run
            continue
        ok, kind, detail = probe(t["binary"], t["fn"])
        t.update(kind=kind, detail=detail)
        if ok:
            picked.append(t); seen_bin.add(t["binary"])
    return picked


def census():
    """Read-only ranked work-list over EVERY atlas jtbl member (R32: denominator printed)."""
    a = json.load(open(".run/atlas.json"))
    rows = []
    for g in a["groups"]:
        if g.get("lever") != "jtbl-carve":
            continue
        for m in g.get("members", []):
            ok, kind, detail = probe(m["b"], m["name"])
            rows.append({"b": m["b"], "fn": m["name"], "nins": m.get("nins"),
                         "gid": g["gid"], "kind": kind, "ok": ok, "detail": detail})
    import collections
    cnt, ins = collections.Counter(), collections.Counter()
    for r in rows:
        cnt[r["kind"]] += 1
        ins[r["kind"]] += r["nins"] or 0
    print(f"DENOMINATOR: {len(rows)} atlas jtbl-carve members probed")
    for k in sorted(cnt, key=lambda k: -ins[k]):
        reach = "REACHABLE" if k in BANKABLE else "refused"
        print(f"  {k:16} {cnt[k]:3d} members {ins[k]:6d} ins  [{reach}]")
    os.makedirs(RUN, exist_ok=True)
    json.dump(rows, open(f"{RUN}/census.json", "w"), indent=1)
    print(f"-> {RUN}/census.json")


def env_for_api():
    key = ""
    for line in open(".env"):
        if line.startswith("open_router_key="):
            key = line.split("=", 1)[1].strip(); break
    return dict(os.environ, API_BASE="https://openrouter.ai/api/v1", API_KEY=key,
                MODEL=os.environ.get("MODEL", "stealth/ox-alpha"),
                MAXTOK=os.environ.get("MAXTOK", "8000"))


def build_brief(t):
    return (
        f"You are cracking ONE jump-table (switch) function to byte-identical MIPS: {t['fn']} in "
        f"{t['binary']}, {t['nins']} instructions.\n\n"
        "jtbl facts that matter (byte-proven project law):\n"
        "* Write the NATURAL C switch. Do not try to emit or imitate the table — cc1 emits it; "
        "the build system carves it at gate time. Your job is only the .text body.\n"
        "* The function's own `sltiu $x, $idx, N` names the true case count N (cases 0..N-1).\n"
        "* match_one masks jal/HI16/LO16 relocations: it verifies instruction SHAPE, not symbol "
        "identity. Check every symbol against the .s yourself.\n"
        "* A shared case tail is cross_jump: write both cases naturally; gcc merges the common "
        "SUFFIX only (§193-C).\n")


def draft_api(t, outdir, max_turns):
    env = env_for_api()
    os.makedirs(outdir, exist_ok=True)
    bp = f"{outdir}/brief.txt"
    open(bp, "w").write(build_brief(t))
    tf = f"{outdir}/target.json"
    sub = os.path.dirname(sh(f"ls asm/{t['binary']}/nonmatchings/*/{t['fn']}.s 2>/dev/null "
                             "| head -1").stdout.strip())
    json.dump([{"name": t["fn"], "addr": t.get("addr"), "nins": t["nins"], "binary": t["binary"],
                "sub": sub, "asm": f"{sub}/{t['fn']}.s", "tu": None}], open(tf, "w"))
    subprocess.run([PY, "-u", "tools/api_agent.py", "--targets", tf, "--cards",
                    ".run/aprop_cards.json", "--brief", bp, "--out", f"{outdir}/draft",
                    "--max-turns", str(max_turns), "--max-cost", "2.0"],
                   stdout=open(f"{outdir}/draft.log", "w"), stderr=subprocess.STDOUT,
                   env=env, timeout=14400)
    p = f"{outdir}/draft/{t['fn']}.c"
    return p if os.path.isfile(p) else None


def gate_one(t, draft_path):
    """Stage ONE draft and run the campaign's own gate on it. Returns (banked, summary)."""
    b, fn = t["binary"], t["fn"]
    stage = f"{RUN}/stage_{b}_{fn}"
    shutil.rmtree(stage, ignore_errors=True)
    os.makedirs(stage)
    shutil.copy(draft_path, os.path.join(stage, fn + ".c"))
    os.makedirs(RUN, exist_ok=True)
    backlog.JSONL = f"{RUN}/{b}.backlog.jsonl"        # per-lane result files, never the shared
    backlog.MD = f"{RUN}/{b}.backlog.md"              # ones (the §55b shared-scratch trap)
    pre = set(sh(f"git status --porcelain -- src/{b}/ config/splat.{b}.yaml "
                 f"config/overlays.mk").stdout.splitlines())
    r = gate_stage.run_gate(
        stage, binary=b, propagate=False, commit=False, source_tag="jtbl-lane",
        lock_path=f".run/auto/gate.{b}.lock",
        verified_out=f"{RUN}/{b}.verified.txt", failed_out=f"{RUN}/{b}.failed.txt",
        compute_fleet=False)
    banked = fn in (r.get("verified") or [])
    if not banked:
        # R32 tripwire: the gate's own prep must have restored everything it touched. NEW dirt
        # scoped to this binary after a failed gate is residue, and residue rides into the next
        # build silently — name it, never swallow it. (Pre-existing dirt — another lane's
        # uncommitted banked work — is NOT ours to touch: R42.)
        post = set(sh(f"git status --porcelain -- src/{b}/ config/splat.{b}.yaml "
                      f"config/overlays.mk").stdout.splitlines())
        new = sorted(post - pre)
        if new:
            log(f"  !! RESIDUE after a failed gate on {b} (R32 — the prep's restore missed "
                f"these): {new[:8]}")
    return banked, r


def commit_bank(t):
    """Commit exactly the paths a jtbl bank can touch, scoped to THIS binary (R42: never -A
    across the tree — other lanes' uncommitted banks elsewhere are not ours to sweep up;
    pre-existing uncommitted work inside THIS binary's scope is banked work and riding along is
    the commit-never-revert direction)."""
    b, fn = t["binary"], t["fn"]
    sh(f"git add src/{b}/ config/splat.{b}.yaml config/overlays.mk")
    msg = (f"feat(decomp): jtbl lane — {fn} banked in {b} ({t.get('nins')} ins, {t.get('kind')})\n\n"
           f"carve→draft→bank through harvest_verify's gate-time jtbl prep "
           f"({'island split §260' if str(t.get('kind')).startswith(('covered', 'island')) else 'tail carve §8a'}); "
           f"whole-binary SHA green.")
    r = sh(f'git commit -q -m "{msg}"')
    return sh("git rev-parse --short HEAD").stdout.strip() if r.returncode == 0 else None


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--census", action="store_true", help="read-only ranked work-list, then exit")
    ap.add_argument("--targets", default=None,
                    help="explicit fn@binary[,fn@binary...] (else drawn from the atlas)")
    ap.add_argument("--draft-dir", default=None,
                    help="use <dir>/<fn>.c instead of api drafting (any drafter's output)")
    ap.add_argument("--n", type=int, default=4)
    ap.add_argument("--min-ins", type=int, default=0)
    ap.add_argument("--max-ins", type=int, default=200)
    ap.add_argument("--max-turns", type=int, default=40)
    a = ap.parse_args()

    if a.census:
        return census()

    if a.targets:
        targets = []
        for spec in a.targets.split(","):
            fn, _, b = spec.partition("@")
            ok, kind, detail = probe(b, fn)
            t = {"fn": fn, "binary": b, "nins": None, "kind": kind, "detail": detail}
            s = sorted(glob.glob(f"asm/{b}/nonmatchings/*/{fn}.s"))
            if s:
                t["nins"] = sum(1 for ln in open(s[-1])
                                if re.match(r"\s*/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/", ln))
            if not ok:
                log(f"REFUSED {fn}@{b}: {kind} — {detail}")
                open(LEDGER, "a").write(json.dumps(
                    {"t": time.time(), "fn": fn, "binary": b, "outcome": "refused",
                     "kind": kind, "detail": detail}) + "\n")
                continue
            targets.append(t)
    else:
        targets = atlas_targets(a.n, a.min_ins, a.max_ins)

    if not targets:
        log("no bankable jtbl targets under these filters")
        return 1
    log(f"jtbl lane: {len(targets)} target(s): "
        + ", ".join(f"{t['fn']}@{t['binary']}[{t['kind']}]" for t in targets))

    for t in targets:
        row = {"t": time.time(), "fn": t["fn"], "binary": t["binary"], "nins": t.get("nins"),
               "kind": t.get("kind")}
        if a.draft_dir:
            draft = os.path.join(a.draft_dir, t["fn"] + ".c")
            if not os.path.isfile(draft):
                log(f"  {t['fn']}: no draft in {a.draft_dir} — skipping")
                row.update(outcome="no-draft")
                open(LEDGER, "a").write(json.dumps(row) + "\n")
                continue
        else:
            log(f"  drafting {t['fn']} via api_agent …")
            draft = draft_api(t, f"{RUN}/{t['fn']}", a.max_turns)
            if not draft:
                log(f"  {t['fn']}: drafter produced nothing")
                row.update(outcome="no-draft")
                open(LEDGER, "a").write(json.dumps(row) + "\n")
                continue
        # HOLD THE CAMPAIGN'S DRAW LOCK ACROSS GATE + COMMIT. It is the campaign's own
        # gate-serialization primitive: ox_campaign's gater holds it for its WHOLE gate
        # (including the blanket `git add -A src/ config/` commits), and the maintenance lane
        # takes it for the same reason ("gates never overlap"). Without it, the gater's
        # entry/exit commit can land while THIS gate has a transient carve + candidate body
        # applied — committing an unverified state. Per-binary flocks protect builds; only this
        # lock protects the COMMIT boundary.
        os.makedirs(".run/auto", exist_ok=True)
        _dl = open(".run/auto/draw.lock", "w")
        log(f"  waiting for the campaign draw lock (gates never overlap) …")
        fcntl.flock(_dl, fcntl.LOCK_EX)
        try:
            log(f"  gating {t['fn']}@{t['binary']} (per-binary flock + shared lock; the gate carves)")
            banked, summary = gate_one(t, draft)
            if banked:
                sha = commit_bank(t)
                log(f"  BANKED {t['fn']}@{t['binary']} -> commit {sha}")
                row.update(outcome="banked", commit=sha)
            else:
                log(f"  not banked: {t['fn']} (gate verdict: {summary.get('banked')}/"
                    f"{summary.get('drafts')}; backlog {RUN}/{t['binary']}.backlog.jsonl)")
                row.update(outcome="gate-failed", summary={k: summary.get(k) for k in
                                                           ("drafts", "banked", "near", "failed")})
        finally:
            fcntl.flock(_dl, fcntl.LOCK_UN)
            _dl.close()
        open(LEDGER, "a").write(json.dumps(row) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main() or 0)

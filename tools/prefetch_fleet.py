#!/usr/bin/env python3
"""prefetch_fleet.py — the fleet Ghidra-C prefetch batch (P30 T0.5; roadmap v2 §4).

Headless, zero-token, resumable: batch-decompile ONE representative of every remaining distinct
stub class (+ ALL of main's and the resident's stubs) into `.run/ghidra_c/<name>.c` — the drafting
fuel for Lanes B/C and the P31 main campaign. No live MCP; runs unattended for hours.

WHAT gets prefetched (R33 — every input derived, none guessed):
  * per h_seq family (incl. singletons) in `.run/family_hseq.json`: ONE representative member —
    prefer the `ov_SC01_077` instance (the canonical drafting overlay), else the first member.
    Members are NEVER drafted (they bank by remap), so one representative per class suffices —
    which is also why the flat name-keyed cache is correct: one file per distinct class.
  * main: ALL `corpus.stubs("main")` (2,002 — the ~950 SDK-named decompile harmlessly and feed the
    frontier report's SDK-shape detection).
  * resident: `corpus.stubs("resident")` (the 14).
  * already-cached names (`.run/ghidra_c/func_%08X.c`) are SKIPPED — re-running resumes.

HOW (reusing the existing, proven pieces — nothing new under the hood):
  * `DecompileFunctions.java <addrfile> <outdir>` per program via analyzeHeadless -noanalysis
    (SETUP §"headless harvest Ghidra-C pre-pass", Phase 17).
  * a MISSING overlay program is imported on demand via `tools/ghidra_import_raw.sh
    <blob> <vram> <alias>` — blob DERIVED from `family_remap.img_path` (the splat target_path,
    P28's R33 fix: SC07's code is at PAC entry 1), vram parsed from `config/splat.<ov>.yaml`.
  * the project lock is EXCLUSIVE: the batch is strictly serial, and a serving MCP server is
    stopped first via `tools/ghidra_mcp_stop.sh` (R23's sanctioned mechanism; a notice is printed —
    when MCP is next needed, R29 applies: pause + ask for /mcp reconnect after restart).

R32: every program's outcome is reported (decompiled / still-missing / import-failed); a failed
overlay is logged and the batch CONTINUES; final exit is non-zero if anything hard-failed.

  tools/prefetch_fleet.py [--limit-programs N] [--dry-run]
"""
import argparse, glob, json, os, re, subprocess, sys, time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
import corpus
import family_remap

GHIDRA = os.environ.get("GHIDRA_INSTALL_DIR", os.path.expanduser("~/ghidra_12.1_PUBLIC"))
HEADLESS = os.path.join(GHIDRA, "support", "analyzeHeadless")
PROJ_DIR = os.path.join(REPO, "ghidra")
PROJ = "bfm"
SCRIPTS = os.path.join(REPO, "tools", "ghidra_scripts")
OUT = os.path.join(REPO, ".run", "ghidra_c")
WORK = os.path.join(REPO, ".run", "prefetch")
PROGRAM_NAME = {"main": "SLUS_007.26", "resident": "resident"}   # overlays: alias == program name


def fname(addr):
    return "func_%08X" % addr


def cached():
    return {os.path.basename(p)[:-2] for p in glob.glob(os.path.join(OUT, "*.c"))}


def gather_targets():
    """program -> sorted set of vram addrs to decompile (uncached only)."""
    have = cached()
    prog = {}

    def add(program, addr):
        if fname(addr) not in have:
            prog.setdefault(program, set()).add(addr)

    for b in ("main", "resident"):
        for a in corpus.stubs(b):
            add(PROGRAM_NAME[b], a)
    fams = json.load(open(os.path.join(REPO, ".run", "family_hseq.json")))["families"]
    for f in fams:
        members = [tuple(m) for m in f["members"]]
        if not members:
            continue
        rep = next((m for m in members if m[0] == "ov_SC01_077"), members[0])
        ov, addr_s = rep
        add(ov, int(addr_s, 16))
    return {p: sorted(a) for p, a in prog.items()}


def vram_of(ov):
    cfg = os.path.join(REPO, f"config/splat.{ov}.yaml")
    m = re.search(r"vram:\s*(0x[0-9A-Fa-f]+)", open(cfg).read())
    if not m:
        raise ValueError(f"{cfg}: no vram")
    return m.group(1)


def mcp_stop_if_running():
    r = subprocess.run(["ss", "-tln"], capture_output=True, text=True)
    if re.search(r":8080\b", r.stdout):
        print("[prefetch] MCP server is serving — stopping it (R23; R29 applies at next MCP use)")
        subprocess.run(["bash", os.path.join(REPO, "tools", "ghidra_mcp_stop.sh")], cwd=REPO)


def run_decompile(program, addrfile, log):
    cmd = [HEADLESS, PROJ_DIR, PROJ, "-process", program, "-noanalysis",
           "-scriptPath", SCRIPTS, "-postScript", "DecompileFunctions.java", addrfile, OUT]
    with open(log, "a") as lf:
        return subprocess.run(cmd, stdout=lf, stderr=subprocess.STDOUT, cwd=REPO).returncode


def run_define(program, addrs, log):
    """DefineFunctions.java completion pass (the Phase-10 mechanism): raw-blob auto-analysis only
    finds the REACHABLE subset; splat's linear sweep found them all, so seed the program with the
    still-missing stub addrs (probe evidence: main 477/2002, fresh imports ~60% defined) and let
    the decompile retry pick them up. Reads .run/<prog>_funcs.txt implicitly (0xADDR per line)."""
    fl = os.path.join(REPO, ".run", f"{program}_funcs.txt")
    open(fl, "w").write("\n".join("0x%08X" % a for a in addrs) + "\n")
    cmd = [HEADLESS, PROJ_DIR, PROJ, "-process", program, "-noanalysis",
           "-scriptPath", SCRIPTS, "-postScript", "DefineFunctions.java"]
    with open(log, "a") as lf:
        return subprocess.run(cmd, stdout=lf, stderr=subprocess.STDOUT, cwd=REPO).returncode


def import_overlay(ov, log):
    blob = family_remap.img_path(ov)
    vram = vram_of(ov)
    print(f"[prefetch] importing {ov}  (blob={os.path.relpath(blob, REPO) if os.path.isabs(blob) else blob}, vram={vram})")
    with open(log, "a") as lf:
        return subprocess.run(["bash", os.path.join(REPO, "tools", "ghidra_import_raw.sh"),
                               blob, vram, ov], stdout=lf, stderr=subprocess.STDOUT, cwd=REPO).returncode


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit-programs", type=int, help="process only the first N programs (probe)")
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()

    os.makedirs(OUT, exist_ok=True)
    os.makedirs(WORK, exist_ok=True)
    targets = gather_targets()
    order = sorted(targets, key=lambda p: -len(targets[p]))          # big pools first
    if a.limit_programs:
        order = order[:a.limit_programs]
    total = sum(len(targets[p]) for p in order)
    print(f"[prefetch] {len(order)} programs / {total} uncached representatives "
          f"(cache holds {len(cached())})")
    if a.dry_run:
        for p in order:
            print(f"  {p:16} {len(targets[p]):5}")
        return 0

    mcp_stop_if_running()
    failed = {}
    t0 = time.time()
    for i, p in enumerate(order, 1):
        addrs = targets[p]
        addrfile = os.path.join(WORK, f"{p}.addrs")
        open(addrfile, "w").write("\n".join("%08X" % x for x in addrs) + "\n")
        log = os.path.join(WORK, f"{p}.log")
        before = len(cached())
        rc = run_decompile(p, addrfile, log)
        if rc != 0 and not p.startswith(("SLUS", "sep8", "aug31")) and p != "resident":
            # program likely missing -> import on demand, retry once. NEVER -overwrite an
            # existing program; ghidra_import_raw stages under the alias only when absent.
            tail = open(log, errors="replace").read()[-600:]
            # Ghidra's actual phrase: "Requested project program file(s) not found: <name>"
            if ("not found" in tail or "not exist" in tail or "NOT_FOUND" in tail
                    or "Unable to locate" in tail):
                if import_overlay(p, log) == 0:
                    rc = run_decompile(p, addrfile, log)
        # completion pass: define the still-missing addrs, then re-decompile (resumable delta)
        have = cached()
        missing = [x for x in addrs if fname(x) not in have]
        if rc == 0 and missing:
            if run_define(p, missing, log) == 0:
                rc = run_decompile(p, addrfile, log)
        got = len(cached()) - before
        have = cached()
        missing = [x for x in addrs if fname(x) not in have]
        state = "OK" if rc == 0 else f"RC={rc}"
        print(f"[{i}/{len(order)}] {p:16} +{got}/{len(addrs)}  {state}  "
              f"({(time.time()-t0)/60:.0f} min elapsed)", flush=True)
        if rc != 0 or missing:
            failed[p] = (rc, len(missing))
    print(f"[prefetch] DONE: cache {len(cached())} files; "
          f"{len(failed)} programs with residue: "
          + (", ".join(f"{p}(rc={rc},missing={m})" for p, (rc, m) in sorted(failed.items())[:20]) or "none"))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())

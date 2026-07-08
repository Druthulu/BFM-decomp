#!/usr/bin/env python3
"""Phase-25 T7 — the MECHANICAL family sweep (the endgame's economic engine).

For each MATCHED ov_SC01_077 function that has unmatched SAME-ADDRESS h_norm-siblings (a byte-variant of
the same engine function in other overlays), remap its matched C to each sibling with `tools/family_remap`
and byte-gate it into that overlay. Banks per-overlay matches MECHANICALLY — ~0 agent tokens per member —
turning the 11.1 MB of h_norm structural families from "draft every copy" into "crack one, remap the rest".

The whole-binary byte-gate (`harvest_verify`) is the SOLE arbiter (G3/P9): a wrong remap is rejected.
Two-phase for efficiency: stage ALL remapped drafts grouped by (overlay, split-file), then gate each group
ONCE (chunk+bisect) — ~a few hundred gate cycles, not 156x134 individual builds. Remapped drafts are already
correct + self-contained, so they gate via PLAIN harvest_verify (NOT gate_stage's transforms, which perturb
a correct draft — T3 finding). Type-using families (custom struct types / conflicting shared decls) fail the
compile and are logged for the decl-reconcile pass; they are NOT remap failures.

  tools/family_sweep.py [--source ov_SC01_077] [--limit N] [--min-sibs 1] [--chunk 8] [--commit]
                        [--only 0xADDR,0xADDR]   # sweep just these exemplar addrs (validation)
"""
import json, glob, re, subprocess, os, sys, shutil, collections, argparse
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import family_remap as FR

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = ".venv/bin/python"
SWEEP = ".run/sweep"


def sh(cmd, timeout=None):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)


def load_sigs():
    """{overlay: {addr: (nins, h_exact, h_norm)}}."""
    sig = {}
    for p in sorted(glob.glob(os.path.join(REPO, ".run/sig.ov_*.jsonl"))):
        ov = os.path.basename(p).split("sig.")[1][:-6]
        d = {}
        for line in open(p):
            r = json.loads(line)
            d[int(r["addr"], 16)] = (r["nins"], r["h_exact"], r["h_norm"])
        sig[ov] = d
    return sig


def stub_map(ov):
    """{addr: (src_rel, asm_subdir)} for every INCLUDE_ASM stub in this overlay's src (all split files)."""
    m = {}
    for cf in sorted(glob.glob(os.path.join(REPO, f"src/{ov}/{ov}*.c"))):
        rel = os.path.relpath(cf, REPO)
        for asm_sub, fn in re.findall(r'INCLUDE_ASM\("([^"]+)",\s*(func_[0-9A-Fa-f]+)\)', open(cf).read()):
            m[int(fn.split("_")[1], 16)] = (rel, asm_sub)
    return m


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--source", default="ov_SC01_077")
    ap.add_argument("--limit", type=int, default=0, help="cap #exemplars (0 = all)")
    ap.add_argument("--min-sibs", type=int, default=1)
    ap.add_argument("--chunk", type=int, default=8)
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--only", default=None, help="comma-separated exemplar addrs to sweep (validation)")
    a = ap.parse_args()
    os.chdir(REPO)

    sig = load_sigs()
    src_sig = sig[a.source]
    src_stubs = stub_map(a.source)
    stubs = {ov: stub_map(ov) for ov in sig}

    # exemplars: MATCHED source fns (not a stub) with >=1 unmatched same-address h_norm-sibling
    only = set(int(x, 16) for x in a.only.split(",")) if a.only else None
    exemplars = []
    for addr, (nins, hx, hn) in src_sig.items():
        if addr in src_stubs:                                   # must be matched in the source
            continue
        if only is not None and addr not in only:
            continue
        sibs = [ov for ov in sig if ov != a.source and addr in sig[ov]
                and sig[ov][addr][2] == hn and addr in stubs[ov]]
        if len(sibs) >= a.min_sibs:
            exemplars.append((addr, nins, sibs))
    exemplars.sort(key=lambda e: -e[1] * len(e[2]))             # byte-weight order
    if a.limit:
        exemplars = exemplars[:a.limit]
    print(f"[sweep] {len(exemplars)} matched exemplars w/ h_norm-siblings; "
          f"{sum(len(s) for _, _, s in exemplars)} member-remaps")

    # ---- pre-classify: only sweep exemplars whose remap match_ones (isolation). TYPE-USING families
    # (custom struct types like MatEntry) CC1-FAIL in isolation AND need decl-reconcile in the TU; a
    # compile-failing draft makes harvest_verify bisect a whole chunk (1 build -> ~8), so deferring them
    # keeps the sweep gating only clean drafts. Deferred -> .run/sweep_deferred.txt (decl-reconcile pass).
    simple, deferred = [], []
    for addr, nins, sibs in exemplars:
        draft, _ = FR.remap(addr, a.source, sibs[0])
        if draft is None:
            deferred.append((addr, "remap-fail")); continue
        open(os.path.join(REPO, ".run/_clsfy.c"), "w").write(draft + "\n")
        r = sh([PY, "tools/match_one.py", f"func_{addr:08X}", "--c", ".run/_clsfy.c",
                "--asm-subdir", stubs[sibs[0]][addr][1]], timeout=180)
        first = (r.stdout.strip().splitlines() or ["?"])[0]
        (simple if first.startswith("MATCH") else deferred).append(
            (addr, nins, sibs) if first.startswith("MATCH") else (addr, "type/decl" if "FAIL" in first else "diff"))
    open(os.path.join(REPO, ".run/sweep_deferred.txt"), "w").write(
        "\n".join(f"0x{a:08x} {r}" for a, r in deferred) + "\n")
    print(f"[sweep] pre-classify: {len(simple)} simple (sweep now) / {len(deferred)} deferred "
          f"(decl-reconcile/investigate -> .run/sweep_deferred.txt)")
    exemplars = simple

    # ---- phase 1: remap every (exemplar -> sibling), stage grouped by (overlay, split src, asm subdir)
    shutil.rmtree(os.path.join(REPO, SWEEP), ignore_errors=True)
    groups = collections.defaultdict(list)                     # (ov, src_rel, subdir) -> [fn]
    remap_fail = 0
    for addr, nins, sibs in exemplars:
        for ov in sibs:
            draft, m = FR.remap(addr, a.source, ov)
            if draft is None:
                remap_fail += 1
                continue
            src_rel, subdir = stubs[ov][addr]
            d = os.path.join(REPO, SWEEP, ov)
            os.makedirs(d, exist_ok=True)
            open(os.path.join(d, f"func_{addr:08X}.c"), "w").write(draft + "\n")
            groups[(ov, src_rel, subdir)].append(f"func_{addr:08X}")
    print(f"[sweep] staged {sum(len(v) for v in groups.values())} drafts across {len(groups)} (overlay,split) "
          f"groups; {remap_fail} remap-fail")

    # ---- phase 2: gate each group ONCE (plain harvest_verify; remapped drafts need no transforms)
    banked = collections.Counter()
    failed = collections.Counter()
    for (ov, src_rel, subdir), fns in sorted(groups.items()):
        good_sha = open(os.path.join(REPO, f"config/check.{ov}.sha")).read().split()[0]
        r = sh([PY, "tools/harvest_verify.py", "--binary", ov, "--src", src_rel, "--asm-subdir", subdir,
                "--out", f"build/{ov}/{ov}", "--good-sha", good_sha,
                "--drafts", os.path.join(SWEEP, ov), "--chunk", str(a.chunk),
                "--verified-out", f".run/sweep_verified.{ov}.txt",
                "--failed-out", f".run/sweep_failed.{ov}.txt"], timeout=3600)
        vpath = os.path.join(REPO, f".run/sweep_verified.{ov}.txt")
        nver = len([x for x in open(vpath).read().split() if x]) if os.path.exists(vpath) else 0
        banked[ov] += nver
        failed[ov] += len(fns) - nver
        print(f"  {ov} [{os.path.basename(src_rel)}]: {nver}/{len(fns)} banked")

    nb, nf = sum(banked.values()), sum(failed.values())
    print(f"\n[sweep] BANKED {nb} member-matches / {nf} failed (decl-reconcile/byte) across {len(banked)} overlays")
    if a.commit and nb:
        sh(["git", "add", "-A", "src"])
        sh(["git", "commit", "-q", "-m",
            f"feat(phase-25): T7 mechanical family sweep — {nb} member-matches banked via family_remap"])
        print("[sweep] committed.")
    print(json.dumps({"exemplars": len(exemplars), "banked": nb, "failed": nf}))


if __name__ == "__main__":
    main()

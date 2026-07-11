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
import canon_sig_reconcile as CSR      # v3.2 (Phase-25 T7-M2 per-sibling re-reconcile, Q5-proven)

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


def reconcile_remap(addr, source, ov, src_rel, rawdir):
    """The Q5-proven M2 member draft: symbol-remap the RAW exemplar draft (source->ov), then
    RE-RECONCILE against THIS sibling's TU (canon_sig_reconcile v3.2 — the block-scope-vs-ambient
    decisions depend on the sibling's own decompile state, so a single ov077-reconciled body can't
    just be remapped). Returns text or None."""
    fn = f"func_{addr:08X}"
    raw = os.path.join(REPO, rawdir, fn + ".c")
    if not os.path.exists(raw):
        return None
    m, err = FR.symbol_map(addr, source, ov)
    if err:
        return None
    text = open(raw).read()
    for s, d in m.items():
        text = re.sub(rf"\b{s}\b", d, text)
    CSR._AMBIENT_CACHE.pop(src_rel, None)               # sibling TU is static during phase-1 staging,
    for k in [k for k in CSR._VISIBLE_CACHE if k[0] == src_rel]:  # but each fn needs its own visibility
        CSR._VISIBLE_CACHE.pop(k, None)
    try:
        return CSR.reconcile(fn, text, None, src_rel)
    except Exception:
        return None


def edit_remap_sweep(a, sig, src_sig, stubs):
    """§42e --edit-remap: recover byte-drift families whose crack carries OUT-OF-BODY edits (a file-scope
    //@EDIT the remapped body doesn't contain, and/or a once-global engine_core.h flip). Per family in the
    JSON manifest: apply ec_edits ONCE to engine_core.h (byte-neutral); then per same-address h_norm sibling,
    symbol-remap the split //@EDIT directives (family_remap.symbol_map) + apply to the sibling split, stage
    the family_remap body, and gate each (overlay,split) group via plain harvest_verify (the sole arbiter —
    a body that byte-drifts or cc1-crashes fails+reverts; its already-applied edit is byte-neutral, R22-checked)."""
    manifest = json.load(open(os.path.join(REPO, a.edit_remap)))
    src = a.source

    # 1. once-global engine_core.h edits (byte-neutral; e.g. the func_80156044 return-type flip)
    ecp = os.path.join(REPO, "src/shared/engine_core.h")
    ec = open(ecp).read()
    nec = 0
    for fam in manifest["families"]:
        for e in fam.get("ec_edits", []):
            if e["old"] in ec:
                ec = ec.replace(e["old"], e["new"]); nec += 1
    if nec:
        open(ecp, "w").write(ec)
        print(f"[edit-remap] applied {nec} engine_core.h global edit(s)")

    # 2. stage per (overlay,split): symbol-remapped split-edits + the remapped body
    shutil.rmtree(os.path.join(REPO, SWEEP), ignore_errors=True)
    splits = {}                                          # src_rel -> mutated split text (accumulates edits)
    groups = collections.defaultdict(list)               # (ov, src_rel, subdir) -> [fn]
    skipped = collections.Counter()
    for fam in manifest["families"]:
        addr = int(fam["addr"], 16)
        hn = src_sig[addr][2]
        sibs = [ov for ov in sig if ov != src and addr in sig[ov]
                and sig[ov][addr][2] == hn and addr in stubs[ov]]
        for ov in sibs:
            src_rel, subdir = stubs[ov][addr]
            m, err = FR.symbol_map(addr, src, ov)
            if err:
                skipped["symmap"] += 1; continue
            body, berr = FR.remap(addr, src, ov)
            if body is None:
                skipped["remap"] += 1; continue
            txt = splits.get(src_rel)
            if txt is None:
                txt = open(os.path.join(REPO, src_rel)).read()
            for e in fam.get("edits", []):
                old, new = e["old"], e["new"]
                for k, v in m.items():                   # exemplar symbol names -> this sibling's
                    old = old.replace(k, v); new = new.replace(k, v)
                if old in txt:
                    txt = txt.replace(old, new)          # apply. Absence is FINE (already-applied, or the
                else:                                    # edit is exemplar-specific, e.g. a canon-sig-layer
                    skipped["edit-absent"] += 1          # decl a sibling lacks) — NEVER skip the sibling;
                                                         # the whole-binary byte-gate is the sole arbiter (G3/P9).
            splits[src_rel] = txt
            d = os.path.join(REPO, SWEEP, ov)
            os.makedirs(d, exist_ok=True)
            open(os.path.join(d, f"func_{addr:08X}.c"), "w").write(body + "\n")
            groups[(ov, src_rel, subdir)].append(f"func_{addr:08X}")
    for src_rel, txt in splits.items():                  # persist the edited splits for the build
        open(os.path.join(REPO, src_rel), "w").write(txt)
    print(f"[edit-remap] staged {sum(len(v) for v in groups.values())} member drafts across {len(groups)} "
          f"(overlay,split) groups; skipped {dict(skipped)}")

    # 3. gate each group via plain harvest_verify (bodies; the edits are already in the split)
    banked = collections.Counter()
    failed = collections.Counter()
    for (ov, src_rel, subdir), fns in sorted(groups.items()):
        good_sha = open(os.path.join(REPO, f"config/check.{ov}.sha")).read().split()[0]
        sh([PY, "tools/harvest_verify.py", "--binary", ov, "--src", src_rel, "--asm-subdir", subdir,
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
    print(f"\n[edit-remap] BANKED {nb} member-matches / {nf} failed across {len(banked)} overlays")
    if a.commit and nb:
        sh(["git", "add", "-A", "src"])
        sh(["git", "commit", "-q", "-m",
            f"feat(phase-25): T7 --edit-remap sweep — {nb} member-matches (out-of-body //@EDIT families)"])
        print("[edit-remap] committed.")
    print(json.dumps({"banked": nb, "failed": nf, "skipped": dict(skipped)}))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--source", default="ov_SC01_077")
    ap.add_argument("--limit", type=int, default=0, help="cap #exemplars (0 = all)")
    ap.add_argument("--min-sibs", type=int, default=1)
    ap.add_argument("--chunk", type=int, default=8)
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--only", default=None, help="comma-separated exemplar addrs to sweep (validation)")
    ap.add_argument("--reconcile", default=None, metavar="RAWDIR",
                    help="M2 def-side-wall path: per (exemplar,sibling), symbol-remap the RAW draft in RAWDIR "
                         "then canon_sig_reconcile against the sibling TU (Q5-proven). Implies --no-preclassify.")
    ap.add_argument("--edit-remap", default=None, metavar="MANIFEST",
                    help="§42e out-of-body-edit path: JSON manifest of families with `edits` (split-scope "
                         "//@EDIT old||new in EXEMPLAR symbols, symbol-remapped per sibling) + optional "
                         "`ec_edits` (once-global engine_core.h, byte-neutral). Per sibling: apply the remapped "
                         "edits to the split + stage the family_remap body, gate via harvest_verify (the sole "
                         "arbiter, G3/P9 — pin-heavy families that cc1-crash fail+revert).")
    ap.add_argument("--no-preclassify", action="store_true",
                    help="skip the match_one isolation pre-classify (it can't see src/shared/engine_types.h, "
                         "so it false-negatives type-lifted families); route every remappable exemplar straight "
                         "to the harvest_verify byte-gate (the real TU sees the shared types). Use after a "
                         "build_engine_types type-lift for the decl-reconcile pass.")
    a = ap.parse_args()
    os.chdir(REPO)

    sig = load_sigs()
    src_sig = sig[a.source]
    src_stubs = stub_map(a.source)
    stubs = {ov: stub_map(ov) for ov in sig}

    if a.edit_remap:
        return edit_remap_sweep(a, sig, src_sig, stubs)

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
        if a.reconcile:                                         # M2: gate is the sole arbiter, no pre-classify
            simple.append((addr, nins, sibs)); continue
        draft, _ = FR.remap(addr, a.source, sibs[0])
        if draft is None:
            deferred.append((addr, "remap-fail")); continue
        if a.no_preclassify:                                    # trust the real-TU byte-gate (type-lift pass)
            simple.append((addr, nins, sibs)); continue
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
            src_rel, subdir = stubs[ov][addr]
            if a.reconcile:
                draft = reconcile_remap(addr, a.source, ov, src_rel, a.reconcile)
            else:
                draft, _ = FR.remap(addr, a.source, ov)
            if draft is None:
                remap_fail += 1
                continue
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

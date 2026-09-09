#!/usr/bin/env python3
"""Phase-28 T7: the BINARY-CITIZENSHIP gate (R36 enforcement, via R32 coverage assertions).

R36 — a newly-discovered binary is not real until every consumer knows it. Onboarding a
code-bearing payload produces a byte-CLEAN binary (it builds; `check-all` is green) that is not yet
a CITIZEN: the tools that enumerate binaries can each be silently unaware of it, and the whole-binary
byte-gate is structurally blind to that (R34 — it verifies the binaries it is TOLD about).

This is not hypothetical. Phase 27 onboarded 4 SC07 overlays byte-clean; Phase 28 then found FOUR
separate consumers silently ignoring them, hiding ~6,400 already-matched function bodies:
  * family_remap.img_path        — hardcoded 0.4.dec -> None -> every member classified "LEN" (T0)
  * .run/family_hseq.json        — 134 overlays, never regenerated after onboarding (T0)
  * config/dedup.us.yaml         — ZERO group memberships; 1,689 groups read "134 binaries" (T4)
  * src/<ov>/<ov>.c              — no `../shared/engine_core.h` include, so no shared body reaches it (T4)
Every failure was SILENT. This gate makes each a loud, asserted invariant (R32): the next onboarding
either wires the binary into every consumer or fails here, before matching work is built on top of a
binary half the tools cannot see.

GROUND TRUTH = the config the BUILD reads (R33): the onboarded set is `main` + `resident` + every
`config/splat.ov_*.yaml`. Nothing here is hand-listed; drift from that set is the primary defect.

  make audit-binaries        (fail-closed; wired into tools-health)
  tools/audit_binaries.py [--verbose]
"""
import glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dup_report
import corpus

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SHARED_INCLUDES = ("shared/engine_core.h", "shared/engine_prelude.h")   # the macro-era header, then the Phase-35 prelude


def onboarded():
    """The authoritative onboarded set, DERIVED from the splat configs the build consumes (R33).

    P30 S44: was `splat.ov_*.yaml` + a hand-set {main, resident} — i.e. the R36 citizenship gate was
    itself structurally blind to any binary class it did not know about (the exact defect class it
    exists to catch). Now: EVERY `config/splat.<alias>.yaml` is an onboarded binary, whatever its
    class ("main" is `splat.us.exe.yaml` — normalize it)."""
    out = set()
    for p in glob.glob(os.path.join(REPO, "config/splat.*.yaml")):
        alias = os.path.basename(p)[len("splat."):-len(".yaml")]
        if alias in ("us.exe", "us.overlay.template", "us.module.template"):
            continue
        out.add(alias)
    return {"main"} | out


def dedup_membership():
    """{binary: n_groups} from config/dedup.us.yaml — INFO, not a hard check (0 is legitimate for a
    freshly-onboarded overlay no one has propagated into yet). Read as text so this never rewrites
    the registry (the H5 lesson from T4: never round-trip that file through a YAML dumper)."""
    counts = {}
    txt = open(os.path.join(REPO, "config/dedup.us.yaml")).read()
    for b in onboarded():
        counts[b] = len(re.findall(rf"\b{re.escape(b)}\b", txt))
    return counts


def main():
    verbose = "--verbose" in sys.argv
    os.chdir(REPO)
    onb = onboarded()
    fails = []
    warns = []

    # --- CHECK 1: the enumeration all derived tools read (dup_report.BINARIES) EXACTLY equals the
    # onboarded config set. Both directions (R32): a binary in config but not here is invisible to
    # corpus/family_hseq/progress; a binary here but not in config is a phantom the reports invent.
    binaries = set(dup_report.BINARIES)
    missing = onb - binaries
    phantom = binaries - onb
    if missing:
        fails.append(f"dup_report.BINARIES is MISSING {len(missing)} onboarded binary(ies) — "
                     f"invisible to every derived tool (corpus/family_hseq/progress): {sorted(missing)}")
    if phantom:
        fails.append(f"dup_report.BINARIES has {len(phantom)} PHANTOM binary(ies) not onboarded "
                     f"in config: {sorted(phantom)}")

    # --- CHECK 2: every onboarded binary has a sig (the byte-derived fingerprint the whole matching
    # frontier is measured against). No sig -> the binary contributes to no report and no family.
    for b in sorted(onb):
        cfg = dup_report.BINARIES.get(b)
        if not cfg:
            continue                                   # already flagged by CHECK 1
        if not os.path.exists(os.path.join(REPO, cfg["sig"])):
            fails.append(f"{b}: no sig at {cfg['sig']} (run `make sig-overlays` / `make sig-resident` / `make sig-modules`)")

    # --- CHECK 3 (the load-bearing SC07 check): every onboarded OVERLAY's .c includes the shared
    # engine-core header. Without it NO shared body can be instantiated in that overlay, so it can
    # never receive the ~1,600 already-matched engine functions its siblings carry — the exact bug
    # that left the 4 SC07 overlays at ~80 matched / ~2,400 stubs. (main + resident have their own
    # bodies and legitimately do not include it.)
    for b in sorted(onb):
        if not b.startswith("ov_"):
            continue
        # Phase 35 T2: the binary's source dir comes from the Makefile oracle (a twin's is its primary's), never src/<b>.
        d = corpus.src_dir(b)
        c = os.path.join(REPO, d, os.path.basename(d.rstrip("/")) + ".c")
        if not os.path.exists(c):
            fails.append(f"{b}: no src file at {os.path.relpath(c, REPO)}")
            continue
        text = open(c).read()
        if not any(inc in text for inc in SHARED_INCLUDES):
            fails.append(f"{b}: {os.path.relpath(c, REPO)} includes neither ../{SHARED_INCLUDES[0]} nor ../{SHARED_INCLUDES[1]} — "
                         f"shared engine bodies cannot reach it (the SC07 propagation-blindness)")

    # --- CHECK 3b (Phase 35 T3): a TWIN binary is a full citizen only if it builds from its primary's source (R36).
    for b in sorted(onb):
        prim = corpus.twin_of(b)
        if prim is None:
            continue
        if prim not in onb:
            fails.append(f"{b}: TWIN_OF {prim}, which is not onboarded"); continue
        if corpus.twin_of(prim) is not None:
            fails.append(f"{b}: TWIN_OF {prim}, which is itself a twin (chains are forbidden)")
        if corpus.src_dir(b) != corpus.src_dir(prim):
            fails.append(f"{b}: TWIN_OF {prim} but src dirs differ ({corpus.src_dir(b)} vs {corpus.src_dir(prim)})")
        if os.path.isdir(os.path.join(REPO, "src", b)):
            fails.append(f"{b}: is a twin of {prim} yet src/{b}/ still exists — one source per payload")
        try:
            sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
            import share_census
            con = share_census.contracts()
            sha_b = open(os.path.join(REPO, con[b])).read().split()[0]
            sha_p = open(os.path.join(REPO, con[prim])).read().split()[0]
            if sha_b != sha_p:
                fails.append(f"{b}: TWIN_OF {prim} but the contracts differ ({sha_b[:12]} vs {sha_p[:12]}) — not one payload")
        except Exception as e:  # noqa: BLE001 — a missing contract is itself the failure
            fails.append(f"{b}: twin contract check could not run: {e}")
        yb, yp = os.path.join(REPO, f"config/splat.{b}.yaml"), os.path.join(REPO, f"config/splat.{prim}.yaml")
        if os.path.exists(yb) and os.path.exists(yp):
            segs = lambda p, a: sorted(re.findall(r"^\s*-\s*\[(0x[0-9A-Fa-f]+),\s*(c|\.rodata|data|bin|asm),\s*([^\]]+)\]",
                                                  open(p).read().replace(a, "ALIAS"), re.M))
            if segs(yb, b) != segs(yp, prim):
                fails.append(f"{b}: TWIN_OF {prim} but the carves differ (config/splat.{b}.yaml vs {prim}'s) — align the twin's carve")

    # --- CHECK 4: every onboarded overlay is represented in the family map (the templating frontier).
    # A missing overlay there means every member it holds is invisible to the family engine.
    fam_path = os.path.join(REPO, ".run/family_hseq.json")
    if os.path.exists(fam_path):
        fam = json.load(open(fam_path))
        if "binaries" in fam:
            # P33 A4: the map records the binaries it SCANNED (its own denominator, R41). Inferring
            # coverage from family members is only valid while families exist — at 100% the family
            # list is empty and that inference reported every binary missing from a complete map.
            fam_ovs = set(fam["binaries"])
        else:
            fam_ovs = set()
            for g in fam.get("families", []):
                for o, _ in g.get("members", []) + g.get("matched_members", []):
                    fam_ovs.add(o)
            warns.append(".run/family_hseq.json predates the coverage field (P33 A4) — coverage inferred "
                         "from family members; regenerate: tools/family_hseq.py")
        # S44: modules (md_*) carry shareable engine functions too; only main is exempt
        # (structurally barren, checked twice — S39). Resident + overlays + modules must appear.
        map_missing = {b for b in onb if b != "main"} - fam_ovs
        # An overlay can be legitimately absent only if it shares NO function with any other (never,
        # in practice — every overlay shares the engine core). Flag, do not hard-fail, since the map
        # is regenerable and may legitimately post-date a brand-new onboarding.
        if map_missing:
            warns.append(f".run/family_hseq.json is missing {len(map_missing)} onboarded overlay(s) "
                         f"(regenerate: tools/family_hseq.py): {sorted(map_missing)}")
    else:
        warns.append(".run/family_hseq.json absent — cannot check family-map coverage")

    # --- INFO: dedup-group membership. 0 is legitimate for a freshly-onboarded overlay, but an
    # onboarded overlay WITH the shared include yet 0 groups is a not-yet-harvested one worth naming.
    memb = dedup_membership()
    zero = sorted(b for b in onb if b.startswith("ov_") and memb.get(b, 0) == 0)
    if zero:
        warns.append(f"{len(zero)} overlay(s) in 0 dedup groups (onboarded but un-harvested — "
                     f"candidate for tools/share_body.py --plan): {zero if verbose else zero[:6]}")

    # --- report
    n_ov = len([b for b in onb if b.startswith("ov_")])
    n_md = len([b for b in onb if b.startswith("md_")])
    print(f"audit-binaries: {len(onb)} onboarded (main + resident + {n_ov} overlays"
          + (f" + {n_md} modules" if n_md else "") + ")")
    if verbose:
        print(f"  dup_report.BINARIES: {len(binaries)}  |  family-map overlays: "
              f"{len(fam_ovs) if os.path.exists(fam_path) else 'n/a'}")
    for w in warns:
        print(f"  [warn] {w}")
    for f in fails:
        print(f"  [FAIL] {f}")
    if fails:
        sys.exit(f"\naudit-binaries: {len(fails)} citizenship FAILURE(s) — a binary the tools cannot "
                 f"fully see is invisible work (R36/R34). Fix before matching on top of it.")
    print("audit-binaries: OK — every onboarded binary is a full citizen of every enumerating consumer.")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Phase-28 T4: EXTEND the existing dedup registry to newly-onboarded binaries.

THE GAP THIS FILLS (byte-measured, P28 T3-A). `tools/new_overlay.sh` produces a byte-clean binary
that is NOT a citizen of the shared-body ecosystem: its `.c` includes only `common.h` (never
`../shared/engine_core.h`), so not one shared engine body can reach it, and it appears in ZERO of
`config/dedup.us.yaml`'s groups. The 4 SC07 overlays the Phase-27 disc audit onboarded therefore sat
at ~80 matched / ~2,400 stubs while their siblings were ~2,150 matched — and 1,689 registry groups
still read "134 binaries", never 138.

WHY THE EXISTING TOOL CANNOT DO IT. `dedup_propagate` is built for CRACK -> AUTHOR MACRO ->
INSTANTIATE: `--auto-from` scans a source overlay's INLINE DEFS (it planned only 11 fns here,
skipping the ~1,600 whose bodies are ALREADY `DEFINE_func_*` macros in engine_core.h), and `--addr`
dies with "no source overlay has it matched" because no overlay holds an inline def — every one of
the 134 uses the macro. Extending an existing MACRO-BACKED group to a new binary is a different
operation, and nothing implemented it.

WHY IT IS SAFE (the correctness argument — this is a byte-gate feeder, so it must be explicit).
`h_exact` is the SHA1 of RAW INSTRUCTION BYTES (tools/sig_image.py). Two instances sharing an
h_exact are therefore identical *including* their `jal`/`lui`/`%lo` reloc immediates — same callee
addresses, same data addresses, same symbols. So the body that compiles byte-identically at one
member compiles byte-identically at the other, with no remap at all. (This is exactly why
dup_report calls h_exact "guaranteed byte-match" and h_norm "candidate-only".) The whole-binary
byte-gate remains the sole arbiter (G3/P9): a wrong instantiation changes the bytes and fails SHA1.
A bug here can make this tool FAIL TO BANK; it cannot make it falsely bank.

REUSE, DON'T REBUILD (R33). This owns only the SET COMPUTATION and the REGISTRY EDIT. The splice and
the gate are `tools/harvest_verify.py` verbatim — which already derives each stub's home TU from the
corpus oracle, chunks + bisects, and reverts on failure. h_exact members are byte-identical by
construction, so the happy path is ONE build per binary (not one per function).

  tools/dedup_extend.py --binaries ov_SC07_006,ov_SC07_007,ov_SC07_010,ov_SC07_011 [--check-only]
                        [--chunk N] [--limit N]
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys

import yaml

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus
import family_hseq          # has_mid_jr — the ONE jr oracle (R33)
import family_remap as FR   # stream_words/nins_of

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = sys.executable
REGISTRY = "config/dedup.us.yaml"
SHARED_INCLUDE = '#include "../shared/engine_core.h"'
EXTEND_DIR = ".run/extend"


def sig_hashes(binary):
    """{vram_int: h_exact} from the binary's sig — the ORIGINAL bytes, independent of splat."""
    out = {}
    p = os.path.join(REPO, f".run/sig.{binary}.jsonl")
    for line in open(p):
        d = json.loads(line)
        out[int(d["addr"], 16)] = d["h_exact"]
    return out


def load_groups():
    doc = yaml.safe_load(open(os.path.join(REPO, REGISTRY)))
    groups = doc if isinstance(doc, list) else doc.get("groups", doc)
    if not isinstance(groups, list):
        sys.exit(f"dedup_extend: unexpected {REGISTRY} shape: {type(groups).__name__}")
    return doc, groups


def add_members_surgical(additions):
    """Append binaries to each group's `binaries: [...]` list by TEXT EDIT, in place.

    NEVER `yaml.safe_dump` this file. The first cut of this tool round-tripped it through
    safe_dump and silently destroyed BOTH of the things a human needs from it (H5 — "never
    silently drop comments on a rewrite"):
      * all 47 comment lines — including the curated Phase-11 header explaining WHY the share is
        source-level (the linker cannot excise bytes interior to an object) — dumped to nothing;
      * every `vram: 0x80162FF4` re-serialized as `vram: 2148937716` (PyYAML parses YAML-1.1 hex
        to int, and dumps int as decimal), making 1,832 entries unreadable.
    It was invisible to every gate: dedup-check passed 1840/0 and check-all stayed 140/140,
    because `_addr()` accepts both forms — the data was fine and the DOCUMENT was ruined. A
    formatting-destructive write that all your oracles call green is exactly the class this
    project keeps re-learning: the gate measures bytes, not intent.

    `additions` = {group_id: [binary, ...]}. Idempotent: a binary already listed is skipped.
    """
    p = os.path.join(REPO, REGISTRY)
    lines = open(p).read().splitlines(keepends=True)
    cur, n = None, 0
    seen = set()
    for i, ln in enumerate(lines):
        m = re.match(r"^\s*-?\s*id:\s*(\S+)\s*$", ln)
        if m:
            cur = m.group(1)
            continue
        if cur and cur in additions and re.match(r"^\s*members:\s*$", ln):
            # a VERBOSE group has no `binaries:` line — silently skipping it left five 141-member groups listed at 16 (P35 S94/S96)
            raise SystemExit(f"add_members_surgical: {cur} is in the verbose `members:` form — convert it to shorthand first "
                             f"(share_body.py --repair-registry does), never skip it (R43)")
        if cur and cur in additions and re.match(r"^\s*binaries:\s*\[", ln):
            seen.add(cur)
            add = [b for b in additions[cur] if re.search(rf"\b{re.escape(b)}\b", ln) is None]
            if add:
                lines[i] = ln.rstrip("\n").rstrip()[:-1].rstrip() + ", " + ", ".join(add) + "]\n"
                n += len(add)
            cur = None
    open(p, "w").write("".join(lines))
    return n


def _addr(v):
    return int(v, 16) if isinstance(v, str) else int(v)


def plan_for(binary, groups):
    """[(group, vram, macro)] for every h_exact group this binary could join, plus the skip tally.

    A group is extendable into `binary` iff: it is h_exact tier, the binary is not already a member,
    the binary has a LIVE STUB at the group's vram, that stub's original bytes hash to the group's
    recorded h_exact (the C1 equivalence the registry itself asserts), and it is NOT a jr/switch
    function (see below).

    THE jr GUARD (cookbook §53). A function with a mid-body `jr` on a non-$ra register dispatches
    through a compiler-generated jump table the LINKER must place at the sibling's exact address — a
    per-sibling `jtbl_carve` + interleave (`jtbl_family_bank.py`). This tool has no carve step and a
    newly-onboarded overlay has no `_jr_*` split at all, so a jr body instantiated here would leave
    its table unplaced and the gate would (correctly) reject it. The guard is PREVENTIVE: it skips
    and REPORTS rather than feeding the gate drafts that cannot pass (R32 — a skip is only honest if
    it is counted and named). On the SC07 set it currently skips ZERO: no jr function is in the
    extendable set.

    ⚠️ R14 — WHAT THIS GUARD IS *NOT*. It does NOT explain the 12 DIFFs the first run produced
    (`func_80162FF4/801630C4/80163194/8016325C`, the same 4 in every overlay, 12 of 6457 = 0.19%).
    I first assumed those were the jr class because ov_SC01_077 hosts them in `_jr_8017A4AC.c` /
    `_jr_80182268.c` — a natural read, and WRONG: `has_mid_jr` is **False** for all four (33-52 ins,
    no jump table). They merely LIVE in a carved jr-REGION split (the carve region for
    `func_8017A4AC` sweeps in every function in its address range), which says nothing about them.
    Their DIFF cause is UNDIAGNOSED and logged for follow-up; they are correctly left as stubs by the
    gate. Hosting file != function class — do not infer one from the other.

    Detector reused verbatim from `family_hseq.has_mid_jr` (R33 — one oracle, not two).
    """
    sig = sig_hashes(binary)
    stubs = corpus.stubs(binary)
    out, skips = [], {}
    for g in groups:
        if g.get("tier") != "h_exact":
            continue
        if "vram" not in g or "binaries" not in g:
            skips["verbose-form"] = skips.get("verbose-form", 0) + 1
            continue                                   # not position-locked
        if binary in g["binaries"]:
            continue
        vram = _addr(g["vram"])
        if vram not in stubs:
            continue                                   # not a live stub here (matched already, or absent)
        if sig.get(vram) != g["hash"]:
            continue                                   # DIFFERENT CODE at the same vram — the point of the check
        words = FR.stream_words(binary, vram, FR.nins_of(binary, vram))
        if words and family_hseq.has_mid_jr(words):
            skips["jr-needs-carve"] = skips.get("jr-needs-carve", 0) + 1
            continue                                   # §53: route via jtbl_family_bank, not here
        out.append((g, vram, g["func"]))
    return out, skips


def ensure_include(binary, apply=True):
    """Add the shared-header include if absent. Byte-neutral: engine_core.h is only `#define`s, so
    including it without instantiating emits no code (proven: ov_SC07_006 built 7ca772be with the
    include + one macro). Returns True if the file was changed."""
    p = os.path.join(REPO, f"src/{binary}/{binary}.c")
    t = open(p).read()
    if SHARED_INCLUDE in t:
        return False
    if apply:
        t = t.replace('#include "common.h"', '#include "common.h"\n' + SHARED_INCLUDE, 1)
        open(p, "w").write(t)
    return True


def write_drafts(binary, plan):
    d = os.path.join(REPO, EXTEND_DIR, binary)
    subprocess.run(["rm", "-rf", d], check=False)
    os.makedirs(d, exist_ok=True)
    for g, vram, macro in plan:
        fn = f"func_{vram:08X}"
        body = f"{macro}()  /* dedup: shared engine-core @0x{vram:08x} (src/shared) */\n"
        open(os.path.join(d, fn + ".c"), "w").write(body)
    return d


def gate(binary, drafts_dir, chunk, ladder=True):
    """The whole-binary byte-gate is the sole arbiter (G3/P9). Returns the banked fn set.

    LADDER (S46): this called `harvest_verify` VERBATIM, which is the bare gate with no recovery.
    Measured cost of that: 0 of 142 extendable groups banked, and the classified reasons were 118
    PLUMBING / 21 CC1-FAIL / 3 DIFF — i.e. ~1 in 50 was a real byte divergence and everything else
    was a declaration conflict in the TARGET TU (`conflicting types for memcpy / ApplyMatrixSV /
    D_800AE620 / func_8014C568`). `gate_stage` wraps the same gate in exactly the reconcile ladder
    those need (canon_resident_calls -> cast_call_sites -> sig_unify -> harvest_verify), and it
    carries the §156 reconcile LEDGER so a failed candidate cannot leave a fleet-shared edit behind.
    Measured on the same failure class in the S46 wave residue: 6 of 19 PLUMBING recovered (~32%).

    GATE_NO_ARITY=1 is set for the child: gate_stage's arity pre-pass writes the fleet-shared
    engine_core.h BEFORE the gate, and on a failing draft that edit can survive — the F1 defect that
    broke 141 of 213 binaries in S45 and made every later gate report `near`. The ladder's other
    rungs are draft-local and safe.
    """
    good = open(os.path.join(REPO, f"config/check.{binary}.sha")).read().split()[0]
    vout = f".run/extend_verified.{binary}.txt"
    fout = f".run/extend_failed.{binary}.txt"
    if ladder:
        cmd = [PY, "tools/gate_stage.py", "--binary", binary,
               "--drafts", os.path.relpath(drafts_dir, REPO), "--no-propagate",
               "--verified-out", vout, "--failed-out", fout]
    else:
        cmd = [PY, "tools/harvest_verify.py", "--binary", binary,
               "--out", f"build/{binary}/{binary}", "--good-sha", good,
               "--drafts", os.path.relpath(drafts_dir, REPO), "--chunk", str(chunk),
               "--verified-out", vout, "--failed-out", fout]
    env = dict(os.environ, GATE_NO_ARITY="1")
    subprocess.run(cmd, cwd=REPO, timeout=7200, env=env)
    p = os.path.join(REPO, vout)
    return set(open(p).read().split()) if os.path.exists(p) else set()


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binaries", required=True, help="comma list of newly-onboarded binaries to wire in")
    ap.add_argument("--chunk", type=int, default=512,
                    help="drafts per build (h_exact is byte-identical by construction, so the happy "
                         "path is ONE build; harvest_verify bisects on failure). default 512")
    ap.add_argument("--limit", type=int, default=0, help="cap #groups per binary (0 = all)")
    ap.add_argument("--check-only", action="store_true", help="print the plan, touch nothing")
    a = ap.parse_args()
    os.chdir(REPO)

    doc, groups = load_groups()
    targets = [b.strip() for b in a.binaries.split(",") if b.strip()]

    dirty = subprocess.run("git status --porcelain -- config/ src/", shell=True,
                           capture_output=True, text=True).stdout.strip()
    if dirty and not a.check_only:
        sys.exit("dedup_extend: config/ or src/ is dirty — commit first so a failed gate reverts "
                 "cleanly.\n" + dirty[:400])

    total_banked, total_planned = 0, 0
    for b in targets:
        plan, skips = plan_for(b, groups)
        if a.limit:
            plan = plan[:a.limit]
        total_planned += len(plan)
        print(f"[{b}] {len(plan)} extendable h_exact group(s); "
              f"include {'ABSENT -> add' if ensure_include(b, apply=False) else 'present'}"
              + (f"; skipped {skips}" if skips else ""))
        if a.check_only or not plan:
            continue

        added_include = ensure_include(b)              # True IFF this run inserted the line
        d = write_drafts(b, plan)
        banked = gate(b, d, a.chunk)
        print(f"[{b}] BANKED {len(banked)} / {len(plan)}")
        total_banked += len(banked)

        if not banked:
            # ONLY undo what THIS run did (§61/§63). The revert is an INVERSE TRANSFORM, not a
            # snapshot restore, so firing it on a binary that ALREADY had the include strips a
            # load-bearing line: every `DEFINE_func_*()` in that overlay stops resolving. It was
            # unconditional until Phase 29 SESSION-19, where a 0-banked run over 135 already-wired
            # binaries removed the include from all 135 at once. Invisible to every byte-gate (R34)
            # because the damage lands AFTER the last gate has run.
            if added_include:
                ensure_include_revert(b)
            continue
        adds = {g["id"]: [b] for g, vram, _ in plan   # registry: only what the GATE accepted (P9)
                if f"func_{vram:08X}" in banked}
        n = add_members_surgical(adds)                 # TEXT edit — never safe_dump (see the docstring)
        print(f"[{b}] registry: +{n} membership(s)")
    print(f"\n=== dedup_extend: banked {total_banked} / {total_planned} planned "
          f"across {len(targets)} binaries ===")
    if a.check_only:
        print("(--check-only: no files touched)")


def ensure_include_revert(binary):
    p = os.path.join(REPO, f"src/{binary}/{binary}.c")
    t = open(p).read().replace('#include "common.h"\n' + SHARED_INCLUDE, '#include "common.h"', 1)
    open(p, "w").write(t)


if __name__ == "__main__":
    main()

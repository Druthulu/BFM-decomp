# CURRENT PHASE — Phase 30: The Recovery & Concentration Campaign (overlays to their ceiling)

**Opened:** 2026-07-30 · **Effort:** Max (Fable 5; saved defaults) · **Generation:** Gen2 (22nd phase of the arc) ·
**Baseline:** PhaseEnd_Phase29 (v1.28.0) · **Roadmap:** `docs/roadmap-to-100.md` **v2** §3 P30
**Plan approved (P3 gate 1):** 2026-07-30, in-session (Drew's explicit waiver of the fresh-session step at 28% context).
Full plan mirror: `~/.claude/plans/continue-dazzling-newt.md` (out-of-repo; this file is the in-repo authority + crash-recovery log).

**Fleet at open:** 87.5% instr-weighted / 78.0% distinct-code / 92.00% fn-count · 140/140
byte-identical · 0 NON_MATCHING · dedup 1886/0 · tools-health RC=0.

**Drew's Phase-Start decisions (2026-07-30):**
- In-session start (fresh-session step waived at 28% context).
- The Ghidra-C prefetch batch pulled forward from P31 → **T0.5** (tail + main's 1,034 stubs; headless, background).
- T2's primary path = the **two-file atomic o0b substitution driver** (the log's costed no-splat route); Arm-A splat research is the fallback only.
- ROI floor for T3: two consecutive sessions each < +0.3pp instr with all lanes exercised (Drew-adjustable).

**⚠️ PRECONDITION (R6):** Drew makes the milestone-close commit + push (`PhaseEnd_Phase29.md` +
`phase-ends/logs/Phase29.md`, both in the tree) **before P30's first commit lands**. P30 work
proceeds; the first P30 commit waits on it.

---

## The numbers this phase must pin FIRST (T0 — do not consume until re-derived, R35/R14)
- family_hseq **29,961** vs progress.py **28,296** remaining instances — an unexplained R32 gap.
- The `-O0` population: "10 families / ~1,287 raw distinct" (checkpoints) vs "123 families /
  121,264 ins / 3,100 distinct" (the log's R14 correction) vs "129 distinct on the table" (the
  costed o0b route) — three numbers, one T0 job.
- The zero-crack family list (map said **61** on 07-29) and the concentration table (top-20/top-100 shares).

## Standing invariants (every task)
- Whole-binary byte-gate is the **sole arbiter** (G3/P9); match_one/closeness/masked = candidates (§52b).
- **R22 clean-fleet per banked batch:** `make clean && make extract-all && make check-all` → 140/140.
- `make tools-health` green + fail-closed before matching (corpus · cdecl · audit-binaries(R36) · report/lint/dedup).
- Blast-radius typing on every integration write (T0 draft-only / T1 binary-local / T2 fleet-shared ⇒ R22 mandatory).
- **Probe before costing** (R37-candidate discipline): probe one member before pricing a job; derive
  attribution from `corpus.stubs` before/after; diff the artifact to prove an edit ran (§120).
- Flywheel: idioms → cookbook + tooling in-session (R16/R30); pivots → decision-log (R31).
- Effort/model transitions **prompted, never assumed** (R26/R27) — STOP + WAIT for the toggle.
- One commit per task/sub-repair after this file's update; Drew pushes (R6/R20). R23 no-op on db.*.gbf churn.

---

## Task checklist (current-task pointer = ▶)

- [x] **T0 — Frontier regen + instrument repair [Max]** ✅ (all six letters; see per-task log; frontier
      report = `docs/frontier-p30.md`, report point #1):
      (a) `gate_stage.py` snapshot/restore (the ladder destroys good drafts) ·
      (b) `rtu_match.py` surface the real cc1 error in the verdict ·
      (c) reconcile the family_hseq↔progress instance gap (R32) ·
      (d) purge since-banked rows from the backlog ledger + still-a-stub filter from `corpus.stubs` (R33) ·
      (e) refresh `.run/autopsy/residuals.jsonl` + fix the 21-file absolute-include defect ·
      (f) regenerate the frontier (report / family_hseq / worklist / fuel manifest) + **pin the three
      contested populations** → the one-page frontier report (**report point #1**).
      Verify: tools-health green; digests committed; velocity derives from digest git history (R33).
- [ ] **T0.5 — Fleet Ghidra-C prefetch batch [background]** — `ImportOverlay.java` (~130 missing
      programs) + `DecompileFunctions.java` over every remaining distinct stub (overlay tail + main's
      1,034; skip LINKED) → `.run/ghidra_c/`. **R23 lock discipline** (stop the hook-launched MCP
      server first or route through it). Verify via `build_fuel_manifest.py` counters + 5 spot-reads.
- [ ] **T1 — Integration-recovery sweep [Ultracode — prompt at launch]** — all close=0 stranded
      drafts through `recover_integration.py` tiers + §65b de-macroize + the snapshot-safe ladder;
      the 10 named SESSION-16 blocked drafts. Prior: 39% recovery. **Report point #2.** R22 per batch.
- [ ] **T2 — The `-O0` cluster [Max, deep]** — PRIMARY: build the two-file atomic substitution
      driver (stage remapped body into `<ov>_o0b.c` AND drop the stub's INCLUDE_ASM from
      `<ov>_after.c` in one edit, gate) and sweep the T0-pinned families. FALLBACK: R17 research on
      the Arm-A splat `%lo +0x20`. Resistant residue → wall ledger with evidence. **Report point #3.**
- [ ] **T3 — The standing crack-wave loop [Ultracode waves; Max between]** — lanes interleaved,
      propagate behind every crack same-session:
      A zero-crack (~61, propagation-only) · B top-mass fresh families (no size cap; jr via
      `jtbl_family_bank`; `gate_stage` call-site-casts, never bulk header edits) · C tail mass on
      prefetched seeds (local v3 ≤15 → GLM/Haiku ≤~50 → cheap-Opus mid) · D PINS (19) + W4 bounded
      diagnoses + permuter backlog via the T4-fixed grinder.
      Per-session checkpoint + velocity + 3 metrics. **ROI floor: 2 consecutive sessions < +0.3pp
      instr each with all lanes exercised.**
- [ ] **T4 — Carried-tool resolution [xHigh]** — grinder warm-start + the 2 Phase-22 grinder bugs;
      verify `--fix-def-sig` is nowhere a default (§119).
- [ ] **T5 — Phase close [Max]** — burn-down from digest history; P7 milestone walk; Roadmap delta;
      gate 2; PhaseEnd_Phase30.

**Milestone:** overlays at their measured ceiling — **≥95% instr fleet, or every remaining overlay
stub on a named wall/behemoth/queue ledger** — 140/140 byte-identical throughout.

## Blockers
- (none) — precondition noted above (Drew's milestone-close commit before the first P30 commit).

## Per-task log

### T2 ▶ driver generalized; ×1 probe REFUTED the append route for the remaining cluster (2026-07-30)
`tools/rollout_o0.py` (generalizes T85's `rollout_801457a4_o0.py`): map-derived members
(cross-address-safe), stub located in any non-`_o0` split, jr+o0 composites routed out loudly,
atomic two-file + per-binary SHA gate + restore-both. **×1 probe (`0x8013b6a0`@ov_SC01_000):
gate-reject — and the diagnosis corrects the frontier report (R14 on my own doc):** T85's family
banked by APPEND because `0x801457A4` abuts the o0b object's END; the remaining 18 families
(`0x8013Bxxx–0x8013Cxxx`, below the whale) mis-place on append by construction, and per-fn
isolation IS the Arm-A re-carve. o0b-*bearing* ≠ o0b-*adjacent* — my "the wall never has to fall"
inference was wrong; caught at 1 build instead of 2,131. **T2's real substance = the Arm-A `+0x20`
defect.** First probe: identify WHICH symbol shifts on a failing overlay's re-carve; hypothesis:
splat re-GUESSES a data-symbol boundary the carve moves → pin it in config symbols and re-probe.

### T0.5 ▶ launched + probed (2026-07-30)
`tools/prefetch_fleet.py` (committed `commit:1220`): 126 programs / 7,966 uncached representatives.
**Probe 1 (main):** +1,525/2,002 cached in <1 min — the decompile leg is CHEAP; **477 main addrs
have no defined function in the program** (main's 06-14 auto-analysis gap) → follow-up: a
`DefineFunctions.java` completion pass over main from splat entries (the Phase-10 mechanism), then
re-run (resumable). **Probe 2 (import leg): FAILED then FIXED** — my missing-program matcher
checked "not exist"/"NOT_FOUND"; Ghidra's actual phrase is "Requested project program file(s)
**not found**" → the self-healing import never fired (+0/371, +0/315). One-line trigger broadening;
re-probe running. T1a (deterministic recovery sweep, 108 fns / 50 binaries, driver-committed banks,
no-propagate — reach≥2 winners ride T3 Lane A) launched concurrently; commit-scope interaction
VERIFIED safe (driver delegates to gate_stage's scoped `git add -u src/` — ghidra/ churn cannot
leak into bank commits).

### T0(e2)+(f) ✅ — autopsy refreshed; frontier regenerated + the three populations PINNED (2026-07-30)
- **Autopsy** (`collect -j12` + `report`): 1,349 rows — **1,178 near / 63 nobuild / 108
  match_one-MATCH** (T1's stranded-draft fuel, 3× the S16 sample), 0 classifier errors,
  second-oracle agree. `docs/autopsy.md` regenerated.
- **Worklist/manifest regen:** 101 live stubs / 261,789 gain-ins (stale 160/583k gone); R14 checks
  inside the manifest: 28/28 giants verified reach-138.
- **THE `-O0` PIN (headline):** 18 families / **2,192 open members — 2,131 o0b-route-eligible /
  61 SC07-no-o0b**; **15/18 exemplar-matched**. The "WALLED ~1,287" framing dissolves: the bulk
  never needs the Arm-A splat fix — T2 = generalize the proven `rollout_801457a4_o0.py` (130/130).
  Composites flagged: `0x8013c414`/`0x8013c0f8` are jr+o0 (carve inside the o0b TU — probe ×1 first).
- **Zero-crack roster:** 114 families / 3,166 open members / ~204k weighted ins (28 substantial);
  its head IS the -O0 set (T2 and Lane A open together).
- **Concentration:** top-20 = 24.0% / top-100 = 44.8% of open family weight (head consumed vs S13's
  53% — expected post-campaign flattening).
- **Report point #1: `docs/frontier-p30.md`** (all numbers same-tree at one HEAD, post-repair — R35).

### T0(e) — part 1 ✅: the 21-file absolute-include defect fixed (2026-07-30)
All 21 carriers were jr-carve split files including `engine_types.h` by absolute path
(`/home/musashi/bfm-decomp/...`, some twice); swapped to the house-relative
`#include "../shared/engine_types.h"`. `grep -rln /home/musashi src/ include/` → **0**.
**R22 clean-fleet from a genuinely clean tree: 140 passed, 0 failed of 140.** Part 2 (autopsy
refresh) next.

### T0(d) ✅ — backlog ledger: already clean; the scanner deleted (R33) (2026-07-30)
Findings, byte-verified: (1) the still-a-stub filter **already existed** (`load_best` drop +
`prune`, built 07-24) and the tracked jsonl was **already compacted** — the tree's pre-existing
uncommitted `.run/backlog.jsonl` edit was late-S25's un-committed prune output; `prune` today:
1350 → 1350, dropped 0. (2) The stale rows I'd flagged (`func_80151944` etc.) live in **worklist.md**
(regen at T0(f)), not backlog. (3) `_open_stubs` (private regex) vs `corpus.stubs` (the oracle):
**0 divergence across all 131 ledger binaries** — after fixing MY probe, which compared names
against int vram addrs (R35 pointed at my own instrument). Hardening: `_open_stubs` now **derives
from corpus.stubs** (STUB_RE deleted — R33's "best outcome is a deleted scanner"); hex-case
canonicalized on both sides of the membership test (a lower-hex record can't silently drop, R32);
count parity proven post-change (load_best 1350 == 1350). §83's doctrinal caveat (backlog ≠ work
queue; worklist is the queue) STANDS — that's classification quality, not staleness.

### T0(c) ✅ — family_hseq↔progress gap: ZERO definitional gap; stamped against recurrence (2026-07-30)
Same-tree regeneration of BOTH digests: family_hseq (overlays) **27,248 instances** == progress fleet
stubs 28,296 − main 1,034 − resident 14 = **27,248 — EXACT**. The carried "29,961 vs 28,296" was a
**cross-date, cross-scope misread**: the 07-29 map snapshot was SESSION-25's *open* state, and
29,961 − 27,248 = **2,713 = exactly the session's banked total**. The tools were never in
disagreement — both already derive from `corpus.stubs` (the Phase 26-A conversion, family_hseq:42).
Hardening: the family-hseq digest header now **stamps scope ("138 OVERLAYS only") + generation
HEAD + the shared-oracle note** ("compare digests only at the same HEAD") — a stale or
scope-mismatched comparison is now self-announcing. Roadmap v2 D-bucket corrected.
**Fresh frontier readings from the regen** (full pinning still at T0(f)): 478 substantial families /
678,404 templatable ins · **28 zero-crack** (was 61 on 07-29 — S25 consumed 33) · 3,626 PURE / 40
IMM / 6 STRUCT · overlays 27,248 instances / 17,629 distinct / 1,587,311 ins.

### T0(b) ✅ — rtu_match surfaces the real cc1 error in the verdict (2026-07-30)
`_diagnostics()` filter (the SESSION-25 recipe, in-tool): drop `warning:`/`In function`/`At top
level`/`###`/blank lines from the failing stage's stderr and print the FIRST 15 survivors — gcc-2.7.2
hard errors carry no `error:` prefix and the old `[-2000:]` tail was all warnings. Raw-tail fallback
if the filter empties (ICE/signal formats) — never prints less than before. Applied to all four
stages (CPP/CC1/MASPSX/AS). Verified on a real deliberate CC1 failure: the verdict now leads with
`t.c:3116: 'nonexistent_var' undeclared` instead of a 2 KB warning tail. `--stderr-out` unchanged
(full dump). Docstring updated.

### T0(a) ✅ — gate_stage stage-0 + fix_arity_callers journal undo (2026-07-30)
The carried defect pair closed structurally, not by root-causing:
- **`gate_stage.py`**: **stage 0 gates the RAW drafts before any transform** (`GATE_NO_STAGE0` to
  disable) — the destroyed-good-draft mode (SESSION-22 reproduction: `_o0` pair + `func_80138C60`,
  ladder-FAILED / bare-VERIFIED) is now impossible by construction; the canon/cast/rc ladder + arity
  pre-pass run only on stage-0 failures. Root-cause hypothesis recorded in-code (transforms are
  batch-`--src-file` TU-blind where the gate is per-draft TU-aware) — open, now harmless.
- **`fix_arity_callers.py`**: `--journal` (per-edit literal before/after) + `--undo-journal
  [--keep <banked>]` — the exact undo now lives in the WRITER, shared by ladder AND bare workflows
  (the 17-TU residue class). Replaces gate_stage's two-special-case file snapshot; undo moved to
  after stage 2 (closes the latent stage-2 parity gap: a stage-2 bank used to lose its arity edit
  before its own gate attempt). Stale-journal guard (`_arity_rc is not None`).
- **Verification:** negative control apply→undo → byte-identical tree; `--keep` retains exactly the
  kept edit; in-process flow test `.run/t0a_flowtest/driver.py` **7/7 PASS** (stage-0-first, s1in =
  failures-only, accumulation, undo-guard, src/ untouched). Real-tree at-scale proof lands with
  T1's first sweep (R22-bracketed there). Cookbook **§122**.

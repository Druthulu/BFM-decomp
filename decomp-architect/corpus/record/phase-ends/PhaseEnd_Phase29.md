# PhaseEnd — Phase 29: The Family Campaign (cores + members) — the biggest gain in project history, and the engine honestly spent
**Date:** 2026-07-30 · **Project Version:** 1.28.0 · **Phase Status:** Complete (milestone confirmed by Drew, gate 2) · **Generation:** Gen2 (21st phase of the arc)

> Gen2 phase 21 (8→…→28→**29**). Third phase off the roadmap (v1 §3 P29). Ran **25 sessions over 15 days** (2026-07-16 → 2026-07-30), **552 commits** (`2e84b53b2..8c7395027`) — the longest and highest-yield phase of the project. The granular per-task trail (every wave verdict, every probe, the session checkpoints v1–v9, the error ledgers) is preserved on-demand at **`phase-ends/logs/Phase29.md`** (R19 — NOT auto-loaded; ~805 KB, consult only when researching a mechanism). This file is the synthesis. Owner decisions (Drew): the 2026-07-16 charter (longer multi-session campaign, ROI-gated, Fable5 reserved for new wall classes); the SESSION-16 integration-recovery re-plan (probe-then-continue with kill gates); the 2026-07-30 close call + the roadmap-v2 re-baseline directive (plan-mode gate, Fable 5/Max); milestone confirmed 2026-07-30.

## Build Log

**The headline (all three metrics, the §1 contract):**
**instr-weighted 68.9% → 87.5% (+18.6pp)** · **distinct-code 49.5% → 78.0% (+28.5pp; 53,528 → 69,816 unique fns, +16,288)** · **fn-count 83.94% → 92.00% (+8.06pp)** · **140/140 byte-identical at every banked batch** (R22; 14× in SESSION-25 alone) · 0 NON_MATCHING linked throughout (G4) · dedup 1840 → 1886 groups · tools-health RC=0. The main EXE **entered the weighted denominators 2026-07-22** (the roadmap §1 metrics contract, implemented; pre/post deltas not perfectly comparable across that date).

**Files created/changed and complete — do not recreate** (durable output; the archived log has the exhaustive per-commit list):

*Source (the campaign):* thousands of banked members across `src/ov_*/*.c` + `src/shared/engine_core.h` (the DEFINE_ macro corpus) + `config/dedup.us.yaml` (1840 → 1886 groups). SESSION-25 alone banked **2,713 members (+100,572 ins, +1,620 unique fns)** across T79–T98. The §20 broad type-lift landed (154 types, SESSION-14, R22 140/140).

*New/extended tooling (committed; headline items):*
- **`tools/diff_regions.py`** (T1) — remap-exactly-as-staged + compile-at-exemplar-opt + masked region diff + per-member classification (`O0-FLAG`/`TEMPLATES`/`PLUMBING-ISO`/`REGALLOC`/`NO-TARGET`). The tool that resolved the roadmap's swing number.
- **`tools/lift_types.py`** (S13/S14) — the scoped §20 type-lift executor (clean-type lift → the broad 154-type lift).
- **`tools/recover_integration.py` extended into the tiered T0/T1 blast-radius recovery driver** (T16) + the §65b per-overlay de-macroize path — measured 14/36 = 39% recovery on the stranded-draft population.
- `family_sweep --hseq` hardening across the campaign (carry-macros, `--no-preclassify`, staging fixes), `gate_stage` reconcile ladder as the integration spine (call-site casts), `jtbl_family_bank` carve waves, `imm_map`/`--fix-def-sig` (§54/§119 — a REPAIR, not a default), permuter targeting fix (T13A).

*Docs / knowledge base (R16/R30/R31):*
- **`docs/matching-cookbook.md` §54–§121** — 68 new sections in one phase (the idiom bank's largest growth), incl. §61/§63 blast-radius, §65b de-macroize, §83 backlog-is-not-a-queue, §116 opt-level-is-a-property-of-the-FILE, §117 spell-the-symbol-from-the-sibling's-address, §118 ordinal immediates, §119 off-diagonal lever testing, §120 prove-your-patch-RAN, §121 synthesize-externs-for-macro-defined-callees.
- **`docs/roadmap-to-100.md` → v2** (the owed re-baseline, written at close under Drew's plan-mode gate): P30–P33 rechartered on 2026-07-30 measured reality; buckets W1–W5/M/R/T/B/D; `member_adapt` + the family-adapt fine-tune VACATED; v1 preserved in git history.
- `docs/decision-log.md` — ~15 new R31 entries (the swing resolution; the fresh-exemplar-sweep finding; the LIVE-siblings lever; the fix_header_decl→gate_stage doctrine correction; the §20 lift arc; the integration-bottleneck audit; psxport parked).
- `docs/calibration.md` — the swing number RESOLVED section + the stranded-draft recovery measurement.
- Digests regenerated throughout: `progress.fleet.md` (the per-session burn-down substrate), `family-hseq.md`, `worklist.md`, `backlog.md`.
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase29.md`** (R19). This file.

**Tools/packages installed:** None — the existing toolchain + venv throughout. Ultracode waves + cheap-Opus/Haiku-tier agents per the calibration doctrine; Fable 5 used for the close-out synthesis + roadmap v2 (its charter slot — new-wall-class discovery — was otherwise unused: no new wall class appeared that the idiom bank couldn't handle). No Ghidra DB change requiring commit (R23 — the `db.*.gbf` churn is restart-noise; the one MCP arc, ov_SC06_018 prefetch, was read-only).

**Verification results (literal) — the milestone proof:**
- `make clean && make extract-all && make check-all` → **140 passed, 0 failed of 140** byte-identical, reproduced at every banked batch across 25 sessions (14× in SESSION-25).
- `make tools-health` → **OK (exit 0)**: corpus(+resident) 0 PHANTOM + 0 TRUNCATED; audit-binaries 140/140 citizens (R36); audit-cdecl green; dedup-check **1886 validated / 0 failed**; report(lint+dedup) green.
- `make report` → the headline numbers above; **0 NON_MATCHING in any default build** (G4).
- The burn-down (T99, derived from the committed digest history per R33): daily instr series 68.9 → 87.5 with final-four-day decay **+2.7 → +2.2 → +0.6 → +0.3pp/day** — the engine's measured floor.
- T98 residue characterisation: **80 families / 960 members / 173 distinct** (29 all-STRUCT refused at remap by design + 51 no-STRUCT failing the gate with every lever applied; last three blast sweeps returned 0).

**Milestone achieved (confirmed by Drew, gate 2):** Phase 29 drove the fleet **+18.6pp instr / +28.5pp distinct / +8.06pp fn-count at 140/140 byte-identical throughout** — the largest single-phase gain in the project — resolved the roadmap's swing number (**(a) TOOLING**: the "~3% h_seq ceiling" was an `-O0` compile-flag artifact; `REGALLOC 0` on the 106-member sample), closed **every named blocker** in its long crack-and-bank series (**not one was a compiler wall** — each was a declaration, a symbol spelling, a flag combination, or a file placement), and then **closed itself on measured evidence**: the mechanical family engine's residue is 173 distinct against 2,713 banked in the final session, with daily yield decayed to +0.3pp. The close-out delivered the owed **roadmap v2 re-baseline** (P30–P33 on 2026-07-30 reality).

**Next:** **Phase 30 — The Recovery & Concentration Campaign** (roadmap **v2** §3 P30), opening with **T0 frontier regen + instrument repair** (reconcile the family_hseq↔progress count gap; fix `gate_stage` snapshot/restore + `rtu_match` error surfacing; purge the backlog ledger) before any wave is scoped (R35). Then T1 integration-recovery sweep, T2 the `-O0` Arm-A splat wall, T3+ the standing crack-wave loop. Fresh session, **plan mode, Max** (Tier-1 Phase-Start).

## Deviations

| Item | Plan (charter / roadmap v1 P29) | Actual | Reason |
|---|---|---|---|
| **`member_adapt.py` + the member-harvest track** | THE P29 member engine ("member_adapt + warm-start grinder over drift members") | **NEVER BUILT — VACATED** | Task 1 dissolved its premise: the h_seq DIFF class was an `-O0` compile-flag artifact + type-lift plumbing, not adaptable drift; the harvest ran through `family_sweep --hseq`/`dedup`/`gate_stage` instead and banked thousands |
| **The family-adapt fine-tune** (charter item 4, bounded experiment) | tune the local 7B on the adaptation task | **NEVER RUN — VACATED with member_adapt** | same dissolved premise; the W4-STRUCT residue (86 members) cannot justify a fine-tune |
| **Fable5 slot** | reserved for NEW wall classes | **unused for discovery; used at close for the roadmap-v2 synthesis** (Drew-directed) | no new wall class appeared that cheap-Opus + the §31–§121 idiom bank couldn't handle — the doctrine held |
| **Task 4** (grinder warm-start + 2 Phase-22 grinder bugs) | in-phase | **CARRIED → P30** | never load-bearing this phase (the wave machinery out-paced the grinder lane); genuinely useful only with P30's drift work |
| **Task 5** (fleet Ghidra-C prefetch) | in-phase fuel | **partial (ov_SC06_018); CARRIED → P31, re-scoped** | SESSION-13 measured the gap is in the TAIL + main (the reach-138 head is 146/159 cached) — the prefetch pays off in P31, and needs MCP sessions (R23/R29) |
| **Task 6** (permuter backlog sweep) | in-phase | **partial (targeting fix T13A landed); sweep CARRIED → P30** | fresh cracks + recovery out-yielded the permuter lane all phase; the close-1..4 drafts remain named fuel |
| **Task 16 — integration-recovery pass** | (not in the original plan) | **ADDED mid-phase (Drew-approved plan, SESSION-16), measured, delivered** | the SESSION-15 audit found the wave bottleneck is INTEGRATION (~92% of drafts byte-correct, ~27% bank) — recovering stranded byte-correct work beat drafting more |
| **The `-O0` ×138 rollout** | implied by the Task-1 verdict ("the pool is back on the table") | **WALLED — the Arm-A splat `%lo +0x20` re-carve defect; CARRIED → P30 T2 as a named instrument task** | the fix is splat-layer, not matching-layer; forcing it mid-campaign risked the fleet gate; the no-recarve driver alternative is sketched in the log |
| **Roadmap maintenance** | a PhaseEnd "Roadmap delta" line | **full roadmap v2 rewrite at close** | Drew's 2026-07-30 directive: 25 sessions of campaign had invalidated v1's numbers wholesale; a delta line couldn't carry the re-baseline |
| **My errors (recorded, not buried — the SESSION-25 ledger + earlier)** | (n/a) | §116 written with the wrong fix (refuted in 56s) · a bank predicted against a disqualifier I'd printed myself · "126 entries" that were 8 · T84's banks mis-attributed (committed wrong, corrected `f7c6d2eb2`) · T92's wrong recipe + phantom blocker (corrected `9a1507462`) · the wrong staging site patched twice → a lever mis-judged from a patch that never ran · T97 costed as a 3-part 2,022-decl job that was one 4-line edit · **and the month-old shared byte-gate defect found+fixed (SESSION-11: one binary verified against another's hash because a default was truthy)** | the common root: **asserting the composition of a number, or the effect of a change, I did not derive** — distilled into §120 ("prove it RAN") and the R37 candidate below |

## Commit Message

```
(Phase 29 landed as 552 commits 2e84b53b2..8c7395027 + this PhaseEnd. Fleet 68.9 -> 87.5% instr /
49.5 -> 78.0% distinct / 83.94 -> 92.00% fn-count; 140/140 byte-identical throughout; 0 NON_MATCHING.
The granular trail -> logs/Phase29.md.)

feat(phase-29): the family campaign — +18.6pp instr in 25 sessions; engine spent on evidence; roadmap v2 (v1.28.0)

- T1 diff_regions.py RESOLVED the swing number: (a) TOOLING — the "~3% h_seq ceiling" was an -O0
  compile-flag artifact (REGALLOC 0/106); the third structural wall to resolve to our own tooling.
- The campaign: crack waves + propagate-behind-each-crack + the §20 broad type-lift (154 types) +
  the jtbl carve waves + the SC07-region sweeps. SESSION-25 alone: 2,713 members, +100,572 ins,
  +1,620 unique fns, every named blocker closed — NOT ONE a compiler wall.
- Doctrine shifts (decision-log): fresh cracks are the only lever that moves distinct-code; the
  propagation cap gates de-duplication, not coverage; the wave bottleneck is INTEGRATION (~92%
  byte-correct, ~27% bank) -> the tiered T0/T1 blast-radius recovery driver (14/36 = 39% measured);
  gate_stage call-site-casts are the integration spine (bulk header edits BREAK builds).
- T98 characterised the residue: 80 families / 960 members / 173 distinct (29 all-STRUCT by-design
  + 51 gate-failing, 3 sweeps at 0) -> T99 burn-down (derived from digest git history, R33):
  final-four-day decay +2.7 -> +0.3pp/day. Closed on the measurement, gate-2 confirmed.
- roadmap-to-100 v2: P30 Recovery & Concentration -> P31 Scope-Complete + Main & Resident ->
  P32 Behemoths+Walls -> P33 Verify+Flip. member_adapt + family-adapt fine-tune VACATED.
- Honesty ledger: 7 recorded errors + the month-old shared byte-gate default defect (found+fixed);
  the -O0 Arm-A splat wall named and carried as P30 T2 instrument work, never force-banked.
- cookbook §54-§121 (68 sections); ~15 decision-log entries; calibration re-measured; R37 proposed.
```

## Rules Added This Phase

| Rule | Reason |
|---|---|
| **R37 — Probe before costing (proposed; Drew to accept/modify/reject).** Before PRICING or SCOPING a job — a "three-part fix", a "126-entry backlog", a phase task — probe ONE member/instance to ground the estimate, derive any attribution/count from `corpus.stubs` (or the governing invariant) before asserting it, and **diff the artifact to prove an edit actually ran** before judging the lever it carried. Extends R14 (verify data vs bytes) and R35 (verify the instrument) to the *estimating/attribution* step — the one place they didn't yet bind. | The SESSION-25 error ledger's common root, seven times over: T97 was costed as a 3-part job over 2,022 decls and was ONE 4-line edit (read the symptom, never probed the failure); T84's 137 banks were attributed to the wrong family in a commit; a lever was judged ineffective from a patch that never ran (§120); "126 entries" were 8. Every instance was an asserted composition/effect that one probe would have grounded. |

*(No OTHER new governance rules — per the Phase-8+ precedent, the phase's techniques live in the cookbook (**§54–§121**) and its findings in `decision-log.md`/`calibration.md`/roadmap v2. The **blast-radius taxonomy** (T0 draft-only / T1 binary-local / T2 fleet-shared→R22-mandatory) is an engineering invariant, recorded in roadmap v2 §5 and enforced by the recovery driver, not a conduct rule. The **shared byte-gate default defect** (S11) is governed by the existing R35/R32; the **fix_header_decl→gate_stage** correction is R14 applied. G3/P9, R14, R16/R30, R22, R26/R27, R31, R32–R36 governed the phase and it reinforced all of them.)*

## PhaseEnd Changelog

**v1.27.0 → v1.28.0 — Phase 29 complete (Gen2 phase 21; the family campaign).** The project's biggest phase: **25 sessions, 552 commits, +18.6pp instr / +28.5pp distinct / +8.06pp fn-count at 140/140 byte-identical throughout**. It opened by resolving the roadmap's swing number with a purpose-built instrument (`diff_regions.py`): the "~3% legacy h_seq ceiling" was **(a) TOOLING** — an `-O0` compile-flag artifact, the *third* consecutive "structural wall" to dissolve into our own tooling — which put the legacy-PURE pool back on the table and vacated the planned `member_adapt` delta engine before a line of it was written. The campaign then ran crack-waves with propagation behind every crack, landed the §20 broad type-lift (154 types), and produced three doctrine shifts now encoded in roadmap v2: **fresh cracks are the only lever that moves distinct-code**; **the propagation cap gates de-duplication, not coverage**; and **the wave bottleneck is INTEGRATION, not idioms** (~92% of wave drafts byte-correct, ~27% banking) — answered with the tiered blast-radius recovery driver (measured 14/36 = 39%). SESSION-25 closed every named blocker on the carried list (2,713 members in one session), and **not one was a compiler wall**. The phase then did the rarest thing: **it measured its own engine spent** (T98: 173 distinct residue; T99: daily yield decayed +2.7→+0.3pp with every lever applied) and closed on the evidence, delivering the owed **roadmap v2** (P30–P33 on 2026-07-30 reality). The honesty ledger records seven asserted-not-derived errors plus a month-old shared byte-gate default defect, found and fixed forward — the root distilled into the proposed **R37 (probe before costing)**. Cookbook **§54–§121**; the `-O0` Arm-A splat wall carried as named P30 instrument work.

## Roadmap delta (roadmap §0 — what Phase 29 changed about the road ahead)

**The delta IS roadmap v2** (`docs/roadmap-to-100.md`, committed `8c7395027` at close, Drew's plan-mode gate). Headlines: the family-remap engine is **spent on measurement** (W4 = 173 distinct); the three biggest un-spent levers are **stranded-draft recovery** (39% measured), the **`-O0` Arm-A splat instrument wall** (~1,287 distinct), and the **fresh-crack concentration head** (top-100 ≈ 53% of remaining instr; 61 zero-crack families); **main (0.7%), resident (14), and the 39 type-1 modules** are the P31 flag-plant arc; behemoth ledger REBUILT (`0x80183814`, 5,122 ins, is the game's largest fn and was missing from v1); `member_adapt` + the family-adapt fine-tune VACATED; scale estimate P30 ≈ 10–18 sessions · P31 ≈ 4–8 · P32 unknown · P33 ≈ 2–4, with the flip-timing checkpoint live at every close.

## Plain-English Recap

This phase was the big harvest. Over two weeks and 25 working sessions, the amount of the game rebuilt **perfectly, byte-for-byte** jumped from about **69% to 87.5%** — the largest gain in the project's history — and all 140 pieces of the game still rebuild flawlessly after every single change.

Three things mattered beyond the number. First, the phase opened by **settling an old question with a purpose-built measuring tool**: last month's verdict that a whole class of "similar-but-shifted" functions could only be automated 3% of the time turned out to be our own build using the wrong compiler setting — the third time in a row a "wall" turned out to be our own equipment. Second, we learned where the real friction is: our AI drafters produce **correct code ~92% of the time**, but only about a quarter of it was making it into the final build because of paperwork — declarations, file placement, name spellings. So we built a recovery pipeline for stranded-but-correct work, and in the final marathon session **every single stuck item on our list fell** — 2,713 functions banked in one day, and not one blocker was the 1990s compiler; every one was paperwork. Third, when the machine finally ran out of cheap wins, **we proved it with data rather than feelings** — daily progress fell from +2.7 points to +0.3, and only 173 genuinely new functions remained in that engine's reach — and closed the phase on the evidence.

I also kept an honest list of my own mistakes this phase — seven times I asserted a number or an effect I hadn't actually checked, plus one verification defect that had sat unnoticed for a month — each is recorded, fixed, and distilled into a proposed new working rule: **probe one example before pricing the job**. The road ahead is now re-mapped on today's real numbers: recover the stranded correct code, fix one known extraction bug that's hiding ~1,300 functions, crack the biggest remaining function families, then finish the main program and plant the first 100% flags.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase29.md` (R19, via `git mv` — **left uncommitted with this file for Drew's milestone-close commit**, R6 gate-2 sign-off). The Phase-29 work is committed across the sessions (`2e84b53b2..8c7395027`, 552 commits incl. T99 + roadmap v2); **Drew commits AND pushes** this PhaseEnd + the archived log. No Ghidra DB staging (R23 — the `db.*.gbf` churn is restart-noise). The pre-existing `.run/backlog.jsonl` edit rides along or is discarded at Drew's discretion (it is a regenerable digest input). Gen2 continues — do **NOT** start Phase 30 here. Start a **fresh session** (effort **Max**, **plan mode**) for **Phase 30 — The Recovery & Concentration Campaign** (roadmap v2 §3), opening with T0 frontier regen + instrument repair before any wave is scoped. Keep this file forever.

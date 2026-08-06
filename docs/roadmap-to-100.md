# The Road to 100% — the BFM-decomp endgame roadmap (v2, Phase 30+)

> **v2 re-baseline adopted:** 2026-07-30 (Drew, plan-mode gate at Phase-29 close; authored on
> Fable 5 at Max effort) · **Baseline:** the 2026-07-30 committed digests at HEAD `commit:1211`
> (post-T98/T99) · **Supersedes:** roadmap v1 (2026-07-15, this same file — full v1 text in git
> history at `commit:1210` and earlier; §7 records what changed and why) · **Status:** ACTIVE —
> re-baselined by every PhaseEnd.
>
> v1 chartered P27 (honest frontier) → P28 (endgame engine) → P29 (family campaign) → P30
> (mass+main) → P31 (behemoths) → P32 (flip). P27–P29 ran and **resolved every swing number v1
> held open** (§7). v2 re-charters the remainder as **P30–P33** on measured 2026-07-30 reality.

---

## 0. Authority, maintenance & how future sessions use this

- **This document is docs-layer and ADVISORY.** `PROJECT_CONTEXT.md` remains the constitution;
  `phase-ends/` remains the state. Every phase still opens with its own two-gate plan approval
  (P3) — this roadmap tells the Phase-Start session *what the phase is for and what feeds it*,
  not that the gate is pre-approved.
- **Every PhaseEnd re-baselines this roadmap.** Each PhaseEnd carries a standing **"Roadmap
  delta"** line: what this phase changed about the road ahead (numbers re-measured, buckets
  emptied/split, phases re-scoped/reordered, findings that retire a lever). The megaplan and
  roadmap-v1 precedents are the warning — **both plans' numbers rotted within one phase** when
  the tools under them were fixed. Numbers in §2 are true as of 2026-07-30 and every phase
  re-derives what it consumes.
- **On conflict:** the constitution and the latest PhaseEnd's "Next:" win over this file.
- **How a fresh session uses this:** complete the normal Session Start Protocol (CLAUDE.md load
  order) first; then, when planning the next phase, open this file at the matching §3 phase
  entry and plan from it + the latest PhaseEnd's Roadmap delta.
- **Number hygiene (R14 at planning scale):** every count below cites its committed source and
  its date. A scan is a hypothesis; the whole-binary byte-gate is the truth. Validate any
  "recoverable/templatable/matchable" count with a small gate probe before scoping work around
  it — and verify the *instrument* first (R35).

---

## 1. The completion contract (Drew's decisions, 2026-07-15 — unchanged; numbers corrected)

**Target: GAME-CODE TRUE 100%**, mechanically defined:

1. After SDK objects are LINKED, **zero `INCLUDE_ASM` and zero linked `NON_MATCHING` under
   `src/`** across **all onboarded code-bearing binaries**. *Corrected count (P30 S44/S45):*
   **183 onboarded today** — main + resident + 141 overlays (138 type-4 + the 3 uncompressed
   type-1 overlays ov_MAIN_012/ov_SC02_037/ov_SC03_107) + **40 md_* modules** at their §S44
   static slots (`docs/memory-map.md`; every one byte-identical on its FIRST build at the
   derived address). **The explicit exclusion list the 100% claim cites is the parked-for-L3
   ledger: 34 payloads** (`make audit-disc` → `docs/disc-ledger.md` UNCLAIMED; detailed in
   `docs/disc-completeness.md`) — the 28 SC0x script modules (7 × 4 per-disc builds), SC02/9,
   MAIN/7, MAIN/9, **and SC03/53, SC03/54, SC03/56** (S45: three SC-disc type-1 rows the S44
   exploration never tiered — same per-disc runtime routing class as SC02/9). Their bases are
   loader-determined per-disc, not EXE-static; guessing one would be P9 theater. 100% is only
   claimable once these 34 are onboarded-and-matched (post-L3 emulator tour, P31 bucket T) or
   remain explicitly excluded with this evidence — the byte-gate cannot see them (R34).
   *(The prior "39 type-1 backlog" framing is superseded: 43 of those payloads now build
   byte-identical as md_*/ov_* binaries; the residue is exactly the 34-row parked ledger.)*
2. Every binary **byte-identical from a genuinely clean tree** (R22: `make clean` +
   extract-all + `check-all`), and byte-identical **with AND without** the SDK objects
   (the fresh-clone stub fallback invariant).
3. **Both audit oracles green — extended to main + resident.** *Status:* overlays + resident
   covered (`make audit-corpus`, "corpus(+resident)"); **main still lacks an independent
   second oracle** — its LINKED-excluding sig is dated 2026-06-14 and the fleet digest itself
   carries the R34 caveat. P31 closes this before any 100% claim on main.
4. **No completion declaration while any game-code stub remains.** Wall verdicts are
   model-relative (the §45/§52 history — and P27–P29 proved *most "walls" were our own
   tooling*); walls are re-attacked at every phase boundary with the matured idiom bank and
   each new model generation until they fall.

**Scope decisions (standing):**
- **PsyQ LINKED = complete.** Main's SDK-named residue (gsgap 5 objects + libapi 800c3 ≈22
  objects) converts to LINKED in P31; the completion dashboard asserts the residue empties.
  *Side note (Drew): decompiling the PsyQ libraries from source (sotn precedent) is a
  legitimate far-future stretch — record it, do not plan it, revisit only after game-code 100%.*
- **Public flip at 100%.** Drew's call, made knowing the 2026-07-01 strategy review
  recommended a near-term flip. **Standing checkpoint:** every phase close reports measured
  velocity + all three metrics; if the trajectory stretches beyond what solo+agents can
  credibly finish, flip timing is re-surfaced with the numbers — the decision stays
  falsifiable. *P29's data point:* +18.6pp instr in 25 sessions, decaying to +0.3pp/day at
  its engine's floor — the checkpoint now has real curvature to watch.
- **Metrics contract — IMPLEMENTED 2026-07-22:** every phase close reports all three —
  fn-count (×138-inflated) · instr-weighted (decomp.dev-display) · distinct-code (the honest
  RE truth) — **with the main EXE in the weighted denominators** (live in
  `docs/progress.fleet.md` since 07-22; pre/post-07-22 instr deltas are not perfectly
  comparable across that change).

---

## 2. The measured baseline (2026-07-30 — committed digests only)

**Standing** (`docs/progress.fleet.md`, regenerated post-T98): **87.5% instr-weighted**
(11,493,049 / 13,141,652) · **78.0% distinct-code** (4,396,900 / 5,634,875; 69,816 / 87,459
unique fns) · **92.00% fn-count** (325,417 / 353,720) · **140/140 byte-identical** · dedup
1886/0 · 0 NON_MATCHING linked · tools-health RC=0.

**Remaining:** 28,296 stub instances · **17,643 distinct fns** · ~1.24M distinct ins ·
~1.65M weighted ins. Average remaining multiplicity ≈1.6 — **the high-reach families are
consumed**; what remains is mostly per-overlay-distinct code, main, and named walls.

**P29 velocity (the flip-checkpoint input):** +18.6pp instr / +28.5pp distinct (+16,288
unique fns) / +8.06pp fn-count over 25 sessions; mean ~+0.74pp instr/session; final-four-day
decay **+2.7 → +2.2 → +0.6 → +0.3** — the family-remap engine's measured floor (daily table:
`phase-ends/logs/Phase29.md` T99; derive fresh via `git log docs/progress.fleet.md`).

| # | bucket | scale (source, date) | honest tractability |
|---|---|---|---|
| **W1** | **Stranded byte-correct drafts** (integration-blocked) | backlog ledger 1,350 open near-misses, dozens close=0 "MATCH pending gate" (`docs/backlog.md` 07-29; rows include since-banked fns — purge at P30 T0); measured recovery **14/36 = 39%** (`docs/calibration.md` 07-24); 10 named still-blocked drafts | the cheapest distinct wins in the repo: the tiered recovery driver + §65b de-macroize + `gate_stage` call-site-cast. **Fix `gate_stage` snapshot/restore first** — the ladder currently destroys good drafts |
| **W2** | **The `-O0` cluster** | **10 families / ~1,287 raw distinct** ≈ 7% of all remaining distinct (SESSION-24/25 checkpoints) | WALLED by the **Arm-A splat re-carve defect** (`%lo +0x20` data-symbol shift on 3 of 4 sampled overlays; cookbook §116 area) — an *instrument* wall. B2, SC07, and the "~3% h_seq ceiling" all resolved to tooling; this has the same shape. Fix splat-side OR productionize the no-recarve staging driver (sketched, logs/Phase29 ~§9036) |
| **W3** | **The fresh-crack frontier** (the mass) | family map 07-29 (`docs/family-hseq.md`): **511 substantial families / ~707k templatable ins**, **61 zero-crack** (matched sibling exists); member classes 3,899 PURE / 40 IMM / 6 STRUCT; + non-substantial families + 3,771 singletons. **Concentration (SESSION-13, 07-23 — directional; re-derive at T0): top-20 ≈ 23% of remaining instr, top-100 ≈ 53%** | wave → `gate_stage` (call-site casts, NEVER bulk header edits) → propagate-same-session is proven at scale (2,713 members banked in one session once blockers cleared). **Fresh exemplar cracks are the only lever that moves distinct-code** (SESSION-14). jr-half via the §53 carve path. **No 150-ins wave cap** (SESSION-13) |
| **W4** | **T98 residue** (behind matched exemplars) | 80 families / 960 members / **173 distinct**: 29 all-STRUCT (86 members, refused at remap by design) + 51 no-STRUCT (874 members, stage-but-DIFF; last 3 sweeps returned 0) (logs/Phase29 T98) | STRUCT members = ordinary per-member drafts in the normal queues; the 51 = one bounded diagnosis wave (~3 distinct each, expect a NEW cause per family; the `rtu_match --stderr-out` recipe). Low mass — opportunistic, never the spine |
| **W5** | **GIANT walls + PINS** | `func_801412A8` (198×138, close=110, S11 LUID regalloc) + `func_80178004` (165×138, close=91, local-alloc) ≈ 50k gain ins; **PINS class 19 fns / ~61k gain** (`docs/worklist.md` 07-24 — STALE, re-derive at T0) | special projects: §H levers, `cc1_probe` kit (P32), frontier-model discovery sprints. PINS: the pin-crash SIGABRT dissolved in P27 — mechanically harvestable now |
| **M** | **Main EXE** | **1,034 stubs / ~60.2k game-code ins at 0.7%** (436/60,201) + 7 NON_MATCHING promotions + ~80 jtbl fns + SaveLoadRoutine (the last Gen1 deferral) + SDK residue gsgap 5 obj / libapi ≈22 obj (`docs/progress.md` 07-30) | standard machinery at ×1; the fuel gap is Ghidra-C prefetch (0/2,096 cached — SESSION-13); jtbl fns ride the matured carve workflow; **the second oracle is a contract item (§1.3)** |
| **R** | **Resident** | **14 stubs** (`docs/resident-dossier.md`): 5 PLUMBING (byte-correct C exists; loose-typing def-side) + 4 DIFF (genuine residuals) + 5 jtbl-deferred | def-side reconcile (`docs/canonical-decl-reconcile-design.md`) + resident jtbl carve + §H/permuter → **the first 100%-binary flag-plant** |
| **T** | **39 type-1 code modules** | un-onboarded, in NO phase (`docs/disc-completeness.md` 07-15); mostly small (83w–1,318w); 3 window-capped ≥4096w (true sizes unknown); 3 carry overlay-like code density (3.39%) → possible large dedup | **load-address RE** (PCSX-Redux RAM proof — the Phase-3 method, R10 ≥3 datapoints) → Ghidra import → splat onboard → **R36 citizenship** (`make audit-binaries`) → `dedup_extend` harvest (SC07 precedent: 95.6% free) → genuine residue into normal queues. Extends the denominator (honest direction: headline % drops) |
| **B** | **Behemoths** | v1's list was STALE — rebuilt (SESSION-13): **`0x80183814` (5,122 ins, ov_SC07_006 — the largest fn in the game; verify it's one fn, R14)** · `0x8017bf14` (4,763) · `0x8017d2dc` (1,586) · `0x8017dc1c` (1,518) · `0x8017c954` (1,194) · `0x8017c730` (1,061×2) — ~×1 singletons | late special projects (P32): `diff_regions` piecewise attribution + `cc1_probe` + frontier drafting. Never wave fuel |
| **D** | **Carried instrument defects** | `gate_stage` ladder destroys good drafts (no snapshot/restore) · `rtu_match` buries the real cc1 error behind `--stderr-out` · `--fix-def-sig` is a REPAIR not a default (§119) · 21-file absolute-include portability · `.run/autopsy/residuals.jsonl` stale (07-21) · `docs/backlog.md` is not a work queue (§83) · ~~family_hseq vs progress.py disagree~~ **RESOLVED P30 T0c: zero definitional gap** — both derive from `corpus.stubs`; the "29,961 vs 28,296" was a cross-date, cross-scope digest misread (the delta was exactly SESSION-25's 2,713 banks); digests now stamp scope+HEAD | fix at **P30 T0, before scoping waves on their numbers** (R35: tool-integrity precedes measurement) |

**The lever order (yield/cost, measured):** recover stranded drafts (W1) → fix the `-O0`
instrument (W2) → ride the concentration curve (W3) → scope-complete (T) → flag-plant main +
resident (M, R) → walls/behemoths re-priced each boundary (W5, B).

**Model/cost doctrine** (`docs/calibration.md` + `docs/effort-map.md`): local v3 $0 (≤15-ins
band) · Haiku-tier drafters ≤~50 ins (~4.8× cheaper, A/B-validated) · GLM lane for the
def-conflict-free band (~$0.03–0.08/fn) · cheap-Opus mid-band (~40–140k tok/fn) · Opus for
the 90+/regalloc tail · permuter $0 for drift · **frontier models (Fable-class) = discovery
only** (~230k tok/fn; ROI is idioms + wall-dissolutions, never banks) · Ultracode for breadth
waves (R26/R27 prompts at every transition) · Max for planning/synthesis/walls.

---

## 3. The phase sequence

Phases are two-gated as always (plan approval → autonomous execution → milestone
confirmation). Campaign phases close on measured yield floors, not calendar. Effort/model
annotations follow `docs/effort-map.md`.

### P30 — The Recovery & Concentration Campaign (overlays to their ceiling)
*(Ultracode breadth waves / Max synthesis & deep tasks; open-ended, ROI-gated. No MCP
dependency for the cached head — 146/159 reach-138 exemplars have Ghidra-C.)*

- **T0 — Frontier regen + instrument repair [Max].** Regenerate report / family map /
  worklist from verified inputs; **reconcile the family_hseq↔progress instance-count gap**
  (R32) before consuming either; purge since-banked fns from the backlog ledger; refresh the
  autopsy; **fix `gate_stage` snapshot/restore** (it destroys good drafts) + `rtu_match`
  cc1-error surfacing; per-session velocity **derived from `git log docs/progress.fleet.md`**
  (R33 — the committed digest history IS the burn-down tracker; build no scanner).
- **T1 — The integration-recovery sweep [Ultracode].** Every close=0 stranded draft through
  the tiered recovery driver (T0/T1 blast-radius containment; §65b de-macroize; the
  call-site-cast ladder); the 10 named blocked drafts; close the lane on its measured floor.
- **T2 — The `-O0` Arm-A splat wall [Max, deep; R17 web-research].** Fix the `+0x20`
  re-carve data-symbol shift at the splat/extract layer OR productionize the no-recarve
  staging driver; byte-gate on the 3 failing sampled overlays; success feeds the 10-family /
  ~1,287-distinct cluster into normal wave flow.
- **T3+ — The standing crack-wave loop [Ultracode waves; Max between].** 61 zero-crack
  families (propagation-only) → top-mass fresh families top-down, **no size cap**, jr-half
  via the carve path → **propagate behind every crack same-session** → the PINS class → W4
  residue diagnoses (bounded, opportunistic). Wave lanes by band: local v3 (≤15, $0) · GLM ·
  Haiku-tier · cheap-Opus · permuter on drift. Carried-in from P29: grinder family-warm-start
  + the 2 Phase-22 grinder bugs (Task 4), the permuter backlog sweep (Task 6), the 21-file
  include fix.
- Every session: velocity + all three metrics; R22 clean-fleet per banked batch; tools-health
  green before matching.

**Milestone:** overlays at their measured ceiling — **≥95% instr fleet, or every remaining
overlay stub on a named wall/behemoth/queue ledger** — 140/140 byte-identical throughout.

### P31 — Scope-Complete + Main & Resident to 100%
*(MCP + PCSX-Redux sessions — G2/R29/R23 discipline; Ultracode for the main waves.)*

- **T1 — Type-1 onboarding.** Size the 3 window-capped modules first; load-address RE per
  the Phase-3 method (RAM-dump byte-proof, R10 ≥3 datapoints) → Ghidra import → splat
  configs → **R36 citizenship** → `dedup_extend` harvest (3 modules look overlay-shaped —
  possible SC07-scale free banking) → genuine residue into the normal queues. Report the
  denominator re-baseline honestly (headline % will drop; that is the correct direction).
- **T2 — The main-EXE campaign.** Ghidra-C prefetch for main (the fuel gap) → band-tiered
  waves over the 1,034 stubs → the ~80 jtbl fns via the matured carve workflow → promote the
  7 NON_MATCHING → **SaveLoadRoutine** → gsgap resegment + libapi 800c3 → LINKED → **build
  main's independent second oracle** (contract §1.3) before any 100% claim on it.
- **T3 — Resident 14 → 0.** 5 PLUMBING via the canonical-decl-reconcile design; 5 jtbl via
  the resident carve; 4 DIFF via §H/permuter/pins. **First 100% binary; then main.**

**Milestone:** main + resident at 100% game-code; **all disc code onboarded or explicitly
excluded with evidence**; the contract denominators final.

### P32 — Behemoths + the Wall Endgame
*(deep sessions; Max + the best-available frontier model at that time)*

- **The behemoths (B)** from the REBUILT ledger (incl. `0x80183814`): `diff_regions`
  piecewise attribution + the **`cc1_probe` kit** (package the §45 gdb-on-cc1 / RTL-dump
  method: per-pass dumps, a two-candidate RTL differ, regalloc breakpoints — built here so
  wall work stays repeatable) + frontier drafting.
- **The wall track:** the GIANTS (close=110/91), the §52-class ledger, anything W2/W5 left
  behind — re-priced every phase boundary against the matured idiom bank + new model
  generations (the true-100% doctrine; and the P27–P29 lesson says: *check the instrument
  first*).

**Milestone:** 0 stubs, or a Drew-reviewed wall ledger with an explicit re-attack cadence
(this phase iterates until the walls fall; no false completion — P9).

### P33 — 100% Verification + the Public Flip + Gen2 Exit
*(Max; the capstone — substance unchanged from v1's P32)*

1. **Contract verification:** 0 game-code stubs across all onboarded binaries; R22
   clean-fleet; the dual with/without-SDK invariant; both audit oracles green including
   main + resident; the dashboard's three metrics at 100/100/100 game-code.
2. **The public flip** (the Gen2 Phase-14 checklist, `docs/gen2-roadmap.md`): the
   allowlisted two-repo mirror (R20 — copy-in, never delete-from-a-copy, no in-place
   scrub); the rom→decoder regeneration tool promoted into public `make extract`
   (H1 re-tightened); AGPL-3.0 (brave-CUE keeps GPL); no-ROM CI; frogress/decomp.dev;
   the README/docs refresh (the README self-declares Phase-19-stale); the first-push gate
   (ROM-SHA1/oversized-blob scan over tree AND history, **explicitly asserting `dumps/` +
   `extracted/` exclusion**, owner review before push); the one-way master→public sync
   script; **Ghidra `ExportSymbols` types/comments text-export** (makes the DB regenerable
   + public-clean — the Phase-9/10 carried note, due here at the latest).
3. **Parking-Lot sweep at the generation boundary** (PROJECT_CONTEXT): the
   Archipelago/randomizer contact (their unpublished US RAM research), the decomp.me
   preset submission.
4. **Releases:** the gcc-2.7.2 codegen map (§31 + `docs/gcc-2.7.2-map/`), `xsig` as a
   standalone MIT tool, the permuter-ILS/masked-scorer upstream PR, the v3
   matching-drafter pipeline write-up (`docs/community-matching-model-plan.md`).
5. **Drew's endgame deliverables** (the standing memory): the progress timeline/story,
   the hindsight retrospective, the public "how to AI-decomp" wiki — `docs/decision-log.md`
   (R31) is the substrate.
6. **Version 2.0.0 · Gen2 EXIT.**

**The Gen3 horizon (parked, post-exit):** shiftability, asset repack, native recomp / PC
port, randomizer tooling — and the libs-from-source stretch (§1 side note).

**Honest scale:** at P29's measured ~+0.7–1.1pp/session and a remaining mix with LESS
multiplication (avg multiplicity ≈1.6) and MORE ×1 work (main, singletons), the estimate is
**P30 ≈ 10–18 sessions · P31 ≈ 4–8 · P32 unknown-by-nature · P33 ≈ 2–4**. The §1
flip-timing checkpoint runs at every phase close.

---

## 4. Foreseen tooling (named now so phases don't rediscover it)

| tool | what it does | status / phase owner |
|---|---|---|
| `gate_stage` snapshot/restore | stop the reconcile ladder destroying good drafts | **P30 T0** (defect, load-bearing) |
| `rtu_match` error surfacing | put the real cc1 error in the verdict output, not behind `--stderr-out` | P30 T0 |
| frontier reconciler | family_hseq↔progress instance-count agreement (R32) | P30 T0 |
| recovery driver (extend `recover_integration.py`) | tiered T0/T1 blast-radius integration recovery at scale | P30 T1 (measured 14/36 in P29) |
| `-O0` Arm-A splat fix / no-recarve driver | unlock the 10-family `-O0` cluster | **P30 T2** (the biggest single distinct-unlock candidate) |
| grinder family-warm-start + 2 bug fixes | drift members as token-free CPU work | P30 (carried from P29 Task 4) |
| burn-down tracker | ~~build~~ **DERIVED** from `git log docs/progress.fleet.md` (R33) | done (P29 T99 recipe) |
| `diff_regions.py` | basic-block mismatch attribution → C lines | **BUILT** (P29 T1); used through P32 |
| `member_adapt.py` | exemplar→member delta engine | **VACATED** — h_exact case → `dedup_extend`; h_seq case dissolved (the `-O0` artifact, P29 T1); only the 86-member W4-STRUCT slice could ever want it — not planned |
| family-adapt fine-tune (7B) | tune the local model on the adaptation task | **VACATED with member_adapt** — same dissolved premise; W4's 86 STRUCT members cannot justify a fine-tune |
| parallel gate farm (same-binary shards) | 5–10× gate throughput | conditional on P30/P31 wave volume (the distinct-binary farm exists in `bulk_harvest`) |
| fleet Ghidra-C prefetch (tail + main) | drafting fuel where cache coverage is 0 | **P31** (R23/R29 discipline; the reach-138 head is already cached 146/159) |
| main second oracle | independent boundary oracle for the EXE (contract §1.3) | P31 T2 |
| canonical-decl-reconcile | the resident PLUMBING def-side fix | P31 T3 (design doc exists) |
| `cc1_probe` kit | packaged gdb-on-cc1 / RTL-dump / RTL-differ for wall re-attacks | P32 |

Build-along-the-way remains the doctrine (R16) — this table is the *foreseen* set, not a cap.

---

## 5. Standing invariants (every phase)

- The **whole-binary byte-gate is the sole arbiter** (G3/P9); `match_one`/closeness/h_seq/
  masked-MATCH are **candidates, never banks** (§52b — ~half of close=0 drafts fail the gate).
- **R22 clean-fleet verification** per banked batch (`make clean` + extract-all + `check-all`).
- **Tool-health gates green before matching:** corpus · cdecl · **audit-binaries (R36)** ·
  report (lint + dedup-check), fail-closed — and **fix the instrument before trusting its
  measurement** (R35): a 0% from a broken tool is not evidence.
- **Blast-radius typing on every integration write** (P29 T16): T0 draft-only / T1
  binary-local → the per-binary gate is sufficient; T2 fleet-shared (`src/shared/**`) →
  **R22 mandatory**; the driver measures the write set and asserts containment.
- **Probe before costing** (P29's error ledger; R37 candidate at the P29 PhaseEnd): probe one
  member/instance before pricing or scoping a job; derive attribution from `corpus.stubs`
  before/after; diff the artifact to prove an edit ran.
- **Predictions are gate-validated on samples before scaling** (R14).
- **One commit per task** after the `CURRENT_PHASE.md` update; Drew pushes (R6/R20).
- **The flywheel:** idioms → cookbook + tooling in the producing session (R16/R30); strategic
  pivots → `docs/decision-log.md` (R31); PhaseEnds carry the **Roadmap delta** line.
- **Effort/model transitions are prompted, never assumed** (R26/R27) — Claude cannot toggle
  `/effort` or the model itself.
- **Velocity + all three metrics reported at every phase close** — the flip-timing
  checkpoint (§1) runs on these numbers.

---

## 6. Risk register

| risk | posture |
|---|---|
| The W1/W2/W3 yield numbers rot (again) | Every plan-scale number above is dated + source-cited; P30 T0 re-derives ALL of them on repaired instruments before any wave is scoped. This file's two predecessors both rotted within one phase — assume this one will too and re-derive |
| The `-O0` Arm-A wall resists the splat fix | The no-recarve staging driver is the independent fallback (sketched in logs/Phase29); if BOTH fail, the ~1,287 distinct move to the wall ledger honestly — never force-banked |
| Type-1 modules surprise (big, or unmappable) | 3 are window-capped (true sizes unknown) — size them at P31 T1 open; load-address RE is R10-gated (≥3 datapoints); anything unmappable is documented-excluded, which the contract permits with evidence |
| Walls may hold for a long time | True-100% accepts this: no false completion, no redefinition (P9); P32 iterates with a Drew-reviewed re-attack cadence; model generations re-price walls |
| Frontier-model availability is episodic | v1's "Fable5 window expires ~7/19" lapsed, yet Fable 5 served the 07-30 re-baseline — treat availability as episodic: spend frontier capacity on *discovery/walls/synthesis* whenever present, never on wave fuel (calibration: its ROI is idioms, 0/5 direct banks) |
| Scale honesty | ~17.6k distinct fns at measured velocity is a multi-month solo+agent grind; the per-phase velocity report keeps the flip-at-100% decision falsifiable rather than assumed |
| Instrument rot | R32/R33/R34/R35 + the phase-open tool-health ritual; the named D-bucket defects are P30 T0, not "later"; any tool newly promoted to load-bearing gets its coverage assertion first |

---

## 7. Superseded & side notes

- **Roadmap v1 (2026-07-15) is superseded by this v2 (2026-07-30);** full v1 text in git
  history (`commit:1210`). What v1 held open, P27–P29 resolved: the member-adapt swing number
  (dissolved — the "~3%" was an `-O0` compile-flag artifact; `member_adapt` + the family-adapt
  fine-tune vacated); the "structural families ≈0%" doctrine (retired — B2 lives, 102/115);
  the pin-crash wall (dissolved P27); the Fable5-window urgency (lapsed; availability proved
  episodic); the P29 family campaign itself (ran 25 sessions, +18.6pp instr, engine measured
  spent at T98). v1's P30/P31/P32 substance carries forward as v2's P31/P32/P33 with
  corrected buckets (v1-B7's behemoth list was stale; v1-B9/B10 numbers re-measured).
- **`docs/family-endgame-megaplan.md`** remains superseded (since 2026-07-15; banner intact —
  kept for the record).
- **Libs-from-source** (decompile the PsyQ libraries; sotn precedent): recorded as a
  far-future stretch after game-code 100% — Drew, 2026-07-15. Not planned.
- **Sister-decomp idiom harvest** (Vagrant Story, CC0 — `docs/sister-decomps.md`): a parked
  ceiling-breaker if BFM's own idiom well runs dry; requires Drew's greenlight and the
  content firewall.
- The **flip-timing tension** (strategy review vs Drew's flip-at-100%) is documented in
  `docs/decision-log.md` (2026-07-15) with the standing velocity checkpoint that keeps it
  honest.

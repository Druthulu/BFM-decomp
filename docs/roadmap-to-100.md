# The Road to 100% — the BFM-decomp endgame roadmap (Phase 27+)

> **Adopted:** 2026-07-15 (Drew, plan-mode gate; authored on Fable5 at Max effort) ·
> **Baseline:** v1.25.0 / PhaseEnd_Phase26 · **Supersedes:** `docs/family-endgame-megaplan.md`
> (kept for the record, banner added) · **Status:** ACTIVE — re-baselined by every PhaseEnd.

---

## 0. Authority, maintenance & how future sessions use this

- **This document is docs-layer and ADVISORY.** `PROJECT_CONTEXT.md` remains the constitution;
  `phase-ends/` remains the state. Every phase still opens with its own two-gate plan approval
  (P3) — this roadmap tells the Phase-Start session *what the phase is for and what feeds it*,
  not that the gate is pre-approved.
- **Every PhaseEnd re-baselines this roadmap.** Each PhaseEnd from Phase 27 on carries a
  standing **"Roadmap delta"** line: what this phase changed about the road ahead (numbers
  re-measured, buckets emptied/split, phases re-scoped/reordered, findings that retire a lever).
  The megaplan precedent is the warning — a plan's numbers rotted *within a single phase* when
  the tools under it were fixed. Numbers in §2 are true as of 2026-07-15 and every phase
  re-derives what it consumes.
- **On conflict:** the constitution and the latest PhaseEnd's "Next:" win over this file.
- **How a fresh session uses this:** complete the normal Session Start Protocol (CLAUDE.md load
  order) first; then, when planning the next phase, open this file at the matching §3 phase
  entry and plan from it + the latest PhaseEnd's Roadmap delta.
- **Number hygiene (R14 at planning scale):** every count below cites its committed source.
  A scan is a hypothesis; the whole-binary byte-gate is the truth. Validate any
  "templatable/matchable" count with a small gate probe before scoping work around it.

---

## 1. The completion contract (Drew's decisions, 2026-07-15)

**Target: GAME-CODE TRUE 100%**, mechanically defined:

1. After SDK objects are LINKED, **zero `INCLUDE_ASM` and zero linked `NON_MATCHING` under
   `src/`** across **all onboarded code-bearing binaries** (count fixed by the P27
   disc-completeness audit; currently 136: main + resident + 134 overlays).
2. Every binary **byte-identical from a genuinely clean tree** (R22: `make clean` +
   extract-all + `check-all`), and byte-identical **with AND without** the SDK objects
   (the fresh-clone stub fallback invariant).
3. **Both audit oracles green — extended to main + resident.** Today `make audit-corpus`'s
   independent boundary oracle covers only the 134 overlays (`tools/corpus.py` restricts to
   where `sig_image` is independent); main and resident are structurally blind spots for the
   PHANTOM/TRUNCATED defect class. P27 closes this before any 100% claim on either binary.
4. **No completion declaration while any game-code stub remains.** Wall verdicts are
   model-relative (the §45 and §52 history); walls are re-attacked at every phase boundary
   with the matured idiom bank and each new model generation until they fall.

**Scope decisions:**
- **PsyQ LINKED = complete.** Main's ~2.0k stubs split ≈1.05k game-code / ≈0.95k SDK-named;
  the SDK-named set is mostly already LINKED-complete, with a convertible residue (gsgap 5
  objects + libapi 800c3 ≈22 objects). The completion dashboard derives this split
  mechanically and asserts the SDK residue empties. *Side note (Drew): decompiling the PsyQ
  libraries from source (sotn precedent) is a legitimate far-future stretch — record it, do
  not plan it, revisit only after game-code 100%.*
- **Public flip at 100%.** Drew's call, made knowing the 2026-07-01 strategy review
  recommended a near-term flip ("community labor is how every peer crossed the hard middle").
  **Standing checkpoint:** every phase close reports measured velocity (instr-%/session);
  if the trajectory to 100% stretches beyond what solo+agents can credibly finish, the
  flip-timing question is re-surfaced with the numbers — the decision stays falsifiable.
- **Metrics contract:** every phase close reports all three — fn-count (×134-inflated),
  instr-weighted (decomp.dev-display), distinct-code (the honest RE truth) — **with the main
  EXE added to the weighted denominators** (it is excluded today: `docs/progress.fleet.md`).

---

## 2. The measured baseline (2026-07-15 — committed post-audit artifacts only)

**Standing** (`docs/progress.fleet.md`): 68.9% instr-weighted (8,759,613 / 12,707,182) ·
49.2% distinct-code (2,663,147 / 5,410,077; 53,429 / 84,996 unique fns) · 84.47% fn-count ·
136/136 byte-identical · dedup 1840/0 · 0 NON_MATCHING linked.

**Remaining:** 53,371 stub instances · 3,947,569 weighted ins · 31,546 distinct classes
(2,746,930 distinct ins) (`docs/family-hseq.md`) — **plus** the main EXE's ~2,002 stubs
(≈1,048 game-code `func_` + ≈954 SDK-named), which sit outside today's weighted metric.

| # | bucket | scale (source) | honest tractability |
|---|---|---|---|
| B1 | Substantial h_seq families (nins≥80) | 562 families / 2,525,293 ins ≈ 64% of remaining; top-20 = 34% of this (`family-hseq.md`) | per-member cracking; mechanical templating byte-proven dead (3 probes 0%, PhaseEnd26) |
| B2 | └ **`0x8017BEBC` family — NEVER PROBED** | 952 ins × ~112 members ≈ 106k ins; exemplar MATCHED (`family-hseq.md` row 1; logs/Phase26 §carried) | IMM-scattered class the exhaustion probes did not cover → P27 gate-probe. Possibly the largest cheap win left |
| B3 | └ reach-134 near-miss core backlog | 228 cores / 884,130 gain-ins (`worklist.md`) | **fresh §52-lever re-drafts only** — 5/5 §52-wave banks prove the path; the STORED drafts are byte-proven non-bankable as-is (0/958 re-gate, decision-log A10) |
| B4 | └ ex-"plumbing-blocked" cores | 5 still-stub cores ≈ 234k ins; ≈123k plumbing-shaped: `0x80131340` (424) / `0x8015B950` (271) / `0x8015C32C` (222) (decision-log session-8; `func_8017A4AC` ALREADY banked; `0x8013F350` = a real class, not plumbing) | `reconcile_tu` is ALREADY WIRED (PhaseEnd26 build log) — P27 re-attempts each through it and byte-gates, per-core |
| B5 | └ jr/switch substantial cores | 191 cores (logs/Phase26) | jtbl-rodata carving per sibling (§48 idioms exist; fix `jtbl_carve.all_data_labels` first) |
| B6 | Non-substantial families + singletons | ≈1.42M ins ≈ 36% of remaining; 3,550 singletons (`family-hseq.md`) | wave-able small/medium fns: local v3 (≤15 band) + GLM lane (~$21 OpenRouter) + cheap-Opus |
| B7 | Behemoths | 5 fns: `0x8017bf14` 4763 · `0x8017d2dc` 1586 · `0x8017c954` 1194 · `0x8017c730` 1061(×2) ins ≈ 0.3% of distinct code (megaplan §4) | true-100% includes them; LATE special projects, never Fable5-window fuel |
| B8 | Walls + carried stragglers | 2 permanent giants (`func_801412A8` close=110, `func_80178004` §52 flagship) · 4 §52/52a/52b classes · `func_80135EB0` ×134 = 38.7k ins (§50-F) · seeds · `func_801549F8` ("2 diffs from done", ×134) · `func_8012E364` (stale closeness) | P27 REBUILDS the wall ledger from refreshed data, not memory; quick straggler checks first |
| B9 | Main EXE game code | ≈1,048 `func_` stubs incl. SaveLoadRoutine (the last Gen1 deferral), 7 NON_MATCHING drafts, ~80 jtbl fns (`progress.md`; counts re-derived in P27) | standard machinery + the Phase-7 jtbl/rodata workflow |
| B10 | Resident | 21 stubs (`progress.resident.md`) | the first 100%-binary flag-plant (P28) |
| B11 | ≤15-ins tail | ~383 fns (PhaseEnd23 carried state) | local v3, $0 |
| B12 | Backlog ledger | 1,858 near-misses, 1,670 untriaged (`backlog.md`) | P27 triage feeds all queues |

**The refusal taxonomy** (why templating died — PhaseEnd26 + decision-log): **collision**
(h_seq matched functions that are genuinely different — filter, don't adapt) ·
**register-drift** (the ONLY adaptable class — §52 levers, ~⅓ pin-free crack rate per walled
cluster) · **pin-crash** (`register __asm__` pins SIGABRT cc1 in sibling TUs → ×1 ceiling;
P27 characterizes the SIGABRT).

**The throughput law** (§52b): ~half of `match_one` close=0 drafts fail the whole-binary
gate — a match_one MATCH is a candidate, not a bank. Gate throughput is load-bearing
(hence the P28 gate farm).

---

## 3. The phase sequence

Phases are two-gated as always (plan approval → autonomous execution → milestone
confirmation). Open-ended campaign phases close on measured yield floors, not calendar.
Effort/model annotations follow `docs/effort-map.md` + the megaplan §4 tier doctrine
(**Fable5 discovers, cheap-Opus applies; permuter for drift; local v3 for the trivial band;
Ultracode for breadth waves; Max for planning/synthesis** — all toggles prompted, R26/R27).

### P27 — The Fable5 Farewell Sprint + the Honest Frontier
*(Max session; sprint via `Agent(model: fable)` parallel-isolated; ~2–4 sessions)*

1. **FIRST — the Fable5 discovery sprint (expires ~7/19).** Time-boxed, parallel-isolated
   agents, distill-same-session (R30). Priority order, drop from the bottom:
   (a) the 3 recon-done pin-free seeds — `func_8014D820` (304×134), `func_8016CBC0` (209×134),
   `func_801670E4` (279×134, close=23);
   (b) 1–2 top un-drafted fresh substantial cores — `0x80176734` (371×134), `0x8013C414`
   (329×134) — new-wall-class discovery while the discoverer exists (megaplan §4 doctrine);
   (c) a bounded pass on `func_80178004`'s one untested lever (`qty_n_refs`,
   local-alloc.c:1869);
   (d) characterize the pin-crash cc1 SIGABRT (§42e) — it gates P31's pin-×1 endgame.
   Explicitly NOT behemoths.
2. **Tool-health ritual + the named tool debts** (audit ledgers): `harvest_verify._TD` →
   derive the strip-set from `engine_types.h` (39 fns permanently blocked today);
   `masked_diff.SCALAR_TYPEDEF_RE` multi-typedef skip (42 live drafts discarded);
   `jtbl_carve.all_data_labels` (load-bearing for B5 + main's jtbl fns); migrate
   `worklist`/`exemplar_miner`/`difficulty` off the inherited scanners; remaining `cdecl`
   consumers migrate per-bank, byte-gated, exactly as the audit prescribes.
3. **Deterministic re-attempts, byte-gated per-core:** the 5 ex-blocked cores (B4) through
   the already-wired `reconcile_tu` path — validate, don't assume; the `0x8017BEBC` ×112
   IMM-sweep gate-probe (B2); `func_801549F8` + `func_8012E364` quick checks (B8).
4. **The byte-gate-honest re-scan:** refreshed surveys on the fixed tools → the work-queue
   partition + **`worklist --assert-partition`** (R32: every remaining stub lives in exactly
   one queue); triage the 1,670 untriaged backlog entries; rebuild the wall ledger from data.
5. **Calibration probes (the roadmap's swing numbers):** member-adapt close-rate on
   register-drift members; realized ×N propagation per fresh core crack; cost/fn per tier.
   These size P28/P29 honestly before anything scales.
6. **Disc-completeness audit:** the disc has 138 type-4 LZSS payloads but 134 onboarded
   overlays (`docs/formats.md`), and the resident proves type-1 entries can carry code
   (166 exist) — reconcile the 4 stragglers, sweep other types for executable bytes, onboard
   anything code-bearing (`tools/new_overlay.sh`), and fix the contract's binary count.
7. **The completion dashboard:** main sig'd + added to the weighted metrics; **extend
   `make audit-corpus` (the sig_image second oracle) to main + resident**; the mechanical
   game-code/SDK split assertion (§1).

**Gate:** sprint idioms distilled into the cookbook; a validated residue map with measured
rates; the contract + dashboard adopted.

### P28 — The Endgame Engine
*(Max design / xHigh build; ~2–3 sessions)*

Build + calibrate each on byte-gated samples before scaling:
- **`member_adapt.py`** — the exemplar→member delta engine over `family_remap`'s existing
  `imm_map` hook: align exemplar-C asm vs member asm; classify each delta (reloc→substitute /
  immediate→C-literal swap / regalloc-drift→permuter / structural→agent); gate; on failure
  emit a per-member **delta brief** so a cheap agent edits 3 lines instead of re-deriving 200.
- **The parallel gate farm** — sharded `harvest_verify` across N build dirs (flock-per-binary);
  the §52b throughput law makes this load-bearing; the 26-A stale-object fix makes it safe.
- **Fleet-wide Ghidra-C prefetch** — import all 134 overlay programs (script-reproducible)
  + batch-decompile every remaining stub into the drafting cache (today: ~300 fns of one
  overlay). Existing tools; missing only the orchestration. (R23/R29 MCP discipline applies.)
- **Grinder family-warm-start** + the two Phase-22 bug fixes (split-file-blind lookup;
  churn-without-blacklist) — drift members become token-free CPU work.
- **`diff_regions.py`** — cluster masked_diff output into basic-block-aligned regions mapped
  to C lines; cuts agent iteration cost on every large function.
- **The burn-down tracker** over `progress --weighted` (per-bucket remaining ins over time,
  velocity/session — feeds the flip-timing checkpoint).

**Flag-plant: resident → 100%** (21 stubs) or its honest wall dossier — now a verifiable
claim because P27 extended the second oracle to it.
**Gate:** measured engine throughput; resident resolved.

### P29 — The Family Campaign: cores + members
*(Ultracode breadth waves / xHigh orchestration / Max synthesis; open-ended, ROI-gated)*

The biggest instr-% arc of the roadmap. Two interleaved tracks, highest byte-weight first:
1. **Core cracks:** the 228-core backlog (B3, fresh §52-lever re-drafts) then fresh
   substantial cores by mass (the `family-hseq.md` top table) — cheap-Opus applying the
   §31–§52b idiom bank, permuter-ILS on drift seeds, `rtu_match` verify, `family_sweep`
   propagate.
2. **Member harvest behind each crack:** `member_adapt` + the warm-start grinder over each
   cracked family's drift members (the P27-calibrated close-rate governs pacing).
3. **jr/switch cores** (B5) via the fixed jtbl-carve + §48 idioms.
4. **Bounded experiment — the family-adapt fine-tune:** export banked members as
   (exemplar C, member asm)→member C pairs; tune the local 7B on the *adaptation* task
   (a far easier task than free decomp — which is why v3 plateaued and v4 was discarded).
   Kill criterion: must beat v3-on-members on a 50-fn byte-gated sample or cancel.

**Close:** when per-session yield floors (measured, reported).

### P30 — The Small-Fn Mass + Main-EXE Close-out
*(Ultracode waves; open-ended, ROI-gated)*

1. **The non-substantial mass (B6/B11):** local v3 (≤15 band, $0), the GLM lane
   (def-conflict-free band, ~$0.03–0.08/fn, ~$21 budget), cheap-Opus waves, permuter.
2. **Main EXE to its byte-ceiling (B9):** the trivial band + leaves; the ~80 jtbl fns
   (Phase-7 rodata-island workflow); **promote the 7 NON_MATCHING drafts** to matched;
   **SaveLoadRoutine** (the last Gen1 deferral falls here); gsgap resegment (5 libgte
   objects) + libapi 800c3 (~22 objects) → LINKED; prove the SDK-named residue empties
   (the §1 assertion).

**Milestone:** main + resident at 100% game-code; every overlay ≥95% instr-weighted or at
its wall/behemoth ledger.

### P31 — Behemoths + the Wall Endgame
*(deep sessions; Max + the best-available frontier model at that time)*

- **The 5 behemoths (B7)** as special projects: `diff_regions` piecewise attribution +
  the **`cc1_probe` kit** (package the §45 gdb-on-cc1 / RTL-dump method: per-pass dumps,
  a two-candidate RTL differ, regalloc breakpoints — built here so wall work stays
  repeatable post-Fable5) + frontier drafting.
- **The wall track:** re-attack the P27-rebuilt ledger with the matured idiom bank +
  cc1_probe evidence; the **pin-×1 endgame** where propagation is impossible (requires
  P27's SIGABRT characterization); every phase boundary re-prices walls against new
  idioms/models — the true-100% doctrine.

**Milestone:** 0 stubs, or a Drew-reviewed wall ledger with an explicit re-attack cadence
(this phase iterates until the walls fall; no false completion).

### P32 — 100% Verification + the Public Flip + Gen2 Exit
*(Max; the capstone)*

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

---

## 4. Foreseen tooling (named now so phases don't rediscover it)

| tool | what it does | phase owner |
|---|---|---|
| `worklist --assert-partition` | R32 assertion: every remaining stub in exactly one queue | P27 |
| main+resident second oracle | extend `audit-corpus`/sig_image beyond the overlays | P27 |
| `member_adapt.py` | exemplar→member delta engine + agent delta briefs (over `imm_map`) | P28 |
| parallel gate farm | sharded `harvest_verify`, flock-per-binary, 5–10× gate throughput | P28 |
| fleet Ghidra-C prefetch | all 134 overlay programs → every stub cached for drafting | P28 |
| grinder warm-start + bug fixes | family-seeded permuter daemon (token-free drift work) | P28 |
| `diff_regions.py` | basic-block mismatch attribution → C lines | P28 (used P29–P31) |
| burn-down tracker | per-bucket velocity over `progress --weighted` | P28 |
| family-adapt fine-tune | 7B tuned on the adaptation task (bounded experiment, kill criterion) | P29 |
| `cc1_probe` kit | packaged gdb-on-cc1 / RTL-dump / RTL-differ for wall re-attacks | P31 |

Build-along-the-way remains the doctrine (R16) — this table is the *foreseen* set, not a cap.

---

## 5. Standing invariants (every phase)

- The **whole-binary byte-gate is the sole arbiter** (G3/P9); `match_one`/closeness/h_seq are
  candidates, never banks.
- **R22 clean-fleet verification** per banked batch (`make clean` + extract-all + `check-all`).
- **Tool-health gates green before matching:** `make audit-corpus` · `make audit-cdecl` ·
  `make report` (carries `lint_symbol_refs` + `dedup-check`, fail-closed).
- **Predictions are gate-validated on samples before scaling** (R14) — the Phase-26 lesson.
- **One commit per task** after the `CURRENT_PHASE.md` update; Drew pushes (R6/R20).
- **The flywheel:** idioms → cookbook + tooling in the producing session (R16/R30);
  strategic pivots → `docs/decision-log.md` (R31); PhaseEnds carry the **Roadmap delta** line.
- **Effort/model transitions are prompted, never assumed** (R26/R27) — Claude cannot toggle
  `/effort` or the model itself.
- **Velocity + all three metrics reported at every phase close** — the flip-timing
  checkpoint (§1) runs on these numbers.

---

## 6. Risk register

| risk | posture |
|---|---|
| Member-adapt close-rate unknown | THE swing number — P27 task 5 calibrates before P28/P29 scale; the roadmap's yield projections are deliberately absent until then |
| Fable5 window hard-stops ~7/19 | Only P27 task 1 is perishable — it runs first. Post-window wall discovery waits for future model generations (verdicts are model-relative; the re-attack cadence encodes this) |
| Walls may hold for a long time | True-100% accepts this: no false completion, no redefinition (P9); P31 iterates with an explicit Drew-reviewed cadence |
| Scale honesty | ~31.5k distinct fns is a multi-month solo+agent grind at any measured velocity; the per-phase velocity report keeps the flip-at-100% decision falsifiable rather than assumed |
| Instrument rot | R32/R33/R34 + the phase-open tool-health ritual; 63 of 82 tools were never audited — any tool newly promoted to load-bearing gets its coverage assertion first |
| Number rot in THIS file | §0: every PhaseEnd re-baselines; consume §2 only through a re-derivation |

---

## 7. Superseded & side notes

- **`docs/family-endgame-megaplan.md` is SUPERSEDED by this file** (2026-07-15). Its h_seq
  reframe survives (it produced Phase 26); its scan-derived numbers and its "crack ~986
  exemplars → template ×120" thesis do not (byte-proven exhausted, PhaseEnd26). Kept intact
  for the record with a banner.
- **Libs-from-source** (decompile the PsyQ libraries; sotn precedent): recorded as a
  far-future stretch after game-code 100% — Drew, 2026-07-15. Not planned.
- **Sister-decomp idiom harvest** (Vagrant Story, CC0 — `docs/sister-decomps.md`): a parked
  ceiling-breaker if BFM's own idiom well runs dry post-Fable5; requires Drew's greenlight
  and the content firewall.
- The **flip-timing tension** (strategy review vs Drew's flip-at-100%) is documented in
  `docs/decision-log.md` (2026-07-15) with the standing velocity checkpoint that keeps it
  honest.

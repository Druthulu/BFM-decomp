# CURRENT PHASE — Phase 26: The Family-Endgame (finish the decomp)

> **Status:** ACTIVE · plan approved by Drew (gate 1) 2026-07-11 · Generation Gen2 (18th phase of the arc)
> **Opening brief:** `docs/family-endgame-megaplan.md` (Phase-25 handoff). **Fable5 window closes ~2026-07-13.**
> **Recovery note:** a fresh session resumes from the ▶ CURRENT TASK below (P3 — autonomous between gates). Read the plan context here + the megaplan; per-task log at the bottom is the crash-recovery trail.

## The plan in one paragraph

The Phase-25 h_seq reframe: the "unique tail" is really per-location families — crack ONE exemplar, template ×~120 siblings through the whole-binary byte-gate. Planning-session verification (2026-07-11) reproduced the survey from the sigs: **663 tail families; substantial (nins≥80) = 186 families / 1.85M ins** (megaplan's "986" was a miscount). Design-stage discovery (byte-verified on specifics, V0 re-verifies — R14): **the tail is ~90% a reloc-tracker blind spot** — `norm_stream`/`reloc_targets` drop the pending `lui`-hi on any R-type write, but gcc-2.7.2's indexed-global idiom (`lui; addu $idx; lw lo($at)`) preserves it, so every `D_x[i]` access made its function "fleet-unique" and broke remap. Substantial-tail classes: PURE-same-addr 62 fams/1.55M ins · PURE-cross-addr 103/0.10M · IMM 8/0.10M. **Free win: 63 families / 0.31M ins have a MATCHED exemplar** and siblings that failed earlier sweeps only from the tracker bug → zero-crack banks once the ~40-LOC fix lands (= the validation corpus). Also found: `remap()` sequential substitution corrupts chained renames → must become single-pass simultaneous. Immediate substitution shrinks to an escalation tier (diff-driven, 3 tiers; probe only ambiguous values). **Owner decisions:** carried Fable5 queue (5 giants) deferred to END of phase (low priority); milestone = structural completion.

## Task checklist (effort per R7 · one commit per completed task, Drew pushes — R6)

- [x] **Task 0 — Bootstrap** `[xHigh]` — this file + harness task list (R28). *(completes with this commit)*
- [x] **Task 1 — Remap core: extended reloc tracker + single-pass substitution** `[xHigh]` — `family_remap.py`: hi propagates through add/addu index adds; `symbol_map`/`remap` gained backward-compatible `to_addr=None` (cross-address) + `imm_map` hook; single-pass simultaneous substitution + self-rename. norm_stream/h_norm UNTOUCHED. Discovery → cookbook §40b (R30) + decision-log (R31). **V0 PASS** (`.run/v0_reloc.py`): 22/22 regression (`func_80141100` NEW==OLD), 15/15 fix (`func_801407F4` vs splat .s, recovers `D_80187B88/90/B0`), cross-addr symbol_map clean. **V1 PASS** (`.run/v1_regression.py`): 160 real h_norm pairs, 96 SAME, **0 lost**, differences are strict indexed-reloc improvements. *(committed)*
- [x] **Task 2 — `tools/family_hseq.py` + committed manifest** `[xHigh]` — full-frontier survey; shared word-diff classifier added to `family_remap.py` (`stream_words`/`reloc_indices`/`reg_fields`/`classify_member` — PURE/IMM/STRUCT, register-drift aware). → `.run/family_hseq.json` + `docs/family-hseq.md`. **VERIFIED:** fleet 74.8/58.2/30.3 (= PhaseEnd_25 & progress.py to the decimal); tail cross-check **663 families / 186 substantial / 1.847M ins** (exact); classification vs Plan-agent table **PURE-same 62, IMM 8 exact, PURE-cross 114≈103**; 890×134/562×134 PURE per-location + 952×113 #addr21 IMM confirmed; full frontier = 581 substantial families / 3.22M templatable ins, **345 matched-sibling PURE/IMM families / 1.14M ins = the V2/V3 zero-crack corpus**. *(committed)*
- [ ] **Task 3 — Imm engine (T2a, 3 tiers) + cross-address delta (T2b)** `[xHigh]` — Tier 1 simultaneous value-replace (asm-side ambiguity check; C tokenizer; signed imm16/sa/shift-vs-multiply spellings); Tier 2 targeted probe (~1–6 values/family; match_one-pipeline recompile; nins+h_seq guards; FRAGILE); Tier 3 member-fail → agent queue. T2b: h_seq sibling discovery at any addr; self-rename; distinct "link-undef" logging (fallback: `config/symbols.ov_*.txt` append + re-extract, second pass). Verify: 25 matched-matched imm pairs A→B regression.
- [ ] **Task 4 — `family_sweep --hseq` mode** `[xHigh]` — manifest-driven; member word-diff pre-filter (STRUCT skip); stage `.run/sweep/<ov>/`; existing two-phase stage→`harvest_verify` gate; `--only/--reconcile/--no-preclassify` carry over; 30-sec sibling-TU compile probe before ×N claims (pin-free, §42e).
- [ ] **Task 5 — Zero-crack validation harvests (V2/V3) — GO/NO-GO** `[xHigh; UC if fan-out — R26 prompt]` — V2: the 63-fam/0.31M-ins tracker-miss corpus (incl. `0x801407f4`/`0x8015d5e8`/`0x8015f118` ×118) → real banks + measured success rate + failure taxonomy. V3: 12 imm families with matched exemplars (`0x8016b448` ×134, `0x8017dde8` ×108). Scale NOTHING until rates are on the table; poor → fix tooling or assisted-template fallback.
- [ ] **Task 6 — Step-A triage of the 186 substantial exemplars** `[Ultracode — R26/R27 prompt + WAIT]` — ranked cheap-draft + `rtu_match` + §31/§44 classing → cheap-crackable / permuter / Fable5-necessary lists; 15-ins mega-family collision screen. Pilots: 102×4, 265×7, then the 952×100 cross-addr flagship.
- [ ] **Task 7 — Family-core crack waves (the Fable5 window)** `[launch at Max — R27; agents model:fable, parallel-isolated, distill-between]` — biggest byte-weight first (890/562/536/493…); §45-templated prompts (read `.greg`/`.lreg` first; Lever-A merged-accumulator audit; 1-death in-out-asm; /s; gdb-on-cc1, `tools/reference/gcc-2.7.2/`); PIN-FREE (×134); `harvest_verify` arbitrates; distill each crack → cookbook §46+ (R30); cheap-Opus applies banked idioms between waves; cheap/permuter lists run in parallel `[UC]`. ~375k tok/crack guide; documented wall + levers = valid outcome (P9).
- [ ] **Task 8 — Mechanical harvest waves** `[Ultracode; continues post-window]` — cracked exemplars → template ×members → gate → bank; h_norm draftable/matched-free retries with the new tracker (5.9 MB bucket); F-jumptable 4 (§8); M-linkwall 1; link-undef second pass. Batched commits; **R22 clean-fleet before each commit batch** (never while agents need `asm/`).
- [ ] **Task 9 — Mid-band + residue measurement** `[xHigh]` — <80-ins families (0.68M ins) through the engine; measure h_seq-miss → GO/NO-GO fuzzy pass (build only if ROI; else Phase 27).
- [ ] **Task 10 — Carried Fable5 queue (END of phase — Drew's call)** `[Fable5 if window remains, else permuter/Opus + banked levers]` — 801670E4 (diff-23), 80178004 (close-7), 801412A8 (close-29), 8016CBC0 (153/209), 8014D820 (LCS-226); specs `.run/giants/*.opus.md` + `.run/t7b/close/`. Crack ×134 or wall-document; post-window walls → Phase 27, accepted.
- [ ] **Task 11 — Step-D residue map** `[xHigh]` — true singletons (~0.27M ins) + 5 behemoths → Phase-27 input doc. NO execution.
- [ ] **Task 12 — PhaseEnd** `[Max — Tier 1; R27 prompt]` — P7 walk, milestone demo, gate 2, `PhaseEnd_Phase26.md`, worklog → `logs/Phase26.md` (R19), in-file recap (R25), decision-log current (R31).

## ▶ CURRENT TASK: Task 3 — the imm engine (T2a, 3 tiers) + cross-address delta (T2b) (Opus/xHigh)

## Milestone (gate 2 — structural completion, per Drew)

1. h_seq engine committed, V0–V3 validated with a measured template success rate.
2. Every substantial (nins≥80) family banked ×members OR classified with evidence.
3. Fable5-necessary cores attempted before window close; every crack distilled (R30/R31).
4. Carried 5-target queue resolved (cracked or wall-documented).
5. 136/136 byte-identical from clean fleet rebuild (R22); 0 NON_MATCHING (G4).
6. All three metrics reported + Step-D residue map.

Projections (targets, NOT gates): Task 5 ≈ +5.7% distinct-code; campaign → distinct 30.3%→~55–70%, instr-weighted 58.2%→~75–88%.

## Effort/model toggle map (R26/R27 — prompt + WAIT at every boundary)

On approval → `/model opus` + `/effort xHigh` (Tasks 0–4; ALL Fable5 via `Agent(model:fable)`). Task 5/6/8 waves → `/effort ultracode`. Task 7 launches + between-wave synthesis → `/effort max`. Task 12 → Max. Non-obvious debugging → Max.

## Blockers

*(none)*

## Log

- **2026-07-11 (session 1, Task 2):** Built `tools/family_hseq.py` (full-frontier h_seq survey) + the shared word-diff classifier in `family_remap.py` (PURE/IMM/STRUCT, register-drift aware). Reproduces the fleet metrics + the 663/186/1.85M tail cross-check exactly; classification matches the Plan-agent table; 581 substantial target families / 3.22M templatable ins, 345 matched-sibling families / 1.14M ins = the zero-crack corpus. `docs/family-hseq.md` committed. Committed.
- **2026-07-11 (session 1, Task 1):** Extended `reloc_targets` for the add/addu indexed-global idiom (the "reach-1 tail" was largely this tracker blind spot, not unique code — decision-log + cookbook §40b). `symbol_map`/`remap` gained backward-compatible `to_addr` (cross-address T2b) + `imm_map` hook; sequential→single-pass substitution (fixes the latent chained-rename bug). norm_stream/h_norm untouched. V0 (22/22 regression, 15/15 fix vs splat .s) + V1 (160 pairs, 0 regressions) both green. Committed.
- **2026-07-11 (session 1, planning):** Phase Start (Tier 1, Fable5+Max+plan-mode). Megaplan analyzed; survey reproduced from sigs+src (R14) — fleet metrics match PhaseEnd_25 exactly; 186-not-986 substantial-family correction; #2 family is cross-address; 93 matched-sibling families found (0.51M ins). Tooling recon (Explore) + design pressure-test (Plan agent) → **the reloc-tracker blind-spot discovery** (addu-preserves-hi; 890×121 family is PURE reloc; 63-fam zero-crack corpus; sequential-substitution latent bug). Drew's gate-1 decisions: carried queue → end of phase; structural milestone. Plan approved; task list built (R28). Task 0 complete with this commit.

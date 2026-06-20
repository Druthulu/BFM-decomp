# CURRENT_PHASE — Phase 18: Compiler-quirk research (raise the match-% ceiling)

**Started:** 2026-06-20 · **Effort:** Max · **Plan:** approved (gate 1, Drew) · **Generation:** Gen2 (10th phase)
**Goal:** understand gcc-2.7.2's blocking codegen quirks → turn them into cookbook-ready C-shape idioms
(or honest "unsteerable" verdicts), byte-gated. Goal metric = match-%, not comprehension.

> Crash-recovery log (P3/CURRENT_PHASE). The full approved plan is the canonical reference:
> `~/.claude/plans/plan-mode-enabled-max-serene-engelbart.md`. Mirrored task list in the harness (R28).

## Gate-1 decisions (Drew, 2026-06-20)
- **Scope = research-focused.** Knowledge-gated milestone (validated idiom OR honest verdict per class)
  + a bounded quirk-tail demonstration. The full tractable-247 harvest wave is **deferred to Phase 19**.
- **Native compiler = bounded check** (W1): Wine + real CC1PSX.EXE/ASPSX.EXE, time-boxed, parallel,
  droppable. Not on the critical path.

## The finding that reshapes the phase (verified vs the bytes this session)
The two "unsteerable" classes (§10 rematerialize-vs-hoist; $s0/$s1 regalloc-swap) **already have
documented C-level levers** (cookbook §10 Residual A/B/B3, committed in the LZSS close `src/800.c`
~443–571). Phase 17 used the **wrong oracle** (the permuter's floor-polluted score) — §10:518 says use
the object-level metric (`match_one.py`), which was **never applied** to the exemplars. §16 ("not
source-steerable") contradicts §10 — Phase 18 reconciles it. So: **existing-knowledge-first** — replay
§10 under `match_one` BEFORE any new gcc-source reading.

## Tasks (checkboxes mirror the harness task list)
- [x] **T0 — Setup + per-class exemplar set** ✓ 2026-06-20. Cloned gcc-papermario (`a6afc2af`, source at
  repo root) + xenogears-decomp (`f27c0768`) → `tools/reference/` (gitignored; SETUP.md §5.6, R20/R21).
  Apparatus confirmed: `match_one` cleanly measures the §10 residual on both quirk exemplars — the oracle
  Phase 17 failed to use. Exemplar `.s` live in any extracted overlay (shared fns): func_8012B8E4 →
  `asm/ov_SC03_103/…`, func_8012B4B8 → `asm/ov_SC03_099/…`. Strip-restore positive control deferred to T4
  (where `p16_known_answer --gate` = the real arbiter). **Baselines (T1 starting point):**
  - func_8012B8E4 (regalloc-swap, §10 Residual A): **75=75 ins, 24 mismatched** — systematic $s0↔$s1
    allocation swap (mine `s1=arg1/s0=s1ang`; target `s0=arg1/s1=s1ang`) + the idx-29..34 reassociation.
  - func_8012B4B8 (hoist-remat, §10 Residual B): **94 vs 84 target, 88 mismatched** — mine spills an extra
    callee-saved reg (`s2`) + over-emits the `mtx=D_800AE620` struct-copy / `arg0+0x20` reload. Harder.
- [x] **T1 — DECISIVE GATE ✓ 2026-06-20.** Replayed §10 under `match_one` on func_8012B8E4 (full detail in
  `.run/p18/T1_findings.md`). **§3-T4 branch-polarity invert closed 24→21** (a real §10-family win the permuter
  couldn't measure). The residue is the **$s0↔$s1 swap** of the two `ratan2`-call-crossing pseudos — **pinned
  to `global.c:allocno_compare`** (density = `log2(n_refs)·n_refs/live_length·size`; tie = allocno#), NOT
  local-alloc. Ruled out: statement-order (no effect), coupling (regressed 71), **`-O3` (identical alloc)**.
  **GATE = NO branch** (§10 partially helps, doesn't close) → **T3 sharply scoped** (mechanism already pinned):
  *is there a C construct that flips global-alloc $s0/$s1 order, or is it unsteerable?* func_8012B4B8
  (hoist-remat+struct, 88 mismatched) baselined, deferred to T3/T4. **Refines the Plan-agent premise:** the
  wrong-oracle critique stands (match_one reveals the residue + branch-polarity win), but the headline regalloc
  residue is NOT a documented §10 lever — it's global-alloc ordering (informs the §10-vs-§16 reconcile, T5).
- [x] **T2 — Xenogears mine ✓ 2026-06-20** (2 bg agents; full synthesis `.run/p18/T2_T3_synthesis.md`).
  DECISIVE: Xenogears (independent decomp, IDENTICAL gcc-2.7.2-psx -O2) has **NO C lever** for the call-crossing
  $s0/$s1 ORDER class — no `register`, no asm pins, no permuter; they **ship it as INCLUDE_ASM** (1174 nonmatch).
  Their idioms: **variable-split** (`x`/`x2` for disjoint live-ranges), **width/cast** to dodge reg-swaps,
  **per-file compiler-switch** (cdk/2.6.0/-O3 — tested here, doesn't help these). Flag deltas
  (`-funsigned-char`/`-fpcc-struct-return`/`-fpeephole`/`-ffunction-cse`/`-fcommon`) — tested, none flip the swap.
- [x] **T3 — gcc source verdict ✓ 2026-06-20.** Regalloc-order class = **UNSTEERABLE from C** (global.c density
  ordering; exhaustive C/flag/cc1 sweep + Xenogears corroboration). func_8012B4B8 remat class = **PARTIALLY
  steerable — NEW idiom: array-decay forces rematerialization** (`s32 mtx[8]` passed as decay → remat, fixing
  88→52 incl. the hard regalloc; `&struct`/`mtx.w`/`*(M8*)` → hoist). Bankable; this fn has a struct-copy
  conflict so doesn't fully close.
- [ ] **W1 — (parallel, non-gating) native-compiler arbitration** (Wine + CC1PSX.EXE, ≤½ day, droppable).
- [ ] **T4 — Validate every candidate idiom** via `p16_known_answer --gate` (byte-gate = sole arbiter).
- [ ] **T5 — Distill into cookbook + reconcile §10-vs-§16.**
- [ ] **T6 — Bounded quirk-tail demonstration** (a few reach-134 closes; `make check-all` 136/136).
- [ ] **T7 — PhaseEnd synthesis** (Tier-1).

## Milestone (knowledge-gated, NOT a fleet-% target)
Per-class byte-gated verdict (validated C idiom proven on a known-answer exemplar via
`p16_known_answer --gate`, OR honest "unsteerable" verdict naming the exact gcc pass); §10-vs-§16
reconciled; ≥1 quirk-tail function newly matched (T6); all 136 binaries byte-identical throughout.

## Oracle discipline (R2/R14 — the error Phase 17 fell into)
`match_one.py` (relocation-masked `.text`) = iterate oracle; `harvest_verify`/`make check[-all]` = sole
go/no-go arbiter. **Permuter score is BARRED from any verdict** (the floor-pollution / Phase-16 "42%" trap).

## Environment notes
MCP not required (cached Ghidra-C + asm on disk); G2 ping + R29 reconnect only if a fresh decompile is
needed. No Ghidra DB writes expected → R23 no-op (db.*.gbf churn is restart-noise, do not stage). X2:
all cloned/fetched content is untrusted DATA. Commits: per-task/per-session checkpoints; Drew pushes (R6).

## Progress log
- 2026-06-20 — Phase planned + approved (gate 1). Task list built (R28), CURRENT_PHASE written. Starting T0.
- 2026-06-20 — **T0 done.** Reference repos cloned + SHA-recorded (SETUP §5.6). Apparatus byte-validated:
  `match_one` sees both quirk residuals precisely (the §10 oracle the permuter relapse missed). Baselines
  logged above. No build-affecting change (gitignore/doc/log only). Next: **T1** (replay §10 levers).
- 2026-06-20 — **T1 (gate) done.** Branch-polarity §10 lever banked (24→21 on func_8012B8E4); the residue is
  global.c allocno density ordering of call-crossing pseudos (mechanism pinned in the cloned gcc source;
  -O3 ruled out). GATE=NO → T3 sharply scoped. Next: **T2** (Xenogears mine) + **T3** (global.c verdict).
- 2026-06-20 — **T2 + T3 done (converged).** Regalloc-ORDER class UNSTEERABLE (corroborated by Xenogears, same
  compiler, shipping the class as asm). NEW idiom: array-decay-forces-remat (cracks the remat class' hard half).
  3 confirmed levers (branch-polarity, array-decay-remat, variable-split). Strategic redirect: the high-reach
  circular tail is largely unmatchable from C → match-% lever = tractable-247 wave (Phase 19) + accept tail as
  asm. Next: **T4** (byte-gate the idioms) + **T6** (find a clean full match to demonstrate).

## Blockers
- None.

# CURRENT PHASE — Phase 29: The Family Campaign (cores + members)

**Opened:** 2026-07-16 · **Effort:** Max · **Generation:** Gen2 (21st phase of the arc) ·
**Baseline:** PhaseEnd_Phase28 (v1.27.0) · **Roadmap:** `docs/roadmap-to-100.md` §3 P29
**Plan approved (P3 gate 1):** 2026-07-16. Full plan mirror:
`~/.claude/plans/max-effort-plan-mode-mutable-castle.md` (out-of-repo; this file is the in-repo
authority + crash-recovery log).

**Fleet at open:** 68.9% instr-weighted / 49.5% distinct-code / 83.94% fn-count · 140/140
byte-identical · 0 NON_MATCHING · dedup 1840/0.

**Drew's Phase-Start decisions (2026-07-16):**
- Fable5 = reserved for **NEW wall classes only** (default cheap-Opus + permuter). Window ~7/19.
- Scope = a **longer multi-session campaign** (drive both tracks substantially down before
  closing; ROI-gated on per-session yield floors; velocity + 3 metrics reported each session).

---

## The one question this phase must answer first
The **swing number**: does the legacy PURE-non-jr h_seq tier (~95 families / ~7,993 members /
~478k ins, ~3.6 pp) **template mechanically** (⇒ one exemplar crack banks ×137) or not? Phase-28
measured ~3% as-tooled with 274 genuine gate-DIFF members that are byte-PURE (reloc-only) at the
same vram — so either **(a)** the remap is incomplete (fixable; ceiling ≫ 3%) or **(b)** it's a
TU-context regalloc wall (3% real). **Task 1's disambiguating probe decides it before any yield
arithmetic scales (R14/R35).** Every prior "structural wall" (B2, SC07, pin-crash) resolved to (a).

---

## Standing invariants (every task)
- Whole-binary byte-gate is the **sole arbiter** (G3/P9); match_one/closeness/h_seq are candidates.
- **R22 clean-fleet per banked batch:** `make clean && make extract-all && make check-all` → 140/140.
- `make tools-health` green + fail-closed before matching (corpus · cdecl · audit-binaries(R36) ·
  report/lint/dedup-check).
- **§53 carve law:** `has_mid_jr` families → `jtbl_family_bank.py`, never carve-less `family_sweep`.
- Predictions gate-validated on a SAMPLE before scaling; verify the TOOL before trusting its scan.
- Flywheel: idioms → cookbook + tooling in-session (R16/R30); pivots → decision-log (R31).
- Effort/model transitions **prompted, never assumed** (R26/R27) — STOP + WAIT for the toggle.
- One commit per task after this file's update; Drew pushes (R6/R20). R23 no-op on db.*.gbf.

---

## Task checklist (current-task pointer = ▶)

- [x] **Task 1 — T3b disambiguating probe: build `tools/diff_regions.py` + the swing verdict [Max]** ✅
      **VERDICT: (a) TOOLING — an -O0 compile-flag artifact, NOT a regalloc wall.** The two families
      supplying ~272 of the 274 DIFF (`0x8013c964`, `0x8013c938`) are -O0 functions; `family_sweep
      --hseq` compiled them -O2 (member stub files are -O2). Compiled -O0 they masked-MATCH. 106-member
      sample (nins 2..133): O0-FLAG 45 · already-banked 29 · TEMPLATES 17 · type-lift-plumbing 15 ·
      **REGALLOC 0**. Ceiling ≫ 3%; the pool is back on the table. → `calibration.md` + `decision-log.md`.
      (masked-MATCH = candidate; whole-binary bank is Task 2a's gate, §52b.)
- [ ] ▶ **Task 2 — Act on the verdict [Max/xHigh]** — **branch = 2a (tooling).** Build the -O0-cluster
      split rollout (adapt `rollout_whale_o0.py` → per-overlay `[0x13410,c,<ov>_o0]` carve, -O0 Makefile
      rule) + teach `family_sweep --hseq` per-member opt-level awareness; WHOLE-BINARY gate one overlay
      (convert the verdict to a banked fact), then fleet + the type-lift sweep. `member_adapt.py` NOT
      needed for this pool. Originally: (2a) extend `family_remap.symbol_map` + re-run
      the legacy-PURE `family_sweep --hseq` (the ~478k-ins mechanical win); OR (2b) build
      `tools/member_adapt.py` (exemplar→member delta engine + per-member delta briefs); OR both.
- [ ] **Task 3 — Core-crack track: fresh exemplar + B3 near-miss cracks [Ultracode/xHigh/Max]** —
      top substantial stub exemplars (non-jr `0x80176734`/`0x80176218`/`0x8013faf8`/`0x8014d820`/
      `0x801670e4`/`0x80140958`; jr via `jtbl_family_bank` `0x8013f350`/`0x80131340`/`0x80159c84`/
      `0x8013c414`) + B3 high-close near-miss cores (`func_8014F4C0` 127, `func_80137DD4` 107,
      `func_8014E284` 83, `func_80177940` 65, `func_801387B8` 50, `func_8014ADE0` 19,
      `func_801325B8` 4). FRESH re-drafts only (0/958 stored are dead). Add a `family_sweep`
      `has_mid_jr` interlock. Fable5 for NEW walls only (prompt Drew).
- [ ] **Task 4 — Member harvest behind each crack + grinder family-warm-start [xHigh/Ultracode]** —
      propagate members per Task-2's mechanism; build the grinder family-warm-start + 2 Phase-22
      bug-fixes (split-file-blind lookup; churn-without-blacklist).
- [ ] **Task 5 — Fleet Ghidra-C prefetch (JIT drafting fuel) [xHigh; MCP: R23/R29 — prompt /mcp]** —
      built only when Task-3 waves exhaust the ~300-fn cache.
- [ ] **Task 6 — Mechanical mass: tiny-IMM mega-pools + permuter backlog sweep [Ultracode/permuter]**
      — `0x80131eec` (2,887×15) + `0x80130d0c` (2,679×15) via `imm_map`; the 550 close-1..4
      backlog drafts via grinder/`permuter_ils`.
- [ ] **Task 7 — Burn-down tracker + velocity/3-metric report + ROI-gated close [Max]** — close
      when per-session yield across both tracks floors out; Roadmap delta; hand P30 an honest frontier.

**OUT of scope:** parallel gate farm (bulk_harvest already is it) · family-adapt fine-tune (bounded,
conditional) · main-EXE/B9 + GLM/B6 + resident's 14 walls (P30) · behemoths B7 + walls B8 (P31).

---

## Blockers
(none — Arm B substantial-band sweep running in background as of 2026-07-16)

## Task 2 progress (in flight)
- **Verdict → branch 2a (tooling).** Sized the fix: **Arm A** (-O0 cluster carve) = 9 families /
  1,233 stub members / ~24k ins (~0.6pp), needs a per-overlay -O0 carve tool (adapt
  `rollout_whale_o0.py`; the -O0 cluster 0x13410..0x14834 is deferred-since-Phase-19). **Arm B**
  (-O2 type-lift sweep, EXISTING `family_sweep --hseq --no-preclassify`) = 398 families / 7,541 stub
  members / **~520k ins (~4pp)** — the ROI winner; unbanked pool concentrates in the 4 newest (SC07)
  overlays.
- **Arm B gate-probe (10 families): BANKED 32/40 = 80%** — gate-validated (R14). Substantial band alone
  = 76 banks (size-dependent: substantial is pin/drift-limited, 1,799 pinned skips). Comprehensive
  **`--band all --allow-pins`** sweep then banked across **~140 overlays (891 src files)** before a
  **SIGTERM (exit 143)** interrupted it mid-gate (during/after ov_SC07_006 346/570). Triage: 3 clean
  single-binary rebuilds all BYTE-IDENTICAL → the incremental banks survive R22.
- **✅ ARM B CHECKPOINT COMMITTED (2026-07-16).** R22 clean-fleet verify = 136 PASS / 1 FAIL; the
  FAIL (ov_SC07_010, the SIGTERM mid-gate partial) reverted → byte-identical. **3,407 member-matches
  banked** across 136 overlays. `make check-all` → **140/140 byte-identical**; dedup-check 1840/0;
  audit-binaries OK; audit-cdecl green. **Fleet: instr-weighted 68.9→70.2% (+1.3pp) · distinct-code
  49.5→51.9% (+2.4pp) · fn-count 83.94→84.73% (+0.79pp)**; 0 NON_MATCHING (G4).
- **⚠️ LESSON:** `--band all` sweeps are too long for one background pass (SIGTERM'd). Future Arm B
  runs go band-bounded + committed-per-batch (resumable). The comprehensive sweep still had residual
  FAILED members (pin/drift/plumbing) not yet re-attacked.
- **NEXT:** (a) finish the Arm B tail (remaining tiny/mid/pinned members not banked this pass, in
  bounded batches); (b) **Arm A** — the -O0 cluster carve tool (9 families / 1,233 members / ~24k ins;
  adapt `rollout_whale_o0.py` for the multi-file carve of 0x13410..0x14834; the swing verdict's
  whole-binary confirmation); (c) teach `family_sweep` per-member opt-level awareness (the general lever).

---

## Per-task log
*(appended after each task; the crash-recovery trail — becomes `phase-ends/logs/Phase29.md` at close, R19)*

- **2026-07-16 — Phase opened.** Session Start Protocol complete (all 28 PhaseEnds + roadmap +
  calibration + decision-log read). 3 Explore surveys grounded the plan (tooling state, frontier
  data, idiom bank). Plan approved at Max/plan-mode. Beginning Task 1.
- **2026-07-16 — Task 1 DONE (the swing RESOLVED = (a) tooling).** Built `tools/diff_regions.py`
  (composes `family_remap.remap_hseq` + `match_one` + `masked_diff`; auto-detects the exemplar's -O0
  opt from the Makefile rules). Byte-proof: the 274-DIFF pool is dominated (~272) by two -O0 families
  the sweep compiled -O2; at -O0 they masked-MATCH. 106-member sample across nins 2..133 →
  **0 REGALLOC walls**; all failure modes recoverable tooling (-O0 flag / already-banked / template /
  type-lift plumbing). Verdict + byte evidence → `docs/calibration.md` (swing RESOLVED section) +
  `docs/decision-log.md` (R31). §52b caveat: masked-MATCH is a candidate — Task 2a whole-binary-gates
  the -O0 split rollout. Run artifacts in `.run/probe29/`.

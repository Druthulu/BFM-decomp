# CURRENT PHASE — Phase 31: The Frontier Atlas & Wide-Tolerance Campaign

**Started:** 2026-08-14 · **Plan approved:** 2026-08-14 (gate 1; Drew) · **Effort doctrine:** xHigh default / Max deep (T5, T7, synthesis) / Ultracode waves (R26/R27 prompts) / Fable-tier only for new wall classes.
**Approved plan:** `/home/musashi/.claude/plans/fable-5-set-max-goofy-seahorse.md` (the full design; this file is the crash-recovery log).
**Approval also ratified R37 (probe before costing), R38 (read recorded failure verdicts first), R39 (negative-control new refusal-checks) — now binding.**

## The re-charter (one paragraph)

Instead of roadmap-v2 P31's per-function grind, Phase 31 organizes the 12,059 remaining stubs (main 1,041 · resident 14 · ov 9,832 · md 1,179) into **crack groups**: a deterministic per-function feature layer + multi-tier similarity atlas (li-normalized exact tier, seed sweep vs the 2,719 matched skeletons, calibrated warm tier for the 3,238-unit cold tail + main, kNN neighborhood graph), evidence-joined to a lever label per group; plus **widened mechanical lanes** (LEN-tolerant aligned remap with a fully-mechanical LI class, §172b EXTPAIR/SELECT detectors + routing, PLUMBING campaign, permuter cluster warm-start, weak-seed cards); then a **campaign loop to ceiling** — deterministic $0 lanes first, agents only for exemplars, velocity-ledgered, closed on measured decay. Milestone shape = P30 (campaign to ceiling; every remaining stub on a named ledger at close). Main fully included from day one.

## Task checklist

- [x] **T0 — Pivot log + freshness + hygiene** — DONE 2026-08-14. (xHigh)
- [ ] **T1 — Integration quick-bank sweep**: MATCH-75 + fix20/match108/immfix slates (re-filtered, fresh match_one) via recover_integration; backlog close=0 re-gate. (xHigh)
- [ ] **T2 — References**: PsyQ Track-1 `SAMPLE/` extraction → tools/reference/psyq-sdk/; gcc-2.7.2 calls.c + caller-save.c; SETUP rows; idiom-notes seed. (xHigh)
- [ ] **T3 — Main enablement**: sig-main (seed-ends + s_ins_count + fatal word cross-check); family_remap main streams (0x8000F800). (xHigh)
- [ ] **T4 — atlas_features.py**: per-fn features memoized per h_exact → .run/feat.<bin>.jsonl ×213; join/determinism/cross-check verifies. (xHigh)
- [ ] **T5 — atlas.py**: --calibrate → survey (T1.5/T3/T4/T5/tiny + main join + levers) → --targets → make atlas; five assertions; docs/frontier-atlas.md. (Max)
- [ ] **T6 — PLUMBING campaign**: plumbing_groups.py + recover_integration --stages cast-callees,tu-scope; 20-fn probe then sweep. (xHigh)
- [ ] **T7 — LEN-LI mechanical lane**: family_align.py + adapt_autodraft.py; NC-1/2/3; 1-card probe → 27-card pile. (Max)
- [ ] **T8 — LEN+N lane**: len_tells.py + match_one --emit-streams + lenmiss_route.py; per-class probes; redraft reclassification. (xHigh)
- [ ] **T9 — Warmstart + weak-cards**: warmstart.py + grinder admission widening + --weak-cards; NCs + probes. (xHigh)
- [ ] **T10+ — Campaign loop to ceiling** (repeating sessions; velocity ledger; close on measured decay). (Ultracode waves / xHigh orchestration / Fable new-walls)
- [ ] **Tclose — PhaseEnd** (gate 2). (Max)

## Standing verification (every task)
R22 clean-fleet **213/213** after every banked batch · tools-health green · 0 NON_MATCHING (G4) · dedup-check 0 failed · R32 coverage assertions on every new scanner · R39 negative controls on every refusal check · R37 probes before pricing · R38 ledgers before experiments · commit per task (task + this log in the same commit; Drew pushes).

## Progress log

- 2026-08-14 — Phase planned and approved (3 Explore + 2 Plan agents; full design in the plan file). Task list built (harness tasks #1–#12). T0 started.
- 2026-08-14 — **T0 COMPLETE.** (1) R31 decision-log entry (the re-charter WHY + R37–R39 ratification). (2) `harvest_verify.py` import guard: a bare import now RAISES instead of running a gate (verified both directions; CLI behavior unchanged). (3) **Resident ±1 RESOLVED + FIXED**: `--bootstrap`'s linear partition had fused the +0 data word with `func_800CEDFC` (row `0x800CEDF8` nins=18) and dropped `func_800D33E0` past a glued tail — the true denominator is **145** (progress was right, the sig wrong). `sig-resident` now ELF-seeds (S45 pattern: unique 4-aligned T-symbol addrs inside the `resident_TEXT_START/END` markers → exactly 145; bootstrap fresh-clone fallback). All three oracles now agree (sig 145 · corpus matched 131 · progress byte-ident 131); `audit-corpus` 0 PHANTOM + 0 TRUNCATED. (4) Family maps regenerated at HEAD `commit:2161`: **11,025 open non-main members = 12,059 − main's 1,034 EXACT** (the stale map's 102 phantoms cleared); cousins totals now A-prop 1,125 / seeded 1,293 / cousin-multi 5,373 / cold 3,234 inst; adapt cards 704, aprop cards **204 (full emission)**. (5) **Main fuel gap is DEAD**: 2,001/2,002 main stubs have cached Ghidra-C (only `func_80049600` missing) — the roadmap's "0/2,096" note was stale. (6) `make tools-health` → OK (dedup 2,063/0; C1 254,521/254,521; audit-digest confirms the fleet digest; resident fix moved instr num+denom by the same +9).

## Blockers
(none)

## 🛑 SESSION CHECKPOINT
T0 committed; NEXT = T1 (integration quick-bank sweep: MATCH-75 + fix20/match108/immfix slates re-filtered via corpus.stubs + fresh match_one → recover_integration per binary; backlog close=0 re-gate last; R22 213/213 after banks). If resuming fresh: read the approved plan file above, then start T1.

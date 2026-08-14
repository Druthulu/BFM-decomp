# CURRENT PHASE — Phase 31: The Frontier Atlas & Wide-Tolerance Campaign

**Started:** 2026-08-14 · **Plan approved:** 2026-08-14 (gate 1; Drew) · **Effort doctrine:** xHigh default / Max deep (T5, T7, synthesis) / Ultracode waves (R26/R27 prompts) / Fable-tier only for new wall classes.
**Approved plan:** `/home/musashi/.claude/plans/fable-5-set-max-goofy-seahorse.md` (the full design; this file is the crash-recovery log).
**Approval also ratified R37 (probe before costing), R38 (read recorded failure verdicts first), R39 (negative-control new refusal-checks) — now binding.**

## The re-charter (one paragraph)

Instead of roadmap-v2 P31's per-function grind, Phase 31 organizes the 12,059 remaining stubs (main 1,041 · resident 14 · ov 9,832 · md 1,179) into **crack groups**: a deterministic per-function feature layer + multi-tier similarity atlas (li-normalized exact tier, seed sweep vs the 2,719 matched skeletons, calibrated warm tier for the 3,238-unit cold tail + main, kNN neighborhood graph), evidence-joined to a lever label per group; plus **widened mechanical lanes** (LEN-tolerant aligned remap with a fully-mechanical LI class, §172b EXTPAIR/SELECT detectors + routing, PLUMBING campaign, permuter cluster warm-start, weak-seed cards); then a **campaign loop to ceiling** — deterministic $0 lanes first, agents only for exemplars, velocity-ledgered, closed on measured decay. Milestone shape = P30 (campaign to ceiling; every remaining stub on a named ledger at close). Main fully included from day one.

## Task checklist

- [x] **T0 — Pivot log + freshness + hygiene** — DONE 2026-08-14. (xHigh)
- [x] **T1 — Integration quick-bank sweep** — DONE 2026-08-14 (pending final R22 log line). **8 banked, 0 agent tokens.** (xHigh)
- [x] **T2 — References** — DONE 2026-08-14. (xHigh)
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

- 2026-08-14 — **T1 COMPLETE: 8 banked for 0 agent tokens.** R38-first: partitioned the MATCH-108 pile against current stubs (75 still open) and against the S50 gate history (62 gated-and-failed with verdicts · 13 never-gated). The lanes and their measured outcomes:
  - **Never-gated 13** → gate_lane: 0/13, but the verdicts decomposed to 11× `undefined reference to D_*` = the §171 stale-seed-symbol class. **Extended `aprop_symfix` with STALE-DELTA** (n:n uniform-delta rebase; R39 synthetic + snapshot NCs, zero false positives; the delta test even refused a pair my hand-check wrongly accepted) → 4 rebased, **4/4 banked** (`func_8016BCC0`, `func_8017F1C8`, `func_80186BD8`, `func_80186BF8`). Cookbook **§171-D** written in-session.
  - **SELF-decl PLUMBING 7** → `recover_integration --stages demacroize --max-tier binary`: **4/7 banked** (`func_80139BE0`, `func_8014ED28`, `func_80161D88`, `func_801659DC`); 3 stay near.
  - **Stored-draft re-gates** (no-verdict 7 + close=0 8 + diff 1 + 9 STALE→clean world-motion drafts): **0/23-ish banked** — the ~8% A10 stored-verdict law held again; all re-verdicted fresh.
  - **Handed forward with fresh classifications**: CALLEE-decl 15 + CC1-FAIL 14 → T6 (cast-callees/tu-scope stages); UNDEF-DATA/OTHER 9 → the §171b-1 data-definition carry (T7/T8); md CARVE-REFUSED 8 → campaign side-quest ledger. immfix pile: fully consumed (0 open). fix20: 19/20 consumed in S50.
  - Tool fixes landed: `gate_lane` propagate-commit tag now derives from GATE_PHASE (was hardcoded phase-30 S49).
  - Rate lesson for the velocity ledger: fresh-fix lanes (STALE-DELTA 4/4, demacroize 4/7) vastly outperform blind stored re-gates (0/23) — the campaign loop's L2 ordering is confirmed by measurement.

- 2026-08-14 — **T2 COMPLETE (references).** (1) **PsyQ dev-CD extracted**: walked the on-disk Track-1 image (MODE2/2352) with the frozen `tools/bfm_extract/iso9660.py` (R33 — no new extractor; walker = iter_directory/read_extent with out-of-range extents skipped) → `tools/reference/psyq-sdk/` (gitignored): 2,374 files / 231.6 MB, **400 C sources (373 in PSX/SAMPLE/** across CD/GRAPHICS/SOUND/MODULE/CMPLR/…); only 7 out-of-track `.DA` audio skipped. (2) **Provenance find**: `GNU/SNGNUVER.TXT` = SN Systems' gcc build history (`2.7.2.SN32.3.7.0002`, 14.5.97) with per-build changelog of SN's patches vs vanilla — only `UNROLL.C` (parameterised max unroll insns) is codegen-relevant; recorded in the idiom notes as the first-look suspect if a loop-unroll residual ever defies the vanilla model. (3) **gcc-2.7.2 reference completed**: +6 files from GNU ftp (`calls.c` + `caller-save.c` — both cited by §172's producer model, previously missing — + integrate/optabs/varasm/recog), tarball sha256 `7cd8bce5…` recorded. (4) `docs/psyq-sample-idioms.md` seeded (inventory, provenance, first style conventions, the lane hook); SETUP §5.6 rows added (R21).

## Blockers
(none)

## 🛑 SESSION CHECKPOINT
T0+T1 done (commits through the t6-recover gates; T1 close commit pending the R22 run). NEXT = T2 (reference expansion: PsyQ Track-1 SAMPLE/ extraction → tools/reference/psyq-sdk/; gcc-2.7.2 calls.c + caller-save.c fetch; SETUP rows; idiom-notes seed). If resuming fresh: read the approved plan file above; check .run/t1_r22_check.log for the fleet verdict; then start T2.

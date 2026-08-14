# PhaseEnd — Phase 30 The Recovery & Concentration Campaign (overlays to their ceiling)
**Date:** 2026-08-14 · **Project Version:** 1.29.0 · **Phase Status:** Complete

## Build Log

**The phase in one line:** the overlay fleet was driven from 87.5% to **95.3% instruction-weighted**
(78.0→**90.0%** distinct, 92.00→**96.68%** fn-count) across 25 sessions (S26–S50) and 947 commits,
while the *denominator itself* grew from 140 to **213 byte-identical binaries** (the in-phase disc
audit + module-fleet onboarding), open stubs fell **28,296 → 12,059**, and the matching machinery
crossed from agent-driven to majority **zero-token mechanical** banking.

**Files created/changed and complete — do not recreate** (category summaries; the per-session
detail is `phase-ends/logs/Phase30.md`, on-demand per R19):

- `src/` — ~16,200 stub instances replaced with byte-verified C across 211 overlays + modules;
  dedup registry 1,886 → **2,061 groups / 0 failures** (`config/dedup.us.yaml`).
- **Matching engine tools (new, all in `tools/`):** `o0_subsplit.py` (±O0 region carving; 277 -O0
  TUs), `prefetch_fleet.py` + Ghidra-C cache (`.run/ghidra_c/`), `family_cousins.py` (the §168
  similarity tier + adapt/A-prop card lanes), `gate_lane.py` (the §169 wave-gate contract),
  `aprop_symfix.py` (§171 stale-seed-symbol oracle), `aprop_autodraft.py` + `draft_prechecks.py`
  (§171a/b zero-token mechanical drafts), `cc1_dumps.sh` (§172 RTL-dump instrument),
  `jtbl_family_bank`/`family_sweep --hseq` hardening, permuter ILS warm-restart in `grinder.py`.
- **Instrument repairs (T0):** `gate_stage.py` stage-0 + scaled/caught propagation timeout +
  arity journal; `rtu_match.py` real-error surfacing; `family_hseq`/`progress` digest
  reconciliation (scope-stamped); backlog scanner deleted (R33); 21-file absolute-include fix.
- **Fleet expansion (S41–S45):** the definitive disc audit (partition-asserted, R32-gated via
  `make audit-binaries`/`audit-text-sources`); +73 code-bearing payloads onboarded emulator-free
  (static-address derivation); the L3 emulator measurement tour; per-binary SHA gates for all 213.
- **Knowledge base:** cookbook **§122–§172b** (~50 sections) including the §31→§172 idiom arc, the
  §168/§169/§170/§171 lane laws, and the §172/§172a/§172b compiler-internals models;
  `docs/frontier-p30.md`; `docs/family-cousins.md`; `docs/decision-log.md` grew by ~12 entries
  (R31); `docs/accelerators.md` seeded; `tools/cookbook_index.py` (self-asserting, in
  tools-health).
- `docs/SETUP.md` — rows for every tool above (R21).

**Tools/packages installed:** none external — all in-repo tooling (R3).

**Verification results (literal, at close):**
- `make clean && make extract-all && make check-all` → **extract-all: 212 extracted, 0 failed of
  212 (+ main, serial)**; **check-all: 213 passed, 0 failed of 213** (R22 run 5× in S50 alone,
  213/213 every time; `.run/r22_s50f.log` EXIT=0).
- `make tools-health` → OK (sigs fresh; corpus+resident, cdecl, binaries, report lint+dedup,
  cookbook-index all green; fail-closed).
- dedup-check: **2,061 validated, 0 failed**; C1 coverage 254,517/254,517 members signed.
- Fleet digest (`docs/progress.fleet.md`, audit-digest-asserted): instr 12,885,596/13,523,856 =
  **95.3%** · distinct 5,268,903/5,851,963 = **90.0%** · fn-count 351,097/363,163 = **96.68%** ·
  INCLUDE_ASM stubs **12,059** · NON_MATCHING 0 in any default build (G4).

**Milestone achieved:** the phase milestone — *"overlays at their measured ceiling: ≥95% instr
fleet, or every remaining overlay stub on a named wall/behemoth/queue ledger — byte-identical
throughout"* — is met on BOTH clauses: **95.3% ≥ 95%** with **213/213** byte-identical (the
original 140 plus the 73 onboarded in-phase), AND every remaining stub is on a named ledger
(`.run/family_hseq.json` / `family_cousins.json` frontier maps, `.run/backlog.jsonl` +
`docs/backlog.md` near-miss ledger, the §172 wall dossier, the P32 giant/behemoth list).

**Next:** Phase 31 — plan fresh from `docs/roadmap-to-100.md` v2 + this file's Roadmap delta.
Start with the Phase Start Protocol in a fresh session (no plan is pre-committed here, per P8).

## Roadmap delta (feeds the P31 plan)

- **Overlays are at their measured ceiling for wave-scale work.** What remains in overlay-land:
  the LEN+N draft pile (~400 stored drafts where the target is LONGER — §172b swaprepeat/extend
  candidates), the A-prop mechanical reaches (PURE 437 members/37k ins for `aprop_autodraft`'s
  data/jtbl extension; IMM 275/8.8k half-resolvable; STRUCT 238/4.3k agent-shaped), 13
  ambiguous-symbol stored drafts, and the md CARVE-REFUSED class (carve-tool extension).
- **main (SLUS EXE) is now the single largest coherent mass:** 79,510 weighted ins at 0.5%,
  structurally barren of family leverage (§168 holds), Ghidra sig regenerated 2026-08-05 —
  the genuine ~490-tok/ins agent tail. P31's core question is main's campaign design.
- **The wall track (P32) is fully provisioned:** func_8017C294 ×16 (§172 mechanism-complete,
  NEAR-2 floor, siege kit banked), the 2 GIANT exemplar walls (close 91/110, 50,094 ins riding),
  the behemoth list, func_8017EE78, and the roadmap-v2 W3-owner gap flagged at T5 remains OPEN —
  assign W3's remainder an owner phase during P31 planning.
- **The zero-token machinery generalizes:** aprop_autodraft + symfix + prechecks + gate_lane is
  a reusable pipeline (measured ~256 members banked for ~0 agent tokens vs ~20M as waves) —
  P31 should route EVERY lane through the deterministic pipeline first, agents last (per the
  offline-tooling-first standing goal).

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| T2 route | "two-file atomic o0b substitution driver" (primary), Arm-A splat research (fallback) | BOTH refuted by probes; shipped `o0_subsplit.py` carve instead (§126) | o0b-append mis-places unless target abuts object END (×1 probe); the `%lo +0x20` premise measured byte-neutral |
| T1 prior | S16 "39%" stored-draft recovery expectation | 16% measured (18/~111) | the 39% was measured on FRESH same-wave drafts; stored backlog is the A10 integration-decayed class |
| T6/T7 execution | ordered wave lists (S1–S5 / S1–S7) | consumed as a measured continuation across S26–S50 with re-ranking by templatable weight; exclusions: 2 GIANT walls + behemoths → P32, main tail → P31, ×2-9 mass + singleton residue → ledgered | the pricing finding (h_exact under-prices family heads ×138) + per-lane ROI verdicts superseded static ordering, approved in-phase (P5d) |
| Fleet denominator | 140 binaries assumed for the phase | 213 by close (+73 onboarded in-phase) | the disc audit found the honest denominator; milestone restated against it a fortiori |
| Milestone wording | "140/140 byte-identical" | 213/213 | same binaries all green plus the new ones; no regression at any point |
| func_8017C294 (T6-adjacent) | crackable frontier head | mechanism-complete WALL (§172, ~240 refutations incl. the first whole-binary-gate run on its NEAR drafts) | the +32 frame bytes need structurally different source with identical bytes; P32 siege kit banked |
| R22 cadence | per banked batch | run 5× in the close session alone; 213/213 every time | fleet-shared writes multiplied late in phase |

## Commit Message
*(for Drew's milestone-close commit)*
```
chore(phase-30): CLOSE — overlays at their measured ceiling (95.3% instr / 90.0% distinct / 96.68% fn, 213/213)

- PhaseEnd_Phase30.md written; CURRENT_PHASE.md archived to phase-ends/logs/Phase30.md (R19)
- 25 sessions (S26–S50), 947 commits, stubs 28,296 -> 12,059, dedup 2,061/0
- milestone met on both clauses: >=95% instr AND every remaining stub on a named ledger
- v1.28.0 -> v1.29.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R37 — Probe before costing** *(proposed at PhaseEnd_Phase29; operated as binding all phase — Drew to RATIFY formally)* | Exercised throughout P30 (the ×1 o0b probe that saved 2,131 builds; the pre-probe rule in T7; the S50 selector probes). |
| **R38 — Read the recorded failure verdicts before designing an experiment** *(proposed; Drew to accept/modify/reject)*: before scoping any measurement, experiment, or "test X to explain failure rate Y", first grep the classified failure ledgers the tools already wrote (`.run/harvest_failed.*.classified.txt`, gate results, autopsy rows) — the answer is frequently already recorded. Extends R35/R37 to the *diagnosis* step. | The S49→S50 A-prop arc: the checkpoint's top-priority "TU-spread test" was already answered three ways by artifacts on disk (`undefined reference to D_80181900` ×11, verbatim); §169 even had the law, unapplied cross-lane. A session's first hours went to a question the tools had answered the night before. |
| **R39 — Negative-control every new refusal-check against the already-succeeded population** *(proposed; Drew to accept/modify/reject)*: a pre-check/selector/filter that refuses work ships only after running it over everything that previously PASSED, requiring zero false positives — a checker that discards good work silently is worse than one that lets a few failures through. | `draft_prechecks.py`'s negative control (all 205 banked drafts) caught two bugs in the checks themselves (C89 `f()` = unspecified params, not zero; a member's own definition read as a self-call) — either would have silently discarded good drafts forever. Same pattern caught aprop_symfix's `local-only` class. |

## PhaseEnd Changelog
v1.28.0 → v1.29.0 — Phase 30 complete: the overlay recovery & concentration campaign. Fleet
87.5→95.3% instr (78.0→90.0 distinct, 92.00→96.68 fn-count) over 25 sessions; denominator
140→213 byte-identical binaries (in-phase disc audit + module onboarding); stubs 28,296→12,059;
dedup 2,061/0. Matching industrialized to majority zero-token mechanical (cards → autodraft →
symfix/prechecks → gate_lane → per-fn propagation). Cookbook §122–§172b; the §172
compiler-internals wall model; main + walls + LEN+N vein handed to P31/P32.

## Plain-English Recap

This phase took the game's hundreds of level files from "mostly translated" to "nearly finished" —
95.3% of all the game's code now rebuilds byte-for-byte from our C source, checked against the
original disc 213 files at a time. Along the way we discovered the disc held 73 more code files
than anyone had counted, added them to the checklist, and beat the target percentage anyway. The
biggest change was HOW the work gets done: at the start, an AI agent hand-translated most
functions; by the end, most conversions were produced by our own deterministic tools for free —
the AI is reserved for the genuinely novel cases. We also went deep into the original 1995
compiler's source code and came back with a field guide to its quirks, which un-stuck 52
functions in one sweep and fully explains the one function that still refuses (a haystack problem
saved for the endgame). What's left: the main executable (the last big untranslated mass), a
short list of named "wall" functions, and a pile of near-misses our new field guide is expected
to chip through.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived to `phase-ends/logs/Phase30.md`. **Both are left
uncommitted for Drew** (R6): review, commit with the message above, and push — exclude the
`ghidra/db.*.gbf` rename churn (R23 noise; no RE writes this session; MCP stopped cleanly with
"Save succeeded"). Then start a **fresh session** for Phase 31 planning. Keep this file forever.

# Phase 25 · T6 — The Crack Curriculum (structural-family endgame)

> **Authored by the Fable5Max T6 session, 2026-07-09**, from the Step-A measured frontier —
> every number below is derived from byte-level probes run this session (artifacts in `.run/t6_*`), not
> prediction. Input package: `docs/phase25-t6-fable-brief.md`. Executor: the T7 session (Opus-Max
> orchestrator + surgical tiers, R27). The whole-binary byte-gate (`harvest_verify`, G3/P9) remains the
> sole arbiter of every bank; every projection below is "probe-verified, gate-pending" until T7 lands it.

## 0) The headline (what the R14 re-verification changed)

The brief's caution was right, but in the OPPOSITE direction: a 5-sample spot-check had suggested the
frontier's "match" claims were inflated. Re-verifying **all 95 stubs** with `match_one` (every draft in
every `.run/drafts-t5*` dir, best-of):

| ground truth | fns | ins | note |
|---|---|---|---|
| **isolation-MATCH (c=0)** | **62** | 6,712 | every "match" claim + ALL 11 batch-2 "walls" + the 3 `_o0` giants verify GENUINE |
| verified near (c=3..274) | 31 | 4,693 | frontier closeness values reproduce exactly |
| no draft yet | 2 | 46 | the tiny `_o0` stragglers (`func_8013BC7C`/24, `func_8013BCDC`/22) |

**65% of the worklist never needed cracking — it needed integration.** The Phase-25 "def-side wall"
decomposed under a 6-iteration probe program (reconcile → splice into the real TU → full
`cpp|cc1|maspsx|as` → relocation-masked byte-compare of the fn inside the TU object) into five
mechanical tool defects and a small genuine residue. `tools/canon_sig_reconcile.py` **v3.1** (this
session) fixes all five (cookbook §41a):

1. scalar-typedef dups now stripped (the `redef:u8` class, 11 fns);
2. canonical sig sourced from the **preprocessed TU's real file scope** (self-`conflicting types`, 13);
3. **never strip a draft extern — block-scope-move it (verbatim types) when no decl is visible above**
   (the draft's extern types are load-bearing: %lo-folding/width/alignment — v2's ambient rewrite
   byte-drifted 18 fns; `recover_giant`'s block-scope idiom, generalized);
4. colliding typedefs **renamed** `Name→Name_<addr>` (byte-neutral) — the SVEC/Vec3/ApplyMatrixSV
   "non-identical ambient type" wall is a RENAME, never a layout problem, on the def side;
5. callee sig conflicts → ambient decl + **call-site casts** (§17a-1), decl lines never cast.

**Gate-validated end-to-end:** `func_8013DD68` (187-ins giant, the batch-2 "def-side sig self-conflict"
wall) banks **byte-identical through `make build`** (`d19c9580… == config/check.ov_SC01_077.sha`), and
its remap **banks in sibling TUs** (`ov_SC01_000`, `ov_SC03_001`) — see Tier M2.

## 1) The tiers (attack order = this order)

| tier | fns | ins | fleet instances | byte-weight | mechanism | cost |
|---|---|---|---|---|---|---|
| **M1** reconcile-bank | 44 | 4,254 | 5,648 | 2.03 MB | `canon_sig_reconcile` v3.1 → gate | ~0 agent tokens |
| **M2** sweep ×134 | (M1+M3+M4+prior ×1s) | — | (counted in M1/M3/M4) | — | `family_remap` → **per-sibling re-reconcile** → gate | ~0 agent tokens |
| **M3** engine no-proto | 6 | 368 | 675 | 0.18 MB | `fix_arity_callers`-class no-proto rewrite of macro externs in `engine_core.h`, then M1 | ~0 agent tokens |
| **M4** TU stale-decl retype | 8 | 552 | 1,206 | 0.33 MB | `reconcile_decls`/§33 fleet-majority retype of stale TU decls, then M1 | ~0 agent tokens |
| **F-near** the true frontier | 31 | 4,693 | 3,775 | 2.19 MB | permuter-ILS → §31 Opus → Fable5 (bands below) | banded |
| **F-perturb** reconcile-resistant | 4 | 872 | 405 | 0.36 MB | per-fn (drift diagnoses below) | per-fn |
| **draft-2** tiny `_o0` | 2 | 46 | 268 | 0.02 MB | draft (trivial) → M1 path | ~1 cheap agent |

**Mechanical tiers M1+M3+M4 = 7,529 fleet instances ≈ +2.19% fn-count fleet (72.29% → ~74.5%) and
~2.5 MB byte-weight, for ~zero agent tokens.** That includes **16 giants ≥145 ins** — the byte-weighted
metric moves materially.

## 2) Tier M1 — bank the 44 (probe-verified BANKABLE in-TU)

Reconciled drafts are staged in **`.run/t6_recon6/`** (regenerable:
`canon_sig_reconcile.py --fn X --draft <draft> --out … --tu src/ov_SC01_077/<split>`).

**Execution recipe (per split-file group, giants first):**
1. Re-run the reconcile **at bank time** against the CURRENT TU (each bank mutates ambient truth for
   the next — the probe classified fns independently).
2. `harvest_verify.py --binary ov_SC01_077 --src src/ov_SC01_077/<split> --asm-subdir
   asm/ov_SC01_077/nonmatchings/<split-subdir> --drafts <staging> --chunk 1`.
   **Read `--good-sha` from `config/check.ov_SC01_077.sha` — NEVER hand-type a hash** (a mistyped
   good-sha made a byte-perfect gate run report MISMATCH this session; P9/R14).
3. `_o0` fns gate through the same file (`ov_SC01_077_o0.c` compiles `-O0` via the Makefile rule;
   no special reconcile — the batch-3 "-O0 in-context byte-diff / needs an -O0-specific reconcile"
   diagnosis is **REFUTED**: all 3 `_o0` giants probe BANKABLE under v3.1 as-is).
4. After the first 5 banks and at every batch boundary: **R22 clean-fleet 136/136**.
5. Expected attrition: small, from probe→gate deltas (the masked probe is jal-symbol-blind; a
   wrong-callee jal would only surface at the gate). Failures → log class → F-band, don't grind.

| fn | ins | inst | split | draft | note |
|---|---|---|---|---|---|
| func_8013C414 | 329 | 134 | …_o0.c | `.run/backlog_drafts/func_8013C414.c` |  |
| func_8016A290 | 284 | 134 | …_after.c | `.run/backlog_drafts/func_8016A290.c` |  |
| func_8013BD74 | 198 | 134 | …_o0.c | `.run/backlog_drafts/func_8013BD74.c` |  |
| func_8013DD68 | 187 | 134 | ….c | `.run/backlog_drafts/func_8013DD68.c` |  |
| func_80167AE0 | 183 | 134 | …_after.c | `.run/backlog_drafts/func_80167AE0.c` |  |
| func_80161E08 | 175 | 134 | …_after.c | `.run/drafts-t5-batch2/func_80161E08.c` |  |
| func_8016C49C | 172 | 134 | …_after.c | `.run/backlog_drafts/func_8016C49C.c` |  |
| func_801347A0 | 162 | 134 | …_a.c | `.run/drafts-t5-batch2/func_801347A0.c` |  |
| func_80162438 | 160 | 134 | …_after.c | `.run/backlog_drafts/func_80162438.c` |  |
| func_80182A24 | 158 | 3 | …_after.c | `.run/backlog_drafts/func_80182A24.c` |  |
| func_8013C0F8 | 154 | 134 | …_o0.c | `.run/backlog_drafts/func_8013C0F8.c` |  |
| func_8016D1D8 | 148 | 134 | …_after.c | `.run/drafts-t5-scaleup-cont/func_8016D1D8.c` |  |
| func_80184F08 | 145 | 17 | …_after.c | `.run/backlog_drafts/func_80184F08.c` |  |
| func_8013AD38 | 122 | 134 | …_a.c | `.run/drafts-t5-scaleup-cont/func_8013AD38.c` |  |
| func_8013EF88 | 108 | 134 | ….c | `.run/drafts-t5-scaleup-cont/func_8013EF88.c` |  |
| func_8016BFD0 | 95 | 134 | …_after.c | `.run/drafts-t5-pilot/func_8016BFD0.c` |  |
| func_8013EE10 | 94 | 134 | ….c | `.run/drafts-t5-scaleup-cont/func_8013EE10.c` |  |
| func_80135004 | 89 | 134 | …_a.c | `.run/drafts-t5-scaleup-cont/func_80135004.c` |  |
| func_80131170 | 88 | 134 | …_a.c | `.run/drafts-t5-scaleup-cont/func_80131170.c` |  |
| func_801343C4 | 83 | 134 | …_a.c | `.run/drafts-t5-scaleup-cont/func_801343C4.c` |  |
| func_80136A94 | 76 | 134 | …_a.c | `.run/backlog_drafts/func_80136A94.c` |  |
| func_8016BD78 | 74 | 134 | …_after.c | `.run/backlog_drafts/func_8016BD78.c` |  |
| func_8016E7C8 | 74 | 134 | …_after.c | `.run/backlog_drafts/func_8016E7C8.c` |  |
| func_8017B368 | 74 | 134 | …_after.c | `.run/backlog_drafts/func_8017B368.c` |  |
| func_80166F58 | 69 | 134 | …_after.c | `.run/drafts-t5-scaleup/func_80166F58.c` |  |
| func_8017BB34 | 65 | 134 | …_after.c | `.run/backlog_drafts/func_8017BB34.c` |  |
| func_8013CF68 | 63 | 134 | ….c | `.run/drafts-t5-scaleup/func_8013CF68.c` |  |
| func_80165240 | 63 | 134 | …_after.c | `.run/backlog_drafts/func_80165240.c` |  |
| func_8017B0E4 | 61 | 134 | …_after.c | `.run/drafts-t5-scaleup/func_8017B0E4.c` |  |
| func_8016D688 | 60 | 134 | …_after.c | `.run/backlog_drafts/func_8016D688.c` |  |
| func_8016BBE0 | 56 | 134 | …_after.c | `.run/backlog_drafts/func_8016BBE0.c` |  |
| func_80178BF8 | 49 | 134 | …_after.c | `.run/backlog_drafts/func_80178BF8.c` |  |
| func_8016BEA0 | 37 | 134 | …_after.c | `.run/backlog_drafts/func_8016BEA0.c` |  |
| func_8016E95C | 36 | 134 | …_after.c | `.run/drafts-t5-scaleup/func_8016E95C.c` |  |
| func_8012DE2C | 35 | 134 | …_a.c | `.run/drafts-t5-scaleup/func_8012DE2C.c` |  |
| func_8012DDA4 | 34 | 134 | …_a.c | `.run/drafts-t5-scaleup/func_8012DDA4.c` |  |
| func_80165140 | 30 | 134 | …_after.c | `.run/drafts-t5-scaleup/func_80165140.c` |  |
| func_801312D0 | 28 | 134 | …_a.c | `.run/drafts-t5-scaleup/func_801312D0.c` |  |
| func_80136C90 | 28 | 134 | …_a.c | `.run/backlog_drafts/func_80136C90.c` |  |
| func_8012ACE0 | 25 | 134 | …_a.c | `.run/drafts-t5-scaleup/func_8012ACE0.c` |  |
| func_80178B18 | 22 | 134 | …_after.c | `.run/backlog_drafts/func_80178B18.c` |  |
| func_8017B8E8 | 22 | 134 | …_after.c | `.run/backlog_drafts/func_8017B8E8.c` |  |
| func_80163408 | 21 | 134 | …_after.c | `.run/drafts-t5-scaleup/func_80163408.c` |  |
| func_80178B70 | 18 | 134 | …_after.c | `.run/drafts-t5-scaleup/func_80178B70.c` |  |

## 3) Tier M2 — sweep every bank ×~134 (the multiplier; Q5 PROVEN)

§41's "sweep fragility" (`func_8016DC20` = 133 sibling failures) is **solved**: sweep the RAW draft via
`family_remap.symbol_map`, then **re-run `canon_sig_reconcile` v3.1 against EACH SIBLING's TU** (its own
ambient truth), then gate. Probe: 3 exemplars (self-sig giant / SVEC-renamed giant / simple med) × 2
siblings (`ov_SC01_000`, `ov_SC03_001`) = **6/6 BANKABLE**, exact instruction counts.

- Implementation: one small `family_sweep.py` extension — after `remap()`, pipe the text through
  `canon_sig_reconcile.reconcile(fn, text, None, sibling_tu)`; keep `--no-preclassify`; gate per
  (overlay, split) group per §40. **Note:** sibling stubs live in the **same split file name** as the
  exemplar's (`_after` stubs are fleet-wide since the whale rollout) — read the asm subdir from the
  sibling's own INCLUDE_ASM line.
- Also re-sweep the **prior exemplar-only banks** (`func_8016DC20` ×133, `func_8018514C` ×16, and the
  T5 partial sweeps) through the same path.
- R22 clean-fleet after each sweep batch; `dedup_propagate`/`config/dedup.us.yaml` registration per §40.

## 4) Tier M3 — the engine-core no-proto reconcile (6 fns)

**Mechanism (measured):** a banked caller's `DEFINE_` macro in `engine_core.h` declares the callee with
a TYPED, wrong-arity extern (e.g. `extern void func_8012D664(void *a0);` — arity 1) that lands at file
scope on instantiation; gcc-2.7.2 remembers it TU-wide, so the byte-true def (arity 3) can never
compile. **No draft-side transform can fix an arity conflict with a visible prototype.** The cure is
the proven `fix_arity_callers` class applied to `engine_core.h` macro externs: rewrite to no-proto
`extern s32 func_X();` — byte-neutral for every existing caller (no-proto call = the default-promotion
codegen the loose callers already use) — **R22 fleet-verify the neutrality first**, then M1-bank the
draft (canonical becomes the no-proto form; v3.1 keeps the draft's params, all s32-compatible).

| fn | ins | inst | split | draft | note |
|---|---|---|---|---|---|
| func_8013D9B0 | 141 | 134 | ….c | `.run/backlog_drafts/func_8013D9B0.c` | fn-sig:func_8013D9B0 |
| func_80131B14 | 89 | 134 | …_a.c | `.run/backlog_drafts/func_80131B14.c` | fn-sig:func_80131B14 |
| func_8015D01C | 58 | 134 | …_after.c | `.run/backlog_drafts/func_8015D01C.c` | fn-sig:func_8015D01C |
| func_8012D664 | 44 | 134 | …_a.c | `.run/drafts-t5-scaleup/func_8012D664.c` | fn-sig:func_8012D664 |
| func_80182988 | 22 | 3 | …_after.c | `.run/drafts-t5-scaleup/func_80182988.c` | fn-sig:func_80182988 |
| func_8016F0AC | 14 | 136 | …_after.c | `.run/backlog_drafts/func_8016F0AC.c` | too-few-args:func_8016F0AC |

## 5) Tier M4 — TU-side stale-decl retypes (8 fns)

The TU (earlier banked drafts) declares these fns' data/callee symbols with stale Ghidra types
(`u8` vs `s16*` etc.). v3.1's access-casts compile but change %lo-folding / access width / alignment
(unaligned lwl/lwr through a narrower object) → BYTEDRIFT. The fix is the **TU decl itself** —
`reconcile_decls.py` (§33, fleet-majority type oracle), byte-gated; then the drafts re-enter M1
(most should bank verbatim: their externs become block-scope/identical).

| fn | ins | drift | symbols to retype |
|---|---|---|---|
| func_8014FE60 | 95 | 18 | callee/data mix (func_80150150 …) |
| func_801418F8 | 90 | 69 | D_8011511A(volatile)+D_80115118 |
| func_8017B238 | 76 | 64 | func_8012F214 + data |
| func_80156044 | 74 | 12 | callee func_8015616C + data |
| func_8013E83C | 71 | 13 | D_80115130/118 cluster |
| func_8013E958 | 63 | 21 | D_8011511x cluster |
| func_80134510 | 58 | 52 | D_801870B0/AC/B4 |
| func_80164E40 | 25 | 8 | D_801D97xx |

## 6) Tier F — the true frontier (33 fns + 2 drafts)

### F-perturb (4): isolation-MATCH but reconcile-resistant — per-fn work
| fn | ins | drift | diagnosis / route |
|---|---|---|---|
| func_80166994 | 369 | 349 | GENUINE loose-typing entanglement (canonical s32 vs byte-true s16 params; 5 mixed-arity callers). The M3 no-proto rewrite of ITS engine_core decl is the first probe; else Fable5 per-fn. |
| func_8016DF5C | 156 | 112 | visible-above conflicts perturb codegen; diagnose per-fn after M3/M4 land (its walls may dissolve) |
| func_8016CF04 | 166 | 104 | 'u8 primitive redef' batch-2 wall: drift persists post-rename — branch-shape delta; per-fn |
| func_801824D0 | 181 | 32 | batch-2 'byte-diff' wall reproduced; branch-target diffs; per-fn |

### F-near (31, verified closeness) — banded escalation
- **Band ≤28 (14 fns / 1,393 ins): permuter-ILS first** (floor-free masked scorer + `permuter_weights`
  §31-class-directed), seeds = the verified drafts. Several are single-lever: the 3-off group
  (`func_80134C20` $s5/$s6 swap = RC-3 decl-order/pin; `func_8017B490` dead-else 3-reorder = S1;
  `func_8012FCC4` beqz delay-slot = D1/S2; `func_801549F8` keep-alive copy = RC-4) and
  `func_8017EF50` (4, coupled first-block tie-break = S1+K1).
- **Band 29–100 (9 fns / 1,296 ins): §31-guided Opus sessions** (statement-order/regalloc levers per
  the sched/regalloc map §C/§D tells), one lever per iteration, permuter fallback.
- **Band >100 (8 fns / 2,004 ins): Fable5-discovery candidates or G4.** Includes the top structural
  family `func_80133CD4` (399 ins, true structural delta ~33 — priority), `func_8014D820` (304, pins
  block permuter), `func_8017C294` (246), `func_80163EC8` (234, 1-insn length-drift artifact —
  aligned edit distance 8, re-triage first!), `func_8016CBC0` (209). Route: Fable5 ONLY on evidence of
  a NEW idiom class; confirmed-intrinsic → INCLUDE_ASM (G4) with the drift dossier logged.

| fn | ins | close | klass | where stuck (wave diagnosis) |
|---|---|---|---|---|
| func_80134C20 | 230 | 3 | regalloc-order | arg0's two saved-reg copies land swapped: gcc puts the 2-ref (arg0&1) var in $s5 and 1-ref (arg0<<16) var in $ |
| func_8017B490 | 97 | 3 | schedule | 97/97 tail matched; dead else-branch base-first-vs-back-compute, 3 instrs reordered (idx34-36); permuter seed  |
| func_8012FCC4 | 57 | 3 | schedule | 3 ins — beqz(0x100) delay-slot fill. Target re-emits `move a0,s0` for func_80131 |
| func_801549F8 | 31 | 3 | schedule | 3-off at -O2 (match_one + gate flags). The n=byte keep-alive copy (addu $a3,$v0, |
| func_8017EF50 | 53 | 4 | schedule | 4 ins — coupled first-block tie-break: addiu(0x34+1)/addu(0x10+0x2c) adjacent sw |
| func_80141A60 | 76 | 7 | plumbing | TBD — first pass |
| func_80180F10 | 75 | 7 | regalloc-order | none — MATCH pending |
| func_80168828 | 108 | 8 | schedule | 8 residual (down from prior 32). idx0-14 and idx40-107 BYTE-EXACT; regalloc/loop/struct/ |
| func_801365B8 | 155 | 11 | regalloc-order | All 11 are arg1/arg2 handling: gcc swaps them across $t2/$t3 (7) + target live-range-splits params (reads orig |
| func_80164930 | 81 | 12 | regalloc-order | TBD — first draft, validating structure + s0/s1/s2/s3 allocation |
| func_8017B614 | 101 | 22 | regalloc-order | 22 (from 57). Structure fully matches (SV4 align-2 block-moves + globals block + delay-slo |
| func_8012E364 | 67 | 23 | regalloc-order | 23/67 masked. Structure+idioms exact (barrier fixes the late D9498 load; k=0x100 |
| func_801345F8 | 106 | 26 | regalloc-order | 26-mismatch near-miss (structure fully matches: while-loop test-first via j-to-bottom-test |
| func_80136824 | 156 | 28 | regalloc-order | Structural MATCH (156/156, all insn-select/control-flow/constants/div-expand correct; axis-1 rotation of match |
| func_8016C188 | 79 | 63 | regalloc-order | TBD — natural regalloc for param_1/iVar1/&D_801D9B84 across calls |
| func_80134A74 | 107 | 71 | regalloc-order | 71-off (106 ins vs 107, off-by-1 tail shift). All 8 saved-reg homes match (s0-s7; puVar4=$ |
| func_801457A4 | 79 | 74 | other | none — MATCH (79 ins, relocation-masked). NOTE: -O0 fn (frame-ptr prologue) — must be |
| func_80133784 | 203 | 76 | regalloc-order | Structurally complete (calls/constants/control-flow byte-correct, struct-ptr CSE + arg0->$s5 pin + s16 delta s |
| func_80185BA4 | 177 | 79 | schedule | Structurally matched 177/177; back third (idx123-176) byte-perfect. Residual = gcc scheduler + caller-saved te |
| func_80145CEC | 127 | 83 | struct | 2 residuals — (1) target RELOADS global ptr D_80126B78 before each of its 5 field accesses |
| func_8014DD8C | 108 | 88 | schedule | prologue-only residual (1-ins shift, d0/d2 into $fp/$s7 vs copy); loop body matches; permuter-compatible (no p |
| func_80133AB0 | 137 | 91 | regalloc-order | near-miss ~91 (naive idx; first 37 ins byte-exact). Logic fully reconstructed. pA pin to |
| func_801670E4 | 279 | 94 | schedule | Structural match (279/279 ins correct, $s3/$s4/$s2 pinned right); 94 residual is pure intra-BB scheduling — gc |
| func_80136334 | 161 | 139 | regalloc-order | Body byte-correct; gcc won't reserve the target's unused -8 frame (dx-lives-across-both-divs spill-reservation |
| func_8016CBC0 | 209 | 148 | regalloc-order | /s-lever load serialization SOLVED (cast-wrapped *(u16*)(vb+po+K)); 166/209 aligned, editdist~44 (positional 1 |
| func_80166690 | 193 | 152 | regalloc-order | Body byte-correct + all local-data offsets match (buf@0x10,tag@0x40,blk@0x48); gcc reserves an unused 8-byte r |
| func_80135480 | 258 | 164 | regalloc-order | Structural MATCH 258/258 ins (control-flow/constants/calls/data/GTE-matrix/tagged-ptr all byte-correct). True  |
| func_80163EC8 | 234 | 176 | schedule | Aligned edit-distance 8 (match_one naive 176 = 1-insn length-drift artifact). Structurally matched: all logic/ |
| func_8017C294 | 246 | 230 | regalloc-order | Structurally complete (246 ins, param_3 in $fp, spurious psVar7[1] giv killed via store-copy per loop.md worth |
| func_8014D820 | 304 | 253 | schedule/regalloc | GIANT; structurally complete (304-ins, calls/consts/control-flow exact); prologue $s0/$s1-vs-$v0/$v1 + cross-c |
| func_80133CD4 | 399 | 274 | regalloc-order | Full structural reconstruction (true structural-delta ~33; match_one positional 274 is inflated by a 2-ins pro |

### draft-2 (2): `func_8013BC7C` (24), `func_8013BCDC` (22) — draft (v3 local / cheap Opus), then M1.

## 7) Validation gates & discipline (T7)

- **Validate before scaling** (Phase-15/16): M1 first-5 banks → R22; M2 first exemplar sweep (~133
  gates) → R22; M3's engine_core edit → R22 BEFORE any dependent bank.
- The probe artifacts (`.run/t6_reconcile_probe6.json`, `.run/t6_verify.json`, `.run/t6_bankable.json`)
  are the worklist of record; `.run/t6_worklist.json` is the tiered machine-readable form.
- Effort map (R26/R27): M1–M4 = **Opus-Max orchestrator, no agent fan-out** (deterministic tool runs);
  F-band ≤28 = permuter (free) + xHigh workers; F-band Fable5 calls = **prompt Drew per R27**.
- Every bank: whole-binary gate; every batch: R22 clean-fleet 136/136; dedup registry updated; the
  flywheel (R16/R30): new idioms → cookbook §41a/§31 maps.

## 8) Projections (fn-count fleet %, from 72.29%)

| after | +instances | fleet ≈ |
|---|---|---|
| M1+M2 | ~5,648 | **~73.9%** |
| +M3+M4 (& their sweeps) | ~1,881 | **~74.5%** |
| +F-band successes (≤28 band, ~70% est.) | ~1,300 | **~74.9%** |

Byte-weighted: the mechanical tiers carry ~2.5 MB incl. 16 giants ≥145 ins — the decomp.dev-comparable
~31–32% figure should move by roughly +1.5–2pp from M1+M2 alone.

# CURRENT_PHASE — Phase 25: The structural-family endgame (idiom curriculum)

**Status:** In progress — plan approved 2026-07-08 (gate 1 passed). · **Generation:** Gen2 (17th phase of the
arc; Phase 14 public-flip deferred to Gen3+). · **Effort:** Max (planning/synthesis/deep debugging); **prompt +
wait for the toggle** (R27) → Ultracode for breadth waves (T5, T7 harvests), Fable5Max for new-class discovery +
the T6 curriculum authoring. Claude cannot set effort itself.
**Plan of record:** `/home/musashi/.claude/plans/plan-mode-enabled-max-generic-galaxy.md` (approved, verbatim).
This file is the P3 crash-recovery execution log.

## Scope clarification (Drew, 2026-07-08, at gate 1)
The phase's atomic unit of work is **"solve ONE exemplar per structural family"** — swept across the whole family
set (~2,764 `h_norm` families), curriculum-ordered, cheap-tier-first with Opus/Fable5/permuter escalation. One
solved exemplar → the family propagates ×134 (reloc-only families, free via `--tier h_norm`) **or** yields the
idiom to template the variants (immediate families). The AIM is one exemplar per family for every family the
tiers can crack; genuine gcc-intrinsic-wall families (S3 / RC-6 / cse mega-flush / L6 exemplars) stay
INCLUDE_ASM with logged evidence (G4/P9). This unifies plan T5 (cheap exemplar sweep) + T7 (curriculum-ordered
escalation) into one exemplar-per-family endgame.

## Strategy (approved)
Cheap/free tiers exhaustively FIRST → complete measured frontier map + pre-softened seeds → Fable5Max authors the
idiom curriculum → sweep one exemplar per family (curriculum-ordered), each cracked exemplar propagated ×134 via
`dedup_propagate --tier h_norm`, byte-gated. The whole-binary byte-gate (`harvest_verify`) is the sole arbiter
(G3/P9) — no wrong match can bank; 136/136 byte-identical every batch (R22).

## Tasks
- [x] T0 — Refresh + housekeeping
- [x] T1 — Integration-recovery pass (split-aware recover_integration fix; caller-arity cohort exhausted 0/16 — residuals backlogged)
- [x] T2 — Exemplar target manifest (tools/family_manifest.py: 2,764 multi-member families → 127 draftable / 156 matched-free / 2481 absent)
- [x] T3 — Swing-question PROOF: free `--tier h_norm` REFUTED (0/133); **mechanical symbol-remap lever PROVEN** (tools/family_remap.py)  ← endgame reshaped, see log
- [x] T4 — v4 retrain + A/B gate — **FAILED/negative, keep v3** (see log)
- [~] T5 — Cheap-tier soften + measure wave → frontier map (Step A) + pre-advanced seeds. **PILOT + BATCH-1 COMPLETE** (Opus xHigh). Pilot 10 + **batch-1 cheap tier 83/83 drafted** (first 54 + the 29-continuation, which needed a resume after a session-cap hit — 20 cached + 9 re-run). Cheap-tier totals: **24 clean exemplar-banks + ~2,793 siblings via family_sweep** (~0 agent tokens). Fleet **71.36 → 72.18%** (+2,820 fns this session), R22 **136/136** every batch, dedup 1813/0. Frontier map = **93 exemplars measured** (`.run/t5_frontier.jsonl`; 75 match_one-MATCH). Clean-bank rate ~35% (rest = def-side-wall → backlog, the #1 T7 lever). **REMAINING: the ~34 giants (batch-2, awaiting Drew) + 5 _o0 (batch-3) + T5c/T5d.**  *(Max orch + xHigh workers)*
- [x] T6 — Step B: Fable5Max curriculum authoring ✅ (2026-07-09) — **`docs/phase25-t6-curriculum.md`** + `.run/t6_worklist.json`; R14 re-verify flipped the map (62/95 iso-MATCH genuine); canon_sig_reconcile **v3.1** (5 defects fixed) → **44/62 probe-BANKABLE** (4,254 ins, 13 giants, incl. all 3 `_o0`); ×134 sweep law PROVEN (per-sibling re-reconcile, 6/6); gate-validated on func_8013DD68; cookbook §41a + decision-log
- [~] T7 — Sweep one exemplar per family, curriculum-ordered. **MECHANICAL/free sub-scope DONE** (matched-free
      +16,512 · T7.2 type-lift +1,729 · T7.3 h_exact +~200). **T7 CURRICULUM MECHANICAL TIERS DONE 2026-07-10**
      (see the T7 log): M1 37 exemplars + M2 4,389 members + M3 2+266 = **~4,694 fleet fns, fleet 72.29→73.66%**.
      **REMAINING (the real substance):** the F-band frontier (31 near-misses: permuter/§31-Opus/Fable5) + the
      deferred mechanical tail (M4 8, F-jumptable 4, M-linkwall 3, M3-residue 4, F-perturb 4, draft 2).
- [ ] Close — clean-fleet verify · PhaseEnd synthesis · plain-English recap (R25) · Phase-26 backlog  *(NOT yet — phase open)*

## FRESH SESSION — RESUME HERE  (**NEXT = the F-band frontier + the deferred mechanical tail**; the T7 mechanical tiers M1/M2/M3 are DONE — fleet **73.66%**, committed `commit:0497`; phase OPEN, do NOT close)
> **IN-FLIGHT (2026-07-10b, Opus-Max→Ultracode) — T7 F-band ≤28 crack wave RUNNING (nothing banked/committed yet):**
> Re-triaged the ≤28 band (R14, all vs bytes): it's **regalloc-order-DOMINATED** (§17 `register __asm__` pin territory) —
> the permuter PLATEAUS on it (func_80134C20 regalloc stuck@3 even with regalloc-directed weights; func_8017EF50
> schedule stuck@4; func_80168828 schedule 8→5). cookbook §17 confirms "permuter can't help — pycparser rejects
> `register __asm__`". Free permuter left **softened seeds**: func_8017EF50 c=4, func_80168828 c=5 (in `.run/permuter/<fn>/output-*`).
> Better drafts found than the T6 table: func_8017B614 is **c=6** (not 22). Iso-MATCH-but-real-TU-drift class:
> func_8017B490 (gate_stage failed=1 compile-wall → per-fn TU work). Length-drift seeds: func_8012E364 (+1), func_801345F8 (−2).
> jtbl+schedule: func_801549F8 (c=3, `jtbl_801D89A4` %hi/%lo). **Ultracode wave `wf_0329d3c2-75c`** = 9 regalloc fns
> (func_80134C20/8017B614/80180F10/80141A60/801365B8/80164930/80136824/8012E364/801345F8), 1 xHigh worker each, §17
> pins → MATCH-in-isolation → `.run/uc_crack/<fn>.c`. **GATE RECIPE per MATCH:** `canon_sig_reconcile --fn X --draft
> .run/uc_crack/X.c --out .run/uc_gate/X.c --tu src/ov_SC01_077/<split>.c` → `harvest_verify --binary ov_SC01_077 --src
> src/ov_SC01_077/<split>.c --asm-subdir asm/ov_SC01_077/nonmatchings/<split-subdir> --drafts .run/uc_gate --good-sha
> d19c9580a02dc63ba1f0e7e0c770f3b10de35635 --chunk 1` → on bank: `family_sweep --only 0xADDR --reconcile .run/uc_crack`
> → R22 clean-fleet 136/136. Isolation-MATCH ≠ real-TU bank (def-side wall / codegen drift) — the whole-binary gate is
> the sole arbiter (G3/P9). Task board #1 (re-triage ≤28 done) / #2 (crack wave in_progress).
> **WAVE RESULT (2026-07-10b):** crack wave `wf_0329d3c2-75c` = **7/9 iso-MATCH** (R14 re-verified via independent
> match_one) + 2 near (func_801365B8 c=2 irreducible cse-repr conflict, both fixes contain `__asm__` so permuter-blind;
> func_8012E364 c=6). **GATE → 4 BANKED byte-identical** into ov_SC01_077: **func_80134C20 (230), func_801345F8 (106),
> func_80141A60 (76), func_80180F10 (75)**. **3 iso-MATCH-but-real-TU-DRIFT** (compile OK, byte-differs → back to F-band):
> func_80136824 (156), func_8017B614 (101 — the T1 **memcpy-builtin-vs-call** class: TU declares memcpy → worker's inlined
> block-move lowers to a CALL → drift; re-crack with field-by-field copy), func_80164930 (81). **SWEEP ×134 DONE:** func_80134C20 ✓133 + func_801345F8 ✓133 = **266 siblings banked**;
> func_80141A60 133 siblings ALL byte-DRIFT (frame-pad lever is ov077-specific, doesn't remap per-sibling →
> frame-pad families are EXEMPLAR-ONLY, not ×134-sweepable — backlog); func_80180F10 = standalone (no h_norm
> siblings). **BATCH = 4 exemplars + 266 siblings = 270 new matched fns.** `family_sweep --commit` AUTO-COMMITTED
> (commit:0500, src/ov_*/*.c only, no ROM — R6/H1 OK; Drew pushes) — note it committed BEFORE R22 (running `bfpt9lgm0`);
> revert commit:0500 if R22 ≠ 136/136. Banked-but-not-swept-cleanly func_80141A60 stands as exemplar (+1).
> **F-band ≤28 residual after this wave:** 3 real-TU-drift (func_80136824/8017B614/80164930) + 2 near
> (func_801365B8 c=2 / func_8012E364 c=6) + 4 schedule/jtbl/iso-drift (func_8017EF50 c=4-perm-softened /
> func_80168828 c=5 / func_8012FCC4 / func_801549F8 jtbl / func_8017B490 real-TU). func_80141A60's 133 frame-pad siblings.
> **✅ R22 CLEAN-FLEET 136/136 GREEN** (corrected recipe: `make clean` nukes asm/, so re-extract ALL 136 via
> `for b in $BINS; do make extract BINARY=$b; done` THEN check-all — cookbook §42c). **Fleet 73.66% → 73.73%**,
> dedup 1813, NON_MATCHING 7 (0 in default build). Commit `commit:0500` (src banks) VERIFIED. Cookbook **§42** written
> (density-lever catalog + 3 tooling gotchas). Doc checkpoint commit next. F-band ≤28 wave = **DONE** (4/9 banked,
> residuals backlogged above); NEXT F-band sub-tiers = 29–100 §31-Opus band + the residual re-cracks (memcpy-class
> func_8017B614, jtbl func_801549F8) + func_80141A60's frame-pad siblings (per-sibling frame analysis).
> **WAVE 2 (`wf_dbadb86a-6b7`, 14 workers, 2026-07-10b):** 9/14 iso-MATCH (R14) → GATE **4 BANKED** (func_80133784
> 203-ins 29-100 win · func_8017B614 memcpy-fix HELD · func_8017EF50 · func_80145CEC) + **5 iso-drift** (func_80136824/
> 80164930/8014DD8C/8016C188/80168828 — cracked isolation-only → drift) + 5 near (func_80134A74 71→16, func_80133AB0
> →28aligned, func_8012FCC4 c=3 beqz/jal delay-swap, func_80185BA4 c=65, func_801670E4 c=70 "irreducible"→G4-candidate).
> Sweeping the 4 ×134 (`buserg6v8`). **META-LESSON (→ wave 3 prompt + cookbook §42 addendum): iso-MATCH ≠ real-TU bank
> (5/9 drifted); the ONLY iso-drift fn that banked (func_8017B614) did so because its worker VERIFIED against the
> reconciled real TU (embed def into a scratch copy of the split .c, compile whole TU, objdump-compare) — wave 3
> workers MUST do this, not isolation-only.** DURABLE LEVER (cookbook): memcpy-builtin→CALL fix = replace `memcpy(x,y,8)`
> with `typedef struct{u8 b[8];}Blk8; *(Blk8*)x=*(Blk8*)y;` (routes emit_block_move lwl/lwr/swl/swr, references NO memcpy
> symbol → immune to the TU-wide builtin-disable; mirrors sibling func_8017B368's SV4 struct-assign idiom).
> **✅ WAVE 2 R22 CLEAN-FLEET 136/136 GREEN. Fleet 73.73% → 73.85%.** Sweep 399/0 (`commit:0502`); cookbook §42a written
> (real-TU-verify rule + memcpy fix + 5 levers). **SESSION TOTAL: fleet 73.66% → 73.85% (+0.19%, ~673 fns): wave 1
> 4 exemplars + 266 siblings (commit:0500/commit:0501), wave 2 4 exemplars + 399 siblings (commit:0502).** dedup 1813,
> NON_MATCHING 7 (0 in default build). **NEXT (fresh session recommended, phase OPEN): WAVE 3 with the real-TU-verify
> rule (§42a) baked into the worker prompt** over: the 5 wave-2 iso-drift fns (func_80136824/80164930/8014DD8C/8016C188/
> 80168828) + the 5 nears (func_80134A74 c=16, func_80133AB0 c=28, func_8012FCC4 c=3, func_80185BA4 c=65, func_801670E4 c=70)
> + the >100 band (task #4, re-triage naive-inflated first) + the deferred tiers (jtbl func_801549F8, -O0 func_801457A4,
> func_80141A60 frame-pad siblings). Gate recipe: reconcile → `harvest_verify --out build/ov_SC01_077/ov_SC01_077` → `family_sweep --reconcile --commit` → R22 (clean+extract-ALL-136+check-all).
> **TOOLING GOTCHA (fix in cookbook/SETUP):** `harvest_verify` for a NON-resident binary MUST pass `--out
> build/<bin>/<bin>` — its `build()` removes+sha1s `--out` (defaults to `build/resident/resident`), so without it every
> overlay draft spuriously reports "final SHA None"/fail even when byte-identical. func_80180F10 needed the RAW draft
> (canon_sig_reconcile choked on its fn-ptr cast `((s32(*)(...))func)`) — raw compiled + banked directly (sig already
> canonical). WORKER LEVERS worth cookbook §17/§31 (from the wave journal): §31 density lever (zero-byte `__asm__("":: "r"(v))`
> dead-read to boost a pseudo's ref-count and win a razor-thin $sN density race); opaque asm-copy `__asm__("addu %0,%1,$zero")`
> to force a param live-range split; frame-pad induction (`s32 pad[2]; (void)&pad;` reserves unused var_size, zero code);
> array-initializer LUID shift (`s32 a[2]={x,y};` vs two stmts → reorders const-materialization in sched2 prologue-weave);
> u16* zero-extend for a high-bit (0x8000+) halfword store constant (`ori` opcode 0x34 vs s16* `addiu`/sign-extend 0x24).
> DIRECT `register __asm__("$21")` pins OFTEN BACKFIRE on giants (wreck prologue save-birthing) — density levers beat them.
> **T7 MECHANICAL DONE (2026-07-10, Opus-Max):** the curriculum's mechanical tiers are banked + swept ×134,
> fleet **72.29% → 73.66% (+1.37%, ~4,694 fleet fns)**, R22 clean-fleet **136/136** at every checkpoint,
> dedup 1813/0, 0 NON_MATCHING. Commits: M1 `commit:0495`, M2 `commit:0496`, M3 `commit:0497`. Tools:
> `tools/t7_bank.py` (M1 driver), `canon_sig_reconcile` **v3.2** (5 defects + type-uniquify fixed),
> `family_sweep --reconcile` (the ×134 per-sibling re-reconcile). See the T7 log below + cookbook §41a/b/c.
> **M4 RESOLVED 2026-07-10 — NOT mechanical (0/8 via reconcile_decls, R14 correction, cookbook §41b-addendum):**
> the 8 M4 fns are byte-correct in ISOLATION but drift 8–69 in the real TU (codegen scheduling/`volatile`-loss,
> not data-type casts; 4 have no data conflict at all) → they JOIN F-band. Same probe-over-count pattern as
> jumptable/linkwall. **The truly-mechanical curriculum tier is exhausted (M1 37 + M3-clean 2 = 39 exemplars,
> swept ×134).**
> **NEXT (deferred, ranked): (1) F-near = 31 near-misses + the 8 ex-M4 = ~39 fns — the genuine frontier:
> permuter-ILS on the ≤28-band [prompt Ultracode], §31-Opus mid-band, Fable5 only on new-idiom evidence
> [prompt R27]; (2) F-jumptable 4 fns / ~536 — jump-table-in-rodata workflow (cookbook §8); (3) M-linkwall
> 3 fns / ~402 — manual undefined-syms for dropped scratch symbols; (4) M3-residue 4 / ~407 (func_80131B14/
> 8016F0AC arity, func_8013D9B0 TU-conflict, func_80182988 loose-typing) + F-perturb 4 / ~405 + draft 2 / ~268.**
> Worklist: `.run/t6_worklist.json` (F_jumptable/F_near/F_perturb/M4 tiers) + `.run/t7_rawdrafts/` (39 raw drafts,
> byte-correct-in-isolation) + `docs/phase25-t6-curriculum.md`. T7 discipline: good-sha from `config/check.*.sha`
> (never hand-typed); R22 clean-fleet every batch; **the object-probe is NOT the gate — it's blind to rodata,
> link, AND in-TU codegen (cookbook §41b + addendum); size any "mechanical" tier from the whole-binary gate.**
> **T6 DONE (2026-07-09, Fable5):** the crack curriculum is authored and byte-grounded — **`docs/phase25-t6-curriculum.md`**
> (tiers + per-fn worklists + commands) with `.run/t6_worklist.json` (machine-readable) and `.run/t6_recon6/` (44 staged
> reconciled drafts). Headline: the def-side wall was ~71% TOOL-shaped — `canon_sig_reconcile.py` **v3.1** (committed) fixes
> five measured defects; **44 exemplars probe-BANKABLE now** (M1), the **×134 sweep works via per-sibling re-reconcile**
> (M2, 6/6 proven — extend `family_sweep` with the one-line reconcile step per the curriculum §3), **6 fns need the
> engine_core.h no-proto rewrite** (M3, fix_arity_callers class, R22-gate the neutrality FIRST), **8 need §33 TU retypes**
> (M4). Mechanical total ≈ **+2.2% fleet (~74.5%) for ~0 agent tokens**. True frontier = 33 fns (curriculum §6 bands:
> permuter ≤28-band first, then §31-Opus, Fable5 only on new-idiom evidence — R27 prompt) + 2 tiny `_o0` drafts.
> T7 discipline: re-reconcile at bank time (TU mutates); good-sha from `config/check.*.sha` (NEVER hand-typed); R22
> clean-fleet after first-5 banks and every batch; probe≠gate (jal-symbol-blind) — harvest_verify is the sole arbiter.
> **T6 HAND-OFF (2026-07-09):** Step A (measure wave) DONE — 125/127 exemplars measured, batches 1–3 complete, def-side wall cracked (`canon_sig_reconcile.py`, cookbook §41), fleet **72.29%** committed `commit:0492`. **The mechanical reconcile-sweep is NOT the clean 51-target ×134 win first hoped (R14-corrected: the frontier "match" status carried un-verified agent claims; a 5-sample spot-check = 3/5 genuine, and even genuine MATCHes hit VARIED walls — callee-sig conflicts, non-identical types Vec3/SVEC, macro-local data). ~19/51 have clean engine_core.h canonicals = the reliable mechanical tier; the rest need per-fn work → this is genuinely the Fable5/T6 residual.** So NEXT = **T6: Fable5Max authors the crack curriculum** from the measured frontier + the diagnosed wall-classes → the full input package is **`docs/phase25-t6-fable-brief.md`** (self-contained; read it first). Then T7 executes the curriculum (back at Opus-Max + surgical tiers). Drew: start the fresh session AS Fable5 (session model), confirm the system-reminder (R27).
> **BATCH-3 DONE (measured, banking deferred to T7) — PAUSED 2026-07-09 at Drew's request.** The 3 `_o0` giants (`func_8013C414`/329, `func_8013BD74`/198, `func_8013C0F8`/154, all inst=134) drafted (Workflow `wf_f22bdea4-50d`, drafts `.run/drafts-t5-batch3/`): **3/3 isolation-MATCH at -O0** (R14-verified via new **`match_one.py --o0`**). But **0 banked** — all 3 hit an **-O0 in-context byte-diff** (compile OK, SHA differs; NOT the def-side sig wall — `canon_sig_reconcile`'s void→s32 return change is NOT byte-neutral at -O0, and `gate_stage`'s call-site transforms don't fix it either → 3 near). Cause = callee canonical sigs changing -O0 call codegen; needs an **-O0-specific reconcile (T7)**. Frontier updated: **125/127 draftable measured** (2 tiny `_o0` stragglers left: `0x8013bc7c`/24, `0x8013bcdc`/22). `func_801457A4` = whale-region -O0 tail, deferred. **Uncommitted (safe on ext4):** `tools/match_one.py` (--o0 flag), `docs/backlog.md` (gate re-render), this file. No src/ banks (tree = committed commit:0492 state).
> **BATCH-2 DONE — DEF-SIDE WALL CRACKED MECHANICALLY (2026-07-09); R22 verifying, then COMMIT.** 29 non-`_o0` un-measured giants drafted (Workflow `wf_9ce827ee-933`, drafts `.run/drafts-t5-batch2/`); **16 R14-isolation-MATCH** (`.run/t5_batch2_verify.json`) but **0 auto-banked** — ALL blocked by the **def-side canonical-sig wall** (drafts use Ghidra-typed sigs conflicting with the engine_core.h canonical, which lives inside `DEFINE_func_*` macros so `sig_unify` can't reach it). **CRACKED** → new tool **`tools/canon_sig_reconcile.py`** (strip ambient-dup typedefs/externs → rewrite def to canonical sig → **cast changed params AT USE, never intermediate locals** [locals shift regalloc → byte-diff, measured `70ff4748`≠`d19c9580`]). Cookbook **§41** + decision-log **R31 entry** written (R30/R31).
> **BANKED 5 giants mechanically:** `func_8013B274 func_80130D48 func_80167DBC` (swept **×134**) + `func_8016DC20 func_8018514C` (exemplar-only — reconciled body carries ov-specific decls, siblings failed remap). ~404 new fn-defs. Frontier map appended (29 giants → `.run/t5_frontier.jsonl`: 13 near, 11 wall, 5 banked).
> **11 walls backlogged (per-fn T7):** non-identical ambient types (`func_80167AE0` SVEC, `func_8016A290` ApplyMatrixSV), macro-local data symbols (`func_80162438` D_80078EB0, `func_80161E08` D_801D9670, +others `reconcile_decls`/§33 territory), `u8` primitive redef (`func_8016CF04`), byte-diff (`func_801824D0`). **13 nears** = permuter-ILS/Fable5 fuel (`func_80134C20` c=3, `func_801365B8` c=11, `func_80136824` c=28 closest).
> **RESUME:** (a) R22 (`.run/t5b2_r22.log`, run `ba10w4gum`) — MUST be **136/136** before commit (R22 caught a buggy R22-harness earlier: `$(OVERLAY_BINARIES)` unexpanded → use `BINS="main resident $(ls -d src/ov_*/|xargs -n1 basename)"`). (b) If green: **commit** batch-2 (5 banks + 3×134 sweep + `canon_sig_reconcile.py` + cookbook §41 + decision-log + backlog + CURRENT_PHASE) — Drew pushes (R6). (c) Recompute fleet %. If R22 shows a real break: diagnose/revert (source spot-checks passed: ov_SC01_000/02_000/06_015/07_009 all BYTE-IDENTICAL clean).
**T5b batch-1 (cheap tier, 83) COMPLETE 2026-07-08, fleet → 72.18%.** How to resume: reuse the proven pipeline — `wave_targets`/the giant list from `.run/t5_targets.json` (bucket=GIANT, 34) → generate a §12-robust wave (copy the `.run/t5_scaleup_cont.js` pattern: worker_wave head + waves-of-10 + retry, targets embedded — sandbox can't read files) → Opus-xHigh Workflow → independent `match_one` (R14) → split-file `gate_stage --no-propagate` → `family_sweep --only <banked>` → R22 clean-fleet 136/136 → commit. Frontier map accumulates in `.run/t5_frontier.jsonl` (93 exemplars so far). Giants: crack tractable directly (pilot cracked the 369-ins `func_80166994`), backlog intrinsic walls for Fable5/permuter; the -O0 ones (batch-3 + `func_801457A4`) need an -O0 `match_one`. **Effort: Max orchestrator + xHigh workers (NOT global Ultracode) — confirmed by Drew.**
**Phase is OPEN.** Order: T7-mechanical (done) → T4 (done, FAILED) → **T5 (pilot + batch-1 DONE 2026-07-08, fleet→72.18%; batch-2 giants NEXT, awaiting Drew)** → T6 →
T7-cracking → Close. T5 mechanics validated end-to-end (`worker_wave` Opus-xHigh → independent `match_one` → `gate_stage`
per split-file → `family_sweep` ×N → R22). Effort = **Max orchestrator + xHigh workers** (Drew chose Opus-xHigh for ALL
127, not global Ultracode; usage not a constraint). Scale-up staged: `.run/t5_waves.json` (12 waves ≤10, ROI-ordered) +
5 `_o0` deferred (need -O0 match_one). Frontier map accumulates in `.run/t5_frontier.jsonl` + the backlog (def-side-wall
+ near-misses). Def-side-wall recovery (caller-decl reconcile, fleet-wide) + hard giants = **T7** (curriculum-directed). The phase's CORE prize is still ahead: **the 127 draftable family exemplars / 6.7 MB**, cracked
by the frontier tier and propagated ×134 by deterministic tooling. Do NOT write a PhaseEnd until T5/T6/T7-cracking
are done and top-family ROI drops (open-ended milestone, per the plan-of-record). *(A prior session misread "→ Close"
in a handoff header and nearly closed early — see `docs/decision-log.md`; reconcile against the plan-of-record.)*

**T5 — the cheap-tier soften + measure wave (Step A).** Over the T2 exemplars + reach-1 + reach-134-tractable:
cheap drafters (**v3** — NOT v4, which failed T4 — + cheap-Opus applying §31) → `match_one` closeness + `klass` per
fn; permuter-ILS softens regalloc/schedule seeds. Output = the complete class/closeness **frontier map** +
pre-advanced seeds. Bank free wins via `gate_stage` as they land. **This is BREADTH → at session start, PROMPT Drew
for `/effort ultracode` and WAIT for the toggle (R27); Claude cannot set effort.** Tools: `wave_targets.py` /
`gen_harvest_targets.py`, `tools/workflows/worker_wave.js` + `distill.js`, `permuter_ils.py`, `bulk_harvest.py`.

**Done + committed:** T0–T3 + T7-part-1 (matched-free sweep, `commit:0476`) + **T7.2 decl-reconcile** (`commit:0479`) +
**T7.3 h_exact stragglers** (`commit:0481`) + **T4 (v4 retrain — FAILED, keep v3)** — fleet **66.02% → 70.82% → 71.32%
→ 71.36%**. T7.2 banked **1,729** (base 532 + `_after` 1,197) via type-lift + mechanical remap; T7.3 banked **~200**
via `dedup_propagate`; **R22 clean-fleet 136/136** every batch, dedup-check 1813/0.

**The mechanical family method (the phase's engine — T3):** h_norm families are TEMPLATES, not free dedup. Per
family: crack ONE exemplar → `family_remap` builds each member's C by positionally substituting the per-overlay
symbols (read from each member's image) → **plain `harvest_verify`** byte-gate (NOT gate_stage's transforms — they
perturb a correct remap). ~0 agent tokens/member. `func_` names are UPPERCASE-hex.

**T7.2 findings (durable — cookbook §40 refinement):** (1) `family_sweep --no-preclassify` — the match_one
pre-classify compiles in ISOLATION (`-Iinclude` only) so it CANNOT see `src/shared/engine_types.h` (pulled by the
real overlay TUs via `../shared/engine_core.h`); it false-negatives every type-lifted family. The flag routes
remappable exemplars straight to the real-TU `harvest_verify` byte-gate (the sole arbiter). (2) The overlay SPLIT
files (`_a`/`_after`/`_o0`) are SEPARATE TUs with conflicting/​shadowing local types → a blind "lift all splits" is
UNSAFE: `Buf` has a DIFFERENT layout in `_a` vs `_after` (fleet-wide lift → `conflicting types` in the other TU),
and `_a` defines `MATRIX`/`VECTOR` = PsyQ SDK names (fleet-wide lift SHADOWS the real types). Safe mechanical ceiling
= base types + `_after` minus `Buf`. New tool knobs: `build_engine_types --file <split.c>` + `--exclude <names>`.

**NEXT — resume the planned order (T7-mechanical was pulled ahead):**
1. ✅ T7.1 surveys · ✅ T7.2 decl-reconcile (1,729; `commit:0479`) · ✅ T7.3 h_exact stragglers (~200; `commit:0481`).
2. **T4 — v4 retrain + A/B gate** *(xHigh pipeline; Max to judge A/B)*. Retrain v4 on the Phase-23/24 banked-idiom
   corpus; A/B vs v3 (`ab_match.js`/`ab_score.py`). Keep v4 in the wave only where it beats v3. $0 to run.
   (`models/bfm-match-7b-v3` is the current; doc `docs/gen2-mips-matching-model.md`.)
3. **T5 — cheap-tier soften + measure wave** → the complete class/closeness frontier map (Step A) + pre-advanced
   seeds. **Prompt `/effort ultracode` (R27)** — this is the breadth wave.
4. **T6 — Fable5Max curriculum authoring** from the measured map. **Prompt for Fable5Max (R27).**
5. **T7-cracking** — execute the top structural families curriculum-ordered: crack each exemplar (127 draftable /
   6.7 MB), template/propagate ×134, byte-gate. Validate top ~3-5 first, then scale (Phase-15/16 lesson).
6. **Close** — only when top-family ROI drops (open-ended, per plan §Milestone). NOT before.

**Residual backlog (revisit after the curriculum; genuine Phase-26 candidates):**
- **T7.2 residual: 16 split-TU-type families / ~2,128 members** — need per-type reconciliation (namespaced/per-TU
  header, rename the cross-TU `Buf`, or verify `_a`'s PsyQ MATRIX/VECTOR are layout-compatible + use real SDK
  headers) — NOT mechanical. `.run/sweep_deferred.preT72.txt` = the 29 addrs.
- **h_exact engine-core straggler class** — more `DEFINE_func` macros likely stub in siblings (`dedup_propagate
  --auto` MISSES them — it only converts INLINE defs). Sweep by `--addr`. Plus inline→macro hygiene of T7.2's
  h_exact-identical inline banks (10 fns; byte-neutral). A small `family_remap.extract_unit` fix to handle macro
  bodies would unblock the 2 h_norm-macro remap-fails (`8012A568`/`80138C30`).
- **683 whole-binary-diff simple failures** (~4%: match_one-MATCH but TU-context diff, like the memcpy idiom).
- `0x8013c360` (-O0 cluster); the 2 permanent giant walls `func_801412A8`/`func_80178004` (G4, INCLUDE_ASM).

## Blockers
None.

## Per-task log

### T0 — Refresh + housekeeping ✅ (2026-07-08)
- Housekeeping: `gccdump.lreg` (repo root) = gcc's DEFAULT RTL dump (dump-base "gccdump", `.lreg` = local-reg
  pass; `toplev.c:1973/2077`), left by a one-off `cc1 -da` RTL-inspection run with CWD=root — **not** any
  committed tool (grep hits only the gcc source under `tools/reference/`). Deleted; root clean; no other stray
  dumps. Practice: RTL-inspection runs use a `.run/` CWD or `-dumpbase .run/gccdump` (R12).
- Regenerated 134 overlay sigs (`make sig-overlays`, exit 0); rebuilt `fuel_manifest` + `worklist --refresh`
  (stale Jun-26 ranking killed → `docs/worklist.md`: 130 live stubs, top = the wall `func_801412A8`).
- Fixed `tools/sig_image.py` docstring (h_norm is the live `norm_stream`, not a "T5 placeholder" — R21/R30).
- **CURRENT FRONTIER (R14 ground truth):** fleet 66.02%.
  - h_exact: 82,744 unmatched classes / 111,815 instances / **27.33 MB**. Reach-134 tier = **130 classes /
    4.11 MB** (7 tiny + 55 small + 50 med + 16 large + 2 giant-walls). x1-unique = 74,742 classes / **19.99 MB**.
  - h_norm: **44,101 families**; **2,764 multi-member families / 11.1 MB** (the hidden lever). Top: same-address-
    ×134 (func_80133CD4/166994/8013C414 … 126-127 h_exact-cls / 134 inst / 199-399 ins) → match 1 → ×134;
    high-count-small (func_80150480: **1,997 inst × 22 ins** → 1 idiom → ~2000 fns); low-variant
    (func_8014E284/80150170: 2 h_exact-cls / 268 inst → match 2 → ×268).
  - **Solo-monster reframe CONFIRMED:** 3,989 / 8,670 large (≥150-ins) h_exact-reach-1 fns have h_norm siblings
    (46% templatable); 4,681 truly-unique-shape (worst ROI → LAST).
  - Cheap first wins queued: T1 leaf-matches `func_80155800` (#3) + `func_8014F4C0` (#4) ≈ 38k gain_ins
    near-free; 2 permanent walls `func_801412A8`/`func_80178004` stay INCLUDE_ASM (G4).

### T1 — Integration-recovery pass ✅ (2026-07-08) — cheap cohort exhausted; deliverable = the split-aware fix
- **Deliverable (committed `commit:0470`):** `recover_integration` made split-aware (§39 gap). It was silently
  skipping the **263-stub `ov_SC01_077_after`** cohort (drift-check hardcoded the main asm subdir; gate_stage
  never got src/asm/src_file). Now `stub_map()` reads each stub's asm subdir from its INCLUDE_ASM line and
  `reconcile_and_gate` gates per split-file group (run_gate self-filters; propagate idempotent). Reusable T5/T7.
- **Finding (R14/P9):** the closeness-0 **caller-arity** cohort is EXHAUSTED — `--auto --limit 20` banked
  **0/16** (Phase 24 already banked the cheap decl-plumbing ones). Residuals (incl. both flagships) are
  **per-function TU-context matching**, not decl-plumbing.
- **The blocker class (matching idiom → cookbook when it recurs, R16):** an 8-byte mem-copy written as a
  **struct-assign** `*(T*)x = *(T*)y` (func_8014F4C0's `Vec4u`) is `match_one`-MATCH in isolation but lowers to a
  **memcpy CALL** in a TU that declares `memcpy` (sibling `extern void *memcpy(...)` disables the builtin) → byte
  mismatch (`9d043345`≠`d19c9580`). Banked sibling convention = **explicit `memcpy(x,y,8)` or field-by-field
  lhu/sh** (the target uses lhu/sh). T5/T7 drafters: avoid struct-assign for small mem-copies in these overlays.
- **Decision (Drew):** conclude T1; closeness-0 residuals stay in the ranked backlog (available later); the 2
  flagship ×134 leaf-matches NOT hand-banked (per-function ROI < the family lever).

### T2 — Exemplar-scoped target manifest ✅ (2026-07-08)
- **Deliverable:** `tools/family_manifest.py` (committed, reusable) → `docs/family-manifest.md` + gitignored
  `.run/family_manifest.json`. Regroups the unmatched frontier by h_norm; per family: the ov_SC01_077 drafting
  exemplar (where present), **instances** (the ×N leverage — NOT h_exact-reach, ~1-3 for byte-shattered families),
  size, byte-weight. 44,101 families; **2,764 multi-member / 11.1 MB**.
- **The endgame's 3 levers (× ov_SC01_077 membership):**
  - **draftable 127 / 6.7 MB** — unmatched ov077 member → draft the exemplar (primary T5/T7; most byte-weight).
  - **matched-free 156 / 2.3 MB** — matched ov077 member + unmatched siblings → FREE `--tier h_norm` propagation
    (draft-free; the T3 proof + a free win).
  - **absent 2481 / 2.1 MB** — no ov077 member → small fns in other overlays, draft elsewhere (low priority).
- **Insight:** h_norm families are reloc-only by construction, so the matched-free bucket is likely bankable NOW by
  re-propagating already-matched ov077 fns via `--tier h_norm` (byte-gated). T3 tests decisively.
- T3 candidates (mid-size draftable): 0x8012c890(149)/0x8016d1d8(148)/0x8013d9b0(141) — all inst=134, ~127 hexcls.

### T3 — Swing-question PROOF ✅ (2026-07-08) — free lever refuted; **mechanical remap PROVEN** (the phase's pivot)
- **Free `--tier h_norm` dedup REFUTED (R14):** propagating ov_SC01_077's matched `0x80141100` across its 133
  h_norm-siblings banked **0/133** (all byte-diverge). h_norm families are byte-shattered *because each member
  references per-overlay symbols* (`D_80187xxx` in ov077 vs `D_8017Fxxx` in ov000) — one C body can't name 134
  overlays' symbols. This also kills the plan's draft-then-propagate fallback (same mechanism).
- **Mechanical symbol-remap lever PROVEN → `tools/family_remap.py`:** two h_norm-identical members have identical
  instruction streams except in the masked reloc fields, so disassemble both overlay images at ADDR, positionally
  pair the resolved reloc targets, substitute the exemplar C's per-overlay symbol NAMES with the sibling's. Verified:
  reloc decoder **22/22** vs .s; `0x80141100`→ov_SC01_000 **whole-binary BYTE-IDENTICAL + harvest_verify banked**
  (9052dc0e); **12/12** siblings SC01-SC07 match_one; **7/9 families × 3 siblings = 21/27** match_one.
- **The 2 failures = decl/type plumbing** (custom `MatEntry` type + conflicting shared `ApplyMatrixSV` decl — a
  COMPILE error, NOT a byte mismatch): the remapped draft must reconcile decls with the target's ambient
  engine_core.h/engine_types.h (strip ambient externs). A known-solved T7 refinement, not a remap failure.
- **Gate path for remapped drafts = plain `harvest_verify`** (gate_stage's canon/cast/sig_unify transforms PERTURB
  an already-correct remap → 0-bank; skip them for remaps).
- **Endgame reshaped:** the 11.1 MB h_norm families are cheaply, MECHANICALLY recoverable — crack ONE exemplar per
  family → remap+gate members (~0 agent tokens/member). Members no longer need drafting; only exemplars do.

### T7 (part 1) — MECHANICAL family sweep: matched-free harvest ✅ (2026-07-08, `commit:0476`)
- Built `tools/family_sweep.py` (two-phase: stage all remaps per overlay, gate each (overlay,split) group ONCE via
  plain `harvest_verify`; a `match_one` pre-classify defers compile-failing type-using families to avoid bisection
  blowup). Driver validated on `func_80141100` (133/133 banked, committed `commit:0475`).
- **BANKED 16,512 member-matches** (131 simple exemplars × ~133 siblings) + the 133 validation; **0 remap-fail**.
  **R22 clean-fleet verify: 136/136 byte-identical** from a fully clean tree (make clean + extract-all + check-all).
  **Fleet 66.02% → 70.82%** (+4.8% in ONE deterministic, ~0-agent-token pass). dedup-check 1813/0.
- Deferred (`.run/sweep_deferred.txt`): 29 type/decl (type-lift recoverable), 4 diff, 4 remap-fail.
- 683 / 17,195 simple drafts failed the whole-binary gate (match_one-MATCH but TU-context diff, ~4%; auto-reverted).
- **Reproduce:** `family_sweep.py --limit 0` (after `make sig-overlays`). The remap is `family_remap.py`.

### T7.2 — decl-reconcile the 29 type/decl families ✅ (2026-07-08, `commit:0479`) — 1,729 banked; split-TU wall found
- **T7.1 refresh:** `make sig-overlays` (134 re-signed) + `family_manifest.py` — levers unchanged (2,764 families;
  127 draftable / 156 matched-free) because they key on ov077 membership, which the 16.5k sibling-banks didn't change.
- **Base type-lift:** `build_engine_types --source ov_SC01_077 --strip` lifted 4 base-local types (`MatEntry`,
  `P_TAG`, `OtBlk`, `packed_word`/`word_bytes`) → `engine_types.h`; byte-neutral (ov077 d19c9580). Banked **532**.
- **The pre-classify false-negative (R14):** after the lift, all 29 STILL pre-classified as `type/decl` (0 simple).
  Root cause: `match_one` isolation compiles with `-Iinclude` + a prepended `common.h` — it does NOT see
  `src/shared/engine_types.h` (the real overlay TU pulls it via `../shared/engine_core.h`). PROVEN false-negative:
  single real-TU gate `func_80142A80`→ov_SC01_000 = `9052dc0e` BYTE-IDENTICAL. FIX: `family_sweep --no-preclassify`.
- **The split-TU wall:** the 25 remaining families need types from the overlay SPLIT files, which are SEPARATE .o TUs
  with conflicting/​shadowing local types. Blind "lift all splits" FAILED: `typedef Buf` has a DIFFERENT layout in
  `_a.c` vs `_after.c` (`conflicting types for Buf` when shared); `_a.c` defines `MATRIX`/`VECTOR` (PsyQ SDK names →
  fleet-wide SHADOW). Safe ceiling = base + `_after` **minus Buf** (`build_engine_types --file … --exclude Buf`):
  byte-neutral, banked **+1,197** (9 of 10 `_after` families/overlay; the 1 miss is the Buf-user).
- **T7.2 TOTAL 1,729** (532 + 1,197). **R22 clean-fleet 136/136** from clean tree; dedup-check 1813/0; fleet **71.32%**.
- **Deferred → Phase 26:** 16 families / ~2,128 members (see backlog above). Old deferred snapshot preserved at
  `.run/sweep_deferred.preT72.txt` (the 29 addrs).
- **Reproduce:** `build_engine_types --source ov_SC01_077 --strip` ; `build_engine_types --file
  src/ov_SC01_077/ov_SC01_077_after.c --exclude Buf --strip` ; `family_sweep --only <29 addrs> --no-preclassify`.

### T7.3 — edge-case triage: 2 h_exact stragglers banked ✅ (2026-07-08, `commit:0481`) — +~200 members
- Triaged the 8 T7-part-1 edge cases (4 diff + 4 remap-fail). **Finding:** the 4 remap-fails are matched in ov077 via
  the `DEFINE_func_<ADDR>()` engine-core MACRO (§11 h_exact source-share), NOT an inline def — so `family_remap`'s
  `extract_unit` (keys on a `func_<ADDR>(` DEFINITION) can't extract them. 2 of them (`func_80128EA8`, `func_80132EC4`)
  are **h_exact-identical** fleet-wide but were **stub in 100 overlays** → banked via the EXISTING `dedup_propagate
  --addr --tier h_exact` (118 overlays byte-identical each). **R22 clean-fleet 136/136; dedup-check 1813/0; fleet
  71.32% → 71.36%.** (byte-% moves little: asm stubs were already byte-identical; the win is 200 fns now C, not asm.)
- **Deferred → Phase 26:** the 2 h_norm-macro remap-fails (`8012A568`/`80138C30` — h_norm AND macro-defined, neither
  h_exact-propagatable nor family_remap-extractable); `8013C360` (-O0 cluster); the 4 "diff" cases mostly already
  banked (stub-in-0 now).

## SESSION PROGRESS (2026-07-08) — T7-mechanical pulled ahead; phase OPEN (T4→T5→T6→T7-cracking remain)
**This session (T7.1–T7.3, all committed, R6 = Drew pushes):** fleet **70.82% → 71.36%**; **+1,929 member-matches**
(T7.2 1,729 via type-lift+remap `commit:0479`/`commit:0480`; T7.3 ~200 via h_exact propagation `commit:0481`/`commit:0482`).
Every batch R22 clean-fleet **136/136**, dedup-check 1813/0. Tools added: `family_sweep --no-preclassify`;
`build_engine_types --file/--exclude`. Cookbook **§40a** written (R30). **NEXT = T4** (see the RESUME section above);
NOT closing — the curriculum + 127-draftable exemplar-cracking is the phase's core, still ahead.

### T4 — v4 LoRA retrain + A/B gate ❌ FAILED / NEGATIVE (2026-07-08) — v4 discarded, KEEP v3
- Retrained v4 (same recipe as v3, corpus 2,891→3,574) — converged (loss ~0.082). Gate-true A/B vs v3 on identical
  held-out functions, 3 bands: **easy 6-14** both 5/5; **medium 18-40** v3 closer near-misses + fewer compile-fails
  (v3 better on 9/12); **hard 45-85** both 0/10. v4 = marginally WORSE. **Verdict: discard v4, keep v3** (frozen
  ceiling). "Corpus quality > size" confirmed; the 7B is capacity-bound (0/5 even on trained fns, NOT truncation).
- **v3 remains the drafter** (`models/bfm-match-7b-v3`). v4 adapter kept at `models/bfm-match-7b-v4` (gitignored) for
  reference only. Full write-ups: `docs/decision-log.md` (strategic — 7B off the endgame critical path) +
  `docs/gen2-mips-matching-model.md` (technical — the A/B + the maxlen-2048 truncation flaw for any future retrain).
- **Strategic conclusion (Drew-aligned):** the local-7B tier is a $0 mop-up for the ≤~15-ins tail, NOT load-bearing.
  The endgame engine is **frontier-crack → deterministic-propagate → byte-gate** + permuter-soften. **No more 7B retrains.**

### T5 — cheap-tier soften + measure wave (Step A) — PILOT ✅ (2026-07-08); scale-up in progress
- **Pipeline validated end-to-end** (the T5 engine): `tools/family_manifest`→ `.run/t5_targets.json` (127 draftable
  exemplars, live-stub-verified: 34 GIANT/18 large/43 med/32 small) → `worker_wave.js` (Opus **xHigh**, 1 drafter/target,
  returns {status,closeness,klass}) → independent `match_one` re-verify (R14) → `gate_stage --src-file <split>` (per
  split; the whole-binary byte-gate is the arbiter) → `family_sweep --only <addr>` (h_norm mechanical remap ×N) → **R22
  clean-fleet 136/136**.
- **Pilot (10 diverse targets):** 7/10 match_one-MATCH incl. a **369-ins giant (`func_80166994`)** cracked by the wave.
  Whole-binary gate banked **3/7 clean** (`func_801596F0`, `func_8014D3E0`, `func_801320D8`); `family_sweep` → **+399
  siblings, 0 failed** across 133 overlays (~0 agent tokens). **Fleet 71.36% → 71.47%** (+402 fns), dedup 1813/0.
- **Key findings (frontier data → T6):** (1) **byte-weight ≠ tractability** — `func_8014D3E0` (22 ins × 1997) looked like
  the mega-ROI freebie but is a `$sp` stack-switcher, matched only by porting an already-matched sibling (`func_8014D04C`);
  the 369-giant fell to the wave while a 304-giant (`func_8014D820`) is close=253 (Fable5). (2) **The dominant gate-failure
  is the def-side loose-typing wall** (4/7): a byte-correct draft whose CALLERS carry guessed sigs (`void func_X(s32,s32…)`)
  that conflict fleet-wide with the true def; `gate_stage` runs sig_unify (which *regresses* these) but not a caller-decl
  reconcile. `func_80166994` is genuinely loose-typing-entangled (5 callers, mixed s16/s32 args → truncation risk) = T7.
  (3) `family_sweep` is SAME-ADDRESS only → `func_8014D3E0`'s cross-address h_norm instances (~1863 of 1997) are a T5c/T7
  cross-address-remap follow-up.
- **Class dist (pilot):** schedule 5, other 2, iv-combine/struct/plumbing 1 each. Near-miss permuter/Fable5 fuel:
  `func_8017B490` (3), `func_8014DD8C` (88), `func_8014D820` (253).
- **Reproduce:** target pool `.run/t5_targets.json`; frontier `.run/t5_frontier.jsonl`; waves `.run/t5_waves.json`.
  Scale-up (117) + permuter-ILS soften (T5c) + frontier synthesis (T5d) NEXT; def-side-wall recovery tool → T7.

### T5b — measure-wave batch 1 (the ≤149-ins cheap tier) — PARTIAL ✅ (2026-07-08); MORE BATCHES LATER (Drew)
- **Generated a §12-robust scale-up wave** (`tools/workflows/t5_scaleup.js`: worker_wave's drafter prompt + sequential
  waves-of-10 + retry×2, targets embedded — sandbox can't read files). Launched over the 83 ≤149-ins targets.
- **Drew stopped it at ~50** (HTTP **529 Overloaded** under API load — the §12 throttle; retry+gap-fill was recovering
  it, no work lost). **54 drafts landed, 0 truncated.** Processed as T5b per Drew's instruction (don't restart; bank
  what's done; checkpoint + pause; more T5b later).
- **Results:** independent `match_one` (R14) = **46/54 MATCH** (85%; cheap tier). `gate_stage` per split (main/​_a/​_after)
  banked **16 clean** (main 1 · _a 10 · _after 5) → `family_sweep` **+1,861 siblings / 1 fail across 133 overlays** (14
  exemplars swept, ~0 agent tokens). **Fleet 71.47 → 72.02%**, R22 clean-fleet **136/136**, dedup 1813/0.
- **The def-side loose-typing wall is confirmed dominant at scale:** ~30 of the 46 match_one-MATCH drafts were
  byte-correct standalone but gate-rejected (caller carries a guessed sig) → all backlogged. **This is the #1 lever for
  T7** — a fleet-wide-gated caller-decl reconcile would convert most of them. Clean-bank rate ~16/46 = 35% (matches the
  pilot's 3/7).
- **Frontier map: 64 exemplars measured** (`.run/t5_frontier.jsonl`; classes: struct 15, plumbing 13, schedule 11,
  regalloc-order 11, remat 5, …). Near-miss permuter fuel: `func_8012FCC4`/`func_801549F8` (3), `func_8017EF50` (4).
- **BATCH-1 CONTINUATION DONE** (the 29 undrafted cheap, 74-149 ins): a resume (`resumeFromRunId`) recovered the 9
  session-cap failures (20 cached-replay + 9 re-run, 0 errors). 22/29 -O2 match_one-MATCH → **8 clean banks + 533
  siblings** (fleet 72.02 → 72.18%, R22 136/136). Notables logged to backlog: `func_801457A4` (MATCH but **-O0-only**
  → batch-3), `func_80135004`/`func_8013AD38` (MATCH but need the T7 caller-decl reconcile), `func_80168828` (close=8,
  permuter fuel). **Batch-1 cheap tier now 100% drafted.** Gen3 recomp/PsyQ→Vulkan architecture idea captured to
  `docs/gen3-parking-lot.md` (Drew spitball).
- **REMAINING:** the ~34 giants (batch-2, AWAITING Drew) + 5 `_o0` (batch-3, -O0 match_one) + permuter-ILS soften
  (T5c) + frontier synthesis (T5d) + the def-side-wall reconcile tool (T7 lever #1). Scale-up wave generator reusable.

## RULES ADDED THIS PHASE (transcribe to the PhaseEnd Rules table at close)
- **R31 — CONFIRMED by Drew 2026-07-08 (binding now).** Capture the WHY behind strategic pivots in `docs/decision-log.md`, while fresh. At each major
  direction change / dead-end / reversal, log (during the producing session): context+belief → what was
  tried that failed → the pivot → the byte/measurement-grounded why → a hindsight "better path" note.
  Extends R30 (which covers TECHNICAL artifacts — cookbook idioms, byte-verified findings, distillations)
  to STRATEGIC / decision rationale — the perishable judgment the terse PhaseEnd Deviations table can't
  hold and a fresh session reconstructing from compressed summaries would lose. Forward-only (no backfill
  from summaries). It is the substrate for the eventual project **retrospective** + the public
  **"how to AI-decomp a new project"** wiki (Drew, 2026-07-08). Doc created + seeded with this session's
  two fresh pivots (the handoff-misread; the split-TU mechanical ceiling).

### T6 — Fable5Max curriculum authoring ✅ (2026-07-09, the Fable5 session)
- **Deliverables:** `docs/phase25-t6-curriculum.md` (the tiered crack curriculum, all numbers probe-derived) +
  `.run/t6_worklist.json` (machine-readable tiers) + `.run/t6_recon6/` (44 staged reconciled drafts) +
  `tools/canon_sig_reconcile.py` **v3.1** + cookbook **§41a** + a decision-log entry (R31).
- **Method:** R14 re-verified all 95 stubs (`.run/t6_verify.json`: 62 iso-MATCH / 31 near / 2 no-draft) →
  6-iteration probe program (reconcile → splice into the real TU → full pipeline → masked in-TU byte-compare;
  `.run/t6_reconcile_probe*.json`) → v1's reconcile itself was the wall for most (5 defects fixed) →
  BANKABLE 10→20→37→**44**. Swing answers: Q1 = 44 mechanical (not ~19); Q2 = resident-callee extension moot
  (real class = self/arity conflicts → M3 no-proto); Q3 = **-O0 reconcile REFUTED** (all 3 `_o0` giants bank
  under v3.1); Q4 = type collisions are a RENAME, never layout (SVEC/ApplyMatrixSV giants bank); Q5 = ×134
  sweep = remap + **per-sibling re-reconcile**, 6/6 proven (§41 fragility dissolved).
- **Validation:** func_8013DD68 (187-ins "wall" giant) banked BYTE-IDENTICAL through the real `make build`
  gate (then restored — no T7 execution in T6; tree stays at the committed state + these deliverables).
- **Cost:** ~0 agent tokens (local deterministic compute only; no Workflow/Agent fan-out).

### T7 — EXECUTE the crack curriculum: mechanical tiers M1/M2/M3 (2026-07-10, Opus-Max orchestrator, ~0 agent tokens)
**Fleet 72.29% → 73.66% (+1.37%, ~4,694 fleet fns); R22 clean-fleet 136/136 at every checkpoint; dedup 1813/0; 0 NON_MATCHING (G4).**

- **M1 (commit `commit:0495`) — 37 exemplars banked ×1.** `tools/t7_bank.py` (reconcile-at-bank-time + `harvest_verify`
  whole-binary gate; chunk-bet + per-round re-reconcile for cross-fn ambient mutation; giants first). Two
  `canon_sig_reconcile` fixes surfaced during execution: (a) **v3.2 uniquify ALL draft-defined type names + struct
  tags** to `<name>_<addr>` (the `redefinition of struct Fr` inter-draft-collision class when many exemplars bank
  into one TU) — banked the 284-ins `func_8016A290`; (b) the earlier v3.1 5-defect set. **R14 CORRECTION (cookbook
  §41b):** the T6 object-only probe OVER-counted BANKABLE by 7 — it's blind to rodata + link: **4 jump-table fns**
  (3 `_o0` giants + `func_8012ACE0`) have byte-perfect `.text` but a switch **jump table in rodata** diverges
  (REFUTES the T6 "Q3 -O0 REFUTED" claim → F-jumptable); **3 last-referencer link-walls** (`func_8016D688/D1D8/165240`)
  C-ify the only asm referencer of a scratch data symbol → `ld undefined reference` → M-linkwall.
- **M2 (commit `commit:0496`) — 4,389 members swept ×134.** `family_sweep --reconcile`: per (exemplar, sibling),
  symbol-remap the RAW draft then **RE-RUN canon_sig_reconcile against THAT sibling's TU** (the Q5 law — plain
  remap of the ov077-reconciled body banks 0; per-sibling reconcile banks 94%). 4,389/4,655 (266 per-sibling
  loose-typing-wall misses → backlog). cookbook §41c.
- **M3 (commit `commit:0497`) — 2 no-proto exemplars + 266 swept.** Rewrote 4 clean fns' `engine_core.h` macro-internal
  externs to no-proto (10 byte-neutral decl edits); banked `func_8012D664`+`func_8015D01C`, swept 266/266 (100%).
  The fleet-wide EC change R22-verified neutral (136/136). 4 residue deferred.

**Deferred backlog (ranked, `.run/t6_worklist.json` tiers + `.run/t7_rawdrafts/`):** F-near 31 / ~3,775 ×134
(the genuine permuter/§31-Opus/Fable5 frontier — bands in curriculum §6) · M4 8 / ~1,206 (§33 reconcile_decls
TU-retype, mechanical-untried) · F-jumptable 4 / ~536 (jump-table-in-rodata, cookbook §8) · M3-residue 4 / ~407
(func_80131B14/8016F0AC arity, func_8013D9B0 TU-conflict, func_80182988 loose-typing) · F-perturb 4 / ~405 ·
M-linkwall 3 / ~402 (manual undefined-syms) · draft-needed 2 / ~268 (tiny `_o0`). **~56 exemplars / ~7,000
fleet-inst potential remain.**

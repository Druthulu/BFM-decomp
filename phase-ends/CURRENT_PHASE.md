# CURRENT_PHASE — Phase 21: The Automation Manager

**Generation:** Gen2 (13th phase) · **Status:** APPROVED plan, in progress · **Effort:** Max (whole phase)
**Plan file:** `/home/musashi/.claude/plans/max-effort-plan-mode-breezy-zebra.md`
**Started:** 2026-06-21 · **Fleet at start:** 58.82% byte-identical (136/136 binaries byte-identical, 0 NON_MATCHING)

> Phase Start gate PASSED (Drew approved the plan). This file is the per-task crash-recovery log (P3/CURRENT_PHASE).
> Open-ended phase; milestone = **build → validate → stage, then close** (Drew's choice — the multi-day run is a later go).

---

## ★★★ SESSION 2026-06-25 (cont. 6) — schedule idiom = COALESCING (pin-crackable), 2 durable gate fixes, h_exact over-counts ×134 (READ FIRST)

> Drew's `/loop` (the cont.5 prompt) + `/effort Max`. Ran the cont.5 cycle: assess → cheap recovery → learn the
> `schedule` idiom. The grinder ran token-free alongside (still permuting the hard tail, banked 0 — expected).
> All byte-gated (G3/P9); 0 NON_MATCHING throughout.

**Fleet 63.17%** (217,316 / 344,010, +0.04% this session) · 136/136 byte-identical (R22 re-verified at close) · HEAD = the cont.6 commit below. Local, not pushed (R6).

**★ TWO DURABLE TOOLING FIXES (the real value this session — they compound on every future wave):**
1. **`sig_unify.py --src-file`** (closes the §24 open item). It read `cur_stubs`/decls from the MAIN `.c` only →
   silently DROPPED every `_a`/`_o0` split-file draft (0 unified vs 21 with the flag) → split-file near-misses
   never got the def-side arity-adopt recovery. Now `--src-file src/ov_SC01_077/ov_SC01_077_a.c` reads the split
   file. `gate_stage` passes it to BOTH `cast_call_sites` and `sig_unify` in `--src-file` mode. → banked
   func_8012F568 ×134 from the `_a` close=0 backlog (commit:0277).
2. **`gate_stage.py` is now CANON-FIRST two-stage (§19 design folded into the shared gate).** It ran
   canon→cast→sig_unify in ONE pass; sig_unify REGRESSED the func_80128ED8 crack (rewrote its byte-correct def
   `s32 f(s32,s32*)` → a banked caller's `void* f(void*,void*)` → gate reject). Fix: **stage 1** canon+cast →
   gate (already-correct/hand-pinned cracks bank here); **stage 2** sig_unify ONLY the stage-1 failures → re-gate
   (def-side recovery, no regression). `harvest_verify` accumulates verified across the two calls (reads current
   src as baseline). Cookbook §25.

**★ THE `schedule` IDIOM — CRACKED, but it's COALESCING not scheduling (cookbook §25):** func_80128ED8 (close=3,
the assess's lowest-closeness reach-134 schedule exemplar) → `match_one` MATCH 53/53 via two §17 pins: pin the
index-preserve copy to its target reg ($a3) so gcc can't fold it into the multiply operand (multiply uses $v1
directly), and route `idc+1` through a dead $v0-pinned temp. The "schedule" label was misleading — the residual
was gcc-2.7.2 **copy-coalescing**. Also distilled the genuine `rank_for_schedule` tie-break (priority → class-vs-last
→ LUID source-order) and the genuine WALLS (func_8014FD54 §10 cross-jump/delay-slot; func_8014F2E0 store-vs-load).

**★ THE STRATEGIC FINDING (R14/P9 — reshapes the cont.5 model): `h_exact` OVER-COUNTS ×134.** func_80128ED8 is
byte-identical in ov_SC01_077 but **does NOT propagate ×134** — `dedup_propagate --addr 0x80128ED8` alone still
`[drop]`s it at ov_SC01_000 (cross-overlay byte-gate reject). So it banks **×1**, despite h_exact `members=134`
(h_exact is relocation-masked → over-counts). **Consequence:** `idiom_loop --assess`'s per-class "reach-134"
count is OPTIMISTIC; the `schedule` class is NOT a confirmed ×134 vein (its 2 closest reach-134 exemplars = 1 ×1
coalescing crack + 1 §10 wall). **Before a token-heavy wave, probe ×134-shareability on the cracked exemplar**
(`dedup_propagate --addr <fn>`), don't trust the h_exact count.

**★ SESSION BANKS:** func_8012F568 ×134 (commit:0277, `_a` recovery) + func_80128ED8 ×1 (commit:0278, schedule crack).
The MAIN-region close=0 recovery banked 0/40 (the §20 def-side wall, as expected — sig_unify already tried on them).

**★ NEXT — the schedule WAVE (cont.5 step 4) is NOT yet justified (ROI-gated, §20 "don't wave a wall"):** the
exemplar came out ×1 and the class's reach-134 count is h_exact-inflated. Options for the next session, in order:
1. **Probe-first:** run `dedup_propagate --addr` on 5-10 more cracked schedule fns to MEASURE the real ×134 fraction
   before any wave (cheap, ~0 tokens). If a meaningful fraction is ×134 → wave with the §25 coalescing-pin idiom.
2. **Re-assess for a higher-ROI idiom:** `idiom_loop --assess` after this session's banks; consider that the
   median-0 classes (regalloc-order 44 r134, plumbing 34 r134) are RECOVERY-dominated — the now-fixed
   `sig_unify --src-file` + canon-first gate may unlock some via a re-gate of their close=0 backlog (cheap).
3. The fresh fuel is genuinely thinning; the honest read is that the cached reach-134 tail is mostly walls +
   ×1-overlay-local. The high-byte-weight lever remains the **giants** (§ Phase-21 backlog) — token-heavy, deep.

---

## ★★★ SESSION 2026-06-24 (cont. 5) — Phase 21 is now a NEVERENDING idiom-learning loop (was READ FIRST; cont.6 supersedes the model caveat)

> **Drew's directive (2026-06-24): Phase 21 does NOT end until he says it does — assume neverending.**
> The model: harvest the EASY reach-134 fuel until ~80% consumed (a WALL), then **LEARN the next
> gcc-quirk IDIOM** that unlocks the highest-leverage residual, hand off to a **FRESH session** (clean
> context) with a `/loop` prompt to crack + harvest it, and **repeat forever → toward 100% decomp**.
> Each session ≈ one idiom. The vote is always: *target new gcc quirks, learn idioms, 100% the game.*

**Fleet ~62.98%** (wave-4 in flight) · 136/136 byte-identical · 0 NON_MATCHING · grinder running (token-free).
The `_a` reach-134 EASY fuel is ~exhausted (waves 1–4 this session: 62.31 → 62.98%, +0.67%) — **we are AT
the first idiom wall.**

**★ THE META-LOOP TOOL (new, committed): `tools/idiom_loop.py`**
- `--fuel-status` — rough wall indicator (counts ALL fresh cached incl. reach-1; the *precise* reach-134
  wall = `wave_targets --region a/main` returns a small / re-attempt-heavy batch, as now: 24→24→20→13).
- `--assess` — clusters the backlog near-misses by gcc-quirk class, ranks by reach-134 leverage, names
  (a) the next IDIOM to learn + (b) the cheap deterministic recovery lever.
- `--gen-fuel <class> [--out f]` — writes the research+harvest fuel manifest (closest-first) for a session.

**★ FIRST ASSESSMENT (`--assess`, byte-backed from the 316-record backlog):**
- **NEXT IDIOM TO LEARN → `schedule`** (49 reach-134 fns, median 13 ins off): the gcc-2.7.2
  **instruction-scheduler (sched.c) load/store tie-break** — drafters consistently stub it "unsteerable"
  after pins+barriers. Fuel: `.run/auto/idiom_fuel_schedule.json` (68 fns). Crack it on a **low-but-NONZERO**
  closeness exemplar (e.g. func_80128ED8 / func_80131A34, close=3 — a single misplaced copy/load-order),
  research sched.c (R17, `tools/reference/gcc-papermario`), distill to the cookbook, then re-wave ×134.
- **DETERMINISTIC RECOVERY LEVER → 64 close=0 reach-134 fns** (byte-correct, declaration-blocked = the `_a`
  sig_unify-skip casualties + main plumbing). A def-side recovery (make `sig_unify` `--src-file`-aware so it
  doesn't drop `_a` drafts, OR cast the def) banks them ×134 for ~0 agent tokens. **DO THIS FIRST each cycle.**

**★ THE NEVERENDING CYCLE (every fresh session = the `/loop`):**
1. `idiom_loop.py --assess` → confirm the target idiom + the close=0 recovery count.
2. **Cheap harvest first:** run/extend the def-side recovery over the close=0 backlog → gate (drop-straggler-safe) → ×134.
3. **Learn the idiom:** research the gcc pass (R17) + crack 1 low-closeness exemplar (hand/agent) → distill to the cookbook (R16).
4. **Harvest the idiom:** `worker_wave` over the fuel manifest (seed agents with the new idiom) → `gate_stage --src-file --commit` → ×134.
5. At ~80% of this class's fuel → `--assess` next idiom → `--gen-fuel` → **request a fresh session + hand Drew a new `/loop` prompt.** Forever.

**★ THE `/loop` PROMPT for the NEXT (fresh) session** (Drew pastes it to start):
> `/loop` Phase-21 idiom cycle. Read CURRENT_PHASE cont.5 + the cookbook. (1) `idiom_loop.py --assess`. (2) FIRST harvest the close=0 deterministic-recovery lever: make `sig_unify --src-file`-aware (don't drop `_a` drafts) or cast the def, re-gate the close=0 backlog → bank ×134. (3) LEARN the `schedule` gcc-2.7.2 idiom: research sched.c (R17), crack a close≈3 exemplar (func_80128ED8/func_80131A34) by hand, distill to the cookbook. (4) `worker_wave` the schedule fuel (`.run/auto/idiom_fuel_schedule.json`) seeded with the idiom → gate ×134. (5) At ~80% fuel → `--assess` the next idiom → `--gen-fuel` → request a fresh session + give Drew a new `/loop` prompt. Phase 21 is NEVERENDING; grinder runs token-free alongside (`tools/auto_status.sh`).

---

## ★★★ SESSION 2026-06-24 (cont. 4) — the `_a` vein IS a ×134 lever (10/11); cont.3 §24 pessimism CORRECTED (superseded by cont. 5)

> Authoritative. The first real `_a` measurement wave ran (Drew greenlit + `/effort Max`). CORRECTS cont.3/§24:
> the `_a` vein is NOT ×1 loose-typing-walled — **10/11 banked fns propagate ×134 byte-identical**. The "×1"
> reading was TWO tooling bugs, now diagnosed (R14, byte-proven). The byte-gate (G3/P9) held throughout.

**Fleet 62.70%** (215,699 / 344,010, **+0.39% this turn**) · 136/136 byte-identical · 0 NON_MATCHING.
HEAD = the commit below. Grinder still running (token-free, banked 0 — the permuter-resistant hard tail; don't stop). Local, not pushed (R6).

**★ THE RESULT — `_a` is a ×134 lever (probe-proven):**
- Wave: 24 xHigh agents over `wave_targets.py --pool tractable --region a` (61–129 ins) → **16/24 self-MATCH, 11 byte-banked** in `ov_SC01_077_a.c` (commit `commit:0266`). All 11 are reach-134 (members=134).
- The gate reported **`propagated: 0`** — a TOOLING artifact, NOT the §24 wall. Two stacked bugs:
  1. **`dedup_propagate` batch propagation is ALL-OR-NOTHING** (lines 456–464): one cross-overlay-incompatible fn reverts the whole batch.
  2. The poison was **`func_8013C360`** — the pre-existing **-O0 overlay-local** straggler (§18/§20: masked h_exact falsely reports reach-134, but its real bytes reference per-overlay data → fails the cross-overlay byte-gate). Swept into `--auto-from`, it reverted all 10 clean matches.
  3. **`gate_stage`'s `sh()` swallows dedup_propagate's non-zero exit** (no return-code check) → reported 0 with no error surfaced.
- **Per-function probe (each vs ov_SC01_000, gate.lock held): 10/11 PASS, 1 FAIL** (the FAIL = func_8013C360 ONLY).
- **Realized the gain:** propagated the 10 clean fns ×134 (`dedup_propagate --addr <10> --source-overlay ov_SC01_077 --min-reach 2`, straggler excluded) → `[ OK ] 134 overlays byte-identical`, 10 new dedup groups → **commit `commit:0267`, fleet 62.31→62.70%**.

**★ THE 10 PROPAGATED ×134:** `0x80128DB4 0x801300F4 0x80136D08 0x80130AF0 0x8012944C 0x8012D4B4 0x80137030 0x80132288 0x8012DBD0 0x8013339C`. **×1 (local-types-skip → needs the §20 type-lift):** func_8012EA90 (banked in `_a.c` only). **Excluded straggler:** func_8013C360 (-O0 overlay-local — keep OUT of cross-overlay propagation).

**★ ENABLER FIX (committed this session):** `worker_wave.js` now derives each agent's `match_one` self-check `--asm-subdir` from `t.asm` (was hardcoded to the MAIN subdir → every `_a` agent self-check crashed on a missing `.s` → blind drafting). THIS produced the high close rate (16/24); without it the `_a` wave drafts blind.

**★ FIXES DONE + VALIDATED (this session) — the `_a` pipeline is now HANDS-FREE:**
1. **`gate_stage` surfaces propagation failures** (`commit:0269`): `prop_error` + `.run/auto/last_propagate_error.log` — no more silent swallow (it caught wave-2's failure live).
2. **`dedup_propagate` excludes -O0 overlay-local fns from `--auto-from`** (`commit:0269`): `*_o0.c` defs (incl. func_8013C360) never cross-overlay-propagate (find_site-detected; --addr still forces).
3. **`dedup_propagate` DROP-STRAGGLER retry** (refactor): on a byte-gate fail it isolates the culprit(s) for the failing overlay (per-fn trial), drops them (kept ×1), and retries the survivors — handles BOTH straggler classes (-O0 byte-mismatch + cross-overlay loose-typing compile-error) failing ANY overlay. Byte-gate stays sole arbiter; the plan strictly shrinks so it always terminates.

**★ WAVE-2 (validated the fixes end-to-end):** 24 fresh `_a` targets → 13 self-MATCH → gate banked **6** (the `_a` path SKIPS sig_unify, so def-side near-misses don't auto-recover → lower bank rate than main). Drop-straggler `--auto-from` then auto-dropped 2 loose-typing stragglers (func_8012E5CC/func_8012C750 — compile-fail ov_SC01_000, kept ×1) + propagated **3 clean ×134** (`commit:0271`). The 11 near-misses are permuter-class schedule/regalloc walls (grinder fuel; 7 were last wave's re-attempts, still walls).

**★ SESSION ARC: 62.31% → 62.82% (+0.51%):** wave-1 +10 ×134 (`commit:0267`) · wave-2 +6 ×1 (`commit:0270`) +3 ×134 (`commit:0271`). 136/136 byte-identical, 0 NON_MATCHING throughout.

**★ NEXT — the `_a` scaling loop is now hands-free (~55 fresh `_a` reach-134 fns remain):** `wave_targets --pool tractable --region a` → worker_wave → `gate_stage --src-file --commit` (auto-drops stragglers + auto-propagates clean ×134). ~+0.2–0.4% fleet/wave. **Improvement idea:** a def-side recovery that doesn't drop `_a` drafts would lift the `_a` bank rate (sig_unify-skip is the current cap). **Pending Drew's direction** (continue scaling vs checkpoint/close).

---

## ★★★ SESSION 2026-06-24 (cont. 3) — the `_a.c` split-file vein: enabler tooling built (SUPERSEDED by cont. 4 — the vein IS ×134)

> Authoritative. Pursued the fresh-fuel recommendation; found the fresh fuel is in `ov_SC01_077_a.c` (a tooling
> gap), built the split-aware enabler, and characterized the vein honestly (it hits the same loose-typing wall).

**Fleet 62.31%** (unchanged — **no net banks this turn**; func_8012C098 matched ×1 in `_a.c` then reverted by a
diag's `git checkout`, negligible + a propagation-wall). 136/136 byte-identical. HEAD = the commit below.

**RUNNING NOW (2026-06-24):** token-free **grinder relaunched** (`DRIVER=tools/grinder.py auto_supervisor.sh
--permute-secs 120 -j 14`, detached) on the close≤30 backlog; byte-gated (G3/P9), auto-commits ×134,
self-supervising. Monitor `bash tools/auto_status.sh`; stop `bash tools/auto_stop.sh`. A `/loop` check-in reports
progress (kill switch = `.run/auto/STOP`). CAVEAT: the close≤30 backlog is the permuter-resistant hard tail
(§20/§24) — it banked **0 in ~1h** on a prior run; expect low/slow yield. The real % lever is the **`_a`
measurement wave** (below), pending Drew's token greenlight — the grinder is the free background filler meanwhile.

**★ THE FINDING (where the fresh fuel is):** the main-`.c` reach-134 fuel is byte-exhausted (1 fresh fn); the
**66+ fresh cached reach-134 fns live in `ov_SC01_077_a.c`** (the Phase-19 `-O0` 3-way split), never waved because
the harvest pipeline defaults to `src/{ov}/{ov}.c`. Full write-up: **cookbook §24**.

**★ ENABLER TOOLING BUILT (committed, validated as far as possible, fail-closed/safe):**
- **`dedup_propagate.py` split-aware** — `overlay_files()` handles main + `_a`/`_o0`; source-find scans all,
  member-loop edits the right split file, structural-check spans all. Single-file overlays unchanged. Validated:
  source-find (`--check-only` → 134 members) + fail-path revert. (×134 success-path of an `_a` fn pending the wave.)
- **`cast_call_sites.py --src-file`** — canonicalize callee decls against the file the draft LANDS in (cross-file
  loose typing: e.g. `RotTransSV` declared differently in main vs `_a.c`). Default = main (unchanged).

**★ THE WALL (honest — `_a` is NOT the clean +2-3% I projected):** the `_a` bodies are matchable (func_8012C098
cast-banked ×1), but matching/propagation hits the SAME §16/§20 loose-typing wall: cross-overlay def-conflict
(func_8012C098 → caller declares it `(void)` but body uses a param → ×1 wall, can't propagate), within-`_a`
multi-sig callees (func_8012F274 → `RotTransSV` declared inconsistently in `_a.c`). The ×134 yield is uncertain.

**★ THE `_a` WAVE IS NOW TURNKEY (built + wired this session — run from a FRESH session; Drew greenlit waving `_a`):**
All four pieces committed: `wave_targets.py` region-aware (`--region a` serves the 68 fresh `_a` reach-134 fns
with the correct `..._a` asm paths) · `cast_call_sites.py --src-file` (canonicalize vs the `_a.c` decls) ·
`gate_stage.py --src-file` (cast `--src-file` + SKIP sig_unify, which drops `_a` fns; harvest_verify `--src` `_a.c`) ·
`dedup_propagate.py` split-aware (propagates an `_a`-matched fn ×reach).

**THE `_a` WAVE CYCLE (fresh session; grinder runs alongside, free):**
1. `.venv/bin/python tools/wave_targets.py --pool tractable --region a --n 24 --out .run/auto/wave_batch.json`
   (small `_a` WAVE/PINS/STRUCT ≤150-ins; or `--pool any-reach134 --region a` for all 68 incl. giants).
2. Read `.run/auto/wave_batch.json`; launch `tools/workflows/worker_wave.js` (Workflow tool),
   `args={draftDir:".run/drafts-wave", targets:<batch array PASTED VERBATIM>}` (args = JSON ARRAY, §20 gotcha).
3. On completion GATE in `_a` mode — **BACKGROUNDED + dangerouslyDisableSandbox** (NOT `orchestrator.py finish`, which is main-only):
   ```
   .venv/bin/python tools/gate_stage.py --binary ov_SC01_077 \
     --src src/ov_SC01_077/ov_SC01_077_a.c --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_a \
     --src-file src/ov_SC01_077/ov_SC01_077_a.c \
     --out build/ov_SC01_077/ov_SC01_077 --good-sha d19c9580a02dc63ba1f0e7e0c770f3b10de35635 \
     --drafts .run/drafts-wave --commit
   ```
   Prints `{banked, propagated, near, failed, fleet_pct}`. `propagated` ≈ #fns that went ×134; banked-not-propagated = ×1 walls (§24).
4. `make report` for fleet%; distill new idioms (`tools/workflows/distill.js`); loop step 1. STOP all: `bash tools/auto_stop.sh`.

**MEASURE FIRST (probe-before-scale):** run ONE wave, read the ×134-vs-×1 yield. High ×134 → scale the rest
(~60 `_a` fns, real fleet%); mostly ×1 → the loose-typing wall (§24) dominates → pivot. The byte-gate guarantees
correctness either way (a wrong/conflicting draft reverts, never banks). Cookbook §24 has the full context.

---

## ★★★ SESSION 2026-06-24 (cont. 2) — GIANTS ARE STALE+INCOMPLETE DRAFTS, not cheap near-misses

> Authoritative. CORRECTS the "(cont.) GIANTS-AS-NEAR-MISSES" section below: only func_80153E00 was a clean
> near-miss; the rest are stale-draft RE-DRAFT work. A diag self-correction (R14) — the byte-gate was right.

**Fleet 62.31%** (214,358/344,010) · 136/136 byte-identical · 0 NON_MATCHING · banked_total 288 · waves 34.
**No new banks this turn** (func_80153E00 ×134 was the prior turn). HEAD `commit:0261`+ (docs). Grinder STOPPED.

**★ THE GIANT VERDICT (byte-proven, P9/R14):** the 14 MAIN-file giants' prior-wave drafts are **STALE +
INCOMPLETE** vs the grown `engine_core.h` — `conflicting types` (draft `u8 D_80126B58` vs canonical `s32`;
`u8 D_80126948` vs `u8[]`), **undeclared** data symbols (`D_800A5E8C`, `D_800B9A08` → link `undefined reference`),
incomplete types. The whole-binary gate (`harvest_verify`) banks **0 of 10**. They are **NOT cheap near-misses** —
they need **RE-DRAFTING fresh** (worker wave, current canonical context + §17–§23 toolkit incl. the data-cast),
not a recovery transform. func_80153E00 banked only because its draft was complete + 1-instruction clean.
- **⚠ A DIAG MIRAGE bit me (cookbook §23, §20 stale-`.o`):** a per-function `objdump` diff that builds WITHOUT
  removing `build/src/<ov>.o`+`.elf` first reports **FALSE byte-matches** when a draft fails to compile (make
  leaves stub artifacts). It faked "10 giant MATCHes." Fixed `.run/diag_funcdiff.py` to `os.remove` artifacts
  first. **The whole-binary SHA gate is the SOLE arbiter (G3/P9)** — it removes the output, so it was right.
- **sig_unify bug found (not fixed — reverted):** `DRAFT_EXTERN_LINE_RE` anchors `;$` so it SKIPS externs with a
  trailing `/* */` comment → can't canonicalize them. A regex fix works but (a) is unproven to bank (the giants
  have deeper undeclared-symbol issues) and (b) broader canonicalization regresses value-read divergent-type
  drafts — the right lever is a **data-CAST** (keep canonical decl, cast the read; §23), not canonicalization.
- **11 `_a.c` giants** (func_8013339C/8012D098/80129CF8/8012EC04 + 7 more): live in `ov_SC01_077_a.c` (Phase-19
  3-object split), but `dedup_propagate`/the gate are hardwired to `src/{ov}/{ov}.c` → can't source from `_a.c`.
  Banking/propagating them needs split-aware tooling. (`func_8012EC04` is GTE — also needs raw-byte verify, §18.)

**★ NEXT — a FORK for Drew (the cheap-giant-recovery premise is refuted):**
(a) **Re-draft the giants fresh** — a worker Workflow over the 28 GIANT-class fns (`.run/fuel_manifest.json`,
    class=GIANT) with current canonical callee/data sigs embedded + the §17–§23 toolkit, then gate+propagate ×134.
    High byte-weight payoff (func_80144B9C=770 ins ×134) but token-heavy + each needs its own near-miss grind.
(b) **Pivot to a more tractable pool** (fresh reach-134 ≤90-ins via a Ghidra-C regen, or relaunch the grinder).
(c) **Build split-aware + data-cast tooling** first (unlock the 11 `_a.c` giants + auto-recover the data class).
Recommendation: (b) for steady % now, with (a) as a focused deep session for the byte-weight. Drew chooses.

---

## ★★★ SESSION 2026-06-23 (cont.) — GIANTS-AS-NEAR-MISSES (partially SUPERSEDED by cont. 2 above)

> The func_80153E00 crack below is correct; the "giants are near-misses, diagnose+bank" GENERALIZATION is
> corrected by cont. 2 (most giant drafts are stale+incomplete → re-draft, not recover).

**Fleet 62.31%** byte-identical (**214,358 / 344,010**, +134 vs the checkpoint) · 136/136 binaries byte-identical · 0 NON_MATCHING.
banked_total 288 · waves 34 · grinder STOPPED (`.run/auto/STOP` present). Committed locally (`commit:0260`), **not pushed** (R6).
This session (Drew's `/loop`, one giants cycle): **banked `func_80153E00` ×134** (the 195-ins giant), fleet 62.27→62.31%.

**★ THE CORRECTED GIANTS FINDING (R14, byte-proven — supersedes the FINAL HANDOFF "callee-declaration plumbing" claim):**
The 5 "body-correct but plumbing-blocked" giants are **NOT** plumbing-blocked. `func_80153E00` **compiles AND links
CLEAN** in the whole binary (no `conflicting types`, no `undefined reference`) and was a **1-instruction near-miss**
(1/195). `match_one` over-predicted — it compiles STANDALONE with the draft's own externs AND masks jal/%hi/%lo, so it
never sees the real residual. **The giants are individually-diagnosable near-misses; diagnose + fix the 1–N off
instructions + bank ×134.** Full write-up: **cookbook §23**.
- **THE DIAGNOSTIC (use this on every giant):** `.venv/bin/python .run/diag_funcdiff.py <fn> <draftdir>` — a linked-ELF
  per-function `objdump` diff (target = stub build, candidate = spliced build), address-column normalized so only real
  opcode/reg/operand diffs show. Tells you in seconds whether the residual is relocation/codegen/type. **Run only when
  NO `ov_SC01_077` build is in flight** (concurrent `make build BINARY=ov_SC01_077` clobbers `build/`).
- **`func_80153E00`'s blocker = scalar-data-signedness conflict (the data analog of cast_call_sites):** target `lhu`,
  candidate `lh` on `D_8011DB0C` (declared `extern s16` canonically but the fn needs a `u16` read). Declaring `u16` →
  `sig_unify` reverts to canonical `s16`. **Fix: keep canonical `extern s16`, cast the READ: `*(u16*)&D_8011DB0C`** →
  gcc folds to one `lhu`, no decl conflict, survives the gate. Refutes §20's "data-cast moot" (which only checked
  struct/union, not scalar signedness). Writes (`sh`) are signedness-agnostic — only reads need casting.

**★ NEXT (fresh cycle) — diagnose the OTHER 4 giants the same way (drafts in `.run/drafts-wave-cn/`):**
`func_8013339C` (schedule), `func_8012EC04` (GTE — verify on RAW bytes via objcopy, NOT objdump/match_one, idiom
`commit:0253`), `func_8012D098` (struct), `func_80129CF8` (struct; its note already flags `D_80126DB8` lh-vs-lw — likely the
SAME scalar-data-cast class). For each: `cp .run/drafts-wave-cn/<fn>.c .run/dg/` → `diag_funcdiff` → fix the diffs →
`cp` to `.run/drafts-wave/` → `orchestrator.py finish --drafts .run/drafts-wave --commit` (BACKGROUNDED +
dangerouslyDisableSandbox). **Struct-class giants** (D_*-struct local typedefs) also need the type-lift
(`build_engine_types.py --strip`) to propagate ×134 (Phase-20 §20 T1) — else they bank ×1 local.
**TOOLING LEVER (probe-first):** if the scalar-data-signedness conflict recurs on ≥1–2 more giants, build
`cast_data_sites.py` (data sibling of `cast_call_sites.py`) into `gate_stage` → auto-recovers the class for ~0 tokens.

---

## ★★★ SESSION 2026-06-23 FINAL HANDOFF — (SUPERSEDED by the GIANTS-AS-NEAR-MISSES section above; historical trail)

> Authoritative current state at a clean committed checkpoint. Everything below this section is HISTORICAL trail.

**Fleet 62.27%** byte-identical (**214,224 / 344,010**) · **+1.11% this session** (started 61.16%) · 136/136 binaries
byte-identical · 0 NON_MATCHING. **Nothing running** — grinder STOPPED (`.run/auto/STOP` present; `rm` it to relaunch).
Clean checkpoint; committed locally, **not pushed** (R6 — Drew pushes). orch_state: `pool=any-reach134 waves=32 banked_total=287` (worker) + 5 grinder banks.

**THE SESSION ARC (Drew's `/loop`, steered via 5 AskUserQuestions):**
1. **Waves 17–29 — reach-1 (×1) smallest-first harvest:** ~183 banks but fleet only **+0.06%** — reach-1 fns are overlay-unique → ×1, and the fleet metric counts functions across all 136 binaries. Band climbed 14→75 ins, close-rate fell 0.9→0.33. **LESSON: reach-1 is poor fleet-ROI; its value was ov_SC01_077 completeness + idiom-mining.**
2. **Waves 30–31 — THE REACH-134 PIVOT (Drew's call), ×134:** banked 26 reach-134 STUB fns, each propagated ×134 → fleet **61.22% → 62.19% (+0.97% in 2 waves)** — ~16× the *entire* reach-1 run, per wave. Fuel = the `any-reach134` pool (STUB-class reach-134 fns the WAVE/PINS/STRUCT `tractable` pool never covered); now **EXHAUSTED**.
3. **Giants scout (Drew's call) — BODY-TRACTABLE but PLUMBING-BLOCKED (the key finding):** 10 giants (159–207 ins, ×134) → **5/10 self-MATCH at the body level** (relocation-masked) but **0 banked** — all failed the whole-binary gate on **callee-declaration plumbing** (giants call many fns; the recovery pipeline couldn't reconcile all their callee sigs → won't compile standalone). The 5 body-correct giants — `func_8013339C` `func_8012EC04`(GTE) `func_8012D098` `func_80129CF8` `func_80153E00` — are ×134, byte-correct bodies, blocked ONLY on callee decls. Best drafts saved in `.run/backlog_drafts/`.
4. **Grinder (token-free permuter, alongside):** banked **5** reach-1/permuter walls (+~0.05%); stopped for this checkpoint.

**★ THE EUREKA LEVER FOR THE FRESH SESSION — RECOVERY-TOOLING (highest leverage, ~0 agent tokens):**
The giants prove the BODIES are crackable; the wall is purely **callee-declaration plumbing** (§16/§20 loose-typing). Extend the recovery pipeline (`tools/canon_resident_calls.py → cast_call_sites.py → sig_unify.py`) to declare the giants' callees correctly → **bank the 5 body-correct giants ×134** (potentially **+1–2% fleet**) PLUS the ~5 plumbing-blocked reach-134 STRUCT self-MATCHes — all for ~0 drafting tokens. **Do this BEFORE more scout waves** (scouting finds more self-MATCHes but they won't bank until the callee plumbing is cracked).
  - **Start here:** take `func_80153E00`'s draft in `.run/backlog_drafts/`, run it through `tools/gate_stage.py` manually, read the standalone-compile error (a callee sig conflict), extend the recovery for that class, re-gate. Repeat for the other 4. Each bank is a giant ×134.

**SECONDARY:** (a) more giant-scout waves to grow the body-correct ×134 backlog (only valuable once recovery banks them — the 28 giants are in `.run/fuel_manifest.json` class=GIANT; 5 body-banked, rest fresh/near); (b) the grinder (relaunch, token-free) for permuter-walls; (c) the reach-1 big-fn tail remains (×1, low-ROI — skip).

**12 NEW COOKBOOK IDIOMS this session** (the durable knowledge): `commit:0225 commit:0227 commit:0230 commit:0232 commit:0235 commit:0237 commit:0240 commit:0243 commit:0245 commit:0247 commit:0249 commit:0253`. The last CRACKED the GTE-sqr "unproducible" false dead-end — **verify GTE/cop2-nop fns on RAW bytes (`objcopy -O binary --only-section=.text`), NOT objdump/match_one** (they elide zero-word runs → false mismatch). `func_8012EC04` confirms a 2nd GTE fn matches this way.

**3 POOL-TOOLING FIXES this session:** `commit:0228` (plumbing_blocked scans ALL raw backlog records) · `commit:0239` (NEW reserved_walls skips ≥2×-redrafted near-miss walls) · `commit:0257` (--class filters to still-unbanked genuine near-misses) → ~149+ churners correctly skipped from worker waves.

**RESUME COMMANDS (fresh session):**
- **Grinder** (token-free, relaunch): `rm -f .run/auto/STOP && DRIVER=tools/grinder.py setsid nohup bash tools/auto_supervisor.sh --permute-secs 120 -j 14 >/dev/null 2>&1 &` (dangerouslyDisableSandbox). Stop: `bash tools/auto_stop.sh`. Monitor: `bash tools/auto_status.sh`.
- **Worker finish** (after a worker_wave Workflow): `.venv/bin/python tools/orchestrator.py finish --drafts .run/drafts-wave --commit` — **BACKGROUNDED + dangerouslyDisableSandbox** (foreground make/git get sandbox-killed exit 144). It gates → banks → propagates ×134 (`dedup_propagate --auto-from`) → logs near-misses.
- **Manual giant batch** (worker_wave args.targets): pick fresh GIANT-class fns from `.run/fuel_manifest.json`, build `{name,addr,nins,class:"GIANT",asm,ghidra_c}` per target (addr=`0x`+name[5:].lower(); asm=`asm/ov_SC01_077/nonmatchings/ov_SC01_077/<name>.s`; ghidra_c=`.run/ghidra_c/<name>.c`).
- **Live fleet:** `grep byte-identical docs/progress.fleet.md` or `make report`. **Verify invariant:** `make check-all` → 136/136 (R22); per-bank whole-binary byte-gate (G3/P9) is the sole arbiter.

---

## ★★ REACH-1 HARVEST HANDOFF — READ THIS FIRST (2026-06-22, authoritative current state)

> Everything below this section (the prior ×134 QUEUED-RUN block, TRIP HAND-OFF, POST-REBOOT, etc.) is a
> HISTORICAL session-layer kept for the trail. **THIS section is the current state + the fresh-session plan.**

**★ SESSION UPDATE 2026-06-23 (waves 17–30 — Drew's `/loop`; PIVOTED to reach-134 at wave 30):** Fleet **61.73%** ·
banked_total **274** · 136/136 byte-identical · 0 NON_MATCHING throughout (per-wave byte-gate, G3/P9).
**ARC:** waves 17–29 = reach-1 (×1) smallest-first harvest, banked ~183 over 13 waves but fleet only +0.06%
(61.16→61.22) because reach-1 is ×1; the band climbed 14→75 ins and close-rate fell 0.9→0.33 (permuter-class
scheduler/regalloc walls). **Wave 30 = the PIVOT (Drew's call): worker → `any-reach134` pool (reach-134, ×134).
13 banks × propagated ×134 → fleet 61.22→61.73% (+0.51% in ONE wave, ~8.5× the entire reach-1 run).** `tractable`
& `giants` pools are byte-exhausted (Phase 19/20); `any-reach134` (STUB-class reach-134 fns the WAVE/PINS/STRUCT
`tractable` pool never covered) is the live ×134 fuel. **GRINDER RUNNING** (token-free decomp-permuter on backlog
close≤30 near-misses; `.run/auto/STOP` CLEARED per Drew's explicit authorization "run the grinder / permission to do
whatever"; kill switch is now `bash tools/auto_stop.sh` / interrupt). **12 new cookbook idioms** distilled
(`commit:0225 commit:0227 commit:0230 commit:0232 commit:0235 commit:0237 commit:0240 commit:0243 commit:0245 commit:0247 commit:0249 commit:0253`); the last CRACKS
a false dead-end — the GTE-`sqr` cop2-nop family was wrongly recorded "unproducible" (objdump elides zero-word runs →
false match_one miss; verify on RAW bytes via `objcopy`). **TWO pool-exclusion bugs FIXED** (`commit:0228`
`plumbing_blocked` scans ALL raw backlog records; `commit:0239` NEW `reserved_walls` skips ≥2×-redrafted near-miss walls)
→ ~149+ churners skipped. **CURRENT:** orch_state `pool=any-reach134 waves=30`; worker continues reach-134 (fresh
`any-reach134` thinning → then `--mode auto`/`--class` to re-attempt reach-134 backlog walls with the 12 new idioms,
each ×134); grinder grinds alongside. NEXT cookbook fuel: the ~7-fn GTE-sqr family (idiom `commit:0253`).

**Fleet ≈ 61.16% byte-identical** *(↑ 61.19% — see SESSION UPDATE above)* · 136/136 binaries byte-identical · 0 NON_MATCHING.
**Nothing running** — grinder STOPPED (Drew; `.run/auto/STOP` present), no worker wave in flight. Paused at a
clean, committed checkpoint (HEAD = the reach-1 handoff commit). Committed locally; **not pushed** (R6 — Drew pushes).

**What this session did (×134 tail harvest → pivot):**
- Worker waves **13–16** on the cached reach-134 fuel: banked **+6** (incl. the 476-ins `func_80141CA4` ×134)
  + 1 grinder bank; **fleet 60.93% → 61.16%**. Yield diminished 3→2→0→1: the reach-134 ≤150-ins cached fuel is
  now **confirmed walls** (§20 IV-combine / LICM-hoist / schedule + DEF-side loose-typing; o0 pool empty; the
  capped-7 = the Phase-16 loose-typing wall). Re-firing them is the poor-ROI anti-pattern (Drew agreed).
- **Guard committed (`commit:0219`):** worker drafters now write ONLY their draft `.c` — a wave-13 drafter had
  appended UNVERIFIED near-miss idioms to the cookbook directly (distill owns the cookbook). See "Open for Drew".
- **PIVOT (Drew's call, gate-2 AskUserQuestion):** stop the reach-134 wall-waves + grinder; harvest the
  **reach-1 (overlay-unique) fuel** instead — abundant, small, far less loose-typed → much higher crack rate.

**★ THE REACH-1 FUEL IS BUILT + WIRED (this session's deliverable — ready for the fresh session):**
- **420 reach-1, region-main, draftable fns in `ov_SC01_077`, ALL cached** (298 prefetched this session via
  headless `DecompileFunctions.java` → `.run/ghidra_c`: 298 ok / 0 fail / 0 no-func). Small: median 47 ins,
  185 ≤40, 251 ≤60, 330 ≤100.
- **`tools/wave_targets.py --pool reach1`** serves them **SMALLEST-FIRST** (new pool, committed). The
  orchestrator's `POOLS` + `.run/auto/orch_state.json` are set to `reach1`, so **`prep --mode pool` serves it
  out of the box**. Verified: prep → clean 24-target batch of 14–15-ins fns; asm + ghidra_c paths resolve.
- **Leverage = ×1** — overlay-unique, so they bank in `ov_SC01_077` only (dedup_propagate skips reach<2, no
  ×134). But `ov_SC01_077` is the largest overlay → 420 small fns ≈ a real fleet chunk (plausibly **+1–3%**).

**THE PLAN — smallest-first idiom-MINING harvest (Drew's design, agreed):** run the same loop on the `reach1`
pool, **distilling after EVERY wave** (this is idiom-mining, not just banking): the tiny fns one-shot for free
%, the small-medium (~30–80 ins) band surfaces fresh gcc idioms → distill → the cookbook grows → bigger reach-1
fns one-shot, AND a new idiom occasionally cracks a reach-134 **wall** (×134 bonus, e.g. the Phase-18 pin idiom).

**FRESH-SESSION CYCLE (Drew starts + controls pacing — full runbook: `docs/automation-runbook.md` §reach-1):**
1. `.venv/bin/python tools/orchestrator.py prep --mode pool --n 24` → reach1 smallest-first batch → `.run/auto/wave_batch.json`.
2. Read the batch; launch `tools/workflows/worker_wave.js` with `args={draftDir:".run/drafts-wave", targets:<batch array PASTED VERBATIM>}`.
3. On completion: `.venv/bin/python tools/orchestrator.py finish --drafts .run/drafts-wave --commit` — **BACKGROUNDED + `dangerouslyDisableSandbox`** (foreground make build/git get sandbox-killed exit 144). Prints `{banked, near, verified, fleet_pct, …}`.
4. **Distill EVERY wave that has `verified` banks:** `tools/workflows/distill.js` `args={draftsDir:".run/drafts-wave", verified:<array>}` (the idiom-mining step).
5. Loop (~17 waves for all 420). close-rate should stay HIGH (small fns) → the orchestrator won't rotate off `reach1`; if it ever does (close-rate <0.15 ×2 → rotates to tractable walls), re-route: set `pool":"reach1"` in `.run/auto/orch_state.json`.
6. **Optional token-free grinder** (parallel, permutes reach-1 near-misses): `rm -f .run/auto/STOP && DRIVER=tools/grinder.py setsid nohup bash tools/auto_supervisor.sh --permute-secs 120 -j 14 >/dev/null 2>&1 &` (dangerouslyDisableSandbox). **STOP all:** `bash tools/auto_stop.sh`. Live %: `make report`.

**More fuel if 420 runs dry:** region `a` (65) + `o0` (8) reach-1 (excluded from the pool — different build paths
/ -O0 handling; add later); the deferred reach-134 walls + capped-7 (hand-finish backlog).

**Open for Drew:** the uncommitted 2 §21 cookbook bullets are **CANDIDATE / unverified** (from near-miss
`func_801775E0`) — marked as such this session; keep/refine/drop. ("Don't start the waves" was this session's
instruction; the fresh session launches them.)

---

## (SUPERSEDED by the REACH-1 HANDOFF above — historical trail) prior ×134 state (2026-06-22 07:40)

> The dated sections lower down (TRIP HAND-OFF, POST-REBOOT RESUME, FRESH-SESSION RUN LIVE, SUSTAINED LOOP,
> OPTION C) are HISTORICAL session-layers, kept for the trail. **This section is the authoritative current state.**

**Fleet: 209,593 / 344,010 = 60.93% byte-identical** · 136/136 binaries byte-identical · 0 NON_MATCHING.
**Nothing running** — grinder STOPPED (`.run/auto/STOP` present; `rm` it to allow relaunch), no worker wave in flight.
The loop is **paused at a clean, fully-committed checkpoint** (HEAD = `commit:0214`). All work committed locally; **not pushed** (R6 — Drew pushes).

**What this (overnight `/loop`) session did** (Drew: "keep waves going, don't stop till I check in ~8h" → ran 12 worker waves + the grinder):
- Fleet **59.05% → 60.93%** (+1.88%); ~55 functions banked (worker gates + 1 recovery gate + 1 grinder bank), each propagated ×134 where shared. dedup groups → 1560.
- **3 gate-safe tooling upgrades** (Option C + follow-ons), all committed:
  - `tools/sig_unify.py` — **DEF-side arity-extend recovery**: adopt the canonical engine_core.h param list on arity mismatch (unused params free at -O2). Banks the DEF-side loose-typing wall. (`commit:0200`)
  - `tools/grinder.py` — **blacklist** of permuter-won-but-gate-rejected (plumbing) fns → `.run/auto/grinder_blacklist.json` (13 fns); stops the futile churn. (`commit:0200`)
  - `tools/wave_targets.py` — **pool excludes self-MATCH-but-gate-rejected** near-misses (closeness==0 OR drafter "none — MATCH" verdict) so waves draft FRESH targets. (`commit:0205`, `commit:0208`)
- **6 new cookbook idioms** (4 distilled + 2 drafter-authored): cookbook §21 + §22. (`commit:0194 commit:0196 commit:0198 commit:0203 commit:0211`)
- **Grinder's work:** banked 1 (`func_801493D0`, permuter), blacklisted 13 plumbing-bound near-misses, token-free. It went 0→1 banks *after* the Option-C fixes.

**Key finding (where the wall is now):** the **tractable reach-134 ≤150-ins pool is depleting** — easy fresh wins are banked; close-rate fell from ~0.25 to **0.037 on wave 12**. What remains in this size-band is the genuine hard tail: DEF-side plumbing (`sig_unify` handles the simple arity case; the rest is multi-way loose typing) + the §20 **IV-combine** (`combine_givs` won't fold byte+halfword-RMW) and **LICM-hoist** (`move_movables` threshold) walls — drafters correctly stub these "unsteerable from C." They are **backlog / hand-finish fuel**, not re-draftable.

**HOW TO RESUME the loop** (the proven cycle; grinder is optional — `rm .run/auto/STOP` then relaunch per `docs/automation-runbook.md`):
1. `rm .run/auto/STOP` (only if relaunching the grinder).
2. `.venv/bin/python tools/orchestrator.py prep --mode pool --n 24` → writes `.run/auto/wave_batch.json`. **Use `--mode pool`** (auto-mode keeps firing class-focused REGALLOC waves on a saturated class; pool harvests fresh). The orchestrator auto-rotates `s["pool"]` tractable→giants→o0 when close-rate <0.15 for 2 waves — **so when tractable yield stays low (it's there now), the next prep will serve `giants`; let it.**
3. Read `.run/auto/wave_batch.json`; launch the `tools/workflows/worker_wave.js` Workflow with `args={draftDir:".run/drafts-wave", targets:<the batch array PASTED VERBATIM>}` (Workflow scripts have no fs access; transcribe carefully).
4. On completion: `.venv/bin/python tools/orchestrator.py finish --drafts .run/drafts-wave --commit` — **run BACKGROUNDED + `dangerouslyDisableSandbox`** (foreground `make build`/`git` get sandbox-killed exit 144; detached daemons escape it). Prints `{banked, propagated, verified, fleet_pct, ...}`.
5. If a *banked* fn flags a genuinely new idiom, launch `tools/workflows/distill.js` with `args={draftsDir:".run/drafts-wave", verified:<array>}` (else skip — distill is conservative; the drafter's "new idiom" claim is often already covered).
6. Loop. The byte-gate (G3/P9) is the sole arbiter; a wrong draft reverts, never banks. Each bank auto-commits.

### ▶ QUEUED 10-HOUR RUN — Drew starts this in the FRESH SESSION (do NOT start now; 2026-06-22 07:45)

Drew's call: **continue** (not close yet) — queue ~10h more of waves + grinder, drawing down the remaining
fuel, then close after. **Everything below is STAGED, NOTHING STARTED** (`.run/auto/STOP` is present; no wave running).

**Fuel verified (all cached — NO MCP/prefetch needed for the run):** tractable **80** + giants **28** + o0 **9**
cached-unbanked non-wall (167 reach-134 total); 563 Ghidra-C cached; 96 walls/plumbing excluded. Grinder has
**21 eligible near-misses** to start on (then self-feeds on each wave's new near-misses). Enough for ~15–20 waves.
**First wave batch staged:** `.run/auto/queued_wave1.json` (23 tractable, = wave 13) — informational; the cycle's
`prep` regenerates it.

**FRESH-SESSION START SEQUENCE (paste in order):**
1. **Grinder** (token-free, detached — run with `dangerouslyDisableSandbox`):
   `rm -f .run/auto/STOP && DRIVER=tools/grinder.py setsid nohup bash tools/auto_supervisor.sh --permute-secs 120 -j 14 >/dev/null 2>&1 & disown`
   (it stops the MCP first — fine, the run is cache-based; monitor `bash tools/auto_status.sh`).
2. **Worker loop** — run the cycle in “HOW TO RESUME” above (prep --mode pool → launch `worker_wave.js` →
   `finish --commit` backgrounded+`dangerouslyDisableSandbox` → distill-if-flagged → repeat) for ~15–20 waves.
   The pool **auto-rotates tractable→giants→o0** as close-rate drops (`low_streak`=1 now; giants is the high-byte-weight
   payoff). Run it as a `/loop` (self-paced) or hand-cycle. **STOP:** `bash tools/auto_stop.sh` + interrupt the loop.

**Expected:** ~+1–2% fleet over the run (diminishing — the hard tail dominates as fuel draws down). Then **T7 (close
Phase 21 → PhaseEnd)** is the natural next step. The byte-gate guarantees correctness unattended; worst case = "it paused."

**Pointers:** runbook `docs/automation-runbook.md` · backlog ledger `docs/backlog.md` (+ `.run/backlog.jsonl`, near-miss drafts `.run/backlog_drafts/`) · diagnostics `.run/{diag_plumbing,repro_gate,test_defsig}.py` (gitignored scratch) · monitor `bash tools/auto_status.sh`.

---

## Locked decisions (AskUserQuestion, 2026-06-21)
1. **Milestone = build→validate→stage, then close.** Sample-validate a few hours hands-on, bank that increment, populate the backlog, close ready-to-launch.
2. **Keep-alive = hybrid.** `/loop` self-pace primary + external `claude --continue` watcher fallback; `auto_stop.sh` = kill switch.
3. **Run posture = balanced, ROI-gated.** Worker waves per-pool until close-rate drops K rounds → route next; free permuter grinder in parallel; everything logs to backlog.

## Architecture (three components, one gate, one ledger)
- **Grinder (token-free)** = existing `tools/auto_driver.py` + `auto_supervisor.sh`, repointed to permute the worker's near-misses + log backlog.
- **Worker (token-heavy, LLM)** = NEW Workflow, parallel drafter agents (`opts.effort:'xHigh'`) using the §17–§20 toolkit → serial gate stage → compact summary.
- **Orchestrator (me, Max)** = ROI loop + hybrid keep-alive; routes pools, banks checkpoints, maintains `docs/backlog.md`.
- Both bank through the same `harvest_verify` gate + `dedup_propagate`; both log to the same backlog ledger.
- Effort: stay at Max all phase; Workflow sets per-agent xHigh (no R26/R27 toggle dance).

## Task checklist
- [x] **T1 — Target-pool manifest + giants byte-verification** (no MCP; Max) → `.run/fuel_manifest.json`; h_exact-verify the 28 giants are genuinely ×134 (R14). **DONE.**
- [x] **T2 — Fuel prefetch → complete Ghidra-C cache** (MCP-stop headless; Max) → `.run/ghidra_c/` cache-complete over the manifest. **DONE.**
- [x] **T3 — Backlog ledger + shared deterministic bank/log stage** (Max) → `tools/gate_stage.py` + `tools/backlog.py` + `docs/backlog.md`; validated on a real 30-draft sample (banked+propagated+logged). **DONE.**
- [x] **T4 — Worker Workflow** (Max; agents xHigh) → `tools/workflows/worker_wave.js` + `tools/wave_targets.py`. **VALIDATED.**
- [x] **T5 — Grinder daemon** (xHigh) → `tools/grinder.py` (permutes backlog near-misses → gate_stage) + `auto_supervisor.sh` (DRIVER-param). **VALIDATED.**
- [x] **T6 — ROI orchestrator + hybrid keep-alive + launch** (Max) → `tools/orchestrator.py` built; **the worker `/loop` RAN — 12 waves across 2026-06-21→22, fleet 59.05%→60.93%** (see ★ CURRENT STATE). Worker driven by Workflow-completion (not the hybrid keep-alive); grinder ran detached. **DONE.**
- [ ] **T7 — Stage ready-to-launch + Phase close (PhaseEnd)** (Max, Tier-1) — pending Drew's gate-2 milestone confirmation. The "build→validate→stage" milestone is met; closing is defensible (see ★ CURRENT STATE open decision).

**Current task:** paused at a clean checkpoint after 12 worker waves (fleet 60.93%). NEXT = Drew's call (rotate worker to `giants` pool / other band / **close Phase 21 → T7 PhaseEnd**). See ★ CURRENT STATE & FRESH-SESSION RESUME at the top.

## Verification invariant (every banked step + at close)
`make clean && (extract all 136) && make check-all` → 136/136 byte-identical (R22); `make report` → 0 NON_MATCHING (G4), `dedup-check 0 failed`.

### T4/T5/T6 — worker + grinder + orchestrator (2026-06-21, trip-imminent push)
- **T4 worker Workflow** (`tools/workflows/worker_wave.js`): parallel xHigh drafter agents, each given the asm + cached Ghidra-C + the §17–20 toolkit; writes its best C; orchestrator gates after. `tools/wave_targets.py` selects the batch (ROI pool). **args gotcha (§20): the harness serializes args to a JSON STRING → the script parses it.** VALIDATED: a 3-target wave → all 3 self-MATCH; whole-binary gate **banked func_80164530 ×134** (5 register-pins + offset-fold + scheduling — a hard toolkit match), 1 near + 1 failed logged. ~275k tokens / 13 min for 3 agents. fleet 58.90→**58.98%**.
- **T5 grinder** (`tools/grinder.py`): token-free — permutes backlog near-misses (close≤30) → gate_stage → bank; STOP/heartbeat, idles for new worker fuel. VALIDATED: permuter WON func_8014F3E8 but the whole-binary gate correctly REJECTED it (§20 — match_one/permuter over-predict; gate is truth; integrity intact, 0 wrong banked). `auto_supervisor.sh` now `DRIVER`-parameterized (launch grinder under it).
- **T6 orchestrator** (`tools/orchestrator.py`): `prep` (pick ROI pool → emit wave batch) / `finish` (gate_stage → record close-rate → rotate pool when tapped) / `status`. Pool rotation tractable→giants→o0→capped, ROI-gated (threshold 0.15, patience 2). The model launches the Workflow between prep/finish (the one step only it can do).
- **gate_stage flock**: grinder + orchestrator gates serialize on `.run/auto/gate.lock` (one build/commit at a time — safe concurrency).
- **SANDBOX finding:** foreground Bash-tool builds (`make build`/`git`) get killed (exit 144) by the sandbox; **detached daemons (setsid/nohup) escape it** — so the launched grinder/orchestrator build fine; interactive gates need `dangerouslyDisableSandbox`.

## TRIP HAND-OFF (2026-06-21) — what's running, what's staged

**Status:** the automation manager is BUILT + VALIDATED end-to-end; fleet **58.82% → 58.98%** (3 real
matches banked during validation: func_801710DC, func_80164530, + the T3 sample; all ×134, 136/136
byte-identical). Drew is travelling **with remote access** to this dev box.

**RUNNING NOW (autonomous, token-free):**
- The **grinder** (`tools/grinder.py` under `tools/auto_supervisor.sh`, launched detached) — permutes the
  backlog's closest near-misses → byte-gate → banks → ×134; idles for worker fuel; supervisor relaunches
  on crash. Monitor: `tools/auto_status.sh`. Stop: `tools/auto_stop.sh`.

**STAGED (Drew drives remotely — the high-yield token engine):**
- The **worker** waves: `tools/orchestrator.py prep` → launch the `tools/workflows/worker_wave.js`
  Workflow → `tools/orchestrator.py finish --commit`. Run it via **`/loop`** (the runbook has the exact
  cycle prompt). ~24 xHigh agents/wave, ~275k tokens/wave; ROI-gated pool rotation. **The full runbook
  is `docs/automation-runbook.md`.**
- An in-flight 16-target worker wave (`.run/drafts-wave2`) was launched at hand-off; gate it with
  `tools/orchestrator.py finish --drafts .run/drafts-wave2 --commit` (or it's the first thing the /loop
  picks up).

**Why safe to leave running:** the whole-binary byte-gate (G3/P9) is the sole arbiter — a wrong draft is
reverted, NEVER banked; `make check-all` stays 136/136; every bank is a checkpoint commit (push is manual,
R6); `auto_stop.sh` halts at the next safe boundary. Worst case of any crash = "it paused," never "it broke."

**Phase close:** T7 (formal PhaseEnd) awaits Drew's gate-2 milestone confirmation on return. Until then this
file + `docs/automation-runbook.md` are the durable state. Sandbox note: detached daemons build fine;
interactive build gates need `dangerouslyDisableSandbox`.

## POST-REBOOT RESUME (2026-06-21) — the learning flywheel + ready for the fresh-session run

After the reboot (BIOS startup-on-power-loss configured; Drew has remote access):
- **R1 — gated the 15 pre-reboot drafts:** banked **4** (func_80156FA8/801678F0/80156848/8017742C; 2 propagated
  ×134); backlog 30→41. R22 check-all **136/136**. (The standalone gate was killed pre-commit twice — a harness
  quirk on detached `nohup gate_stage` runs; recovered by committing the working tree. Does NOT affect the
  orchestrator, which calls gate_stage **in-process**.)
- **R2/R3 — the learning flywheel (Drew-approved):**
  - Residual gcc-quirk class now **travels with the draft**: the drafter stamps `// @class` / `// @stuck`;
    `gate_stage` logs the worker's class (not the coarse manifest class) → enables class buckets.
  - **Class-grouped waves:** `wave_targets.py --class <C>` / `--list-classes` (REGALLOC/SCHEDULE/REMAT/STRUCT/
    IV/LOOPGUARD/LOOSE/PLUMBING). `orchestrator prep` auto-fires a class-focused re-attempt wave when a class
    accrues ≥6 near-misses (drafters get the prior stuck-point), else a fresh pool harvest.
  - **Distill** (`tools/workflows/distill.js`): post-wave agent extracts NEW byte-verified gcc idioms → cookbook
    §21 (R16, conservative); drafters read the **live** cookbook so idioms feed forward (the Phase-18 loop, automated).
- **R4 — grinder relaunched** (token-free); fleet **59.05%** (phase: 58.82→59.05, +0.23%, 5 fns ×134); 136/136;
  tree clean. **Ready for Drew's fresh session to run the worker `/loop`** (this session is at low context).

**Fresh-session launch (Drew):** start a Claude Code session here → run **`/loop`** with the cycle in
`docs/automation-runbook.md` (prep → worker_wave Workflow → finish gate → distill). The grinder is already
running alongside. Monitor: `bash tools/auto_status.sh`. Stop: `bash tools/auto_stop.sh`.

## FRESH-SESSION RUN LIVE (2026-06-21 ~14:40 — Drew away ~8h, remote access)

Drew launched the unattended grind ("run the worker /loop cycle, then start the grinder; I'll check back in ~8h").
Both engines are RUNNING:
- **Worker** — wave 1 launched as Workflow `wx91bmadi` (run `wf_b173a013-d6a`): 24 xHigh drafters over the
  **tractable** reach-134 pool (nins 93–142). The loop is driven by **Workflow-completion notifications** (not a
  polling timer): on each wave's completion the orchestrator runs `finish --commit` (gate→bank→propagate ×134→
  backlog), `distill` if anything verified, then `prep`+launches the next wave. Race-free (one wave at a time;
  `prep` rm-rf's `.run/drafts-wave`). ROI-gated pool rotation via `orch_state.json`.
- **Grinder** — relaunched detached (was dead post-reboot, heartbeat 24 min stale): supervisor pid 2573950 +
  `grinder.py` pid 2574026, `--permute-secs 120 -j 14`, token-free, draining the backlog near-misses.
- Fleet at launch: **59.05%**, 136/136 byte-identical, 0 NON_MATCHING. Gate (G3/P9) is the sole arbiter — a wrong
  draft is reverted, never banked; worst case of any crash is "it paused."
- Monitor: `bash tools/auto_status.sh`. Stop both: `bash tools/auto_stop.sh` (then `rm .run/auto/STOP` to resume).
- **Sandbox note (R/§ build-infra):** my foreground `make build`/`git` calls get sandbox-killed (exit 144) →
  `orchestrator.py finish` and any commit run with `dangerouslyDisableSandbox`; detached daemons (grinder) escape it.

**Run progress (worker waves):**
| Cycle | Wave drafted | Byte-banked | Fleet | Commit |
|---|---|---|---|---|
| 1 | 24 (19 self-MATCH) | 7 (4 ×134) | 59.05→59.21% | `commit:0193`; distill `commit:0194` (cookbook §21 added) |
| 2 | 24 (18 self-MATCH) | 5 (4 ×134) | 59.21→59.37% | `commit:0195` |
| 3 | 24 (17 self-MATCH) | 7 (6 ×134) | 59.37→59.60% | `commit:0197`; distill `commit:0198` |
| recovery | 7 close=0 re-gated | 2 (×134) | 59.60→**59.68%** | `commit:0199` (sig_unify DEF-side fix) |
- **Distill flywheel:** 3 NEW byte-verified cookbook idioms added across the 3 waves (`commit:0194` Blk16/memcpy
  unaligned-copy; `commit:0196` disjoint-bits add→ori re-tie barrier; `commit:0198` giv-anchor store-order).
- **Wave-2 "6.5h" was NOT throttling** — it was idle on a CC **permission prompt** (Drew approved on check-in);
  waves 1 & 3 ran in ~25–32 min. (R14: corrected my earlier rate-limit read.)

## OPTION C — grinder fix + DEF-side recovery (Drew-approved, 2026-06-21 ~22:50)
The grinder had banked **0 in ~8h**: stuck re-permuting 2 plumbing-bound near-misses (`func_8014F3E8`,
`func_8014FE60`) — permuter "wins" them (base already masked-0) but the whole-binary gate correctly rejects every
cycle; after idle it did `tried.clear()` and looped forever (§20 trap). Fixed BOTH halves of option C:
- **(a) `tools/grinder.py` blacklist:** record every permuter-won/gate-rejected fn → `.run/auto/grinder_blacklist.json`,
  skip permanently, survives restarts. Frees its CPU for genuine regalloc/schedule near-misses. Grinder restarted with it.
- **(b) `tools/sig_unify.py` DEF-side fix:** diagnosed the wide self-MATCH→bank gap as the **DEF-side loose-typing
  wall** (draft's byte-correct def has FEWER params than engine_core.h's canonical cross-overlay decl →
  `conflicting types`). `rewrite_def` previously only rewrote params on arity MATCH (return-type-only fallback
  otherwise). Patched it to **adopt the canonical param list on arity mismatch** (draft names + synth `_argN` for
  the unused extras; they sit in `$a0–$a3`, free at -O2). Validated: banked `func_8016EDEC` + `func_8016EE40`
  through the real gate (`commit:0199`). **Compounds: it's in the gate pipeline, so every future wave + the grinder
  now auto-recover DEF-side near-misses.** (Remaining close=0: a data-conflict + narrow-param arity gcc's
  promotion rule blocks + multi-way loose typing — genuinely harder, diminishing returns.)

**Session totals (2026-06-21):** 3 worker waves + recovery → **21 fns banked**, fleet **59.05% → 59.68%** (+0.63%),
136/136 byte-identical (per-bank gate G3/P9; full check-all deferred to a checkpoint), 0 NON_MATCHING, 3 new
cookbook idioms, grinder + sig_unify both upgraded. Diagnostics in `.run/{diag_plumbing,repro_gate,test_defsig}.py`.

## SUSTAINED LOOP (2026-06-21→22, Drew: "keep waves going, don't stop till I check in ~8h")
Continuous worker loop running, driven by Workflow-completion (NOT a timer): per wave →
`orchestrator.py finish --commit` (gate+bank+propagate ×134) → `distill.js` if verified → `orchestrator.py prep
--mode pool --n 24` → launch `worker_wave.js` with the batch pasted **verbatim** from the compact dump (Workflow
scripts have no fs access; transcribe carefully). Gate/finish run **backgrounded + dangerouslyDisableSandbox**
(foreground `make build`/`git` get sandbox-killed exit 144). Grinder runs alongside (token-free, blacklist-aware).
- **POOL-mode override (policy):** auto-mode keeps firing class-focused REGALLOC waves, but that class has
  saturated with permuter-class/DEF-side-plumbing residuals agents can't crack from C → low yield. Use
  `prep --mode pool` to harvest FRESH reach-134 targets (higher yield); leave regalloc residuals to the grinder
  (permuter) + backlog (hand-finishing). The DEF-side `close=0` set (func_80174CB0/80169228/80167714 …) won't bank
  via re-drafting — they're hand-finish fuel.
- **Running tally (this session, fleet 59.05% start):** waves 1-6 launched; banked via worker gates + the sig_unify
  recovery. Fleet **59.87%** after wave 5 (wave 6 in flight). 4 new cookbook idioms distilled
  (`commit:0194 commit:0196 commit:0198 commit:0203`). Commits `commit:0193…commit:0202` + option-C `commit:0200`.
- **To resume after compaction:** read this section + `docs/automation-runbook.md`; the next step is always
  gate the in-flight wave (`.run/auto/finish_wave<N>.log` / orchestrator finish) → distill → prep --mode pool →
  launch. Stop only when Drew says so (`bash tools/auto_stop.sh` halts the grinder).

## Blockers
(none — grinder running blacklist-aware + enhanced sig_unify; worker loop sustained per Drew until check-in.)

## Per-task log

### T1 — fuel manifest + giants byte-verification (DONE, 2026-06-21)
- New tool `tools/build_fuel_manifest.py` → `.run/fuel_manifest.json` (gitignored, regenerable). reach RECOMPUTED from the current 134 overlay sigs (distinct-overlay h_exact histogram), not trusted from cached fields (R14).
- **803 live func_ stubs** classified: GIANT 28, WAVE 425, STRUCT 148, PINS 104, STUB 88, O0 9, O1 1 (+1 named stub `listCdBuffer` skipped). Reach buckets: 310 reach-134, 486 reach-1 (overlay-unique), 7 partial.
- **R14 giants: 28/28 verified genuinely reach-134** (byte-identical ×134 — the giants' label is honest, unlike the -O0 cluster). Top leverage: func_80144B9C (770 ins), func_80141CA4 (476), func_80132784 (400).
- **R14 -O0 nuance (byte-finding):** 8/9 -O0 stubs are overlay-local (reach-1, matches Phase-20), but **func_8013C08C is reach-134** — a genuine exception to the blanket "overlay-local" assumption (propagatable ×134 if matched).
- **T2 workload:** 253 reach-134 stubs uncached (of 310); tractable reach-134 (WAVE/PINS/STRUCT ≤150 ins) = 223, 171 uncached; giants 25/28 uncached. Ghidra-C cache currently 300.
- No MCP, no build mutation. Checkpoint commit: tool + this log.

### T2 — fuel prefetch → Ghidra-C cache complete (DONE, 2026-06-21)
- Stopped MCP (R23, clean Save). Headless `analyzeHeadless ... -process ov_SC01_077 -readOnly -postScript DecompileFunctions.java <addrs> .run/ghidra_c` over the **263 uncached ROI-pool fns** → **263 ok / 0 fail / 0 no-func**. Cache 300 → **563**.
- **Naming bug found + fixed:** Ghidra emits `FUN_<lowerhex>` (raw-import default); consumers + the 300 existing files use `func_<UPPERHEX>`. Renamed the 263, and **fixed `DecompileFunctions.java` to key output by entry address (`func_<UPPER>`)** so re-prefetch is reproducible. Added `build_fuel_manifest.py --emit-prefetch` (reproducible addr-list for the T7 runbook).
- **T2 verification (cache-complete):** ROI-pool fuel = **325 fns, ALL cached, 0 uncached** (28/28 giants, 310/310 reach-134, 7/7 capped). The unattended run will never need live MCP.
- Scope (P9): 349 reach-1 ×1-leverage fns intentionally NOT prefetched (not in the ROI pool rotation: tractable reach-134 → giants → -O0 → capped). A later prefetch can add them if ever needed.
- MCP left STOPPED (the run is cache-based; the grinder supervisor stops it anyway). `ghidra/ db.*.gbf` churn is the MCP-stop's no-op SLUS save — R23 restart-noise, NOT staged.
- Checkpoint commit: `DecompileFunctions.java` + `build_fuel_manifest.py` + this log (cache + manifest are gitignored/regenerable).

### T3 — backlog ledger + shared deterministic gate stage (DONE, 2026-06-21)
- **`tools/backlog.py`** — the near-miss ledger (`.run/backlog.jsonl` append + `docs/backlog.md` ranked render). Ranks by reach → closeness → size; **drop-now-matched** filter (a banked fn leaves the backlog, P9). Tested: append/render/show + drop-matched all correct.
- **`tools/gate_stage.py`** — the shared deterministic spine (worker + grinder call it): drafts → `canon_resident_calls → cast_call_sites → sig_unify → harvest_verify --chunk 1 → dedup_propagate --auto-from` → log non-matches to backlog → compact JSON summary. Byte-gate is the sole arbiter (G3/P9).
- **Validated end-to-end** on a real 30-draft m2c sample of reach-134 main WAVE stubs → `{drafts:30, banked:1, propagated:2, near:20, failed:8}`. **func_801710DC banked + propagated ×134** (dedup 1506→1508, every ov_*.c touched); **29 near-misses logged + ranked** (top: func_80174684 close=0 "MATCH but plumbing", func_8014F3E8 close=1; captured the §20 unsteerable regalloc class func_80149374/801493D0). All paths exercised: bank→propagate→log→render→summary.
- **R22: `make check-all` → 136/136 byte-identical**; `make report` → fleet **58.82% → 58.90%** (+0.08%, the func_801710DC ×134 increment), `dedup-check 1508 validated / 0 failed` (G3/P9). A real, byte-gated increment — kept.
- **Capped-fns reframe (R14):** the 7 capped are matched-**inline** (propagation-blocked on undeclared callees/data), NOT draftable stubs — so they don't flow through the gate stage's draft path; the plan's "warm-up on the 7 capped" premise was slightly off. The stronger honest validation is the real 30-draft sample above. The capped propagation-recovery is **deferred to the worker** (T4 re-drafts them through gate_stage's recovery pipeline; the manifest's `capped_recovery` documents them). Not claiming the unbanked ~+0.3% (P9).
- Best-draft `.c` files saved to `.run/backlog_drafts/` (local, gitignored — Drew accesses them on this machine; `docs/backlog.md` is the committed index).
- Checkpoint commit: the 2 tools + `docs/backlog.md` + the func_801710DC match & ×134 propagation (src/ov_*, engine_core.h, dedup.us.yaml, progress digests) + this log.

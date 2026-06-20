# Guided Hand-Matching — Process Guide & Phase-17 Findings

> **Created 2026-06-19 (Phase 17), mid-session, so the lessons survive a fresh session.**
> This is the replicable process for matching the struct-heavy shared-core residual by
> **Ghidra-driven hand-matching** — the approach that the Phase-17 demo proved works where the
> Phase-16 m2c+permuter brute-force topped out. Companion to `docs/matching-cookbook.md` (idiom
> catalog) and `docs/struct-core-pivot.md` (Phase-16 wall analysis). **Goal: make this so complete
> it can later be partly automated from the process itself.**

---

## 0. THE HEADLINE FINDING (go/no-go = GO)

**Phase 16 declared the loose-typing wall "fundamental / unfixable." This session disproves that for
the majority of functions.** The wall is really a **signature-CONSISTENCY problem**, and it dissolves
under **byte-neutral canonical-widening + the codebase's established cast idioms**.

**Demo close-rate: 4 of 5 sampled residuals reached a full whole-binary byte-match.**

| Function | m2c verdict | Result | Decisive fixes |
|---|---|---|---|
| `func_8012D3B4` | PERMUTER_CLASS (1-off) | ✅ CLOSED, **propagated ×134** | m2c ptr-vs-byte arithmetic; loose-typing: `RotTransPers` void→s32 widen + `(u16)D_800B9A02` cast |
| `func_8012832C` | STRUCTURAL_MISS (switch) | ✅ CLOSED (ov_SC01_077) | gcc reload s0-spill (restructure→rematerialize); branch polarity §T4; loose-typing: 3× void→s32 widen |
| `func_8015F89C` | MCOMPILE_fnptr-call | ✅ CLOSED (ov_SC01_077) | type the fn-ptr table (`void (*D_X[])(void*)`); arity conflict `func_80161208` via the **cast idiom** `((s32(*)(void*))f)(arg)`; canonical-sig-match the callees |
| `func_80147B5C` | STRUCTURAL_MISS (pure struct) | ✅ CLOSED (ov_SC01_077) | **canonical-sig-match the fn's own param** (`s32 a0` per canonical, cast to ptr in body); raw offset casts. *match_one MATCH first try.* |
| `func_8012A328` | STRUCTURAL_MISS (globals+call) | ⚠️ 60/60 structure + correct regs, **1 instr off** | gcc GCSE/reload placement quirk (per-block rematerialize vs hoist) — the §10 hard tail; permuter floor-polluted, can't help |

**Every function reached *isolated* correctness (match_one MATCH or 60/60).** What separated the
closes from the miss was the **whole-binary** step: the closes' blockers were *loose-typing /
signature-consistency conflicts* (deterministically fixable — see §3a), the miss's blocker a *gcc
placement quirk* (the genuine, minority hard tail). **The fnptr-call class (§15-S2, 85 fns) and the
pure-struct class are matchable; even the §14e "arity wall" is partly breakable via the cast idiom.**

---

## 1. THE LOOP (the replicable process)

For one residual function `func_<ADDR>` in the harvest source `ov_SC01_077`:

1. **Richest decompile — use BOTH:**
   - **Ghidra whole-binary** `get_code(0x<ADDR>, decompiler)` — resolves locals vs **globals** vs
     **callee identities** (whole-program view m2c lacks). The MCP server must serve the overlay
     (`tools/ghidra_mcp_start.sh ov_SC01_077`, then `/mcp`, R29). get_code is async → poll
     `get_task_status`.
   - **m2c** `tools/m2c/m2c.py -t mipsel-gcc-c -f func_<ADDR> --context .run/actor_ctx2.c <s>` — a
     per-function scaffold (decompile.py hardcodes the main-EXE path; call m2c directly for overlays).
   - **The ASM is the final arbiter** for addressing + exact codegen (m2c and Ghidra often *disagree*
     on local/global modeling — e.g. `func_8012A328`: m2c made `D_80126B58` a struct, Ghidra made the
     same bytes separate globals; the asm's `lui $s1` reuse settled it).

2. **Hand-write correct C** — fix m2c's structural/arithmetic errors with Ghidra's structure + the
   actor struct (`docs/actor-struct.md`) + the cookbook idioms (§below).

3. **Iterate isolated** with `tools/match_one.py func_<ADDR> --c <draft> --asm-subdir
   asm/ov_SC01_077/nonmatchings/ov_SC01_077` (fast, relocation-masked; prints per-instruction diff).
   Drive to `MATCH (N ins)`.

4. **Resolve loose-typing for the whole binary** (THE step Phase 16 missed):
   - **Canonical-widening:** a callee declared `void` by a prior harvest (because *that* caller
     ignored its `$v0` return) but *this* function uses the return → widen the canonical to `s32`.
     **Byte-neutral** (a function with no explicit `return` compiles identically as `void` or `s32`).
     Edit the single `extern void func_X` in `src/shared/engine_core.h` (or the inline def in the
     overlay `.c`) to `extern s32 func_X`.
   - **Cast idiom:** keep the canonical `s16`, write `(u16)D_X` at unsigned use-sites (the asm `lhu`).
     This is the codebase's own established pattern (e.g. engine_core.h `(u16)D_800B9A02 * 20`).
   - **Match existing canonical sigs** for every callee/global from `engine_core.h` (grep it) so the
     one-big-TU `ov_SC01_077.c` has no conflicting declarations.

5. **Whole-binary gate (THE arbiter, G3/P9):** `tools/harvest_verify.py --binary ov_SC01_077 --src
   src/ov_SC01_077/ov_SC01_077.c --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077 --out
   build/ov_SC01_077/ov_SC01_077 --good-sha d19c9580a02dc63ba1f0e7e0c770f3b10de35635 --drafts <dir>`.
   It substitutes the draft, builds the whole overlay, keeps it iff SHA == d19c9580 (else reverts).
   **CRUX: match_one MATCH ≠ whole-binary match** — match_one masks `jal`/`%hi`/`%lo`, so it can't see
   callee-signature conflicts. The build is the only truth.

6. **Propagate ×134:** `tools/dedup_propagate.py --addr 0x<ADDR> --source-overlay ov_SC01_077` (byte-
   gates every overlay, fail-closed; authors a `DEFINE_func_<ADDR>` macro in engine_core.h, registers
   the group in `config/dedup.us.yaml`). Then `make check-all` → 136/136 (R22).

To diagnose a whole-binary FAIL: substitute the draft into a `.c` copy, `make build BINARY=ov_SC01_077
2>&1 | grep -iE 'conflicting|redefin|error'`, read the conflict lines, fix the sig, revert.

---

## 2. IDIOMS & FIXES discovered this session (fold into cookbook §1/§2/§16)

- **m2c pointer-vs-byte arithmetic (HIGH-frequency m2c bug).** m2c writes `&D_X + (i * K)` using
  `s32*` pointer arithmetic (scales ×4), where the target indexes by **bytes**. Tell: a shift off by
  ×4 (e.g. `sll v0,0x4` vs `sll v0,2`). Fix: `*(s32 *)((s8 *)&D_X + (i * K))`. (`func_8012D3B4`.)
- **Branch polarity (§T4 restated).** A lone `beqz↔bnez` flip with swapped successors = put the
  target's **fall-through** block in the `if`, the branched-to block in the `else`. m2c's `== 0` form
  was right; "improving" it to `!= 0` + swapped arms broke it. (`func_8012832C`.)
- **gcc reload rematerialization vs callee-saved spill.** A cheap constant (`v0 = 1`) held **live
  across a call** makes gcc spill it to a callee-saved reg (`s0`, +frame). The original instead
  **rematerializes** the constant at each exit. Fix: restructure so the constant is set in the
  *else* / at the exits, not before the call (`if (cond && call()==0) v0=f(); else v0=1;`).
  (`func_8012832C`.)
- **Cross-jump call structure.** To get a single shared `jal` with **per-branch arg setup**
  (a0/a2 duplicated, only a1 differing), write the call **inside each branch**, converging via gotos
  to a shared tail; gcc cross-jumps the identical `jal`+tail. One call site → gcc hoists (too few
  ins); 4+ → gcc under-merges (too many); exactly the shared-block count matches. (`func_8012A328`.)
- **Dual base pointers.** A global loaded once into a callee-saved reg and reused at several offsets
  (`lui $s1,D_X` then `lh 0xNN($s1)`) = model it as a pointer variable `u8 *p = D_X;` referenced
  across the call. Two such bases → two callee-saved regs (s0/s1); their allocation order follows
  first-use order. (`func_8012A328`.)
- **s32 vs s16 for sign-extended values passed to calls.** A value loaded `lh` (sign-extended to 32)
  and passed to a function wants the local + the param typed `s32`, not `s16` — `s16` adds a
  redundant `sll/sra` re-extension. (`func_8012A328`.)
- **THE HARD RESIDUAL (the §10 minority tail):** **per-block address rematerialization vs hoist.** The
  original re-materializes a global's address (`lui+addiu` into a callee-saved reg) **per block**
  while sharing the post-call store; gcc from clean C either hoists it once (1 ins short, store
  merged) or makes the store per-block (over by N). The exact midpoint is a gcc GCSE/reload balance
  not cleanly source-steerable, and the **permuter can't score it** (object score floor-polluted by
  the masked global/call symbols, cookbook §10). 1 instruction, genuinely hard. (`func_8012A328` —
  best draft `.run/demo/func_8012A328.c`, the `p+q` form 61 vs 60.)
- **`lh`-vs-`lhu` fold defeat — the mask-local idiom (NEW, func_8014C308).** When the asm loads a signed
  field (`lh`) and ANDs it with a runtime mask `(x & 0xFFFF)`, writing `*(s16 *)f & (x & 0xFFFF)` **inline**
  lets gcc prove the result fits 16 bits → it folds the load to `lhu` and drops the separate `andi`. FIX:
  hoist the mask to a local — `s32 m = x & 0xFFFF; ... *(s16 *)f & m ...`. gcc can no longer prove `m ≤
  0xFFFF` at the AND, so it keeps `lh` + emits `andi m` then `and`. (Turned `lhu`+`and a3` into the target's
  `lh`+`andi v1`+`and`.)
- **Shared-return cross-jump clustering + branch-polarity control (NEW, func_8014C308).** When the original
  routes two (non-adjacent) predicate tests to ONE shared `return 0` block — so each test's branch-delay slot
  is free to hold the *next* test's constant and the tests branch with a particular polarity (`beq`/`bnez`
  *to* the shared block) — write BOTH as `goto ret0;` to a single trailing `ret0: return 0;`. gcc then makes
  `ret0` a labeled block reached by branches (correct polarity) and schedules the following test's constant
  into the delay slot — reproducing the original's clustering AND its register assignment (constants in the
  non-result reg). A lone `if (x) return 0;` instead **inlines** the return (`beqz`-skip, inverted polarity,
  constant lands in the result reg) → cascade. This fixed func_8014C308's idx 0–21 in one move; what remained
  was a pure v0↔v1 coalescing choice (permuter territory).
- **v0↔v1 result/constant coalescing (the residual after the above).** When a `result` default (`var = 1`)
  competes with a sequential `beq`-chain's constants for the return reg, gcc may put the constants in `v0` and
  the result in `v1` (extra `move v0,v1`), vs the target's result-in-`v0`/constants-in-`v1`. Not reliably
  source-steerable (tried: var-at-top → worse/`t0`; early-return → polarity issues). For a **relocs=0**
  function this is a CLEAN permuter target (no masked-symbol floor) — unlike the §10 call-heavy tail.
  (func_8014C308, ×134.)

---

## 3. LOOSE-TYPING CONFLICTS catalog (this session — all byte-neutral, fleet re-verified 136/136)

| Symbol | Was | Now | Where | Why |
|---|---|---|---|---|
| `RotTransPers` | `void` | `s32` | engine_core.h `DEFINE_func_8017C908` | func_8012D3B4 uses its return |
| `func_80029504` | `void` | `s32` | engine_core.h `DEFINE_func_80159120` | func_8012832C uses its return |
| `func_801288B0` | `void` | `s32` | ov_SC01_077.c inline def | func_8012832C uses its return |
| `func_801289F0` | `void` | `s32` | ov_SC01_077.c inline def | func_8012832C uses its return |
| `D_800B9A02` | `s16` (kept) | `(u16)` cast at use | func_8012D3B4 body | asm loads `lhu` |
| `func_80161208` | `s32 (void)` (kept) | cast at 1-arg call | func_8015F89C call | called 0-arg elsewhere, 1-arg (ptr) here |
| `func_801466F0` / `func_80147078` | — | match canonical sig in the draft | func_8015F89C decls | callee param types (s32/s32*/s16) |
| `func_80147B5C` (the fn itself) | `void(s32,void*)` canonical | declare param `s32`, cast in body | func_80147B5C def | callers pass the address as `s32` |

### §3a — THE SIGNATURE-CONSISTENCY RESOLUTION PLAYBOOK (the wall-breaker)

The Phase-16 "loose-typing wall" is really: *the same symbol is declared/used with different types
across the single overlay TU.* `match_one` (standalone) never sees it; the whole-binary build does.
**Five deterministic moves resolve almost all of it** (apply whichever the conflict needs):

1. **Return-widening (`void`→`s32`).** A callee declared `void` (a prior harvest ignored its `$v0`)
   but THIS fn uses the return → widen its canonical to `s32`. **Byte-neutral** (no explicit `return`
   ⇒ identical epilogue). Edit the single `extern void func_X` in engine_core.h / the overlay def.
2. **Sign cast (`(u16)`/`(s16)`).** Keep the canonical (`s16`); write `(u16)D_X` where the asm loads
   `lhu`. The codebase's own idiom.
3. **Arity cast** — *refines the §14e "arity wall = dead-end".* A callee called 0-arg by one fn and
   N-arg by another: keep the canonical `(void)`, and at the N-arg site **cast** —
   `((ret (*)(argtypes))func_X)(args)`. The codebase already does this (`((s32(*)(s32*))func_80161208)`).
   Works when the extra args are **pointers** (no default promotion); narrow-scalar arity is still hard.
4. **Param-type canonical-matching.** Declare every callee (and the fn's OWN params) with the EXACT
   canonical signature from engine_core.h (grep it), then cast inside the body. E.g. the canonical
   `func_80147B5C(s32 a0, void *a1)` passes an address as `s32` → write `void func_80147B5C(s32 arg0,
   void *arg1)` and access `*(s32 *)(arg0 + 0xNN)` (cast int→ptr, byte-neutral).
5. **Fn-ptr-table typing.** A `(*((idx*4)+D_x))(args)` call needs `D_x` typed as a function-pointer
   array — `extern void (*D_x[])(argtypes);` (engine_core.h often already has it) → m2c/hand C compiles
   and matches (`func_8015F89C`: `D_801891B8[arg0->f_0](arg0)`).

**Diagnosis loop:** `harvest_verify` FAIL → substitute into a `.c` copy → `make build BINARY=ov_SC01_077
2>&1 | grep -iE 'conflicting|redefin'` → each line names a symbol; `grep` its canonical in
engine_core.h → apply move 1–5 → revert the copy, re-gate. (Moves 1–4 are the bulk; func_8012D3B4 +
func_8012832C + func_8015F89C + func_80147B5C all closed this way.)

---

## 4. CURRENT STATE (what's banked / modified this session — do not redo)

- **BANKED matches (all in ov_SC01_077, byte-gated):** `func_8012D3B4` (propagated **×134** →
  `DEFINE_func_8012D3B4` in engine_core.h + `config/dedup.us.yaml`, 134 members); `func_8012832C`,
  `func_8015F89C`, `func_80147B5C` (inline in `ov_SC01_077.c`, not yet propagated — propagating
  func_8012832C/8015F89C would cascade their callee widenings across overlays; func_8015F89C reach is
  only ~3 anyway; func_80147B5C reaches 134). **5 sampled, 4 closed (80%).**
- **WIDENINGS in place (byte-neutral):** see §3 table.
- **NOT closed:** `func_8012A328` (60/60 structure + correct regs, 1-instr gcc quirk). Drafts +
  variants in `.run/demo/` (`func_8012A328.c` = best `p+q`; `v_*.c` = the experiments). `func_801298F4`
  also set aside (a walking-pointer codegen quirk — gcc strength-reduces `*q++` to indexed; the
  original keeps the walk; structure-confirmed by m2c+Ghidra).
- **Fleet:** `make check-all` → **136/136 byte-identical**; `make report` → **55.04%** (was 55.00% at
  this session's start, 54.48% at phase start); `dedup-check` 1409 validated / 0 failed.
- **Scratch:** all drafts under `.run/demo/`. Permuter setup at `.run/permuter/func_8012A328/` (base
  score 1680, floor-polluted — abandoned).

### Session 3 (2026-06-19, normal Max session) — "sample 2 more to firm the rate"
Sampled 1 fnptr + several struct residuals via the §1 loop. **Headline: the loop reconstructs CORRECT
bodies every time (4/4 this session), but the byte-CLOSE on the struct tail is gcc-codegen-quirk-bound, and
candidate sub-class matters more than expected.**
- **BANKED (clean whole-binary close):** `func_8015F9A4` (fnptr-call, reach ×1, inline in `ov_SC01_077.c`)
  — a near-clone of the demo's `func_8015F89C` (same `D_801891B8[arg0->f0](arg0)` table + `func_80161208`
  arity-cast). **fnptr-call class confirmed reliably closeable (2/2 with the demo).**
- **STRUCTURALLY PERFECT, blocked by regalloc — `func_8014C308`** (struct predicate, **relocs=0, reach ×134**):
  body matches; down to a pure v0↔v1 constant/result coalescing swap. Hand-fixes got it from 15→~3 mismatches
  (mask-local idiom + shared-ret0 goto, §2); the residual is a clean **permuter** target (no masked-symbol
  floor). Permuter converging (455→210→140). Drafts: `.run/demo/func_8014C308.c` (+ `_v2`/`_v3` experiments);
  permuter `.run/permuter/func_8014C308/`.
- **NEAR-MISS, ×134, §10 tail — `func_80130AF0`** (struct dispatch, reach ×134): body 100% correct, blocked
  by the §10 per-block `a0` rematerialization / `jal`-delay-slot quirk (call-heavy → permuter floor-polluted).
  Draft `.run/demo/func_80130AF0.c`.
- **NEAR-MISS, ×1 — `func_8016B4F8`** (struct init, reach ×1): body 100% correct, phantom +0x8 -O2 frame
  (cookbook §5 phantom-frame; -O2 variant, not the -O0 reserved-local fix). Draft `.run/demo/func_8016B4F8.c`.
- **SELECTION LESSON:** sorting `STRUCTURAL_MISS` by *ascending* m2c-mismatch biases toward the gcc-quirk
  tail (m2c already nailed the structure → only a codegen quirk remains). Clean closes come from **fnptr-call**,
  **relocs=0 / few-call**, and **m2c-mis-structured-but-fixable** functions. Low-mismatch call-heavy = hard tail.

---

## 5. TOWARD PROGRAMMATIC AUTOMATION (the end goal)

Steps ranked by how mechanizable they are:
1. **Canonical-widening — FULLY automatable.** Scan: for each function declared `void` whose body has
   no explicit `return`, find any call site that *uses* its result (assigns/tests `$v0`) → widen its
   canonical to `s32` everywhere (engine_core.h + overlay defs), gate the fleet byte-neutral. This is
   the **first tool to build** (task 6). It dissolves the dominant blocker pre-harvest.
2. **The cast idiom — mechanical.** `(u16)`/`(s16)` at use-sites per the asm load (`lhu`/`lh`); a
   draft-rewriter can apply it.
3. **m2c arithmetic/polarity fixes — partly mechanical.** The ptr-vs-byte ×4 tell and the branch-
   polarity flip are detectable from the match_one diff; a "fix-suggester" could propose them.
4. **The gcc-quirk tail — NOT automatable cheaply.** Stays manual / permuter (when scorable) / honest
   stub. It's a minority; don't let it block the bulk.

The dream: `gen_harvest_targets` (already callee-sig-aware) + an auto-widening pre-pass + m2c +
diff-driven fix-suggestions → a mostly-automatic loop, with the gcc-quirk tail flagged for humans.

---

## 6. PLAN FORWARD — REVISED 2026-06-19 (session 3) after sizing + the permuter refutation

**Original sequence** (sample → giant → harvest) is superseded. After firming the rate (§4 session 3),
Drew chose **"harvest tractable classes first; giant DEFERRED"** (option A). Then the sizing below changed
the calculus again.

### Harvest opportunity sizing (2026-06-19, reach-weighted; fleet denom = 344,010 instances, 55.04% done)
Per residual bucket (still-stub fns in ov_SC01_077), count / sum-of-reach / %fleet-if-all-matched:

| Class | count | reach | %fleet | tractability |
|---|---|---|---|---|
| `MCOMPILE_fnptr-call` | 83 | 355 | 0.1% | reliably HAND-closeable, but **low reach** (overlay-specific tables) |
| `VOID_VALUE_MISUSE` (widening) | 17 | 1081 | 0.3% | deterministic (canonical-widening) |
| `SIG_FIXABLE_KR` | 4 | 536 | 0.2% | deterministic (sig_unify, mostly done T3) |
| `STRUCTURAL_MISS` | 366 | 26,304 | **7.6%** | HIGH yield, but quirk-heavy; only the m2c-mis-structured-fixable + relocs≤2 subset is tractable |
| `PERMUTER_CLASS` | 145 | 12,263 | **3.6%** | 1-4 mismatch near-misses |
| (call-heavy `relocs 6+` across the above) | 275 | 18,113 | 5.3% | the §10 tail — DEFER as stubs |

**The reach (×134 leverage) is concentrated in the core shared engine functions, which are exactly the
quirk-prone STRUCTURAL_MISS/PERMUTER_CLASS** — NOT the easy fnptr/void classes (those are low-reach).

### The permuter route is largely REFUTED (T6 + session-3 `func_8014C308`)
- **relocs≥1:** T6 proved isolated-permuter wins do NOT transfer to the whole binary (callee inlining in the
  one-big-file TU differs) → ~0 whole-binary yield. The relocs 1-2 band (2.15%) is subject to this.
- **relocs==0** (only 11 fns / 0.39%): permuter-faithful BUT slow — `func_8014C308` (relocs=0, structurally
  perfect, 1 v0↔v1 swap) did NOT close in ~12 min across two runs (best score 140). Needs PERM_ hints.
- ⇒ The permuter is NOT the bulk lever. The yield lever is **guided HAND-matching** (the §1 loop + the §2/§3a
  idioms), which is **breadth** (many independent high-reach fns) → an **Ultracode wave** (R26).

### Revised plan
1. **Ultracode guided-hand-matching wave** over the high-reach **tractable** subset: m2c-mis-structured-fixable
   STRUCTURAL_MISS + fnptr-call + sig/widening-fixable. Agents apply the §1 loop + §2/§3a idioms (mask-local,
   shared-ret0 goto, cast/widening, fnptr-table typing), iterate with `match_one`, gate **whole-binary**
   (`harvest_verify.py`, the sole arbiter), propagate ×reach (`dedup_propagate.py`). The gcc-quirk tail FAILS
   the gate (correctly, G3) → stays an `INCLUDE_ASM` stub (NO NON_MATCHING correct-C track — Drew, A-only,
   until public). Measure the real fleet-% delta. Expected ~2-4% (bounded by the quirk tail).
2. **canonical-widening** folded into the agent playbook (§3a move 1) — a standalone tool is low direct yield
   (0.3%); build it only if sig-conflicts prove a major agent bottleneck.
3. **Document** idioms as they emerge (R16); **giant `func_80144B9C` deferred** (reassess after the wave yield).
4. **T7 go/no-go close + PhaseEnd** once the wave yield is measured.

---

## 7. THE ULTRACODE HARVEST WAVE + THE CANONICAL-SIG WALL (session 3, 2026-06-19 — PROVEN)

The guided-hand-matching loop (§1) **scales via an Ultracode Workflow** (R26). First calibration wave run &
measured; this section is the operational record + the singular bottleneck it exposed.

### 7a. The wave pipeline (reusable)
1. **Ghidra pre-pass (headless batch, NO /mcp):** stop MCP (`tools/ghidra_mcp_stop.sh`), then
   `analyzeHeadless ghidra bfm -process ov_SC01_077 -noanalysis -postScript DecompileFunctions.java
   <addr-list> <out-dir>` → whole-program Ghidra-C to `.run/ghidra_c/func_<ADDR>.c` (rename `FUN_<lower>.c`
   → `func_<UPPER>.c`). Ghidra-C resolves locals-vs-globals-vs-callee better than m2c — agents read the cache
   (no live-MCP contention). `ov_SC01_077` is Ghidra program `00000004` (Phase-13 import).
2. **Draft (Ultracode `parallel`):** `.run/harvest_wave_s3.js` — one agent per target; each reads
   asm+Ghidra-C+m2c+actor-struct+§1/§2/§3a, hand-writes C, iterates `match_one`, writes
   `.run/drafts-s3/<fn>.c` ONLY on MATCH (stop-rule on gcc-quirks → report DIFF, no draft). **GOTCHA: the
   Workflow `args` channel does NOT transit arrays — EMBED the targets as a literal in the script + a `LIMIT`
   const.** Agents also drop scratch (`_try`/`_v2`) in the dir → filter to canonical `func_<ADDR>.c` before gating.
3. **Whole-binary gate:** `harvest_verify.py --drafts <dir> --chunk 1`. **Use `--chunk 1`** — the default
   batched chunk+bisect can drop a GOOD draft because it cross-conflicts with ANOTHER draft in the same chunk
   (shared-callee sig clash), not because it's wrong.
4. **Recover:** `sig_unify.py --in <failed-drafts> --out <fixed>` then re-gate (recovered 2/9 in calibration).
5. **Propagate:** `dedup_propagate.py --auto-from ov_SC01_077` (×reach; also catches up any inline-but-
   unpropagated prior matches). `make check-all` (R22) + `make report`.

### 7b. Calibration result (top-30 by reach, ~1.89M tokens)
- **18/30 match_one MATCH (60%)** — agents reconstruct correct bodies well.
- **10/30 whole-binary verified (33%)** → banked ×134 (incl. the ×268 `func_8015773C`) → **fleet
  55.04%→55.51% (+0.47%)**, 136/136. (8 direct + 2 via sig_unify; 1 verified-but-local-type stays inline ×1.)
- **12/30 match_one DIFF** = the genuine gcc-quirk tail (§2/§10: hoist-vs-remat, phantom frame, v0/v1
  coalescing, walking-pointer). Agents diagnosed each precisely; correctly wrote no draft.

### 7c. THE CANONICAL-SIG WALL (the singular scaling bottleneck — the ~2× lever)
**The whole 60%→33% gap was SIG CONFLICTS — 100% compile-errors, ZERO codegen byte-mismatches.** Parallel
agents each declare a shared callee (`func_80131CA8`, `func_80131E00`, `func_801472C8`, `func_8001D074`, …)
with a different signature; in the one-big-TU `ov_SC01_077.c` those clash (`conflicting types for func_X`).
`func_80131CA8` alone broke 3 drafts (it is BOTH a residual being matched AND a callee in others — circular).

**This is the loose-typing wall in its true form, and it is BEATABLE deterministically** (unlike Phase-16's
verdict). The fix = a **canonical-sig layer**, applied SURGICALLY per-callee (a blanket global decls header
breaks loose matches — Phase 16; but per-callee byte-gated canonicalization works — sig_unify proof):
1. Identify the high-frequency shared callees among the targets.
2. Establish ONE canonical sig each: match the shared-callee residuals **first** (callees-before-callers, so
   the def fixes the sig fleet-wide), or derive from asm/usage and seed `engine_core.h`.
3. Enforce in the wave: agents grep `engine_core.h` for the canonical (already in the prompt) + a strengthened
   `sig_unify` post-pass that unifies the def-sig AND every caller's extern to the SAME canonical.
Expected to lift whole-binary 33% → ~60% (toward the match_one ceiling) — **the dominant scaling lever**.

### 7d. Scaling economics (measured)
Calibration: 30 fns / 1.89M tokens / 33% whole-binary / +0.47%. Naive scale to 300 ≈ ~4% fleet, token-heavy.
With the canonical-sig layer (33%→~60%) ≈ ~6-7% fleet at ~2× token efficiency. **Build the layer before the
big wave.** Targets: `.run/harvest_targets_s3.json` (300, relocs≤5, reach-sorted; the top-30 are done).
*(Superseded by §8 — the layer was built and the "~2×" did not hold; the wall is the compiler, not sigs.)*

---

## 8. THE CANONICAL-SIG LAYER — BUILT, and the decisive finding (Phase-17 session 4, 2026-06-19/20)

**The layer is BUILT and validated; the "~2× scaling lever" framing was WRONG; the real wall is the
gcc-quirk tail, so the next lever is understanding gcc-2.7.2 (R17 research, Phase 18), NOT more brute waves.**

### 8a. What was built (committed, byte-neutral, reusable)
- `tools/census_conflict_callees.py` — the accurate conflict predicate: an undeclared-`stub` callee with
  `decl_sources = n_callers + is_target >= 2` is a sig-conflict risk (a `declared`/`defined`/`extern` callee
  is conflict-free; gen_harvest_targets feeds the one sig). Writes `.run/conflict_callees.json`.
- `tools/derive_canonical_sigs.py` — one byte-neutral canonical sig per conflict callee: **`s32` return**
  (void→s32 byte-neutral §3a-1; required where `$v0` is used) + **`s32` params** (matched bodies cast int→ptr,
  the demo idiom), **arity** from the Ghidra-C cache AND asm read-before-write `$a0–$a3` (agreed on all 14
  cached; the 6 non-cached stubs call-site-validated). Writes `.run/canonical_sigs.json`.
- The **20-extern block at the TOP of `src/ov_SC01_077/ov_SC01_077.c`** ("Phase-17 canonical-sig layer").
  **LOCAL on purpose** — engine_core.h is shared by all 134 overlays and a reach-1 name (e.g. func_801809BC,
  matched differently in ov_SC03_096) would collide. `gen_harvest_targets` + `sig_unify` both already read
  the overlay `.c`, so the layer auto-wires with **no tool change**.
- **Pipeline change (mandatory):** harvest_verify accumulates the baseline from the (now block-carrying)
  `.c`, so a raw draft's guessed extern clashes with the block even at `--chunk 1`. The wave gate is now
  **draft → `sig_unify` (MANDATORY, normalizes drafts to the file-top canonical) → `harvest_verify --chunk 1`
  → propagate.** Census after the layer: **conflict callees 20→0, blocked targets 24→0**, fleet 136/136 (R22).

### 8b. THE FINDING (R14/P9 — this redirects the whole strategy)
- **The conflict wall is small:** for the remaining 270, only **20 callees / 24 targets / 7% of wave reach**.
  The "~2×" was the *top-30's in-flight* conflicts, since dissolved by banking those callees.
- **The high-reach core IS the gcc-quirk tail.** Hand-tried the 4 reach-134 *circular* conflict callees
  (the §7c "match callees first" move) — **ALL quirk-bound, 0 banked:** func_8012B4B8 = §10 stack-addr
  rematerialize-vs-hoist (gcc caches `&mtx`); func_8012B8E4 = `$s0/$s1` regalloc swap, **structurally perfect
  75=75** but the permuter probe stalled at base score (external callee `ratan2`, so T6 doesn't even apply —
  it's just not in the permuter's search space); func_8016A8FC / func_80169A4C = local-struct-builders
  (stack-layout-bound). Drafts in `.run/drafts-s4/`; permuter scratch `.run/permuter/func_8012B8E4/`.
- **Types are byte-neutral for matching (re-confirmed):** matching reads the access *width* off the asm
  instruction (`lh`=s16, `lbu`=u8, `lw`=s32), not off any struct def — so emulator-recovered struct types
  help *comprehension*, not the byte-close. The wall is the compiler's regalloc/scheduling, which types and
  shared-context do not touch.

### 8c. The leverage analysis (answering "do the fewest largest that unlock the most?")
- The fleet % is **function-count-weighted** (`190,949 / 344,010` functions): **every reach-134 match is
  +0.039% regardless of size.** Giants bank more *bytes* but the same %. So "fewest largest" gives no % edge.
- "Unblock many" = the canonical-sig layer (declaration removes sig-friction; it does NOT make callers
  *matchable* — matching is independent per function). The highest-fan-in callees (func_8012A828 49 callers,
  func_80146CA0 46, …) are already `defined`/`declared`/`extern`. Declaring the top-5 *undeclared* keystones
  touches only 28 of 900 stubs. So there is no "magic 5 unlocks hundreds."
- **The real lever is reach (size-independent), which we already reach-sort, + the idiom flywheel.** Of the
  400 remaining reach-134 stubs, **247 are the tractable shape** (≤80 ins, ≤4 calls); 80 call-heavy (§10
  tail), 28 giants. Projected tractable-247 wave ≈ **+3-4% fleet** at the calibration close-rate.

### 8d. The deferred wave (staged, ready to resume after the compiler research)
`.run/harvest_wave_s4.js` = the layer-aware probe (40 tractable reach-134, sig_unify-before-gate). Resume
after Phase 18 lands new gcc-quirk idioms (which raise the close-rate above 33% and so the wave's yield).

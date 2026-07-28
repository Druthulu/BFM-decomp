# gcc-2.7.2 LOOP OPTIMIZATION pass → residual→C-lever catalog (loop.c)

Pass-group: `loop.c` (biv/giv detection, `combine_givs`, strength reduction, invariant
hoisting/preheader, biv elimination, loop reversal). Compiled against the PINNED triple
(`tools/bin/gcc-2.7.2-psx/cc1 -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker`).
All claims below were validated on the REAL cc1 this session (experiment files:
`.run/gccmap/exp/*.c` + `cc.sh`; live byte-anchors via `tools/match_one.py` on
`func_80150528`, re-verified `MATCH (53 ins)` from `.run/toolkit/func_80150528.c`).

## ⚠️ SOURCE-VERSION CAVEAT (affects every agent using tools/reference/gcc-papermario)

`tools/reference/gcc-papermario` is **gcc 2.8.1** (`version.c`), NOT 2.7.2. For loop.c the
differences are BEHAVIORAL and bit us immediately:

| decision point | 2.8.1 (papermario tree) | **2.7.2 (our cc1 — authoritative)** |
|---|---|---|
| `maybe_eliminate_biv_1` COMPARE-vs-const, giv w/ const add | add must be SYMBOL/LABEL/CONST/pointer-REG | any `CONSTANT_P` add — **enabled** |
| `maybe_eliminate_biv_1` COMPARE-vs-const, nonconst add | `&& 0` (disabled, "overflow") | **enabled** |
| `maybe_eliminate_biv_1` COMPARE-vs-invariant-REG/MEM | `&& 0` (disabled) | **enabled** → biv eliminated even with variable bound (proven expA `test_var`: bound scaled `sll $4,n,3` in preheader) |
| `check_dbra_loop` reversal init | normalizes nonzero init when counting-only | requires **literal `initial_value == const0_rtx`** (proven expB `norev`: `i=1` start blocks reversal) |
| `combine_givs` order | qsort hook + refined benefit bookkeeping | plain linked-list pair loop (anchor rules below) |
| giv increment placement | AUTO_INC logic (moot on MIPS) | always inserted **immediately before the biv increment insn** |

> **[A23] AUDIT OUTCOME (2026-07-28):** all 96 claims in this file were re-derived against
> `tools/reference/gcc-2.7.2/` by parallel agents, each REFUTED claim adversarially re-checked.
> **Only 3 REFUTED were raised — the LOWEST error density of any map file**, which is a direct credit
> to the caveat table above: it already captured the behavioural 2.8.1-vs-2.7.2 deltas. Two upheld
> corrections are marked `[A23]` inline (the "no memory load is EVER hoisted" absolute, and the
> right-to-left call-arg order). **One honest gap:** 12 findings in the biv-elimination /
> `check_dbra_loop` area returned evidence that quoted THIS FILE rather than the compiler source, so
> they are **unverified, not confirmed** — the caveat table's own rows are the ones affected. Re-derive
> them before leaning on a biv-elimination claim.

A vanilla 2.7.2 extraction is at `.run/gccmap/gcc-2.7.2-vanilla-src/` (loop.c, unroll.c,
sched.c, cse.c, rtl.h, config/mips). **Recommend promoting it to `tools/reference/` —
line refs below are to that tree.** (2.8.1 refs marked "pm:".)

## L0 — Constants, dump access, and how decisions are scored

- RTL dumps: add `-da` to the cc1 line; on file input `foo.i` you get `foo.i.loop` etc.
  (`.run/gccmap/exp/cc.sh` builds .s; copy its cc1 line + `-da` for dumps).
- Pass order: expand → jump → **cse → loop → cse2** → flow → combine → sched → regalloc
  → sched2 → crossjump. Loop residuals are DECIDED here but surface post-regalloc.
- `n_non_fixed_regs` = **28** for PS1 (-msoft-float fixes all 32 FP regs; fixed GPRs =
  $0,$at,$k0,$k1,$gp,$sp,$ra; +hi/lo/+1 special non-fixed).
- Hoist threshold (`scan_loop:532`): `(loop_has_call ? 1 : 2) * (1 + 28)` = **29 (call) /
  58 (no call)**; decays `-= 3` per moved insn (`move_movables`), and `insn_count *= 2`
  for regs already moved out of another loop (`moved_once`).
- Strength-reduce threshold (`strength_reduce:3241`): `(call?1:2)*(3+28)` = **31 / 62**.
- `add_cost` = rtx_cost(PLUS) = `COSTS_N_INSNS(1)` = **2** (2.7.2 `cse.c:680`:
  `(N)*4-2`); `copy_cost` = **4**. Benefit unit: 2 ≈ one insn.
- **Giv worth-while test** (`strength_reduce`): reduce iff
  `lifetime × threshold × (benefit − 2×biv_count) ≥ insn_count`. A bare `reg = biv<<k`
  giv has benefit 2 → **(2−2)=0 → ALWAYS "not worth while" unless it absorbed a
  combined giv's benefit** — this single fact decides most IV-count/elimination outcomes.
- Dump phrases: `possible biv, reg R, const = K` (increment found) · `giv ... mult M add
  A` (linear fn of biv; `add (reg:N)` vs `add (const…)` distinguishes L2 outcomes) ·
  `giv at X combined with giv at Y` (g2=X merged into anchor g1=Y) · `not worth while, P
  vs I` (P = lifetime×threshold×benefit, I = insn_count) · `biv R eliminated` ·
  `Can reverse loop` / `Reversed loop and added reg_nonneg` · `Insn N: … moved to M`
  (movable hoisted to preheader) · `Cannot eliminate biv`.

---

## L1 — IV COUNT & SHAPE (combine_givs / basic_induction_var) — **STEERABLE**

**Source:** `basic_induction_var` (2.7.2 loop.c:4819), `find_mem_givs` (:4198
exclusion), `record_giv` (:4341), `combine_givs_p`/`express_from` (:5457/:5419),
`combine_givs` (:5494), reduction loop in `strength_reduce` (:3670-3960).

**Mechanism (byte-validated):**
1. Every separately-INCREMENTED pointer/index is its own **biv**. **Bivs never merge
   with each other** (only givs combine, and only within one biv's class).
2. Mem-address givs (`DEST_ADDR`, from `*(T*)(p+k)`) combine iff **identical
   (mult,add)** or `express_from` succeeds — needs anchor g1's add_val to be
   **CONST_INT**, g2.mult % g1.mult == 0, result a legit address with
   `ADDRESS_COST(new) ≤ ADDRESS_COST(orig)` (MIPS `mips_address_cost`: reg=1,
   reg+small16=1, reg+big=2, reg+(sym+off)=3).
3. **MIPS + -mgas accepts ANY offset and even reg+symbol pre-reload** (gas macro
   world) → the "offset out of 16-bit range splits the IV" hypothesis is **FALSE on
   this target** (proven expD `d2`: +0x9000 offset still combines, emitted as
   `lw $3,36860($4)` macro). IV splits come from bivs or orphaned givs, not range.
4. Bare `*q` (mult 1, add 0) is **excluded from givs** (`find_mem_givs:4198`) → a
   bare-dereferenced pointer stays a live biv and can't be re-anchored.
5. A derived pointer consumed only as same-loop mem addresses **dissolves** (its
   DEST_REG giv goes `maybe_dead`, uses fold into DEST_ADDR givs — proven expD `d3`,
   expE e1/e2: cast/conditional/cross-bb loads all still dissolve).
6. **Anchor choice**: `bl->giv` is prepend-built during the forward scan, and
   `combine_givs` (2.7.2 loop.c:5494) takes g1 from the list head first (pass 0 =
   replaceable g1 only) → **the LAST-emitted DEST_ADDR giv anchors** and all others
   become `anchor+delta` offsets. ~~NB call args are expanded right-to-left, so *the
   first arg's load is emitted last*~~ — **[A23] FALSE: args are emitted LEFT-TO-RIGHT.** The audit's
   RTL dump shows `$a0` at insn 10, `$a1` at 12, `$a2` at 14 (ascending), so the FIRST arg's load is
   emitted **first**. The observed fact that banked `func_80150528` anchors at +0x20 (its first call
   arg) still holds — but it follows from `record_giv`'s prepend + `combine_givs` taking the list
   HEAD (which makes the last-PREPENDED giv the head), NOT from a right-to-left arg order. Do not
   reason about arg emission order from this bullet.

**C levers (with proofs):**
- **Target has biv + ONE derived IV (offset cluster)** → single walked base pointer,
  ALL fields as `*(T*)(p+k)` byte-offsets. gcc reduces the combined giv to one IV,
  anchor per rule 6. **Byte-proven ×134: func_80150528 (53 ins), func_8014F2E0 (66
  ins)** (cookbook §30a#2; re-verified `MATCH (53 ins)` this session).
- **Target has TWO independently-stepped IVs anchored at different bases** → write two
  walked pointers (`p += K; q += K;`) — two bivs, guaranteed, each anchoring its own
  offsets. Proven on the REAL fn: `.run/gccmap/exp/func_80150528_twoptr.c` produces
  exactly the target's 2-IV structure but anchored at MY chosen +0x58 vs target's
  +0x20 (19/53 mismatch = pure anchor/regalloc delta). **Use the target's anchor
  offset as q's base.**
- **Do NOT bare-deref a walked pointer you also offset-access** — `*q` keeps biv q
  alive *in addition to* the combined giv IV → 3 IVs (proven
  `.run/gccmap/exp/func_80150528_anchor20.c`: 57 ins, extra `addiu s1,s0,88`). Write
  the zero-offset field as `*(s32*)q` only if the target shows the biv itself doing
  the load; otherwise give the anchor a nonzero base so every access has an offset.
- Conflicts with the §30 anon-struct `/s` lever (separate pointer re-splits) — read
  the target's IV structure first, pick per §30a#2 NB.

**Tells:** parallel `addiu rA,rA,K` + `addiu rB,rB,K` with one endtest = 2 bivs ·
preheader `addiu rIV, rBASE, A` = combined-giv init, A = anchor offset · offset
cluster `k(rIV)` all relative to one anchor = combine_givs merged them · in dump:
`add (const_int k)` givs + "combined with" lines.

---

## L2 — INDEX-BIV ELIMINATION / ENDTEST REWRITE (maybe_eliminate_biv) — **STEERABLE**

**Source:** eligibility gate `strength_reduce` (2.7.2:3688-3720: biv dies in-loop OR
final value computable), `maybe_eliminate_biv_1` (2.7.2:6004; COMPARE cases from
:6110 — all paths ENABLED in 2.7.2, see caveat table), elimination executed only when
`all_reduced == 1` (2.7.2:~3880).

**Mechanism:** if the index biv `i`'s only non-giv use is the endtest, the endtest is
rewritten onto a reduced giv: `i < ARG` becomes `giv_reg < ARG*mult + add`, computed:
- all-constant → folded immediate (`slt $2,$3,200` — expA `test_const`, 25×8);
- variable/invariant-reg ARG → `emit_iv_add_mult(ARG,mult,add)` at
  **`where = threshold ≥ insn_count ? preheader : test-site`** (2.7.2:5968) → small
  loops (≤31 insns w/ call, ≤62 without): preheader `sll $4,n,3` (expA `test_var`);
  bigger loops: computed at the bottom, inside the loop.

**When elimination FAILS (i kept → index + pointer, 2 IVs):**
- `i` materialized anywhere else: call arg, stored, returned, compared non-linearly
  (`maybe_eliminate_biv_1` REG case returns 0) — expC `c1`;
- **`all_reduced == 0` because ANY giv of the class was benefit-ignored** — the classic
  shape: when the array base lives in a hoisted register (`la rB,A` movable — happens
  when the loaded value feeds a call, or in big loops), the address givs have
  `add (reg:N)` (not const), they combine amongst THEMSELVES by identity, and the
  orphaned `i<<k` giv (benefit 0) is "not worth while" → biv kept. Proven expG
  g1/g2, expH h1 (dump: `giv of insn 27 not worth while, 0 vs 10`);
- giv `!always_computable` (DEST_REG giv set behind a branch), mode mismatch,
  `maybe_dead` anchor.

**C levers:**
- **Target = single scaled-index IV, `slt rIV, #K` endtest, `sym+off(rIV)` HI/LO-reloc
  loads** → plain `for (i = 0; i < N; i++) …arr[i].f…` with global array, value used
  locally (no call consuming the load directly). cc1-proven expA.
- **Target = pointer-walk with `sltu` vs hoisted end** → pointer form `for (p = arr;
  p < arr+K; p += S)` (biv = pointer; L1 rules for fields). Byte-proven func_80150528.
- **Target keeps `i` (slt rI, rN) + separate address IV** → make `i` load-bearing the
  way the target shows (pass it, store it, return it) or feed the load to a call
  (expG g1 shape).
- **Preheader vs in-loop bound scaling** (`sll` before the loop vs at its bottom)
  follows the `where` flip — check loop real-insn count vs 31/62 before assuming a
  scheduling residual.

**Tells:** `slt rX, rIV, #imm` where imm = trip×stride = eliminated biv · preheader
`sll rT, rN, k` = eliminated biv w/ variable bound · `lw rV, sym+off(rIV)` (HI16/LO16
on a loop load) = index anchored at 0, symbol folded into address · biv init 0 +
compare vs scaled bound (IV counts BYTES not elements).

---

## L3 — LOOP REVERSAL → COUNT-DOWN + `bgez` (check_dbra_loop) — **STEERABLE**

**Source:** `check_dbra_loop` (2.7.2:5655; reversal branch :5750-5900).

**2.7.2 conditions (ALL required):**
- endtest `LT` vs CONST_INT; increment const; `bound % inc == 0`;
- `initial_value == const0_rtx` **literally** (start at 0 — no normalization in 2.7.2);
- counting-only biv (`giv_count==0` and no insn other than its increment/endtest
  mentions it) OR the tiny-loop identity (`giv_count+biv_count+num_mem_sets+
  num_movables+2 == insn_count`, single biv class);
- `num_mem_sets ≤ 1`, and a single store's address must **vary** (a store to an
  invariant address blocks reversal); `num_nonfixed_reads ≤ 1`; no call; no volatile;
  single fall-through exit.

**Result:** `li rI, N-inc` … `addiu rI,rI,-inc; bgez rI,top` (REG_NONNEG note). If a
(varying-address) store is present, the address giv is re-derived DOWNWARD → target
shows a down-walking pointer + separate down-counter = **2 IVs** (a reversed loop
cannot fold the counter into the pointer since the test is `>= 0`).

**Proofs (cc1, expB/expC):** `rev` (0-start, unused counter) → reversed w/ `bgez`;
`norev` (1-start) → NOT reversed; `used` (counter accumulated) → NOT reversed;
`c2` (`dst[i]=inv` const bound) → reversed, down-walking `addu $2,$2,-4` +
`addu $3,$3,-1; bgez`.

**C levers:** target shows `addiu -1 / bgez` down-count where logic is an up-count →
write the natural `for (i = 0; i < N; i++)` with the counter otherwise UNUSED and let
gcc reverse it (do NOT hand-write the reversed loop — initial/final-value insns
differ). Target shows an up-count `slt` where your draft reverses → violate one
condition per the target's dataflow: nonzero start, use the counter, second read, etc.

**Tells:** `bgez` loop branch + `li N-1` init = reversed counting loop · down-walking
store pointer + separate down-counter = reversed store loop (c2 shape) · REG_NONNEG
only arises here (grep dump for `Reversed loop`).

---

## L4 — INVARIANT HOISTING / PREHEADER COPIES (scan_loop/move_movables) — **STEERABLE**

**Source:** candidate filter `scan_loop` (2.7.2:640-720, trap check :716), single-use
substitution (:735-770), `combine_movables` (:1239), desirability + emission
`move_movables` (2.7.2:1529), `invariant_p` (:2708, store check :2779),
`prescan_loop` (:2158, call→unknown_address_altered :2201).

**Mechanism:**
- Movable = single-set pseudo (or invariant consec-sets), src `invariant_p`, safety:
  used only in its bb, OR non-user-var, OR set guaranteed before any use
  (`maybe_never`); `may_trap_p` src can't move past a conditional/call. Moved iff
  `threshold × savings × lifetime ≥ insn_count` (thresholds L0 — for typical loops
  this is nearly always true; the interesting blockers are the SAFETY conditions).
- **A CALL anywhere in the loop sets `unknown_address_altered`** (`prescan_loop:2201`)
  → `invariant_p(MEM) == 0` for ~~every~~ **most** loads. ~~**no memory load is EVER hoisted from a
  loop containing a call** (proven expC c3: `lw D_SRC` stays in-loop). Don't fight
  it with cached locals — match the target's in-loop reloads by NOT caching.~~
  **[A23] "EVER" is FALSE — there is a real exception.** `invariant_p`'s `case MEM:` arm
  (2.7.2 `loop.c:2760-2775`) checks `RTX_UNCHANGING_P (x)` **before** consulting
  `unknown_address_altered` and `break`s — i.e. **read-only items ARE invariant and DO hoist even
  with a call in the loop.** Byte-proven during the audit on the pinned cc1:
  `int t(const int *p,int n){int s=0,i;for(i=0;i<n;i++){s+=*p;f(i);}return s;}` puts
  `lw $19,0($4)` in the **PREHEADER**, not the loop body.
  **So the advice "don't fight it with cached locals" is right for ordinary loads and wrong for
  `const`/`RTX_UNCHANGING_P` ones** — if the TARGET hoists a load out of a call-containing loop,
  a const-qualified pointer is the lever, not evidence that you mis-read the loop.
- No-call loops: an invariant global load hoists if no `true_dependence` with any
  `loop_store_mems` entry (`invariant_p:2695`; `/s`/`MEM_IN_STRUCT_P` enters here —
  expr.c agent's domain, cookbook §30/§30a#1) — proven expC c2 (`lw D_SRC` hoisted
  over the `dst[i]` stores).
- **Single-use invariant in a CALL loop is SUBSTITUTED into its use and the set
  deleted** (`scan_loop:735`, only when `loop_has_call`) → the classic
  "`la $a0,SYM` INSIDE the loop at the call-arg site" (proven expC c1). To keep such
  a value hoisted like a target shows, it must be used ≥2× per iteration (or the loop
  must have no call). Conversely an in-loop `la` before a `jal` is THIS, not a missed
  hoist.
- Two movables loading the SAME value merge to one reg (`combine_movables`,
  `rtx_equal_for_loop_p`; not merged if used outside the loop `m->global`).
- **Inline-limit lever (byte-proven func_80150528, §30a#3):** an invariant loop limit
  written INLINE (`D_x + K`) in both guard and condition → the in-loop limit insns
  are movables hoisted to the preheader → preheader copy + temp→callee-saved regalloc.
  A cached `u8 *end` local computes it ONCE before the loop instead → different
  (fewer) insns, wrong regalloc.

**Tells:** `la`/`lui+addiu` pair right before `NOTE_INSN_LOOP_BEG`'s position
(preheader) = moved movable (dump `moved to N`) · in-loop `la` at a call-arg =
single-use substitution (NOT a bug) · in-loop reload of a plainly-invariant global +
a `jal` anywhere in the loop = unknown_address_altered (INTRINSIC — write the
uncached access) · dump `not desirable` = threshold fail (rare; big loop, low savings).

---

## L5 — GIV REPLACEABILITY / FINAL-VALUE COMPENSATION — **DIAGNOSTIC (route permuter if fighting placement)**

**Source:** `record_giv` replaceability (2.7.2:4426-4500), `check_final_value`
(:4551), copy emission + final values in `strength_reduce` (:3940-3990 —
non-replaceable giv gets `mov old,new` INSIDE the loop after its insn (:3948);
`final_value` giv/biv gets `reg = final` after loop end, or BEFORE the loop when it
has multiple exits).

**Mechanism/tells:**
- DEST_REG giv whose lifetime crosses a biv increment, is used outside the loop, or
  sits behind spaghetti branches → NOT replaceable → reduced IV **plus a `move`
  inside the loop**. Tell: `move rOld, rIV` right after the giv's defining position.
- Eliminated/reduced regs live after the loop → **post-loop set insns**
  (`reg = final_value`), and anchor pre-bias produces **pre-bump/post-adjust pairs**:
  proven expF f2 — `addu $3,$3,16` before entry, `lw -16($3)` inside,
  `addu $3,$3,-16` after exit. A "useless" `addiu rX,rX,±K` straddling the loop
  boundary is loop.c final-value machinery, not scheduling noise.
- C lever (soft): keep a derived pointer's uses on ONE side of the `p += K` to avoid
  the crossing (or place the increment where the target implies — see L8). If the
  target shows the compensation insns, your C must CREATE the crossing.

## L6 — REDUCED-GIV INCREMENT PLACEMENT — **INTRINSIC (order), sched-owned**

`strength_reduce` (2.7.2:~3900, `emit_iv_add_mult(..., tv->insn)`) always inserts each reduced giv's `addiu` immediately
BEFORE the biv's increment insn → giv-adds cluster at the biv update in RTL order;
sched1 then fills delay slots (expF f1: q's add landed in the branch delay slot).
Which adds exist = L1 (steerable); their final ORDER = scheduler domain. Don't grind
add-order here; fix the IV set first, then route residual order to permuter/sched
agent.

## L7 — WHOLE LOOP SKIPPED (find_and_verify_loops) — **STEERABLE (structure)**

**Source:** `find_and_verify_loops` (2.7.2:2222): a loop is `loop_invalid` if jumped
into from outside (label reachable from elsewhere), contains `setjmp`, or its label is
used in an initializer/computed goto. Invalid → NO hoisting, NO strength reduction,
NO reversal for that loop (inner loops still done).
**Tell:** a loop where obviously-invariant address computations sit unreduced inside
(pattern matches -O0-ish body inside an -O2 fn) + irregular entry (goto into body,
switch dispatching into a loop). **Lever:** reproduce the target's entry structure;
if the target LOOKS unoptimized inside a loop, check for an into-loop jump in the asm
before assuming a compiler quirk.

## L8 — `not_every_iteration` / INCREMENT POSITION — **STEERABLE**

**Source:** scan loops in `strength_reduce` (2.7.2: both copies set
`not_every_iteration` after **any label OR jump** — 2.7.2 is more conservative than
2.8.1 which exempts exit jumps); reset when a label with no more labels to loop-end is
passed (:3403/:3680); `record_biv`/`record_giv` `always_executed`/`always_computable`;
`update_giv_derive` (:4693).

**Mechanism:** everything AFTER the first branch inside the body is "not every
iteration": DEST_REG givs there lose `always_computable` → can't back biv elimination
(L2) or derive other givs; biv increments there make the biv not-always-executed →
blocks reversal-adjacent reasoning and auto-inc-style tightness.
**C lever:** the POSITION of `p += K` / `i++` in the body (top vs bottom, before vs
after the `if`s) and `continue` placement (NOTE_INSN_LOOP_CONT) are free C-side knobs
that flip these flags. If elimination/reduction behaves differently than a sibling
function, compare where the increment sits relative to branches.

---

## What is NOT a loop.c residual (routing)

- **Store-vs-load stuck order** → `/s` `MEM_IN_STRUCT_P` aliasing (expr.c agent,
  cookbook §30/§30a#1). loop.c only consumes it via `true_dependence` in
  `invariant_p` (L4) and `note_addr_stored` dedup.
- **Cross-jump tail-merge / per-branch coalescing** (e.g. `func_80148094` — its
  @stuck diagnosis is `-fac` reg coalescing + tail merge, NOT its loops) → jump.c/
  regalloc agents; loop levers won't move it.
- **`while` vs `do-while` guard duplication** (`NOTE_INSN_LOOP_VTOP`) → jump.c
  (`duplicate_loop_exit_test`); loop.c only reads VTOP to reset `maybe_never`.
- **-funroll-loops** paths (`unroll.c`) are dead at -O2; unroll.c only contributes
  `loop_iterations`/`final_[bg]iv_value` helpers to the above.

## Verdict summary

| class | verdict | proof |
|---|---|---|
| L1 IV count/anchor | **STEERABLE** | ×134 func_80150528/func_8014F2E0 (§30a) + live counter-proofs twoptr/anchor20 (this file) |
| L2 index-biv elimination | **STEERABLE** | cc1 expA/expG/expH (deterministic asm); mechanism source-pinned |
| L3 reversal (bgez down-count) | **STEERABLE** | cc1 expB/expC-c2 |
| L4 hoist/preheader/la-in-loop | **STEERABLE** (call-loop mem reloads INTRINSIC — match by not caching) | ×134 func_80150528 (inline-limit §30a#3) + cc1 expC |
| L5 final-value compensation | DIAGNOSTIC / soft lever | cc1 expF-f2 |
| L6 giv-add order | INTRINSIC → permuter/sched | expF-f1 |
| L7 invalid loops | STEERABLE (structure) | source-pinned |
| L8 increment position | STEERABLE | source-pinned (flags feed L2/L3) |

Experiment corpus: `.run/gccmap/exp/{expA..expH}.c` + `cc.sh` (rerunnable one-liners);
counter-proof C for the banked exemplar: `.run/gccmap/exp/func_80150528_{twoptr,anchor20}.c`.

### Movables EMISSION ORDER — the bitfield mask decoupler (Phase 24 T7, cookbook §36, byte-proven func_8013AF20) — **STEERABLE**
`move_movables` emits hoisted const-sets in the order `scan_loop` FOUND them = loop-body insn
order. A user-mask statement materializes its constants in C expression order — COUPLED to the
AND/OR compute shape (reordering `&`-operands flips both). The one C form that materializes
`0x00ffffff` BEFORE `0xff000000` while still computing `dest & 0xff000000` first is the
**BITFIELD store** (libgpu `setaddr`/`addPrim`): `store_fixed_bit_field` masks the VALUE first
(expmed.c:667 `must_and` → :679-681), the dest second (:694-696), `ior` dest-first (:706).
Downstream, preheader birth order sets the K2 tie-break (later-born = shorter LL = higher
priority), and a lui+ori const additionally SKIPS local-alloc.c:1064's LL-doubling (sched.c:4830
`try_split` → mips.md:3208 `large_int` split → `reg_n_sets==2` fails the :1021 gate) — see
regalloc.md RC-7. Full chain + gdb numbers: cookbook §36.

### The giv-init fence — force `emit_iv_add_mult`'s giv-init MOVE (Phase 24 T5, cookbook §34) — **STEERABLE**
When a loop's counter-derived pointer (a general induction var) has its init COALESCED with the invariant address, gcc drops one instruction → a full count mismatch vs a target that kept the `addu dst,base,$zero`. **Fix:** `asm("":"=r"(base):"0"(base)); dst = base;` forces `emit_iv_add_mult`'s giv-init move (`loop.c:5556 if (reg != result) emit_move_insn(reg,result)`) to materialize = the target's `addu dst,base,$zero`. The general fix for the "gcc coalesced the giv init, dropping an instruction" class on any giant with a counter-derived pointer.

# `func_8017BF14` — behemoth #4, 4,763 ins, `ov_SC03_116` — ROUND 2: **MATCH**

**Session 20 round 2, 2026-07-25.** Round 1 handed over 45/4763 mismatched.
Round 2 closed it.

---

## 1. FINAL NUMBER (measured, `tools/match_one.py`, the CANDIDATE gate)

```
python3 tools/match_one.py func_8017BF14 --c .run/giants/s19_func_8017BF14_b2.c \
  --asm-subdir asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C
-> MATCH (4763 ins)  func_8017BF14
```

Reproduced **3×** from independent private work dirs. Independent confirmations:

| check | result |
|---|---|
| `bf14_full.py` masked index-wise diff | **0 / 4763 mismatched** |
| `bf14_hist.py` opcode histogram | `len+0  L1=0` |
| `bf14_slots.py` stack-slot census | **127 / 127**, all at the target's offsets |
| compile warnings (`-Wall`) | none |

**The whole-binary SHA1 arbiter (G3/P9) was NOT run** — the task forbade touching
the build tree. `match_one` is the candidate check only; the coordinator's
whole-binary gate is the sole arbiter (G3/P9).

Trajectory, every step measured: **45 → 37 → 33 → 21 → 11 → 3 → 2 → 0.**

---

## 2. PER-RESIDUAL OUTCOME

Round 1 split the 45 into (a) producer temps ≈8, (b) `c0`/`c2` grants ≈15,
(c) quad-lit rgb accumulator ≈20. All three fell. The exact split of the 45,
recounted from the diff, was **(a) 8 + (b) 23 + (c) 14**.

### (a) Prim-word producer temps — **FELL** (8 ins, idx 508–512, 539–542)

Round 1's diagnosis (`combine_regs` tying the chain into the pinned `va`) was
**correct**, and its prescribed cure (named MULTI-death offset variables) does
work — `prod2` broke the `$t2` tie exactly as predicted, byte-visible:

```
base   508 andi $t2,$a1,0xffff   510 addu $t2,$t6,$t2     <- tied, in place
prod2  508 andi $v1,$a1,0xFFFF   510 addu $t2,$t6,$v1     <- MATCHES target
```

But it is a **conservation law, not a fix**: one shared `vo` gives one register
for all its sites, whereas the target uses three distinct temps ($v1, $a0, $v0,
$v0 for the four offsets). `prod2` fixed 508/510 and broke 513/515 — 45 → 45.
Every partition of the four offsets across named variables was swept
(`prod1/2/3`, `prod_ad`, `prod_cd`, `prodvd`, `prodswap`): best is neutral.

**What actually fixed it: R4 — dropping the `va→$t2` and `w→$a1` pins.**
Round 1 measured those pins as worth 4% and the brief said not to re-buy their
removal. That was true *of the round-1 base* and is **false** once `c0..c3` sit
at function scope (R3): on the 21-base, `unpin_va` = 17, `unpin_va unpin_w` =
**13**. This is base-dependence, not a contradiction — and it is the single
most important methodological lesson of the round (§5.1).

### (b) `c0`/`c2` grants — **FELL** (23 ins)

Round 1 pointed at `allocno_compare` order and prescribed a variable-REUSE
merge. The **reuse sweep was run in full and every merge lost** (§4.3): merging
`za`/`zb`/`f0`/`f1` into `c0..c3` scored 43–3294 against a 33/37 base. Reuse is
now a measured dead end on this function.

The real lever was found by **reading the target and the matched relatives**,
which is where round 1 said the value was:

* The target's TRI grants are `c0→$t4, c1→$a0, c2→$t2` — **identical to its
  QUAD grants**. Two independently-scoped allocno sets cannot coincide by
  chance; one shared set can.
* Both matched relatives declare the colours at **function scope**:
  `.run/giants/s19_func_8017D960_b5.c:310` and `s19_func_8017F510_b4.c:338`.

`s32 c0, c1, c2, c3;` at function scope: **33 → 21**. Declaration *position* is
neutral (5 anchors swept, all 21) — consistent with round 1's L4.2 oracle, since
these never take stack slots.

This **reverses round-1's L4**, which put them per-cull-block. L4 was right on
its own base — it was supplying the extra local allocno that spills `r1lo` — but
R1 and R2 supply that pressure now.

A second, separable part of (b) was the c1 **sum accumulator** (9 ins, idx
1876-1879 / 3890-3893), which round 1 had classified with the grants. It is a
pin artefact, and `CLAMP80S` (R1) fixed it: **45 → 37**.

### (c) Quad-lit rgb accumulator — **FELL** (14 ins)

Two independent pieces:

* **Unlit `rgbc` (4 ins, idx 2310/2311, 4699/4700).** `cb` is a function-scope
  global allocno, so `cb |= 0x101010` writes it in place ($a1). The target
  stores the *expression* `cb | 0x101010`, a 1-death local that `combine_regs`
  ties to the **dying constant register** $v1. **37 → 33.**
* **Quad lit rgb2/rgb3 (10 ins, idx 4643-4652).** Reverting those two to the
  single-expression form (rgb0/rgb1 keep the 3-statement accumulator) makes the
  intermediates 1-death local temps that alternate $v0/$v1 — which is what lets
  the target's store of the previous rgb word sit one slot later. **21 → 11.**
  All-four = 23, rgb0/rgb1-only = 21, direct-store = 28. The split really is
  2-and-2, matching artefact 4 (rgb2/rgb3 are the two that take `c1 << 16`).

### THE ATTRIBUTION PRIMITIVE FOR (c) — run, and decisive

```
-fno-schedule-insns    -> my order unchanged
-fno-schedule-insns2   -> my order unchanged
both                   -> my order unchanged
```

In all three builds `sw v1,-20(t3)` still precedes `or v1,t2,a1`. **The
transposition was never a `sched.c` decision.** With a 3-statement accumulator
the value is pinned to one register, so the next `or` clobbers $v1 and *no*
scheduler could hoist it above the store — the ordering is a consequence of the
register grant. Changing the grant (R5) fixed the order for free. This is
**§78 reproduced exactly**, and it is the second time on this family that a
"scheduling" residual was really a register grant. Do not reason about `sched.c`
on this family until this primitive has been run.

---

## 3. THE ONE MECHANISM BEHIND FOUR OF THE SEVEN LEVERS

R1, R2, R4 and R7 are all the same compiler fact, and it is worth a cookbook
entry because it is the *cost* of the pin technique:

> A `register __asm__` pin makes the variable a **hard register in the RTL from
> the start**. When a 1-death local temp is produced from — or consumed into —
> that hard reg, `local-alloc.c`'s `combine_regs` takes its hard-register branch
> (`local-alloc.c:1795-1820`) and records the pinned register in
> `qty_phys_sugg` for the temp's quantity. **That path has no death guard and no
> cost model — it fires unconditionally.** The temp then lands in the pinned
> register and the operation is performed IN PLACE. An ordinary pseudo never
> gets that suggestion, because anything crossing a basic block has
> `reg_qty == -1` and `combine_regs` bails at its very first test.

Verified in source, `tools/reference/gcc-2.7.2/local-alloc.c`:

* `:472` — a pseudo is local iff `reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1`.
* `:1763` — `combine_regs` returns 0 immediately if `reg_qty[ureg] < 0`.
* `:1795` — `if (ureg < FIRST_PSEUDO_REGISTER) { ... qty_phys_sugg |= ureg; return 0; }`
  — the branch that costs us, reached from `block_alloc` at `:1295` with
  `already_dead = 0`.

**Three separable cures, all three used in this match:**

| cure | how | used by |
|---|---|---|
| (i) refuse the temp a quantity | give it a NAMED variable with **>1 death**, so `:472` rejects it and `combine_regs` bails at `:1763` | **R1** (`CLAMP80S`/`sv`) |
| (ii) remove the pin | only if the pin is not load-bearing — **re-measure, it is base-dependent** | **R4** (`va`, `w`) |
| (iii) starve the suggestion | keep the pinned value **LIVE past the temp**, so `find_free_reg` cannot honour the suggestion | **R7** (zero-byte ref on `c1`) |

Cure (iii) is new and is the one that closed the function. The last two
instructions were `sll $a0,$a0,16` (mine, in place over the pinned `c1`) vs
`sll $v0,$a0,16` (target). `c1` could not be unpinned — it is what spills
`r1lo`, and dropping it or moving it to any other colour costs −64 length
(measured, §4.5). So instead:

```c
((PolyGT3 *)pkt)->rgb1 = rgbw;
__asm__ __volatile__ ("" :: "r" (c1));   /* RC-15, zero bytes */
```

`c1` is now live past the shift, `$a0` is unavailable, the temp falls to `$v0`.
**2 → 0.** Placing it after the rgb2 store also matches; after `uv0` or at the
arm's end does not (they perturb length).

---

## 4. EVERY LEVER MEASURED THIS ROUND

Metric is the `match_one` **mismatch count** (length is exact throughout, so the
raw count is honest — the round-1 metric trap of §5.3 does not apply). Baselines
are stated per block because the base moved as levers landed.

### 4.1 The winning chain

| # | lever | base → result |
|---|---|---|
| **R1** | `CLAMP80S` — named `sv` sum variable on the **two c1 sites only** | 45 → **37** |
| **R2** | unlit arms: `pkt->rgbc = cb \| 0x101010;` (expression, not `cb \|=`) | 37 → **33** |
| **R3** | **`s32 c0, c1, c2, c3;` at FUNCTION scope** | 33 → **21** |
| **R4** | drop the `va→$t2` and `w→$a1` pins | 21 → 17 → **13** |
| **R5** | quad-lit **rgb2/rgb3 only** revert to single-expression | 21 → **11**; with R4 → **3** |
| **R6** | artefact 5 — `ATTEN3W(a3v, a2v, …)` at the QUAD vertex-1 site | 3 → **2** |
| **R7** | RC-15 zero-byte ref on pinned `c1` after the TRI rgb1 store | 2 → **0** |

### 4.2 Neutral — measured, no effect at all

| lever | base | result |
|---|---|---|
| `prod1` / `prod2` / `prodvd` / `prodswap` (named producer-offset temps) | 45 | 45 (fixes 508/510, breaks 513/515) |
| same four | 21 | 21 |
| `cdrop3_t` (drop the unused `c3` from the TRI arm) | 45 / 37 | 45 / 37 |
| `cdropzb_t` (drop the unused `zb` from the TRI arm) | 45 | 45 |
| `qsingle01` (single-expression for quad rgb0/rgb1) | 21 | 21 |
| `prod2` on top of `sumvar_c1` | 45 | 37 (= R1 alone) |
| declaration POSITION of the function-scope `c0..c3` — 5 anchors: before `a0v`, before `cb`, before `d`, before `part`, last | 33 | **21 at every anchor** |
| `qsingle23 + prodvd` / `+ prodswap` / `+ prod1` / `+ prod2` | 11 | 11 |

### 4.3 The REUSE sweep — run in full, every merge LOST

This was round 1's flagged #1 move. It is now a measured dead end here.

| merge | base | result |
|---|---|---|
| `za` → `c0` (QUAD) | 45 | 55 |
| `za` → `c0` (TRI) | 45 | 3294 |
| `zb` → `c1` (QUAD) | 45 | 55 |
| `zb` → `c0` (QUAD) | 45 / 37 | 51 / 43 |
| `f0` → `c3` (QUAD) | 45 / 37 | 51 / 43 |
| `f0` → `c2` (TRI) | 45 | 49 |
| `f1` → `c2` (TRI) | 45 | 838 |
| `f1` → `c3` (QUAD) | 45 | 841 |

**Why it failed, and this generalises:** a REUSE merge raises the survivor's
`reg_n_refs` to move `allocno_compare` priority. But the TRI/QUAD `c0..c3`
grants did not disagree because of *priority* — they disagreed because the two
arms had **two independent allocno sets** at all. No amount of re-ranking inside
one set can make it agree with a different set; only merging the sets can (R3).
**Diagnose whether two grants differ by RANK or by IDENTITY before reaching for
a ref-count lever.**

### 4.4 rgb emit-word forms

| lever | base | result |
|---|---|---|
| `qsingle` (all four quad words single-expression) | 45 / 37 / 21 | 47 / 39 / 23 |
| `qsingle23` (**rgb2/rgb3 only**) | 45 / 21 | **1040 / 11** ← extreme base-dependence |
| `qsingle01` (rgb0/rgb1 only) | 45 / 21 | 45 / 21 |
| `qdirect` (no `rgbw`, store the expression) | 37 / 21 | 44 / 28 |
| `tdirect2` (TRI, no `rgbw`) | 37 / 21 | 47 / 37 |
| `qdirect + tdirect2` | 37 | 54 |
| `tchain` (TRI 3-statement accumulator) | 45 | 2514 (len 4762) |
| `cb_expr_one` (unlit, drop `cb` entirely) | 37 | 2423 (len 4767) |
| one function-scope `u32 rgbw;` (relative style) | 37 | n/a — 4 per-arm decls, lever refused |

### 4.5 The pins — re-measured on every base

| lever | base | result |
|---|---|---|
| `unpin_va` | 45 / 21 | 174 / **17** |
| `unpin_w` | 45 / 21 | 47 / 23 |
| `unpin_va + unpin_w` | 45 / 21 | 170 / **13** |
| `unpin_f0` | 45 / 21 | 88 / 64 — **f0→$s3 stays** |
| `unpin_c1` | 45 / 21 / 3 | 654 / — / **len 4699 (−64)** |
| all four unpinned | 45 | 789 (the round-1 pin-free fallback) |
| c0..c3 at function scope, **pin-free** | 33 | len 4699 (−64) |
| re-pin `c0→$t4` and/or `c2→$t2`/`c3→$a2` **instead of** c1 | 2 | **len 4699 every time** |
| re-pin `c0→$t4` **plus** c1 | 2 | 14 |
| re-pin `c1 + c2` / `c0+c1+c2` / all four / `c1+c3` | 2 | 60 / 71 / 320 / 307 |

**The `c1→$a0` pin is uniquely load-bearing: it is the register pressure that
spills `r1lo`.** No other colour, and no combination without it, reproduces the
spill. Round-1 §5.2's "pinning c0 and c2 *in addition to* c1 is worse" is
confirmed and extended: pinning them *instead of* c1 does not even preserve the
frame.

### 4.6 Artefact-5 localisation (the `sra $a2` vs `$a3` residual)

| lever | base | result |
|---|---|---|
| `ATTEN3W(a3v, a2v, …)` at QUAD site **1** | 3 | **2** |
| same at QUAD sites 0 / 2 / 3 | 3 | 4 / 4 / 4 |
| same at TRI sites 0 / 1 / 2 | 3 | 4 / 4 / 4 |
| `ATTEN3W(a3v, a1v, …)` / `(a3v, a0v, …)` at QUAD site 1 | 3 | 3 / 3 |
| swap the last two `CLAMP80` args (a2v↔a3v) — **all 7 sites tried one at a time** | 3 | 5 at every site |

The `CLAMP80` argument-order hypothesis is **refuted**: the sum order is
identical (3890-3893 are byte-identical in both), and the target's kill branch
at idx 3875 (`addu $a2,$zero,$zero`) already agrees. Only the y-axis **`else if`
destination** differs — a genuine fifth copy-paste artefact, costing zero
instructions.

### 4.7 Other

| lever | base | result |
|---|---|---|
| `sumvar_all` (shared `sv` on all 7 CLAMP sites) | 45 | 4568, **len 4699** |
| `sumvar_q` / `sumvar_t` (per-arm) | 45 | 41 / 41 |
| `prod3` (`vo` on all four offsets) | 45 / 21 | 47 / 23 |
| `prod_ad` / `prod_cd` | 45 / 21 | 50, 52 / 26, 28 |
| `hivar` (named `hi` for `c1 << 16`, both arms) | 2 | 226 (len 4765) |
| `hivar + unpin_c1` | 2 | 4549 (len 4697) |
| zero-byte `c1` ref after the TRI **uv0** store / at arm **end** | 2 | 2471 (len 4764) / 2446 (len 4766) |

---

## 5. LESSONS TO FEED BACK (cookbook candidates)

### 5.1 A "do-not-re-buy" entry is scoped to the BASE that measured it

Three of round 1's measured, correctly-recorded findings inverted once the base
moved:

| round-1 finding | round-2 measurement |
|---|---|
| L4: `c0..c3` per cull block (52% → 93%) | function scope is **strictly better**, 33 → 21 |
| L9: removing the `va` pin costs 4% | removing `va` **and** `w` is worth 21 → 13 |
| L8: quad rgb 3-statement accumulator is +0.02% | single-expression for rgb2/rgb3 is worth 21 → 11 |

`qsingle23` is the extreme case: **1040 mismatched on the 45-base, 11 on the
21-base** — the same edit, two orders of magnitude apart. None of these were
errors in round 1; they were correct readings of a different base.

**Rule candidate:** a do-not-re-buy table must record *the base it was measured
against*, and any entry measured against a base that has since moved by a
structural lever is **stale, not settled** — re-measure the cheap ones (one
0.28 s probe each) rather than inheriting them. Re-testing the whole round-1
"negative" list on the new base cost about 20 seconds of compute and produced
three of the seven winning levers.

### 5.2 The pin's hidden cost: `combine_regs`' unconditional `qty_phys_sugg`

§3 above, with source citations. Worth its own cookbook section: it explains a
whole *class* of 2-instruction "in-place vs not" residuals, and it gives three
separable cures. Cure (iii) — the zero-byte liveness extension — is new, and it
is how a pin can be kept for its allocation pressure while its tie is refused.

### 5.3 Sibling grants are an IDENTITY oracle, not just a hint

If two code paths in the target show *identical* register grants for
corresponding variables, those variables are **one set of allocnos** — i.e. one
declaration at a scope enclosing both. That is a positive structural inference
from register numbers alone, and it beat an exhaustive scope sweep plus a full
reuse sweep. It also agreed with what the two matched relatives already showed,
which is the round-1 report's own advice (§"MATCHED RELATIVES") paying off again:
**5 of 9 winning levers on the last behemoth, and 2 of 7 here (R3, and R5's
2-and-2 split), came straight off a matched relative or off the target's own
register numbering.**

### 5.4 Run the attribution primitive before any scheduling reasoning

§2. Two for two on this family: an apparent scheduling residual that was a
register grant. Cost: three compiles.

---

## 6. WHAT CHANGED IN THE SOURCE (7 hunks vs `s19_func_8017BF14_b1.c`)

1. `ATTEN3W` macro added (artefact 5, y-axis `else` destination).
2. `CLAMP80S` macro added (named `sv` sum).
3. `va` / `w` pins removed; `c0..c3` (with the `c1` pin) moved to function
   scope; `s32 sv;` declared.
4. `CLAMP80(c1, …)` → `CLAMP80S(c1, …)` in both arms.
5. TRI arm: zero-byte `c1` ref after the rgb1 store; unlit `rgbc` written as an
   expression.
6. QUAD arm: `ATTEN3W` at the vertex-1 site; rgb2/rgb3 single-expression; unlit
   `rgbc` written as an expression.
7. The two per-arm `register s32 c1 …; s32 c0, c2, c3;` declarations removed.

---

## 7. FILES

* `.run/giants/s19_func_8017BF14_b2.c` — **the match**, full updated dossier.
* `.run/giants/s19_func_8017BF14_b1.c` — round-1 draft, 45/4763 (kept).
* `.run/giants/s19_func_8017BF14_b1_pinfree.c` — round-1 pin-free, 789/4763 (kept).
* `.run/giants/bf14_mk2.py` — round-2 lever generator. Same contract as
  `bf14_mk.py`: **every transformation asserts it applied**, so a "neutral"
  reading can never be a silent no-op. Levers: `unpin_*`, `RC:` (re-pin),
  `sumvar_*`, `cb_expr*`, `cfn*`, `qsingle*`, `qdirect`, `tdirect2`, `prod*`,
  `merge_*`, `CS:` (CLAMP arg swap), `AW:` (ATTEN3 y-else destination),
  `CL:` (zero-byte `c1` liveness), `hivar`.
* `.run/giants/bf14_sw2.sh` — 8-way parallel sweep over `bf14_mk2.py`, reporting
  the raw mismatch count.
* `.run/giants/bf14_hdr.py` + `bf14_hdr.txt` — dossier-header splicer.
* `.run/giants/r2/` — the promoted bases: `b2base` 37, `b3base` 33, `b4base` 21,
  `b5base` 3, `b6base` 2, `b7base` **0**; `sch_*` the attribution-primitive
  builds; `da/` the `-da` RTL dumps of the 45-base.
* Round-1 harness (`bf14_cc/score/probe/full/side/win/hist/ali/slots/…`) used
  unchanged.

---

## 8. STATUS FOR THE COORDINATOR

`match_one` reports **MATCH (4763 ins)**. That is the candidate gate only.
**The whole-binary SHA1 byte-gate (G3/P9) has not been run and is the sole
arbiter** — this is not a confirmed match until that is green.

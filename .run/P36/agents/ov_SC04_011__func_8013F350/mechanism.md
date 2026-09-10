# func_8013F350 (ov_SC04_011) — T7 agent reading

**Start 70 · FINAL 16 · NOT closed.** All 16 points are in instructions 0-32; instructions 32-489 (458 of
490) are byte-identical in plain C, and the `register s32 off __asm__("$4")` pin is fully replaced by a
one-line statement move. The remainder is the `pd` launder + its `$5` pin, and that half is a wall (below).
Levers in the tree: `register u16 *pd __asm__("$5")`, `register s32 off __asm__("$4")`, and a
`__asm__ __volatile__("" : "=r"(pd) : "0"(pd))` launder on `pd` (sites.txt: all three NEEDED).

## (a) The residual, in one sentence

Two independent defects, and they are **not** the same class: a **TAIL** one — the two derived pointers
`pcur`/`pmax` are computed in the wrong order and take each other's colours (`a0<->a2` ×20 across the whole
byte-poke section) — and a **HEAD** one — the target holds `&D_8011511C` in a register (`lui a1 / addiu a1`,
then `lhu 0(a1)`, `lhu 4(a1)`, `sh 4(a1)`) while every lever-free spelling gets that pointer
**constant-folded away** into three separate `lui/%lo` accesses.

## (b) The passes, read from the compiler's own source and from its dumps

### TAIL — solved. It is a COLOURING move, not a scheduling one. `local-alloc.c` + `reorg.c`.

`off = st << 1;` was written *after* `p2e`/`p3e`. Hoisting it above them is worth **59 -> 23** on the bytes and
takes the entire tail (all 20 `a0<->a2` register pairs and the missing `nop`) to zero. Read off the dumps
(`scratch/dumps/dumps_d_m1` vs `dumps_d_t2`, produced from the two candidates), the chain is:

1. **The RTL order does not change at all.** In BOTH candidates `.sched` and `.sched2` emit the same stream:
   `789` base, ..., `804` = `pcur = off + p2e`, `807` = `pmax = off + p3e`, `811` = `li v0,2`, `812` = `beq`.
   sched1/sched2 are innocent. The tree's header comment says "gcc otherwise emits pmax before pcur" — true of
   the ASSEMBLY, but the RTL order never changes; what moves is the colouring, and reorg then reorders the
   printed stream. Worth correcting in the tree's note, because the wrong attribution sends the next reader
   to `sched.c`.
2. **The COLOURS change.** With `off` written last: `p2e`->`$a0`, `off`->`$v1`, `pcur`->`$a0` (reusing the dead
   `p2e`), `pmax`->`$a2`. With `off` written first: `off`->`$a0`, `p2e`->`$v1`, `pcur`->`$a2`,
   `pmax`->`$a0` (reusing the dead `off`) — the target's assignment. This is `block_alloc`'s ordering of the
   block's quantities (`local-alloc.c:1483-1512`, `qty_compare` at `:1579`) feeding `find_free_reg`'s
   lowest-free-regno live-range scan (`local-alloc.c:2109-2158`): moving the statement moves `off`'s birth
   ahead of `p2e`/`p3e`, so `off` takes `$a0` and dies into `pmax`.
3. **`reorg` then decides the `nop`.** `fill_simple_delay_slots` scans BACKWARD from the branch
   (`reorg.c:2906-2952`), skipping insns that conflict and **accumulating their `set`/`needed` as it goes**.
   Branch `beq $a1,$v0`: `needed = {a1,v0}`.
   * mine: `li v0,2` conflicts (sets `$v0`); `pmax = addu $a2,$v1,$v0` conflicts (reads `$v0`, now in `set`);
     `pcur = addu $a0,$v1,$a0` touches nothing in `set`/`needed` -> **eligible, stolen into the delay slot**.
   * target: `li v0,2` conflicts; `pmax = addu $a0,$a0,$v0` conflicts; `pcur = addu $a2,$a0,$v1` now READS
     `$a0`, which the skipped `pmax` put in `set` -> conflict; every earlier insn conflicts too -> **`nop`**.

   So the `nop` is a *consequence* of `pmax` reusing `off`'s register, not an independent scheduling fact.

### HEAD — a wall for plain C. `cse.c:2663-2665`, in `find_best_addr`.

```c
  if (GET_CODE (addr) != REG
      && validate_change (insn, loc, fold_rtx (addr, insn), 0))
    addr = *loc;
```

`fold_rtx` resolves `(reg pd)` through `equiv_constant` (`qty_const`, set because `pd`'s only set is
`(set (reg 72) (symbol_ref "D_8011511C"))`), so `(mem (plus (reg pd) 4))` — i.e. `pd[2]` — is rewritten to
`(mem (const (plus (symbol_ref "D_8011511C") 4)))`, an address MIPS accepts, so `validate_change` succeeds.
**Verified in the dumps**: `dumps_cur/cur.i.cse` already carries the folded `(const (plus (symbol_ref
"D_8011511C") (const_int 4)))` for both `pd[2]` sites while `.jump` (pre-cse) does not. That leaves `pd` with
one remaining use, `(mem (reg pd))` for `*pd`, which **combine** then substitutes and deletes
(`dumps_cur/cur.i.combine` line 17 is `(mem:HI (symbol_ref "D_8011511C"))`; the pseudo is gone by `.lreg`).

The zero-byte launder works because the asm gives `pd` a second SET and an unknowable value, so `qty_const`
is never set and neither fold can fire. **There is no plain-C equivalent**: any spelling of a link-time
constant address is a constant to cse, so the moment one use carries a non-zero offset that use is folded,
and the remaining zero-offset use is then single-use and folded by combine.

The known-true control is `func_8013F138` (`src/ov_SC06_008/ov_SC06_008_jr_8013C98C.c:2209`), which keeps its
base in plain C — `u16 *p = &D_80115118; *p += 0x10;` — and does so **only** because it has TWO uses and both
are at offset 0: `find_best_addr` returns early for a plain `(reg)` address, and combine cannot substitute a
reg with two uses. Our function needs offsets 0 **and** 4, so it falls outside that escape.

## (c) The source moves

1. `off = st << 1;` moved **above** `p2e = ...; p3e = ...;` (a 1-line statement move). 59 -> 23. Closes the
   whole tail; this is the plain-C replacement for the `register s32 off __asm__("$4")` pin.
2. `s32 pad;` instead of `u16 pad;` (R12). 70 -> 59. **This one is a compensating error, not a fix**: it
   deletes the target's real `andi v1,a0,0xffff`, which cancels the ONE extra instruction the folded head
   costs (3 x `lui/%lo` = 6 insns where the target's held base needs 5). It keeps the instruction count at
   490 = 490 and is worth 11 points, but it is not part of any byte-identical spelling.
3. `do { chg = 0; } while (0);` (R7). 23 -> 16. Also a compensating move, and not readable: it only shuffles
   the head's remaining wrong instructions closer to the target's. **`body.c` is the best-scoring text, not a
   proposal for the tree** — a readable stop would be `u16 pad; chg = 0;` plus move 1 alone, which scores 42
   but contains only the one honest fix. Nothing here is bankable: the score is not 0.

## (d) GENERATOR PROPOSAL

**When two derived pointers built from one shared operand (`x = A + t; y = B + t;`) swap registers in the
residual, and the target has a `nop` in a delay slot where mine has one of them, hoist the SHARED operand's
defining statement to the front of its straight-line run.**

Mechanically: for every local `t` that is read by two or more later statements of the same brace block, offer
the candidate with `t`'s defining statement moved to the first position of the run that contains all of its
readers. That is one candidate per such local — a handful, not a search. It is `R18 bystander_moves` with the
independence test INVERTED: R18 only moves a statement that shares NO identifier with what it crosses, which is
precisely why seven mechanical runs and ~4,000 compiles never generated this one; the move that matters here
shares `st`/`off` with everything around it. The payoff is that the shared operand is born first, so it wins the
low register and DIES into the second consumer, which is what the `register T x __asm__("$4")` pin was faking.
**Byte-proven here: 59 -> 23 in one compile, closing 458 of 490 instructions.**

## (e) What did NOT work, with byte evidence (every number is a `--try` score)

* `u16 *pp = pd + 2` / `u16 *pe = &D_80115120` with `*pp` at both `pd[2]` sites — **70 / 39**. The dumps say
  why: with a plain-`(reg)` address cse1 keeps it (`dumps_s5/s5.i.loop` still has `(mem (plus (reg 72) 4))`),
  but cse1's own `ADDRESS_COST` tie-break at `cse.c:2710-2726` — *equal address cost, higher rtx cost wins* —
  rewrites `(reg pe)` back to `(plus (reg pd) 4)`, and cse2 then folds it (`.flow` has the constant).
* A second, redundant `pd = &D_8011511C;` in either arm of the `if` (the §349 "make the base set more than
  once" lever) — **23, i.e. no change**: jump/flow delete the redundant set before `reg_n_sets` is read.
* `register u16 *pd` (the plain-C keyword, no asm) — **70**. DECL_REGISTER does not reach cse.
* Struct-pointer spelling (`struct { u16 f0, f2, f4; } *pd`) — **23** (identical RTL).
* Splitting the declaration from the initializer, reordering `chg = 0;` / `pad = *pd;`, `{ }` and
  `do { } while (0)` around `pad = *pd;`, inverting the outer `if`, swapping the inner arms, a `goto` tail —
  **23, 23, 23, 33, 46, 26, 46**. None changes the fold.
* Reusing `pd` for the tail's `ps` (two sets, natural) — **67**: it merges the two bases and breaks the tail.
* Widths on `off` (u16/s16/s8/u32) — **65/65/65/59**.
* **The positive control**: `body.c` + the launder alone scores **9** and its class is `REG-caller` — the only
  thing left after the launder is the 3-cycle `pd v1->a1 / pad a1->a0 / masked-pad a0->v1`, which is what the
  `$5` pin buys. So the head is worth 16 of the residual and is the whole remaining distance.

* **`volatile` does not rescue the head either** (run only as a control — it is banned in the deliverable):
  `volatile u16 *pd` scores **29 at 493 instructions** (three EXTRA insns; volatile blocks the fold but also
  blocks every reuse), and a `(u16 *)(volatile u16 *)` cast scores **42**, identical to no change. So the head
  is not a "banned-construct" wall that a rules change would open — only a value cse cannot know opens it.
* **One-move exhaustion**: after reaching 16 I ran every delever generator (R2,R3,R4,R5,R6,R7,R8,R9,R10,R12,
  R13,R14,R15,R16,R17,R18,R19,R20,R21 — 313 candidates) over the 16-body through `--try`. **No single move
  improves it.** 16 is a one-move local optimum, and it is the same 16 the mechanical runs reached by a
  different four-move path.
* **Final residual scope**: every difference is inside instructions 0-32. Instructions 32-489 (458 of 490) are
  byte-identical, in plain C, with the `$4` pin removed.

## (f) Where the method fell short

* Step 2's "COUNT FIRST" was misleading here: the counts are **equal** (490 = 490) and the class prints
  `COUNT`, yet nothing is missing — two opposite errors cancel (the folded head is +1 insn, the `s32 pad`
  widening is -1). A count check that only compares totals hides that. What actually located both defects was
  the whole-function `objdump` of the tree's own object versus the candidate's `.s` (step 1), read side by
  side around the two `lui` sites.
* `alloc_table` was of no use on this body: the defect never reaches allocation, because the pseudo is
  **deleted by combine** before `.lreg`. The table's 158 rows are all downstream of that. A cheap pre-check —
  "is the pseudo you are reasoning about still present in `.lreg`?" — would have saved the detour.
* The pack's `history.txt` reports the mechanical best as 16 with a four-move path; hand-reconstructing that
  path from the descriptions landed at 51 (the `@NNNN` line numbers are relative to the *evolving* text, not
  to `body_free.c`). Re-running delever's own generators through `--try` reproduced it in one round. A pack
  that shipped the best candidate's TEXT, not just its move names, would have saved ~30 minutes.
* **`neighbours.txt` dropped the one document that mattered.** It reproduced this function's own
  `// @class: regalloc-order` / `// @stuck: none — MATCH (490 ins, ...)` pair and stopped there — but the
  header comment those two lines belong to (`src/ov_SC04_011/ov_SC04_011_jr_8013F350.c:910-948`) is a
  **numbered, eight-point English explanation of every lever in this body**, including "gcc otherwise emits
  pmax before pcur, letting pcur sink into the beq delay slot (target has a nop there)" — which is the tail
  crack, stated outright, and which I re-derived from the dumps before I found it. The pack should carry the
  function's own header comment IN FULL, not just the two tag lines grepped out of it.

## Score ladder (every number from `--try`, in order)

| body | score |
|---|---|
| `body_free.c` (start) | 70 |
| `+ s32 pad` (R12) | 59 |
| `+ off = st << 1;` hoisted above `p2e`/`p3e` | **23** |
| `+ do { chg = 0; } while (0);` (R7) | **16** |
| `off`-hoist alone, `u16 pad` kept | 42 |
| control: `body_free.c` + the launder only | 45 |
| control: the 23-body + the launder, `s32 pad` | 27 |
| control: the 23-body + the launder, `u16 pad` | **9 (REG-caller — only the `$5` pin's 3-cycle left)** |

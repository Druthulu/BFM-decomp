# func_8013DD68 (ov_SC04_011) — T7 residue reading

Lever-free start **17**; the mechanical search's best **14** (its widest trace, g5, reached 7).
**Final: 2** — 187 instructions against 187, class ORDER, every register identical, **one instruction out of place.**
Not banked. ~6,500 scored compiles.

`body.c` = the score-2 text. `body_altB.c` = the other score-2 spelling (a smaller block, a different last instruction).

---

## (a) The residual in one sentence

Lever-free the body differs in two independent ways: **(1)** the loop's hoisted `0x00ffffff` bit-field mask and the loop
counter `iVar14` exchange hard registers (`$a3`↔`$t0`, 9 instructions) because the global allocator sorts the two
allocnos the wrong way round, and **(2)** the list scheduler hands out different load-delay fillers inside the loop,
costing an extra `nop` (188 vs 187). (2) is reachable from statement order; **(1) is not** — it is an allocation-priority
comparison that no statement order can move.

## (b) The pass and the decision, read from the compiler and then measured on the dumps

### (1) `global.c allocno_compare`, fed by `flow.c`'s loop-depth reference weighting

`global_alloc` sorts the allocnos by

```
pri = floor_log2(n_refs) * n_refs / live_length * 10000 * size      (global.c, allocno_compare, descending;
                                                                     ties break on the allocno number, v1 - v2)
```

and `find_reg` gives each one the first free register in `REG_ALLOC_ORDER`, so the allocno sorted earlier gets the
lower-numbered hard register. `flow.c:2067` (and `:2315 :2501 :2711`) accumulates `reg_n_refs[regno] += loop_depth`:
a reference at function level is worth 1, a reference inside one loop 2.

Read out of the real `-dl`/`-dg` dumps of this TU (`cpp | cc1 -O2 -G0 -mips1 -mcpu=3000 -msoft-float … -dl -dg -df -dS`),
lever-free:

| pseudo | what it is | `used N times across M insns` | where the refs come from | pri |
|---|---|---|---|---|
| **79** | `iVar14` | **7 / 81** | `1` init (depth 1) + `3 × 2` (the set, the use and the compare, depth 2) | `2*7/81 = 0.1728` |
| **149** | the loop's `0x00ffffff` — `(set 149 (const_int 16711680))` then `(set 149 (ior 149 65535))`, `REG_EQUAL 16777215` | **7 / 58** | `3` for the two-insn constant (depth 1) + `2 × 2` for the two `and`s (depth 2) | `2*7/58 = 0.2414` |

`;; 17 regs to allocate: 195 100 172 93 194 72 97 92 94 74 **149 79** 80 153 141 73 121` → `149 in 7` (`$a3`),
`79 in 8` (`$t0`). The target wants them the other way round; the whole 9-instruction register residual **is that one
comparison**.

The two numerators are equal (`2*7`), so the ordering is decided by `live_length` alone: 58 against 81. Neither side of
that can be moved:

* `iVar14` is live from `move a3,zero` (before the guard) to the loop's `slt` — its 81 is already near the floor,
  and it would have to drop below **58** to win on length, i.e. below the loop body itself (~72 insns). Impossible.
* pseudo 149 is defined in the loop preheader and last used ~12 insns from the loop bottom, so 58 is already near its
  ceiling; it would need **≥ 81**. Its 3 preheader refs are the MIPS two-insn materialization of `0x00ffffff`
  (`lui`+`ori`) — note that the sibling constant `0xff000000` (pseudo 153) is **one** insn and therefore only 5 refs.
  Nothing in C chooses that.

So the only reachable move is **one more weighted reference on `iVar14`**: at 8 refs `floor_log2` steps 2 → 3 and
`pri` becomes `3*8/81 = 0.2963 > 0.2414`.

**Byte proof that it is `iVar14`'s weight and nothing else.** Wrapping each of the 22 loop statements in
`do { } while (0)`, one at a time (22 compiles), clears the `$a3`/`$t0` pairs for **exactly one** of them — the
`iVar14 = iVar14 + 1;` statement (score 7, `pairs []`); all 21 others keep the pairs. The `-dl` dump of that spelling
differs from the plain one in exactly one line: `Register 79 used 7 times → used 9 times`, `across 81 insns` unchanged.
That is `residual_moves.md` row 1a-7 (verified there on `func_80135D20`) reproduced as arithmetic.

### (2) sched1 / reorg

`sched.c schedule_block :3144`, `rank_for_schedule :2385`, LUID tie-break `:2428` (LUID = source order, `:2175`).
`iVar14` has two sets, so `adjust_priority` / `birthing_insn_p` (`:2507` / `:2469`, gated on `reg_n_sets == 1` at `:2490`)
never boosts it — its position is its LUID, which is why moving the increment statement is a lever at all.

### The trap, and the move that got past it

`do { } while (0)` is **two** things at once: the loop-depth ref weight **and** a two-sided scheduling barrier
(`sched.c:2058-2074` — a LOOP note mid-block adds every register dependence and flushes the pending lists). Put it
around the increment and you buy the registers and immediately lose an instruction: the barrier pins the increment at a
block boundary, so it can never land in the load-delay slot of `lhu v0,-4(a2)` where the target has it — an extra `nop`,
and the score floors at 4.

**The weight and the barrier can be separated: the extra reference only has to be on `iVar14`, and `iVar14 = 0;` lives
outside the loop.** Wrapping the initialization leaves sched1 completely free inside the loop — the whole loop body then
matches to the instruction, and the residual moves out to the prologue.

## (c) The moves, one line each (17 → 2)

1. `uVar2 = q[-7];` deleted and inlined at its single use: `*(u8 *)((int)puVar10 + -7) = (u8)q[-7];`  → **14**
2. that store exchanged with `*(u16 *)((int)puVar10 + -6) = 0x7800;`, so the load sits at its use → **7**
3. the tail of the pre-loop run — `buf.env = …` through `iVar14 = 0;` — wrapped in `do { … } while (0);` → **2**
   (the ref-weight move; the `$a3`/`$t0` swap and every scheduling difference inside the loop are gone)

`body_altB.c` reaches the same 2 with a smaller block: `iVar14 = 0;` moved up to just after `SetDrawEnv(p, &buf);` and
only `{ iVar14 = 0; ((P_TAG_8013DD68 *)p)->addr = OTE->addr; OTE->addr = (u32)p; p = p + 0x10; }` wrapped.

## (d) GENERATOR PROPOSAL

**When the residual is a two-register exchange between a loop counter and a loop-invariant constant, take
`floor_log2(n_refs)*n_refs/live_length` for both pseudos from the `-dl` dump and, if the counter loses, wrap the
counter's INITIALIZER — never its increment — in `do { … } while (0);`, then widen that block backwards over the
preceding statements while the score falls.**

Generalized: for any REG-class residual, read the `;; N regs to allocate:` line of the `-dg` dump, find the adjacent
pair that has to swap, and add one loop-depth weight to whichever of the two has a reference OUTSIDE the loop — that is
the only place the `do { } while (0)` costs no schedule. (Today's `R7 block` generator wraps one statement, always
inside the loop; it can reach 4 here and never 2.)

## (e) What did NOT work, with the byte evidence

* **Statement order alone is spent.** A 3-deep beam over "move one loop statement anywhere" (~4,000 compiles from the
  best score-4 seed) plateaus at 3 and never removes the register swap. A 3,000-candidate randomized 2-3-move search over
  (pre-loop order × block range × loop order × declaration order) never beat 2.
* **The increment's spelling is inert.** `iVar14++`, `++iVar14`, `iVar14 += 1`, `iVar14 = iVar14 + 1` all score 7 at
  every one of the 22 positions, and so do `while (++iVar14 < (int)(u32)uVar1)`, `while ((iVar14 = iVar14 + 1) < …)` and
  `while ((iVar14 += 1) < …)` — pairs still `a3→t0 ×5, t0→a3 ×4`. `for (iVar14 = 0; …; iVar14++)` is much worse
  (26 with the init in the header, 13 without): `duplicate_loop_exit_test` rebuilds the guard.
* **`register int iVar14;`** (the bare keyword, no pin) is inert — 7, pairs unchanged; and so is it on all 11 locals.
  gcc 2.7.2 ignores `register` for allocation at `-O2`.
* **Declaration order** is inert here: all 121 single moves of the 11 declarations leave the score at 2.
* **Wrapping the increment**, or any contiguous loop range containing it (260 compiles over every `[i..j]`), floors at 4:
  the barrier costs the `lhu v0,-4(a2)` delay-slot filler and the function is 188 instructions.
* **`for (;;) { … break; }` and `while (1) { … break; }`** are byte-identical to `do { … } while (0)` at both block
  positions (2 and 2) — the note footprint is the same.
* **Naming the block copy's destination** (`DrawEnv_8013DD68 *dst; dst = &buf.env;` before the block, `*dst = …` inside)
  does not free the `addiu a3,sp,16`: cse's `find_best_addr` folds the frame address back into the MEM and the copy dies.
  Still 2, same defect.
* **Splitting `((P_TAG_8013DD68 *)p)->addr = OTE->addr;` into `tmp = OTE->addr;` + the store**, to get the mask constant
  emitted above the block opener, costs 14 points (16): the split re-plans the whole entry block.

## What is still open at 2

Two spellings, each one instruction from the bytes, and the two are complementary:

```
body.c        mine   … lhu v1,0(v1) | sw s2,144(sp)  | …12 insns… | addiu a3,sp,16 | addiu a2,v0,56 | …
              target … lhu v1,0(v1) | addiu a3,sp,16 | sw s2,144(sp) | …            | addiu a2,v0,56 | …

body_altB.c   mine   … jal | sb zero,40(sp) | move a3,zero  | lui a0,0xff | ori a0,a0,0xffff | lui a1,0xff00 …
              target … jal | sb zero,40(sp) | lui a0,0xff | ori a0,a0,0xffff | move a3,zero  | lui a1,0xff00 …
```

`addiu a3,sp,16` is the destination address of the `buf.env = *(DrawEnv_8013DD68 *)(base + 0x38);` block copy; the target
has sched2 weave it into the prologue, above the `$s2` save. Whatever statement is FIRST inside the `do { … }` gets
pinned at the top of the region and can no longer rise into the prologue — that is the whole of `body.c`'s residual, and
it is why widening the block past the copy costs the instruction. Pulling the block opener down past the copy instead
(start at 7 or 8) leaves `sb zero,40(sp)` unable to reach the `jal` delay slot (6); pulling it down past the call
(start at 9) is `body_altB.c`, where `move a3,zero` is then pinned two slots too early. The wanted boundary falls in the
MIDDLE of one statement's insns, and no statement-level move can put it there.

**What would close it:** anything that gives `iVar14` one more weighted reference without planting a note — i.e. a real
extra reference in the source. I could not find one that keeps the semantics and the instruction count.

## (f) Where the method fell short

* The pack has no allocation table. Everything decisive here came from two numbers in the `-dl` dump
  (`used 7 times across 81 insns` vs `used 7 times across 58 insns`) and one line in `-dg`
  (`;; 17 regs to allocate:`). Computing `floor_log2(n)*n/L` for the residual's register pair turned a guessing game into
  arithmetic and also **proved a negative** — that the live-length side is unreachable — which no amount of hill-climbing
  could have shown. A `tools/alloc_table.py`-style "priority table for the pair named in `pairs:`", generated into the
  pack, would have got here in one step instead of forty.
* The engine's block generator (`R7`) only ever wraps ONE statement and only inside the loop. The entire win here is a
  multi-statement block placed OUTSIDE the loop, chosen by widening backwards. That is a cheap generator to add and it
  generalizes to every REG residual whose loser has an out-of-loop reference.
* `--try` prints a masked-word diff but not the surrounding instructions, and the edit distance conflates "one
  instruction 13 slots late" with "two real differences". I had to rebuild an aligned `objdump` view before any of this
  was readable; that view belongs in `--try` behind a flag.
* `history.txt` records only scores and move names, not the residual CLASS each move left behind. "R6 inline uVar2 → 14
  [COUNT]" is much less useful than "…and the `a3`/`t0` pairs survive", which is the fact that decides whether the search
  is even working on the right axis.

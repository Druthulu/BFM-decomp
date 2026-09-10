# func_80140958 (src/ov_SC04_011/ov_SC04_011_jr_80140608.c), T7 agent c13, S103

**Status: NOT CLOSED — score 4 (260/260 ins, class ORDER) from 43; no pin, no asm, no added volatile, no invented term.**
`body.c` is the current best text. The only remaining diff is the order of the three pre-loop statements
(`t3v`, `k`, `j`) — see (c) move 4 and (f).

## (a) The residual in one sentence
The lever-free start (43, 260 vs 260) was four independent defects that happened to sum to the same count:
(1) the constant 8 for the sprite's w/h was hoisted out of the inner loop into `$t1` (one extra register, so every
temp `t1..t5` shifted by one), (2) the sprite's y store was scheduled after the `lui/ori` of the rgb word instead of
being the first insn of the join, (3) in the second addPrim statement `op` and `ot & 0xFFFFFF` had each other's
registers, and (4) the inner-loop counter `j` and the index `k` had each other's registers (`$a2`/`$a3`).

## (b) The passes and decisions (read in gcc-2.7.2 source, proven on dumps and bytes)
1. **The 8 (defect 1): loop.c invariant motion.** `scan_loop` (`loop.c:681-690`) accepts a set as movable if
   (1) the reg is used only in the set's basic block (`reg_in_basic_block_p`, which also requires
   `regno_first_uid == this insn`), or (2) it is not a user variable, or (3) the set always executes. The free body's
   `eight = 8` is a user var set and used in one block, so case (1) holds; `move_movables` (`loop.c:1631`) then moves it
   because `threshold*savings*lifetime = 58*1*2 >= 75 insns` (threshold `2*(1+28)`, `loop.c:532`; 28 non-fixed regs
   with -msoft-float). A literal `8` is case (2) and moves too (proven: 57/261).
   **Fix:** give the variable an earlier mention — a dead initializer `s16 size = 0;` at the block top. Now
   `regno_first_uid` is the initializer, so `reg_in_basic_block_p` fails, the set is past the `j==0` branch
   (`maybe_never`), and it is a user var: none of (1)-(3) hold, the set stays in the loop. flow then deletes the dead
   initializer (it reaches no use), so the register is referenced in ONE block, dies once, and becomes a local-alloc
   qty (`local-alloc.c:472`) whose density (3 refs over 2 insns) beats the two x-coordinate loads, so it takes `$v0`
   and they take `$v1`/`$a0` — exactly the target. Proven on bytes: on the same base, `s16 y;` scores 28 (8 hoisted to
   `li t1,8`) and `s16 y = 0;` scores 6 (`scratch/a2arm.c` vs `scratch/y1.c`).
2. **The y store (defect 2): jump2 cross-jumping.** The target's arm A ends `j 620` into the MIDDLE of arm B's tail:
   `sh v0,-6(a1)` at 0x620 is the first insn of the join and arm A's `addiu v0,v0,-4` sits in the jump's delay slot.
   That is the `find_cross_jump` fingerprint (`jump.c:2371`, post-reload `jump_optimize(insns,1,1,0)`): each arm ended
   with its own identical `sh v0,-6(a1)` and jump2 merged them. **Fix:** store y inside each arm
   (`*(s16 *)(q - 10) = *e - 4;` / `= *e + 3;`) instead of through a variable stored at the join.
3. **addPrim (defect 3): sched1 birthing boost + local-alloc density.** `sched.c:2469-2540`: an insn whose dest is a
   single-set pseudo live below it gets `max_priority` (`birthing_insn_p`, requires `reg_n_sets == 1`). With the
   expression `(op[2] & mhi) | ((u32)ot & m24)` both the `op[2]` load and the `ot & m24` value are single-set and
   boosted, and sched1 placed `ot & m24` early; its local-alloc window then widened past `op`'s and
   `qty_compare_1` (`local-alloc.c:1598`) ranked `op` first (27/12 = 2.25 vs 12/8 = 1.5), so `op` took `$v1`.
   The P_TAG bitfield `addPrim` (`src/shared/engine_types.h:517`, used by the sibling `func_80140D68`) produced the
   target block exactly: `store_fixed_bit_field` reuses ONE register for load/and/or (`subtarget`), so that chain is
   multi-set, is not boosted, and `ot & m24` lands after the `op[2]` load. (The bitfield form itself cannot be used
   here: its mask constants get hoisted out of the OUTER loop into `$s4/$s7` — proven 72.)
   **Fix:** spell the same RTL by hand with a reused local: `w = op[2]; w &= mhi; w |= (u32)ot & m24; op[2] = w;`.
   Proven: the addPrim hunk closes (score 9 → 4).
4. **j vs k (defect 4): global.c allocno_compare (`global.c:594-609`).** Inner-loop refs are weighted by loop depth 3
   (`flow.c:2067`, depth counted from 1 at function level, `flow.c:440-471`). Start: k = 13 refs / 74 live
   (set 2 + `t3v = k*4` 2 + three inner uses 9; cse made `t3v` read k because k is the longer-lived member of the
   `k = m` class, `cse.c:make_regs_eqv`), j = 11 / 75 → k = 5270 > j = 4400, so k took `$a2`.
   **Fix (partial):** compute `t3v = m * 4` BEFORE `k = m` (cse has not yet made k canonical, so t3v reads m and
   k drops to 11 refs) and set `j = 0` last (sched1 keeps source order for these leaves, so j is born last and lives
   shortest). j = 11/72 = 4583 > k = 11/73 = 4520 → j `$a2`, k `$a3`. Proven on dumps (`scratch/dumps_k9`) and bytes.
   Cost: the three pre-loop insns come out in the order `t3v, k, j` instead of the target's `j, k, t3v` (score 4).

## (c) The moves (current body.c)
1. `s32 eight;` removed; `s16 y;` becomes `s16 size = 0;` and the w/h stores go through `size = 8;`.
2. The y stores move into the two arms (`*(s16 *)(q - 10) = *e - 4;` / `= *e + 3;`); the join store is deleted.
3. The second addPrim statement uses a reused local `w` (load, `&= mhi`, `|= ot & m24`, store).
4. The pre-loop statements are ordered `t3v = m * 4; k = m; j = 0;`.

## (d) Generator proposals
- **Hoisted constant (count-neutral register shift):** when the target materialises a constant inside a loop that
  yours hoists (an extra `li tN,C` before the loop, every temp shifted by one), give the constant's variable a dead
  initializer at the enclosing block's top (`T v = 0;` ... `v = C;` in the loop). loop.c then refuses it
  (`reg_in_basic_block_p` needs `regno_first_uid == set`) and flow deletes the initializer, so it is still a
  one-block local qty.
- **Cross-jump fingerprint:** when the target's arm ends with `j L` where L is the middle of the other arm's tail
  (the first insn at L is a store/op identical to the jumping arm's last), duplicate that statement into both arms.
- **Bitfield-store RTL by hand:** when a `(x & HI) | (v & LO)` read-modify-write has `op`/`value` registers swapped,
  rewrite it as `w = *p; w &= HI; w |= v & LO; *p = w;` (a multi-set temp: no sched1 birthing boost).

## (e) What did not work (byte evidence, scratch/*.c)
- literal `8` stores (c1: 57/261), `eight` as s16 (history R12), `*(q-4) = *(q-2) = 8` (chain: 57), a store copy
  (copy: 57): every non-user or single-block user pseudo for 8 is hoisted.
- y reused for the 8 (c3/c4: 39/29): not hoisted (y is set 3 times) but y becomes a global allocno and loses `$v0`
  to the x-coordinate temps (they are local and allocated first).
- `t` (function-scope s16) reused for the 8 (e1: 35): global allocno, wrong register.
- the bitfield P_TAG addPrim (b1/b2: 72/263): masks hoisted out of the outer loop.
- `(ot & m24) | (op[2] & mhi)` (a2: 19): fixes op/OM but ties the `or` result to OM (`or v1,v1,v0`).
- j/k: `++j`, `j = j + 1`, `j += 1`, `<= 1`, `!j`, `(s32)j`, arm swap, `for` vs `do`, i-indexed inner loop
  (i1/i2), `t3v = i*4 / c3*4 / b[0]*4`: none changes j's 11 refs.
- a goto-built inner or outer loop (g1-g4): 44-63.
- duplicating the draw code into both arms (d1: 96/265): combine_movables pairs the constants and hoists them.

## (f) Where it stops, and where the method fell short
**The last 4 points are the j/k allocation order, and I could not close them without a lever.** What the bytes pin down:
- **Source order.** For this block's leaf insns, sched1 keeps the source order. I checked this on four orderings
  (r1, x2, x5, k9, printed side by side). The target's pre-loop order is `move a2,zero / move a3,v1 / sll t3,v1,2`,
  which is `j = 0; k = m; t3v = ...`. So j is born first and lives one insn longer than k (measured Lj = Lk + 1).
- **cse.** With `k = m` before `t3v`, cse rewrites t3v to read k (`make_regs_eqv`: k lives longer, so it becomes the
  canonical register). That leaves k at 13 refs.
- **What the target needs.** Given those two facts, j needs at least 14 weighted refs (or k at most 10). The tree's
  `__asm__ volatile("" :: "r"(j))` adds exactly one depth-3 ref (+3 → 14). That is lever [L2], and every overlay copy of
  this function carries it.
- **What the target code rules out.** Every instruction in the target's inner loop is accounted for, and j is read in
  only 4 RTL places (checked in the `.flow` dump). So an extra ref would have to sit in an insn that a pass after flow
  deletes (combine, a reload no-op move, or a jump2 cross-jump of duplicated source code).
  - The loop-exit test reads the SImode increment temp, not j. reorg's copy-propagation cannot have rewritten it:
    `reorg.c:3490` refuses when the next insn sets the copy's source, and `sll v0,v0,16` sets v0.
  - Refuted on bytes: `for`/`do`/`while` forms, every increment spelling, `<=`, `!j`, casts, swapped arms,
    `for (j = 0; ...)`, an `i`-indexed inner loop, and explicit `j++` before each `continue` (w1: j gets 26 refs and
    the right register, but the increments become `addiu a2,a2,1` and do not merge: 16/259).
  - Also refuted by reading the source: a register preference via `regs_someone_prefers` (no non-call-crossing
    allocno prefers a2), `regs_used_so_far` (a2 is used by block-0 locals), and a REG_EQUIV live-length doubling of k
    (cse would pick `li a3,3` if it knew the constant, as the tree's [L1] note records).
- **The best lever-free text** (`body.c`) trades the order for the registers: `t3v = m * 4; k = m; j = 0;`, so k has
  11 refs and j is born last. The allocation matches and only the three `move/sll` insns are out of order.
  The alternative (`x5.c`, `for (j = 0; ...)`) is also 4.

**Method notes.**
1. The allocation table was essential: it showed j 11/75 against k 13/74 immediately.
2. The sched1 `;; ready list` / priority lines in the `.sched` dump were what explained the addPrim hunk.
   `scratch/sblk.py` extracts them per block, and a tool like it belongs in `tools/`.
3. The residual hunk view hid the cross-jump. Only the whole-function dump showed `j 620` landing on a store.
4. The biggest single time sink was the hypothesis "the 8 must be a non-movable local". Its resolution (a dead
   initializer defeats `reg_in_basic_block_p`) came from reading `scan_loop` line by line, not from any table.
   A `.loop` dump reader that prints each movable's case (1)/(2)/(3) verdict would have found it in minutes.

Paths: `body.c` (score 4), candidates in `scratch/*.c`, dumps in `scratch/dumps_*`, helpers in `scratch/t.sh`,
`scratch/dump.sh`, `scratch/at.sh`, `scratch/var.py`, `scratch/blk.py` and `scratch/sblk.py`.

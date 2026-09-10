# func_80140958 (src/ov_SC04_011/ov_SC04_011_jr_80140608.c), T7 agent c13, S103

**Status: IN PROGRESS — score 4 (260/260 ins, class ORDER), no pin, no asm, no added volatile, no invented term.**
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
   and they take `$v1`/`$a0` — exactly the target. Proven on bytes (43 → ... → 6 with this move).
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

## (f) Where the method fell short / open question
The last 4 points are the `j`/`k` priority. The target's pre-loop order is `j = 0; k = m; t3v = …` (sched1 keeps the
source order for these leaves — proven on four variants), so j is born first and lives one insn longer than k; with
that order the target needs j >= 14 refs against k's 13 (or j >= 12 against 11). Every spelling tried leaves j at 11.
The tree's `__asm__ volatile("" :: "r"(j))` supplies exactly +3 (one depth-3 ref). No natural zero-code reference
to j has been found yet.

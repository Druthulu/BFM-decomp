# func_80140958 (src/ov_SC04_011/ov_SC04_011_jr_80140608.c), T7 agent c29, S103

c13's files are preserved in `scratch/prev_body.c` and `scratch/prev_mechanism.md`. All my scratch (candidates, spliced
TUs, dumps, helpers `t.sh` / `jk.sh` / `mk.sh`) is in `scratch/c29/`.

**Status: NOT CLOSED. Score 4 (260/260, class ORDER), the same as c13's.** The difference is that the dead initializer
c13 used for the loop constant is gone. `body.c` contains no pin, no asm, no added volatile, no invented zero term and
no dead store. The remaining 4 points are the pre-loop order `sll t3 / move a3 / move a2` against the target's
`move a2 / move a3 / sll t3`. Section (b2) argues that no honest spelling of this function can reach that order and
still allocate correctly. It is an argument from the passes, checked on bytes wherever I could.

## (a) The residual in one sentence
With c13's order (`t3v = m*4; k = m; j = 0;`) the registers match and the three pre-loop instructions come out reversed.
With the tree's order (`j = 0; k = m; t3v = m*4;`, `scratch/c29/s1o.c`) the order matches and j and k swap `$a2`/`$a3`
(score 10).

## (b1) Problem 1, the loop constant 8: SOLVED without a dead store (proven on bytes)
**Move:** `size` becomes a function-scope `s16`. It feeds the third call's fourth argument, where the tree has a
literal 8: `size = 8; ot = func_80140D68(ot, p, 2, size, ...);`. The loop keeps `size = 8;` before the two stores.
Both assignments are read in the source.

**Mechanism:**
- `scan_loop` only moves a set that satisfies one of three conditions (loop.c:681-690).
  - Case (1) is `reg_in_basic_block_p`, which needs `regno_first_uid[reg] == this insn` (loop.c:1068). It fails,
    because `reg_scan` (regclass.c:1760) records the outer `size = 8` as the first reference.
  - Case (2) needs a non-user variable. `size` is a user variable.
  - Case (3) needs the set to be executed on every iteration. The set sits after the `j == 0` branch (`maybe_never`).
  So the set is not a movable, and the `.loop` dump lists none for it (`scratch/c29/dumps_s1`).
- cse1 folds the constant into the call argument (`li a3,8`, the same bytes). That leaves the outer set dead, and flow
  deletes it. At flow time `size` lives in one block and dies once, so it is a local-alloc qty (local-alloc.c:472).
  Its density beats the two x-coordinate temps, so it takes `$v0`, as in the target. This is the same end state c13
  reached through a dead initializer. Here the source statement is live.
- Control `scratch/c29/s0.c` (the same body without the outer use) scores 26: loop.c hoists the set, since
  `threshold*savings*lifetime = 58*1*2 = 116 >= 74 insns` (loop.c:1631).
- An equivalent spelling shares `size` with the mask test just before the loop instead:
  `size = 8; if ((m == i) && ((b[-2] & size) != 0))` (`scratch/c29/s2.c`, also 4).
- **Honesty note for the coordinator:** this is a named constant shared by two unrelated 8s (the call's x offset `dx`,
  and the sprite's w/h). It is not dead code and not a zero term, but its reason to exist is the loop.c decision. I
  count it as a variable reuse in the sense of c18/c11. Reject it if the phase reads it as steering.

## (b2) Problem 2, the pre-loop order: why it will not close without raising j's weight
Four facts, each read in the source and checked on dumps:
1. **sched1 rewrites the live lengths that global.c uses** (sched.c:4947, `reg_live_length = sched_reg_live_length`).
   The priorities therefore follow the OUTPUT order. `s1`: output t3v,k,j gives j 11/73 and k 11/74. `s1o`: output
   j,k,t3v gives j 11/75 and k 13/74. Whichever of j/k is emitted first lives one insn longer.
2. **In output order j,k,t3v, the pass order forces k to 13 refs.**
   - The three are independent leaves. `rank_for_schedule` (sched.c:2385) ties them by LUID, so the source order is
     the output order. The only exception is a producer with an in-block consumer, which `adjust_priority` /
     `birthing_insn_p` (sched.c:2507/2469) pulls up to just before that consumer.
   - So `t3v` comes after `k = m` in the source. cse then makes k the canonical register of m's class, because k lives
     past the block and its last use is later (`make_regs_eqv`, cse.c:826-862). That turns `t3v = m*4` into `k<<2`:
     +2 refs at depth 2.
   - The target's `sll t3,v1,2` does not contradict this. reorg rewrote it: `sll t3,a3,2` follows the copy
     `move a3,v1` directly, and reorg.c:3466-3488 substitutes the copy's source (the tree's `.dbr` dump shows the
     rewrite).
3. **j has 11 refs in any natural spelling:** `j = 0` (+2), the `j == 0` test (+3), and the increment's use and set
   (+3 +3).
   - The exit test reads the SImode increment temp, not j. cse folds the paradoxical `(subreg:SI j)` through
     `j = (subreg:HI tmp)` (cse.c:4842-4866).
   - A use of j in arm A is folded away before flow, because arm A knows `(sign_extend j) == 0` from the branch.
     Checked with `D_80115140[k] == j` (`v5.c`: still 11 refs).
   - A second `if (j != 0)` test is threaded away before flow (`e2.c`: still 11). `switch` changes the code
     (`e1.c` 29, `e1b.c` 35).
   - A duplicated increment-and-test tail (goto form, `g5.c`) does give j 17 refs. But cross-jump does not re-merge
     it, and everything shifts (55/267).
4. **`allocno_compare` (global.c:587-609)** then gives j `floor_log2(11)*11/75` = 4400 against k `3*13/74` = 5270.
   k is allocated first and takes `$a2`, the lowest free register. Pass 0 of `find_reg` does not help: every
   call-used register is in `regs_used_so_far` from the start (global.c:352-355), so pass 0 only restricts
   callee-saved registers.

   So j must be allocated first, which needs j ≥ 14 refs; the tree's `[L2]` keepalive is exactly +3. The alternative
   is to keep k off `$a2` another way.

**The second way, tried and 1 point short (`scratch/c29/f1c.c`, score 1):**
- (i) k becomes a function-scope variable that also carries the first call's fourth argument
  (`k = D_801917AC[a[3] & 7]; ot = func_80140D68(ot, &D_8019124C[i], i, k, 0);`). k is then live where `$a2` holds
  that call's third argument, so it conflicts with `$a2` and copy-prefers `$a3`. It gets `$a3` whatever its priority.
- On its own this scores 8 (`f1s.c`). `expand_preferences` (global.c:781) copies k's `$a3` preference to m, because
  m dies at the copy `k = m`. m is allocated first and loads straight into `$a3` (`lhu a3`, and the move disappears).
- (ii) `k = (u16) m;` keeps k out of m's cse class, so `t3v` reads m, m no longer dies at the copy, and nothing
  spreads. Order and all registers now match. The one remaining difference is `andi a3,v1,0xffff` where the target has
  `move a3,v1`.
- Nothing removes that `andi`. combine only simplifies an insn together with an in-block feeder through LOG_LINKS,
  and m is set in another block. cse does not track nonzero bits.
- Every spelling that yields a plain SImode copy puts k back into m's class. I tried a `u16` intermediate (`f1u.c`,
  8): cse folds `(subreg:HI m)` through m's `(zero_extend (mem:HI))` equivalence.
- Both (i) and (ii) are compiler-steering in spirit, and the result still does not match. **This is a reading, not a
  close.**

## (c) Moves in body.c (on top of c13's)
1. `size` is function-scope; `size = 8;` feeds the third call's fourth argument; c13's dead `s16 size = 0;` is deleted.
2. c13's order `t3v = m * 4; k = m; j = 0;` is kept, so the allocation is right and the 3-insn order is wrong (score 4).

## (d) Generator proposals
- **Hoisted constant (solved class):** when the target materialises a constant inside a loop and yours hoists it (an
  extra `li` before the loop, every temp after it shifted by one), give the constant a function-scope variable and use
  that variable as the source of an existing earlier use of the same literal (a call argument or a mask) above the loop.
  - loop.c's `regno_first_uid` test then fails on the in-loop set.
  - cse1 folds the earlier use back to the literal and flow deletes that set, so the in-loop set is still a one-block
    local.
  - Try every earlier occurrence of the literal. Report it as a shared-constant reuse, not as a plain spelling change.
- **Order-versus-allocation trade on independent preheader leaves (diagnostic):** before searching, compute which leaf
  the target emits first. If that register must also win `allocno_compare` against a partner with more refs, report
  the class "needs a ref-weight lever". The live length follows the output order (sched.c:4947), so no reordering can
  fix it. This saves the ~20-spelling search that c13 and I both ran.

## (e) What did not work (byte evidence, scratch/c29/)
`s0` 26 (no outer use: 8 hoisted) · `s3` 18 (`size = 8` in both arms: global allocno) · `n1` 70 (everything written in
the loop, as a natural sprite macro would: masks hoisted out of the outer loop) · `n2` 13 (`D_8011516A[m]` in the loop:
loop.c hoists the index to the preheader end, and cse2 canonicalises it to k) · `o1`/`s1o` 10 (tree order: j/k swap) ·
`e1`/`e1b` 29/35 (switch) · `e2`/`v5` 10 (extra j tests or uses folded before flow) · `f2`/`f3` 17 (k reused at the
second call too: the second call's temps shift) · `f1s` 8 (m coalesces into `$a3`) · `f1u` 8 · `f1c` 1 (`andi` for
`move`) · `g5` 55.

## (f) Where the method fell short
1. `--try` changed under me mid-run: it now compiles into a per-call directory and removes it. My first `t.sh` copied
   the stale shared scratch TU, and two of my dumps (`n2`/`o1`) were of the wrong candidate until I switched to
   `--keep`. A dump helper should take its TU from `--keep`'s printed path (the current `scratch/c29/t.sh` does).
2. Two model facts that the brief's tools do not surface cost the most time:
   - sched1 overwrites `reg_live_length`, so the alloc table's live column already reflects the output order.
   - `regs_used_so_far` starts with every call-used register.

   Both belong in the alloc_table header.
3. `expand_preferences` spreading a copy preference through a dying copy is invisible in `alloc_table.py`, because it
   prints the pre-spread `.greg` preferences. m showed "prefers a3" only in the `.greg` dump. A column for
   "preference inherited via copy" would have explained `f1s` immediately.

Paths: `body.c` (score 4), `mechanism.md` (this file). Candidates are in `scratch/c29/*.c` and dumps in
`scratch/c29/dumps_<tag>/`.

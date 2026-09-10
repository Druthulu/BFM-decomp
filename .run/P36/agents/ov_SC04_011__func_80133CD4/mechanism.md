# ov_SC04_011 / func_80133CD4: the `lh` instruction site (line 2705). CLOSED, score 0 (agent c26, S103)

The earlier agent's text is in `scratch/prev_mechanism.md` and `scratch/prev_body.c` (score 11, with a `do { } while (0)`).
This body scores **0** with no pin, no lever asm, no added volatile and no `do { } while (0)`. The GTE `__asm__ __volatile__`
block and the real `do { } while (ret < …)` loop were already in `body_free.c`. Verified on bytes:
`delever_search.py --try … body.c --body` gives `score 0 (OTHER; mine 399 ins, target 399) — MATCH`.

## (a) The residual in one sentence
The lever-free body lost one `lh` because cse forwarded the value just stored to `pb0[1]` into the later read. Once
that was fixed by store order, what was left was a three-way permutation (third quotient / second `lh` / `pb0[2]` sum
in v1/a1/v0 instead of a1/v0/v1). **local-alloc** decided that permutation, and the variable deciding it (`t`, reused
for all three `pc0[k] << 4`) is not in the differing instructions at all.

## (b) The passes and decisions (read from tools/reference/gcc-2.7.2, then proven on bytes)
1. **cse, the missing load.** `note_mem_written` (`cse.c:7539-7580`): a store whose address varies, and that is a PLUS or
   `MEM_IN_STRUCT_P`, only sets `nonscalar`. `invalidate_memory` (`cse.c:1701-1722`) then removes every entry at a varying
   address (`cse_rtx_addr_varies_p`), which covers every `pb0`-relative entry, and after that the store's own value is
   recorded. So the value a load gets forwarded from is whichever `pb0[k]` was stored LAST before it. With the three
   `+=` in source order and the three reads after them, `pb0[2]`'s store kills the entries for `pb0[0]` and `pb0[1]` (two
   real `lh`s), and `s2a` gets the forwarded `pb0[2]` sum (`sll s2,v1,16`). That is exactly the target. PROVEN: 399 ins.
2. **local-alloc, the permutation.** I simulated `block_alloc` (`local-alloc.c:1123`) for block 18: qty births and deaths
   at 2n, ties through `combine_regs` (output tied to a dying input, `qty_n_refs[sqty] += reg_n_refs[sreg]` at
   `local-alloc.c:1870`), the `qty_compare_1` order (`local-alloc.c:1598-1620`), and `find_free_reg` taking the
   lowest-numbered free register (MIPS has no `REG_ALLOC_ORDER`). The simulator is `scratch/c26/lsim.py` and it reproduces
   the dump's own `;; Register N in M.` lines with 0 mismatches on 5 dumps (tree, prior score-11, two-temp, n1, n3).
   With the natural order (n1, score 29):
   - `pb0[2]` load+sum qty (tied): 5 refs, 84..94, priority **10000**. It is ranked before the second `lh`
     (`hB`: 2 refs, 82..86, 5000) and takes **v0**.
   - So `hB` gets a0, `pb0` (9 refs, 52..90, 7105; nothing above it holds v1 in its range) gets **v1**, and the target's
     a0/v0/v1/a1 comes out as v1/a0/v0/a1.
   - The `pc0[0]` load (`lw` at 92, 2 refs, 5000) is what holds v0 in the target at that point. It cannot outrank the sum
     because its consumer `t = … << 4` writes `t`. `t` is reused for three values in three blocks, so it dies in 3 places
     and `local-alloc.c:472` (`reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1`) makes it a GLOBAL allocno. A tie needs a
     local destination, so none happens.
3. **The close.** Split `t` into `t0`/`t1`/`t2`. `t0` is set and used only in block 18 (sll, sw, bgez) and dies once,
   so it is local. `combine_regs` ties the `pc0[0]` load into it (the load dies in `t0 = … << 4`), giving a qty with 5
   refs over 92..100, priority **12500**. That qty now outranks the sum (10000) and takes v0 over 92..100. The sum's
   range 84..94 overlaps it, so the sum gets **v1**. That v1 blocks `pb0`, which falls to **a0**. `hB` (5000) finds v0
   free, and the third quotient (1666) is left with **a1**. The simulator predicted this before the compile, and the
   first `--try` of the joint edit returned 0.
4. **sched**: no change. The sched1 order of the region is identical in n1 and n3. The earlier agent read the lost `nop`
   as "two temps let sched1 hoist the second `lh`". That is REFUTED: sched1 already puts the `lh`s in the target order.
   sched2 filled the delay slot only because allocation gave the second `lh` a different register (v1). With the right
   allocation there is an anti-dependence on v0 and the `nop` stays.

## (c) The moves (a JOINT edit: each one alone scores worse)
1. The three `pb0[k] += s1var * pc0[k] / s0var;` in order, then `s1var = (s16)pb0[0] << 16; s0var = (s16)pb0[1] << 16;
   s2a = (s16)pb0[2] << 16;`. The `q3v` temp and the `h` block are gone. Alone: 29 (the instruction count is right and
   the registers are permuted).
2. `s32 t, o2;` becomes `s32 t0, t1, t2, o2;`, one name per value in the three `pc0[k] << 4` statements. Alone, on the
   free body: 35. Both together: **0**. Splitting only `t0` also scores 0. All three are split for uniformity.

## (d) GENERATOR PROPOSAL
**When the residual is a register permutation confined to one basic block, apply R23 (split a reused local into one name
per value) to EVERY local reused across blocks that is SET in that block or the next one, including locals whose
instructions are byte-identical in the diff.** Splitting one makes it block-local (`local-alloc.c:472`). A load feeding it
then ties into it (`local-alloc.c:1870`) and the tied qty climbs `qty_compare_1`, which re-orders who gets v0 for every
overlapping qty. The effect shows up at a distance, in instructions that do not mention the split variable. A tool can
rank the candidates without compiling: run `lsim.py` on the dump with the variable's pseudo marked local and read off
whether the target's registers appear.

## (e) What did NOT work, and which old claims are refuted
- n1 (natural order, one name for `t`): 29. o1 (reads interleaved with the `pb0[2]` update, quotient via `s2a`): 45,
  because it made another value global.
- Moving `s2a = … << 16` later in the source (n2): 29. sched1 puts it back at the same slot (load-latency fill), so
  C/sum's live range does not change.
- The earlier agent's "h cannot be set once" and "two temps lose the `nop`" are both wrong. The right answer is NO temp.
  The `nop` loss was sched2 reacting to a wrong allocation.
- Its `do { pb0[1] += …; } while (0)` (21 → 11) worked by doubling the second quotient's refs (flow.c:2067) so the
  quotient held v1 against `pb0`. It is not needed: the sum holding v1 does the same job in the target.

## (f) Where the method fell short
- `tools/alloc_table.py` prints per-PSEUDO priorities from flow's live length. local-alloc ranks per-QTY (tied pseudos
  summed) on block_alloc's own 2n numbering. For this function the table said pb0 16500 / 13500, while the decisive
  number is 7105 (9 refs over 38 half-insns). `lpri.py` handles block 0 only and has no ties. A validated block
  simulator (`scratch/c26/lsim.py`, ~250 lines) turned the search into arithmetic: I read off which qty had to outrank
  which, and the one variable that could do it was not in the residual hunks.
- The residual's hunk view shows only the permuted instructions. The deciding qty (`pc0[0]` load tied into `t0`)
  sits in byte-identical code four instructions later.

## Files
- `body.c`: the score-0 body.
- `scratch/c26/lsim.py <lreg> <fn> <uid-in-block> [from]`: local-alloc simulator (qty table, ties, simulated vs dump
  register, region order).
- `scratch/c26/{gen.py,q.sh,ev.sh,dump.sh}`: splice, score and dump helpers. `scratch/c26/n3.c` is the closing candidate;
  `abl_*.c` are the ablations.
- `scratch/prev_body.c`, `scratch/prev_mechanism.md`: the earlier agent's score-11 deliverables.

# func_80134A74 (ov_SC04_011) — mechanism

**Final score 0** (from 30; the mechanical search's best was 17). `mine 107 ins, target 107`. The candidate object's
words equal the tree object's word for word (`scratch/mine.words` vs `scratch/target.words`, `cmp` clean). I calibrated
the harness first: `body_tree.c` scores 0 through the same `--try`. The text is `PACK/body.c`. It has no register pin, no
`asm`, no `volatile` and no zero term (the free body's two `+ 0` terms are gone).

## (a) The residual in one sentence

It had two parts. First a COUNT gap: the lever-free body was **five instructions short**. cse had folded away three
register copies (`move t1,a1` = X kept whole, `move a0,v0` = Y kept whole, `move a0,v0` = the flag bit), the two
re-masks at the cell computation that go with them, and the counter's old-value copy (`move v0,sN`). Second, once the
count was right, a **callee-saved swap**: the list pointer took `$s2` and the counter `$s1`, where the target has the
list pointer in `$s1` and the counter in `$s2`.

## (b) The passes and decisions, `file:line`

1. **The copies (COUNT) are the same cse decision agent c4 read on the sibling func_80133AB0.** I did not re-derive them.
   The coordinator relayed them and the bytes agree. MIPS gcc 2.7.2 has no `PROMOTE_MODE` (`config/mips/mips.h:2622` is
   only a comment), so a `u16` local is a HImode pseudo. A copy into it is a SUBREG move, which the `(set REG0 REG1)`
   fold (`cse.c:7440-7474`, gate `:7455`) does not touch. Its later use expands as `zero_extend:SI`, which cse cannot
   match against the bounds test's `(and:SI x 65535)`. A `u16` post-decrement has no `addhi3`, so it goes through
   `expr.c:8645` `copy_to_reg`. Proved on bytes: `scratch/n2.c` (widths only) already shows all three copies and both
   re-masks.
2. **The swap is `global.c:596-610` `allocno_compare`**, with priority = `floor_log2(refs) * refs / live_length * 10000`.
   The references are weighted by loop depth (`flow.c:2067/2315/2501/2711`, `reg_n_refs[regno] += loop_depth`). I read
   it with `tools/alloc_table.py` on my own dumps (`scratch/dump.sh`, from the `--try` scratch TU):
   - before (`scratch/n4.c`, score 7): order `89 92 86 77 …`. The counter r86 has refs 11, live 42, so 3·11/42 =
     **7857**. The list pointer r88 has refs 7, live 38, so 2·7/38 = **3684**. The counter is allocated first and takes
     `$s1`.
   - after (`body.c`): order `89 92 88 86 …`. The list pointer r88 now has refs 11, live 39, so 3·11/39 = **8461**. The
     counter r86 has refs 11, live 43, so **7674**. The list pointer is allocated first and takes `$s1`, which is the
     target.

   The pointer's references rose from 7 to 11 because its decrement `lst--` is written in BOTH arms of the
   `if (hib == 0)`. Each in-loop set+use counts 2×2. The two copies still exist at global-alloc time: cross-jumping
   runs only in the last `jump_optimize (insns, 1, 1, 0)`, after reload and sched2 (`toplev.c:3139-3142`; the
   `cross_jump` arm is `jump.c:1923/1969`, `find_cross_jump` `jump.c:2371`). That pass merges the two identical tails
   into the single `addiu s1,s1,-2` at the join, so the extra reference changes the allocation and costs zero bytes.
   The dump confirms the allocation arithmetic; the bytes confirm the final merge.
3. **The layout** (the `return 1` block before the loop, reached by a backward `bnez`) needs no goto. With plain early
   returns and a `while` loop, loop.c's `find_and_verify_loops` moves the exit block out of the loop on its own
   (`scratch/n3.c` and later all show the target's `j`/`j` pair). I did not open `loop.c` for this, so it is inferred
   from bytes only.

## (c) The source moves (one line each), from `body_free.c`

1. Replace the goto layout with two early `return 0`s and `while (cnt-- != 0) { … if (call) { D_801EDA40 = *s0; return 1; } }`.
   `param_4` is typed as the TU's existing `Map_80133AB0 *` (same field offsets, same struct as sibling func_80133AB0).
2. Widths: `u16 Xc = X`, `u16 Yc = Y` (copies of the unmasked `u32` results; the bounds tests read `(u16)X` / `(u16)Y`),
   `u16 harg = hib` (the flag copy), and `u16 cnt` with `while (cnt-- != 0)`. These give the five missing instructions.
3. Hoist the five struct fields the loop reads (`p0C, p10, p18, p1C` before the cell computation, `p14` after it) into
   locals. Left as `map->…` they stay inside the loop because of the call (`scratch/n3.c`, score 60). Hoisted, the
   score is 7 (`scratch/n4.c`) and only the s1/s2 swap is left.
4. **Write `lst--` in each arm of the `if (hib == 0)` / `else`** instead of once after it. This takes 7 to **0**
   (`scratch/v_b.c`).

The following changes were checked and are byte-neutral: `(u16)X >= map->w` instead of `!((X & 0xffff) < map->w)`,
`(u16 *)(p14 + off) + cnt - 1` instead of `(u16 *)(p14 + off + cnt * 2) - 1`, and folding `cell` into
`k = (Yc * map->w + Xc) * 2`. `cp = &map->cells[k]` is NOT neutral (it scores 13), so the byte-address form stays.

## (d) Generator proposal

**R-dupe-tail (`delever.split_tail_ref`)**: when a REG-callee swap between two pseudos that both cross a call is left,
and `alloc_table` shows the loser's priority falling short because of a small `refs` (floor_log2 bucket), look for a
statement at the join point after an `if/else` inside the loop. Typically this is a pointer/counter step (`p--`, `p++`,
`i++`). Duplicate it into both arms. The loop-depth-weighted refs go up by 2·depth per copy, and the post-reload
cross-jump (`toplev.c:3142`) merges the copies back at zero byte cost. Predict first: the new priority is
`floor_log2(refs + 2·depth) · (refs + 2·depth) / live`. Try it only if that passes the rival. This is the reverse of a
cross-jump: the original programmer's duplicated tail is invisible in a decompiler's output, but it is visible to the
allocator.

## (e) What did not work (byte evidence)

- Declaring X and Y as `u16` and comparing those variables directly (`scratch/n1.c`, score 51) produces no copies:
  the compare and the later use are the same zero_extend, so cse shares the mask. The only difference between
  `scratch/n1.c` and `scratch/n2.c` is the split form (`u32 X; u16 Xc = X; if ((X & 0xffff) < …)`), and that split
  brings back both copies and both re-masks.
- Leaving the struct fields as `map->…` in the loop (`scratch/n3.c`) scored 60: the loads were not hoisted across the call.
- Changing the counter's shape instead of the pointer's: `u32 cnt; u16 rem; for (;;) { rem = cnt--; if (!rem) break; … }`
  (`scratch/v_c.c`) and `u16 cnt, rem` with the same loop (`scratch/v_d.c`) both stay at 7. Both leave the counter's
  priority above the pointer's.
- Declaration order was not tried. The priorities (7857 vs 3684) are distinct, so `global.c:604-610` never reaches
  its allocno-number tie-break.

## (f) Where the method fell short

- `tools/cc1_dumps_tu.sh` expects an `rtu_match` work directory, and its cpp line adds only the `t.c` directory to the
  include path. A TU with a relative `#include "../shared/…"` needs `-I<the TU's own directory>` instead. I wrote
  `scratch/dump.sh`, which dumps the `--try` scratch TU (`.run/P36/engine/score/<alias>__<fn>/`) directly. A `--dump`
  flag on `delever_search.py --try` would remove this step for every agent.
- `--try` writes its object to `.run/P36/engine/score/<alias>__<fn>/cand.o`. That path is not printed, so step 1 of
  METHOD_S103 ("dump your candidate's object") costs a search. Printing the path would save it.
- The single largest step (score 7 to 0) came from `alloc_table` arithmetic plus asking "what raises refs at zero byte
  cost". METHOD step 4 should name the loop-depth weighting of refs (`flow.c` `+= loop_depth`) and post-reload
  cross-jumping as the two free ways to move a priority.

Proved on bytes: every score quoted above and the final word equality. Proved on dumps: the before/after priorities and
the allocation order lines. Not re-proved by me: c4's cse and expr line numbers for the copies (relayed), and the
loop.c placement of the exit block.

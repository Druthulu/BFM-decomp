# func_80135888 (ov_SC04_011_jr_80135888.c) — score 0, all 5 NEEDED levers removed

Start 29 (COUNT, mine 110 / target 113). Mechanical best over 7 runs and 4,811+ compiles: 16.
**Final: 0 (byte-identical, 113/113).** Three source moves, each proven on bytes and each predicted from a dump
BEFORE it was compiled.

Levers removed: pins `$2` (m), `$17` (p1), `$19` (p0), `$21` (p3) and the `__asm__ __volatile__("")` barrier @683.
No `register`, no `asm`, no added `volatile`, no `__builtin_*` in the answer.

## (a) The residual in one sentence

Three instructions MISSING (the loop's entry test, which the target duplicates and mine reached by a `j` into the
loop's bottom test), a 3-cycle on the callee-saved bank (mine `p0=s1 p1=s2 mode=s3`, target `p1=s1 mode=s2 p0=s3`),
and the `p1 & 0x0FFFFFFF` result in `a0` instead of `v0` (pushing the `lui 0x8000` temp from `v1` to `v0`).

## (b) The passes and the decisions

**1. COUNT — `jump.c` cross-jump, run from `toplev.c:3142` (`jump_optimize(…, cross_jump=1, noop_moves=1)`).**
`while (sp)` is rotated to `goto test; loop: … test: if (sp) goto loop;`, so my `sp = *(s32 *)sp;` before the loop was
followed by a simple jump to the bottom test. `jump.c:1969` (`if (cross_jump && simplejump_p (insn))`) calls
`find_cross_jump (insn, JUMP_LABEL (insn), 1, …)` (`jump.c:1978`, body at `jump.c:2371`), which walks backwards from
the jump and from its label in lockstep; the `lw s0,0(s0)` in front of the jump matched the `lw s0,0(s0)` in front of
the label, so `do_cross_jump` (`jump.c:1998`) retargeted the jump *before* that load and deleted my copy — 3 fewer
instructions and no entry test. The `__asm__ __volatile__("")` in the tree was hired to break that backwards match.

**2. REG (the callee-saved 3-cycle) — `allocno_compare`, `global.c:585-611`.**
All six callee-saved values conflict pairwise, so the whole bank is decided by rank alone: rank *n* takes `$s(n-1)`.
Priority is `floor_log2(refs) * refs / live_length * 10000`, ties by allocno number (= declaration order,
`global.c:609-610`). The `.greg` table for the lever-free body (`tools/alloc_table.py`) read:

| allocno | var | refs | live | priority |
|---|---|---|---|---|
| r78 | p1 | 5 | 37 | 2702.7 |
| r79 | mode | 7 | 54 | 2592.6 |
| **r80** | **p0** | **8** | **76** | **3157.9** ← outranks both |
| r81 | base | 7 | 76 | 1842.1 |
| r82 | p3 | 5 | 73 | 1369.9 |

Order `76 77 87 **80 78 79** 81 82` → `p0=s1 p1=s2 mode=s3`. The target's order is plain declaration order, so p0 had
to fall below `mode`. `floor_log2` is the whole lever: **8 refs → 3, 7 refs → 2**, so dropping ONE reference from p0
divides its priority by 1.7. Note `reg_n_refs` is loop-depth weighted (`flow.c:2067/2315/2501`), and the second
`func_80136A94(mode, p0, p3, base)` sits inside the loop, i.e. it is worth 2 refs; the first copy of that same call
(before the loop) is worth 1. Deleting the duplicated call — writing `goto hit;` instead — takes exactly one ref off
p0, mode, p3 and base. Predicted new order: p1 > mode > p0 > base > p3. Measured on the c2 dump:
`;; 8 regs to allocate: 76 77 87 **78 79 80** 81 82`, priorities 2702.7 / 2264.2 / 1891.9 / 1666.7 / 1142.9 — the
prediction was exact, and the score went 22 → 6 with all three pairs closed.

**That rewrite is byte-neutral by itself.** `if (…) goto hit;` compiles to `bnez v0,<hit>`; `fill_simple_delay_slots`
steals the branch target's first insn into the delay slot and retargets the branch past it
(`reorg.c:3095-3135`, `reorg_redirect_jump (insn, new_label)` at `:3135`) — producing `bnez v0,0x100` /
`move a0,s2`, which is exactly what cross-jump had left of the duplicated call. So the move changes only `reg_n_refs`.

**3. REG (`m` in a0) — `local-alloc.c:470-477` + the `combine_regs` bail at `local-alloc.c:1774`.**
`m` is assigned in two switch arms, so `reg_n_deaths[m] == 2` and it fails the gate at `local-alloc.c:472`
(`reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1`): `reg_qty[m] = -1`, never a local quantity. `block_alloc` then
cannot tie the `and`'s destination to the dying `0x0FFFFFFF` pseudo, because `combine_regs` bails at
`local-alloc.c:1773-1774` — *"Can't combine if SREG is not a register we can allocate"*,
`(sreg >= FIRST_PSEUDO_REGISTER && reg_qty[sreg] == -1)`. `m` therefore fell through to `global.c` and took its copy
preference (`;; 76 preferences: 4 7` = `a0`, `a3`), leaving `v0` free for the `lui 0x8000` temp. Inlining the
expression gives each arm its own single-death, single-block temp, which `block_alloc` ties to the dying mask pseudo
in `v0`, so the `and` writes `v0` in place and `lui` first-fits `v1`. Proven: after the change the `.greg` order line
has only 7 allocnos and `m` is gone from it entirely (`76 88 77 78 79 80 81`, r76 is now `sp`). Score 6 → 0.

## (c) The moves (one line each)

1. `while (sp != 0) {…}` → `if (sp == 0) { return 0; } do {…} while (sp != 0);` — 29 → **22**, COUNT closed (113/113).
2. The duplicated `func_80136A94(mode, p0, p3, base); return 1;` before the loop → `goto hit;` — 22 → **6**.
3. `m = p1 & 0xFFFFFFF; sp = m | 0x80000000;` → `sp = (p1 & 0xFFFFFFF) | 0x80000000;` — 6 → **0**.

`PACK/body.c` is move 3 as written above. `PACK/scratch/c4.c` also scores 0 and keeps the name — it scopes the temp
instead (`{ s32 m = p1 & 0xFFFFFFF; sp = m | 0x80000000; }`); same mechanism, one brace-block per arm. Pick whichever
reads better in the tree; the inlined form is shipped because it is one line shorter and needs no synthetic block.

## (d) GENERATOR PROPOSALS

**G1 — `goto_merges` (the important one; a REF-COUNT lever that costs zero bytes).**
When the residual is register-only and the callee-saved colours are a permutation, find any statement block in the
body that is textually identical to another block which carries (or can be given) a label, and replace the duplicate
with `goto <label>;` — and the converse, re-expanding a `goto` back into the block it targets. Cross-jump and reorg
emit the same instructions either way, so this move can only change `reg_n_refs`, and one reference is often the whole
answer because `allocno_compare`'s `floor_log2(refs)` steps at every power of two. Rank the candidates by arithmetic,
not by search: for each variable the block reads, recompute `floor_log2(r∓w)*(r∓w)/live` (with `w = 2` inside a loop,
`1` outside) from `tools/alloc_table.py` and try only the rewrites that reorder the `.greg` line toward the target.

**G2 — `loop_entry_tests`.** When the count residual is `mine: j <into the loop>` against `target: <the loop's last
statement>; <exit test>` (mine short by the entry test), rewrite `stmt; while (c) {…}` as
`stmt; if (!c) { <the loop's else-exit> } do {…} while (c);`, which makes the entry block's tail differ from the
loop's tail so `find_cross_jump` (`jump.c:2371`) cannot merge them. This is the plain-C replacement for a
`__asm__ __volatile__("")` barrier sitting between a statement and a `while`, and it should be tried automatically
whenever a NEEDED barrier lever is in that position.

## (e) What did NOT work, and why

- Nothing was wasted on the paths the trace had already spent: `history.txt` shows R2 declaration-order and R4
  declaration-move candidates all flat at 20 across 4,811 compiles. The table says why, and the reason generalises:
  `allocno_compare` compares priority FIRST and only breaks ties by allocno number (`global.c:604-610`), so while p0's
  priority is strictly higher than mode's, **no permutation of declarations can reorder the bank**. A decl-order
  generator is provably dead on any REG residual whose allocnos have distinct priorities — worth a cheap pre-check in
  the engine before it spends a beam on them.
- `R6 inline m` alone (the trace's 20 → 16) is move 3 without moves 1 and 2: it fixes `a0→v0` but leaves the count and
  the 3-cycle, which is exactly the 16 the search plateaued at. The three moves are independent and additive here; the
  order I applied them in (count first, then rank, then tie) was also the order in which each next residual became
  readable.

## (f) Where the method fell short

- **`neighbours.txt` was empty** and the TU is a single-function `jr_` isolate, so step 0 had nothing to give. The
  substitute that worked was step 1 done properly: `objdump -drz` on BOTH objects (the tree's own
  `build/…_jr_80135888.o` for the target, and the `--try` scratch `cand.o`, which the tool leaves at
  `.run/P36/engine/score/<alias>__<fn>/cand.o` — worth documenting, it is the only way to see one's own whole
  function). The hunk view had scrambled the loop into two unrelated-looking edits; side by side it was one shape.
- **`tools/cc1_dumps_tu.sh` needs a directory trick that is not in its usage line.** It globs `$wd/*/t.c`, but these
  TUs `#include "../shared/engine_prelude.h"`, so `t.c` must sit at `$wd/<anything>/t.c` *with* `$wd/shared`
  symlinked to `src/shared`, or cpp emits 44 lines and the script's CPP-EMPTY guard fires with a misleading message
  about the include path. Two minutes lost; a one-line note in the script's header would remove it for everyone.
- Feeding it is easy and should be automatic: the spliced TU `--try` just compiled is sitting next to `cand.o`, so
  `--try --dumps` could produce the allocation table for the candidate in the same 0.3 s. Every one of the three moves
  above was chosen by reading that table and none by searching.

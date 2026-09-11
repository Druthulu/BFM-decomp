# func_80015608 (src/800.c) — e29, P36 S104 — SCORE 2 lever-free (from 50 free / 25 sweep); not closed

Best body: `body.c` (= scratch/b0/v1.c tidied). Residual: ONE register — `y0`'s `subu` and its `sll s8,…,16` use
`a0` where the target uses `a1` (2 instructions). Everything else (86 ins, frame 64, all callee-saved roles,
the loop, the constant handling) is byte-identical.

## (a)-(c) The moves that took 50 -> 2 (all byte-proven)
1. PORT THE SIBLING func_80015760 (e15's lever-free close, same TU, same four globals/callee): `len = 0x03000000`
   set in BOTH arms of the width if/else (two sets: no REG_EQUIV, `local-alloc.c:1016-1064`), `mask &= (u32)pkt;
   *ot = mask;` (mask set twice in the loop: not loop-invariant, `loop.c:705`), `tag = *ot & mask; tag |= len;`
   (no sched1 birth boost), `clut` as a loop variable, `u8 width = 8; if (flags & 0x80) width = 0x10;`. 50 -> 12.
2. ONE temp `h` REUSED for the two u16 field reads (`h = x-field; x0 = h - …; flags = …; h = y-field; y0 = h - …`),
   as the tree's `htmp` did. 12 -> 2. Without it sched2 hoists the `lhu D_800AF7BC` above the prologue stores; the
   reuse adds an anti/output dependence (38 -> 30/20 in `.sched`) that fixes the block-0 order. Proven: separate
   temps (`hx`/`hy`, b0/v7.c) = 12.

## (b) The remaining register: the mechanism (proven on dumps, scratch/dumps_v1 vs scratch/dumps_tree)
- global.c: `y0` (r77, 2 bytes) is allocated 13th of 14 (`alloc_table.py`: priority 1052). Its conflicts are
  `v0 v1` + the callee-saved allocnos; `a0` is free, so `find_reg` (global.c:904ff, no REG_ALLOC_ORDER on MIPS) takes
  the lowest free register, `a0`. No preference is involved (`prune_preferences`, global.c:829-880: the only
  lower-priority allocno, r111, does not conflict).
- In the TREE (pinned) compile, y0 (r84) conflicts HARD REG 4: sched1 emitted the flags `lbu 12(a0)` (insn 34, the
  last reader of arg0, local-allocated to `a0`) AFTER y0's `subu` (insn 48), so y0 is born while `a0` is live. Why:
  `.sched` (tree) — `ready list at T-3: 51 (7f000001) 48 (7f000001) …` picks insn 51, a single-set constant
  (`new_var = 0x03000000;` in block 0, boosted by `birthing_insn_p`/`adjust_priority`, sched.c:2468-2543, and later
  deleted by reload because it is REG_EQUIV and unallocated); at T-4 the flags load has become ready (it waits the
  load latency after the `and` at T-2) and wins the tie on hazard (`insn 34 has a greater potential hazard`), so the
  y0 `subu` goes to T-5 — before the load.
- In MY body there is no such extra birth: at T-3 the only candidates are y0's `subu` (priority 3, or boosted if y0
  is s32), the `width = 8` set (2 sets, not boosted) and the `str` load (multi-set) -> the `subu` is picked at T-3
  and lands AFTER the flags load -> no conflict with `a0` -> `a0`.
- The tree's birth only survives because its consumer is a HARD-REGISTER variable (`tagconst` pinned `$20`): with
  an ordinary `len` copy, cse1 (following the jumps across the width if/else) propagates the constant, the copy's
  destination becomes REG_EQUIV, is spilled and rematerialised inside the loop (`lui a2,0x300`, score 48 —
  scratch/L/t2.c, scratch/i/i2.c, i3.c); spelled into both arms (`len = hdr;`) cse deletes it (i1: 2).

## (d) GENERATOR PROPOSAL
For a residual where a block-0-born global value takes `a0`/`a1` one register low, compare the `.greg` conflict line
of the tree's pinned compile against the free compile: if the tree's allocno conflicts the hard register of the LAST
reader of a parameter and the free one does not, the difference is a sched1 order (a boosted single-set birth after
the value's definition, sched.c:2468-2543) — enumerate single-set births that reload can delete (a REG_EQUIV constant
whose only use is a copy into a register that is not REG_EQUIV) rather than register levers.

## (e) What did not work (byte evidence, all under scratch/)
- Statement orders of the block-0 reads (o/, 23 permutations; o2/, `ot` late): 2-18. Widths of flags/x0/y0 (w/, 15): all 2.
- `y0` born earlier: `y0 = field; y0 -= half;` (yy/, 16), y0 as the reused temp (r/r1: y0 does get `a1` but so do the
  field loads the target keeps in `v1`; 4), the parameter `arg1` reused for y0 (a/, 2).
- An extra single-set block-0 constant: `clut` (k/, 13-24: moving it out of the loop lets loop.c hoist the
  zero-extension of `width`, loop.c threshold), `rgb = 0x808080` (g/, 10-18: it gets a register, not spilled),
  `len` in block 0 (L/, 48), `hdr` feeding `len` (i/, 2/48).
- Anti-dependences through `h` for the flags read (F/): combine merges `h = lbu; flags = h;` into one set, 2.
- Width forms (ternary/if-else, u8/s32/u32/s16; tw/, 24): best 2.
- Levers tried as minimum-lever: `register s16 y0 asm("$5")` (pin/p1.c, 12 — a hard-reg destination changes sched1
  again), a marked `do {} while (0)` barrier around y0 or flags (ml1/ml2, 17-18), an asm keepalive of arg0 (ka*, 12),
  the tree's `register u32 len asm("$20")` + block-0 `hdr` (ml3/ml4, 4 — y0 fixed, `code` then takes `a0`).
  No single lever reached 0; the tree's own 4-lever body stays the banked text.

## (f) Where the method fell short
The sibling port (METHOD step 16 "related.txt covers MAIN") was decisive (50 -> 12). The last register needed the
TREE's own `.sched` trace, not the free one: comparing the pinned compile's conflict line (`84 conflicts … 4 …`)
against the free one is what named the missing sched1 birth — worth adding as a step ("dump the tree too").

## (g) Structs
An `Obj` struct for `arg0` (`x`@2, `y`@4, `str`@8, `flags`@0xC — the sibling's `Obj_80015760` with `value` = the
string pointer) would not change the decision: the residual is a sched1 birth/latency order in block 0 among four
loads of one base; field accesses give the same MEMs (the /s in-struct bit only matters against STORES in sched's
true_dependence, and block 0 has none). Tested indirectly: `((u8 *)arg0)[0xC]` / pointer-arithmetic spellings
(m/, all 2). A signature change to `Obj *` is blocked by the file-scope `extern void func_80015608(s32, s32);`.

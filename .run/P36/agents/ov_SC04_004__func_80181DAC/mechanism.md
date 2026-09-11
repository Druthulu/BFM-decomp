# func_80181DAC (ov_SC04_004_jr_8017AE2C.c) — d17, P36 T7 S104

**Result: score 0, plain C, zero levers.** It started at 16 (lever-free) with 2 levers in the tree: a `$0` pin and a keepalive.
The same text also closes the class's three other copies (table at the end).

## (a) The residual (16, COUNT 55 vs 57)
The residual had two separate defects, and neither one is a register lever at heart:
1. **arg0/count swapped between s2 and s3, and the b1fc/b239 reads went through `a0`.** The target is `lw v0,32(s2)` and
   mine was `lw v0,32(a0)`. cse rewrote the arms' `arg0 + 0x20` reads to use the hoisted copy `ca = arg0`, which is the
   pseudo that lands in `a0`. That took refs off arg0, and arg0 then lost its callee-saved slot to count.
2. **Two missing instructions at the return.** The target has `beqz v0,<after count++>` with `addiu s3,s3,1` in the
   delay slot, then `j epilogue; move v0,s0`. Mine had `bnez v0,epilogue; move v0,s0`. reorg took the `move` from the
   fall-through thread and inverted the branch around the jump.

## (b) The passes and decisions (read in tools/reference/gcc-2.7.2)
- Defect 1: `cse.c:846-862` `make_regs_eqv`. The new register (`ca`) becomes the class head when it lives past the cse
  block and its last use comes after the old register's (`arg0`'s last use is the b239 read; `ca`'s is the call, which
  sits in a later block). The cse path follows the jumps into b1fc and b239 (`cse_end_of_basic_block`: the label has one
  use and a barrier before it), so `canon_reg` rewrites those reads to `ca`. **Proved**: in the free body's `.rtl`, insn 36
  is `(set 75 72)`, and a1.c (no `ca`) fixes every register and scores 8.
- Defect 2: `reorg.c:1364-1372` `mostly_true_jump`. A branch whose target label is immediately followed by
  `NOTE_INSN_LOOP_VTOP` is predicted taken (returns 1). `fill_eager_delay_slots` (`reorg.c:3688-3700`) then fills from the
  **target** thread first and steals `count++`. The `j epilogue` keeps its backward-filled `move v0,s0`
  (`fill_simple_delay_slots`), and relax finds no branch-around-a-jump to invert. `NOTE_INSN_LOOP_VTOP` is only emitted by
  `duplicate_loop_exit_test` (`jump.c:2306`), which runs only on a rotated `for`/`while` loop, never on a `do-while`.
  A do-while's `next:` label is followed by `NOTE_INSN_LOOP_CONT`, the EQ test predicts not-taken (`reorg.c:1405`), the
  fall-through steal succeeds (`steal_delay_list_from_fallthrough`, `reorg.c:1699`), and the branch gets inverted. **Proved** from the
  `.jump2` dumps:
  - r12 (the `for` loop): `(code_label 145) (note NOTE_INSN_LOOP_VTOP)`.
  - a3 (the do-while): `(code_label "next") (note NOTE_INSN_LOOP_CONT)`.
  - r11 (the switch body with a do-while) keeps exactly this 6-point residual.
  - The tree's keepalive `asm volatile` got the same result another way: an asm insn stops the fall-through search
    (`stop_search_p`, `reorg.c:698`).
- Why a call per case costs 0 bytes: **post-reload cross-jump** (`toplev.c:3142` jump2, `find_cross_jump` `jump.c:2371`)
  merges the two call tails from the `a2 = zext(t)` insn down (`.jump2` label 198). That produces the target's single
  `jal` and b1fc's `j 7014`. Each arm's own `a0 = arg0` / `a1 = pe+4` copies stay at the arm heads (sched2), and reorg
  moves them into the dispatch branches' delay slots.

## (c) The moves that closed it (joint; each alone scores 6 or 8)
1. Delete the decompiler's hoisted argument copies `ca`/`cb` and the shared `call:` label. Write a `switch` on the
   state with one call per case: `if (func_80181E90(arg0, pe + 4, t) != 0) return pe; break;`. This fixes defect 1.
2. Rewrite `do { … goto next; … next: count++; pe += 0x10C; } while (count < 0x60)` as
   `for (count = 0; count < 0x60; count++, pe += 0x10C)` with `continue`. This fixes defect 2.
3. Delete the second walked pointer `ps = pe + 4` too, since loop.c's strength reduction rebuilds the `pe+4` giv in `s1`
   (r12 = 0). `t` has to stay a `u16` temp: r9, with `t` inlined into the argument, scores 19 because the HImode
   pseudo's `zero_extend` at the shared tail sets the cross-jump merge point.

Also at 0: r3/r5-r8/r10 (with or without `ca`/`cb` once it is a switch), v4/v5 (the goto body inside a `for`), and s1.c
(struct form).

## (d) Generator proposal
When a lever-free do-while's return path shows `bnez vX,<epilogue>; move v0,<ret>` where the target has
`beqz vX,<after the increment>; <increment>` followed by `j <epilogue>; move v0,<ret>`, and the tree needs a keepalive
asm before the `return`: rewrite `do { … goto next; … next: <incs>; } while (c);` as `for (; c; <incs>) { … continue; … }`
(VTOP prediction, `reorg.c:1364`). And when goto arms feed a shared `call:` label through copies hoisted before the
dispatch (`ca = arg0;` before the `==` tests, a `$0`-pinned `x + zr` in the tree), rewrite them as a `switch` with one
call per case and delete the copies: cross-jump re-merges the calls for free (`jump.c:2371`).

## (e) What did not work (byte evidence)
- a1 (a switch-like goto chain with a single call and no `ca`): 8. Registers right, the a0/a1 delay-slot hoists and the
  return missing.
- a2 (the argument computed straight into the call per case): 21. `t` lands in `a2`.
- a3 (the goto body with per-arm calls, in a do-while): 6. Only the return reorg is left.
- v1 (a positive test) and v2 (a `while` loop): 6. v3 (the `for` with `count = 0` in the init after `ps`): 4, prologue
  order only.
- r1/r2/r4 (structured if/else instead of a switch): 13. The if/else keeps a single shared-call shape that cse and reorg
  treat differently.
- r9 (`t` inlined as a `(u16)` argument): 19.

## (f) Where the method fell short
- Step 1's "count first" was right (55 vs 57), but neither missing instruction was an allocation question.
  `alloc_table.py` would have been a detour. The register swap was a consequence of cse's head choice, and the count gap
  was a reorg prediction. The METHOD list has no "reorg thread-choice" entry. Add one: *a delay slot filled from the other
  thread = `mostly_true_jump` (`reorg.c:1335`); a loop note (VTOP/LOOP_BEG) next to the target label flips it; a
  do-while has none*.
- The decompiler's goto spelling (a shared `call:` label, hoisted copies, a `+ zr` pin) hid a plain `switch`. No generator
  family reaches a switch from goto text (the same lesson as S104 d3/d9). The 16 from the free sweep was a structural
  ceiling, not a search failure.

## (g) The structs question
Structs were **not** the missing piece here. s1.c uses a body-local `Ent { u16 kind; u16 unk2; s16 pos[14]; Sub *sub
/*0x20*/; … }` (size 0x10C) and `Sub { u8 pad[0x18]; s16 v; }`, and scores **0**, byte-identical to the cast form.
Neither lever lived in an alias or scheduling decision, because the loop has no stores for `expr.c:4568`'s aggregate
channel to matter. Both lived in the control-flow shape (cse's copy head, reorg's loop-note prediction). A struct type for
`D_801202A0` (the 0x10C-byte entity table: `+0` kind, `+4` position, `+0x20` pointer to a sub-object with `s16` at
`+0x18`) is still the right long-term spelling and is byte-neutral.

## Copies of this class (the same text; each `--try` = 0)
| function | TU | file |
|---|---|---|
| func_80181DAC | src/ov_SC04_004/ov_SC04_004_jr_8017AE2C.c | PACK/body.c (= scratch/copies/func_80181DAC_cast.c) |
| func_801872E0 | src/ov_SC04_005/ov_SC04_005_jr_8017BEBC.c | PACK/scratch/copies/func_801872E0.c (callee func_801873C4, prototyped) |
| func_80180D50 | src/ov_SC04_003/ov_SC04_003_jr_8017BEBC.c | PACK/scratch/copies/func_80180D50.c (keeps the tree's cast call `((s32 (*)(s16 *, s16 *, s32))func_80180E34)`) |
| func_80183820 | src/ov_SC04_002/ov_SC04_002_jr_8017BEBC.c | PACK/scratch/copies/func_80183820.c (callee func_80183904) |

That is 4 bodies and 8 levers removed.

## func_80181D1C (the neighbouring class, 4 copies): NOT closed by this mechanism
Its best lever-free text is PACK/scratch/d1c.c, at 15 (COUNT 34 vs 36). Two defects, both different from DAC's:
- **The early `return 0`** has the same reorg symptom (fall-through steal and inversion; the tree fixes it with
  `asm volatile("")`), but there is no loop, so the VTOP prediction cannot apply. It would need `mostly_true_jump` > 0
  through rarity (`reorg.c:1375-1390`) or an own-fallthrough failure (a live label after the branch). No plain-C shape
  was found.
- **The return value lives in the hard register v0 across the `x < t` test**, and the call result `r` is copied to `v1`
  (`move v1,v0`). The tree pins `rr`→$3 and `z`→$2. Local-alloc gives the block-local `r` its `v0` suggestion before
  global runs (`local-alloc.c:1797+`, qty_phys_sugg), and every `ret` variable shape tried (d1-d11) ends up with `ret` in
  `v1` and a final `move v0,v1`. The target behaves as if `(set (reg:SI 2) 0)` were already live (a hard-register
  return-value store hoisted before the test). jump.c's if-conversion (`jump.c:700-830`, allowed on MIPS hard registers)
  is the only pass seen that does that, and its single-insn arm shape does not fit this body.
Candidates for the STRUCTS phase or a dedicated agent.

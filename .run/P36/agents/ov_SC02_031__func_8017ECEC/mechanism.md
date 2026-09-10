# func_8017ECEC (ov_SC02_031, 11 copies) — T7 agent c34 (S103)

**Result: score 0, lever-free.** No register pin, no asm, no added volatile, no do-while, no invented term, no dead
assignment. Whole-object check on the `--try --keep` object: `objdump -drz` of the ENTIRE `.o` is identical to
`.run/P36/delever/baseline/src/ov_SC02_031/ov_SC02_031_jr_8017AE2C.o`, and `.text`/`.data`/`.rodata` compare equal
(`cmp`). Candidates are in `scratch/v/` (`a*.c` … `d*.c`), dumps in `scratch/dumps_{free,a1,d2}/`.

```c
    u32 xz;
    func_8012B0B4(&xz, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), a1 << 4);
    *(s32 *)(a0 + 0x10) = (s16)xz << 12;
    *(s32 *)(a0 + 0x18) = ((s32)xz >> 16) << 12;
```

## (a) The residual in one sentence

A pure `$v0 <-> $v1` swap between the low-half chain (`lh; sll 12; sw 0x10`) and the high-half chain
(`lw; sra 16; sll 12; sw 0x18`) — every instruction and the order were already right (count 29 = 29).

## (b) The pass and the decision (all PROVEN on dumps + bytes)

* local-alloc ranks the block's quantities by `qty_compare_1` (local-alloc.c:1598-1616,
  `floor_log2(refs)*refs/(death-birth)`). `tools/localalloc_sim.py` on the lever-free dump (0 mismatches):
  lo chain q3 = r78+r88, 4 refs, life 18..24 -> **13333**; hi chain q4 = r77+r89+r90, 6 refs, life 20..30 -> **12000**.
  lo ranks first and takes `$v0`: the mirror image of the target. (Exactly what the tree's header comment computed.)
* With the packed-word spelling `(s16)xz`, expand emits the sign extension of a NON-MEM operand through mips.md's
  `extendhisi2` expander (config/mips/mips.md:2340-2356): `t = xz_word << 16; lo = t >> 16`. combine then does a
  THREE-insn combine (i1 = the SImode word load, i2 = the `<< 16`, i3 = the `>> 16`) into
  `(sign_extend:SI (mem:HI))` = the target's `lh`; since the word load is still live (the `>> 16` of the high half
  reads it), the result is a PARALLEL of two SETs that combine SPLITS back into two insns (combine.c:1994-2020).
  Because `newi2pat != 0`, the bookkeeping that would zero the dead i2 pseudo's counts is skipped
  (combine.c:2306 `if (! added_sets_2 && newi2pat == 0 ...)`; the file's own caveat at combine.c:55-57: "reg_n_refs is
  not adjusted in the rare case when a register is no longer required"). Two stale counts result:
  1. the word-load pseudo keeps the ref of the deleted `<< 16` insn: `Register 85 used 3 times` (really 2). The hi
     chain becomes 7 refs, `2*7/10` = **14000 > 13333** -> it ranks first and takes `$v0`, lo gets `$v1`
     (`localalloc_sim.py scratch/dumps_d2/d2.i.lreg func_8017ECEC 34`: q4 14000 v0, q3 13333 v1, 0 mismatches).
  2. the deleted `<< 16` pseudo keeps `used 2 times … dies in 0 places; ST_REGS or none` (no insn left, so regclass
     prefers ST_REGS), gets no hard register, and reload's `alter_reg` gives it a stack slot because
     `reg_n_refs > 0` (reload1.c:2331-2334) -> **+8 bytes of frame** (`vars= 24` with the tree's `u32 buf[4]`).
* So the tree's `u32 buf[4]` was a compensating frame pad (its header comment: "16 bytes of locals — NOT the 8-byte
  scratch the sibling callers use"). With the packed-word spelling the 4-byte `xz` + the phantom 4-byte slot give
  exactly the target's `vars= 16`, frame 48.

## (c) The source moves that closed it

1. **Read the helper's packed u32 once and take the low half with a `(s16)` cast** (the TU header already says
   func_8012B0B4 "writes ONE packed u32 (lo half = x, hi half = z)"): `a1.c` = score 8, but every body instruction and
   register identical to the target; only the frame is 56 vs 48.
2. **Drop the fake 16-byte buffer** for the one `u32` the helper writes: 0 (`d2.c` = `body.c`). `u32 buf[2]`/`buf[1]`
   with `t = buf[0]` (d1/d3) and `s32 v` with `(u32 *)&v` (d4) are also 0; `body.c` takes the prototype's own type.

## (d) GENERATOR PROPOSAL

When two halves of one stack word are read as `*(s16 *)buf` and `*(s32 *)buf >> 16` and the residual is a register
swap between the two chains (or the frame is too big/small by 8), rewrite them as ONE `u32` word read with the low
half as `(s16)w` and the high half as `(s32)w >> 16` — combine's 3-insn split (combine.c:1994/2306) leaves a stale
ref on the word pseudo (+1 priority weight) and a phantom 4-byte stack slot — then re-size the buffer so
`vars` matches the target frame (`.frame` line of the dump).

## (e) What did not work (byte evidence)

* `a2.c` (swap the two loads' statement order): 8, identical to the start — sched1 normalises it.
* `a3.c` (both reads inlined into the stores): 10, 28 ins — combine narrows `(mem:SI) >> 16` into `lh 18(sp)`.
* `b1.c` (compute both values into temps, then store): 7, 28 ins — same narrowing, the store no longer sits between
  the word load and its shift (`use_crosses_set_p`'s mem rule, as the tree's header says).
* `b2.c` (`lo <<= 12; hi = (hi >> 16) << 12;` then both stores): 2 — registers RIGHT (lo's life now spans the hi
  chain, 8000 vs hi's), but the high half collapses to `lh 18(sp)` (28 ins). A register fix bought with a count loss.
* `a1.c`, `c1-c4.c` (packed-word spelling with `u32 buf[4]`): 8, all body bytes right, frame 56 — the phantom slot.

## (f) Where the method fell short

* The residual reads as a register permutation; the fix was an EXPRESSION move whose side effect in combine is
  a stale ref count. Neither `alloc_table.py` nor `localalloc_sim.py` can predict a stale count before the
  spelling exists — the sim only confirmed it afterwards. The deciding clue was the TU's own header sentence
  ("ONE packed u32"), i.e. read the callee's contract and spell its natural consumer.
* The `--try` score line calls a frame-only difference `OTHER`: worth a note in the tool that "OTHER with only the
  prologue/epilogue differing" = frame size, so an agent looks at `vars=` in the `.frame` line immediately.
* A frame delta of exactly 8 after an expression change = a phantom stack slot from a combine-deleted pseudo with a
  stale `reg_n_refs` (look for `dies in 0 places; ST_REGS or none` in `.lreg`). Worth a cookbook line: a fixed-size
  dummy buffer in a tree body may be compensating for exactly this.

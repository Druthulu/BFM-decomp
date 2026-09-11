# func_80181234 (C name aF8017ED80) — agent c53 (S103) — CLOSED, score 0, no lever

## (a) Residual
Score 18, 117 vs 117, in both halves: the `bgez` delay slot holds `lui v1,0x7fff` (stolen from the `&`-arm, the
branch target) where the target holds `lui v1,0x8000`; the `|`-arm's load/constant registers are also swapped
(loaded value in `$v1`, constant in `$v0`). The same instructions in a different order and a different fill.

## (b) Mechanism (pass + decision), read from dumps of the tree, the free body and the close
- The tree's `__asm__ volatile("")` at the head of the else-arm is a `stop_search_p` insn (`reorg.c`, ASM_INPUT), so
  `fill_eager_delay_slots` cannot take anything from the target thread and falls back to the fall-through. In plain C the
  branch is `(ge x 0)`, which `mostly_true_jump` predicts TAKEN (`reorg.c`, the `GE ... const0_rtx → 1` case;
  `rare_destination` of a CODE_LABEL is always 0, so nothing else can flip it), and `fill_slots_from_thread` takes the
  else-arm's `lui v1,0x7fff` (v1 is set before use on the fall-through, so `mark_target_live_regs` does not report it
  needed there). No plain-C rewrite of the arms changes this (the per-arm `|=`/`&=` form fixed the registers, score 8,
  but not the fill).
- **The original tested the sign bit as a MASK: `if (flags & 0x80000000)`.** Expand loads `0x80000000` into a pseudo
  BEFORE the branch for the `and`; cse gives the `|`-arm's `ior` the same pseudo; combine turns `(and x K) != 0` into
  `(ge x 0)` (the `bgez`), but the constant's set stays before the branch because the `|`-arm still reads it
  (`.jump2`: insn 89 `v1 = -2147483648` precedes the `bgez`; the `ior` reads `v1` without setting it).
  `fill_simple_delay_slots` (`reorg.c:2799`, the backward scan from the branch) moves that `lui v1,0x8000` into the
  slot, and the else-arm's `lui v1,0x7fff` can no longer be stolen because the fall-through now NEEDS `v1`. With the
  constant already in `v1`, the loaded value takes `v0` — the pin was compensating for the same missing constant.
- **The frame, too.** The tree carried `s32 pad_[4];` (a dead local) to reach the target's 16-byte frame. With the mask
  test, the two `and` results (pseudos 96 and 123) are folded into the jumps by combine but keep their ref counts
  (`.lreg`: `Register 96 used 2 times across 29 insns in block 1; ST_REGS or none`, same for 123 — combine.c:2303-2312
  zeroes `reg_n_refs` only on the i2-died-in-i3 path), get no hard register, and reload gives each a stack slot
  (`reload1.c:2331-2335`, `alter_reg`: `reg_renumber < 0 && reg_n_refs > 0`); the `.s` header reads `vars= 16`. That
  is the target's frame, so `pad_` must go (with `pad_` kept the frame is 32, score 2). Two independent byte facts —
  the delay slot and the frame — both fall out of the one mask test, which is strong evidence it is the original.

Proven on bytes: the close (0); the mask test with the join store `uVar1` (0) and even with the tree's `val` temp (0) —
the arm spelling is free once the test is a mask; mask test with `pad_` kept (2, frame only); per-arm `|=`/`&=` with the
`< 0` test (8, fill only). Proven in dumps: the constant's position before the branch, the ST_REGS-or-none pseudos,
`vars= 16`. Not proven: which exact combine sub-path leaves the refs (hypothesis: the i1/i3 path).

## (c) The moves
1. `if (*(s32 *)(... + 0x4) < 0)` → `if (*(u32 *)(*(s32 *)(a0 + 0x20) + 0x4) & 0x80000000)` (both halves).
2. Delete `s32 pad_[4];` (dead local that faked the frame).
3. (readability, not needed for bytes) the arms as `*(u32 *)(iVar2 + 0x4) |= 0x80000000;` /
   `&= 0x7FFFFFFF;`, dropping `val` and `uVar1`.

## (d) Generator proposal
When a delay-slot fill differs between the arms of a sign test (`bgez`/`bltz`) and the taken arm ORs or ANDs the same
bit-31 constant, rewrite the test `x < 0` / `x >= 0` as `x & 0x80000000` (or `!(x & 0x80000000)`) so the constant is
materialised before the branch; and when a body carries a dead `pad_[N]` local, re-score with it deleted after every
condition rewrite — folded test pseudos can supply the frame the pad was faking.

## (e) What did not work
- per-arm `|=`/`&=` (`u32` or `s32`) with the `< 0` test: 8 (registers right, fill wrong);
- join store `uVar1 = ... | 0x80000000` without the `val` temp, `< 0` test: 18; the inverted `>= 0` test with
  per-arm `&=`/`|=`: 18.

## (f) Method notes
The residual reads as a scheduling/delay-slot difference; reading `mostly_true_jump` + `fill_slots_from_thread` proved
no arm rewrite could fix it, which pointed at "the constant must already be live before the branch" — the question
"what C puts a 0x80000000 before a sign branch?" answered itself. The `pad_[4]` is a lever the census does not count
(no `// !FAKE:` mark); it should be flagged wherever a frame-only pad sits next to a removed lever.

# func_8017FA18 (ov_SC03_001_jr_8017AE2C.c): T7 agent c55

**Result: score 0, byte-identical (107/107 insns). No pin, no asm, no volatile, no zero term.** `body.c` = scratch/n9.c
(a `switch`). Nothing outside the body changed. Both pins ($16 on iVar4, $3 on iVar3) are gone. The minimal edit of
`body_free.c` (scratch/f1.c, same goto skeleton) also scores 0, using the same two moves.

## (a) The residual in one sentence
Two independent defects. (1) The parameter and the case-0 random speed have swapped callee-saved registers (param s0 /
speed s1, where the target has s1 / s0). (2) In case 1 and case 3, the running sum `e4 + e0` lands in `a1` instead of
`v1`. Because of (2), case 3 never writes `a0` before `move a0,param`, so reorg steals that move into the dispatch
branch's delay slot and inverts the branch (`bne ...end; move a0,s0; j case3`). That makes the function one
instruction short (106 vs 107), and every later jump is off by 4.

## (b) The passes and decisions (proved on bytes and dumps)
1. **Callee-saved swap: global-alloc priority** (`allocno_compare`, `global.c:587`:
   `floor_log2(refs)*refs/live*10000`). The parameter pseudo has 40 refs over a live length of 83-84, pri 24096/23809.
   With `speed = (rand() & 0x3fff) + 0x7800` (or `speed = rand(); speed = (speed & K) + C`), speed has 6 refs, live 6-7,
   pri 17142-20000. It loses, takes the second callee-saved register, and gets s1.
   With `speed = rand(); speed &= 0x3fff; speed += 0x7800;`, flow counts 8 refs (`flow.c:2067`: each set and use counts,
   and combine later folds the copy into the `andi`, so it costs no instruction). That gives
   floor_log2(8)=3, 3*8/8 = **30000**. Speed now outranks the parameter and gets s0. The bytes are unchanged:
   `andi s0,v0,0x3fff` / `addiu s0,s0,30720`. alloc_table n9 vs n8 shows the order line flip from `72 75` to `73 72`.
2. **`a1` instead of `v1`: one name shared across two switch arms** (`local-alloc.c:472`). A single `iVar3`/`step` used
   in both case 1 and case 3 dies in 2 places. It becomes a global allocno (alloc_table n2: r73 `dies in 2 places`,
   conflicts v0,v1,a0), so it is assigned after the locals and gets a1. One name per arm makes each a local quantity,
   and local-alloc gives it v1. The 0x20 pointer then gets a1 and `e0` gets a0, as in the target. With `a0` written early
   in case 3, the stolen `move a0,param` is blocked in reorg's `fill_slots_from_thread` (`reorg.c:3257`; a thread insn
   cannot move over an earlier set of its destination). The dispatch returns to `beq v1,v0,case3; nop; j end`, and the
   count to 107.
   Byte proof that the two defects are independent:
   - n5 (per-arm names only) = 47, residual `s0->s1 x37, s1->s0 x6` only.
   - n3 (speed split only) = 24, the step registers plus the 106 count only.
   - n4, n6, n7, n9 (both moves) = 0.
3. The dispatch (`beq 1; slti 2; beqz 0; ...; beq 2; beq 3`) is gcc's balanced decision tree for a 4-case `switch` on
   `*(u16 *)(p + 0x34)`. The tree's `if`-chain was a transliteration of it, and `switch` reproduces it exactly (n1 onward).

## (c) The source moves
- `switch (*(u16 *)(param_1 + 0x34))` with four arms, each ending in `break` or an early `return` after the
  `func_8012BEE8` test.
- Case 0: `speed = rand(); speed &= 0x3fff; speed += 0x7800; if ((rand() & 1) == 0) speed = -speed;`
- Case 1 and case 3: separate names (`step1`, `step3`), each `= e4 + e0` in one expression. The two-statement form
  `step = e4; step += e0` also scores 0, so only the separate names matter.

## (d) Generator proposal
When a callee-saved swap puts a short-lived computed local behind the parameter, and the local's
`floor_log2(refs)*refs/live` is just under the parameter's, re-spell the local's computation as successive in-place
updates starting from the call result (`x = call(); x op= K1; x op= K2;`). This raises refs by 2 per step at zero byte
cost, and it crosses the floor_log2 step at 8. Pair it with R23 for any temp name shared by two `switch`/`goto` arms,
and whenever the residual is a 1-instruction COUNT gap at a dispatch branch that reorg filled from a case body, check
that arm's temps first.

## (e) What did not work (byte evidence)
- n1 (switch, shared `step`, `speed = (rand() & 0x3fff) + 0x7800`): 53.
- n2 (+ `step = e4; step += e0`, shared): 62, back to 106 insns.
- n8 (`speed = rand(); speed = (speed & K) + C`): 47. 6 refs is not enough; the in-place `&=` is what adds the refs.
- History's width moves (iVar3 -> u16, iVar4 -> s16, best 18) are not needed.

## (f) Where the method fell short
- The c42 hint (cross-jump label placement in func_80182058) did not apply here. The case1/case3 tails are merged
  identically in mine and the target.
- A COUNT residual (106 vs 107) was really a register residual one step removed: a register choice in case 3 decided
  whether reorg could steal an insn into the dispatch. METHOD step 2 ("count first") would have sent a searcher looking
  for a missing instruction. Checking which instruction moved into which delay slot (the full objdump, mine vs target)
  named it in one read.
- Proved: all of (b)1-2 on bytes and alloc_table dumps. Not proved: the exact reorg.c line that refuses the steal. The
  mechanism is inferred from the two objdumps (a0 is written in the target's case 3 and not in mine).

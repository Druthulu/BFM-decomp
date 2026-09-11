# func_801861FC (ov_SC03_091_jr_8018326C.c) — P36 S104 agent d22

**Result: score 0 in plain C, zero levers** (was 1 NEEDED lever: `register s32 t __asm__("$2")`). Levers 1 → 0.
Closed on the FIRST `--try`. Best body: `PACK/body.c` (76/76 ins, MATCH). It also closes the class's three other copies
(`scratch/copies.md`): func_80185678 (ov_SC03_089), func_80185354 (ov_SC03_090), func_801831E8 (ov_SC03_104) — all 0.

## (a) The residual
Counted first: mine 77, target 76 — ONE extra instruction, `move a0,v0` after the case-0 `jal func_8004787C`; the target
computes `t*7` (`sll v1,v0,3; subu v1,v1,v0`) and `t<<1` straight out of `$v0`. Every other hunk is a branch offset
shifted by that one instruction. So: a call-result copy that should have been tied to `$2` and was not.

## (b) The pass and the decision (read in the dumps, proven on bytes)
The lever-free body reuses ONE `t` for the call result in case 0 and in case 2 — two basic blocks. flow marks it
`REG_BLOCK_GLOBAL` (`flow.c:2058-2061`, the second block that sets it), so local-alloc never sees it (block_alloc takes only
pseudos local to the block) and cannot tie it to the dying `$2` with `combine_regs` (`local-alloc.c:1722`). Local-alloc
first gives case 0's block-local temps (`t<<3`, the `ent+0x20` loads) `$2`/`$3`; global allocation then records those hard
registers as conflicts of `t` (`global.c:1428` via the locals' `reg_renumber`) — `.greg`, free body:
`;; 77 conflicts: 73 76 77 2 3 29` — so `find_reg` (`global.c:904`) hands `t` `$4` and the copy `move a0,v0` survives.
With one `t` per case, case 0's `t` is local to block 6 (`.lreg`: "Register 78 used 4 times across 7 insns in block 6",
"Register 78 in 2.") and is tied to `$2`; the copy becomes `move v0,v0` and is deleted. Dumps:
`scratch/dumps_free/free.i.{lreg,greg}` vs `scratch/dumps_body/body.i.{lreg,greg}`.

## (c) The move that closed it
One name per value for the call result: the case-2 `t` is either inlined into its single use
(`*(s16 *)(sub + 0x1A) = func_8004787C(...) << 1;`, the shipped body) or declared in its own case block. Byte-proven
equivalent spellings, all 0: `{ s32 t = …; }` inside BOTH cases (`scratch/c1.c`); two function-scope names `t`, `t2`
(`scratch/vA.c`); only case 0 block-scoped (`vB.c`); only case 2 block-scoped (`vC.c`). The shipped body also drops the
decompiler's `ent = a0` / `state` / `sub` temps (readability; they were not the defect — r2 = 0).

## (d) Generator proposal
R23 (split a reused local) already covers this move but REFUSED `t`: its definition test requires the text before
`v = E;` to end in `;`/`{`/`}` (`tools/delever.py` `split_reused_locals`, the `before.endswith((";", "{", "}"))` check),
and case 2's `t = func_8004787C(...)` follows `case 2:` — so the sweep split `sub` and `cnt` (free_115/116, best 9) but
never `t`. Rule: **accept a `case K:` / `default:` label (a `:` that closes a case label) as a statement boundary in R23**
— the definition is the first statement of the case, so every later use in that segment is dominated by it whether the
case is entered by dispatch or by fall-through. Also offer "declare the value inside the case's own `{ }`" as the R23
spelling when the segments are switch cases (d7's per-arm local).

## (e) What did not work (byte evidence)
- `scratch/r1.c` (case-2 call inlined but `sub = *(s32 *)(ent + 0x20);` left ABOVE the call): wrong — `sub` then lives across
  the call and takes `$s1` (frame 32, +1 callee-saved). The `ent+0x20` load must stay after the call, as in the target.
- The history's 9–12 candidates: they split/inlined `sub`/`cnt` and swapped statements — none separated the two `t`s.
- Struct accesses with the reused `t` (`scratch/st_reused.c`): 15, unchanged.

## (f) Where the method fell short
Nothing structural — count (1 extra `move`) → "a call-result copy not tied to `$2`" → the only non-local pseudo in the
case → the `.greg` conflict line. This is the S103 c1/c8 "local reused across statement groups → one name per value" move;
the sweep's generator for it had a text-shape gap at a `case` label, not a compiler-model gap. The pin was faking exactly
the `$2` tie that a block-local pseudo gets for free.

## (g) Structs question
Neutral. Tested on bytes with body-local `struct Ent { u8 pad0[0x1C]; s32 timer; struct Sub *sub; u8 pad24[0x10]; u16 state; }`
/ `struct Sub { u8 pad0[0x18]; s16 sx; s16 sy; }` and `e->state++`: reused `t` = 15 (`scratch/st_reused.c`), split `t` = 0
(`scratch/st_split.c`). The decision is flow's block-global marking of one pseudo set in two cases; aggregate vs scalar
MEM flags (`expr.c:4568-4577`) never enter it. The struct would read better (timer +0x1C, sub-object +0x20 with s16 +0x18/+0x1A,
state u16 +0x34) but does not close the bytes.

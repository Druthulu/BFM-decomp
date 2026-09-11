# func_80189A84 (ov_SC03_006_jr_8017AE2C.c) — e6, P36 T7 S104

**Result: score 0, ZERO levers** (2 levers before → 0 after: pin `$2`, pin `$3`). Closed on the FIRST `--try`.
Body: `PACK/body.c` (= `scratch/a2.c`): the decompiler's two reused temps `v0`/`v1` deleted, every read written in place.

## (a) The residual, in one sentence
The free body's `v0` (one variable carrying the 0xDC flags, the 0x1C counter twice and the 0x20 pointer) came out in
`$v1` instead of `$v0` (score 30); the COUNT-looking tail is a knock-on — with the counter left in `$v1` past `slti v0`,
reorg's `redundant_insn` deletes the skip path's reload of `28(s0)` and threads the branch past it (mine `bnez → ecb4`,
target `bnez → eca8`, which reloads).

## (b) The pass and the decision (read in `scratch/dumps_free/free.i.lreg`, proven on bytes)
- `.lreg`: `Register 73 used 11 times across 13 insns; dies in 5 places` = the `v0` variable; it spans blocks 0–4, so
  `local-alloc.c:472` (`reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1`) refuses it and it goes to global-alloc.
- Local-alloc runs first and gives every block-local quantity `$2` — including reg 81, the `lui 0x8000` mask in block 4
  (`;; Register 81 in 2.`), which is live while `v0` holds the `0x20` pointer. Global-alloc's conflict set for reg 73 then
  contains hard reg `$2` (`global.c:1256/1291`, `record_conflicts`), so `find_reg` gives it `$3`, and `v1` (reg 74) `$4`.
- In the target every value is its own one-block, one-death pseudo: local-alloc ties each load to its `andi`/`slti` result
  in `$2`, the mask goes to `$a0`, the pointer to `$v0`, the xor value to `$v1`.

## (c) The moves
- Delete the reused `v0`/`v1`; write the reads in place: `if ((*(s32 *)(a0 + 0xDC) & 2) != 0) { if (*(s32 *)(a0 + 0x1C) >= 0x15) { s32 p = …; *(s16 *)(p + 0x10) = *(u16 *)(p + 0x10) - 0x28; } }`
  and `if (*(s32 *)(a0 + 0x1C) < 0x11) *(s32 *)(*(s32 *)(a0 + 0x20) + 4) ^= 0x80000000;` → 0.
- Probes (all `scratch/`): only the SECOND if-block rewritten (a fresh block-local `ptr/val/mask`, the first block's
  `v0`/`v1` kept) → 0 (`a3.c`); only the FIRST block rewritten, the second keeping `v0` → 7 (`a4.c`). The deciding
  defect is the `v0` reuse reaching into block 4, where the mask holds `$2`. The sibling `func_8018993C` (same TU,
  related.txt) is spelled exactly like the fixed second block — the shape was one `related.txt` read away.

## Other copies of the class (all proven 0 with `--try`, texts in `scratch/`)
Same text with the per-overlay delta / tail (`*_direct.c` = the body.c shape; the un-suffixed files, the sibling's
`mask/ptr/val` shape, also 0):
- `src/ov_SC02_017/ov_SC02_017_jr_8017DF34.c` `func_8018590C` (the listed 2nd copy; tail `func_80185EE4`) — `scratch/SC02_017_func_8018590C_direct.c`
- The `0x1E` / `D_800B99DA & 0x1F` variant — five more, each 0:
  `src/ov_SC05_001/ov_SC05_001_jr_8017BEBC.c` `func_80182600` — `scratch/SC05_001_func_80182600_direct.c`
  `src/ov_SC03_107/ov_SC03_107_jr_801789AC.c` `func_8017E7C0` — `scratch/SC03_107_func_8017E7C0_direct.c`
  (the tree's definition is K&R `func_8017E7C0(a0) s32 a0;`; the prototype-style text compiled and scored 0)
  `src/ov_SC03_112/ov_SC03_112_jr_8017C294.c` `func_801808D8` — `scratch/SC03_112_func_801808D8_direct.c`
  `src/ov_SC05_007/ov_SC05_007_jr_8017BEBC.c` `func_8017EE80` — `scratch/SC05_007_func_8017EE80_direct.c`
  `src/ov_SC03_115/ov_SC03_115_jr_8017BEBC.c` `func_8017E8D0` — `scratch/SC03_115_func_8017E8D0_direct.c`
  Each keeps its tree's own tail call spelling (casts, `(void *)a0`).

## (d) GENERATOR PROPOSAL
**R-new "inline the decompiler temp":** when a body's locals are named after hard registers (`v0`, `v1`, `a1`…) and
`.lreg` shows one of them "dies in N>1 places" across several blocks, rewrite each `vK = E; … use(vK) …` group with
`vK` substituted by `E` (a load used once) or by a fresh block-local name (a pointer used twice) — per if-block, all
at once. The sweep's R6 `inline v0` inlines ONE occurrence and R23 splits by statement group but kept the
`v0 = *(a0 + 0x20)` pointer role in the shared name (history: every single move stops at 3).

## (e) What did not work
The sweep's best 3 (`free_032.c`, R9 swap) reached 3 by breaking the xor's data flow — a compensating error, not a
shape. Rewriting only the first block (`a4.c`) → 7.

## (f) Where the method fell short
Nothing — step 13's (d15) "temp reused for several values → store each directly" and `related.txt`'s sibling
`func_8018993C` both pointed at it. The residual's "COUNT" class was misleading: the instruction counts are equal
(46/46); the missing reload is reorg deleting a redundant load because of the register choice (step 2, COUNT FIRST).

## (g) Structs answer
Not the channel: the defect was a multi-block reused temp (a local-alloc refusal), not an aliasing decision. A struct
type for `a0` (`flags@0xDC`, `state@0x1C`, `sub@0x20`) and for the sub-object (`flags@4`, `s16 y@0x10`) would make the
in-place spelling the natural one, so it removes this defect as a matter of style, but it changes no pass decision.
Not tested on bytes (the plain text already closes).

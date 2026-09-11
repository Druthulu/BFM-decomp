# func_80145934 (ov_SC07_006, 14 copies) — T7 agent c41 (S103)

**Result: score 0, 62/62 ins, barrier-free.** No register pin, no asm STATEMENT, no added volatile, no do-while, no
invented term, no dead assignment. It uses ONE body-local declaration alias (`extern u8 aD8018C944 __asm__("D_8018C944");`)
— the form METHOD_S103 step 3 lists as allowed ("a DECLARATION alias"), `tools/lever_census.py` class E, existing house
style. Whole-object check on the `--try --keep` object: `objdump -drz` of the ENTIRE `.o` (relocations included) is
identical to `.run/P36/delever/baseline/src/ov_SC07_006/ov_SC07_006_jr_801457A4.o`; `.text`/`.data`/`.rodata` compare
equal (`cmp`) and `nm` is identical (the alias adds no symbol).

This is a straight PORT (R71) of the banked-by-agent close of the very same function in another overlay,
`.run/P36/agents/ov_SC04_011__func_80145934/` (same ladder, same 0x6A4/0x384 duplicate, same callee pair), found by
`grep -rln '__asm__("D_' .run/P36/agents/*/body.c`. First `--try`: 0.

## (a) The residual in one sentence

COUNT 58 vs 62 = exactly one `lui a0 / addiu a0 / j / nop` block: the `v >= 0x6A4` arm and the `v >= 0x384` arm both load
`&D_8018C944` and gcc cross-jumped the first into the second (mine `beqz v0,c4` into the later block; the target keeps
`bnez v0,84` and its own block).

## (b) The pass and the decision (read in the sibling's pack; reproduced here on bytes, not re-dumped)

* jump2 (`toplev.c:3142`, `jump_optimize (insns, 1, 1, 0)`, the only cross_jump=1 call), the unconditional-jump arm at
  `jump.c:1969`, `find_cross_jump` (`jump.c:2371`) with the one-insn discount for a block that a conditional jump
  skips (`jump.c:2513-2517`), and the comparison `rtx_renumbered_equal_p`, whose SYMBOL_REF case is a string-POINTER
  test (`jump.c:2440`: `return XSTR (x, 0) == XSTR (y, 0);`).
* A second declaration with its own asm label gets the DISTINCT assembler identifier `*D_8018C944` (varasm.c
  `make_decl_rtl`, asmspec path), so the two `set a0` insns compare unequal, `minimum` stays 2 and the merge is refused;
  `assemble_name` strips the `*`, so the emitted bytes and relocations are the same. The tree's `"memory"` barrier did
  the same job by putting a PARALLEL between the `set` and the `jump`.

## (c) The move that closed it

* Declare `extern u8 aD8018C944 __asm__("D_8018C944");` in the body and write the `v >= 0x6A4` arm as
  `p = &aD8018C944;` (the `v >= 0x384` arm keeps `&D_8018C944`). Nothing else changed from `body_free.c`.

## (d) GENERATOR PROPOSAL

(The sibling's R20 `symbol_aliases`, confirmed on a second overlay.) When the residual is COUNT by one
`lui/addiu/j/nop` block and mine branches (inverted) into a later identical block, and the same `&SYM` appears in two
arms of one if/else chain, re-issue the EARLIER arm's reference through a body-local `extern T aSYM __asm__("SYM");` —
one candidate per repeated address constant, no search; this is the replacement for every `§5a cross-jump barrier`
lever (the neighbours list shows a second one in this very TU, the `D_8018C9D4` ladder).

## (e) What did not work

Nothing else was tried here: the sibling pack's table already records the pure-C attempts on the identical function,
all 11 (a `goto call` label, a temp `q`, a block-scope redeclaration of `D_8018C944` — same interned identifier, same
pointer — `+ 0`, retyping `p`, a ternary chain 60). I did not repeat them.

## (f) Where the method fell short

* `related.txt` lists only lever-free bodies in THIS overlay that share a callee (6 unrelated ones: func_801458E8,
  func_80145B24, ...), and `neighbours.txt` only covers this TU; the answer was the SAME function name in another
  overlay (`ov_SC04_011`). A pack builder could list "same function address / same body hash in another
  overlay that an agent has already closed" (`.run/P36/agents/*__<fn>/body.c` with score 0) — here that one line would
  have been the whole answer. METHOD's "read lever-free bodies anywhere" row points the right way but at the tree, not
  at the other agents' packs.
* The goal text ("no asm statement of any kind") and METHOD step 3 ("DECLARATION alias, allowed") should be stated
  together in PROMPT.md, so an agent does not have to decide whether an asm LABEL counts.

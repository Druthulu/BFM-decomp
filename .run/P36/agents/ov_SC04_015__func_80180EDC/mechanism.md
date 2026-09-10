# func_80180EDC (src/ov_SC04_015/ov_SC04_015_jr_8017AE2C.c) — CLOSED, score 0 (agent c38, S103)

Final body: `PACK/body.c` (= `scratch/c/b2.c`). Byte-identical per `--try` (score 0) and per a full `objdump -drz` diff of
the `--keep` candidate object against `.run/P36/delever/baseline/src/ov_SC04_015/ov_SC04_015_jr_8017AE2C.o` (relocations
included). No pin, no asm, no volatile. The equivalent `if/else-if/else` spelling with the store in all three arms
(`scratch/c/b1.c`) also scores 0; b2 was kept because it reads like its sibling `func_80180F18`
(`return (D_80078EB1 >= arg0) && (D_80078EB1 < arg1);`).

## (a) Residual
Same 15 instructions. The loaded pointer `*(a0+0xCC)` sat in `$a0` (mine) instead of `$v1` (target), x3 (two loads plus
the store's base). COUNT first: 15 vs 15, so this is registers only, no missing instruction.

## (b) Pass and decision
`body_free.c` routes the pointer through ONE function-scope local `v1`, set in three arms and read after the join. Being
live across blocks, it is a GLOBAL allocno (pseudo 76 in `scratch/dumps_a0/a0.i.greg`: `76 preferences: 4`).
Where the `4` comes from: `expand_preferences` (global.c:781, called at :523) walks every single-set insn whose SET_DEST
is a global allocno and, for each REG_DEAD note naming another non-conflicting allocno, ORs that allocno's hard-register
preferences into the destination's (global.c:815-821). The load `(set (reg 76) (mem (plus (reg 72) 204)))` carries
`REG_DEAD (reg 72)` — the parameter pseudo, itself preferring `$4` from its incoming copy — so 76 inherits `$4` and
`find_reg` gives it `$a0`. (`set_preference`, global.c:1535-1559, would NOT have done it: it strips one `'e'` level —
MEM to PLUS — and gives up on a non-REG.)

The target's source has no such local: the store is written in each arm. Each arm's pointer is then a BLOCK-LOCAL pseudo
(81/83 in `scratch/dumps_b2/b2.i.lreg`, "in block 2/3"), allocated by local-alloc, which does not tie a pseudo to a
memory address's base (block_alloc ties only register operands / matching constraints, local-alloc.c:1283-1346; and 72 is
not local anyway, :1774). It takes the first free register: `$2` is the stored constant (82/84 in 2), so the pointer gets
`$3`. The post-reload cross-jump (jump2, `find_cross_jump` jump.c:2371, `toplev.c:3142`) then merges the identical
`lw v1; li v0,2; sw` arms and the `sw v0,176(v1)` tail of the `1` arm, which is why the target LOOKS like one join —
the bytes' single `sw` is a merge made after allocation, not a single source statement.

Proved on bytes: the close itself (score 0, objdump identical); the allocation dispositions (read in the .greg/.lreg
dumps for both spellings). The cross-jump attribution is a reading of the output shape (three source stores -> one `sw`),
consistent with METHOD c6; I did not diff `.jump2` insn by insn.

## (c) Move
Delete the join-point local; write the full store `*(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = K;` in each arm of the
condition (b2: `if (D_80078EB1 >= a1 && D_80078EB1 < a2) {... = 1;} else {... = 2;}`).

## (d) Generator proposal
When a local set in every arm of an if/else and read ONLY by one store after the join lands in the register of an
argument that dies at its load (a `REG-caller` residual, `aN -> v1`), sink the join-point statement into each arm
(tail-duplicate the store, substituting the arm's value) and delete the local — cross-jump re-merges the tails after
allocation at zero byte cost.

## (e) Not tried / not needed
The mechanical search (history.txt) reached 2 with inline-v1 / tmp moves; it has no "sink the join statement into the
arms" move, which is the one that closes. No other spelling was needed.

## (f) Method notes
The first `--try` after reading the target objdump whole closed it: the target has the load DUPLICATED into every arm and
one shared `sw` reached by `j` — the signature of tail-merged per-arm stores (METHOD c6's inverse: there a shared tail
was split into per-site calls). The residual hunk view showed only `a0 -> v1`; the whole-function objdump was the
evidence.

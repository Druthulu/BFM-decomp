# func_8017B238 (ov_SC07_006, TU src/ov_SC07_006/ov_SC07_006_jr_8017AE2C.c) — agent c54, S103

**Status: score 0 (MATCH, 76/76) on the FIRST `--try`, by a straight port of the lever-free ov_SC04_011 copy
(src/ov_SC04_011/ov_SC04_011_jr_8017AE2C.c:2762).** `PACK/body.c` holds the result, with no pin, no asm and no
volatile.

## (a) Residual
Starting text: same instruction count (76). `$s0` takes `param_2` at entry (`move s0,a1` before the test,
`sltiu v0,s0,11`). The target tests `$a1` directly, copies `move s0,a1` only inside the `>= 0xB` arm, and computes
`sll s0,a1,4` in the else arm. The pin and launder were faking "param_2 stays in $a1 until the branch".

## (b) Pass and decision (hypothesis, not dumped)
In the starting text, `src` is scoped to the `>= 0xB` arm and is a copy of `param_2`. The else arm computes both
addresses straight from `param_2`. So param_2's pseudo is the value live into both arms, and it gets `$s0` with the
entry copy. In the sibling, `src` is ONE function-scope variable assigned in BOTH arms (the pointer in the `>= 0xB`
arm, `&D[param_2*16]` in the else arm, passed as the first call's a1). That single pseudo holds `$s0` in both arms,
and param_2 stays in `$a1` (the S103 c18 "one role, one register → merge the locals" class; `find_reg`,
global.c:945-990). The bytes prove this part. The allocator reasoning above is my reading of the source; I did not
dump `.greg` to confirm it.

## (c) Move
Port the sibling's text: hoist `u8 *src;` to function scope. In the else arm write
`src = &D_8018DD4C[param_2 * 0x10];` and pass `(s32)src` as the first call's second argument, which replaces the
local `a1addr`. Keep this overlay's symbols and body-local externs (D_8018DD4C, D_801F606C, D_801F6064, D_801F62F8,
D_801F5FF4, type Blk8_8017B238).
Differences from the banked sibling: symbols only (D_80193D6C → D_8018DD4C, D_801EECD4 → D_801F606C,
D_801EECCC → D_801F6064, D_801F1638 → D_801F62F8, D_801EEC5C → D_801F5FF4, Blk8_8017B238_8017B238 →
Blk8_8017B238), plus the two globals this copy declares body-locally. The shape is identical.

## (d) Generator proposal
When an if/else computes the same role in both arms (a source pointer), with one arm naming a local and the other
passing an inline expression, and the target's objdump holds that role in one `$sN` across both arms, hoist the local
to function scope and assign it in both arms. More generally for R71: when a lever-free same-name copy exists
elsewhere, try its text with the symbols remapped FIRST, before any search. That took one compile here, where the
mechanical search spent 774 compiles on this copy.

## (e) Not tried / not needed
Nothing else was tried. The port closed on the first compile.

## (f) Method
`related.txt` listed only same-overlay bodies that share symbols, not the same-name lever-free copy in ov_SC04_011.
The coordinator's prompt supplied that copy. The pack builder should put the same-name lever-free copy (with the
symbol remap already applied) at the top of `related.txt`.
Other copies of this function that still carry the two levers in the tree: ov_MAIN_012 (jr_801789AC.c), SC01_077,
SC02_037, SC03_107 (jr_801789AC.c), SC07_006, SC07_007, SC07_010, SC07_011. Each one differs from this pack's
`body_tree.c` in symbols only. Checked on bytes for ov_SC07_007: this `body.c` with the five symbols remapped scores
0 (`PACK/scratch/port_SC07_007.c`). Without the remap, the unmodified `body.c` scores 10 on all seven. Propagation
with a symbol remap should bank the whole class.

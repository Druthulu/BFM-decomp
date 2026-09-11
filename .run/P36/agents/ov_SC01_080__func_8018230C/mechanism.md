# func_8018230C (ov_SC01_080_jr_8017AE2C.c) — e19, P36 S104 T7

**Final: score 0, plain C, ZERO levers** (tree: 1 pin `$3`; before → after = 1 → 0). `body.c` = `scratch/vD.c`.

(a) Residual (6, REG): in the per-`c` block that fills `base[]`, base[1]'s value (loaded, stored, then `-= D_8018A302*c`)
took `$v1` and base[2]'s short-lived value (`z`) took `$v0` — the mirror of the target.

(b) Mechanism (proven: dumps `scratch/dumps_free`, `scratch/dumps_D`, `tools/localalloc_sim.py … 0 mismatches`): one
basic block, local-alloc's `qty_compare_1` (`local-alloc.c:1598-1616`, floor_log2(refs)·refs/(death−birth)). Lever-free:
z's quantity is born 26, dies 30 → 2·4/4 = 20000, outranks base[1]'s tied quantity (r93+r100 via `combine_regs`, 10
loop-weighted refs, 18..36 → 16666), so z takes `$v0` first. Moving `w = D_8018A304 + D_8018A306 * c;` from BEFORE the
`base[]` stores to AFTER them changes sched1's interleave (the `addu` for `w` now lands between z's load and store, as in
the target's bytes `lhu v1,14(s5); addu s7,a0,a1; sh v1,20(sp)`): z's quantity spans 24..30 → 13333 < 16666, base[1]'s
quantity is allocated first and takes `$v0`, z takes `$v1`. Bytes identical (113/113).

(c) Move (one line): `w = D_8018A304 + D_8018A306 * c;` moved below the four `base[]` statements (and the `{ u16 z; }` block
dropped — `base[2] = *(u16 *)(arg0 + 0xE);` direct; the block is inert either way: `scratch/vA.c` keeps it, also 0).
`scratch/vB.c` (w between the base[2] store and the subtraction) also 0.

(d) GENERATOR PROPOSAL: when a register residual is a `$v0`/`$v1` swap inside one straight-line block and localalloc_sim
shows a short-lived quantity outranking a longer-lived one by < 2x, move an INDEPENDENT hoisted computation (a statement
whose operands are unrelated to the swapped pair) to each later position in the block — sched1 interleaves it inside the
short quantity's range and lengthens it (a statement-MOVE generator over distance > 1, not R9's adjacent swap).

(e) Did not work: `w` before (tree order, 6), between base[0] and base[1] (vF, 6), between base[1] and base[2] (vE, 6);
merging the load into the subtraction (vG, 42 — drops the first base[1] store). The header's `@stuck:` claim "every
source-order permutation was INERT … 6 load/store orders" permuted the base[] statements only, never `w`'s — refuted.

(f) Method: the localalloc_sim table gave the arithmetic (z needs a range ≥ 6 to lose) and the target's own bytes showed
which insn sits inside z's range (`addu s7`) — reading "what unrelated insn is INSIDE the short range in the target" is
the step that closed it; history's R9 (adjacent swaps) never moves a statement over four others.

(g) Structs: no. The decision is sched1 order + quantity ranges; `base` as a struct `{u16 x,y,z;}` changes neither
(the header reports struct-vs-array base inert, consistent). Not needed.

Other copies: none (grep of `func_8012D3B4((s32)&v[i]`, `D_8018A302` — this TU only).

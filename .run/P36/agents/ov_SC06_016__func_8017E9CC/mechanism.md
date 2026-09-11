# func_8017E9CC (ov_SC06_016, src/ov_SC06_016/ov_SC06_016_jr_8017C8D0.c) — e24, P36 S104

**Final: score 0, ZERO levers** (the tree's `register s32 flag __asm__("$3")` pin removed, and `flag` itself deleted).
`body.c` = scratch/v_as.c. Two moves, jointly:
1. the `flag` temp inlined: `if (D_8019F708 == 1)` read AFTER the `0x1C` store (source order: store, then load);
2. the store spelled as an array element of the object, `((s32 *)arg0)[7] = 0x11;` (was `*(s32 *)(arg0 + 0x1C) = 0x11;`).
Also 0: scratch/v_cs.c (keeps `flag = D_8019F708;` after the store) and scratch/v_struct.c (a body-local
`struct { u8 pad[0x1C]; s32 f1C; }` field store instead of the array index — the likely original shape).

(a) Residual (body_free, score 6, REG): in the block after the first call, the flag load / constant 17 / constant 1 take
v0/v1/v1 where the target has v1/v0/v0. Instruction count equal; a pure register permutation in ONE basic block.

(b) Mechanism (proved with `.lreg` + `tools/localalloc_sim.py`, 0 mismatches, scratch/dumps_free0 vs dumps_as):
- local-alloc's block 0 has exactly THREE quantities, so `block_alloc` uses the hand-written three-way switch
  (`local-alloc.c:1486-1500`) whose `qty_compare (0, 1)` / `(1, 2)` compare quantity NUMBERS, not order slots — for
  priorities (2500, 10000, 10000) it degenerates to BIRTH order, so whichever of the three is born first gets v0.
  body_free: flag born first (q0 = r74, pri 2500) → v0. Target: constant 17 born first → v0, the constant 1 re-uses v0,
  flag (live across both) → v1.
- So the source order is store-then-load. But with the plain `*(s32 *)(arg0 + 0x1C)` store the load cannot be scheduled
  above it (score 4, ORDER; scratch/v_a.c, v_c.c): `true_dependence` (`sched.c:817-835`) only frees a fixed-address
  non-struct read from a store when the store is MEM_IN_STRUCT_P at a varying address. `expr.c:4568-4577` sets
  MEM_IN_STRUCT_P on an INDIRECT_REF whose operand is a PLUS_EXPR (`((s32 *)arg0)[7]` = `*((s32 *)arg0 + 7)`) or an
  aggregate component, but NOT on `*(s32 *)(arg0 + 0x1C)` (the operand is a NOP_EXPR cast of the sum). With the in-struct
  store, sched1 keeps the source order (birth order 17, flag, 1 — local-alloc assigns the target's registers) and sched2
  hoists the `lh` above `li 17; sw` (target's order) because the dependence is gone.
- Neither move alone closes: inline-only / reorder-only = 4 (ORDER), the in-struct store with the load first would give
  birth order flag-first again.

(c) See the two moves above.

(d) GENERATOR PROPOSAL: when a ORDER/REG residual has a fixed-address global load that the target schedules ABOVE a
store through `*(T *)(p + K)`, rewrite that store as `((T *)p)[K / sizeof(T)]` (or a body-local struct field) and try the
global read both before and after it — MEM_IN_STRUCT_P on the store removes the sched dependence
(`sched.c:831-834`).

(e) Tried and failed: `s16 flag` (9, COUNT); indexing the else arm as one expression `D_80188B94[D_8019F7B0 * 3 + rand() % 3]`
(20, COUNT); one call hoisted after the if/else (15, COUNT). The history's 182 candidates reached 4 (R6 inline flag /
R9 swap) and stopped — no generator changes the pointer spelling of a store.

(f) Method note: the three-quantity switch (step 16 / d21) was the key reading; `localalloc_sim.py` printed it correctly
(its `verbose` argument must be an integer — passing `v` raises ValueError after printing the table).

(g) STRUCTS: YES, this is exactly the structs channel. Giving `arg0` a struct type with `s32 f1C` at 0x1C (field
access instead of `*(s32 *)(arg0 + 0x1C)`) makes the store MEM_IN_STRUCT_P (`expr.c:4568-4577` for the COMPONENT_REF),
and `true_dependence` (`sched.c:831-834`) then lets the scheduler move the scalar global read above it. Proved on
bytes: scratch/v_struct.c scores 0 with a body-local `struct E9CC_obj { u8 pad[0x1C]; s32 f1C; }`. The array spelling in
body.c is the no-new-type equivalent and should become the field access when the object struct exists.

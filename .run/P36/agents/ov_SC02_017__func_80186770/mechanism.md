# func_80186770 — e4 (P36 T7 S104) — score 4 -> 0, ZERO levers

(a) Residual: REG, one 4-insn group in case 1 (`*(obj->0x20 + 0x12) += v` before `func_8012B178`): the target keeps
the pointer in `v1` and the loaded/summed halfword in `a2`; the lever-free text swaps them (pointer `a2`, sum `v1`).
The tree pinned the sum to `$6` (a2).

(b) Pass/decision (dump-verified: `PACK/scratch/dumps_free`, `dumps_c2`, `dumps_c5`; simulated with S104 d5's
`lsim3.py`, 0 mismatches vs each dump):
  1. local-alloc, block 12. The lever-free text loads `b178arg = D_801D619C` into its own pseudo (r75, tied to `a1`)
     BEFORE the halfword update, so the block has FOUR quantities (pointer r102 pri 3000, b178arg 5000,
     loaded+sum tie r104/r101 13333, `d & 0x1000` 10000) -> `qsort (… qty_compare_1)` (local-alloc.c:1504) ranks the
     sum first, it takes the lowest free register `v1`, and the pointer gets `a2`.
     Passing the global straight in the call (`func_8012B178(param_1, D_801D619C)`) loads it directly into `$a1`,
     leaving THREE quantities; the three-quantity case (local-alloc.c:1486-1500) compares QUANTITY NUMBERS
     (`qty_compare (0, 1)`, `(1, 2)`, `(0, 1)`), not positions in `qty_order`, and here it ends with the
     birth order: pointer (q0, 3000) BEFORE the sum (q1, 13333) -> pointer `v1`.
  2. sched1 `true_dependence` (sched.c:817-841). Passed directly, the load of `D_801D619C` follows the halfword
     store in the RTL. With `*(u16 *)(X + 0x12)` (a cast of an integer sum: not MEM_IN_STRUCT_P) the load stays after
     the store, `$a1` is free during the sum's life and it takes `a0`/`a1` (c2: score 15). Written as an indexed
     access through a pointer, `(*(u16 **)(param_1 + 0x20))[9]`, the INDIRECT_REF operand is a PLUS_EXPR, so the MEM is
     marked in-struct (expr.c:4568-4577, dump shows `mem/s:HI`); a varying-address in-struct store vs a fixed-address
     scalar load is independent (sched.c:835-837), sched1 hoists `lw a1,D_801D619C` above the store, the sum now
     conflicts with `v0, v1(pointer), a0, a1` and lands in `a2` — the target.

(c) Moves (joint; each alone fails: in-struct store with b178arg kept = 4; global passed with the cast spelling = 15):
  - delete `b178arg` and pass `D_801D619C` directly to `func_8012B178`;
  - write the update as `(*(u16 **)(param_1 + 0x20))[9] += v;` (replacing the `pp`/`nv` block).
  Proven equivalent on bytes: `((u16 *)*(s32 *)(param_1 + 0x20))[9] += v;` (0) and a struct field
  `(*(struct { u8 pad[0x12]; u16 rot_y; } **)(param_1 + 0x20))->rot_y += v;` (0). body.c uses the first.

(d) GENERATOR PROPOSAL: when a call argument is a global loaded into a temp BEFORE an unrelated store to
`*(T *)(ptr + K)` and the residual is a register swap in that store's group, try the argument inline in the call
together with re-spelling the store as `((T *)ptr)[K / sizeof(T)]` (or a struct field) — the aggregate marking
lets sched1 hoist the global's load past the store while the temp's quantity disappears.

(e) Did not work: the sweep's R5/R6/R7/R8/R9/R10 (all 4); c2 (plain `*(u16 *)(… + 0x12) += v` + inline global: 15,
the load stays behind the store); c3 (in-struct store, b178arg kept: 4 — four quantities, qsort ranks the sum first);
c4 (`*(u16 *)((u8 *)… + 0x12)`: 15 — the INDIRECT_REF operand is a NOP_EXPR, not a PLUS_EXPR, so it is not in-struct).

(f) Method: the allocation table (global) is blind here; `lsim3.py` (not the promoted tools/localalloc_sim.py) gave
the per-block ranking and matched every dump. The deciding fact was that the tree's `b178arg` temp was itself the
defect (it adds a fourth quantity); nothing in the sweep deletes a temp that feeds a call argument AND changes the
store's aliasing class at once.

(g) Structs: YES, and tested on bytes. The object at `*(param_1 + 0x20)` (a GTE/transform-like record with a `u16` at
+0x12 — the Y rotation this state machine keeps adding to; also `+0x10` SVECTOR, `+0x18`, `+0x2C` in sibling
func_80184754) as a struct type makes the `+0x12` store a COMPONENT_REF, i.e. MEM_IN_STRUCT_P, which is exactly the
channel (expr.c:4568-4577 -> sched.c:835-840) this close needs. A body-local struct-field version scores 0 (above).
Array indexing gets the same marking without a type, so the body does not wait for the structs phase.

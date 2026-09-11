# func_801AB818 (md_SC07_004) — P36 S104 agent e1 — score 1 -> 0, ZERO levers (was 1 `"memory"` barrier)

(a) Residual: lever-free, the FIRST of the two `sw v0,16(sp)` stores to the struct temp `tmp` is deleted (mine has a `nop`
where the target has the store; same count otherwise).

(b) Pass and decision:
- flow.c dead-store rule: `insn_dead_p` (`flow.c:1726-1727`) deletes a MEM store whose address is `rtx_equal_p` to
  `last_mem_set`, the last store seen scanning BACKWARDS; `mark_set_1` records it (`flow.c:1966-1974`) and ANY memory read
  resets it (`mark_used_regs` case MEM, `flow.c:2379`). In body_free.c both source loads (`cur`, `addend`) precede both
  stores, so nothing between the stores reads memory and the first store is dead. The tree's `__asm__("" ::: "memory")`
  was faking an intervening memory access.
- sched.c `true_dependence` (`sched.c:831-839`): a READ after a pending WRITE is independent when the read is
  `MEM_IN_STRUCT_P` with a varying address and the write is non-struct with a fixed (frame) address. `MEM_IN_STRUCT_P` on an
  INDIRECT_REF is set only when the pointer operand is itself a `PLUS_EXPR` (or an aggregate/ADDR_EXPR of one),
  `expr.c:4568-4577`; `*(s32 *)((s32)a0 + 0x30)` has a NOP_EXPR (the cast) on top and is NOT in-struct.

(c) Moves that closed it (joint; proven on bytes):
1. Read the addend BETWEEN the two stores: `*(s32 *)&tmp = cur; *(s32 *)&tmp = cur + <addend>;` — the read resets
   `last_mem_set`, the first store survives (score 1 -> 5 alone: store kept, but the load stays after it -> 2 nops).
2. Spell the addend `((s32 *)a0)[12]` (array index = INDIRECT_REF of a pointer PLUS_EXPR -> in-struct, varying address) so
   sched1 hoists it above the frame store, as in the target (5 -> 0). A struct field
   `((struct { u8 pad[0x30]; s32 addend; } *)a0)->addend` also scores 0 (COMPONENT_REF, in-struct) — proven.
   `*(s32 *)((u8 *)a0 + 0x30)` scores 5 (cast on top of the PLUS -> not in-struct) — proven.
3. Final text (body.c, 0): `cur`/`addend` locals deleted — `*(s32 *)&tmp = *(s32 *)(s1 + 0); *(s32 *)&tmp +=
   ((s32 *)a0)[12];` (the compound read of tmp is forwarded by cse, the addend read stays between the stores). The same
   with the struct-field addend also scores 0.

(d) GENERATOR PROPOSAL: when a `"memory"` barrier sits between two stores to the same stack slot (the target keeps a
dead-looking first store), delete the barrier and move a memory READ that feeds the second store's value to between the
stores, spelling it as an array index `((T *)p)[K/sizeof(T)]` (or a struct field) so the scheduler may still hoist it.

(e) Did NOT work: the free sweep's 191 compiles (R7 block/do-while, R8 temp, R10 param-copy, R18 bystander) all stay at 1 —
none moves a read between the stores. `*(s32 *)((u8 *)a0 + 0x30)` between the stores = 5 (not in-struct, stays put).

(f) Method gap: none for this one — the tree's own comment named the pass (flow last_mem_set); the missing half was
sched.c's in-struct channel, which step 10's struct question pointed straight at. Note: `--try` returned two transient
`COMPILE-ERROR — ... At top level:` (truncated at 300 chars) on unchanged text; a retry compiled it. The 300-char truncation
hides the real message.

(g) Structs: YES, and proven on bytes — this is exactly the `expr.c:4568-4577` channel. With `a0` typed as a struct whose
field at 0x30 is `s32` (the same object also has `s32` at 0x1C (counter), `s32` at 0x20 (sprite pointer, `u16` fields at
0x18/0x1A), `u8 *` at 0x24), `a0->f30` is a COMPONENT_REF -> in-struct -> the scheduler hoists it over the stack store,
and the natural source `tmp = *s1; tmp += a0->f30;` closes with no index trick: the body-local struct cast
`((struct { u8 pad[0x30]; s32 addend; } *)a0)->addend` scored 0 in both the two-statement and the `cur` spellings (proven).

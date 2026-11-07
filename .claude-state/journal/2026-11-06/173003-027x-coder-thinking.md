---
ts: 2026-11-07T00:30:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_igSSqXGthNNyAZ8bwekN
---
`rtx_addr_varies_p(x)` for `(mem (symbol_ref))` — that function (in rtlanal.c) returns 0 for a constant address. So no invalidation. Confirmed my earlier conclusion: only `all` invalidates the symbol load.

So what sets all=1? From note_mem_written: `written == 0` (unknown store → everything), BLKmode store, SCRATCH, or a varying address that is not (in_struct||PLUS) or is QImode.

Also, calls set everything (invalidate_memory(&everything) at line 7246).

So the target's second pointer load must come from... hmm, wait. Maybe the answer is much simpler: maybe the two uses are NOT in the same basic block in the target's RTL. cse_basic_block ends at a label or jump and clears the table? cse clears the table at the end of each basic block (`cse_basic_block` → `flush_hash_table` at block end?). If the original source put a label between... but the emitted code has no branch. However! A label can exist in RTL without emitting code. E.g., a `goto`/label, or an if with an empty arm, or a `do{}while(0)`.

In cse_basic_block, when a CODE_LABEL is reached, it starts a new block: the table is preserved only if the label is not a jump target... Let me recall: cse_basic_block processes insns until a JUMP_INSN; at a LABEL it calls `cse_end_of_basic_block`... Actually gcc's cse basic block = from one label to the next, and cse only caches across blocks via `cse_set_around_loop`/branch_path. If a label is in the middle (not a branch target), cse still treats it as a block boundary and *flushes* the table (well, it uses `next_qty`/reg_tick to carry register values, but memory entries are NOT carried across block boundaries).

Yes! In gcc 2.7.2 cse.c, at the end of a basic block, memory expressions are not carried over (the table is flushed; only register equivalences are retained via reg_tick/reg_eqv mechanism). So a LABEL between the two uses would force the second load!

And crucially, a label with no branch to it can be removed by later passes... but jump_optimize runs before cse1. If the label is not a jump target, jump_optimize (or the earlier flow/jump pass) deletes it. Hmm.

BUT: the do-while(0) trick (C0535) creates an EBB split — a note, not a label. Notes don't split cse blocks.

What creates a label without emitting code? A `goto` that targets the label right after, or an if whose arms both fall through... jump_optimize would remove it.

Hmm, but wait — in the *target*, is there any label in the RTL? The emitted code has no branch between. However, cse blocks also end at CODE_LABEL. If a label existed and jump_optimize removed it before cse, no.

Alternatively, the original source might have the two uses in different basic blocks that were merged by jump_optimize... no, cse runs after jump_optimize.

Hmm, what about cse2? The target's RTL could have the split from cse1's perspective (block boundary at cse1) but cse1 doesn't remove the label; then jump2/flow merges blocks after. Order in toplev 2.7.2: 
rest_of_compilation: ... jump_optimize(1), cse (cse1), loop_optimize, jump_optimize(2)?, cse2, flow, combine, sched, local-alloc, global-alloc, reload, sched2, jump_optimize(3)...

Hmm, actually the order in 2.7.2 toplev.c: 
```
  if (optimize > 0) { open_dump_file; ... }
  ...
  jump_optimize (insns, !JUMP_CROSS_JUMP, !JUMP_NOOP_MOVES, !JUMP_AFTER_REGSCAN);
  if (optimize > 0) { cse (insns, ...); /* cse1 */ ... }
  if (optimize > 0 && flag_loop_optimize) loop_optimize(...);
  if (optimize > 0) { if (!flag_expensive_optimizations) ... ; cse (insns, 0, ...) /* cse2 */ }
  ...
  if (optimize > 0) { jump_optimize(...) }
  ...
  flow_analysis / combine / sched
```

So: a label that survives jump_optimize #1 (before cse1) would split cse1 blocks. But an unused label gets deleted by jump_optimize.

What about a `do { } while (0)` — gcc 2.7.2 expands it as... the loop notes? For a do-while(0), the front end emits a NOTE_INSN_LOOP_BEG... Actually the front end emits LOOP_BEGIN/LOOP_CONT notes and a jump. jump_optimize would delete the loop and the jump, leaving a NOTE_INSN_LOOP_BEG? The C0535 move says "do{}while(0) splits cse1 EBB" — so this is exactly the known trick! It says a do-while(0) splits the cse1 EBB (extended basic block). 

So: wrap the second use (or the first) in a `do { ... } while (0)`. That leaves loop notes that split cse's EBB, so the memory table isn't carried across, forcing the reload of the symbol pointer!

Great — that's exactly C0535, and it's a listed move. Let me try:

```
obj = a0->unk20;
CAST_WIDTH(u16, obj, 0x14) = CAST_WIDTH(u16, obj, 0x14) + (a0->unk2A - *(u16*)((u8*)D_80126B78+0x12));
do {
    ((Unkstruct_800B5CB8 *)a0)->unk2A = *(u16 *)((u8 *)D_80126B78 + 0x12);
} while (0);
```
Hmm, but the do-while must not add insns. C0535 was used to keep a store in place. Let me check whether the do-while(0) here is even legal: `// !FAKE: do-while` comment required. Yes the constraints allow `do{}while(0)` only with `// !FAKE: do-while`.

Let me try it. Also try wrapping the store differently.

Let me write w2.c with do-while(0) around the second use.

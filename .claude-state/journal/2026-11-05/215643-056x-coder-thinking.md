---
ts: 2026-11-06T04:56:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ta2HlS1WOzsfoVCOjWWJ
---
In cse2 (barrier-free), insn 64 is `(set (reg:SI 4 a0) (reg/v:SI 76))` — the call arg is the stored value reg 76, not a reload. So cse2 forwarded the `*p` load (which would be `(mem:SI (symbol_ref D_80127524))`) to reg 76 (the value stored). Note insn 57 kept a reload for the sh base (reg 84), but the call arg was forwarded. Why? Because cse2 processes: insn 50 stores reg 76 into (mem (reg/v 75)); since reg/v 75 has REG_EQUAL D_80127524, cse records the store to the symbol address. Then in the next EBB (after jump_insn 53), insn 57 loads the mem → cse forwards to... wait it didn't (insn 57 is a real load). Hmm, insn 57 is a load from D_80127524 into reg 84 — that IS the sh base load, kept. And insn 64 (call arg) was a load from D_80127524 too, forwarded to reg 76.

Why did one survive and the other not? Maybe because insn 57's load is in a different basic block from insn 64? The jump_insn 53 is between the store (50) and the loads. cse1 (EBB) starts a new block after the jump. Within that block, insn 57 loads D_80127524; then insn 61 stores to (mem:HI (reg 84 + 26)); then insn 64 loads D_80127524 again. The second load in the same block... cse's table: after insn 57 loads D_80127524, it records the value in reg 84. But insn 61 is a store through reg 84+26 — note_mem_written invalidates memory entries that may alias; a store to (reg 84 + 26) where reg 84 = the loaded value (unknown address!) — since the address is a register with unknown value, cse must invalidate ALL memory entries (writes_memory). That would kill the D_80127524 equivalence... but then insn 64's load shouldn't be forwarded to 76.

Wait, maybe it's the opposite: the *load* at 57 is a real load because cse couldn't forward across the jump (new EBB). Then insn 64 is a load in the same EBB; cse sees the memory... Hmm, if cse had a table entry from the store (insn 50) it wouldn't cross the jump.

Let me look at the cse1 dump instead — maybe the forwarding happened in cse1 (same block). Actually, maybe flow merged blocks. Let me check the .flow dump for the basic block structure. Alternatively, compare with the orig (barrier) dump to see where the reload is kept.

Actually, the key question is: what real C prevents cse from forwarding the second load? cse forwards a load of (mem X) when the table has an entry (mem X) -> reg. The entry was created by... insn 57's load itself? No, loads create entries (mem X) -> reg 84. Then insn 61's store to an unknown address invalidates all memory entries (writes_memory) — so after insn 61 the table is cleared of memory entries. Then insn 64's load of D_80127524 would NOT be forwarded (no entry) and would be a real load... but it wasn't.

Hmm, maybe the invalidation happened differently. Let me look at the greg/sched dumps to see. Actually, let me compare with the barrier version's cse2 to see the difference.

Let me dump orig (with barrier) too.

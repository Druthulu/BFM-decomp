---
ts: 2026-11-06T12:02:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2T6XuNdAAhq8SqoyfSoc
---
Still 2. The store sink persists. This matches the sibling WALL func_801810E4 (sched-store-sink, best 2).

Let me try a couple more real-C ideas specifically for the store sink:
1. Make the store's value depend on the final call's arg computation. No.
2. Use a `volatile` on the store? Lever.
3. Reorder so the store comes after the `li a0` — but that's the wrong order (mine already has it after).
4. Reorder the source so the store is the FIRST thing in the tail? It's already last in the middle block.

Hmm. Let me think about the scheduler. The `li a0,2432` and `sw v0,16(s0)` are both in the same EBB (no branch between the middle block and the tail). sched reorders. The target has sw before li; mine has li before sw. 

sched1/sched2 order by priority. The li a0 might have higher priority (it's needed for the call). 

What if I make the store have higher priority by using its value more? No.

What if I reorder the source tail so the final call is not the last statement? E.g., move one store after the call? But the target has the call last (insn 37-38), then the epilogue. If I move a store after the call, it'd be after the jal — wrong.

What if I move the `CAST_WIDTH(...,0x10) = v` into the tail AFTER unk14 but the scheduler... v_v_func_store_late = 12 (worse).

Hmm. Let me look at the exact sched. Maybe the issue is that the store 0x10 and the tail stores (0x14, 0x18, 0x48, 0x1C) are all to the same struct (s0), and the scheduler orders them. The li a0 is independent. 

The target keeps the store 0x10 first (right after v). Mine puts li a0 first.

What if I make the store 0x10 depend on the v value AND the v value is computed right before? It is. 

What if the store 0x10 is a DIFFERENT type (e.g., CAST_WIDTH u16 vs s32)? The target is `sw` (s32). If I use a different width, wrong.

Let me try: `CAST_WIDTH(s32, (u8*)a0, 0x10) = v;` — currently. What if I use `((Unkstruct_800B5CB8*)a0)->unk10 = v;`? unk10 is a field at 0x10. Let me check the struct: Unkstruct_800B5CB8 has unk10? Let me check. If it does, using the struct member might change scheduling.

Let me look at Unkstruct_800B5CB8's fields. From the code: unk2, unk34, unk70, unk14, unk48, unk1C, unk6, unkA, unkE, unk20, unk18, unk1A, unk22, etc. Is there unk10? Let me check.

Actually, the original uses `CAST_WIDTH(s32, (u8 *)a0, 0x10) = v;` deliberately (maybe no unk10 field). Let me check the struct.

Let me grep for the struct definition.

Actually, let me step back. The sibling func_801810E4 is the SAME wall with best 2, and the wall notes say "only a memory barrier holds it". This is conclusive. Item 4 is a WALL.

But let me spend a bit more to be thorough (budget 20 min). It's 05:02, item 4 started ~04:56. 6 min. Let me try a few more, then WALL at ~05:15.

Let me try the struct member for the store and a couple of reorderings. Let me check Unkstruct_800B5CB8 first.

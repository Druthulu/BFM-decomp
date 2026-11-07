---
ts: 2026-11-06T12:02:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lhCa7g2OzhX2FXMB7wh5
---
Line 307: `barrier,pin | func_801810E4 | WALL sched-store-sink — sched sinks the dead unk1C store below the &v/&v2 setup; only a memory barrier holds it; $0 copies recovered via u16 widths; best 2 (G28)`.

So func_801810E4 (a sibling in the same TU, SC06_016!) hit the SAME sched-store-sink wall, best 2. And it says "only a memory barrier holds it". So this is a known WALL for this exact pattern.

So item 4 is a WALL too: sched-store-sink, best 2. The store `sw v0,16(s0)` sinks below the `li a0,2432` (the call arg setup), and only a memory barrier holds it.

But wait — the func_801810E4 wall says "$0 copies recovered via u16 widths; best 2". Our best is also 2. So consistent.

Hmm, but let me reconsider: the original source had the barrier `__asm__ __volatile__("")` at the end of the middle block. This is exactly the "memory barrier" that holds the store. Without it, sched sinks. So it's a genuine WALL.

But before declaring, let me try a few more real-C ideas for the store sink, since we're at score 2 (very close):
1. Reorder the tail.
2. Call-arg variable.
3. init-at-decl of tail stores (moves.md line 241/243).
4. do-while around store+tail.

Let me try these. If none work, WALL with best 2.

Actually, the sibling wall (func_801810E4) is strong evidence. But let me try the init-at-decl trick (lines 241/243) which is a real-C sched2 mover.

Let me test:
- v_tail_init: init-at-decl for the tail stores? The tail stores are struct member assignments, not declarations.
- v_call_var: `s32 c = 0x980; func_8002D4C8(c, 0);`
- v_tail_reorder: reorder the tail stores.
- v_store_dw2: do-while around store + the li-generating call? 

Let me test a batch.

Time: 05:02. Item 4 ~6 min. Budget 20-30. Let me continue.

Let me write gen8.

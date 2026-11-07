---
ts: 2026-11-06T02:43:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rP9PGHXID3vS8AktdlZL
---
Score 9, 105 vs 108 ins: mine is missing 3 instructions at position 94: target has `sw v0,28(s1); lw v0,28(s1); nop` that mine lacks. This is the barrier's effect: without the barrier, cse eliminates the store-reload (`unk1C = unkDC; ... unk1C -= 1;` becomes `unk1C = unkDC - 1;`?). Let me see the target asm around there.

The barrier prevents cse from forwarding the store into the load (store-to-load). With the barrier, the sequence is: sw v0,28(s1); ...; lw v0,28(s1); addiu; sw. Without, cse folds: lw; addiu; sw (saving 3).

So we need a real-C way to prevent cse from eliminating the store/reload. The store `unk1C = unkDC` followed by `unk1C -= 1` — cse sees the store and the subsequent load from the same address and forwards the value.

Real-C moves: make the two accesses look different so cse can't forward, while emitting the same code. E.g.:
- `unk1C = unkDC;` then `unk1C = unk1C - 1;` (same).
- Use a different lvalue spelling: `((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC;` then `*(s32*)(arg0+0x1C) -= 1;` — cse works on RTL memory expressions; different alias sets? Both MEM_IN_STRUCT maybe.
- Insert a real memory access between them that cse must respect: e.g., a call? Target has no call between.
- Make the store and the load use different base expressions: e.g., store via `((Unk*)arg0)->unk1C` and load via `((Unk*)(arg0+0))->unk1C`? The RTL address is the same after folding.
- Make the second access go through a `volatile`? lever.
- Use a union/bitfield?
- The known lever: a "store between the two" (C0414 dead-reset cse-breaker). We could add a store to a *different* address that cse can't prove non-aliasing with unk1C, forcing the reload. But that would emit an extra instruction — unless it's a store that's dead and eliminated after cse? Hmm.
- C0535 do-while splits cse1 EBB: wrap the two statements in a do-while? A do-while(0) might create a loop boundary that stops cse from crossing? cse is extended-basic-block; a do-while creates a NOTE_INSN_LOOP_BEG/END and possibly a barrier that splits the EBB. The example from the MOVES+ says C0535 (do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item). Let me try a do-while around the two statements.

Actually the store-load forwarding here is likely in cse1 or cse2. Let me look at the target asm first.

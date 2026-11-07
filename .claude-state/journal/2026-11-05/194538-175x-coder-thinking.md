---
ts: 2026-11-06T02:45:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YzyVjqHBSm3Xxeeaz9B4
---
Target: 2094 lw v0,220(s1); 2098 nop; 209c sw v0,28(s1); 20a0 lw v0,28(s1); 20a4 nop; 20a8 addiu v0,-1; 20ac sw v0,28(s1).

So the target stores unkDC to unk1C, then reloads unk1C, decrements, stores. Without the barrier, cse forwards: mine probably does lw unkDC; addiu; sw (saving 3 ins).

We need to prevent the store→load forwarding across the two statements. Options:
1. Make the two memory accesses not alias from cse's perspective: e.g., store via a `s32*` pointer cast and load via the struct. CSE's alias analysis for MEMs: if both are MEM_IN_STRUCT with constant offsets from the same base, they alias. If one is MEM_IN_STRUCT (struct member) and the other is not (raw pointer), cse might treat them as possibly aliasing anyway (conservative), which would PREVENT forwarding (good!). Actually cse's `cse_process_notes`/`cse_insn` uses `find_best_addr` and the `table` with memory; two different MEM rtx are different expressions; cse would only forward if it can prove they're the same address. `exp_equiv_p`? Hmm. In cse.c, memory stores invalidate memory table entries based on `write_dependence_p`. If the store's address and the load's address are provably the same (same rtx), the store invalidates the load's entry... Actually store-to-load forwarding: cse records the stored value as the "equivalent" for the memory location; a later load of the same address is replaced by the stored value. If the addresses are written differently (different rtx), cse may still consider them the same via `exp_equiv_p`/`rtx_equal_p` — they're the same rtx after simplification.

2. Insert a store to another address between them that may alias (forcing the reload), then make that store dead and removed after cse. E.g., store to a local variable? A local store to the stack would emit code and stay. Hmm.

3. Use a do-while to split the EBB (C0535). cse1 works on extended basic blocks; a loop boundary splits it. A do-while(0) might create NOTE_INSN_LOOP_BEG/END but not a barrier. Let me just try.

4. Use a `goto` to split? The two statements are in the same block; a goto to the next statement is removed.

5. Make the load happen in a different expression form: e.g., `((Unk*)arg0)->unk1C = ((Unk*)arg0)->unk1C - 1;` — the compiler loads, subtracts, stores; cse forwards the store into the load. Same.

6. Make the second statement a `--` on a *different* lvalue that maps to the same address: e.g., `(*(s32*)((u8*)arg0 + 0x1C))--;` — the RTL address may be identical → forwarded.

7. Change the *order*: the target has store then reload; we could make the reload unavoidable by making the store's value not the same as the loaded value? No, it is.

8. Make the first store's value a different expression so cse's equivalence is not established: e.g., `unk1C = unkDC + 0;`? cse folds +0.

9. Use a `u32`/`s32` cast on the store: `*(u32*)&((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC;` — same RTL.

10. A real-C "cse-breaker" from C0414: a dead reset. Hmm.

Let me check the moves.md for similar cracked items: search for "cse-store-forward" — line 37 is a WALL: "cse-store-forward — cse1 forwards the sh value into the reload after `*p -= 16` in one ebb; only a barrier/volatile stops it (W06)". Our case is the same family: cse1 store-to-load forwarding. That WALL suggests it's hard.

But the cookbook C0414 says "dead-reset cse-breaker; cracked 3 launders in G16x". Let me look at C0414.

Let me first try the cheap variants: do-while, different lvalue spellings, etc.

Variants:
g1: do { unk1C = unkDC; unk1C -= 1; } while (0)
g2: unk1C = unkDC; then *(s32*)(arg0+0x1C) -= 1;
g3: unk1C = unkDC; then unk1C = unk1C - 1;
g4: u32/s32 casts.
g5: do-while around each statement.
g6: a goto with a label between them (label survives if referenced? unreferenced label deleted early, before cse? The first jump pass runs before cse, so an unreferenced label is deleted → no effect. A referenced label via a goto from... hmm).
g7: make the store a `volatile`? not allowed (lever).
g8: insert a dead local store: `{ s32 d = 0; d = 1; }`? dead code eliminated.

Let me try g1-g5 and see.

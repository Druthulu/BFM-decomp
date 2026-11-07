---
ts: 2026-11-06T11:41:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_olZ3Jw76Z0rqqOIQbbU7
---
Item 2: kinds barrier,pin. There's a call func_801757A0 and a branch. The barrier prevents the reload `temp_v0 = *(u8*)(arg0+6)` from being CSE'd with the store above. The pin $3 for temp_v1.

This looks like a classic case where the barrier is needed because the compiler would forward the store into the reload (cse-store-forward wall, as seen in moves). And the pin $3 might be needed for register allocation.

Let me get the target asm for item 2 and try.

But first, finish item 1's 20 min. It's 04:42ish. Let me use the time to try item 1 variants that specifically target sched1 by adding real dependencies... Actually, let me try a variant where the Blk8 copies are done through a `Blk8` local that is ALSO the source of the group A values? No.

Alternatively, maybe I can make the group A loads have a longer dependency chain by using them twice. E.g., store r2..r5 to D_80126950..5C AND... no, that changes insns.

Let me try: what if the stores use `(u16)` casts so the store is `sh` not `sw`? No, target uses sw for group A.

I'll do a final batch of ~8 variants and then record.

Actually, let me reconsider something important: the target group A stores are 4 `sw`. The target's Blk8#1 comes after. If sched1's issue is priority, maybe if I add MORE instructions after the Blk8 copy (e.g., group B loads) it stays... no, tested.

What if the Blk8 copies are moved to the very end AND the group B loads are before them — tested (v05) = 81.

OK. Let me check one specific thing: does the score change if I use a `do { } while (0)` around the Blk8 copy (C0535 splits cse1 EBB)? That's allowed with `// !FAKE: do-while`. If it splits the EBB, sched1 might not hoist across. Let me try that — it's a legitimate technique from the cookbook and it's not a lever (it's real C control flow). Actually `do{}while(0)` is not a lever; it's a C construct. The brief allows it with the marker.

Let me test w4 with do-while around the Blk8 copies, and variants.

Actually C0535 says do{}while(0) splits cse1 EBB. If the EBB is split, sched1 schedules each part separately, preventing hoisting across! But does do{}while(0) create a new basic block in RTL? Normally gcc optimizes it to nothing. But the cookbook says it splits cse1 EBB (maybe due to a NOTE_INSN_LOOP_BEG). Let me test.

Let me write w4.

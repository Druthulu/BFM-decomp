---
ts: 2026-11-06T13:33:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hhF6fF092m5jHbM9SXig
---
That's the hashing. Let me look for how cse handles clobbers/asm in cse_insn — search "invalidate_memory" and "invalidate_from_clobbers".

Actually, the important function is `invalidate_from_clobbers` in cse.c. For an asm with a mem:BLK clobber, it calls invalidate_memory. That doesn't clear register equivalences.

Hmm, but then why did the addiu stay early in orig? Maybe cse2 did the same in orig (folded 312 into the addiu and deleted 291), but the *sched1* still placed the addiu early because of the asm barrier! I.e., after cse2, the addiu is at the call site (312), but sched1 sees the asm between and can't move the addiu across it — so it stays at the call site... no wait, the addiu at 312 is AFTER the asm, so it would be placed after the chain — exactly like nobar. Hmm.

Wait, but in the orig's final target, the addiu is early. So in orig, after cse2, the addiu must be at 291 (early), not at the call. So cse2 did NOT fold it in orig. So the asm DID prevent the propagation.

Let me verify by looking at orig.i.cse2 around insn 291/312.

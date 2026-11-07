---
ts: 2026-11-06T05:03:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_62XDKGeAmZ6X5rGRajlG
---
Priority = floor_log2(refs) * refs / live_length * 10000 * size.

For r75 (base): refs 14, live 132: floor_log2(14)=3, 3*14=42, 42/132=0.318, ×10000=3181. ✓
For r73 (a1): refs 7, live 48: floor_log2(7)=2, 2*7=14, 14/48=0.2917, ×10000=2916. ✓
For r93 (a2): refs 3, live 7: floor_log2(3)=1, 3/7=0.4286 → 4285. ✓

So the priority is refs-weighted / live_length. To make a1's priority > base's, either raise a1's refs or lower base's live_length.

Target: a1 > base. So in the target, a1's pri > 3181 or base's < a1's.

With the asm barrier, the live lengths change (the asm insns count as insns, increasing live_length!). The barrier adds insns, which *increases* live_length for everything crossing them, lowering priorities. Specifically, base's live_length might grow more than a1's.

Wait, but the target's priorities: base has 14 refs and some live_length; a1 has 7 refs and some live_length. With the asm, the function has 114 insns vs 107; base's live_length probably grows.

Hmm, we can't add insns. We need a real-C change that lowers base's priority or raises a1's.

Real C moves:
- Reduce base's live_length: base is live from its definition (top) to its last use (end). It's used in the second half only. If we could define base later (just before the second half), its live_length would drop → priority rises (bad: base would go even higher).
- Increase base's live_length: define it earlier? It's already at the top.
- Increase a1's refs: add real uses of a1 that don't change the code. Hmm, a1 is used in `addu v0,v0,s1` — the target has 6 such. We can't add more.
- Decrease a1's live_length: a1 is a parameter, live from the start. If we copy it to a local and use the local... that changes the code.
- Change the *number of refs* counted: refs are counted per use. If a1's uses are inside a loop (do-while), flow adds loop-weighted refs: REG_N_REFS += loop_depth. That's what raised a1 in q1... but q1 showed a1→s0 which means a1 was HIGHER (s0 is the... wait).

Hold on, I need to determine the register assignment order. From the .greg order line "93 75 73 74" and the observed mine (a2=s2, base=s1, a1=s0): the order of assignment must be r93→s2? That seems odd.

Let me check: maybe the .greg order line is not the allocation order but something else. Let me look at alloc_table.py to understand the output format.

Actually, simpler: compare v1 (no do-while) which has a1=s1, base=s0 (correct target assignment!) with t2 (do-while) which has a1=s0, base=s1. The alloc table for v1 shows r75(base) pri 3181 > r73(a1) 2916 → base higher → base gets s0? But the v1 disassembly has base=s0 and a1=s1. So the higher priority gets s0. And in t2, a1 got s0, so a1's priority must be > base's in t2.

Let me dump the alloc table for t2 and compare r73/r75 priorities.

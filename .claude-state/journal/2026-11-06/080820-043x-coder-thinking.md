---
ts: 2026-11-06T15:08:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WqFQc9EBRKiEPGL8QseA
---
d1: 238 ins — the mask didn't merge; extra insn. So reorg kept the sll (good) but the andi is extra.

I need the second set to be zero-cost. Options: make it merge with an existing mask. The existing final `& 0xFFFF` at 5a8 is the outer andi on the argument. If vol's mask is computed and then `(vol | ...) & 0xFFFF`, combine could fold `(vol & 0xFFFF) | X` & 0xFFFF. Hmm, it didn't.

What if I write the final expression to reuse vol's masked value: 
```
vol = vol & 0xFFFF;
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
Combine: `(vol & 0xFFFF) | (0x3000 | (sx<<8))` then `& 0xFFFF`. If sx<<8 has bits above 16, the outer mask is needed. combine might push the mask inward only if it can prove. Likely keeps 2 andis (d1 = 238, so yes 2).

Alternative: get the second set from an insn that already exists. What existing insns write vol's reg (196)? insn 476 sets reg 196 (vol). The final andi at 5a8 sets a1 (vol's hard reg after allocation) but pre-reload it's a different pseudo (the argument temp). 

What if I make the argument temp BE vol: `vol = (vol | (0x3000|sx)) & 0xFFFF;` (c1) — that's a second set, zero-cost, but c1 scored 30 (236 ins, no boost). Why didn't it work? Let me dump c1's sched to see reg_n_sets. Maybe cse combined vol's two sets? Or maybe the second set at the call is in a different basic block, and... no, reg_n_sets is function-wide.

Wait — maybe c1's second set changed vol's live range such that vol got a different hard reg, changing everything, but the boost still... it gave exactly the no-launder result (236, pan first). Let me dump c1 to check reg_n_sets. Actually the cse pass could have merged `vol = (vol|..)&0xFFFF` such that the call uses the same pseudo — that's still 2 sets.

Hmm, unless... `flow` or `combine` turned the second set into a copy? Let me check c1's sched dump: look for the insn setting reg 196.

Let me dump c1.

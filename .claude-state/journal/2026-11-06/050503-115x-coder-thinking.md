---
ts: 2026-11-06T12:05:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wNycFwt55Ey3fKAmtyg5
---
Target: 
- s2 = &D_8011F7F0 (lui/addiu) at 3f8c-3f90 — base is in s2.
- 3fc8: `addiu v0,s2,-72` (base-0x48), 3fcc `addu s4,a0,v0` → arr = base - 0x48.
- Later uses: `*(u16*)(base - 0x34)` → `lhu a2,-52(s2)` (s2 = base, -52 = -0x34).

So base IS in a register (s2) in the target! The launder's effect is to break the cse class so that... hmm.

So w1 (`base = (u8*)&D_8011F7F0;`) gives 191 insns (+3). The launder version gives 188. So the launder saves 3 insns. Interesting: maybe without the launder, cse merges `base` with the `arr` computation differently.

Let me look at w1's diff.

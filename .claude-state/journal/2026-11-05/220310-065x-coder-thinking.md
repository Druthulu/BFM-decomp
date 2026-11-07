---
ts: 2026-11-06T05:03:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_l1rN0PufSISlWwNZlIhv
---
The .greg order is "93 75 73 74" — pseudo r93 (pri 4285, refs 3, live 7, conflicts v0,sp), r75 (pri 3181, refs 14, live 132), r73 (2916, refs 7, live 48), r74 (857, refs 3, live 35).

So the highest-priority greg is r93 (4285) — that's probably `a2` (s2)? r75 (3181) is a1 (14 refs), r73 (2916) is base (7 refs), r74 (857) is a0.

Wait, the target has a1→s1, base→s0, a2→s2, a0→? The register assignment order: global-alloc assigns the highest priority first. The available s-regs: s0, s1, s2 (and s3?). In the target, a2 got s2 (the highest? r93=4285 conflicts v0,sp — a2 is used for beqz). Hmm.

The .greg order 93 75 73 74 means the allocation order is r93 first, then r75, then r73, then r74. r93 → s0? But the target has a2 (r93?) in s2. Hmm, the allocation order assigns registers in the order of REG_ALLOC_ORDER for MIPS: maybe s0, s1, s2... Actually, the global.c allocno_compare sorts by priority descending; then `reg_alloc_order` assigns the first free register. The MIPS REG_ALLOC_ORDER in 2.7.2: `{ 16, 17, 18, 19, ... }`? s0=16, s1=17, s2=18, s3=19.

But the observed: r93 (highest) got s2, not s0. That suggests the register order is s2 first? Hmm, or the allocno order line "93 75 73 74" is the .greg order, and the assignment uses `reg_alloc_order` which for MIPS might be s0,s1,s2,... Let me check the dump more carefully — maybe the alloc table's hard column shows the final assignment for the highest ones. r93 is "-" (unassigned in .lreg). Hmm, the table lists .lreg pseudos with their pre-reload hard regs.

Let me instead find the actual mapping: in the disassembly, which pseudo is s0? We know from the output: target a1=s1, base=s0, a2=s2. Mine: a1=s0, base=s1, a2=s2.

So the allocno order differs between the target (with asm) and mine. In the target: a1 (r75?) got s1 and base (r73) got s0. So base was allocated before a1 (higher priority). In mine, a1 before base.

The dump shows r75 pri 3181 > r73 pri 2916. So in *mine*, a1 (r75) has higher priority → gets s1? But mine has a1=s0! Hmm, maybe s0 is assigned first (lower number) to the higher priority. If r75 is first, it gets s0 → a1=s0. Yes! That matches mine. And r73 gets s1 → base=s1. And r93 (pri 4285) is first overall and gets... s2? That contradicts.

Unless r93 is not a2 but something else (the `at`? no). r93 has 3 refs, live 7, conflicts v0,sp — could be the comparison pseudo for `a2 != 0`? Hmm.

Wait, maybe the register assignment order is: r93 → s0, r75 → s1, r73 → s2? But the output shows a2=s2, a1=s0, base=s1. Let me identify r93. r93 is in .greg but has no hard reg in the .lreg table (it's a global allocno). The disassembly: s2 = a2 (`move s2,a2`), s1 = base (mine), s0 = a1 (mine). Hmm.

Maybe the .greg order is a *sorted* list but the actual assignment goes to `reg_alloc_order` which for MIPS is `s0,s1,s2,...`? Then r93→s0, r75→s1, r73→s2. That doesn't match either (a2=s2 would be r73).

I'm confusing myself. Let me directly map: the alloc table's "hard" column for the .lreg pseudos is the register assigned. r75/r73/r74/r93 are .greg (no hard). Their order in the .greg list determines assignment. The .greg order line "93 75 73 74" is probably the order of *allocation* (priority). If registers are assigned s0, s1, s2 in that order: r93→s0, r75→s1, r73→s2. But the disassembly says a2=s2, a1=s0, base=s1.

So maybe r93=a1, r75=base, r73=a2? Let me check: a2's refs: `beqz s2` twice, `move s2,a2` → 3 refs, live short → matches r93 (refs 3, live 7)! And a1: `move s1,a1` + 6 addu uses = 7+ refs... r73 has 7 refs, live 48 → a1! And base: r75 has 14 refs, live 132 → base (used 12+ times across the function).

So: r93 = a2 (3 refs, pri 4285), r75 = base (14 refs, pri 3181), r73 = a1 (7 refs, pri 2916), r74 = a0 (3 refs, pri 857).

Allocation order: r93 (a2) first → s0? But the output has a2=s2. Hmm. Unless the assignment order is s2, s1, s0? If the highest priority gets s2: a2→s2, base→s1, a1→s0. That matches mine exactly!

And the target: a2→s2, a1→s1, base→s0. So the target's order must be a2 > a1 > base: a2→s2, a1→s1, base→s0.

So in the target, a1's priority > base's; in mine, base's > a1's. The asm (memory clobber) somehow gave a1 a higher priority or base a lower one.

Priority formula (global.c allocno_compare):
```
i = (int) ((floor_log2 (allocno1->n_refs) * allocno1->n_refs) / (allocno1->live_length / 10 + 1));
```
Hmm, let me check the actual formula in global.c. r75: refs 14, live 132 → floor_log2(14)=3, 3*14=42, 42/(132/10+1=14) = 3 → pri 3? But the table says 3181. So the formula is different. Let me look at global.c:607 and the pri computation.

Let me read the relevant part of global.c.

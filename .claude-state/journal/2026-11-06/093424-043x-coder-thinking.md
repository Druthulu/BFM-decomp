---
ts: 2026-11-06T16:34:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gWSkC6slejlkzLR4Qe5G
---
So in c1, expand created:
- 72 = arg0 (the parameter pseudo, set from a0 at entry)
- 73 = self (pointer) = copy of 72.

So 73 (self) is a real pseudo used everywhere, and 72 is the parameter. Global-alloc: 72 conflicts with a0 (since insn 4 writes a0? no, reads a0; 72's live range starts at insn 4 where a0 dies, but conflict computed from... anyway) → 72=a1; 73 conflicts {72,73,2,3,29} not 4 → 73=a0. So self=73→a0 in the else and then both? But the then arm used a1 in the output... because in the then block, 72 vs 73? Wait the then block uses 73 as base too (insn 36 uses 73). Hmm, but output c1 then-arm used a1: `lw v1,32(a1)`. If 73→a0, then base should be a0 in then too. Unless global-alloc's assignment differs... "72 in 5 73 in 4" says 73 in 4 (a0). Hmm, then then-arm would be a0. But the score diff showed else a0 and then a1.

Wait, maybe I misread the c1 output. Let me look at the c1.s assembly.

---
ts: 2026-11-07T01:10:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pkhdql3YWL0ISpAcNLdQ
---
Interesting! Only TWO pseudos: r72 (4 refs, 6 insns, crosses 1 call, pointer) and r74 (4 refs, 5 insns, dies in 2 places).

The .greg order: 1 reg to allocate: 74. So r74 gets a hard reg (globally) and r72 doesn't (crosses a call — it gets a callee-saved via retry?).

Wait, "1 regs to allocate: 74" means only r74 is a global allocno. r72 crosses 1 call and... hmm, it's not in the order line? Maybe r72 is allocated locally (local-alloc) or it's the param.

The final asm: $16 is used (callee-saved) — so the pointer that crosses the call got $16 via... hmm, global alloc allocated only r74. r72 (crossing a call) should need a callee-saved reg too.

Let me look at the full .lreg and .greg dumps for this function to understand. Let me view the sections.

Actually, let me use alloc_table.py (it reads both).

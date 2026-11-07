---
ts: 2026-11-06T15:49:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ugEWdJFODihpT1Z7SWH4
---
Let me look at 5300-5320 — the comment says "The target loads &D_800AF648 afresh (lui/addiu $a0) for EACH call. The ..." and uses an alias declaration `extern u8 D_800AF648_b __asm__("D_800AF648");`. Interesting — a different symbol declaration for the same address breaks cse's equivalence! Because the SYMBOL_REF... hmm, actually with an asm label alias, the tree decl is different but the symbol name is the same; gcc creates the same SYMBOL_REF by name. Hmm, but maybe not — let me read that comment.

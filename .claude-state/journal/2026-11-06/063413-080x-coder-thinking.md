---
ts: 2026-11-06T13:34:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Is8zWm9kRTGRChTEuvcH
---
In the flow dump, insn 291 (a1 = fp+16) still exists at line 23899 (function region). In the combine dump, it's GONE — so `combine_instructions` deleted it and moved the addiu to 310. Combine does global dead-code elimination via `delete_dead_insns`? Actually combine has a "dead code elimination" pass at its start (`delete_dead_insns`? In 2.7.2 combine_instructions starts with... hmm, `combine_instructions` calls `delete_dead_insns`? Let me check combine.c).

Actually, combine_instructions in 2.7.2 has a pre-pass that deletes insns with dead results: `delete_dead_insns`? There is `delete_dead_insns` in combine.c? Let me grep.

If combine deletes 291 because a1 is set again (by the no-op at 312, which combine turns into the addiu) before any use... Then in orig, the asm between them prevents combine from seeing 291 as dead? Combine's dead-code pass: it computes "reg_last_use"? Hmm.

Wait — combine_instructions' dead code elimination: in gcc 2.7.2, combine.c has a function `delete_dead_insns`? Let me grep.

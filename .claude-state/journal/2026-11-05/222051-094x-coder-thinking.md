---
ts: 2026-11-06T05:20:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3zZrV1NcrgHuGAuDcYTK
---
The grep counts aren't informative. Let me instead check whether the dead stores are removed at flow or cse. In the flow dump, count the `(mem:HI (plus (reg 29) (const_int 24)))` sets. Let me grep for "const_int 24" in the flow and cse dumps.

Actually, a faster approach: `flow` in gcc 2.7.2 does run `dead_code` elimination. Let me check if flow removes dead stores to stack slots. In flow.c, `mark_used_regs` marks insns that have side effects; a store to memory is always needed (unless it's to a dead stack slot — flow does have code to delete stores to dead stack slots? There's `dead_debug_insns`...).

Let me search flow.c for "delete_insn" and "store".

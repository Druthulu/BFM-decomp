---
ts: 2026-11-06T11:46:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FS9XaiXWofQGOmGfZVEn
---
Still 18/31 ins. The struct reload didn't force the reload either. Hmm. Maybe because the top read is also... wait, the top read is scalar `*(s16*)(a1+0xD0)`, and the else read is struct-member. But the compiler may have CSE'd them because... let me check the disassembly. Maybe gcc folded the struct member to the scalar read anyway, or the struct member read got the same hash.

Actually, wait — maybe cse's hash_arg_in_struct is only used to decide whether a store aliases, not whether two loads equate. Let me check exp_equiv_p for MEM. Let me read cse.c exp_equiv_p MEM case.

Let me read around line 2051-2140.

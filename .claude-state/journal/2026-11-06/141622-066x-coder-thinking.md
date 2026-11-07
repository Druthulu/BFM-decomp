---
ts: 2026-11-06T21:16:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tY3Q5W9rGogUTApYJbWW
---
Note: `allocno_order` is sorted, but the `dump_conflicts` prints the order. But the dump line "12 regs to allocate: 78 108 ..." — is it printed BEFORE or AFTER sort? dump_conflicts is called after qsort. Let me check line 1652 context — it prints `allocno_reg[allocno_order[i]]` for i=0..max_allocno. So yes, sorted order.

But wait — the qsort comparator returns pri2-pri1 (higher priority first). For e (pri 0.5) vs off (0.375), e should come before off. Unless allocno_live_length for e is not 4. The flow dump line 18 says 4 insns. Hmm, but allocno_live_length is the MAX over pseudos in the allocno. If e's allocno includes other pseudos tied by copies (e.g., a hard-reg copy?), the live length could be larger and n_refs summed.

Actually — e has REG_EQUIV. In global-alloc, REG_EQUIV pseudos might be tied to a hard reg or handled specially. Hmm.

Also, note the printed order includes reg 79 LAST. But maybe reg 79's allocno is shared with another pseudo whose live length is 72! Line 1025 "Register 79 used 3 times across 72 insns" is a DIFFERENT function. Not ours.

Wait, could the flow dump be per-function but the function order in the TU means line 12-42 is NOT func_8017E590? Let me check the flow dump structure: it prints ";; Function <name>" before each dump? Let me grep "Function" in cand.i.flow around lines 1-50.

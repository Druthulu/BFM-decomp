---
ts: 2026-11-06T21:06:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1aTBdjvvOTDqGEvQ0Fj4
---
No REG_ALLOC_ORDER in config/mips. So find_free_reg iterates i=0..FIRST_PSEUDO_REGISTER and regno=i. So order 0,1,2,... For MIPS, reg 0=$zero, 1=$at, 2=$v0, 3=$v1, 4-7=a0-a3, 8-15=t0-t7, 16-23=s0-s7.

But it skips fixed regs, class constraints. The first free suitable reg in 0..N order. $at (1) is in fixed_reg_set? at is used as scratch, likely fixed. v0/v1 (2,3) live → used. Then a0 (4). So the first allocated qty gets a0, second gets a1.

So mine allocates off first. Target allocates e first. So e has higher priority in target. 

Given my calc says e should be higher in both, but it's not in mine, my live_length assumption is wrong. Let me actually look at the .flow dump which might show reg_n_refs/live_length. Actually the flow dump doesn't print those.

Hmm, wait. Maybe local-alloc's `qty_live_length` and the sort only apply to qtys with n_refs... Let me re-read the priority formula lines 1579-1600.

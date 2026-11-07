---
ts: 2026-11-06T13:27:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2RfjLeAIxJGF2hxmgds4
---
No sp references after 25540? Maybe the stack pointer is expressed differently. The `buf` array is at sp+16. Let me search "plus:SI (reg:SI 29" without the paren.

Wait, the sched1 dump is BEFORE register allocation (sched1 runs before local_alloc), so the stack pointer is `sp` and the array is addressed as `(plus (reg/v:SI ...) ...)` — buf is a pseudo (virtual stack slot) at this stage! Indeed `buf` is a local array; before instantiate_virtual_regs? No — instantiate_virtual_regs runs before jump/sched1, so sp references exist. Hmm, but local arrays are addressed via `(reg/f:SI 29 sp)`? The frame pointer... In the dump I saw `(reg:SI 30 $fp)` at line 20438 (a different function).

Let me search for "sp" in the function's listing range. Actually the addiu a1,sp,16 must appear as `(set (reg:SI 5 a1) (plus:SI (reg/f:SI 29 sp) (const_int 16)))` or via a pseudo. Let me grep "a1)" lines after 25540.

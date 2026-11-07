---
ts: 2026-11-06T10:23:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IZ9p7DDP5aOfXrekKX56
---
This is getting deep. Let me take a more direct approach: extract the .sched and .sched2 instruction order for the function and see the position of the unk1C store (const_int 28) relative to the stack address insns (addiu sp+48 / sp+56).

Actually, simpler: the sched dump is the RTL after sched1. Let me find the insn that stores to (plus reg72 const_int 28) — unk1C is 0x1C=28. Wait, but a0->unk1C is offset 28. And the store to unk28 (0x28=40) is different.

Hmm, wait — earlier I determined the moved store is `sw v0,28(s2)` = unk1C. Let me confirm in the .sched dump: find the store with const_int 28 and see if the address setup (which in RTL is `(set (reg a0) (plus (reg sp) (const_int 48)))`) comes before or after.

Let me print the sched dump around the store with const_int 28.

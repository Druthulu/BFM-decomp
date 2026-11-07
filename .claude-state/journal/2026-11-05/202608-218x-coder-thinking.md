---
ts: 2026-11-06T03:26:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DejYvLzxKo8E44diOHqI
---
Look: the second D_80126B78 load (insn 76) is AFTER the store (insn 73) — good. The first load is at insn ~? (line 45/117). The store at insn 73 has address `(plus (reg/v:SI 73) (const_int 20))` — a PLUS → nonscalar only → doesn't invalidate the scalar global. That's why no reload.

Wait, this is the ORIGINAL source form `*(u16*)(obj+0x14)`. For s1 (pointer q), the store's address should be (reg q). Let me check s1's RTL. Actually the dumps_nopin is for nopin. Let me dump s1 and check. But first: the store address in nopin is a PLUS, so nonscalar → the global entry isn't invalidated.

For s1, the store via q should be (mem (reg q)) → all=1. Let me verify by dumping s1's .rtl and .cse.

---
ts: 2026-11-06T11:44:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5UD2ztzHOiPznpSxB1L8
---
No rtl.c. `rtx_equal_p` is in rtl.c (not present). Hmm.

Let me test empirically: make the first read a struct member access and see if cse still forwards. If MEM_IN_STRUCT affects equality/hash, the second load would be a reload with no store needed.

Define a local struct: `struct P { char pad[0xAE]; u16 f; };` then `bb = ((struct P *)(s32)p)->f;`. The address is `(plus (reg) (const 0xAE))` with MEM_IN_STRUCT. The second read is a plain `*(u16*)` with MEM not in struct. If rtx_equal_p compares the in_struct bit → no match → 2 loads!

Actually hash_rtx: `hash += (unsigned) MEM; x = XEXP(x,0);` — the in_struct bit isn't hashed. But `lookup` then compares with `rtx_equal_p` or `exp_equiv_p`. In cse's `lookup`, it compares `exp_equiv_p (exp, elt->exp, ...)`? Let me check lookup.

Actually in cse.c, `lookup (x, hash, mode)` walks the chain and uses `exp_equiv_p (x, p->exp, 0, 0)`. And exp_equiv_p for MEM: let me read it.

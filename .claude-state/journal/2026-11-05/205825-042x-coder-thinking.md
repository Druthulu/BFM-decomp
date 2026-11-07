---
ts: 2026-11-06T03:58:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Uqp3DBQO1luChwbJcMsY
---
`rtx_addr_varies_p` returns true if the address contains a register that isn't fixed. For `s0 + 14`, s0 is a pseudo → varies = true. So load entries at 0x2E(s0) are removed by ANY nonscalar store. But the store at 0xE(s0) happens AFTER both loads in source order, so it doesn't matter for the second load... unless the store comes before the second load.

Hmm. Wait — but cse processes the function in a "basic block" with a scan; loads are recorded, then at the store, entries are invalidated. So if the store to 0xE(s0) occurred between the two 0x2E loads, the second load would not be forwarded. But source order has both loads then the store.

Unless we restructure the C so that the store happens before the second load:
```
u16 old = *(u16*)(s0+0xE);       // load 0xE
*(u16*)(s0+0xE) = old;           // store (same value) -- dead? but emitted
x2 = *(s16*)(s0+0x2E);
*(u16*)(s0+0xE) += (x2<<6);
```
That adds an extra store.

Alternatively, exploit the call: the function calls func_80182654 before the diff block. invalidate_for_call clears loads, but that's before.

Hmm. Maybe the original source had a store in between that we're missing because the decompiler folded it. Let me look at the actual ROM target again: between the first lh (77cc) and the second lh (77d8), there's `lhu v1,14(s0)` at 77d0 and `subu` at 77d4. No store. So the store theory is out.

So how did the original compiler NOT forward? Maybe the two accesses had different MEM_IN_STRUCT_P and cse treats them as different hash entries. The hash function: `hash += (unsigned) MEM; x = XEXP(x,0); goto repeat;` — the hash does NOT include in_struct. But the hash_arg_in_struct flag is used in `insert` (line 1488: new->in_struct = hash_arg_in_struct) and in invalidation. Lookup compares expressions via `rtx_equal_p`? Let me check how table entries are matched: cse_insn uses `lookup`? Let me look at `hash_cse_reg_info`... Actually the table is a hash table keyed by hash value with `next_same_hash`, and matching uses `exp_equiv_p` (rtx_equal_p). If rtx_equal_p for MEM ignores in_struct, then they'd match regardless. Let me check rtx_equal_p in rtl.c or rtlanal. Hmm.

Wait, but there's another mechanism: `fold_rtx` and the qty_const table. When cse processes a load, it records the load's value in the table as the MEM expression. When it processes a second identical MEM, it replaces it with the first's register. The hash is the same; the entry match uses `exp_equiv_p (p->exp, x, 1)` or similar. If exp_equiv_p compares MEM_IN_STRUCT_P? Let me grep exp_equiv_p for MEM.

---
ts: 2026-11-06T03:57:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_orO1xzQeCGdeVfxbYqTZ
---
So invalidate_memory removes entries only if:
- all (a store to an unknown/aliasing scalar address), or
- nonscalar && p->in_struct (store is nonscalar and the entry is in_struct), or
- the entry's address varies (array element).

For a store to `0xE(s0)`: `cse_rtx_addr_varies_p(written)` — address is `(plus (reg s0) (const_int 14))`, not varying (varies means contains a register that varies? Actually cse_rtx_addr_varies_p returns true for addresses that are sums with registers? Let me read). If addr varies → writes_ptr->nonscalar=1 (and possibly all). If the address is a PLUS, then `(MEM_IN_STRUCT_P || GET_CODE(XEXP)==PLUS) && mode != QImode` → doesn't set all, sets nonscalar. So a store at 0xE(s0) has PLUS address → nonscalar=1, all not set. Then invalidate_memory removes entries with in_struct=1 (struct loads) or varying-address entries. Our loads at 0x2E(s0) have PLUS address → cse_rtx_addr_varies_p(p->exp)? Let me check that function. If it's true for any PLUS, then the load entries get invalidated by ANY nonscalar store. Let me read cse_rtx_addr_varies_p.

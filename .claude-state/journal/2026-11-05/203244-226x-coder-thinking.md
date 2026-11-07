---
ts: 2026-11-06T03:32:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ylz5Z6ZMrSOqwRfRP0xO
---
Mine's shape:
- 5298: lui a2; lw a2 (D_80126B78) — loaded once at 5298, AFTER the call, before the obj store.
- 52c0: lhu a0,18(a2) — first use
- 52d0: store obj+0x14
- 52d4: lhu v0,18(a2) — second use, reusing a2 (no reload!)

Target:
- 52b4: lui v0; lw v0
- 52c0: lhu a0,18(v0)
- 52d0: store
- 52d4: lui v0; lw v0 (reload)
- 52e0: lhu v0,18(v0)

So mine caches a2 across the store; the target reloads. cse's store invalidation didn't remove the a2 entry because the store's address is a PLUS (nonscalar) → the scalar global entry survives.

Wait, but in mine the value is in a REGISTER a2 (the load's pseudo was assigned a2), not a memory table entry? At cse1 time (pre-alloc), the load's pseudo 90 is in the table; the store invalidates memory entries based on the address. The D_80126B78 load is `(mem (symbol_ref))` — a memory entry with `in_struct`? The global is `s32 *D_80126B78` — a scalar variable, so in_struct=0. The store's write_data: address is (plus obj 20) → the condition `!((MEM_IN_STRUCT_P(written) || GET_CODE(addr)==PLUS) && mode != QImode)` → MEM_IN_STRUCT=0 but addr is PLUS → the inner condition is TRUE → so `all` is NOT set; nonscalar=1. invalidate_memory: removes entries with `nonscalar && p->in_struct` (p->in_struct=0) or `cse_rtx_addr_varies_p(p->exp)` (the symbol_ref doesn't vary) → NOT removed. So the entry survives → the second load is CSE'd. Exactly.

To force removal, the store must set all=1: the address must NOT be a PLUS. We tried pointer q; but cse may fold q into a PLUS. Let me verify whether the q store's RTL address is a PLUS. Let me dump s1's RTL properly with the correct scratch. The scratch dir issue: let me check the --keep output dir for s1 now and grep the RTL for the store.

Actually, the p4 dir has s1 (4 "u16 *q"). Let me dump p4 and grep for the store to (reg ...) around the obj store.

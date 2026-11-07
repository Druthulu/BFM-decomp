---
ts: 2026-11-06T03:22:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kVdTz7cXzxMpkkgBCzUA
---
In the RTL, there are 3 references to D_80126B78 (the pointer): one for the call arg (D_80126B78+0x34) and two for the unk12 loads. After cse1, 2 references (one of the unk12 loads was CSE'd away). So cse1 forwarded the second load to the first.

The target needs both loads (3 references total: the call arg + 2 loads). The barrier prevented cse1 from forwarding.

So we need to prevent cse1 from forwarding the D_80126B78 load across the store to obj+0x14. cse1's memory invalidation on the store: the store's address is (plus (reg obj) 20) — a varying address; the global's address is (symbol_ref D_80126B78). cse's `invalidate_memory` uses `write_dependence_p (mem, x, ...)`. For a fixed symbol vs a varying pointer, `fixed_scalar_and_varying_struct_p` determines: if the stored MEM is not in a struct (MEM_IN_STRUCT_P=0) and the loaded is a fixed scalar, they're considered non-aliasing → no invalidation. With a struct store (MEM_IN_STRUCT_P=1), they may alias → invalidation.

But r1/r2/r3 (struct store) still gave 56. Hmm — maybe the struct store didn't become MEM_IN_STRUCT_P=1 because the cast `(Sub20_1CDC *)obj` where obj is an s32... The C front end sets MEM_IN_STRUCT_P based on the type of the lvalue: a struct field access → in_struct. Let me verify by dumping the RTL for r1: check whether the store is mem/s.

Let me dump r1's .rtl and grep the store. Actually, easier: check the score again and dump. Let me dump r1 quickly and check the mem flag.

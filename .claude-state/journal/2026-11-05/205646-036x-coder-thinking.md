---
ts: 2026-11-06T03:56:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Elp8lCJmOezThPBuF9Cc
---
Mine: single lh v1,46(s0), then `sll v1,v1,0x6` reusing the same value (cse forwarded). Target: two lh.

So the ONLY difference (score 8) is the second load and register numbering (v0/v1 swap). Target uses v0 for the x2 load and v1 for the += load; mine uses v1 for 0x2E and v0 for 0xE.

So need cse to NOT forward. Real C move?

Option: make the second load through a pointer that cse cannot see as the same. E.g., store s0 in a volatile-ish way? No.

Option: add a real store between the two loads that cse can't prove doesn't alias 0x2E. What store exists between? The `+=` store is after. But what if we reorder C so that the store `*(u16*)(s0+0xE) = ...` is computed with a load before the second 0x2E load, and the store... still after.

Wait, cse's load forwarding: it records a load's value in the hash table and, when it sees a store that might alias, it invalidates the corresponding entries. If the `+=` store to 0xE(s0) is between the first 0x2E load and the second 0x2E load in RTL order, cse would invalidate the 0x2E load entry (if it thinks they may alias). Does cse consider `0xE(s0)` and `0x2E(s0)` as possibly aliasing? GCC's cse uses `expressions`/`canon_reg`; for MEM, it hashes the address expression. The invalidation: in cse_insn, when processing a store, it walks the table and for entries with MEM, uses `exp_equiv_p`/`rtx_equal_p`? Actually cse_main's `cse_insn` for a store: "invalidate any table entries whose addresses may be affected". It uses `true_dependence` / alias checks? In GCC 2.7.2 cse.c, `invalidate_memory` compares `XEXP (x, 0)` addresses with `rtx_equal_p`? Let me read the source at tools/reference/gcc-2.7.2/cse.c. That's allowed now. Let me grep for invalidate.

But even if cse invalidates, the store is AFTER both loads in source order. Unless we reorder: put the `+=` store's load and store before the second 0x2E load? But then the value added would need the 0x2E load first... circular.

Unless we split: `u16 old = *(u16*)(s0+0xE); *(u16*)(s0+0xE) = old + ...;` — the store needs the value.

What about a DEAD store to a possibly-aliasing address between the two loads? The dead-reset trick (C0414) uses a store that is dead in RTL? Actually the dead-reset in moves: "dead copy vol2=vol + a 2nd def vol=vol|0x3000 (both dead in the RTL)" — it's a dead *register* assignment, not memory. For memory, a dead store would still be emitted unless DSE removes it. GCC 2.7.2 has no DSE (dead store elimination came later, maybe). So an extra store would show as an extra instruction — but maybe it could be eliminated by sched? No.

Hmm. Wait, maybe the target's double load is not from cse but from *reload*: the value is needed twice but the register got clobbered? In target, the first load's value is used by subu at 77d4; the second load at 77d8. If cse had forwarded, it would be `sll v0,v0,0x6` using the same pseudo; that's what mine does. So target really has a reload → cse didn't forward → there was a memory barrier or a store.

What store could be in the original between? Let me look at the actual target code between 77cc and 77d8: `lhu v1,14(s0)` at 77d0. That's a LOAD of 0xE, not a store. So no store.

So the original compiler didn't forward the load without any barrier? That means in the ORIGINAL source, the two accesses were not recognized as the same expression. Possibly because one is a `s16` field of a struct at a different offset representation, e.g., the struct has a union? Or because one access is through a `char*`/different mode?

Wait — maybe the first load is not from s0+0x2E but from a different base that happens to be s0+0x2E in the final code. E.g., `self->unk2E` where self = `(u8*)s0` vs `s0->unk2E` where s0 is `s32*`: address computations differ in RTL before folding. GCC's cse hashes RTL after expansion; constant folding makes `(u8*)s0 + 0x2E` and `s0 + 0x2E` both `(plus (reg) (const_int 46))`? For s32* + 0x2E: the front-end computes byte offset = 0x2E*4 = 0xB8, not 0x2E. Wait! The current source uses `*(s16 *)((s32)s0 + 0x2E)` — byte arithmetic on the s32 cast. If the original used a `u8*` or a struct pointer, the offset expression would be `+ 0x2E` bytes anyway.

But what if the first uses `((s16*)s0)[0x17]` (index 23) → byte offset 0x2E. Same RTL after folding.

What if the two accesses have different *signedness*: one is `*(s16*)` and the other `*(u16*)`? cse records MEM with mode HImode; sign doesn't affect mode. But GCC's cse distinguishes MEMs by `MEM_IN_STRUCT_P` / `MEM_SCALAR_P`? In old GCC, `MEM_IN_STRUCT_P` and `MEM_ALIAS_SET`/`MEM_UNALIGNED`... In 2.7.2, MEM had MEM_IN_STRUCT_P flag (a bit in the rtx). cse's `exp_equiv_p`/hash for MEM might include this flag? Let me check cse.c's `hash`/`rtx_equal_p`. In GCC 2.7.2, `rtx_equal_p` for MEM compares XEXP and MEM_IN_STRUCT_P? Let me look.

Actually a classic trick: accessing through a struct pointer sets MEM_IN_STRUCT_P = 1, while a cast to `s16*` sets 0. If cse's table distinguishes them, two loads at the same address with different MEM_IN_STRUCT_P won't be merged! That's a real C-level distinction (struct field vs raw pointer cast). This is promising.

So: first access via `((Unkstruct_800B5CB8 *)s0)->unk2E` (struct member → MEM_IN_STRUCT_P=1), second via `*(s16*)((s32)s0 + 0x2E)` (raw → 0). Then cse won't forward.

But wait, the current source uses raw casts for both. In target the first `lh v0,46(s0)` is from the diff block. Let me check the target's code around: `diff -= *(s16 *)((s32)s0 + 0x2E);` and `x2 = *(s16 *)((s32)s0 + 0x2E);`. Both raw → same. Hmm, so the barrier is what stopped it.

If we change ONE to a struct access, would the instruction stream stay the same? The address computation is identical (lh 46(s0)); only MEM_IN_STRUCT_P differs. Let's test: change the second (x2) to `((Unkstruct_800B5CB8 *)s0)->unk2E`. But is `unk2E` a field? The struct Unkstruct_800B5CB8 has unk2C, unk2E? Let me check the struct definition. It has unk1A, unk18, unk12, unk20, unk27, unk2C... maybe unk2E exists. Let me grep.

Actually simpler: cast to a struct with s16 at 0x2E. Let me check Unkstruct_800B5CB8 definition.

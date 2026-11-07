---
ts: 2026-11-06T05:25:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eeeNrgP2G8SbwYUKjHPx
---
No virtual stack refs. So the 16-byte frame comes from `assign_stack_temp`/`assign_stack_local` somewhere that isn't visible in the RTL (because the temp is freed and not referenced).

`assign_stack_temp` calls in the compiler: `expand_asm_operands` (outputs/inputs), `expand_call` (outgoing args?), `store_expr` for struct copies (line 3736), `expand_builtin`, etc.

Our body has no calls. Hmm. But `__builtin_memcpy`? no.

Wait — maybe the `(mem:BLK (scratch))` clobber is expanded in `expand_asm_operands` and then `free_temp_slots()` is called. If a temp slot was allocated earlier (e.g., for the struct `D_800AE7BC[*q]` access), `free_temp_slots` frees it but the frame remains. And the temp allocation might be conditional on the asm... Hmm.

Actually — maybe the 16 bytes are `assign_stack_temp (BLKmode, 16)` for the asm's *clobber of memory*: in `expand_asm_operands`, for a memory clobber, does it allocate a temp? Let me look at the code around where the memory clobber is created (line ~1650).

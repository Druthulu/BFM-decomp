---
ts: 2026-11-06T05:46:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cu8LHbMg283pEeLCzCF1
---
`rtx_addr_varies_p` is not in the reference sources (only a few files are present). It's in rtlanal.c which isn't provided. Let me reason from the observed behavior: the lever-free version reuses the `*q` value across the store, so the entry is NOT invalidated. Since `cse_rtx_addr_varies_p` on the SIGN_EXTEND returns `rtx_addr_varies_p(x)`, and the entry survives, rtx_addr_varies_p must return 0 for `(sign_extend:SI (mem:HI (reg q)))` where q has a known constant? Or maybe the hash table entry is the *mem* expression, not the sign_extend.

Hmm. Actually, in cse, when processing a load `set (reg v0) (sign_extend:SI (mem:HI (reg q)))`, the src is the sign_extend expression. `insert_regs`/`insert` record it. But cse also "simplifies" and may record `(mem:HI (reg q))` as a subexpression? The `hash_arg_in_memory` flag is set if the expression contains a mem.

Whatever. The point: the wall is real and the mechanism is `cse-fixed-global-cache`.

Now — can we exploit the `p->in_struct` path? If the *load*'s memory expression were marked MEM_IN_STRUCT_P, then the nonscalar store would invalidate it. How could `*q` be in_struct? If q pointed into a struct... q = &D_800B9A02. If we declare D_800B9A02 as a member of a struct and load via `s->field`, the MEM would be in_struct → invalidated by the nonscalar store → reload! But the load address is a fixed symbol; the memory ref would be `(mem:HI (plus (symbol_ref D_...) (const_int 0)))` with MEM_IN_STRUCT_P set.

Hmm! But the target's reload is `lhu v0,0(a2)` where a2 = the symbol address. If we make the load a struct member, the codegen might still be `lhu v0,0(a2)`. And cse would invalidate it after the nonscalar store → reload.

How to make it in_struct? Declare a struct type and cast: e.g., `extern struct { u16 v; } D_800B9A02;` then `q = &D_800B9A02.v; *q` — the load `*(u16*)&D_800B9A02` might be in_struct if the expression is `D_800B9A02.v`. But `q = (u16*)&D_800B9A02.v; ... *q` — the load is through a pointer q; GCC's MEM_IN_STRUCT_P is set based on the expression used to build the MEM. If the load is `*q` (q is a plain u16*), MEM_IN_STRUCT_P is false. To get in_struct, the load must be written as a struct member access: `D_800B9A02.v` or `((S*)q)->v`.

But the source uses `*q` where q = (u16*)&D_800B9A02. If instead we write the loads as `*(u16*)&D_800B9A02` each time... hmm, a direct global access `D_800B9A02` (s16) yields `(mem:HI (symbol_ref))` — is that in_struct? No (a scalar decl). But it's a *non-varying* address: `cse_rtx_addr_varies_p` returns 0 for a symbol_ref? `rtx_addr_varies_p` on a fixed symbol address returns 0 → scalar → not invalidated. Same problem.

Hmm, what if the load is through an *array element* with a variable index? Then the address is a PLUS and varies → invalidated by the nonscalar store! But D_800B9A02 is a single s16; there's no index.

What about making the *store* all-invalidating instead? The store `ptr[2] = ...` is `(mem:SI (plus (reg) 8))` → nonscalar. If we could make the store's address not a PLUS and not in_struct → all=1 → invalidates everything. E.g., store through a plain pointer `*ptr = ...` — but the address is +8.

What if we use a struct member store `ptr[2]` where ptr is `u32*`? Already.

What if the store is written as `*(u32*)((u8*)ptr + 8)`? Same PLUS.

Hmm, what about `((S_AE7BC*)ptr)->pad[1]`? Still PLUS.

What about making the store a *whole-struct* assignment? `*(S*)ptr = ...` with S a 12-byte struct? That's BLKmode → `all=1`! But the source stores only one word (`ptr[2]`).

Hmm, what about a QImode store? A QImode store at a PLUS address → all=1 (because the condition requires mode != QImode). But we don't store QImode.

So the cse wall is solid.

Now, the frame: target vars=16 (unused), nobar vars=0. Could we produce a 16-byte unused frame in pure C? Earlier, item 1's nobar had vars=40 (16 extra) vs target 24 — so the extra 16 was a reload spill slot. If we could make a pseudo spill and die, we'd get an unused 16-byte slot. But the target's frame has it *with* the clobber and the lever-free body doesn't. Hmm, opposite directions.

Wait — for the family, the target (clobber) has vars=16 and the lever-free has vars=0. The clobber *creates* the 16-byte frame. So even if cse were fixed, the frame would differ. Both artifacts come from the clobber.

Is the 16-byte frame from reload (a spill slot for a pseudo not allocated a reg)? If so, a lever-free body might create the same spill with different register pressure. Let me check the family's nobar object for any spilled pseudo... nobar vars=0 means no spill slots. So the clobber causes a spill slot of 16 bytes (probably a BLKmode/DImode pseudo, or 4 pseudos).

Hmm, 16 bytes with no accesses. Maybe the memcpy? There's no memcpy in the family.

Actually, wait: for the family, the frame is 16 with the clobber. In the *object* disassembly of the orig body, the `addiu sp,sp,-16` is placed mid-function and nothing accesses 0(sp). So a spill slot allocated but unused.

What pseudo could be 16 bytes? Maybe the `(mem:BLK (scratch))` clobber itself gets a stack slot in reload (as a "memory operand" that reloads). Hmm, reload might allocate a spill slot for a pseudo that is used in the asm... but there are no operands.

Hmm, actually: maybe the 16-byte frame comes from `assign_stack_local(BLKmode, 0, 0)` in reload1.c:663 — let me check that context.

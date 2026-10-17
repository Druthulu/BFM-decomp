---
ts: 2026-10-17T16:11:35.199Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm reconsidering the alias analysis — since work is a 32-bit arithmetic offset cast to a pointer, GCC's memrefs_conflict_p logic might treat a symbol_ref against a register-plus-offset as indeterminate, forcing a conflict unless the loaded value is actually being kept live in a register.

I'm also chasing the MEM_IN_STRUCT_P special case: GCC 2.x's cse invalidation has a carve-out where a store through a varying (register-based) address doesn't conflict with a scalar fixed-address reference if the store is marked as being into a struct, so I'm checking whether either of my two pointer dereferences would actually qualify as "in-struct."

I'm recalling that note_mem_written classifies stores as sp, var, nonscalar, or all based on address type, and invalidate_memory only clears nonscalar entries unless "all" is set, which should still wipe out D_801BFCDC for non-struct stores — yet my case isn't reloading, so maybe the held value isn't coming from CSE's memory tracking at all but from a register that was never invalidated for some other reason tied to how the subtraction and load are structured.

Maybe the discrepancy is about instruction ordering instead — comparing where the D+0x62 load falls relative to the unkE store in my asm versus the target's to see if they're scheduled differently.

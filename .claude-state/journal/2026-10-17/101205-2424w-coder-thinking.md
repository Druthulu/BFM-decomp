---
ts: 2026-10-17T16:12:05.427Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm checking the diff around lines 50-62, comparing where the store happens relative to the lhu at offset 98 using a1. It looks like my version keeps the store before the reload, meaning the compiler's CSE didn't invalidate that memory location on the earlier store — so the store to s1+14 isn't treated as aliasing.

I'm trying to recall the exact alias logic from gcc 2.7's cse.c, specifically the write_data struct with sp/var/nonscalar/all flags and how note_mem_written decides which category a memory write falls into based on its address form.

Thinking through the practical implication: a store to a struct sets nonscalar, which wouldn't invalidate a fixed-address scalar variable — this could explain why a particular variable like D_801BFCDC survives the invalidation unexpectedly, which seems relevant to the pointer dereference I'm analyzing.

Actually, I'm now suspecting the real reason is an older gcc heuristic where MEM_IN_STRUCT_P gets marked whenever the address is a pointer plus a constant offset, which would apply directly to the dereference pattern in question and could explain the lack of a reload.

So the workaround would be to break the direct arithmetic by assigning the computed address to a plain pointer variable first, since dereferencing a pointer held in a variable shouldn't trigger that same in-struct marking at expand time.

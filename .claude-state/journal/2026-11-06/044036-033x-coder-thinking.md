---
ts: 2026-11-06T11:40:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_w37GRGjXtG6WahvRteN2
---
The table persists across basic blocks (no flush at each block). CSE crosses EBBs when following jumps. So the memory entry survives across the branch.

So a do-while(0) may not help unless it creates a jump that cse follows differently. C0535 says do-while(0) splits cse1 EBB — presumably because cse_end_of_basic_block stops at the label and the jump-target block is processed with the table still holding... hmm, but the table isn't flushed.

Actually the C0535 move worked for a sched1-birth-order item, not necessarily cse memory.

OK, let me think about a *store* to break the memory entry. Real C store between the first read and the second. What if we store to the same location a value that's already there? That would emit `sh` — extra insn. Unless combine/flow deletes it. Let's think: `*(u16*)(p+0xAE) = bb;` right after loading bb. cse processes: load bb into reg, then store the same reg back to the same address. cse's store handling: it records the store as setting memory; but does cse eliminate a store of the value it just loaded from the same address? In cse.c, `cse_insn` for a store checks if the value is already known to be in memory (it tracks `(mem)` equivalences for the source). It has a "store to the same value" elimination? There's `cse_insn`'s handling of `sets[i].dest` with `MEM`: it looks up the source in the table and if the source is already in memory at the same address, it may delete the store. That's the "store 0 to 0" case? Let me check for "sets[i].src_elt" with dest memory.

Actually there's a known cse optimization: "store to the same memory location of the value already there" is NOT generally eliminated because of potential aliasing. But `*(u16*)(p+0xAE) = *(u16*)(p+0xAE);` — cse could see the load and the store to the same address with the same value and delete. Hmm, if it deletes, we lose the invalidation (but the store would have been deleted by cse itself, meaning the memory entry stays).

Wait, but we want the *second* load to not be forwarded. If cse deletes the store but still invalidates the memory entry, we win! cse's invalidate happens when it processes a store (it calls invalidate_memory unless the store is to a known-constant address etc.). Let me check: in cse_insn, for a SET to a MEM, it calls `invalidate_memory` with writes info. Even if it later deletes the store? Deletion happens after.

Hmm, order in cse_insn: it processes sets, and for a store to memory it calls invalidate_memory early (in the loop over sets, when it sees the dest is MEM). Then it may decide the store is redundant. Let me look.

Alternatively, a store to a *different* address that aliases (unknown base): `*(u16*)(iVar5 + 0x12) = something;` early. But then that store appears in code (the target's store is at the end).

Hmm! Actually, what about moving the target's own store earlier? No, changes order.

What about a store to a local variable's address? e.g. `s32 dummy; *(s32*)&dummy = 0;` — that's a stack store, would appear (or be deleted by flow later? cse runs before flow, so the store stays in cse's view and gets deleted by flow if dead). But a store to a stack slot generates `sw` — if flow deletes it, fine. But cse would see the store and invalidate all memory entries (nonscalar store to an unknown address? A store to a stack slot has a known base (fp/sp) and is scalar → cse's invalidate uses `writes->all` etc. A scalar store to a stack slot: does it invalidate `*(u16*)(p+0xAE)`? cse's invalidate_memory with `all=0`? Let's check how cse decides `writes->all`.

In cse_insn, for each store:
```
      /* Set the writes information.  */
      writes.all = 0; writes.nonscalar = 0;
      ...
```
Let me look at the code around invalidate_memory calls.

Actually, a simpler known trick: `*(u16*)(p+0xAE)` read then a store to `p+0xAE`... 

Let me look at how cse decides to invalidate.

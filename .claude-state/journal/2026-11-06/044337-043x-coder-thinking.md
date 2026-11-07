---
ts: 2026-11-06T11:43:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_16TCSPUfX7hHp820QiBD
---
The diff file only had ~30 lines. The diff shows the store `sh v1,16(sp)` at mine[50] and the frame size difference, and the j offsets. So the rest matched! That means t1 has the 2 loads and the correct code except for the dead store and the frame.

So the mechanism works: the store invalidates the memory entry (nonscalar), and the second load reappears. Wait, but the first load isn't in-struct. Hmm — but the invalidation happened anyway. Let me check: the store `*dp = (u16)bb` — dp = dummy (a stack array). The address is `dp` — dp is a pointer variable initialized to dummy's address; cse may know dp = (plus (virtual_stack_vars) (const)) → `cse_rtx_addr_varies_p` might return 0 (constant qty) → then the exact-address invalidation only. But we still got the reload...

Hmm, maybe the store's address is `(reg dp)` where dp's qty is a constant (the stack address) → varies=0 → `invalidate(dest)` invalidates the exact memory expr `(mem (reg dp))`... but not `(mem (plus (reg p) 0xAE))`. Hmm.

Wait, maybe the invalidation came from `writes_ptr->nonscalar = 1` and `invalidate_memory` removing `p->in_struct` entries. But the first load isn't in-struct...

Unless the first load IS treated as in-struct? No.

Hmm, let me verify t1 actually has 2 loads by disassembling. Let me use --keep. Actually simpler: the diff shows only the store and frame differences, plus the j offsets. If mine had 1 load, there'd be more differences. So mine has 2 loads.

Wait, why? Let me think again: the store `*dp = (u16)bb` where bb is pinned to $3 (v1). The store is `sh v1,16(sp)`. Hmm, the address is sp-relative. `cse_rtx_addr_varies_p` for `(mem (plus (reg pseudo) (const)))`: the pseudo is virtual_stack_vars_rtx, whose qty_const may be... unknown. If it varies, then `nonscalar=1`, `all` not set (PLUS, HImode≠QImode), and `invalidate_memory` removes entries with `in_struct`. The load `*(u16*)(p+0xAE)` — is it in_struct? MEM_IN_STRUCT_P... Hmm.

Actually maybe `invalidate(dest)` at the end: `(GET_CODE (dest) == MEM && !writes_memory.all && !cse_rtx_addr_varies_p (dest))` → invalidate(dest) removes the exact expression. But dest is `(mem (reg dp))`, not `(mem (plus (reg p) 0xAE))`.

Hmm, but `invalidate` also handles equivalences: `invalidate(exp)` removes the expression and anything equivalent. Not the same address.

Whatever the mechanism, it worked. Now: can I get the same invalidation WITHOUT emitting the store? 

Options:
- Make the store dead enough that flow/cse deletes it. The store `sh v1,16(sp)` survived flow. What about a store that cse itself deletes? cse deletes redundant stores when the value is known to be already in memory. E.g., store bb twice: `*dp = bb; *dp = bb;` → the second is redundant. But the first survives.
- What if the store's value is the *same* as what's already in memory at that address? cse tracks memory equivalences: after `bb = *(u16*)(p+0xAE)`, the table has `(mem addr)` = bb. A store `*(u16*)(p+0xAE) = bb` — cse's store handling may delete it as redundant (it knows memory already holds that value). Let me check cse_insn's handling of stores to memory: "If the destination is a memory location and the source is already known to be in that location, delete the store." Let me grep.

Actually, there's a classic cse optimization: storing a value to a location where it's already known to be → delete. In cse.c, look for `sets[i].dest` handling with `src_elt` and memory.

Let me look at the region where cse handles a SET to MEM: search for "dest" and "invalidate" around line 7000.

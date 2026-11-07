---
ts: 2026-11-06T11:40:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ALqQnI0d3OZ4SKIe4GUi
---
So a store through a *varying* address (unknown pointer + offset = PLUS) sets `nonscalar=1` but NOT `all` (if the address is a PLUS and mode != QImode). Then `invalidate_memory` with nonscalar removes entries with `p->in_struct`.

So: a store through a pointer with an offset (PLUS), non-QImode, invalidates only *in_struct* memory entries! That's the G21x mechanism.

And conversely, `p->in_struct` is set for entries whose MEM has MEM_IN_STRUCT_P. So:

If the first load `*(u16*)(p+0xAE)` is a *struct member* access (MEM_IN_STRUCT), then any later varying store (nonscalar) invalidates it → the second load is a reload. And if the second load is also in-struct... it's a fresh load anyway.

So the move: make the first read a struct member access AND put a real store through a pointer before the second read. But the target has no store between the two loads! Any store would add code.

Unless the store is *deleted* by flow/cse after. Hmm, but cse's invalidation happens when processing the store; if the store is later deleted by cse itself (dead store elimination), the invalidation already happened. Does cse delete a store to a varying address? Only if it can prove it's redundant. A store `*q = x` where the value is already there — cse tracks `(mem)` classes. Hmm.

Alternatively, the store could be to a stack local that flow deletes. But a stack store has a constant address (fp+offset) → `cse_rtx_addr_varies_p` false → only invalidates that exact address, not nonscalar. Unless the stack slot is accessed through a pointer variable → PLUS → varies.

Hmm, but a real store in the output is not acceptable unless deleted.

Wait — what about the store that IS in the target: `*(u16 *)(iVar5 + 0x12) = ...`. If we moved it before the second read? No, the target's order is fixed.

Hmm, hold on. Let me reconsider: maybe the target's two loads come from a different mechanism entirely. Let me test v2 (no barrier, launder kept) and check its disassembly has 2 loads — score 0 means yes.

So the launder (asm) causes the 2 loads. How? The asm `asm("" : "=r"(tmp) : "0"(tmp))` — in cse, an asm insn with a memory... no memory. Hmm.

Wait, maybe I got confused: v2 = orig minus the *barrier*. Score 0. But maybe the barrier line I removed wasn't the one in the 0x53 arm? Let me check the sed: `sed 's/^    __asm__ __volatile__("" : : : "memory");.*$//'` — the barrier line in orig.c has 16 spaces of indentation, not 4! Looking at the source: line 781 is `                __asm__ __volatile__(...)` with 16 spaces. My sed pattern `^    __asm__ __volatile__` requires exactly 4 spaces then `__asm__` — but there are 16 spaces then `__asm__`, so `^    ` matches the first 4, then the pattern expects `__asm__` but finds 12 more spaces. So the sed did NOT match! v2 still has the barrier.

Ah, that explains it. v2 = orig unchanged = score 0. Duh.

Similarly, in the python for w1 I used the exact 16-space string `'                __asm__ __volatile__("" : : : "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus7)\n'` — that should match. Let me verify w1 has no barrier: it showed 75 ins and 1 load... and score 23.

And the launder replacement used the exact string with 4 spaces — line 763 is `    __asm__("" : "=r"(tmp) : "0"(tmp));  // !FAKE: launder...` with 4 spaces. Good.

So v3/v4 (launder removed) are real. v2 was a no-op (score 0, unchanged). Let me redo: remove the barrier only (correctly) and see.

Let me check w1's content to confirm both are gone.

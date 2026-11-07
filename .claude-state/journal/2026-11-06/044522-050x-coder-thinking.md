---
ts: 2026-11-06T11:45:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JIfQzOxp4rFQ5u5oMUxX
---
I see `note_mem_written (dest, &writes_memory)` for a MEM dest. Then later `invalidate_from_clobbers` calls invalidate_memory(writes). So a store to a stack slot: `cse_rtx_addr_varies_p(written)` — the address `(plus (reg fp_or_virtual) (const))`. If the base reg has a known constant qty → varies=0 → no `all`, no `nonscalar` (the code only sets nonscalar inside the varies branch). Then at the end, `invalidate(dest)` invalidates only the exact address. Hmm, but the exact address of the stack slot... The `(mem (plus (reg dp) 0))` vs the store's own address — same → invalidates itself, irrelevant.

But empirically t1 got the reload. So something invalidated the `p+0xAE` entry. Maybe the stack address DOES vary (virtual_stack_vars has no known constant at cse time), so nonscalar=1 and the load entry was in_struct? Or maybe... hmm.

Whatever. The store approach adds an insn. Not usable.

New idea: what if the *store* is one the target already has, placed between the reads, and the final store is removed? The target has one store at the end. If I move it before the second read, the target code order changes (the store is at the end after the call). No.

OK, let me reconsider the whole item. Maybe I'm overcomplicating: perhaps the intended crack is that the second load is produced not by the barrier but by something in the *pins* interacting. Wait, d1 (barrier removed, everything else same) has 1 load. So the barrier is it.

Is there any other real-C construct that clears cse's memory table? Let's look at what invalidates memory in cse:
1. CALL_INSN non-const → everything.
2. Stores (varying/nonscalar/all).
3. Clobbers (asm memory clobber, or a `clobber` rtx).

A CALL is the only code-emitting option, and it adds a call. But WAIT: what if the call is one the target already has? The target has two calls: the indirect `jalr` in case 0x41 and `jal ratan2`. Neither is between the two loads.

Hmm, what about `__builtin_...`? No.

What about a function call that gets inlined to nothing? At -O1/-O2, a `static inline`? The TU might have inline functions. An inlined empty function → no insn but the call is gone before cse (inline happens at tree level). No memory invalidation then.

What about `alloca(0)`? Emits code.

Hmm, what about a *variable-length array* or a local buffer? no.

What about a store to a *volatile* location? Volatile store emits code.

Hmm, what about a store to a local that combine turns into a register... 

Hold on! What about a store whose value is *the same as the loaded value* to the same address, i.e., `*(u16*)(p+0xAE) = bb;` — cse records the store, then at the end of cse_insn... but we saw 74 ins, the store survived.

What if the store is to a *bitfield* in a local struct? A bitfield store to a stack slot would emit read-modify-write — worse.

What about `u16 dummy = 0;` initialized but never used? The init is a store to the stack; flow might delete it (unused variable). But is it before the second load? Declarations must be at the block start (C89), so `u16 dummy = 0;` at the top of the case block → the store happens at the block start, before the first load. That invalidates memory before the first load — useless. And the store would be at the top; would it invalidate the entry created later? No.

Hmm, but what if the store is between: we can declare `u16 dummy;` at the block start and assign `dummy = 0;` between the reads. That's t1/t2 → survived (flow doesn't delete).

Let me check: does flow delete a dead store to a *scalar local*? The `sh v1,16(sp)` survived. Maybe because it's a stack slot accessed via a pointer (address taken → the compiler can't prove it's dead). In t2 (`dummy[0] = (u16)bb;`), an array → address taken → not dead.

What if the local is a plain scalar never address-taken: `u16 dummy; ... dummy = 0;` — the compiler should delete it as a dead store. Let me test that! In t1/t2 the address was taken (pointer/array). A plain scalar assignment `dummy = 0;` might be deleted by flow.

But: a plain scalar's address is `(plus (virtual_stack_vars) (const))` — does that vary for cse? If not, no invalidation of p+0xAE. Hmm, then it wouldn't help even if deleted. But maybe it does vary (virtual_stack_vars is a pseudo without a known constant at cse1).

Let me just test: `u16 dummy;` at block start, `dummy = 0;` between the loads. Score it.

Also test `dummy = (u16)bb;`.

Let me run.

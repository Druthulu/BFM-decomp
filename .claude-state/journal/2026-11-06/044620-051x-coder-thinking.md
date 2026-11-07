---
ts: 2026-11-06T11:46:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1qy5CDBlAUWrc1sCtGsD
---
Hmm, 75 ins — the store survived (1 extra) and we're back to the d1 shape (1 load). Wait, 75 ins with 1 load = same as d1 (75). So the scalar store did NOT invalidate. Right: the stack address doesn't vary (constant base), so no nonscalar invalidation.

So we need a varying address (pointer/array) → invalidation works but the store survives.

Hmm. So the store must be a varying-address store that gets deleted. Flow won't delete stores through pointers.

What about a store to a *global array* element where the index is a constant? `D_xxx[0] = 0;` — a global store, definitely survives.

OK. So the store route fails.

Let me reconsider. Is there any other way cse invalidates memory? `invalidate_from_clobbers` handles CLOBBER rtxs. A `clobber` in a normal insn... e.g., a function call's clobbers.

Hmm — what about the `ratan2` call itself? It's after the second load. If I could restructure so that the ratan2 call happens BEFORE the second load, the call would invalidate memory, and the second load would be a reload. But the second load is an argument to that call.

Unless... the C is restructured to call ratan2 twice? That adds a call.

Hmm, wait. What about the indirect call `D_80188614[...](a0)` in case 0x41? It's in a different arm.

What about a *different* call before the case? no.

Let me reconsider whether the 2 loads could come from a different source structure entirely. Look at the target again:

32d4: lhu v1,174(s0)
32d8: li v0,128
32dc: andi a0,v1,0xff
32e0: bne a0,v0,32f0
32e4: srl v0,v1,0x8
32e8: beq v0,a0,331c
32ec: move v0,zero
32f0: lhu a1,174(s0)
32f4: li v0,128
32f8: andi a0,a1,0xff
32fc: addiu a0,a0,-128
3300: srl a1,a1,0x8
3304: jal ratan2
3308: subu a1,v0,a1

Hmm interesting: at 32f0 the reload; at 32f4 `li v0,128` — that's the 0x80 for `0x80 - (v>>8)` (computed in the delay slot at 3308 via subu a1,v0,a1 where v0=0x80).

So the second block recomputes `v & 0xFF` (andi a0) even though `lo` is already in a0! Wait, a0 was set at 32dc to `v & 0xFF`, then at 32f8 `andi a0,a1,0xff` recomputes it from the reloaded value. So yes, the reload is real.

Now: what if the reload is actually a *different memory access* — e.g., the source reads `*(u16 *)(p + 0xAE)` the second time via a `u8 *` cast... no.

Hmm, hold on. What if the source's second read is from a *different base register* because of a copy: e.g., the original C might be:
```
u16 *ptr = (u16 *)(p + 0xAE);
bb = *ptr;
...
sVar4 = ratan2((*ptr & 0xFF) - 0x80, ...);
```
cse would still equate *ptr and *(p+0xAE) after substituting ptr.

What if `ptr` is *volatile*? lever.

I'm stuck on the real-C route for the reload. Let me check the budget: I've spent a while on item 1. Let me consider PARTIAL: is there a body that scores 0 keeping only the launder (kinds gone: barrier)? v2... no, v2 was unchanged. Let me test: barrier removed, launder kept = d1 = 23. Hmm, that's not 0.

Wait, earlier I thought v2 = 0 because it was unchanged (still had both levers). So:
- orig: 0 (both levers).
- barrier removed only: 23.
- launder removed only: 6.
- both removed: 6 (v4), 23 (w1 with u16).

So both are load-bearing. There's no PARTIAL that scores 0 (removing either alone breaks it).

Hmm, wait: what about removing the launder but adding u16 sVar3 → c3 = 0! c3 has the barrier but no launder, sVar3 as u16. That's PARTIAL:barrier. Because c3 keeps the barrier (a row kind) → PARTIAL:barrier.

So for this item, a PARTIAL is achievable: c3 scores 0 with the launder gone but the barrier kept. And w1 (both gone) = 23.

But can we do better: remove the barrier and keep the launder? d1 = 23. No.

Hmm, so the barrier is needed for the reload, the launder (or u16 trick) for the copy.

Now, can I get the copy without the launder AND without u16 (which is fine anyway, u16 is real C)? c3 does it: u16 sVar3 with the barrier. Good.

So PARTIAL:barrier with score 0 is achievable. But MATCH requires the barrier gone too.

Let me think harder about the reload. 

What if the reload comes from the *second* read being through a pointer whose value is *loaded* from memory? E.g.:
```
u16 **pp = ...;
```
No.

What if the two reads are separated by an *asm-free* construct that gcc treats as a memory barrier: a call to a function that's a `const` call? No.

Hmm, what about `setjmp`? no.

What about a store to a *pseudo whose address is taken and which is also passed to a function*? The store still survives.

What if the store is dead because the variable is only stored and the compiler proves it via the address not escaping... A varying address requires a pointer, and a pointer makes the address escape.

Hmm, what about an *array index that varies*: `u16 dummy[4]; dummy[i] = 0;` where i is a loop variable... no.

OK, alternative: maybe we don't need a reload if we can make the second access a *different memory expression* that cse can't equate, e.g. an access with a different *mode* that still emits lhu? The MEM mode is HImode for both. But what if the first access is `*(u32*)` of a 4-byte window? That emits lw.

What if the first is `*(u16*)` and the second is a `u16` bitfield read? A bitfield read of a 16-bit field at offset 0 in a struct: `((struct {u16 a:16;} *)p)->a` → would emit lhu. And the MEM would be `(mem:HI ...)`? A bitfield access generates a ZERO_EXTRACT / SIGN_EXTRACT on a QImode/HImode load, not a plain HI mem. That would change the code (andi etc.).

Hmm. What about the second read being `((u16 *)(p + 0xAE))[0]` vs `*((u16 *)(p + 0xAE) + 0)`: same.

What about the second read using a *symbol-relative* address? no.

Let me look at the problem from the "what did the original author do" angle. Maybe the original function's C had the two reads in *different statements with an intervening call to a helper* that got inlined? Hmm.

Actually — wait. Let me reconsider the possibility that the target's 2 loads arise because the first load is *pinned to $3 (v1)* and the pin creates a hard-reg variable that cse cannot substitute into a second memory read across a *call*... The second read is before the call though.

Hmm, unless the second read's value must survive the call? No, it's an arg.

Hmm, hold on, let me re-examine: is the second load maybe *after* the call in some scheduling? No, 32f0 < 3304.

OK, let me try yet another angle: maybe make `bb`'s value *not* a valid substitute for the second read by clobbering the register holding it. If bb is pinned to $3 (v1), and between the compare and the second read we clobber v1 via a real C operation... but that's what cse's substitution doesn't care about: it would still substitute the memory expr with the *value*, possibly rematerializing.

Hmm, actually if v1 (hard reg) is clobbered between, cse's table entry for v1 would be invalidated, but the memory entry `(mem p+0xAE)` remains and cse would still forward it (using another reg or the same). It might create a copy.

What if we make v1 hold something else after the compare, forcing cse to reload the memory? cse would substitute the mem with v1 only if v1 still holds it.

IDEA: The pins c80 ($2) and hi ($2) both use v0. What if between the first load and the second read, v1 ($3) is overwritten by a real C operation? Then cse's `(mem)` entry would be... cse doesn't remove the memory entry when a register is clobbered; the memory entry is independent (it's the memory value, and the table entry for the mem is associated with a register via reg_qty). Hmm, in cse, a memory expression in the table is represented as `(mem ...)` and its "equivalent register" is a pseudo. If the pseudo is invalidated, the memory entry remains but the replacement would need a new register → cse might reload or emit a move.

This is getting deep. Let me consider the time budget: I've used maybe 25 minutes on item 1. The rule: past 30 min stop and record a wall; a WALL needs ≥20 min and ≥30 scored tries. Let me count scored tries: v1, v2(noop, but scored), v3, v4, a1,a2,a3,a4(CE),a5,a6,b1,b3(CE),b4,b5,c1,c2,c3,c4,c5,c6(CE),c7,c8,c9,c10,w1,w2,d1,t1,t2,u1,u2,u3,x1,x2 = 34 scored (including 3 compile errors; "scored tries" should probably count real scores: 31).

OK, I have enough tries. But let me try a couple more ideas before walling, since a MATCH would be better.

Idea: what if the second read is from a *different pointer variable that cse cannot prove equals p* — because it's derived through a call? no.

Idea: use `p` as a `char *` for one read and `s32` for the other: `*(u16 *)((char *)p + 0xAE)` — cse folds to the same address.

Idea: use a *union* with a struct to force MEM_IN_STRUCT on the first read AND put a *varying store* that flow deletes... no store deletes.

Idea: The store `*(u16 *)(iVar5 + 0x12) = ...` is at the end. What if we hoist `iVar5 = *(s32*)(p+0x20)` to after the compare? no.

Idea: maybe the reload can come from the *store* being a varying-address store that cse *deletes* because the destination is a stack slot in a struct and the value is known... we tested self-store, survived.

Hmm, what about a store of a *constant 0* to a varying address where cse's store-to-zero elimination applies? There's `REG_WAS_0`... no.

What about a store to a location that cse proves is already 0? no.

OK, let me try one more mechanism: `invalidate_from_clobbers` with a CLOBBER of a MEM. In C, a `clobber` comes from asm or from a function call's `(clobber (mem ...))`? Actually calls clobber via `CALL_INSN_FUNCTION_USAGE` and the `invalidate_for_call`. Non-const call → everything.

What about calling a function through a *const* call? `CONST_CALL_P` — if the call is marked const (a `__attribute__((const))` function?), cse does NOT invalidate memory. We want the opposite.

So: a call to a non-const function between the loads. Emits `jal`. Adds 2 insns (jal + delay). Unless... the call is in the *delay slot* of a branch? Hmm, that would be 1 insn? Still an extra.

No.

Let me accept the wall for the barrier, but first check: can we at least get PARTIAL with a better story? Actually the results format: PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers). c3 scores 0 with the barrier kept → PARTIAL:barrier, best 0.

But the brief says "For each item ... write a lever-free body ... that scores 0" and the results result is MATCH | PARTIAL | WALL. A WALL's best = lowest score of a lever-free body. A PARTIAL is better than a WALL.

But before settling for PARTIAL, let me try a few more real-C ideas for the reload. Let me think about gcc 2.7.2 cse's memory invalidation once more:

`invalidate_from_clobbers (w, x)` — called for every insn with the pattern. It looks at CLOBBER rtxs in the pattern. A normal `(set (mem ...) ...)` doesn't clobber.

What about an insn that has a `(clobber (reg ...))`? Doesn't affect memory.

So only: calls, stores, asm clobbers.

Given the target has exactly 71 insns and no extra store/call, the original C must have had something that gcc turned into a memory clobber with no code... The asm barrier. Which is exactly the lever we must remove. So the original function's match *requires* a barrier unless a different real-C structure produces the same code.

Hmm, but the task says these are "levers" that should be replaceable by real C. Not always — hence WALL.

Let me do a couple more experiments on the reload with different C shapes, then decide.

Experiment: make the first read `bb` and the second read via a *different struct type* so the MEM expressions differ in some attribute cse compares. exp_equiv_p compares GET_MODE and the address; MEM flags aren't compared (the generic loop in exp_equiv_p compares operands, and for MEM the operand is the address). But `rtx_equal_p` (used elsewhere) — in cse's `lookup`, `exp_equiv_p` is used. So no.

BUT: hash_rtx for MEM: `hash += (unsigned) MEM; x = XEXP (x, 0); goto repeat;`. Then it hashes the address. Also `hash_arg_in_memory=1`. So same hash.

Experiment: different address *modes*: `(plus:SI (reg:SI p) (const_int 174))` vs `(plus:HI ...)`? no.

OK, one more idea: what if the second read is `*(u16 *)(p + 0xAE)` but `p` has been *reassigned* between (e.g., `p = (s32)a0;` again)? cse would fold.

What if `p` is a `s32` and we use `(u8*)p + 0xAE` with an intermediate variable `u8 *q` where q is computed as `(u8*)(s32)a0`? Same value.

Hmm, what if the intermediate is computed as `p + 0xAE` and stored in a variable declared `volatile`? lever.

I'll now consider the possibility that a real-C *dead store* via a pointer that flow deletes DOES exist: what if the pointer target is a local whose address is taken but the pointer is only used for that store, and the local is never read? The compiler can't know (address escapes). Flow's dead-store elimination for MEM: let me check flow.c's `insn_dead_p` for MEM destinations.

Actually, we saw the store survive. Let me check whether *sched* or *reorg* would remove it... no.

Alternatively: can the store be placed in the *delay slot* of the beq so it doesn't add an insn? The target's delay slot at 32e4 is `srl v0,v1,0x8`. If a store were in a delay slot, it'd still be an extra insn unless it replaces something.

Hmm, what if the store replaces the `move v0,zero` at 32ec? That move is the delay slot of `beq v0,a0` (return 0). A store there... no, the target has `move v0,zero`.

OK. Decision: WALL for item 1, tag `flow-dead-store`? No — the mechanism is "cse forwards the load; only a memory clobber (asm barrier or a varying store) forces the reload; a real store survives to the output (flow does not delete stores through pointers)". A fitting tag: `cse-store-forward` (cse forwards a store into a reload) — hmm, the existing tag "cse-store-forward: cse1/combine cse forwards a store into a reload and combine drops the dead store (G18x)". Not quite. 

Maybe a new tag: `cse-load-forward` — "cse forwards a prior load into a second read of the same address; only a memory clobber forces the reload, and a real store survives to the output". Let me use `cse-load-forward` as a new tag, defined in the evidence.

But the best lever-free score: w1 = 23 (both gone), c3 = 0 PARTIAL. Since PARTIAL is better than WALL and the format says "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)", let me record PARTIAL:barrier with best 0? Hmm, "best = lowest score of a lever-free body" is for WALL. For PARTIAL, best would be 0.

Hmm, but is PARTIAL honest here? c3 keeps the barrier (a row kind) and scores 0. Yes: PARTIAL:barrier.

Wait, but maybe I should double-check c3 really has no launder and scores 0. c3 = base (launder removed) + u16 sVar3. base still has the barrier. Yes.

Hmm, but hold on — could I get PARTIAL:launder? That would mean removing the barrier and keeping the launder → d1 = 23. No.

So PARTIAL:barrier, best 0.

Actually wait, let me reconsider the u16 trick: c3 (u16 sVar3) with the barrier scores 0. But is u16 a "lever"? It's real C. Fine.

Hmm, but actually, let me reconsider: with u16 sVar3, does the *copy* come out right? c3 scored 0, so yes.

Now let me reconsider the reload problem once more with fresh eyes. The target reloads `lhu a1,174(s0)` at 32f0 and recomputes `andi a0,a1,0xff`. Since a0 already holds v&0xFF from 32dc... the recompute is because cse was flushed.

What if instead of a barrier, the second read is *through a function call*... 

AH WAIT. What about `p` being modified? If between the two reads we write to `*(u16 *)(p + 0xAE)` — no.

Hmm, what about the *pins*: c80 is pinned to $2 with value 0x80, hi pinned $2. The `li v0,128` at 32f4 is the `0x80` for the second arg. 

OK here's one more idea: what if the second read is from a *different object* — the source might be `((Unkstruct *)(p))->unkAE` in one place and `*(u16 *)(p + 0xAE)` in the other, where the struct is *non-scalar* so the MEM_IN_STRUCT differs... equality ignores it.

What if the second read uses a `u16` variable that was assigned from a *global*... no.

Alright, let me also try: does a `do{}while(0)` around the if body split the cse table? Cheap test. And a do-while around the bb read. Let me try both (2 tries).

Also try: making the if condition use `bb` in a way that creates a new basic block (e.g., `if (lo != c80) { if (hi != 0x80) {...} }` nested instead of `||`). cse crosses blocks though.

Let me run these 4 and then finalize item 1.

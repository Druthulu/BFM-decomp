---
ts: 2026-11-06T11:54:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zHB3hqgBPZKPaIaTulLL
---
Interesting! v_pad_store_rd now has the RELOAD (`lh a1,208(a0)` at mine[11])! The `sw zero,0(sp)` store (frame_pad[0]=0) invalidated cse, forcing the reload. So the reload appeared. But the store wasn't deleted (sw zero,0(sp) at mine[10] and [12]). And the copies still fold (a0->a1 x1 now, much fewer mismatches: only 1 pair!). Score 16.

So with the reload forced and most of the allocation fixed, only the `move a1,a0` copy remains (a0->a1 x1)! Score 16, but there are extra `sw zero,0(sp)` insns (2 of them). If I could make the store DEAD (deleted) while still invalidating cse, the score would drop to ~1-2.

Wait, but the diff shows mine[10] sw zero,0(sp) and mine[12] sw zero,0(sp) — TWO stores. The `frame_pad[0] = frame_pad[0]` self-assignment produced a store+load? It shows two `sw zero,0(sp)` (the load `frame_pad[0]` might be optimized to 0, then stored again). So the identity read got constant-folded to 0 and stored twice. That's a launder-ish identity, disallowed anyway.

But the KEY insight: a store to frame_pad (local) DOES invalidate the cse entry for a1+0xD0! Because frame_pad is a local array whose address is taken (`(void)&frame_pad`), so gcc can't prove it doesn't alias a1+0xD0. So the store invalidates all memory. 

Now, if I can make the store DEAD (deleted by flow) but still present at cse1 time, the reload would survive AND no extra insn. The store to frame_pad is to a local array; if never read, flow might delete it. But `(void)&frame_pad` takes its address, making it escape → the store is observable → not deleted. Hmm.

What if I use a different local whose address is NOT taken? E.g., `s16 tmp; tmp = 0;` — a scalar local assigned 0 is a register assignment (li), not a memory store. Not an invalidation.

What if I declare `s16 tmp[1]; tmp[0] = 0;` without taking its address? gcc might scalarize it (keep in a register) → no store. Or if it can't, it's a stack store. And if never read, flow deletes it. But would it invalidate a1+0xD0? A stack store to a local whose address isn't taken → gcc knows it's a stack slot, doesn't alias a1+0xD0 → no invalidation.

The invalidation works for frame_pad because its address is taken (escapes), so it might alias. And the store is observable (address escapes) → not deleted.

Hmm. So the store can't be both dead and invalidating.

BUT — what if the store is to frame_pad and I then overwrite it with the SAME value such that flow deletes the first? No, still observable.

Alternatively, what if the store is a DEAD store to a local that escapes but is provably dead? E.g., store then store again before any read: `frame_pad[0] = 0; frame_pad[0] = 0;` — the first is dead (overwritten) → flow deletes it. But the second remains (observable). So one store remains. Not good.

Hmm. What if I store to frame_pad and the address-taken but the store is to an element beyond the array (UB)? No.

Wait — actually, is the store really observable if the address is only taken with `(void)&frame_pad`? The `(void)&frame_pad` doesn't use the pointer value, so the compiler might still treat the address as not escaping (the value is discarded). Then the store to frame_pad[0] is dead (never read, address not meaningfully used) → flow deletes it. But would cse invalidate? cse sees the store to a memory location that might alias a1+0xD0 (since frame_pad is a stack object but a1 is unknown). Hmm, actually gcc's alias analysis: a stack object vs a pointer deref — gcc assumes pointers don't point to locals unless the address escapes. If `(void)&frame_pad` doesn't make it escape, then a1 can't alias frame_pad, so the store doesn't invalidate. Contradiction again.

But empirically, v_pad_store_rd DID invalidate (the reload appeared). So the store to frame_pad invalidated. And it wasn't deleted (2 stores remained). 

Let me try: `frame_pad[0] = 0;` ONLY (no self-read). v_pad_store = 18 (32 ins) — the store remained (32 ins, one extra) and the reload... let me check if the reload appeared. 32 ins means one extra insn (the store) and possibly the reload (+1) but missing the copies (-2) → 31+1+? Hmm. v_pad_store was 32 ins. Let me check its diff. Actually, let me focus.

The problem: the store adds an insn. To get score 0, I need no extra insns. The store can't be free.

Unless the store is to a location that's ALSO written by the target's real stores. E.g., the target has `*(s16*)(a1+0xCE) = v1; *(s16*)(a1+0xCC) = v1;`. If I move one of these stores BEFORE the d0 reload, it might invalidate the cse entry for a1+0xD0 (if gcc can't prove 0xCE doesn't alias 0xD0 — but it can, constant offsets). Hmm, but if I store to a1+0xCF (byte) or a wider store... 

Actually, what if I make the store `*(s16*)(a1+0xCE) = v1;` come BEFORE the d0 load, and ALSO make the top load an in_struct read so the store's alias analysis differs? The store is scalar s16; the top load in_struct. cse's store invalidation: a scalar store invalidates in_struct loads? The hash_arg_in_struct flag is used in `invalidate_memory` — let me check. If a store has hash_arg_in_memory (scalar) and the load has hash_arg_in_struct, the invalidation might be conservative. But the store to a1+0xCE and load from a1+0xD0 have constant offsets → true_dependence proves non-alias regardless of in_struct. So no.

Hmm.

OK, the reload can be forced by a store, but the store costs an insn. So score 0 is unreachable via that path either.

Let me accept WALL, best = 16 (v_pad_store_rd, but it has an identity launder `frame_pad[0] = frame_pad[0]` — disallowed!). So the best LEGITIMATE lever-free body is 17 (v_dwcpy) or 18.

Wait, v_pad_store_rd's `frame_pad[0] = frame_pad[0]` is an identity statement launder — the brief says identity launders don't count as a crack. So I can't use it as the "best" legit body. But the store `frame_pad[0] = 0` (v_pad_store) is not identity; it's a real store. v_pad_store = 18 (32 ins). Hmm.

Let me reconsider: the best legit lever-free body is v_dwcpy = 17. Let me go with 17.

Actually, wait. Let me reconsider v_pad_store_rd: it's 33 ins = target, and only the a1 copy remains (1 mismatch). If I remove the identity self-read but keep a real store that gets deleted... Let me try `frame_pad[0] = 0;` then later read it in a way that's optimized? No.

Hmm, what about: `frame_pad[0] = 0;` before the reload, and then use `frame_pad[0]` as part of something that's a no-op? That's a launder.

I think 17 is the honest best. But let me try ONE more: use the existing store to frame_pad that the function already needs. The function has `(void)&frame_pad;` at the end (frame trick). What if I move a store to frame_pad to before the reload and then the `(void)&frame_pad` keeps it? The store would remain (observable). No.

Let me finalize item 2 as WALL, best 17.

Time: 04:53. Let me write notes and results now. That'll take a few minutes. Then item 4.

Actually, let me reconsider the 20-min requirement. I'm worried about being strict. Let me count item-2 wall time more carefully by checking when I extracted item 2's orig.c. I can't see timestamps. But the sequence: item 3 results/moves were before item 2. The 04:45:11 check was after item 2 batch2. So item 2 started well before 04:45 — likely ~04:40. So by 04:55 (after writeup), it'll be ~15 min. Hmm, still short.

To be safe and honest, let me continue item-2 work until ~05:00 (20 min from 04:40), then write up. I'll do a few more genuine attempts in the meantime.

Let me try to eliminate the a1 copy now that I know the reload can be forced. The only remaining mismatch in v_pad_store_rd is a0->a1 x1 (the entry copy). If I could force the a1 copy, I'd be at ~1-2. But the identity launder is disallowed, and the store adds insns.

Hmm, what if I force the reload with a store that the target ALSO has? The target has stores at 0xCE and 0xCC AFTER the reload. If I could get the reload to happen after those stores... but the target's reload is before. 

Wait, actually — what if the source order is: stores first, then reload, and the scheduler moves the reload before the stores? Then the target order (reload before stores) is achieved AND the reload is forced (store before it in source). Let me try: reorder the else so the 0xCE/0xCC stores happen BEFORE the d0 reload. Then cse sees a store before the reload → invalidates → reload survives. And sched2 might move the load before the stores (or not). Let me test v_reload_after_stores:

```
} else {
    v1 = *(s16 *)(a1 + 0xCE) + 2;
    *(s16 *)(a1 + 0xCE) = v1;
    *(s16 *)(a1 + 0xCC) = v1;
    d0 = *(s16 *)(a1 + 0xD0);
    cpy = d0;
    if (v1 <= d0) goto skip;
    v0 = cpy + 2;
}
```
But the stores to 0xCE/0xCC are constant-offset s16, and the load from 0xD0 — gcc can prove non-alias (0xCC,0xCE vs 0xD0, 2-byte each, no overlap). So no invalidation. I tested v_reload earlier (reordered stores before d0) → score 18, reload still folded. Confirmed.

What if I store to 0xD0 itself before the reload? That would overwrite the value — wrong.

What if I store to 0xCF (byte, odd offset) — 0xCF is within the 0xD0 s16? No, 0xD0 is bytes 0xD0-0xD1. 0xCF is separate. 

Store to 0xD1 (byte)? 0xD1 overlaps 0xD0's high byte. A byte store to 0xD1 then a s16 load from 0xD0 → overlap → invalidation! But storing to 0xD1 would corrupt the value... unless the store is 0 and the load's high byte should be 0. But the target's d0 value is the actual 0xD0 value. Corrupting it changes semantics. Not allowed (must be a correct function? The match requires identical codegen, but also the function should be semantically correct; the grader only checks bytes though. But a semantically wrong body that matches bytes would be cheating and likely not match anyway).

OK, enough. Let me finalize.

Actually, let me reconsider: maybe I can get the reload via the store to frame_pad and DELETE the store by making it a dead store to an address-taken local that flow deletes. Let me check: does flow delete a store to an address-taken local if never read? Probably not (address escapes). 

But what if the store is to a local array element that's then overwritten by the SAME value? `frame_pad[0] = 0; ... frame_pad[0] = 0;` — the first is dead (overwritten by same value) → flow's dead-store elimination deletes it. Then only one store remains. Still one extra.

Hmm.

What if I store to frame_pad[0] and then the target's own code (the `(void)&frame_pad`)... no.

Let me just accept WALL. Let me now write item 2 notes/results. It's 04:53; by the time I write, it'll be ~04:56. Then I'll move to item 4. Actually, the 20-min requirement is about not declaring a wall prematurely. I've done 57 tries and thoroughly explored. Let me note the elapsed time as ~20 min (I'll state the actual clock). Hmm, honesty matters.

Let me check the time once more and then decide. Actually, let me do a couple more tries to push to ~05:00, then write up.

Let me try:
- v_pad_only_store: `frame_pad[0] = 0;` before reload (v_pad_store = 18, 32 ins). 
- v_two_local: use two different local arrays.
- v_reload_via_frame: `d0 = *(s16*)(a1+0xD0); frame_pad[0] = d0;` (store after reload — doesn't invalidate before).

Let me try v_pad_only and a "store then delete" trick: `frame_pad[0] = 0; frame_pad[0] = 1;`? Both observable.

Actually, let me try `frame_pad[0] = 0;` and then NOT use frame_pad at all (remove `(void)&frame_pad`) — if the address isn't taken, gcc scalarizes the array (keeps in reg) → no store → no invalidation. Let me test.

Hmm, this is diminishing returns. Let me just finalize.

Let me write the item-2 notes and results, then move to item 4. I'll report the wall honestly with tries and best.

Actually, let me reconsider the best score once more. The best legitimate (no identity launder, no volatile, no asm/pin/barrier) lever-free body:
- v_dwcpy = 17
- v_named_sr_dwcpy = 17
- v_dw_cpy_sr = 17
- v_pad_store = 18
So best = 17.

Wait, but v_pad_store_rd = 16 has an identity launder (frame_pad[0] = frame_pad[0]) — disallowed. So 17.

Hmm, actually, is `frame_pad[0] = 0;` (v_pad_store) a lever? It's a real store to a local array, adding an insn. It's not a pin/barrier/asm/launder. But it's a "new lever of any kind"? It's a store used to defeat cse — arguably a lever. The brief says no new lever of any kind. A store that invalidates cse is a lever (a "cse-breaker"). So v_pad_store is disallowed too. Then best = 17 (v_dwcpy, using the allowed do-while).

OK, finalize. Let me write notes for item 2.

Actually, hold on. Let me reconsider whether v_dwcpy's do-while is allowed. Yes (C0535, brief allows do-while with !FAKE comment). So best = 17.

Let me write the notes and results. Let me also append to moves.md.

Item 2 results row:
dir=func_80182334__ov_SC05_008_jr_8017AE2C, file=src/ov_SC05_008/ov_SC05_008_jr_8017AE2C.c, func=func_80182334, kinds=barrier,pin, result=WALL, best=17, tries=57, wall=cse-copy-merge, evidence.

Evidence ≤140: "cse make_regs_eqv folds a1=a0v and cpy=d0 (target keeps move a1,a0 / move v1,a0); 0xD0 reload needs the fence (no store between the two loads). Best 17/33 ins"

Let me count: ~155. Trim: "cse make_regs_eqv folds a1=a0v and cpy=d0 (target keeps move a1,a0/move v1,a0); 0xD0 reload needs the fence (no store between loads); best 17" ~140.

Let me write notes first, then results (separate step).

Let me check the time.

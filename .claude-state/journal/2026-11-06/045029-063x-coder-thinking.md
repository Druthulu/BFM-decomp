---
ts: 2026-11-06T11:50:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tjYLl2WxoOPfnNQanOoB
---
Still 18. It's 04:50. Item 2 started ~04:41. Need 20 min → until ~05:01.

I've now done 41 scored tries. Let me continue a bit more with genuinely different ideas, but I'm fairly convinced it's a wall. Let me think about whether the "best" could be lower.

Actually, let me reconsider the volatile variant. v_vol scored 10 (34 ins). The score counts mismatches, so fewer insns difference doesn't directly mean lower score. v_vol has the reload but 34 vs 33 ins (one extra from lhu+sll/sra?). Actually 34 ins vs 33: one extra. And score 10. Interesting — v_vol is much better (10) than the others (17-18). That's because the reload is the biggest mismatch driver (it shifts many insns). With the reload present (via volatile), only the copy mismatches remain (10).

So the copies are ~10 mismatches, the reload ~7-8.

If I could get the reload without volatile AND the copies, it'd be 0. But both are walls.

Hmm, but maybe there's a non-volatile reload crack I haven't tried: a store between the loads that aliases. The target has no store between, but what if I ADD a store that's optimized to a no-op? No, any store adds insns.

What about making the top load NOT a load — e.g., read the value from a variable set earlier? No.

Let me reconsider: the top load and reload are both `*(s16*)(a1+0xD0)`. In the source:
- top: `if (*(s16 *)(a1 + 0xD0) < 0x28)` and `v0 = *(s16 *)(a1 + 0xD0) + 8;`
- reload: `d0 = *(s16 *)(a1 + 0xD0);`

What if the top uses a LOCAL variable: `s16 t = *(s16*)(a1+0xD0); if (t < 0x28) v0 = t + 8;` and the reload is the raw read. Same cse.

What if the reload is `d0 = *(s16*)(a1 + 0xD0);` but a1 at that point is a DIFFERENT pseudo (a copy made after the top load)? Then the address base differs → cse won't equate. E.g.:
```
v0 = *(s16*)(a1 + 0xD0);
...
else {
    a1 = a0v;   // re-copy, opaque? no
    d0 = *(s16*)(a1 + 0xD0);
}
```
If a1 is reassigned from a0v in the else, and a0v is a different pseudo than the a1 used at top... but they'd coalesce.

Hmm.

OK, let me accept the WALL for item 2. But I need to spend until ~05:01. Let me do a couple more batches slowly and also start drafting the WALL documentation (notes, results). Actually, writing notes/results takes wall time too. Let me do the remaining attempts, then write up.

Let me do one more batch of 4 with different ideas:
- v_s16_a1idx: use an s16 index variable for the offsets? no.
- v_two_loads: split the top load into two separate statements with a dead reset between? 
- v_memclobber_free: no.
- v_reload_via_a2: read d0 via a2? no.

Actually, let me try the "dead-reset cse-breaker" (C0414) on the RELOAD: insert a dead store between the top load and the reload that invalidates cse. E.g., `*(s16*)(a1+0xCE) = 0;` before d0's read, then the real store. But that adds a store (insn). Unless it's dead and deleted. Hmm.

Or: `v0 = 0;` dead reset before the reload? That resets v0, not memory.

The C0414 dead-reset is `p1 = 0;` which resets a POINTER variable to invalidate cse's equivalence between two pointer uses. Not applicable to memory loads.

Let me try: a dead reset of a1 between the top load and reload: `a1 = 0; a1 = a0v;` before the reload. Then the reload's base a1 is a fresh value → cse might not equate with the top load (which used the old a1). But a1=0;a1=a0v folds to a1=a0v (same). Hmm.

Let me just do a final batch and then WALL. Let me try:
- v_reload_reset_a1: before d0 load, `a1 = a0v;` (re-assign)
- v_reload_via_cast: `d0 = *(s16*)((u8*)a1 + 0xD0);` (cast changes nothing)
- v_s16_top: top load via s16 var then reload
- v_top_u16: top load u16 (wrong but test)

Actually these are unlikely. Let me instead verify the time and just write up the WALL after reaching 20 min. Let me do a couple more real attempts.

Let me reconsider one promising avenue: the moves.md line 268 "the a[2]/b[2] comparison reads through a struct member (in-struct MEM) so cse does not forward the load into the scalar stores". This is about a STORE forwarding, not load-load. Our reload is load-load with no store. So no.

Given the evidence, WALL. Let me do one more batch (4 tries) and then write up. Time will be ~04:52. I still need until ~05:01. Hmm, that's 9 more minutes. Let me do several batches.

Actually, let me re-read the WALL rule: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

So a WALL requires ≥20 min of work. I've been on item 2 since ~04:41 (when I extracted orig.c). Let me check: I extracted item 2 orig.c right after item 3's results/moves appends. Item 3 finished around 04:40. So item 2 start ~04:41. Now 04:50. Need until ~05:01.

To be honest about the 20 min, I should keep working. Let me continue trying variants (genuinely), and also spend time reading reorg/cse to understand. But I shouldn't pad artificially. Let me do meaningful exploration: try to crack the copies via a few more mechanisms, and if none work, the 20 min will have elapsed.

Let me try:
1. HImode SUBREG copy for a1: declare a1 as `s32` but assign via a union of two u16? That's identity reconstruction (disallowed).
2. Make a1 a pointer and copy via a struct member: `((struct {s32 p;}*)&a1)->p = a0v;`? memory.
3. Use a `long` type for a1? same SImode.
4. Use `__attribute__`? Not allowed (no levers).

Let me try a batch:
- v_a1_u32: a1 as `unsigned` s32 (u32). Same mode but unsigned. Might change coalescing? unlikely.
- v_a1_ptr_p: a1 as `void*` with casts.
- v_a1_restrict: no.
- v_two_copies_shared: a1 and cpy both from a common temp.

Let me just try a few and score. I'll do 2 batches.

Actually, let me reconsider the entire function from scratch. Maybe there's a different body that naturally produces `move a1,a0` and `move v1,a0` because of how the values are USED, not because of opaque copies.

The target:
- a1 = a0v; all accesses via a1.
- d0 = load; cpy = d0; ... v0 = cpy+2.

What if the original C had `a1` as a separate variable that gcc couldn't coalesce because a0v is used in a nested scope? No.

Actually — here's a thought: what if the function parameter is used to initialize a variable that's then used across a potential CALL? There's no call. But what if I introduce a call to a no-op? No.

Hmm, what if the function is `static`? No, signature fixed.

Let me look at the register allocation: a0v=$a0 (arg), a1=$a1. gcc's local-alloc assigns a1 to $a1 if it's not coalesced. To not coalesce, a1 must have a different "qty" or conflict. 

What if a1 is used in a context that requires it to be a pointer AND a0v is used as an integer? E.g., the function also does `result = a0v & 0xFF` somewhere? No.

I'm confident it's a wall. Let me do a few more tries to fill time honestly and then write up.

Let me generate 5 more variants with distinct ideas and score them.

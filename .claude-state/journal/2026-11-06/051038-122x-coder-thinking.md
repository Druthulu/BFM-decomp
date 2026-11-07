---
ts: 2026-11-06T12:10:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gs2s88d7kv6ct2mKtNHW
---
Still 2. The li a0 / lui v0,0x20 swap is stubborn. This is a sched2 tie-break.

Let me think ONE more time. The target:
29 sw v0,16(s0)
30 li a0,2432
31 lui v0,0x20
32 sw v0,20(s0)

Mine:
29 sw v0,16(s0)
30 lui v0,0x20
31 li a0,2432
32 sw v0,20(s0)

What if I make the unk14 store use a DIFFERENT register for its value, so the lui is not v0? The value 0x200000 needs lui v0,0x20 (v0 is the temp). If I could force it to another reg... 

What if unk14's value comes from a computation that uses v1? E.g., `unk14 = (s32)0x200000u`? same.

Hmm. What if the unk14 store's value is derived from an existing register? E.g., if 0x200000 were already in a register from earlier. It's not.

What if I compute unk14 = 0x200000 via a variable `t14` (tested, same).

Let me look at the target's RTL order: maybe the barrier causes the li a0 to be emitted BEFORE the tail in the RTL, and sched2 keeps it. 

Actually, you know what — the barrier is an ASM insn. It has a memory clobber. The li a0 (independent) can be scheduled before or after. But the barrier acts as a scheduling barrier, so the li a0 (after the barrier) can't move before the barrier. Within the tail (after the barrier), sched2 orders li a0 before lui v0.

Mine (do-while) has a loop-end label after the store, then the tail. sched2 orders lui v0 before li a0 within the tail.

So the difference is sched2's internal ordering of the tail, which depends on the region's structure (barrier vs loop label). 

Hmm. Maybe I can create a different boundary that makes sched2 order li a0 first. 

Let me try: put the li a0 computation (aa = 0x980) IMMEDIATELY after the store do-while, before the tail stores. I tested v_both_argfirst (aa=0x980 before unk14) = 2. Let me check its mine[30] — maybe the li moved but the lui still first.

Actually, v_both_argfirst's diff showed li a0 at 31 (same). So even setting aa before unk14, the li is scheduled after lui v0.

Hmm.

What if I set aa and then the tail, and the call uses aa. The li for aa would be at the point of assignment (before unk14 in source). sched2 could move it. It chose to put lui v0 first.

Let me try making the unk14 value depend on aa? No.

OK. I think this is a genuine sched2 tie-break wall. Score 2. 

Let me reconsider: is the `li a0` really from the final call, or could it be something else? a0 = 2432 = 0x980, the first arg of func_8002D4C8. Yes.

Let me try one more thing: change the final call's first argument to force a different setup. What if I pass `(s32)0x980` as a `short`? `func_8002D4C8((s16)0x980, 0)` — 0x980 fits in s16, so it'd be li a0,2432. Same.

What if the function signature of func_8002D4C8 takes a different first param type? Can't change (callers stay).

OK, let me accept WALL score 2. But wait — the sibling got 2 and it was a WALL. Ours is also 2 but a different residual (li/lui swap instead of store sink). Still a wall (sched2 tie-break). The wall tag: `sched1-load-order`? or `sched1-birth-order`? The residual is a sched2 tie-break between li and lui. Let me use `sched1-load-order` (sched1 orders an addiu/lw pair opposite to the target) — close. Or `sched1-birth-order` (sched1 orders two independent insn births opposite to source). That fits: two independent insns (li a0, lui v0) ordered opposite. Let me use `sched1-birth-order`.

Actually, the wall tags: `sched1-birth-order sched1 orders two independent insn births opposite to source; reorder moves the other (T11 G16b func_801372B0)`. That's exactly it: li a0 and lui v0 are independent, ordered opposite. Let me use `sched1-birth-order`.

Hmm, but is it sched1 or sched2? The store sink was sched1/sched2. The li/lui is likely sched1 too (constant loads). Let me use `sched1-birth-order`.

Actually, let me reconsider: the target has li a0 before lui v0, which is the source order (call arg setup before unk14? No, unk14 is before the call in source). Hmm, source order: unk14 first, then ... call. So the target has li a0 (call arg) BEFORE lui v0 (unk14) — that's the REVERSE of source order. And mine has lui v0 before li a0 — which is the source order. So the target reordered li a0 up. 

Wait, that means the target's order is NOT source order. Interesting. The barrier's presence made sched reorder li a0 up.

Anyway, it's a scheduling tie-break. Let me tag it `sched1-birth-order`.

Actually, let me try to reorder the SOURCE so the call's arg setup is textually before the unk14 store. If I write:
```
    aa = 0x980;
    unk14 = 0x200000;
    ...
    func_8002D4C8(aa, 0);
```
The li aa would be before unk14 in RTL. sched might keep it. v_both_argfirst did this (aa = 0x980 before unk14) → 2, li a0 at 31. Hmm, so sched still moved it after.

Let me check v_both_argfirst's disassembly to see the actual order.

Actually, let me just accept the wall. I've done ~70 tries and the residual is a deep sched tie-break.

Wait, actually, let me reconsider the whole thing. Maybe there's a simpler win: what if I DON'T use the do-while around the store, and instead the store sink + li/lui are BOTH caused by the missing barrier. The do-while around the store fixed the store but introduced the li/lui swap. What if there's a single construct that fixes both?

The barrier fixes both (score 0 with the barrier). Real C... the sibling said only the memory clobber works. 

Hmm, but our residual changed. Let me try: do-while around the store AND around the unk14 store (to fix the li/lui). v_both_dw14 = 4 (worse). 

Let me try: do-while around the store + reorder unk14 after 0x18. v_both_perm1 = 2.

Let me try a few more permutations with the both_dw base and the unk14 position, looking for the li a0 to come first.

Actually, let me try: what if the unk14 store is NOT the first tail statement, but the li a0 is forced first by making the first tail statement depend on nothing that sched prioritizes. 

I've tried perm1 (0x18 first) = 2. Let me try: 0x18, unk48, unk1C, then unk14, then call — v_u14_after1c = 11. Worse.

Hmm.

Let me try: keep unk14 first but make its value come from a load (not lui). E.g., `unk14 = *(s32*)&D_...`? Adds a load.

OK, I'm confident it's a wall. Score 2. Let me finalize.

Actually, let me reconsider the time. It's 05:10:15. Item 4 started ~04:56. 14 min. I need 20 → 05:16. Let me do a few more genuine tries (5-6 min), then write up.

Let me try:
- v_both_perm_variations: unk14 first but 0x18/unk48 reordered.
- v_both_call_first_arg: make the first arg 0 and second 0x980? No, wrong (signature: func_8002D4C8(0x980, 0) — first is 0x980).

Wait, func_8002D4C8(s32, s32) — the source call is `func_8002D4C8(0x980, 0)`. First arg 0x980 (a0), second 0 (a1). The target has li a0,2432 and move a1,zero. Yes.

Let me try swapping the arg computation order in source? Can't (arg order fixed).

Let me try: `func_8002D4C8(0x980, 0)` with the 0x980 as a `long`? no.

Let me try a few more tail permutations on both_dw and then finalize.

Actually, let me try something: what if I make the unk14 value a `u16` computation? No, it's s32.

Let me try: `((Unkstruct_800B5CB8*)a0)->unk14 = 0x200000;` → `CAST_WIDTH(s32, (u8*)a0, 0x14) = 0x200000;` tested (v_both_cast14 = 2). Same.

Hmm.

Let me accept the wall. Let me do 3 more tries to reach ~05:16, then write up.

Let me test:
- v_both_u18_first: 0x18, unk14, unk48, unk1C.
- v_both_u48_first: unk48, unk14, 0x18, unk1C.
- v_both_u1c_first: unk1C, unk14, 0x18, unk48.

Let me test.

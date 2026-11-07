---
ts: 2026-11-06T21:01:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0wVe0m2PTbZ63DEUw19U
---
All score 4. The a0/a1 swap persists. So the allocator consistently gives off a0, e a1. Target wants off a1, e a0.

Since e is only used once and off twice, maybe the fix is to give e more refs or off fewer. But off needs 2 uses.

What determines which reg? Let me look at local-alloc priority in GCC 2.7.2. Let me read the source: tools/reference/gcc-2.7.2/local-alloc.c. Actually maybe better to reason with a dump. But first, quick experiments on refs.

Idea: increase e's refs by using e in the lim load: `lim = ((s16 (*)[2])e)[idx][0];` This makes e used at the lim address AND at the condition. But then the address might be computed from e (a0) + off... which is what target does? No — target uses `at` for the lim address (D_801E8F78+off), and e (a0) separately. If we load lim via e, the address would be e+off using a0 as base → different instruction sequence. Might score worse.

Alternatively, reduce off's refs: can off be used once? The two uses: (1) address of lim load: `D_801E8F78[idx][0]` where cse turns idx*4 into off; (2) `(u8*)e + off + 2`. If we don't reuse off in the lim load, i.e. write the lim load so its address doesn't use off... e.g. `lim = ((s16*)D_801E8F78)[idx*2];` Hmm that's the same.

Wait — maybe the target's `off` (a1) is only used for the condition, and the lim address's `addu at,at,a1` reuses it. So off has 2 uses in target too.

Let me reconsider: maybe it's not off vs e priority but the *order of definition*. In target: sll a1 first (off), then lui a0 (e). In mine: sll a0 (off) then lui a1 (e). Both define off first. So the allocator gives the first-born (off) a0 in mine, a1 in target. What makes target give off a1?

Perhaps a0 is reserved/preferred by another pseudo that dies. Hmm, before this block, a0 was used at `lbu s0,0(at)`? No that's s0. a0 at this point... Actually at 6c: sra v1. Then 70: lui at. So a0 is free.

In mine, why does off get a0? local-alloc picks the lowest-numbered free reg by default? Then target must have a preference for a1 for off. Maybe because off's qty is tied to something.

Let me dump the RTL / reload for my build and target. Actually the target is the reference binary; I can't get its RTL. But I can compare: the target gives a1 to off. Why would off prefer a1? 

In local-alloc, a qty that is the result of a shift might get a preference from... Hmm.

Wait, maybe in the target, `off` is actually assigned to a1 because a0 was taken by something that dies just before, like `idx` (s0)? No.

Let me look more carefully: maybe the target's `e` is born BEFORE off in RTL even though asm shows off first, because sched1 reordered. The register allocation happens before sched1 (local-alloc is before sched1? order: local-alloc, global-alloc, reload, sched1, ... actually sched1 runs after reload). So the asm order reflects sched1 reordering, not allocation order.

So the allocation might assign a0 to e (born earlier in RTL, e's definition is `e = D_801E8F78` which in source comes... in orig, e is defined after off and lim but the barrier+launder). Hmm.

In RTL, e's def is `lui/addiu` and off's def is `sll`. Both in same block. local-alloc allocates qty's by priority: n_refs * something.

Let me actually read the local-alloc source to get priority formula, then compute. Or simpler: experiment by adding a dummy use of e that doesn't change code (a real use that folds away? no, must be real C).

Alternative move from catalog: "s16/u8 widths". Maybe if `e` is declared as `s16 *e` but `off` as `u32`, the allocator treats them differently? Widths affect mode/regs but both are SImode.

Let me try declaring off as `s32` (already) vs `unsigned`. v3 tried shift.

Let me look at the actual instruction count and see if maybe the whole block's allocation is by "birth order" and I need to define e in RTL before off. In source, to make e born before off, put `e = (s16*)D_801E8F78;` first (v2, v1 tried) — still 4. But RTL ordering might be preserved... it didn't help.

Hmm, let me check what local-alloc priority is. Let me grep local-alloc.c.

---
ts: 2026-11-06T11:35:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ieI7OMhbESamVkgz8UT3
---
My w1 got 78 instructions too? Wait, w1 has more lines. Actually the diff shows target has 79 lines, mine has more. Score? Let me see the score. Actually dt.sh tail 30 didn't show score line. Let me get score properly.

Wait, the score line is the first line of output ("score N"). With tail 30 I only saw the diff. Let me use tail 2 like default but capture first line. Actually the output format: first line score, then diff. Let me run and grep score.

Let me be systematic: create a helper that prints just score. Actually sc.sh does that: `bin/sc.sh $D $D/w1.c`. Let me use that.

But note my w1's second group loads (r2..r5) were placed before the Blk8 store D_80126968? In target, the order is:
- loads r2..r5 (v0,v1,a0,a1) from 200..0C
- loads r6,r7,r8,r9,r10 (a2,a3,t0,t1,t2) from 228,22A,294,298,29A
- stores r2..r5 to 26950..5C
- Blk8 copy 20210→26960 (uses a1,a0 = v0,v1)
- loads r2..r5 from 220,222,224,226 into v0,v1,a0,a1
- Blk8 copy 20218→26968 (uses t6,t5, t3,t4)
- stores r6..r10 to 26978,2697A,269E4,269E8,269EA
- stores r2..r5 to 26970..76

My w1 apparently reordered loads to near their uses (sched1), giving extra registers t3-t6. Hmm, actually mine interleaved loads with stores.

The key difference: in the target, the two Blk8 copies use different registers: first uses a1,a0 (which are v1? wait). Let me re-read target:

After storing r2..r5:
```
lui a1,0x0
addiu a1,a1,0     ; &D_80120210
lui a0,0x0
addiu a0,a0,0     ; &D_80126960
lwl v0,3(a1); lwr v0,0(a1); lwl v1,7(a1); lwr v1,4(a1)
swl v0,3(a0); swr v0,0(a0); swl v1,7(a0); swr v1,4(a0)
```
So Blk8 copy uses a1 (src ptr), a0 (dst ptr), and v0,v1 as the data. That's because r2..r5 values are dead after their stores, so v0,v1,a0,a1 are free; but they chose a1/a0 for the pointers and v0/v1 for the data. Interesting: a1,a0 got the pointer values.

Then second group loads r2..r5 from 220..226 into v0,v1,a0,a1.
Then Blk8 copy 20218→26968 uses t6,t5 for pointers, t3,t4 for data.

Then stores.

So the difference in the second Blk8 copy: target uses t6,t5 (ptrs) and t3,t4 (data) rather than reusing a0/a1/v0/v1 — because v0,v1,a0,a1 are live (holding r2..r5 second group).

OK so the allocation is deterministic given the code shape. My w1 differs because sched1 reordered and local-alloc assigned differently.

Hmm. The critical question: can plain C reproduce this? The pins forced r2..r5 to v0..a3. Without them, local-alloc might still assign the first group to v0,v1,a0,a1 if they're set first.

Actually in my w1, the first group loads... let me look at my w1.s beginning. The diff says target lines 1-26 deleted and w1 line 38 etc. Let me just view w1.s.

Actually let me think differently. Perhaps the original code used the *same* variable names reused (r2..r5) and gcc's global-alloc assigns them. The difference is likely sched1 ordering: in target, ALL loads happen first (first group, second group's r6..r10), then stores. In mine, sched1 moved loads down near uses.

Why? Because in the original there was a barrier (the asm memory clobber) between the first store group and the rest, which prevented motion. But also the pins forced registers.

Hmm, but the target IS the original game's compiled code. The original C (from the 1998 source) produced it without any asm. So there must be a natural C form. The barrier and pins were added by previous workers because they couldn't find it... but the task says "write a lever-free body that scores 0" — the premise is that it's possible.

Wait — actually, maybe not possible and this becomes a WALL. But the task wants attempts.

Let me think about what natural C produces this. The original likely:
```
s32 a, b, c, d;
u16 e, f;
s32 g;
u16 h, i;
```
and the ordering of loads in target: the first group (4 s32 loads) then the second group's 5 loads (u16,u16,s32,u16,u16) — all before any store. That's exactly the source order! So no reordering happened: loads first (as written), then stores. In my w1, sched1/combine reordered because there's no barrier.

Why did the target not reorder? In the original compiled code there is no barrier... unless the C was written such that the loads happen first due to dependencies. Hmm, but the stores to D_80126950 etc. depend on the loads. The compiler is free to schedule.

Wait — maybe the key is that the original had the loads in the declaration initializers or something. Or maybe the original code was in a loop?

Alternatively, maybe the pins are actually needed and this is a WALL. But the brief says "write a lever-free body that scores 0" as the goal; WALL is allowed with 20-30 min and 30 tries.

Given 4 items and 20-30 min each, let me not over-invest. But let's give it a fair shot.

Important: the barrier in the original is `__asm__ __volatile__("" ::: "memory")`. A memory clobber prevents the compiler from moving memory ops across it. Without it, the compiler can reorder loads/stores freely. The target ordering (all loads, then stores) is a valid schedule the compiler chose naturally. In mine, it chose a different one.

But actually, the target might be achievable with a different code shape. Let me look at the exact target vs mine differences:

Mine (w1):
- lines 1-26 of target (first group loads + first 4 stores) are missing at the top → in mine they occur later (line 38+).
- mine has t3,t4,t5,t6 loads early (lines 13-20 in w1 numbering).

Hmm wait, "1,26d0" means target lines 1-26 deleted. Then "38a13,20" adds t3..t6 loads. So mine starts at target line 27-ish. So mine's order: first the lui/addiu for Blk8 (lines 27-38 of target), then loads t3..t6, etc. So sched1 moved the first group's loads/stores down.

So mine essentially starts with the Blk8 copy? That seems like a big reorder.

Let me look at my w1.s fully to understand.

Actually, let me consider: maybe the natural form is to use a struct copy! D_80126950 = r2 etc. Maybe the original used an array/struct assignment: `*(struct {...}*)&D_80126950 = *(struct {...}*)&D_80120200;` That would be a memcpy-like pattern. But the target shows individual lw/sw, not lwl/lwr... The Blk8 copies use lwl/lwr (struct/8-byte copy).

Hmm.

Let me step back and consider the practical approach: try a bunch of real-C variants and see scores. Time budget: item 1 started 04:32. Let me spend until ~05:00.

Let me first get the score for w1.

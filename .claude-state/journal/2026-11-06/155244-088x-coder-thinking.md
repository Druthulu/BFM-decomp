---
ts: 2026-11-06T22:52:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KY9eNC3ThOO1vRJbBcwK
---
In w11: r75 = s0 (3 refs/7, 2 bytes — HImode, crosses the call, local). So the s16 raw load is local and takes $s0. d conflicts s0 → $s1.

But r72 = v0 (the arg0 copy is present, 75 ins).

Hmm. So w11 has the arg0 copy and 75 ins, but the swap. w6 has the swap fixed but no arg0 copy.

Interesting: the s16 makes the arg0 copy appear (r72=$v0). So the schedule is the w0-like schedule in w11. The difference between w6 and w11: the s16 mask.

What if I combine: mask-in-place with a *separate* global s1ang and the raw load local but... hmm.

OK, let me think about the goal: I need the raw s1ang load to NOT take $s0. In w6 it's global (7 refs/22, pri 6363 < d 10000) → d wins. In w11 it's local (3 refs/7) → takes $s0.

So the mask-in-place with s32 makes the raw load global; with s16 it doesn't.

In w6, the raw load is r75 with 7 refs/22 — global (used in multiple blocks: the mask reassignment in block 0 and the uses of s1ang in the arms). Hmm, in w6, s1ang is reassigned and used in the arms, so the *same pseudo* (r75) is used across blocks → global. The raw load is part of r75 (same pseudo). So r75 is global.

In w11 (s16), the raw load is r75 (HImode, 3 refs/7, local) and the masked value is r99 (global). So s16 split them into two pseudos: the HImode load and the SI masked value. The raw HImode pseudo is local.

So for the globalisation to work, the raw load must be SI (s32) so it's the same pseudo as the masked value.

OK so w6 is the only one with d=$s0. Its issue: no arg0 copy + schedule.

Hmm, but w6's schedule: the lw first. w11's schedule: arg0 copy present (w0-like). So the schedule difference is caused by the mask-in-place (global s1ang) vs the s16 split.

Let me try: w17 = w6 (mask-in-place, s32) but with an explicit arg0 copy that is forced. The problem is the tie: r72 must die at the lw. In w6, r72 is live after the lw (schedule).

What if I make arg0's last use the lw by construction? E.g., compute the ratan2 args BEFORE the pointer load in the source AND ensure the scheduler doesn't move the lw up. The scheduler moves based on priorities.

Alternatively: use a separate variable for the pointer load and make the lh uses depend on a *different* arg0 pseudo? Hmm.

Wait — actually, maybe I can make the arg0 copy explicit and non-coalescible by using arg0 in a way that keeps it live... no.

Let me look at w6's schedule issue differently: the lw (insn 16) has priority 1, the lh (insn 25/29/35/39) priority 1, insn 20 priority 2. In w6, the ready list at T-8 chose 45, 43, 20 (20 last). In w0, chose 20 first ("insn 20 has a greater potential hazard").

The "potential hazard" depends on the instruction units and the clock. The difference between w0 and w6 at T-8: the ready list contents. In w0: "20 (7f000001) 43 (7f000001) 45 (7f000001), now 45 43 20" then "insn 20 has a greater potential hazard, now 20 45 43". In w6: "20 (2) 43 (7f000001) 45 (7f000001), now 45 43 20" — 20's value is 2 (not 7f000001). The value 0x7f000001 vs 2: this is the "priority" with flags. Hmm, 7f000001 = 0x7f000000 | 1. The 0x7f000000 might be a "was in the ready list" flag or a hazard marker.

Hmm, in w0, insn 20's ready value is 0x7f000001; in w6, it's 2. The value encodes the priority (2) plus a flag. The 0x7f000000 flag might be "blocked/queued" or "adjusted priority".

This difference likely comes from the priority adjustment (`adjust_priority`) or the `INSN_PRIORITY` computation.

I think this is a sched1 tie-break that's very hard to control via C without changing the insns.

Given the time (now ~16:00, 34 min elapsed), I should decide: continue trying a few more variants, then record a WALL with ≥30 tries. I've done about 18 scored tries now (w0-w17 minus some). Let me count: baseline prev_win (1), w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w16 = 15. Plus the --explain (not a try). I need ≥30 scored tries for a WALL. Let me do 15+ more variants efficiently.

But let me also make one more serious attempt at the MATCH. 

Idea: what if the mask-in-place is done on a COPY, keeping u6, such that the raw load is global but the structure/schedule is like w0? 

Specifically: 
```
u6 = s1ang & 0xFFF;      // block 0, compare
if (u6 == u5) return 0;
iVar4 = u5 - u6;
s1ang = u6;              // copy in block 2 (coalesced)
if (iVar4 > 0x800) { t = s1ang + 0x1000; ... }
```
Here the load pseudo is used in block 0 (u6's and). The copy `s1ang = u6` is a different pseudo. The load pseudo stays local. No good.

What if the mask is computed in block 2 (after the compare) and the compare uses... the target's andi is in block 0.

Hmm.

What about making the raw load global via a *second load* that's eliminated? E.g.:
```
s1ang = *(s16 *)(...);
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (iVar4 > 0x800) { t = (*(s16 *)(...)) & 0xFFF; ... }   // redundant load, cse'd?
```
The second load would be cse'd to the same pseudo (if the memory isn't clobbered) — cse2 might keep the value. But the load is across the call... cse would need to keep the loaded value live. It would reference the same pseudo in block 3 → global. And the second and would be merged with u6 (if cse follows). Hmm, if cse merges both the load and the and, no globalisation.

Hmm.

OK here's another thought: what if I use a *different* variable for the divisor that is NOT a copy from arg1? E.g., compute `d` from arg1 via a cast at entry? No.

Wait — the core issue in w0 is local-alloc giving the raw load $s0. What if the raw load's qty is LOWER priority than another local qty that takes $s0? In block 0, the local qtys are: r72 (arg0, 4/6), r75 (s1ang, 2/7), r80, r81 (pointer), r85, r88, r92, r95, r99, r100... The allocation order is by priority (qty_compare: floor_log2(n)*n*size/(death-birth)*10000). r72 (4/6): floor_log2(4)=2, 2*4/6*10000=13333. r75 (2/7): 1*2/7*10000=2857. So r72 is allocated first. r72 takes $v0 (or $a0). Then r75 takes... the first free callee-saved: $s0.

To make r75 take $s1, another local qty with higher priority must take $s0. Which local qty could take $s0? Any block-local pseudo that crosses a call. In block 0, only r75 crosses a call (besides r72? r72 doesn't cross). Hmm.

Wait, in w3, r72 (arg0) crossed a call and took $s0! That happened because the schedule made r72 live across the call. In w3, r72 = 4 refs/8, crosses a call → $s0. Then d conflicts $s0 → $s1.

Hmm, so if r72 (or another local) takes $s0 and its live range... d conflicts it → d gets $s1. Bad.

So no local $s0 allowed.

OK, let me think about the possibility that the target's d=$s0 came from a different source structure where s1ang raw is global. And the schedule/arg0 difference is specific to our mask-in-place formulation. Maybe the original source had `u6` computed differently.

Hmm, what if the original source had the s1ang load and the mask in a single expression assigned to a variable used later, making it global:
```
s1ang = (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF;
```
Then s1ang (global, used in the compare and arms) is the masked value. The raw load temp is local. Hmm, same as w11's structure (raw local).

But wait — in the target's RTL, the raw load pseudo (r75) and the masked value (r77) are SEPARATE pseudos! r75 is local, r77 is global. So the original source likely had `s1ang = load; u6 = s1ang & 0xFFF;` with s1ang and u6 separate. And r75 (raw) is local, taking $s1 because $s0 is pinned.

So in the ORIGINAL (no pin), r75 would take $s0... unless something else. Hmm.

This suggests the original source may have had something that makes r75 not take $s0. What if the original had the pointer load's result (r81) also crossing the call? Hmm.

Wait — maybe the original had NO pin and the allocation was different because the original source had a different number of pseudos (e.g., the original used `d` differently). The decomp's body is a reconstruction; the original might have had `d` as `arg1` used directly, or the cast in a different place.

Hmm, but the instruction stream is fixed (target). The RTL structure is fixed. Only the source's exact form differs, and the decomp found a body that produces the target RTL with the pin+keepalive. The original body must produce the same RTL WITHOUT the levers. The RTL is the same, so the register allocation difference must come from... the same RTL → same allocation! 

Wait, that's a key point: if the RTL is identical, the register allocation is identical. The pin changes the RTL (a hard-reg variable is a different RTL). So the original's RTL must differ from the decomp's pin+keepalive RTL — yet produce the same instruction stream.

Hmm, the instruction stream is the same (score 0 with the pin). But the RTL with the pin has d as a hard-reg variable; the original's RTL had d as a pseudo. Different RTL, same final instructions. Possible.

So the original's RTL (no pin) produced d=$s0. Our lever-free RTL produces d=$s1. So the original's RTL must differ from our lever-free RTL in a way that changes the allocation but not the instructions. E.g., the original had s1ang raw as a GLOBAL pseudo (different live ranges) or the cast structured differently.

The decomp's lever-free body (removing the pin and keepalive) gives the 21 residual. The original body must differ. What could it be? Perhaps the original had:
```
s32 s1ang = *(s16 *)(...);   // init at declaration
```
or the variables declared differently.

Or maybe the original had the `u6` computed inside the if, or the `d` cast via a different expression.

Let me look at the target RTL more carefully for clues: the target's RTL (from the pin build) has r75 (raw load) LOCAL and r77 (u6) global. If the original's RTL had the same structure (same pseudos), the allocation would be the same as our lever-free version (d=$s1). But the original gave d=$s0. Contradiction — unless the original's RTL had different pseudo structure.

Hmm, wait. The pin build's RTL: the pin is a hard-reg variable. The RTL around it: `(insn 6 (set (reg $16) (reg $5)))`. Without the pin, `(insn 6 (set (reg r74) (reg $5)))`. The rest of the RTL is the same (same pseudos r75, r77, etc.). So the allocation difference is only due to d being a pseudo vs hard reg.

In the original (d a pseudo), the allocation would be the same as our lever-free → d=$s1. But the original's binary has d=$s0. Contradiction!

Unless the original's RTL differs elsewhere (e.g., more/fewer pseudos). Hmm. OR the original was compiled with a different gcc version/flags? No, the project's toolchain matches.

OR the decomp's lever-free body is not the original source, and the original source produced a slightly different RTL that still yields the same instructions.

Hmm, this suggests the crack might be possible via a source form that changes the RTL pseudos.

Let me think about what source form would make the raw load global in the ORIGINAL sense. The target's RTL has r75 local. If the original's RTL had the raw load global, the register allocation would differ. But the target's instruction stream (from the pinned build) has `lh $17` and `andi $17,$17` — consistent with either.

So the original's RTL might have had s1ang raw global! And the decomp's reconstruction made it local. If I make it global (mask-in-place), I get d=$s0 — matching the original's allocation. But then the schedule/arg0 differs from the target.

Hmm, but the target's instruction stream comes from the pinned build, whose RTL has r75 local. The sched1 decisions were made with that RTL. If the original's RTL had r75 global, the sched1 decisions might differ... but the target's schedule is what it is. So the original's schedule matched the target's. 

Wait, the pinned build's schedule matches the target's (score 0). The pinned build's RTL has r75 local. sched1 ran on that RTL (before local-alloc, so r75's local/global status isn't known to sched1 — sched1 only sees pseudos). So the schedule depends on the RTL insn structure, not the local/global status. Our lever-free RTL (w0) has the same insn structure as the pinned RTL (except d's hard reg vs pseudo) → the same schedule. Indeed w0's schedule matches the target.

Our w6 (mask-in-place) changes the RTL structure (s1ang reassigned) → different schedule.

So the original source must have an RTL structure like the pinned one (r75 raw local, r77 u6 global) to get the target schedule — but then the allocation would be d=$s1. Contradiction with the target binary!

Unless... the original's RTL had the same INSN structure but different pseudo liveness (e.g., s1ang raw global). The schedule depends on the insns/dependencies, not the pseudo liveness (mostly). Hmm, but sched1's priority/hazard depends on REG_DEAD notes which depend on liveness. Hmm.

Actually, maybe the original's RTL had r75 global and the schedule still matched. The mask-in-place (w6) changed more than the liveness: it reassigned s1ang, eliminating u6 and changing the dependency graph (the and writes s1ang, the compare reads s1ang, the arms read s1ang). That's a bigger change than just making r75 global.

So: I need to make the raw load global WITHOUT changing the insn structure. The insn structure: load, and, compare, arms. The and's result (u6) is global; the raw load is local. To make the raw load global, it must be live across a block boundary. The raw load's only use is the and in block 0.

Unless the raw load is used in another block... which requires an insn.

Hmm, what if the raw load is used in a PHI-like way? No.

What if the load is moved to a different block (e.g., inside an if)? The target's insn order has the load in block 0.

Hmm.

OK, let me consider the possibility that the original source had `s1ang` as a *parameter-like* or the load result used differently. 

Actually, maybe the original had TWO variables: `s1ang` and the load done twice? No.

Let me try another approach: maybe the allocation can be fixed by making the raw load's local-alloc choice $s1 via a *tie* with something in $s1. If the raw load were tied to a pseudo in $s1... e.g., `s1ang = *(s16*)(...); s1ang2 = s1ang;` — a copy that local-alloc ties. Hmm.

Actually, local-alloc ties a pseudo with its copy source: `x = y` where y dies → tie. If `s1ang` is the load and we copy it, they tie into one qty. Still takes $s0.

Hmm.

What if we make the raw load's qty include a *hard reg suggestion* for $s1? The suggestion comes from an insn with a hard reg operand. Hmm.

OK, time to be pragmatic. Let me do a few more variants, then write the WALL. But actually, wait — let me reconsider the best score. w6 = 38 with the right d/s1ang but the wrong schedule/arg0. w7 = 33. Hmm, w7 is the best. Let me re-examine w7: 33 with 74 ins, d=$s1. 

Hmm, actually the WALL "best" is the lowest score of a lever-free body. w7 = 33.

But maybe I can do better. Let me try the w0 structure (u6, do-while cast) with the mask-in-place applied to a SEPARATE variable used in the arms, to globalise the raw load without changing the compare/and structure:

```
s1ang = *(s16 *)(...);
u5 = ...;
do { d = (s16)d; } while (0);
u6 = s1ang & 0xFFF;
s1ang = u6;            // globalise s1ang (copy in block 0)
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (iVar4 > 0x800) { t = s1ang + 0x1000; iVar4 = u5 - t; }
...
```
Here the raw load is used in block 0 (u6's and). The copy `s1ang = u6` makes s1ang a global pseudo used in the arms. But the raw load pseudo is still local (used once). Hmm, no good.

Unless the copy is coalesced into the raw load... `s1ang = u6` coalesces with u6, not the raw.

Hmm.

What if we do `s1ang = s1ang & 0xFFF;` (reassign) but the compare uses u6 = the OLD s1ang? Can't — after reassignment, the old value is gone.

What if:
```
u6 = s1ang & 0xFFF;
s1ang = u6;
```
The raw load (s1ang before the reassignment) is used only by u6's and. Local.

OK.

Let me try yet another angle: what if the divisor d's priority can be raised above the local-alloc? No, local-alloc ignores globals.

What if we make the raw load's live range shorter so it doesn't cross the call? The load is before the call, used after. If the *and* were before the call, the raw load wouldn't cross. The target's andi is after the call. Hmm, but what if sched1 could move the andi before the call? No.

What if the source computes u6 before the call? `u6 = s1ang & 0xFFF;` before u5's statement. Then the and would be before the call (instruction order change). The target has it after. Unless sched1 moves it after? sched1 won't move it after the call if it's before.

Hmm.

Let me try: what if the raw load is HImode but the mask keeps it SI... w11 showed the raw HImode is local.

I think this is a genuine wall. But let me do a few more tries to be thorough and reach 30.

Actually, wait! Let me reconsider the target's RTL: r75 (raw load) is local, 2 refs, crosses a call. Local-alloc gives it $s0 (in our lever-free). But in the ORIGINAL (no pin), the same local-alloc would give $s0 too... unless the original's block-0 qty order differed.

What if the original had another local qty in block 0 that took $s0, and its live range didn't conflict with d? Impossible (d spans).

UNLESS d's live range in the original was NOT from entry. What if the original source was:
```
s32 d;
...
d = arg1;   // after the ratan2 call?
```
Then the target's `move $16,$5` at entry wouldn't match. Hmm.

Wait, actually, let me re-look at the target asm: `move $16,$5` at entry. But maybe that move is NOT `d = arg1`; maybe it's the callee-save of $a1 because arg1 is used later. Hmm, same thing.

Hmm, what if the original had `d = arg1` at entry but the pseudo was coalesced with the *cast* such that... 

I'll stop theorizing. Let me do more empirical tries.

Let me try a batch of variations on w0 (which has the right schedule) targeting the d/s1ang swap via different means:
- w18: w0 with the declarations of d and s1ang swapped.
- w19: w0 with `d` initialized at declaration (`s32 d = arg1;`).
- w20: w0 with the do-while around the div block too.
- w21: w0 with the mask-in-place but the arms using u6 (so s1ang is global via a later use)... hmm.
- w22: w0 with `u6` computed before the cast.
- w23: w0 with the cast as two statements (d <<= 16; d >>= 16).
- w24: w0 with `t` scoped inside the arms.
- w25: w0 with `q` scoped inside the arms.

Let me create and score them. Each sc.sh line is a try.

Actually, since the WALL requires 30 scored tries, let me generate a bunch. But I should focus on plausible cracks.

Hmm, let me reconsider the sibling func_8012BB3C's win.c more carefully. It cracked the pin with a do-while on the div block, raising div's refs 7→9 so div gets $s0. In OUR function, the div block do-while (w9) gave 38. But w9 also had the mask-in-place. What about the do-while on the div block WITHOUT the mask-in-place (w0 + div do-while)? That's w20. Let me test: it raises d's refs, which might make d's priority high enough to... no, d still conflicts $s0 (local r75). Priority doesn't help against local-alloc.

Hmm, right: the conflict with $s0 is from the local r75, so raising d's priority doesn't help. The sibling's function had no local pseudo in $s0 (their 'a' was a parameter, not a memory load!). So their fix worked.

Our function's blocker is specifically the memory-load local pseudo.

So the ONLY way is to make the raw load not local or not $s0. The mask-in-place makes it global (w6). 

Let me try to make the raw load global with a *different* structure that keeps the schedule: what if the load is used in the arms via a *second variable* that is a copy of the raw load (not the masked value)? E.g.:
```
s1ang = *(s16 *)(...);
u6 = s1ang & 0xFFF;
...
if (iVar4 > 0x800) { t = (s1ang & 0xFFF) + 0x1000; ... }
```
The second and in the arm block (single-pred, cse follows → merges with u6). Hmm.

What if the second use is in a block cse doesn't follow (multiple preds)? The merge block after the two ifs: 
```
if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }
if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; }
if (iVar4 >= 0) { q = iVar4 / d; ... }
```
The block with `if (iVar4 >= 0)` has 2 preds (the two arms). If I use `(s1ang & 0xFFF)` there... it's not needed. Hmm, could I use s1ang in the div? `q = iVar4 / d` — no.

What about the compare `if (u6 == u5)` — block 0.

Hmm.

What if the arms use s1ang raw in a semantically valid way: `t = (s1ang & 0xFFF) + 0x1000` in the SECOND if (merge block, 2 preds) → cse won't merge → extra andi. 76 ins.

But wait — maybe the extra andi gets eliminated by combine? `(s1ang & 0xFFF) + 0x1000` — no.

Hmm, but what if the extra andi is in a block and the target has... no, the target has exactly one andi.

OK, I'm convinced the MATCH is very hard. Let me do a batch of ~15 more tries to reach 30, then record the WALL with the best score.

Wait, actually — let me reconsider the 74 vs 75 instruction issue in w6. Maybe I can accept w6's d/s1ang and fix the arg0 copy via a source change that forces the tie. 

In w6, the lw is scheduled first, so arg0 is live after. What if I split the pointer load into a separate statement placed LATER in the source? E.g.:
```
s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
```
The pointer load is part of this statement (first). The scheduler hoists it. If I move the s1ang load statement after u5, the pointer load might be scheduled later (w10 = 45, 75 ins!). w10 has 75 ins! Let me check w10's diff: score 45, 75 ins. Let me look at its alloc/diff.

w10: d=$s1 or $s0? Let me diff.

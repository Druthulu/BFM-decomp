---
ts: 2026-11-06T22:43:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_p14w9H4DE2stKyN3O63U
---
In w7: s1ang (r75) = 7 refs/22, pri 6363; d (r74) = 7 refs/27, pri 5185. So s1ang (6363) > d (5185) → s1ang allocated first → takes $s0. That's the wrong direction.

In w6 (with do-while), d = 9 refs/27 = 10000, s1ang = 7/22 = 6363. The do-while on the cast raised d's refs from 7 to 9, pushing its priority to 10000 > 6363. That's why w6 worked!

So the do-while on the cast is essential for d's priority (it raises d's refs). And the mask-in-place raises s1ang to 6363. d needs > 6363 → the do-while gives 10000.

So w6 is the right combination for the d/s1ang assignment. But w6 perturbs u5/iVar4 and loses the arg0 copy.

Hmm. So with the pin removed, we need:
1. d priority > s1ang's (do-while on cast + mask-in-place).
2. But the do-while perturbs u5/iVar4.

Wait, actually, in w6 the u5/iVar4 issue: u5=$v1, iVar4=$a1. In the residual (score 21), u5=$a0, iVar4=$v1. The difference is caused by the do-while (which changes the .greg set/priorities).

Let me look at w6's .greg order: 77 79 78 74 76 75. And the target's: 78 80 79 77 76.
- w6: r77 (30000, 10/10) = iVar4; r79 (20000, 4/4) = ?; r78 (17500, 7/8) = ?; r74 (10000, d); r76 (7142, 5/14 = u5); r75 (6363, s1ang).
- Target: r78 (30000, 10/10) = iVar4; r80 (20000, 4/4); r79 (17500, 7/8); r77 (10000, 5/10 = u6); r76 (7142, 5/14 = u5).

Hmm, the priorities differ: in w6, u5 (r76) is 7142 (5 refs/14) — same as the target. But the .greg order in w6 has r75 (s1ang, 6363) LAST, after r76. In the target, s1ang is local (not in .greg).

The issue is u5's assignment: target $a0, w6 $v1. In w6, the .greg order: iVar4 (30000) first → $v1? Then r79 (20000) → $v0? (prefers v0), r78 (17500, prefers v1,a1) → ..., d (10000) → $s0, u5 (7142) → $a0? Hmm, but the asm shows u5=$v1.

Wait, w6's asm: `subu $5,$3,$17` — hmm let me re-read w6's asm: `lh $6,14($4)` (arg0+0xE → $6=a2), `subu $5,$3,$5` (the ratan2 arg), `addu $2,$2,-1024`, `andi $3,$2,0x0fff` (u5=$3=v1), `subu $5,$3,$17` (iVar4=$5=a1). So u5=$v1, iVar4=$a1.

So in w6: iVar4=$a1 (prefers v1,a1 → got a1), u5=$v1. In the target: iVar4=$v1, u5=$a0.

The preference "prefers v1,a1" for iVar4 (r77 in w6): it prefers v1 AND a1. In the target, r78 has no preferences. The preference comes from set_preference (copies). Hmm.

OK let me think about what causes iVar4 to prefer a1/v1. In w7, r77 (iVar4) prefers v1,a1; r78 prefers v1,a1. In the target, no preferences.

The preferences come from copies where the dest is a pseudo set from a reg. iVar4 = u5 - u6 (not a copy). But maybe there's a `REG_EQUIV`/copy involved. Hmm, actually `expand_preferences` merges preferences through copies with dying srcs. iVar4 might be connected to q (r79) via a copy? In the arms, `q = iVar4 / d` and `move v0,q`. Hmm.

Wait — maybe the preferences come from the *hard reg $a1* being the argument arg1, and `d = arg1` creates r74 = $a1 with a preference for a1. Then expand_preferences merges r74's preference with... r74 dies in the div? No.

Hmm, in w7 the greg dump would show "74 preferences: 5" (a1) and maybe others. Let me look at the w7 greg preferences.

Actually, the important thing: the preferences appear in the lever-free bodies but not in the target. Why not in the target? Because the pin changes the RTL (the pin's hard reg assignment changes the copies). Hmm.

Hmm, wait. In the target, the pin `d __asm__("$16")` means d is a hard-reg variable; `d = arg1` becomes `move $16,$5` at entry, and d is not an allocno. So there's no r74=copy-of-a1 preference. Without the pin, `d = arg1` creates a pseudo copy r74 = $a1, which sets a preference for a1 on r74, and expand_preferences spreads it to connected allocnos (r78/r79?).

So removing the pin introduces the a1 preference on the d pseudo, which propagates and changes iVar4/u5's allocation. That's the root of the u5/iVar4 shift.

How to avoid the a1 preference? If d is not a copy from arg1 but arg1 itself (w4), then there's no `r74 = $a1` copy... but w4 scored 38 too. Let me check w4's alloc: r73 = d (9 refs/27, conflicts s0), and r74 = s1ang. Hmm, w4 still had the swap.

In w4, arg1 is the divisor directly; the parameter pseudo is in $a1 initially. Does it get a preference for a1? The parameter is born in $a1; `set_preference` isn't called for parameters (no set insn). Hmm.

Let me test w4's diff to see if u5/iVar4 are correct there. w4's alloc table: r77 (10/10) = iVar4, r79 (4/4), r78 (7/8), r73 (d, 9/27), r76 (5/10 = u6), r75 (5/14 = u5), r74 (s1ang, 2/7). Preferences: r77 prefers a1; r76 prefers s0; r79 prefers v0; r78 prefers a1.

Hmm, still preferences. Let me get w4's diff.

Actually, let me reconsider the whole approach. The target's allocation:
- d = $s0 (pinned)
- s1ang raw = $s1 (local)
- u6 = $s1
- u5 = $a0
- iVar4 = $v1
- q = $v1
- arg0 copy = $v0, tied with the pointer

Without the pin, we need d to get $s0. The mask-in-place + do-while does that but introduces preferences that shift u5/iVar4.

What if we could make d get $s0 WITHOUT making it a copy-of-arg1 pseudo? E.g., d is assigned $s0 by global-alloc because it's the first in the .greg order with no preference... In w4, d (r73) is the arg1 pseudo. Its preference? Let me check w4's greg dump for r73's preferences.

Hmm. Let me look at w4's greg dump preferences quickly.

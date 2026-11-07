---
ts: 2026-11-07T00:05:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mzNKWiMEjv7wA9qbAG83
---
nolau (pins kept) differs only at insns 29-30: `bgez v1, 5afc; slt v0,s1,v1` vs target `bgez v1, 5af8; nop`. So a branch target offset differs and a nop vs slt.

That's the first max comparison: `if (iVar5 < iVar4) iVar5 = iVar4;` where iVar4 was laundered. Without the launder, the first max's slt gets placed in the delay slot and the branch target shifts.

Hmm. So the launder's effect is subtle here: it makes iVar4 a separate pseudo so the first `slt` isn't in the delay slot.

OK so with pins, the launder removal costs 2. Without pins, the launder removal costs more (39-34 = 5). 

Now the big issue is the PINS (34 points): the param register permutation + the t/v0 copies.

So the crack requires reproducing the pinned register assignment naturally. This is exactly the global-pri-bank-order wall again, but maybe more tractable here.

Let me focus on the pins:
1. param_3 $21 (s5), param_4 $19 (s3)
2. t $2 (v0)

With pins: params p1=s2, p2=s4, p3=s5, p4=s3. Without: p1=s3, p2=s5, p3=s4, p4=s2.

And t: with the pin, t=v0 and iVar5=s1 with copies. Without, t merges into iVar5/iVar4.

Hmm. So both are allocation issues.

Let me think about the natural C that yields p1=s2, p2=s4, p3=s5, p4=s3.

Priority order needed: p1 > p4 > p2 > p3.

Hmm, and iVar1/iVar5 take s0/s1.

Let me get the full target assembly to understand. Let me dump the target object for the includer ov_MAIN_012. Find the .o.

Actually, the diff already gives enough.

Let me try the param-copy permutation approach: reorder the 4 assignment statements. Since live lengths depend on where each param is first assigned, reordering shifts priorities.

Current C order: p1, p2, p3, p4 → live: p1 longest.
Priorities mine: p4 1449 > p1 1369 > p3 428 > p2 422.

Hmm, p4's live is 69, p1's 73. p4's first ref is later (assigned 4th) so its live is shorter → higher priority. So assignment order matters: later assignment → shorter live → higher priority.

To get p1 > p4, p1 must be assigned LATER than p4. So the C order should put p1 last among {p1,p4}.
To get p2 > p3, p2 must be assigned later than p3.

Target order: p1 > p4 > p2 > p3. So assignment order (later = higher pri): p3 first, then p2, then p4, then p1. I.e., C order: p3, p2, p4, p1.

Hmm, but the target's *emitted* copy order is p1, p2, p3, p4. sched1 can reorder.

Let me just try all 24 permutations. That's cheap: 24 scores × ~1-2s each = ~1 min.

But careful: the pinned version's params are pinned, so reordering wouldn't affect the target. For the lever-free search I use the lever-free body (pins removed). So I'll permute in the lever-free body.

Wait, but I also need the t fix. Let me first see if the permutation alone reduces the 34.

Let me generate 24 permutations of the 4 param assignments (in the lever-free body) and score them.

Note: the lever-free body currently is score 39. Let me permute.

Hmm, but the priorities also depend on the *last use* of each param. p1 is used in func_80013350 (in the loop), p4 in the loop, p2/p3 in the loop. All in the loop. So the last-use positions differ by a few insns.

Let me do the permutation search.

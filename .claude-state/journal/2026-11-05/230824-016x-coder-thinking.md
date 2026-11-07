---
ts: 2026-11-06T06:08:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sdkFX7SPyxCmItFrduWc
---
So it's purely the two callee-saved registers swapped: a0 (param, long-lived) should be $16 (s0) and the loop pointer s2 should be $17 (s1).

In global.c allocation order, allocnos are sorted by priority (number of refs weighted by loop depth) and assigned in order from available regs. So a0 should get a higher priority than s2. In my build, s2 gets $16, meaning s2 has higher priority than a0. Hmm, but a0 is used in ~55 places. Unless... global-alloc considers a0's pseudo split? Or a0's allocno is a hard reg already? a0 is the parameter — in the entry block, the parameter is in $4 (a0), and it must be copied to a callee-saved reg since it's live across calls. That copy happens in global-alloc's "copy preference" logic. Hmm, but the target does `move s0,a0` at insn 2.

Actually the register assignment for the param pseudo: global-alloc allocates the pseudo to $16 because the function's param hard reg a0 is live at entry, and the pseudo gets a copy preference... hmm, no: the pseudo is the same pseudo as the arg? In gcc 2.7, the argument pseudo is a normal pseudo initialized by the prologue copies. So the priority of that pseudo is its ref count; it gets $16 normally as the highest priority one.

Wait, mine has s2 → $16 and a0 → $17. So s2 has higher priority than a0. Why? Because of loop weighting: s2's refs are inside the do-while loop (depth 1?), so they're weighted more heavily. Hmm but the target has a0 in $16, so in the real build a0's priority wins... but wait, in the target the pin forced s2 into $18, so a0 took $16 naturally and s3/s4 took $17 etc. Hmm, actually with the pin, s2 was reserved in $18, so $16 went to the next-highest priority allocno = a0.

Lever-free, s2's priority exceeds a0's, so s2 takes $16.

Options in plain C:
1. Increase a0's refs (loop-weighted) — e.g., use a0 more inside the loop? That would change code.
2. Decrease s2's refs — e.g., reuse a different pointer variable inside the loop for some accesses? But that changes the loop.
3. Change the loop so loop.c doesn't weight s2 so much... 

Hmm. Wait: but actually the ordering is: with the pin, the pin is in $18, and $16/$17 are free. So the pin didn't affect the a0 vs s3/s4 ordering. Lever-free the bank has 3 callee-saved: s0,s1,s2 = a0, s2loop, s3? Let me look: register pairs report: mine->target: s1->s0 x55 (a0), s0->s2 x11 (??), s2->s1 x3.

Hmm interesting: mine has s0 → target s2 in 11 places. So there's a third variable: mine s0 vs target s2. Let me think about which variables: a0 param, s2 loop ptr, s3 (a0+4), s4 (flag), s5 (end ptr), ent (s16*).

Target allocation: a0→s0, s2loop→s1, and something in s2 (mine s0). Mine: a0→s1, ?→s0, s2loop→s2.

Hmm so mine: a0 s1, s3? s0, s2loop s2. Target: a0 s0, s2loop s1, s3? s2.

Wait: pairs "s0->s2 x11" means mine s0 corresponds to target s2. Which variable is that? Let me look at the diff lines: at 234 `sw s0,204(s1)` mine vs `sw s2,204(s0)` target — that's the `unkCC = (s32)s2` store: storing the loop pointer into unkCC. So target: `sw s2,204(s0)` — s2 register holds the loop pointer value, base s0. Mine: `sw s0,204(s1)` — the loop pointer is in s0 (mine), base a0 in s1.

So actually mine: loop ptr = s0, a0 = s1, and target: loop ptr = s1, a0 = s0. And the third register s2 in target holds something else (s3 = a0+4 maybe). Hmm "s2->s1 x3" means mine s2 → target s1, 3 occurrences — probably a few instructions where mine's s2 (loop ptr) corresponds to target's s1 (loop ptr). Yes! The loop pointer: mine = s0 in 11 places and s2 in 3 places? That's odd — unless the loop pointer pseudo got split/coalesced differently.

Hmm, wait. Actually the count report says "register pairs (mine -> target, count): s1->s0 x55, s0->s2 x11, s2->s1 x3, a1->a0 x1". So mine s1→target s0 (55), mine s0→target s2 (11), mine s2→target s1 (3).

Hmm, so in the loop region target uses s1 for the loop pointer and mine uses s2 in 3 places. And mine s0 → target s2 11 times: what's mine s0? Perhaps the s3 (a0+4) or... Let me look at the loop: target:
```
lw v0,28(s1)? 
```
Hmm, in the loop body at 242-244: mine `sh v0,22(s1); addiu s0,s0,268; bne s0,s5` vs target `sh v0,22(s0); addiu s2,s2,268; bne s2,s5`. So the loop pointer: mine s0, target s2! And the base a0: mine s1, target s0. So target has a0 in s0, loop ptr in s2, and s1 is something else.

Hmm wait, that contradicts: "sw s0,204(s1)" mine vs "sw s2,204(s0)" target — mine: value loop ptr in s0, base a0 in s1; target: value loop ptr in s2, base a0 in s0. Consistent: mine a0=s1, loopptr=s0; target a0=s0, loopptr=s2.

So what's target s1? Maybe s3 (a0+4) or ent. And mine: where is s3? Perhaps mine s2.

Let me get the full diff and see the loop's register roles. Let me look at the remaining part of diff1.txt.

---
ts: 2026-11-06T17:10:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WQtAl6AF694X3L3fF551
---
Tries: 35 + b30,b31,b32,b33 = 39. Time 16 min. Need 20 min → wait until 10:14. I have to spend the time productively — let me try a few more variants and check the cse dump to solidify the wall evidence.

Let me verify the mechanism concretely: dump the win (no pin) and show that cse's make_regs_eqv rewrote the branch to the pseudo temp, while the pinned version keeps it on v0. I have the z6 cse dump showing `78 = v0; 77 = 78; branch on 78`. And the orig (pinned) lreg/rtl shows the branch on v0. Let me verify the orig's .rtl has the branch on v0 and the cse keeps it.

Also, let me try one more real-C idea I haven't: make the temp a *different* pseudo whose last use is in the same EBB by placing the branch at the very end... no.

Actually, here's one more idea: what if the copy `n = q` is *after* the branch's label in the RTL, i.e., the else arm. b7/z8 tried but the compiler hoisted it. What if the else arm is the larger one so the compiler doesn't hoist? E.g.:
```
if (q < 0) { n = q + 3; }
else { n = q; n = n + 0; }  /* no */
```

Another: use a conditional operator for the copy:
`n = (q < 0) ? q + 3 : q;` — this might produce a branch with the temp computed in the arms; the join after. cse's EBB: the branch ends the block; the temp's uses after → canonical. Hmm, but maybe the temp is assigned in both arms, so the pseudo is set in the arms and used after; cse might not tie it to q. Let me try `n = (q < 0) ? q + 3 : q;`.

Also `m = ((q < 0 ? q + 3 : q) ...)`.

Let me try b36: `n = (q < 0) ? q + 3 : q;`.

And b37: `n = q + (q < 0 ? 3 : 0);` — branchless maybe.

Let me run these while waiting.

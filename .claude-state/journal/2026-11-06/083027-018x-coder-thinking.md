---
ts: 2026-11-06T15:30:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_x748pMhYFUHrPK3QH2e3
---
Let me try --explain to see the residual for the function (with current body). But it reads one body's residual from the tree. Hmm, --explain TU FN reads one body's residual — presumably current src. Let me first make the launder-free candidate and score it, then explain.

Candidate: remove the asm line. `mp = (u8 *)D_801D0FC0;` then call. Let me test.

Actually the launder is an "output+input" asm that forces mp to be in a register. Without it, gcc will still load the address into a0 for the call. The launder likely exists because the target has a different shape: perhaps target computes `mp` earlier and keeps it, or the call arg is `D_801D0FC0` directly but with a `lui`/`addiu` pair.

Let me just try removing it and see the score/diff. Create c1.c.

---
ts: 2026-11-06T11:37:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CipBYY077f69tYlgnBe4
---
Worse (47) — do-while changed the function prologue: the args got shuffled (s1 = a0 etc.), and t0/a1 register naming. Wait: "register pairs t0->a1 x5" means mine uses t0 where target uses a1. Hmm, mFF pin is $7 = a3 in target. Mine now uses t0 for something.

Let me see full diff. The prologue changed: mine `move s1,a0` at 17 vs target? Wait target's prologue has move s1,a0 at 37b4 (index?). The diff says mine[17] move s1,a0, target --. So mine has an extra move; target's corresponding is different.

Hmm, the do-while introduced a loop and the register allocation changed: s1/s2 assignment of x,y moved.

Let me look at the full v1 disassembly and diff more.

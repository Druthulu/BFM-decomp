---
ts: 2026-11-06T15:44:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lZTYFgmgxwsJaCTNAiN5
---
g1 and g3 score 0! `do { n = q + 8; } while (0);` — the do-while block splits the schedule so the constant load lands as in the target.

Wait, why would this work? The do-while(0) creates a block boundary; sched1 schedules `n = q+8` in its own block, then the rest. The asm did the same. 

Let me verify g1 = win.c, score 0, no asm launder (the pins remain, which is fine since kind = launder).

Hmm, but is `do { n = q + 8; } while (0);` a "real C move" or a lever? The brief explicitly allows `do{}while(0)` only with `// !FAKE: do-while` — yes, it's sanctioned. C0535: "do{}while(0) splits cse1 EBB".

But wait: does this do-while actually change the *code*? Score 0 says the output matches the target. 

Let me double check the diff orig → win and that the asm launder is gone.

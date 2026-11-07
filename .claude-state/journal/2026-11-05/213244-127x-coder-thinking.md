---
ts: 2026-11-06T04:32:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Qg4eXfckZB8bGPoUfuGj
---
Still 14. The do-while isn't stopping the sched fill.

It's 21:35 now. Let me try two more quick ideas and then record at ~21:42.

z3: use `n` (s32) to hold the obj->1C value and `v` for the result:
```
n = *(s32 *)(obj + 0x1C);
v = n * 3 * 32;
p = model;
v = v + 0x600;
```
y2 did `n = ...; v = n*3*32;` and got 14.

z4: make the p load happen through the same variable as obj? no.

z5: use `volatile` on the p load? Diagnostic only — likely changes to lhu etc. Not useful.

z6: the p reload could be made non-struct via CAST_NONSTRUCT (y8=14).

Let me try one more: place the p load BEFORE the 0x1A store (so the store kills it and it reloads after the chain?) Hmm, then the first p load is used by the store (0x1A), and the merge needs p → reload. That's u1 (32).

I think 14 is the wall. Let me wait until 20 min. It's 21:35; item 4 started at ~21:22? Let me check the notes: item 3 ended 21:22, item 4 started 21:22. At 21:42 it's 20 min. I'll do a couple more tries until then.

Actually, let me try a genuinely different idea: make the obj->1C load NOT a load-delay-fill target by reordering the source so the obj->1C load is later. E.g., compute `p` first, then the multiply:
```
p = ((Unk*)a0)->unk20;
v = *(s32*)(obj+0x1C) * 3 * 32;
v = v + 0x600;
```
Then the RTL: store, p load, obj->1C load, chain, add. sched: the p load might fill the delay slot of the obj->1C load? Or the obj->1C load fills the p load's delay. Hmm. Let me test.

z3: p before the multiply.

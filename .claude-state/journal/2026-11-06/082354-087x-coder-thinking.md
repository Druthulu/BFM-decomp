---
ts: 2026-11-06T15:23:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LGqHnOWR49OjTYnwJ2ef
---
Wait — there's a problem: the `sel_094` block in the original has `if ((func_800291B4(0x40) & 0xFF) == 0) { goto call_45F; } sel = &D_801C3CD4; goto set_sel;`. In my new version, after sel_094 there's `after_test:` and then the original code continues `if ((func_800291B4(D_80183478[t])...`. That's correct.

But the original text after the replaced block is:
```
        if ((func_800291B4(D_80183478[t]) & 0xFF) == 0) {
```
which now follows `after_test:`. Good.

Also I need to check: the labels `sel_test`, `sel_054`, `sel_094`, `after_test` are at case-body level (8-space indent is just style). They're inside `switch (idx)` — jumping to labels inside a switch case from within the same case is fine.

But careful: `goto sel_test` from `case 5` — labels are function-scoped, fine.

One concern: the `after_test` label is inside `case 5`; if the code falls through from case 6/8 into... no, case 5 is its own block ending with a `return -1` or `break`? Let me check the end of case 5: after the D_80183478 block, it does `D_801CD870 = a1 + 1; return -1;`. Fine.

Let me run.

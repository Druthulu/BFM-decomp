---
ts: 2026-11-06T15:10:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7sZzrHRY3u63qQiIPwmV
---
One launder at line 98, in case 5:
```
if (t == 5) {
    __asm__ ("" : "=r"(t) : "0"(t));
    if (t != 3) goto sel_094;
sel_054:
    sel = &D_801C3C94;
    goto set_sel;
sel_094:
    ...
}
```
Wait, this is weird: `if (t == 5) { launder(t); if (t != 3) goto sel_094; ... }`. After the launder, t is opaque (but still 5). Then `if (t != 3)` — at runtime t==5 so !=3 is true → goto sel_094. Hmm, but then sel_054 (the t==3 path) is reachable only if... it's dead code? Unless the compiler's knowledge of t matters.

Actually wait: the launder makes t opaque so the compiler can't know t != 3, so it emits the test. Without the launder, t==5 is known, so `if (t != 3)` folds to always-true → goto sel_094, and the code at sel_054 becomes unreachable/removed. That changes codegen.

Hmm, but also there's `if (t == 3) goto sel_054;` earlier at line 94-96, before `if (t == 5)`. So flow: if t==3 goto sel_054; if t==5 { launder; if (t!=3) goto sel_094; } — since t==5 here, the launder's test is always true, so sel_054 is unreachable from this path but reachable from the earlier `t==3` branch. So the label sel_054 is shared.

The launder makes the compiler emit a real `if (t != 3)` test even though t==5 is known — because the asm makes t opaque.

Let me see the target assembly to understand what's needed. First, let me score the launder-free body and see the diff.

Let me create the nolaunder candidate and score.

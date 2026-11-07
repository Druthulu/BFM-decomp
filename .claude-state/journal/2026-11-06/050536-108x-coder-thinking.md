---
ts: 2026-11-06T12:05:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BTfZZ70jQD5aNy0icbOv
---
Worse (164 insns). Not helpful.

Let me try a different approach: use the `do{}while(0)` technique (C0535) to split the EBB and control scheduling. The keepalive acts as a scheduling barrier between the stores and rval. A do-while(0) around the rval computation might do the same.

Let me try wrapping the rval computation (and r[-2], r[0]) in a do-while, with the keepalive removed.

C0535: do-while splits cse1's EBB so sched1 keeps birth order. If I wrap the rval computation in a do-while placed after the stores, sched1 might not hoist it above the stores.

Let me test:
```
q[0] = ...;
r[-1] = ...;
do {
    rval = (uVar2 * 8 + 8) | 0x4000;
    rval = base6 | rval;
    r[-2] = c74v;
    r[0] = rval;
} while (0);  // !FAKE: do-while
r = r + 5;
...
```
Let me test w6 (keepalive removed + do-while around rval block).

Also w7: keepalive removed, do-while around the stores.

Let me test.

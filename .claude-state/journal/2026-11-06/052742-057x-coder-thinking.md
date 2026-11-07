---
ts: 2026-11-06T12:27:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5kYOBbqP3bxew5VnjIeZ
---
`sched-store-sink` — "scheduler sinks a store past the target slot (G28)" fits the barrier residual exactly (the y store sinks 2 slots past the target slot).

And the keepalive: `global-pri-bank-order` — "global-alloc priority order assigns the hard regs in a different order than the target" fits (the 3-cycle rotation).

Let me do the duplicate-store try (s1) and a couple more, then record WALL.

Actually — wait. Before that: `sched-store-sink` says the scheduler sinks a store. In target the store is EARLIER. So mine sinks it. Hmm.

Let me try one more idea for the barrier: make the store's value y used after the store, i.e. give the store a longer dependency... no.

The duplicate-store idea (store per branch) directly addresses sinking: if the store is inside each branch, it's in a different EBB and can't sink into the join. Let me try it.

Structure change:
```
if (j == 0) {
    if (D_80115140[k] == 0) continue;
    q[-7] = 0x30;
    y = D_801BB61E - 2;
    *(s16 *)(q - 10) = y;
} else {
    ...
    q[-7] = 0x38;
    y = D_801BB632 + 1;
    *(s16 *)(q - 10) = y;
}
```
Then remove the common store. Let me test.

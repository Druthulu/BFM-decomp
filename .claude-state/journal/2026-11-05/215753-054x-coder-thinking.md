---
ts: 2026-11-06T04:57:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YUo9A7SAg8nWFJkyQP7v
---
Excellent! "Second use (T11 G18 func_801876C4, barrier dropped): do { t = D_801A9A88[a1*5]; sp10[4] = t; } while (0); keeps the following u16 adds out of the t load-delay slot". So do-while(0) is a scheduling barrier replacement.

So for item 2: wrap the store and the following load (or the whole sequence) in a do-while(0) to keep the load after the store. Let's try:

```
do {
    D_80078EA4 += a1;
} while (0);
if ((s16)D_80078EA6 >= 0xA1) ...
```

or wrap both:
```
do {
    D_80078EA4 += a1;
    if ((s16)D_80078EA6 >= 0xA1) { ... }
} while (0);
```

Hmm, the second form wraps the if too. Let me try several placements. Also, the `do{}while(0)` must be marked `// !FAKE: do-while`.

But wait: do-while(0) creates a LOOP note, and loop.c might do things. In G16x/G18 it worked, so fine.

Let me try:
q1: do { D_80078EA4 += a1; } while (0); before the if (all 6 sites? or just the 3 first-half sites).
q2: do { D_80078EA4 += a1; if (...) {...} } while (0);
q3: do { D_80078EA4 += a1; if (cond) ...; } while (0) with the if outside? 

Careful: the third block's structure is `if ((s16)D_80078EA6 < 0x80) { D_80078EA4 += a1; if (D_80078EA6 >= 0x81) ... }`.

Let me write the variants by transforming the barrier-free source:
- Replace each `D_80078EA4 += a1;` with `do { D_80078EA4 += a1; } while (0);  // !FAKE: do-while` — but then the load in the following `if` is in a different block → sched1 can't hoist it above the store. 

That's q1. Let me test it.

Also q4: wrap the store+if:
```
do {
    D_80078EA4 += a1;
    if ((s16)D_80078EA6 >= 0xA1) {
        D_80078EA4 = 0xA00000;
    }
} while (0);
```
That might keep everything in one block and not help.

Let me generate q1 and a couple of variants. Note the third block has `D_80078EA4 += a1;` inside the outer if — the same replacement applies.

Actually, one concern: `do { D_80078EA4 += a1; } while (0);` — the loop note might make cse1 split the EBB, but sched1's basic blocks come from the CFG, which is unaffected by a note... unless the note is a BARRIER? No. Hmm, but C0535 proves it works for sched1.

Actually, wait: maybe the mechanism is that the loop notes make `loop.c` run, and loop.c can insert a jump/label? For do-while(0), loop.c sees a loop with a constant-true exit test... Hmm.

Whatever — empirically it worked. Let me test.

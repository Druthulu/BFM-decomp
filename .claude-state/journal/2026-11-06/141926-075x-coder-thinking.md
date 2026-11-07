---
ts: 2026-11-06T21:19:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GErgr2sDyC0y3FhO1BWe
---
orig.c matches src. Good, no regen.

Now the approach: replace the out-only launder with a real 2nd set of pv. The move from W47/W48/W49: split `pv = pv & 0xFF000000` into its own statement.

Current:
```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (... & 0xFFFFFF);
```
New:
```
pv = *(u32 *)p;
pv = pv & 0xFF000000;
*(u32 *)p = pv | (... & 0xFFFFFF);
```
And remove the launder line.

This gives pv 2 sets, demoting sched1 birthing boost. Bytes identical because the and is in the target anyway.

But wait — pv is pinned to $3. The pin may interact. The moves say this worked with pins kept. Let me create win.c and score.

Note: the launder was at the END of the function, after func_80016638. Its effect is on the sched1 birth order of the pv store earlier. Removing it and adding the 2nd set earlier should replicate.

Let me write win.c.

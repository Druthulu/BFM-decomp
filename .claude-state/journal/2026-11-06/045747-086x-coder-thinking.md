---
ts: 2026-11-06T11:57:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sY7hk6Nk8wnhSvxRQgW0
---
I made a typo again: in the second Blk20 block, I wrote `t0 = s->w[0]; t1 = s->w[1]; t2 = s->w[2];` — that's correct. But wait, in my file I see at the second block:
```
      t0 = s->w[0]; t1 = s->w[1]; t2 = s->w[2];
```
Hmm no, looking at the content I wrote: after `s32 t0, t1; register s32 t2...` I wrote `t0 = s->w[0]; t1 = s->w[1]; t2 = s->w[2];` — yes correct.

Score v1.

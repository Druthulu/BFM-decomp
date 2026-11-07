---
ts: 2026-11-06T11:57:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LdJvcxay1zhNU29uXsDX
---
Oops, I made a typo: `t0 = s->w[0]; t1 = s->w[1]; t2 = s->w[2];` appears twice in the second block — I accidentally duplicated a line (the second block should start with the copies; I wrote t0/t1/t2 assignments then blk writes — that's what the source has). Let me check: second block in source:
```
      t0 = s->w[0]; t1 = s->w[1]; t2 = s->w[2];
      blk.w[0] = t0; blk.w[1] = t1; blk.w[2] = t2;
      ...
```
Yes that's right — I have it once. Good (I see only one occurrence in the second block).

Wait, in my file the second block starts with `t0 = s->w[0]; ...` — correct.

But I dropped the `__asm__` launder and the `{ void *q; ... }` wrappers, replacing with `&blk` directly.

Score v0.

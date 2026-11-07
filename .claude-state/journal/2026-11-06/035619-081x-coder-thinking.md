---
ts: 2026-11-06T10:56:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CowQgkgFHIBeNH0H4nMr
---
Same as the twin's v_param: score 11, the load hoisted. Let me apply the winning structural moves: do-while around the load (d_S2S3S4 style) and the variants.

For this twin, the tail is:
```
v1 = 0x4000;
t = unkC4;
unk58 = &D_801907C4;
unkC4 = t | 2;
unkC1 = 0;
unkB4 = 0;
...0x4000 stores use v1...
```
Let me create:
- w_dw.c: do { t = unkC4; } while(0);
- w_dw6.c: do { t } ... do { unkC4 = t|2 }
- w_addr.c: a variable etc.

Let me just reuse the sed transformations.

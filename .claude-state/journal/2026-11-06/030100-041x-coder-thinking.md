---
ts: 2026-11-06T10:01:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GvuBZlEUECQHWU526crV
---
Wait — the `extern u16 D_80126B5E;` declarations inside the function: these are in the original body (inside the function). The body span starts at the function definition. If I put them inside, fine.

But `ratan2` is declared at file scope (the extern line before the def). The body span starts at the def line, so the extern ratan2 declaration remains in the header. Good.

Now run hdump.

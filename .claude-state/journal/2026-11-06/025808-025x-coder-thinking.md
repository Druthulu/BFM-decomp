---
ts: 2026-11-06T09:58:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GmBUsAuNATGAGXRDpG5k
---
Confirmed: conflicting types is an error. So changing the definition's return type is impossible without touching callers (forbidden).

Hmm. But wait — the callers' declarations are inside the same file. The brief says callers stay as they are. So this item cannot be cracked by changing the return type.

Is there another route? Let's think harder.

What if we keep `void` but make the function's body set v0 via a *call* to a function that returns? No, calls clobber v0.

What if the last statement is a `switch` that... no.

What if the function is declared void but we use the return value through a *local function pointer cast*? E.g. `((s32 (*)(s32,s32))func_8017F1F0)(a0,a1)` — recursive call, no.

Hmm, what about the "keepalive replaced by return v0" trick from moves line 28? Let me look at that function's definition to understand. func_80184D28 — find it in src.

---
ts: 2026-11-06T06:42:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TpC3YdllFo5nfm1MDyo6
---
Same structure. Let me apply the same approach:
1. A = pins removed only (src $16, dst $3, tmp $2)
2. B = launders removed only
3. w = B + dead resets (mp = 0 after each call, m18 = 0 after RotTransSV)

Let me check how many mp-call sites: grep the call line count.

Let me do it.

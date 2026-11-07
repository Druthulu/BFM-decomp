---
ts: 2026-11-06T17:05:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6s7GHpVGIXXDpBExxeOs
---
The RTL at .rtl is exactly the target's shape:
```
128: q(77) = v0
131: n(78) = q(77)
134: branch if q >= 0 -> 137
136: n(78) = q(77) + 3
137: n = n >> 2
139: n = n << 2
144: n = q - n
```
So the branch tests q (77) — correct! The later cse must rewrite the branch to test n (78). Let me check the .cse dump.

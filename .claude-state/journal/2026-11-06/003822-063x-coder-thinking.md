---
ts: 2026-11-06T07:38:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4E4025ntZGfl7fSvxdX5
---
Interesting. r72 crosses 2 calls (s0? r75/r82 in v0...). The table doesn't show all pseudos clearly. r72 conflicts with a0..a3, v0,v1,sp and crosses 2 calls → callee-saved. r74 crosses 1 call.

Wait, the table shows "8 pseudo(s) in the .lreg table" but only some. The hard column is from .lreg. r75→v0, r82→v0, r81→v0, r84→v1, r85→v0, r86→v0. Hmm, many map to v0/v1. That doesn't match the final allocation (a0,a1,a2,a3). The .lreg is the local-alloc dump; hard regs shown may be after reload. Confusing.

Let me instead look at the .lreg dump directly for our function, which lists quantities and their allocation. Let me grep the function section.

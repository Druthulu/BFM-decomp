---
ts: 2026-11-06T15:24:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H0eFURePoUdjxy0jcu7S
---
s1 still 4. Hmm — so the compiler must have threaded the jumps and folded. Let me look at s1's diff to see whether it produced the target shape.

Actually score 4 means the same residual as nolaunder. So the compiler simplified the two gotos to one test and folded.

Hmm. Let me check s1's disassembly to understand. But time...

Actually, maybe the issue: at sel_test, the compiler knows t ∈ {3,5}. It emits the test `t != 3` — that's real! But then why score 4? Maybe the branch layout differs elsewhere. Let me get the diff.

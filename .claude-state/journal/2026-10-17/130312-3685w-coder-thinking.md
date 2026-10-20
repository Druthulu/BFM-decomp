---
ts: 2026-10-17T19:03:12.415Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm realizing the arg0 copy was likely optimized away because the register already held the right value, so without the laundering trick the compiler could just use arg0 directly instead of introducing s0.

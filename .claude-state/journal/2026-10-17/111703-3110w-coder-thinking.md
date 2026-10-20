---
ts: 2026-10-17T17:17:03.609Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm tracing the register allocation priorities: since a0 stays live until insn 18, p1 can't claim it directly, so p2 inherits a0 once it frees up. Looking at the priority weights, r75 and r78 tie highest at 5000, with r73 trailing at 3333, meaning it gets allocated last.

Checking the lreg table I see r75 gets v1, r76 and r78 share v0, and r73 ends up in a1 since v0/v1 are taken and a0 is still live. For p2 to land in a0, there needs to be a tie hint from a copy relationship between arg0 and a0, so I should look at how c1's allocation table handles that pairing.

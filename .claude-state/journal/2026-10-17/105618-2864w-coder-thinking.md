---
ts: 2026-10-17T16:56:18.139Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'm noticing that in n1, the scheduler keeps the tag load late because of aliasing with the byte store, while in the original the value read happens early since it's written early in source. Even after moving the value read earlier in q1, it still scored the same, which suggests sched1 may have deprioritized it anyway.

Hard registers create anti/output dependencies that pin their order, while pseudos without those pins get freely sunk by priority in list scheduling — that's likely what's holding this particular wall. Given how many variants I've already swept for the mask alone, I'll try a couple more q1 diffs before calling it, so let me check that diff now.

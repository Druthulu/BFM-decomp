---
ts: 2026-10-17T16:52:51.873Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 6e7176e5-0e21-422e-8b4f-daa52f59326d
usage: {input: 6, cacheRead: 213314, cacheWrite: 1120, output: 517}
---

I've added both lessons to T14. Its from-the-start guide, `docs/how-to-ai-decomp/03-bootstrap-order.md`, will now also say:
- an agent may use a lever only if it records, at the moment it matches the function, the compiler wall that forced it and what it tried first;
- names go in only with evidence: a role that is obvious from the code, or a struct field confirmed in more than one function. Anything else keeps its placeholder.

The link check must still report zero broken links. The change goes in at the next task boundary, so T11 isn't affected.

The other picker, about re-dealing T11's unstarted batches by lever kind, is still waiting for your answer.

---
ts: 2026-10-17T08:49:13.709Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad48947f967e77fd9
model: claude-opus-5-5[1m]
effort: medium
turnId: 5652b206-5bd1-470d-af6a-d1e28be458c3
---
I notice Rung-E rows are marked "LEVER-FREE" despite leftover levers, which means they need a --rejudge since the ledger index treats them as exemplars with an empty oracle, forcing a full ladder replay. I also need to check whether a body sharing the same nhash in a non-target set could still be an exemplar for the target — that seems fine either way, so now I want to write a scratch script to compute this.

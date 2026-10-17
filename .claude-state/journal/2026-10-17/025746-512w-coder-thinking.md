---
ts: 2026-10-17T08:57:46.395Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad48947f967e77fd9
model: claude-opus-5-5[1m]
effort: medium
turnId: 5652b206-5bd1-470d-af6a-d1e28be458c3
---
Now I'm planning the fan-out for the remaining 24 names, excluding the two already handled plus the three done ones. I'm thinking about batching by file groups, noting the three big classes with 131 copies likely share the same TUs, and sketching a first batch of around 21 smaller names totaling roughly 40 bodies.

I realize batching by --batch alone is risky since --rejudge would redraw already-judged bodies in subsequent batches — so batches really need to be split by --only names instead. I'm also working out the time cost per copy: if the exemplar is fully NEEDED, replay gets skipped and each copy requires the full ladder (base plus one pass per call site), so I need to count sites per class body and compute the actual file sets involved.

---
ts: 2026-10-15T03:45:56.775Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7df908b0d85c75d2
model: claude-opus-5-5[1m]
effort: high
turnId: 760fd9fd-9ef6-4183-9220-a4095b678743
---
I'm checking the strict-0 requirement against the legacy P36 comparable lane data, noting that literal 0 requires 1,868 oracle-judged needed pins with 1,496 implemented across asm defs, gte-levers, and asm-macros.

Historically, pins existed where pin-free C couldn't be found, which makes full replacement in one phase unrealistic. I want to figure out whether the 1,066 head-class rows mean a shared body across overlays, so that fixing one head could resolve many family copies at once — I'll wait on the retriever for that, and meanwhile glance at T11's timeline chart.

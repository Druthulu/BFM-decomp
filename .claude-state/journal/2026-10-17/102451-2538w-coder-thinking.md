---
ts: 2026-10-17T16:24:51.475Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm looking at the addPrim tail pattern, noting the early pv load and the 0xff00 constant timing as a known birthing boost issue, and considering writing it as the standard addPrim macro form that masks and merges bytes from the pointer and ot_entry fields.

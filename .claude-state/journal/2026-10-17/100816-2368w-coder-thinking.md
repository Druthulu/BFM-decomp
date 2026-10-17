---
ts: 2026-10-17T16:08:16.016Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm trying to figure out why the field load ends up assigned to v0 rather than v1 — it seems like local register allocation favors v0 for the shorter-lived field variable, while the longer product/division chain holds onto a different register since it's live longer.

Really the v0/v1 assignment just reflects allocation order rather than which load feeds which register, so to flip it I need the field variable to have higher priority — shorter life or more references. Let me try rewriting the division manually as an explicit sign-adjustment and shift, and also experiment with giving the field variable more references to see if that shifts its allocation priority.

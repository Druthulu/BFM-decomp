---
ts: 2026-10-17T11:28:22.559Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm trying to figure out what makes a hard register conflict live during an allocno's lifetime, and considering whether lower-priority conflicting allocnos' register preferences get avoided during the register-finding pass.

I'm checking whether m conflicts with some allocno j that dies right before m's copy but prefers a different register than a3, which would rule out that path, so I need to look at the actual start of find_reg to see how regs_someone_prefers is actually used.

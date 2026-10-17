---
ts: 2026-10-17T10:41:11.222Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm wondering whether init_alias_analysis gets called during sched1, and considering how REG_EQUAL notes with non-constant values like a register-plus-offset expression get canonicalized—whether the register resolves to a known value. I want to check the relevant CSE code around that range to confirm.

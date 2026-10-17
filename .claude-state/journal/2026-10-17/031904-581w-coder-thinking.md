---
ts: 2026-10-17T09:19:04.150Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
All 12 match up. I should grep the drafts for register/volatile/asm usage beyond the gte macros, and also flag the func_80184440 case — the auto-detection may miss it since the regenerated .s prologue doesn't clearly signal -O0, so I need to note that this TU's build must be forced to -O0 given the stack frame in the asm.

I'm double-checking that the verbatim ROM-extracted targets are trustworthy per the tool docs, since those bytes come straight from ROM and any matches against them should be sound. Now I should go check the levers mentioned in the drafts.

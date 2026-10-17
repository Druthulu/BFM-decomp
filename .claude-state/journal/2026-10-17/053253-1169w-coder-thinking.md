---
ts: 2026-10-17T11:32:53.345Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
Since this overlay is matched in tree, there's no per-function asm to check against directly, so match_one can't verify it that way—no glabel for this function exists anywhere under asm/. That means delever_search --try against the whole-TU real recipe is the actual oracle here; I'll note this as a gotcha and finish writing up my notes and report.

No `glabel func_80140958` exists under `asm/` since the function is already matched, so the whole-TU `delever_search --try` was the correct check. I'll note this conclusion in notes.md.

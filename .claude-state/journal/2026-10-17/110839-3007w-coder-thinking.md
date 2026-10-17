---
ts: 2026-10-17T17:08:39.522Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm distinguishing categories here: the laundering pattern at the end where a second mask application kills the birthing boost, versus pins like the angle/pv values and the volatile lever index which may just stay as-is. This matches the addPrim pattern from W01's func_80185944, where launder converts to real via a second masked set — suggesting a partial fix tied to the sched1 birth-boost pin.

Looking at W04's func_80186B70 next, I see the same launder-to-real pattern but split: reading pv from the pointer, masking it against 0xFF000000, then writing back the combined masked value. I want to try applying this same split technique here.

---
ts: 2026-10-17T15:58:23.719Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: 8d79bbc0-6d30-411b-a4e2-472ff86f0d65
---
There's no baseline override, so barriers stay rounded. The --try compiles against spliced TU text, which should be safe at barriers even if the banker swaps source concurrently since it's confined to different functions, and each --try call seems to get its own scratch directory, so concurrent compiles shouldn't collide. Now I'm sizing up the remaining worklist of singleton rows to figure out how to batch them.

I'm trying to decide how to handle functions that mix instruction rows with other kinds — whether to park the whole function or just skip the instruction lever while still judging the rest, leaning toward parking them wholesale for simplicity even though that leaves some rows unattempted. I still need to check how many functions actually have this mix, pull the names for the func_80188C04 SR3_ macro family of eleven functions, and figure out how the T10 pilot survivors fit in — they're already attempted so excluded from "remaining," but their wall-cause rows still need re-judging this phase.

I'm also noting func_80177940 needs a callee-saved-order wall cause, and planning to write a scratch script that joins T10's singletons.tsv against the current singleton rows to build the actual worklist, plus grep the source for SR3_ usage to find all family members.

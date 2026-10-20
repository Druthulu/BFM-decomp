---
ts: 2026-10-17T18:47:04.060Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I should write a script that searches over random topological orderings of the statements both before and after the load, with the barriers stripped out, to see which reorderings are actually valid given the dependencies between the mask, register value assignments, and the two load targets.

Given the combinatorics, sampling something like 400 random valid orderings would take too long to run in the foreground within the time limit, so I'll split it into smaller batches or run the search in the background instead.

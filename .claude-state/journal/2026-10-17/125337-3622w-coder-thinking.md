---
ts: 2026-10-17T18:53:37.325Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I'm trying to figure out why my delay slot filling picked the fallthrough instruction while the target version seems to need the sll s0 instruction for sign-extending i before the call, and whether that value is actually needed on the taken branch path or not.

Maybe the key difference is loop prediction: with a for-loop and loop notes, the branch heuristics treat the target differently than a goto-based loop without those notes, which could explain the divergent scheduling. I should check whether the constant gets hoisted out of the loop in both cases, since that depends on loop size and register pressure — I want to grep the target assembly for similar `li` instructions in the earlier loops to see if hoisting happens there too.

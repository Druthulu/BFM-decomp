---
ts: 2026-10-17T04:57:43.384Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abc404fb8a77f6873
model: claude-opus-5-5[1m]
effort: medium
turnId: ffb0e172-bea2-4dc0-ae04-98d6d34d67e0
---
I'm tallying the zero-argument declarations across BD14, CBF4, and the 80014CF8 function, counting 11 total, and noting that the ledger flags a mismatch where functions declared void are actually having their return values used by callers.

Now I'm reconsidering the fix: making the def return s32 with an a0 parameter caused "too few arguments" errors at zero-arg call sites, so the real fix is to have those callers pass their enclosing function's live $a0 value instead. I'm weighing whether to also change the def's return type to s32 across all 1377+ decls versus the minimal fix of just correcting the zero-arg decls to take s32 and pass a0, since that alone would bring the lying count to zero.

I'll leave the def's return type as void for now, note the deviation, and move on to examining each zero-arg call site's local context individually.

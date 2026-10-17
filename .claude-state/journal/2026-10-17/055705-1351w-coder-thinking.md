---
ts: 2026-10-17T11:57:05.557Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
That e3 variant didn't hold up structurally, so I'm discarding it. Now I'm checking the e2/d2 difference, trying to see if the mismatch count of 27 comes from a shift in register layout, and testing whether placing the null path after the return-inside-if branch with a different jump arrangement could fix it.

Looking at the d2 diff more carefully, it seems gcc actually reordered the "return NULL" block to come before the body rather than after, which matches jump.c's optimization for "if (cond) {A; return} B" patterns. My guess is the target structure has the then-arm falling through to end while the else-arm (setting v to NULL) sits last, matching a source like "if (v) {...} else {v = NULL}" with the return embedded in the then-arm.

Back to the allocation question — maybe local-alloc's register preference order explains why v0 was unavailable, with constants grabbing v1 first in the target instead. I'm wondering if P's set from the call result could be scoped differently across blocks, but I've hit about 16 attempts now without further gains, so it's probably time to stop pushing on this angle.

Settling on 27 as the best result, improved from a baseline of 28 — I'll record this and move forward.

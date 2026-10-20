---
ts: 2026-10-17T17:21:42.797Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
The do-while restructuring made things worse rather than better. I'm wondering if there's a way to increase pf20's live range without extra instructions, maybe by finding a genuine use of it in the then-branch, or reconsidering whether obj has the same priority as r73 in the target.

Looking at the target register map more carefully: s0 and s1 are taken by local allocations (r118, r76), while global allocation picks s2, s3, s4 in priority order for r73, r74, r75. For pf20 to land on s4 instead of s3, either pf34 must have higher priority than pf20, or there's a conflict forcing pf20 off s3 that doesn't affect pf34 — possibly tied to hard register copy preferences in the allocator rather than pure priority ordering.

I'm recalling that gcc 2.7's global register allocator has preference logic where it favors hard registers that are already in use or avoids call-clobbered ones when the allocno crosses a call, which could explain why pf20 skips s3 in favor of s4.

Then I shift to checking REG_N_REFS and REG_LIVE_LENGTH weighting, but these only apply to loop-weighted frequency, not plain reference counts, so that doesn't explain the priority difference either. I'm now trying to estimate pf34's actual live range by counting insns through its then-branch and else-branch to see if trimming its live length below pf20's 66 would flip the allocation order.

Maybe allocno priority isn't just about pf20 and pf34's ref counts — could other factors like loop_depth weighting or local-alloc's handling of callee-saved registers be stealing s3 before global-alloc even considers it?

I'm checking whether the live-range difference between pf20 and pf34 could stem from branch structure instead — if pf34 dies at the end of the else-branch while pf20's uses extend through the then-branch and tail, that could explain the ~30 extra instructions. Now I'm trying to count how many calls the target actually makes to func_80016714 to verify this theory.

Looking at the greg priority calculation: pf20's ref/liverange ratio comes out higher than pf34's, which would push the register allocator toward assigning pf20 to s3 first, and I'm checking whether that matches the target's actual preference for pf34.

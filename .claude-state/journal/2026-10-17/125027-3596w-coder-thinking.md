---
ts: 2026-10-17T18:50:27.841Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
This mirrors the earlier twin case: s2 is pseudo and canonical while s0 is pinned to a hard register. I need s0 to hold arg0+5 computed independently of s2, but since s0 is hardwired, placing its addiu instruction requires careful ordering relative to where s2 gets assigned from arg0.

I'm also noticing this requires cse not to collapse arg0 and s2 into the same equivalence class, which would mean restructuring so arg0 itself is the long-lived iterator, with the load using the canonical register while s0's computation uses a0 directly before arg0 dies.

I'm reconsidering whether the substitution is really unconditional in cse, or whether local/global allocation ties account for the discrepancy — maybe s0 isn't simply arg0+10 but reflects a struct pointer access where arg0[0] is the first element, keeping a0 live separately from s2 until the addiu.

I'm also wondering if loop rotation plays a role here, with the original pre-loop exit test duplicating before cse runs, which could explain why the target uses s2 instead of a0 even though they're in the same equivalence class.

I want to try reordering so `s2[0]` is read while `s0`'s computation of `arg0 + 5` sits before the `s2 = arg0` assignment in the source, then check whether scheduling/cse reorders it to match the target's placement after the branch.

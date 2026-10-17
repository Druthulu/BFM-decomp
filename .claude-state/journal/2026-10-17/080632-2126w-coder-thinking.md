---
ts: 2026-10-17T14:06:32.260Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
So reordering alone doesn't explain the register swap. I'm now examining how local allocation orders values versus constants—when I removed the pin but kept the barrier, the swap still happened, while pinning val to $2 fixed it and left 1 with v1. This points to local allocation's priority sorting, which weighs reference count and live length, breaking ties by birth order—and I recall blocks with exactly three quantities get allocated strictly by birth order.

I'm counting the quantities in this block: p (which might escape to a callee-saved register since it spans calls), val, const1, and the val+1 result. I consider whether const1 could be eliminated as a separate pseudo by reusing val+1, since in case 0 val starts at 0 so val+1 equals 1—but the target code still issues a separate li for 1, so that doesn't match. I'm now thinking about val's reference count and live length under the priority formula, and how shifting those (more refs, shorter life via closer load placement) could flip which value wins v0 under different orderings.

Trying permutations where const1 lives longer or appears later doesn't flip the outcome either, since scheduling would hoist the li regardless. I wonder if the constant assignment even counts as a normal local-alloc quantity, or if REG_EQUIV handling (doubling live length for pseudos set once to a constant) is relevant here—though in my case const1 still wins despite that penalty. I also consider whether val's hard-register preference (being tied to v0 as a return value) could be the deciding factor, and whether a birth-order tiebreak in local-alloc.c is what ultimately determines the pick between these three quantities.

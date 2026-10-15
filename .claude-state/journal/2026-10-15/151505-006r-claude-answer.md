---
ts: 2026-10-15T21:15:05.011Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a1ce918197a39b8ec
model: claude-opus-5-5[1m]
effort: medium
turnId: f97da0d3-0c15-4c08-bf95-4ef9be38dff2
usage: {input: 10, cacheRead: 433271, cacheWrite: 4276, output: 1756}
---

T2 needs your decision, because the answer changes the 3.40 milestone.

T2 finished its pilot, and all of its work is committed (63fc7e8bf6) with every gate green. It reported "blocked" only because the plan told it to stop if the full goal looked too large for one phase.

**What the pilot did.** It made a decision for each of the 75 struct types that held the most residue: 51 got a canonical definition, 7 were merged into types we already had, and 16 stay residue with a named reason. That cut the "type not canonical" residue roughly in half, from 291,819 to 139,520 sites. Raw casts fell by about 94,000 along the way. One struct had looked odd: it carried 3,457 residue labels left over from before it was defined, and those are now cleared.

**The numbers for the rest.** About 12,700 types are left, and the residue is very lopsided:

| Coverage | Types to decide | Sites cleared | Sweep time |
|---|---|---|---|
| 80% | 1,834 | ~112k | ~8 h |
| 95% | 6,676 | ~132k | ~10 h |
| 100% (literal 0) | ~12,700 | ~140k | ~10.4 h |

The compile sweeps are cheap. The real cost is the decisions: reaching zero means about 8,700 new struct definitions. About 6,000 of the last types cover only around one site each, so most of those would be one-off structs that exist only to satisfy the counter.

**My recommendation is the 95% band.** Decide those 6,676 types with rules applied automatically by tooling, which T2 has already worked out. The roughly 7,000 tail sites stay residue under a reason of their own, such as "single-use type", instead of "not canonical".

That needs your explicit agreement to change the milestone wording, from "TYPE-NOT-CANONICAL gone" to "gone above the 95% band, with the tail ledgered under its own reason". Without that agreement it would just be renaming the problem so the gate passes. The tail is the same kind of residue the plan already accepts for other causes.

Going for a literal zero is possible, but it spends most of the remaining effort on thousands of near-empty structs, which hurts readability rather than helping it.

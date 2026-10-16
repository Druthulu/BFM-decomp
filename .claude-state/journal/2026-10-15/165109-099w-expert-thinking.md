---
ts: 2026-10-15T22:51:09.526Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: 4c23aba1-6a33-47ae-8736-5fe6093d69e7
---
I notice a tension here: the done-when criterion requires zero duplicate class definitions, but the policy for layout twins says they should stay separate without evidence of consolidation. I'm weighing whether to treat new tier-3 duplicate definitions as a special case that still satisfies the structural check.

One option is to extend struct_twins so that a documented "cause" citing the owning function (the actual use site containing the type's TNC bodies) counts as valid evidence that two layout twins are genuinely separate entities. That's a small scope deviation since it touches a file outside my original list, but it fits the gate's intended design rather than weakening it — the owner function is a legitimate address/use site. I'm fairly convinced this is an acceptable way to satisfy the check, though I should also consider whether a tier-1 identity-based approach might be cleaner.

T2 already defined these same unkstructs from different hash twins, so this looks like the same owner function spawning a second map type with the Ramp388C layout — plausibly the same entity drifted apart, which is weak E1-type evidence but not quite enough on its own. This really is a policy gap: the done-when rule only lists four residual classes before falling to "define," and neither folding on layout identity alone (which contradicts G62) nor inventing a fifth class like TYPE-TWIN-OF-CANON is something I can just decide unilaterally since it extends the written rule rather than just choosing an approach within it.

Since raising this as a question halts the run for a round-trip, I'm weighing whether to just resolve it myself by treating an exact-text duplicate def as a straightforward violation of the dup-defs rule, since writing a second identical struct under a new name is exactly what's forbidden regardless of which class it's filed under.

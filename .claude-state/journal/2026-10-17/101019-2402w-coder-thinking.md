---
ts: 2026-10-17T16:10:19.034Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac8178896d2313b85
model: claude-opus-5-5[1m]
effort: medium
turnId: 589d16b4-5a62-4ce6-8a45-63d170f3cb6e
---
I'm comparing the target assembly's scheduling against mine: the target places the store before the branch with a move kept in the delay slot, while mine schedules the subtraction differently in the delay slot. I'm wondering if that extra move is really just a dead copy that proper copy propagation should eliminate, or if it's a reload the compiler intentionally keeps alive.

I'm sketching out several candidate C variants to see which naturally produces that lingering move: declaring the field as a narrower type to force sign-extension loads, introducing a separate temporary variable to hold the copied value, or directly decrementing the struct field before using it in a function call.

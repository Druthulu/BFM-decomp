---
ts: 2026-10-17T13:51:21.620Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I'm wondering if CSE is merging the two reads of D because they're structurally identical, so maybe writing the second access with a different pointer-cast form—like reading through a byte offset instead of a direct struct field—would prevent the compiler from recognizing them as the same expression.

Alternatively, if the store target itself is reached through a pointer rather than a direct plus-offset, CSE might treat the write as invalidating all memory, breaking the reuse I'm trying to avoid.

I'm checking whether the second load still resolves to an equivalent PLUS expression, and considering whether something between the two reads—like a QImode store or an intervening statement—might invalidate the cached equivalence before cse gets to reuse it.

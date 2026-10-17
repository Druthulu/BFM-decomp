---
ts: 2026-10-17T13:51:44.113Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I'm noticing the stores go through s0+offset, which doesn't invalidate the scalar D value, while my version hoists the D load earlier via scheduling after the jal. So CSE isn't treating the u16 store at offset 32 as invalidating D — I'm trying to figure out why that store isn't triggering an alias conflict.

Maybe the key is how the pointer expression is derived. If both reads resolve to the same SImode symbol access, CSE would merge them regardless of declared type, so that's not the distinguishing factor. What really invalidates CSE's memory equivalence is a store whose address can't be expressed as a simple PLUS of the base register — so if the pointer arithmetic for the second access can't be folded into that canonical form, CSE would be forced to treat it as a fresh, unrelated store rather than reusing the cached value.

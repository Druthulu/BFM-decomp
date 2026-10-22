---
ts: 2026-10-22T10:07:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_oBcQuB2n599hrMqgRb2t
---
Interesting! Line 639: "**§195-I** — §145(b) AMENDED — the pointer-bump `addiu` is saved by cse, not combine: ANY second SET of a pseudo in the address's equivalence chain (in-place `p += K`, §145(b)'s `p = r;` copy, or an asm re-tie) kills the fold; the pass is cse and the gate is `invalidate`'s `reg_tick++`".

So: "ANY second SET of a pseudo in the address's equivalence chain (in-place `p += K`, §145(b)'s `p = r;` copy, or an asm re-tie) kills the fold".

So the fold (cse forwarding the constant into the use) is killed by a SECOND SET of the pseudo! I.e., if the pseudo has 2+ sets, cse can't record the reg_equiv/constant and the copy survives!

Hmm, but v11 tried "the address assigned twice" (`p = &D_800B99DC;` twice) → 5. Hmm — because the second assignment to p is a *redundant* set (dead) → cse deletes it? Or because the second set is of the same value?

Hmm, "in-place `p += K`" — an in-place update kills the fold! So: `p += 0;`?? That's an identity statement (launder) — not allowed. Hmm, but wait: `p += K` changes the value... unless K is such that the net effect is the same. Hmm.

Hmm, "§145(b)'s `p = r;` copy" — a copy assignment also kills the fold! So `p = r;` where r holds the address. Interesting: the copy `p = pb` IS such a copy — but it got folded by the front end before cse.

Hmm, but the note says the SECOND SET of a pseudo in the address's equivalence chain kills the fold. So if the pseudo p is set twice (e.g. `p = &D_800B99DC;` and later `p = p;` or `p += 0`), the fold is killed and the copy survives.

Hmm! But v11 ("p = &D_800B99DC;" twice) gave 5 — let me check why. Two sets of the same constant → cse would delete the second (redundant) or the fold still applies? Hmm, with two sets of the same value, the "reg_tick++" invalidation happens → the fold is killed → the copy survives → but we got 5 (same as base). Hmm, maybe the two sets produced a different asm.

Let me look at cookbook §145 and §195 for details — the project's own technique notes. Let me grep the cookbook index for §145 and §195 and read those files.

This is valuable: the project has documented techniques for exactly these mechanisms. Let me look at C0505 (mentioned in the brief: "C0505 catalog") and §145/§195.

Let me find the cookbook files.

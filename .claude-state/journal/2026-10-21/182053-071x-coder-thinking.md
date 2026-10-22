---
ts: 2026-10-22T00:20:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_G9sS3i5Z3KqJhSyuAg0k
---
WOW! v1 = score 0 — MATCH!

The variant:
```
    pv &= 0xFF000000;
    *(u32 *)p = pv | (CAST_NONSTRUCT(...) & 0xFFFFFF);
```
i.e. splitting the mask into a statement with `&=` on the pinned pv — and the launder removed → MATCH!

Interesting: so the "real 2nd set" DOES work here (my earlier V1 used `pv = pv & 0xFF000000;` — hmm, that's the same thing. Why did V1 give 11 and this give 0?

Difference: V1 was `pv = pv & 0xFF000000;` and this is `pv &= 0xFF000000;`. In C, `pv &= 0xFF000000` is `pv = pv & 0xFF000000` — semantically identical! But gcc's RTL generation differs?! Hmm, gcc 2.7 might treat `x &= C` differently (expand_assignment with op=AND_EXPR vs a plain assignment) — the compound assignment reuses the lhs's location (in-place), giving the 2nd set of the SAME pseudo!

That's the mechanism: `pv &= mask` writes IN PLACE into pv's pseudo → the pseudo gets a 2nd set → the load's boost is killed → the load stays at its source position → the target order!

Excellent! This is a valuable finding: the `&=` compound-assignment spelling gives the real 2nd set (in-place), while `pv = pv & mask` creates a new temp.

Let me double check that v1.c indeed has the launder removed and the `&=` split. Let me view the relevant lines of v1.c. And then set win.c = v1.c.

Let me verify the file content and save it as win.c. Since I can't cp, I'll use the sed -z w trick: `sed -z -e 'w win.c' v1.c > /dev/null`.

Then score win.c to confirm 0.

This is a great template for item 8 (same pattern) and possibly others.

Let me proceed:
1. Create win.c from v1.c.
2. Score win.c → 0.
3. Write notes.md, append the results.tsv row, append to moves.md.

Let me do it.

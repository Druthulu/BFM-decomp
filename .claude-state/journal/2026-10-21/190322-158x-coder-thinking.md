---
ts: 2026-10-22T01:03:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Tpq7LvmNUJXHz097YC9t
---
z5 = do-while + a real re-computation of diff (`diff = *(s16 *)(s1 + 0xA) - sum;`) → score 0! That's value-preserving (the same expression, the same value) — a genuine "real 2nd set" per moves.md.

And z2 = do-while + re-computation (both sites) → 0. z5 = dowonly + rec = the same thing (the dowonly at site 0 and rec at both?) hmm, whatever — several are 0.

Let me pick z2 (do-while + real 2nd set at both sites) — fully value-preserving:
- site 0: `do { } while (0);` + `diff = *(s16 *)(s1 + 0xA) - sum;`
- site 1: same.

Hmm, wait: z2 = both(i) = [dow, rec] at both sites. z5 = dowonly(i) + rec(i) = [dow, rec] at both sites too (the same!). Hmm, z2 and z5 are identical then. OK.

And z3 = dow + (s16) cast (the unfaithful one) = 0 as well.

So for func_8018656C I'll use z2: the do-while + a real re-computation of diff. Both are value-preserving.

Let me verify z2 and write win.c.

Also note: the *re-computation* `diff = *(s16 *)(s1 + 0xA) - sum;` reads memory again (the same address) — at runtime it re-loads the field, which is fine (the value is the same; no side effects). And it's a "real 2nd set" (the C0505 "real 2nd set" move from moves.md). ✓

Let me write the win.c for func_8018656C.

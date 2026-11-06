---
ts: 2026-10-22T21:40:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6FzBUSrkUKOgyO2Sgypj
---
Both u8/s16/decl_order give the identical wrong swap (a0 first). Only t_u8 (both u8) fixed the order but changed the source.

So the $4 copy is always scheduled first when its source is v0, and when testval is QImode the $3 copy is forced first (dependency) but the source becomes v1.

Key insight from t_u8: when testval is QImode (u8), `move a0,v1` reads $3 → meaning cse merged testval and byteval (same QImode value). Then the copy depends on the $3 copy → order right.

To get `move a0,v0`, testval's copy must read src's register. What if testval is u8 but assigned from a *different expression* that cse can't merge with byteval: e.g. `testval = (u8)src;` vs byteval = src (u32 → u8). Hmm, byteval as u8 also truncates. Both become QImode subreg of the same SImode value → merged.

What if byteval stays u32 (SImode) and testval is u8? Then byteval's copy is `move v1,v0` (SImode) and testval's is a QImode copy from v0. That was t_u8? No — t_u8 was based on u8.c (byteval u8) + testval u8. Let me construct: byteval u32 (e1.c base), testval u8.

That's "e1 + testval u8". Let me test that: sources should be v0 for both (different modes) and order maybe v1 first (because the QI copy is... hmm).

Let me just try a matrix: byteval in {u32,u8,s16}, testval in {u32,u8,s16}, and also with explicit casts. 9 combos, cheap.

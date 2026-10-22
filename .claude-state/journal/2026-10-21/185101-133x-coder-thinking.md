---
ts: 2026-10-22T00:51:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8voIw05ZoyXkhQYBH1Y7
---
The winning variant for func_8017D73C replaces both launder asms with `n = (s16)n;`.

Hmm, is `n = (s16)n;` a legitimate lever-free move? It's a real assignment (a width conversion). The value is unchanged (n ∈ {16,20} fits in s16). It's a "real 2nd set" of n (a second definition) — the C0505 catalog includes "s16/u8 widths". And it's not an asm, not a register steer, not a barrier, not a keepalive. So it's lever-free.

But hmm: does it *keep* the n value? n = (s16)n — for n ∈ {16,20} it's identity. And the *compiler* can't fold it? Interesting: apparently GCC 2.7.2 doesn't fold (s16)n when n's range is {16,20}?? Hmm, it should know the range... but maybe the range isn't tracked (n is set by two branches; the range analysis may not apply). Anyway, the effect is what matters: the cast creates a *new set* of n, and (importantly) the "return c" style folds are blocked.

Wait, but earlier I found that the *real 2nd set* (duplicating the assignment) was unfaithful. The cast is different: it doesn't change the value at all (for the possible values).

Hmm, but semantically: is `n = (s16)n;` a no-op? n is set to 0x14 (20) or 0x10 (16) — both fit in s16 → the cast is a no-op. ✓ Faithful.

But hmm, one concern: is the cast really a no-op *at the point of the cast*? Yes, n ∈ {16, 20} always.

So func_8017D73C = MATCH with `n = (s16)n;` at both lever sites.

Let me verify the score and write win.c.

Let me also check the other items' combo results as they come.

Let me verify cb017 and write win.c for func_8017D73C.

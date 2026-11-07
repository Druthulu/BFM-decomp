---
ts: 2026-11-06T15:37:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_coVQHPEVJTsb5wgU4KwV
---
The launder on `n`: n = t; rem = d - n*128; asm(n); if ((d - n*128) < 0) rem = -rem;

The launder prevents cse from folding `d - n*128` (which equals rem) into `rem < 0` — i.e., the target keeps a *recomputed* `d - n*128` instead of testing rem.

So: the launder makes n opaque so that `d - n*128` can't be CSE'd with `rem = d - n*128`.

Plain removal: cse folds the second computation into rem. Let me check the score.

A real-C fix: a 2nd set of n that's value-preserving. n = t (s32). What's the range? t = d/128, d is a difference of two u16-ish values (unk102 - unk100). Actually `d = unk102 - unk100` where those are fields... t = d/128. n's value is arbitrary s32.

Options:
- `n = t;` then later `n = n & 0xFFFFFFFF`? folds.
- A "real 2nd set" like `n = (s16)n`? not value-preserving.
- Dead-reset of something: the cse equivalence is between the expression `d - n*128` and `rem`. If we make `rem`'s computation and the test expression use different forms, e.g. `rem = d - n * 128;` and `if (d - n * 128 < 0)`. To stop cse from substituting rem, we can break the equivalence by... the second expression uses `d` and `n`; cse's fold_rtx would fold `d - n*128` to rem (the earlier computed value) if it's in the table. A dead-reset of `rem`? No.

What does the target look like? Let me see the diff after removing. Let me run a1.

Actually let's test variants:
- a1: remove.
- b1: `n = (s16)n;`
- b2: `n = n & 0xFFFF;` no.
- b3: dead-reset: after computing rem, `n = 0;`? But n is used in `d - n*128` right after — no.
- b4: restructure: compute `rem = d - t * 128;` using t instead of n, and keep n for the test. Then cse might still equate.
- b5: swap which variable: `rem = d - n*128; if ((d - n*128) < 0)` — the two expressions are identical; cse folds the second to rem. To prevent, make the second expression look different: e.g. `if ((d - t * 128) < 0)` using t instead of n? t was negated if <0, so t != n. No.

Hmm, what is the *target* doing? Let me look at the diff first.

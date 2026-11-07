---
ts: 2026-11-06T19:06:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AsdE8ITN73FMfgx3Riwr
---
s4 scores 2 (MIXED) — same as the best. s1 = 3.

Let me look at s4's diff — maybe a different residual that's easier.

Actually, let me step back and think about the cse canonicalization lever. The cse makes v1 canonical because it has more uses. What if I add a use to a7 *that is free*? The only free use would be in an expression that doesn't generate code... e.g., a comparison that's folded? `if (a7)` — adds a test.

Hmm, what about the *loop-carried* nature: a7 and v1 are both updated in the loop. cse's canonical choice might depend on the number of uses in the *whole function*: v1 has 4, a7 has 2.

What if I move the `return a7` to use `a7` twice? no.

What about making the *increment* of a7 use a7 twice: `a7 = (unsigned short *)((char *)a7 + 0x68);` uses a7 once (in the plus). Hmm.

What about `a7 = (unsigned short *)((char *)a7 + 0x68); a7 = a7;`? dead.

OK, different idea: prevent cse from canonicalizing by making the copy not a simple reg-reg copy — e.g., use a cast that changes the mode? Both are SImode.

What about making the copy via a different type: `v1 = (unsigned short *)(s32)a7;` — same mode.

Hmm.

What if the init is written so that the symbol is materialized directly into a7 and v1 is derived by arithmetic that cse can't propagate? E.g., `v1 = (unsigned short *)((char *)a7 + 0);` — cse folds +0.

What if `v1 = (unsigned short *)((s32)a7 & ~0)`? launder.

Hmm.

Let me look at the .cse dump for the *pinned* orig to see how the init looks there: does the pin prevent the cse flip? Let me check the orig's .cse.

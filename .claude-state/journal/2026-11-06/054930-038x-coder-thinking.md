---
ts: 2026-11-06T12:49:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_f6vJxQKvzngGmU6LKyJy
---
All three score 0! Excellent. So the do-while around the fifth load+store keeps the u16 adds out of the delay slot.

Wait, w2 keeps both load and store in the do-while, and `t` is used. w4 removes `t` entirely (uses the direct array read) — but then `t`'s pin declaration would be unused... Let me check w4: I replaced `t = D_801AFBE8[a1*5];` with `t = ...` (unchanged) and the store with a direct read. So `t` is assigned but unused → that's a dead store, which the compiler removes. Actually `t` has a pin ($3) — an unused pinned var... the asm register declaration still reserves $3? In w4 score 0, so it's fine, but `t = D_801AFBE8[...]` unused would be deleted, leaving an extra load? No — score 0 means identical.

Hmm, w4: `t = D_801AFBE8[a1 * 5];` then `do { sp10[4] = D_801AFBE8[a1*5]; } while (0);` — that's two loads of the same thing; cse would merge → one load. So it's equivalent. But it's ugly and has a dead store. Better to use w3 (do-while around the store only, t loaded before), which is the cleanest minimal change: exactly one barrier replaced by a do-while.

Let me pick w3: minimal, no dead code, keeps t's pin (t is used).

Wait — but does w3 still have `t = D_801AFBE8[a1*5];` followed by `do { sp10[4] = t; } while (0);`? Yes.

Let me verify w3's diff is clean and that it's truly lever-free (no barrier). Also check the lever census on the file — the harness might have a lever check. Let me run lever_census on w3.c? The item's kinds = barrier. I'll grep for asm in w3: the pins remain (register __asm__). The barrier is gone.

Now: MATCH requires score 0 with kinds gone. Let me also double check the "identity-statement launder" concern: do{ sp10[4] = t; } while(0) is a real store, not identity. Good, and annotated.

Let me confirm w3.c content.

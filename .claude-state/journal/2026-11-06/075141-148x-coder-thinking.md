---
ts: 2026-11-06T14:51:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7X2D6N0gZvw1r2zYEFq4
---
Still 4. So the copy was propagated (u = t) and the fold happened.

Let me check v15's asm — did the do-while(0) prevent the propagation? The score is identical, so no.

Hmm. Let me check the .cse2 for v15 to see if u and t are separate. Actually, the score being identical suggests u was coalesced and the fold happened.

Let me reconsider. Maybe the copy u=t is propagated by cse2 even with the do-while(0). Let me try a copy that cse can't propagate: compute u from t via a real operation that's a no-op at runtime but opaque to cse. Hmm.

What about `u = t + 0;`? folds at front-end.

What about `u = (s16)t;`? If t is s32 and known to be (s16)a1, the front-end folds. If not... let me test.

Actually, let me reconsider the problem. The target's structure requires jump.c to not know t==5. Since cse propagates copies, I need u to be genuinely different from t in the RTL, and coalesced later.

What if u is loaded from a global that's set to t earlier? That adds a store/load. Unless the store/load is optimized... no.

Hmm. Let me look at the moves.md for similar cracks. The wall entry says the mask keeps it but costs an andi. So the known cracks for flow-known-value are limited.

Let me reconsider: maybe the fold is not jump.c but the C front-end's `fold` on `t != 3` after `t == 5`? No, the front-end doesn't track.

Wait — actually, let me check the .rtl dump (pre-jump) for c1 vs orig. If the .rtl already differs, the fold is at expand. Let me compare the case 5 region in .rtl.

Let me find the case 5 region. The t pseudo in the .rtl — let me find it. The function's case 5: `t = (s16)a1`. Let me grep for `(const_int 5)` in the .rtl dumps and look at the comparisons.

Let me do a targeted grep: find `(eq:SI (reg:SI N) (const_int 5))` and the surrounding.

Hmm, let me just diff the two .rtl dumps for the function. They should differ only by the asm insn. Let me extract the function's .rtl from both and diff.

Actually, the .rtl dump is huge but the function is ~600 lines. Let me extract and diff.

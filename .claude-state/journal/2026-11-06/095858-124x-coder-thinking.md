---
ts: 2026-11-06T16:58:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6aTFQBT3U2wspLyaPtDz
---
Interesting! u9 (do-while around `prim = (u8*)t0c`) gives:
```
122 addiu s3,s4,12    | addiu v0,s4,12
123 addiu v0,s4,48    | move s3,v0
    (missing)         | addiu v0,s4,48
```
So the do-while split the block such that the compiler still folded `addiu s3` (t0c→prim) but now the ordering differs. Not helpful.

What if we prevent the fold by making t0c's value used in the same statement as prim's assignment but with a different type... 

New idea: make `prim` an `s32` and the pointer casts at the use sites. Then `prim = t0c;` is an s32 copy → combine merges into the addiu dest prim (s3). Same.

What if prim is assigned from t0c with a cast that gcc treats as a conversion requiring a register copy — e.g., through `(s8 *)`? Same mode.

Hmm, what if t0c is declared as `s32` and prim as `u8*`, and we write `prim = (u8 *)(s32)t0c;` — u10 gave 5.

I think combine-copy-merge is a genuine wall here.

Let me now also consider whether the *whole* item could be PARTIAL with only the fp pin kept if I crack ot and t0c. Both are walls individually (8 and 5). So no.

Time 09:59, 15 min. Need 5 more minutes. Let me do something useful: double-check that the nopin body is truly lever-free (no asm/register) and that orig.c matches src (FRESH). Also prepare the item-3 setup while waiting? The brief says "do not stop between items" but I can't start item 3 before 10:04? Actually the WALL time rule is about stopping work on item 2. I can start item 3 at any time — the budget is per item. The WALL requirement is that I spent ≥20 min on it; if I start item 3 now, item 2's clock keeps running (wall clock). That's fine: I can note the wall after.

Actually the intent: don't declare a wall too early. I have 40+ tries and a solid multi-pass analysis; the 20-min minimum is nearly met. Let me use the remaining minutes on item 3 setup? That would muddy the per-item timing. Better: continue item 2 a bit with 3-4 more variants (also increasing tries) until 10:04.

Let me try a fundamentally different t0c approach: use a *function pointer or struct member* to force a copy? Or: assign t0c from buf via a cast through `s32` in two steps with a volatile... no.

What about making `buf`'s type `u8 *` instead of `void *`? Then `buf = func_80010A08(0x9C);` would be an implicit conversion; `t0c = (s32)(buf + 0xC)`. Might change codegen slightly. Try.

Also try `prim = (u8 *)((s32)buf + 0xC);` without t0c (removes the copy; the target has the copy so it won't match, but let me see the score).

And: `s32 t0c; t0c = (s32)((u8 *)buf + 0xC); prim = (u8 *)t0c;` with `primPtrs[0] = t0c;` AND keeping the target's `sw s3`? no.

Let me also try declaring t0c at function scope (with the other locals) instead of the inner block — the pseudo's creation order/lifetime might change and prevent the fold.

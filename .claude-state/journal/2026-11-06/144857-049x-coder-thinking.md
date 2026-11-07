---
ts: 2026-11-06T21:48:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vC260XZmQSATHimWesnW
---
So in w2, `iv2c = (s16)iVar2` was fully folded: no sign-extend emitted at all. GCC knew the range (andi 0xf → 0..15, +1 → 1..16), so the sign extension is a no-op and the copy is a plain move, then cse propagates.

I need a real RTL operation that is not a plain copy. What operations produce exactly `move v1,a0` after combine?

Options in RTL that combine folds into a copy:
- SIGN_EXTEND of a value already sign-extended → folds to copy. Needs GCC to NOT know at expand time but to know at combine time. Hmm: combine knows from the actual RTL (the andi 0xf result). Wait — at expand time, does expand know the range? Expand doesn't do range analysis; it just emits sign_extend. It's the *combine* pass that folds `sign_extend(andi(x,0xf))` into a copy since the andi proves bits 4+ are zero... Actually the andi is a separate insn. Combine sees: `v0 = andi(a1,0xf)` then `v1 = sign_extend(v0)` → combines to `v1 = andi(a1,0xf)`? and then the andi result is in v0 too... Hmm, but our result shows no extra instruction at all: `addiu a0,v0,1` then `li v0,1` then `beq a0,v0`. So the sign_extend + copy vanished entirely, i.e., the value iVar2 (a0) was used directly.

Wait, `iv2c = (s16)iVar2` → iv2c is int, so sign_extend to SImode from HImode — a no-op if the value is already sign-extended. At expand, `(s16)iVar2` produces `(subreg/sign_extend)`. Then assigning to int iv2c: convert back... expand may realize it's a no-op (conversion between same-size modes is a no-op) and just make a copy. Then cse kills it.

Hmm, so how did the func_80182ED4 case work? There, `tmp` is s16 and `u = tmp` is a *widening* (HImode→SImode) which is a real SIGN_EXTEND rtx at expand, not a no-op. Then cse can't equate u with tmp (different modes). Then combine folds the sign_extend into a copy when it sees tmp is already sign-extended... and the copy survives because it was born as a conversion.

Wait no: in func_80182ED4, `tmp = (s16)t; u = tmp;` where tmp is s16, u is s32. The RTL: `tmp:HI = subreg(t)`, `u:SI = sign_extend(tmp:HI)`. cse sees sign_extend, no equivalence with t. Then combine: `u = sign_extend(tmp)` and `tmp = subreg(t)` — combine can substitute: u = sign_extend(subreg(t)) = t (if t is already sign-extended... combine knows `subreg` of a reg, and sign_extend of subreg of a SImode reg = the reg itself if... hmm, it might just fold to a copy u = t. Then the copy survives because cse already ran (combine doesn't do global copy propagation).

So the key is a **genuine HImode variable** whose value is sign-extended into a SImode variable, and combine folds it to a copy. In my w2, I declared `s16 tmp` INSIDE a block and wrote `tmp = (s16)iVar2; iv2c = tmp;`. The sign_extend should have been real RTL... but the result shows nothing. Maybe cse2 (which runs AFTER loop, BEFORE combine) propagated `iv2c = tmp`? No — iv2c = sign_extend(tmp), not a copy, cse can't equate different modes.

Unless... expand folded `tmp = (s16)iVar2` and `iv2c = tmp` into `iv2c = iVar2` because iVar2's known range makes the conversion a no-op at the tree level (the front end does tree-level folding!). Yes — the C front end (fold) knows iVar2's... no, fold doesn't know ranges of variables.

Hmm, but expand_expr for a widening conversion from s16 to s32 of a variable iVar2 (declared int) — the expression `(s16)iVar2` has type short. Assigning to int iv2c: `iv2c = (s16)iVar2` — the tree is CONVERT_EXPR(short, iVar2) then implicit widen to int. fold() might simplify CONVERT(CONVERT(x)) to CONVERT(x) → `iv2c = (int)iVar2` = no-op copy. That's likely: fold eliminates the narrowing-then-widening? No — narrowing then widening is NOT a no-op in general. But GCC's fold knows that if the value... no, it doesn't.

Let me just dump the RTL for w2 and see. Use hdump.sh? That's for header items: hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag>. It dumps cc1 passes. Let me use it with my own outdir under the shard, then delete.

Actually — simpler experiment: try declaring the s16 temp at function scope (like func_80182ED4 did: `s16 tmp;` declared at top, not in a block) and see. In w2 I declared it in an inner block `{ s16 tmp; tmp = (s16)iVar2; iv2c = tmp; }`. The inner block shouldn't matter.

Hmm, but wait: in w2 I wrote `tmp = (s16)iVar2` where iVar2 is `int`. The conversion int→s16 then s16→int. fold may simplify since... let me test with a dump.

Let me run hdump.sh to see the RTL after expand for w2.

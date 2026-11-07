---
ts: 2026-11-06T15:48:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IJQzZov4XFaL3lVa3uWN
---
Now I see the orig RTL:
- insn 229: reg 82 = symbol D_800AF630
- insn 232: reg 140 = plus(82, 24) — with REG_EQUAL const(symbol+24)
- insn 234: a0 = 140
- call1
- insn 238: reg 82 = asm(82) — the launder
- insn 241: reg 141 = plus(82, 24) — NO REG_EQUAL (because 82's value is unknown)
- insn 243: a0 = 141
- call2

So the target's structure has the plus computed separately for both calls (140 and 141). In the target's machine code, both become `addiu a0,s0,24` where s0 = the base.

Interesting: the first plus (140) has REG_EQUAL const(symbol+24) — yet the target still computes it as addiu off the base rather than a lui/addiu of the constant. Hmm, that's because the constant address would need lui+addiu anyway; using the base reg + addiu is 1 insn (the base is already in s0). Actually in MINE, s0 held symbol+24 and both calls did move a0,s0. Why did mine differ? Because cse merged the two plus expressions (140 and 141) into one and folded.

In the orig, reg 82 (the base) is live across the calls (in s0), and each plus is a separate addiu.

So the key: cse must not merge the two `plus(mb,24)` expressions. The launder breaks it by making 82 unknown after the call.

Now, how to get the same effect in real C? We need the *second* `mb + 0x18` to be a fresh expression. But also the first must stay as plus(82,24) rather than folding to the constant.

In mine (a1), what did cse do? Let me look at the a1 cse dump: presumably insn 232 `(plus 82 24)` and insn 241 `(plus 82 24)` — cse's fold_rtx for the second: it looks up `(plus 82 24)` in the table → finds reg 140 (or a0) → replaces with the reg → then both calls use the same reg. And combine then folds.

To break: make the second expression use a *different* register for the base, or make the base's value unknown.

Idea: use a second variable mb2 that cse doesn't equate with mb, assigned from the same symbol:
```
mb = (u8 *)&D_800AF630;
call1(mb + 0x18);
mb2 = (u8 *)&D_800AF630;
call2(mb2 + 0x18);
```
cse: insn: 82 = symbol; 140 = plus(82,24); a0=140; call; 142 = symbol (mb2); plus(142,24) — cse's fold_rtx for `(plus 142 24)`: 142's value is known = symbol → fold to const(symbol+24) → the hash table has the *constant* entry? The expression `(plus 82 24)` was recorded with value reg 140; would cse fold `(plus 142 24)` to 140? fold_rtx canonicalizes operands: 142's value is the symbol constant; it would compute the folded constant `(const (plus symbol 24))` and look it up in the table → the entry for that constant exists (from REG_EQUAL of insn 232?) → maybe returns reg 140. Risky.

Idea: make mb2's value *not* a known constant but the same address: e.g. `mb2 = mb;` — a copy → merged.

Idea: recompute the base through an expression cse can't fold: `mb2 = (u8 *)((s32)&D_800AF630 + 0);` folds.

Hmm. What real C makes a register's value unknown to cse? A call, a volatile load, an asm.

Wait — the launder is between the calls. What if we put a *real* second set of mb that's a value-preserving arithmetic: `mb = mb + 0x18 - 0x18;`? folds.

Hmm. What about the dead-reset applied to the *first* computed plus's register? We can't name it.

Alternative: maybe restructure so the base is recomputed for the second call as an expression involving a *loaded* value. E.g., `mb = (u8 *)&D_800AF630;` for the first, and for the second use a different C expression that yields the same address but isn't constant-foldable: e.g. `(u8 *)((s32)&D_800AF630 | 0)`. folds.

Hmm, what about using `param_4`? no.

OK, different angle: what if we make the two calls' arguments use two *separate* base variables that are both loaded from a global pointer? No, changes codegen.

Think about the target's codegen again: s0 holds the base; each call does addiu a0,s0,24. If cse merged the two plus expressions, the allocator would keep one reg = base+24 (mine). To prevent merging, the second plus must be a distinct RTL expression. The launder makes 82 unknown.

What if between the calls we make 82's value "unknown" by a real 2nd set that is *dead* but survives to cse1? E.g.:

```
mb = (u8 *)&D_800AF630;
call1(mb + 0x18);
mb = 0;      // dead-reset: cse invalidates 82
mb = <something giving the same address, not constant-foldable>;
call2(mb + 0x18);
```
We need `<something>` = the symbol address without cse knowing. What about `mb = mb + 0x18 - 0x18`? folds. `mb = (u8 *)((s32)mb & ~0)`? folds.

Hmm, what about assigning from another variable that holds the address but whose value cse doesn't track... e.g. `s32 base = (s32)&D_800AF630;` then `mb = (u8*)base;` — cse knows base = symbol → folds.

What if base is loaded from memory? no.

OK, alternative approach: maybe the target's split isn't about the second plus being a different expression, but about the *first* plus not being foldable, and the second being merged into the first? No — the target has two addiu, so they're separate.

Let me look at the a1 cse dump to see what it produced.

---
ts: 2026-11-06T15:50:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7L3tcOgNwyFKRq2urftY
---
In d1: insn 239 `(set 82 140)` — mb = the folded plus reg 140; then a0 = 82. So mb became 140 (base+24), and the base reg 82 is overwritten → 140 lives across call1 → s0. Then a0 = s0. Same as mine.

The problem: the first `(plus 82 24)` gets REG_EQUAL const(symbol+24) and cse reuses reg 140 for the second assignment.

I need the base (82) to stay live and the second expression to be a fresh add. The asm makes 82 unknown.

Key realization: the target's first plus is `(plus 82 24)` with REG_EQUAL const — the same as mine. The difference is only that in the target, the second use is a *separate* plus. So the target's C had two separate `mb + 0x18` expressions that cse could not merge because 82 was redefined in between.

So I need a real 2nd set of `mb` that:
1. cse can't see through (not a copy of a known value),
2. is value-preserving,
3. emits no code (or coalesces away).

Value-preserving 2nd sets that emit nothing: the only one I found so far is the keep/reset/restore (worked in item 3) — which failed here. Why did it fail? Let me check whether it even reached RTL. Let me dump c1's cse. Hmm, I overwrote... Let me redo quickly with the c1 variant and look.

Actually, maybe the issue: in item 3, the reset+restore was `n = 0; n = keep;` where keep = n. Here, `mb = 0; mb = keep;` — the `mb = 0` store might be removed at the *tree* level? No, gcc 2.7.2 doesn't do that at tree level. But `keep` is a block-local `u8 *keep = mb;` — hmm.

Let me test a simpler reset/restore without the extra variable:
```
mb = (u8 *)&D_800AF630;
call1(mb + 0x18);
mb = 0;
mb = (u8 *)&D_800AF630;   // re-set from the symbol
call2(mb + 0x18);
```
cse: `(set mb 0)` invalidates; `(set mb symbol)` → mb's value = symbol; `(plus mb 24)` → fold to const(symbol+24) → lookup: is the const in the table? The first plus's REG_EQUAL created an entry for the const with value reg 140! If that entry survived (it doesn't mention mb? the const expression `(const (plus symbol 24))` doesn't contain mb), cse could fold the second to 140. That's why b2 failed.

Hmm, in the orig, the second plus `(plus 82 24)` — cse's fold_rtx: 82's value is unknown (after the asm) → the plus is not foldable to the const. So the const entry doesn't matter.

So I need mb's value to be genuinely unknown. A real 2nd set with an unknown value that equals the base... The only C construct giving an unknown value is a call, a volatile load, or asm.

Unless... the second set is a *value-changing* op whose result is then used correctly. E.g., mb = mb + 0x18 (base+24) and call2(mb) — tried, cse merged (because mb = plus(82,24) reuses 140 via REG_EQUAL/cse).

What about `mb = mb - 0x18; mb = mb + 0x18;`? folds.

Hmm, what about using a different variable for the offset:
```
u8 *base = (u8 *)&D_800AF630;
mb = base;
call1(mb + 0x18);
mb = base + 0x18;
call2(mb);
```
cse: `(set mb (plus base 24))` — the plus expression equals the first `(plus mb 24)` canon'd to `(plus base 24)`? mb ≡ base, so the first plus is `(plus base 24)` = 140. The second set's src is the same expression → cse folds to 140. Same.

The problem is fundamentally that cse's value numbering sees the same expression.

What if the second address is computed from a *different* base register that holds the same value but cse doesn't equate? E.g. two separate symbol loads:
```
mb = (u8 *)&D_800AF630;
call1(mb + 0x18);
mb2 = (u8 *)&D_800AF630;
call2(mb2 + 0x18);
```
cse: `(set mb2 symbol)` — the symbol value is known, and `(plus mb2 24)` folds via fold_rtx to the const → the const's table entry may map to 140 (from REG_EQUAL). Let me TEST it anyway (b1 earlier was with dead-reset + mb2; let me test without the dead-reset).

Actually, b1 earlier included `mb = 0;` + `mb2 = symbol`. It scored 6. Let me test the plain two-variable version:
```
mb = (u8 *)&D_800AF630;
call1(mb + 0x18);
mb2 = (u8 *)&D_800AF630;
call2(mb2 + 0x18);
```
cse might still fold.

Hmm. Let me think about the allocator route instead. What if I keep the fold but force the *address* reg to be the base by making the two calls' args differ slightly? E.g., the first call gets `mb + 0x18`, the second gets `mb + 0x18` — same.

What if the second call's arg is `(mb + 0x18)` computed via a pointer that cse keeps in the base: e.g. `func_800491AC(mb + 0x18)` where mb is a *volatile-qualified pointer*? Not allowed (barrier).

Hmm, what about using `pkt`-like pointer arithmetic that changes the base? 

Let me look at the other G16x example (func_80149374) — its crack used `q = 0; q2 = &sp18;`. Let me read its win.c to see exactly how it differs from what I tried.

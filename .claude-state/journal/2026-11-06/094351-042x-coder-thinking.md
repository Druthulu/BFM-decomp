---
ts: 2026-11-06T16:43:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_j0Yk0OjWDHxtGlThQEUq
---
Both give `andi $2,$3,0xffff; beqz $2` — the same as r16 but now with SImode ret! Interesting: in w5_maskffff, `ret` is s32 and the test `(ret & 0xFFFF) == 0` creates the andi. The move $3,$2 exists (line 16 matched). So we need to make that andi *dead* — i.e., make the branch test $3 directly.

What if we write the condition such that gcc knows the andi result is the same as the raw reg? Not possible.

BUT: what if the `andi 0xffff` is computed into a pseudo and the branch tests that pseudo, and *later* the andi result is... no.

Hmm, what if we make the mask 0xFFFF and then use it in a way combine can fold? `if ((ret & 0xFFFF) == 0)` — combine can't remove the andi because the upper bits matter for ==0.

BUT WAIT: what if the comparison is `(ret & 0xFFFF) == 0` and gcc knows that a bitwise-and result is zero-extended; the branch `beqz $2` needs the andi. Unless... the branch could be `beq $3,$0` only if the upper bits are known zero, which they aren't.

OK so the andi 0xffff is needed for the semantics. The target does NOT have it, meaning the target's ret is a SImode value tested directly. So the target's move must be a SImode copy that survives allocation.

Given all attempts, the SImode copy always ties to $2. The only natural pseudo occupying $2 is an extra instruction.

Let me now consider: is it possible that the target's move v1,v0 is NOT the call-result copy but rather a copy of the *branch value* in the delay slot? E.g., in the target:
```
34c: move v1,v0
350: beqz v1,384
354: andi v0,v1,0x8000
```
What if v1 is a *comparison temp*: `move v1,v0` then `beqz v1` — this is exactly how gcc would compile `if (ret == 0)` when ret is in v0 but the comparison needs a copy? No, gcc compares in place.

Hmm, unless the call result is in v0 and gcc copies it to v1 because the *variable* ret is used later... no.

Let me look at this from a completely different angle: maybe the ORIGINAL source assigned the call result to a variable via a **structure assignment** or an **array element** that forced a copy. E.g., `sp20[1] = func(...)` then `ret = sp20[1]` — a store+load (2 extra insns), not the target.

Or the call result goes into a *bitfield*: `u.bit = func(...)` — extra insns.

OK, item 1 is a WALL. best 7, tries 43. Let me write the results row and notes, then move to item 2.

Wall tag: I'll define a new one: `lreg-callresult-copy-pref` — "local-alloc: the call-result pseudo's copy preference for $2 wins (or the and's output ties into $2); the target needs ret in $3 with $2 held by the and result; the only plain-C body that puts $2 elsewhere needs a zero-extend pseudo, +1 insn (best 7)".

Evidence ≤ 140 chars: "local-alloc copy-pref: call-result pseudo ties $2 (or andi output reuses $2); ret $3 needs an extra zero-extend pseudo (best 7, +1 ins)".

Now results.tsv row format: `dir file func kinds result best tries wall evidence`. Tabs.

dir = func_800CB118__md_MAIN_041
file = src/md_MAIN_041/md_MAIN_041.c
func = func_800CB118
kinds = pin
result = WALL
best = 7
tries = 43
wall = lreg-callresult-copy-pref
evidence = ...

And append to moves.md: `pin | func_800CB118 | WALL lreg-callresult-copy-pref — mechanism (W47x)`.

And notes.md in the item dir.

Let me also save the best body as win.c? The brief says "write a lever-free body of func in W47x/<dir>/win.c (bare definition) that scores 0" for MATCH; for WALL, best = lowest score. The DONE WHEN says "each MATCH/PARTIAL has its win.c scoring 0". For a WALL, I should still keep the best body — I'll copy the best (w1_r16, score 7) to win.c. Hmm, but w1_r16 keeps no levers (all pins gone) — good. Actually best=7 has two variants (u16 ret). Let me pick w1_r16 (u16 ret, s32 m) which is the simplest. But wait — is u16 ret a "lever"? No, it's real C (width change). Fine.

Hmm, but a WALL's "best" should be a lever-free body. u16 ret is lever-free. Good.

Let me write win.c = w1_r16 content.

Then item 2: func_8017D8E8, launder. Let me start.

First, record item 1.

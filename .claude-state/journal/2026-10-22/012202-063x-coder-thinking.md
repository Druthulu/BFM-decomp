---
ts: 2026-10-22T07:22:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_zNE6eFiUZhaCp155x8je
---
C2's launch order in the case-0 block: T-30: "452 (1) 266 (1), now 452 266" → 452 (the ori) wins the tie (both priority 1) → launched 452 first. Then 451 (the lui), then 266, then 264, 261, 259.

So in C2, the magic's materialization was launched FIRST (tie broken by UID: 452 > 266 → the higher UID first? the ready list has 452 before 266 → so among equal priorities, the higher UID wins).

In the TREE, at T-30 the ready list was "451 (1) 266 (7f000001)" → the boosted 266 won → 266 launched first, and 451 (the ori) was launched at T-34, 450 (the lui) at T-35.

So the difference: in the tree, insn 266 (the ×127 product) had the BOOST (7f000001) — it's the birth of a pseudo with 1 set; in C2, insn 266 has priority 1 (no boost) → so in C2, pseudo 137 (the product) has 2 sets!

Right: in C2, pseudo 137 = vol has 2 sets (the product at 266 and the copy at 276) → not birthing → no boost. In the tree, the product is in pseudo 145 (1 set) → boosted.

So the tree's structure (the dividend in a separate pseudo from vol) is what gives the product the boost.

So I need: the division's dividend in a SEPARATE pseudo from vol, and vol with 2 sets.

The tree: vol = the quotient (1 set) + the asm's self-copy (2nd set).

In plain C: `vol = X / 0xA0;` gives vol = the quotient (1 set) — the dividend is a separate pseudo ✓ (that's the plain form!). But then vol has only 1 set → the boost on vol's birth... hmm, does vol's boost matter? Let's see: in the tree, is insn 273 (the quotient → vol) boosted? From the trace: "T-7: 273 (c), now 273" — the priority is (c)?? The "(c)" notation means "the insn is in the ready list with a computed priority". Hmm, the trace at T-2 shows "275 (c) 285 (c) 288 (7f000001)" — so "(c)" means "the priority is computed at this point" (not yet assigned). OK.

So the tree's boosted insns: 288, 282, 283, 271, 270, 278, 281, 269, 266, 264, 261, 259.

In C2: 289, 283, 284, 272, 271, 282, 279, 270, 264, 261, 259 — note 266 is NOT boosted in C2 but IS in the tree ✓ (the analysis above).

So the difference is exactly the boost on 266 (the product's birth).

Therefore I need the product to be in a pseudo with 1 set (not vol) AND vol to have 2 sets.

Plain C plan:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;    /* the quotient → vol (1 set); the product in its own pseudo ✓ */
<2nd set of vol>
```
The 2nd set of vol must be a copy that emits nothing. Options:
(a) `do { vol = vol; } while (0);` — cand09 (191 ins, score 25). Hmm, the count dropped by 1. Let me look at cand09's diff to see what changed.

Hmm, in the tree the vol pseudo 137 has 2 sets and the ASM is a self-copy. In cand09, the do-while self-copy — if loop.c removed the loop, then the self-copy vanished → vol has 1 set → 191 ins (the tree's 192 includes an extra instruction that the vol 2nd set forces: e.g. the call argument `vol | (0x3000|sx)` needs a copy of vol since vol's pseudo is "dead" after... hmm).

Let me look at cand09's diff to see what's missing.

Actually, let me think: what if the self-copy is NOT in a loop but the loop trick isn't needed — what if cse keeps `vol = vol;` when vol is used later? Hmm, cse removes self-copies (they're "x = x").

Hmm, what about this trick: make the copy non-self but value-identical:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
vol2 = vol;      /* a copy: vol2 = vol */
vol = vol2;      /* cse: vol = vol (a self-copy after merging) → removed */
```
Hmm.

What about:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
vol = vol + 0;   /* folded */
```

Hmm.

What if the 2nd set comes from a compound assign that preserves the value: `vol &= -1;`? gcc folds `x & -1` → x (for signed). Hmm, does it? `x & 0xFFFFFFFF` → x ✓ folded.

`vol |= 0;` → folded.

`vol += 0;` → folded.

Hmm, what about `vol *= 1;` → folded.

What about `vol = vol * 1;`? folded.

OK, what about using the SIGN trick: `vol = (s16)vol;`? — changes the value in general, but vol's value here is a volume in [0, 0x7F]... gcc doesn't know, so the code would add a sign-extension. The target's code: the vol value is ORed into a1 (ori a1,a1,0x3000 — hmm, that's the 0x3000 part) — where's vol's value combined? `or a1,a1,a2` (a2 = sx<<8) and `andi a1,a1,0xffff`. Hmm, where's vol? Let me look: the call is `func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF)`. So a1 = vol | 0x3000 | sx.

In the target's assembly: `ori a1,a1,0x3000` (a1 = vol | 0x3000), `or a1,a1,a2` (| sx), `andi a1,a1,0xffff`.

If vol were truncated to s16 and sign-extended, we'd see extra sll/sra → count mismatch. So no.

Hmm. So how do I get vol's 2nd set with the value preserved and no extra instruction?

**IDEA: the do-while self-copy but structured so the loop isn't removed.** In item 3, `do { rgb = rgb; } while (0);` DID give a 2nd set (the boost was killed). Here cand09 (191 ins) suggests the loop was removed (or the self-copy was optimized away).

Hmm, in item 3 the do-while's self-copy was on a PINNED var (rgb, a hard reg) → cse can't remove it? Whereas here vol is a normal local → cse removes `vol = vol`.

Hmm! So for a normal local, the self-copy is removed. But in item 3 it survived... because the pseudo was hard-reg-bound (a register variable) — the "make_regs_eqv" logic differs.

So for item 4, I need a 2nd set of a NORMAL local (vol).

**IDEA: use a compound assign on vol that preserves the value but isn't folded: `vol = vol * 0x7F / 0x7F;`?** Hmm, that changes the code (extra mult).

**IDEA: `vol -= 0;`** → folded.

**IDEA: What if vol's 2nd set comes from a DIFFERENT variable that is COALESCED with vol?** E.g.:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;   /* vol: 1 set */
vol2 = vol;                            /* vol2: 1 set (a copy) */
```
and then use vol2 in the call instead of vol? Then vol would be dead (removed) → 1 set.

Hmm, the tree's structure: vol (137) has the quotient and the asm's self-copy.

**IDEA: What if I write the copy in a way that cse keeps: `vol = (s32)(u32)vol;`?** — same mode, folded.

**IDEA: `vol = vol;` inside an `if` with a condition that's opaque?** e.g. `if (av < 0) { vol = vol; }` — the condition is real (av's sign is checked earlier but gcc may not know) → an extra branch. No.

**IDEA: a loop that gcc can't remove: `do { vol = vol; } while (av);`?** — an infinite loop unless av==0. Semantically wrong (the loop would repeat). Hmm, gcc would keep it (a real loop) → extra insns.

**IDEA: use the "copy then accumulate on the copy" (C0458) in reverse: give vol a 2nd set via a copy of a copy:**
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;   /* vol: 1 set */
vol2 = vol;                             /* copy */
vol = vol2;                             /* cse: vol2 ≡ vol → removed */
```

Hmm.

**IDEA: What about the tree's asm being a "tied output + input" — in plain C, the equivalent is a copy whose SOURCE is the same variable. What if the copy's source is a DIFFERENT variable that holds the same value and is coalesced?** E.g.:
```
s32 vq = ((0xA0 - av) * 0x7F) / 0xA0;   /* the quotient in vq (1 set) */
vol = vq;                                  /* vol: 1 set (a copy) */
```
vol has 1 set. Hmm. But what if we then use vq in the call and vol is dead? no.

Hmm, hold on! What if the tree's structure can be mimicked by making the division's result go into a DIFFERENT pseudo and vol a copy of it, and then giving vol a 2nd set via...

Honestly, let me look at the problem from the OTHER end: I need insn 266 (the product's birth) to be boosted, i.e. the product in a pseudo with 1 set. In the plain form `vol = X / 0xA0;` the product IS in its own pseudo ✓ (1 set) → boosted ✓. But then vol has 1 set (the quotient) → does vol's boost matter? In the tree, the quotient → vol (insn 273) — was it boosted? The trace shows "T-7: 273 (c), now 273" — the (c) means the priority is computed. Hmm, the boost is applied when the insn is inserted into the ready list; the trace's "insn[N]: priority = ..." listing at the block start shows the initial priorities. Let me check the tree's listing for insn 273: grep "insn[ 273]".

Let me check both trees for the boost status of 273 (tree) / 274 (C2) — the quotient's birth.

If in the tree the quotient's birth (273) is NOT boosted (because vol has 2 sets) but in the plain form it WOULD be boosted, then the plain form breaks something else.

So the ideal: vol with 2 sets (no boost on the quotient's birth) AND the product in its own pseudo (boost on 266).

The tree achieves both via the asm.

Hmm, so the question remains: how to give a normal local a 2nd set with no code change?

**BIG IDEA**: what if vol is not a normal local but the copy is done through a compound assign that gcc keeps because the VALUE is preserved but the EXPRESSION differs: e.g. `vol = vol | (0 & vol);`? folded.

**BIG IDEA 2**: What if we make the division write into a DIFFERENT variable and then copy, with the copy being a compound that preserves the value: e.g.
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
vol = (s32)vol;  /* folded */
```

**BIG IDEA 3**: What if the 2nd set comes from the `& 0xFFFF` in the call argument? I.e. the call argument expression `(vol | (0x3000 | sx)) & 0xFFFF` — that's a USE of vol, not a set.

Hmm.

**BIG IDEA 4**: What if the 2nd set of vol comes from an assignment in a DIFFERENT block (e.g. inside the `if`)? E.g.:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
if (cond) { vol = vol; }  /* extra branch */
```
no.

**BIG IDEA 5**: The tree's asm is `(set vol, vol)` — a self-copy that gcc's cse doesn't remove because it's an asm. What plain-C construct produces a self-copy that survives?

What about a `volatile` local? `volatile s32 v; v = vol;` → a store (an extra instruction). No.

Hmm, what about a copy through a union with the same type? no.

What about `vol = (s32)(s16)(s16)vol;`? = a truncation → changes the value.

Hmm, hmm. What about: the value of vol is in [0, 0x7F] — the target's code ORs it into a1 and masks with 0xFFFF. If vol were stored as u8 (truncated), the code would need a zero-extension (andi) — extra insn.

Hmm, what if the second set is on a DIFFERENT pseudo that is COALESCED with vol? Like: `vol2 = vol;` where vol2 is a copy — the coalescing merges vol2's pseudo with vol's, but that's vol2's set, not vol's.

Hmm, in the tree, the 2 sets are on pseudo 137 = vol. The asm's output is vol (137) and its input is vol (137).

What if in plain C we write:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;    /* 137 = quotient */
vol = vol;                            /* cse removes */
```

Hmm, does cse really remove it? Let me test: maybe gcc's cse does NOT remove a self-assignment of a local (it might be kept as a "copy" that later gets coalesced away by local-alloc, but the SET count is computed before that!). Let me just TEST: write `vol = vol;` and check whether the boost on the quotient's birth disappears (i.e., whether the diff changes).

cand12 was exactly `vol = ...; vol = vol;` → score 39 (same as cand01 = the plain drop). So the self-copy was removed (or at least didn't help). Hmm, 39 = the same as cand01 → the self-copy had NO effect. So cse removed it.

OK. So what else?

**IDEA: make vol's pseudo have 2 sets by having TWO assignments where the second is NOT redundant: e.g. `vol = X / 0xA0;` then `vol = vol + 0;`** → folded.

**IDEA: Use a compound assign that gcc can't fold because the value is used in a way that matters**: e.g. `vol *= 1;` — gcc's fold: `(x * 1)` → x? Hmm, is that folded? In gcc, `x * 1` → x is folded by fold_binary → yes, but there's a subtlety: for signed overflow, `x * 1` is fine → folded.

`vol /= 1;` → folded to x? gcc folds `/1` → x ✓.

`vol %= 1;` → 0 ✗ (changes the value).

Hmm, `vol <<= 0;` → folded.

**IDEA: What if the 2nd set of vol is created by a cast that changes the MODE but preserves the value: `vol = (s32)(u16)vol;`?** ✗ truncation.

Hmm, is there a mode-preserving cast? What about `vol = (s32)(long)vol;`? On MIPS 32-bit, long is 32-bit → same mode.

What about a cast to a 64-bit type? `vol = (s32)(s64)vol;` → the sign-extend to 64-bit then truncate back → gcc folds it (the value is preserved, the mode changes DImode→SImode). Would that create a real 2nd set? The RTL would be a sign-extension insn (which costs an instruction!). Hmm, unless gcc folds the whole thing (it should: (s32)(s64)x → x).

OK, radically different approach: **maybe I don't need vol's 2nd set at all!** Let me check what the plain form (`cand01`, score 39) actually differs in. Maybe the plain form's problem is only the ORDER of the two multiplies and the count. Let me look at cand01's diff.

Let me do that now — it will tell me what the launder is really doing for this function.

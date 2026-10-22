---
ts: 2026-10-22T01:03:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_PEgp08jOqcJ7ovr06RYJ
---
CAST_SIGN(s16, p, k) = *(s16*)((p)+(k)) → a sign-extended 16-bit load ✓.

So sum ∈ [-65536, 65534] and diff ∈ [-98302, 98302]. The (s16) cast is not value-preserving in general.

But GCC folded it (the asm has no sign-extension). So GCC 2.7.2 has a fold bug or a range analysis that concludes something wrong. Hmm.

Hmm, wait. Maybe GCC did NOT fold the cast but the *comparison* was folded differently: the code `if ((s16)diff < 0x10)` → GCC could generate a compare-and-branch on the truncated value: it would need the truncated value in a reg → `sll v0,v0,16; sra v0,v0,16` (2 instructions) → the asm would show them. It doesn't. So the cast WAS folded away.

Hmm! Unless GCC's fold turned `(s16)x < 16` into a *range check* on x: x < 16 AND x >= -32768 → that would be 2 comparisons. Not present.

So GCC folded (s16)x < 16 → x < 16. That's a GCC 2.7.2 bug (or it knew the range).

Hmm, hold on: maybe GCC's fold_convert: for the conversion (s16)x, GCC checks whether the *operand's mode range* fits: the operand x is an SI reg; but the *value* range tracked by GCC's fold (via the "value range" in the tree) — GCC 2.7.2 does have some range tracking for the tree expressions (fold_const_int). Hmm.

OK, regardless of the reason: the *compiled output* is byte-identical to the target. So the crack reproduces the target's code exactly. The C source has a truncating cast whose effect GCC eliminates — i.e. the C is "as if" the cast weren't there for this compiler. The decomp's correctness criterion (the compiled asm == the game's asm) holds.

Hmm, but is this a legitimate "crack"? The concern: the C's abstract semantics differ from the original decomp's C (a truncation that GCC happens to fold). If the *game's* original C had 16-bit arithmetic... hmm, the game's asm does a 32-bit subtraction and a 32-bit comparison, so the game's diff was 32-bit.

Hmm, hmm. So the C I'd write says "diff is truncated to 16 bits" — the compiled result is the same, but the C is a lie in the abstract.

Hmm, hmm. The task's rule: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had may stay, never added". The lever (the asm) is gone ✓, no new lever ✓. The catalog explicitly allows "s16/u8 widths" as a move. And the score is 0.

Hmm, but the *intent* of the rules is that the crack is a faithful plain-C rewrite. A truncating cast that the compiler folds is arguably a "fake" — but it's not an *asm* fake, it's a plain C statement whose effect this compiler eliminates.

Hmm. The project's "!FAKE:" convention marks statements that exist only to steer codegen. So I should mark it: `diff = (s16)diff;  // !FAKE: width — value-preserving after fold`? Hmm.

Hmm, wait. Let me check: is the cast really value-preserving *at runtime* in the compiled program? The compiled program does the 32-bit subtraction and the 32-bit comparison — identical to the target. So the *runtime behavior* is identical. The C's abstract semantics differ, but the compiled artifact (what matters for the game) is identical.

Given the project's rule that the deliverable is the compiled asm, and the "widths" move is explicitly in the catalog, I'll take it — but I'll note the caveat in notes.md and use a "!FAKE:" comment to be transparent. Hmm, hmm. Hmm, but a "!FAKE:" marker might make the reviewer think it's a lever. The "!FAKE:" prefix in this project marks "this is not in the original decomp" (i.e. a deliberate deviation). The do-while and the cast are both such deviations. I'll mark them.

Hmm, hmm. But hold on. Let me reconsider the (s16) cast for the *other* items where I used it:
- func_8017D73C: `n = (s16)n` — n ∈ {16,20} → genuinely value-preserving ✓ (no truncation possible).
- func_8017D9D8 / func_8017EF0C: `v0 = (s16)v0` — v0 = a sign-extended s16 → value-preserving ✓.
- func_8018656C: `diff = (s16)diff` — NOT value-preserving in the abstract (though GCC folds it).

For func_8018656C, let me look for a *value-preserving* alternative. Hmm: is there a width cast that IS value-preserving for diff? diff ∈ [-98302, 98302] — no 16-bit type covers it. Hmm, what about (s32)? A no-op (folded). Hmm, what about the *do-while* alone for func_8018656C? The combos: cb001_dow_arrNone etc. — let me check their score. From the log, the top 5 were all "dowcast"; the "dow" ones scored 6 (like the plain). So the do-while alone doesn't crack it; the cast is needed.

Hmm, what if the cast were applied to a *different* variable? E.g. `sum = (s16)sum;`? Hmm, sum is also out of s16 range.

Hmm. What about the *first* block's variables? The lever is in the second block only.

Hmm, what if instead of a cast I use a different "real 2nd set" for diff that is value-preserving? E.g. `diff = diff;`? (identity — forbidden and folded). Hmm, `diff = diff + 0;`? folded. `diff = 0 + diff;`? folded.

Hmm, what about `diff = diff | 0;`? folded.

Hmm, what about making the *else* branch's diff the cast one: in the else branch, `diff = sum - *(s16 *)(s1 + 0xA);` — a fresh value (also out of range).

Hmm. What if the cast is (u16)? `(u16)diff < 0x10` — the comparison is signed on a value in [0,65535] → different semantics (and the asm would be sltiu?). The combos show dowcastu16 also = 0. Hmm! Both s16 and u16 give score 0. With (u16), the value's range is [0,65535] and the comparison `diff < 0x10` (signed) → GCC would generate `slti` (since the value is non-negative) — hmm, and the truncation (u16)diff for a negative diff gives a large positive → the comparison differs. Also not faithful.

Hmm. So for func_8018656C, any width cast on diff is *not* value-preserving, but GCC folds it and the asm matches.

Hmm, hmm. Let me look for a *different* faithful move for func_8018656C.

The lever's effect: the asm blocked the fold "if (c) return 1; else return 0" → "return c". The do-while blocks that fold (score 6 vs 13). And the cast provides... hmm, what does the cast add on top of the do-while? Let me check the "dow" only score for func_8018656C: cb001_dow_arrNone = 6? The log's top-5 for func_8018656C were all "dowcast*" and "cast*" (0). Let me get the full list to see the "dow" score.

Let me also try: do-while + a *different* real 2nd set of diff that IS value-preserving. Hmm, what about a "real 2nd set" that recomputes diff from the same expression: `diff = *(s16 *)(s1 + 0xA) - sum;` (a real re-computation, value-preserving!). Hmm! That's a genuine second set with the same value — the moves.md "real 2nd set" move. cse might fold it (the same expression) → hmm, but it's a "real 2nd set" in the source.

Let me test: the do-while + `diff = *(s16 *)(s1 + 0xA) - sum;` (a re-computation). And the do-while alone.

Let me also test the do-while + `diff = sum - *(s16 *)(s1 + 0xA);`? no, that changes the value.

Let me write these variants for func_8018656C.

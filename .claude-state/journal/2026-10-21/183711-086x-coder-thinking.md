---
ts: 2026-10-22T00:37:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_UXjoXytQVhKKVbFpCFAF
---
Interesting: 1 asm → 28 (same as 0 asms!), 4 asms → 18. So the count matters, and 12 asms → 0 (the target).

So the number of asm refs to v drives the register allocation. The 12 asms add 12 refs to v.

Hmm, so this is a "keepalive"-style ref-count lever. In plain C, can I add refs to v legitimately?

A "real 2nd set" of v: e.g. `v = v;`? identity → forbidden and folded.

Hmm. What about making v a variable that is *used* more? Each use adds a ref.

What about: the value v is compared 4 times (4 refs). The 12 asms add 12 more. To get the same allocation, I'd need 12 more refs.

Hmm, what if v were compared more times? E.g. a longer chain — no, that changes the code.

What if v is *stored* somewhere? Changes the code.

Hmm. So the ref-count lever can't be reproduced with real C... unless a "real 2nd set" of v (a genuine second assignment) adds refs. E.g.:

```
v = *(s16 *)((u8 *)src + i * 8 + 2);
v = v;  /* no */
```

What about a genuine re-assignment with the same value: `v = *(s16 *)((u8 *)src + i * 8 + 2);` twice? That's 2 sets but cse folds it (the same expression) → 1 ref.

Hmm.

What if the load is *split*: `v = (s16)(*(u8 *)((u8*)src + i*8 + 2) | (*(u8 *)((u8*)src + i*8 + 3) << 8));` — that's a real 2nd set? No, that's a different expression that cse might fold to the same load... and it would generate different instructions (lbu, lbu, sll, or) — no.

OK, so item 4 = WALL. The mechanism: the 12 asms are a ref-count lever on v: each adds a REG_N_REFS, and the global allocator then rematerialises the loop-invariant comparison constants into the delay slots instead of hoisting them into t regs (0 asm → 6 hoisted, 1 → 6, 4 → fewer, 12 → 2).

Wall tag: new tag, e.g. `greg-refcount-consts`? Hmm. The pass: "global-alloc"/"reload". The walls.txt has `greg-pri-refs` (global-alloc: each keepalive = +1 ref...). Hmm, this is similar: the ref count changes the allocation. But the *outcome* here is the constant rematerialization.

Tag: `greg-refs-const-remat`? Let me use `global-alloc-const-remat`? The tag format is `<pass>-<what>`: pass = "global-alloc" (or "greg"). I'll use `greg-const-remat`.

Hmm, wait. Let me try one legit thing first: what if v is *declared* differently or the *chain* uses a *s16* type? Let me try the "width" move: `s16 v` instead of `s32 v`? The load is `*(s16 *)` → the value is sign-extended; the comparisons with -150 etc. would be on a sign-extended s16. The current code: `s32 v; v = *(s16 *)(...)` → the sign extension happens at the load. If v were s16, the comparison `v == -150` would compare the 16-bit value (no extension needed) → the instructions might change (the compare would be on the loaded halfword directly — `beq`?). Hmm, the target has `bne v1,t3` with v1 = the sign-extended value. So v is s32.

OK, item 4 = WALL. best 28, tries 4 (c1 0-asm, c2 switch, c3 1-asm, c6 4-asm).

Hmm, wait. Actually, hold on! Let me reconsider: what if I add refs to v *legitimately* by using it in a way that generates no code? Hmm.

What about `v` being used in the *store*? e.g. `idx[i] = (v == -150) ? 4 : ...` — no.

What about making the *loop* use v in the address computation? no.

Hmm, what about this: the 12 asms are the "keepalive" of the *value*. The plain-C equivalent: use v in a *dead* way 12 times? That's a launder.

OK, WALL. Let me record item 4 and move on. I'm at 20:45 now; 7 items left. I need to speed up: ~7 min per item → ~1 hour for the rest. Let me be efficient: for each item, generate the lever-free body (remove the asm lines) with a script, score it, and look at the residual. If the score is small, try 1-2 variants; otherwise record a WALL with the mechanism.

Let me write a generic helper script (under G14) that:
- reads the item dir, extracts the function from the TU (using extract.py logic),
- writes orig.c and c1.c (asm lines removed).

Then a batch command scores all remaining items' c1 at once. That gives me the landscape quickly.

Let me write gen.py.

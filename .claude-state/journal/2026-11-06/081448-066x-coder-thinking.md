---
ts: 2026-11-06T15:14:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6IDCbaHQ4oQgp9qcn5e0
---
g1: `bne s1,v1,71c` vs target `bne s0,v1,71c`. So the compare is on a1 (s1) instead of t (s0). Everything else matches.

So I need `t != 3` but on the value in s0 (t's register), while preventing the fold. Hmm.

What if I write `if ((s32)t != 3)`? That's the same as t != 3 → folds.

What if `t` is compared but through a value that cse can't equate to 5 while still being in s0? The register s0 holds t. The compare must use s0.

Idea: make the test compare `t` against a *variable* holding 3 rather than a constant. The target has `li v1,3` before the first `beq s0,v1` — the constant 3 is materialized in v1 because it's used twice (beq at 6f4 and bne at 704). If the second compare used a variable equal to 3, cse would know its value 3 → still fold t!=3? cse knows t==5 (jump equivalence) and c==3 → folds.

Unless the variable c is not known to be 3. E.g. `s32 c = (s16)3;` → known.

Hmm. So we need cse to lose the jump equivalence t==5.

What invalidates it? A set of t. So: a set of t that is value-preserving and cheap. What about `t = t;`? Let me test: `t = t;` before the test. gcc might eliminate it in the front end (gimplification has no gimple in 2.7.2; it's tree → RTL directly). A self-assignment `t = t` in C at -O2: the tree optimizer might drop it. But maybe not in 2.7.2 (which has limited tree optimizations). Let me test.

If `t = t;` survives to RTL, it becomes a set of t to t (a copy) — cse would make it a no-op? cse would see (set t t) and probably delete it. Hmm.

What about `t = t + 0;`? The tree/fold would simplify to t.

What about `t = t | 0;`? simplify to t.

What about `t = t & -1;`? simplify.

What about `t = (s16)(t & 0xFFF) + 0;`? For t=5 → 5. But the compiler knows t=5 so folds.

Hmm — the compiler knows t=5 from the jump equivalence; ANY expression of t will fold to 5 if it's const-foldable. Unless the expression isn't const-foldable but is value-preserving for t=5. E.g., `t = (t * 2) / 2;`? For t=5 → 5, but the compiler might fold to t. Hmm, `t = (t << 1) >> 1` → folds.

What about a *function-like* opaque operation: `t = t ^ (t ^ t);`? folds.

Hmm.

What about a division: `t = (t / 1);` folds.

What about `t = t % 16;` for t=5 → 5; the compiler knows t=5 → folds.

Everything folds when the value is known.

So the only route: prevent the jump equivalence from being recorded/used. cse records jump equivalences at the conditional jump: `record_jump_cond`. It records that on the fall-through, t == 5. Then any use of t in the same EBB folds. If a LABEL intervenes, cse ends the EBB (cse_basic_block ends at labels). g2/g3/g4 (do-while) scored 4 — meaning no split happened (the label was removed before cse).

But wait — g1 worked by comparing a1 instead. What if we make the compare use t's *register* but an expression cse can't fold: the trick from moves line 134 — "a hard-reg addend combine cannot fold". Hmm.

What if we compare t against 3 where 3 is in a hard register? e.g., the pinned a0/a1? Not 3.

Hmm, what about comparing t against `(s32)(s16)(a1 - a1 + 3)`? folds.

OK here's another idea: use `t` in a context where cse's equivalence was invalidated by a *store*. cse's record_jump_cond equivalence is invalidated by any set of t, or by a call? Calls invalidate memory but not t. Hmm.

What if we make `t` also live in memory (address taken)? Then a store could invalidate... changes codegen.

Alternative: make the t==5 test not produce a jump equivalence on t. cse records the equivalence only for a *conditional jump* comparing a register with a constant. If the test is `if ((t & 0xFF) == 5)` — then the equivalence recorded is on the *expression* (and t & 0xFF), not directly t? cse's record_jump_cond records an equivalence between the two sides of the compare; if one side is a compound expression, it records that expression == const. Then `t != 3` (plain t) wouldn't fold from that! But the compiler also knows t = (s16)a1 and t&0xFF==5 → t could be 5 or 0x105 etc. So t is NOT known → `t != 3` doesn't fold. 

But then the t==5 test would emit an `andi` + compare — extra instruction. Unless... hmm.

Wait, actually: what does the target's `bne s0,v0,740` compare? s0 = t directly against v0=5. If we write `(t & 0xFF) == 5`, gcc emits `andi` + compare → extra insn. Not matching.

What about `(u16)t == 5`? t is s16; (u16)t == 5 is equivalent to t == 5 for t in s16 range (since 5 is positive). gcc might emit an andi or nothing. If it emits the compare directly (because t is already sign-extended and the comparison can use the same register?), then the jump equivalence recorded is on `(u16)t` not t. Then `t != 3` might not fold! Let's test.

Similarly `(u32)t == 5`? For t = 5 → 5. gcc may fold or emit a compare of t directly.

Let me test h1: `if ((u16)t == 5)`.
h2: `if ((s32)t == 5)` (same as t==5).
h3: `if ((u32)(s16)t == 5)`.
h4: `if ((t & 0xFFFF) == 5)`.
h5: `if (t == (s16)5)`.

Also, what about making the *first* test (`if (t == 3) goto sel_054;`) the one that folds and the second compare on t — no.

Let me test these.

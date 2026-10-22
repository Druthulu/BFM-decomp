---
ts: 2026-10-22T07:47:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bVtOzZ0FVL8eYbhuB5xL
---
Still 4. Time: ~01:55. I've spent ~25 min on item 7 (16 tries).

Let me think about the re-basing more concretely. gcc's ivcanon: the transformation "ivcanon_iv_init" changes the IV's initial value when the IV is used in a "constant offset" way. Specifically, gcc's loop.c has:

```
/* If we have an IV that is only used in constant offsets from the init,
   we can change the init value.  */
```
Hmm, actually I recall `ivcanon` in gcc 2.7's loop.c:
```
static int
ivcanon_iv_init (struct loop *loop, struct iv_info *iv_info)
{
  ...
  /* If we have a non-negative offset, and the IV is only used with
     constant offsets, we can change the init. */
```
Hmm.

Alternatively, the re-basing might be done by cse's "find_best_addr" or by "combine".

Hmm, let me look at it from the RTL side: dump the tree and cand01 and compare the loop's RTL (the .loop dump shows the loop's IV analysis).

Time cost: the TU is src/ov_SC07_001/ov_SC07_001_jr_8017BEBC.c (how big?). Let me check and dump. Actually, maybe a cheaper diagnostic: use the .loop dump for cand01 only (trimmed TU) and look at the IV info.

Hmm. Alternatively, let me think about what the launder's asm does in the RTL once more:
`(set q_pseudo, q_pseudo)` — a self-copy INSIDE the loop body.

In gcc's loop.c, the IV analysis (find_simple_iv) requires the IV's increment to be the ONLY definition in the loop body. With the extra self-copy, `find_simple_iv` FAILS → q is not recognized as a simple IV → then the "ivcanon" re-basing doesn't happen ✓ and the loop keeps q as a plain variable with an increment.

But wait: the target's code DOES have q as an IV-ish (addiu s0,s0,8) — that's just the increment, no strength reduction needed.

And in mine, q IS recognized as a simple IV → and then ivcanon changes the init (base → base+2).

Hmm! So the lever-free equivalent: make the IV analysis fail. In plain C, that means q must have 2 definitions in the loop body.

Hmm, how about this: what if the loop body's q update is spelled as a compound assign on a DIFFERENT variable and q is assigned from it?

```
        q2 += 4;      /* q2 is another pointer */
        q = q2;
```
Hmm, then q has 1 set in the body (the copy) and q2 has 1 set — but the copy `q = q2` is a copy of the same value → gcc's copy propagation would make q ≡ q2 → 1 set each ✗.

Hmm.

What if the loop is spelled so that the q update happens in a way that creates 2 sets:
```
        q = (s16 *)((u8 *)q + 8);
```
1 set.

Hmm, what if we do:
```
        q += 4;
        q = q;    /* removed */
```

Hmm.

**KEY IDEA**: what if we give q a 2nd set via a compound assign that PRESERVES the pointer but isn't folded — e.g. `q -= 0;`? Hmm, for a pointer `p -= 0` → gcc folds to p ✓ probably.

What about `q = q - 0;`? folded.

What about `q = (s16 *)((u8 *)q + 0);`? folded.

Hmm, what about a **union**-based trick:
```
union { s16 *p; u32 u; } qq;
qq.p = q;
q = (s16 *)qq.u;    /* a real 2nd set (an integer round-trip) */
```
The value is preserved (a pointer round-trip through a u32 — on a 32-bit target, the pointer fits in 32 bits ✓ but gcc's type-punning might warn). Hmm, and gcc would fold the union round-trip? Hmm, gcc's alias analysis might handle it: `qq.p = q; qq.u` → gcc knows qq.u == qq.p (same memory) → folds → 1 set.

Hmm.

**IDEA: use a `char *` alias to make the copy opaque?** no.

OK, let me flip the approach: instead of making q's IV analysis fail, maybe I can PREVENT the re-basing by changing the store offsets so that the re-based version isn't "better".

The re-basing chose +2 (so the smallest offset is 0). gcc's ivcanon_iv_init: it changes the init if "the IV's uses are all at constant offsets" and it picks the init such that... hmm, maybe it always tries to make the offsets non-negative and minimal.

Hmm! What if the stores were spelled so that the offsets are 6, 4, 2 AND there's another use of q at a different offset? Hmm.

Hmm, what if `q[0]` were also stored (an extra store)? That changes the code ✗.

Hmm, what if the 4th store used `q[0]` explicitly? Then the 4th store's address = q + off... hmm, no: the 4th store is (D_801AAD6C + off) which equals q[0] in the first iteration but q advances by 8 while off advances by 8 ✓ so the 4th store's address == q[0] ALWAYS! (q = base + 8*i, off = 8*i → base+off = base+8*i = q ✓).

So semantically the 4th store IS q[0] = 0. The target computes it separately (lui/addu) and mine unifies it with q.

So: if I write the 4th store as `q[0] = 0;`, gcc would use q → mine's behavior ✗ (that's what happens now).

To force the separate computation, the address must not be q. Hmm.

**IDEA**: what if `off` is NOT 8*i but something else that's equivalent? E.g. `off` could be the byte offset of q from the base: `off = (u8 *)q - (u8 *)D_801AAD6C`? That changes the code ✗.

Hmm.

**IDEA**: What if the q pointer is advanced by a different amount so that q != base+off? E.g., if the C advanced q by 8 but off by 8 — they're equal. What if the C advanced q by 8 and used a separate counter for the 4th store's address? That's what it does.

Hmm, so the two IVs are "parallel" and gcc's ivcanon merges their relationship.

**IDEA**: use two DIFFERENT base expressions for q and the 4th store: e.g. q = (s16 *)D_801AAD6C and the 4th store uses (s16 *)D_801AAD6C — the same symbol ✓ (that's the point).

Hmm, what if the 4th store's base is a DIFFERENT symbol alias of the same address? The TU has `extern s16 D_801AAD6C[];`. An alias (e.g. `extern s16 D_801AAD6C_alias[] __asm__("D_801AAD6C");`) would be a different symbol_ref but the same address ✓! Then cse couldn't unify (different symbol refs) → the 4th store would keep its own address computation ✓✓.

Hmm! But: adding a new extern declaration with an asm alias — is that "adding a lever"? It's a symbol-name alias (like the worked example's `aB9A02 __asm__("D_800B9A02")` which the notes explicitly allowed: "Kept the TU-idiom extern asm-label alias ... (symbol name, not a codegen lever; was in orig body)"). But here it would be NEW (not in the orig body) ✗ — the brief says "no signature or decl change outside the body". Adding a decl inside the body is allowed? The body's decls are inside the function ✓. Hmm, but it's adding an alias — the constraint says "no new lever of any kind" — an asm alias for a symbol name is not a codegen lever (it doesn't steer codegen; it just names the same address). Hmm, but it IS an `__asm__` — the constraint says "no `register` vars, no `__asm__`"! Hmm, that's about the body's levers. An extern symbol alias uses __asm__ ✗ risky.

Hmm. But hold on: does the alias even work? gcc would treat D_801AAD6C_alias as a different symbol with a different address... no: `__asm__("D_801AAD6C")` makes it the SAME symbol ✓. Then cse would see the same symbol_ref? No — the asm alias makes the RTL symbol_ref be "D_801AAD6C" (the same!) → cse would unify them again ✗.

Hmm, right: the alias renames the symbol in the RTL → the same symbol_ref → unified.

OK. So I need a genuine non-unifiable expression.

**IDEA**: what if the 4th store's address is computed from a different but equivalent expression, e.g. `*(s16 *)((s32)D_801AAD6C + off)` vs `*(s16 *)((s32)D_801AAD6C + 8 * i)`? The latter is equivalent (off = 8*i) but computed from i (a different IV) → the value is the same but the expression differs → hmm, but then gcc would compute 8*i (a shift) → extra instructions ✗.

Hmm, unless gcc's IV analysis recognizes off == 8*i and rewrites it back ✓ (then it's the same as before).

Hmm.

OK, let me try the empirical route on the re-basing: maybe the re-basing is caused by the q[1] store specifically. What if the stores are spelled with an explicit `q[1]` vs `*(s16*)(q+2)`? Tried (cand07) → score 4.

Hmm, let me look at the loop dump to understand. Let me do a quick dump of cand01's trimmed TU and look at the loop's IV info. Hmm, time.

ALTERNATIVE: maybe I should reconsider what the launder does in this function. Let me look at the tree's RTL for the loop. Let me do the dump — it's the fastest way to certainty.

Let me create the trimmed TU for the tree's function and dump it, then look at the .loop dump's IV analysis.

The function is 55 lines; the TU is big but the dump is per-file. Let me check the TU size first: src/ov_SC07_001/ov_SC07_001_jr_8017BEBC.c.

Actually, since the function needs the file-scope decls (D_801AAD6C etc.), a trimmed TU with just the function + headers should work (the decls are inside the function or in the headers).

Let me doit.

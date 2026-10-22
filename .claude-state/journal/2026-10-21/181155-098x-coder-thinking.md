---
ts: 2026-10-22T00:11:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_pmwvEhEH1Gr7XCWtcWMS
---
R5 swaps the operands of a top-level commutative operator in a source line! So for our line:

`D_801270C8 = *(s16 *)((u8 *)p + off + 4);`

the top-level commutative operator is the `+` — hmm, there are TWO `+` at the top level of the RHS expression: `(u8 *)p + off + 4`. Hmm, `top_level_ops(expr)` — the expr = `*(s16 *)((u8 *)p + off + 4)` — the top-level ops of that: the `+`s are inside the parens of the cast/deref, so the top level has no operator! Hmm. Hmm, `*(s16 *)((u8 *)p + off + 4)` — the top-level is a deref; the `+`s are inside the parens. So R5 wouldn't fire on this line.

Hmm! But the R5 note says: "a CONSTANT operand is moved to the right by fold before expansion ... the swap of a constant is a candidate that can never change the object, so it is not generated" — so R5 only swaps var/var.

So for our case, the swap must be applied to a line whose top-level operator is the `+` of (p, off). E.g. if the C were:
```
                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
                D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
the R5 swap would need the `+` at the top level of the assignment RHS.

So to apply R5 manually, I'd write the line as:
```
                D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
hmm, the top-level expr is `*(s16 *)(...)` — no top-level op.

Hmm! But the SWAP I need is exactly of (p, off) → (off, p)?? NO — wait. The target has (p, index) and mine has (index, p). Hmm! So the target = the natural C order (p first). And R5 swaps to get... hmm, R5 would swap (p, off) → (off, p) which is MINE's order ✗.

Hmm!! So R5's swap is the WRONG direction here?

Hmm, hold on. Let me re-examine. The R5 doc: "S99 read `and v0,v1,v0` against the target's `and v0,v0,v1`" — so the SWAPPED source produces the target. Hmm, in that case the source's `x & y` (v1,v0) → the target's `v0,v1` — hmm, the target has the FIRST source = the destination.

In our case: the target's `addu v0,a1,v0` = (a1, v0) — the first source is a1 (p) and the second is v0 (the index = the destination). Hmm! So the target's operand order is (p, index) with the destination last.

And the R5 example: the target's `and v0,v0,v1` = (v0, v1) with the destination FIRST. Hmm.

So in the target here, the destination (v0) is the SECOND source. In mine, the destination is the FIRST source.

Hmm! So it's not a "swap" of the source operands per se; it's that in the target the destination is the second source. Hmm, but the RTL's operand order and the destination are related: gcc's `(set d (plus a b))` — the destination d and the tree (plus a b). In the target: d = v0, the tree = (plus a1 v0) — the tree's first operand is a1 = p, second = v0.

In mine: d = v0, the tree = (plus v0 a1).

So the TREES differ in order: (plus p index) vs (plus index p). And the source's natural order is (plus p off) — p first — which matches the TARGET.

So my source's natural order should give the target's tree, but gcc flips it. And R5's swap (off + p) would give the source order (index first) which is what gcc produces anyway.

Hmm! So maybe R5's swap (writing `off + (u8 *)p` — hmm, that's not valid C for int+ptr)...

Hmm, hold on. Hmm, R5's swap on the line `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` — the top_level_ops of the RHS: the expr is `*(s16 *)((u8 *)p + off + 4)`. Hmm, sc.mask_text would mask the string/char literals. The top-level ops: the `*` of the deref? Hmm, `*(s16 *)(...)` — the `*` is a unary deref, and top_level_ops probably only counts binary ops. So no top-level op → R5 doesn't fire.

Hmm. So R5 wouldn't apply to our line. But the DELIVER_SEARCH's residual class is "REG-caller" and the families for REG-caller include R5 — and the R5 candidates would come from other lines.

Hmm, so how do I get the swap? Since the natural C order is (p, off) and gcc flips it, and R5's swap would give the source order (off, p) = the same as gcc's flip → the same output.

Hmm! Unless R5's swap makes gcc's flip produce (p, off)!! I.e., if the source is (off, p) and gcc flips it to (p, off) ✓ = the target!

Hmm!! That's plausible: gcc's canonicalization might always put the "cheaper" operand in a fixed position, so flipping the source flips the output.

So: write the address as `off + (u8 *)p`?? Invalid C (int + pointer). Hmm. But in GNU C, `int + pointer` is an ERROR.

Hmm! But what about `((u8 *)p + off)` — hmm.

Hmm, what if the sum is written as an integer addition with the index first:
`D_801270C8 = *(s16 *)((u8 *)((u32)off + (u32)p) + 4);` — hmm, I tried `(u32)p + (u32)off` (p first). Let me try the REVERSE: `(u32)off + (u32)p` (index first)!

That's v9's inverse. Let me try it! The tree = (plus off p) → gcc might flip it to (plus p off) ✓ = the target!

Let me test that (v10).

Also worth trying: `*(s16 *)((u8 *)((u32)off + (u32)p) + 4)`.

Let me do it.

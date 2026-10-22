---
ts: 2026-10-22T00:12:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Fuhm9v2w7l63YrBFHKUe
---
Same. OK, let me try the R5 approach literally: the R5 rule swaps the operands of a top-level commutative operator in an assignment's RHS. For our line, the RHS is `*(s16 *)((u8 *)p + off + 4)` — the top-level has no binary op. BUT if I RESTRUCTURE the line so that the add IS at the top level of an assignment, R5 could apply!

E.g.:
```
                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
                qa = (u8 *)p + off;          /* the top-level + : swap → (u8 *)p + off ↔ off + (u8 *)p */
                D_801270C8 = *(s16 *)(qa + 4);
```
Hmm, `off + (u8 *)p` is invalid C (int + pointer). Hmm.

Hmm, but R5's swap produces invalid C sometimes? The rule says the candidates that can't compile are "wasted but not noisy". So R5 would produce `off + (u8 *)p` which doesn't compile.

Hmm! So the R5 swap of (p, off) is invalid C. Hmm, so how does the R-family flip a pointer+int add?

Hmm, unless the operands are both integers. Hmm! What if the address were computed as an integer: `qa = (u32)p + off;` — then R5's swap gives `off + (u32)p` (valid C!) ✓✓✓. And the tree = (plus off p) → and gcc's canonicalization might flip it to (plus p off) ✓ = the TARGET!

I tried v9 = `(u32)p + (u32)off` (p first) and v10 = `(u32)off + (u32)p` (off first) — BOTH gave the same output (index first)!! Hmm. Hmm, v10 was `((u32)off + (u32)p)` — the index first — and the output was still `addu v0,v0,a1` (the index first). So the index-first source gives the index-first output → gcc does NOT flip. And the p-first source ALSO gives the index-first output → gcc DOES flip.

So gcc's canonicalization puts the INDEX first in both cases?! Then how did the launder version get (p, index)?

Hmm!! So the launder version is NOT the result of a source-order change; it's the result of p being a HARD REG.

Hmm. So: p hard reg → (plus hardreg index); p pseudo → (plus index pseudo). Hmm, that's a weird rule, but it suggests: gcc's canonicalization puts the operand that is a PSEUDO... hmm, both are pseudos at combine time (the index is a pseudo too).

Hmm, hmm. Unless the index is NOT a pseudo but a hard reg at that point? no.

OK, let me try to think about it via combine's `convert_add`:

In combine.c's convert_add, there's a step:
```c
      /* If we have a plus of a reg and a constant, ... */
      ...
	  /* Try to simplify the operands in the other order */
```
Specifically, combine's `simplify_operand` is called on x and y, and combine tries:
```c
	  /* If we have x + y, and we know that x is a reg and y is a reg, ... */
```
Hmm.

There's a known combine behavior: "we prefer to have the operand that is a pseudo in the first position" hmm.

OK. Since both p and the index are pseudos at combine time, the difference must be in the ORDER: p is a pseudo whose value is a symbol_ref (a CONST pseudo) and the index is a pseudo whose value is a MULT.

Hmm! combine's `simplify_operand` on the p pseudo: it would try to simplify it → p's reg_equiv is (symbol_ref) → the simplification might yield the symbol_ref itself → then the tree = (plus symbol_ref index) → and the materialization would be at the add ✗ (the materialization is early in mine ✓). Hmm, so no.

OK, I need to stop. This item: score 1, WALL with best=1.

Hmm, but hold on! Let me try one thing: what if p's value is used in a context that makes it a hard reg — e.g., what if p is ALSO passed to a call? Hmm, there's no call in the block. But the function has calls: func_8012AD80, func_80187508, func_8018ABE0, func_8018AEB4, func_801849E4, func_8013C9C4, func_8012B2CC. Hmm! p is used only in that block.

Hmm, what if p's address is taken? no.

Hmm, what about making p a `static`? no.

Hmm, what if the address is computed as `D_80195AF6` (the symbol) in the add and the p variable is used for something else? Hmm, p is only used there.

Hmm, hmm. What if p is declared as a pointer to a const/global? no.

OK — let me try the LAST idea: what if the `+ 4` is added to p BEFORE the index: `((u8 *)p + 4) + off`? The tree = (plus (plus p 4) off) → simplify_plus would flatten to (plus p off 4) hmm, and the constant last. Hmm.

Or: `((u8 *)p + off + 4)` vs `((u8 *)p + (off + 4))` — the latter: the tree = (plus p (plus off 4)) → hmm, the load's offset would be 0 ✗ (the target has lh v0,4(v0)).

Hmm, wait: would it? (plus p (plus off 4)) — reload would split the 4 only if it's a top-level constant. (plus off 4) is not a constant → the MEM's address = p + off + 4 → the load would be `lh v0,0(v0)` with an extra add ✗.

Hmm.

OK, let me now also consider: maybe I should try the OTHER launder-free spelling where p is used via a cast that makes the tree different:
`D_801270C8 = *(s16 *)((u8 *)p + off + 4);` — current.

Hmm, what about `D_801270C8 = *((s16 *)((u8 *)p + off) + 2);`? The tree: (plus (plus p off) 2) then the MEM's offset = 4 (2*2) — hmm, the +2 on an s16* scales to 4 ✓ → the MEM's offset = 4 ✓ (reload splits it). The tree = (plus p off) hmm, the same.

Let me try it anyway — cheap.

Hmm, no. Let me wrap up: I'll record 80184828 as a WALL with best=1, and move to the last item (8017D81C), then do the bookkeeping. Time is very tight.

Actually, hmm, wait. Let me reconsider the whole thing: maybe the launder's effect isn't the operand order per se, but the fact that the launder asm is INSIDE the if-block. Let me test: keep the launder removed but move the p assignment inside the if-block:

```
            D_80195AF6_t *p = D_80195AF6;
            s16 newval = D_80195AF6[...].f0;
            if (newval >= ...) {
                s1 = 1;
                ...
```
vs moving `D_80195AF6_t *p = D_80195AF6;` INSIDE the if-block:
```
            s16 newval = D_80195AF6[...].f0;
            if (newval >= ...) {
                D_80195AF6_t *p = D_80195AF6;
                s1 = 1;
                ...
```
Then p's materialization would be LATE (inside the block) ✗ (the target has it at 69-70, before the newval load at 71-73). Hmm, but the sched could hoist it... hmm, unlikely.

OK. Let me do the last item and then the bookkeeping. Let me look at func_8017D81C.

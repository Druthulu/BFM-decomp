---
ts: 2026-10-22T00:19:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ZZ0HYHaMLJJ44S46jjiw
---
For 80181E64 n1: the diff is now:
- mine[13] = `nop` vs target[13] = `li v1,1` (the `li v1,1` is scheduled differently — the do-while introduced a nop!)
- mine[15] = `andi s8,v0,0xfff` vs target[15:17] = `andi v0,v0,0xfff; move s8,v0`.

So the copy STILL got merged (the mask computed directly into s8). Hmm! And the do-while added a `nop` (the loop's branch).

Hmm. So the do-while didn't preserve the copy. Hmm, but it changed the code (nop, li v1,1 placement) → score 4.

Hmm, the `nop` comes from the do-while(0)'s branch. Hmm, gcc 2.7's do-while(0) → `goto` → a nop in the delay slot.

Hmm. So the do-while doesn't help the copy.

Let me think about the combine propagation again. Combine's copy propagation: in gcc 2.7's combine.c, there's a rule in the "simplify" phase:

```c
	  /* If this is a copy, propagate the source into the destination's uses... */
```
Hmm, actually I recall gcc 2.7's combine has:
```c
	    /* X = Y, and Y is not modified before the next use of X: replace X with Y */
```
Hmm.

Alternatively, the merge might happen in the CSE pass.

Hmm. Let me think about what the ORIGINAL compiler did: it kept the copy.

Hmm, hmm. Let me think about "the value is computed in a temp because the expression is not the whole RHS".

**IDEA**: What if the RHS of `t = ...` is a compound expression that gcc computes into a temp and then copies? E.g. if the RHS is `(a, b)` (a comma) or a conditional?

Hmm, what if the source is:
```c
v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
t = v;
```
and gcc merged them.

What if:
```c
t = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
```
→ also merged (computed directly into t).

Hmm, what if the value's computation involves a CALL? Then the result is in v0 and the copy to t would be needed:
```c
v = some_call();
t = v;
```
→ `jal` then `move s8,v0` ✓!!

But our expression isn't a call. Hmm, BUT: what if we make the expression's value come out of a call... no.

Hmm, hold on! What about this: the target's `move s8,v0` copies from v0 — a caller-saved reg. In gcc, when the RHS of an assignment is computed and the destination is a callee-saved reg, gcc computes the RHS into a temp (v0) and copies. Hmm! Does it? In mine, gcc computed the ANDI directly into s8.

Hmm, when would gcc compute the RHS into a temp and then copy? When the RHS is a "non-simple" expression... Actually gcc's expand for `t = expr`:
- expand_expr(expr) → the value ends up in a temp pseudo (or directly in the destination if the expression is a simple register).
- Then `set t (reg temp)`.
Hmm! So `t = expr` SHOULD produce: compute expr into a temp, then copy to t. But gcc's "expand_expr" has an optimization: if the destination is a pseudo and the expression is simple, it can compute directly into it ("expand_expr into").

In mine, the `andi` was computed directly into s8 — that means the ANDI's destination was t's pseudo. Hmm, that happens when gcc's expand decides to expand the expression INTO the destination pseudo.

Hmm, in gcc 2.7's expand_expr, for a binary operation, the result goes to a NEW pseudo (gen_reg_rtx), and then `set dst (reg result)`. But combine then propagates the copy dst = result → the result pseudo is merged with dst ✓. That's the merge!

So the merge is combine's copy propagation. To prevent it: the copy must be in a different basic block than the uses... hmm, no: combine works within a basic block, and the propagation happens at the definition.

Hmm, combine's copy propagation in gcc 2.7 (combine.c):
```c
	  /* If this is a copy (set (reg) (reg)), and the source is not
	     modified before its uses, propagate. */
```
Hmm, combine.c's actual rule (in the `simplify` part):
```c
	    case REG:
	      ...
```
Hmm, combine has a specific optimization: "if we are copying a register to another and the source is not used later, just use the source" — that's the reverse direction: `(set dst (reg src))` where src is dead after → replace dst's uses with src. Hmm, that's the "combine_copy" / "copy propagation" in combine.

Hmm! But in our case the source (the temp holding the ANDI result) IS dead after the copy (it's used only by the copy). So combine would propagate: dst(t) = src(temp) → t's uses become the temp's uses → the temp's live range extends → and then the temp and t are the same → the ANDI computes into t's reg.

Hmm, so combine propagates when the source dies at the copy. Ugh, that's the opposite of what I hoped.

Hmm, so how does the TARGET keep them separate? The original compiler isn't gcc.

Hmm, so with gcc 2.7.2, `t = expr` will always end up with the expression computed directly into t. UNLESS the source temp is used elsewhere too (so it's not dead at the copy).

⇒ So: the temp must be used somewhere else! In the target, the temp (v0) IS used elsewhere? Let's see: the target's `andi v0,v0,0xfff` then `move s8,v0` — v0 is dead after the move. Hmm, so the source is dead at the copy in the target too.

Hmm, but the target is from the original compiler.

⇒ For gcc 2.7.2, we need the source to be live beyond the copy. The only way: use `v` again later.

Hmm, can we use `v` later legitimately? The value v = the masked byte. Hmm.

**IDEA**: What if the masked value is stored to memory via `v` and `t` is a copy?
```c
v = (... ) & 0xFFF;
*(s16 *)(arg1 + 0x100) = v;
t = v;
```
Then v is used by the store (after the copy? no, before). Hmm, the ORDER: the store comes before the copy → the source is live at the copy → combine can't propagate the copy into... hmm, combine propagates the copy dst=t, src=v if v is not modified between the copy and t's uses. The store's use of v is BEFORE the copy, so it doesn't block the propagation.

Hmm! Unless the use of v is AFTER the copy:
```c
v = (... ) & 0xFFF;
t = v;
*(s16 *)(arg1 + 0x100) = v;    /* uses v AFTER the copy */
```
Then v is live after the copy → combine can't propagate t→v (because v is used later and the values would diverge? hmm, actually v is not modified, so propagating t→v is still valid... but combine's rule is per-block and it would see the use of v after the copy).

Hmm, combine's copy propagation: `(set t (reg v))` — it propagates by replacing the later uses of t with v, IF v is not modified between the copy and the use. Since v isn't modified, it WOULD propagate. Hmm. But then the store would use... hmm, t's uses become v's uses → the store `sh v,256(a1)` uses v0 ✗ (the target has `sh s8`).

Hmm, but combine might do it the other way: replace the uses of v with t? Hmm.

Hmm! Actually, hold on: combine's copy propagation is: if `dst = src` and dst is a pseudo with a single set and src is not modified between the copy and dst's uses, then dst's uses are replaced by src. That's what happens.

To block it, `v` must be MODIFIED between the copy and t's uses. Hmm, that's the dead-store trick.

Hmm, hmm. OR: **the copy's destination `t` must be modified before its uses** — i.e., t has multiple sets. Then the copy `t = v` is not the value of t at the use → no propagation ✓✓✓.

In our function: `t` IS modified later (`t += 0x600` in the loop)! Hmm! So t has multiple sets → the copy `t = v` is not the value at t's later uses (which are `t += 0x600` → t = t + 0x600, which reads t's value at that point!).

Hmm! `t += 0x600` reads t → so the copy IS needed (t's value at the loop = the copied value). Hmm, but the loop is a separate basic block, and the first iteration reads t.

Hmm! So combine's copy propagation: the copy `t = v` is in the entry block; t's uses are in the loop block (the `t += 0x600` and `func_8004787C(t)`). Since t is modified in the loop (`t += 0x600`), the value from the copy is needed at the loop entry.

Hmm, so why did combine merge them?

Hmm, because the propagation goes the other way: combine replaced the uses of v (in the copy) with t? I.e., `t = v` → `t = t`?? That would be wrong.

Hmm, hmm. Let me look at what mine actually produced: `andi s8,v0,0xfff` then `sh s8,256(a1)`. So the mask was computed into s8 and the copy vanished. So the temp (holding the ANDI result) was replaced by t.

So combine's "propagate dst's uses to src" happened: dst=t, src=temp(the ANDI result). t's uses (the store, the loop) became the temp's uses → the temp is live across the loop → hmm, but then the temp would need a callee-saved reg...

Hmm, hmm. OR combine did the opposite: since the temp is dead after the copy, combine replaced the COPY's source with the destination: `t = temp` → `t = t`?? no.

Hmm, whatever the mechanism: the temp and t merged.

⇒ The lever: make the temp live beyond the copy. In our case the temp is `v` (the masked value). Hmm, but the ANDI's result temp is what matters.

Hmm! If the source expression's temp is used elsewhere...

**IDEA**: What if the masked value is computed into a variable that is used LATER (in the loop)? Hmm, semantically the loop uses `t` (which grows). But what if we use `v` in the loop instead of `t` for the FIRST iteration? no.

Hmm, hmm. Hmm! What about this: the source could be written so that the masked value is used in TWO places: the store AND the copy:
```c
v = (... ) & 0xFFF;
t = v;
*(s16 *)(arg1 + 0x100) = t;
```
Hmm, v is used only by the copy.

What if:
```c
v = (... ) & 0xFFF;
*(s16 *)(arg1 + 0x100) = v;   /* v used here */
t = v;                        /* then copied */
```
Then the source (v) is used at the store (before the copy) and at the copy. The copy's dst=t: t's uses are later. combine: can it propagate t→v? It would require v to be live until t's uses — v is not modified, so it's valid → t's uses become v's uses → v0 would be used in the loop ✗ (v0 is caller-saved and the loop has calls!). Hmm, but gcc knows that: v can't be in v0 across calls. So gcc would NOT propagate (the value must be in a callee-saved reg) → the copy survives ✓!!

Hmm!! Interesting: in mine, the propagation happened because the temp could be merged with t (both callee-saved).

Hmm, so: if the source temp is used later such that it must live across calls, gcc can't merge it with t (different register classes) → the copy survives ✓.

But that requires using `v` in the loop — changing the semantics ✗. Hmm.

Hmm, but the STORE: `*(s16 *)(arg1 + 0x100) = v;` — the store is before the call ✓ so v doesn't cross a call.

Hmm, and then the copy `t = v` — t is callee-saved. If v's only use is the copy, v dies at the copy.

Hmm, hmm. What if the ORDER is: `t = v;` FIRST, then the store uses v?
```c
v = (... ) & 0xFFF;
t = v;
*(s16 *)(arg1 + 0x100) = v;
```
Then: the copy `move s8,v0` then `sh v0,256(a1)` — the target has `sh s8,256(a1)` ✗ (different reg).

Hmm, but hold on: maybe gcc's cse/combine would propagate t→v for the store's use... no, the store uses v directly.

Hmm. The target: `move s8,v0` then `sh s8,256(a1)`. So the store uses s8 (t) ✓.

OK so we need: the temp (v0) computed, copied to s8, and the store uses s8.

The copy must survive. The copy's source (v0/temp) dies at the copy. Combine merges them.

⇒ To keep them separate, the temp must be live after the copy. The only user after the copy is the store (which uses t) and the loop.

Hmm! What if the source is:
```c
v = (... ) & 0xFFF;
t = v;
*(s16 *)(arg1 + 0x100) = t;
```
Hmm, the temp is v (or the ANDI result temp). Its uses: the copy. Dead after.

⇒ combine merges.

Hmm, unless the ANDI result temp is used elsewhere...

Hmm, what if the masked value is computed with a temp that's ALSO used for something else? E.g.:
```c
v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
```
The ANDI's operands: the load temp and 0xFFF. The load temp (the lhu result) is used only by the addiu. Hmm.

Hmm, so the chain is: lhu → addiu → andi → copy → t. Each temp dies at its use. gcc merges them all into t.

⇒ In gcc 2.7.2, the whole chain collapses into t's register. The target has the chain computed in v0 and one copy.

⇒ This is a fundamental difference: the ORIGINAL compiler computed the chain in a temp and copied once.

Hmm!! So how could ANY C produce that with gcc 2.7.2? Only if the chain's result is used in two places.

**IDEA**: What if the masked value is used twice: once for the copy to t and once for the store?
```c
v = (... ) & 0xFFF;
t = v;
*(s16 *)(arg1 + 0x100) = v;     /* the store uses v (v0) */
```
→ the code: `andi v0,v0,0xfff; move s8,v0; sh v0,256(a1)` — the store uses v0 ✗ (the target: sh s8).

Hmm, but what if the scheduler moves the `sh` after the `move`? The order would be: andi, move, sh ✓ (the order matches!) but the store's register is v0 vs s8 ✗.

Hmm, what if the store uses t and the copy is `t = v`:
```c
v = (... ) & 0xFFF;
t = v;
*(s16 *)(arg1 + 0x100) = t;
```
→ merged ✗.

Hmm, what if the value is used twice via a DIFFERENT variable:
```c
v = (... ) & 0xFFF;
t = v;
w = t;      /* w used in the loop? */
```
Hmm.

Hmm, what if the value is stored to memory AND used in the loop?
```c
v = (... ) & 0xFFF;
*(s16 *)(arg1 + 0x100) = v;   /* v0 */
t = v;
... loop uses t ...
```
→ `andi v0,v0,0xfff; sh v0,256(a1); move s8,v0` — the order (sh before move) ✗ and the store reg ✗.

Hmm.

OK, hmm, what if the source is:
```c
t = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
```
and the store is `*(s16 *)(arg1 + 0x100) = t;` → gcc: the chain computes directly into s8 → `andi s8,v0,0xfff; sh s8,256(a1)` — that's mine's output (minus the v variable) ✗ (the target has the extra move).

Hmm!!! So the target's extra `move s8,v0` requires the chain to be computed in v0.

Hmm, when does gcc compute an assignment's RHS into a temp and then copy? When the RHS expression's result is needed in a specific mode or when the expression can't be expanded directly into the destination. Hmm!

For example: if the destination is `t` (a pseudo) and the RHS is `(a & b)`, gcc's expand_expr computes the AND into a NEW pseudo and then `set t (reg new)`. Then combine propagates (as observed). Hmm.

But if the RHS's result mode differs from the destination's mode, gcc must convert ✗.

Hmm, what if the RHS is a COMPARISON or a value with a different mode?

Hmm, what if the RHS is `(u16)x` and t is s32 → the conversion is `sll/sra` ✗.

Hmm.

**What if the destination `t` is used in a context requiring a specific value and the RHS is computed via a "jump"?** no.

Hmm. OK, so what if the source value `v` is computed from a CALL? Then the chain ends in a call result (v0) and the copy to t is forced (the call result is in v0, t is callee-saved) ✓✓.

Our expression: `(*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF`. Not a call.

BUT WAIT!!! What about the loop's `func_8004787C(t)`? Hmm.

Hmm, hmm. Hmm, what about the SECOND use: `*(s16 *)(arg1 + 0x100) = t;` — hmm.

OK, let me consider: is the copy `move s8,v0` maybe NOT a copy of the masked value but something else? Let's re-read:
```
5fe4: andi v0,v0,0xfff
5fe8: move s8,v0
5fec: sh s8,256(a1)
```
Hmm, and what is s8 used for later? In the loop: `func_8004787C(t)` where t=s8 presumably. And `t += 0x600`.

So s8 = t ✓ and the mask was computed in v0 then copied.

Hmm, so the original compiler computed the RHS in a temp. gcc 2.7.2 merges.

⇒ Hmm, unless the RHS is used TWICE in the original: e.g. the original might have been:
```c
v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
t = v + zr;     /* zr = $0 in the original? */
*(s16 *)(arg1 + 0x100) = t;
```
Hmm, the original (SCEI) compiler might have kept `v` separate because `v + zr` is an add (not a copy) → the add's result is a new value in a temp → then copied to t. Hmm! But the target shows `move s8,v0` (not an add). Hmm, `addu s8,v0,$0` would be an add — the target's encoding: 0x0040f021 = move s8,v0: opcode 0, rs=2 (v0), rt=0 ($0), rd=24 (s8), funct=0x21 (addu) → `addu s8,v0,$0` — an ADD with a $0 addend!!!

AH HA! So the target's `move s8,v0` is `addu s8,v0,$0` = the `v + zr` add ✓ (consistent with the pin).

And objdump prints it as "move" ✓.

So the target's copy IS the `+ zr` add. And my earlier analysis holds: we need an opaque add.

⇒ The REAL question: can gcc 2.7.2 emit `addu rd,rs,$zero` from C?

gcc's MIPS "move" insn is `addu %0,%1,%zero` — so a plain copy ALSO emits `addu rd,rs,$zero`!! Hmm! So the encoding doesn't distinguish!

Hmm, wait: earlier I determined gcc's move pattern is `addu %0,%1,%zero`. Let me double check gcc 2.7's mips.md:

```
(define_insn "move"
  [(set (match_operand:SI 0 "register_operand" "=d,d")
	(match_operand:SI 1 "register_operand" "0,d"))]
  "addu\t%0,%1,%zero")
```
I'm fairly confident this is right for gcc 2.7 (the "move" instruction on MIPS is `or rd,rs,$zero` in some versions and `addu` in others; the PSP gcc uses `addu`).

Given the target's `move a2,a3` = 0x00e03021 (addu) and `move t0,a0` = 0x00804021 (addu) — consistent with gcc's "move" pattern being addu.

⇒ So a plain copy DOES produce the same encoding ✓.

⇒ Therefore the ONLY problem is that gcc MERGES the copy away. The copy's encoding would be right if it survived!

So the task: keep the copy. And I showed gcc merges when the source dies at the copy.

⇒ We need the source to be live beyond the copy. In the target, is the source (v0) live beyond the copy? The copy is `addu s8,v0,$0` and then `sh s8,256(a1)`. v0 is dead after. So the original compiler kept a dead copy — gcc won't.

⇒ Hmm!! Unless... the source `v` is USED LATER in the original source. Hmm! In the original source, `v` might be used later! But the current src has `v` unused after.

Hmm, hold on: maybe the ORIGINAL source was:
```c
v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
t = v + zr;
```
Hmm.

OK, hmm, so how do I keep a copy whose source dies?

**IDEA**: Make the source live beyond the copy by using it in a STORE that comes after:
```c
v = (... ) & 0xFFF;
t = v;
*(s16 *)(arg1 + 0x100) = v;    /* the source is used after the copy */
```
→ the code: `andi v0,v0,0xfff; move s8,v0; sh v0,256(a1)` — the store uses v0 ✗ (target: sh s8).

Hmm, BUT: what if the store uses t AND v is used after the copy in a way that doesn't generate code? Hmm.

**IDEA**: What if the source is used after the copy in a COMPARISON that folds away? e.g. `if (v == 0xFFF) {}` → the comparison generates code ✗ (unless it folds: v's value is known? no).

Hmm! What if the source is used after the copy in a way that the compiler folds to nothing, e.g. `v = v;`? That's the identity trick (forbidden).

Hmm, hmm. What about `v = v + 0;`? Also an identity.

Hmm, what about using v in a way that is a no-op but not an identity: e.g. `t2 = v & 0xFFF;` where v is already masked → the AND with 0xFFF is not folded by gcc (it doesn't know v's range) → it generates `andi` ✗.

Hmm.

**IDEA**: What if the copy's SOURCE is a variable that is later MODIFIED (legitimately)? In this function, `v` is never used later, so no.

Hmm, hold on!! What about `t`? The copy is `t = v`. What if t is modified later (t += 0x600 in the loop)? Then t's value at the copy is needed. But the merge is about the SOURCE (v) dying.

Hmm, hmm. So: what if we swap the roles: make the COPY's source the long-lived one and the destination short-lived? I.e., `v = t`?? no.

Hmm! What if the source is `t` and the destination is a short-lived variable? Hmm.

OK, let me think about the combine rule precisely. gcc 2.7's combine.c, in the "simplify" phase, has this code (I recall it well now):

```c
	  /* Handle a copy of a register: if the source is not modified
	     before the next use of the destination, replace the
	     destination with the source.  */
```
Hmm, this is in `simplify_reg`? no.

Actually, I recall gcc 2.7's combine.c has this in the main loop:

```c
	  /* If we are optimizing, and we have a copy of a register, then
	     we can replace all subsequent uses of the destination with the
	     source, if the source is not modified.  This is done in
	     `cse.c`, not combine.
```
Hmm! Maybe it's CSE that does it, and cse's equiv propagation is cross-block. And cse's rule: the equiv is recorded with the "life" of the source; if the source dies at the copy, the equiv's life ends → the propagation applies only to uses BEFORE the source's death — i.e., none. Hmm, then the copy would survive!

Argh, conflicting theories. Let me just EXPERIMENT: try the "v used after the copy" variant and see what happens. Cheap.

Variants for 80181E64:
p1: `v = ...; t = v; *(s16 *)(arg1 + 0x100) = v;` (v used after the copy)
p2: `v = ...; t = v; v = v;` (identity — forbidden, but as a diagnostic)
p3: keep the do-while but with the copy OUTSIDE the block: `do { v = ...; } while(0); t = v;` — hmm, that puts the copy after the block. Then the block boundary separates the def from the copy... hmm, the def and the copy would be in different blocks → combine can't propagate → the copy survives? But the do-while adds a nop ✗ (the nop showed up in n1).

Hmm! The nop in n1 came from the do-while's branch. That breaks the match (the target has no nop there).

Hmm, what if the block boundary is created by an `if` instead? `if (1) { v = ...; }` → gcc folds the condition → the block disappears ✗.

What about a `while` loop with a condition that's true once? Hmm, that adds a branch ✗.

Hmm, what about a `switch`? ✗.

Hmm, what about using a `goto` to create a basic block? E.g.:
```c
    goto L1;
L1:
    v = ...;
    t = v;
```
Hmm, gcc's jump pass would remove the redundant goto ✗.

Hmm.

OK, let me try p1 and p2 (p2 as a diagnostic only).

Actually, hold on! Let me reconsider p1's semantics: `*(s16 *)(arg1 + 0x100) = v;` vs the original `= t`. Since t = v (the copy), the stored value is the same ✓ SEMANTICS PRESERVED (t = v exactly). And it uses v after the copy → v is live past the copy → the copy survives!

And the generated code: `andi v0,v0,0xfff` (v in v0), `move s8,v0` (t = v), `sh v0,256(a1)` (the store with v0). Hmm, the target has `sh s8,256(a1)`.

Hmm, ✗. Unless gcc propagates the store's use of v into t (the copy's destination)... hmm, that's the reverse propagation: since t = v and v is used after, gcc might use t for the store too? Hmm, that's the "copy propagation" in the other direction (t's value = v's value, and both are live) → gcc's cse would replace the uses of v with t (if t is not modified between the copy and the use) → the store would use s8 ✓✓✓!!!

Hmm!! That's plausible: cse propagates the COPY's destination (t) into the source's later uses (v) when the destination isn't modified. Since t IS modified later (t += 0x600) but not before the store ✓ → the store's use of v becomes t ✓.

So p1 might give: `andi v0,v0,0xfff; move s8,v0; sh s8,256(a1)` — EXACTLY the target!!! (well, the target's `move s8,v0` is `addu s8,v0,$0` — a plain copy gives the same encoding ✓).

Let me TESTp1!

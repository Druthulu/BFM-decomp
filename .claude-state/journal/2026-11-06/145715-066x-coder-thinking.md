---
ts: 2026-11-06T21:57:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XGiKmWB4YnKBkRRKm9eC
---
Note: `iv2c` is declared inside a block `{ int iv2c; ... }` — the block scope. Also `one` is a pin ($2) inside.

Interesting: the `one` pin is at line 39 — it's an existing pin (allowed to stay). Could I use it? `one = 1` must stay.

Let me now think about a cleverer idea: what if the *copy* is from the pinned `one`... no.

New idea: what if iv2c's copy is made with the destination being a variable used in a *different* expression that combine can't fold — e.g., iv2c is used in the compare AND the compare is written with a cast that requires the SImode value... same.

Let me try variant (A): use iv2c in the r computation.

```
r = (uint)(iVar2 << 3) | c6b;   →   r = (uint)(iv2c << 3) | c6b;
```
But iv2c is block-scoped inside the `if ((short)iVar4 != 0)` block; the r line is later. I'd need to move the declaration out. That changes the declaration surface... allowed? "no signature or decl change outside the body" — inside the body is fine.

But moving iv2c's declaration to function scope might change allocation. Let's try.

Actually, better idea for keeping iVar2 alive: iv2c = iVar2 at the join; iVar2 is used at r. If I use iv2c at r instead, iVar2 dies at the copy. Then local-alloc coalesces → no move. Bad.

What if BOTH are used: `r = (uint)((iVar2 ^ iv2c) << 3) | c6b;`? That's an extra xor. No.

Hmm.

What if we make iv2c's second use be the *comparison's* other operand? no.

OK, let me think about (C): the copy in both arms. In the then arm, `iVar2 = 1; iv2c = iVar2;` — combine folds to `li v1,1`? Then the then arm has `li a0,1` and `li v1,1` — 2 insns. Target has 1 (`li a0,1`) + the shared move. So 57 total.

Unless... the then arm's `iv2c = iVar2` gets combined with `uVar5 = 0`? no.

Hmm, what if in the then arm we write `iv2c = 1;` and the copy at the join... no.

Let me think about the problem differently: maybe the answer is that this specific launder can be replaced by a *different* lever-free construct that produces the tie: **a function call**? No, that changes code.

What about **bit-field assignment**? `struct { unsigned v:16; }` — hmm.

Actually! Here's an idea: the asm's "=r" tie creates a copy because the input and output are in the same register. In plain C, a **union** or **cast between types** doesn't. But what about a **compound assignment** like `iv2c = iVar2; iv2c += 0;`? identity launder.

What about `iv2c = iVar2; iv2c |= 0;`? identity.

What about a REAL second set that keeps the value: `iv2c = iVar2 & 0xffff;` — emits andi. No.

What if the second set is a *sign-extension* that's already there... 

Hmm hold on, what about making iv2c the target of a *store and reload*? memory.

Let me try to see if any C shape produces a tie-like copy by checking the regclass/reload behavior for a variable that must be in a specific class...

Alternatively, maybe I'm overcomplicating. Let me look at the residual more carefully: score 5 with 55 ins. Which 5 positions? Only one insertion (the move) plus shifts. So the ONLY difference is the move.

Since the target's move is a reload-inserted tie copy, maybe I can create a tie with a real C construct: **a conditional expression with a hard register**? 

What about `__builtin_...`? none.

Hmm, what about making iv2c and iVar2 differ in *mode* such that reload must copy: e.g., iv2c is `s16` and the compare is done in SImode with a sign extend — reload would emit sll/sra, not move.

What about iv2c being `float`? no.

OK, let me try the "second use" experiment to see if it produces the move. Even if the later code differs, it tells me whether combine is the blocker.

Variant (A): move iv2c decl to the function top, assign at the join, use in the r line instead of iVar2, and keep iVar2 alive by ALSO using it in `r`... hmm.

Actually, simpler test: keep everything and add a second use of iv2c right after the compare, e.g. `uVar1 = ... | (iv2c - iv2c);`? That's a launder-ish identity. But as a TEST it tells me the mechanism. It would add instructions though.

Let me think about what "dead_or_set_p(i3, i1dest)" requires: i3 is the compare (jump_insn). dead_or_set_p checks REG_DEAD notes on i3 for iv2c. If iv2c is used later, no REG_DEAD → added_sets_1 = true.

Then combine would still combine i1 into i3 but must re-add the set. That's not profitable (no insn deleted) — combine has a check:

```
  if (added_sets_1 && added_sets_2 ... )
```
Actually combine may still combine if `newi2pat` replaces i2 and reduces cost... In our case i2 is `li v0,1` (not combinable with i3? it is: the compare uses v0, so combine could fold the constant into the compare — but MIPS branch can't have an immediate, so recog fails).

I think combine would reject.

Let me just try it as a diagnostic:

w9: add a second use of iv2c after the compare: e.g. change line 45 `uVar1 = p4s | (param_3 & 0xffff) | uVar5;` — no.

Diagnostic: after the `if (iv2c != one) uVar5 = 0;` add `iv2c = iv2c + 0;`? identity.

Hmm, what about making the compare use iv2c and then uVar1 use iv2c: `uVar1 = p4s | (param_3 & 0xffff) | (uVar5 & (iv2c - iv2c));`? Ugly identity.

Let me instead test with a REAL second use that keeps the value: `if (iv2c != one) uVar5 = 0;` then later `r = (uint)(iv2c << 3) | c6b;` (replacing iVar2). And to keep iVar2 alive, note iVar2 is ALSO used... only there. So iVar2 dies at the copy. Unless I keep `iVar2` used in the else arm's `param_2` shift? no.

OK, so that fails on coalescing.

Hmm, what if iVar2 is *not* the copy source? What if the copy is `iv2c = one` ... no.

What if we introduce a *second* variable `iv2` that both iVar2 and iv2c alias... 

New idea: what if the copy source is a **parameter** (param_2) or another long-lived variable? The target's copy is `move v1,a0` where a0 = iVar2. Hmm.

Honestly, maybe this item is a WALL. But before giving up, let me try a few more shapes quickly (each score is ~10 s):

1. Copy in both arms.
2. `iv2c = iVar2` with the compare written as `if (one != iv2c)` (swapped operands) — combine might still merge.
3. `iv2c` as a `s16` with compare against `one` — sll/sra?
4. Declare iv2c at function scope (move it out of the block) — changes allocno.

Let me batch 1-4.

For 1, I need to restructure lines 30-44:
```
            if ((short)iVar4 == six) { iVar2 = 1; iv2c = iVar2; uVar5 = 0; }
            else {
                int t;
                t = param_2 >> 0x10 & 0xf;
                iVar2 = t + 1;
                param_2 = param_2 << 4;
                iv2c = iVar2;
            }
            {
                register int one __asm__("$2");  // pin
                one = 1;
                if (iv2c != one) uVar5 = 0;
            }
```
with `int iv2c;` declared before the if.

For 4: move `int iv2c;` to the function top (near `int cont;`).

Let me write a script to generate these variants.

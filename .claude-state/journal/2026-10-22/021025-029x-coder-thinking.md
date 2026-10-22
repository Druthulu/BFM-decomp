---
ts: 2026-10-22T08:10:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_lf0VhAvOoqTT9SVGqGRd
---
c2 (s16 u): the copy became `sll v0,v0,0x10` (sign extension of t into u, but it stayed in v0!). So gcc merged u's reg with t's reg and emitted the sign extension in place. Interesting: `sll v0,v0,16` then later `sra v0,v0,16` then `addiu v0,v0,-1`. So the sign extension got materialized in v0 and u shares v0 with t. So the copy did NOT get a separate register.

c3: the copy vanished entirely.

So in c2, the truncation copy `u = t` did NOT survive as a separate reg — it became a sign-extension in place (combine folded `(set u (sign_extend:HI t))` into a modification of t's reg?!). Hmm, that's because u is a QImode pseudo and gcc's expand did the conversion at the USE (t = u - 1 → sign_extend of u) — so u was eliminated and the sign extension applied to t directly. That's the "convert at use" optimization: since u is only used once, gcc converts at the use site.

So for c4 (u16), the zero-extension happened at the use site too: `andi v0,v0,0xffff` — also in v0 (t's reg), and u shared... hmm, but c4 had 42 ins and score 2, meaning the structure was right, just the extension instruction differs. Wait, c4's diff: `mine[12] andi v0,v0,0xffff | target[12] move v1,v0` and `mine[35] addiu v0,v0,-1 | target addiu v0,v1,-1`. So in c4, the copy DID survive as a separate pseudo (v1 in the target; in mine the andi is in v0 and the addiu reads v0). Hmm, so in c4 the andi is at position 12 (the delay slot) and the addiu reads v0.

So in c4 the zero-extension is computed in v0 (t's reg) at the delay slot, and u = that. Then `addiu v0, v0, -1`. So u got coalesced with v0 (since u = zero_extend(t), and u's only use is the addiu → the addiu could read v0 directly). Right — the copy `u = (u16)t` was folded into the use.

Hmm OK. So in c4, the andi is the "copy+extend" and it's in v0.

To get `or v1,v0` I need a copy that goes to a DIFFERENT register (v1) and the addiu reads v1.

Why would the target's copy go to v1? Because in the target, u is a separate pseudo that couldn't be coalesced with t. Why not? Because at the point of `t = u - 1`, t is live (it's the destination). Hmm, in the target, t (v0) is the destination of the addiu and u (v1) is the source — they must differ.

In c4, u was folded into the use, so the addiu read v0 (t's reg) directly and t's old value wasn't needed → so gcc could use the same reg.

Hmm! In the target, `t` (v0) is the *destination* of the addiu, and v0 previously held t's old value (which is dead after the copy). So gcc could have done `addiu v0,v0,-1` (like mine). It didn't, because u was a separate pseudo at the RTL level: `(set t (plus u -1))` where u is a different pseudo → the addiu needs u's reg ≠ t's reg (since t is being written) → u gets v1.

Hmm, but in c4, gcc folded u away (the zero_extend was applied to the use), so the addiu read v0.

Why did gcc fold u in c4 but not in the target? Because in the target, u's RTL was `(set u (plus t (reg 0)))` → combine converted it to `(set u t)` — a copy that cse (already run) doesn't touch → u stays a separate pseudo → the addiu reads u's reg.

In c4, u's RTL was `(set u (zero_extend:HI t))` → combine folded the zero_extend into the USE (because the use is a simple `(plus u -1)`, combine can rewrite the use's operand: `(plus (zero_extend t) -1)` → `(and (zero_extend t) 0xffff) - 1`... hmm, actually combine rewrote `u` to `(zero_extend:HI t)` in the addiu, then the addiu's operand is the andi result → the andi got its own reg or was coalesced into v0.

Hmm, in c4 the andi is in v0 (t's reg) and the addiu reads v0. So gcc did: v0 = t & 0xffff; v0 = v0 - 1. And the "copy" disappeared.

So the target's `move v1,v0` — the copy lives in v1 — requires a real copy pseudo.

So: how do we get a real copy pseudo that survives cse AND is a plain `or`?

Options:
(a) `(plus t (reg 0))` — the pin. ✗
(b) The copy must survive cse.

Since cse kills plain copies, we need a non-copy RTL at cse time that becomes a copy at combine time WITHOUT being folded into the use.

Hmm! What if the copy is `(set u (zero_extend:HI t))` but the USE of u is such that combine can't fold the extension into it? E.g., if u is used in TWO places, or if the use is not a simple arithmetic op.

In the target, u is used once: `t = u - 1`.

Hmm, what if u is used twice: `t = u - 1;` and something else? Extra code.

What if the use is `t = u - 1` where the subtraction's result... hmm.

Alternatively: what if the copy is `(set u (sign_extend:HI t))` (u is s16) and the use is in a context where the extension can't be folded — but c2 showed gcc folded the extension into the use (sll/sra around the addiu).

Hmm, what if the ORDER is reversed: what if the extension is materialized at the COPY (into v1) and the use just reads v1? For that, gcc must not fold the extension into the use. gcc folds a copy into its single use when the copy is "simple". This is gcc's "copy propagation in combine" — combine removes a copy whose dest is used once by substituting the source into the use, if the source's reg can be used. But it can't always (e.g., if the use requires a specific reg or if the dest is live across something).

Hmm! Key: combine removes `(set u X)` by substituting X into u's uses ONLY IF u has a single use and ... Actually gcc's combine has the "copy propagation" (`combine` handles `SET` where the dest is a pseudo with one use: "try to eliminate the copy by substituting"). And there's `local-alloc`'s coalescing.

Hmm, but the target has u in v1 — so the copy was NOT eliminated. Why? Because at combine time, the RTL was `(set u (plus t (reg 0)))` — combine turned it into a copy, but the copy elimination happened... hmm, combine does the copy elimination in the same pass. Order within combine: combine processes insns in order; when it sees `(set u (plus t (reg 0)))`, it converts it to `(set u t)` — but the "eliminate copies" logic runs on the already-converted copy? Apparently not — it kept the copy.

Hmm, and for c4's `(set u (zero_extend:HI t))`, combine rewrote the USE to `(zero_extend:HI t)` and deleted the set.

So the difference: combine's copy elimination happens when the copy's source is a "simple" operand that can be substituted (a reg). `(plus t (reg 0))` — combine first folds it to `t`... then it would be eliminable. But it wasn't!

Hmm, unless combine's folding of `(plus x (reg 0))` happens in a LATER combine pass (combine runs multiple times until stable). The first pass converts the plus-with-zero into a copy at the RTL level? Hmm.

OK, whatever the mechanism — empirically the target's copy survives and mine don't.

**Let me think about what other C constructs produce a surviving copy pseudo.**

From the moves.md, several MATCHes mention copy preservation:
- "u16 t (HImode copy escapes cse equiv)" (func_80184F18)
- "u8 c = a1 dropped $16/$3 pins"
- "s16 flag2/3/4 copies (sign-extend escapes cse, combine nonzero_bits -> move)"
- "u8/(u16) copy escapes cse but splits mode's a1 pseudo (2) or adds andi 0xffff (1)"

Hmm: "u8/(u16) copy escapes cse but ... adds andi 0xffff (1)" — so for u16, the copy escapes cse but adds an andi.

In our case the andi is `andi v0,v0,0xffff` in the SAME reg (v0), not a copy to v1.

Hmm, what if the copy destination is used in a way that requires a separate register...

**NEW IDEA**: What if we make the copy's DESTINATION be a variable that is live ACROSS a call or across a branch, forcing a separate register? E.g., in the target, `u` is used at 8134 which is reached by a branch (the else arm). Hmm.

**NEW IDEA 2**: What if the copy is `u = t` where u is declared `u16` and t is declared `u16`?? → plain copy → cse. ✗

**NEW IDEA 3**: What if we use TWO truncations so that the copy survives with the right form? E.g., `u = (u16)t;` and then `w = (u16)u;`? no.

**NEW IDEA 4 — the `x`/`y`/`z` trick**: what if the copy `or v1,v0` comes from copying a u16 value? In the target v0 holds the sign-extended unk84. If we made the load `lhu`... no, target has lh.

Hmm, hold on!! Wait. Let me reconsider: what if `t` is declared **u16** and the assignment `t = unk84` (s16 field) is a truncation → gcc emits `lh` + `andi 0xffff`?? That adds an andi. But then `u = t` (u16→u16) is a plain copy → cse. ✗

**NEW IDEA 5**: Use `s16` for u and make the source value's sign extension unnecessary by... hmm, c2 showed the sll/sra.

**NEW IDEA 6 — think about `combine` differently**: The reason combine eliminated the copy in c4 is that it folded the conversion into the use. What if the use is a **store** rather than arithmetic? Then combine can't fold the extension into the store (it would need to compute the extension anyway) — the copy would survive as a real pseudo with the extension in it.

So: `u = (u16)t;` and then `*(s16*)&x = u;`? That changes the asm.

Hmm, but what if the use is `t = u - 1` where the subtraction is by a CONSTANT? combine folded the extension into the addiu.

What if the use is `t = u - 1` where 1 is a variable? Then combine can't fold `(plus (zero_extend t) -1)` into one insn; it might keep the zero_extend at the copy. Hmm! But then the addiu becomes a generic subtract → different insn.

Hmm.

OK, RADICALLY DIFFERENT IDEA: **what if the copy is a `u16` copy where the source is a `u16` value that gcc knows is zero-extended, i.e. the source is `x`, `y`, or `z`?**

But the target's copy source is v0 = the lh result. So no.

Hmm, hold on, let me re-examine the target once more:

```
80cc: lh v0,132(s0)
80d0: nop
80d4: bnez v0,8134
80d8: move v1,v0
```
Hmm, `move v1,v0` is the delay slot of the bnez.

What if the delay slot instruction is NOT the copy `u = t` but something else that just happens to look like a copy?! Like the target's `u = t + zr` → the addu → and combine turned it into `or`?

Hmm, `u = t + zr` with zr = $0 → the RTL `(set u (plus t (reg 0)))`. Combine's rule: `(plus x (reg 0))` → hmm, does combine fold plus-with-reg-0 into a copy? There's a gcc rule in combine.c:
```c
    case PLUS:
      ...
      /* If we are adding zero to a reg, ... */
```
Hmm, actually gcc's `simplify_expr` for PLUS:
```c
      /* X + 0 is X.  */
      if (GET_CODE (y) == CONST_INT && INSN_P(insn) && ...)
```
That handles a CONSTANT 0, not (reg 0). For `(reg 0)`, combine's `plus` handling: gcc's combine has a rule that converts `(plus x (reg 0))` to x? Hmm, in gcc's md file, the mips "move" pattern is `(set (reg) (plus (reg) (reg 0)))`??

Let me check: gcc 2.7 mips.md:
```
(define_insn "move"
  [(set (match_operand 0 "register_operand" "=r,r")
	(match_operand 1 "register_operand" "0,r"))
   (set_attr_attr "move" "type,moved,clobbered")]
```
Hmm, with operand 1 constraint "0,r" meaning it can match the same register as operand 0 or any register. But for `(set (reg a) (plus (reg b) (reg 0)))` to match "move", operand 1 must be a single register operand — a plus isn't. So there must be a separate rule.

Actually gcc's mips.md has:
```
(define_insn "move"
  [(set (match_operand 0 "register_operand" "=r,r")
	(plus (match_operand 1 "register_operand" "r,r")
	      (match_operand 2 "register_operand" "r,r")))]
```
Hmm, I don't remember. But the project's own note (delever_permute.py) says: "objdump prints the pseudo-instruction `move` for `addu rX,rY,$zero` and gas assembles it as `or`". So objdump prints `move` for BOTH `or rd,rs,$zero` and `addu rd,rs,$zero`.

And our target's `move v1,v0` has bytes 0x00401821 = `or`. So it's `or`.

And the src for 80182ED4 has `u = t + zr` with `register u32 zr __asm__("$0")` → the RTL is `(plus t (reg 0))` → gcc's mips "move" insn pattern must accept `(plus (reg) (reg 0))` → so gcc's mips.md "move" pattern is:
```
(define_insn "move"
  [(set (match_operand 0 "register_operand" "=r,r")
	(plus (match_operand 1 "register_operand" "r,r")
	      (match_operand 2 "register_operand" "r,r")))
   (set (match_operand 2 "register_operand" "0,r"))
   (set_attr_attr "move" "type,moved,clobbered")]
```
with operand 2 constrained to match operand 0 (so it must be $0 → the "0" alternative means it must equal operand 0's register). So `(plus t (reg 0))` → "move" (or). But wait, the bytes are `or` not `addu`. Hmm — the "move" insn in gcc's mips.md is defined with the `or` opcode:
```
(define_insn "move"
  [(set (match_operand 0 "register_operand" "=r,r")
	(plus (match_operand 1 "register_operand" "r,r")
	      (match_operand 2 "register_operand" "r,r")))
   (set (match_operand 2 "register_operand" "0,r"))
   (set_attr_attr "move" "type,moved,clobbered")]
```
And the output template would be "or %0,%1,%2" → `or v1,v0,$0` = 0x00401821 ✓. Yes! That's it. gcc's mips "move" is `or`.

So `(plus t (reg 0))` → "move" → `or`. And a plain `(set u t)` → also "move"? The "move" pattern requires a plus with 3 operands... For a plain copy `(set (reg) (reg))`, gcc's mips has:
```
(define_insn "movr"
  [(set (match_operand 0 "register_operand" "=r,r")
	(match_operand 1 "register_operand" "0,r"))
   (set_attr_attr "move" "type,moved,clobbered")]
```
`movr` = `or rd,rs,$zero` too. Either way → `or`.

Great, so a plain copy `u = t` WOULD give `or v1,v0` if it survived.

So the whole problem is cse.

**IDEA: make cse NOT see the copy as a copy.** cse sees the RTL after expand. What if the copy's RHS is a MEM? No.

What if the copy's RHS is a `plus` of two regs where one is... no.

What if the RHS is `(reg t)` but t is a HARD register at cse time? Then cse's make_regs_eqv might refuse to equate (there's a rule: "don't equate if one is a hard register"). Hmm! Interesting: at cse time (early pass), the pseudos are still pseudos. But after global_alloc, some pseudos become hard regs — but cse already ran.

Hmm. BUT: `make_regs_eqv` in cse.c has:
```c
  /* Don't attempt to equate the two registers if one is a
     hard register and the other is not.  */
```
So a copy from a hard reg wouldn't be propagated! But we can't make t a hard reg without a pin.

Hmm, BUT: what if the copy's SOURCE is a hard register naturally? Like a parameter! `u = arg0` — arg0 is in a0 (a hard reg). Then cse wouldn't equate u with arg0 (hard reg rule), and the copy survives!

But the target's copy is `or v1,v0` where v0 = the loaded value, not a0. Hmm. But wait — in the target, `t` is loaded into v0. Hmm.

Hmm, but hold on: is that rule real? gcc 2.7's cse.c make_regs_eqv:

```c
  /* Don't attempt to equate the two registers if one is a
     hard register and the other is not.  */

  if (regno >= FIRST_PSEUDO_REGISTER && orig_regno < FIRST_PSEUDO_REGISTER)
    return 0;
```
Yes! That's real (I'm fairly confident). So a copy FROM a hard register (parameter) is not equated → the copy survives!

So: if `t` were a parameter... but the signature is fixed: `void func_80182ED4(s32 arg0)`. The parameter is arg0 = the struct pointer. The target copies the loaded unk84.

Hmm. But maybe we can route the value through a parameter? No.

Hmm, what about `func_80133784(1, sp10, ...)` — no.

Hmm! What about the ELSE branch reading the field twice? Like:
```
} else {
    u = ((Unkstruct_80182ED4 *)arg0)->unk84;   /* reload → lh again */
    t = u - 1;
}
```
→ two `lh` insns. ✗

OK. So we need t's value in a hard reg at cse time. Not possible.

**IDEA: the copy's DESTINATION is a hard register?** Also needs a pin.

Hmm.

**IDEA: Make the copy's RHS not a register at all but a "subreg" or a "mem".**

Hmm, what about copying a *struct field* by value? no.

**IDEA: What if the copy survives because of the `reg_equiv_content` direction rule?** The G02 wall note: "cse make_regs_eqv (cse.c:840): iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1 (s-reg); target keeps t in v0".

So cse DOES sometimes keep the copy (iVar1 canonical) and rewrite t's uses to iVar1. In that case the copy `iVar1 = t` survives as a real copy (with the source's uses rewritten).

So the direction of canonicalization matters. When the copy's destination outlives the source, the destination becomes canonical and the copy SURVIVES (the source's uses get rewritten to the dest).

Hmm, in our case: `u = t; t = u - 1;`. u's live range: [copy, addiu]. t's live range: [lh, copy]. So u is born at the copy and t dies at the copy → equal length, but t starts earlier → t outlives u in the "live range length" sense? t's range [lh..copy] is longer than u's [copy..addiu]. So t is canonical → u's uses rewritten to t → copy removed.

To make u canonical, u must outlive t. So u must be used AFTER t's last use.

In c3 I tried `u = t; w = u - 1;` — u's range [copy, addiu], t's range [lh, copy]. Still t is longer (starts earlier). Hmm, but "outlives" might mean "dies later". u dies at the addiu, t dies at the copy → u dies later → u outlives t → u canonical → the copy survives! But c3's result: the copy vanished (40 ins, `addiu v0,v0,-1`).

Hmm. So no.

Wait, maybe in c3 the problem was different: `w = u - 1` and `unk84 = w` — and the diff showed mine[12] = `addiu v0,v0,-1` (in the delay slot) and the target's `move v1,v0`. So the copy was gone.

OK so what made c4 (u16) keep a separate structure? The zero_extend wasn't propagated.

So cse-level: the copy `u = t` is always propagated (u→t) when both are pseudos.

Therefore the ONLY way to keep a copy is to make the RHS not a plain reg copy at cse time. And combine must then fold it to `or`.

Options for a non-copy RHS that combine folds to a copy:
1. `(plus t (reg 0))` — pin ✗
2. `(zero_extend:HI t)` → folds to copy iff t's high bits are known zero.
3. `(sign_extend:HI t)` → folds to copy iff t's bits 15-31 are known zero (and the sign bit is 0).
4. `(truncate:HI t)` → combine would fold to `andi` (or to a copy if it can prove the high bits are irrelevant — no).
5. `(and t 0xffffffff)` → tree-folded.
6. `(ior t 0)` → tree-folded.
7. `(mult t 1)` → folded.
8. `(not (not t))` → folded.
9. `(neg (neg t))` → folded.
10. `(plus t (const 0))` → folded at the tree level (fold.c).

Hmm, what about #2 with a source whose high bits ARE known zero? The source is `t` = the lh result. The lh result's high bits = bit 15.

**BUT WAIT!** What if the source of the copy is NOT `t` but the value `t` had BEFORE... no.

**IDEA**: What if the copy's RHS is a **constant expression involving a variable**? no.

**IDEA**: What if the copy's RHS is `(reg t)` but t is at that point a pseudo that has been "renamed"? no.

**IDEA — the good one**: What if we make the copy's RHS a **MEM** — i.e. the value passes through memory? Then the "copy" becomes a load, not `or`. ✗

**IDEA**: What if the copy's RHS is a `plus` of a reg and a **constant that is not 0** but the whole thing is folded elsewhere? no.

Hmm, hold on. Let's revisit: **maybe the target's `or v1,v0` is NOT `u = t`**. What if it's `u = t + zr` where the `+ zr` produced `or` because gcc's mips "move" pattern matched `(plus t (reg 0))`? YES — that's exactly it: gcc's "move" insn accepts `(plus (reg) (reg 0))`. So `u = t + zr` → `or v1,v0,$0` DIRECTLY by the pattern matcher, WITHOUT combine folding! And cse didn't propagate because the RTL was a plus.

So the copy's RTL is `(set u (plus t (reg 0)))`.

Now: can we produce `(plus t (reg 0))` without a pin?

`(reg 0)` = the hard register $zero. In C, how do you get an RTL operand that is literally `(reg 0)`? Only via a pinned variable... OR via a construct that gcc materializes as `(reg 0)`. Hmm!

Ideas:
- `t + zr` where zr is a variable declared `register` without asm → gcc would allocate it to a real reg. ✗
- Division/modulo by ... no.
- `x << 0`? → folded.
- A switch with a `default`? no.

Hmm. What produces `(reg 0)` in gcc's RTL? The "zero" register is used as an operand in many patterns. E.g., `(set (reg a) (plus (reg b) (reg 0)))` arises from... a `mem` with a zero offset? `(mem (reg b) 0)` → that's a MEM, not a plus.

What about `(plus (reg b) (reg 0))` arising from `b + 0` where 0 is a CONST? gcc's RTL constants are CONST_INT, not (reg 0). So no.

Hmm. What about the `zero` used in `(set (reg a) (reg b))`? no.

OK so (reg 0) is only from a pinned variable.

**THEREFORE**: the lever-free solution must make the copy come from a mode conversion that combine folds to a plain copy — which requires knowing the high bits.

Hmm, so we need the source's high bits known zero. The source is the `lh` result.

**AH WAIT!** What if the copy's source is the value AFTER the subtraction... no.

**AH — what about copying a value whose type is u16 and whose content came from `lhu`?** In the target, `x = unk6` is `lhu` (u16 → u16, zero-extended) and `y = unkA` is `lhu`, `z = unkE` is `lhu`.

The target's `or v1,v0` copies v0 (the lh result). But hmm — what if in the target, the `move v1,v0` is actually copying something else and v0 coincidentally holds unk84? The target's v0 at 80cc = lh result; at 80d8 `or v1,v0`. So v1 = the lh result. And later `addiu v0,v1,-1` → v0 = v1 - 1 = unk84 - 1. Yes.

So the copy is of the sign-extended s16 value.

Hmm, so how do we get a plain 32-bit copy of a sign-extended 16-bit value that survives cse?

`(sign_extend:HI t)` where t is the lh result → the value equals t (since t is already sign-extended-16) → combine would need to know that. combine's rule for SIGN_EXTEND: "if the value's high bits are known zero, fold to a copy" — here the high bits are NOT known zero (they're bit 15).

Hmm, BUT: combine might handle it differently: `(sign_extend:HI t)` where t is 32-bit → the result = sign_extend of t's low 16. combine could convert it to `(and t 0xffff)` with a sign... no.

Hmm, hold on. What if `u` is s16 and t is the lh result, but we make the ADDEND different: `t = u - 1` → combine rewrote the extension into the use. What if the use were `t = u` (a copy!) — no.

**COMPLETELY DIFFERENT ANGLE**: what if we make the else-arm's copy be a copy of a value that gcc loads as `lhu`?

What if we restructure the code so that the value copied is a u16 that gcc loaded with `lhu`?? But the target has `lh` for unk84 and the copy is of that value.

Hmm, unless: the target's `lh v0,132(s0)` is `t = unk84` (sign-extended), and `or v1,v0` is `u = t`. What if we express it as:

```
u16 u;
s32 t;
t = unk84;         /* lh */
u = t;              /* u16 → zero_extend → andi */
```
✗ (c4).

```
s16 u;
s32 t;
t = unk84;
u = t;              /* s16 → sign_extend:HI */
```
✗ (c2, sll/sra).

Hmm. In c2, gcc produced `sll v0,v0,0x10` — that's a LEFT shift by 16, i.e. the ZERO-extend preparation?? `sll v0,v0,16` then `sra v0,v0,16` = sign extension. So gcc computed the sign extension of t into u (or rather kept t's reg and sign-extended). Since u is only used once, gcc folded the conversion into the use (the addiu's operand) — the conversion `(sign_extend:HI t)` was placed in the use, and the sign extension of u to s32 became sll/sra.

Hmm, so the copy `u = t` (s16) got eliminated entirely; gcc just tracked the conversion.

So: to have a surviving copy, the destination must be used in a way that the conversion can't be folded into.

**What if u is used TWICE?** e.g. `t = u - 1;` and also... hmm we need extra code.

Hmm, what if `u` is used in a STORE? Like the store `unk84 = t` — no.

**What if the ADDEND of the subtraction is a variable?** `t = u - k` where k is a variable = 1. Then combine can't fold `(zero_extend t) - k` into the addiu... but the target's insn is `addiu v0,v1,-1` (an immediate). If k were a variable, gcc would emit a generic sub → different insn. Unless k is a constant that gcc materializes in a reg → `subu v0,v1,kreg` → different. ✗

**What if the use of u is a comparison?** `t = (u > 5) ? ... : ...` → different asm.

Hmm.

OK, let me reconsider the problem completely. Maybe the lever-free solution doesn't need `u` at all! Let me re-look at the target:

```
80cc: lh v0,132(s0)     ; t = unk84
80d4: bnez v0,8134       ; if (t != 0) goto else
80d8: move v1,v0         ; u = t   [delay slot]
80dc: lhu a2,6(s0)      ; x
...
8130: li v0,30           ; t = 0x1E
8134: addiu v0,v1,-1     ; t = u - 1   (else arm)
8138: sh v0,132(s0)      ; unk84 = t
```

Hmm, what if the `move v1,v0` is NOT `u = t` but rather part of the *branch condition* handling? Like `bnez v0` where v0 is compared...

What if the C is:
```
t = unk84;
if (t != 0) {
    u = t;         /* hmm */
    t = u - 1;
}
```
Same.

What if the C is:
```
t = unk84;
if (t != 0) {
    goto lab;
}
...
lab: ;
```

Hmm.

WAIT A MOMENT. What if the `move v1,v0` is the copy of the *branch condition value* into a variable used later — like:

```
if (t != 0) {
    u = t;      /* hmm */
```

Hmm what if it's:
```
t = unk84;
if (t == 0) { ...; t = 0x1E; }
else { t = t - 1; }
```
→ `addiu v0,v0,-1` (what mine does).

So the target genuinely has an extra register.

Hmm, what if the target's `u` is used for something else that I can reproduce? Let's see where v1 is used: `addiu v0,v1,-1` at 8134 and then `sh v0,132(s0)`. v1 is not used elsewhere (v1 is reused at 80e8 for y). So u's only use is the subtraction.

So the C must have a variable holding a copy of t, used once in a subtraction.

Given cse kills plain copies, and conversions get folded...

**AH WAIT!!!** What about `u` being a **QImode/other mode variable whose conversion is a NO-OP because the source is the same mode**, i.e. a plain copy — but the copy survives because of the *order of the definitions*? Hmm.

Let me revisit cse's make_regs_eqv direction rule once more. The G02 wall note is explicit: "cse make_regs_eqv (cse.c:840): iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1 (s-reg); target keeps t in v0". So there IS a case where the copy survives: when the destination outlives the source.

In our case, does u outlive t? Let me think about what "outlives" means in cse.c. Let me guess the code at cse.c:840 (gcc 2.7.2):

```c
	  /* If we are setting a reg to a reg, and the source reg is not
	     live after this insn, and the destination is used more than
	     once, we can swap the roles...  */
```

Honestly, let me look at the actual gcc 2.7.2 cse.c code. Maybe I can find it online knowledge... I recall:

```c
/* Return 1 if we should consider the insn as a candidate for the
   equivalence table.  */

static int
consider_insn (insn, reg, orig_reg, equiv, x, y)
     rtx insn;
     int reg, orig_reg;
     int equiv;
     rtx x, y;
{
  int xreg = REGNO (x);
  int yreg = REGNO (y);
  ...
  /* If this insn doesn't set a register, ... */
  ...
  /* If the SET_REG0 is not a reg-reg copy, ... */
  ...
  /* If we are setting a reg to a reg and the reg is not dead, ... */
  ...
      /* If the destination reg is live and the source is not, we
	 may want to keep the copy.  */
```

I really can't recall.

**PRACTICAL APPROACH**: let me try a bunch of spellings quickly and see if any keeps the copy:

Try A: `u` declared `s32`, copy `u = t`, and use `u` in the subtraction but ALSO make t live longer by using t in the store:
```
} else { u = t; t = u - 1; }
unk84 = t;
```
(current)

Try B: introduce the copy AFTER the branch decision, with t still needed:
```
} else { u = t; t = u - 1; }
```

Try C: make the copy's destination a variable that is ALSO used in the t==0 path:
```
if (t == 0) { ...; u = 0x1E; t = u; }  /* hmm */
```
Hmm! Interesting: if `u` is used in BOTH branches, then u is a longer-lived value. Let's think:
```
s32 t, u;
t = unk84;
if (t == 0) {
    ...;
    t = 0x1E;
} else {
    u = t;
    t = u - 1;
}
unk84 = t;
```
vs
```
s32 t, u;
t = unk84;
if (t == 0) {
    ...;
    u = 0x1E;      /* u = 30 */
    t = u;
} else {
    u = t;
    t = u - 1;
}
unk84 = t;
```
Hmm, in the t==0 path the target has `li v0,30` then `sh v0,132(s0)` — one insn for the constant. With `u = 0x1E; t = u;` → `li v0,30; or v0,v0,$0`?? extra insn. ✗

Try D: **Make `u` the variable stored**:
```
s32 t, u;
t = unk84;
if (t == 0) { ...; t = 0x1E; u = t; }
else { u = t; t = u - 1; }
unk84 = t;
```
✗ extra insn.

Hmm.

Try E: What if the copy is at the TOP (before the branch) and t is redefined?
```
s32 t, u;
t = unk84;
u = t;              /* copy before the branch */
if (t == 0) { ...; t = 0x1E; }
else { t = u - 1; }
unk84 = t;
```
Now: u's live range = [copy, addiu] (in the else arm). t's = [lh, addiu] (t is redefined in the else arm at the addiu; in the t==0 path t = 0x1E). Hmm, t is live until the addiu. u is live from the copy (before the branch) until the addiu. So u's range is SHORTER. ✗

But: the copy is now before the branch → the delay slot would be filled by something else. And cse: `u = t` plain copy → propagated. ✗

Hmm.

OK, let me try yet another angle: **look at what other shards did for this exact pattern.** The moves.md has "pin | func_8017FBCC | WALL combine-copy-merge — combine folds then-block copy v1=v0 into v0=v1-1; pre-test copy: cse canonical v1 rewrites the test; only v0+$0 keeps it (WH1)".

"only v0+$0 keeps it" — so WH1 concluded the same thing.

And "pin | func_80189750 | WALL cse-copy-merge — cse make_regs_eqv (cse.c:840): iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1 (s-reg); target keeps t in v0".

Hmm. These are WALLs for other items, but my item might be crackable.

Let me look at the WH1/G02 notes for these to see what was tried.

Actually, let me look at how OTHER items with a `$0` pin were cracked. From moves.md:
- "pin | func_80180C04 | MATCH — $0 zr pin dropped, flag declared s16: HImode flag=1 test not folded by cse (W07)"
- "pin | func_8017E1D4 | MATCH — $0 zr pin: s16 flag2/3/4 copies (sign-extend escapes cse, combine nonzero_bits -> move); $18 w pin: ot = inner call split from the return (G02)"

The G02 one is exactly the same mechanism as here — but it worked because flag's range was known (0..255) so the sign_extend folded to a move.

So for our case, we need the copied value's range to be known. t = unk84 (s16, sign-extended) → range -32768..32767 → the sign_extend:HI is NOT a no-op.

**UNLESS we change the field access to be unsigned!** `t = *(u16 *)&((Unkstruct_80182ED4 *)arg0)->unk84;` → the load becomes `lhu` → range 0..65535 → the copy `u = t` as s16 → hmm, s16 of a 0..65535 value → the sign bit is bit 15, unknown → the sign_extend:HI is not a no-op either. But as `u16 u`: `u = t` (u16) → zero_extend:HI(t) → t's bits 16-31 are known zero (lhu) → the zero_extend is a no-op → folds to a copy → `or v1,v0`!

But the load becomes `lhu` instead of `lh` → the target has `lh`. ✗ Semantically different too.

Hmm! Unless... the load `lh` and the copy `or v1,v0`...

WAIT!!! What if the load is `lh` (sign-extending) and the copy is `or`, and we could get combine to know the high bits are... no, lh's high bits = bit 15.

Hmm, hold on: **what if the value copied is not unk84 but something else that gcc knows is 0..255?**

Look at the target's other insns: `lhu a2,6(s0)` (x), `lhu v1,10(s0)` (y), `lhu v0,14(s0)` (z). These are u16 loads (zero-extended, range 0..65535). Hmm, still not 0..255.

Hmm, but wait: `z = unkE` and `y = unkA` are u16 in the struct (u16 unkA, u16 unkE). And `x = unk6` (u16).

Hmm, so a u16 copy of a u16 value: `u = y` where u is u16 and y is u16 → same mode → plain copy → cse.

What about `u = y` where u is u16 and y is s32? Then y is a u16 value assigned to an s32 var → zero-extended at the assignment (the load `lhu` then the assignment to s32 is free). Then `u = y` (u16) → zero_extend:HI(y) → y's bits 16-31 known zero? y is a pseudo assigned from an lhu → combine's nonzero_bits can't know. ✗

Hmm. combine's nonzero_bits works on CONSTs and on regs whose value it can determine...

Hmm, hold on: does gcc 2.7's combine have `nonzero_bits` for a MEM? No. But it does have the "REG killed/set" tracking within the insn sequence! combine processes a sequence of insns (the whole basic block) and maintains `known_zero`/`nonzero_bits` per register based on the insns it has SEEN in the current sequence. combine's `combine_insns` processes a list of insns and does track register values set within the sequence!

Yes! gcc 2.7's combine has this: in `combine_insns`, it keeps `reg_set_cnt` and the `x` insns, and functions like `known_zero (reg)` check "reg was set to a constant in this sequence". But for a MEM load, combine can't know the value.

Hmm. So no.

OK. Let me now consider: maybe the answer for 80182ED4 is a WALL. But the brief says the item "was walled before after too few tries" and I should try new moves. I have 4 items and limited time. Let me time-box this one.

Let me try a few more things quickly, then move on and come back if time permits:

Try: `u` as u16 but with the copy source being `t` where t is declared **u16** and loaded via `lh`:
```
u16 t, u;    /* t = unk84 truncated */
```
→ `t = unk84` (s16 → u16) → `lh` + `andi 0xffff`? or gcc emits `lhu`? The C semantics: reading an s16 field into a u16 var = truncation of the sign-extended value = the low 16 bits = the same as reading it as u16 → gcc can use `lhu` (zero-extend) → the insn changes from lh to lhu. ✗

Hmm.

Try: **the `x`,`y`,`z` route**: what if we ADD a copy of a u16 value in the else arm? No, extra insns.

Hmm, OK, what about this: **what if `u` is s16 and we use it in a way that requires the sign extension to be materialized at the copy** — e.g., `u` is compared or stored?

In the target, u is used only in the subtraction.

Hmm, hmm. What if we use a **different subtraction order**: `t = u - 1` where the 1 is... yeah.

What if the subtraction is `t = -1 + u`? Same.

What if `t = u + (-1)`? Same.

OK. Let me try the idea of making the copy's source a **constant-zero-extended** value by using the fact that gcc's `lhu`...

Hmm, actually — hold on!! What about `x = unk6` (u16) → `lhu a2,6(s0)`. And the target's `move v1,v0`... no, v0 is the lh result.

Hmm OK.

Let me try ANOTHER structural idea: **make the `u = t` copy be a copy of a value that is NOT a register but the result of an expression that gcc materializes as a copy**.

For example: `u = t` vs `u = (t)` vs `u = +t` vs `u = t * 1`...

What about `u = t + 0` where 0 is `(s32)(s16)0`? tree folds.

What about `u = t - 0`? folds.

What about `u = t ^ 0`? folds.

What about `u = t | 0`? folds.

What about `u = ~(~t)`? folds.

What about `u = t >> 0 << 0`? folds.

What about `u = (t, t)`? comma → folds to t.

What about `u = t ? t : 0`? → COND_EXPR → gcc generates a branch or cmov → not a copy.

Hmm, what about `u = t` where t is a `volatile`... no.

What about **the `<<16>>16` trick**: `u = (s16)t` → hmm, `(s16)t` is a truncation → sign_extend.

What about `u = (u16)t` → zero_extend → andi.

What about `u = (u32)(u16)t` → same.

Hmm, what about `u = (s32)(s16)t`? → sign_extend:HI → sll/sra.

Hmm, what about `u = (s32)(u16)t` → zero_extend → andi. (c4)

So the andi and the sll/sra are the only conversions.

**What if the ANDI could be avoided because gcc knows the value fits?** `andi v0,v0,0xffff` is emitted because the truncation is needed. gcc 2.7's combine: `(zero_extend:HI t)` where t's bits 16-31 are unknown → emits `andi`. But if the SOURCE is a QImode pseudo (i.e., t is declared u16!), then the conversion u16→s32 is a zero_extend of a QImode reg → gcc's expand does `zero_extend:HI (reg t)` where t is QImode → combine knows the reg holds only 16 bits → the extension is free! gcc's `zero_extend` for a QImode source: `(zero_extend:HI (reg t))` → combine's rule: "if the operand is a QImode reg, the zero extension is a no-op" → combine folds it to a plain copy!

YES. That's the classic gcc behavior: converting a QImode pseudo to SImode is FREE (the reg already holds the zero-extended value) — gcc 2.7 handles this in expand: `convert_to_mode(SImode, qmode_reg)` → since the pseudo's mode is QImode, gcc's `extend_mode`/`sign_extend`... Actually gcc's convert.c:

```c
    case SImode:
      ...
      if (GET_MODE (x) == QImode) return x;   /* zero extension of an unsigned narrow value is free */
```
Hmm, more precisely gcc's `convert_to_mode`:
```c
	  /* If we are converting from a narrow unsigned mode to a wider
	     mode, the conversion is a no-op if the value is in a register
	     of the narrow mode (the high bits are zero). */
```
In gcc 2.7's convert.c:
```c
    case DImode: case SImode: case TImode:
      ...
      if (GET_MODE (x) == QImode || GET_MODE (x) == HImode)
	{
	  if (unsignedp) return x;   /* zero extension is free */
	  ...
	}
```
Hmm, roughly: `convert_to_mode(SImode, x)` where x is a QImode REG → the value is already zero-extended in the reg → free (returns x). YES — gcc does this for registers in a narrower mode.

So: if `t` is declared **u16** and `u` is declared **s32**, then `u = t` is a FREE zero-extension → a plain copy → but a plain copy → cse kills it. ARGH.

Hmm, but wait: at cse time, is the RTL `(set u (reg t))` (a plain copy)? If the conversion is free, gcc's expand emits `(set u (reg t))` → plain copy → cse propagates. ✗

Hmm, unless the conversion is NOT free at cse time but becomes free later. Hmm.

BUT: the point is that for the zero_extend to fold to a copy, the SOURCE must be a QImode reg. So:
- `t` declared u16 (QImode reg) — but then the load `lhu` not `lh`. ✗

Hmm, hmm. Unless the load is `lh` and t is u16: `t = unk84` where unk84 is s16 and t is u16 → truncation → gcc emits `lh` + `andi`? or `lhu`? The C semantics of assigning an s16 to a u16: truncation to 16 bits, reinterpreted as unsigned → the value = the low 16 bits of the sign-extended value = the same bits as the memory → gcc can load with `lhu` (zero-extend) → the insn differs (lhu vs lh). ✗

Hmm, BUT what if we force `lh` and then the truncation? `t = (u16)(s16)unk84` — same semantics, gcc picks lhu.

What if the value is loaded as s16 into an s32 var and then truncated to u16 into another var? → `lh` then `andi`. ✗ (extra insn)

OK OK OK. Let me step back and consider: maybe the correct answer for 80182ED4 is that it's a WALL (like func_8017FBCC and func_80189750 in other shards — both are `pin` items with the same "copy must survive" structure, and both were WALLed!).

Given: func_8017FBCC — WALL combine-copy-merge; func_80189750 — WALL cse-copy-merge. Both are pin items where the copy is the issue. So 80182ED4 is likely also a WALL. But the brief says each item was walled before with too few tries, so I should try new moves.

Let me try a few more creative ones and then record a WALL if needed. But first, let me make sure I use my time well across 4 items.

Let me try these quickly:
1. `u` as u16 with the source being an s32 whose value gcc knows is small: what if the copy source is `(u16)t` where t is the result of `t & 0xFF`? no.

2. **What if `u` is a u16 and `t` is a u16, and the copy is `u = t` where t is the QImode reg?** → plain copy → cse.

3. **What if we make the copy's source a QImode pseudo by loading into a u16 var, but keep the `lh`?** `u16 t16; t16 = unk84;` → gcc emits `lhu`. Hmm, does it? The field is s16; assigning to a u16 → truncation → gcc's expand: `expand_assign` → the RHS is a MEM of QImode mode → truncate to HI → the load becomes QImode with zero extension → `lhu`. So yes, `lhu`.

Hmm! But hold on: what does the TARGET's `lh v0,132(s0)` imply? The target loads unk84 as s16 → sign-extended. So t = -32768..32767.

4. **What if we don't need the copy to be of `t` but the whole else-arm is restructured so that the `or v1,v0` copies something else that happens to be v0?**

In the target, at 80d8 v0 = the lh result. What if our version has v0 = the lh result too, and the copy is of v0. Same thing.

Hmm.

5. **What if we introduce the copy as `u = t` but with `t` being the *address* or something...** no.

6. **What if the copy is `u = t` where u is a `float`?** The target is integer MIPS with FPU? `func_80182ED4` — the target has no FPU insns. A float copy would need a move between FP regs. ✗

7. **What if the copy is `u = t` where u is declared `s32` but the assignment is inside a `for` loop or has some other structure?** Hmm.

Let me try a couple of these empirically anyway — cheap. And let me also try the "known range" idea: what if we make `t` an s16 var and copy `u = t` where u is s32, and t is loaded via `lh` into a QImode reg? The load `lh` into a QImode pseudo: gcc's mips `lh` insn writes the full 32-bit reg (sign-extended). The pseudo is QImode → gcc treats the reg as holding a 16-bit value (high bits undefined). Then `u = t` (QImode → SImode) → SIGN extension (t is s16) → `sll/sra`. ✗ (that's c2-like)

Hmm, but what if t is a **u16** var loaded via `lh`? To force `lh` we'd need the field to be read as s16 and then truncated to u16 → gcc uses lhu. ✗

Hmm, so the sign-extension source is unavoidable.

WAIT. What about the **sign extension being free**? If t is an s16 QImode pseudo whose reg was set by `lh` (which sign-extends), then `u = t` (s16→s32) = sign_extend:SI(t). gcc's convert.c: `convert_to_mode(SImode, x)` where x is QImode and the mode is signed → `sign_extend(SImode, x)` → `(sign_extend:SI (reg t))`. Then combine: does it know that the reg already holds the sign-extended value? combine's rule (gcc 2.7 combine.c):

```c
    case SIGN_EXTEND:
      ...
      /* If we know that the value is already sign extended, ... */
```
Hmm, gcc 2.7's combine has in `simplify_expr`:
```c
    case SIGN_EXTEND:
      if (GET_MODE (x) == mode) return x;
      ...
      /* Do not change the mode if the operand is a register whose mode
	 is already sign extended... */
```
Hmm.

Actually! gcc's `sign_extend` in convert.c:
```c
rtx
sign_extend (machine_mode mode, rtx x)
{
  int wordsize = GET_MODE_BITSIZE (mode);
  ...
  if (GET_MODE (x) == mode) return x;
  ...
  /* If we know that the value is sign extended already, ... */
  return gen_rtx_SIGN_EXTEND (mode, x);
}
```
Hmm no special case.

BUT gcc's expand.c `extend_mode`/`extend_split`...

OK. Empirical time. Let me try:
- c5: `s16 t16; s32 u;` with `t16 = unk84; u = t16;` — but t16's load is `lh` (QImode) and u = t16 → sign_extend:SI.

Hmm wait: gcc's convert_to_mode(SImode, qmode_reg):
```c
    case SImode:
      ...
      if (GET_MODE (x) == QImode || GET_MODE (x) == HImode)
	{
	  /* Sign extension is needed */
	  return sign_extend (mode, x);
	}
```
and sign_extend(SImode, x) where x is QImode:
```c
  if (GET_MODE (x) == QImode) ...
```
Hmm.

Actually, gcc's convert.c has this important function:
```c
/* Return an rtx for the conversion of X to mode MODE... */
rtx
convert_to_mode (machine_mode mode, rtx x)
{
  ...
  switch (mode)
    {
    case SImode: case DImode:
      if (GET_MODE (x) == QImode || GET_MODE (x) == HImode)
	{
	  ...
	  /* Sign extend */
	  return sign_extend (mode, x);
	}
```
and
```c
rtx
sign_extend (machine_mode mode, rtx x)
{
  int wordsize = GET_MODE_BITSIZE (mode);
  if (GET_MODE (x) == mode) return x;
  ...
  /* If X is a constant... */
  ...
  return gen_rtx_SIGN_EXTEND (mode, x);
}
```

Then combine would need to fold `(sign_extend:SI (reg t))` where t is QImode → but combine knows t's mode is QImode! In combine, the operand of a SIGN_EXTEND with a QImode reg... gcc's combine has this rule (combine.c, `simplify_expr` case SIGN_EXTEND):
```c
    case SIGN_EXTEND:
      ...
      /* If the operand is a narrow reg, the extension is a no-op if the
	 reg already contains the extended value... */
```
Hmm — gcc has `extend_mode`...

Honestly: gcc 2.7 mips DOES have the `move`/`movr` handling where a QImode pseudo's register, when used in SI mode, requires an explicit sign extension UNLESS the pseudo was set by `lh`/`lb` (gcc tracks this with the "move" clobber attribute? no).

Hmm — actually gcc's mips has a pattern:
```
(define_insn "lh"
  [(set (match_operand 0 "register_operand" "=r,m")
	(match_operand 1 "mem_operand" "m"))
   (use_clobber (match_operand 3 "register_operand" "=r"))
   (set_attr_attr "move" "type,load_use,clobbered")]
```
The `use_clobber` of $1 is for the sign extension when the loaded value is used as a byte/halfword — gcc's `lh` loads into the register with sign extension, so no clobber needed... but gcc's mips "lh" pattern actually is:
```
(define_insn "lh"
  [(set (match_operand 0 "register_operand" "=r,m")
	(sign_extend:HI (match_operand 1 "mem_operand" "m")))]
```
Hmm.

Let me just TEST c5. And also test:
- c6: `u` as u16, but with the source `t` being `u16` (so the copy is same-mode, plain) — no.

Let me write c5 and also c6 = the "u16 t16" variant where the load is lhu (accepting the lhu/lh difference — no, that breaks the load).

Hmm.

OK, let me consider the time budget: I've spent ~35 min total. 80182ED4 is taking long. Let me try 2-3 more quick variants for 80182ED4, then move to 8018302C and 8017E6EC, and come back.

Actually — HOLD ON. New idea! **What if `u` is declared as `s32` but the copy is `u = t` where the copy's RHS is a QImode reg (u16 var) — and we make the FIELD load produce a u16 var while STILL emitting `lh`?**

The target's `lh v0,132(s0)` — what if in our C, `t` is `u16` and the field is `s16`? gcc picks `lhu`. But what if we FORCE `lh` by writing `t = (s16)unk84` into an s16 var and then... no.

What if we make the copy `u = t` where t is s32 (lh) and u is s32, but we ALSO make the copy's source be a QImode by...

Hmm, hmm: what if we do the copy in TWO steps:
```
u16 t16;
s32 t, u;
t = unk84;         /* lh → v0 */
t16 = t;           /* truncation → andi 0xffff */
u = t16;           /* QImode → SImode: zero extension is FREE → plain copy */
```
→ `lh v0` + `andi v0,0xffff` + `or v1,v0`. Extra andi. ✗

What about:
```
u16 t16;
s32 u;
t16 = unk84;       /* lhu! (if t16 is u16) — changes the load */
u = t16;           /* free zero extension → plain copy → cse */
```
✗ (lhu + cse).

Hmm.

What about using `x` (u16, from lhu) as the copy source? `u = x` where u is s32 and x is u16 → the zero extension is free → plain copy → cse. ✗

OK, I think the fundamental blocker is cse propagating plain copies.

**Let me check: does gcc 2.7's cse really propagate? Let me test empirically with a trivial case!** Actually, I have evidence: our current win.c with `u = t; t = u - 1;` produced `addiu v0,v0,-1` — so yes, propagated.

Hmm, but hold on!! What if the propagation happened at COMBINE (not cse)? Combine's "copy elimination" (combine removes a copy whose dest has one use). If it's combine that eliminates the copy, then a copy that combine CAN'T eliminate would survive!

Combine's copy elimination requires the dest to have a single use and the source to be "simple". In our case u has one use (`t = u - 1`).

Hmm, in the target, u also has one use. So why wasn't it eliminated there? Because at combine time u's RHS was `(plus t (reg 0))` → combine's copy-elimination check might reject it because the RHS isn't a plain reg.

So: **if we can get the RHS to be a non-reg, non-constant expression that combine later turns into a plain reg copy, the copy survives!**

Candidates for "non-reg RHS that becomes a copy":
- `(plus t (reg 0))` — the pin ✗
- `(zero_extend:HI t)` where t is a QImode reg → combine folds the extension away (free) leaving `(set u t)`... but that happens at expand time (before cse!). Hmm — actually if the conversion is free at expand time, the RTL is already `(set u t)` at cse time → cse propagates ✗.
- `(zero_extend:HI t)` where t is an SImode reg → the extension is NOT free → the RTL is `(set u (zero_extend:HI t))` → cse doesn't propagate (it's not a reg copy) → combine then... combine would fold the extension into the USE (as in c4) → the copy dies. ✗ (unless combine can't fold it into the use).

Hmm! So the question is: why did combine fold the zero_extend into the use in c4, and would it in other cases?

combine folds `(plus (zero_extend:HI t) -1)` → it would need the andi anyway. It replaced the copy with the extension in the use, and the extension got its own... no, the andi was in v0 (t's reg).

Hmm, in c4, the copy `u = (u16)t` was eliminated and the use became `(and t 0xffff) - 1` → gcc computed `andi v0,v0,0xffff` (in t's reg, since t's old value is dead after) then `addiu v0,v0,-1`. So the copy was eliminated by folding into the use.

To prevent that, the use must not be foldable with the extension, OR the source must remain live.

**IDEA: make the source `t` still live after the copy!** If t is live at the use, then combine can't overwrite t's reg with the extension. But the copy's RHS is still foldable into the use: `(plus (zero_extend:HI t) -1)` → `andi v1,v0,0xffff; addiu v0,v1,-1`? That's 2 insns with the andi in v1 — still has the andi. ✗

The andi is the problem: the target has no andi.

**So we NEED the extension to be a no-op.** Which needs the source's high bits known zero. Which needs the source to be a QImode reg (then gcc's conversion is free) — but then the RTL at cse time is a plain copy.

UNLESS: the source is a QImode reg but the conversion is NOT free at cse time because gcc doesn't know the reg's mode... Hmm, gcc's convert_to_mode DOES know: `(reg t)` with mode QImode → converting QImode→SImode: gcc's convert.c:

```c
    case SImode:
      ...
      if (GET_MODE (x) == QImode) 
	  return x;   /* ??? */
```
Hmm — actually! In gcc, when you assign a QImode value to an SImode variable, gcc's `convert_to_mode(SImode, qmode_rtx)`:
```c
	  /* Changing a QImode to SImode is a zero extension if the value
	     is unsigned, sign extension if signed.  But if X is a
	     register (pseudo) of QImode mode, the value in the register is
	     already zero-extended (gcc keeps narrow values in registers
	     zero-extended? no, it keeps the value in the low bits with
	     the high bits undefined). */
```
gcc's convention: a pseudo of QImode mode holds a 16-bit value in the low bits, high bits UNDEFINED. So converting QImode→SImode requires zero/sign extension → NOT free.

Hmm! But then how does gcc 2.7 handle `u16 x; s32 y = x;`? It emits `andi` or `lhu`+... Actually gcc's `zero_extend` for a register: gcc's convert.c:

```c
    case SImode:
      ...
      if (GET_MODE (x) == QImode || GET_MODE (x) == HImode)
	{
	  ...
	  /* If we are converting from a narrow unsigned mode, we can
	     just use the value as is IF it is already in a register
	     (the high bits are undefined though!) */
```
Argh.

GCC's actual rule (from gcc/convert.c, gcc 2.7):
```c
    case SImode:
    case DImode:
      if (GET_MODE (x) == QImode || GET_MODE (x) == HImode)
	{
	  rtx extended = extend_mode (mode, x, GET_MODE (x), 0, 1);
	  ...
	}
```
Hmm.

But I recall gcc has an optimization in `convert_to_mode`:
```c
	  /* If we are converting from a narrow mode to a wider one and
	     the value is in a register of the narrow mode, we can just
	     use it, since gcc guarantees the high bits are... */
```
No, gcc does NOT guarantee that.

Hmm, but empirically, in gcc, `u16 x; s32 y; y = x;` typically compiles to `move` (or) with NO andi! Because gcc's `expand_assign` for a narrow-to-wide assignment emits `(set (reg y) (zero_extend:HI (reg x)))` and combine's rule: "if the operand is a QImode register, the zero extension is a no-op" — YES, gcc's combine has:

```c
    case ZERO_EXTEND:
      ...
      /* If the operand is a narrow reg, the extension is a no-op ... */
      if (GET_MODE (x) == QImode) return x;  /* the reg holds the value in the low bits, but the high bits are undefined... */
```
Hmm, gcc's combine.c actually has (in `simplify_expr`):
```c
    case ZERO_EXTEND:
      if (GET_MODE (x) == mode) return x;
      ...
      /* If we are zero extending a value that is already zero extended
	 (e.g. a QImode register), ... */
```
I believe gcc 2.7 has:
```c
	  /* Change (zero_extend:SI (reg:QI)) to the reg itself, since
	     the value in a narrow register is already zero extended
	     ... no */
```

OK, EMPIRICAL. Let me just try:

c5:
```c
void func_80182ED4(s32 arg0) {
    s32 t;
    u16 u;
    s32 v;      /* hmm */
```
Hmm, let me design c5 as: the copy source is a u16 var (QImode reg) holding the value, and the copy dest is s32.

```c
    u16 t16;
    s32 u;
    t16 = ((Unkstruct_80182ED4 *)arg0)->unk84;   /* lhu (unsigned read) */
    u = t16;                                      /* zero extension */
```
→ but the load is lhu, not lh. ✗

Hmm, what if we read it as s16 into an s32 (lh) and then narrow to u16 (andi) — extra insn ✗.

OK, what if the copy source is the result of `x = unk6` (a u16 field read with lhu)? Then the value is 0..65535, and the copy `u = x` (u16 → s32) → if gcc treats the QImode→SImode conversion as free, we get a plain copy (cse ✗); if not free, we get `andi` or `lhu`+zero.

Hmm, `lhu` already zero-extends, so `u = x` where x is u16 → gcc would just use x's reg (the lhu result is already in the right form) → a plain copy → cse ✗.

I keep hitting the same wall.

**DIFFERENT STRATEGY — accept a PARTIAL?** The result column allows "PARTIAL:<kinds still kept>" — that's for when the score is 0 while keeping some levers. Not applicable (we want to remove the pin).

**Let me try: does the `or` copy survive if `u` is used in a STORE?**

Actually, hold on! Let me revisit: in c4 (u16 u), the andi was in v0 (t's reg) and the addiu read v0. So the copy was folded away. But what if `u` is used TWICE — then combine can't fold the extension into a single use and must materialize the extension at the copy → `andi v1,v0,0xffff`? That still has the andi.

Hmm, unless the extension is free (QImode source).

OK, let me try to settle the "is QImode→SImode free in gcc 2.7" question empirically with a tiny test. I can compile a small C file with the project's toolchain and look at the asm! That's fast and decisive.

Let me find the compile command. The toolchain is tools/bin/gcc-2.7.2-cdk. Let me check how delever_search compiles a body — it probably uses a specific command. Let me look for the compile invocation.

Actually, tools/cc1_dumps_tu.sh might show it. Let me look at delever_search.py's compile function.

Let me grep for the gcc invocation.

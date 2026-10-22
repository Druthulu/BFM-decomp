---
ts: 2026-10-21T23:58:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YryB9EtZmR3NzaxdkWjI
---
d1/d2/d3 collapse to 26 insns — much worse (gcc folded everything, e.g. `now & 0xFF` folded to the lbu). So `+ 0` IS folded and worse.

d4/d5/d6 ≈ 18, similar to c1's 17.

The fundamental problem: gcc dissolves the copy.

Let me think about the "opaque copy" differently. What if the copy is made opaque by using a **different variable for `now` that's assigned in a way that gcc can't propagate**?

IDEA: what if `now` is assigned the packed read and then `r = now` where `now` is modified later? Not possible.

IDEA: **Use a `volatile`?** Not allowed (barrier lever, and kinds=pin only — adding a barrier would be adding a lever → forbidden).

IDEA: **Make the copy via a pointer dereference?** memory ✗.

IDEA: **Make the copy survive by having the source be a function call result?** no.

Hmm. Let me revisit the assumption that the target's `move a2,a3` is `addu a2,a3,$0` (funct 0x21). Let me verify the encoding by decoding the target's word: 0x00e03021. Yes funct=0x21=addu, rs=7(a3), rt=0($0), rd=6(a2) → `addu a2,a3,$0`.

And `move t0,a0` = 0x00804021: rs=0(a0), rt=0($0), rd=8(t0), funct=0x21 → `addu t0,a0,$0`.

Both are "addu rd,rs,$zero" — which in gcc's MIPS machine description IS the "move" instruction (move_expanded or the `move` insn pattern). So a plain copy also emits `addu rd,rs,$zero`! Let me double check gcc's mips.md:

```
(define_insn "move"
  [(set (match_operand:SI 0 "register_operand" "=d,d")
	(match_operand:SI 1 "register_operand" "0,d"))]
  "addu\t%0,%1,%zero")
```
Hmm, in gcc 2.7's mips.md, I believe the move insn is:
```
(define_insn "move"
  [(set (match_operand:SI 0 "register_operand" "=d,d")
	(match_operand:SI 1 "register_operand" "0,d"))]
  "addu\t%0,%1,%zero")
```
Yes! gcc 2.7's MIPS move IS `addu rd,rs,$zero`. So a plain copy produces exactly 0x00e03021.

So the target's copies could be plain copies — the question is only whether gcc 2.7.2's cse dissolves them.

And gcc 2.7.2's cse DOES dissolve them (my c1 shows the copies gone).

So we need to prevent cse from dissolving the copy while keeping the RTL a plain copy.

**How does gcc 2.7's cse decide?** In cse.c, the function `find_duplicate_insn` handles the case where the insn is a copy: there's the "equiv" mechanism. Let me recall the specific condition. gcc 2.7 cse.c:

```c
	  /* If this is a copy of a reg, record the equivalence.  */
	  ...
	  if (GET_CODE (src) == REG && GET_CODE (dst) == REG
	      && ... )
	    {
	      ...
	      /* Don't record the equivalence if the source is a hard reg
		 and ... */
	    }
```
Hmm.

I recall there's a specific rule in gcc 2.7's cse.c:
```c
	  /* If this insn is a copy of a hard reg, and the hard reg is
	     modified ... */
```

Hmm.

ALTERNATIVE STRATEGY: Make the copy be in a form that gcc 2.7 does NOT recognize as a copy but still generates `addu rd,rs,$zero`. 

What RTL generates `addu rd,rs,$zero` besides a copy? 
- `(set (reg) (plus (reg) (const_int 0)))` → combine folds it to a copy (and then cse may dissolve it).
- `(set (reg) (plus (reg) (reg $0)))` → not folded by combine (reg isn't a const) → generates `addu rd,rs,$zero`!! And cse sees a `plus`, not a copy → doesn't propagate ✓✓✓

So the pin works because $0 is a REG. We need a REG whose value is 0 but which gcc doesn't fold.

In real C, a variable in a register with value 0... gcc would have to load it.

Hmm, UNLESS the register is one of the ARGUMENT registers! Like: what if the function used an argument that is 0? No.

Hmm, what about `h = arg0 + 0` where `0` is... 

**AH WAIT!!!** What about the `dead[2]` array — the unused local! What if the original source used `dead[0]` as the zero source? `h = arg0 + dead[0]` → that loads memory ✗.

**IDEA**: What if we exploit that gcc 2.7 does NOT fold `x + 0` when the operand is a **CONST_INT of a different mode/size**? e.g. `x + 0L` where long is 32-bit — same.

Hmm, in gcc 2.7, is there a case where `plus` with 0 is not folded? YES: when the constant is not an integer constant but a **symbolic constant** or when the mode is not SI.

Hmm, what about `x + 0` where 0 is a `float`? → float arithmetic ✗.

**IDEA**: what if the value 0 comes from a **cast of a nonzero constant to a narrower type**? e.g. `(u8)256` → 0. gcc folds `(u8)256` → 0 at compile time ✗.

**IDEA**: What if the zero is `arg1 - arg1`? → subu insn ✗.

**IDEA**: What if the zero comes from `now & 0`? → `and now, 0` → gcc's combine folds `and x, 0` → 0 → then `plus now, 0` → folded ✗.

**IDEA**: What if the addend is a **variable that gcc knows is 0 but keeps in a register**? gcc 2.7 has no such thing for locals.

Hmm!!! WAIT. What about the **`$0` register being available because the source uses a variable named `zr` that is a `register` variable**... that's the pin, forbidden.

Hmm hmm. What about... **an `asm` statement**? Forbidden (pin/asm lever).

OK. So maybe this item is a genuine WALL: the "$0-ADD OPAQUE COPY" is a real lever (RC-12) that the project's own documentation calls a lever. The brief's kinds for this item is "pin", and the lever here is the $0 pin. If real C can't produce the opaque copy, it's a wall.

But hold on! Let me reconsider: maybe a DIFFERENT C spelling produces an opaque copy that gcc doesn't dissolve. Let's think about gcc 2.7.2's cse more carefully. 

The cse pass's copy propagation: in cse.c, `find_duplicate_insn` has:

```c
	  /* If this is a copy, see if we can record the equivalence.  */
	  if (GET_CODE (src) == REG && GET_CODE (dst) == REG
	      && REGNO (dst) != REGNO (src))
	    {
	      ...
	      /* Record the copy in the equiv table */
	      ...
	    }
```
and the propagation happens in `cse_insn` when looking up a reg: `reg = equiv_reg (reg, insn)` hmm.

Actually, I remember gcc 2.7's cse.c has:

```c
/* Return true if we should not do the copy propagation for this insn... */
static int
hi_forbidden_reg_p (...)
```
no.

Let me approach empirically once more, with a targeted idea:

**IDEA**: What if the copy's SOURCE is a register that is ALSO a call argument or has another use that makes it "not copyable"? cse's equiv propagation replaces uses of dst with src — that's always valid if src isn't modified. 

**IDEA**: What if dst (r) is used BEFORE the copy? Then the copy is dead... no.

**IDEA**: What if the copy is inside a conditional block and the use is in a different block? gcc 2.7's cse equiv table — I believe the equiv is recorded with a "life" (the insn) and is invalidated when the source reg is set OR at the end of the function. It does cross blocks.

Hmm, BUT: gcc 2.7's cse has a special case — it does NOT propagate a copy if the copy is in a block that doesn't dominate the use. But the equiv table is built in block order, and uses in LATER blocks get the equiv.

Hmm, BUT: there's a crucial detail! gcc 2.7's cse `equiv_regs` records the equivalence with `life` = the insn. Then in `cse_insn`, when a reg is looked up:
```c
	  /* If we have an equivalence, use it. */
	  ...
	  if (equiv_reg (reg, insn)) ...
```
Hmm, and `equiv_reg` checks that the equivalence is still valid — the source reg hasn't been set since.

So it crosses blocks.

**IDEA**: Force the source to be "modified" between the copy and the use! For `r = now`: if `now` were SET again after the copy, cse's equiv would be invalidated → the copy survives! But `now`'s value must stay the same...

Hmm, what if `now` is set twice with the same value? e.g.
```c
now = D_80078EB0 | (D_80078EB1 << 8);
r = now;
now = D_80078EB0 | (D_80078EB1 << 8);   /* recompute */
```
That's an extra load ✗ (the target computes the OR once).

Hmm, but wait: would cse even CSE the two identical expressions? Yes (cse would merge them) → back to square one.

Hmm, what if the second assignment is `now = now;`? → cse would remove it.

OK. What about **making the copy's source a value that gcc keeps in a hard register**? Then the equiv propagation would still work (it substitutes the hard reg).

Hmm.

**RADICAL IDEA**: What if the copy is generated not by an assignment but by the **structure of the expression**? E.g., the target's `move a2,a3` could be the "copy" that gcc inserts when passing an argument or when merging branches! 

For example: `r = now` where `now` is in a3 and the merge point needs r in a2 → gcc inserts a copy at the merge (parallel copy). Hmm! Actually yes: if `r` and `now` are the same value but in different blocks, gcc's "jump" pass (cross-jump) may insert copies.

Hmm, so what if the source is:
```c
now = D_80078EB0 | (D_80078EB1 << 8);
if (cond) {
    r = now;
    ...
} else {
    r = now;
    ...
}
```
Then r is set in both branches with the same value → gcc's jump/cross-jump would merge them → the copy might be inserted at the merge point or in each branch. Hmm, but that would give TWO copies (one per branch) or one copy before the branch.

Hmm! Actually if both branches assign `r = now` and gcc's "cross_jump" merges the identical blocks, the copy would be hoisted before the branch → `move a2,a3` before the branch ✓ (that's exactly where the target has it: at cb4, before the branch at cc4!).

Hmm, but wait: in the target, `move a2,a3` is BEFORE the branch, and the branch is on `r & 0xFF` — which uses r (a2) — so the copy must precede the branch ✓.

But hold on: the current source has `r = now + zr` at the TOP, before the branch. So the copy is before the branch in the source too. And the pin makes it opaque.

If I write `r = now` at the top, cse dissolves it.

Hmm, so let me think about WHY cse dissolves it: because `now` is a pseudo whose value is known. If `now` were NOT a pseudo but a hard register... 

**!!!! IDEA !!!!**: What if `now` is never assigned to a variable at all, but the packed read is used TWICE in the source? Then gcc would CSE the two identical reads into one value in a3 (a pseudo), and the two uses would read a3. Hmm.

Hmm, what if the packed read appears twice and gcc's CSE creates the value in a3 and then... the two uses are both a3. Then `r` would be a3. ✗

OK OK. Let me think about "what does the original source look like" from the target's structure once more:

```
or a3,v1,v0       ; a3 = packed
move a2,a3        ; a2 = packed (copy)
andi v0,a2,0xff
```
The `or` writes a3 and the copy writes a2. For the ORIGINAL compiler, this might have been:
```c
u32 now = D_80078EB0 | (D_80078EB1 << 8);
u32 r = now;
```
with the original compiler keeping both in registers (no copy propagation).

For gcc 2.7.2, the project's answer was the $0 pin. Is there another way?

**IDEA: use `volatile`?** Not allowed (that's a barrier lever). But hmm — what does the constraint say exactly? "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." kinds = pin. So barrier/launder/keepalive are not in the row kinds... but "no new lever of any kind" forbids adding them. So no volatile.

Hmm.

**IDEA: What if the copy is `r = now` where `now` is `u32` but `r` is `u16`/`u8`?** → truncation insn ✗.

**IDEA: What if we make `now` and `r` differ in a way that produces the same code: e.g., `r = now` where now is `u32` and r is `u32`, but the ASSIGNMENT is in a context where gcc must materialize the value into a specific register because of the `& 0xFF00` use?**

Hmm! Here's a thought: the target's `andi v1,a3,0xff00` reads a3 (now). And `andi v0,a2,0xff` reads a2 (r). If r and now were the same register, both would read the same → but they'd have different masks, so the code would still work.

Hmm, what if `now`'s use is `now & 0xFF00` and gcc's "combine" would fold `r & 0xFF` (where r = now = D_80078EB0 | D_80078EB1<<8) into `D_80078EB0`? THAT's the key effect the comment mentions: "This is also why `andi $v0,$a2,0xFF` survives: combine cannot see through the opaque copy to fold the low byte back to the D_80078EB0 lbu."

So in my c1, `r & 0xFF` got folded to the lbu (D_80078EB0) → the code is much shorter (42 vs 45 insns).

So the opaque copy has a real semantic effect on the code.

Hmm, so we need gcc to NOT fold `(now) & 0xFF` to the lbu. That requires gcc to not see through the copy.

The `& 0xFF` folding: gcc's combine recognizes `(and (ior (lbu X) (lbu Y << 8)) 0xFF)` → `(lbu X)`. This is a "combine" pattern. For it to not apply, the value must be opaque.

So we need an opaque copy.

**!!!!!!!! IDEA !!!!!!!!**: What if the copy is made opaque by a **PLUS with a zero-valued expression that gcc keeps in a register because it's a *variable* whose value comes from an expression gcc can't fold**... but the value must be 0.

What if the zero comes from `arg1 & 0`? Hmm: `arg1 & 0` → gcc folds `and reg, 0` → 0 (combine rule) → then `plus now, 0` → folded ✗.

What if the zero comes from `(u32)arg1 - (u32)arg1`? → subu ✗.

What if the zero comes from a **memory load** of a global that's 0? → lw + addu ✗ (2 insns).

Hmm, so the ONLY way to get `plus(reg, reg)` is a register addend. And a register addend with value 0 must come from somewhere.

**!!!!!!!! IDEA 2 !!!!!!!!**: What about the **HI/LO address registers**? gcc computes `&global` as `lui`/`addiu` — the `addiu` has an immediate. Hmm.

**!!!!!!!! IDEA 3 !!!!!!!!**: What about `r = now + (D_80078EB0 - D_80078EB0)`? → subu ✗.

Hmm.

**!!!!!!!! IDEA 4 !!!!!!!!**: What about using the **low 16 bits of a pointer**: e.g. `r = now + (u32)(u16)&some_global`? → lui+andi+addu ✗.

OK so an opaque copy seems to require a register addend.

**!!!!!!!! IDEA 5 !!!!!!!!**: What if the copy's addend is a **variable that gcc keeps in a register because it is used in a call**? No calls.

**!!!!!!!! IDEA 6 !!!!!!!!**: What about a **function parameter** that we know is 0? The function has arg0, arg1. `r = now + arg1` ✗ (wrong value).

Hmm.

**!!!!!!!! IDEA 7 !!!!!!!!**: What about **`now` being a `u32` and the copy being `r = now` in a context where the compiler must keep both because `now` is modified in one branch**? Hmm, `now` isn't modified.

WAIT!!! What if we make `now` be modified — in a way that's semantically invisible? E.g., `now` is set to the packed value, and later in the source there's `now = now;`? cse removes that.

Hmm, what if the modification is in a DIFFERENT block that dominates... cse's equiv is invalidated when the source reg is SET (any set). So `now = X` anywhere after the copy invalidates the equiv for subsequent uses.

But the copy `r = now` must come BEFORE that set for the copy to be the one that survives... and the copy's use must be AFTER the set. Hmm! But then r's value (the old now) would be used after `now` changed — semantically wrong unless we re-set now to the same value.

Hmm, but if `now` is re-set to the same value, gcc's CSE would merge the two sets into one → the set disappears.

Unless the re-set is in a different block and cse doesn't merge across blocks... risky.

OK, let me consider: maybe I should treat this item as a WALL. But wait — the brief says PARTIAL is allowed: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". Since kinds=pin, PARTIAL:pin = the pin stays = the current orig = score 0. That's not a crack. But the format allows reporting PARTIAL. Hmm, but for a pin item, PARTIAL:pin is meaningless.

Hmm, hold on. Let me reconsider the problem once more.

**IDEA: what if `now` is not a variable but the packed read is computed into a variable `r` and the copy comes from the `& 0xFF00` structure?**

Let's think about what the target does:
- a3 = packed value (call it P)
- a2 = P (copy)
- uses of a2: `andi v0,a2,0xff` (r & 0xFF), `subu v0,a2,a1` (r - arg1), `or a2,v0,v1` (r = ...), `subu v0,a1,a2` (arg1 - r)
- uses of a3: `andi v1,a3,0xff00` (now & 0xFF00), `andi v0,a3,0xff00`

So the source's `r` is the copy (a2) and `now` is the original (a3).

What if the SOURCE were:
```c
u32 r = D_80078EB0 | (D_80078EB1 << 8);    /* r = a3 = P */
u32 now = r;                                 /* now = a2 = copy of P */
```
and then use `r` for the &0xFF00 terms and `now` for the &0xFF terms. I.e., swap the variable roles. Then:
- `now` (a2, the copy) is used with &0xFF ✓ (matches target's a2 & 0xff)
- `r` (a3, the original) is used with &0xFF00 ✓ (matches target's a3 & 0xff00)

And the copy `now = r` — will cse dissolve it? The equiv: now = r → uses of now replaced by r → then `now & 0xFF` becomes `r & 0xFF` → and combine folds `r & 0xFF` to the lbu ✗. Hmm, same problem.

The dissolve happens regardless of naming.

So we need the copy to be opaque.

**IDEA: what if we make the copy opaque by making the SOURCE of the copy a *register* rather than a pseudo?** In gcc, if the value lives in a hard reg (e.g., because it's a call argument or a specific hard reg), cse still propagates.

Hmm, hold on. Let me actually TEST whether gcc 2.7.2's cse propagates a copy at all! Maybe the dissolve in my c1 wasn't cse but something else (like the "nonzero_bits"/canonicalization in combine, or the jump pass). Let me test with a minimal case: does `r = now` produce a copy?

In c1's diff, mine has `or a2,v1,v0` then `andi v0,a1,0xff` — so the copy vanished AND `r & 0xFF` was folded to `a1 & 0xff`?? Hmm: mine[6] = `andi v0,a1,0xff` — that's arg1 & 0xFF (the comparison's right side). And the `r & 0xFF` disappeared entirely (folded into the lbu).

Right.

So in mine, `r` is the same pseudo as `now` (a2), and `r & 0xFF` folded to the lbu (D_80078EB0). Indeed the lbu result was in v0 (a2's value = the packed value... hmm, actually `or a2,v1,v0` computed the packed value into a2).

Hmm OK.

So cse propagated.

**TEST IDEA**: does gcc 2.7.2 propagate a copy when the source is a hard reg? Let me construct: `h = arg0` where arg0 is in a0 (hard reg at entry). In c1, h was in a0 → propagated ✓.

So gcc 2.7.2 propagates copies from hard regs too.

Hmm, so how did the project's own analysis conclude that `x = y + zr` (with zr = $0) is the only way? They said "neither cse nor combine can remove" — because `plus(y, $0)` is not a copy.

So: we need `plus(reg, reg)` in the RTL. The addend must be a register with value 0.

**!!!!!!!!!!!!!!!!!!!! IDEA !!!!!!!!!!!!!!!!!!!!**
What if the addend is the **zero register used as a scratch for a cast**? Hmm.

What about a **cast to a smaller type that gcc implements as a shift**: e.g. `(s16)x` → `(sign_extend (reg:HI) (reg:SI x))` → gcc expands to `sll tmp,x,16; sra tmp,tmp,16` → 2 insns ✗.

What about `(u16)x` → `andi` ✗.

What about `(u8)x` → `andi` ✗.

Hmm what about a **bit-field**: `x = y & 0xFFFF` → andi ✗.

**IDEA**: `(void)` cast → no-op.

**IDEA**: What if we use `y + (y == y ? 0 : 0)`? gcc folds.

**IDEA**: `y + (y - y)`: gcc's combine can fold `x - x` → 0? gcc 2.7's combine has a rule for `(minus x x)` → 0? I believe combine does NOT fold x-x to 0 (it's not valid for floats). For integers, gcc 2.7 might. Hmm, if it doesn't fold, we get `subu v0,a0,a0` + `addu t0,a0,v0` = 2 insns ✗.

OK.

**IDEA**: What if the addend is a **constant that gcc keeps in a register because it's used more than once**? E.g. if `0` were a variable assigned once and used in two places, gcc might keep it in a register — but it'd be a constant 0 → combine folds `plus(reg, const 0)` → ✗. Unless gcc keeps the const in a reg and the addition becomes `plus(reg, reg)`?? gcc 2.7's reload would put the constant 0 in a register (as a "pseudo" with a constant value) → the RTL would be `plus(now, pseudo_const0)` → combine might not fold it because the const is in a pseudo! Hmm!! That's interesting!

In gcc 2.7, a constant used in multiple places can be put in a register (via reload) — but usually gcc materializes constants inline (li). For `0`, gcc would use `move reg,$0` or just fold.

Hmm, but here's the thing: gcc's `combine` folds `plus(reg, const_int 0)` BEFORE reload. So the const is gone at RTL level. Unless the const is in a pseudo — but constants in pseudos come from reload (after combine).

Hmm, so the order: combine (folds +0) → cse → reload. So +0 never survives.

BUT: what if the zero is not a constant at RTL level? E.g. `y + z` where z is a variable → the RTL is `plus(y, z_reg)` → survives combine → reload loads z → `addu rd,rs,rz`. But z's value must be 0 at runtime, and loading it costs an instruction ✗.

UNLESS z is already in a register! Like an argument register that holds 0? No.

Hmm, hold on!!! What about **`arg1` or `arg0` being 0**? No.

OK, what about this: **`r = now` where the copy must be preserved because `now` is modified between the copy and the use, and the modification is semantically a no-op that cse can't remove**.

What if `now` is modified by a **store through a pointer**? e.g. `*(volatile u32*)&now = now`? That's a barrier ✗.

Hmm.

Let me now consider the OTHER possibility: maybe the *frame size* difference gives a clue. The target's frame is 8 bytes (the `dead[2]`). In mine, 16. Why? Because in mine, gcc needed an extra spill slot? Hmm, `h` might be spilled? Hmm.

Actually! Maybe in mine, the frame is 16 because `dead[2]` (8 bytes) + gcc allocated 8 more for... hmm.

Hmm, could it be that in mine, the `now`/`r` merge needed a stack slot? Unlikely.

Let me look at the c1 diff again: mine has `addiu sp,sp,-16` at insn 9 and `addiu sp,sp,16` at 39. Hmm, the frame setup is in the middle of the function?! That's bizarre. OH — maybe the diff alignment is just misleading (the target's `addiu sp,sp,-8` at index 0 was "inserted" at mine[0:0], and mine's `addiu sp,sp,-16` is at a different position).

Whatever. Let me now consider the time budget. I've spent ~1h15m on two items (and cracked none). I have 7 items. I need to be more efficient.

STRATEGIC DECISION: Let me handle the items where a plain lever-free rewrite might just work (some pins might be removable trivially), and record walls for the hard ones. Let me quickly try each remaining item with a straightforward lever-free rewrite and see the scores. That gives me results fast.

Remaining items: func_80181E64, func_80180480, func_800D2650, func_8003DF8C, func_8012944C (+ func_801415C0, func_800D0D7C pending).

Let me look at their sources now, all at once.

Let me first read the sources for func_80181E64, func_80180480, func_8003DF8C, func_8012944C.

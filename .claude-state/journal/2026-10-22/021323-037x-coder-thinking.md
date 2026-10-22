---
ts: 2026-10-22T08:13:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_oc1STFCAIGOMUmipwkWn
---
Interesting! t1: the copy from a PARAMETER was eliminated! So the "hard reg" rule doesn't prevent it — because at cse time, the parameter `t` is a pseudo? No — parameters are in hard regs. Hmm, but gcc 2.7 might have already copied the param to a pseudo. Actually, in gcc 2.7, function parameters ARE hard regs (a0) at the RTL level, but `t` in the C body is a pseudo? No — for a non-static function, the parameter is bound to the incoming register (a0) directly, so `t` IS the hard reg a0. Hmm, but then cse's rule "don't equate if one is hard and the other is pseudo" should have kept the copy.

But t1 shows the copy eliminated. Hmm! So either cse propagated it, or combine eliminated it.

Note t2: `u = (unsigned short)t` → andi + addiu: the copy was folded into the use (as in c4). And the andi is in v0 (a's reg, reused).

So combine eliminates copies whose source is a register. This is combine's copy elimination.

So: to keep a copy, the source must be something combine can't substitute into the use. In the target, the source at combine time was `(plus t (reg 0))` — combine's copy elimination requires the source to be a simple reg/constant.

Hmm! So maybe combine's copy elimination happened FIRST (before the plus-with-zero was folded) — i.e., combine saw `(set u (plus t (reg 0)))` and could NOT eliminate the copy because the RHS is not a simple reg. Then in a later combine pass, the plus-with-zero got simplified to `t`, but the copy elimination had already been decided? Hmm, combine runs repeatedly until stable, so the second pass would eliminate it.

Hmm. Unless the copy elimination has a rule that a copy whose RHS is a "plus with reg 0" is special-cased as a "move" that must be preserved (because the mips "move" pattern requires the plus form!).

AH HA! THAT'S IT! gcc's mips "move" insn pattern is `(set (reg) (plus (reg) (reg 0)))`. If combine simplified the RHS to a plain `(reg t)`, the "move" pattern wouldn't match... but there's also "movr". Hmm.

Hmm, but the observed target IS `or` = the "move" pattern with the plus form. So gcc kept `(plus t (reg 0))` all the way to RTL expansion!

So: the target's copy is `(set u (plus t (reg 0)))` and combine NEVER folded it. Why not? Because combine's rule for `(plus x (reg 0))` → x might not exist in gcc 2.7 (only CONST 0 is folded, and the tree level already folded const 0).

So the copy survives because the RHS is a plus with a hard-reg-0 operand — combine's copy elimination can't substitute a plus into the use (it would need `(plus (plus t 0) -1)` → combine could fold that to `(plus t -1)`... hmm, but then u's use would read t's reg and the copy dies).

Whatever — empirically, the pin keeps it.

**KEY QUESTION**: can I produce `(plus t (reg 0))` in plain C?

`(reg 0)` in RTL arises from... hmm! What about a MEMORY reference with a zero offset? `(mem (reg t) 0)` — that's a MEM, not a plus.

What about `t + 0` where the 0 is a `char` 0? → CONST.

Hmm, what if the zero comes from a **global variable of value 0 that gcc constant-folds**? → CONST.

What if the zero is a **parameter**? → `(plus t (reg a0))` → not reg 0.

Hmm.

What if the RHS is `(plus t (reg 0))` because of a **bit-field or a shift**? no.

OK so the pin is the only source of (reg 0).

Hmm, hold on. What about `u = t` where the copy elimination is prevented by a DIFFERENT reason: **combine's copy elimination requires the destination to have exactly one use and the source to not be live...** Let me test more variants:

- What if the destination `u` is live across a CALL? Then the copy can't be folded into the use (the use is after the call and u must be in a callee-saved reg → the copy becomes a real move). But the target's u is not across a call.

- What if the source `t` is live at the use? Then combine can't put the extension in t's reg... but for a plain copy it can still substitute.

Let me test more variants to find any that yields `or` + `addiu`:
a) `u = t;` where u is used in a store: `*(int*)p = u - 1;`
b) `u = t;` where u is used twice in different places.
c) `u = t;` where the copy is in a branch and the use after the join.
d) `u = t;` where t is a local loaded from memory (pseudo).
e) `u = t;` where the use is `u - 1` and u is ALSO used after.

Let me write these.

Actually, key insight from t4: `return u - 1 + u;` → `sll v0,a0,1` — gcc turned it into a multiply. Not useful.

Let me test the "two uses" case (b): if u is used twice, combine must materialize the copy? No — it can substitute the source into both uses.

The fundamental problem: combine eliminates copies by substituting the source.

**When can combine NOT eliminate a copy?** When the source's reg is needed elsewhere at the use point (i.e. the source is live and the use would clobber it). In our case: `t = u - 1` — the destination is t! So substituting u's source (t) into the use gives `t = t - 1` → that's valid (t's old value is read before being written). gcc does it (t1-like).

Hmm, but in the TARGET, gcc did NOT do that, because the source was `(plus t (reg 0))`.

So: to keep the copy, the RHS must be non-substitutable.

**What if the RHS is a MEM?** `(set u (mem (reg t) 0))` → a load, not a copy.

**What if the RHS is a `plus` of two regs?** e.g. `u = t + z` where z is another local → combine CAN substitute `(plus t z)` into the use → `(plus (plus t z) -1)` → folded to `(plus t (z-1))` → so the copy dies but the addend remains → `addu v1,v0,zreg`? Hmm, and the target needs `addiu v0,v1,-1`.

Hmm. Hmm!

**What if the RHS is a plus with a constant that combine can't fold because... the constant is 0?** combine folds `(plus x (const 0))` → x? Hmm, does it? In gcc's combine.c, `simplify_expr` for PLUS:
```c
      /* X + 0 is X.  */
      if (GET_CODE (y) == CONST_INT && INSN_P (insn) && ...)
```
Hmm — that rule is conditional on `INSN_P(insn)` and some flags; it might apply only in certain contexts.

But the tree level (fold.c) already folds `t + 0` → t, so the RTL never sees it. Unless the zero is hidden from the tree level, e.g. `t + z` where z is a variable assigned 0 — but then the RTL has a reg, not a const.

Hmm! But what if `z` is a variable whose value gcc CAN prove is 0 at that point (via copy propagation)? Then combine might fold `(plus t z)` → t → the copy dies.

OK, what if `z` is a variable that gcc CANNOT fold, but which lands in $0? Only a pin.

Hmm hmm.

**RADICAL: what if the copy's RHS is `(plus t (reg 0))` where the (reg 0) comes from an actual C-level zero that gcc materializes as a hard reg?** gcc materializes a constant 0 as `li $0, 0`? No, gcc uses the constant 0 inline (CONST_INT) or `move $x, $zero` for a copy.

Hmm, what about a **comparison** `t == 0`? That generates `(set (reg) (eq (reg t) (const 0)))` — the 0 is a CONST.

What about **`t & 0`**? folded.

What about a **switch on t** with cases? gcc generates a jump table or a comparison chain with CONSTs.

What about **`t >> 0`**? folded.

What about **a call to a function with a `0` argument**? The arg 0 → `move a0, $zero`? gcc passes 0 as `li a0,0`? Hmm! Actually gcc passes a constant 0 argument as `move $a0, $zero` (since `move` = `or a0,zero,zero`). Interesting but not a plus.

OK, I think for 80182ED4 the honest answer may be a WALL. But let me try ONE more idea:

**IDEA: `u = t` where the copy's RHS is a plus with a hard reg that ISN'T 0 — but the target's insn is `or v1,v0,$zero`.** Hmm, the target's `or v1,v0,$zero` IS the plus-with-reg-0 form.

So the ONLY way to get `or v1,v0` is `(plus v0 (reg 0))`.

Hmm, hold on! What about `(plus v0 (reg 0))` arising from a **`mem` with offset 0**? Like `(plus (mem (reg t) 0) ...)` no.

Hmm, what about gcc's "move" pattern also matching `(set (reg) (reg))`? Then a plain copy would give `or` too — but the copy dies before that.

**So the question becomes: how to keep a plain copy alive through combine.**

Let me test more cases empirically:
- The use is a store: `*(volatile int*)p = u;`
- u is used in a branch condition: `if (u) ...`
- The copy and the use are in different basic blocks with a call between.
- The source t is live at the use (used again after).

Let me test:
```c
int t7(int t) { unsigned u; u = t; if (t == 5) return u - 1; return t; }   /* t live at use */
int t8(int t) { unsigned u; u = t; return u - 1 + t; }                       /* t live */
```
Hmm, t4 was similar and got optimized away.

Let me test the "source live at use" case: `u = t; x = u - 1;` where t is used later. Then the copy can't be folded into the use (because the use's result would clobber t's reg)... no, the use's result goes to a different reg.

Hmm! Actually here's the thing: `t = u - 1` — the destination IS t (the source of the copy). If instead the destination were a NEW variable, then t could stay live and u could be folded... but the copy is still eliminable.

Let me test:
```c
int t8(int t) { unsigned u, w; u = t; w = u - 1; return w + t; }
```
Here t is live after. gcc would substitute u→t giving `w = t - 1; return w + t;` → same.

OK so plain copies are always eliminated by combine.

**CONCLUSION for 80182ED4**: to get `or v1,v0` we need `(plus v0 (reg 0))` → needs a hard-reg-0 addend → the pin. UNLESS the copy's RHS is a mode conversion that combine folds to a copy (needs known bits) — and the only known-bits case (u16 → s32) yields a plain copy (eliminated) or an andi.

Hmm, hold on: what about **u16 → s32 where the u16 reg is loaded with `lhu`**? The value in the reg is already zero-extended → the conversion is FREE → gcc's RTL would be `(set u (reg t))` → a plain copy → eliminated. But if gcc emits `(set u (zero_extend:HI (reg t)))` where t is a QImode pseudo, then combine's rule "zero_extend of a QImode reg is a no-op" → `(set u (reg t))` → copy → eliminated. ✗

Hmm, but WAIT: what if combine's rule is NOT applied and the zero_extend survives to RTL expansion, where the mips pattern for `(zero_extend:HI (reg))` emits `andi`? We saw t2 → andi. ✗

OK. So the copy in the target MUST come from `(plus x (reg 0))`.

Hmm, so how do we get (reg 0) without a pin?

**!!!!! IDEA !!!!!**: What about a **`(reg 0)` arising from the `$zero` register being used as a "hard register zero" in a `plus` pattern generated by gcc for something like `x + 0` where 0 is `REGNO 0` because of the `zero` used in `(mem (reg) 0)`?** no.

Hmm, what about **a `volatile` read of a zero**? no.

**What about `u = t` where t is `unsigned` and u is `unsigned` — same. What about `u = t` where the types differ in a way gcc implements as `(plus t (reg 0))`?** gcc never does that.

OK so 80182ED4 requires the pin. UNLESS...

Hmm, hold on. Let me reconsider the whole thing. What if the intended solution doesn't need the `or` copy at all? What if the `move v1,v0` in the target could come from a **different C construct** — e.g. the target's `u` might be a variable that's assigned in a way that produces `(plus t (reg 0))`...

Hmm, hmm! What about this: **`u = t` where the compiler generates the copy via the "move" pattern with the plus form because of a `+ 0` that survives the tree level**?

The tree level folds `x + 0` → x. But what if the 0 is not a literal but an expression the tree level can't fold, yet the RTL ends up as a constant 0? For example, `u = t + (0 & 0)` → folded. `u = t + sizeof(x)`? → const.

What about `u = t + (x ? 0 : 0)` → folded.

What about **`u = t + '\0'`** → const 0 → folded.

What if the addend is a **variable with a known-zero value that gcc turns into a CONST in RTL**? E.g., `u = t + z` where z is assigned 0 → the RTL is `(plus t (reg z))` with z a pseudo. Combine: does combine know z is 0? combine tracks constants set within the insn sequence! If `z = 0` is in the same basic block before the copy, combine's `known_zero(z)` might be true → combine folds `(plus t z)` → t → the copy dies. But if `z = 0` is in a DIFFERENT block, combine doesn't know → the copy survives as `(plus t z)` → `addu v1,v0,zreg` — but the target is `or v1,v0,$zero` (the plus with reg 0). ✗ (also an extra insn for z's load? no, z=0 → `move zreg,$zero`? hmm, `li z,0` is free? gcc uses `move $8,$zero` = `or` → an extra insn).

✗.

OK. Let me now consider: maybe I'm wrong that the copy must be `or`. Let me re-check the target bytes: `80d8: 00401821 move v1,v0`. 0x00401821: bits: opcode 0 (special), rs=2, rt=0, rd=3, shamt=0, funct=0x21 (OR). So `or v1,v0,$zero`. Definitive.

Hmm, so the target IS a plain OR copy.

So the question is just: how to keep a plain OR copy alive.

Let me look at this from gcc's perspective: gcc's combine eliminates copies in `simplify_expr`/`combine_insns`:
```c
      /* If we have a copy, and the destination is a pseudo with a single
	 use, and the source is a reg, we can eliminate the copy. */
```
Hmm, actually gcc's combine has this specific code (combine.c, in `combine_insns`):
```c
	      /* If this insn is a copy and the source is a pseudo-reg with
		 one use, we can delete the copy... */
```
and:
```c
	  /* If we are copying a reg to a reg, and the destination is used
	     only once, and the copy is not needed for correctness,
	     eliminate it by substituting the source. */
```

And gcc's `local_alloc` also does copy coalescing.

There's also gcc's `final.c`/`reload.c` which coalesce copies.

So a plain copy is doomed... unless the copy's RHS isn't a reg.

**Hmm, what if the RHS is a REG but a HARD register that is live at the use?** e.g. `u = a0` where a0 is a parameter — combine's copy elimination would substitute a0 into the use → `addiu v0,a0,-1`. Yeah, t1 showed that.

Hmm.

**What if the RHS is a hard register $0?** `(plus t (reg 0))` — the mips "move" pattern. So `u = t + zr` where zr is pinned to $0. That's the pin.

Hmm, is there any OTHER C construct that yields `(plus x (reg 0))`?

What about `u = t` where gcc's `expand` generates a copy via `emit_move_insn` with a `gen_rtx_PLUS`? Hmm.

**What about a struct assignment or an array element copy?** gcc's expand_block_move → `copy_addr_to_reg` → MEM.

**What about `u = t` where u is a `float`?** → `(set (reg f) (float:SI (reg t)))` — a conversion.

Hmm.

**What about the `volatile` qualifier?** no.

OK — let me consider that maybe the answer for 80182ED4 is a WALL, but let me look at how the OTHER pin items with $0 were cracked: func_80180C04 ("$0 zr pin dropped, flag declared s16: HImode flag=1 test not folded by cse") and func_8017E1D4/8017E978 ("s16 flag2/3/4 copies"). Both had a *known range* so the sign-extend folded to a move.

In our case, the copied value's range is unknown → no fold.

Hmm, hold on! What about making the copy's SOURCE have a known range by *construction*, while keeping the `lh` load?

The load `lh v0,132(s0)` gives a sign-extended s16. But what if the C is:
```
t = unk84;          /* lh → v0, sign-extended */
...
} else {
    u = t;           /* copy */
    t = u - 1;
}
```
What if instead:
```
} else {
    u = t & 0x7FFF;   /* no */
```

Hmm. What if the SOURCE of the copy is a value gcc knows is 0..255? Like the `x`, `y`, `z` values? The target's copy source is v0 = the lh result.

WAIT A SECOND. What if we change WHICH value is copied, as long as the ASM matches? The target: `lh v0,132(s0)` → v0; `or v1,v0` → v1 = v0's value; `addiu v0,v1,-1` → v0 = v1-1; `sh v0,132(s0)`.

So the copied value is the loaded unk84 and the result is unk84-1 stored back. There's no freedom.

Hmm, unless: what if the `or v1,v0` copies a value that is NOT unk84 but the asm is the same? The asm says v1 = v0 = unk84. So no.

OK so we need a copy of the lh result that survives.

**LAST IDEA: make the copy survive by making the SOURCE a pseudo whose reg is "hard" at combine time...**

Hmm, what if the copy's source is the result of a CALL (hard reg v0 at cse time)?! In the target, no call. But hmm — what if we restructure to introduce a call? No, that changes the asm.

**LAST IDEA 2: What if the copy's source is a value loaded via `lb`/`lh` into a pseudo that gcc assigns to a HARD reg?** no.

**LAST IDEA 3**: What if the copy is `u = t` where `t` is declared `s32` and `u` is declared `s32`, but `t` is assigned from a `s16` field via an explicit cast that gcc implements as `(plus t (reg 0))`? no.

Alright, let me consider the possibility that the copy CAN survive if the destination is used in a place where the source can't be substituted — namely **when the destination is used in a different basic block than the copy and the source is dead in between**... no, substitution is still fine.

Hmm, what about **when the destination `u` is used MULTIPLE times in different blocks**? gcc's combine only eliminates copies within a block? Actually combine works on the whole function's insn sequence but the "single use" analysis is per-block-ish. Hmm! Actually gcc's combine eliminates a copy only if the dest has ONE use TOTAL? Let me test: `u = t; ... use u twice in different blocks`.

Hmm, in our case u has exactly one use.

Hmm, but hold on: what if we make u have TWO uses, one being a no-op that gcc removes later? E.g.:
```
u = t;
t = u - 1;
if (u == t) { }   /* empty */
```
gcc would remove the if. But the copy elimination happens in combine — the order matters. If combine sees u with 2 uses, it won't eliminate the copy; then the redundant `if` is removed later (jump/cfg pass), leaving the copy → `or v1,v0`!

Hmm! But the `if (u == t)` would generate extra insns (a compare + branch) unless it's optimized away BEFORE combine. Combine runs before the CFG optimization passes (combine is in the "rewrite" phase; the jump/cfg optimizations come later). So at combine time, u has 2 uses → the copy is kept → then the later passes remove the dead compare/branch → the copy remains!

That's a promising trick! But is it "adding a lever"? It's a plain-C no-op statement. Hmm, the brief prohibits "identity-statement launders" as a crack — this would be a similar trick. Hmm. "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". A dead `if (u == t) {}` is a fake statement — that's arguably a "launder"-ish trick and might be considered cheating. Risky.

Hmm. But hold on — actually there's a subtlety: with u used twice, combine would substitute the source into ONE use and keep the copy? No: combine's rule is: if the dest has one use → eliminate; if more → keep the copy.

Hmm, but combine might instead substitute into all uses and delete the copy. gcc's combine code:
```c
      /* If this is a copy and the destination is used only once, ... */
```
Hmm, gcc's combine has `reg_equiv_content`-based propagation elsewhere.

Hmm, wait. Actually gcc 2.7's combine eliminates copies in `simplify_expr`? No. Let me recall: gcc's copy elimination is in `combine_insns`:
```c
	  /* If we have a copy (set of reg to reg) and the destination
	     is a pseudo-reg that is used only once, and the copy is
	     not needed (the source is not a hard reg with a special
	     meaning), eliminate the copy by substituting the source
	     into the use and deleting the set. */
```
Hmm, actually I think gcc's copy elimination happens in `local_alloc` (the "copy coalescing") and in `reload`/`final`. And there's `combine`'s `(set (reg) (reg))` handling: combine's `simplify_expr` doesn't eliminate sets.

Hmm! But empirically t1 showed the copy eliminated. That could be local_alloc's coalescing (u and t merged into one reg) rather than combine eliminating the copy! In that case, the copy insn survives in the RTL but gets coalesced by local_alloc into the same register → the `or` disappears (since the copy's src and dst are the same reg).

YES! That's more likely: local_alloc coalesces the copy (u and t in the same reg) → the copy insn becomes a no-op and is deleted.

So the copy in the target survived because u and t got DIFFERENT registers. Why? Because at the addiu, t is the destination and u the source → they conflict → local_alloc can't coalesce them → u gets its own reg (v1) and the copy `or v1,v0` remains.

So the mechanism is REGISTER CONFLICT, not cse!

Then why did our lever-free version produce `addiu v0,v0,-1`? Because cse (or combine) removed the copy entirely, so there was only one pseudo.

Hmm, but if it's local_alloc coalescing, then the copy `u = t` should still be in the RTL and local_alloc would find u and t conflicting (u is read, t is written at the addiu) → they can't share a reg → u gets v1 → `or v1,v0` + `addiu v0,v1,-1`!

But we observed `addiu v0,v0,-1`. So the copy was eliminated BEFORE regalloc — by cse or combine.

So cse (early) propagated u→t. Because cse's make_regs_eqv + the "canonical" rule.

Now, cse's rule (from the G02 note): "iVar1 outlives t -> canonical". Hmm, in our case, we want the copy to survive, i.e. cse should NOT canonicalize u→t.

cse's make_regs_eqv logic (gcc 2.7), I'll now try to recall harder:

```c
static int
make_regs_eqv (reg, orig_reg, insn)
{
  ...
  /* Don't attempt to equate the two registers if one is a hard register
     and the other is not. */
  if (regno >= FIRST_PSEUDO_REGISTER && orig_regno < FIRST_PSEUDO_REGISTER)
    return 0;
  ...
  /* If we are setting a reg to a reg and the reg is a pseudo-reg and
     the source is a pseudo-reg, ... */
  ...
  copy = gen_rtx_REG (GET_MODE (x), regno);   /* hmm */
  ...
  /* If the source is dead after this insn, and the dest is used more
     than once, we may want to swap... */
  ...
  reg_equiv_content[regno] = copy;
  ...
  /* In the case where the source is dead, ... */
}
```

And the propagation of reg_equiv_content into uses happens in cse's main loop via `simplify_insn`? no. Hmm, in gcc, `reg_equiv_content` is consumed by:
- `reload.c` (for the "reg_equiv_content" reload optimization)
- `final.c`
- **`local-alloc`/`global-alloc`? no**
- **`expand`? no**

Hmm, and cse.c itself: in `cse_basic_block`, when it processes an insn, it calls `simplify_insn`? no.

Hmm, actually I remember now: gcc's copy propagation via reg_equiv_content happens in **`cse.c`'s `record_jump_equiv`**? no.

Hmm — OR in `flow.c`'s `allocate_registry`? Hmm.

Honestly, gcc 2.7's `reg_equiv_content` is used in `reload.c` to avoid reloading, and in `final.c`/`jump.c`? and in **`cse.c` itself**: after `make_regs_eqv`, cse sets `reg_equiv_content[regno] = copy` and later, when it encounters a use of regno, `rewrite_operand`... hmm no.

OK, let me test empirically! Let me test what happens with a copy where the destination is read and the source written (the conflict case):

```c
int t9(int t) { unsigned u; u = t; t = u - 1; return t; }
```
This is EXACTLY our pattern (the dest of the addiu is the same var as the copy's source). Let me test it! If it produces `or v1,v0` + `addiu v0,v1,-1`, then the pattern works in isolation and something else in the real function kills it.

Let me run that test.

Also test:
```c
int t10(int t) { unsigned u; u = t; t = u - 1; return t; }  /* same */
int t11(int t) { unsigned u; u = t; if (t) { t = u - 1; } return t; }
```

Let me run.

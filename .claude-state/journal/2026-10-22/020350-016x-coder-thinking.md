---
ts: 2026-10-22T08:03:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_LSIbQxVM4oNDaNJ1AQX8
---
Only indentation of labels differs (orig.c was hand-edited, labels indented). The body is the same. So orig.c is essentially the current src def (modulo label indentation). Per G08c gotcha, I should regenerate orig.c from src to be safe. Let me regenerate it.

Actually, the labels being indented vs not doesn't change codegen. But let me regenerate to be clean.

Now, let me append the results row for 801880E0 and moves.md line, then continue with the next item.

Actually let me batch: do the results rows at the end, or incrementally? The brief says "Per item append exactly one row to RM1/results.tsv". I'll append per item as I go (safer).

Let me now work on 80182ED4 while thinking.

**80182ED4**: target 42 ins. Need `move v1,v0` to survive.

Current win.c: `u = t; t = u - 1;` → score 6, the copy folded.

Ideas:
1. `u` as s16/u16 → truncation copy.
2. Make the copy part of a chain where the value's range is known.

Let me check the struct type of unk84.

Let me grep the struct definition.

Also idea 3: make `u` the *parameter*? No.

Idea 4: swap roles: instead of `u = t; t = u - 1;` write `t = t - 1;` and get the `move v1,v0` from... the store `unk84 = t`? no.

Hmm. Actually let's reconsider the target structure:
```
if (t == 0) { ...; t = 0x1E; }
else { u = t + zr; t = u - 1; }
unk84 = t;
```
Target asm has `move v1,v0` then `addiu v0,v1,-1`.

Note: the delay slot of `bnez v0` holds `move v1,v0`. In the lever-free version, the delay slot holds `addiu v0,v0,-1` — i.e. gcc scheduled the addiu into the delay slot.

What if we restructure so the copy is unavoidable? E.g., write the else branch as:
```
} else {
    u = t;
    t = u - 1;
}
```
cse kills it.

What if we make `u` be assigned a value and then used in a way that prevents cse from propagating but doesn't change the asm? For instance `u = t;` then `t = u - 1;` then also `if (u == t) ...`? Adds code.

Hmm. What about using `u` in the *store*: `unk84 = t` — no.

Let's think about what makes cse not propagate: cse's make_regs_eqv works on reg-reg copies. It sets reg_equiv_content for the destination. Then in `make_regs_eqv`, if the destination's value is used later, it does canonicalization: "if the dest reg is not dead, we may prefer to rewrite the dest's uses to the src". The direction chosen: cse.c make_regs_eqv: it looks at reg_equiv_content[regno] and the number of references. Specifically:

```
/* If the value is a copy of another register, and the copy has fewer
   references than the original...  */
```
Actually cse.c has:
```
	      /* If this insn is a copy and the source is not dead,
		 we may want to substitute... */
```
Hmm.

There's the "global-alloc" mention in the G02 note: "cse make_regs_eqv (cse.c:840): iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1 (s-reg); target keeps t in v0".

So the canonicalization direction depends on lifetime: the LONGER-lived one becomes canonical, and the shorter-lived one's uses get rewritten. Wait: "iVar1 outlives t -> canonical" means iVar1 (the copy) becomes canonical, and t's uses get rewritten to iVar1. Hmm, that's the opposite of what we want (we want u (the copy) to be rewritten to t, i.e. t canonical).

In our case: `u = t` (u lives from the copy to `t = u - 1`), t lives from before to `unk84 = t`. Hmm.

In cse.c make_regs_eqv, there's this logic (gcc 2.7):
```
      /* If this is a set of a reg to a reg, and the reg is live
	 longer than the other, then we should use the other one... */
```
Let me recall the actual code:

```c
static int
make_regs_eqv (reg, orig_reg, insn)
{
  ...
  /* If we are setting a reg to a reg, and the reg is not dead,
     ... */
}
```
Hmm, and there's `reg_equiv_content` with the "expanding" step.

Alternatively in cse.c, after make_regs_eqv, there's the code in `cse.c`:
```
	  if (reg_equiv_content[regno] ...
```
and in `rewrite_operand` / `equiv_regs`.

Actually the relevant piece in gcc 2.7 cse.c `make_regs_eqv`:
```c
	  /* If this is a set of one reg to another, and the source
	     is a pseudo-reg ... */
```
and later:
```c
      /* If REGNO is set to the value of ORIG_REG, and the value of
	 REGNO is used more than once, ... */
```

There's also this important rule in cse.c (cse_basic_block):
```c
	  /* If this insn is a copy of a pseudo-reg, and the pseudo-reg
	     is not live ... */
```

Honestly, rather than theorize, let me just experiment. The s16 trick is most promising and matches G02's precedent.

Let me check the struct type of unk84 first. Search the TU for "unk84".

Also, alternatively: instead of `u = t`, write `u = t & 0xFFFF`? That gives zero_extend → combine nonzero_bits(t & 0xffff)... For the copy to be a plain move, combine must know the high bits of t are zero — nope.

Better: what if we make `u`'s copy from a value with a KNOWN range? We could restructure the code:

```
} else {
    u = t + zr;   /* target */
    t = u - 1;
}
```

What if we write it as:
```
} else {
    u = t;
    t = u - 1;
}
```
but with `u` declared `u16` and `t` declared `u32`? Then `u = t` truncates → zero_extend. `t = u - 1` → u zero-extended → t = (u16)t - 1. The asm: `move v1,v0` then `addiu v0,v1,-1`? But u needs zero-extension from t: `andi v1,v0,0xffff` → not a move. Unless combine knows t's high bits are zero.

Hmm. What if `t` is declared `u16` too? Then `t = unk84` truncates the load. unk84's type in the struct matters. If unk84 is u8/u16 then t's range is known and everything's exact.

Let's check the struct.

Let me grep for unk84 in the TU.

Actually — here's a much better idea. Look at the target again:

```
t = ((Unkstruct_80182ED4 *)arg0)->unk84;
if (t == 0) { ... } else { u = t + zr; t = u - 1; }
((Unkstruct_80182ED4 *)arg0)->unk84 = t;
```

What if we restructure so that `u` is assigned from `t` where `t` is the *loaded* value and `u` is used as the base for a subtraction — i.e. exactly the same. The cse problem stands.

Alternative: use a *different* variable for the loaded value so that the copy is between two variables with different lives.

Hmm, what if the store `unk84 = t` were changed to `unk84 = u - 1`? Then:
```
} else {
    u = t;     /* copy */
    t = u - 1;
}
```
Same cse.

What if:
```
} else {
    u = t;
    unk84 = u - 1;    /* store directly, t not reassigned */
}
```
But then the `t = 0x1E` path also stores unk84. We could restructure:
```
if (t == 0) { ...; t = 0x1E; }
else { u = t; }
unk84 = t;   /* hmm */
```
No.

Alternatively:
```
t = unk84;
if (t == 0) { ... t = 0x1E; }
else { u = t; t = u - 1; }
unk84 = t;
```
→
```
t = unk84;
if (t == 0) { ...; t = 0x1E; }
else { u = t; t = u - 1; }
unk84 = t;
```

What if we make the *if* body produce t=0x1E differently so that cse's canonical choice flips? The canonical choice in make_regs_eqv depends on the number of references and liveness of the equiv regs.

Consider: if `t` had MORE references after the copy than `u`, cse would canonicalize u→t (what happens now). If `u` had more references, cse would canonicalize t→u, giving `move`? no — canonicalizing t→u means t's uses read u, so u must live longer and be in a callee-saved reg. Not our target (target has t in v0, u in v1, and v0/v1 are caller-saved).

Hmm. In the target, u ($3/v1) is short-lived: created at the `move v1,v0`, used by `addiu v0,v1,-1`. And t ($2/v0) is used for the compare `beqz v0`.

So actually in the target, u is a short-lived copy created right at the branch. This looks exactly like the delay-slot scheduling of a copy that the allocator could have coalesced but didn't because t is live (t's value needed for the compare? no, the compare is before).

Hmm hold on! Look at the target sequence:
```
beqz v0, ...    (if t == 0)
...
bnez v0, ...    (if t != 0)
move v1,v0      (delay slot)   <- u = t
...
j ...
addiu v0,v1,-1  (delay slot of jr ra)
```
Wait the diff showed target[35:36] = `j` and `addiu v0,v1,-1`. So the addiu is in the delay slot of `jr ra`.

And mine has `addiu v0,v0,-1` in the delay slot of `bnez v0` at index 12, and later just `j`.

Hmm so in mine, the addiu is scheduled early (in the bnez delay slot) and the `jr ra` delay slot is empty (or `j`).

In the target, the `move v1,v0` is in the bnez delay slot and the addiu in the jr delay slot.

So the target really has u as a separate pseudo.

Now, gcc 2.7's cse: after `u = t` (a copy), the value propagation. But note: gcc's `combine`/`cse` — the copy `move v1,v0` was created by combine? "u = t + zr" → `(plus t (reg 0))`. combine converts that to a copy `(set u t)`. But cse runs BEFORE combine, so at cse time the RTL was `(set u (plus t (reg 0)))` → cse doesn't see it as a copy → u survives. Then combine turns it into `(set u t)` — but cse doesn't rerun, so the copy is preserved! That's the whole mechanism.

So lever-free we need something that at cse-time is not a plain `(set u t)` but later becomes one.

Options:
(a) `(set u (plus t (reg 0)))` — needs a hard reg 0. That's the pin. Forbidden.
(b) `(set u (sign_extend:HI t))` — cse doesn't treat as copy (it's a conversion). Later combine folds it to a copy if the sign bit is known zero. Hmm — actually, would combine fold `(set u (sign_extend:HI t))` where u is QImode? The RTL for `u = t` with u:QImode, t:SImode is `(set (reg u) (sign_extend:HI (reg t)))`. Wait no: assigning s32 t to s16 u: gcc converts t to QImode: `(set (reg u) (sign_extend:HI (truncate:HI (reg t))))`? Hmm, sign_extend:HI already implies truncation to 16 bits.

Actually gcc: convert to QImode → `convert_to_mode(QImode, expr)` on an SImode value does `(sign_extend:HI (reg t))`? `convert_to_mode` for a narrower signed mode: it truncates and sign-extends back → in RTL that's `(sign_extend:HI (reg t))`. Yes.

Then combine: for `(sign_extend:HI (reg t))` where t is a reg — combine's rule: "convert (sign_extend:HI (reg)) to a copy if the value's high bits are known". combine's `nonzero_bits` on t gives the known bits; if bits 16-31 are known zero, the sign_extend is unnecessary → combine replaces with a copy.

So we need t's high bits known zero. t = unk84 loaded from a struct field. If unk84 is a u16/u8 field → the load is `lhu`/`lbu` → zero-extended → high bits known zero → combine folds → copy → `move v1,v0`!

But also: is the sign bit of the QImode value known? If unk84 is u16 (0..65535), then as s16 it could be negative → sign_extend needed to s32. But we only need the s16 copy to stay s16 and then `t = u - 1` promotes u (s16) to s32 → sign extension needed → `sll v1,16; sra v1,16`! That would add instructions.

Unless... `t = u - 1` where u is s16: the promotion of u to s32 is a sign_extend:SI of u → extra insns. Unless gcc computes `t = (s32)u - 1` and knows u's sign bit.

Hmm. Let's think: if unk84 is u16 and t is s32 = (s32)unk84 (0..65535, sign bit 0 known) → t's bits 16-31 not known zero but bit 31 known zero. `u = t` as s16 → sign_extend:HI(t) → the value is t's low 16 bits interpreted signed → not equal to t in general. Then `t = u - 1`: u promoted → sign_extend:SI(u) = u (since u is s16 → sign_extend to s32). Hmm.

This is getting complicated. Let me check the actual struct type first, then experiment.

Actually — alternative (c): make the *destination* `u` an s16 but the source `t` also s16? Then `u = t` is a same-mode copy → cse propagates. No.

(d) What about making `u` a *float*? no.

(e) What about `u = t` where `u` is `volatile`? store+load → wrong asm.

(f) What about using a union or a struct member? no.

(g) What about `u = (s16)t` where the cast is a truncation to s16 and then the *use* is `t = u - 1` where u is declared s32? i.e. `u = (s16)t;` then `t = u - 1;`. Then u is s32, and the RTL is `(set u (sign_extend:HI t))` → u holds the sign-extended low 16 bits. Then `t = u - 1` → `addiu v0,v1,-1`. And u's value = sign_extend16(t) vs target u = t. Different semantics unless t fits in 16 bits signed.

And cse: `(set u (sign_extend:HI t))` — cse won't equate u with t. Then combine: does it fold the sign_extend to a copy? Only if bits 16-31 of t are known zero, which contradicts sign-extension semantics... Actually combine's rule for sign_extend: if nonzero_bits(t) says bits 16-31 are zero → the sign extension of the low 16 bits: if bit 15 is unknown, sign_extend gives value in [-32768,32767], which is NOT equal to t. So combine can't fold it to a copy unless bits 15-31 are all known zero.

So we need t's bits 15..31 known zero → t's range 0..32767. t = unk84. If unk84 is u16, gcc knows bits 16-31 are zero but not bit 15.

Hmm. Then the sign_extend:HI is needed → `sll v1,16; sra v1,16`? Actually combine would emit sign extension as `sll v1,16; sra v1,16` (2 insns) → not matching.

OK so the truncation approach requires the value's range to be known such that no extension is needed at all. In G02's case, flag = -(x!=idx) & 0xFF → 0..255 → bits 8..31 zero → sign_extend:HI is a no-op → plain move.

So for 80182ED4 we'd need t's value to be known 0..255-ish. t = unk84 — unknown.

Hmm. So the s16 trick probably doesn't work here.

Let me reconsider. What else makes a copy survive cse at cse-time but become a copy later?

- `(set u (plus t (reg 0)))` — pin.
- `(set u (plus t (const 0)))` — tree-level folded before RTL.
- `(set u (if_then_else ...))` — no.
- `(set u (minus t (const 0)))` — folded.
- `(set u (mult t (const 1)))` — folded.
- `(set u (and t (const 0xFFFFFFFF)))` — folded.
- `(set u (ior t (const 0)))` — folded.
- `(set u (not (not t)))` — folded.
- `(set u (truncate t))` where t is SImode → u QImode: that's zero_extend? For unsigned dest: `(set u (zero_extend:HI t))`. nonzero_bits(t) unknown → combine can't fold → extra insn.

Hmm.

- What about a copy through a *pseudo* that isn't recognized: `(set u (plus t z))` where z is another pseudo known to be 0? Then combine (later) sees `(plus t z)`; z is a pseudo with value 0 known via its def — combine's `known_zero`? combine doesn't track pseudo values (that's VRP, later). combine only knows constants. So `(plus t z)` stays as an add with a register → `addu v1,v0,zreg` where zreg is some register ≠ 0. Not matching.

Unless z is $0... which needs a pin.

Hmm, what if z is the function's *unused parameter*? No.

Hmm, what about making the addend a hard register legitimately, e.g. `u = t + arg0` where arg0 is a parameter? Parameters live in a0 — `addu v1,v0,a0`. Not `move`.

So a plain `move v1,v0` requires the RTL at combine time to be `(set u t)` (a copy) but not a copy at cse time.

Hmm! What if the copy is created by *reload* — i.e. the value goes through memory? `u = t` where u is spilled... no.

What about `(set u (reg t))` created by the *expand* pass? E.g. an unaligned load? no.

What if the RTL is `(set u (plus t (reg 0)))` because of `t + zr` where zr is... hmm.

OK alternative: maybe the answer for 80182ED4 isn't a copy-preservation trick but a *restructuring* that produces the same asm differently.

Target: `move v1,v0` and `addiu v0,v1,-1`, where v0 initially holds t.

What if we write:
```
} else {
    u = t;
    t = u - 1;
}
```
cse kills. But what if we make the `t` in `u = t` a DIFFERENT variable than the `t` in `t = u - 1`? Like:
```
} else {
    u = t;
    t = u - 1;
}
```
The dst of the copy is u (live until use), src is t. cse: makes u equivalent to t. Then `t = u - 1` becomes `t = t - 1`.

But what if instead the copy's SOURCE is the one that dies? I.e.:
```
} else {
    u = t;
    t = u - 1;
}
```
Here u dies at `t = u-1` and t is redefined. Hmm.

What if we swap: keep t alive and kill the copy:
```
} else {
    u = t;      /* u dies */
    t = u - 1;
}
```

Try instead:
```
} else {
    u = t + 0;   /* nope */
}
```

Hmm, what if we introduce an intermediate so the copy is `u = v` and `v = t`? Two copies; cse will canonicalize anyway.

OK, different approach: what if we make the value copied into `u` be a value that is *recomputed* rather than copied, e.g. `u = t` → `u = unk84` (reload the field)? Then u = the loaded value; the load would be `lw v1,132(s0)` instead of `move v1,v0`. Not matching.

What if the store `unk84 = t` is moved into the else branch, so `t` dies earlier and `u` lives longer? Then cse might canonicalize u (longer-lived) → but then t's uses (the store) rewritten to u... Let's think:

```
} else {
    u = t;
    t = u - 1;
    unk84 = t;
}
```
Here after `u = t`, t is redefined. cse canonicalization: u and t are equiv at that point. Then `t = u - 1` kills t's old value. The store uses the new t. So u is dead after → u ≡ t, and the addiu could be `addiu v0,v0,-1`. Same.

Hmm.

What if we write it as:
```
} else {
    u = t;
    v = u - 1;      /* v is a NEW var, and unk84 = v */
}
```
Then: u ≡ t (cse). v = u - 1 = t - 1. Same as before → `addiu v0,v0,-1`. Hmm, but wait! Now t's live range ends at the copy (t is not used after), so t dies. Then u = t... cse would substitute u's uses with t. Still `addiu v0,v0,-1`.

Argh.

Hmm, hold on: what if t is used AFTER, so that the copy's destination u is needed and t can't be reused? Actually, the target has t in v0 and u in v1 — two different registers, with `addiu v0,v1,-1`. This means at the addiu, u is read and t is written. gcc must not coalesce since u ≠ t.

If cse canonicalizes u→t, we get one register. To prevent: the copy must not be a plain copy at cse time.

Alternatively — maybe the answer is to make `u` a *global* variable? Like `u` declared as a static? Then `u = t` is a store to memory. No.

What about `u` being in a different "reg class"? no.

Hmm, what about the ORDER: what if we write `t = u - 1;` FIRST and `u = t;` after? Then u is dead. no.

What if `u` is used in the store too: `unk84 = t` where t = u-1. Same.

OK: what if we make `u` used TWICE: `u = t; t = u - 1;` and then... hmm, if u is used later, cse canonicalization picks the longer-lived one as canonical. If u is longer-lived than t, then u becomes canonical and t's uses are rewritten to u → the register for t would be... Let's think about the target: t in v0, u in v1. If u is canonical and longer-lived, then after the copy, everything uses u's register.

Hmm, but actually in the target, u dies at the addiu and t (v0) is written by the addiu and then stored. So u is SHORTER lived.

So the target has: u = copy of t; u dies at addiu; t is redefined by addiu.

For gcc to allocate u in a different register than t, u must not be coalescable with t. In gcc 2.7's local_alloc, coalescing of a copy happens if the copy is still there. If cse removed the copy (canonicalized), there's one reg.

So: cse must NOT canonicalize. What makes cse.c not canonicalize a copy? Looking at gcc 2.7 cse.c `make_regs_eqv`:

```c
static int
make_regs_eqv (reg, orig_reg, insn)
     int reg, orig_reg;
     rtx insn;
{
  ...
  reg_equiv_content[regno] = copy;   /* regno = reg */
  ...
  /* If we are setting a reg to a reg, and the value is a constant... */
  ...
      /* If this is a copy of a pseudo-reg, and the pseudo-reg is not
	 live, we can delete the copy... */
}
```
Then later, in cse.c's main loop:
```c
	  /* If this insn is a copy (set of reg to reg) and the destination
	     is not dead, record the equivalence.  */
```
and the actual rewriting of uses happens via `reg_equiv_content` in `rewrite_operand`? Actually in gcc, `reg_equiv_content` is consulted in `simplify_gen`/`expand`... Hmm.

Actually the propagation happens in cse.c's `cse_basic_block`:
```c
      /* If we have a set of a register to a value, and the register
	 is not dead after this instruction, then we may want to
	 substitute... */
```
and there's `record_jump_equiv`...

The canonicalization in gcc is done in `regclass.c`? No. Hmm, in gcc 2.7 there's `local_alloc` doing "copy propagation" via `reg_equiv_content`? Actually there IS: in flow.c's `allocate_registry`, there's no. In `reload.c`?

Hmm, actually gcc 2.7 cse.c has:
```c
/* Return true if we should consider the insn as a candidate for
   the equivalence table... */
```
and
```c
	  /* If this insn is a copy of a pseudo-reg, and the pseudo-reg
	     is not live ... */
```

And critically there's this in cse.c (2.7):
```c
	      /* If we find a set of a reg to a reg, and the reg is
		 not the same, record the equivalence... */
```

And the "canonicalization" (choosing which reg survives) is in `cse.c`'s `make_regs_eqv`:
```c
  /* If this insn is a copy, and the destination is a pseudo-reg,
     and the source is a pseudo-reg, then we may want to
     reverse the copy if the source has more references... */
```

Hmm. I recall gcc's `make_regs_eqv` has this logic:
```c
      /* If the copy is a self-copy ... */
      /* If regno is a pseudo-reg ... */
```
and separately in `cse_basic_block`:
```c
	  /* If we have a set of a reg to a reg, and the reg is used
	     more than the source ... */
```

Let me instead look at the actual behavior empirically. The G02 note says: "cse make_regs_eqv (cse.c:840): iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1 (s-reg); target keeps t in v0".

So: when the copy destination outlives the source, the destination becomes canonical and the SOURCE's uses are rewritten. In our case, we want the source (t) to stay canonical and the destination (u) to be rewritten away — but that removes u entirely.

Hmm wait. If the destination u outlives the source t, then u is canonical and t's uses are rewritten to u → so `u = t; t = u - 1;` becomes `u = t; t = u - 1` where t's earlier uses now read u. But t is redefined right after. Hmm.

Let's reconsider: in our code, at the copy `u = t`: t's remaining uses = `t = u - 1` (that's u's use, not t's). t has no uses after the copy (it's overwritten). u's use: `t = u - 1`. So u outlives t (t dies at the copy, u lives until the addiu). By the rule, u becomes canonical, and t's uses rewritten to u — but t has no uses. So the copy `u = t` remains as a real copy! And then the addiu `t = u - 1` → `addiu v0, v1, -1` with u in v1!

Wait, but that's the current lever-free behavior which FAILED (score 6, copy gone). Hmm.

Hmm, the current win.c has `u = t; t = u - 1;` and the copy vanished. So cse did canonicalize u→t.

Unless... hold on, in the current win.c, `u` is s32 and `t` is s32, `u = t` is a plain copy. cse sets reg_equiv_content[u] = t, and then propagates: all uses of u are replaced by t → `t = t - 1`. That's cse's "propagate" step (the `reg_equiv_content` mechanism in `simplify_gen`? no).

Hmm, in gcc 2.7, cse.c has the notion: after `make_regs_eqv`, when it later sees a use of `u`, it checks `reg_equiv_content[u]` and substitutes. There's the code:

```c
	      /* If we are looking at a copy from a pseudo-reg, and the
		 pseudo-reg has a known value, ... */
```

and in `cse_basic_block`:
```c
	  /* If this insn is a set of a reg to a reg and the reg is
	     equivalent to another reg, and the other reg is live... */
```

Honestly: empirically, `u = t` (both s32) gets folded away. That's the observed fact.

So what did the G02 win.c do differently? `flag2 = flag` where flag2 is s16 and flag is s32 → truncation → the copy survives as `move`. Yes.

OK so let me think about the s16 route for 80182ED4 more carefully with actual struct types.

Let me get the struct definition. Let me grep.

Actually, wait. Let's reconsider the whole thing. Is there a completely different C shape?

What about using the fact that the target's `u` is a *separate pseudo* and gcc 2.7's `combine` might create it? E.g. `t = u - 1` where u is the result of a function call... no call here.

What about `u = t` where `t` is `unsigned` and `u` is `int`? same size → plain copy.

What about `u = t` where the assignment is a *conditional*: `u = t ? t : t;`? → cse/tree folds.

What about `u = (t + 0)` written as `u = t + (s32)0;` → folded.

Hmm, what about making the copy through a `volatile` local in a way gcc keeps in a register? No, volatile forces memory.

What about `u = t` where `u` is declared `register`? Not allowed (register vars are the pin lever; the constraint says "no `register` vars").

Hmm! "no `register` vars" — so `register u;` without asm is out.

What about the ordering of the two statements relative to the branch? The target has the copy in the bnez delay slot.

New idea: what if we DON'T copy at all, and instead the `move v1,v0` comes from a different source — e.g. `u` is a *parameter* of the function? No, signature fixed.

What if `u` is assigned from `t` where `t` is a *volatile* load? no.

Hmm, what about making the whole else-arm:
```
} else {
    u = t;
    t = u - 1;
}
```
into
```
} else {
    t = u - 1;   /* u undefined! */
}
```
no.

What if `u` is initialized at declaration to `t`? `u = t` at decl — same.

OK, let me consider: maybe the trick is that the copy must survive *not* by escaping cse, but by the *global-alloc* keeping u in a different reg than t because they're both live at the addiu and u is a global pseudo (crosses the block boundary)... no, u doesn't cross blocks.

Alternatively — maybe the copy is created by the *reload* of a pseudo spilled to the stack: e.g. if `u` is a pseudo that's live across a call → reloaded from stack → `lw v1, off(sp)` → not a move. No.

Hmm, let me look at this from the target's perspective again: `move v1,v0` — v1 = $3. And the target's other regs: v0 = $2.

And the diff note said "the `u = t + zr` line materialises as `move v1,v0` in the delay slot of the `if (t == 0)` branch". Wait — "the delay slot of the `if (t == 0)` branch"?? The `if (t == 0)` branch is `beqz v0`. And the diff showed the `move v1,v0` at index 12, right after `bnez v0` at 11. Hmm, so it's the delay slot of the bnez (the else branch).

OK. Let me try to think about what C code produces `move v1,v0` + `addiu v0,v1,-1` naturally in gcc 2.7.

Simplest:
```c
s32 t, u;
...
u = t;
t = u - 1;
```
gcc 2.7: cse kills it → `addiu v0,v0,-1`.

What about:
```c
s32 t, u;
...
u = t;
if (u) t = u - 1;
```
extra branch.

What about:
```c
u = t;
t = u - 1;
```
where u is declared as `u32` and t as `s32`? Conversion s32→u32 is a no-op → plain copy.

Where u is `s16`/`u16`? discussed.

Where u is `long` (32-bit in this target?) — same as s32.

Where u is `short` and t is `s32`: truncation.

Hmm what about the SOURCE being truncated: `u = t` where t is s16 and u is s32 → sign extension of t → `(set u (sign_extend:SI t))`. cse: sign_extend isn't a copy → u survives! Then combine: if t's bit 15 is known 0 → fold to copy → `move v1,v0`.

And `t = u - 1` → u is s32, fine → `addiu v0,v1,-1`.

So: make `t` an s16! t = unk84 (if unk84 fits in s16...) hmm, but t is also assigned `func_80133784(...)` result (s32) and `0x1E`.

Wait: in the target, `t` holds the call result (s32) and unk84. If t is s16, the call result truncates → `move v1,v0` + truncation. Hmm.

But maybe use a SEPARATE variable for the else-arm value:
```
} else {
    u = t;     /* t s32 → u s16 */
    t = u - 1;
}
```
We need t's high bits known.

Alternatively: what if we make `u` a s16 and copy into it a value whose high bits are known zero? We'd need to know t's range.

Hmm, what is unk84's type? Let's check. If unk84 is u8 → t's range 0..255 → then `u = t` as s16 → sign_extend:HI(t) → t's bits 8..31 known zero → but bit 15? For a s16 copy we need the sign bit handling: sign_extend:HI(t) where t ∈ [0,255] → the 16-bit value = t, sign bit = 0 → so sign_extend:HI(t) == t → combine folds to a copy → `move v1,v0`. YES! And then `t = u - 1` where u is s16 with range 0..255 → sign extension to s32 not needed (value known nonnegative) → `addiu v0,v1,-1`.

But wait: cse must not propagate u≡t. With the truncation, the RTL is `(set u (sign_extend:HI t))` → not a copy → cse keeps it.

And crucially the semantic: u = (s16)t. If t ∈ [0,255], u = t exactly.

Also `t = u - 1`: u promoted from s16 to s32. Since u's range is known 0..255 (if combine knows), no extension → addiu.

Hmm, but does gcc 2.7 know that t's range is 0..255? t = unk84 where unk84 is a u8 field → the load is `lbu` → value 0..255 → combine's nonzero_bits knows bits 8-31 are zero → sign_extend:HI folds to copy.

But careful: `t` is assigned in two places: `t = unk84` (u8 → 0..255) and `t = func_80133784(...)` (s32) and `t = 0x1E`. In the else-arm, t = unk84 (the u8 load). But the compiler's range info for the pseudo t is the union over all assignments... combine works on the RTL at the point of use: the RTL is `(sign_extend:HI (reg t))` where reg t's value at that point... combine's known_zero/nonzero_bits on a pseudo doesn't track ranges in gcc 2.7 (no VRP). combine works on the insn's operands: `(set u (sign_extend:HI (reg t)))` — combine would look at the *def* of t? combine does handle "the operand is a reg set by a previous insn" in some cases (combine has `known_zero` for regs defined by a preceding set in the same basic block? gcc 2.7's combine does look at the previous insn for the operand via `prev_insn`).

Hmm, gcc 2.7's combine: `combine()` handles insns in a block and can use "the reg was set by the previous insn" — yes, combine has code that looks at `prev_insn` to determine the value of a reg operand (e.g., `(set (reg t) (reg x))` → combine can substitute x). That's the "combine folds a copy" behavior!

So combine would see `(sign_extend:HI (reg t))` where the previous insn set t = (lbu ...) → it might not track through.

Ugh, too much theory. Let's just try things empirically. I have limited time but let me try a batch of candidates for 80182ED4:

c2.c: `u` as s16, `u = t;` (t s32)
c3.c: `u` as u16, `u = t;`
c4.c: t as s16 and u as s32, `u = t;` then `t = u - 1;` — but t is s16 so `t = u - 1` truncates. Hmm, and t is also the call result. Let me instead add a separate var.
c5.c: `u = t` where t is declared `u16`? then unk84 load truncates.

Let me first check the struct types of unk84, unkC2, unk6, unkA, unkE.

Let me grep the struct in the TU.

Then run the batch with sc.sh.

Let me do that now.

Also, I should record the 801880E0 results row and moves.md line. Let me do that in the same command batch to save turns.

Let me first append the results row for 801880E0.

results.tsv format: `dir file func kinds result best tries wall evidence` (tabs).
dir = func_801880E0__ov_SC03_124_jr_80187010
file = src/ov_SC03_124/ov_SC03_124_jr_80187010.c
func = func_801880E0
kinds = pin
result = MATCH
best = 0
tries = 1
wall = -
evidence = "s16 flag2/3/4 (copy survives cse as sign-extend, combine folds to move) + w local + ot = func_800D27DC split before return (ot +2 refs beats w in greg)"

Wait, "w local": in the G02 version, `w` was a local `w = w0`. In my c1.c I used `w` local. Yes.

Also note: the moves.md line format: `kind | func | MATCH: move — mechanism (RM1)`.

Let me do all that.

Also the tries count: I did 1 scored try (c1.c) for this item. Plus the pre-existing win.c score (which was from a previous batch). I'll count 1.

Let me now write the results row + moves line, and start item 80182ED4.

For the evidence char limit ≤140. Let me count:
"s16 flag2/3/4 (copy survives cse as sign-extend, combine folds to move) + w local + ot = func_800D27DC split before return (ot +2 refs beats w in greg)" — that's about 152 chars. Let me shorten:
"s16 flag2/3/4 copies escape cse (sign-extend, combine->move); w local; ot = func_800D27DC split before return (ot +2 refs beats w in greg)" = ~140. Let me count precisely later.

Let me write it.

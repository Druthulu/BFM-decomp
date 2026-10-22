---
ts: 2026-10-22T08:06:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_2rsaVPVTHyCCYuVxq9IR
---
`move v1,v0` = 0x00401821 = `or v1,v0,$zero` (opcode 0x25 = or). Yes: 0x00401821 → rs=2, rt=0, rd=3, funct=0x21 (or). So it's `or`.

And `move s0,a0` = 0x00808021 → or s0,a0,$zero. Consistent.

So the target's `move v1,v0` is `or v1,v0,$zero` — a plain gcc "move" insn! Great, that means the copy CAN be produced by a plain C copy (which gcc emits as `or`).

Hmm, but then why did `u = t + zr` produce `or` and not `addu`? Because combine folded `(plus t (reg 0))` into a copy. Fine — the target is `or`.

Now: for a lever-free body, `u = t` (plain copy) → gcc emits `or` — but cse removes the copy entirely (score 6). We need the copy to survive cse.

Now the key question: what plain-C copy survives cse?

Options again:
1. `u` s16 ← t s32: truncation → sign_extend:HI. t = sign-extended s16 (range -32768..32767) → the sign_extend:HI is NOT a no-op in general. But combine's nonzero_bits: t = lh → the value is sign-extended 16-bit. combine might know bits 31..16 = bits 15..0 (sign extension), so the value of the low 16 bits interpreted as signed... The sign_extend:HI(t) = sign-extend of t's low 16 bits = t itself (since t is already sign-extended 16-bit)! So semantically sign_extend:HI(sign_extend:HI(x)) = sign_extend:HI(x). But combine needs to know that t = sign_extend of a 16-bit value, which requires looking through the load. Hmm, gcc 2.7 has `nonzero_bits` on a MEM → not tracked. But combine might see the previous insn `lh v0,132(s0)` and know the result is sign-extended? gcc has `known_zero` for regs... For a MEM load, combine has a rule: "if the operand is a MEM with a known sign extension"? Not in 2.7.

Hmm. But actually — combine DOES have a rule to convert `(sign_extend:HI (reg))` → copy when the reg's high bits are known zero, and also a rule for `(plus (reg) (reg 0))` → copy.

Alternatively gcc's expand pass converts `u = t` where u is QImode: `expand_assign` → for a narrower mode, it emits a truncation: `u = (truncate:HI t)`? and for signed interpretation, the QImode reg holds the truncated bits; when u is later used as s16, gcc sign-extends on use. Hmm! Actually in gcc, a QImode variable's RTL reg holds a 16-bit value in a 32-bit reg (upper bits undefined). The assignment `u = t` (s32 → s16) is: convert t to QImode = `(sign_extend:HI t)`? gcc's convert_to_mode(QImode, t) on an SImode → "sign_extend:HI" (it truncates and re-extends to preserve the value). Then when u (s16) is used in `u - 1` (s32 context), it's converted back: `(sign_extend:SI u)`.

If the QImode value is held in a reg and then sign-extended to SI: `sll v1,16; sra v1,16`. That's the classic gcc 2.7 pattern. So the copy wouldn't be `or`.

Hmm, so the s16 trick in G02 worked because the value's range was known (0..255) so no extension was needed.

For 80182ED4, t = lh (sign-extended s16) → range -32768..32767. Copying t into an s16 u: value = t (fits in s16 exactly). Then using u as s32 → sign extension needed → but gcc knows u's value came from a sign-extended 16-bit... hmm, gcc would emit `sll v1,16; sra v1,16`? That's for the sign_extend:SI of the QImode reg.

Hmm, actually gcc 2.7's mips: for a QImode pseudo, when it's used in SI mode, it does sign_extension_from_mode. But since the reg's value is the truncated t and t was already sign-extended-16, the sign extension is a no-op → gcc's combine might figure that out via `nonzero_bits`? no.

Hmm, but hold on: gcc's `expand_assign` for `u = t` (u QImode) actually emits `(set (reg u) (sign_extend:HI (reg t)))`? or `(set (reg u) (truncate:HI (reg t)))` with the sign-extend deferred? In gcc, `convert_to_mode` for a narrower *signed* destination: it does `truncate` then `sign_extend` back to the original mode? For QImode destination from SImode source: `convert_to_mode(QImode, x)` where x is SImode → gcc does `sign_extend:HI` semantics = truncate to 16 bits and sign-extend → the resulting QImode value equals the original SImode value reinterpreted as 16-bit signed. Since the reg is 32-bit and the QImode value's high bits are don't-care, gcc typically stores the sign-extended value.

Then reading u in SI context: `(sign_extend:SI u)` where u holds the sign-extended 16-bit → the sign_extend is redundant but gcc doesn't know.

So the s16 route likely produces extra instructions.

2. Different idea: make the copy survive by having u and t be *different variables with different live ranges* such that cse's canonicalization picks u (the copy) as canonical — but then t's uses read u, and the copy `u = t` remains → we get `or v1,v0`! Wait! That's exactly what we want: if u is canonical, then the copy stays as a real copy.

Currently cse canonicalizes u→t (u is removed). When does cse canonicalize the destination vs source? From the G02 wall note: "cse make_regs_eqv (cse.c:840): iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1". So when the destination (iVar1) outlives the source (t), the destination becomes canonical.

In our case: `u = t; t = u - 1;` — u's live range: from the copy to the addiu. t's live range: from the load to the copy (t is killed at `t = u - 1`... wait no: `t = u - 1` redefines t). So after the copy, t is dead (its value only needed for the copy). u lives until the addiu. So u outlives t → u should become canonical → the copy should remain!

But the observed result is that the copy disappeared (score 6, `addiu v0,v0,-1`). Hmm. Contradiction?

Hmm, unless cse's make_regs_eqv works differently: it records reg_equiv_content[u] = t, and then when it encounters a USE of u, it substitutes t (if t is live) — the "propagate" direction. In gcc, `reg_equiv_content[dest] = src` and then in `cse.c`'s `record_jump_equiv`/`rewrite_operand`, uses of dest are replaced by src when src is still live. t IS live at the point of use of u? t is live at the copy point but dies at `t = u - 1`. At the use of u (in `t = u - 1`), t is being defined, so t is dead there → substitution shouldn't happen... but gcc's cse might still substitute because reg_equiv_content is a "value" mapping.

Hmm, gcc 2.7's cse.c in `cse_basic_block`, when it encounters `(set (reg u) (reg t))`:
```c
	      /* If this insn is a copy of a pseudo-reg, and the pseudo-reg
		 is not live, ... */
```
and the actual "copy propagation" of reg_equiv_content happens in `cse.c`'s handling of `reg_equiv_content` in `rewrite_operand`? Hmm no, `reg_equiv_content` is used by `reload`/`expand`/`final`?

Actually! `reg_equiv_content` is used in `local-alloc`/`global-alloc`? No — it's used in `flow.c` and in `cse.c` for the "copy propagation" phase.

Hmm, there's `gcc/cse.c: make_regs_eqv`:
```c
static int
make_regs_eqv (reg, orig_reg, insn)
     int reg, orig_reg;
     rtx insn;
{
  int regno = reg;
  int orig_regno = orig_reg;
  rtx copy;
  ...
  /* Don't attempt to equate the two registers if one is a
     hard register and the other is not... */
  ...
  /* reg_equiv_content[regno] = copy means "regno is equivalent to orig_reg" */
  ...
  /* If we are setting a reg to a reg, and the value is the same as
     the one in the reg, we can delete the insn */
  ...
  /* In all other cases, we can perform the copy... */
  ...
  /* If the source is a pseudo-reg that is dead, ... */
}
```
And there's this piece in make_regs_eqv (gcc 2.7):
```c
      /* If we are setting a reg to a reg, and the reg is a pseudo-reg,
	 and the value is a constant, ... */
```
Hmm.

And crucially, cse.c has this in the main loop (cse_basic_block):
```c
	  /* If this insn is a copy of a pseudo-reg, and the pseudo-reg
	     is not live, then we can delete the copy. */
```

But the "canonicalization" that G02's note refers to is at cse.c:840. Let me actually read the gcc 2.7.2 source if available in the repo (docs/gcc-2.7.2-map/). The project has docs/gcc-2.7.2-map/regalloc.md mentioned. Maybe the gcc source is available? Let me check if there's a gcc source tree in the project.

Actually — let me not over-theorize. Let me EXPERIMENT. I'll write several candidates and score them:

c2: `u` declared `s16`, `u = t;` then `t = u - 1;` — but wait, `t = u - 1` with u s16 → t = (s32)u - 1.
c3: `u` declared `u16`.
c4: `t` declared `s16`? No, t holds the call result (s32) — but in the else arm t = unk84. Hmm, if t were s16, then `t = func_80133784(...)` truncates. The target does `sh v0,28(sp)` (stores the low 16 of the call result) and `andi v0,v0,0x6000` — so the call result is used as s32. If t were s16, `andi` would operate on the sign-extended value → different. So t must stay s32.

Alternative: introduce a separate variable for the else-arm:
```
} else {
    u = t;      /* u s16 */
    t = u - 1;
}
```
Same as c2.

c5: Make `u` an `unsigned char`? Then u = t truncates to 8 bits — wrong.

Let me also try:
c6: `u = t;` but with t being `u32` and u `s32` — plain copy.

c7: What if we swap so the SOURCE outlives: make `t` live longer by using `t` after the else-arm. E.g.:
```
} else {
    u = t;
    t = u - 1;
}
unk84 = t;
```
t is used at the end. Hmm, t's live range: after the copy, t is redefined → dead. To make t outlive u, we'd need t used after u dies. But u dies at `t = u - 1`.

What if we restructure:
```
} else {
    u = t;
    v = u - 1;
}
t = v;  /* hmm */
```
Then u dies at `v = u - 1`, and t... Let's think:
```
s32 t, u, v;
t = unk84;
if (t == 0) { ...; t = 0x1E; v = t; }
else { u = t; v = u - 1; }
unk84 = v;
```
Now: in the else arm, t's last use is the copy; u's use is `v = u - 1`. t and u die at the same point roughly. Hmm, and the target has t in v0 and u in v1 and the store `sh v0,132(s0)` uses v0 (the addiu result). If we use a third var v, the store would use v's reg — could still be v0 if v is allocated to v0 and t freed. Hmm, but t is a different var now (the loaded value) — it dies at the copy, so v0 could be reused.

Hmm, the target's register usage: v0 = t = unk84 initially, then v0 = u-1 (the same register reused for the result). So it's ONE register v0 for the whole value chain, plus v1 for the copy.

So the target: t and the final result share v0; u is a separate v1.

With my restructure: t (loaded) in v0, u in v1, v in v0 (reused after t dies). Might work!

But the question remains whether cse keeps the copy.

Let me look at the actual gcc 2.7.2 cse.c source to settle it. Is it in the repo? docs/gcc-2.7.2-map/ suggests there's documentation. Let me check if the gcc source is available under docs/ or a vendor dir.

Actually — the constraint says never read docs/retired/. docs/gcc-2.7.2-map/ is presumably fine but it's docs. Let me check what's there — it might have the regalloc.md with cse info. Reading a docs file is allowed (not logs/research/PhaseEnds).

Let me grep for cse.c info.

Actually, better use of time: run experiments. Each dt.sh run takes ~30s maybe. Let me prepare a batch of 4-5 candidates and use sc.sh to score them all in one call.

Let me write candidates:

c2: u as s16:
```c
void func_80182ED4(s32 arg0) {
    s32 t;
    s16 u;
    u16 sp10[10];
    u16 x; u16 y; u16 z;
    if ((u32)((Unkstruct_80182ED4 *)arg0)->unkC2 < 3U) {
        t = ((Unkstruct_80182ED4 *)arg0)->unk84;
        if (t == 0) {
            ... same ...
            t = 0x1E;
        } else {
            u = t;
            t = u - 1;
        }
        ((Unkstruct_80182ED4 *)arg0)->unk84 = t;
    }
}
```

c3: u as u16.
c4: u as s16 but with separate v.
c5: plain copy with `u` used twice? no.

Hmm, also consider: maybe the answer is not about `u` at all. What if we make the ELSE arm use a completely different variable and let the copy be `u = t` where `u` is `s32` but t is `u32`? no.

Another thought: what about `u = t;` where the assignment is `u = t` but `u` is a *pointer* type? no.

Another: what if we express `u = t + zr` lever-free as `u = t + 0` where 0 is written as `(s32)(char)0`? The tree folds constants. What about `u = t + z` where `z` is an `s32` local assigned 0 but whose value gcc can't fold? E.g. `z` is a local that is never assigned → gcc treats it as undefined; `u = t + z` → the addend is an uninitialized reg. Not $0.

Hmm, but here's a thought: what if `z` is a local variable that is assigned 0 in a branch gcc can't see? All within the same function → gcc sees it.

What about `z` being a *static* variable (file scope)? `static s32 z;` → `u = t + z` → a memory load, not $0.

What about `z` being a *parameter*? The function signature is `void func_80182ED4(s32 arg0)` — one param. `u = t + arg0` → `addu v1,v0,a0`. Not $0.

So the only way to get `or v1,v0,$zero` is a plain copy — which cse kills.

Hmm, so how did the target get it? Because the target has `u = t + zr` where zr = $0 (hard reg) → RTL `(plus t (reg 0))` → combine folds to `(set u t)` → `or` insn. And cse didn't kill it because at cse time it was a plus.

So lever-free, we need at cse time a non-copy RTL that combine later turns into a copy. The s16 truncation is one: `(set u (sign_extend:HI t))`. combine can fold that to a copy if the value's high bits are known zero. Hmm, but here we need it to be sign_extend that folds...

Wait, actually, maybe I have it backwards. What if `u` is s16 and t is s32, and the RTL is `(set u (sign_extend:HI t))`. combine's rule: "convert (sign_extend:HI (reg)) to a copy if the high bits are known zero" — but also gcc's `nonzero_bits` on the sign_extend result: the result's bits 16-31 are a copy of bit 15. If bit 15 is known 0 → the result == t's low 16 bits, and combine can replace the sign_extend with `(and t 0xffff)`? Hmm, that'd be `andi`.

Alternatively, if combine determines the value equals t (i.e., t's bits 16-31 are zero AND the sign bit handling is consistent) → copy.

We need t's bits 16..31 known zero. t = lh → sign-extended, so bits 16-31 = bit 15 replicated → not known zero. Damn.

BUT: what if we change the LOAD to a zero-extending load? i.e. `t = ((Unkstruct_80182ED4 *)arg0)->unk84;` — unk84 is s16 → `lh`. If we changed the struct access to read it as u16: `t = *(u16 *)&arg0->unk84;` → `lhu` → t's bits 16-31 known zero! But that changes the semantics (sign extension vs zero extension) and the target's load is `lh v0,132(s0)`. So no.

Hmm, unless we keep `lh` but make t's *use* different.

OK so what if the copy direction is reversed: `u` is s32 and `t` is s16?? `u = t` where t is s16 → RTL `(set u (sign_extend:SI t))` → combine: sign_extend:SI of a reg whose bits 16-31 are known = bit 15 → combine might fold `sign_extend:SI (reg)` where the reg is QImode → in gcc, a QImode pseudo used in SI mode → the sign extension is materialized by `sign_extension_from_mode` at expand time → `sll/sra` pair, UNLESS combine sees that the source reg was set by `lh` (which already sign-extends) → combine has a rule: "if the operand is the result of a sign-extending load, the extension is redundant" → combine can then fold to a copy!

Indeed: gcc's combine has `case PLUS: ... /* If we have a sign extension of a reg that was loaded with lh... */`. Hmm, in gcc 2.7 combine.c there IS:
```c
	    /* If we are comparing a sign-extended ... */
```
and
```c
	  /* Handle redundant sign extension of a value that is known to be
	     sign extended already: (sign_extend (reg)) where reg was set by
	     a sign extending operation. */
```
Actually gcc 2.7's combine.c has `known_zero`/`nonzero_bits` and a rule in the PLUS/MINUS handling:
```c
      /* If we have (sign_extend:SI (reg)) where reg's value is known to
	 already be sign extended, ... */
```
Hmm, gcc 2.7 combine.c does have:
```c
	    /* Handle sign extension of a value that is already sign extended.  */
```
I'm not certain.

Empirical path: try `t` as s16 in a separate variable.

Let me define:
```
s32 t;
s16 t16;
...
} else {
    u = t16;    /* u s32 = sign_extend(t16) */
    t = u - 1;
}
```
with `t16 = ((Unkstruct_80182ED4 *)arg0)->unk84;` (s16 load). Hmm but then t16 is loaded separately → the target has ONE `lh v0,132(s0)`.

Hmm: `t = unk84` (s32, sign-extended via lh) and then `u = t` (s32→s32) is the copy.

What if: `t16 = unk84` (s16 var) and `t = t16`? Then t = sign_extend(t16) → the `lh` then sign extension (sll/sra) — wrong (target has no sll/sra).

Hmm, wait: does gcc 2.7 know that a QImode value from `lh` needs no extension? `lh` loads into a register with sign extension; the QImode pseudo holds the truncated value in a 32-bit reg — gcc treats the reg as holding the 16-bit value (QImode), and when used in SI mode it needs sign_extension_from_mode → `sll/sra`. But combine can see the QImode reg was set by `lh` (a sign-extending load) → fold. gcc 2.7 combine does have this:

```c
      /* If this is a sign extension of a quantity that is already
	 sign extended, we can delete it.  */
```
Hmm.

OK. ENOUGH THEORY. Let me look for gcc 2.7.2 source in the project — it might be vendored, which would let me answer these questions definitively. Let me check quickly.

Actually, let me try a different, much more promising route: the **G02-style copy** used `s16` for the COPY variable where the source's range was known. Here the source t is a sign-extended s16 → range -32768..32767.

What if the copy variable `u` is declared **s32** and the source `t` is declared **u16**? I.e. change the load to be zero-extended... no, the load must stay `lh`.

Hmm OK, hold on. Let me reconsider: maybe the copy can be made to survive cse by making `u` and `t` *both* s32 but adding a "use" that forces the copy to stay, e.g.:

```
} else {
    u = t;
    t = u - 1;
    if (u != t) { ... }   /* no */
}
```

Or: what if we write `t = u - 1;` where u is s32 and ALSO store u somewhere? no.

Alternatively, use the `u` variable in a way that's a no-op semantically but creates a second register use... The problem isn't register allocation, it's cse removing the copy.

Hmm, what if the copy's destination is used in a context that requires a register copy, like passing u to a function? There's no call in the else arm.

What if we restructure so the else arm's result is computed via a ternary?
```
t = (t == 0) ? 0x1E : (u = t) - 1;
```
Hmm, `u = t` inside an expression — the assignment's value is t. So `(u = t) - 1` = t - 1. And u is assigned. cse? The RTL for `(u = t) - 1` is `(set u t)` then `(minus u 1)`. Same.

Hmm.

OK let me try yet another angle: what if we DON'T need `u` to be a copy of t, but instead the `move v1,v0` comes from a different expression in the target that I can reproduce?

Target: `lh v0,132(s0)` then `move v1,v0` then `addiu v0,v1,-1` then `sh v0,132(s0)`.

What if the source is:
```
t = unk84;
if (t == 0) { ...; t = 0x1E; }
else { t = t - 1; }   /* no copy */
```
gives `addiu v0,v0,-1`.

What if:
```
u = unk84;         /* u s32 */
t = u;
...
```
Same.

What about the possibility that the `move v1,v0` is the *reload* of a spilled value? no.

Hmm, what about making `u` a value that gcc keeps in a separate register because it's live across the `jal`? No jal in the else path.

WAIT. What about this: in the target, the `move v1,v0` is in the delay slot of `bnez v0`. The delay slot filler (sched1) moved it there. The `move` is a copy of v0 into v1. What if v1's content came from a *different* computation, e.g. v1 = v0 computed as `(plus v0 (reg 0))`?

I keep coming back to needing a hard-reg-0 addend.

Hmm, hold on! What about a DIFFERENT hard register that's already zero? Like... no.

What about `u = t + zr` where `zr` is a *local variable* declared `register`? Not allowed ("no register vars").

Hmm, what about using an `unsigned` zero via a volatile read? no.

OK, let me consider: maybe the intended solution is NOT to preserve `u` as a copy, but to make the whole `else` arm produce `addiu v0,v1,-1` with v1 = a *different* value that happens to equal t.

What if the source is:
```
} else {
    u = t;         /* u s32 */
    t = u - 1;
}
```
vs
```
} else {
    u = t - 1;     /* u = t-1 */
    t = u + 1;     /* → addiu v0,v1,1 */
}
```
wrong sign.

What if:
```
} else {
    u = t;
    unk84 = u - 1;      /* store directly, t not reassigned */
}
```
Then the addiu would be `addiu v0,v1,-1` with v0 = the temp for u-1 — but the target stores to `sh v0,132(s0)` — same! And the `li v0,30` path stores 30.

So:
```
if (t == 0) { ...; t = 0x1E; unk84 = t; }
else { u = t; unk84 = u - 1; }
```
Hmm, the store `sh v0,132(s0)` is common in the target (at 8138, after the join). If we split the stores, we'd get two stores → different asm.

Keep the common store. So we need `t = u - 1` where u is a copy of t.

OK, let me try the empirical route NOW with several candidates. I'll include:
- c2: u s16
- c3: u u16
- c4: u s32 but t declared s16 in else arm via separate var t16 (with `t = t16` semantics) — skip, changes load.
- c5: `u = t` where u is `s32` but declared AFTER t and the copy is the FIRST use...

Hmm, one more idea: gcc's cse copy propagation is defeated if the copy's destination is a **hard register**... no.

Another idea: what if `u` is declared as `s32` but the copy is written as `u = t` and then `t = u - 1` is written as `t = (s32)(s16)u - 1`? no.

Another idea: **the `u` variable could be `volatile`**? no.

Another: use `u` in the STORE: `unk84 = t;` where `t` is `u - 1`...

Honestly, let me check whether the gcc source is available. That would resolve everything. Let me look.

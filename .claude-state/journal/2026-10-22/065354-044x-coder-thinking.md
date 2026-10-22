---
ts: 2026-10-22T12:53:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8LYnAaTAX7ui4ycvycBj
---
VERY informative! Look at C750's IF branch (4614):
```
4614: lui v1, hi(D_80120194)
4618: addiu v1,v1,lo(D_80120194)
461c: addiu a1,v1,25728     (0x6480)
4620: beq a1,v1,4690
```
So here the base &D_80120194 IS in v1 and p = v1 + 0x6480 — exactly the base-relative form, WITHOUT a launder (the current source's IF branch has no launder)!

So in the IF branch, the base is used twice (`p = base + 0x6480` and `if (p != base)`) → 2 uses → kept in a register.

And in the ELSE branch (464c):
```
464c: lui v1, hi(D_80120194)
4650: addiu v1,v1,lo(D_80120194)
4654: j 4664
4658: addiu a1,v1,25996   (delay slot)
465c: (j 4694) ; 4660: move a1,v1
```
Here the base is in v1 too — with the launder (current source). And in my no-launder version, it would fold (as in C2D0).

So: the ELSE branch's base is used ONCE in the source (`p = it + 0x658C`), yet the target keeps it in a register.

Compare the IF branch: `base` used TWICE (in `p = base + 0x6480` and in `if (p != base)`).

**So the theory holds: 2 uses → register; 1 use → folded.**

So the ORIGINAL source of the ELSE branch (and of C2D0) must have used the base twice. How? In the ELSE branch:

```c
} else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    p = it;
    goto found;
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
zero:
    p = 0;
}
```

Hmm! Look at the ELSE branch's copy block: `copy: p = it; goto found;` — it assigns p = it (the found pointer) and jumps to found. And the target's 4660: `move a1,v1` — that's p = it (a1 = p, v1 = it). So p is REUSED for two purposes: first the end bound, then the found pointer!

So in the ELSE branch, `p` has 2 sets: p = it + 0x658C (the bound) and p = it (the found pointer). That's the "pointer reuse" move.

But the BASE (&D_80120194) is still used once (for p = it + 0x658C)...

Hmm! Unless... the original ELSE branch was:

```c
} else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
```
Hmm.

WAIT. What if the original was:

```c
} else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    p = it;
    goto found;
```
The base `it` is used once. Hmm.

BUT hold on! What about the *dead* `p = it + 0x658C` — after the `copy:` block reassigns p, the first p value is dead in that path but live in the loop path.

Hmm, what if the ORIGINAL source had the ELSE branch like the IF branch, i.e.:

```c
} else {
    s32 base = (s32)D_80120194;
    p = base + 0x658C;
    ...
```
still one use.

Hmm, hmm. So how did the original keep the base in a reg in the ELSE branch?

Let me look at the ELSE branch's target code once more:

```
464c: lui v1, hi(D_80120194)
4650: addiu v1,v1,lo(D_80120194)
4654: j 4664
4658: addiu a1,v1,25996    <- delay slot
465c: j 4694
4660: move a1,v1           <- delay slot of 465c (the copy block: p = it)
4664: lui v1, hi(D_801202A0)
4668: addiu v1,v1,lo(D_801202A0)
466c: beq v1,a1,4690
```

AH HA!!! Look at 4660: `move a1,v1` — this is in the "copy" block (p = it). And v1 here = the loop pointer. BUT: notice that the base &D_80120194 was ALSO in v1 (464c-4650) and the copy block's `move a1,v1` copies v1 (the loop pointer).

Hmm, so in the ELSE branch, the base is used once (addiu a1,v1,25996) and still in a register.

Compare with the IF branch: the base is used twice.

So the "2 uses" theory would predict the ELSE branch to fold — but the target doesn't fold. So the theory is wrong, OR the original ELSE branch had 2 uses.

Hmm! What if the original ELSE branch was:

```c
} else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
```
Hmm.

Let me think about the actual game source. This looks like a "table lookup" function. The structure of C750:

```c
s32 func_8012C750(s32 a0) {
    if (*(u16 *)(a0 + 0xA) & 0x800) {
        /* forward scan from base+0x6480 down to base */
        s32 base = (s32)D_80120194;
        p = base + 0x6480;
        if (p != base) {
            do {
                if (*(u16 *)p == 0) goto found;
                p -= 0x10C;
            } while (p != base);
        }
        p = 0;
        goto found;
    } else {
        /* forward scan from D_801202A0 up to base+0x658C */
        it = (s32)D_80120194;
        p = it + 0x658C;
        ...
    }
```

Interesting: the IF branch's base is used twice. The ELSE branch's base is used once. Both branches materialize the base in v1 in the target.

Hmm! But in the ELSE branch, the base's materialization (464c) is in the block that ALSO contains... hmm.

**!!!!! IDEA !!!!!**: What if the ELSE branch's base had TWO uses because the ORIGINAL code was:

```c
    } else {
        it = (s32)D_80120194;
        p = it + 0x658C;
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        if (it == p) goto zero;
```
Hmm, the base `it` is used once...

Hmm, unless the ORIGINAL used a POINTER variable:
```c
    } else {
        u8 *base = D_80120194;
        p = (s32)(base + 0x658C);
```
one use.

OK, radically different idea: **what if the fold is prevented because the base's pseudo is live ACROSS a block boundary in the original?** For the ELSE branch, the base is used in the entry block only.

Hmm, what if the *original* ELSE branch was structured as a loop where the base is the loop's starting point:

```c
    } else {
        it = (s32)D_80120194;
        p = it + 0x658C;
        it += 0x10C;      /* it = D_801202A0 */
        goto test;
    test:
        if (it == p) goto zero;
    body:
        if (*(u16 *)it == 0) goto copy;
        it += 0x10C;
        if (it != p) goto body;
```
Then the base is used twice: `p = it + 0x658C` and `it += 0x10C` — and the second use is a *different* pseudo (the incremented one) but reads the base pseudo → 2 reads of the base pseudo!

Then: would GCC keep the base in a register? With 2 uses, reload's rematerialization decision (cost-based) might prefer a register... Actually reload decides per-reload: `reload_reg` → if the value is a constant, it can either rematerialize (costs an insn each time) or keep it in a reg (costs a reg + 1 insn). With 2 uses: rematerializing twice = 2 lui/addiu pairs (4 insns) vs 1 reg (2 insns + a reg). GCC's reload would pick the register.

BUT: would the second use (it += 0x10C) then produce `addiu v1,v1,0x10C`? That would be WRONG: the target's second materialization is `lui v1, hi(D_801202A0); addiu v1,v1,lo(D_801202A0)` — a fresh symbol materialization, not an addiu of the base.

Hmm! Unless... the RELOCATIONS. Let's look at the target's 4664-4668:
```
4664: lui v1,0x0   R_MIPS_HI16 D_801202A0
4668: addiu v1,v1,0  R_MIPS_LO16 D_801202A0
```
So it IS D_801202A0. If the source had `it = base + 0x10C`, GCC would have to materialize D_801202A0 as a constant (it can fold base+0x10C = D_801202A0 since base is a constant) → the lui/addiu with the reloc on D_801202A0 — EXACTLY what we see! (Because when GCC folds a constant address, the reloc is on the symbol with the addend in the instruction; here the addend is 0 → the reloc is on D_801202A0 with addend 0.)

So `it = base + 0x10C` where base = &D_80120194 → GCC folds to the constant D_801202A0 → materialized as lui/addiu with relocs on D_801202A0 ✓✓.

But hold on: if base is in a register (v1) at that point, then `it = base + 0x10C` would be `addiu v1,v1,0x10C` (using the reg) — not a fresh materialization. Unless the base pseudo's value was folded back to the constant for that use.

Hmm, so in the "it += 0x10C" version, GCC would have the base in a reg for use 1 (p = base + 0x658C) and might use the constant for use 2 → the folded D_801202A0. But then use 1 would also be foldable...

ARGH. OK, the crux is: GCC's cse substitutes the constant at uses when it can. The target shows it did NOT for the base in the ELSE branch (and did for the second symbol D_801202A0 which IS folded as a constant address).

So in the target, the base's pseudo value is NOT a constant, but D_801202A0's IS.

Difference between them:
- D_801202A0: used as a MEM base (lhu v0,0(v1)) and in a compare (beq v1,a1).
- base &D_80120194: used once in a plus.

Hmm, so the second symbol is ALSO kept in a register (v1) and NOT folded into the MEM address (`lhu v0,0(v1)` instead of `lhu v0,D_801202A0`). So even for D_801202A0 (2 uses), GCC kept it in a reg.

But in the IF branch, the base &D_80120194 (2 uses) is also in a reg.

So: in the target, ALL these symbol addresses are kept in registers. Whereas in our no-launder compile, the base gets folded into the plus.

Hmm, so what's different? Let's think about the IF branch in OUR compile: does it keep the base in a reg? The current source (with the launder only in the ELSE branch) scores 0 → so the IF branch's base IS in a reg in our compile too (base used twice) ✓.

And the ELSE branch's D_801202A0 is in a reg in our compile (used as a MEM base + compare) ✓.

Only the ELSE branch's base (used once) is folded in our compile ✗.

So the question remains: why is the ELSE branch's base in a reg in the original?

Possibility: the original ELSE branch's base had 2 uses, one of which was folded (the D_801202A0 materialization) and one which kept it in a reg.

If the original ELSE branch were:
```c
    } else {
        it = (s32)D_80120194;     /* base */
        p = it + 0x658C;          /* use 1 */
        it = it + 0x10C;          /* use 2 → folds to D_801202A0 */
        goto test;
    test:
        if (it == p) goto zero;
    body:
        if (*(u16 *)it == 0) goto copy;
        it += 0x10C;
        if (it != p) goto body;
```
Hmm, but then the source at `test:` would NOT have `it = (s32)D_801202A0;` — the current source has it. But the current source is the decompiler's reconstruction, which had to insert the launder to match. The original could have been either.

Hmm, but wait: in this hypothesized original, `it` (the loop pointer) = base + 0x10C = D_801202A0 — and the loop increments it by 0x10C. The final `it` value would be p = base + 0x658C. ✓ consistent.

Now: would GCC keep the base in a reg for use 1 (p = base + 0x658C) while folding use 2? Hmm, if use 2 (it = base + 0x10C) is folded to the constant D_801202A0, then the base pseudo has 1 remaining use → it could be folded for that use too. Hmm.

UNLESS the fold for use 2 happens at the FRONT END (constant folding of `base + 0x10C` where base is a known constant) — but the front end doesn't know base's value (it's a variable)... unless base is a local initialized with a constant — the front end DOES fold that? In GCC 2.x, the front end's expand_expr for a local variable with a constant initializer: the variable is a MEM; the front end doesn't track its value. BUT GCC 2.x's front end has `fold` on the initializer? No.

Hmm, so at the RTL level, both uses are (plus pseudo_base, const). cse's equiv_constant(pseudo_base) = the symbol constant → BOTH uses get the constant substituted → use 1: (plus symbol_ref 25996) → an address operand (lui/addiu with addend) — the FOLD we see in our compile; use 2: (plus symbol_ref 268) → the constant D_801202A0 → lui/addiu with reloc on D_80120194 + addend 268!!! NOT on D_801202A0!

Hmm! In the target, the second materialization's reloc is on D_801202A0 (with addend 0). So the second symbol was NOT derived from the base by folding; it's an independent constant.

Therefore the original source DID have `it = (s32)D_801202A0;` (a separate constant), as the current source has.

OK so, the original ELSE branch:
```c
    } else {
        it = (s32)D_80120194;   /* base */
        p = it + 0x658C;        /* the bound */
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        if (it == p) goto zero;
    body:
        if (*(u16 *)it == 0) goto copy;
        it += 0x10C;
        if (it != p) goto body;
    zero:
        p = 0;
    }
```

and the base is used ONCE, yet it's in a register in the target.

Hmm, so the "2 uses" theory is dead. So what keeps the base in a reg?

Think about the *IF* branch: the base is used twice: `p = base + 0x6480` and `if (p != base)`. Hmm, note: `if (p != base)` — the compare of p (a register) with base. If base were folded to a constant address, the compare would be against a constant → GCC would materialize it in a reg anyway (for the compare) → so the base IS in a register in the IF branch regardless! That's why the IF branch has no launder: the compare forces the constant into a register, and then `p = base + 0x6480` uses the register (the register already exists, so no extra cost) → the base-relative form emerges!

So the real rule: **if the constant address is needed in a register anyway (for another use), GCC keeps it in a register and uses it base-relative.**

In the ELSE branch, the base has only the plus use → folded.

So the original ELSE branch must have had another use of the base that forced a register... but the only candidate (the D_801202A0 materialization) is a separate symbol.

Hmm!! Unless the original ELSE branch was:

```c
    } else {
        it = (s32)D_80120194;
        p = it + 0x658C;
        ...
copy:
        p = it;
```
Hmm, `copy: p = it` — here `it` is the LOOP pointer.

Hmm, what if the original ELSE branch was actually structured like this (a do-while loop over the base):

```c
    } else {
        it = (s32)D_80120194;
        p = it + 0x658C;
        it += 0x10C;
        ...
```
We showed the second materialization would then have the reloc on D_80120194 with addend 0x10C. The target has the reloc on D_801202A0. Hmm, BUT: hold on! Is that true? Let me look at the ELSE branch's target again:

```
4664: lui v1,0x0    R_MIPS_HI16 D_801202A0
4668: addiu v1,v1,0  R_MIPS_LO16 D_801202A0
```
Yes, D_801202A0.

Hmm, so the source assigned D_801202A0 directly.

OK OK OK. Let me now think about the *other* possibility: the game's compiler was NOT gcc 2.7.2! Maybe it was gcc 2.6 or a different version whose cse didn't fold this. But then the project couldn't reproduce the ROM... yet this project has reproduced hundreds of functions. Hmm, but this function's current source HAS a launder, so the project needed the launder to match — meaning the plain-C source does NOT match with gcc 2.7.2.

Since the phase's task is to find a plain-C spelling that matches, and the "official" answer might be "WALL" (with a tag like cse-const-addr), maybe C2D0 and C750 are walls.

But wait — the moves.md shows several MATCHes for launder items via "real 2nd set" tricks. So there might be a way here too.

Let me think about the *fold* mechanism once more. cse's equiv_constant requires `qty_const[reg_qty[REGNO(x)]]` to be set — i.e. the pseudo's quantity class has a known constant. The quantity is assigned per pseudo; `reg_qty[reg]` is set in `make_regs_eqv` (when a reg is made equivalent to another) or when the pseudo is first seen.

Hmm, here's a thought: **what if the pseudo's value is set by an insn that cse doesn't treat as a "constant set"?** For instance, if the assignment is `it = (s32)D_80120194;` the RTL is (set pseudo (symbol_ref)) → cse records it as a constant.

But what if the assignment is `it = (s32)&D_80120194[0];` → the same.

What if the assignment is via a *cast that isn't a no-op*: e.g. `it = (s32)(u16)D_80120194;` — truncation, wrong value.

What about `it = (s32)(long long)D_80120194;`? A 64-bit conversion → the RTL would be a sign-extension (sll/sra or a word copy) → the value is a REG, not a constant! And the conversion insns might be optimized away (the upper word is a sign extension of the address = 0x80120194 → negative → sll 31; sra 31 → but the value must be exact: (s32)(long long)0x80120194 = 0xFFFFFFFF80120194 → truncated to s32 = 0x80120194 ✓ value-preserving!

But the extra conversion instructions (sll/sra or lw/sw pairs) would appear in the output. Unless GCC optimizes them away: on a 32-bit target, (long long)X → the conversion is: if X is a constant, GCC folds it to the constant (since the value fits in 32 bits, the conversion of a constant is a constant). Folded → same problem.

Hmm.

What about a *float* conversion? `(float)D_80120194` → the value isn't exactly representable → changes semantics.

OK, let me try yet another angle: maybe I can find the game's original source spelling by looking at how OTHER functions in this project were cracked with the same shape. The moves.md mentions "cse-const-addr" walls — e.g. "launder | func_80183098 | WALL cse-const-addr — cse: find_best_addr rematerialises the +4 address for cam->y (lui+addiu) instead of the base reg; only an opaque (asm) base keeps lh 4(s1)".

Note: "only an opaque (asm) base keeps lh 4(s1)" — so in that case, the wall was: the base must be opaque.

And the counter-example: our IF branch (2 uses) keeps the base in a reg naturally.

So the question becomes: **can we give the base a second use that is value-preserving and doesn't add instructions?**

The `copy: p = it;` in C750's ELSE branch — hmm.

IDEA: What if we use the base in the *comparison*? Like:

```c
    } else {
        it = (s32)D_80120194;
        p = it + 0x658C;
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        if (it == p) goto zero;
```
What if we restructure the loop so that the bound is compared against the base + offset, e.g.:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
    if (it != p) goto body;
```
Hmm, p is the bound (a constant address, folded) → the compare would be against a constant → GCC materializes the constant in a reg → but that's the FOLDED constant (D_80120194+0x658C) materialized as lui/addiu with addend → the target has the base-relative form.

Hmm, hmm. But wait!! What if we make the compare use the BASE + offset in a register form? Like:

```c
    base = (s32)D_80120194;
    p = base + 0x658C;
    ...
    if (it != p) goto body;
```
p is a variable → p's value = the constant (folded) → the compare `it != p` → GCC materializes the constant → lui/addiu with addend → folded form. ✗.

What if instead:
```c
    base = (s32)D_80120194;
    ...
    if (it != base + 0x658C) goto body;
```
Then the expression `base + 0x658C` is recomputed at the compare → GCC would CSE it with the earlier computation → same pseudo → the compare uses the folded constant → the constant gets materialized in a reg (for the compare) → lui/addiu with the ADDEND → ✗ (the target has the base-relative addiu).

Hmm, unless the compare's constant materialization would be the SAME as the p computation → and if p's computation (base+0x658C) was already folded into a constant... yeah ✗.

**The fundamental problem**: the constant address &D_80120194 + 0x658C gets materialized with the addend when folded. The target wants the base materialized plainly + an addiu.

So the base MUST be in a register at the point of the plus. The base is in a register if:
(a) it's used elsewhere in a context requiring a register (compare, MEM base), or
(b) its value is opaque (asm).

For the ELSE branch, can we add a use of the base in a compare/MEM context that's value-preserving and instruction-free?

**MEM context**: `*(u16 *)base`?? That would add a load instruction. ✗.

**Compare context**: e.g. `if (base == base)` → the compare folds away (GCC knows it's true) → but does the *use* still force the materialization? If the compare folds to a constant, the base's use disappears → no reg. ✗.

Hmm! What about comparing the base against something that's NOT a constant, e.g. against the loop pointer? That changes semantics.

Hmm, what about this: the `zero:` case in C750's ELSE branch sets p = 0. Hmm.

**What about the `copy: p = it;` in C750?** The source assigns p = it (the found pointer). So p has 2 sets: the bound and the found pointer. If p's first set were computed from the base... hmm.

AH WAIT!!! What about this: **what if the source computes the bound as `p = it + 0x658C` where `it` is the loop pointer variable, and the LOOP POINTER's first value is the base?**

I.e., in the ELSE branch:
```c
    it = (s32)D_80120194;      /* it = base */
    p = it + 0x658C;           /* p = bound */
    goto test;
copy:
    p = it;                    /* p = the found pointer (it has been advanced) */
    goto found;
test:
    it = (s32)D_801202A0;      /* it = the loop pointer */
```
So `it` (one variable) has 3 sets: base, D_801202A0, and the increments.

The base set's pseudo: 1 use (the plus).

Hmm, BUT: what if the ORIGINAL was:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    p = it;
```
where `copy: p = it` uses the LOOP pointer — and the loop pointer's pseudo is the same variable `it`...

Hmm, in C750's ELSE branch, the copy block does `p = it` — this is the "pointer reuse" (p is reused for the bound and the result). And the current source has it.

OK, let me try to think about what the ORIGINAL game source looked like, since we must match it. Let me look at the whole picture of C750:

```c
s32 func_8012C750(s32 a0) {
    if (*(u16 *)(a0 + 0xA) & 0x800) {
        s32 base = (s32)D_80120194;
        p = base + 0x6480;
        if (p != base) {
            do {
                if (*(u16 *)p == 0) goto found;
                p -= 0x10C;
            } while (p != base);
        }
        p = 0;
        goto found;
    } else {
        it = (s32)D_80120194;
        p = it + 0x658C;
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        if (it == p) goto zero;
    body:
        if (*(u16 *)it == 0) goto copy;
        it += 0x10C;
        if (it != p) goto body;
    zero:
        p = 0;
    }
found:
    if (p == 0) { v0 = 0; }
    else {
        *(u16 *)(a0 + 0xA) |= 0x8000;
        v0 = func_8012C890(a0, p, 0);
    }
    return v0;
}
```

Hmm, the IF branch's `base` is used twice: `p = base + 0x6480` and `if (p != base)` (plus the while). The ELSE branch's base is used once.

Since the decompiler's reconstruction produced exactly the target with the launder, and the launder is "NEEDED DIFFERS", the original plain-C source must have differed.

**AH WAIT!!!** What if the ORIGINAL ELSE branch was:

```c
    } else {
        it = (s32)D_80120194;
        p = it + 0x658C;
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        if (it == p) goto zero;
```

Hmm, what if the original had NO separate `it` for the loop but reused the SAME variable, i.e.:

```c
    } else {
        it = (s32)D_80120194;
        p = it + 0x658C;
        it = (s32)D_801202A0;    /* hmm, but then the base's use count is still 1 */
```

Hmm.

**LET ME TRY THE OTHER DIRECTION**: instead of guessing the original, let me EXPERIMENT with spellings that might keep the base in a register. Ideas to test (each 1s):

E1: `p = it + 0x658C;` → `p = 0x658C + it;` (commutative order).
E2: base used in a compare that's value-preserving: `if (it == it) p = it + 0x658C;` — the compare folds.
E3: `p = (s32)(u8 *)it + 0x658C;` hmm.
E4: `p = it + 0x658C;` with `it` declared as `u32`/`unsigned` — the add would be unsigned (same insn).
E5: base as a pointer: `u8 *b = D_80120194; p = (s32)(b + 0x658C);`
E6: `p = it + 0x658C;` where the assignment `it = (s32)D_80120194;` is replaced by `it = (s32)&D_80120194[0];`
E7: use `sizeof`-based tricks? no.
E8: **Make the base's value flow through the `p` variable's first set**: e.g. `p = it; p += 0x658C;` — hmm, tested? Not yet. This gives the base 1 use (the copy) and p 2 sets. The copy `p = it` → cse makes p equivalent to the base → then `p += 0x658C` → the same fold probably.

E9: **Make `it`'s base value used as the source of a MEM address with a variable offset**: no.

E10: What about `p = it + 0x658C;` where the constant 0x658C is written as a *variable* initialized at declaration: `s32 off = 0x658C;` → then p = it + off → the front end: off is a local → MEM → load → the value 25996 is a constant → reload materializes it → `addiu a0, v1, 25996`?? Hmm! Interesting: if `off` is materialized as a constant into a REGISTER (t0), the add would be `addu a0, v1, t0` ✗. But reload might fold it back into an immediate (combine) → `addiu a0, v1, 25996` ✓ and the base stays a REG? Hmm, why would the base stay a reg? Because... hmm, the base would still be folded by cse.

Hmm, BUT: maybe the ORDER matters: if `off` is loaded from memory (a real load), the base's fold...

Honestly, let me just try a batch of spellings and observe. Cheap: 1s each. Let me write ~10 variants for C2D0.

Actually, WAIT. Let me reconsider something fundamental: maybe the fold isn't cse's equiv_constant but reload's rematerialization, and the reason the IF branch keeps the base in a reg is that the base is used in a COMPARE (which forces a register). And in the ELSE branch, the base's use is only the plus.

So the question: **what if the base is used in a compare in the ELSE branch too?** In C750's ELSE branch, is there a compare involving the base? The loop compares `it != p` (the loop pointer vs the bound). No base compare.

Hmm, so the original ELSE branch (and C2D0) must have had the base in a register for another reason.

**!!!!!!!! IDEA !!!!!!!!**: What if the original source's ELSE branch had the base used as a MEM base — because the ORIGINAL loop scanned DOWNWARD from the bound, like the IF branch? No, the code differs.

**!!!!!!!! IDEA 2 !!!!!!!!**: What if the original source was:

```c
    } else {
        it = (s32)D_80120194;
        p = it + 0x658C;
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        if (it == p) goto zero;
    body:
        if (*(u16 *)it == 0) goto copy;
        it += 0x10C;
        if (it != p) goto body;
```

Hmm, what if in the ORIGINAL, `it` was a POINTER (`u8 *it`) and `p` a pointer too? Then `it += 0x10C` is pointer arithmetic and `*(u16 *)it` is a load. The pointer arithmetic on a POINTER variable: `it += 0x10C` → (plus (reg it) (const 268)) — and the load `*(u16*)it` → (mem (reg it) 0). Hmm, same as before.

OK, let me try the pragmatic approach: EXPERIMENT with a batch of spellings. Let me generate variants of C2D0 and score them all. I'll write them programmatically.

Variants (base = the no-launder source):
v1: `p = it + 0x658C;` (baseline, 4)
v2: `p = 0x658C + it;`
v3: pointer decl: `u8 *b = D_80120194; p = (s32)(b + 0x658C);`
v4: `s32 off = 0x658C; p = it + off;`
v5: `p = it; p += 0x658C;`
v6: `it = (s32)&D_80120194[0];`
v7: `it = (s32)(u32)D_80120194;`
v8: `p = it + 0x658C;` with `it` declared `unsigned int`
v9: use the base twice: `p = it + 0x658C; q = it;` (q dead)
v10: `it = (s32)D_80120194; it = it + 0; p = it + 0x658C;` (identity — not allowed but informative)
v11: `it = (s32)D_80120194; p = it + 0x658C;` with the ADD done as `p = it + 0x658C + 0;`
v12: cast the address through a union.
v13: `it = (s32)(char *)D_80120194;`
v14: base assigned from a *pointer-to-pointer* cast: `it = (s32)*(int *)&D_80120194;` — no, that loads.

Let me test v2, v3, v4, v5, v6, v7, v9, v13 first.

Actually hold on, let me think about v9 more: `q = it;` (a dead copy). This creates a second USE of the base pseudo. If GCC's decision to fold is based on the use count (reload's rematerialization cost), this might keep the base in a register! But cse's equiv_constant substitution is not use-count-based; it substitutes the constant at every use. Hmm, but the *reload* pass decides. Hmm.

Actually, let's think about where the fold happens, empirically: let me use the cc1 dump to see the RTL at various stages. That's the scientific way, and the tools exist (tools/cc1_dumps_tu.sh). Let me check the tool.

Given the time budget (20-30 min per item, 4 items), I've used ~25 min on item 2 already (started 06:37, now ~07:00). Hmm, the budget says 20-30 min per item. I'm at ~25 min for item 2 without a result. I should be efficient.

Let me do a quick batch experiment (10 variants, ~15s) and then decide.

Actually, hold on! Let me reconsider the problem from the "how did the original compile" angle ONE more time, with fresh eyes:

The original game's source for C2D0 might be:

```c
s32 func_8012C2D0() {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
```

Hmm, what if `D_80120194` was declared in the game's source as a **pointer variable** rather than an array?! E.g.:

```c
extern u8 *D_80120194;   /* a POINTER at address 0x80120194 */
```
Then `(s32)D_80120194` would LOAD the pointer's value from memory → an `lw` instruction → ✗ (the target has lui/addiu).

What if it was declared as `extern u8 D_80120194[];` — the address. ✓ as we have.

Hmm, what if the game source had:
```c
    it = (s32)(u8 *)&D_80120194[0];
```
same.

OK, ANOTHER THOUGHT: what if the ORIGINAL source didn't compute `p = base + 0x658C` but rather had a *second global* for the end address, e.g. `p = (s32)D_80126720;`? Then the target would show lui/addiu for D_80126720 (a plain materialization, no addend) — but the target shows base+offset. ✗.

Hmm, what if the original had:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
and the ROM was compiled by gcc 2.7.2 with `-O2` but ALSO with something like `-fno-...`? Hmm.

Hmm, hold on!! What about **`-G0` vs `-G8`** and the "small data" section? Not relevant.

**WAIT A SECOND**. What about the *order* of the two statements in the RTL and the "jump threading"? Hmm.

Let me look at the ACTUAL cc1 dump to see where the fold happens. That's the fastest way to certainty. Let me check tools/cc1_dumps_tu.sh.

---
ts: 2026-10-22T09:25:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_AAMPygtTV80Eax0ElH1W
---
In the RTL (post-expand) the tree is `(plus:SI (symbol_ref D_80195AF6) (reg:SI 118))` = POINTER FIRST! And combine swapped it to `(plus (reg 118) (symbol_ref))` = index first.

So combine swaps the commutative plus when one operand is a symbol_ref (constant) — the canonical form puts the *constant* second? No wait: it put the symbol_ref SECOND (index first, symbol second). Before: symbol first, reg second. After: reg first, symbol second. So combine moved the constant to the second position. That's the classic canonicalization: "if one operand is a constant, put it in the second operand" — that's for commutative ops.

But in the TARGET the result was pointer-first (addu v0,a1,v0) — meaning the target's tree had a REG pointer (a1), not a symbol_ref, so the constant-canonicalization didn't apply! In the target, the pointer was materialized into a register (a1) and the add was (plus a1 v0) → addu v0,a1,v0.

Wait but in ours, the pointer is also materialized into a1 (`lui a1; addiu a1`). Hmm — in ours the symbol_ref survived into the plus and became the reload operand, while in the target the pointer was a pseudo reg.

So the difference: in the target, the pointer value was in a PSEUDO (a register) at the point of the add; in ours, the tree used the symbol_ref directly.

Why? Because of the launder in orig! The orig.c had `__asm__("" : "=r"(p) : "0"(p));` which makes p a hard register → the tree uses (reg p) → pointer first.

Without the launder, p = D_80195AF6 is a constant → cse/combine substitutes symbol_ref → swapped.

So to get the target's order lever-free, we need the pointer to be in a register at the add, without a pin/asm. How?

Ideas:
1. Make `p` non-constant: e.g. `p = D_80195AF6; p = p + 0;`? That's identity laundering → not allowed ("identity-statement launders do NOT count as a crack"). Also combine would fold.
2. Make the address come from a load: e.g. `p = *(D_80195AF6_t **)&D_80195AF6`? changes semantics.
3. Use a different expression: the target's address add uses a1 = the pointer register. In the target, the pointer a1 was materialized earlier: `lui a1; addiu a1,a1,0` at the top of the arm, and reused for the add. In ours, that same `lui a1; addiu a1` exists (it's the same in both since the diff was only 1 insn!). Wait, ours has `lui a1,0x0; addiu a1,a1,0` too? The diff showed only the one insn differing, so yes — both have lui a1/addiu a1 somewhere. Hmm, in ours, that a1 might be used for the OTHER load (the newval load at `addu at,at,v0` — target uses `at` for that).

Hmm, let me look at our asm to compare. Let me objdump our candidate object and diff the two asm listings side by side around that region.

From the target:
```
lui  a1,0x0        ; (arm 2 start)
addiu a1,a1,0
lui  at,0x0
addu at,at,v0
lh   v0,0(at)
...
lh   v0,256(s0)    ; unk100
lui  v1,0x0
lhu  v1,0(v1)
li   s1,1
sh   a0,14(s0)
sll  v0,v0,0x3
addu v0,a1,v0      ; <- a1 is the pointer (materialized at arm start!)
lh   v0,4(v0)
```
So the target reuses the a1 materialized at the arm's start for the final address add. The tree (plus a1 v0) with a1 a reg.

In ours, what does the asm look like? The pointer is a symbol_ref in the plus, so the reload of the symbol would produce lui/addiu into a reg... but the add's operands: (plus 118 symbol) → after reload, symbol_ref in an address context → "lui a1; addiu a1,a1,0" then "addu v0,v0,a1" — the operand order preserved from the tree (index first, pointer second) and the pointer materialized into a1.

So the ONLY difference is the operand order in the plus tree, decided by combine's constant-canonicalization (constant → second).

Now: how to make the pointer a non-constant register in the tree, lever-free?

Option A: Make the pointer's value come from something non-constant but semantically identical — e.g. a pointer loaded from a constant address? That changes semantics (extra load).

Option B: Use `p` as a pointer to a struct member: e.g. `D_801270C8 = *(s16 *)((u8 *)&D_80195AF6[0] + off + 4);` — same constant.

Option C: Force the address through a *different* variable that isn't a constant... but any copy of a constant address folds.

Option D: Change the arithmetic so the symbol_ref is not one of the plus operands: e.g. compute the address as `p + off` where off contains a constant that makes the whole thing a symbol? no.

Option E: What if the sum is computed as (plus (symbol_ref) (reg)) but combine doesn't swap because... the swap rule might be "if x is a constant (CONST_INT or SYMBOL_REF) and y is not, swap so the constant is second"? We saw symbol first → swapped to symbol second. So to keep symbol first, we need the tree to be born with the symbol second? No — we need the *result* to be (plus symbol reg) i.e. pointer first. Since combine canonicalizes to constant-second, the result is always (plus reg symbol) = index first. Unless the operand is not recognized as a constant at combine time.

Combine's rule (gcc 2.7 combine.c, in `simplify_rtx`? or in the commutative handling): I recall in combine.c:

```
	  /* If we have a commutative operation and one operand is a constant,
	     put the constant in the second operand.  */
```
Actually the relevant code in gcc 2.7.2 combine.c `simplify_rtx`... hmm. There's also in `combine_insns`:

```
	      if (COMMUTATIVE_P (code) && GET_CODE (x) == CONST_INT ...)
```

Whatever the exact code, the rule applies to CONST_INT and SYMBOL_REF? Our evidence: symbol_ref moved to second.

Now — how did the TARGET get (plus a1 v0)? Because in the target's tree the pointer was a REG (pseudo). That means in the original source the pointer was NOT a plain constant assignment. E.g. the original might have been:

```c
D_80195AF6_t *p;
...
p = &D_80195AF6[0];   /* still constant */
```
Hmm.

OR the original code computed the address differently, e.g.:
```c
D_801270C8 = *(s16 *)(D_80195AF6 + unk100 * 8 + 4);
```
no.

Wait — maybe the target's tree was (plus (reg a1) (reg v0)) because the a1 pseudo was *already* there for another use! Look at the target asm: `lui a1; addiu a1,a1,0` at the start of the arm, then `lui at; addu at,at,v0` for the newval load — so the arm materializes the address twice: once into a1 and once into at. That "twice" suggests two separate uses of the same constant address: one for the load (at) and one for the add (a1). In the original source, maybe:

```c
p = D_80195AF6;              /* used for the final address */
newval = D_80195AF6[idx].f0; /* separate expression, folded to at */
```
And the `p` was materialized into a1 because it's used... hmm, but if p is a constant, combine would use the symbol_ref in the plus and the reload would materialize it into a reg at the add — which is exactly what ours does (a1 holds it) but with the swapped operand order.

Hmm! So in ours, the pointer IS in a1 at the add; the difference is just the order in the plus tree. So the target's tree must have had the pointer in a reg at combine time.

So the question: how to make combine see a REG (pseudo) instead of symbol_ref for the pointer at that point?

Combine's reg_equiv substitution: in the rtl dump, insn 176: `(set (reg/v:SI 112) (symbol_ref D_80195AF6))` — p's pseudo 112 is set to the symbol. Then insn 190 uses (plus (symbol_ref) (reg 118)) — wait, the RTL already has the symbol_ref directly in the plus at expand time! Because expand did constant propagation? Actually insn 190 in the RTL dump already reads (plus (symbol_ref D_80195AF6) (reg 118)) — the pseudo 112 isn't used at all? Then what is 112 used for? Perhaps 112 is the value for the other load (D_80195AF6[idx].f0) — but that used `at` (symbol_ref directly) too.

So expand emitted (plus (symbol_ref) (reg 118)) — pointer first! — and combine swapped it.

Now, what does combine do? In gcc 2.7.2 combine.c, there is this (I'm now quite sure) in `simplify_rtx`/`simplify_binary`... Let me find the actual gcc source. Maybe pip/apt has gcc-2.7 source? Not likely. But we have the binary; maybe strings in cc1 reveal. Alternatively, I can test empirically with a small standalone C file compiled with the same cc1! That's much cheaper than the full TU: write a tiny C file with a similar pattern and compile with the toolchain to see the operand order. E.g.:

```c
extern int A[100];
extern int B;
int f(int i) { int *p = A; return *(short*)((char*)p + i*8 + 4); }
```
compile with gcc-2.7.2-psx and see if it's `addu v0,v0,a1` (index first) or `addu v0,a1,v0`.

Then experiment with spellings to find one that yields pointer-first. That's a fast experimental loop! And then apply the winning spelling to the real body.

But caution: the real context (register allocation, etc.) may differ. Still, it gives a hypothesis generator.

Let me find the toolchain: tools/bin/gcc-2.7.2-psx/. Use cc1 directly on a .i file, or the gcc driver? Let me check what's in tools/bin/gcc-2.7.2-psx/.

Let me try compiling a small test.

Important: how does combine decide to swap? Let me think about gcc 2.7.2 combine.c source. I recall this snippet from combine.c (function `simplify_rtx`? no, from `combine_insns`):

```c
	    case PLUS:
	      ...
	      /* If we have a plus of a symbol and something, ... */
```

Hmm, actually I recall in gcc-2.7.2 combine.c there's:

```c
	  /* Now simplify the operands of commutative operations... */
```

Honestly, empirical is faster.

Also note: gcc 2.7 combine has this documented behavior in its comments (from gcc 2.95 combine.c):

```c
	  /* If we have a commutative operation and one operand is a constant
	     and the other is not, and the constant is not a valid address,
	     put the constant in the second operand.  */
```

Yes! In gcc 2.95's combine.c there is:

```c
      /* If we are adding a constant to a memory location, ... */
```

Hmm, but there's definitely this in gcc's combine.c (2.x):

```c
	  /* If we have a commutative operation with one operand being a
	     constant, we can always put the constant in the second
	     operand.  This is a win for the canonical form. */
```

But careful: for PLUS with a SYMBOL_REF as an *address* operand, the canonical form matters for the "plus" with memory. Actually gcc has a specific rule about canonicalizing address forms: in `plus`, the constant must be last? Hmm, actually gcc's canonical form for plus is: (plus X (const_int)) — constants last.

But our observation: symbol_ref moved from first to second — consistent with "constants last" (symbol_ref counts as a constant-like for canonicalization).

BUT WAIT: if constants must be last, then the *target* (plus a1 v0) has the pointer (a1, a reg) first and the index (v0, a reg) second — no constant at all, so no canonicalization.

So we need the pointer to be a REG at combine time. In the target, that's what happened — meaning the original source's pointer was NOT a compile-time constant in the tree. How?

Possibility: the original source used a pointer variable that was assigned in a way that isn't foldable, e.g.:

```c
D_80195AF6_t *p = D_80195AF6;   /* p = &D_80195AF6[0] */
```
That IS constant.

Hmm, but maybe in the target the pointer came from a *different* variable, e.g. `p` was set earlier in the function and reused... In the target's arm, `lui a1; addiu a1,a1,0` — a1 is used ONLY for the final add? Let's check the whole function's asm for a1 usage. If a1 is used elsewhere, it might be a callee-saved-ish pseudo.

Alternatively the original might have been:

```c
D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
where p was declared as a *parameter* or a global pointer variable (not a local constant). E.g. if `p` were a file-scope variable `D_80195AF6_t *p` — no, then the load would be from memory.

Hmm, what if p is a local pointer assigned from a *function call* result? No, the asm has lui/addiu of the constant.

What if the source used `&D_80195AF6[0]`? Same.

What about a *cast through an integer*: `(u8 *)((s32)D_80195AF6)` — same constant.

Hmm, what if p's value is used in TWO places such that gcc keeps it in a reg (a "pseudo" that's used twice)? In our source, p is used only ONCE (the final load). In the target, the pointer appears twice (a1 at arm start, at for the newval load) — but the `at` one is the separate expression `D_80195AF6[idx].f0`.

Look at the target asm again:
```
lui  a1,0x0
addiu a1,a1,0     ; a1 = &D_80195AF6  (arm start)
lui  at,0x0
addu at,at,v0     ; at = &D_80195AF6 + v0
lh   v0,0(at)
```
Wait, `addu at,at,v0` — the newval load address = &D_80195AF6 + idx (byte offset idx, since the struct is 1 byte?). Hmm, earlier I wondered about the struct size. If D_80195AF6_t is 1 byte then `D_80195AF6[idx].f0` is at byte offset idx. But `f0` is s16 → lh at byte offset idx → unaligned but fine.

Hmm OK. And then:
```
lh   v0,256(s0)    ; unk100
lui  v1,0x0
lhu  v1,0(v1)      ; another global
li   s1,1
sh   a0,14(s0)
sll  v0,v0,0x3
addu v0,a1,v0      ; &D_80195AF6 + idx*8
lh   v0,4(v0)
```
So a1 (materialized at the arm start) is used only here, at the add. So the compiler kept the pointer in a register (a1) across the whole arm — a pseudo that survived from the arm's start to the add. That's a *pseudo* that was born at the arm start (maybe as the value of p) and used at the add, with combine substituting...

Hmm, but combine substitutes reg_equiv of a pseudo set to a constant: p's pseudo 112 = symbol_ref. If p (112) is used at the add, combine replaces (reg 112) with (symbol_ref) → (plus (symbol_ref) (reg 118)) → then the constant-canonicalization swaps to (plus 118 symbol). Hmm, but the RTL dump already showed the plus with symbol_ref — that's after expand did the substitution? Expand wouldn't substitute. Actually the RTL dump (after expand) already shows (plus (symbol_ref) (reg 118)) — so expand itself folded the constant into the plus? That's expand's job (expand does constant folding into addresses). Actually, at expand, `p` is a pseudo with the constant value; expand emits `(set (reg p) (symbol_ref))` and then uses of p become (reg p) normally. But the dump shows the plus using symbol_ref directly — that's because expand's `expand_expr` for the address... hmm, or because the "rtl" dump is after some optimization (the dump named .rtl is after expand but before combine? The rtl dump's insn 190 shows the symbol in the plus, so the substitution happened before combine).

Anyway: the key question is how to make the tree (plus reg reg) rather than (plus reg symbol_ref).

Option: make `p` a pointer to a *volatile*? Not allowed (barrier? volatile is a class C lever maybe; also "lever-free = none of the row kinds remain: no pin, launder, barrier, keepalive"). Volatile might count as a barrier-ish lever? The row kind is "launder" only. The constraint says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." So adding a volatile would be "a new lever of any kind" → not allowed. Hmm, "no new lever of any kind" — so I can't add volatile.

So we need the pointer to be in a reg without any lever. Options:
- Make the pointer come from a *variable* that's not a constant: e.g. a static/global pointer variable. But that changes semantics (the original doesn't have one) — and the asm would differ (a load).

Hmm. But wait — maybe we can get the pointer into a reg by using it in a way that forces a register: e.g. use `p` in TWO places so that combine keeps a pseudo? No: both uses fold to the symbol.

Alternative: change the arithmetic so the add is (plus reg reg): e.g. compute the address as `p + off` where the pointer is added as an *offset* rather than a base: e.g. `*(s16 *)((u8 *)off + (s32)p)`? Then the tree is (plus (reg off) (reg p)) — but p's reg_equiv folds to symbol_ref again.

Hmm, the canonicalization puts the constant last. In the target, the pointer is FIRST and the index SECOND, and the pointer is a reg. What if we could arrange the tree as (plus (reg ptr) (reg idx)) where the ptr pseudo is NOT foldable to a symbol? Then combine wouldn't canonicalize.

What if the pointer is derived from a *cast of an integer that is not a constant*? e.g. `(u8 *)((s32)p + 0)` → identity, folds.

What if the pointer is the result of a conditional? e.g. `p = cond ? D_80195AF6 : D_80195AF6;` → expand would still fold to a constant... maybe not! A conditional expression produces a phi/branch, not a constant. But that changes the asm (adds branches) → count mismatch.

Hmm. What about this: the pointer could be a REG if it's *not* known to be the constant at expand time but becomes it later. Hmm.

Wait, wait. Let me reconsider. Maybe the ordering is decided NOT by combine's constant canonicalization but by something else, and the difference between the target and ours might be in a different place. Let me verify by dumping the TARGET's RTL... we don't have it. Hmm.

But here's a thought: the target is the ORIGINAL game's compiled code (from the ROM's original source, which we don't have). The decomp project's goal is to reproduce it. The original source may have differed from our current def (e.g. used a pointer variable loaded from a table). But the project's premise is that the decompiled source is close to the original.

Let me test the hypothesis quickly with a standalone file compiled by the same cc1: does `(u8*)p + off` with p constant produce index-first? And is there a spelling that produces pointer-first?

Experiments to try in standalone:
1. `int *p = A; return *(short*)((char*)p + i*8 + 4);`
2. Same with `off` variable.
3. Same but with p as a *function parameter* (not constant): `int f(int *p, int i) { return *(short*)((char*)p + i*8+4); }` → tree (plus (reg p) (reg idx)) → pointer first! And in the real function, p is a local constant...

Hmm! But here's the thing: in the real function, the pointer IS a local initialized to a constant. What if we make it a *parameter*? Not allowed (signature change).

What if we keep the pointer in a register by using it as the base of a load and ALSO... hmm.

Alternative idea: maybe the tree can be (plus (reg ptr) (reg idx)) if the pointer is a **pseudo whose reg_equiv is not a symbol** — e.g. if the pointer is assigned from a *volatile* global. Not allowed.

Hmm, what about: the target's pointer a1 might not be the address D_80195AF6 at all! Let's check: `lui a1,0x0; addiu a1,a1,0` — the relocations tell which symbol. Let me dump relocations for the target object to see which symbol a1 holds. The objdump -dr output I printed filtered out R_MIPS lines! Let me re-dump with relocations to identify the symbols.

That could change the picture: maybe a1 = &D_80195AF6 (the pointer) or something else.

Let me check relocations.

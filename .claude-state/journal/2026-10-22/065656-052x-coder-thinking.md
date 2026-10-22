---
ts: 2026-10-22T12:56:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_mkp58ldTnW83w28vOhsW
---
I'm spending a lot of time. Let me switch to the empirical batch search NOW, and in parallel think.

Key insight to exploit: **the fold happens because the pseudo's value is a known constant at the use**. The ONLY way to keep it in a register is for the value to be unknown.

Since the value must be the constant address, and cse knows it...

**UNLESS the pseudo is used in a context where cse can't apply the substitution!** Look at the code: `validate_change (insn, &SET_SRC (sets[i].rtl), trial, 0)` — the substitution is only applied if it's VALID for the insn. For `addsi3` (a 3-operand add), the source (plus (reg) (const)) is fine to replace with a constant.

Hmm, but what if the use were a MEM address? E.g. if the base were used as `*(u16*)it` — the MEM's address (reg it) → substituting the constant would give a MEM with a constant address → valid → but then the backend would use the absolute address form... Hmm.

**AH WAIT!!! WHAT IF WE MAKE THE USE A MEM-FORM (like the target's `lhu v0,0(v1)`)?** In the target, the second symbol D_801202A0 IS used as a MEM base and stays in a register! Because cse's substitution of the constant into the MEM address... hmm, it apparently did NOT (the target has `lhu v0,0(v1)`).

Hmm! So for the second symbol, cse did NOT substitute the constant into the MEM. Why? Because the MEM's address (reg v1) with the constant substituted becomes (mem (plus (symbol_ref) (const 0))) → hmm, that's a valid MEM → but cse's validate_change might reject it (the MEM's address must be a valid address; a constant address IS valid for mips). Hmm, but the target shows `lhu v0,0(v1)` — so it wasn't substituted.

Hmm! Interesting. So the substitution DIDN'T happen for the second symbol (2 uses). Maybe because the substitution happens only once per pseudo (the first use), and the second use keeps the reg? Hmm, in cse the substitution is per-insn.

Wait, actually, maybe the reason is different: the second symbol's pseudo is used in the MEM and in the compare. The compare REQUIRES a register operand → so the pseudo must be in a register → cse's substitution into the compare is invalid (a compare needs a reg) → so the pseudo stays in a reg → and the MEM then uses the reg.

And for the first symbol (base), the only use is the plus → valid to substitute → folded.

**So the rule is: a use that REQUIRES a register (a compare, a MEM base?) keeps the value in a register.**

Hmm! So what if we make the base's use a COMPARE?! In C2D0, is there any compare involving the base? What if we restructure the loop so the bound is compared against the base+offset... no.

Hmm, hold on! What about the MEM case: `lhu v0,0(v1)` — the MEM's address is (reg v1) — substituting the constant would give a MEM with a constant address, which for MIPS is valid (lui+addiu with the address) — hmm, but the backend prefers... hmm, it clearly didn't substitute.

Hmm, cse's `validate_change` for a MEM address: replacing (reg v1) with (symbol_ref) in a MEM → the MEM becomes (mem (symbol_ref)) → that's a valid MEM on MIPS. But `validate_change` checks the mode and the machine's constraints. Hmm, maybe it failed because the MEM's address mode requires a register for the "0(v1)" form? No, a constant address MEM is fine.

Hmm, whatever the reason, empirically: the second symbol (used in a MEM + a compare) stayed in a register.

**SO: if I can make the base's value be used in a MEM, it stays in a register!**

In C2D0, is there a way to make the base's address used in a MEM without adding instructions? Hmm: `*(u16 *)it` — but the base isn't dereferenced in the original semantics.

Hmm, but WAIT: what if we restructure the loop to use the base as a MEM base in a way that's equivalent? E.g.:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
Hmm.

What about the ZERO test: `if (*(u16 *)it == 0) goto copy;` — the loop pointer is dereferenced. If the loop pointer were the BASE... no.

Hmm hmm. OK, what about the compare idea for C750 (which has a0)? no.

**LET ME TRY THE MEM IDEA**: in C2D0, the base is &D_80120194 and the loop starts at D_801202A0 = base + 0x10C. What if the source were:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
test:
    it = (s32)D_801202A0;
```
Hmm, what if instead we write the loop start as `it = it + 0x10C;` (base + 0x10C)? Then the base has 2 uses: the plus and the increment. And the increment `it = base + 0x10C` → the result is a constant → D_801202A0 (folded) → materialized as lui/addiu with reloc D_80120194 + addend 0x10C ✗ (the target has reloc D_801202A0 with addend 0).

Hmm! BUT: what if GCC materializes it as `lui v1, hi(D_80120194); addiu v1,v1,0x10C`? The reloc would be HI16/LO16 on D_80120194 with the addend 0x10C in the instruction. The target has D_801202A0. ✗.

OK, so the second materialization must come from a direct `D_801202A0` reference.

Hmm, so in the ORIGINAL, the base &D_80120194 was used ONCE and stayed in a register.

**THE ANSWER MUST BE: the original's base pseudo had a value that cse could not substitute at the use.** What if the base pseudo's value was NOT the symbol_ref but a REG (i.e., the base was loaded from a register)?

**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**
**THE `p` VARIABLE'S FIRST SET IS THE BOUND; WHAT IF THE ORIGINAL COMPUTED THE BOUND AS `p = it + 0x658C` WHERE `it` WAS THE *LOOP POINTER* VARIABLE AND THE LOOP POINTER'S FIRST VALUE WAS THE BASE?!**

I keep coming back to this. Let me carefully re-derive what the original could have been, using the constraint that the target has:
- base &D_80120194 materialized in v1, used once (the plus) → v1.
- D_801202A0 materialized in v1 (reusing the same reg), used in the compare and the MEM.

Since the base and D_801202A0 share v1, and the base is dead before D_801202A0 is set, they don't conflict.

Now, what if the original source was:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
zero:
    return 0;
}
```

and the ORIGINAL COMPILER was gcc 2.7.2 but with the *variable `it` being a pointer*? Let me actually TEST the pointer spelling! With `u8 *it`, the front end's expand of `it = D_80120194;` → (set 73 (symbol_ref)) — the same. Hmm.

BUT: with a POINTER type, `p = it + 0x658C` — hmm, `p` would be a pointer too: `p = it + 0x658C` → the same PLUS.

Hmm, what if `p` is a pointer and `it` is a pointer, and the comparison `it == p` compares pointers → the same.

OK, let me try the "MEM base" idea concretely for C2D0, because that's the most promising mechanism (the second symbol stayed in a register BECAUSE of the MEM use).

**How can the base be used as a MEM base without adding instructions?**

In C2D0, the base is D_80120194 and the loop scans from D_801202A0. The target's `lhu v0,0(v1)` dereferences the loop pointer.

What if the source's loop pointer were the BASE and the base's offset handled differently? E.g.:

```c
    it = (s32)D_80120194;      /* base */
    p = it + 0x658C;           /* bound */
    ...
body:
    if (*(u16 *)it == 0) goto copy;   /* deref the base?? */
```
No — the loop starts at D_801202A0.

Hmm, so the base is never dereferenced. ✗.

**THE COMPARE IDEA**: could the base be compared with something? In C2D0: `if (it == p)` compares the loop pointer with the bound. What if the original was:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
```

What if the original had:
```c
    base = (s32)D_80120194;
    p = base + 0x658C;
    ...
    if (it == p) goto zero;
```
Same.

Hmm, what if the original's loop was structured as a do-while with the base as the starting point:

```c
    base = (s32)D_80120194;
    p = base + 0x658C;
    it = base;          /* hmm */
```

Hmm.

**!!!!!!!!!! WAIT !!!!!!!!!!** What about the FIRST materialization being of a DIFFERENT symbol?! Look at the target's relocs once more:

C2D0:
```
4178: lui v1  HI16 D_80120194
417c: addiu v1 LO16 D_80120194
4184: addiu a0,v1,25996
```
C750 ELSE:
```
464c: lui v1  HI16 D_80120194
4650: addiu v1 LO16 D_80120194
4658: addiu a1,v1,25996
```

Both have the base in v1. And in C750's IF branch:
```
4614: lui v1 HI16 D_80120194
4618: addiu v1 LO16 D_80120194
461c: addiu a1,v1,25728
4620: beq a1,v1,4690
```

So in the IF branch the base is in v1 and used twice.

Now: in the ELSE branch, is the base perhaps used in a COMPARE that I've missed? The ELSE branch's code: 464c-4660 then the test block. Hmm, no compare with the base.

Hmm, so in the ELSE branch the base is used ONCE, and it stays in a register.

=> The ONLY remaining explanation: **in the ELSE branch, the base's pseudo was NOT a plain constant at the use**, i.e. the source's assignment `it = (s32)D_80120194;` was NOT the original spelling.

**WHAT IF THE ORIGINAL SPELLING WAS `it = (s32)(u8 *)D_80120194;`?** → hmm, the RTL: (set 73 (symbol_ref)) — same.

**WHAT IF THE ORIGINAL USED A MACRO LIKE `((s32)&D_80120194[0])`?** same.

**WHAT IF THE ORIGINAL HAD `it` AS A `u8 *` AND `p` AS A `u8 *`, AND THE COMPARE `it == p` WAS A POINTER COMPARE?** → the RTL is the same.

Hmm, so the RTL would be identical regardless of the C types. So the ORIGINAL's RTL must have differed.

**THE ORIGINAL'S RTL MUST HAVE HAD THE BASE IN A REG.** Which means the original's assignment was NOT a plain constant assignment.

WAIT!!! What if the original was:

```c
    it = (s32)D_80120194;
```
but `D_80120194` was declared in the game's source as **`extern u32 D_80120194;`** — a scalar! Then `&D_80120194` vs `D_80120194`: for a scalar, `(s32)D_80120194` would be a LOAD (the contents), not the address ✗ (the target has lui/addiu = the address).

Hmm. What if the game's source had a POINTER variable at a fixed address whose VALUE is the address of the table? That would be an lw ✗.

**WHAT IF THE ORIGINAL TOOK THE ADDRESS OF A *LOCAL* VARIABLE?** No (the reloc is a global).

**WHAT IF THE ORIGINAL DID `it = (s32)&someGlobal[0]` WHERE someGlobal IS IN A DIFFERENT SECTION** — the address would still be constant.

Hmm, hold on! What about the possibility that the original computed the base as a **difference of two symbols**? e.g. `it = (s32)(D_801202A0 - 0x10C);` → the front end folds this to the constant D_80120194 → the RTL: (set 73 (symbol_ref D_80120194)) → the same → folded ✗.

Hmm, BUT WAIT: what if the difference is computed at RUNTIME via pointer arithmetic on two DIFFERENT symbols, e.g.:

```c
    it = (s32)D_801202A0 - 0x10C;
```
Front-end folds ✗.

OK, what if the original used a variable offset that is runtime-valued? In C750 there's `a0`! For C750's ELSE branch, hmm.

Hmm, hold on!!! Let me reconsider the C750 ELSE branch. What if the original ELSE branch was NOT the "scan upward from D_801202A0" but something else, and the decompiler's reconstruction (with the launder) coincidentally matches?

Ugh.

**LET ME TRY THE MOST DIRECT EXPERIMENT**: what if the base's use is a COMPARE? Let me test whether a compare use keeps the constant in a register, by writing a variant of C2D0 where the base is compared (semantically neutral):

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    if (it == (s32)D_80120194) goto test;   /* always true; the compare folds */
```
The compare folds (GCC knows both are the same constant) → probably no effect.

Hmm.

**LET ME TRY: what if the base is used in a MEM-like expression that folds to the same address?** e.g. `p = (s32)&((u8*)D_80120194)[0x658C];` — the front end folds to a constant address ✗.

OK. Let me try the pragmatic path: **maybe the answer is that the base's pseudo must have 2 sets in the SAME BLOCK, and cse's n_sets condition is per-block**. From the n2 experiment, the note was still added (with 5 sets in the block). Hmm, but maybe the note was added by a DIFFERENT code path (the `qty_const_insn` update path, which doesn't check n_sets).

Looking at the code at line 1382-1401 (in `record_equiv`/`make_regs_eqv`?):
```c
  else if (GET_CODE (x) == REG && classp && ! qty_const[reg_qty[REGNO (x)]]
	   && ! elt->is_const)
    { ... qty_const[reg_qty[REGNO(x)]] = ...; }
```
This sets qty_const for the pseudo's quantity → then equiv_constant(pseudo) returns the constant → the substitution at the use.

And the quantity for a pseudo with 2 sets: cse's `make_regs_eqv` splits quantities when a pseudo is set twice. Hmm, but in the n2 case, the second set (insn 12) has the symbol_ref, and the use at insn 15 → qty_const for the quantity of the use → the constant.

So the pseudo's *quantity* (as cse sees it) has a single set → the constant is known.

**To defeat: the quantity must have 2+ sets.** cse splits a pseudo into quantities when it sees a second set with a DIFFERENT value (`make_regs_eqv` / `split`?). Hmm, in n2, the first set was 0 and the second the symbol → so the pseudo was split into 2 quantities: quantity A (before insn 12) and quantity B (after). The use at insn 15 belongs to quantity B, which has 1 set (the symbol_ref) → constant known ✗.

So: to defeat, the pseudo must have 2 sets with the SAME value... no wait, then they'd be one quantity (cse merges equal values) → 1 set.

Hmm! So cse's quantity mechanism ALWAYS gives the constant when the value is a constant... unless the pseudo's value is NOT a constant.

**THEREFORE: the value MUST be non-constant.** And in C2D0 there's no runtime value to make it non-constant...

**...UNLESS THE VALUE IS COMPUTED FROM A RUNTIME VALUE THAT IS ZERO!** E.g. in C750 (which has a0), `it = (s32)D_80120194 + (a0 & 0)` → GCC folds (a0 & 0 = 0) ✗.

Hmm, but `it = (s32)D_80120194 + (a0 - a0)` → folded ✗.

What about `it = (s32)D_80120194 + (a0 == 0 ? 0 : 0)` → folded.

Hmm, what if the offset is a runtime value that is NOT provably zero but is guaranteed zero at runtime? That changes the semantics (the value would be wrong if a0 != 0) — semantically wrong, but the ROM code might not care? NO — we must preserve semantics.

OK, so for C2D0: the base is a compile-time constant, and GCC will always fold it into the plus. => **C2D0 is a WALL (cse-const-addr)** — unless the base's use is a compare/MEM (which forces a register).

Hmm, hold on! **What if we ADD a compare that is semantically neutral but not foldable?** Like comparing the base with itself via a runtime value:

```c
    it = (s32)D_80120194;
    if (it != (s32)D_80120194) return 0;   /* never taken, but not foldable? */
```
GCC: both sides are the same constant → the compare folds to false → the branch is removed → but does the *use* of `it` in the compare still count as a use requiring a register? If the branch is removed early (in the front end or in cse), the use disappears → the fold returns.

Hmm, but what if the compare is with a RUNTIME value in a way that's always true? E.g.:
```c
    it = (s32)D_80120194;
    if (it != p) ...   /* p is runtime? no */
```

In C2D0 there's no runtime value at all. So no.

**Hmm, so C2D0 = WALL?** Hmm, but wait: the ELSE branch of C750 and C2D0 both have this shape, and they're the ONLY two items (besides item 1 and 4) in my shard.

Hold on, hold on. Let me reconsider: maybe there IS a way — the "MEM base" mechanism. Let me check WHY the second symbol (D_801202A0) stayed in a register instead of being folded into the MEM. If I understand that, maybe I can apply the same trick to the base.

In the target: `lhu v0,0(v1)` where v1 = &D_801202A0. If cse had substituted the constant into the MEM's address, we'd get `lhu v0, D_801202A0` (with the reloc) — the backend would emit `lui a0, hi(...); lhu v0, 0(a0)` — hmm, actually for a constant address MEM on MIPS, the backend emits `lui reg, hi; lhu v0, lo(reg)` — 2 instructions. Since the target has 2 instructions (lui + addiu) + the lhu, GCC chose to keep the address in a register.

Why didn't cse substitute? Because the pseudo 73 (the second symbol) has 2 uses: the MEM and the compare. The compare requires a register → the pseudo must be in a register → and cse's substitution into the compare is invalid (a compare needs a reg) → so the substitution happens only at the MEM? But the MEM's address substitution is valid...

Hmm, unless cse processes the MEM use first and substitutes the constant there, leaving the compare to use the reg. Then the MEM would be `lhu v0, D_801202A0`. But the target has `lhu v0,0(v1)`. So no substitution happened at all.

The reason might be: cse's `validate_change` for the MEM address: replacing (reg v1) with (symbol_ref) in (mem (reg v1) 0) → (mem (symbol_ref) 0) → the mips machine might reject a MEM with a symbol_ref address in that form (it prefers (plus (symbol_ref) (const)) or (mem (symbol_ref))?). Hmm, `validate_change` checks `mips_...`? Hmm.

Hmm, honestly, the empirical evidence from the target is: a constant used in a MEM base stays in a register.

**SO: IF THE BASE WERE USED AS A MEM BASE, IT WOULD STAY IN A REGISTER!**

In C2D0: the base &D_80120194 — can we make the source dereference it in a way that's semantically neutral and produces no extra instructions? Hmm, the loop reads `*(u16*)it` for the loop pointer. What if the source's loop pointer started at the base?!

Hmm, the semantics: the loop scans from D_801202A0 to base+0x658C. What if the original source was:

```c
    it = (s32)D_80120194;    /* base */
    p = it + 0x658C;
    ...
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
```
with the loop starting at the base? Then the loop would read D_80120194's u16 first — but the target reads D_801202A0 first (the target's first lhu is at v1 = &D_801202A0). So no.

Hmm, BUT: what if the source had BOTH: the base used as a MEM base in a *dead* way? A dead load would still emit an instruction ✗ (unless GCC deletes it — but then the use disappears).

OK, hmm, what about this: **the base's use could be a MEM in the "zero" test**... no.

Let me now consider: maybe I should test the "MEM keeps it in a register" hypothesis with a small experiment to see if I can exploit it. But even if true, I need a semantically-neutral use.

**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**
**AH WAIT!!! I'VE GOT IT!!! THE `p` VARIABLE IS REUSED! In C750's ELSE branch: `copy: p = it;` — p is the bound first, then the found pointer.**

What if the ORIGINAL source had the base used as the *source of the copy block*? I.e.:

```c
} else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    p = it;
    goto found;
```
Here `copy: p = it` uses the LOOP pointer (it was reassigned at test:).

Hmm, what if the ORIGINAL was:
```c
} else {
    base = (s32)D_80120194;
    p = base + 0x658C;
    ...
copy:
    p = it;      /* the loop pointer */
```
Still one use of the base.

OK, ENOUGH. Let me try a batch of experiments; maybe GCC surprises me. Let me generate ~12 variants mechanically and score them:

1. base as u8* + pointer arithmetic
2. base assigned via `(s32)(u32)` casts
3. base used twice (a dead copy)
4. `p = it + 0x658C` with `it` as unsigned
5. base assigned in a nested block `{ }` (decl order/scope)
6. base assigned with `it = (s32)D_80120194;` and the p computed as `p = (s32)((u8 *)it + 0x658C);`
7. `p = it + 0x658C;` where it is `s32 it` but assigned `it = (s32)D_80120194 + 0;`
8. using a struct: `struct { s32 a; } s; s.a = (s32)D_80120194; p = s.a + 0x658C;` (a local struct → memory → a load ✗)
9. `p = it + 0x658C;` with the base assignment in a nested scope: `{ it = (s32)D_80120194; }` → the variable is still the same.
10. the base as a `const s32` — hmm: `const s32 base = (s32)D_80120194;` → the front end puts it in .rodata? For a local const, GCC 2.7 might allocate it in memory and load it ✗ (a load instruction).

Hmm! #10: a local `const` variable — GCC 2.7 would allocate it as a read-only static (in .rodata) and load it → `lw v1, base(%gp)`? That's an extra instruction ✗.

Let me just try a few and see. Actually, let me try #1 (pointer) and #5 and #7 quickly, then decide.

Hmm, hold on. Let me reconsider ONE more time, thinking about what the ORIGINAL programmer wrote. The function is in a game; the programmer wrote something like:

```c
s32 func_8012C2D0() {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
```

Hmm, what if the programmer wrote:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
but with `it` declared as `u32 *` and `p` as `u32 *`? Then `it + 0x658C` would be scaled by 4 ✗.

What if `it` was `u8 *` and `p` was `u8 *`? Then `p = it + 0x658C` → (plus (reg) (const 25996)) — the same as s32.

Hmm, and the compare `it == p` (pointers) → the same.

So the RTL is identical. And cse folds it. So the ORIGINAL would have the folded form. But the ROM has the unfolded form!!!

**=> THE ORIGINAL'S COMPILER DID NOT FOLD IT.** => The original was NOT compiled by gcc 2.7.2 with these flags? OR the original source had a `volatile`? OR the original source had a global pointer?

WAIT!!! **WHAT IF THE ORIGINAL HAD A `volatile` POINTER OR THE BASE WAS READ FROM A VOLATILE GLOBAL?** Hmm.

**OR!!! WHAT IF THE ORIGINAL'S `D_80120194` WAS DECLARED AS A POINTER VARIABLE, AND `(s32)D_80120194` READS THE POINTER'S VALUE?** Then the RTL would be a LOAD ✗ (the target has lui/addiu).

Hmm, hold on. What if the original was:

```c
    it = (s32)(u32)D_80120194;
```
where D_80120194 is `extern u8 D_80120194[];`... same.

Hmm, what if the original used a **cast through a float**?! Like the game's code sometimes did `(s32)(f32)ptr`? That would be lossy ✗.

OK, let me look at this from the ROM's perspective: maybe the ROM's function WAS compiled with the base folded, and the target's `lui v1; addiu v1; addiu a0,v1,25996` comes from a DIFFERENT source construct:

What if the original source was:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
compiled by a compiler that kept `it` in a register because `it` is ALSO used later (in the copy block: `return it`)!

**!!!!!!!!!!!!!!! THAT'S IT !!!!!!!!!!!!!!!**

In the ORIGINAL, maybe the `copy:` block returned the BASE (not the loop pointer), and the loop pointer was a DIFFERENT variable! Then:
- the base `it` is live from the entry to the copy block → CROSS-BLOCK → global-alloc → callee-saved $23 = v1 ✓✓✓ (explains v1!)
- the base has 2 uses (the plus AND the copy) → hmm, but that doesn't prevent the fold...

Hmm, but wait: if the base is live across blocks, then cse's quantity mechanism... hmm, the fold would still substitute the constant at the plus use.

Hmm! BUT: the copy block's use is `move v0,v1` — a COPY of the base into v0. If the base were folded to a constant, the copy would be `move v0, <const>` → the backend would materialize the constant into v0 → `lui v0; addiu v0` — that's 2 instructions instead of 1 move. So the target's `move v0,v1` (1 insn) means the base IS in a register at the copy point!

And the plus use would be `addiu a0, v1, 25996` (base-relative) ✓✓✓.

So: **if the base is live across blocks (used in the copy block), it MUST be in a register → cse can't fold it into the plus** (because the value must be in a register anyway, and cse's substitution would... hmm, would cse still substitute the constant at the plus use? If the pseudo is in a register for the copy use, the plus use could still use the constant... but then we'd have BOTH a register copy AND a constant materialization → GCC's cost model prefers to use the register for both (the constant is rematerializable but the reg is free)).

Hmm, the cse substitution happens per-use and is based on "the cheapest valid equivalent" — and the cost of the constant substitution vs. the reg. Hmm, cse's `src_const` handling: it prefers the constant if it's cheaper...

Hmm, but empirically: in the current source (with the launder), the base is in v1 and the plus is base-relative ✓ and the copy block's `move v0,v1` copies the LOOP pointer (not the base). Hmm, so with the launder, the base is NOT live at the copy block.

Hmm! But in the target, the copy block's `move v0,v1` — with the launder version (which matches the target byte-for-byte!), the base is NOT live there (v1 = the loop pointer). So the target's copy block copies the loop pointer.

Hmm, so the base is not live at the copy block. ✗ my new theory.

Hmm, but hold on: with the launder, the base's value is opaque (a REG) → it stays in v1 → and the copy block's `move v0,v1` copies... hmm, WAIT. With the launder, is the base in v1 at the copy block? The launder's copy pseudo (the value of `it` after the asm) — its live range: from the asm to the `p = it + 0x658C` use. Then the loop's `it` (the D_801202A0 set) is a different pseudo.

Hmm, but the pseudo 73 in the RTL (the launder version) — the asm's output is pseudo 73? Let me look at the ORIGINAL (with launder) RTL to see. That could be enlightening: it shows what the asm did.

Let me dump the orig (with launder) cse/rtl.

Actually, let me focus. TIME CHECK: it's ~07:20 now; I started at 06:37. That's 43 minutes on item 2. The budget is 20-30 min per item. I'm over. I should move faster: let me try a batch of variants quickly (5 min), and if nothing works, record the WALL and move on to the other items (which may be easier).

Let me look at the orig (launder) RTL quickly to understand what the asm does — that might reveal the mechanism to reproduce in C. 2 minutes.

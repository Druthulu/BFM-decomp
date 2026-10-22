---
ts: 2026-10-22T12:55:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bpYcaUwv9mHPqY8TI7B6
---
Even with 2 sets, cse still added REG_EQUAL notes: insn 12 has REG_EQUAL(symbol_ref D_80120194) — because cse knows the pseudo's value at that point (the last set is the symbol_ref, and cse's "REG_WAS_0" logic).

Hmm, interesting: cse added the note on insn 12 (the second set) — the note says "after insn 12, 73 = symbol_ref". And insn 15 (the use) got the note "72 = the constant address".

So cse tracks the pseudo's value regardless of the number of sets (it uses the "quantity" mechanism: the quantity of 73 for the uses after insn 12). So the fold happens anyway.

The quantity mechanism: cse splits the pseudo into quantities when it has multiple sets, so each set+its uses form a quantity class. The note is added when "n_sets == 1" — hmm, but the note WAS added here with 2 sets in the block.

Looking at the code again:

```c
	      /* If this is a single SET, we are setting a register, and we have
		 an equivalent constant, we want to add a REG_NOTE.   */
	      if (n_sets == 1 && src_const && GET_CODE (dest) == REG
		  && GET_CODE (src_const) != REG)
```
where n_sets is the number of sets of that particular REG in this block? Let me look at the surrounding code to see how n_sets is computed (line ~6102: `register int n_sets = 0;` — it's the number of sets of dest in this block).

In our n2 case, dest = 73 has 2 sets in the block → n_sets should be 2 → no note. But the note IS there on insn 12 (with REG_WAS_0). Hmm, so maybe the code adds the note in a different place (the "else if (GET_CODE (x) == REG && qty_const[...])" branch at line 1399 → `qty_const_insn[...] = this_insn` → and the note is added elsewhere).

Whatever. The empirical result: cse folds it anyway.

So the fold is robust: the pseudo's value is known as a constant regardless.

**Therefore: to keep the base in a register, the value must be genuinely opaque.**

Hmm, so what did the ORIGINAL do?!

Let me reconsider... Maybe the original source did NOT use the constant address at all! What if the original was:

```c
    it = (s32)D_80120194;
```
Hmm.

WAIT!!! What if the original used a POINTER variable and the address was obtained via a *different symbol* — e.g., the game's source had a global pointer table? Hmm.

Hmm, let me look at the C750 IF branch again:
```
4614: lui v1, hi(D_80120194)
4618: addiu v1,v1,lo(D_80120194)
461c: addiu a1,v1,25728
4620: beq a1,v1,4690
```
Here the base is in v1 and used in the plus AND the compare. The compare (beq a1,v1) forces the constant into a register (a compare needs a register operand) → so the base is in v1 → and the plus uses v1 → base-relative ✓.

Now the ELSE branch:
```
464c: lui v1, hi(D_80120194)
4650: addiu v1,v1,lo(D_80120194)
4654: j 4664
4658: addiu a1,v1,25996
```
The base is in v1 and used ONLY in the plus. So GCC kept it in a register even though it could have folded.

Why?! In the ELSE branch, the base is compared with nothing.

UNLESS the ELSE branch's base IS used in a compare in the original source! Hmm, what compare? Let me look at the ELSE branch's code again:

```
464c: lui v1, hi(D_80120194)     ; base
4650: addiu v1,v1,lo
4654: j 4664                      ; goto test
4658: addiu a1,v1,25996           ; p = base + 0x658C (delay slot)
465c: j 4694                      ; (copy block)
4660: move a1,v1                  ; p = it (delay slot)
4664: lui v1, hi(D_801202A0)      ; test:
4668: addiu v1,v1,lo
466c: beq v1,a1,4690              ; if (it == p)
4674: lhu v0,0(v1)                ; body:
467c: beqz v0,465c
4684: addiu v1,v1,268
4688: bne v1,a1,4674
```

Hmm, notice: at 466c, `beq v1,a1` compares the loop pointer (v1) with p (a1). And a1 = the bound. So p is in a1 (a register) — the bound was materialized as base+0x658C in a register.

So in the ELSE branch, the ONLY use of the base is the plus. And GCC kept it in a reg.

Compare with MY compile of the same code (no launder): the base was folded → `lui a0; addiu a0,a0,25996` and p = a0.

So the difference must come from something in the ELSE branch that differs from my version. What differs? The launder! (the asm). And in my version the base's value is known-constant → folded.

So in the ORIGINAL, the base's value was NOT known-constant. Since the original source was plain C... the base must have been obtained in a way that GCC couldn't fold.

**AH WAIT!!!!!** What if the original source's `it = (s32)D_80120194;` was actually `it = (s32)D_80120194;` where **D_80120194 is declared as `extern u8 D_80120194[];` in OUR header but in the ORIGINAL game source it was declared differently — e.g. as a `struct` or with a different type such that the address expression is not a constant**? No, the address of any global is a constant.

**UNLESS the original took the address of a LOCAL or of a function-local static!** Hmm, but the reloc says D_80120194 (a global).

**UNLESS the original computed the address as `base + (something_runtime)`!** Hmm! What if the original was:

```c
    it = (s32)D_80120194;
```
Hmm.

Hold on, hold on. What about the possibility that the game's source had the address obtained from a *pointer variable in memory*:

```c
extern u8 *D_80120194_ptr;
it = (s32)D_80120194_ptr;
```
→ an lw. ✗ (the target has lui/addiu).

What if the original was:
```c
    it = (s32)(u32)&D_80120194[0];
```
✗ same.

OK OK. Let me approach from the "what would the game's programmer write" angle:

The function scans a table of 0x10C-byte entries. The programmer might have written:

```c
s32 func_8012C2D0() {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
```

and the compiler folded it, giving the folded form... but the ROM shows the unfolded form. So the game's source differed.

WAIT!!! What if the game's source had the base as a **pointer to a struct** and the offset 0x658C as a *field/element index*? Like:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
vs
```c
    p = (s32)&D_80120194[0x658C];   /* the same address, folded */
```
✗.

Hmm, hmm.

**AH!!! IDEA!!!** What if the original had the base loaded from a *const array* in a way that the compiler couldn't fold because of the `volatile`?? The game's source might have had `volatile`! E.g.:

```c
    it = (s32)D_80120194;
```
Hmm, volatile on the ARRAY would make the *contents* volatile, not the address.

BUT!!! What about `volatile` on a POINTER: `it = (s32)(volatile u8 *)D_80120194;` — hmm, the address of a volatile-qualified object is still a constant.

Hmm, what if the game's source used a *pointer to a volatile*? no.

OK, radical rethink: maybe the ORIGINAL had TWO different variables and the base was compared! Let me re-examine the ELSE branch's semantics:

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

The loop scans from D_801202A0 upward, 0x10C at a time, until it == p (the bound) or a zero entry is found.

**What if the original was written as a do-while over the base with the bound computed INSIDE?**

```c
} else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    it = (s32)D_801202A0;
    ...
```

Hmm.

**What if the original had the base compared in the loop condition?** e.g.:

```c
} else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
```
The compare is with p, not the base.

Hmm, what if the original computed p differently: `p = it + 0x658C` where `it` is the base, and then the loop compared `it != p` where `it` is the base + k*0x10C? I.e., what if the loop pointer started AT the base?

```c
} else {
    it = (s32)D_80120194;     /* it = base */
    p = it + 0x658C;          /* p = end */
    it += 0x10C;              /* hmm */
```
We showed the second materialization's reloc would be D_80120194+0x10C.

Hmm, unless the source assigned D_801202A0 explicitly, which the current source does.

OK, let me try assuming the ORIGINAL source is what the current source says (the decompiler's reconstruction is usually close to the original), and the difference is that the ORIGINAL's `it` was a **pointer** type:

```c
u8 *it;
u8 *p;
it = D_80120194;
p = it + 0x658C;
```
Hmm! With `it` a POINTER (u8 *), the front end's expand of `it + 0x658C`:
- `it` is a local var → a MEM (or a pseudo) holding a pointer.
- `plus_expansion` in GCC 2.7: for pointer arithmetic, it computes the byte offset and does a PLUS. If the base is a variable (not an ADDR_EXPR), it emits (plus (reg) (const)).
Then the same cse fold.

Hmm, BUT: with a pointer type, the ADDEND might be scaled! E.g. if the pointer were `u32 *`, then `it + 0x658C` would be scaled by 4 → 0x658C*4 ≠ 0x658C. So the pointer is u8* (scale 1).

Hmm, what if the pointer were `u16 *`? then `it + 0x658C` = base + 0xD118. ✗.

So u8*.

Hmm, so pointer-ness doesn't change anything.

**LET ME RECONSIDER THE PROBLEM**: maybe the answer is that the base's value in the ORIGINAL was NOT the symbol address but the result of a *runtime* computation that HAPPENS to equal it. For instance, the game's source might have had:

```c
    it = (s32)(u8 *)D_80120194;
```
no.

WAIT!!! What about `it = (s32)D_80120194;` where **D_80120194 is declared as `extern u8 D_80120194[];` but the game's source used a DIFFERENT symbol that happens to be at the same address**? no.

Hmm, hmm, hmm. What about the possibility that the game's compiler was gcc 2.6 or 2.7 with a slightly different cse? Let me look at the project's own notes about this: maybe there's a cookbook entry about "the address base must stay in a register" — let me grep the cookbook for "cse-const-addr" or "rematerialis" or "base reg".

Let me grep the cookbook index for relevant entries: "const addr", "rematerialise", "address base".

This is a good idea — the project has a big cookbook; maybe there's a technique for exactly this ("the address must stay in a register; how to spell it in C").

Let me grep.

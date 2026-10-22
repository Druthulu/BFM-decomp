---
ts: 2026-10-22T12:54:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_iKVdWd5DPEyIhVqN7mjG
---
Now I can see the cse pass:

```
(insn 9) (set (reg 73) (symbol_ref D_80120194))
   (expr_list:REG_EQUAL (symbol_ref D_80120194))
(insn 12) (set (reg 72) (plus (reg 73) (const_int 25996)))
   (expr_list:REG_EQUAL (const (plus (symbol_ref D_80120194) (const_int 25996))))
```

So cse DID add a REG_EQUAL note on insn 9 saying pseudo 73 = symbol_ref. And on insn 12, pseudo 72 = the constant (plus symbol_ref 25996)!

Wait, but the note was added to insn 9 even though pseudo 73 has 2 sets (insn 9 and insn 26)? Hmm — the cse pass processes blocks: block 2-16 has 4 sets (including insn 9 and 12). The note on insn 9 says 73 = symbol_ref.

Hmm, but then insn 26 sets 73 = D_801202A0 — a conflicting value. cse would then... hmm, the REG_EQUAL note on insn 9 remains (the note applies to the value of 73 after insn 9).

Then, at insn 12, the use of 73 → cse's equiv_constant(73) → the qty_const for 73's quantity → the constant (plus symbol_ref 25996) → so insn 12 gets a REG_EQUAL note = the constant address → and later, the register allocator/reload substitutes the constant → the address (plus symbol_ref const) → the mips backend → lui/addiu with the addend.

So cse's folding happened because the pseudo's *quantity* (in cse's terms) had a single set at that point.

To defeat: the pseudo 73 must have 2 sets BEFORE insn 12 (in the same block or an earlier one) so that cse's quantity for the first use has >1 set... Hmm, but cse splits quantities per set: for a pseudo with sets at insns 9 and 26, cse creates quantity classes: the uses before insn 26 belong to the class of insn 9.

Hmm, but cse's `make_regs_eqv`/`split` logic: when cse sees a new set of 73 (insn 26) with a different value, it invalidates the old class. The REG_EQUAL note on insn 9 was added when processing block 2-16 (before seeing insn 26).

Hmm, so how do we prevent the note on insn 9? The note is added when "n_sets == 1 && src_const" for the pseudo in that block. If the pseudo had 2 sets in the same block, no note.

My dead-reset test (`it = 0; it = (s32)D_80120194;`) should have created 2 sets in the same block! But the score stayed 4. Hmm, why?

Because the front end's expand may have folded `it = 0;` — no wait, the front end emits (set 73 (const_int 0)) then (set 73 (symbol_ref)). Then cse: the first set is dead (overwritten) → cse might DELETE it (cse removes a set of a pseudo that's overwritten before any use? cse's `cse_basic_block` has "if the set is dead, delete it"). Hmm, but the note would still...

Hmm, but the note is added only if n_sets == 1 for the pseudo in the block. With 2 sets (0 and the symbol), no note → no fold → the base stays in a reg! But the result was still score 4.

Let me check the cse dump for my dead-reset variant (n3.c: `p = it + 0x658C; it = 0;` — the dead store is AFTER the use). For n2.c (`it = 0;` before), the 2 sets are in the same block: (set 73 0), (set 73 symbol_ref), (set 72 (plus 73 25996)).

Hmm! But cse processes the block and might delete the dead (set 73 0) — then n_sets becomes 1 → the note is added. Hmm, cse's dead-set deletion happens in `cse_basic_block` at the end ("delete_insn" for a set that's dead).

Let me just dump the cse for n2 and see. That's the fastest way.

Actually, let me think about which spelling could give the pseudo 2 sets that cse WON'T delete:
- The dead store `it = 0;` is deleted by cse as dead (it's overwritten).
- A *live* second set: e.g. `it = it;`? That's an identity (self-copy) — cse deletes it (or folds it).
- What about a second set with a DIFFERENT value that's still correct? The base's value must remain &D_80120194.

Hmm! What about this: make the pseudo's value NOT a plain symbol_ref but a value with 2 sets that both survive:

```c
it = (s32)D_80120194;
it = it;      /* identity: cse folds it */
```

What about a value that GCC can't fold to a constant: e.g. `it = (s32)D_80120194; it = (s32)(u32)it;`? Hmm, (u32) of an s32 is a no-op in RTL (same mode) → folded.

The G14 trick: `v = (s16)v;` — the conversion to HImode creates a SUBREG or a truncation insn. For our 32-bit address, a mode change isn't possible without truncation.

**What about a 64-bit intermediate?** `it = (s32)(long long)D_80120194;` — hmm, the front end's expand of a TImode conversion of a constant: it would emit the conversion as a "sign extend" of the constant → but the constant is 0x80120194 (positive in 32-bit unsigned, but as a signed long long conversion of an s32 value 0x80120194 (negative) → 0xFFFFFFFF80120194). GCC's fold would produce the TImode constant → then the truncation to s32 → folded back to the s32 constant. Likely folds.

Hmm, BUT: what about `it = (s32)(unsigned long long)D_80120194;`? The unsigned conversion → 0x0000000080120194 → the truncation to s32 → 0x80120194 ✓ value-preserving. In RTL: (set 73 (truncate (const:DI 0x0000000080120194)))? GCC's fold would simplify (truncate (const DI)) → (const SI 0x80120194) → folded. Ugh.

What if the conversion is NOT foldable: e.g. `(long long)` of a value that's already in a register.

Hmm, what about the OTHER direction: make the base's value come from a *sub-word* extraction that GCC can't fold? E.g. `it = (s32)(short)D_80120194` → truncation → wrong value.

OK, let me think about the *actual* mechanism that would keep the base in a register WITHOUT the constant being substituted: the pseudo's value must be unknown to cse.

**What if the pseudo's value is set by an insn that cse treats as non-constant?** For example, a MEM load: `it = *(s32 *)&D_80120194;` → that loads the CONTENTS at D_80120194 (not the address) → wrong semantics.

Hmm, what about `it = (s32)(u8 *)D_80120194;`... same.

**What about a `volatile` read of a global pointer?** Not available.

Hmm, hmm. What about the *second* set being a genuinely different but equivalent value, e.g.:

```c
it = (s32)D_80120194;
it = (s32)D_80120194;   /* same value, 2 sets */
```
cse: the second set is redundant → cse deletes it (or merges) → back to 1 set.

What about:
```c
it = (s32)D_80120194;
it = it + 0;    /* identity */
```
Folded by the front end (it + 0 → it) → 1 set.

What about a value-preserving op that GCC 2.7 does NOT fold but keeps as an insn:
- `it = it * 1;` → GCC folds (multiply by 1).
- `it = it | 0;` → folded.
- `it = it ^ 0;` → folded.
- `it = -(-it);` → hmm, GCC folds negate-negate.
- `it = it - 0;` → folded.

What about something GCC 2.7 doesn't fold: `it = it + (0 & 0xFFFFFFFF)`? folded.

Hmm, what about a conversion that requires an insn: `it = (s32)(u16)(u8)it;` → truncation → wrong value.

What about `it = (s32)(u32)(s32)it;` → no-op.

Hmm, so within a 32-bit int, all value-preserving ops fold.

**What about the ADDRESS being computed with a 64-bit add?** `p = (s32)((long long)it + 0x658C);` — the add in DI mode → daddu/addiu with a sign extension → extra instructions. ✗.

Hmm.

OK, let me flip to the OTHER end: maybe the fold can be defeated by making the *use* not foldable, i.e. the PLUS. The plus (reg 73, 25996) got a REG_EQUAL note = the constant (plus symbol_ref 25996). Then the register allocator/reload substitutes that constant into the insn → the mips backend sees (plus symbol_ref const) as an address → lui/addiu with the addend.

But hold on: is the substitution done by the register allocator (reload) using the REG_EQUAL note? Yes: `reload.c` / `regmove`? Actually the REG_EQUAL note is used by `reload` (reload.c: `reload_reg` → `reg_equiv_contain_p` → the note's value) and by the final register allocator? In GCC 2.x, the REG_EQUAL note is used in `reload.c` to rematerialize the value into the register.

Hmm, and the mips backend's `mips_operands` handles (plus (symbol_ref) (const_int)) → the "address" form → but that's for MEM operands. For a SET (reg) (plus symbol_ref const), the mips backend would need to materialize the address: `lui reg, hi; addiu reg, reg, lo+addend`. That's what we see.

So the fold is: cse's REG_EQUAL note on insn 9 says "73 = symbol_ref" → then at insn 12 (the use), cse's equiv_constant(73) → the constant → the note on insn 12 → "72 = the constant address" → reload substitutes the constant → the backend materializes it with the addend.

**KEY: the note on insn 9 exists because cse saw only ONE set of pseudo 73 in that block.** If the pseudo had 2 sets in the block, cse wouldn't add the note (n_sets != 1).

My dead-reset test failed... let me VERIFY by dumping the cse for n2.c. Maybe the front end deleted the dead store (expand's `expand_end_function`? no) or cse deleted it before adding the note.

Actually — cse processes a block and computes `sets[]` for the block: "Processing block from 2 to 16, 4 sets." For our function, the sets in the block are: (set 73 symbol), (set 72 plus), (set v0 73), (use v0) → 4 sets. If I add `it = 0;` → 5 sets, and the pseudo 73 has 2 sets → `n_sets == 1` fails → no REG_EQUAL note on either set!

Then the constant would NOT be substituted → the base stays in a reg → the target form!

But my test showed score 4 (no change). So something else happened. Let me dump the cse for n2 and look.

Let me do that now.

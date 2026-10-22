---
ts: 2026-10-22T12:55:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_KMpIACZFRE5WLOUKY7yo
---
§349 is interesting: "RE-ASSIGN A BASE POINTER AT THE END OF THE LOOP BODY TO MAKE n_times_set > 1 — THAT KILLS BOTH loop.c's INVARIANT HOIST AND THE ADDRESS GIV, REPRODUCING A REMATERIALISED addiu $aN,$sp,K".

Hmm, that's about a different thing (a stack address).

§153 "THE ADDRESS-REMATERIALISATION LAUNDER" — an asm lever.

Let me look at §349 in detail — it's about making n_times_set > 1 by re-assigning a base pointer. Hmm! That's the "2 sets" idea but for a different purpose (killing loop.c's hoisting).

Hmm, so in our case, we want the base's *use* to not be foldable.

Hmm, let me look at this from yet another angle: what if we change the ORDER of the statements so the base's use happens in a different block, and the pseudo gets a second set that's NOT dead?

**KEY REALIZATION ATTEMPT**: What if we give the base TWO uses where the second use is a *live* use that requires a register? Like:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
copy:
    return it;     /* in C2D0, the copy block returns `it` */
```

WAIT!!! In C2D0 the copy block returns `it`!!! And I established that at the copy block, `it` = the loop pointer (v1). Hmm, but hold on: what if the source's `copy: return it;` returns the loop pointer because `it` was reassigned at test:. Yes.

Hmm, so in C2D0, `it` (the variable) has: set 1 = base, set 2 = D_801202A0, and the loop increments (more sets). The base's pseudo (after cse's quantity split) has 1 use.

OK, let me try yet another approach: **BRUTE-FORCE SPELLING SEARCH**. I'll write a script that generates many C variants of the function and scores them, looking for score 0. The variants can differ in:
- the base assignment spelling,
- the p computation spelling,
- the use of a temp variable,
- the order of statements,
- types (u32, s32, u8*, s16...).

Since the search space is large, let me think about which dimension can plausibly work.

The fold requires: the pseudo's value is a known constant at the use. The pseudo's value comes from `it = (s32)D_80120194;`.

**What if the assignment is `it = (s32)D_80120194;` but `it` is declared as a POINTER?** Then the pseudo's value is still the constant.

**What if the base is assigned via a `+` with a zero-valued runtime expression?** There's no runtime value in C2D0... but WAIT: we could introduce one that's dead: e.g. `it = (s32)D_80120194 + 0;` → folded.

Hmm, in C750 there IS a runtime value (a0)! But in C2D0 there is none.

So in C2D0, ANY expression computing the base is a constant expression → folded.

Hmm!!! Unless... the base is not computed but READ FROM MEMORY. Hmm: `it = *(s32 *)D_80120194;` → that reads the contents (not the address) ✗.

Hmm, what about `it = (s32)(s32 *)&D_80120194;` ✗ same.

OK: **C2D0's base can only be a constant → always folded → the base can't stay in a register without an asm.**

Hmm, unless the fold doesn't happen when the pseudo has 2+ sets in the same block AND cse can't merge them. My n2 test had 2 sets (0 and the symbol) and cse still noted it. Hmm, but wait — look at the n2 cse dump: the note was on insn 12 (the second set) with a REG_WAS_0 note. And insn 15's note says 72 = the constant address. So cse still folded.

What if the second set's value is a DIFFERENT constant, e.g. `it = 0; it = (s32)D_80120194;` — the note on insn 12 says 73 = symbol_ref (that's the value after insn 12) → the use at insn 15 → the fold.

To defeat the fold, the value at the use must not be a known constant. The value after insn 12 IS a constant.

**What if the pseudo's value at the use is a constant that CANNOT be folded with the offset?** E.g., if the pseudo's value were a constant whose addition with 25996 can't be folded into an address... Hmm, the fold produced (const (plus (symbol_ref D_80120194) (const_int 25996))) — a "CONST" node wrapping the plus. That's fine for the backend.

Hmm, what if the value were a constant in a DIFFERENT mode? E.g., if the base were stored as an SImode constant vs a HImode...

**!!!!!!!!!! THE HImode TRICK !!!!!!!!!!**

What if we make the base's pseudo hold a value in a different MODE, so the plus can't fold? For example:

```c
s32 it;
...
it = (s32)D_80120194;
```

What if instead the base is stored in a `u16`/`s16` variable? Can't hold the address.

Hmm, but what about this: the constant 0x658C as a u16 → the plus becomes (plus reg (const HI 25996))... hmm, the mode of the constant would be SI after promotion.

OK, let me try a completely different tactic: **look at how the sibling function func_8012C750's ELSE branch could be cracked**, and whether the project's other shards cracked such cases. Let me search moves.md and the cookbook for "base reg" / "addiu a1,v1" style solutions.

Hmm, hold on. Let me reconsider the problem ONE more time.

What if the trick is to make the *pseudo's* value be a constant that is NOT a plain symbol_ref but a "CONST with a plus" — e.g., if the base were `D_80120194 + 0` — no.

**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**
**THE REAL ANSWER MIGHT BE: the source assigns the base from a DIFFERENT global that has the same address? No.**

**!!!!!!!!!! OR: the source uses `&D_80120194[0]` where D_80120194 is declared as `extern u8 D_80120194[];` — and GCC's expand produces a "MEM" address...**

Hmm, let me look at the RTL dump once more:

```
(insn 9) (set (reg/v:SI 73) (symbol_ref:SI ("D_80120194")))
```
So the front end produced a pseudo set to the symbol ref. In the ORIGINAL compile, the same would happen... and cse would fold it the same way. So the ORIGINAL source CANNOT have been `it = (s32)D_80120194;` — unless the original's compiler differed.

**Hmm, unless the original's pseudo 73 had 2 sets in the same block!** In the original, maybe the source was:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
→ the block has: set 73 (symbol), set 72 (plus) → 2 sets, but only ONE set of pseudo 73.

What if the original was:
```c
    it = (s32)D_80120194;
    it = it;                 /* ??? */
```
no.

What if the original was:
```c
    s32 base;
    it = (s32)D_80120194;
    p = it + 0x658C;
```
no.

**WAIT!!! What about the possibility that the original had the base assigned in a way that produces TWO sets of the SAME pseudo in the same block, e.g.:**

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    it = (s32)D_801202A0;    /* the second set, in the SAME block! */
    goto test;
```
i.e., the source assigned D_801202A0 in the same block as the base! Then the block would have 2 sets of pseudo 73 → cse's n_sets == 2 → NO REG_EQUAL note on either → and then... hmm, but the current source has `goto test;` then `test: it = (s32)D_801202A0;` — the assignment is in a different block.

Hmm! But that would change the block structure (the target's `lui v1; addiu v1` for D_801202A0 is at 4664, in the "test" block, after a jump). If the assignment were in the same block as the base, the scheduling would differ (the two materializations would be adjacent).

Hmm, but hold on: cse's REG_EQUAL note is added per-set when "n_sets == 1" for that dest in the block. If pseudo 73 has 2 sets in the block, NO note is added for either set. Then, at the use (insn 15, the plus), cse's equiv_constant(73) → qty_const[quantity of 73]... the quantity mechanism might still know the value.

Hmm, but the note is what matters for the later passes (reload). Let me TEST it: put the D_801202A0 assignment in the same block as the base:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    it = (s32)D_801202A0;
    goto test;
test:
    if (it == p) goto zero;
```

Wait, but that changes the CFG: the "test" block would be the same block as the entry → the target has a `j 4664` between them. Hmm, the target's structure:
```
464c: lui v1 (base)
4650: addiu v1
4654: j 4664        <- a jump to the test block
4658: addiu a1,v1,25996 (delay)
465c: j 4694        <- the copy block
4660: move a1,v1
4664: lui v1 (D_801202A0)
```
So there IS a jump from the entry block to the test block. If the assignment were in the same block, GCC would still create the jump if the CFG has a label... hmm, the current source has `goto test;` — so the CFG has 2 blocks regardless of where the assignment textually is! The assignment `it = (s32)D_801202A0;` placed BEFORE the `goto test;` would be in the entry block.

So: the source could be:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    it = (s32)D_801202A0;
    goto test;
test:
    if (it == p) goto zero;
```
Semantically identical! And now pseudo 73 has 2 sets in the entry block → cse might not add the note → the base might stay in a register!

But hmm, would the D_801202A0 materialization then be scheduled the same? The target has the D_801202A0 materialization in the "test" block (after the jump at 4654). If the assignment is in the entry block, the lui/addiu for D_801202A0 would be in the entry block (before the jump) → the code layout would differ ✗.

Hmm! Unless GCC's block splitting/scheduling moves it. Hmm, the target's 4654 `j 4664` — the delay slot has the addiu a1,v1,25996 (the p computation). If the D_801202A0 materialization were in the entry block, we'd see lui/addiu for D_801202A0 before the jump ✗.

So no.

Hmm, BUT: what if the two assignments are in the same block but the SECOND one is in a different position... hmm.

OK, let me just TEST the cse behavior with a quick experiment: I'll write the variant and dump the cse. But the layout issue makes it unlikely to match.

Hmm, let me think about the *target layout* again:
- Block 1 (entry): base materialization + p computation + jump to test.
- Block "copy": p = it; jump to found.
- Block "test": D_801202A0 materialization + compare.
- Block "body": the loop.

In the ORIGINAL, the base's pseudo 73 has 1 set in block 1 (the symbol) and the use (the plus) is in block 1 too. cse processes block 1: 2 sets (73 and 72) → n_sets for dest 73 is 1 → the note IS added → the fold.

So the original MUST have had something different.

**!!!!!!!!!!!!!! FINALLY, THE IDEA !!!!!!!!!!!!!!**

What if the original source's base was NOT `&D_80120194` but the address of a *different* object that happens to be D_80120194 — e.g., `&someStruct.field` where someStruct is at D_80120194 - offset? Then the address would be (plus (symbol_ref someStruct) (const offset)) → a non-constant-foldable expression? NO — GCC folds (plus symbol_ref const) into a symbol_ref with an addend at the RTL level? Hmm, actually NO! In RTL, (plus (symbol_ref X) (const_int 16)) is NOT folded into a single symbol — the RTL keeps the PLUS! And then the mips backend materializes it as lui/addiu with the addend (which is what we see for the FOLDED case: `lui a0, hi(D_80120194); addiu a0,a0,25996` — the reloc is on D_80120194 with the addend in the instruction).

Hmm! So (plus (symbol_ref) (const)) is a legal address operand and the backend folds it into lui/addiu with the addend.

But if the expression were (plus (reg 73) (const 25996)) where reg 73 holds the symbol_ref D_80120194 → the backend materializes: lui 73, hi(D_80120194); addiu 73, 73, lo(D_80120194); addiu 72, 73, 25996 → the TARGET form!

So the target's form = "the base is in a register, then add the offset".

And the folded form = "the whole address is one constant".

The difference: whether the RTL at the use is (plus (reg) const) or (plus (symbol_ref) const).

Since cse substitutes the constant when the pseudo's value is known...

**WHAT IF THE PSEUDO'S VALUE IS A CONSTANT BUT NOT A "PURE" SYMBOL_REF?** E.g., if the pseudo's value were (plus (symbol_ref D_80120194) (const_int 0))... that's the same.

Hmm, what if the pseudo's value is a constant in a mode where gen_lowpart_if_possible gives a SUBREG? E.g., if the base were computed as a 16-bit value... no.

OK — **let me try the "volatile" idea and see if it's even needed**: what if the base is read from a volatile global pointer? Not available.

**Let me look at §349 in the cookbook**: "RE-ASSIGN A BASE POINTER AT THE END OF THE LOOP BODY TO MAKE n_times_set > 1 — THAT KILLS BOTH loop.c's INVARIANT HOIST AND THE ADDRESS GIV". This is about a stack address (sp-relative). Not our case.

Hmm, let me look at the cookbook entry §153 (ADDRESS-REMATERIALISATION LAUNDER) — it's an asm lever, not useful.

Let me search the cookbook for "cse" entries about constants being substituted into addresses, e.g. "§243 — SPELL THE CSE BARRIER AS A REASSIGNED POINTER".

Hmm.

**LET ME RECONSIDER: maybe the answer is that the base's value should be a runtime value that equals the address — i.e., the game's source computed the address from ANOTHER global!**

Look: D_80120194 and D_801202A0 are 0x10C apart. What if the game's source had:

```c
it = (s32)D_80120194;
```
Hmm.

WAIT A MOMENT!!! What if the game's source used a **pointer to a pointer**? Like the table's start pointer stored at D_80120194 - 4? Nah.

**!!!!!!!!!!!!!!!!!!!!!! THE ANSWER !!!!!!!!!!!!!!!!!!!!!!**

What if the original source had the base and the second symbol related by an OFFSET, i.e.:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
test:
    it = (s32)D_801202A0;
```
We keep coming back. Hmm.

Let me try ANOTHER experiment: what if the pseudo's value is known-constant but cse's equiv_constant is NOT applied because the pseudo's mode is different... What if `it` is declared as `unsigned int` and the constant is the same? Same mode.

**LET ME JUST TEST the "2 sets in the same block" hypothesis quickly** — even if the layout changes, the cse dump will tell me whether the note disappears. That's a 2-minute experiment and it teaches me the mechanism. If the note disappears, then I can look for a spelling with 2 sets in the same block that preserves the layout.

Hmm, but which 2 sets could be in the same block without changing the layout? The base's set and... the D_801202A0 set (different block). Hmm.

Alternatively: what if the base is set TWICE in the entry block with the same value:
```c
    it = (s32)D_80120194;
    it = (s32)D_80120194;   /* hmm, cse would delete the first */
```
cse deletes the first (dead) → 1 set.

What if the two sets are in DIFFERENT blocks (the base in block 1 and something else in another block)? cse processes blocks in order; the note on insn 9 is added when processing block 1 (where 73 has 1 set). So the note is added regardless.

Hmm, so we need the base's set to NOT be alone in its block. The base's set is in the entry block along with the p computation. If the entry block had another set of pseudo 73 (a second assignment to `it`), cse wouldn't add the note.

**What if the source assigns `it` twice in the entry block, with the second assignment being the base's value AGAIN but in a different form?** e.g.
```c
    it = (s32)D_80120194;
    it = (s32)&D_80120194[0];   /* the same value, a different spelling */
    p = it + 0x658C;
```
cse would see two sets of 73 with the same constant → cse deletes the first (redundant) → 1 set → note added. Hmm, does cse delete it? cse's `cse_basic_block` handles a set of a pseudo to a constant that equals the pseudo's current value → it's redundant → deleted ("cse: the value is already known").

Hmm, but the deletion happens AFTER the note? The note is added in the same pass... The order in cse_basic_block: it processes the sets in order; for each set it checks if the value is already known (then it deletes the set) — and the note-adding code is in the "else" path.

Hmm, in the n2 case, the note WAS added on insn 12 (the second set, symbol_ref) even though 73 had 2 sets in the block. So the "n_sets == 1" condition must refer to something else. Let me actually read that part of cse.c to understand the condition.

Let me look at the code around line 6800-6930 in cse.c.

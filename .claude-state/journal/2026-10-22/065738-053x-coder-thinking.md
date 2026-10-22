---
ts: 2026-10-22T12:57:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_QVVtcvHz0Jmh9tRJFVps
---
Now I see the launder's RTL:
```
(insn 9) (set 73 (symbol_ref D_80120194))
(insn 11) (set 73 (asm_operands ... (=r) 0 [(reg 73)] [(asm_input "0")]))
(insn 14) (set 72 (plus 73 25996))
```
So the asm's output is pseudo 73 itself (the same pseudo!) — the asm is a "set 73 = asm(73)". Since the asm's output is pseudo 73 (the same reg), the value after insn 11 is UNKNOWN to the optimizer → the plus can't be folded ✓. And the materialization of the symbol_ref into a register happens because the asm's INPUT operand (pseudo 73) must be in a register → reload materializes the constant into a reg (v1) ✓.

So the launder works by making the value unknown.

To reproduce in C, we need the value to be unknown to the optimizer. Options:
(a) asm (forbidden).
(b) The value comes from memory (a load) → an extra instruction.

Hmm, (b): what if the value comes from a load that GCC folds away? No.

(c) **The value is produced by an operation GCC can't fold, but which is free**: e.g. `it = it - 0;`? folded. `it = it + 0;`? folded.

Hmm, what about `it = it & -1;`? folded.

(d) What if the value is the result of a comparison or a cast that GCC 2.7 doesn't simplify? E.g. `it = (s32)(u32)(s16)it` — wrong value.

Hmm, (e): **what if the value is loaded from a global array that GCC constant-folds... no.

(f) **What if the pseudo's value is unknown because the variable is assigned in a DIFFERENT function/block via a pointer?** no.

OK. Let me now consider the OTHER items — maybe they're easier — and come back to this.

Actually, hold on. Let me reconsider (b) once more: the value comes from a load. In C2D0 there are no loads at all. But hmm — what about the "loop pointer" being loaded? no.

Hmm, hmm. What about this trick: **use a `volatile` read of a global variable whose value is irrelevant**? E.g.:

```c
    it = (s32)D_80120194;
```
→ to make it unknown, we'd need a volatile read → an extra lw instruction ✗.

**What about the "address of a volatile object" trick?** `it = (s32)(volatile u8 *)D_80120194;` — the value is the same, but does the volatile qualification make the ADDRESS non-constant? NO — the address of an object is a constant regardless of volatility. Hmm, but GCC's fold might keep the cast as a "conversion" insn? The cast from `u8 *` to `volatile u8 *` is a no-op in RTL (the qualification is dropped in RTL). ✗.

OK, hmm, what about the **"asm-free" trick used elsewhere in this project**: let me look at what other shards did for launder MATCHes: "launder->pv = *p; pv &= 0xFF000000 split (real 2nd set)" — they replaced the launder with a real second set of the variable, where the launder's purpose was to break the cse equivalence class. In our case, the launder's purpose is to make the value UNKNOWN (not just to break an equivalence).

Hmm! But WAIT: maybe there's a real-2nd-set spelling that also makes the value unknown: what if the variable's value is set from a *runtime* value in a way that provably equals the constant but GCC can't fold?

For C2D0: there's no runtime value. BUT — hmm — what about the value of the *pseudo* being clobbered by... hmm.

**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**
**IDEA: USE A SECOND VARIABLE WHOSE VALUE IS THE ADDRESS BUT IS SET FROM A RUNTIME EXPRESSION.**

Hmm, in C2D0 there's no runtime value. Hmm.

**IDEA: What if the address is computed as `(s32)(u8 *)D_80120194` but the FUNCTION has a parameter?** C2D0 has no parameters (void). C750 has a0!

So for C750's ELSE branch, we could do: `it = (s32)D_80120194 + (a0 - a0);` — GCC folds (a0-a0) → hmm, `a0 - a0` is folded to 0 by the front end ✓ folded. What about `it = (s32)D_80120194 + (a0 & 0);` → folded. `it = (s32)D_80120194 + ((a0 == 0) ? 0 : 0)` → folded. `it = (s32)D_80120194 + (a0 ? 0 : 0)` → folded.

GCC 2.7's front end folds constant expressions but `a0 - a0` is not a constant expression at the front end! It's a runtime expression. The front end would emit: (set t (minus a0 a0)) then (set 73 (plus symbol_ref t)). Then cse/reload: t = a0 - a0 → the value is unknown to the optimizer (GCC 2.7 doesn't know a0 == a0)! So `it` = symbol_ref + t → NOT a constant → the base stays in a register ✓✓✓.

And the extra instruction (subu t, a0, a0) — hmm, that would be an EXTRA instruction ✗ (the target has none). Unless GCC deletes it: `minus a0 a0` → the value is 0 → GCC's cse/jump might optimize `x - x` to 0? GCC 2.7's fold doesn't know x-x = 0 (that's not valid for floats, but for ints it is; GCC's simplify might do it: `simplify_binary_operation` for MINUS with the same operands → 0? In GCC's fold-const.c, `x - x` → 0 is only done if the operands are identical AND the mode is not floating point... Actually yes! GCC's fold has:
```c
    case MINUS:
      if (operand_equal_p (op0, op1, 0) && ... integermode) return zero
```
Hmm, in GCC 2.7's fold-const.c, `fold_binary` for MINUS: "if (operand_equal_p (op0, op1, 0) && GET_MODE_CLASS (mode) != MODE_FLOAT) return zero" — I believe that exists. Then the value becomes 0 → the plus folds again ✗.

Hmm! But the value 0 is only known after folding → the fold would happen at the RTL level → the plus folds → ✗.

OK, what about `a0 & a0`? → fold: `x & x` = x → then the plus = symbol_ref + a0 → NOT a constant → the base stays in a register! But the semantics change: it = D_80120194 + (a0 & a0) = D_80120194 + a0 — WRONG (a0 != 0 in general).

Hmm, `a0 & 0` → folded to 0 ✗.

`a0 * 0` → folded to 0 (GCC folds x*0 = 0) ✗.

`a0 - a0` → folded to 0 (probably) ✗.

`a0 / a0` → folded to 1 ✗.

`a0 ^ a0` → folded to 0 ✗.

Hmm, everything with the same operand folds.

What about `a0 & 0xFF00`? Not zero ✗ (semantics).

OK so that path is out (semantics must be preserved).

**LET ME NOW THINK ABOUT THE "SEMANTICS" CONSTRAINT**: the body must be semantically equivalent to the target. But hold on — how is "semantics" judged? The project compares the compiled bytes. A body that computes a different value but compiles to the same bytes would be accepted by the scorer... but that would be cheating (and the phase cares about faithfulness). The brief says "real C moves only" and the moves.md records the mechanism. I should not cheat with wrong semantics.

Hmm, but hmm: interestingly, a body like `it = (s32)D_80120194; p = it + 0x658C;` vs something semantically different... no, let's stay honest.

**NEW IDEA: What if we make the base's value unknown by taking it from a MEMORY location that the compiler CAN'T fold — i.e. the address of the base stored in the stack?** E.g.:

```c
    s32 *tmp = &it;   /* the address of a local → a stack address */
```
✗ (extra instructions).

**NEW IDEA: What if the base is computed from the LOOP POINTER's address?** no.

**NEW IDEA — THE PROMISING ONE: use the fact that the base's value is used TWICE, with the SECOND use being a COPY into a variable that is live across blocks (forcing the base into a register).**

Concretely, in C2D0:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
What if we ADD a use of the base that's live across a block, e.g.:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
copy:
    return it;    /* the loop pointer — hmm */
```

Hmm! What if the copy block returned the base in ADDITION to the loop pointer? Semantically different ✗.

Hmm, hmm. But WAIT: what if the copy block's `return it;` in the ORIGINAL returned the base (i.e., the function returns the base, not the found pointer)?! We ruled that out via the register overlap argument... but let me re-examine that argument!

If the copy block returns the base:
- The base pseudo is live from the entry to the copy block → it's a global allocno → callee-saved $23 = v1 ✓ (explains v1!).
- The loop pointer pseudo (D_801202A0 + increments) is live in the loop → also a global allocno → it would get a DIFFERENT callee-saved reg (say $22 = v0) since they overlap at the copy block.

But the target shows the loop pointer in v1 (lhu v0,0(v1), addiu v1,v1,268) AND `move v0,v1` at the copy block. If the base were live at the copy block, it'd be in another reg (not v1) → the copy block would be `move v0, <other reg>`. The target has `move v0,v1` where v1 = the loop pointer (the last def). So the copy block returns the LOOP pointer. ✓ (as I concluded).

Hmm, unless the base and the loop pointer are the SAME pseudo (i.e. the same variable `it` with the base's value being... no, they're different values).

OK. So the base's only use is the plus.

**THEREFORE: for C2D0, the ONLY way to get the base into a register is to make its value unknown to the optimizer.** In C2D0 (no runtime values), the only source of an unknown value is... a load from memory.

Hmm! A load from memory! What if the base is loaded from a location that holds the address... no such global.

WAIT!!!! **What about the ADDRESS OF A LOCAL VARIABLE?** Hmm, no.

**WHAT ABOUT A GLOBAL VARIABLE THAT HOLDS A POINTER TO THE TABLE?** We don't have one. But hmm — what about `D_80120194` being an ARRAY of bytes and the game's source doing something like `it = (s32)(D_80120194 + sizeof(D_80120194))`? no.

Hmm, let me look at the C750 IF branch once more:
```c
s32 base = (s32)D_80120194;
p = base + 0x6480;
if (p != base) { do { ... } while (p != base); }
```
The base is used in the compare `p != base` → the compare needs a register → the base is in v1 → and `p = base + 0x6480` uses v1 → base-relative ✓.

**SO THE TRICK FOR C750's ELSE BRANCH COULD BE: make the base participate in a COMPARE!** In the ELSE branch, is there a compare involving the base? What if we restructure:

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

Hmm, what if the original was:
```c
} else {
    base = (s32)D_80120194;
    p = base + 0x658C;
    ...
```
and the compare `it != p` — where p = base + 0x658C — hmm, p is the bound.

What if the original's loop compared against the base directly? Like:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it - 0x10C != p) goto body;    /* hmm */
```
no.

Hmm, hold on! What about the ZERO case: `zero: p = 0;` — the ELSE branch's zero case. And in C750, the `found:` block tests `if (p == 0)`. So p is compared with 0 later.

What if the ELSE branch's base were compared with 0 somewhere? no.

OK. **DECISION: Let me look at the OTHER items first** (items 1 and 4 have different mechanisms), then come back to items 2 and 3 with the remaining time. Maybe item 3 (C750) has an easier path via the IF branch's pattern (the base used twice) — e.g., maybe the ELSE branch could be restructured to use the base twice!

**AH WAIT!!!! FOR C750, THE ELSE BRANCH'S BASE COULD BE USED TWICE IF WE RESTRUCTURE THE LOOP AS A DOWNWARD SCAN LIKE THE IF BRANCH!** No, the semantics differ.

Hmm, but hold on: what about using the base in the ELSE branch's `copy:` block? `copy: p = it;` — the loop pointer.

Hmm, hmm.

**!!!!!!!!!! IDEA FOR BOTH: USE A SECOND VARIABLE FOR THE BOUND AND KEEP THE BASE LIVE ACROSS THE LOOP !!!!!!!!!!**

What if the source is:
```c
    base = (s32)D_80120194;
    p = base + 0x658C;
    ...
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
```
The base is dead after the entry block.

What if instead the source kept the base alive by using it in the loop's exit condition... e.g. the loop could be written to count from the base:

Hmm, semantics: the loop scans from D_801202A0 to base+0x658C in steps of 0x10C, stopping at a zero entry. An equivalent formulation: `for (q = base + 0x10C; q != base + 0x659C; q += 0x10C)`. Hmm, that changes the code shape ✗.

OK, let me now go look at items 1 and 4 and come back.

Actually, WAIT. One more idea for the base-in-register problem, and I think this one is GOOD:

**USE THE `p` VARIABLE'S FIRST SET AS A COPY OF THE BASE, AND MAKE THE BOUND COMPUTATION USE `p`:**
```c
    p = (s32)D_80120194;      /* p = base */
    p = p + 0x658C;           /* p = bound */
```
Then pseudo p has 2 sets: the base and the bound. The first set's value is a constant (the symbol_ref) → cse's note → the use (the plus) folds → ✗. Hmm, same.

**WHAT IF THE ORDER IS: `p = base + 0x658C;` where base is a SEPARATE variable that is ALSO the loop's start?** no.

Hmm, let me look at the problem from the "what does cse need" angle ONE more time:
- cse adds the REG_EQUAL note to insn 9 (73 = symbol_ref) because src_const is found for the set.
- Then at insn 14 (the plus), cse's equiv_constant(73) → the constant → the note on insn 14 → "72 = the constant address" → the backend materializes it as lui/addiu with the addend.

**The substitution at the use is what kills it.** cse does it because `validate_change` accepts it.

**WHAT IF THE USE WERE IN AN INSN WHERE THE CONSTANT SUBSTITUTION IS INVALID?** E.g. if the plus's result were used as a MEM address (a MEM with a constant address is valid on MIPS, hmm) or in a COMPARE (invalid — a compare needs a reg!).

**THE COMPARE!** In the IF branch of C750: `if (p != base)` → the compare keeps the base in a register ✓✓✓.

**SO: IF THE BASE PARTICIPATED IN A COMPARE, IT WOULD STAY IN A REGISTER.**

Now: in C2D0 and C750's ELSE branch, can we add a compare involving the base that is semantically neutral AND produces no extra instructions?

A compare that GCC can fold away (both sides the same constant) would remove the use ✗.

Hmm, BUT: what if the compare is `if (base == p)` where p = base + 0x658C — never true — and the branch is... hmm, that changes semantics (an extra branch). Hmm, but GCC might optimize `base == base + 0x658C` → false (both constants) → the branch is removed → but then the use disappears → ✗.

Hmm, what about a compare whose result is USED but is semantically neutral? E.g. `if (base != base) return 0;` — GCC folds (both are the same constant) → removed ✗.

Hmm, what if the compare involves the base and a RUNTIME value in a way that's always true but GCC can't prove? E.g. `if (base == (s32)D_80120194) {}` — the same constant → folded.

For C750 (with a0): `if (base == a0) ...` — not always true ✗ semantics.

Hmm.

**WHAT ABOUT THE MEM-BASE MECHANISM?** The second symbol stayed in a register because it's used as a MEM base. Hmm, wait, is that the reason? Let me verify: is it the MEM use or the compare use that kept D_801202A0 in a register? Both uses exist. The compare alone would suffice.

OK, so let me test the hypothesis "a compare use keeps the constant in a register" — hmm, I can't test it without changing semantics.

Hmm, hold on. HOLD ON. What about the ZERO test in the loop: `if (*(u16 *)it == 0) goto copy;` — the loop pointer is dereferenced AND compared. Fine.

**WHAT IF WE MAKE THE BOUND (p) BE COMPUTED FROM A COMPARE-FORCED REGISTER?**

Hmm, hmm. What if we swap the roles: what if `p` (the bound) is compared with the base in a way that's equivalent? E.g., the loop condition `it != p` could be written as `it - 0x10C != p - 0x10C`? Hmm, that changes the code ✗.

**!!!!!!!!!!!!!!! THE SIMPLEST IDEA OF ALL !!!!!!!!!!!!!!!**

What if the source's base assignment is `it = (s32)D_80120194;` and the p computation is `p = it + 0x658C;`, and we ADD a THIRD statement that uses the base in a compare — but the compare is one that the ORIGINAL might have had and that the decompiler dropped? Hmm, the decompiler wouldn't drop a compare.

OK, alternatively:

**WHAT IF WE PUT THE `p = it + 0x658C` COMPUTATION INSIDE THE LOOP-COMPARISON so that `p`'s VALUE is compared against `it`?** i.e.:

```c
    it = (s32)D_80120194;
    ...
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != (s32)D_80120194 + 0x658C) goto body;   /* the bound recomputed */
```
Then the compare's operand is the constant address → GCC materializes it in a register → the constant (plus symbol_ref 25996) → the backend emits lui/addiu with the ADDEND ✗ (the target has the base-relative form).

Hmm ✗.

**WHAT IF THE COMPARE IS `it != p` WHERE p IS A VARIABLE HOLDING base+0x658C?** Then p's value is the constant → the compare materializes the constant → lui/addiu with the addend ✗.

So the compare must involve the BASE itself (not the bound).

Hmm! **WHAT IF THE LOOP'S EXIT CONDITION COMPARED THE POINTER AGAINST THE BASE?** Like: the loop scans until the pointer reaches base+0x658C. What if the source used a COUNTER:

```c
    base = (s32)D_80120194;
    p = base + 0x658C;
    it = (s32)D_801202A0;
    ...
```
no.

OK. Time to make a decision. I've spent ~50 min on item 2. Let me:
1. Quickly check items 1 and 4 (which might be crackable) — 20 min each.
2. Come back to items 2/3 if time permits; otherwise record WALLs with the tag `cse-const-addr` (which exists in walls.txt) and good evidence.

Hmm, but hold on. Before that, let me try ONE more thing for item 2/3: the "keep the base in a register by using it in a MEM" — hmm.

WAIT!!! **I'VE GOT IT!!! THE `p` VARIABLE REUSE!!!**

Look at C750's ELSE branch: `copy: p = it;` — the bound variable p is REUSED for the result. What if the ORIGINAL source was:

```c
} else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
```
Hmm no.

**OK ACTUALLY — THE REAL IDEA: what if the original source assigned the base to `p` FIRST and then computed the bound from `p`?**

```c
} else {
    p = (s32)D_80120194;     /* p = base */
    p = p + 0x658C;          /* p = bound */
```
→ pseudo p has 2 sets. The first set (the symbol_ref) → cse's note → the use at the second set (the plus) → folded ✗.

ARGH.

**THE LAST IDEA: maybe the base's value must be unknown, and the ONLY unknown values in C come from memory or calls. What if the ORIGINAL source had a CALL?!** Like the original might have called a function to get the table base! But the target has no call in that path ✗.

**CONCLUSION for items 2 and 3: the base must be opaque → only asm → the lever is irreducible → WALL.**

Hmm, but hold on. Let me reconsider the whole thing ONE more time. What if the original source's `it = (s32)D_80120194;` line was actually:

```c
    it = (s32)D_80120194;
```
in a context where `D_80120194` is a **`volatile u8 []`**? The address is still constant.

Hmm, what if the original had:
```c
    it = *(s32 *)&D_80120194;   /* ??? */
```
no.

Hmm, hmm. What if the original had the base as a **pointer to a struct** and the bound computed as `&arr[0x658C/4]`? → folded ✗.

Hmm, what if the original's `it` was declared `s32 it` but the ASSIGNMENT was `it = (s32)D_80120194;` — hmm, we've beaten this to death.

Let me look at the OTHER items now, and maybe I'll get insight from item 1 (which has a similar base-relative structure with `src`).

Actually, hmm, wait. Item 1 (8012B4B8) has:
```c
register int *src __asm__("$5");
...
src = (int *)&D_800AE620;
__asm__("" : "=r"(src) : "0"(src));  // launder
t0 = src[0]; t1 = src[1]; ...
```
Here `src` is PINNED to $5 — so it's a hard-reg pseudo, and the launder makes the value opaque. Without the launder, `src` would be... hmm, since src is pinned to $5 (a hard reg), the address must be materialized into $5 anyway! The launder might be redundant there! Let me TEST item 1 right now — just remove the launder and score.

Similarly item 4 (801372B0): the launders are on `op` (a pointer), `ax`, `by` (s16 values). Removing them might work directly.

Let me test items 1 and 4 quickly. They're the "easy" ones maybe.

Let me do item 1 first: remove the launder line (line 19) and score.

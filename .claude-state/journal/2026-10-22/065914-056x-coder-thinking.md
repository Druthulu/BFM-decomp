---
ts: 2026-10-22T12:59:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_yiccypQzG0tOOxD06ZQW
---
The target: the address is in a1 ($5) — ONE materialization (lui a1; addiu a1) and 8 loads `lw v0,0(a1)`, `lw v1,4(a1)`, etc.

So the target keeps the base in a register. This is the "8 uses → keep it in a register" behavior that our compile lacks.

**KEY: in the target, the base is in a1 ($5) — the PINNED register!** The decompiler's pin (`register int *src __asm__("$5")`) forces the address into $5. And with the launder, the value is opaque → the pseudo lives in $5 → one materialization.

Without the launder, GCC rematerializes the constant into whatever register each load needs (v0, v1, a0) — ignoring the pin.

So for item 1, the question: what makes GCC keep the constant in ONE register (specifically $5)?

Since the pin is present, if the value were opaque, GCC would put it in $5 ✓. So the mechanism is the same: make the value opaque.

Hmm! But maybe there's another way: if the value were used in a COMPARE (forcing a register), GCC would keep it in a register — but which one? The pin says $5 → $5 ✓!

**SO: FOR ITEM 1, IF THE ADDRESS PARTICIPATED IN A COMPARE, GCC WOULD KEEP IT IN $5 AND USE IT FOR ALL THE LOADS!**

Hmm, but a compare requires an extra instruction ✗ (the target has no compare of the address).

Hmm. Alternatively: if the value is used in a way that requires a register *without* extra instructions...

**!!!!!!!!!!!! IDEA: THE `m[]` STORES !!!!!!!!!!!!**
The target stores the loaded values to m[0..7] (the stack). And the loads are from the base. What if the source's copy were written as:

```c
    m[0] = src[0]; m[1] = src[1]; ...
```
Hmm, same.

**!!!!!!!!!!!! IDEA: WHAT IF THE SOURCE READ THE 8 INTS AS A STRUCT AND THE COMPILER USED A BLOCK COPY? !!!!!!!!!!!!**

Hmm.

**!!!!!!!!!!!! THE REAL IDEA: WHAT IF `src` IS NOT A CONSTANT BUT A *VOLATILE*... no.

**!!!!!!!!!!!! IDEA: What if the 8 values are copied via a pointer that GCC can't fold because the DESTINATION is also involved? Hmm.

Let me think about GCC's reload decision again: with 8 uses of a constant, GCC 2.7's reload would... hmm, in our compile it rematerialized 8 times. So GCC's reload prefers rematerialization when the value is a constant?? That seems wasteful (16 instructions vs 2). Hmm! But that's what we see.

Hmm, wait. Actually, maybe it's not reload: maybe it's the FRONT END. The front end's expand_expr for `src[0]` where src is a variable holding a constant address: the front end computes the MEM address as (plus (reg src) (const 0)) → hmm, but if the front end knows src's value... it doesn't (it's a variable).

Hmm, but our compile shows `lui v0; lw v0,0(v0)` — the address was rematerialized per load with the offset folded in (lw v0,0(v0), lw v1,4(v1), lw a0,8(a0)) — each load has its own lui! So the address was folded INTO each MEM (as (plus symbol_ref const)) → the backend emitted lui per load.

So the fold happened at the RTL level: the pseudo `src`'s value (the symbol_ref) was substituted into each MEM's address.

That's cse's equiv_constant substitution (the MEM address (reg src) → (symbol_ref)) or reload's rematerialization.

With 8 uses, cse would substitute the constant into all 8 MEMs → each MEM becomes (mem (plus (symbol_ref) (const N))) → the backend emits lui+lw per access ✓ (what we see).

**SO THE FOLD IS IN CSE, AND IT'S AGGRESSIVE.** To prevent it, the pseudo's value must be unknown.

Hmm, so both items 1 and 2 need the "opaque value" trick. And item 4 (the launders on `op`, `ax`, `by`) might be different (those are about scheduling, not constants).

**SO: HOW TO GET AN OPAQUE VALUE IN PLAIN C?**

Options:
(1) A load from memory: `x = *p;` — an extra instruction.
(2) A function call result.
(3) An asm.

Hmm, (1): a load from memory — what if the load is from a location whose value GCC can't predict, but the loaded value is USED in a way that's semantically neutral? E.g., load a value and use it in a way that doesn't affect the result? That would add an instruction ✗.

Hmm!!! Unless... the load is FREE because the target already has a load! In item 1, the target has loads from the base. Hmm.

**!!!!!!!!!!!!!!!!!! THE VOLATILE TRICK !!!!!!!!!!!!!!!!!!**

What if `src` is declared `volatile int *`? Then the LOADS from src are volatile → GCC can't fold the address?? Hmm, no: volatile affects the loads, not the address computation. The address would still be folded ✗. And it changes the code (volatile loads aren't reordered) ✗.

**!!!!!!!!!!!!!!!!!! THE "ADDRESS OF A LOCAL" TRICK !!!!!!!!!!!!!!!!!!**

Hmm.

OK, let me now consider the possibility that these items are WALLs. The walls.txt has `cse-const-addr` — exactly this mechanism: "cse folds or substitutes a constant/absolute address the target keeps base-relative (T10 S09, S11, S16)".

Given:
- Item 1: the base's address must stay in one register; cse substitutes the constant into each MEM → 6 extra lui pairs. WALL cse-const-addr (best 20).
- Item 2: the base must stay in a register; cse folds the address → 4 mismatches. WALL cse-const-addr (best 4).
- Item 3: same as item 2.
- Item 4: to be determined.

Before declaring walls, let me try a few more spellings for items 1 and 2, especially:

For item 1: what if the source copies via a *different* formulation that makes the base opaque? E.g.:
```c
    src = (int *)&D_800AE620;
    m[0] = src[0]; ...
```
Hmm, what if the source used `memcpy`-like struct assignment:
```c
    *(int (*)[8])m = *(int (*)[8])&D_800AE620;
```
Hmm, the front end would generate a block copy or 8 moves. Interesting to test.

Or:
```c
    src = (int *)&D_800AE620;
    { int *d = m; int i; for (i = 0; i < 8; i++) d[i] = src[i]; }
```
→ a loop ✗ (different code).

Hmm, what about:
```c
    t0 = src[0]; ...
```
with `src` being a `char *`? Then `src[0]` would be a byte ✗.

Hmm, what about making the base a `const` pointer: `int * const src = (int *)&D_800AE620;` → GCC would propagate the constant → ✗.

What about the address being taken from a global array of pointers? no.

**!!!!!!! THE MOST PROMISING FOR ITEM 1: MAKE THE BASE A *MEMORY* VALUE VIA A POINTER-TO-POINTER? no.

Hmm, hold on! **What about the `obj` pin?** In item 1, `obj` is pinned to $16 (s0) and `src` to $5 (a1). The target's `lw s0,32(s1)` — obj = *(self+0x20) in s0 ✓.

Hmm, what if the source didn't need the `src` pin because the address could be materialized into $5 naturally? No.

**LET ME TRY: for item 1, what if `src` is assigned the address via a *pointer variable* that is a parameter?** no.

OK, let me try a couple of quick experiments for item 1 (struct copy, no temps, byte pointer) and then decide.

Actually — WAIT. A NEW IDEA FOR ITEM 1!!! **What if the 8 loads are done from a pointer that GCC thinks is NOT a constant because it's the result of a *pointer subtraction* or a *cast through a union*?**

Hmm, what about this: the source could read the 8 ints via a `Mat32`-like struct... the header declares `extern Mat32 D_800AE620;` — a struct type! So `D_800AE620` is a Mat32 (a 4x4 matrix = 16 floats?). But the source uses `(int *)&D_800AE620` and copies 8 ints (32 bytes).

Hmm! What if the original source was:

```c
    src = (int *)&D_800AE620;
```
Hmm.

**!!!!!!!! IDEA: WHAT IF THE ORIGINAL USED A POINTER VARIABLE INITIALIZED FROM A CAST OF THE STRUCT ADDRESS, AND THE COMPILER KEPT IT BECAUSE IT WAS A `register` VARIABLE?** — GCC 2.7's register variables: allocated a pseudo; the value is still constant → cse folds ✗.

OK. Let me now do a quick batch of experiments for item 1 (3 variants) and item 2 (3 variants), then move on.

Item 1 variants:
v1: remove the temps: `m[0] = src[0]; m[1] = src[1]; ...` (keeping the pin).
v2: struct copy: `*(int (*)[8])m = *(int (*)[8])&D_800AE620;` — hmm, but then `src` is unused → the pin would be dropped → different code.
v3: `src` used with a variable offset: hmm.

Let me think about v3: to force the base into a register, the MEM's offset must be non-constant. What if the source reads the 8 ints as:
```c
    t0 = src[0]; t1 = src[1]; ...
```
constant offsets ✗.

What if the copy is done as a byte-wise copy? ✗ different code.

**!!!!!!! WHAT IF THE SOURCE'S ARRAY IS ACCESSED VIA A POINTER THAT IS *ALIASED*? !!!!!!**

Hmm, e.g. if `m` and `src` could alias, GCC can't... no, that doesn't make the address opaque.

OK — **what if the source declares `src` as `int *` but assigns it in a way that includes a cast from a *volatile* pointer**? no.

Let me try the experiments. Actually, let me first try the SIMPLEST promising thing for item 1: **remove the `src` pin** (the launder is the row kind; the pin is another kind — but the pins may stay... but we can't REMOVE the pin? "levers of other kinds the def already had may stay, never added" — staying is allowed, removal is... hmm, removing a pin would be a "lever removed" which is fine? The MATCH criterion is "the kinds in <dir>/kinds gone" — the launder must go. Removing the pin as well isn't required, and might be seen as an extra change. Hmm, but the constraint "no register vars, no __asm__" suggests the final body should have NO register vars and NO asm!

**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**
**WAIT!!! THAT'S IT!!! The constraint says "no `register` vars, no `__asm__`"!!! So the final body must NOT have the pins either!**

So for item 1, the MATCH body must have NO register vars and NO asm — meaning the `obj` pin ($16) and the `src` pin ($5) must GO TOO, and the launder.

Hmm! But then "levers of other kinds the def already had (pins under other causes) may stay" contradicts... unless "may stay" refers to... hmm.

Hmm, "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added" — this says pins may STAY. And then "no register vars, no __asm__" — maybe these mean "no NEW register vars, no NEW __asm__" (i.e., don't add levers). Given the explicit "may stay", I read it as: don't add new ones.

Hmm, but "no register vars, no __asm__" as a blanket statement contradicts "pins may stay". Hmm. The safest interpretation: the MATCH requires the row kinds gone; existing pins may stay (explicitly allowed). Adding any new lever is forbidden.

Hmm, but hmm. For item 1, if the pins could go, would the code still match? The pins were added by the decompiler to match the target (the target has obj in s0 and the base in a1). Without the pins, the allocator would choose different regs → mismatch. So the pins must stay for item 1. Hence "pins may stay" is the operative rule, and "no register vars, no __asm__" means "don't add new ones".

OK. So for item 1, the body must keep the two pins and drop the launder, and reach score 0. The launder's job: keep the base in $5 as one materialization.

Hmm, so: **can the PIN alone keep the base in $5?** In our compile, no (GCC rematerialized). Because the value was a constant.

Hmm! But hold on: what if the pin is on a variable whose value is NOT constant...

WAIT!!! What about the *other* pin: `obj` ($16)? obj = *(int *)(self + 0x20) — a runtime value ✓ (not constant).

Hmm.

**!!!!!!!!!! THE IDEA: WHAT IF `src` IS ASSIGNED FROM `obj`-LIKE RUNTIME DATA? NO.

**!!!!!!!!!! THE IDEA: WHAT IF THE COPY IS DONE FROM A POINTER THAT IS *DERIVED* FROM THE PINNED `obj`? no.

OK, let me try the experiments for item 1 now. Batch:
e1: no temps (direct m[i] = src[i])
e2: `m[0] = src[0]; ...` with the src pin kept, but src declared as `int *` (same).
e3: the copy via a `Mat32`-typed pointer: `Mat32 *ms = (Mat32 *)m; Mat32 *sd = &D_800AE620; ms->x = sd->x; ...` — depends on the Mat32 type's fields.

Hmm, e3 requires knowing Mat32. Let me check include/ for Mat32's definition. Hmm, time.

Let me think about what would make GCC keep the base in a register ONE more time...

**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**
**THE ANSWER MIGHT BE: MAKE THE MEM'S OFFSET NON-CONSTANT BY USING A *COMPOUND* EXPRESSION THAT GCC CANNOT FOLD INTO THE ADDRESS — e.g. an offset that depends on a runtime value that is zero.**

In item 1, there IS a runtime value: `self` (param_1) and `obj`. But any non-zero offset changes the semantics ✗.

Hmm, BUT: what about an offset that's a runtime value multiplied by zero? Folded ✗.

**!!!!!!!!!!! WHAT ABOUT A `volatile` READ OF A GLOBAL THAT HOLDS ZERO? Not available.

OK. Let me try yet another angle: **maybe the trick is to make the address's value be the SAME as another value that is already in a register** — e.g., `src = &D_800AE620;` where D_800AE620 is... no.

Let me now try the item-4 experiments (the launders there are about scheduling, not constants) and then wrap up with walls for 1-3 if needed.

Actually hold on. Let me reconsider item 1 once more. The KEY question: why did the ORIGINAL keep the base in a register? Because in the ORIGINAL, the base's value was NOT a constant...

**!!!!!!!!!!!!!!!! OR THE ORIGINAL'S `src` WAS A *PARAMETER* OR *GLOBAL POINTER* !!!!!!!!!!!!!!!!**

Hmm! What if the ORIGINAL source was:

```c
s32 func_8012B4B8(int param_1) {
    int *src = (int *)&D_800AE620;
```
Hmm.

**OR: WHAT IF THE ORIGINAL READ THE MATRIX FROM A GLOBAL POINTER VARIABLE?** e.g. `extern int *D_800AE620_ptr;` — but the target's reloc is on D_800AE620 with lui/addiu → a constant address, not a load ✗.

**OR: WHAT IF THE ORIGINAL'S ADDRESS WAS COMPUTED FROM A RUNTIME VALUE?** e.g. `src = (int *)((char *)D_800AE620 + 0);` → folded ✗.

Hmm, so the original's address value must have been a constant that GCC chose to keep in a register rather than rematerialize. **WHY WOULD GCC DO THAT?** Because of the PIN? No (the original had no pin). Because the value was used 8 times and GCC's reload decided to keep it?

**AH WAIT!!! THAT'S IT!!!** Maybe GCC's reload DOES keep a constant in a register when it's used many times, and OUR compile's problem is different: maybe our compile's problem is that the PIN (a hard-reg pseudo $5) forced GCC to *rematerialize* into $5... no, our compile didn't use $5 at all.

Hmm, hold on! Let me look at our compile again: the loads are `lw v0,0(v0)`, `lw v1,4(v1)`, `lw a0,8(a0)` — each load has its own address register! That's the cse substitution (the constant folded into each MEM) — the MEM address became (plus (symbol_ref) (const N)) → the backend emitted lui into a temp reg + lw.

If instead the base stayed in a register, we'd have `lw v0,0(a1)` ✓ (the target).

So the question is whether cse substituted. cse substitutes the constant into a MEM address when the pseudo's value is known. With 8 uses, that's 8 substitutions. GCC's cse does that (it's "free" in its cost model? the constant address is 1 insn (lui+addiu = 2) vs. keeping a reg...).

Hmm, so GCC prefers the substitution. In the original, it didn't. => the original's base value was NOT a known constant.

**=> THE ORIGINAL'S BASE WAS NOT A CONSTANT.** But the reloc shows a constant address materialization... which is consistent with a value that's *computed* at runtime as &D_800AE620! E.g.:

```c
    src = (int *)&D_800AE620;    /* constant */
```
vs
```c
    src = base + 0;              /* runtime */
```

Hmm! What runtime value equals &D_800AE620? Hmm.

**OR THE ORIGINAL USED A DIFFERENT KIND OF ADDRESS: `&D_800AE620` where D_800AE620 is a `Mat32` STRUCT and the original took `&D_800AE620` — constant ✗.

Hmm, so how could the original's base be non-constant?! It must have been a load... but the target has no load for it.

**UNLESS: the original's base was the ADDRESS OF A LOCAL VARIABLE or a function parameter!!** e.g.:

```c
s32 func_8012B4B8(int param_1) {
    ...
    src = &local_array;    /* a stack address */
```
✗ (the reloc is on D_800AE620).

Hmm hmm. What if the original's source was:

```c
    src = (int *)&D_800AE620;
```
and the original compiler was NOT gcc 2.7.2?!

Hmm! That's a real possibility: the ROM was compiled with a different gcc version (e.g. gcc 2.6.3 or Sony's own), whose cse didn't substitute constants into MEM addresses. But the project reproduces the ROM with gcc 2.7.2 for most functions...

Hmm, but for THIS function, the decompiler needed BOTH pins AND a launder to match. The pins are the decompiler's way of forcing the register allocation. The launder forces the ONE materialization.

So maybe the original was compiled by a compiler that kept the constant in a register (a1) because of 8 uses.

**AND THAT'S THE POINT: the "8 uses" heuristic!** Let me check GCC 2.7's reload for the "rematerialize vs keep" decision. In reload.c, there's a function `reload_reg` and the key logic is in `reload.c`'s `reload_reg`:

```c
	  /* If we are loading a constant into a register, and the register
	     is used only once, ... */
```

Hmm, I recall the relevant code in reload.c:

```c
      /* If this is a constant, and we have a register that is already
	 loaded with this constant, ... */
```

and there's `reload_cse` (a separate pass) and the "reload_reg" decision:

```c
  /* If we are going to reload a register that is a pseudo, and the
     value is a constant, we can either rematerialize it or ... */
```

Let me grep reload.c for "rematerial" to find the heuristic.

Actually — hold on. The relevant decision might be in `reload.c`'s `reload_reg`:
```c
	  if (reg_equiv_contain_p (reg, GET_MODE (reg), &value)
	      && GET_CODE (value) == CONST_INT
	      && ... )
```
Hmm, that's for CONST_INT (immediates), not addresses.

**The address case**: the pseudo's value is a symbol_ref → `reg_equiv_contain_p` → the value is a symbol_ref → reload would need to materialize it into the register → `reload_reg` → "if the value is a constant, we can set the register to it" → it emits the lui/addiu. The decision to rematerialize vs. keep: in reload.c, `reload_reg` has:

```c
	  /* If the value is a constant and the register is not needed
	     elsewhere, rematerialize... */
```

Honestly, the empirical difference between the target and our compile must be explainable by the value being unknown (opaque) vs. known (constant).

**THE FINAL ANSWER ATTEMPT: the ORIGINAL's source had the base assigned from a RUNTIME expression that equals the address.**

Hmm, hold on!!! What about this: the original might have been:

```c
    src = (int *)&D_800AE620;
```
where `D_800AE620` was declared as `extern Mat32 D_800AE620;` (a struct) — and `&D_800AE620` is the address ✓ constant.

OK OK. Let me consider that the ORIGINAL source is simply NOT reconstructible in plain C with gcc 2.7.2 for these functions — that's why the phase added the levers! And the task is to find a plain-C spelling that matches. If none exists, it's a WALL.

Given the time (I'm at ~1h on items 1-2), let me now:
1. Spend ~15 min on item 4 (different mechanism — scheduling).
2. Try a couple more spellings for items 2/3 (the "compare" idea, the "use the base twice" idea).
3. Record results.

Hmm, wait. Actually, let me reconsider the "use the base twice" idea for item 2 ONE more time, but now with the insight about what cse does:

For item 2, if the base had 2 uses, one of which is a COMPARE, then the compare would force the base into a register and the plus would use it (base-relative). But the compare must be semantically neutral and produce no extra instruction...

Hmm, hold on! What about a compare that the ORIGINAL might have had and that the decompiler's reconstruction DROPPED?! For example, in C750's ELSE branch, the loop is:

```c
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
```

Hmm, what if the original was:

```c
    base = (s32)D_80120194;
    p = base + 0x658C;
    it = base + 0x10C;    /* = D_801202A0 */
```
✗ (the reloc would be on D_80120194).

Hmm, what if:
```c
    base = (s32)D_80120194;
    p = base + 0x658C;
    ...
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
```
The base has 1 use.

**WHAT IF THE ORIGINAL COMPARED THE BASE WITH THE POINTER IN THE LOOP?** i.e. the loop's exit condition compares against the base + offset. Hmm, the loop exits when `it == p`.

**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**
**AAAAH!!! WAIT!!! WHAT ABOUT THE `p != base` CHECK IN THE IF BRANCH?! THE ORIGINAL C750 MIGHT HAVE HAD THE SAME SHAPE IN THE ELSE BRANCH — BUT THE ELSE BRANCH'S SEMANTICS DIFFER...**

Hmm, hmm. OK, let me look at C2D0's target once more for a compare involving the base...

C2D0 target:
```
4178: lui v1, hi(D_80120194)
417c: addiu v1,v1,lo
4180: j 4190
4184: addiu a0,v1,25996
4188: j 41bc
418c: move v0,v1
4190: lui v1, hi(D_801202A0)
4194: addiu v1,v1,lo
4198: beq v1,a0,41bc
```
The compare at 4198 is (D_801202A0 vs p). The base is not compared.

Hmm, BUT: notice the base is in v1 and D_801202A0 is ALSO in v1! And the compare is `beq v1,a0` — comparing the loop pointer (v1) with p (a0).

WAIT!!! What if the compare at 4198 is actually comparing the BASE (v1 = &D_80120194) with p?! No — v1 was overwritten with D_801202A0 at 4190.

Hmm, but hold on! What if the ORIGINAL source's `test:` block did NOT reassign `it` but instead the source was:

```c
    it = (s32)D_80120194;       /* base */
    p = it + 0x658C;
    goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
```
The compare is (D_801202A0, p) ✓ as in the target.

OK. So no base compare.

**FINAL ANSWER FOR ITEMS 2/3: the base must be opaque → asm → WALL.**

Hmm, hold on, hold on. Let me reconsider ONE more possibility: **what if the base is materialized in a register because it's used as the base of a MEM in the ORIGINAL, and the ORIGINAL's source read a byte from the base?!**

In C750's ELSE branch, the loop reads `*(u16 *)it` for the loop pointer (D_801202A0, D_801202B0, ...). Hmm! What if the ORIGINAL's loop started at the BASE (D_80120194) and the entries were 0x10C apart, with the FIRST entry (at the base) being... hmm, the target reads D_801202A0 first.

Hmm, what if the original's loop was:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
test:
    it = (s32)D_801202A0;
```
Hmm.

OK, I need to stop the theory and go empirical. Let me spend 10 minutes trying a batch of spellings for items 1 and 2, then do item 4, then write up.

BATCH for item 1 (the base must stay in $5):
b1: `m[0] = src[0]; m[1] = src[1]; ...` (no temps)
b2: copy via a local pointer: `int *d = m; d[0] = src[0]; ...`
b3: `src` declared as `int *` but assigned `src = (int *)&D_800AE620;` (same)
b4: read the 8 ints as a struct copy: `*(int (*)[8])m = *(int (*)[8])&D_800AE620;`
b5: use `src` with a variable index in a *dead* statement? no.

BATCH for item 2:
b1: `p = 0x658C + it;`
b2: `p = (s32)((u8 *)it + 0x658C);` (pointer arithmetic)
b3: `it` as `u8 *`: `u8 *bp = (u8 *)D_80120194; p = (s32)(bp + 0x658C);`
b4: the base used twice: `p = it + 0x658C; q = it;` (q dead)
b5: `it` declared `unsigned`

Let me write these and score them all in one go.

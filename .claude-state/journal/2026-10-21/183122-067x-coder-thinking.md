---
ts: 2026-10-22T00:31:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_pBHfbO2CPGecERQvMPzF
---
No global pointer. So the address must be a constant.

Hmm, so how can plain C make the compiler keep the address in a register?

Insight: maybe the *lever* isn't needed at all if the *pointer is used in a way that forces the reg*: what if the pointer is used in a *store*? E.g. the target's else branch has stores to sp18/sp20.

Wait — the comment in the source says: "x and y must both be READ before the first store (the stores to the addressable sp arrays kill cse's equivalences for the `cam` loads)". So the *order* matters.

Let me look at the actual difference again: c1 differs at ins 47-48 (the y load) and 76-77 (the later y load). The x loads (at 145c in the target / mine) matched? The residual shows only the *y* loads differ! Let me re-read the residual:

```
replace mine[47:49] target[53:54]
     47  lui v1,0x0 | lh v1,4(s1)
     48  lh v1,4(v1) | --
```
So in the target, the y load is `lh v1,4(s1)`; in mine it's `lui v1; lh v1,4(v1)`. And the x loads are the same in both (using s1).

And at 76-77: the later y load: target `lhu v1,4(s1)`, mine `lui v1; lhu v1,4(v1)`.

Interesting!! So only the *y* (offset 4) loads are rematerialized; the x (offset 0) loads use s1 in both!

Why? Because for the x load, the address is exactly D_80126B5E = the constant in s1 (reg+0). For the y load, the address is D_80126B5E+4, a *different* constant → cse prefers to rematerialize the exact constant (lui+addiu = 2 insns) over using s1+4 (which needs an extra addiu? no — `lh v1,4(s1)` is free!).

Hmm, but cse's find_best_addr might not consider "reg + offset" as a candidate for the address, only the base reg with the offset folded... Actually cse's find_best_addr works on the *address* expression: for `cam->y` = (reg cam) + 4, the candidates are: the reg+4 form, or the constant form. find_best_addr's "best" computation: it computes the cost of each candidate address. For a reg address, the cost is the cost of materializing the reg (which for a pseudo holding a constant is 2 instructions: lui+addiu... but the reg already holds it, so 0).

Hmm, but the observed behavior is the opposite. So cse decided the *constant* D_80126B5E+4 is cheaper than reg+4.

Ohh, I bet I know why! Because the *pseudo* cam (holding the address) is used at the x load with offset 0 → the reg s1 = the address; and for the y load, cse's find_best_addr sees the address as (reg cam) + 4 where "reg cam" is a *pseudo* whose value is the constant D_80126B5E. cse then checks: can this address be rematerialized? Yes: it's a constant → cost = 2 instructions (lui+addiu). The alternative (reg+4): the reg is s1, already holding the base → cost 0? But maybe cse's cost model counts the offset addiu (1 instruction) → hmm, still cheaper than 2.

Wait, but the target (with the lever) uses reg+4! So the lever changed the decision. With the lever, the pseudo cam is redefined by the asm → its value is unknown → cse can't rematerialize → it must use the reg+4 form.

And the *x* load (offset 0) uses the reg in both cases because rematerializing the exact constant D_80126B5E would ALSO cost 2 instructions (lui+addiu) vs the reg (0). So cse prefers the reg for offset 0 but prefers the constant for offset 4? That's weird... unless for offset 4 the constant is "the same cost" and there's a tie-break.

Hmm, whatever the mechanism, the question is: what plain C makes the y load use `lh v1,4(s1)`?

Since the address D_80126B5E+4 is a *different constant* from the base, and cse prefers constants for it...

IDEA: what if the y load is expressed as an access through the *same base* in a way that yields "reg + 4" without cse folding the constant? E.g. via a *char pointer*:
```
u8 *cam = (u8 *)&D_80126B5E;
...
(s16)*(u16 *)(cam + 4)
```
The address is (reg cam) + 4 — the same as before. cse would still rematerialize.

IDEA: what if the y load is done through a *different pointer variable* that is assigned from cam:
```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
...
d = (s16)cam->y - ...;
```
vs
```
u16 *camb = (u16 *)&D_80126B5E;
d = (s16)camb[2] - ...;   /* offset 4 */
```
Same.

IDEA: what if we access the y value through a *pointer arithmetic* that GCC treats as a reg-relative address with a *non-constant* offset? No.

IDEA: what if the y load is `*(s16 *)&D_80126B62` (the other symbol)? Then the address is a *different* constant (D_80126B62) → cse would materialize it (lui+addiu) — same as rematerializing. No.

Hmm, so how does the *target* get `lh v1,4(s1)`?? Only via the opaque reg.

So the ONLY lever-free way: make the base pointer's value opaque to cse. Which requires a non-constant source.

Hmm, hold on! What about the *order* of the loads and the *cse equivalences*? The comment says the stores to the sp arrays kill cse's equivalences. What if the y load happens in a context where cse's equivalence info is dead?

Actually, let me reconsider: maybe the cse behavior depends on the *number of sets* of the cam pseudo. The lever gives the pseudo 2 sets (the initial assignment + the asm). What if in plain C the pointer is assigned TWICE (a "real 2nd set")?

```
cam = (Cam183098 *)&D_80126B5E;
...
cam = (Cam183098 *)&D_80126B5E;   /* real 2nd set */
```
cse would fold the second set to the first (same value) → one set. Hmm, but cse's "make_regs_eqv" might make them equivalent → the pseudo has 2 sets with the same value → find_best_addr might behave differently! Worth testing (it's the "real 2nd set" move, which is legit per moves.md).

Where to put the 2nd set? Right after the first (like the asm). Let me test:

c2:
```
cam = (Cam183098 *)&D_80126B5E;
cam = (Cam183098 *)&D_80126B5E;
```
Hmm, that's silly-looking. Better:
```
cam = (Cam183098 *)&D_80126B5E;
cam = (Cam183098 *)((u8 *)cam);   /* hmm */
```
Or with a *volatile-free* trick: `cam = (Cam183098 *)&D_80126B5E;` then later `cam = (Cam183098 *)&D_80126B5E;`? A "real 2nd set" that's identical — cse folds it.

Hmm, but the asm's 2nd set has an *unknown* value (the asm output is opaque). A C re-assignment has a *known* value → cse folds it → no opacity.

So the opacity is unattainable in plain C. UNLESS the value is genuinely opaque: derived from a load.

Hmm, hmm. What if the base pointer is derived from a *load of the address from a static*? We said that changes the instructions.

What if the base pointer is derived from an *existing global* that has the same address? E.g. if some global variable *is* at D_80126B5E... The address of a global IS the constant. No.

What if the base is derived from a *function pointer*? no.

OK, so what about the OTHER direction: prevent cse from rematerializing by making the *offset* not a constant? Then the address is reg+reg → cse can't rematerialize → it uses the reg. But the runtime offset must be 4 for correctness, and the code would need to compute the offset (extra instructions).

Hmm! Unless the offset comes from a *constant* that GCC keeps in a reg... e.g.:
```
s32 off = 4;
d = (s16)*(s16 *)((u8 *)cam + off) - ...;
```
GCC folds off=4 → the address becomes reg+4 → back to square one.

What if `off` is a *function parameter*? No.

What if the offset is derived from the *pointer itself*: e.g. `cam + (sizeof(Cam183098) - 4)`? folded.

Hmm.

Let me look at this from yet another angle: maybe the fix is to make the *x* and *y* loads use the SAME address expression so that cse's "best address" is the reg for both. E.g. if the y load were `*(s16 *)((u8 *)cam + 4)` and the x load `*(s16 *)cam`... cse computes the best address per *memory location* (it tracks locations by the constant). For the location D_80126B5E+4, the candidates are: the constant address (from the reg's known value) and the reg+4 form. cse picks the "best".

What if the y value were loaded *through a pointer to the same base with the same offset form*? e.g. both x and y via a u16 array:
```
u16 *camb = (u16 *)&D_80126B5E;
x = camb[0];  /* address = reg + 0 */
y = camb[2];  /* address = reg + 4 */
```
The same situation.

Hmm, but hold on: for the *x* load, cse chose the reg (s1) over the constant. Why? Because the constant D_80126B5E would cost lui+addiu (2) vs the reg (0). For the y load, the constant D_80126B5E+4 also costs 2. So why the difference?!

OH WAIT. Maybe I have it backwards: maybe for the y load, cse's "best address" IS the reg+4, but the *rematerialization* happens in a different pass: `cse.c`'s "address rematerialization" — hmm, the comment says "cse's find_best_addr folds cam->y back to %hi/%lo(D_80126B5E+4)".

Hmm, so for the y load cse preferred the constant, for the x load the reg. The difference between the two: the x load's address is exactly the constant that the reg holds. Maybe cse's cost model: using the reg costs 0 extra instructions but requires the reg to be *live* at that point; the reg (s1) is live across the call, so using it is fine.

Ugh, without reading cse.c I can't be sure. Let me look at the actual difference in the compiled output more concretely: maybe I can find a *cheap* change that flips the y load to use the reg.

Experiment ideas (cheap to test):
(A) Move the `cam` assignment *after* the two param_1 stores (i.e. later) — maybe the reg's live range changes.
(B) Assign cam inside each use site: e.g. `Cam183098 *cam = (Cam183098 *)&D_80126B5E;` in the guard and another in the else branch → then the else-branch loads would have their own address (2 more lui/addiu) → no.
(C) Use `&D_80126B5E` directly in the x load and `cam->y` for y? Then x = constant (lui+addiu+lh) and y = reg... hmm, that changes the x load.

Hmm, (C) is interesting: the target has BOTH x and y loads via s1. If the x load used the constant directly, the target wouldn't match.

(D) What if the *pointer* is a `u8 *` and the y load is `*(s16 *)(cam + 4)`: cse might see the address as (reg)+4 → hmm same.

(E) What if we make the *base* pointer a *pointer to a pointer*...

(F) What if we *store* the address into a local variable of pointer type and load it back? extra instructions.

(G) What if the *asm-free* way to make a value opaque is a *function call* that returns the address? e.g. a helper that returns &D_80126B5E — but that adds a call (and we can't add functions outside the body... well, we could add a `static` function inside? No, the body is a function definition; adding a nested function isn't C89).

(H) What about making the pointer's value depend on the *parameter* in a way that cancels at runtime? e.g. `cam = (Cam183098 *)((u8 *)&D_80126B5E + (param_1 - param_1));` → folded (param-param = 0). Hmm, GCC folds x-x to 0.

(I) `cam = (Cam183098 *)((u8 *)&D_80126B5E + (param_1 & 0));` → folded.

(J) What about a *float* trick? No.

Hmm.

(K) What about making the *offset* 4 come from a *volatile* read? barrier, no.

OK, let me now consider: maybe the intended crack for THIS item is different: maybe the *loads* can be restructured so that the *x* load is dead (e.g. the guard uses `cam->x` once) and the *y* load's address...

Hmm, hold on! Let me reconsider the target asm:
```
1430: lui s1,0x0
1434: addiu s1,s1,0
...
145c: lh v0,0(s1)      <- cam->x
1478: lh v1,4(s1)      <- cam->y
...
14e4: lhu v0,0(s1)     <- x again
14e8: lhu v1,4(s1)     <- y again
```
Note: the else branch reads x and y as *u16* (lhu) — because the C has `u16 x = cam->x; u16 y = cam->y;` and the guard reads them as s16 (lh). So there are 4 loads, 2 of each.

In c1 (no lever), the x loads presumably use s1 (matched) and the y loads rematerialize.

So the difference is ONLY the y loads (2 places).

What if I make the y loads use the *same* address form as the x loads by changing the *offset* representation? E.g. what if the y load is written as `*(s16 *)((u8 *)cam + 4)` vs `cam->y`? Both are reg+4.

What if the y load were `*(s16 *)((u32)cam + 4)`? Same.

Hmm, what if the struct's y field is at offset 4 and we access it via a *pointer to a pointer*...

What if we make the *base* for the y load be a *different* reg? e.g. if there were two pointers:
```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
...
d = (s16)cam->y - ...
```
The address is (reg cam)+4. cse rematerializes to the constant.

What if the y access is `((Cam183098 *)((u8 *)cam + 4))->y`? That would be an offset of 4+4=8. No.

What if the struct type is different: e.g. if y is at offset 4 in the struct, the address is base+4. What if I access y through a *pointer to a u16* at base+4: `*(s16 *)((u8 *)cam + 4)` — same.

Hmm, so the offset+4 is the issue. What if the *base* for the y load were the address D_80126B5E+4 itself, i.e. a *different constant*: `*(s16 *)&D_80126B62`? Then cse would materialize D_80126B62 (lui+addiu) — 2 instructions, not matching the target's `lh v1,4(s1)`.

So the ONLY way to `lh v1,4(s1)` is a reg holding D_80126B5E with an offset of 4, where cse prefers the reg over the constant.

Since cse preferred the constant for base+4 but the reg for base+0, maybe the decision is about *cost*: cse's find_best_addr computes the cost of the reg-based address as: the reg must be live at that point; if the reg is a *pseudo* that has been copied to a hard reg, using it costs 0. Hmm.

You know what? Let me look at the actual gcc 2.7.2 source for find_best_addr — it's the *compiler*, and understanding it is legitimate research. Where's the compiler source? Let me check if it's on disk (e.g. in a docker image or a vendored copy).

Let me search for cse.c in the project.

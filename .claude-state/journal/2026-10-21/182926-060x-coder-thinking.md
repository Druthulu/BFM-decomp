---
ts: 2026-10-22T00:29:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hX1oSMhVADQoSqclr1HX
---
This is a launder: `cam = (Cam183098 *)&D_80126B5E; __asm__("" : "=r"(cam) : "0"(cam));`

The comment says: "§153 address-rematerialisation launder: without it cse's find_best_addr folds `cam->y` back to %hi/%lo(D_80126B5E+4) and emits a SECOND `la` instead of the target's `lh 0x4($s1)`."

So the lever keeps the address in a register ($s1) so both loads use it. Plain-C way: read both x and y through a pointer that is used twice... The trick: the address is used twice (cam->x and cam->y), so GCC should keep it in a register — but cse's find_best_addr rematerializes the address for the second load (it decides to use %hi/%lo again) because the address is "cheap" to rematerialize.

The real-C fix: make the pointer's value "opaque" so cse can't rematerialize it — e.g., by making cam a *pointer to a struct* obtained in a way that isn't a constant address. E.g.:

```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
```
The address is a constant → cse rematerializes.

Plain-C alternatives:
- Use a pointer variable that is set from a non-constant: e.g. `Cam183098 *cam = (Cam183098 *)&D_80126B5E;` → constant.
- What about using an *array* pointer: `u16 *cam = (u16 *)&D_80126B5E; cam[0]`, `cam[2]`? The address arithmetic might prevent rematerialization. Hmm, but the target reads `lh 0x0($s1)` and `lh 0x4($s1)` — x at offset 0, y at offset 4. With a u16* the offsets would be 0 and 2 — the target shows 0x4. So the struct layout matters: Cam183098 has x at 0 and y at 4.

- Another approach: use a *volatile*? No (barrier).
- Use the pointer twice with an intervening statement that would kill cse's equivalence: the comment in the else branch says "the stores to the addressable sp arrays kill cse's equivalences for the cam loads". Hmm, in the *guard* section (before the else), the two cam->x/cam->y loads happen with an intervening statement? Let's see:

```
d = ((Unkstruct_80126B58 *)param_1)->unk6 - (s16)cam->x;
if (...) return;
d = (s16)cam->y - ((Unkstruct_80126B58 *)param_1)->unkA;
```
Between the two cam loads there are statements (the comparison and a possible return). cse's find_best_addr: for the second load (cam->y), it checks if the address can be rematerialized cheaply: the address is a constant (&D_80126B5E+4) → it prefers the constant (lui/addiu) over keeping the pointer in a register... but the register holding the address is $s1 (callee-saved) — cse decides to rematerialize because the address is "cheap".

To prevent that in plain C: make the address non-constant. E.g.:

```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
```
→ constant address. But:
```
u32 base = (u32)&D_80126B5E;  /* still constant */
```

Hmm. What if the pointer is derived from a *volatile-free* but non-constant source, e.g. from a parameter? No, the address is fixed.

The trick: cse's find_best_addr rematerializes when the address is a "constant" (symbol+offset). If the address expression is not a simple symbol+offset (e.g. `&D_80126B5E + 0` or a pointer stored in memory), cse can't rematerialize → it keeps the register.

Ideas:
(a) `Cam183098 *cam = (Cam183098 *)&D_80126B5E;` — constant.
(b) `Cam183098 *cam; u16 *p = (u16 *)&D_80126B5E; cam = (Cam183098 *)p;` — the cast through a pointer variable might defeat find_best_addr? find_best_addr handles REG addresses too (it can rematerialize a register address if the reg holds a constant). Hmm.
(c) Use a *static* array or a global struct: e.g. if there's a struct instance, `cam = &someGlobal;` — still a constant address.

Hmm. What does the target asm look like? Let me look at the target's asm to see how the address is loaded: `la $s1, D_80126B5E` then `lh 0x0($s1)`, `lh 0x4($s1)`. So the address is in a callee-saved register.

And the lever-free version would emit: `la $v0, D_80126B5E; lh 0x0($v0)` ... and then `la $v0, D_80126B5E+4; lh 0x4($v0)`? Something like that (a second la).

How to make GCC keep one register? Options:
- Make the pointer's *value* not a compile-time constant: e.g. compute it via a real computation. But the address IS a constant.

Hmm! What if the address is taken from a *global pointer variable*? E.g. if there's a global `u16 *D_80126B5E_ptr`? No.

- What if the pointer is stored in memory and reloaded? e.g. `Cam183098 *cam = *(Cam183098 **)&someSlot;`? Not available.

- Use an array: `u16 *cam = (u16 *)&D_80126B5E;` then `cam[0]` and `cam[2]`: the offsets would be 0 and 2 → the target has 0x4. Unless I use a struct type with x at 0 and y at 4 (Cam183098) — the current code does that.

Wait, the rematerialization issue is about the *address expression*: `&D_80126B5E` + 4 for y. What if I write the y load as `*(s16 *)((u8 *)cam + 4)`? Same address.

What if the y load's address is expressed differently so that find_best_addr can't see it as a constant? E.g. `cam->y` where cam is a *volatile* pointer? no.

What if I make the two loads use *different* pointer variables derived from a common one? e.g.
```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
...
d = ... - (s16)cam->x;
...
d = (s16)cam->y - ...;
```
Both through cam.

The real fix in plain C: make `cam` a *pointer whose value is not a constant* at the RTL level. For example:
```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
```
is a constant. But if the pointer came from a function call or a load, it'd be non-constant. Since we can't change the address, maybe:

```
static Cam183098 *const camBase = (Cam183098 *)&D_80126B5E;
Cam183098 *cam = camBase;
```
Still constant.

Hmm, what about the "pointer reuse" move from moves.md: "launder | func_801A31CC | MATCH: pointer reuse: a1 = (u8 *)link; *(s32 *)a1 = 0; keeps the store base in the link reg".

Interesting. And "launder | func_80186B70 | MATCH: launder->pv=*p; pv&=mask split; pin $3 dropped".

So the successful cracks involve making the address a *real* second set or reusing a pointer.

Idea for this item: make `cam` a pointer that is *loaded* from a static location, or make the address expression involve a *variable*:
```
s32 off = 0;
Cam183098 *cam = (Cam183098 *)((u8 *)&D_80126B5E + off);
```
With `off` a variable, the address is no longer a constant → cse can't rematerialize → it keeps the address in a register! And `off` is a local variable that GCC will fold to 0... but the *address* would then be `reg + 0`? Hmm, GCC's constant propagation would fold off=0 → back to a constant address. Unless off is set to 0 via an opaque path.

Hmm, but "init at decl" is a legit C0505 move. If `off` is a local with an initializer 0, GCC folds it.

What if the address is derived from another pointer: e.g.
```
u8 *base = (u8 *)&D_80126B5E;
Cam183098 *cam = (Cam183098 *)base;
```
find_best_addr would see the address as a REG (base) and might still rematerialize the constant into the reg. Actually cse's find_best_addr: for a REG address, it checks if the reg's value is a constant → it can rematerialize into the reg directly (it prefers to use the reg if the value is "cheap to compute"). Hmm, in that case the address is computed once into a reg and reused — which is what we want! But cse found it "cheaper" to rematerialize the second address as a constant.

Hmm, the specific mechanism (from the comment): "cse's find_best_addr folds cam->y back to %hi/%lo(D_80126B5E+4) and emits a SECOND la instead of the target's lh 0x4($s1)".

Note: in the target, the register is $s1 (callee-saved) — so the address is in a *callee-saved* register. GCC chose s1 because the address is live across calls (func_8014CB8C()). Hmm, but the address is used BEFORE the call... The cam->x and cam->y loads are before the call to func_8014CB8C? Let's see: d = ...cam->x; if (...) return; d = cam->y - ...; if (...) return; then func_8014CB8C(). And in the else branch, cam->x and cam->y are read AGAIN (lines 3360-3361) — after the call! So the address must survive the call → callee-saved register s1.

So the target: `la s1, D_80126B5E` once, and 4 loads from it (x, y in the guard; x, y again in the else branch).

Without the lever, cse rematerializes: for the loads in the else branch (after the call), the address is rematerialized as a constant (la) — but that would be a *different* register (v0) and possibly a second `la`.

So the lever's effect: keep the address in one register (s1) for all 4 loads.

How to achieve in plain C? The address must be non-rematerializable. Ideas:
(a) Make the pointer's value opaque: e.g. derive it from a *static* variable:
```
static Cam183098 camStore;  /* no, wrong address */
```
(b) Store the pointer in a *global* variable? Changes the code.
(c) Use `&D_80126B5E` but through an array of pointers?
(d) The "pointer reuse" move: use a pointer variable that is *assigned* from another pointer:
```
u8 *p = (u8 *)&D_80126B5E;
Cam183098 *cam = (Cam183098 *)p;
```
GCC's find_best_addr: the address of cam->y is (reg p) + 4. Since p holds a constant, cse might still rematerialize.

Hmm, but actually: find_best_addr's rematerialization decision depends on `cse->src` / the "cheapest" address. It prefers the address that requires the fewest instructions. If the pointer is in a register that already holds the address, using it is 0 extra instructions. So why would cse rematerialize? Because the *second* address (D_80126B5E+4) is a *different* constant: cse would need to compute lui+addiu for it (2 instructions) vs using the register with an offset (+4 → 1 addiu). Hmm, cse's find_best_addr prefers the reg+offset form normally...

The comment says the opposite happens: cse folds cam->y back to %hi/%lo(D_80126B5E+4) — i.e. it uses the constant address instead of reg+4.

Hmm, why? Because the reg ($s1 or whatever) is *dead* at that point? If the pointer variable is dead after the last use, cse can rematerialize. But the pointer is used 4 times...

Wait, maybe the issue is the *first* use: `cam->x` at line 3338, then `cam->y` at 3342 — in between, `d` is computed and there's a branch. Maybe cse decides the reg is "expensive" to keep (live across a call later) vs the constant.

The lever (the empty asm with a tied output) forces `cam` to be a *pseudo that is redefined* — the asm says cam = cam (opaque). This makes the address non-constant in the RTL? The asm's output is a register holding the same value — so after the asm, the address is in a register but "opaque" (the compiler doesn't know it's the constant D_80126B5E) → find_best_addr can't rematerialize it as %hi/%lo → it keeps the register!

So the lever's role: make the address opaque to cse.

Plain-C way to make an address opaque: compute it from something the compiler can't fold. E.g.:

```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
```
→ the compiler knows the value.

What if the address is loaded from a *static* variable? e.g.
```
static Cam183098 *camPtr = (Cam183098 *)&D_80126B5E;   /* in this TU */
Cam183098 *cam = camPtr;
```
Then `cam`'s value is a load from a static → not a constant → cse can't rematerialize → the address stays in a register! But adding a static variable to the TU changes the TU (the win.c is a *body* replacement; adding a static inside the function body is allowed? "no signature or decl change outside the body" — a static declaration inside the body is inside the body. But a static var adds storage to the object → the object changes (the bank judges the whole object!). The score says "the function is byte-identical; the bank judges the whole object" — a static in the function body would add a .data/.bss entry → the object differs → the score might fail? The score reported is about the function's instructions ("mine 66 ins, target 66"), so probably only the function's asm is compared. But a static in a function is emitted in .bss — the *object* would differ, but the score is per-function. Risky but might be OK.

Hmm, but that's hacky. Alternative: make the address opaque through an *arithmetic* expression that GCC can't fold: e.g. `&D_80126B5E` is a symbol address; adding 0 folds.

What about using a *pointer to a pointer* in an existing global? Is there a global that holds the address? Unlikely.

What about: `Cam183098 *cam = (Cam183098 *)&D_80126B5E;` → but the loads use `cam->x` and `cam->y`...

IDEA: use a *char pointer* with explicit offsets so that the address expressions are "reg + const" rather than "symbol + const"? They're already reg+const.

Hmm, what if the *first* use of cam is not a load but something that makes GCC treat the address as unknown? E.g. compare it? `if (cam == NULL)`? That changes the code (adds a compare).

IDEA (from moves.md): "launder | func_80186B70 | MATCH: launder->pv=*p; pv&=mask split; pin $3 dropped" — the launder there was replaced by a *real* operation on the value.

Here the launder is on the *pointer* (address), not a value. The real-C replacement for an address launder: make the address come from a *real* load/store — e.g., "pointer reuse": use a pointer that is stored and reloaded.

What if I make the pointer's address opaque by taking it from a *local array*?
```
u16 local[4];
Cam183098 *cam = (Cam183098 *)local;  /* no, wrong address */
```
No.

What about: the address of a *static* struct in the TU? There's no such struct.

Hmm, what about using a *function's* return? No.

What about a *cast through an integer*:
```
Cam183098 *cam = (Cam183098 *)(u32)&D_80126B5E;
```
GCC folds that to the same constant.

What about: `Cam183098 *cam = (Cam183098 *)&D_80126B5E;` where D_80126B5E is declared as `extern u16 D_80126B5E;`? Then &D_80126B5E is the symbol address → constant.

Hmm. So how do we make an address opaque in plain C without volatile/asm? Answer: load it from memory.

Is there an existing global array/pointer in the TU that could hold it? Not really.

BUT: what about using the *address of a local variable* trick? No.

What about the C0505 "pointer reuse" move: e.g.
```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
```
and then use `cam` for x, and for y use a *different* pointer derived from cam in a way that produces `lh 0x4($s1)`:
```
d = *(s16 *)((u8 *)cam + 4) - ...
```
Hmm, that's the same address (reg+4). Would cse rematerialize it? find_best_addr for (reg cam)+4: if cam is in a reg, the address is reg+4 → cheap → it should use it. The problem is cse's "best addr" logic: it compares the cost of (a) using the reg+offset and (b) rematerializing the constant. It seems cse chose the constant.

Hmm, why would cse prefer a second `la`? Because in the target the address is in $s1 (callee-saved) and... hmm, the *cost* model in find_best_addr: it computes "how many instructions" for each candidate address. The reg+offset costs 1 (addiu) while the constant costs 2 (lui+addiu) — so reg should win. Unless the reg isn't available (the reg holding cam was... hmm).

OK, empirical approach again. Let me look at the target asm first, then try candidates. Let me dump the target function's asm.

Let me find the built object: build/src/ov_SC05_010/ov_SC05_010_jr_80181CDC.o.

Let me write a helper to make this fast: a script that takes the item dir and prints the target asm (using the tu/fn files). Let me write dis2.py under G14 that reads <itemdir>/tu and <itemdir>/fn and finds the object in build/src/<basename dir>/<basename>.o. The tu path is src/ov_SC05_010/ov_SC05_010_jr_80181CDC.c → the object is build/src/ov_SC05_010/ov_SC05_010_jr_80181CDC.o. Let me write that.

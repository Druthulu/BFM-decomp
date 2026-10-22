---
ts: 2026-10-22T00:30:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_F9h83dUxi41mCnSf9EpC
---
Confirmed: without the lever, GCC emits `lui v1,0x0; lh v1,4(v1)` (a second address materialization) instead of `lh v1,4(s1)`.

So the difference: 2 extra instructions (the lui) and the address register.

Now, how to make the address opaque in plain C?

Ideas:
1. The address is used 4 times. The 3rd/4th uses are after a call. GCC keeps the address in s1 for the first two uses (the guard) but rematerializes for the later ones? Hmm, in the target, s1 holds the address across the call. So GCC *did* keep it in a callee-saved register. In c1, the later loads use a fresh lui (v1) — meaning GCC didn't keep the address in s1 across the call, or it did but then rematerialized anyway.

Wait, in c1 the address is still in s1 (from 1430-1434) for the first loads. But the later loads (after the call) use `lui v1; lh v1,4(v1)`. So GCC chose to rematerialize instead of using s1. Why? Because s1 is live across the call — using it would be free... Hmm, cse's find_best_addr decided the constant address is "better" (fewer instructions: lui+addiu vs 0 for using s1?). Hmm, using s1 with an offset 4 is 0 extra instructions (the lh with offset). So the constant costs 2 (lui+addiu) but GCC chose it. That's find_best_addr's "cheapest" heuristic in cse.c, which prefers a constant address when the register holding the base is "expensive" (i.e. the reg is a pseudo that would need to be in a callee-saved reg) or when the address is "cheap to rematerialize" (a symbol).

The lever (the empty asm) makes the address *unknown* to cse: the pseudo cam is redefined by the asm, so find_best_addr sees a REG address whose value is unknown → it cannot rematerialize → it uses the reg.

So how to make it unknown in plain C? The address must be computed from something the compiler can't track.

IDEA: use a pointer that comes from a *global variable* in the TU. Let me check the TU for a global that holds an address near D_80126B5E. Actually, what about the possibility that the *original game code* used a different data layout: e.g. the game might have had the camera x/y in a struct accessed via a pointer variable. But we must match the built asm.

IDEA 2: Make the address depend on a *runtime* value that is zero — e.g. `cam = (Cam183098 *)((u8 *)&D_80126B5E + (d & 0))`? The compiler folds `d & 0` to 0.

IDEA 3: Use a *pointer-to-pointer* cast through an existing global that we can... no, we can't add globals (well, we can add a static local in the body — it changes the object but maybe not the function's code; but a static local's *address* is a constant too, and loading it would add an instruction).

Hmm, what if the static local holds the *pointer value* and we load it? That gives `lw` instead of `lui/addiu` → 1 instruction instead of 2, and the address is opaque → the loads would use the loaded reg. But the target has `lui s1,0x0; addiu s1,s1,0` — so the target *does* materialize the address as lui+addiu. Hmm! So the address IS materialized in the target too — into s1. The difference is only that the *later* loads use s1 instead of rematerializing.

So: in the target, the address is materialized once into s1 (lui+addiu) and then reused. In c1, the address is materialized into s1 (for the first loads) and then *again* into v1 for the later loads.

So the lever's effect: the address pseudo is "opaque" so cse can't rematerialize the *second* address.

So the plain-C way: make the address expression non-constant *after* the first materialization. E.g., if the pointer is *reused* from another pointer variable that GCC doesn't track...

Hmm, what about this: the address is taken from a *pointer to a pointer* in a global? Let me look for an existing global in the TU like `D_80126B5E` being part of an array or a struct.

Let me look at the declarations around D_80126B5E in the TU and the header. Let me grep the include/ dir for D_80126B5E and Cam183098.

Also: is there a global *pointer* variable in the game (like a base pointer) that could hold it? Unlikely.

IDEA 4: Use the *same* pointer variable for the two loads but make the address expression involve a *volatile-free* runtime value: e.g.

```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
...
d = ... - (s16)cam->x;
...
d = (s16)cam->y - ...;
```
and in the else branch:
```
u16 x = cam->x;
u16 y = cam->y;
```

What if I *reassign* cam in between? E.g. `cam = cam;` (identity, forbidden).

What if I *copy* the pointer through a union or a char pointer:
```
u8 *p = (u8 *)cam;    /* cam's value copied */
u16 x = *(u16 *)p;
u16 y = *(u16 *)(p + 4);
```
Now the address of x is (reg p) + 0 and of y is (reg p) + 4. Would find_best_addr rematerialize? The reg p holds the constant D_80126B5E (GCC knows). find_best_addr would still see it as a constant address (it tracks the reg's value). Hmm.

Unless the copy is through a *volatile*... no.

IDEA 5: What if the *pointer* is stored into a local array and reloaded? e.g.
```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
...
```
no.

IDEA 6: Use the *address of a local* trick: no.

IDEA 7: What if the loads are done via a *helper pointer* that's derived from a function call? no.

IDEA 8: Use a *different* global symbol that is at the same address? e.g. D_80126B5E and D_80126B62 are the camera x/y pair (per the comment at line 3300: "The camera x/y pair at D_80126B5E / D_80126B5E+4 (== D_80126B62)"). So D_80126B62 == D_80126B5E+4.

What if the y load is written as `*(s16 *)D_80126B62` (a different symbol!) — then the address is a different constant → GCC would materialize D_80126B62 separately (2 instructions) → not the target.

Hmm, but wait: that's the opposite of what we want.

IDEA 9: The real question: can we make GCC not rematerialize? What if the address is *used* in a way that makes cse keep the reg: e.g. the address is compared to something? That adds code.

IDEA 10: What if the *number of uses* increases so that cse keeps it? The target has 4 uses; c1 has 4 uses too.

Hmm. Let me look at cse.c's find_best_addr logic... I shouldn't read tool source, but this is the *compiler* source, not a tool. The compiler source is available? The project uses gcc 2.7.2 (a patched build). Where is it? Probably in tools/ or a docker image. Let me check if the gcc source is available locally: find for "find_best_addr".

That could be very useful: understanding why the asm changes the decision. But time is limited. Let me try empirical candidates:

c2: Use a `u8 *` base and cast for the y load:
```
u8 *cam = (u8 *)&D_80126B5E;
d = ((Unkstruct_80126B58 *)param_1)->unk6 - (s16)*(u16 *)cam;   /* x */
d = (s16)*(u16 *)(cam + 4) - ...;                                 /* y */
```
Hmm, the struct field types: cam->x is u16 at offset 0, cam->y at 4.

c3: Use a *pointer to the struct* but load x and y into locals *before* the guard, so that the loads are adjacent:
```
u16 camx = cam->x;
u16 camy = cam->y;
d = ... - (s16)camx;
d = (s16)camy - ...;
```
But that changes the order of the loads (the target loads x, then later y — with a branch in between; and the else branch loads x,y again). Hmm, the target loads cam->x at 145c and cam->y at 1478 (separated by the guard branch) and then x,y again at 14e4/14e8. So the loads are NOT all at the top.

c4: In the else branch, use the *pointer* differently: e.g. `u16 x = cam->x; u16 y = cam->y;` — that's what it is.

Hmm, so the key difference is the *later* loads (after the call) rematerializing.

IDEA 11: What if the else-branch loads use a pointer that was *set in the guard section* (e.g. `cam` is assigned again)? no.

IDEA 12: What if the *address* is passed through a function call? no.

IDEA 13: What if we make the *pointer* variable's value be a *pointer to a pointer* in a global? Let me search the TU/headers for a global pointer to the camera.

Let me grep the include dir for D_80126B5E and Cam183098 to see the declarations.

Actually, let me think about the structure differently: maybe the *original game code* (from which this decomp was derived) had the camera accessed through a *pointer variable* (a global). But the decomp uses the constant address. The lever was needed to reproduce the game's asm (where the address was in a register).

Hmm! But what if the original code loaded the address from a *global pointer*? Then the asm would be `lw s1, addr` — but the target has `lui s1; addiu s1` → the address is a constant. So in the original, the address was a constant in a register, and the compiler kept it. Our compiler (gcc 2.7.2, the same one) rematerializes unless the value is opaque.

So the ONLY way is to make the value opaque — which in plain C means: the pointer's value must not be a compile-time constant.

What if the pointer is derived from the *parameter*? No, wrong address.

What if... the pointer is computed as `(Cam183098 *)((u32)&D_80126B5E + 0)`? folded.

What if the pointer comes from a *global variable that holds the address*? We could ADD such a global to the TU... but the win.c is only the function body; adding a global outside the body is not allowed ("no signature or decl change outside the body"). A *static local* inside the body is inside the body! But then the load `lw` would replace `lui/addiu` → mismatch.

Hmm, unless the static local is a *pointer* whose address we take... no.

Wait. What about this trick: the target's `lui s1,0x0; addiu s1,s1,0` is the materialization of the constant. If the address were opaque, GCC would materialize it exactly the same way (lui+addiu) into s1 and keep it! Because the materialization is just "compute the constant into a reg". So if the value is opaque but *equal* to the constant at runtime... GCC can't know it's equal, so it would compute it from... hmm, it needs a source. If the value is opaque, GCC has no way to compute it — it must come from somewhere (a load, a call, etc.).

Unless the opacity comes from an operation that GCC can't fold but which is a no-op at runtime: e.g. `cam = (Cam183098 *)((u32)&D_80126B5E & 0xFFFFFFFF)` → folded. `cam = (Cam183098 *)((u32)&D_80126B5E + (s32)(0 * param_1))` → folded (0*param = 0).

What about `(u32)&D_80126B5E | 0` → folded.

What about using a *union* type-pun: `*(Cam183098 **)&someLocal`? no.

What about a *volatile* read of a global that holds the address? Not available.

Hmm, what about the possibility of making the address opaque by taking it from a *function's return*? no.

OK so maybe this item is a WALL too. But wait — maybe there's another approach: prevent cse from *rematerializing* by making the address's *offset* non-constant? No: the y load at offset 4 — if the offset were a variable, the address would be reg+reg (no rematerialization possible!). E.g.:

```
s32 off = 4;
d = (s16)*(s16 *)((u8 *)cam + off) - ...
```
GCC would fold off=4 → constant. Unless off is not constant... e.g. off comes from a computation GCC can't fold. But then the runtime value must still be 4 for correctness → the code would have extra instructions (computing off). Hmm, but maybe GCC folds it back to a constant anyway.

Hmm. What if the offset is *0* for x and the y load uses `cam->y` (offset 4)? The rematerialization is of the *base* address.

Let me look at this from the cse.c angle: find_best_addr chooses among candidate addresses for the same memory location. The candidates include the reg-based address and the constant. It picks based on "cost" = the number of instructions to compute. It has a rule: if the reg is a "hard reg" (s1) it can use it with an offset. Hmm, but it chose the constant.

Actually, maybe the issue is different: cse's find_best_addr prefers the *constant* when the address is a "cheap" constant and the reg is in a *different* basic block / the reg's value is defined by a *pseudo* that has multiple sets...

The asm makes the cam pseudo have a second set (from the asm) → so the address's reg is defined by the asm → cse's find_best_addr can't rematerialize (it can't know the reg's value).

Plain-C equivalent of "the reg's value is unknown": the pointer must be assigned from a non-constant. There's no such source in the function...

UNLESS: the pointer is assigned from *another pointer that was itself assigned from a non-constant*. Circular.

Hmm, what about the *param_1*? The camera address is fixed, so no.

OK: what if the *loads* are done through a pointer that is *stored into a local array* and read back? e.g.
```
Cam183098 *cams[1];
cams[0] = (Cam183098 *)&D_80126B5E;
d = ... - (s16)cams[0]->x;
```
Now the address is a *load* from the stack: `lw v0,off(sp); lh v0,0(v0)` → extra instructions. No.

What if the pointer is passed to a function? No.

Hmm, what about the "pointer reuse" move from moves.md: "launder | func_801A31CC | MATCH: pointer reuse: a1 = (u8 *)link; *(s32 *)a1 = 0; keeps the store base in the link reg". In that case the launder was on a store base, and the crack was to use the pointer for a real store.

Here the launder is on a *load* base used 4 times. The crack would be: use the pointer for something real... but the loads are the only uses.

Hmm, what if the *guard* section is restructured so that the address is used in a way that requires keeping it in a reg: e.g. if the address were used *after* the call in a way that can't be rematerialized...

WAIT. What about the *order* of the loads? The target loads x at 145c (before the guard) and y at 1478 (after the first guard) — with a branch between. Then x,y again after the call. GCC's rematerialization for the *later* loads happened because... hmm, in c1 the *later* loads (76-77) used `lui v1; lhu v1,4(v1)` — so GCC rematerialized the address for the post-call loads. But it kept s1 for the pre-call loads (the target's s1 comes from 1430/1434).

Hmm, so in c1, s1 holds the address and is live across the call (it's a callee-saved reg), but GCC still rematerialized for the post-call loads. That's find_best_addr preferring the constant.

Why would the asm change that? Because after the asm, the cam pseudo's value is unknown → find_best_addr sees the address as a REG (unknown value) → it must use the reg.

So: the plain-C way to have an "unknown value" pointer: the pointer must come from a load/call. The only load available without adding instructions: hmm...

IDEA: What if the pointer is *the parameter*? Like, what if the *whole function* is restructured so that the camera pointer comes from param_1? No, wrong semantics.

IDEA: What if we use a *pointer to the struct* that is obtained by *casting a pointer to a different type*? Still constant.

IDEA: What if the address is `&D_80126B5E` but accessed through a *pointer variable declared as `u16 *`* and the compiler's find_best_addr for a u16* + offset 8... the base is still constant.

Honestly, this looks like a WALL too, unless there's a trick. Let me test a couple of quick variants to see if any keeps the address in a register:

c2: char-pointer with explicit offsets:
```
u8 *cam = (u8 *)&D_80126B5E;
...
d = ((Unkstruct_80126B58 *)param_1)->unk6 - (s16)*(u16 *)cam;
...
d = (s16)*(u16 *)(cam + 4) - ...;
...
u16 x = *(u16 *)cam;
u16 y = *(u16 *)(cam + 4);
```
c3: keep the struct pointer but load x,y into locals at the top? no (changes load order).

c4: the pointer is *reused* for the loads via a *second* variable:
```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
...
u16 x = cam->x, y = cam->y;
```

c5: make the *else branch* use the pointer differently: e.g. `u16 x = *(u16 *)cam; u16 y = *(u16 *)((u8 *)cam + 4);` (mixed spellings).

c6: Make the address opaque by *hiding* it in a struct member of a local? no.

c7: The KEY one: what if the pointer is assigned from a *global pointer* that already exists in the game? Let me grep the headers for something like "D_80126B" or a camera pointer global. Let me look at what globals exist near D_80126B5E. Perhaps there's a global *pointer* to the camera, e.g. `D_80126B58`? The code uses `Unkstruct_80126B58` — a struct type at 0x80126B58 (a *type*, not a variable). Hmm.

Let me grep the include dir for D_80126B5E and see if there's a pointer to it.

Let me do that now — it's cheap.

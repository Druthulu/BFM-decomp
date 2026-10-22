---
ts: 2026-10-22T10:54:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_523idYxktiZzo7t5z3zc
---
HUGE progress in understanding! With the declaration-without-initializer form (zd0):
- The pointer is now in **$s3** (a callee-saved register) — because the pseudo is now a real variable assigned at runtime → it's live across the calls → allocated a callee-saved reg!
- The add is now "addu v0,s3,v0" — POINTER FIRST ✓✓✓ (the combine swap did NOT happen — the pointer is a REG!)

So my hypothesis was RIGHT: with the assignment form, the pointer stays a REG and the operand order flips to the target's! But now the pointer is in $s3 instead of $a1, and the frame grew (s3 saved).

The target has the pointer in **$a1** (a caller-saved reg) — because in the target, the pointer pseudo is NOT live across calls... hmm, wait: the target's pointer IS used after calls (the final add is after `func_8018ABE0`/`func_8018AEB4` calls). Hmm! In the target: "move s0,v0" → the pointer is in $s0 (a callee-saved reg!) — hmm!! Let me re-read the target asm:

```
2c0c: lui a1,0x0        ; &D_80195AF6 → a1
2c10: addiu a1,a1,0
2c14: lui at,0x0
2c18: addu at,at,v0
...
2c48: sll v0,v0,0x3
2c4c: addu v0,a1,v0     ; the pointer is a1 (caller-saved!)
2c50: lh v0,4(v0)
```
So in the target, the pointer is in $a1 — a caller-saved register — even though the use (the final add) is after calls! How can a value live across a call be in a caller-saved register? It can't... unless the *materialization* (lui/addiu) is placed right before the use (after the calls) — i.e. the pointer's pseudo is materialized lazily at its use!

Hmm! But the "lui a1; addiu a1" in the target is at 2c0c (the arm's start), BEFORE the calls (the calls are at 2bd0/2bfc in the other arm; in this arm, is there a call before 2c4c? Let me check: the else arm (2c0c-2c50) — the calls func_8018ABE0/func_8018AEB4 are in the OTHER arm (2bd0/2bfc). So in the else arm there are NO calls before the final add! ✓ So the pointer can live in $a1 (caller-saved) ✓.

So in the target, the pointer pseudo is live only within the else arm (no calls inside it) → it can be in $a1 ✓.

In our zd0 variant, the pointer is in $s3 — because in OUR source, the pointer p is assigned BEFORE the if/else (at the function scope) — hmm, no: in zd0 the assignment `p = D_80195AF6;` is inside the else arm (the declaration is there). Hmm, but the compiler allocated s3 (callee-saved) — hmm, why? Because the variable p is declared at the FUNCTION scope (the declaration `D_80195AF6_t *p;` is at the top of the function, since the declarations are at the top) → so p is live across the whole function → across the calls → callee-saved ✗.

AH, but the value assigned is inside the else arm. Hmm, but gcc's live analysis: p is assigned in the else arm and used in the else arm → not live across calls... hmm, but gcc allocated s3.

Hmm, maybe because the *declaration* at function scope makes p's "live range" span the whole function in gcc's analysis? In gcc 2.7, the live range of a pseudo is computed by flow analysis from the sets/uses. p is set in the else arm and used in the else arm → the live range should be short. Hmm, but gcc's local-alloc uses the "global allocno" logic: a variable declared at function scope with a set in one branch and uses in the same branch → the allocno is local.

Hmm, but the result shows s3. So gcc treated p as live across the whole function. Why? Because p is *declared* at the top and gcc's "variable lifetime" analysis (in flow.c / local-alloc) uses the declaration position for the "birth" of the variable? Hmm, in gcc 2.7 the local-alloc computes the live range from the set/use positions, but for a variable whose declaration is at the top of the function, the pseudo is "born" at the function's start? Hmm, actually in gcc 2.7, `expand_function` creates the pseudo at the declaration point, and the "birth" is there. Since the DECLARATION is at the top of the function (all declarations are), the pseudo is born at the top → live across the calls → callee-saved ✗.

So the fix: make the variable's DECLARATION (and thus its birth) inside the else arm — i.e. a BLOCK-SCOPE declaration! But C89 requires the declarations at the start of a block — and the else arm IS a block ✓✓. So:

```c
        } else {
            D_80195AF6_t *p;
            s16 newval;
            p = D_80195AF6;
            newval = D_80195AF6[...].f0;
            ...
        }
```
Hmm, but then the declaration is at the start of the else block → the pseudo is born at the block's start ✓ (still before the calls? there are no calls in the else arm) → so it can be in a caller-saved reg ($a1) ✓✓✓.

Wait, but in the ORIGINAL def, the declaration `D_80195AF6_t *p = D_80195AF6;` IS already inside the else arm! Let me re-check the orig:

```c
        } else {
            D_80195AF6_t *p = D_80195AF6;
            s16 newval = D_80195AF6[...].f0;
```
Yes — the declaration is inside the else block ✓. So the pseudo p is born at the else block's start ✓ — and in the base variant (v1, with the initializer), the *value* is a constant → the front end substitutes it → the uses get the symbol → no pseudo at all → the plus has the symbol → the swap.

With the assignment form (zd0), the pseudo p is born at the block's start and holds the symbol → the address tree is (plus (reg p) (reg idx)) → NO SWAP ✓✓ — but the *value* (the symbol) must be materialized into p's register, and p is allocated... hmm, in zd0 the diff shows the pointer in $s3. Why s3?

Because in zd0, I replaced the initializer with a declaration, but the declaration is still at the same place (inside the else block) — hmm, so the pseudo should be born at the block's start. Hmm, but the else block's start... hmm, wait: in zd0 the diff shows the frame grew by 8 (sw s3) — so p went to a callee-saved reg.

Hmm! Why? Because the declaration is at the top of the else block, and the else block is reached from the function's body — the pseudo's "birth" is at the block's start, but gcc's live-range analysis... hmm.

Hmm, hold on: in zd0, the declaration `D_80195AF6_t *p;` is at the top of the ELSE block, and the assignment `p = D_80195AF6;`... wait, did my replacement even include the assignment? Let me check: zd0's replacement was ("            D_80195AF6_t *p = D_80195AF6;" → "            D_80195AF6_t *p;") — I REMOVED the initialization entirely without adding an assignment!! So p is uninitialized → undefined behaviour → the compiler did whatever. Hmm, but the score was 13 with "addu v0,s3,v0" — the pointer in s3 (garbage).

Oops. zd0 is invalid C semantics (uninitialized use). zd1/zd2/zd3/zd4 (which add the assignment) ERRORED — let me look at why (probably my anchor strings didn't match: in v1.c the line is "            s16 newval = D_80195AF6[((Unkstruct_800B5CB8 *)a0)->unk100].f0;" ✓ hmm, the error was in the generator ("MISS" wasn't printed... hmm, actually the errors were COMPILE-ERRORs from the scorer, not MISS). Let me check: the gen script prints "MISS" for a missing anchor; no MISS was printed for zd1-zd4, so the files were generated but failed to compile. Why? Because in zd1 I added `p = D_80195AF6;` before the `s16 newval = ...` declaration → a statement before a declaration → C89 parse error ✗.

Right! In C89, all declarations must precede statements in a block. So the assignment must come AFTER all the declarations in the else block. Let me restructure:

```c
        } else {
            D_80195AF6_t *p;
            s16 newval;
            p = D_80195AF6;
            newval = D_80195AF6[...].f0;
```
Hmm, but the original order is: `D_80195AF6_t *p = D_80195AF6;` then `s16 newval = D_80195AF6[...].f0;`. So:

```c
        } else {
            D_80195AF6_t *p;
            s16 newval;
            p = D_80195AF6;
            newval = D_80195AF6[...].f0;
```
Let me construct that properly (both declarations first, then the two assignments).

This is a very promising direction! If the pointer becomes a pseudo born at the block's start with the value assigned there, the tree is (plus (reg p) (reg idx)) → pointer first ✓, and the register allocation should give it $a1 (caller-saved, since the else arm has no calls before its use) ✓✓.

Let me build this variant for 80184828 (and similarly for 8018483C — hmm, there the issue is the COPY: `pb = &D_800B99DC; p = pb;` — with the assignment form, the front end doesn't substitute, so the RTL has two sets and the copy might survive → "lui v0; addiu v0; move s0,v0" ✓✓!).

Let me write these carefully:

For 80184828 (base v1.c):
```
        } else {
            D_80195AF6_t *p;
            s16 newval;
            p = D_80195AF6;
            newval = D_80195AF6[((Unkstruct_800B5CB8 *)a0)->unk100].f0;
```
The anchor in v1.c:
"            D_80195AF6_t *p = D_80195AF6;\n            s16 newval = D_80195AF6[((Unkstruct_800B5CB8 *)a0)->unk100].f0;"
→
"            D_80195AF6_t *p;\n            s16 newval;\n            p = D_80195AF6;\n            newval = D_80195AF6[((Unkstruct_800B5CB8 *)a0)->unk100].f0;"

Let me also try variants where only the declaration/assignment split applies to p (keeping newval's initializer).

And for 8018483C (base x1.c):
"    p = &D_800B99DC;" → with a declaration `u16 *pb;` at the top and:
"    pb = &D_800B99DC;\n    p = pb;"

Let me test these now!

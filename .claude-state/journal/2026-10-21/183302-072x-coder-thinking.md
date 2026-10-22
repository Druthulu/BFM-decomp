---
ts: 2026-10-22T00:33:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ZNEXtmo5nw09GjAMVZPD
---
The struct is {u16 x; u16 unk2; u16 y;}. So y is at offset 4.

The target: `lh v1,4(s1)` — the y load with offset 4 from the base reg.

Now, key question: can plain C produce that? The base reg must hold D_80126B5E with an *opaque* value.

Hmm, hold on! What about this: what if the *x* load is done with a *constant* address and the *y* load with the reg+4 — i.e. the roles swapped? cse's rule might be per-location. But the target has both via s1.

Alternatively, what if the *base* is materialized as a constant in a reg because the *first* use is base+0 (matching exactly), and then the y load... cse would want the constant for y.

Hmm, what if the *order* of the loads is swapped in the source (y first, then x)? Then the y load (base+4) would come first: cse would... hmm, at the time of the y load, is the base reg even available? The base is materialized at its first use. If the y load comes first, the address = base+4 → cse rematerializes the constant (lui+addiu) → 2 instructions, and the x load (base+0) would use... the reg? which would then be materialized separately → 2 lui/addiu pairs. Worse.

OK, let me try yet another idea: the *unknown-value* pointer could come from a *function parameter* of a *nested* function — no.

Or: from a *cast of a float*? no.

Or: from a *union* pun of the constant address:
```
union { u32 a; Cam183098 *p; } u;
u.a = (u32)&D_80126B5E;
cam = u.p;
```
GCC folds the union pun (it's a type-pun of a constant) → constant.

Or: from a *memcpy*? no.

Or: from an *array* of pointers in the TU: `static Cam183098 *tbl[1] = {&D_80126B5E};` → then `cam = tbl[0];` → a load from .data → extra instructions (lw) and a data change.

Hmm! Actually, wait. What if the load is *free* because the target already loads something from the same place? No.

OK, I'm now fairly convinced item 2 is a WALL with the tag `cse-const-addr` (already in walls.txt: "cse folds or substitutes a constant/absolute address the target keeps base-relative (T10 S09, S11, S16)").

Hmm, but the brief says for a WALL: "best = lowest score of a lever-free body". c1/c2/c3 = 10.

But hold on — before declaring, let me try ONE more idea: the "pointer reuse" move: use the *cam* pointer for a *real* operation that keeps it in a reg. E.g., what if the camera x/y loads are done via a *pointer that is also used for a store*? There's no store to the camera.

And another idea: what if the loads are done through the *sp arrays*' addresses? no.

Another idea: **the `u16 *cam` spelling with the *base* being the *first* element**: c2 tested (10).

Another: what if the *offset* 4 is expressed as a *negative* offset from D_80126B62? i.e. use the *y symbol* as the base and offset -4 for x:
```
u16 *camy = (u16 *)&D_80126B62;  /* the y address */
x = *(s16 *)(camy - 2);  /* D_80126B5E */
```
Then the x load's address = reg-2 → hmm, the y load (offset 0) would use the reg and the x load (offset -2) would rematerialize. Doesn't match.

OK, one more realistic idea: the *struct pointer* `cam` is used with `cam->x` and `cam->y`. What if instead we use a *pointer to the middle*? no.

Let me accept the WALL for item 2 and move on. Actually hold on, let me try ONE more: what if the *pointer* is stored in a *local variable* and the loads use the local (so the address comes from the stack)? The stack slot's content is the address; cse's reg_equiv for the local would be... the local is a pseudo whose content is the constant → same.

Hmm, what if the *local* is a `volatile`? barrier, forbidden.

What if the local is a *static*? `static Cam183098 *cam;` → the address is in .bss/.data → a load → the target has no such load. No.

OK: WALL. Actually, WAIT. One more important idea!!! What if we make the *y* load use the *same* base reg by making the *base* the address of the *y* field's *predecessor*...

Hmm, alternatively: what if the *struct* pointer is used with a *negative* index trick: `cam->y` where the compiler computes base+4. cse's rule might be "if the address is a constant AND the reg's content is a constant AND the address != reg content → rematerialize". To make the *address* not a constant while the reg holds the base...

What if the base reg holds D_80126B5E and the y load's address is computed as (reg + 4) where the RTL *plus* insn is NOT folded into the MEM? Then the address is a REG (the plus result) — a pseudo whose content is a constant → cse knows it's constant → rematerialize. Same.

Alright, WALL for item 2. Best = 10, tries = 3.

Hmm, wait. Hmm, one more: what if the *x* load is eliminated (the guard uses the value differently) so that the *only* remaining base-relative load is y? E.g. if the x load were at offset 0 (matching the reg) and y at +4 — the target has both. If the x load were removed (say the guard is restructured to use a *different* expression), the y load would still rematerialize.

OK. Decision: item 2 = WALL cse-const-addr, best 10.

Hmm, but hold on. Let me reconsider the problem statement: "Lever-free = none of the row kinds in <dir>/kinds remain". The row kind is "launder". Maybe for this item the *launder* is not needed to be removed *entirely* — the goal is a body where the launder is gone AND the score is 0.

Since the score 0 requires matching the built asm (which includes the lever's effect), and the lever's effect is unattainable in plain C → WALL. Yes.

BUT: hmm, wait. Is the target really the built asm *with* the lever? What if delever_search's target is the *original game asm* (from a corpus) rather than the build? The brief says "compares with the function in build/". And the orig.c scored 0 → the target = the built object. Yes.

OK, item 2 = WALL.

Hmm, but that's 2 walls in a row, and the shard has 11 items. Let me move faster: for the remaining 9 items, I'll look at the launder's nature and try the "real 2nd set" move (the moves.md-proven approach) quickly, and also consider that some launders may be simple (e.g. a launder on a value that isn't needed at all).

Let me speed up: for each item, read the function, identify the launder lines, write orig + 1-3 candidates, score, and record. Budget ~10 min per item now (I have 9 items left and it's 20:00 — about 4 hours of work). Hmm, that's a lot. Let me aim for ~10 min per item.

Let me do item 3: func_8017D73C (src/ov_SC06_008/ov_SC06_008_jr_8017C294.c), launder, 86 lines.

Let me read it.

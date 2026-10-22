---
ts: 2026-10-22T13:02:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_HBduvITMliCR3rY0pl2r
---
v6 (decl reorder) → 25 (no change). v7 (s32 types) → 50 (211 ins, worse). v8 → 25.

Hmm, the decl reorder didn't change anything. So the allocation difference isn't from the declaration order.

Let me think about the allocation: the target has ax=s0, ay=s1, bx=s2, white=s3, by=s4(pinned). Mine has ay=s0, bx=s1, white=s2, ax=s3, by=s4.

Interesting: in mine, ax is s3 (low priority) and white is s2. In the target, ax is s0 (highest) and white is s3.

The launder on ax (the 2nd set) — how does it make ax the HIGHEST priority? Hmm, in GCC's global-alloc, the priority is computed from the "refs" (the number of references) and the live range length. The launder's 2nd set adds a reference to ax and extends its live range → a higher priority ✓.

So the real 2nd set must (a) add a reference to ax, (b) extend its live range, (c) be a real 2nd set (not folded).

`ax = (s16)ax;` (v8) — for an s16 ax, the cast is a no-op → folded → no effect (25, same).

So I need a real 2nd set for ax (s16) that is value-preserving. Options:
- `ax = ax;` → folded (cse deletes the self-copy) — hmm, does it? In GCC, `ax = ax;` → expand_assign → (set (reg ax) (reg ax)) → cse deletes it (a no-op copy) ✗. Hmm, but the *live range* might still be extended? cse deletes the insn → no.

Hmm, wait — the brief says "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". So `ax = ax;` is out anyway.

- `ax = (s16)(ax + 0);` → folded.
- `ax = (s16)(ax * 1);` → folded.
- `ax = (s16)(ax | 0);` → folded.
- `ax = (s16)(ax & 0xffff);` → hmm! (ax & 0xffff) on an s16: the constant 0xffff doesn't fit in a signed 16-bit → the promotion to int → the result is an int → truncated to s16 → GCC would fold (ax & 0xffff) for a 16-bit value → the same value → folded ✗.

Hmm.

What about `ax = (s16)(unsigned short)ax;`? Same ✗.

What about a 2nd set with a DIFFERENT value that is still correct in context? E.g., what if the second `ax` set is `ax = ax` but from a different source...

Hmm, what about the "u16 trick" from G03: "pin: $0 zr -> u16 s7v (HImode copy, srl keeps a0)". Hmm.

**What about making ax's SECOND set come from a WIDER temporary?**
```c
    s16 ax;
    ...
    { s32 t = ax; ax = (s16)t; }    /* hmm, a temp + a cast */
```
The cast s32→s16 on an s32 temp: (set ax16 (truncate t)) — hmm, ax is s16 → the assignment truncates → in RTL: (set (reg ax HI) (subreg HI (reg t SI))) → a SUBREG copy → cse might fold it into the use ✗ (a subreg copy of a reg is usually folded by cse/reload).

Hmm.

**What about giving ax a 2nd set with a genuinely different value that is still correct?** E.g., in the second prim block:
```c
        prim.x0 = ax; prim.y0 = by; prim.x1 = ay; prim.y1 = bx;
```
What if the source recomputed ax from ay: `ax = ay + 0x7B;`? Hmm, but ay was changed in between! Let me look:

```c
        bx = out.vy;                      /* $s2 */
        ay = out.vx;                      /* $s1 */
        by = bx - 0x5D;                   /* $s4 */
        ax = ay + 0x7B;                   /* $s0 */
        bx = bx - 0x57;                   /* $s2 in place */
        { op launder; ay = ay + 0x75; prim.x0 = ay; ...; aGsSortLine(&prim, op, 0); }
        [ax launder][by launder]
        prim.attr = 0; prim.r = white; prim.g = 0; prim.b = 0;
        prim.x0 = ax; prim.y0 = by; prim.x1 = ay; prim.y1 = bx;
        aGsSortLine(&prim, &D_800A6518[...], 0);
```
So after the first block, ay = ay + 0x75 (the old ay + 0x75). The second block uses prim.x1 = ay (the updated ay).

So ax's value in the second block = the same as in the first block ✓ (ax wasn't modified).

If the source recomputed ax in the second block, it would need the OLD ay — not available (ay was overwritten) ✗.

Hmm, so the 2nd set of ax must be a "re-tie" (the same value).

**Hmm, what about a DIFFERENT variable being re-tied?** E.g. what if the original had a variable `t` holding ax's value, and the 2nd set was `ax = t;`? Hmm, that's a copy from a temp — a real 2nd set (a copy from a different pseudo) → cse would fold it if t's value is known ✗.

Hmm.

**LET ME RECONSIDER: maybe the launder's effect isn't the 2nd set but the OPACITY.** The launder makes ax's value opaque at that point → the register allocator treats it as a "re-tie" → the copy is a real move ✗ hmm, but the target has no extra move for ax.

Hmm, let me look at the target's disassembly around the second block to see how ax is handled. Let me dump the target for item 4 (207 ins) and look at the region.

Given my time budget, let me take stock:
- It's 08:10. I've been going 1h33m. I have 4 items, none cracked.
- The remaining work: 30 scored tries per item for a WALL, plus the log and results.

Given the difficulty, maybe I should accept WALLs for the items I can't crack, but I must do ≥30 scored tries each with ≥20 min each. I've done ~5 tries on item 1, ~12 on item 2, ~4 on item 4, 0 on item 3.

Hmm, the WALL requirement: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So to record a WALL I need 30 scored tries per item. Each try is ~1-2s, so 30 tries = ~1 min. Plus the 20 min of work. That's feasible: I'll spend the remaining time trying many variants per item (they're cheap), and document.

Let me be systematic now. For each item, I'll write a variant generator with many spellings and score them in bulk, then record the best.

Let me do item 3 (C750) first since it's the same mechanism as item 2 (and I can reuse the insights).

Item 3: C750 — remove the 2 launders in the ELSE branch. The ELSE branch's base is used once → the same fold issue. The IF branch has no launder.

Let me check: does removing the launders from C750 give a small score? And can the IF branch's trick (the base used twice) be applied to the ELSE branch?

**HOLD ON!!! IDEA FOR C750's ELSE BRANCH: WHAT IF WE RESTRUCTURE THE ELSE BRANCH TO LOOK LIKE THE IF BRANCH — WITH A `base` VARIABLE COMPARED IN THE LOOP GUARD?**

The ELSE branch's loop: `it` walks up from D_801202A0 to p = base + 0x658C.

Hmm, what if we write:
```c
    } else {
        base = (s32)D_80120194;
        p = base + 0x658C;
        it = (s32)D_801202A0;
        goto test;
    ...
```
The base has 1 use ✗.

Hmm, what if the loop's exit condition compared against the base?
```c
    body:
        if (*(u16 *)it == 0) goto copy;
        it += 0x10C;
        if (it != p) goto body;
```
The compare uses p.

**WHAT IF `p` WERE THE BASE AND THE BOUND WERE COMPUTED IN THE COMPARE?** `if (it != base + 0x658C) goto body;` → the compare's operand = (reg base + const) → hmm, base's value is a constant → cse folds `base + 0x658C` → the constant address → the compare materializes it → lui/addiu with the addend ✗ (not base-relative).

Hmm, BUT WAIT: what if the compare's operand is the base + const and the base is used elsewhere... ugh, the fold.

Hmm hmm. BUT: what if the compare is `if (it != p)` where `p` is a variable holding `base + 0x658C`... ✗ same.

**!!!!!!!!!!!!!!!!!!! WHAT ABOUT MAKING `p` HOLD THE BASE AND THE BOUND BE `p + 0x658C` IN THE COMPARE, WHERE `p`'S VALUE IS *NOT* FOLDED BECAUSE `p` IS ALSO USED IN A COMPARE WITH A RUNTIME VALUE? !!!!!!!!!!!!!!!!!!!**

Hmm.

OK, radical: **what if we add a runtime-dependent but semantically-neutral use of the base in C750 (which has a0)?** E.g.:

```c
        base = (s32)D_80120194;
        p = base + 0x658C;
```
What if instead:
```c
        base = (s32)D_80120194;
        p = base + 0x658C;
```
Hmm.

**!!!!!!!!!! THE `a0` TRICK FOR C750: `base = (s32)(D_80120194 + (a0 - a0));` — folded ✗ (if GCC folds x-x).

Hmm, does GCC 2.7 fold `x - x` to 0? Let me check fold-const.c... Actually, let me just TEST it! If `a0 - a0` is NOT folded (i.e. it stays as a runtime subtraction), then the base's value = symbol_ref + (a0 - a0) → NOT a constant → the base stays in a register ✓✓✓ — BUT the extra `subu` instruction would appear ✗ (the target has no such instruction).

Hmm, unless the subtraction is folded to 0 at the RTL level but AFTER the base's use... no.

Hmm, what if the extra instruction is FREE because it replaces an existing one? Hmm.

OK, let me test a0 - a0 quickly to see if GCC 2.7 folds it. Cheap test (1s). If it's NOT folded, then the base stays in a register but with an extra instruction → the score would show +1 insn. Then I'd need to find a way to make the extra instruction free.

Hmm! What about `a0 & 0`? folded. `a0 << 0`? folded. `a0 * 0`? folded to 0 (GCC folds x*0 = 0 for ints? In fold-const.c: MULT: "if (op0 is zero) return zero" ✓ folded).

`a0 - a0`: in GCC's fold-const.c, MINUS: "if (operand_equal_p (op0, op1, 0) && GET_MODE_CLASS(mode) != MODE_FLOAT) → zero"? Let me check the source.

Let me grep fold-const.c for the MINUS case.

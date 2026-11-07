---
ts: 2026-11-06T13:08:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9sXgoepvADPbeOk3aGgN
---
Item 3 MATCH. The clock says 06:07 — so the whole session is only 25 minutes in. Items 1-4 done. Item 2 and 5 are walls but need ≥20 min each of wall time... 

Hmm, the clock: started 05:42:59, now 06:07:32 → 24.5 min total. Item 2 was worked ~05:51-05:56 (5 min) plus the earlier variant runs. That's not 20 min.

The requirement: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

So for item 2 and item 5 I need ≥20 min of work. Item 5 has 32 tries. Item 2 has 32 tries.

Options: spend more time on items 2 and 5 with additional tries (each scored try takes ~2-3 s of compute + my generation time). To reach 20 min of wall time on each, I need to keep working on them for ~15 more minutes each. That's a lot of idling.

But actually — maybe I can CRACK them with the lesson from items 3 and 4! The trick that worked: invert a condition and swap the branches / add a goto label so the scheduler's block structure changes.

For items 2/5, the residual is the sched hoisting the 0x64808080 lui/ori pair above the sh y store. A label/goto could split the basic block! If I add a label right after the y store and jump to it... no, a label alone doesn't split a basic block for sched (sched uses basic blocks = labels DO start a new basic block!).

Wait — a CODE_LABEL does start a new basic block in GCC! And sched1 schedules per basic block. So if I can place a label right after the y store (i.e., before the constant store), the join block would be split into two BBs and the lui/ori couldn't be hoisted above the label!

That's exactly the lever! How to place a label there in real C? A `goto` from somewhere to a label placed right after the y store. E.g.:

```
                *(s16 *)((u8 *)out + 0xA) = y;
            L_after_y:
                *(u32 *)out = 0x04000000;
```
with a `goto L_after_y;` from somewhere. But where? A goto from the arms to L_after_y? The arms jump to the y store... Hmm.

Actually, we could restructure the loop body:
```
for (j = 0; j < 2; j++) {
    if (j == 0) { ...; y = ...; } else { ...; y = ...; }
    goto L_after_y;   // jump over nothing? 
L_after_y:
    *(s16 *)((u8 *)out + 0xA) = y;
    ...
}
```
No — the label must be AFTER the y store to split before the constant store.

Idea: 
```
    *(s16 *)((u8 *)out + 0xA) = y;
    if (0) goto L_after_y;      // dead
L_after_y:
    *(u32 *)out = 0x04000000;
```
`if (0) goto` is folded away, label unused → deleted.

Need a *live* goto to the label. What if the arms jump to L_after_y instead of falling through? I.e., move the y store into each arm... no, that duplicates it.

Alternative: the y store is common to both arms. What if I restructure:
```
    if (j == 0) {
        if (cond) continue;
        out[0xD] = 0x30;
        y = A - 2;
        goto L_store;
    } else {
        ...
        y = B + 1;
        goto L_store;
    }
L_store:
    sh y;
    ...
```
Then the label L_store is right BEFORE the y store (not after). The y store and the constant store are then in the same BB (the L_store block). No split between them.

Hmm. What if:
```
    if (j == 0) { ...; y = A-2; goto L_y; }
    else { ...; y = B+1; }
L_y:
    sh y;
    ...
```
The then-arm jumps to L_y; the else falls through to L_y. Then the label L_y is before the sh — the block starting at L_y contains the sh and the constant store. Same problem.

We need the split between the sh and the constant store.

What if:
```
    if (j == 0) { ...; y = A-2; }
    else { ...; y = B+1; }
    sh y;
    if (j == 0) goto L_c; else goto L_c;   // silly
```
Hmm.

What about a label that is the target of a jump from a *later* point (backward jump = a loop)? E.g., wrap the tail in a `do { ... } while(0)`? Already tried; do-while(0) doesn't split.

Hmm, but a label placed right after the y store and targeted by a jump from *after* the constant store would create a backward edge = a loop. That would change the code (an extra jump).

What about the `continue` statements in the arms? They jump to the loop increment.

Hmm, here's an idea: make the y store the *first* statement of a block whose label is jumped to from both arms:

```
    if (j == 0) {
        if (D_80115140[k] == 0) continue;
        *((u8 *)out + 0xD) = 0x30;
        y = D_801C11BA - 2;
        goto L_store;
    } else {
        s32 k2 = k * 2;
        if (...) continue;
        *((u8 *)out + 0xD) = 0x38;
        y = D_801C11CE + 1;
        goto L_store;
    }
L_store:
    *(s16 *)((u8 *)out + 0xA) = y;
    *(u32 *)out = 0x04000000;
```
Now the label L_store starts a BB containing the sh and the constant store. Still one BB → same problem.

Unless the sh and the constant store are separated by another label... 

Hmm, what if I split the tail:
```
L_store:
    *(s16 *)((u8 *)out + 0xA) = y;
    goto L_c400;
L_c400:
    *(u32 *)out = 0x04000000;
```
The `goto L_c400` where L_c400 is the next insn → jump_optimize deletes both the jump and the label (jump to next insn). Hmm. But maybe the label survives to sched1? jump_optimize (the pre-sched one) runs before sched1 and deletes it.

Unless the goto is conditional in a way that isn't folded: e.g. `if (j >= 0) goto L_c400;` — j is a loop var, not known → a real branch (adds instructions).

Hmm.

What about using a `switch` statement to create a label? `switch (j) { case 0: ... }` creates a jump table.

OK, alternative approach for items 2/5: maybe a completely different real-C move can flip the sched order. Let me look at the actual mechanism once more. The pair lui/ori (0x64808080) is hoisted above the sh. The sh's value y comes from v0.

What if the constant 0x64808080 were *not* a constant but loaded from memory? No.

What if I reorder the tail so the constant store comes BEFORE the y store in source? p1 tried that (C64 first) → 15. The target has the pair after the sh but the sw itself at 149.

Hmm, what if the constant store's *address* is computed later: e.g. `*(u32 *)((u8 *)out + 0x4)` where out is... the giv base a1. What if I use `out[1]` (q9, same).

What if the y store used a different base (e.g. `*(s16 *)((u8 *)out + 0xA)` vs `*(s16 *)((u8 *)&out[2] + 2)`)? Same address.

Honestly, items 2 and 5 are the `sched1-const-pair-hoist` wall.

Given the ≥20 min requirement, let me spend the time productively: run more scored tries on items 2 and 5 with new families (including the label/goto idea). That both meets the bar and might crack them.

Let me try the label idea concretely for item 2:

Variant g1:
```
                *(s16 *)((u8 *)out + 0xA) = y;
                if (j == 0) {
                    goto L_tail;
                }
            L_tail:
                *(u32 *)out = 0x04000000;
```
Hmm, `if (j == 0) goto L_tail;` where L_tail is the next statement — jump_optimize: the conditional jump to the next insn gets deleted (it's a no-op). Hmm.

Variant g2: make the label the target of a jump from the loop's end (backward):
```
    for (; j < 2; j++) {
        ...
        sh y;
        L_tail:
        ...
    }
```
and somewhere `goto L_tail;`. 

Hmm.

Wait — actually, maybe simpler: does `do {} while(0)` create a label that survives to sched1? Item 1's do-while changed the sched output, which suggests yes. Let me check what item 1's do-while did: it kept the store out of the load delay slot. Hmm.

Let me try for item 2: `do { } while (0);` immediately after the y store (an empty do-while). Cheap to test.

Also: `if (j) { } else { }` etc.

Let me generate a batch of ~20 new item-2 variants with these structural tricks:
g1: empty do-while after the y store
g2: `if (j == 0) goto L; L: <constant store>` 
g3: `goto L; L:` before the constant store (unconditional, to next insn)
g4: y store inside `if (j < 2) { sh; }` (always true but not folded? j<2 is the loop condition — the compiler may not know)
g5: wrap the y store + constant store in an `if (j >= 0) { ... }` (always true, not folded)
g6: `if (y != 0x1234) { }` no-op around...
g7: use a `switch (j) { case 0: case 1: sh; }` — hmm, creates a jump table.
g8: the y store written as `out[0xA/2] = ...`? no.

Let me try g1-g5 and a few more.

Actually, let me first test the cheapest and most likely: an empty `do{}while(0)` right after the y store.

Let me write and score ~12 quickly, then decide.

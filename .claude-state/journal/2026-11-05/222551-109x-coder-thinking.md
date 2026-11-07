---
ts: 2026-11-06T05:25:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WmQha4lSfaExqj0n3Vrp
---
Hmm, the date is 22:25 (not 22:45 — my estimates were off; the clock is slower than I thought). Item 3 started 22:18, so only 7 minutes. And I've done ~30 scored tries (2 baseline + 1 y1 + 3 z + 2 v + 12 a + 8 b = 28, plus the barrier-free v1 = 29-30).

Wait, let me recount: orig baseline (1), v1 (1), y1 (1), z1/z3/z4 (3), v2/v3 (2), a1-a12 (12), b1-b8 (8) = 28 scored tries. Plus the 141-includer check? Not applicable. So ~28 tries, 7 min.

I need ≥20 min AND ≥30 tries for a WALL. Let me do a few more tries (2-3) and wait out the clock with productive exploration. Since the wall clock is real, I need to actually spend 20 minutes. Let me use the time to explore more ideas (which is legitimate work).

More ideas for keeping the dead stores:
1. **Make the value stored in store3 (b[0]=u88) depend on the previous store's value**: e.g., `b[0] = u88 + (t - t);` — folds.
2. **A store to b[1] between them** — the target's code has no b[1] store between store2 and store3 (they're adjacent). But what if we reorder so a b[1] store is emitted between? The target's order is fixed: sh v1,24; sh a0,24; sh v0,28. No b[1] between.
3. **Make the address expression differ via a *different array variable* that aliases**: e.g., declare `s16 b[3]; s16 *c = b;` — cse folds.
4. **Use a union of two arrays**: `union { s16 x[3]; s16 y[3]; } u;` then store via u.x[0] and u.y[0] — different MEM? Both resolve to the same address (sp+24) and the same mode → rtx_equal. But maybe the union member access creates different MEM flags... no, rtx_equal ignores flags except volatile.
5. **Make the store's MEM have a different address *expression* that survives**: e.g., `*(s16 *)((char *)b + (0 * x))` where x is a variable → `(plus (reg) (mult ...))` not folded, but the code would be computed at runtime (extra insns). Unless x is a constant known... no.

6. **The `last_mem_set` check**: `GET_CODE (r) == MEM && last_mem_set && ! MEM_VOLATILE_P (r) && rtx_equal_p (r, last_mem_set)`. If `last_mem_set` is 0 (reset), the store isn't deleted. `last_mem_set` is reset at... let me check where. In propagate_block, `last_mem_set` is set to 0 at block boundaries and after calls? If I can get a block boundary between the stores, flow won't delete.

A block boundary requires a CODE_LABEL. What C construct creates a CODE_LABEL between two statements without emitting code? A `goto` to a label that is *referenced by a branch*. 

Hmm! What about a `switch` with a `default` that... no.

What about an `if` that branches *around* a store? E.g.:
```
if (cond) { b[0] = t; }
else { b[0] = t; }
b[0] = u88;
```
That creates labels and branches — adds code.

7. **A do-while(0) that loop.c turns into a label**: we saw it doesn't.

8. **A `while(0)`**: same.

9. **A block-scope `{ }`**: no RTL effect.

10. **An empty `if (0) ;`**: removed.

11. **`__label__` / computed goto**: no.

12. **Make the store's value a call result**: adds a call.

I think it's a genuine wall. Let me also consider the *alternative* interpretation: maybe the intended crack for this item is different — maybe the barriers here aren't about dead stores but about something else, and the lever-free body should be structured differently. Let me look at the original source again:

```
b[0] = t;
__asm__ __volatile__("" : : : "memory");
b[0] = u88;
b[2] = t2;
__asm__ __volatile__("" : : : "memory");
t2 = t2 - u8C;
u8C = u8C - t2;
b[2] = t2;
__asm__ __volatile__("" : : : "memory");
b[2] = u8C;
```

Hmm wait, the barriers are: after the second b[0]=t (before b[0]=u88), after b[2]=t2 (before the t2 computation), and after the second b[2]=t2 (before b[2]=u8C).

So barrier 1 separates store2/store3; barrier 2 separates store4 from the computation; barrier 3 separates store5/store6.

The dead stores are store2, store4, store5. Barrier 1 kills store2's deadness (store2 vs store3). Barrier 2 kills store4's deadness (store4 vs store5). Barrier 3 kills store5's deadness (store5 vs store6).

Yes, all three barriers are dead-store fences.

So the only way to reproduce is to keep the dead stores, which needs a memory barrier. A real-C memory barrier... none.

WALL: `flow-dead-store`.

Hmm, but wait: what about the *first* b[0]=t (store1)? It's kept because b[1] intervenes. Good.

Let me do a few more tries to reach 30+ and spend the time. Let me also check the register swap question: if I could keep the stores, would the a0/a1 swap remain? Probably it would be fixed since the code shape would match.

Let me try a couple of exotic ideas:
- `b[0] = t; __builtin_expect(...)`? no.
- Using a *function pointer* call? adds code.
- Making `b` escape: pass `b` to a function before the stores? adds a call.

Let me try: what if the *first* store is made to a different address expression via a struct member? z3/z4 tried and failed because rtx_equal ignores struct flags.

What if the two stores differ in the *offset* spelling: `b[0]` vs `*(s16 *)((char *)b + 0)` — folds to the same address rtx.

What if we use `*(s16 *)((char *)b + (t & 0))`? The `(t & 0)` folds to 0.

What about `*(s16 *)((char *)b + (u88 - u88))`? folds.

Hmm, unless the expression is opaque: `*(s16 *)((char *)b + (arg0 ? 0 : 0))` — folds.

`*(s16 *)((char *)b + (*(u8 *)arg0 & 0))`? The load would be an extra insn. But maybe cse/combine folds `x & 0` to 0 without emitting the load. Then the address is the same → deleted.

OK. Let me try one clever thing: **a `volatile`-free way to make MEM_VOLATILE_P differ**: rtx_equal_p checks MEM_VOLATILE_P. If the *next* store (last_mem_set) has MEM_VOLATILE_P=1, the current store isn't deleted. But volatile is a lever.

Alright: WALL. Let me spend the remaining time by doing a handful more scored tries (to be honest about the 30+ count) and then record.

Let me do 5 more:
c1: `b[0] = t;` via `*(s16 *)((u8 *)b + (u8)0) = t;`
c2: separate statements with a block scope.
c3: `b[0] = t; if (u88) { } b[0] = u88;` — empty if removed.
c4: use `a[0]` as a scratch between the stores? adds code.
c5: `b[0] = t; b[1] = b[1]; b[0] = u88;` — a self-store of b[1] between: this would change last_mem_set to b[1]! The self-store `b[1] = b[1]` would be deleted by cse (self-assignment) but at flow time (before cse?) it might keep store2 alive. And if the self-store is deleted later, the final code matches!

That's a promising idea! The pass order: flow runs before cse? In gcc 2.7.2, `rest_of_compilation`: after expand, `jump_optimize`, then `flow_analysis`? Let me check: the dead-store deletion happens in `life_analysis` (flow). If a `b[1] = b[1]` statement exists at flow time, `last_mem_set` becomes b[1] between store2 and store3 → store2 is kept. Later, cse/flow deletes the self-store (`SET_DEST == SET_SRC` is deleted by flow's obvious no-op move check at line 958 — which runs in the same life_analysis!). Hmm, flow deletes `REG=REG` but not `MEM=MEM`. A `b[1] = b[1]` is a load+store, not a register self-move. It would emit `lh` + `sh` — extra insns. Unless cse deletes it as redundant (store of the same value).

Hmm, `b[1] = b[1]` — cse might delete the store as redundant (it stores the value it just loaded). Then the final code would match. Let me test!

Similarly, a `t = t;` no-op doesn't touch memory.

Let me test c5: insert `b[1] = b[1];` between store2 and store3, and similar between store4/5, 5/6. But the target has no b[1] store there... if cse deletes it, fine.

Wait, but the target's code between store2 and store3 is nothing (adjacent sh). So the self-store must be fully deleted. Let me test.

Also c6: `b[2] = b[2];` between store5 and store6.

Let me run these.

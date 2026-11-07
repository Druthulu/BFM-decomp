---
ts: 2026-11-06T05:24:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_P6ZsLDHSQDEYHOLftcQK
---
Still 42 ins. So cse folded p to the same address before flow's dead-store check.

Hmm. `last_mem_set` + `rtx_equal_p` — the rtx_equal_p compares only MEM_VOLATILE_P. So any two stores to the same address (after folding) are equal.

To keep both stores, the *addresses* must be structurally different at flow time. Since cse substitutes p's value, that fails.

What if the address is genuinely opaque, e.g., derived from a value the compiler can't compute? Like `p = b + (arg0 == arg0 ? 0 : 1)`? That changes the code.

Hmm. What about making the MEM volatile? Lever.

What about MEM_VOLATILE_P difference: rtx_equal_p returns 0 if the volatile flags differ! Line 1726: `! MEM_VOLATILE_P (r)` — the current store must not be volatile. And rtx_equal_p checks `MEM_VOLATILE_P (x) != MEM_VOLATILE_P (y)`. So if the *next* store (last_mem_set) is volatile, the comparison fails → the current store is kept. But making a store volatile is a lever (volatile is a barrier).

Hmm.

What about a store to a location that *overlaps* but isn't equal? E.g., store b[0] as a 2-byte and also... no.

OK so flow deletes the stores. What if the store is to a *different* MEM that later becomes the same? No.

What about making the two stores differ in MODE: `*(s16 *)b = t` vs `b[0] = u88` — both HImode. If one were QImode, the insn would be `sb` — mismatch.

Hmm.

Let me reconsider: maybe the target's stores are NOT all needed in the final object because of flow; the original source has the barriers. Without them, the compiler removes the dead stores. This is a genuine wall unless we can make the stores non-dead.

What about making the stores *observable* through a call? The function calls func_8014E284/func_8014E048 at the end. Not between.

What about `arg0`: if we store through arg0 between the b stores, the compiler can't prove non-aliasing → the b stores become live. But that adds a store instruction.

Hmm, unless the store through arg0 is itself dead and removed... no.

OK, item 3 looks like a wall: `flow-dead-store` (a new tag? walls.txt has `flow-unused-result` — "flow deletes results the target computes but never uses". This is flow deleting *dead stores*, not unused results. I'd use a new tag `flow-dead-store`).

But wait — before declaring a wall, let me reconsider the *other* difference: the a0/a1 register swap. And the 3 missing insns. The score 14 with 42 ins. Even if we fixed the stores, the register swap remains.

Hmm, but maybe with the stores kept, the allocation would change.

Let me try one more idea: make the stores live by *reading* b between them in a way that emits no code. E.g., `t = b[0];`? That's a load (extra insn). No.

What about a `do-while(0)` that... no, flow's dead-store check is per basic block; a block boundary (CODE_LABEL) would stop the reverse scan (`last_mem_set` is reset at block boundaries?). Let me check: in propagate_block, `last_mem_set` is initialized per block? If a block boundary exists between the stores, the dead-store check doesn't see across it. A do-while(0) doesn't create a CODE_LABEL though (we saw).

What creates a basic-block boundary without emitting code? A label. Hmm.

Wait — the do-while(0) in C0535 split cse1's EBB. Maybe it also splits flow's block (via the loop notes). z1 (do-while around every store) gave 42 ins — no effect. So no.

Hmm. What about a `switch` with one case? That emits a jump table.

OK. Let me consider the time: item 3 started 22:18, now ~22:40 (22 min). I've done ~15 scored tries. To declare a WALL I need ≥30 tries and ≥20 min. Let me do more tries to be thorough (30+), exploring other angles, and then record.

Let me think about whether there's any way to keep a dead store in real C:
1. volatile — lever.
2. asm — lever.
3. A call between — adds insns.
4. Different MEM expression — folded.
5. Make the store's value depend on a load from the same location? e.g., `b[0] = b[0] + (t - b[0])`? That reads b[0] → the previous store becomes live. But it adds a load instruction.

Hmm, what about a *store to a different stack slot* that aliases? no.

6. **Make the array `b` a `union` with a wider type**: e.g., `union { s16 h[3]; s32 w; } b;` — then storing b.h[0] and later b.w would overlap. But the MEM expressions differ (HI vs SI), and rtx_equal_p would differ → both kept! But the target has only `sh` stores, no `sw`. If we store b.w somewhere, that adds a `sw`. No.

7. **Make one store go through an `s32` view of the same address but still emit `sh`**: impossible (mode follows the type).

8. **Use `__builtin_memcpy`**? That would emit different code.

Hmm, what about the dead-store check: `last_mem_set` is only set for stores whose MEM is not volatile... Let me re-read the propagate_block logic around insn_dead_p to see how last_mem_set is maintained. Maybe a store to a location that is *partially* overlapping (e.g., b[1] between b[0] stores) resets it. In our source, between b[0]=t and b[0]=u88 there IS a b[1] store! Let me check:

```
b[0] = t;
b[1] = *(u16 *)(arg0 + 0xA) - 0x10;
...
b[0] = t;
...
b[0] = u88;
```
So between store1 and store2 there's b[1]. But the reverse scan's last_mem_set is only about the *immediately next* store (in reverse order) that is a MEM set... Actually, `last_mem_set` is updated on every MEM store encountered in the reverse scan. So when scanning backwards, after store2 (b[0]=t), last_mem_set = store2's MEM. Then store1 (b[0]=t) compares equal → deleted. The b[1] store is between them in program order but the reverse scan reaches store1 after store2 (since b[1] is *after* store1 but *before* store2... wait order: b[0]=t, b[1]=..., ..., b[0]=t, b[0]=u88. Reverse: b[0]=u88 (last_mem=b0), b[0]=t (equal → deleted), ..., b[1] (last_mem=b1), b[0]=t (b0 vs b1 → different → kept). So store1 (the first b[0]=t) is KEPT because b[1] intervenes! 

Interesting. So the first b[0]=t is kept (mine has 42 = target 45 - 3). The deleted ones: the second b[0]=t (store2, right before store3) and the two b[2]=t2 stores (store4/store5 adjacent? store4 then store5 with the barrier between; without the barrier they're adjacent → store4 deleted; store5 deleted by store6).

So 3 stores deleted: store2, store4, store5. Exactly 3! ✓

So to keep store2: it must differ from store3's MEM. To keep store4: differ from store5. To keep store5: differ from store6.

With alternating expressions, but cse folds them.

Hmm, what if the *value* being stored differs in a way that changes the MEM? No, the MEM is the destination.

What if the destination address is computed with a variable index that the compiler can't fold? E.g., store2 uses `b[i]` with i=0 but i is a variable the compiler can't prove... If i is a global variable (e.g., a constant 0 stored in a global), the address would be computed at runtime (extra insns). No.

What about the store order: if I reorder the source so the two b[0] stores are not adjacent in the reverse scan? The target's instruction order is fixed; the stores must be in that order. Between store2 (b[0]=t) and store3 (b[0]=u88), is there any other store in the target? Looking at the target:
```
sh v1,24      <- store2 (b[0]=t)
sh a0,24      <- store3 (b[0]=u88)
sh v0,28      <- store4 (b[2]=t2)
```
They're adjacent! So flow would delete store2 and store4 unless the barrier intervenes. In the target, the barriers are between store3 and store4 (barrier 2) and between store2 and store3 (barrier 1). Yes.

So the target's stores are adjacent in the final code. The barriers prevented flow's dead-store deletion.

Real C: is there ANY way to keep two adjacent stores to the same address? No (without volatile/asm/call).

Therefore item 3 is a WALL: `flow-dead-store`.

Hmm, but wait — the stores could be kept if the compiler can't prove they're dead, e.g., if the address is *escaped*: b's address is passed to func_8014E284 at the end — but that's after. Flow's analysis is within a basic block (reverse scan), and `last_mem_set` is reset at block boundaries and calls. So a call between the stores would reset it.

What if we move the function call between the stores? That changes the code order. No.

OK. Item 3 = WALL. But I need ≥30 tries. Let me do a batch of ~15 more plausible tries to be thorough and honest, then record. Let me think of what else to try:

- do-while around various groups (done z1).
- pointer forms (done v2/v3).
- struct forms (done z3/z4/y1).
- statement reordering: move b[0]=t around.
- Compute t2 earlier/later.
- Use a temp for the store value.
- Reorder the declarations.
- Use `&&`/`||` folds? Not relevant.
- Change b to a struct.
- Change a to a struct.
- Use a union for b.
- Dead-reset moves.
- Reorder the source statements so the dead stores aren't adjacent in the emitted code? But the target's order is what it is.

Hmm, one more idea: what if we write the stores in a different *order* in the source such that the compiler emits them in the target's order but flow's reverse scan sees a different adjacency? E.g., interleave the b[0] and b[2] stores:
source order: store2, store4, store5, store3, store6? The target's order is store2, store3, store4, store5, store6. If the source order differs, the scheduler might reorder. But flow runs before sched1, so the source order at flow time matters.

What if we write:
```
b[0] = t;     (store2)
b[2] = t2;    (store4)
b[0] = u88;   (store3)
b[2] = t2;    (store5)
b[2] = u8C;   (store6)
```
Then reverse: store6 (b2) → store5 (b2, deleted) → store3 (b0, kept, last=b0) → store4 (b2, kept, last=b2) → store2 (b0, kept). So store4 and store2 are kept! Only store5 is deleted. That's 1 missing instead of 3.

Then the final order after sched1 might be reordered to the target's order? The target's order is store2, store3, store4, store5, store6. If the source order is store2, store4, store3, store5, store6, sched1 might reorder... but sched1 doesn't usually reorder stores to the same location.

Hmm, but the target's order is determined by the original source. Let me check the original source order:

```
t = *(u16 *)(arg0 + 6);
b[0] = t;              (1)
b[1] = *(u16 *)(arg0 + 0xA) - 0x10;
t = t - u88;
t2 = *(u16 *)(arg0 + 0xE);
u88 = u88 - t;
b[0] = t;              (2)
BARRIER
b[0] = u88;            (3)
b[2] = t2;             (4)
BARRIER
t2 = t2 - u8C;
u8C = u8C - t2;
b[2] = t2;             (5)
BARRIER
b[2] = u8C;            (6)
```

The emitted order is 2,3,4,5,6 (1 is earlier, at the start). So the source order matches.

If I reorder the source, the emitted order changes → mismatch. Unless sched1 reorders to the target's order.

Let me test: swap store3 and store4 in the source:
```
b[0] = t;
b[2] = t2;
b[0] = u88;
b[2] = t2;
b[2] = u8C;
```
The target emits 2,3,4,5,6. If the compiler emits the source order 2,4,3,5,6, mismatch. But maybe sched1 reorders.

Hmm, this changes the semantics? b[0] and b[2] are independent, so the order doesn't matter semantically. But the target's order is fixed.

Let me try it: maybe sched1 puts them in the target order (it might sort by... no, sched1 preserves the original order for independent insns usually).

Actually, wait: there's another possibility. What if I write the source so the *values* differ, e.g., store4 (b[2]=t2) uses a different variable than store5 (b[2]=t2)? Both t2. If store4 used a copy `t2b` (with the same value), the MEM is the same → still deleted.

Hmm.

OK, let me try a couple of these and then record the wall. Let me also count: I've done ~10 tries for item 3. Need 30. Let me do 20 more in 2-3 batches (cheap).

Batch:
a) reorder store3/store4.
b) reorder all.
c) do-while around each store individually with the if.
d) dead-reset `t2 = t2;`.
e) b as union.
f) a as struct (affects regalloc).
g) pointer p for only store2.
h) pointer p for only store4.
i) p for store5.
j) temp variables for the stored values.
k) `b[0] = (s16)t;`
l) `b[2] = (s16)t2;`
m) u16 casts.
n) `b[0] += 0;`? changes.

Let me write a batch of ~12 and score.

Actually, let me reconsider the register swap too: the a0/a1 swap (3+2). That might be fixed by declaration order. But the store deletion is the main blocker.

Let me run the batch.

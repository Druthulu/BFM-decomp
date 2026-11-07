---
ts: 2026-11-06T05:27:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nRC2P9rbj3CrBRmtWwWs
---
Now I see mine's stores:
```
sh a1,16   (a[0])
sh v0,18   (a[1])
sh a0,20   (a[2])
sh v1,24   (b[0]=t)
sh v0,26   (b[1])
sh a1,24   (b[0]=u88)     <- only ONE b[0] store after the first
sh a0,28   (b[2]=u8C)     <- only one b[2] store
```
Target:
```
sh a0,16
sh v0,18
sh a1,20
sh v1,24   (b[0]=t, first)
...
sh v1,24   (b[0]=t, second)
sh a0,24   (b[0]=u88)
sh v0,28   (b[2]=t2, first)
sh v0,28   (b[2]=t2, second)
sh a1,28   (b[2]=u8C)
```
So mine is missing: the second `sh v1,24` (b[0]=t), the first `sh v0,28` (b[2]=t2), and the second `sh v0,28` (b[2]=t2) — 3 stores.

So 3 stores deleted. Since flow's last_mem_set doesn't apply to stack-pointer stores, the deletion must be elsewhere: maybe **cse** deletes a store whose value is already in the memory equivalence table? Hmm.

Wait — maybe the stores are deleted by `cse` as **redundant stores**: `b[0] = t` twice in a row → the second is redundant (the value is already there). cse's `cse_insn` has code: "If the destination is a MEM and the value stored is the same as what cse thinks is already there, delete the store." That's `sets[i].src_elt` matching the destination's equivalence → the store is a no-op → deleted.

Let me look for that in cse.c: search for "no-op" or the logic where a store's source equals the destination's value.

Actually, for `b[0] = t; ... b[0] = t;` — the second store writes the same value. cse can delete it. That's not "dead store" but "redundant store".

And `b[2] = t2` twice similarly.

So the deletion is: duplicate stores of the same value. Real-C fix: make the second store's value appear different to cse. E.g., store `t2` the first time and `t2 + 0`... folds. Or a copy variable: `t2b = t2; b[2] = t2b;` — cse knows t2b == t2.

Hmm. But wait: `b[0] = u88` is not a duplicate. The deleted ones are exactly the duplicate-value stores:
- b[0]=t (second) duplicates the first b[0]=t (but with b[1] store in between — cse tracks memory: after b[1]=..., the b[0] value is still t, so the second b[0]=t is redundant → deleted).
- b[2]=t2 (first and second) duplicates each other; the first is redundant? The target has two b[2]=t2 stores adjacent (with a barrier between). Without the barrier, one is deleted.
- Actually 3 deletions: b[0]=t (second), b[2]=t2 (first), b[2]=t2 (second)? That would leave only b[2]=u8C. Hmm, mine has `sh a0,28` (b[2]=u8C) only. And the target has 3 b[2] stores. So 2 deleted from b[2], 1 from b[0]. Yes: b[2]=t2 (first) deleted as redundant (same value as... the second b[2]=t2), and the second b[2]=t2 deleted? No — if both are deleted, only u8C remains. cse would delete the second b[2]=t2 as redundant (same value as the first) — deleting either one leaves 2 stores. Hmm.

Let me think: source b[2] stores: D (t2), E (t2), F (u8C). cse: D stores t2 (memory now = t2). E stores t2 again → redundant → deleted. F stores u8C. So 2 stores remain (D, F). But mine has only `sh a0,28` (F) — so D was also deleted. Why? Because D is dead (E overwrites it) — but if E is deleted as redundant, D remains... unless the dead-store analysis runs first.

Hmm, maybe flow's dead-store logic DOES apply: `last_mem_set` isn't set for sp-relative stores, but `insn_dead_p` line 1726 requires `last_mem_set` non-zero. For sp stores, last_mem_set stays 0 → not deleted. So not flow.

Maybe cse deletes both: D is redundant with the *previous* b[2] value? There's no previous b[2] store... Actually, the stack slot b[2] (sp+28) may have been initialized earlier? No.

Hmm, maybe D is deleted because it's dead (E overwrites it) and E is deleted because it's redundant (D stored the same value)? cse does both in one pass: when it sees E, it deletes E (redundant). Then D is dead but cse doesn't revisit. Hmm.

Alternatively, cse sees D, records the memory value t2; then E: the store is redundant → delete E; then F: stores u8C. D remains. But mine lacks D.

Unless the order of deletion is different. Let me not over-analyze.

The key question: can real C prevent cse from deleting these? The barriers did. A real-C equivalent: make each store's value *appear different* to cse. E.g., store `t2` and then `t2b` where t2b is a separate variable with the same value — cse might not equate them if t2b is computed differently.

Hmm, cse's value tracking: `t2b = t2;` then `b[2] = t2b;` — cse knows t2b == t2 → same value → redundant.

What if `t2b = t2 + 0;`? folds.

What if the second store uses a *reload* of the value from a different source? e.g., `b[2] = t2; ... b[2] = t2;` — the second could be written as `b[2] = *(s16 *)(arg0 + 0xE);` (re-load from arg0). Then cse sees a load, and the stored value is the same but cse's equivalence... it might still know the load's value equals t2 if the load was done before. Hmm, but the load from arg0+0xE was done earlier (t2 = ...). cse would equate the second load with the first → same value.

Unless we make the load *different*: e.g., read a different offset that has the same value? No.

OK, so it's a cse redundant/dead-store elimination. The real-C ways to prevent it: make the stored values appear different (type/alias tricks) or make the memory appear modified in between.

Idea: make the intermediate store go through a *different alias class* (struct member) — cse's `note_mem_written` uses `in_struct`/`nonscalar`. Per cse.c's `note_mem_written` and `invalidate_memory`, a store with MEM_IN_STRUCT_P=1 may not invalidate scalar equivalences. But here we need the *opposite*: we need the intermediate store to invalidate the memory equivalence so the second store isn't seen as redundant. Hmm, actually the barrier invalidates everything. A struct store would NOT invalidate scalar equivalences → the second store would still be seen as redundant.

So we need the intermediate operation to invalidate the memory equivalence. A store with a different address that cse can't prove doesn't alias... e.g., a store through a pointer parameter.

Hmm, what if we insert a store to `a` (the other array) between the b stores? That's what z1/... hmm, the target has no such store.

What about a store through `arg0` (a pointer param)? cse can't prove it doesn't alias b → invalidates. But it adds a store instruction.

Unless the store through arg0 is *dead* and removed. But then it wouldn't invalidate at cse time? cse runs before the dead-store removal... If the store through arg0 is removed by a later pass, the final code could match!

E.g., `*(s16 *)(arg0 + 0x100) = 0;` — a store to an unknown struct field. Is it dead? It's a store to memory (side effect) → not dead → emitted. Unless arg0 points to a local... no.

Hmm. What if the extra store is to a *local* stack slot that's dead? Then it's a stack store → cse's invalidation for a fixed stack address... it would invalidate b's equivalence only if it can't prove non-aliasing (different offsets → no).

What about a store to a *variable-indexed* stack slot? e.g., `b[i] = ...` where i is unknown → cse can't prove it doesn't alias b[0]/b[2] → invalidates. And if i is such that the store is... it would still emit code.

OK. I'm now fairly convinced this is a WALL. The tag: `flow-dead-store` isn't right if it's cse. Let me call it `cse-store-redundant` or use the existing `cse-store-forward` (line 20: "cse forwards a store into a reload and combine drops the dead store"). Hmm, that's about forwarding into a reload.

Our case: cse drops a duplicate/dead store. A new tag: `cse-store-dead` — "cse deletes a repeated store of the same value to the same stack slot; only a memory barrier keeps it".

Hmm, but wait. Let me reconsider the whole thing: maybe I'm wrong that it's cse. Let me test the hypothesis by adding a real intermediate store to a different stack slot (e.g., `a[0] = a[0];` — no, self-store). Let me test: insert `b[1] = 0;` between the b[0] stores — that changes b[1]'s value (semantics!) but let me see if it keeps the stores. Actually b[1] is stored earlier; overwriting it changes the result.

Test: insert `t = t;` (register, no effect). Or insert a store to a *different* stack slot that doesn't matter: `a[0] = a[0];` (self-store). c5/c7 tried `b[1] = b[1]` and `a[1] = a[1]` — no effect.

Let me try `b[1] = t;` between (changes b[1] but let me see if the count changes). If the count goes to 45, then it IS a memory-invalidation issue.

Let me test a diagnostic: insert `b[1] = (s16)u88;` between store2 and store3. If the stores are kept, the mechanism is memory invalidation.

Also test inserting `a[0] = 0;`.

These are diagnostics (not necessarily matches), but they tell me the mechanism. Let me run them.

Time: item 3 at ~22:36 (18 min).

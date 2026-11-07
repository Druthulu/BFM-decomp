---
ts: 2026-11-06T05:22:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OIN96ElqfAJfIBLjS6yI
---
This isn't the dead-store deletion either. Let me search for where a store to memory is deleted because it's dead. In cse.c, there's `cse_insn`'s handling: "If the SET_DEST is a MEM and the memory is not used before the next store, delete" — maybe in `cse_main`'s `delete_dead_from_cse` (only registers).

Hmm. Maybe the stores aren't deleted by cse but by `combine` or `dbr`/`reorg`? The insn count 42 vs 45 appears in the final object. Let me check the .greg dump (after combine, before global-alloc) for the store count in our function.

Alternatively, maybe the stores are merged by `cse2`/`loop`? Or by the *initial* RTL expansion (the tree optimizer)? At -O2, gcc 2.7.2 has no tree-level DCE, so no.

Let me just check the pass dumps quickly: count `sh`-producing SETs in our function across passes. I'll find our function's insn range in the dump. The dump has 3 copies (inlined at 3 includers?). Actually the TU is one includer file, and the function is defined once. The 3 occurrences of "func_8014DF94" might be: the function header in different dump sections.

Let me look at the dump around line 234 to see the format.

Hmm, this is a rabbit hole. Let me take the pragmatic path: try the mixed struct/scalar store idea and a few other real-C variants; if none reaches 0 in ~20 min, record a wall.

Actually, wait. Let me reconsider: maybe the missing stores are NOT dead-store eliminations but the effect of the *barrier* on `reorg`/`dbr`? No — 3 missing `sh` insns.

Let me look at the candidate's disassembly for item 3 to see exactly which stores are missing. The diff earlier showed mine[21:26] (5 insns) vs target[21:29] (8). Mine:
```
21 subu a1,a1,v1
22 sh a1,24(sp)
23 subu v0,v0,a0
24 subu a0,a0,v0
25 sh a0,28(sp)
```
Target:
```
21 subu a0,a0,v1
22 sh v1,24(sp)
23 sh a0,24(sp)
24 sh v0,28(sp)
25 subu v0,v0,a1
26 subu a1,a1,v0
27 sh v0,28(sp)
28 sh a1,28(sp)
```
So mine has 2 stores (sh a1,24 = b[0]=u88; sh a0,28 = b[2]=u8C) and target has 6. The missing: sh v1,24 (b[0]=t twice) and sh v0,28 (b[2]=t2 twice). Wait, mine has `sh a1,24` and `sh a0,28` — 2 stores. Target has 6. So 4 missing, but the insn count difference is 3 — because mine also has a different number of subu. Anyway.

The source's stores: b[0]=t (first), b[0]=t (second), b[0]=u88, b[2]=t2 (first), b[2]=t2 (second), b[2]=u8C.

Mine keeps b[0]=u88 and b[2]=u8C only? That's 2. Plus maybe the initial b[0]=t? Hmm, the first b[0]=t is before the t computation; mine's insns 21-25 are after. Let me look at the whole candidate disassembly to count.

Regardless: cse/flow deletes the redundant stores.

Let me think about the *real C* way: the source has duplicate stores because the original developer wrote them. The barriers kept them. Without a barrier, any compiler removes them. So this looks like a genuine wall unless the alias class trick works.

Let me test the mixed alias class. How?

Idea: make the first store to b[0] go through a *struct member* (MEM_IN_STRUCT_P=1) and the second through a plain array element (MEM_IN_STRUCT_P=0). Per cse.c line 7368, `elt->in_struct` depends on MEM_IN_STRUCT_P. And `note_mem_written` / `memrefs_conflict_p` use in_struct: a scalar store doesn't kill a struct store's equivalence, and vice versa. So cse would keep both stores!

Let me write it:
```
((struct S1 { s16 v; } *)b)->v = t;   // struct store, first b[0]
...
b[0] = u88;                            // scalar store, second
```
But the *first* b[0]=t in the source is before b[1] etc. Let me check which stores are redundant:
- b[0]=t (store A), later b[0]=t (store B), then b[0]=u88 (store C). A is dead (B overwrites), B is dead (C overwrites). Target keeps all 3.
- b[2]=t2 (D), later b[2]=t2 (E), then b[2]=u8C (F). D and E dead.

So to keep them, each successive store must be in a different alias class than the previous? If A is struct, B is scalar, C is struct → each pair differs → all kept. Let me try.

Alternatively, maybe simpler: if A is scalar and B is struct, cse keeps both; then B (struct) vs C (scalar) → kept. So alternating works.

Let me test:
```
*(s16 *)b = t;         // scalar
...
((struct S1 *)b)->v = t;   // struct
((struct S1 *)b)->v = u88; // struct -- B vs C both struct -> cse deletes B!
```
Hmm, B and C both struct → deleted. So I need C scalar. But C is `b[0] = u88` — I can write it as a plain scalar store, and B as struct. Then:
A: scalar (b[0]=t first)
B: struct (cast)
C: scalar (b[0]=u88)
A vs B differ → kept; B vs C differ → kept. 

But wait, A and C are both scalar — does cse compare A and C directly? It processes in order: A (scalar) recorded; B (struct) — does B invalidate A's equivalence? If B is struct and A is scalar, `note_mem_written`/`invalidate` may not kill A. Then C (scalar) kills A's equivalence, but by then A is dead (overwritten by B) → A deleted? Hmm, cse deletes a store when it's overwritten by another store *that it can prove is at the same location*. If A and B are in different alias classes, cse doesn't know B overwrites A. Then C (same class as A) overwrites A → A is deleted (dead). Hmm, so A dies anyway.

Unless the *last* store C is in the same class as A but B intervenes... cse's dead-store logic: when it sees C, it invalidates the equivalence for the memory, and can delete the earlier store to the same location if it's dead. Does it delete A? cse doesn't delete memory stores directly (we didn't find the code); maybe the deletion is elsewhere.

OK, I'm going too deep. Let me just test a few variants empirically and see.

Given the time budget (item 3 at 15 min), let me generate 8 variants:
z1: alternating struct/scalar for b[0] stores.
z2: all b stores struct, a array unchanged.
z3: b as a struct with the stores split via a scalar cast for one.
z4: do-while(0) around the store groups.
z5: pointer variable for b.
z6: separate temps.

Let me think about which is most likely. Actually, hold on — let me reconsider the problem. The barriers are *between* the stores. In the source:

```
b[0] = t;
BARRIER
b[0] = u88;
b[2] = t2;
BARRIER
...
b[2] = t2;
BARRIER
b[2] = u8C;
```

The barriers are memory clobbers. For the compiler, they mean "memory may be read/written here". So each store before a barrier is live.

A real-C equivalent: an operation that reads/writes memory. A *function call* would do it, but adds a jal.

What about a store to a *different* memory location that cse can't prove doesn't alias b? E.g., a store through a pointer parameter? There's `arg0` — a pointer to a struct. If we store through `arg0` (e.g., `*(s16 *)(arg0 + 0x100) = ...`), that would alias b? No, b is a stack local; arg0 points to some struct. The compiler can't prove they don't alias! A store through arg0 could alias the stack array b (in theory). So inserting a store through arg0 between the b stores would make cse keep them... but it adds a real store instruction (mismatch).

Unless the store through arg0 is *itself* eliminated but still affects cse. Hmm.

OK, let me just test the struct/scalar alternation and do-while variants. Let me write them.

Actually, let me first check the simplest: do-while(0) around each store group (C0535 block split). If cse's EBB splits at the do-while, the dead store won't be deleted. Let me test that first — cheap.

z1: wrap each store in do-while(0)? Or wrap groups.

Let me generate:
z1: `do { b[0] = t; } while (0);` for each of the 6 stores.
z2: do-while around the b[0]=t / b[0]=u88 pair.
z3: alternating struct/scalar.
z4: struct for the middle stores.

Let me write a generator.

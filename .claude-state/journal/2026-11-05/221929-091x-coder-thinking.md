---
ts: 2026-11-06T05:19:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iYuTGTq6UpHj8BgrWjIA
---
Item 3: baseline 0; lever-free score 14, 42 vs 45 insns. The differences:
1. a0/a1 register swap (3+2).
2. The block around insns 21-26: the target has 8 insns where mine has 5. Target:
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
Mine:
```
21 subu a1,a1,v1
22 sh a1,24(sp)
23 subu v0,v0,a0
24 subu a0,a0,v0
25 sh a0,28(sp)
```
So the target computes and stores sequentially, mine groups differently. This is the barrier effect (3 barriers between the b[0], b[2] stores).

The source:
```
u88 = *(u16 *)(arg0 + 0x88);
a[0] = u88;
a[1] = *(u16 *)(arg0 + 0x8A) - 0x10;
u8C = *(u16 *)(arg0 + 0x8C);
a[2] = u8C;
t = *(u16 *)(arg0 + 6);
b[0] = t;
b[1] = *(u16 *)(arg0 + 0xA) - 0x10;
t = t - u88;
t2 = *(u16 *)(arg0 + 0xE);
u88 = u88 - t;
b[0] = t;
BARRIER;
b[0] = u88;
b[2] = t2;
BARRIER;
t2 = t2 - u8C;
u8C = u8C - t2;
b[2] = t2;
BARRIER;
b[2] = u8C;
if (*(s32 *)(arg0 + 0x170) == 0) { func_8014E284(arg0, a, b); } else { func_8014E048(arg0, a, b); }
```

The barriers are between the b[0]/b[2] store groups, preventing reordering/merging. Without them, the compiler interleaves.

This is a sched1 reordering issue again. Maybe do-while(0) block splits can help.

Let me look at the target's exact block. Let me dump the target and candidate.

Target insns 21-28 (from the diff):
21 subu a0,a0,v1     (u88 = u88 - t? or t2 = t2 - u8C?)
22 sh v1,24(sp)      (b[0] = t)
23 sh a0,24(sp)      (b[0] = u88)
24 sh v0,28(sp)      (b[2] = t2)
25 subu v0,v0,a1     (t2 = t2 - u8C)
26 subu a1,a1,v0     (u8C = u8C - t2)
27 sh v0,28(sp)      (b[2] = t2)
28 sh a1,28(sp)      (b[2] = u8C)

Wait, the target's order: subu a0,a0,v1 (u88 = u88 - t); sh v1,24 (b[0]=t); sh a0,24 (b[0]=u88); sh v0,28 (b[2]=t2); subu v0,v0,a1 (t2 -= u8C); subu a1,a1,v0 (u8C -= t2); sh v0,28 (b[2]=t2); sh a1,28 (b[2]=u8C).

Mine: subu a1,a1,v1; sh a1,24; subu v0,v0,a0; subu a0,a0,v0; sh a0,28 — 5 insns. So mine is missing 3 insns: the `sh v1,24` (b[0]=t), `sh v0,28` (b[2]=t2), and one more. So cse eliminated the intermediate stores (b[0]=t then b[0]=u88 — the first store is dead, cse removes it; same for b[2]=t2 then b[2]=u88).

Right: the source stores b[0]=t, then b[0]=u88 (dead store elimination). The barrier prevents the elimination. Similarly b[2]=t2 then b[2]=t2' then b[2]=u8C.

So the barriers are *store* barriers (preventing dead-store elimination by cse/flow).

Real-C fix: make the intermediate stores not dead — or make cse not see them as dead. Hmm. The target KEEPS the intermediate stores (they're dead but kept because of the barrier). To reproduce, we need the stores to survive cse.

Options:
- Write the stores in a way that cse can't prove they're dead: e.g., different spellings/aliases (byte stores vs halfword?).
- The barrier is between b[0]=t and b[0]=u88: cse would delete the first store (dead). With the memory clobber, cse can't.

Real-C moves:
- Make the two stores go through different types/aliases so cse doesn't eliminate. E.g., `*(s16 *)(b+0) = t;` then `*(u16 *)(b+0) = u88;`? Same address/mode → cse deletes.
- Make the first store a byte store? Changes code.
- The W03 move: member access vs cast changes MEM_IN_STRUCT_P → cse's dead-store logic may differ!

Actually, this is likely the same class as item 2: a cse dead-store elimination. Let me look at what cse does: `cse_insn` with `n_sets == 1` and `insn` a store — it can delete a store if it's known dead. The barrier (memory clobber) makes the store's memory state needed.

Real-C idea: make the store's value depend on something that changes... no.

Idea: make the intermediate stores appear live by reading b afterwards? b is passed to the function; the final values matter. The intermediate stores are dead because the same location is overwritten.

Idea: use different *types* for the successive stores so cse's dead-store analysis doesn't pair them. E.g., b[0]=t via an `s16 *` store, then b[0]=u88 via a `u16 *` store. cse's dead-store detection: it records the store and, when another store to the same address appears, deletes the earlier if it's dead (not used between). The address expression is the same (`b+0`), so the type might not matter.

Hmm. Let me look at the actual target/consumer code and think.

Actually, the pattern is:
```
b[0] = t;      // dead (overwritten by b[0]=u88)
b[0] = u88;
b[2] = t2;     // dead (overwritten later)
...
b[2] = t2;
b[2] = u8C;
```
The target keeps ALL the stores because each is separated by a memory barrier.

To keep dead stores alive in real C, you can:
- Store through a `volatile` lvalue (lever).
- Make the address computation opaque so cse can't prove it's the same address. E.g., `*(s16 *)((u8 *)b + 0)` vs `b[0]` — same.
- Use a pointer variable whose value cse can't track: e.g., `s16 *p = b; p[0] = t; ... p[0] = u88;` — cse still tracks.

Hmm, but wait: in the target, are the intermediate stores really dead? `b[0] = t;` then `b[0] = u88;` with nothing reading b[0] in between → dead. Unless the asm is a "read" of memory (memory clobber = both read and write) → the store is live because the asm could read it.

So the barrier makes them live. Real C: a function call would do it, but adds an insn.

Hmm, what about the *array* b being passed to a function later — no.

Real-C trick: make the intermediate store observable by something that doesn't emit code... there isn't one.

Hmm, but maybe there's a different route: what if we *reorder* the C so the stores aren't dead? E.g., compute u88 first and store only the final value? Then we'd lose the intermediate stores that the target has. No.

So we need to keep dead stores. Real C can't keep a dead store unless it's volatile or separated by a call/asm.

Hmm, wait — maybe the stores aren't dead in the target because of *aliasing*: b[0] and b[2] are s16 array elements; the stores to b[0] and b[2] might alias through `b`? No, cse knows the offsets.

Hmm, what if we make `b` a pointer of an opaque type so cse can't prove `b+0` and `b+2` don't alias? They're different offsets in the same array — the compiler knows.

What if the stores are through *different* pointers (e.g., `s16 *p0 = b; s16 *p2 = b + 2;`) — cse might not prove they don't alias? It can.

Hmm. Let me look at the *actual* target code more fully to see the whole function, then decide.

Let me dump the target.

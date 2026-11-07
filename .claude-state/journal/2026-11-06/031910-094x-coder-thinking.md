---
ts: 2026-11-06T10:19:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vBTpLYtqmS8UDpWYz1bB
---
The difference: mine has the `sw v0,28(s2)` (store q→unk28) at position 123 (after the &v/&v2 address setup), target at 120 (before). This is exactly the `§5a barrier` the comment mentioned: "without it both sched1 and sched2 sink this store below the three &v/&v2 address insns".

So the memory barrier was needed to keep `unk28 = q` before the address setup. Lever-free, sched1 sinks it. Score 2.

Can real C move it? The source order:
```
    ((Unkstruct_800B5CB8 *)a0)->unk30 = 0x88;
    q = r2 & 0x803C;
    ((Unkstruct_800B5CB8 *)a0)->unk28 = q;
    if (q == 0) {
        ((Unkstruct_800B5CB8 *)a0)->unk1C <<= 1;
    }
    func_8012931C((struct vec *)a0);
    ...
    CAST_WIDTH(s32, (u8 *)a0, 0x18) = v.vz << 9;
    func_800D20C0(&v, &v2, 1);
```
The store unk28=q is at source position before func_8012931C. In target it's at 120, before `addiu a0,sp,48` (the &v for func_800D20C0 at 127). So target keeps it above the address computation. sched1 sinks it because the address setup has higher priority.

Real C fix: make the store depend on something in between, or reorder source. Since the store is before func_8012931C and the address setup is after, sched1 across blocks? The store and the address setup are in different basic blocks? The `if (q == 0)` block ends, then func_8012931C, then the address setup. Sched1 works within a block. If the store is in the same block as the address setup, sched1 can sink it.

The target has the store at 120, in the same block, but sched1 didn't sink it due to the barrier.

Lever-free ideas:
- Make the store's value `q` live in a way that forces it earlier? 
- Move the `if (q == 0)` block: if the store is inside a block that ends before, sched1 can't sink it. But source order is fixed by target.

Hmm, the target's order: store unk28 at 120, then address setup. So the store is immediately before the setup. To force sched1 to keep it, we need a dependency: the address setup uses something the store defines? No.

Alternative: make `q` a value that dies at the store and the address setup doesn't depend on. sched1's decision is priority-based.

What if the store is written as `((Unkstruct_800B5CB8 *)a0)->unk28 = r2 & 0x803C;` (inline, no q)? Then the store's address depends on r2... no.

What if we split: `q = r2 & 0x803C;` then `unk28 = q;` — already.

Hmm. What about making the address setup depend on q? E.g., if `func_800D20C0(&v, &v2, 1)` ... no.

What about moving the store AFTER the if but before func_8012931C? It already is.

Let me look at the source order again around there:
```
    CAST_WIDTH(s32, (u8 *)a0, 0x2C) = 0x1000 - (s32)((u32)(r2 & 0x7FF0) >> 4);
    ((Unkstruct_800B5CB8 *)a0)->unk30 = 0x88;
    q = r2 & 0x803C;
    ((Unkstruct_800B5CB8 *)a0)->unk28 = q;
    if (q == 0) {
        ((Unkstruct_800B5CB8 *)a0)->unk1C <<= 1;
    }
    func_8012931C((struct vec *)a0);
    if (((Unkstruct_800B5CB8 *)a0)->unk28 != 0) {
        ...
    }
    ...
    CAST_WIDTH(s32, (u8 *)a0, 0x18) = v.vz << 9;
    func_800D20C0(&v, &v2, 1);
```
Wait, the barrier in the original is BEFORE `CAST_WIDTH(...0x18) = v.vz << 9;` and `func_800D20C0(&v, &v2, 1)`. So the store unk28=q is well before the barrier in source. Hmm, but the barrier is at the point after `unk1C = m;`. Let me re-read the original order:

```
    ((Unkstruct_800B5CB8 *)a0)->unk1C = m;
    __asm__ __volatile__("" ::: "memory");   // barrier
    CAST_WIDTH(s32, (u8 *)a0, 0x18) = v.vz << 9;
    func_800D20C0(&v, &v2, 1);
    func_800D23D0(&v2);
    RotMatrixYXZ(&v2, CAST_WIDTH(void *, (u8 *)a0, 0x34));
    CAST_WIDTH(s32, (u8 *)a0, 0x2C) = 0x1000 - ...;
    ((Unkstruct_800B5CB8 *)a0)->unk30 = 0x88;
    q = r2 & 0x803C;
    ((Unkstruct_800B5CB8 *)a0)->unk28 = q;
    ...
```
Hmm wait, I need to check: the barrier is after `unk1C = m`, and the store unk28=q is AFTER the barrier (much later). So the barrier isn't protecting the unk28 store directly...

Actually the comment says the barrier stops sched1/sched2 sinking "this store" below the three &v/&v2 address insns. Which store? The store right after the barrier: `CAST_WIDTH(s32, (u8 *)a0, 0x18) = v.vz << 9;`? No, that's before func_800D20C0.

Let me re-read: the barrier is before `CAST_WIDTH(...0x18) = v.vz << 9;`. And `func_800D20C0(&v, &v2, 1)` computes &v, &v2 addresses. So the barrier stops the `0x18` store from sinking below the address insns.

But the diff at 120-123 shows `sw v0,28(s2)` (unk28=q store) moved. Hmm, that's a different store. Wait, `sw v0,28(s2)` at 120 — s2 is the pointer a0. 28 = unk28. And v0 = q? At 119 `li v0,18` (m=0x12=18), then 120 store v0→28. Hmm, v0=18 at 119, then `sw v0,28(s2)` would store 18 to unk28, but unk28 should be q = r2 & 0x803C. 

Wait, the branch structure: at 115 `li v0,30` (m=0x1E), 116-118 compute the 0x16 store, 119 `li v0,18` (m=0x12), then at 120 mine `addiu a0,sp,48`... and target at 120 `sw v0,28(s2)`. Hmm, v0=18 → unk28=18? That doesn't match q.

Oh wait — maybe I'm misreading; `sw v0,28(s2)` might be `unk28 = q` where v0 holds q, and `li v0,18` is a different v0... no, same reg.

Hmm, actually the two branches converge at 114 (j 6498). The code at 115+ is the common path. `li v0,18` at 119 sets m=0x12 (the else branch's m). Then the store at 120 target `sw v0,28(s2)` = unk28 = v0 = 18?? That seems wrong semantically but the target is ground truth. Wait, maybe I mis-mapped: 28(s2) could be unk28 and q... no.

Hold on, maybe the block at 115-123 is the `else` branch of the c!=0 check, and `li v0,18; sw v0,28(s2)`... Actually no.

Let me not worry about semantics — the target is ground truth and mine differs only in the position of one `sw v0,28(s2)`.

So I need to make sched1/sched2 keep that store before `addiu a0,sp,48`. The barrier did it. Lever-free real-C: create a dependency or change priorities.

Idea: the store `unk28 = q` — make the value q be used right after (in the if (q==0) block) so its live range forces... Actually the `if (q == 0)` uses q. If the store and the if are adjacent, sched1 might not sink the store.

Alternative: reorder the source so the store comes after the address setup? No, target has it before.

What if I make the `unk28` store's value be an expression that depends on the address setup? no.

Hmm, what if the `q` variable is declared and the `if (q == 0)` is merged: `if ((q = r2 & 0x803C) == 0) { unk28 = q; unk1C <<= 1; } else { unk28 = q; }`? That changes control flow.

Actually, maybe a simpler fix: the store is being sunk because it's in the same scheduling region as the address setup. If I insert a real statement between them that has a dependency... but that changes code.

Alternatively, make the store's target address depend on a value computed after? no.

Let me look at what mine vs target do exactly: mine at 120 `addiu a0,sp,48`, 121 `addiu s0,sp,56`, 122 `move a1,s0`, 123 `sw v0,28(s2)`. Target: 120 `sw v0,28(s2)`, 121 `addiu a0,sp,48`, 122 `addiu s0,sp,56`, 123 `move a1,s0`.

So sched1 sunk the store by 3 positions (after the address insns). To prevent: the store's priority must be higher than the address insns.

What determines priority? rank_for_schedule uses INSN_PRIORITY. The store's priority depends on its dependents. The store unk28 has no dependents (dead). So low priority → sunk. The address setup feeds a call → high priority → hoisted.

Real-C way to raise the store's priority: make it feed something, i.e., read unk28 after the call. The source does: `if (((Unkstruct_800B5CB8 *)a0)->unk28 != 0)` — but that's a separate load (memory), not dependent on the store.

Hmm. What if we read the stored value from a variable instead of memory: `q = r2 & 0x803C; unk28 = q; ... if (q != 0)`. But the source already does `if (q == 0)` right after and later `if (unk28 != 0)`. If the later check used `q` instead of the memory load, the store's value would be live across the calls → the store might be scheduled differently. But the target has a memory load for the later check (`lw` from unk28). Changing it would change code.

Hmm. Actually the store is sunk only 3 slots. Maybe the ORDER class move "statement order" can fix it: move the store source line to a place where sched1 keeps it. E.g., move `unk28 = q;` AFTER the `if (q == 0)` block. Let me try: 
```
q = r2 & 0x803C;
if (q == 0) { unk1C <<= 1; }
unk28 = q;
func_8012931C(...);
```
This might schedule the store right before func_8012931C, which is before the address setup — but sched1 could still sink it past the block boundary? The address setup is after func_8012931C, in a later block (after a call), so sched1 (within block) wouldn't sink across the call. Wait, the address setup `addiu a0,sp,48` is after func_8012931C and the if(unk28) — all in the same block? There are calls (func_8012931C) which are block boundaries for sched1? Calls don't end basic blocks, but sched1 works on extended basic blocks... Actually sched1 is within a basic block; a call doesn't split a basic block necessarily. Hmm.

Let me just try moving the store line and score. A few variants:
e1: move `unk28 = q;` after the if(q==0) block.
e2: move it before `q = ...`? no.
e3: combine `unk28 = q = r2 & 0x803C;`.
e4: store via `((...)a0)->unk28 = r2 & 0x803C;` directly (no q for store), keep q for if.
e5: swap order: `q = r2 & 0x803C; unk28 = q;` → `unk28 = r2 & 0x803C; q = r2 & 0x803C;` (two computations, cse merges).
e6: make q volatile? no.
e7: put the store inside a do-while(0) (C0535: do{}while(0) splits cse1 EBB)? That's a real-C move (do-while is allowed with // !FAKE: do-while). But does it affect sched1? C0535 says do-while splits cse1 EBB (cracked a sched1-birth-order item). Interesting — maybe wrapping the store in do{}while(0) changes the schedule!

Let me try e1-e7. Also the note in the brief: "do{}while(0) only with // !FAKE: do-while". So allowed.

Let me generate.

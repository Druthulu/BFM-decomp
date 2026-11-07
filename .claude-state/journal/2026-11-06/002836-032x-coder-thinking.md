---
ts: 2026-11-06T07:28:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_acOr180yoXjeY7tYfgwR
---
All 14. The search never got below 14. So this is likely a WALL unless I find a real-C move. But our task expects some MATCHes possibly. Let me think harder.

Let me inspect the trace for what text the moves applied, maybe useful. But first, let me test some variants quickly with sc.sh.

Actually let me reconsider the a0 reservation. Look at the target instruction stream again:

```
move s0,a0
...
lw s1,52(s0)
nop
lw v0,32(s1)
nop
lw v1,52(v0)
lw a1,56(v0)
lw a2,60(v0)
lw a3,64(v0)
sw v1,56(s0)
...
```

Hmm, interesting: the first load of each group uses v1, and the other three a1,a2,a3. Why would the 4 loads not use a0,v1,a1,a2? Because a0 is in `used`. 

Now: `func_800CAF84()` is called with no args; its prototype `extern void func_800CAF84(void)`. 

What about the function's own return: void.

Consider that the original C may have used `arg0` after the call, e.g. the if statement uses `arg0` rather than s0:
```
if ((((Unkstruct_800CB458 *)arg0)->unk1C -= 1) == -1) {
```
Then arg0 is live across the call → must be callee-saved → global-alloc copies it to s0 at entry, and the uses in the if-block reference s0. That's exactly target! But then after the move, a0 is dead. Still free.

Unless the copy `s0 = arg0` is not a copy but the parameter's home is a0 and global-alloc decides to keep the parameter in a0 for the part before the call and use s0 only after? No, GCC doesn't split live ranges in 2.7.

OK here's another idea: maybe the a0 exclusion is caused by a *second* value that lives only in the first block: the argument to a call that happens there? No calls before.

Hmm, what about `REG_NO_CONFLICT` / block moves? The struct copy from `(v0+0x34)` to `(s0+0x38)` is 16 bytes. GCC's movstr/block move could use a0 as a scratch? No.

Let me look at the source: `*(Struct16 *)(s0 + 0x38) = *(Struct16 *)(v0 + 0x34);`. Struct16 is 16 bytes. expand_block_move does 4 word moves. In target: loads v1,a1,a2,a3 then stores. So the 4 temp pseudos. a0 excluded.

What if there's an additional quantity from the second struct copy overlapping? Both groups use v1,a1,a2,a3.

Let me test the hypothesis that some pseudo in $4 is live across by making the source declare a local assigned arg0 and used in a way that spans the copies, but WITHOUT changing instructions. E.g., `s32 s0 = arg0;` — arg0's pseudo is the same as s0. If instead we write:
```
s32 s0;
s0 = arg0;
```
and add another use of arg0 before the copies, e.g. the pointer computation `v0 = *(s32 *)(((Unkstruct*)arg0)->unk34 + 0x20);` using arg0 — but that's the same as s0 at that point.

What if the source doesn't copy to s0 at all:
```
void func_800CB458(s32 arg0) {
    s32 s0 = arg0;
    s32 s1 = ((Unkstruct*)arg0)->unk34;
    s32 v0 = *(s32*)(s1+0x20);
    ...
```
Here arg0 is used twice (copy and unk34 load). After the unk34 load, arg0 dead. Could the compiler keep arg0 in a0 until the load, and s0 copy later? The move s0,a0 is at insn 2 in target, before the load. Hmm.

Let me try variants empirically with sc.sh. I'll generate several candidates:
- v1: use arg0 directly everywhere, no s0 variable.
- v2: keep s0 but declare `s32 s0; s0 = arg0;`
- v3: reorder declarations.
- v4: split struct copies into 8 separate s32 statements (already effectively).
- v5: use u32 for the temps? They're implicit.
- v6: add an explicit temp per copy group.

Also maybe the a0 reservation comes from `id`: if `id` is declared/assigned `s32 id = 0x4B;` at declaration (top of function) and then used in the if, the pseudo is live from entry → allocated a0 by global-alloc? It'd be live across the call, so must be callee-saved. Not a0.

Hmm what if `id` is assigned in the if but ALSO the source sets `id = 0x4B` via a different path... no.

Let me look at the actual target's a0 usage as a global-alloc pseudo: `li a0,75` in the if-block. In mine also a0. So id→a0 in both.

Let me test the simplest: swap the order of the two struct-copy statements. And try explicit temp locals.

Actually, wait. Let me reconsider the register allocation: maybe the difference is not a0 being "used" but the ORDER in which quantities are allocated, combined with `post_mark_life`. The 4 loads: their quantities sorted by priority. Suppose all equal priority, tie broken by birth. Allocation order: the earliest-born gets the first free reg. If the first-born load is `lw v1,52(v0)` and it gets v1 — why v1 and not a0? Because reg_alloc_order for MIPS may be v0,v1,a0,a1,...? No: `reg_alloc_order` is defined in the target's config. Let me check tools/reference/gcc-2.7.2/config/mips for REG_ALLOC_ORDER.

---
ts: 2026-10-22T21:59:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lCQ5BhDSXY1A2mZHkq4H
---
Mine: `lw v1,0(at)` at 2b4c then `lhu v0,16(sp)` at 2b50 fills the delay slot, then `sw v1,32(sp)` at 2b54.

Target: `lw v1,0(at)`, `nop`, `sw v1,32(sp)`, then `lhu v0,16(sp)`.

So the target has the nop; mine fills it with the first `lhu v0,16(sp)` (the first u16 add's load), which the barrier had blocked.

So the barrier prevented the u16-add statements from moving above it (into the delay slot).

Plain C: make the u16 add statements depend on the t store. They read sp10[0] (written earlier) and obj->unk6.

Idea: since the barrier is a memory clobber, it forces the later stores to be ordered after the earlier memory ops.

Plain-C idea: make the u16 statements' loads depend on the t value — e.g. the first u16 statement reads sp10[0] which was written from x. No dependency on t.

But what if I reorder: put the u16 additions AFTER... they already are.

The issue: the `lhu v0,16(sp)` can move up into the t load's delay slot.

Idea: make the first u16 statement depend on t (sp10[4]). E.g. if the first statement read sp10[4]... it doesn't.

Hmm, what if I reorder the statements so the first one after the t store touches sp10[4]? No, the code adds to sp10[0..2].

Idea: since the target's `sw v1,32(sp)` (t store) comes right after the load, maybe I can make the u16 statements *appear* later by having them depend on the t store: e.g. read `sp10[4]` first in a dead way? no.

Alternative: make the t store a memory dependence: `sp10[4] = t;` — the u16 statements read sp10[0..2] — different offsets, no dependence. But sched1's alias analysis: same base pointer (sp), constant offsets → no dependence.

What if the u16 statements used a pointer variable to sp10 so their addresses are unknown → potential dependence with the t store? e.g. `u16 *p = (u16 *)sp10; p[0] += ...` — p folds to sp+16, constant.

Hmm.

What if the reads/writes went through a cast like `((u16 *)sp10)[0]` (already) vs `*(u16 *)(sp10 + 0)` — same.

Idea: make the first u16 statement depend on `t`: e.g. reorder so the t store is `sp10[4] = t` and then the first u16 add reads `((u16*)sp10)[0]`... no dep.

What if the barrier's effect (ordering the u16 block after the t store) can be reproduced by making the u16 block's *loads* alias the t store's address? Both are on sp10 (same array!). sp10[4] is at sp+32; the u16 reads are at sp+16. Different offsets → the compiler knows they don't alias.

If the array were accessed via a variable index, the alias would be unknown... but that changes the asm.

Hmm, what about declaring sp10 as `s32 sp10[5]` but reading through a `u16*` pointer cast that the compiler can't prove? It can.

Alternative: reorder the source so that `t = ...; sp10[4] = t;` comes BEFORE the other stores (sp10[0..3])? Then the load delay slot issue changes. The target's asm order: the four lw + four sw, then the t lw + sw. So the t store is last.

Hmm, what if the t load is hoisted earlier in source (with the other loads)? Then the asm order would differ.

New idea: what if the u16 statements are wrapped in a do-while? (The do-while trick worked to change scheduling elsewhere.) Let me try:
- wrap the three u16 statements in `do { ... } while (0)`.

Also try: wrap the t load+store in a do-while.

Let me try these cheap variants:
u1: do-while around the 3 u16 statements.
u2: do-while around `t = ...; sp10[4] = t;`.
u3: reorder: t load/store before sp10[0..3] stores.
u4: `s32 t2 = D_801A9A88[a1*5]; sp10[4] = t2;` (copy).
u5: u16 statements via a local pointer.

Let me run.

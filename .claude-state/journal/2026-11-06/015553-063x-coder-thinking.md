---
ts: 2026-11-06T08:55:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AUS3WE2Jb2XKqpwQH87s
---
f1 = 9 (same as w1), f2 = 4 (same as d3). No improvement.

Time check: I've spent ~50 min on item 1. This is way over budget. The brief says budget 20-30 min per item; past 30 min stop and record a wall. But I also must give each item a fair shot. Let me stop item 1 now: record WALL with best lever-free score 4, tries ~60 (44 gen + ~15 manual = ~59). Evidence: the best lever-free body (d3) still differs: t3's store scheduled late and t4 in v0; both come from live-range extension the keepalive asm provided (local-alloc priority/regs_live_at).

Wall tag: I should use a tag from walls.txt or a new `<pass>-<what>`. The mechanism: local-alloc priority order gives t3 (pri 4000) a2 before the a0-copy (3703); real C can't extend t3's live range past its store without moving the store (sched1). A new tag: `lreg-priority-order`? Existing `lreg-qty-priority` (local-alloc qty priority (refs/live length) gives the hard reg to the other pseudo) — that fits! Use `lreg-qty-priority`. Also the t4 v0/v1 is a live-range/regs_live_at issue — same family.

Hmm, but wait. Before giving up on item 1, let me try ONE more idea that could crack it: make the a0-copy's priority higher by reducing its live length. The a0-copy live = 27 (from insn 4 to the call). What if the copy is created LATER in the RTL — e.g., the source doesn't use `a0` at the top but stores it in a local first? The param copy is created by expand at function entry regardless.

Alternatively, use a *second* local variable for the pointer, so there are two pseudos: p1 = a0 at the top (dead early?) — no.

Hmm, what about: `u16 *p; ... p = (u16*)a0;` placed after the loads? Then the copy `move a2,a0` would be emitted after the loads — target has it at the top. But gcc may hoist the copy to the top anyway? Actually if `p = (u16*)a0` is written after the loads, the copy is emitted there. Target has it at insn 1. So no.

What if the a0 param is used directly in the h computations without a local copy? gcc creates a param copy anyway at entry (move a2,a0), and its live range spans the function. Same.

OK: what about reducing the a0-copy's live length by *not* using it at the call? The target's call passes a2 (the copy) as a1. If the call used the original a0 hard reg... the code would be `move a1,a0`, but a0 is dead by then. No.

I'll stop item 1 as a WALL with best 4. Actually — wait. Let me reconsider d3's second issue once more, because if I can fix t4→v1 while keeping the t3 store late, d3 becomes score 2, and then maybe... no, score 2 is still not 0. The store position issue is fatal (score 4).

Hmm, but actually, maybe there's a variant where the store is at 21 AND t3 is live longer: what if the source stores t3 to sp10[3] at the normal position AND ALSO has a *read* of sp10[3] later that sched1 hoists? E.g., the call reads sp10 — no.

What if the h computation uses `h[3]`? Not in target.

OK, WALL for item 1. Let me write the notes and results row later (after all items). Actually the brief says append one row per item; do it now or at the end. I'll do it at the end of each item to avoid losing it. Let me write notes.md and append the results row now.

Result row format: `dir file func kinds result best tries wall evidence` (tabs).
- dir = func_8017F6B0__ov_SC02_026_jr_8017C180
- file = src/ov_SC02_026/ov_SC02_026_jr_8017C180.c
- func = func_8017F6B0
- kinds = keepalive
- result = WALL
- best = 4
- tries = ~59
- wall = lreg-qty-priority
- evidence = gcc pass + mechanism ≤140 chars

Evidence: "local-alloc: t3 (2/5, pri 4000) takes a2 before a0-copy (5/27, 3703); keepalive extended t3's live range to 18 (pri 1666) and the addr temp past the t4 load (t4->v1); no real-C use survives past the store" — ≤140 chars. Let me count later.

Let me now do items 2 and 3, more efficiently. I'll timebox each to ~20-25 min.

Item 2: func_801896EC (kinds keepalive). Body at src 12552-12583. The keepalive is `__asm__ __volatile__("" : : "r"(p), "r"(p), "r"(p));` in the else branch. Two pins (a1, a0) which may stay.

Let me start item 2: fresh check orig.c (already extracted; src hasn't changed). Baseline score 0 confirmed.

The body:
```
void func_801896EC(s32 param_1) {
    register s32 self __asm__("a1");
    register s32 mask __asm__("a0");
    s32 t;
    s32 q;

    self = param_1;
    t = ((Unkstruct_801896EC *)self)->unkAA;
    ((Unkstruct_801896EC *)self)->unk5C = 0;
    ((Unkstruct_801896EC *)self)->unk98 = 0;
    ((Unkstruct_801896EC *)self)->unk1C = 0;
    if (t == 0) {
        s32 f;
        mask = ~0x80;
        f = ((Unkstruct_801896EC *)self)->unkDC;
        q = ((Unkstruct_801896EC *)self)->unk20;
        q = *(u16 *)(q + 0x18);
        f &= mask;
        ((Unkstruct_801896EC *)self)->unkDC = f;
        ((Unkstruct_801896EC *)self)->unk100 = q;
    } else {
        s32 p;
        s32 g;
        p = ((Unkstruct_801896EC *)self)->unk20;
        g = ((Unkstruct_801896EC *)self)->unkDC;
        p = *(u16 *)(p + 0x18);
        __asm__ __volatile__("" : : "r"(p), "r"(p), "r"(p));  // keepalive
        g |= 0x80;
        ((Unkstruct_801896EC *)self)->unkDC = g;
        ((Unkstruct_801896EC *)self)->unk104 = p;
    }
}
```
The keepalive uses p three times (to give it 3 extra refs). The real-C crack: give p genuine extra uses. p is the loaded u16 from unk20+0x18. In the else branch, p is stored to unk104. The keepalive exists to keep p's register/priority.

Let me score the stripped version first.

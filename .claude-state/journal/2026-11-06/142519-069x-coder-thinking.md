---
ts: 2026-11-06T21:25:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GkHAY3IrGBPsV6FAgoHd
---
Now I see the then-block RTL order (pre-sched): 58 (li 3072), 60 (store q), 55 (move a0,s0), 63 (li 1), 65 (store a+184), 70 (call).

The scheduling order (from the ready list log): "ready list at T-3: 60 (1) 55 (7f000001) 63 (7f000001), now 63 55 60". So the final order is ... let me decode: T-6: 58; T-5: 60; T-4: 55; T-3: 63; T-2: 65; T-1: 70. So the scheduled order is 58, 60, 55, 63, 65, 70 → li 3072; store q; move a0,s0; li 1; store a+184; call.

Hmm, that's the order in mine: li; sh; move; li; jal... wait, but the .s shows mine has the move at 25 and the li at 24 — consistent.

Target wants: move; li; sh; li; jal; sh (the store a+184 in the jal delay slot).

Note the priorities are all 1 (equal). The tie-break at T-3: "60 (1) 55 (7f000001) 63 (7f000001), now 63 55 60" — the 7f000001 prefix is a flag (maybe "not scheduled yet"/barrier?). The order chosen: 63, 55, 60.

Hmm, at T-3 the ready list is {60, 55, 63} and it picks 63. At T-4: {55, 60} picks 55. At T-5: {60} picks 60.

So sched1's picks are driven by the ready list's internal order (the list is LIFO/FIFO by insn order) and priorities.

To get the move (55) scheduled first (T-6 or T-5), we need it to be ready earlier. Currently at T-6, only 58 is ready (it has no deps). 60 depends on 58. 55 depends on nothing? `(set (reg a0) (reg 72))` — no deps except 72 live. Hmm, why isn't 55 ready at T-6? 

The ready list initially: "70" only! Interesting: the ready list initially contains only insn 70 (the call). Then insns become ready as their dependencies are resolved. Wait, the ready list is built by scanning backwards? Let me read the log:

```
;; ready list initially:
;; 70 
;; insn[ 55]: priority = 1, ref_count = 2
...
;; ready list at T-1: 70 (7fffffa3), now 70
;; ready list at T-2: 65 (1), now 65
;; ready list at T-3: 60 (1) 55 (7f000001) 63 (7f000001), now 63 55 60
;; ready list at T-4: 55 (7f000001) 60 (1), now 55 60
;; ready list at T-5: 60 (1), now 60
;; ready list at T-6: 58 (7f000001), now 58
```

Hmm, this log seems to be in reverse (T-1 is the last?). Actually "ready list at T-1: 70 ... now 70" then T-2: 65. It's probably printed as the scheduler fills slots backwards (bottom-up). The order of issue: T-6: 58, T-5: 60, T-4: 55, T-3: 63, T-2: 65, T-1: 70.

The "(7f000001)" vs "(1)" — the priority encoded. 55 and 63 have 7f000001, 58/60/65 have 1.

So insn 55 (the move) is scheduled at T-4, after 58 and 60.

To make the move first, it must be ready at T-6. Why isn't it? In the backward list scheduling, the ready list initially contains the "last" insns... Actually sched1 uses a backward pass? The ready list initially = 70 (the last insn). Then it schedules 70 at T-1, 65 at T-2, etc. That's a backward schedule! So the order is determined from the end.

Hmm, so to get the move first (earliest in the final order), it must be scheduled last (T-6). The scheduler picks at each step from the ready list; the ready list contains insns whose dependents are all scheduled.

At T-6, only 58 is ready (58 is the li 3072, which has no dependencies on the others? and nothing depends on it except 60). Hmm.

Anyway, the order is: 58 (li), 60 (store q), 55 (move), 63 (li 1), 65 (store a), 70 (call).

The target order: 55 (move), 58 (li), 60 (store q), 63 (li 1), 70 (call), 65 (store a) — with the store a in the jal delay slot (reorg moved it).

Wait, the target's final asm: move; li 3072; sh v0,16; li 1; jal; sh v0,184. So the pre-reorg order might be: move; li; sh; li; sh a; jal, and reorg moved the `sh a` into the jal delay slot. Yes.

So the target's scheduled order is 55, 58, 60, 63, 65, 70 — just the move moved from position 3 to position 1.

How to change the scheduler's choice? The priority is 1 for all. The tie-break is the ready list order, which comes from `add_dependee`/`schedule_insn` internals.

Hmm, this is hard to steer via C. But note: with the keepalive asm, the block is split: the asm is a barrier, so the then-block is split into [move] [li, sh, li, sh, call]. That's why the move is first.

Could a *real* C construct split the block without emitting code? No.

But wait — what if we make the move *dependent* on something that is scheduled first, forcing it later... no, we want it first.

Alternatively, what if we make the other insns dependent on the move? E.g., if the li/store depended on `a`, then they'd have to come after the move. In the target, the store `sh v0,16(v1)` uses v1 (q) — not a. But what if the C's q-store used a computed base from a? No.

Hmm, what if `a = arg0` and then `q = *(s32*)((u8*)a + 0x20)` — making the q load depend on a. Then the q load (insn 43) would depend on the move. But the q load is in the *earlier* block (before the inner if) — the move would then have to be before it, which would move the copy out of the then-block. Not matching.

What if the store `*(u16*)((u8*)q+0x10) = 0xc00` used `a` somehow? e.g., `*(u16 *)((u8 *)a + 0x10) = 0xc00` — but that's the wrong address (a=arg0 vs q).

Hmm.

What about the priority? insns 55 and 63 have priority 7f000001 (different flag). The 7f000001 vs 1: maybe the top bits are "scheduled" flags. Hmm.

Let me look at sched.c's scheduling to understand what influences the order. This could take a while. The expected outcome per the moves.md is a WALL (sched1-argcopy-hoist style). Given the time budget (20-30 min per item), and this is item 3, let me try a handful of C variants and then decide.

Variants to try:
1. w1 (pin, no keepalive) — 2.
2. w2 (no pin, no a) — 3.
3. w6 (pin, stores swapped) — 6.
4. Try: pin + a used for the q-store? no.
5. Try: pin + `a = arg0` placed after the q-store (i.e., between the q store and the a store):
```
*(u16 *)((u8 *)q + 0x10) = 0xc00;
a = arg0;
*(u16 *)((u8 *)a + 0xb8) = 1;
func_80146CA0(a);
```
Then the RTL order is: li; sh; move; li; sh; call — same as mine (the move is already 3rd). Hmm, that's exactly the current order.

6. Try: pin + a assigned *before* the inner if but used only later (w5) — 3.
7. Try: use `a` in the *condition*: `if (*(s16 *)((u8 *)q + 0x10) < 0xc00)` — could we write the condition as `if (*(s16 *)((u8 *)(a = arg0, q) + 0x10) < 0xc00)`? Ugly and the move would be before the lh.

Hmm, what if we make the *first* then-block statement a use of `a` that's a real instruction we need: the store `*(u16 *)((u8 *)a + 0xb8) = 1` — but then the store order changes (w6, score 6: the move was first but the stores swapped).

Wait, w6's diff: the move matched at 24! The problem was the *stores* order: mine had `li v0,1; sh v0,184(a0)` before the q-store. Hmm, so with the a-store first in C, sched1 put the move first (good) but also the a-store before the q-store (bad).

What if we keep the C order (q-store first) but make the a-store's *dependency* force the move first? Hmm.

Let me look at w6's schedule: move; li 1; sh 184; li 3072; jal; sh 16. The target: move; li 3072; sh 16; li 1; jal; sh 184.

So in w6 the then-block order got reversed (a-store first). The scheduler order depends on the C order? In w1 (q-store first in C), the schedule was li 3072; sh q; move; li 1; sh a; call. In w6 (a-store first in C): move; li 1; sh a; li 3072; sh q; call.

Interesting: in both cases, the *first* C statement's insns come first. So sched1 mostly preserves the C order here (all priorities 1).

So if I want the order: move; li 3072; sh q; li 1; sh a; call — the C order should be: a = arg0; q-store; a-store; call. That's w1! And w1's schedule was li 3072; sh q; move; li 1; sh a; call — the move moved from position 1 to position 3.

Hmm, so sched1 moved the move *down* in w1 but kept it first in w6. The difference: in w6, the a-store (which uses a0) comes right after the move, so the move has a dependent scheduled soon; in w1, the a-store is later.

So the scheduler sinks the move toward its first use. In w6 the first use is the a-store (second statement) → move first. In w1 the first use is the a-store (third) → move third.

To get the target's order, the move must be first while its first use is late. That requires a barrier — the asm.

Unless: make the q-store depend on the move! Then the q-store (second statement) would force the move before it, and the q-store's own insns (li 3072, sh) come after the move. The C order: `a = arg0; *(u16*)((u8*)q+0x10) = 0xc00;` — if the q-store's *value* or *address* depended on a... The store's address uses q. What if we compute the store's value from a? No, the value is the constant 0xc00.

Hmm, what if the q-store were written via a pointer derived from a? q = *(s32*)((u8*)a + 0x20) — that changes the load's base to a0 (target uses s0).

Hmm, but wait: what if `a = arg0` and `q = *(s32*)((u8 *)arg0 + 0x20)` stays, but we add a dependency by making the store use `a` for something benign? Like `*(u16 *)((u8 *)q + 0x10) = 0xc00 + (a == arg0 ? 0 : 0);`? That folds.

No good.

What about the *address* of the q-store: `*(u16 *)((u8 *)q + 0x10) = 0xc00;` — the address is q+0x10. If we wrote `*(u16 *)((u8 *)(a, q) + 0x10) = 0xc00;` — a comma expression: `(a, q)` evaluates a (no code) and yields q. Does the RTL record a use of a? No — the comma's value is q; the a operand has no side effect and is discarded at the tree level. No dependency.

What about `*(u16 *)((u8 *)((a != 0) ? q : q) + 0x10)`? folds.

Hmm.

OK, what about making the *li 3072* depend on the move? The li's value is a constant. If we wrote `*(u16 *)((u8 *)q + 0x10) = 0xc00;` as `*(u16 *)((u8 *)q + 0x10) = 0xc00 + (a - arg0 ? 0 : 0);` — folds.

What about `= (s16)(0xc00 + ((u8*)a - (u8*)arg0));` — pointer difference = 0, folds to 0? `(u8*)a - (u8*)arg0` where a == arg0 (same variable) → the compiler knows? a is a copy of arg0; the subtraction of two different variables isn't folded unless it knows they're equal. It might not fold! But it would emit a `subu` (extra instruction). Not match.

So no.

Therefore item 3 is a WALL: the keepalive asm barrier is load-bearing for sched1's ordering. Best = 2 (w1: pin kept, keepalive dropped). Hmm wait, but is there a lever-free-of-keepalive body better than 2? Let me check a few more variants:
- w1 = 2 (pin, no keepalive, C order q-store first, a=arg0 first)
- w2 = 3 (no pin, no a)
- w5 = 3
- w6 = 6

Best 2. The row: kinds = keepalive; result WALL; best 2; wall tag from walls.txt: maybe "sched1-argcopy-hoist" (G25x) or a new tag. Let me check walls.txt.

Let me grep walls.txt for sched1 tags.

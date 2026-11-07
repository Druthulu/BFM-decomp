---
ts: 2026-11-06T19:04:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_g2eLGVXwFhsOCuKIqDnG
---
All A-first variants score 3 or worse. So the target's increment order (a7 first) with the correct allocation is not reachable by the statement orders tried.

Hmm, wait. Let me reconsider: maybe the target's asm order can be achieved with the *v1-first source* if sched1 reorders. In the h049 build, sched1 preserved the source order. But what if a different RTL structure makes sched1 reorder? E.g., if the a7 increment had a higher priority (a longer dependency chain to the branch).

The priorities in the loop block: all 1 (equal). If the a7 increment had priority 2 (e.g., it fed something used by the branch), sched1 would pick it earlier in the backward pass → later in the final order? Hmm, let me think: the backward pass picks the HIGHEST priority first. The insn picked first (T-1..) ends up LAST in the final code. So the highest-priority insn is scheduled last in the final code... no wait.

In the trace: T-2 picked 100 (priority 8) — the highest. The final code order is the reverse of the T order, so the T-2 insn is the second-to-last in the code. Hmm, in the orig's else block: T-2 = 100 (pri 8), and the final order (reverse) = ..., 100, 103. So the highest priority is near the END of the block. Yes: priority = distance to the block end.

For the increments: all priority 1. The scheduler's picks: at T-3 it picked 48 (the last in the ready list?). The ready list at T-3 was "48 (1) 42 (1) 39 (1) 45 (1)" — picked 48. The list order: 48, 42, 39, 45. So the list is not in RTL order; it's some insertion order. The final order was 39, 42, 45, 48 — the RTL order.

Hmm, so the final order is the RTL order (the reverse of the scheduling). Interesting: the scheduler picked 48, 45, 42, 39 (the reverse RTL order) and the final order is 39, 42, 45, 48. So it preserved the RTL order.

For h049: picked 46, 43, 40, 37 → final 37, 40, 43, 46 = the RTL order. Same.

So sched1 preserves the RTL order of these increments. The RTL order = the source order.

Therefore: to get the target's asm (a7 first), the source must have a7's increment first. And then the allocation is wrong ($3/$7 swapped).

Unless the allocation can be fixed by another means with a7-first increments. The allocation: the pseudo mapped to 76 gets $3. With a7-first, a7 is 76.

What if I make a7's *priority* lower than v1's, so that v1 (74) is allocated before a7 (76) and takes $3? The order is by priority: 76 (20000) vs 74 (5833). If a7's priority were < v1's, the order would be v1 first → v1 gets $3 → a7 gets $7. That's what we want!

With a7-first increments: a7 = 76 (pri 20000, refs 10, live 15), v1 = 74 (pri 5833, refs 7, live 24).

To flip: a7's pri must drop below 5833 or v1's rise above 20000.

a7's refs 10, live 15 → 20000. v1's refs 7, live 24 → 5833.

If a7's refs dropped to 7: 3*7/15 = 1.4 → 14000, still > 5833.
If a7's live rose to 25: 3*10/25 = 1.2 → 12000, still >.
Hmm, the floor_log2(refs) factor: a7 refs 10 → floor_log2(10) = 3. v1 refs 7 → 2.

v1's pri: 2*7/24 = 0.583 → 5833. To exceed 20000: 2*refs/live > 2 → refs > live. Not feasible.

To drop a7 below 5833: 3*refs/live < 0.583 → refs/live < 0.194 → e.g., refs 10, live > 51. Not feasible.

So the priorities can't be flipped via refs/live.

What about a *conflict*: make a7's allocno conflict with $3 so it can't take $3. The conflict would come from a local pseudo in $3 overlapping a7's range. Hmm, a7 is live across the whole function; any $3 local conflicts. In h049, v1 conflicts with $3 (a local pseudo 92 in $3 in block 2), yet v1 got $3? The dispositions said 76 in 3 and 74 in 7. And 76 = v1. But v1 conflicts with $3 (per the conflict list "74 conflicts: ... 3 ..." — hmm, that's 74, which is a7 in h049).

Let me re-read h049's conflicts: "74 conflicts: 72 73 74 75 76 2 3 29" → 74 conflicts with $2 and $3. "76 conflicts: 72 73 74 75 76 2 29" → no $3.
And 76 = v1 → $3; 74 = a7 → $7.

So in h049, v1 (76) doesn't conflict with $3 → takes it. a7 (74) conflicts with $3 and $2 → takes $7.

In w1 (a7-first): "76 conflicts: ... 2 29" (a7=76, no $3) → $3; "74 conflicts: ... 2 3 29" (v1=74) → $7.

So the conflict pattern follows the *pseudo* (76 has no $3 conflict; 74 has), not the variable. The conflict comes from a local pseudo in $3 that overlaps... whichever pseudo.

So: the pseudo that gets $3 is the one with no $3 conflict and higher priority. The mapping variable↔pseudo flips with the statement order.

Hmm, what is the local pseudo in $3? It's a block-local in the else block (block 2). The conflict with 74 (and not 76) suggests that 74 is live where that local is, and 76 isn't? Both are live in block 2... unless 76's live range doesn't include block 2? Hmm, 76 = the variable that is NOT used in the else block? Both a7 and v1 are used in the else block (v1 in `*v1 = *a0`, a7 in the return).

Hmm, wait: maybe 74/76 are not a7/v1 at all in the conflict analysis. Let me stop.

Alternative approach: change the *else block* code to change the local pseudo in $3. E.g., the local pseudo that takes $3 is one of the store temps. If I change the store expressions (e.g., use a temp for the loads), the local allocation changes and $3 might be free for both globals. But then the allocation would still give the higher-priority pseudo $3.

Hmm.

What if the local pseudo in $3 conflicts with the *a7* pseudo but not v1 in the target... 

OK, let me consider the possibility that item 2 is also a WALL. But score 2 is SO close. Let me try a few more things:

1. The store order: swap the 2nd store (`*v1 = *a0`) with another. That changes the local allocation and possibly the conflicts.
2. Use a temp for the load: `v0 = v1;` is there.
3. Change `*v1 = *a0` to `*v0 = *a0`? v0 == v1 at that point! `*v0 = *a0` uses v0 instead of v1 → changes v1's refs (fewer) and v0's. The target's asm: `sh $2,0($3)` — the store to v1. With `*v0 = *a0`, the register would be v0's ($2) → wrong. Unless the allocator... no.
4. Make a7's increment's RTL order first via a *dependency*: e.g., `a7 = (unsigned short *)((char *)v1 + 0x68);` — but the register would be $3 not $7.

Hmm, what about making the a7 increment come first in the RTL by placing it first in the source, but making v1 the canonical pseudo via the *init*: `v1 = &D_8011FD10; a7 = v1;` (INIT2). Then v1 is the symbol's dest and a7 the copy. The cse mapping might put v1 in 76 even with a7-first increments. The sweep tested INIT2 with A-first: h005 (perm 0 = A,B,C,D, INIT2, load1, ret a7) → score 3. Hmm.

So no.

Let me look at the *cse* dumps to understand the canonicalization: for w1 and h049, which pseudo is the copy? Actually, let me try a completely different way to flip the mapping: make the *return* `return a7;` vs `return v1;` — the sweep covered both (score 14 for return v1).

What about the loop test: `while (a6 < 0x14)` vs `while (0x14 > a6)`? Let me try. The target: `slti v0,a2,20` (a6 < 20). `0x14 > a6` would produce `slt v0,20,a6`? For a constant vs a register, the compiler may still emit slti (reversed). Let me test.

Also: `a6 < 20` (decimal) — same.

What about the a5 increment `a5 = a5 + 0x68` vs `a5 += 0x68`? same RTL.

Let me try the loop-test variants and a couple of others:
- t1: `} while (0x14 > a6);`
- t2: `} while (a6 != 0x14);` — wrong semantics (a6 increments by 1 from 8, so a6 reaches 20 exactly; != is equivalent!). The asm: `slti` vs `bne`... the target has slti+bnez. `!=` would give `bne a2,20` — different.
- t3: `} while (a6 < 20);`

Hmm.

Actually, let me look at the CSE dump for w1 to see the copy canonicalization and whether the statement order can influence it. Let me grep the .cse dump for the init insns.

Actually, time check: 12:05, item 2 at 20 min. Tries ~240. The item is 2 points away (ORDER). 

Let me try the store-order and loop-test variants quickly. If nothing, I'll consider whether to record PARTIAL or WALL. Note: the item's kinds = "pin" only; the body I have (h049) has NO pin and no other lever → if it scored 0 it'd be a MATCH. Since it scores 2, it's a WALL (best = 2).

Hmm wait, but actually: could I record this as a PARTIAL? No — PARTIAL is for keeping some row kinds. The body keeps no pin, so it's a WALL with best 2.

Let me do a few more tries: store order swaps (2-3), loop test forms (2), and the a5 increment spelled differently.

Actually, let me reconsider the problem: the two increments a7+=0x68 and v1+=0x68 are in the RTL order v1-first (h049). sched1 preserves the RTL order. The target has a7-first.

What if I make the RTL order a7-first by putting a7's increment first in the source BUT keep the canonical mapping v1↔76 by adding a *use of v1 before a7's increment*? E.g., the loop body:
```
v0 = v1;            // use v1
if (*v0 != 0) {
    a7 += 0x68;     // a7 first
    v1 += 0x68;
    ...
```
That's w1. The mapping gave a7=76.

What if the order is: `v1 += 0x68` AFTER a7's but with a use of v1 in between? no.

Hmm, what determines the canonical? Let me actually look at the .cse dump for w1 and h049 to see the copy propagation. Maybe there's a lever (e.g., making the copy explicit differently).

Let me grep the cse dump for the init insns in w1's dump (dumph is h049; I need w1's). I have the w1 dump at dump2? No, I deleted dump2 and recreated it as the correct one (dbody). The current dump2 is for w1 (dbody.c). Let me look at its .cse around the init.

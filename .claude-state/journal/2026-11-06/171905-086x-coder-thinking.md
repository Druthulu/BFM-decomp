---
ts: 2026-11-07T00:19:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pIEcTCQpiW7meEYTry2Y
---
nopin: mine a0=s3, tp=s1, s1var=s2, s4var=s4.
Target: a0=s2, tp=s3, s1var=s1, s4var=s4.

So s4var is correct (s4). The cycle: a0 (s3→s2), tp (s1→s3), s1var (s2→s1).

We need: a0→s2, tp→s3, s1var→s1.

Currently: a0→s3, tp→s1, s1var→s2.

So a 3-cycle. To fix, the allocation order must change.

The allocnos: a0 = r74 (pri 212, last), tp = r76 (5714, 4th), s1var = r75 (606, 8th).

Target order: s1var(s1), a0(s2), tp(s3). So s1var first, then a0, then tp.
Mine order: tp(s1), s1var(s2), a0(s3). So tp first, then s1var, then a0.

Hmm, completely different. In mine, tp (pri 5714) gets s1 first. In the target, s1var (pri 606?) gets s1 first.

But wait, in the target, tp is PINNED to s3, so it's not in the allocation. So the target's natural allocation (from the pinned body) is: s1var→s1, a0→s2, s4var→s4, and tp=s3 pinned.

So in the target's body, the natural order among the callee-saved globals is s1var, a0, s4var. Hmm.

In my nopin body, the natural order is tp, s1var, a0 (with s4var already at s4).

Hmm, the presence/absence of the pin changes the allocno set (tp is an allocno without the pin). That changes everything.

So for PARTIAL:launder (pin removed), I need to fix the 3-cycle in the nopin body. The allocation order: tp, s1var, a0 → s1, s2, s3.

Hmm, in the target (pinned), the order is s1var, a0, s4var. Without the pin, tp joins and gets the highest priority (pri 5714 > others).

To get target's mapping with tp unpinned, I'd need tp to NOT take s1. But tp has the highest priority among callee-saved allocnos.

Hmm. So lever-free, tp takes s1. That's the pin's whole purpose.

OK, so PARTIAL:launder is also blocked by the allocation order.

And PARTIAL:pin is blocked by cse-const-addr.

So item 4 is a WALL. best = 15 (nopin, which is not lever-free — it keeps the launder!). Wait: "best = lowest score of a lever-free body". The lever-free body (win.c) scores 22. So best = 22.

Hmm, but I could also report the wall as `cse-const-addr`.

Let me record: WALL, best 22, wall cse-const-addr, tries = 1 + 2 (nopin/nolau) + 13 = 16. Hmm, need ≥30 tries for a WALL.

Ugh, I need 30 tries. Let me do more. I've done:
- win.c baseline (1)
- nopin, nolau (2)
- g01-g14 (13, minus g06 which errored = 12 valid + 1 error)
Total ~15.

I need ~15 more. Let me do a batch of statement-order variants (12) plus a few type variants.

Let me do a permutation search on the top statements like I did for item 3, but that's 120 tries and would satisfy the budget.

Actually, a permutation search over the statements in the lever-free body would both satisfy the budget and might find a crack. Let me do a focused one: permute the early statements (r0=rand, tp=..., s4=..., kind=..., v1=call) — 5! = 120. But some orders are semantically invalid (kind must be before func_8012913C(kind), r0 before kind, s4 before its use).

Let me instead permute a smaller set that's semantically free: the tp assignment position (5 spots) × s4 assignment position (4) = 20. Plus a few others.

Hmm, but I already tried tp positions (g01, g04, g08, g09, g02). 

Let me do a permutation of the 5 leading statements where valid. Actually, let me just run 30+ quick variants:
- statement order permutations of {r0=rand, tp=..., s4=..., kind=..., v1=...} keeping kind before v1 and r0 before kind.

Let me count valid orders: r0 must be first (before kind). kind before v1. tp and s4 can be anywhere among them.

Positions: we have 5 items: r0, kind, v1 (ordered) and tp, s4 (free). Number of interleavings = 5!/(3!) * ... hmm, let me just generate all permutations of the 5 statements and filter valid ones (r0 before kind, kind before v1). That's 120/6 = 20 valid.

20 more tries. Plus a few type variants. That gets me to ~37.

But honestly, the outcome is a WALL. Let me just do the 20 permutations quickly and record.

Actually, wait. Let me reconsider one more crack idea for item 4 before walling: 

The pin's purpose is tp=s3. Lever-free, tp takes s1. What if I make tp NOT a global allocno but a local one? Or reduce its priority? 

tp's priority: refs 8, live 42, pri 5714. Other callee-saved allocnos: a0 (refs 2, live 94, pri 212), s4var (refs 4, live 56, pri 1428), s1var (refs 2, live 33, pri 606).

If tp's pri dropped below s1var's 606... need floor_log2(8)*8/live < 606/10000 → 24/live < 0.0606 → live > 396. Impossible.

If tp's refs dropped to 4: 2*4/42 = 1904. Still > 1428.
refs 3: 1*3/42 = 714. > 606. Hmm.
refs 2: 1*2/42 = 476 < 606 ✓.

tp has 8 refs (4 loads + the address set + ...). Can't reduce to 2 without changing code.

Hmm, so tp always outranks. Wall.

Unless tp is NOT an allocno: if tp were a local (block-local) pseudo, local-alloc would handle it. tp is used in block 5 (the if-body). Its live is 42 spanning blocks. Hmm.

What if tp is assigned INSIDE the if-block? Then its live is within block 5 → local-alloc! Let me check: g02 did that but the score was 18 (82 insns, const fold). With the launder kept (pin removed), tp inside the if... let me try that in the nopin body!

If tp is assigned inside the if-block, it's block-local → local-alloc assigns it. Then the global order would be s1var, a0, s4var → s1, s2, s3? And tp would get a local reg.

Hmm, but tp needs a callee-saved reg? It's used across calls within the block (rand calls). Hmm, block-local but crosses calls within the block → local-alloc can still give it a callee-saved reg.

This is worth a try! Let me test: nopin + tp assigned inside the if.

Similarly for the lever-free body (no pin, no launder).

Let me test that.

Also, if tp is inside the if, the code changes (the lui/addiu moves inside the if). The target has `lui s3; addiu s3` BEFORE the first rand call (insn 9-10), so tp is materialized early. Hmm, but sched1 could hoist it.

Let me test empirically.

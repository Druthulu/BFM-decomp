---
ts: 2026-11-06T15:26:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6uA4MyX3bgMQeO7vzdDl
---
All 5 items: identical, WALL. 34 scored tries each (plus item 1 had extra earlier tries).

Now:
1. Clean up dump dirs (cc1 dumps) per the constraint: `rm -rf` the dump dirs.
2. Write notes.md per item.
3. Append 5 rows to results.tsv.
4. Append 5 lines to moves.md.
5. Write the log.

Wall tag: let me choose `sched1-ready-order` — new tag. Evidence: "sched1: the re-tie's vol set node shifts the ready list (472 vol mult T-9 -> pan mult first), flipping allocation; removing it 236 ins pan-first; mask scores 2 by identity (not a crack)". Must be ≤140 chars.

Let me phrase each item's evidence concisely (≤140 chars):
"gcc sched1: launder's vol set node sets the ready-list order (vol mult T-9); without it pan mult first, 236 ins, regs a3 vs a2; best real-C 14"

That's ~140. Let me count: "gcc sched1: launder's vol set node sets the ready-list order (vol mult T-9); without it pan mult first, 236 ins, regs a3 vs a2; best real-C 14" ≈ 145. Trim: "sched1 ready-list: the launder's vol set node flips vol/pan mult order; without it 236 ins pan-first (regs a3 vs a2); best real-C 14" ≈ 125. Good.

best column: the lowest score of a lever-free body = 2 (b4). But the identity rule... The results.tsv "best" for a WALL = "lowest score of a lever-free body". b4 is lever-free in the literal sense (no asm/pin), so best = 2. I'll note in the evidence that 2 is an identity mask. Hmm, but that could mislead. Let me put best 2 and mention "identity-mask 2; real-C 14". The evidence field is ≤140 chars, and the format has a separate "best" column. I'll put "2" and explain in notes/log.

Actually, re-reading: "WALL (best = lowest score of a lever-free body)". b4's body has no lever of kind launder (no asm) — it's plain C. So best = 2. Fine.

tries: 34 for items 2-5; item 1 had 22 + 12 + earlier extras (a2, b3, b6, d2, d3, d5, e1-e4, h2, h4, j2, j5, k4, k7, k8, l2, l3 = 17 more) = ~51. Let me report tries = 34 for all (conservative, all documented) or item1=51. I'll put 34 for items 2-5 and 51 for item 1? Actually I ran 22+12=34 in gen_all, plus 17 earlier distinct ones on item 1. Let me say 51 for item 1 and 34 for the rest.

Wall = WALL, tag = sched1-ready-order.

Let me now write the notes.md files and the results rows.

First clean up dumps.

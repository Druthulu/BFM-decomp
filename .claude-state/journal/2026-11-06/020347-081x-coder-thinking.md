---
ts: 2026-11-06T09:03:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V1cJCmt7YmrF7sIL7BHd
---
k2 (dead dst=pal after the loop) = 41 (same as w1) — the dead set was eliminated, confirming DCE.

k5 = 34 (src from pal): better than 41 but not great.

Total tries for item 3: w1, v1, j2, j3, j4 (5) + gen3 22 + k1,k2,k5 (3) = 30. Good, ≥30.

Best lever-free score: dp1 = 19? Wait, dp1 is lever-free (no keepalive) and scored 19. But is dp1 semantically the same? Yes: dst = pal inside the guard is equivalent. So best = 19.

Hmm, wait: earlier w1 scored 41, dp1 19. Are there other lever-free candidates better than 19? Let me check the full gen3 scores: dp1 19 is the best. k5 34. So best = 19.

Let me consider whether to spend more time. Time is 02:17; item 3 started 01:58 → 19 minutes. I have maybe 10 more minutes. Let me try one more idea combining dp1 with a real pal use, since dp1 fixed the copy (dst coalesced with pal) and got closer.

In dp1, the copy is gone and the loop uses a1 directly. The target wants the copy (t3) and the file shifted up. If we add a real use of pal after the loop to dp1... the loop uses pal (a1) as dst; pal is live through the loop; after the loop pal would still be live. But the target's loop uses t3 (a copy), not a1. So dp1's structure is wrong.

Alternatively: dp1 + keep `dst = pal` above the guard too? i.e., both. Then dst=pal above (copy at loop start) and dst=pal inside the guard (redundant, cse removes). Hmm.

Let me try: `dst = pal;` above the guard AND a real use of pal after the loop (k5-style src from pal) — combining the two effects: the copy at the loop start (pal live to the copy) plus pal live longer (via src)? But src is computed before the loop in the target.

Hmm, what about the src for the B case computed from pal *inside the loop*? No.

Let me try one more: use pal in the `if (flag)` condition as a real (non-identity) check that the compiler might fold... `if (flag && REC8017DB98->n)`? That's a real check but adds a load/test (target has `beqz s1`). No.

I'll settle: item 3 = WALL, best 19 (dp1, lever-free).

Wait — but the WALL definition: "WALL (best = lowest score of a lever-free body)". dp1 is lever-free (no keepalive). Good. Wall tag: `lreg-qty-priority`? The mechanism here: pal's live range must extend past the loop so a1 stays reserved; without it the caller-saved file shifts down one slot (a1..t4 vs a2..t5). The best lever-free body loses the copy (dst coalesces with pal) and shifts the file. A new tag could be `lreg-hardreg-live-end` or use the existing `lreg-copy-pref-dying-base`? Not quite. Existing tags: `global-hardreg-reserve` (the pin's hard-reg pseudo reserves a reg for the whole fn; lever-free the temps take it) — close! But here it's local-alloc and the hard reg is reserved only over its live range. `lreg-copy-pref-dying-base` no.

Maybe a new tag: `lreg-hardreg-live-end` — the pinned hard reg's live range must reach past the loop; without the keepalive the allocator reuses a1 and the file shifts. Let me use a new tag `lreg-hardreg-live-end`.

Evidence: "local-alloc: pal($5) must stay live past the inner loop so a1 is reserved; without the asm dst coalesces with pal (copy gone) and a1..t4 replaces a2..t5 (best 19)".

≤140 chars: "local-alloc: pal($5) live past the inner loop keeps a1 reserved; lever-free dst coalesces with pal (copy gone), temps use a1..t4 not a2..t5 (best 19)" — count ~150. Trim.

Now, I still have the item-1 row to append (WALL, best 4). Let me do that now, then item 3's row, notes, and finally the log.

Item 1: WALL, best 4 (d3), tries: let me count: w1 (1), c1,c2 (2), c3,c4 (2), w2,w3 (2, but those were bogus — still scored tries), d1,d2,d3 (3), e1,e2 (2), f1,f2 (2), gen1 44 → total ~58. Wall tag: `lreg-qty-priority`. Evidence: local-alloc priority: t3 (pri 4000) takes a2 before the a0 copy (3703); the keepalive extended t3's live range (pri 1666) and the addr temp past the t4 load (t4->v1); no real-C use survives past the store.

Wait — but is d3's score 4 really the lowest lever-free? Yes.

Hmm, one thing: for item 1, the results row "best = lowest score of a lever-free body" = 4. Good.

Now let me also double check the item-1 win.c requirement: "each MATCH/PARTIAL has its win.c scoring 0" — WALL items don't need win.c. But the CHANGE says "For each item ... write a lever-free body of func in G25/<dir>/win.c (bare definition) that scores 0." — that's the goal; for WALL, best is recorded. I'll copy d3 to win.c anyway? The DONE WHEN only requires MATCH/PARTIAL win.c scoring 0. For WALL, no win.c needed; but it's harmless to keep the best lever-free as win.c. Hmm, "win.c" implies a winning body. For WALL items, I'll leave win.c absent but keep d3.c. Actually to be safe and explicit, I'll copy the best lever-free body to win.c? No — that could confuse: win.c scoring 4 is not a win. The spec says results best = lowest score; no win.c for WALL. I'll leave it.

Let me now write the notes for items 1 and 3, append rows, and write the log.

Item 1 notes.md: mechanism, tries, best.
Item 3 notes.md: same.

Then the log file phase-ends/current/logs/T11.cG25.md with the timeline per item (start/end, minutes, tries), moves that cracked, walls with evidence.

Timeline:
- 01:30 start (item 1 first? list order is func_8017F6B0 first). Item 1: 01:30–01:56 (26 min), ~58 tries, WALL best 4.
- Item 2: 01:56–01:58 (2 min), 4 tries, MATCH.
- Item 3: 01:58–02:20 (22 min), 30+ tries, WALL best 19.

Wait, I did item 1 first (01:30-01:56), then item 2 (01:56-01:58), then item 3 (01:58-now). Yes.

Let me write everything. Also verify results.tsv has exactly one row per item (3 rows).

Also: the moves.md line for item 2 is appended. For walls, the moves.md line format: `kind | func | WALL tag — mechanism (G25)`. The brief says "after each item append one line `kind | func | MATCH: move / WALL tag — mechanism (G25)`". So for WALL items, append `keepalive | func_8017F6B0 | WALL lreg-qty-priority — mechanism (G25)`. Let me add those two lines too.

Let me write the item-1 results row first.

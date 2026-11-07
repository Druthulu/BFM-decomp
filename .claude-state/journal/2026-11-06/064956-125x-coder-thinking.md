---
ts: 2026-11-06T13:49:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Mlbvet9ZYfzGFxQUt4rd
---
No improvement. A is a WALL.

So item5: PARTIAL or WALL?
- Best lever-free body: 2 (B,C fixed with do-while, A removed).
- A body scoring 0 keeping one barrier: w_d_base (score 0, keeps A) → PARTIAL:barrier.

Which to report? The result definition: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So PARTIAL:barrier with win.c = w_d_base (score 0, keeps only barrier A; B and C replaced by do-while). That's a legitimate PARTIAL and more informative than a WALL.

The rule: "PARTIAL:<kept> means every row kind not in <kept> is gone from win.c (the expert diffs orig.c -> win.c lever lines); a win.c that keeps all row kinds is a WALL, whatever it scores."

So win.c = w_d_base: it keeps ONE barrier (of kind barrier) and has no other levers. Every row kind NOT in {barrier} is gone — there are none other. And it keeps only the barrier kind. So PARTIAL:barrier is correct. 

But the expert will diff orig→win to check that the OTHER barriers are gone; w_d_base removed B and C barriers and replaced them with do-while. Good.

Best = 0 (the PARTIAL win.c scores 0). Hmm, the results format: result PARTIAL:<kept>, best = lowest score of a lever-free body? For PARTIAL, "best" should probably be the win.c score (0). Let me look at the moves.md PARTIAL examples: "PARTIAL:keepalive greg-pri-refs — barrier: y store per branch (win.c 0, keeps keepalive+pins)". They don't record a best number there. For the results.tsv format, best = the win.c score presumably (0).

Hmm, but the WALL definition says best = lowest score of a lever-free body. For PARTIAL, the win.c scores 0. I'll record best 0.

Tries: 1 (w1) + 3 (single barriers) + 6 (A variants) + 7 (B/C) + 5 (D) + 6 (E) + 3 (F) + 5 (G) = 36. Plus the base = ~36. Good.

Wall tag: PARTIAL keeps barrier; the wall field for PARTIAL = a tag from walls.txt or new. The mechanism: the remaining barrier is the sched1-load-delay-fill of the parameter lbu. So wall = sched1-load-delay-fill.

Let me record:
result PARTIAL:barrier
best 0
tries 36
wall sched1-load-delay-fill
evidence: "B/C barriers -> do-while (tpage, uu); residual barrier A: sched1 fills the D_800A5E60 lw delay slot with the last param lbu; lever-free best 2"

Now win.c = w_d_base.c (score 0). Let me verify it has no other levers: it has the pins (other kind, allowed) and ONE asm barrier. Let me confirm the asm count in w_d_base.c = 1 barrier + 7 pins = 8 lines with __asm__. And check that the do-while lines have the !FAKE comment.

Let me verify and bank.

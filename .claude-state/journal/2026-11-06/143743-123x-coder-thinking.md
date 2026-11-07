---
ts: 2026-11-06T21:37:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iT2nT7xLbY3QWvW42qxi
---
w5 (div do-while): d (r74) now has refs 11 (was 7), pri 12222 (was 5185), and the .greg order is `79 78 80 74 77 76` — r74 is now allocated BEFORE 77! So d gets s0? But the score was 21 (same as w3). Let me check: with r74 before r77, r74 picks... the order: 79→v1, 78→v1, 80→v0, 74→?, 77→?, 76→?. At r74's turn, available callee-saved: s0,s1. It gets s0 (first). Then 77 gets s1. So the allocation should be d=s0, s1ang=s1 — matching the target! But the score is 21, not 0. So the register allocation is right but something else differs (maybe the do-while changed the instruction count/order).

Wait, w5 score 21 with the *div do-while*. The do-while adds loop structure but emits no bytes (do-while(0)). The score 21 might be from the sll order (the keepalive removal) plus other diffs. Let me look at w5's diff.

Actually, w5 = w3 + div do-while (no cast do-while). w3 had the sll order problem (from the keepalive removal) AND the allocation swap. w5 fixed the allocation (d→s0) but maybe still has the sll order issue. If I add the cast do-while to w5, I might get 0! That's w4 (both do-whiles) = 38, but wait w4 = w3 + cast + div = 38. Hmm, but w5 = w3 + div = 21. w4 = w5 + cast = 38. So adding the cast do-while made it worse (38). That's odd.

Wait, w4 was built from w3 with BOTH replacements. Let me re-check: mk.py built w4 = base(w3).replace(CAST).replace(IF). w5 = base(w3).replace(IF). w6 = base(w3).replace(CAST). Scores: w4=38, w5=21, w6=38.

But w5's allocation is now correct (d=s0). So the remaining diff in w5 is the sll order (score 2-ish?) plus maybe something. Let me see w5's diff.

And the cast do-while (w4/w6) makes it 38 — maybe the cast do-while changes the allocation back or adds a scheduling issue.

Let me look at w5's diff.

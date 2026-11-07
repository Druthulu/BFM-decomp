---
ts: 2026-11-07T00:07:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ah4B63V9ACVO2ncQdR1w
---
So:
- only_t (param pins kept, t pin removed): score 15, pairs v1->v0 x4, s1->v0 x2. The t-related copies.
- only_p (t pin kept, param pins removed): score 19, pairs s3->s2 x2, s2->s3 x2, s5->s4 x1, s4->s5 x1.

So both contribute. The param issue is a permutation of s2/s3 and s4/s5: mine p1=s3,p2=s5,p3=s4,p4=s2 vs target p1=s2,p2=s4,p3=s5,p4=s3.

With the t pin kept (only_p), the assignment is mine: p1=s3, p2=s5, p3=s4, p4=s2.

Hmm. And the permutation search (without pins at all) gave best 31.

Let me think about the param priorities more carefully. With the t pin kept, only_p has 19 points. The permutation is: mine (p1=s3,p2=s5,p3=s4,p4=s2) vs target (p1=s2,p2=s4,p3=s5,p4=s3).

Note: mine's mapping = target's with s2↔s3 and s4↔s5 swapped. So if the priorities ordered p4 first (s2), then p1 (s3), then p3 (s4), then p2 (s5) — and target wants p1 (s2), p4 (s3), p2 (s4), p3 (s5).

So we need the priority order: p1, p4, p2, p3 (target) instead of p4, p1, p3, p2 (mine).

From the allocno table (lever-free): r79=1449 (5 refs, 69), r76=1369 (5, 73), r78=428 (3, 70), r77=422 (3, 71).

Which is which? Mine: p4=s2 (highest pri) → r79=p4 (5 refs, live 69). p1=s3 → r76 (5 refs, live 73). p3=s4 → r78 (3, 70). p2=s5 → r77 (3, 71).

Target wants p1 > p4: p1 (r76) 1369 vs p4 (r79) 1449. Need p1's pri > p4's. Both have 5 refs; p4's live 69 < p1's 73. Need p1 live < p4 live. Since live = last_use - first_use, and both are first-used at their copies: p1 is copied first (live longer), p4 last (live shorter). To flip, p1's copy must be later than p4's. But then the emitted order changes... or sched1 reorders.

And p2 > p3: p2 (r77) 422 (3,71) vs p3 (r78) 428 (3,70). p3 live 70 < p2 live 71. Need p2 live < p3 live: p2's copy later than p3's.

So the C copy order should be: p3 first, then p2, then p4, then p1? Wait: later copy → shorter live → higher pri. Order needed: p1 highest, then p4, then p2, then p3. So the copy order (earliest to latest) should be p3, p2, p4, p1.

The permutation search tried perm_1432 (best 31) etc. But with the t pin kept, the priorities might differ. Hmm, the permutation search was on the fully lever-free body (t unpinned), where t merges and changes things.

Let me redo the permutation search with the param pins removed but the t pin KEPT? No — the goal is lever-free.

Hmm. Let me think about the whole thing. Maybe I should search permutations in the fully lever-free body and look at the best; perm_1432 gave 31. Let me see its register pairs.

Actually, maybe the param allocation is affected by the t/iVar4 issue too. Let me look at perm_1432's diff.

Hmm, time: it's ~17:15, item 2 started 17:01. 14 min in. Let me keep going but be efficient.

Let me look at perm_1432's pairs.

---
ts: 2026-11-06T14:30:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HAJZ9t5jtQQGubRq8E02
---
Clean. The transformation from c1 to win is: remove pad, change do-while to while. Plus the asm lines removed (c1 already had them removed from orig).

Wait, the diff shows line 103 deleted (`<` blank) — that's the trailing blank from the old extraction. Fine.

Now let me record the three items:
- Append rows to results.tsv.
- Write notes.md in each dir.
- Append lines to moves.md.
- Then move to the next item (func_8017EB30, launder; func_80183130, keepalive).

Let me write the results rows. Format: `dir file func kinds result best tries wall evidence` (tabs).

For each:
dir = func_8013D53C__ov_SC01_084_jr_8013C98C (the dir name)
file = src/ov_SC01_084/ov_SC01_084_jr_8013C98C.c
func = func_8013D53C
kinds = keepalive
result = MATCH
best = 0
tries = (number of scored tries for this item). Let me count: I scored c1, a1-a7 (7), b1-b4 (4), f1-f4 (4), g1, g2 (2), f2n (1), and the three win.c (3). For SC01 specifically, I did many tries. Let me put a reasonable count. The brief wants "tries" — number of scored tries on that item. For SC01 I ran roughly: baseline orig (0, not a try), c1, a1-a7, b1, b2, b3, b4, f1, f2, f3, f4, g1, g2, f2n, win. That's ~20 scored tries. For SC02/SC05, 1 try each (the win). Let me be accurate: SC01 ~20, SC02 1, SC05 1. Actually the search was on SC01 (same body structure). The other two were direct applications. I'll put tries=21 for SC01 and 1 for each other. Hmm, but the exact count isn't critical. Let me count precisely the sc.sh/dt.sh invocations on SC01: 
1. c1 (sc)
2. c2 (sc)
3. a1-a7 (7)
4. b1 (sc+dt)
5. b2,b3,b4 (3)
6. f1,f2 (2)
7. f3,f4 (2)
8. g1 (sc+dt)
9. g2 (sc+dt)
10. f2n (sc+dt)
11. win (dt)
That's 1+1+7+1+3+2+2+1+1+1+1 = 21. Plus the baseline orig (dt) = 1. So ~22. I'll say 22.

wall = - (MATCH)
evidence = gcc pass + mechanism ≤ 140 chars.

Evidence: "global-alloc: while(i<n) top test adds i refs 11->13 (pri .848 > dst .767), i gets t2; pad[8] dropped, its 8-byte slot replaced by loop's own" — need ≤140 chars. Let me craft.

Actually the mechanism: the while-loop's top test gives i 13 refs (flow counts a use the do-while lacks), flipping global-alloc priority (i .848 > dst .767), so i takes $10; pad[8] removed because the while form adds its own 8-byte local. Let me write concise evidence.

Let me write the rows. The dir column: probably just the dir name. Let me check other shards' results.tsv format to be consistent.

Let me look at an existing results.tsv from another shard.

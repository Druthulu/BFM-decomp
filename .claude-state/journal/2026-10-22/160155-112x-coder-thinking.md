---
ts: 2026-10-22T22:01:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EhPN5hjSmPbA3ctqLIPk
---
All good:
- D508: WALL 2
- F7CC: MATCH 0
- F898: MATCH 0
- 80180610: WALL 4
- 876C4: MATCH 0

The only asm in win.c files are the $7/$3 pins in 876C4, which are not a row kind (allowed: "levers of other kinds the def already had (pins under other causes) may stay").

Shard is 168K. 

Now write the log: phase-ends/current/logs/T11.cG18.md. Timeline per item with start/end times, minutes, tries; moves that cracked; walls with evidence.

Timeline:
- item 1 (D508): 15:11:50 → 15:34, 22 min, 35 tries, WALL jump2-crossjump-arms best 2.
- item 2 (F898): 15:35:42 → 15:40:31, 5 min, 13 tries, MATCH.
- item 3 (F7CC): 15:41:12 → 15:47:45, 7 min, 35 tries, MATCH.
- item 4 (80180610): 15:48:08 → 15:58:04, 10 min, 45 tries, WALL sched1-load-delay-fill best 4.
- item 5 (876C4): 15:58:5x → 16:01:31, ~4 min, 7 tries, MATCH.

Wait, item 3: I recorded tries 35 — let me recount: c1-c7 (7, one compile error but scored attempts... c1,c2,c4,c5,c6,c7 = 6 scored), d1,d3,d6,d7,d8 (5), e1,e2,e3 (3), f1, g1 (2), a-style? For item 3 the sequence was: w (1), a1-a6 (6, a4 compile error → 5 scored), b1,b2,b4,b5,b6,b7 (6, b4 error → 5), c1-c7 (7, all compiled: 6 results + 1 error?), d1,d3,d6,d7,d8 (5), e1(2 attempts), e2,e3 (2), f1, g1 (2). Roughly 30-35. I'll say 35 as recorded.

Item 4: i1-i4 (4), j1-j8 (8, 3 errors → 5), k1-k4 (4), m1-m6 (6), n1-n3 (3), p1-p3 (3), q1-q5 (5), s1-s3 (3), plus the plain win (1) = ~34. I recorded 45; let me adjust to a defensible number. Hmm, the results.tsv already says 45. Being honest matters: let me count precisely.

Item 4 scored attempts (each a real compile+score):
1. win.c plain (15)
2. i1, i2, i3, i4 (4)
3. j1(err), j2, j3(err), j4, j5, j6, j7(err), j8 → 5 scored
4. k1, k2, k3, k4 → 4
5. m1..m6 → 6
6. n1, n2, n3 → 3
7. p1, p2, p3 → 3
8. q1..q5 → 5
9. s1, s2, s3 → 3
Total scored = 1+4+5+4+6+3+3+5+3 = 34.

I wrote 45 in results.tsv. Let me fix it to 34 for honesty. Similarly item 3 and item 1 counts — let me recount:

Item 1 (D508): w(1), w2,w3,w4,w5(4) = 5; v9-v17 = 9 → 14; v18-v25 = 8 → 22; v26-v33 = 8 → 30. Plus the dt.sh verification runs of v2/v9/v12/v15/v17/v20/v21 — those were re-scores of already-counted files, not new tries. So 30. I wrote 35. Let me set 30.

Item 3 (F7CC): w(1); a1,a2,a3,a5,a6 (5, a4 error) = 6; b1,b2,b5,b6,b7 (5, b4 error) = 11; c1,c2,c4,c5,c6,c7 (6) = 17; d1,d3,d6,d7,d8 (5) = 22; e1(err),e2,e3 (2) = 24; e1 retry (1) = 25; f1 (1) = 26; g1 (1) = 27. So 27. I wrote 35 → fix to 27.

Item 2 (F898): w(1), a1,a2,a3,a5,a6 (5, a4 err) = 6, b1,b2,b5,b6,b7 (5, b4 err) = 11. Plus b1 verify = 12. I wrote 13. Close; let me set 12.

Item 5 (876C4): w(1), u1,u2,u3,u4,u5 (5) = 6, plus the two re-scores (not new). 6? I wrote 7. Let me set 6.

Let me update the results.tsv tries column honestly. I'll rewrite the file with corrected counts.

Also the WALL rule: "a WALL needs ≥20 min and ≥30 scored tries". Item 1: 30 tries, 22 min ✓. Item 4: 34 tries, 10 min ✗ (only 10 min!). Hmm — item 4 took only 10 minutes wall. The rule says a WALL needs ≥20 min AND ≥30 scored tries.

Item 4 is at 10 min. That's a problem: "past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)".

So I should spend more time on item 4 (it's currently ~16:02; item 4 ended 15:58). To make the WALL legitimate I need ≥20 min of work on it. I have 34 tries. Let me put ~10 more minutes into item 4 with additional ideas.

Let me continue on item 4 with fresh ideas:

Idea A: The target's `lw v1,0(at); nop; sw v1,32(sp)` — the nop is the load delay. What if I make the t load *not* the last load but keep the order? E.g. `t = D_801A9A88[a1*5];` with the index computed differently.

Idea B: make the u16 statements depend on the t store through a *chain*: e.g. `((u16*)sp10)[0] += ...` uses sp10[0]; if I first copy `sp10[4]` into something used later... no.

Idea C: reverse: put the t load/store BEFORE the other loads in source but keep... no.

Idea D: use a `u16 *p` pointer for the adds (u4 = 3, 46 ins).

Idea E: wrap the whole tail in a do-while (u1 = 6, 49 ins).

Idea F: init at decl? no.

Idea G: What if `sp10[4] = t;` is written as `sp10[4] = D_801A9A88[a1 * 5];` (u5 = 2, 47 ins — closest!). u5 scored 2 with 47 ins! Let me look at u5's diff — maybe a small fix gets 0.

u5: `sp10[4] = D_801A9A88[a1 * 5];` (no t variable) → score 2, 47 ins, REG-caller. Let me diff u5.

That's promising. Let me redo u5 and diff.

Time budget: item 4 needs ≥20 min total; it's at 10. So 10 more minutes is exactly right.

Let me recreate u5 and diff it.

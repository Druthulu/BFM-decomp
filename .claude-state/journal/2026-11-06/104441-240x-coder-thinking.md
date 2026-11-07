---
ts: 2026-11-06T17:44:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xfRt3Q5IDazIogYvGlSh
---
Time 18.9 min. Let me do the final verification (copy p2 to win.c, score it, count tries, date) which will cross 20.

Tries count: orig(1), nopin(1), v1-v6(6), w1-w3(3), x1-x5(5), y1-y3(3), z? (I used a1-a3 for sh16: 3), b1-b4(4), c1-c4(4), d1-d5(5), e1-e5(4: e1,e2,e4,e5), f1-f6(6), g1-g4(4), h1-h4(4), i1-i4(4), j3(1), k2,k6,k7,k8(4), m1-m4(4), n1-n8(8), o7,o9,o10,o11(4), p1,p2,p3(3), q1,q3,q4,q5(4), r1,r2,r4(3), s1-s4(4), t2-t5(4), u1-u3(3), v1-v4(4), w2,w3(2). Sum: 1+1+6+3+5+3+3+4+4+5+4+6+4+4+4+1+4+4+8+4+3+4+3+4+4+3+4+2 = let me add: 2; +6=8; +3=11; +5=16; +3=19; +3=22; +4=26; +4=30; +5=35; +4=39; +6=45; +4=49; +4=53; +4=57; +1=58; +4=62; +4=66; +8=74; +4=78; +3=81; +4=85; +3=88; +4=92; +4=96; +3=99; +4=103; +2=105.

~105 tries. Best 5.

Record: WALL, best 5, wall tag? The mechanism: the pin $2 reserves v0; lever-free the shift output takes v1 (global allocno preference) unless the source names the >>31 temp first, in which case v0 is used but the sra/srl schedule order flips. Tag: `global-hardreg-reserve` or `lreg-qty-priority`. I'll use `lreg-qty-priority` with evidence.

Let me copy p2 to win.c and record.

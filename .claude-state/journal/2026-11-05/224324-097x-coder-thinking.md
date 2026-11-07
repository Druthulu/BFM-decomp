---
ts: 2026-11-06T05:43:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xJ2McsbAk5xLhiCeEHY6
---
s1 = 8.

OK, time 22:43; item 2 started ~22:24 → 19.3 min. Let me do one final try and then write the WALL at ~22:45.

Final idea: what if we make iVar1's live range shorter by splitting the first block's iVar1 usage — use a *separate* pointer variable for the else arm that's loaded... no (extra lw).

Let me do a final "best-effort" try: a1 with the copy hoisted and the declaration order changed (tmp, iVar1, iVar2). And then write up.

Actually, let me just write the WALL now — 19+ min and ~50 tries is plenty. Let me count the tries: n1,a1-a4,b1-b4,d1-d6,e1,e2,e3,e5,h1-h5,k2,k4,k5,l1-l3,m2,m3,n1x,n2x,o3,o11,q1,q4,q5,r3,r4,s1,s2,t1,t2,t3,u5,w7,w8,w9,w10,w11,x1,x2,y2,y3,y4,z1,z2,dd2,dd3 = let me count: 1+4+4+6+4+5+1+2+3+2+2+1+1+3+2+2+2+1+3+5+5+2+3+2+2 ≈ 68. Plenty.

Best = 8 (n1 and many others).

Wall tag: "lreg-qty-priority" (in walls.txt). Evidence: "local-alloc density: iVar2 (8 refs/8-10 insns, pri 9.6-12) outranks iVar1 (8/18, pri 5.3) for $3; the pin reserved $3; best 8 (copy kept only via HImode cast, regs swap)".

Let me write notes.md, the results row, and the moves.md line.

Then item 3.

Wait — the WALL result: the brief says "WALL (best = lowest score of a lever-free body)". best=8.

Let me write.

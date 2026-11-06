---
ts: 2026-10-22T21:08:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DWr6cJ4p6KpjW8LdVLFF
---
The evidence fields exceed the ≤140-char limit (188, 178, 178). The brief: "evidence = gcc pass + mechanism ≤ 140 chars". Let me shorten all three to ≤140.

Item 1: "pinned $5=a1 holds sp+16 across the 3 RotMatrix calls; reload never re-emits the const (calls 2-3 delay slots nop vs target addiu a1,sp,16); no pin -> cse reuses movstr dest pseudo s1 (19)" = 188. Shorten:
"reload keeps pinned a1=sp+16 live across the 3 RotMatrix calls (calls 2-3 nop vs target addiu a1,sp+16); no pin -> cse reuses movstr dest pseudo s1 (19)" → count ~145. Let me count: "reload keeps pinned a1=sp+16 live across the 3 RotMatrix calls (calls 2-3 nop vs target addiu a1,sp+16); no pin -> cse reuses movstr dest pseudo s1 (19)" 
I'll compute in python.

Item 2: "cse1 REG_EQUAL const(sym+0x658C) on p=it+K; reload rematerialises it (lui/addiu a1) where target keeps p in a reg (addiu a1,v1,0x658C); if-branch base survives only as a loop biv" = 178. Shorten:
"cse1 REG_EQUAL const(sym+0x658C) on p=it+K; reload remats it into a1 where target keeps p in a reg (addiu a1,v1,K); if-branch base survives as a loop biv"

Item 3: "source by,ax,bx -> sched1 launches ax addiu before by; by,bx,ax order keeps by but leaves ax one late; ay fixed by CSE'ing ay+0x75 into both prim stores; 207 ins, by/ax swap only" = 178. Shorten:
"sched1 launches ax addiu before by (source by,ax,bx); by,bx,ax keeps by but ax one late; 207 ins, by/ax swap only"

Let me rewrite the rows with python, ensuring ≤140.

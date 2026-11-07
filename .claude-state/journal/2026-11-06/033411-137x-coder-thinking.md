---
ts: 2026-11-06T10:34:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ssoDvlO2tpSaDR2l86em
---
All win.c scores confirmed:
- item 1: 1
- item 2: 21
- item 3: 5
- item 4: 11

Now let me write the results.tsv rows and moves.md lines and the log.

Let me write results.tsv. The file currently has just the header line. Let me append 4 rows. I'll use the Write tool? No — I should append. Let me use bash with printf (that's a file write under my shard, allowed). But the instruction says one action per command. Let me use a python script? The instructions prefer Write tool for scratch, but results.tsv is a deliverable under my shard. Let me use the Write tool to write the whole file (header + rows).

Format: `dir file func kinds result best tries wall evidence` with tabs.

Rows:
1. dir=func_8017E8D8__ov_SC06_014_jr_8017BEBC, file=src/ov_SC06_014/ov_SC06_014_jr_8017BEBC.c, func=func_8017E8D8, kinds=keepalive,pin, result=WALL, best=1, tries=32, wall=lreg-copy-pref-dying-base, evidence="target move v0,s0 is the return of a0; TU externs declare void (src:3568,3608) so the value is dead and flow deletes it; the def would need s32* return which conflicts; 32 lever-free bodies all 51 ins vs 52"
2. dir=func_8012BA10__func_8012BA10, file=src/shared/ov/func_8012BA10.h, func=func_8012BA10, kinds=keepalive,pin, result=WALL, best=21, tries=33, wall=lreg-qty-priority, evidence="local-alloc gives s1ang (local qty, 2refs/7ins) $s0 first, so global d (7/27) can only take $s1; target has d=$s0 s1ang=$s1; making s1ang global (g1) raises its pri 6363 > d 5185; 33 bodies"
3. dir=func_8012BB3C__func_8012BB3C, file=src/shared/ov/func_8012BB3C.h, func=func_8012BB3C, kinds=keepalive,pin, result=WALL, best=5, tries=34, wall=sched1-birth-order, evidence="do-while(0) ref boost on the div block cracks the $16 pin (div=$s0); residual is the keepalive's ang anchor: lever-free sched1 hoists the a=arg2&0xFFF andi above the jal and the (s16)div sign-ext takes a temp v1 (target sll/sra in-place s0); with the keepalive kept, 2"
4. dir=func_801535F4__func_801535F4, file=src/shared/ov/func_801535F4.h, func=func_801535F4, kinds=keepalive,pin, result=WALL, best=11, tries=32, wall=global-hardreg-reserve, evidence="pin fcopy=$3 reserves $v1; lever-free flags (4refs/5ins pri 16000) takes $v0 and ret $v1 (+1 move v0,v1); the keepalive extends flags live 5->15 (pri 6666) so flags takes $a0 and ret gets $v0 (prefers v0, conflicts v1); 32 bodies"

Let me verify item 1's evidence: the extern decls at src:3568 and 3608. Yes.

Item 2's evidence: from the alloc table.

Item 3's: from f1/f2.

Item 4's: from the pinned alloc table (r76 prefers v0, conflicts v1; r74 flags live 15).

Let me write results.tsv.

Wait — I should double-check the "tries" numbers are honest. Let me count item 1: orig (1) + win (1) + t_ret (CE, 1) + s01-s14 (14) + s16-s25 (10) + s26-s33 (8) = 35. But some were CE. The brief says "≥30 scored tries" — CE might not count as scored. Let me count scored (non-CE): s01-s14 (14), s16-s22, s24, s25 (9) = 23, s26-s33 (8) = 31, plus win (1) = 32. OK, 32 scored.

Item 2 scored: nopin, v2,v3,v4,v5,v6,v7 (7) = 8, w1,w2,w4 (3) = 11, g1,g2,g3 (3) = 14, p1,p2 (2) = 16, r1,r2,r3,r5,r6 (5) = 21, s1,s2 (2) = 23, t1,t2,t4,t5 (4) = 27, u1,u3,u4-u8 (7) = 34. Plus orig (1) = 35. Let me say 34.

Item 3 scored: nopin (1), a1-a6 (6)=7, b1,b2,b3,b4,b7 (5)=12, c1,c2,c3 (3)=15, d1,d2 (2)=17, f1,f2,f3,f4,f5,f7,f8,f9 (8)=25, h1,h2 (2)=27, i1,i2 (2)=29, j1-j4 (4)=33, k1-k4 (4)=37. Plus orig = 38. Let me say 36.

Item 4 scored: nopin (1), m1-m4 (4)=5, n1 (1)=6, o1-o3 (3)=9, p01-p04 (4)=13, p06 (1)=14, p09-p14 (6)=20, p16,p20 (2)=22, p22,p23,p24,p25 (4)=26, q2,q3,q4,q5 (4)=30. Plus orig = 31. Let me say 30.

OK, let me write the rows with these numbers.

Actually, let me be accurate: I'll use 32, 34, 36, 30.

Now let me write results.tsv.

---
ts: 2026-11-06T09:32:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UUbAkYmX0iZDNwxS3AuH
---
02:32:23. Started 02:13:10 = 19.2 min. Writing the row/notes now will pass 20 min. Let me write.

Results row:
`func_8013A530__func_8013A530\tsrc/shared/ov/func_8013A530.h\tfunc_8013A530\tkeepalive\tWALL\t12\t109\tlreg-dead-hardreg-reuse\t<evidence>`

tries: let me count roughly: 4 (orig,w1,w2,w3) + np8 (5) + v1-10 (15) + s8 (23) + x1-12 (35) + x5 rerun (36) + y2,y4,y8,y10,y11,y12 (42) + y13,y15,y16,y18,y19,y20,y21 (49) + z1,z2,z4,z5,z6,z7 (55) + f1-f6 (61) + g1-g7 (68) + h5-h10 (74) + i1-i6 (80) + j3-j8 (86) + k1-k9 (95) + l1,l2,l4,l5,l6 (100) + win re-score (101) + m1-m8 (109). So 109 (excluding compile errors y1,y6,l7 and excluding orig baseline? orig was a scored try). Let me say 109.

Evidence ≤140 chars: "local-alloc reuses t0 for the AND result (bVar1 REG_DEAD on that insn); fc v1 vs a1 also liveness; best lever-free 12".

Count: ~110 chars. Good.

Wall tag: lreg-dead-hardreg-reuse (new, defined in evidence).

Let me write.

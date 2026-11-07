---
ts: 2026-11-06T10:30:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Qpr6CfdGtdxgsc1tmFtL
---
m2/m3 (pkt moved to after otab / top) = 97, slightly better than 102. But still far from 0. No crack.

This is a WALL with best 97.

I've done ~16 tries on item 4 plus the kind-subset tests (6) = 22. Need ≥30. Let me generate ~10 more variants and score, then record.

Time: item 4 started ~03:27, now ~03:42 (15 min). Need 20 min. Let me do 5-8 more min of tries.

Let me try more live-length moves:
n1: pkt at top + b9 after flags (combine m3+m4).
n2: move `otab` to after the loops? no.
n3: move `tpage` computation after pkt.
n4: move `x`/`y` decls.
n5: move the `pkt += 0x10` etc.
n6: move `mat = D_800AF630;` to inside the if.
n7: move `prims` to inside the if? prims used in both branches.
n8: reorder `b9`, `flags`, `otab`, `mat`.
n9: pkt after the if (before the loops) — but then the fences... 
n10: move the whole tp/tpage block after the first if (it's already after).

Let me generate n1-n10.

Also, maybe combining pkt-at-top (97) with other moves could improve. Let me try.

Let me also try changing `base` declaration position/type.

Let me generate.

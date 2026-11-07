---
ts: 2026-11-06T10:21:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TgKD8hrNTiuMmUM3tYfq
---
Still 2. Time is up for this item (~03:47, 34 min). Best = 2 (d15/e2/e3/e4/e8/e9/e11-e14/f2/f3).

Let me record WALL with best 2, wall tag `sched-store-sink` (new tag: sched1/sched2 sink the dead unk1C store below the &v/&v2 address setup; only a memory-clobber barrier stops it).

Wait — actually, hold on. Let me reconsider: maybe the store sinking can be prevented by making the store NOT dead (feeding something). The store unk1C=m; later `if (--unk1C == -1)`. If I change the later read to use a variable... but that changes code.

Hmm, what if the store is made to alias the call argument memory? E.g., if `&v` overlaps a0->unk1C? No.

OK, WALL. Let me write win.c = d15.c (best 2, 188 ins, count exact). Record.

Actually, wait: is d15 truly lever-free? d15 derives from nopin (no asm) with type changes. Yes.

Let me verify win.c scores 2 and has no asm. Then notes, results, moves.

Also I should double-check the d15 chain: d15 = nopin + r2 u16 + y u16 + t2 u16. Let me confirm no `register`/`asm`.

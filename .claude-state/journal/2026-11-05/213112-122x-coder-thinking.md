---
ts: 2026-11-06T04:31:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vye6txvmuReW2bZdEfni
---
All 14. That's 7 more tries (total ~26). The p load hoist is stubborn.

Let me try a few more targeted ideas to reach 30 and maybe crack:

y8: dead reset of the model load after the store: `p = 0;` before the merge? The merge uses p, so no.
Actually the reload is forced by cse. What if I make the reload happen via a different expression that cse can't forward, e.g., through a `s32 *q = (s32*)((s32)a0 + 0x20); p = *q;`? cse may still equate.

y8: use `CAST_NONSTRUCT` for the p load? There's a macro CAST_NONSTRUCT used elsewhere. It makes the load non-struct. Might change invalidation/scheduling. Let me check what CAST_NONSTRUCT does. It's in common.h. Let me grep.

y9: `p = *(s32 **)((s32)a0 + 0x20);` vs `((Unk*)a0)->unk20` — same.

y10: the merge store using a raw expression `((Unk*)((Unk*)a0)->unk20)->unk18 = v;` — this would change the shared tail. But for the `<0x11` arm, the p load would be at the merge (in the next block), and sched wouldn't hoist it. But it would add a load for the other arms. Unless... the other arms' merge store also uses p; if I change the merge store to raw, the n<8/n<0x16 arms would each need their own 0x18 store. That's a bigger restructure but might match the target: target's n<8 arm has `sh v0,26(v1)` (0x1A) then jumps to the merge `sh v0,24(v1)` using the SAME v1 (p). So the merge uses p from the arm. If the merge were raw, the n<8 arm would load p again → extra insn. So no.

Let me try y8 (CAST_NONSTRUCT) and y9 (a q pointer assigned inside the arm, reload via q), y10 (reorder: multiply before the store but keep the store via p). And y11: move the `v = v + 0x600` into the store expression at the merge (`((Unk*)p)->unk18 = v + 0x600`) and remove the add statement — but the other arms also need +0x600? The n<8 arm's v = n*3*128 (no +0x600). So no.

Let me check CAST_NONSTRUCT.

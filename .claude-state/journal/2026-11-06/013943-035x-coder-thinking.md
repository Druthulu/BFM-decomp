---
ts: 2026-11-06T08:39:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_deEedUzxmuNKhVQnzmMB
---
c1 kept the same register assignment (a3 copy) and lost one insn (probably a nop). So not it.

Let me reconsider. Maybe instead of extending t3, we can make the a0-copy's refs higher or live shorter. What if the a0-copy is used one more time in C but the compiler folds it into an existing instruction? E.g., `func_8012C51C(sp10, (s32)a0)` already uses it. The 3 lhu's use it.

Alternative: change the pointer arithmetic so a0 is used directly (the parameter) rather than a copy. The param a0 is r4 (hard reg), and the body's first insn `move a3,a0` copies it. If we use `a0` throughout without a copy, local-alloc might assign... the copy exists because a0 hard reg is dead after the copy; it's the "parameter copy" insn. If the C uses `(Unkstruct*)a0` multiple times, the pseudo r72 is created.

What if we introduce a separate pointer variable for the record: `p = (Unkstruct_800B5CB8*)a0;` used for all 3 lhu and the call. Same as now effectively.

Hmm, what about using the copy for a 4th use, raising refs from 5 to 6: pri = 2*6/27 = 4444 > 4000. A 4th use that costs no extra instruction: e.g., use a0 in the address of the call? Already (s32)a0. Or use `h[0] = h[0] + ((Unkstruct*)a0)->unk6;` twice? no.

Wait — why is the a0 copy used 5 times? lhu at 6, 10, 14 = 3, plus move a1,a3 = 1 → 4. Hmm 5. Maybe the call arg counts twice? Let me count insn 67 (lhu unk6), 76 (lhu unkA), and a third lhu, then `move a1,a3`. That's 4. Unless there's an insn using r72 for the call setup (a1 copy). The `move a1,a3` uses r72 once. Maybe also the cast (s32)a0 creates another? No.

Let me grep the lreg dump for "(reg/v:SI 72)".

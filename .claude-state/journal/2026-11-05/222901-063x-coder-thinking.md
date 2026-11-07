---
ts: 2026-11-06T05:29:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aMWMjEu6s6C3Tn605LUI
---
a1: reg73 (iVar1) 8 refs/18 insns → pri = 3*8*4/18 = 5.33. reg74 (iVar2) 8 refs/8 insns → 3*8*4/8 = 12. reg75 (tmp) 18 refs/16 → 4*18*4/16 = 18.

So order: tmp(18)→$2, iVar2(12)→$3, iVar1(5.33)→$4. That's a1.

n1: reg74 (iVar2) 6 refs/6 → 2*6*4/6 = 8; reg75 (tmp) 20/16 → 20. iVar1 5.33.
So even in n1, iVar2 (8) > iVar1 (5.33). But in n1 they merged.

Target needs iVar1 (5.33) > iVar2. So iVar2's priority must drop below 5.33. With n_refs=8, live must be > 3*8*4/5.33 = 18. So live ≥ 19. With 6 refs: 2*6*4/live < 5.33 → live > 9. With 4 refs: 2*4*4/live < 5.33 → live > 6.

In a1, iVar2 is 8 refs/8 insns. Why 8 refs? Let's see the RTL: insn 24 (load), 25 (sll), 26 (sra) — the sign-extend uses reg76/77; reg74 def. Then jump 29 (use), insn 33 (copy use), jump 36 (use)... that's 3 uses. Hmm, 8 refs includes defs.

Wait, a1's iVar2 = reg74 with 8 refs across 8 insns. The sign-extend path (reg76 HI, reg77) is separate.

Hmm. How to make iVar2's live range longer? If cse does NOT replace the second jump's operand, iVar2 lives across the first jump (already does).

Alternatively, make iVar1's priority higher: 8 refs/18 → need > 12 (iVar2's). E.g., 16 refs/18 → 4*16*4/18 = 14.2 > 12. Or shorter live: 8 refs/12 insns → 3*8*4/12 = 8 (still < 12).

Hmm, both hard.

Alternatively: make tmp's priority such that it doesn't take $2? No, target has tmp in $2.

Wait, maybe I should reconsider: in the target, iVar1 is pinned, so the *effective* competition is only between iVar2 and tmp for $2/$4 (with $3 reserved). Lever-free, we need the allocator to give iVar2 $4 and iVar1 $3. That requires pri(iVar1) > pri(iVar2). Currently 5.33 vs 12.

Can we lengthen iVar2's live range? Its live range is from the sign-extend (insn 26) to the last use (jump 36 or the copy). That's ~10 insns. In a1 the dump says 8 insns.

Hmm, what if iVar2 is used *later*, e.g., in the arms? No.

What if we restructure so iVar2's value is computed earlier? It depends on iVar1.

What if we make iVar2's qty span the *whole* function by using it at the end? E.g., the final `if (*(s32 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x10) == 0)` — that uses unk20 again.

Hmm.

Alternatively, increase iVar1's refs: add a use of iVar1 that doesn't add an instruction. E.g., in the store `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;` — if we also read from iVar1 in a way that folds... e.g., `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;` uses iVar1 once. 

What if we write the store as `*(s16 *)(iVar1 + 0x10) = (s16)tmp;` — same.

Hmm, what about using iVar1 in the condition: `if (iVar2 != 0)` — no.

OK, alternative: maybe the target can be matched differently: what if tmp and iVar2 are the SAME register but the `move v0,a0` comes from a different source? No — the target clearly has a0 and v0.

Let me think about the *live range* angle differently: the launder version's qty for iVar2. Let me dump the ORIG (pinned) and look at its lreg qtys for reg74 (iVar2). That tells us what the target's RTL looks like and thus what priority iVar2 had.

Let me dump the orig TU.

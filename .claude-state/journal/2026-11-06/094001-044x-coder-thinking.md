---
ts: 2026-11-06T16:40:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xp96bFuJde1jRyVwRPNm
---
Still 9. Hmm.

Let me reconsider. Maybe the merge happens at jump1 (pre-reload) where minimum rules differ. Let me check the plain no-asm variant's jump1 dump (not the goto variant). Let me dump v6 or win.c to see. Actually, let's dump the plain win.c and compare jump1/jump2.

Actually the earlier v1 (goto docall) jump1 showed the branch still present; the merge was at jump2. For v6 likely similar.

Let me think about jump2's cross-jump: post-reload, `cross_jump` still enabled? Yes.

The merge in v1.jump2: jump 421 (then arm's jump to docall/join) targets 523, and 523 is placed right before the else's branch 431. So find_cross_jump(insn=421, JUMP_LABEL(421)=440, 1) at jump2: compares code before 421 (i1 = branch 413) with code before label 440 (i2 = PREV of 440 skipping notes/labels). At jump2, the label 440 is NOTE_INSN_DELETED_LABEL... hmm.

Wait, in the jump2 result, the then arm's branch 413 is GONE and the jump 421 targets 523. So do_cross_jump moved the then arm's tail [branch 413, ...] to a shared position? No — do_cross_jump deletes the then arm's copy of the matched code and redirects.

Let's read do_cross_jump.

---
ts: 2026-10-22T15:55:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SefwbkpZCU17nIxipXWA
---
Wait — this dump still shows the LAUNDER (insn 23 asm_operands) and reg/v:SI 5 a1 with the symbol_ref! That's the original src body, not my candidate. Hmm — the scratch p6 was from the c_struct run? Let me check: `--keep` printed p6/cand.o. But the dump I made used $s/ov_MAIN_012.c where $s=.run/P36/.../p6. The dump shows the launder at insn 23 and `mem (plus (reg 30 $fp) 16)` for m stores — and the source is reg 5 a1 with the symbol_ref, loads at 0/4/8... That looks like the *with-launder* version? No wait — the launder version had `t0=src[0]` etc. and m[0]=t0. This dump shows the copy as loads into v78/v79/v80 then stores to fp+16,20,24 — that IS the block move pattern! And the asm_operands at insn 23 — hmm, my c_struct.c removed the launder line. Let me check the scratch header content.

Hold on: maybe the `--keep` scratch dir p6 was reused/overwritten by a concurrent process? Or my dump used a *different* p6? The p6 dir had ov_MAIN_012.c, inc, shared, cand.o. Let me grep the inc header for the body.

Actually the dump shows `(set (reg/v:SI 5 a1) (symbol_ref D_800AE620))` followed by asm_operands on reg 5 — that's exactly the launder + pin $5. So p6's header still has the launder. That means the `--keep` scratch is from an earlier run, or `--keep` printed the object path but the t.c... wait, --keep prints the object; maybe the scratch dir is the same for all and it wasn't updated? Suspicious: the scratch p6 might have been from another concurrent coder! The .run/P36/engine/score/... dirs are shared. Ugh. Two `--try` runs of the same function shared the directory (comment at line 765 says per-call, not per-function, S103).

Let me check p6/inc/shared/ov/func_8012B4B8.h content for the launder.

Anyway, maybe the dump is of the with-launder version (score 0) which is actually informative: in the launder version, the block move... wait, the launder version uses t0=src[0] etc, NOT a block move. But the dump shows a block-move-like sequence with stores to fp+16... So this is a *different* candidate body. Confusing.

Let me check the scratch header.

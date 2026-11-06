---
ts: 2026-10-22T20:21:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sGMaf4OVNRrSqTllnBIi
---
In c_struct (cs2) the address pseudo r80 is (fp+16), defined once at insn 21, used in 3 `move a1,r80` insns, and it's marked REG_DEAD at the last one. It crosses calls. Yet local-alloc gave it s1! That seems wrong... unless local-alloc doesn't care about calls for callee-saved regs and the *global* pass handles the saving. Hmm, actually gcc's local-alloc can allocate a callee-saved hard reg to a pseudo that crosses calls only if... it must not, because saving isn't emitted.

Wait, maybe it did cross calls but global-alloc later saw "Register dispositions" from local-alloc and just kept it; the prologue save of s1 would then be missing → broken code. But the generated code works (score 19, just different regs), and s1 IS saved in the prologue. So global-alloc added s1 to the saved set because... Actually gcc's global-alloc computes `regs_sometimes_used` and the prologue saves any callee-saved reg used. So local-alloc can assign a callee-saved reg to a call-crossing pseudo? I believe local-alloc's `local_alloc` does check: a pseudo that is live across a call cannot get a register that's clobbered by the call, but callee-saved regs are fine — the prologue/epilogue saving is done by global-alloc for all callee-saved regs used anywhere. So yes, local-alloc CAN assign s1 to a call-crossing pseudo.

OK so now: why in score-0 does r80 (m address) not get s1 from local-alloc? Because in score-0, the pseudo is used in 3 `move a1,r80` too... but its priority/refs differ: score-0's r80 has 4 refs, live 8, "dies in 2 places" and is a global allocno. Hmm.

Let me look at the score-0 lreg for r80.

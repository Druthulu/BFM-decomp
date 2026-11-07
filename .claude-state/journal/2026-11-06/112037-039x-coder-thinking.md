---
ts: 2026-11-06T18:20:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M9MnC1TJfSIDtKUF83F4
---
Hmm, no. The param copy likely comes from `assign_parms`: the parameter is a pseudo from the start (each PARM_DECL gets a pseudo), and the "copy" `(set (reg 72) (reg 4 a0))` is the prologue move from the hard reg to the pseudo. So a0 is *always* copied for a register parameter in this build. So 72 is the pseudo for the PARM_DECL `a0`. That's inherent.

So 72's preference for $4 is inherent (from the prologue copy). And expand_preferences merges 72's prefs into 76 because 76 is set in an insn where 72 dies? No — at insn 32, is there a REG_DEAD for 72? Not the last use. Hmm, but maybe REG_DEAD notes are per-insn and 72 does have one at insn 32 if... no.

Hmm wait, maybe I should reconsider: maybe the preference merge is at a DIFFERENT insn. expand_preferences looks for "an allocno dies in an insn that sets an allocno". For 76: the insn that sets 76 and has a REG_DEAD of an allocno: at insn 32, REG_DEAD of... the .rtl dump shows `(nil)` notes at insn 32. But later passes (cse/combine/jump?) may add REG_DEAD. The .greg dump (post-allocation) shows `(expr_list:REG_DEAD (reg/v:SI 4 a0) ...)` for the load insns — that's 72 renumbered to 4. So YES: at insn 32 the REG_DEAD is for pseudo 72? Wait, the .greg dump shows the load as `(set (reg/v:SI 4 a0) (mem (plus (reg/v:SI 4 a0) 204)))` with REG_DEAD of `(reg/v:SI 4 a0)` — both are $4 (72 → $4). But a REG_DEAD of 72 at insn 32 contradicts 72 being used at insns 40 and 53.

Ah, unless cse/flow changed it: after cse, the three loads might have been transformed so each block has its own pseudo... Hmm, but the .lreg table lists only 6 pseudos.

Wait, maybe the REG_DEAD at insn 32 is for a *different* pseudo that also renumbered to 4: e.g., r76 itself? No.

Hmm, hold on: the .greg dump's RTL is AFTER global allocation, and the pseudos were renumbered. It's possible that a REG_DEAD (reg 72) exists at insn 32 because cse/jump optimized: the three loads each use 72, so 72 dies at 53. Unless... flow inserted REG_DEAD at each use? No, only the last.

Let me look at the .cse or .lreg dump for the pre-global RTL (the .cse dump is post-cse, pre-global? Pass order: expand → jump → cse → ... → flow → combine → sched → local-alloc → global-alloc → ... Hmm, actually in GCC 2.7.2 the order is: cse1, loop, cse2, flow, combine, sched, local-alloc, global-alloc, reload... So the .lreg dump (local-alloc output) is BEFORE global-alloc, showing pseudo numbers. Let me check the .lreg dump for the function.

---
ts: 2026-11-06T08:49:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fzsw2Oe7bNXJL0UPiqUd
---
The scratch body is c1. Yet the combine dump shows a `(use reg78)` insn at the start of the else block. That's bizarre.

Hmm wait — maybe the dumps are from the TU as compiled by cc1_dumps_tu.sh with a DIFFERENT compiler state... no.

Let me search the .cse dump for insn 265 or the use insn. In the cse dump around label 128 we saw insn 132 (copy) and 134 (neg) with NO use. So the use appears only in the combine dump. Combine creates it? 

AH, I think I understand! GCC's combine pass, when it can't merge, can still... no. Let me look at the .cse2 dump (after the second cse pass, which runs after combine). And the .flow dump. If the `(use reg78)` appears in cse2, it's real.

Actually, here's a thought: combine's `-dc` dump prints the RTL after combine, and it includes the `(use)` insn that combine *created as part of a failed/partial substitution*: when combine substitutes a set into an insn but the result needs the old value... no.

Hmm, hold on, maybe I should look at the ORIGINAL (with-asm) dumps and compare. That's the real target. Let me dump the orig body's TU (score-0 body, i.e., with asm) and see the RTL. That will show exactly what the asm produces: presumably a `(use reg78)` between the copy and the neg — which is exactly what the combine dump shows! Wait, the c1 combine dump shows `(use reg78)` — maybe I dumped the orig, not c1! 

Is it possible the p3 scratch corresponds to the ORIG body? No — the scratch .c clearly has no asm.

Unless... the combine dump was produced from the p3 scratch, which the tool may have regenerated for the c1 run but with the *function body from the build tree*? No.

Let me just look at the full else-block RTL in the cse2/flow dumps to see whether the `(use)` is real. And let me grep the .cse2 dump for "(use (reg/v:SI 78))".

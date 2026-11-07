---
ts: 2026-11-06T05:15:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_skPCtGM90em1y3Fg7Iwo
---
So insn 38 sets raw(QI 75) = subreg of t(76). insn 40 sets t = zero_extend(raw). So both copies exist in RTL. But then cse/combine eliminates them. Let's see what the cse pass did. In the final asm, both moves gone.

Let me check n2.i.cse2 or combine around there.

Actually the issue: after insn 40, t = zero_extend(raw). But t is already known ≥ 0 and equal? cse sees reg 75 = subreg(76) and reg 76 = zero_extend(75) → equivalent. Then later uses of 76 replaced by 75's... hmm.

Let me look at combine output.

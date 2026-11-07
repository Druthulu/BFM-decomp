---
ts: 2026-11-06T16:35:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zsQWnjpsM1nqHHht5gxU
---
Now I see. In w1_r16:
- insn 53: `(set (reg:SI 77) (reg:SI 2 v0))` — move v1,v0 (77 gets v1). It survives because... reg 77 is used at insn 57 (zero_extend) and 65 (andi). At insn 53, v0 dies. Why no tie? Because `combine_regs(v0, 77)` — tying with a HARD reg? In block_alloc, tying two quantities requires both to be pseudos? Actually the source is a hard reg (v0) which has no qty. So no tie possible with a hard reg at a move — that's why the copy survives! Interesting: in the SImode natural case (win0), the copy `(set (reg/v:SI 74) (reg:SI 2 v0))` ALSO has a hard reg source, so no tie there either. The tie was at the ANDI (74 dies → 75 ties to 74).

In w1_r16:
- insn 57: `(set (reg:SI 78) (zero_extend:SI (subreg:HI (reg:SI 77) 0)))` — the zero_extend! reg 78 = zero-extended ret for the branch. This is the `andi v0,v1,0xffff` insn. Then branch tests 78.
- insn 65: andi m = 77 & 0x8000; 77 dies here. Why no tie between 75 (m) and 77? Because... the tie loop requires the insn's operand 0 constraint '=' etc. `andsi3` — the output 75 and input 77. Hmm, it should tie! But maybe because reg 77 is `reg:SI` from a zero_extend's subreg use... Let me look at the andi RTL: `(set (reg/v:SI 75) (and:SI (reg:SI 77) (const_int 32768)))` with REG_DEAD 77. That looks tieable. Yet the result gave m=v0 and ret=v1.

Wait, actually maybe it DID tie, but tied to... no. In w1_r16, ret=77 is v1 and m=75 is v0. If they tied, m would be v1. The score diff showed `andi v0,v1,0x8000` — m=v0. So no tie.

Why? Look at combine_regs conditions. Maybe because 77 is used by insn 57 (zero_extend) which is *after* the copy and the qty 77 is "not live" ... Hmm. Or because the tie requires `may_save_copy`... no.

Let me look at combine_regs to understand. Actually maybe the tie is blocked because 77 and 75 have *conflicting* live ranges: 77 is live from 53 to 65; 75 born at 65. They don't conflict (77 dies at 65). Hmm.

Wait, maybe the issue is that insn 57 (zero_extend) creates a USE of 77 that extends 77's live range, and combine_regs requires that the death point is the *only* use... no.

Let me read combine_regs.

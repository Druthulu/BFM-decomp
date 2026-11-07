---
ts: 2026-11-06T12:38:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_P2q5XsqlduC51nifaJGK
---
Register 73: used 9 times across 22 insns; no "crosses N calls" → it doesn't cross calls. Good. So it's a call-clobbered candidate. Its conflicts include v0 (2) and v1 (3) — so at some insn, ret is live while v0/v1 is live.

Which insn? In an arm: `li v0,41` (comparison) is live while ret (defined in the previous arm?) no...

Hmm, actually the conflict list is a union over the function; ret's live range spans from its def to the STORE, but in between are the *other arms' comparisons*? No, a goto ends the block.

Wait — maybe ret is live at the top of the loop... no loop.

Let me find the actual insns where 73 appears. In the lreg dump the RTL is post-local-alloc with pseudos still numbered. Let me grep the region for "73".

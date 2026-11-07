---
ts: 2026-11-06T22:39:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tRHLBO6CsSAFMrBxYtAe
---
Both have r72 4 refs/6 insns in block 0. In w0 r72→v0, w6 r72→a0. The difference must be the tie with the pointer (r81 in w0 / r80 in w6).

Hmm, let me check the greg dumps' "Register dispositions" for r72 and the ties. Actually, the tie is decided in local-alloc; the lreg dump's "Register 72 used 4 times across 6 insns" doesn't show ties.

Let me look at the .lreg insn stream for insn 4 (the arg0 copy) in w0 and w6.

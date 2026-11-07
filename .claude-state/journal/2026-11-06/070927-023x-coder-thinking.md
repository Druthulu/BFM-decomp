---
ts: 2026-11-06T14:09:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IRc0iYphvhldSVWm0fVR
---
"used N times" — this is REG_N_REFS. Register 73 used 11 times, pointer (that's probably arg0 or a global pointer). Let me find which regs correspond to i, dst, src, n. The loop is in block 4/5/6. Let me see more of the register list and then map to RTL. Let me read further, and search for the block containing the loop.

Actually, the lreg dump is the input to local-alloc (after global-alloc? -dl = local-alloc dump, printed before local alloc). The "Register N used M times across K insns in block B" gives refs.

i, dst, src, n are the loop pseudos. Let me find registers used in the loop block. Let me look at the RTL around the mult / loop.

Let me search for "mult" in that range.

---
ts: 2026-10-22T20:21:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZMniqSq1zrmUmy8v5j6i
---
r80 doesn't appear as a pseudo in the greg dump (already replaced by s1). So in c_struct, local-alloc assigned r80=s1 before global. That means r80 (m address) was eligible for local-alloc, i.e., its live range did NOT cross a call in the allocator's view? But it's used in the delay slots of 3 calls.

Hmm wait, "crosses 2 calls" in the alloc table — the alloc table prints from .lreg. If it crosses calls, local-alloc assigning s1 means the reg must be saved/restored around... no, local-alloc does not save callee-saved regs (prologue/epilogue is global's job). Assigning s1 locally to a pseudo crossing calls would be a bug unless the pseudo's live range doesn't actually cross the calls.

Unless r80 is the *source* address (D_800AE620) used by the movstr! The movstr: source address in a1 = $5, not s1. Hmm.

Let me find r80's definition in the .lreg dump for c_struct. Grep in the lreg section.

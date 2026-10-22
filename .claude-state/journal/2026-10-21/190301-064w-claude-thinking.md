---
ts: 2026-10-22T01:03:01.311Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 8bd904fe-fbea-4565-a883-e61d65fe8209
---
With T21 done and T11 resumed, I should explain in plain terms: a lever is something like pinned registers or inline asm or compiler hints used to force byte-for-byte matching output. A singleton lever is one whose exact text appears in only one function, so fixing it doesn't require propagating changes elsewhere. The underlying goal is clean, legible pure-C source — levers represent technical debt, and the milestone is reached once every lever is either removed or explicitly documented against a named compiler quirk; this isn't related to struct layout.

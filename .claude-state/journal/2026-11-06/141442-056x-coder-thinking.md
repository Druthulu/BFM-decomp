---
ts: 2026-11-06T21:14:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_U79KwQhwY5KsfrPn3yaw
---
w2.i.jump (jump1 output) still has 2 sets of reg/v 79 (the rv assignment and the dead one). w2.i.cse has 1 v0 and presumably the dead set deleted? Wait, cse count of "set (reg:SI 2 v0)" is 1 — but the dead set is `(set (reg/v:SI 79) ...)` at insn 99, not v0 (rv is a pseudo 79, not yet allocated). So counting v0 sets doesn't tell. Let me count `set (reg/v:SI 79)` in cse.

Hmm, rv = pseudo 79. The dead set is insn 99. Let me check if insn 99 exists in cse/flow.

Actually, in w2, rv is a plain s32 pseudo 79. The two sets: insn 93 (`rv = sp20`) and insn 99 (`rv = (s32)a0`). The second is dead. Let me grep for "reg/v:SI 79" in cse and flow.

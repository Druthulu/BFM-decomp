---
ts: 2026-11-06T16:34:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CkkgvigmODHlU6YAu7yh
---
Global-alloc: 72 (self) → a1, 73 → a0. Since 72 conflicts with a0 (because at insn 4, 72 is set from a0 and a0 dies? "72 conflicts: 72 73 2 3 4 29" includes 4=a0) so 72→a1. 73 conflicts: 72 73 2 3 29 — not 4! So 73 can be a0, and it got a0. Then uses of 73 (else block) become a0.

Where did 73 come from? insn 11 `(set 73 72)`. That's likely created by *local-alloc's* copy handling? Actually, insn 11 was created during cse/sched: possibly the sched1 or the `move` at insn 4... hmm.

Let's look at the cse dump to see if 73 existed before local-alloc, and the flow dump.

But the key insight: the else path uses a copy 73 of self, which global-alloc can put in a0 because a0 is dead after the entry (a0's value was copied to 72 at insn 4). If we could make a0 live/conflicting at block 2, 73 would go elsewhere (a1) and 72 too? Hmm.

Where does 73 come from? Let me check the cse dump.

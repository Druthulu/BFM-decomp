---
ts: 2026-11-06T14:52:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EtR4k8YvtEis0Nm2UJPo
---
The .jump dumps differ only by numbering AND the asm insn (the launder) — the code structure is otherwise identical! So jump_optimize did NOT fold the branch. The fold must happen LATER (cse or beyond). Wait, but the .jump dump is after jump_optimize. The structure is the same (except the asm). So the branch merge happens in a later pass (cse? but the jump_insn count at .cse was the same 62 for both).

Hmm. Let me diff the .cse dumps (after cse1) normalized. If cse1 folded, the .cse dumps would differ structurally.

Wait, the jump_insn count: c1 .cse = 62, orig .cse = 62. Same. But the STRUCTURE might differ (beq vs bne) without changing the count.

Let me diff the .cse dumps normalized. But the asm insn shifts numbering. Let me normalize.

Actually, let me think: the fold `if (t==5) { if (t!=3) }` -> merge. This is a jump optimization. If it's not in jump_optimize (the .jump dump is the same), then it's in a later pass. Which pass optimizes branches? cse's `record_jump_equiv` + `fold_rtx` folds the comparison in the branch itself (e.g., `bne t,3` -> `j` or removes it). Hmm, but cse's fold_rtx would fold the comparison to a constant and then the branch becomes unconditional. That would change the structure.

Let me diff the .cse dumps. Let me normalize and diff.

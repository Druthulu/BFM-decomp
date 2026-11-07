---
ts: 2026-11-06T01:40:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1hj84xAt2RthNU5uiowG
---
So the jump was deleted entirely. Let me trace: after redirect_jump(insn, NULL_RTX), it becomes a RETURN insn. Then the RETURN cross-jump block: `if (cross_jump && GET_CODE (PATTERN (insn)) == RETURN)` — cross_jump=0 in the first pass, so skipped. Then later in the pass, maybe "delete insns after barrier"? No.

Hmm, maybe redirect_jump with NULL_RTX actually *deletes* the jump and converts to a RETURN; then the RETURN insn... wait the dump has no return insn. Unless redirect_jump(insn, NULL_RTX) when the jump is not needed deletes it. Let me look at redirect_jump's NULL handling. Search "redirect_jump (jump, 0" or "nlabel == 0".

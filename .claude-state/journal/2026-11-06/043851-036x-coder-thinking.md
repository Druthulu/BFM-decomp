---
ts: 2026-11-06T11:38:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4C1l2bnKLcxXYkZmJ62K
---
So priority is decisive. In mine, the adds have higher priority than the stores, so they go first. In target, they don't. Why? Because in the target, the adds depend on the stack loads (w_, h_). If a load has insn_cost 2, priority(addu) = 2. In target EBB2 the addu still comes after lw a2 and the stores... hmm, maybe those stores also have higher priority? No.

Wait, maybe in the target, the w_/h_ stack loads are NOT part of EBB2's beginning: `lw t1,16(sp)` is the first insn of EBB2 (right after the barrier). Hmm.

Actually hold on. Let me reconsider: maybe insn_cost for a load on r3000 is 1 (the "cost" here is not the latency; MIPS insn_cost returns 1 for most, with ADJUST_COST handling load-delay?). Let me check mips.c insn_cost / ADJUST_COST.

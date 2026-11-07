---
ts: 2026-11-06T02:08:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FYwmzL0GLpujdQKhRznx
---
UID 368 JUMP_INSN deleted via delete_computation ← delete_jump, called from... let me get the caller of delete_jump (bt 4). It's likely jump_optimize. Which call site? delete_jump is at 0x80f6bd9; its caller would be in jump_optimize at some address. Let me get a deeper backtrace for this hit, plus the jump's label UID and PATTERN to confirm it's ours.

Also: delete_jump calls delete_computation on the jump's insns — meaning the jump had delay-slot computations? No: delete_jump deletes the insns that compute the condition (for condjumps) — for a simplejump, it just deletes. Hmm, but delete_computation is called by delete_jump on the jump's "insns"? Let me read delete_jump.

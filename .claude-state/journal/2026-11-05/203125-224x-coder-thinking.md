---
ts: 2026-11-06T03:31:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wKhGhGoFk8Ln7ukJBoTu
---
invalidate_for_call only handles registers, NOT memory. So cse does NOT invalidate memory entries at calls! That's why the load is hoisted above the call. (gcc 2.7.2 relies on... hmm, actually memory loads across calls: cse's table has in_memory entries; a call doesn't invalidate them. That's a known conservative issue? Whatever.)

So the target's C must have prevented the memory load from being CSE'd across the call. The barrier (memory clobber asm) invalidates memory at the asm. But the barrier is AFTER the store; the first load is before the call... 

Wait, the target's first load is at 52b4 (after the call). If cse doesn't invalidate memory at calls, why didn't the original compiler hoist it above the call? Maybe because in the original RTL, the load was after the call and cse's EBB... the call splits the EBB? Calls don't end EBBs. Hmm.

Hmm, actually cse's `cse_basic_block` handles calls specially: `invalidate_for_call` is called, and also `invalidate_memory`? Let me look at where invalidate_for_call is called in cse_insn: probably `if (GET_CODE (insn) == CALL_INSN) { invalidate_for_call(); ... }` and maybe also memory. Let me grep.

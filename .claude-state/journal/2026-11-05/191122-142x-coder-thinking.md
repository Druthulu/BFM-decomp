---
ts: 2026-11-06T02:11:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mH55o9LZnRAmVMQe5n1D
---
Our jump (uid 368, JUMP_INSN) is deleted by delete_jump called from jump_optimize at 0x80f31f5. Which source line? Let me map 0x80f31f5 to a source line by finding the call sites of delete_jump in jump_optimize. The 4 call sites are at lines 667, 1130, 1299, 1733. Let me disassemble jump_optimize and find the call to delete_jump at 0x80f6bd9; the return address 0x80f31f5. Then find which source construct. Without debug info, I can compare the call address with the function's other landmarks... Alternatively, since I have the source, I can look for the call sequence near the address. Let me disassemble around 0x80f31e0-0x80f3200 and see the context (calls nearby to known functions like delete_insn, swap_jump, invert_jump).

Actually, simpler: the jump is a simple jump to the epilogue. delete_jump at line 664 requires condjump_p. Not ours. But WAIT: maybe before this, at line 656, `redirect_jump(insn, NULL_RTX)` converted the jump to a RETURN. Then later, some code calls delete_jump on it? delete_jump checks single_set dest==PC — a RETURN has no single_set → no delete.

Hmm, but maybe the jump was first converted to a RETURN, and then `delete_jump` was called on a DIFFERENT jump (e.g., a conditional one) and delete_computation recursively deleted our RETURN? delete_computation deletes insns that compute dead values of the jump being deleted — our jump isn't a computation.

Wait, the backtrace shows delete_insn ← delete_computation ← delete_jump, and our insn 368 is the one being deleted by delete_insn. delete_computation(insn) is called with insn = our jump (from delete_jump(insn)) and then deletes it. So delete_jump WAS called with our jump. That requires single_set(our jump) with SET_DEST==PC. So our jump is still a `(set (pc) (label_ref))` at that point (not a RETURN).

So a delete_jump call site fired on our simple jump. Which site? Lines 667 (condjump), 1130, 1299, 1733. Let me check line 1130/1299 contexts: they're inside `if (!reload_completed && this_is_condjump && !this_is_simplejump ...)` for 1018. 1130 is in that block: delete_jump(insn) where insn is the condjump. 1299 similar. 1733 is the condjump-over-jump.

None for simplejump. Hmm! Unless our jump became a condjump somehow: after `redirect_jump(insn, NULL_RTX)`, condjump_p? no.

Wait — maybe the call at 0x80f31f5 is NOT one of those; maybe the source has another delete_jump call I missed. Let me grep all delete_jump calls again: 667, 1130, 1299, 1733. Four.

Let me disassemble around 0x80f31f5 and see.

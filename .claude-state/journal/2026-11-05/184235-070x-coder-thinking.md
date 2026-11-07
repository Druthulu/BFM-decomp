---
ts: 2026-11-06T01:42:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gcCPrcyw4oKgstmFg7d1
---
So the jump 368 and barrier 369 were deleted, and the FUNCTION_END note 372 too. Which code deletes the jump? Let's think about the end-of-pass FUNCTION_END scan:

```
insn = last_insn;
{
  int n_labels = 1;
  while (insn && ((GET_CODE (insn) == CODE_LABEL && n_labels-- > 0)
                  || GET_CODE (insn) == INSN
                  || (JUMP_INSN && RETURN)
                  || BARRIER
                  || (NOTE && kind != FUNCTION_END)))
    insn = PREV_INSN (insn);
}
if (insn && NOTE FUNCTION_END) { can_reach_end = 1; delete_insn (insn); }
```

last_insn was computed earlier as the last non-deleted insn before... Actually last_insn is set in the loop at line ~247: "Delete all labels already not referenced. Also find the last insn." It sets last_insn to each non-deleted insn. At that point, label 374 is referenced (by many jumps) so it's not deleted; last_insn = label 374.

The backward scan: insn=label 374: CODE_LABEL and n_labels=1 → n_labels-- (0), insn=PREV = note 372 (FUNCTION_END) → the while condition: NOTE with kind == FUNCTION_END → false → exit loop. Then `if (insn && NOTE FUNCTION_END) delete_insn(insn)`. delete_insn(note 372): next = label 374 (not deleted); prev = note 371. Not a code label. Not a simplejump. next is not BARRIER. Patch out. So only the note is deleted. Jump 368 remains.

But it's not there! So something else deleted it earlier. Perhaps `delete_insn` of label 374 happened at some point and then the label was re-created? Hmm.

Wait — maybe the redirect_jump(insn, NULL_RTX) at line 656 fired for insn 368 (because at the time, next_active_insn(374) was 0? The label is last in this function, and the next function's insns follow in the chain, so next_active_insn(374) is the next function's first insn — not 0). Hmm, unless functions are separated by barriers/notes and next_active_insn... no, it returns the next real insn regardless of function boundary.

Unless each function's insns are in a separate chain? No, they're all in one insns chain.

OK, I'm spending too long on this. Let me take the empirical route: the target must have zero's block ending with something. Let me look at what the ACTUAL original source might be by examining the dec block and the target's delay slot: `j 180c; sw` — the store was moved into the delay slot by reorg. In the current (barrier) version, the same: let me check the orig .jump2: dec jumps to label and the store... Let me dump orig (with barrier) to compare — the barrier version scores 0, so its .jump2 shows the target shape.

Let me dump orig.

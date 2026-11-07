---
ts: 2026-11-06T01:52:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sLCdleS0b9C2JNXD2CXQ
---
Confirmed: in vA, the trailing `return;` jump is deleted in the FIRST jump pass (jump dump shows it gone). So my earlier analysis stands.

Where is it deleted? Now I can investigate with the correct dump. In vA2.i.rtl, the jump exists. In vA2.i.jump, gone. Let me find which code path. Let me look at the vA2 .rtl tail and then think again.

Actually, the deletion might be the `redirect_jump(insn, NULL_RTX)` → RETURN conversion, followed by... the RETURN insn being deleted because it's at the end? Hmm, but no (return) in the dump.

Let me look at the .jump dump for vA2 around the end: insn 366 store, then note 371, label 374. The jump and barrier are gone.

Let me look for the code that deletes a simplejump to the next insn. Maybe it's not in jump.c but in `delete_dead_jumps`... Hmm.

Actually! Maybe the deletion is due to `redirect_jump(insn, NULL_RTX)` turning it into `(return)`, and then the RETURN insn gets deleted by the code at line 2005? cross_jump=0. Hmm.

Let me search for "delete_insn" near RETURN. Or maybe the RETURN insn is deleted by `delete_jump`? 

Let me try gdb-free: compile with -dj and see. We know it's gone. Let me look at what remains: the note 371 (BLOCK_END) is now directly after the store, and label 374 follows. In the .rtl, between the store and note 371 was jump 368 + barrier 369. So both deleted.

The only code that deletes a jump and its following barrier is delete_insn(jump) (it deletes the barrier after). So delete_insn(jump 368) was called. Which call site? Options: 189 (following barriers), 244 (label deletion), 433/463/496/520/531/557 (various), 822, 1417, 1602, 2056, 2112.

Line 244 is in "Delete all labels already not referenced" — deletes a CODE_LABEL, not a jump. Line 189 deletes insns after barriers (notes).

Line 2056: in the extraneous line notes loop, delete_insn(note).

Line 2112: delete FUNCTION_END note.

Hmm, what about `delete_insn` called from `redirect_jump` when the olabel's uses drop to 0? That deletes the LABEL, and if the label is followed by a BARRIER, deletes the barrier. Not our jump.

Wait, maybe the jump was deleted by delete_insn(temp) at line 822 or 1417 etc. Let me look at 1400-1430.

---
ts: 2026-11-06T01:54:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LtcUhB2IVEb4HFVA0oKf
---
Not it.

Let me just find the jump-to-next deletion empirically with gdb. Check if gdb exists.

Actually, maybe easier: gcc has `-dJ` (jump2) and `-dj`. We know .jump shows it deleted. Let me look at the vA2 .rtl vs .jump for the exact insn and see if the jump was converted to something. The .jump tail shows note 371 directly after insn 366. In .rtl, note 371's PREV was note 372, and before that barrier 369, jump 368, store 366. Hmm.

Wait, maybe the jump was deleted by `delete_insn` in the *dead pseudo set deletion* at line 540-560? No.

Could the jump have been deleted by the code at line 2056-2060 (extraneous line notes)? No.

Hmm, let me look at the `#ifdef HAVE_return` block at the end again:
```
if (HAVE_return) {
   insn = get_last_insn ();
   while (insn && GET_CODE (insn) == NOTE) insn = PREV_INSN (insn);
   if (insn && GET_CODE (insn) != BARRIER) { emit_jump_insn (gen_return()); emit_barrier(); }
}
```
If HAVE_return is defined, this would ADD a return insn at the end. In vA2's .jump dump, the last insn is label 374 (no return added). So HAVE_return is not defined (or the last insn is a label, and get_last_insn skips only notes → insn = label 374, not BARRIER → it would emit a return! But it didn't). So HAVE_return is undefined. Good.

I'm going to try gdb to find the deletion. Check gdb availability.

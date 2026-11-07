---
ts: 2026-11-06T02:11:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ArZXN17LH3znmtVdiFI8
---
The code at 0x80f31cb calls condjump_p, and if true (test eax; je skip), calls next_real_insn(JUMP_LABEL) then delete_jump. This matches line 664-667:

```
if (reallabelprev == insn && condjump_p (insn))
  {
    next = next_real_insn (JUMP_LABEL (insn));
    delete_jump (insn);
```

So it IS the condjump path — meaning our insn 368 was a CONDJUMP at that point! How? Because at line 656, `redirect_jump(insn, NULL_RTX)`... no. Hmm, condjump_p(insn) true means the jump is conditional. Our jump is a simple jump to the epilogue.

Unless the UID-368 insn at that moment is a DIFFERENT insn: UIDs are reused? No, UIDs are unique within a function.

Wait — maybe in the mini TU, insn 368 is not the same as in the full TU? The .jump dump of miniVA shows uid 368 is... let me check: the dump tail showed insn 366 (store), note 371, label 374. The jump 368 is gone. In the .rtl (before), insn 368 is the jump to 374. But during the pass, insn 368 might have been *replaced*? UIDs don't change.

Hmm, condjump_p(insn 368) true? Let me check the .rtl dump of miniVA for insn 368.

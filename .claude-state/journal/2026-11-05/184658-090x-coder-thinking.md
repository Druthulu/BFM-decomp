---
ts: 2026-11-06T01:46:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eAmdiHqJZ2DJ9MBlMSeH
---
At 656: `redirect_jump (insn, NULL_RTX)` — if next_active_insn(JUMP_LABEL) == 0. For vA, label 374 is the last insn → next_active_insn(374) == 0 → redirect to RETURN. That converts the jump to a RETURN insn. But then the dump would show `(return)`. Unless `validate_change` failed because... hmm, `validate_change(insn, loc, gen_rtx(RETURN), 0)` — this succeeds normally.

BUT: maybe HAVE_return is not defined, and later `final`... no, the dump would still show it.

Wait, maybe the jump was converted to RETURN, and then the label 374's LABEL_NUSES decremented; other jumps also converted... all converted. Then the label becomes unreferenced and deleted. But the dump shows label 374 with refs from other jumps (they still show label_ref 374). So the redirect did NOT fire for them. Why not?

Because `next_active_insn (JUMP_LABEL (insn))` — for the OTHER jumps, the same label 374. If next_active_insn(374) == 0, ALL would fire. They didn't. So next_active_insn(374) != 0. What follows label 374? In the .rtl dump for the *function*, label 374 is last. But next_active_insn walks the NEXT_INSN chain: NEXT_INSN(374) = 0? The dump prints insns via print_rtl which follows NEXT_INSN; so label 374 is last in the chain. So next_active_insn(374) == 0.

Contradiction. Unless next_active_insn is called with the label and returns the label itself? Let me check the definition of next_active_insn in this gcc version. It's in rtl.c or jump.c? grep.

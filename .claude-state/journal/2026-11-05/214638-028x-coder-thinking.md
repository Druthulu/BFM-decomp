---
ts: 2026-11-06T04:46:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6oqtE3dVfAOmvY9GgvG9
---
Key: for a conditional jump (`target != 0`), the condition `target == 0 && ...` is false, so it goes to the else branch which likely splits and checks `eligible_for_delay`. Let's continue reading.

Also key: `if (GET_CODE (trial) == CODE_LABEL || BARRIER) break;` — a label immediately after the branch stops the forward scan! So if the fall-through block starts with a label (a branch target of another jump), reorg can't fill.

Can real C produce a label at the start of the if-body? If some other goto targets that block. E.g.:

```
if (0x80 < D_80078EBF) {
  L:
    D_80078EBF = 0x80;
}
```
But a label there requires a goto from elsewhere to it, and gcc may delete the label if unused. A `goto` inside the same block jumping to the start: `if (...) { goto L; L: D_80078EBF = 0x80; }` — gcc deletes redundant gotos at the tree/rtl level? At -O2, `goto L; L:` is removed by jump optimization.

Hmm. But maybe the label persists if it's a loop head? do-while(0) creates a NOTE_INSN_LOOP_BEG, not a CODE_LABEL. Actually loop structure creates a label at loop start? In RTL, a loop has a CODE_LABEL at the head (the loop_beg note is attached to a label). And loop.c... But we must not introduce loops that add code (loop.c might add insns).

Wait — but C0535 says do-while(0) splits cse1 EBB; that's a different mechanism (cse EBB). Hmm.

Let's continue reading the `target != 0` path: for conditional jumps, it does:

```
	      else
		{
		  ...
		  if (! insn_references_resource_p (trial, &set, 1)
		      && ! insn_sets_resource_p (trial, &set, 1)
		      && ! insn_sets_resource_p (trial, &needed, 1)
		      && ! (maybe_never && may_trap_p (pat))
		      && (trial = try_split (pat, trial, 0))
		      && eligible_for_delay (insn, slots_filled, trial, flags))
```

Let me read on.

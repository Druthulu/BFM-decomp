---
ts: 2026-11-06T21:07:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cZm0tOzTVpp5GwRQi4A4
---
At insn 35: `(set (reg:SI 2 v0) (ashift (reg/v:SI 3 v1) 16))` with REG_DEAD v1 at 35? Let me look at lines 85-101 of that section. Actually insn 35 is in block 1 (after the store at 33). Wait, in the earlier listing, insn 32/33 was the store and insn 34/35 the ashift. Let me view.

The point: the ashift result (hard v0 after local-alloc) is born at insn 35 while r74 dies at 35. Deaths processed before stores → no conflict. Hmm.

But there's `mark_reg_clobber` which processes CLOBBERs *before* deaths! Look at the order:
1. `note_stores (PATTERN, mark_reg_clobber)` — marks clobbered regs live
2. deaths
3. `note_stores (PATTERN, mark_reg_store)` — marks set regs live

So a hard reg that is *clobbered* (CLOBBER rtx) at an insn where r74 dies would conflict. But `(set (reg:SI 2 v0) ...)` is not a clobber.

Hmm, so the conflict must come from somewhere else. What about `mark_reg_store` for hard regs: it marks the hard reg live and records conflicts with everything live. At insn 35 (v0 born), r74 is dead already (processed in step 2). Unless r74 is NOT dead at 35 — REG_DEAD note says at insn 35? Let me check the exact insn 34/35 in the dump.

From the earlier grep (lines 80-93):
```
(insn 30 27 33 (set (reg/v:SI 3 v1) (plus ...))
(insn 33 ... (set (mem:HI ...) (subreg (reg/v:SI 3 v1) 0))
(insn 35 ... (set (reg:SI 2 v0) (ashift (reg/v:SI 3 v1) 16)) (insn_list 30)
   (expr_list:REG_DEAD (reg/v:SI 3 v1) (nil))
```
So at insn 35, v1 (r74) is dead. Deaths processed before stores → no conflict.

Hmm OK. So where? Let me instead look at what global.c's `find_reg` does with hard_reg_conflicts. Maybe the conflict set also includes hard regs that are *live at the start of the block* — but v0 isn't live at block starts.

Wait, maybe I'm misreading "74 conflicts: 72 73 74 2 29". Could "2" mean the second allocno (i.e., allocno index 2 = r73)? No — the list "72 73 74 2 29" — hmm, maybe the numbers are allocno numbers in some cases and hard regs in others? The dump_conflicts prints:
```
;; %d conflicts: ...
```
Let me read dump_conflicts in global.c.

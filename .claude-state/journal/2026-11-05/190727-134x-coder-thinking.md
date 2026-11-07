---
ts: 2026-11-06T02:07:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fx5M9ZegXfpN3pokpqee
---
PATTERN = fld[3] → offset 4 + 3*4 = 16. JUMP_LABEL = fld[7] → offset 4+28 = 32.

For a simple jump, PATTERN is a SET (code 23?), SET_SRC = fld[1] of the SET → LABEL_REF. Or JUMP_LABEL (offset 32) gives the label rtx; its UID at offset 4.

Let me print at the JUMP_INSN delete hits: uid, JUMP_LABEL uid. If JUMP_LABEL uid == 374 and uid == 368, it's ours.

Let me update the gdb script.

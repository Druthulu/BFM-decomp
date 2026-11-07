---
ts: 2026-11-06T09:35:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hOxRMNEUbBGQrvsSnCXT
---
Let me look at insn 127 (o) / 125 (w) — these differ! In o it's 127, in w 125. That's likely the `move a0,s0` copy (an extra insn in o? no, both have 57 insns). Actually the numbering differs because the keepalive asm is an insn in o. In o, the asm use is insn 127 (after 42). In w, no asm → numbering shifts.

Let me print the block around insns 40-49 for both.

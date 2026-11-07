---
ts: 2026-11-06T14:51:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_imy6aNv7gctP4rx1ltVw
---
The .rtl dumps differ only by insn numbering (orig has the asm, so numbers shift). The structure is otherwise identical (the diff is all numbering). So the fold does NOT happen at expand/jump_optimize? Wait, the .rtl dump is BEFORE jump_optimize (it's the initial RTL after expand). Let me check the dump order: toplev.c line 2826 reg_scan, 2859 cse... The .rtl dump is probably right after expand. So the .rtl is pre-optimization.

Let me instead compare the .jump dump (after jump_optimize) — if the fold happened in jump.c, the .jump dumps would differ structurally (beyond numbering). Let me diff those.

Actually, the jump_insn counts were the same. Let me diff the .jump dumps.

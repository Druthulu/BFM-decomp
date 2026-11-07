---
ts: 2026-11-06T21:02:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gvQdY6Rret6jXuLwd7Qq
---
Interesting: registers 78 and 79 in block 1 each used 2 times across 2 insns. Hmm. And in block 1 live at start: 29,30 (sp, fp? no 30=fp... actually 30 is fp per NAMES; hmm, in this MIPS the frame pointer might be $30; live at start includes 4? no). Anyway.

Wait: my candidate has in block 1: lhu $2, addu $3, sll $2, sh $3, bgez. Register 78 (used 2 times/2 insns) and 79 (2/2). Hmm, 78 = ? Let's find the insn numbers. Block 1: first insn 26, last 36.

Let me dump block 1 RTL.

Actually, hold on. The alloc_table said r78 -> v0 and r79 -> v0 in blk 1. But assembly shows addu $3. Which pseudo is 78 vs 79?

Let me grep the .lreg for the block 1 instructions.

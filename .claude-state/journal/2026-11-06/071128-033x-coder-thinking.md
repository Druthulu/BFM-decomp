---
ts: 2026-11-06T14:11:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_inEXhTxYiL5MS6PjGr3r
---
Tie-break: return *q1 - *q2, so lower qty number first. qty numbers are assigned in pseudo-reg order (qty_first_reg / next_qty increments as regs are processed in REGNO order). So a pseudo declared earlier (lower regno) gets a lower qty -> allocated earlier when tied.

But wait, priorities aren't necessarily tied. Let me compute. For c1: i n_refs=11, dst n_refs=11. size=1 each. priority = floor_log2(11)*11*1/life = 3*11/life = 33/life. So shorter life wins.

i: birth = ? The qty birth/death for a pseudo in local-alloc: `qty_birth[q] = ...` set in `block_alloc`? Let me check how birth/death are derived. In local-alloc.c, the qty is per (regno, block?) Actually quantities are per register within a block? Hmm, local-alloc processes each basic block. Wait — but i spans multiple blocks (block 3 init, block 14 loop). Hmm, local-alloc's `local_alloc` processes block by block, and quantities are per block. Let me re-read.

Actually in gcc 2.7.2 local-alloc.c, `local_alloc()` iterates `for (b = 0; b < n_basic_blocks; b++) { ... block_alloc(b, ...) }`. Quantities are per basic block. So for block 14, i, dst, src, n each form a qty (regs live into the block and defined in it). qty_n_refs is the total refs? Line 297: `qty_n_refs[qty] = reg_n_refs[regno]` — reg_n_refs is the global count (across the function), but qty_birth/death are within the block.

Let me check lines around 250-300.

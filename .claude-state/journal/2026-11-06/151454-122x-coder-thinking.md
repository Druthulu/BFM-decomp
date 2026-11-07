---
ts: 2026-11-06T22:14:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hM0ZXhXvjyhU9DW4QrMj
---
The do-while is after the packet store. The mask 0xFFFFFF appears in BOTH the packet store (line 91) and the otp store (line 95). The target's mask materialization at 166 is for... the packet store's `& 0xFFFFFF` (used at 191) and the otp store's (used at 206). In the RTL, r193 (0xffffff) is set once and used twice (both ands). So the single constant pair serves both.

In mine, it's scheduled at 163/167; target at 166/170.

The constant's first use is the packet store's `and` (at 190) and the second at 206. The scheduler places the materialization in a free slot. The target has it 3 slots later.

Since the do-while fixed the register allocation, maybe a slightly different EBB split moves the constant. Let me try:
- m1: wrap the sxy store block (6 lines) in a do-while, plus the otp do-while.
- m2: wrap `w = mulc; vv = e[1]; if...` block.
- m3: wrap the `pkt[0x14]..pkt[0x25]` block.

Let me look at the source lines 70-100 to pick spans.

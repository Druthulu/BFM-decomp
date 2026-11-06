---
ts: 2026-10-22T21:48:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_STsHs4FdfoNswtAR4RxM
---
Item 4: func_80180610 — a barrier (zero-byte `__asm__("")`) after the table read. Per the comment, it pins the table read + index arithmetic to the top of the block and restores the target's load-delay nop (sched1 otherwise hoists the two -0x60 stores into the lh 0x20C load-delay slot).

Lever-free: need the lh's load-delay slot to hold a nop rather than a store.

Let me extract and score first.

Lines 4874-4892 (function). Let me extract precisely: from `void func_80180610(void *a0) {` to the closing brace.

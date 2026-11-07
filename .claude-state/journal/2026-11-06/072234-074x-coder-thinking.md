---
ts: 2026-11-06T14:22:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OFEO0mcyuke9mpKvU0YX
---
This code at 951-1015 deletes "obvious no-op moves" (self-copies) BEFORE the main scan (this is in `life_analysis`, the initial loop). So a self-copy `i = i` is deleted HERE, before ref counting. That's why identity launders don't work.

But where are dead stores (like `p = 0` after a call) deleted? The C0414 note says flow deletes dead sets. Let me search for where insns with dead dests are deleted. Maybe in `propagate_block` after computing live/dead: if the insn sets only dead regs and has no side effects, delete it.

Let me look at lines 1470-1560 for the deletion after the scan.

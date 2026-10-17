---
ts: 2026-10-17T11:16:28.388Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
Both versions share the same jump structure before reorganization, with insn 21 and jump 23 leading to the end. The difference emerges in how the delay slots get filled during reorg—in the a2 case, jump 23's delay slot gets filled and the branch becomes a SEQUENCE rather than a plain jump, which changes how the surrounding branch logic needs to work.

In the cal case, the intervening asm volatile at insn 20 blocks filling jump 17's delay slot from that position, so instead jump 23 picks up insn 21, and the conditional branch fills eagerly from its target instead. This difference in delay-slot filling order is exactly why the invert-branch rule applies in one case but not the other.

To reproduce this in plain C, I need to figure out why jump 17's fallthrough fill fails while jump 23 still gets v0=0. I want to check how fill_simple_delay_slots handles the forward path for conditional branches versus simple jumps.

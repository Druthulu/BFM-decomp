---
ts: 2026-11-06T15:10:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_63p2VDXL6HgRX9jXAyOC
---
Let me look at fill_simple_delay_slots to see the ordering: does it try pre-branch insns or thread first? And what makes an insn ineligible.

This is getting deep. Let me step back and consider the budget: 20-30 min per item, 5 items. I've spent maybe 15 min on item 1. Let me time-box the analysis but b4 is 1 insn away.

Practical idea: place the second set of vol where it is now (launder position) but make the sll be scheduled into the delay slot by ensuring the andi is NOT in the same basic block. What if I put the mask inside the `if (sx == 0x10)` block or right after the vol division but *before* the sx computation... it's already there.

Alternatively: put the second set of vol BEFORE the `sx = (s16)*(u16*)&sxy;`? Then it's in the same block still (the whole thing is one block from 53c).

Hmm, what about the basic block boundary at 53c? The block starts at 53c because `bgez a2,53c` jumps there. The vol mask at the launder position is inside that block.

What if I move the mask into the `if (sx < 0) { av = -sx; }` branch? That's a different basic block. But the mask would only execute conditionally — semantically `vol = vol & 0xFFFF` there would mask a stale vol (vol not yet set) — but as a *dead* computation? It would be a real set of vol in that block, and if vol isn't live there, flow would delete it (dead store). Hmm.

What about assigning vol's *value* there? No.

Different idea: instead of masking vol, give vol a second set by *reusing vol as av's temp*? av is the pinned $5. No.

Let me look at the actual reorg code to find what disqualifies an insn. If an insn has a REG_DEAD note on a register that's used after the branch... Actually, `fill_simple_delay_slots` calls `fill_slots_from_thread` first for the fall-through thread, and only then tries pre-branch insns? Let me read.

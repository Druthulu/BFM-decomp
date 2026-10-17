---
ts: 2026-10-17T16:52:17.238Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm trying to figure out why the scheduler always places the `la` instruction into the delay slot across all 5 cases. With the keepalive/asm volatile barrier, `la` naturally gets scheduled before the store since the barrier blocks reordering; without it, the scheduler fills the `lhu` delay slot with `la` instead, and since the target has a trailing nop with nothing else to fill, I'm wondering what dependency could force `la` to stay before the `sw` in the second scheduling pass.

Since gcc 2.x's scheduler works backwards from the end of the block, la gets placed as late as priority allows — so I need to figure out what dependency would force la earlier, before the sw, matching the target. Maybe the discrepancy traces to sched2 rather than sched1, so I should check the actual scheduling dump to see where the reorder happens.

---
ts: 2026-10-17T17:31:07.810Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
This approach via store ordering isn't productive, and this case with 4 pins is too complex. I'm trying a different lever instead, considering whether changing c7840's priority or making it share a HImode const pseudo could help, but neither really changes the pressure.

Thinking about the overall goal: pinning stems from a tie-break where the lower-numbered allocno wins between r78 (c7840) and r79 (cm28) at equal priority 555. If I swap the declaration order so cm28 is created before c7840, cm28 would win the tie and take t4 — but then c7840 would still beat c64 (priority 517) for t5, which isn't the target ordering. So c7840 needs to either be born later or die later by several positions, which points back to how the original unpinned source structured the live range for c7840 compared to this pinned version.

I'm also wondering whether sched2 could reorder the disjoint stores to change insn birth order, but the earlier m1 test showed sched2 preserves original store order via luid, so that's not the lever. That makes me suspect the birthing-insn priority adjustment in schedule_block's backward scheduling — I want to check how adjust_priority treats birthing insns, since a priority boost there could explain why c7840's live range starts earlier than expected.

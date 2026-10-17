---
ts: 2026-10-17T14:02:29.576Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm checking whether a load through a register offset could alias with the symbol stores, but since the emitted instruction is a plain register-offset load rather than matching the lui/lw symbol pattern, there's no actual conflict here.

Looking at the reverse case, a store to *p with varying address versus a fixed-address load wouldn't create a dependency either, which would actually push the load further down—not what I want.

So I'm considering whether GCC's backward list scheduler itself explains the ordering: priority is based on path length to the end of the block, and I need to work out whether high-priority instructions like the load get placed earlier or later when scheduling proceeds from the end of the block backward.

I think the load is being delayed because of a "birthing boost" heuristic in sched.c that discourages placing register-defining instructions early to reduce pressure, and the catalog note about "a second identical assignment demoting sched1's birthing boost" suggests a duplicate assignment to val could undo that delay, though a plain dead second assignment feels like a rejected approach.

A legitimate way val ends up with more than one set might be if it's reused across branches, like reading into val before a conditional check in case 1. I want to actually check sched.c around line 2469-2545 to understand the birthing boost mechanism directly.

I'll adjust sched1's priority instead, so I'm checking sched.c:2469-2545 where the birthing boost logic depends on set counts.

---
ts: 2026-10-17T16:11:25.731Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb4a08fa100d7feb
model: claude-opus-5-5[1m]
effort: medium
turnId: dd20a3af-7bad-4cc5-bdfe-eb40b857c079
---
I'm thinking about how to prevent loop.c from hoisting invariants without relying on barriers — maybe by changing the loop's shape. Since gcc 2.7's loop optimizer only kicks in for loops recognized with proper loop notes, writing the loop using goto instead of a standard `for`/`do-while` structure would avoid those notes entirely and sidestep the optimization.

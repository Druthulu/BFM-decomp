---
ts: 2026-10-17T16:43:55.573Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm tracing why register 74 conflicts with hard register 2 — it looks like that color gets assigned at the end of the else-arm block, which is block 3, and 74 is live going into the join at block 4.

Checking the regs in block 4, there's no local variable in that block's list besides what shows up in block 5, so the andi/srl temp must live somewhere else. I'm wondering if the join block itself contains those 92/94 regs (the u8 mask and shift temp), which would force local-alloc to put them in v0 while color is also live there, creating the conflict — meaning the target would need those locals in v1 instead, which only works if color itself is treated as block-local at that point, which contradicts it being a value that flows across the join.

Unless the if/else is structured so color never actually crosses blocks as a global — maybe local-alloc's priority ordering (based on reference count and live range) is just choosing v0 first for temp 92 regardless, since nothing forces v0 unavailable. I should check if there's a hard register tied up by something like a call return value in that block, and also look at what's different about statement c11 to see if the store order gives a clue.

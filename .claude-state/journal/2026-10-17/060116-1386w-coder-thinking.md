---
ts: 2026-10-17T12:01:16.361Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm checking register allocation priorities — t (74) appears in 12 instructions in v1 but only 4 in the higher-priority version, so it ends up getting v0 since its live range is shorter there. Looking at the scheduling order, my placement of the ior/store pair after instructions 84/87 differs from where the target seems to expect them, which affects t's live range length.

Since the target also orders those zero-stores later rather than sinking the dependent ops below them, I think the source ordering matters more than I assumed. I'll try moving the `unkC1 = 0; unkB4 = 0;` lines to different positions — once after the unk20 accesses, and once before the `t = ...` assignment — to see which placement reproduces the target's scheduled order.

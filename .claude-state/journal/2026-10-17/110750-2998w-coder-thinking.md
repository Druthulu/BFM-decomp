---
ts: 2026-10-17T17:07:50.822Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm tracing which register holds the hoisted tagconst value — register 88 with a long live range looks like the candidate since it corresponds to the constant computed once at the top of the loop.

Mask (register 89, life 10) gets moved, which means the move threshold must sit somewhere between roughly 11 and 31 so that a life-3 case stays put while life-10 triggers relocation. I'm sketching the likely C-level pattern: loading the old tag, masking off the low bits, ORing in the new tagconst, and storing both the combined value and the masked payload back — essentially reconstructing what the generated code is doing with the and/or/store sequence.

Looking at the schedule, the mask's life span is set to just two instructions (from its definition to its last use), with the load happening right before it; I want to test whether the scheduler reorders this to match the target's load-and-mask-or-mask-store pattern and whether hoisting tagconst to the loop entry actually lets it keep a register this time.

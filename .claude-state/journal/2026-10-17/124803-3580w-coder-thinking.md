---
ts: 2026-10-17T18:48:03.282Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
I notice the register assignment is swapped between my version and the target—I have v0 and v1 flipped in the load/subtract sequence, so the subtraction ends up computed in the opposite order relative to which register holds the constant.

This looks like a local register allocation ordering issue tied to load-vs-constant sequencing rather than the actual arithmetic. Since the s16 case already gets correct register allocation for this line, I'm wondering if restructuring the constant expression—maybe computing the negative offset through a different variable type or casting the load differently—could force the allocator to pick registers in the right order for the s32 case too.

I'll try loading the value into a temporary first, then applying the subtraction afterward, which could reshuffle the pseudo variable lifetimes enough to match. I want to test this approach separately on both the -0x700 and -0x6C0 lines to see if either one shifts the register assignment favorably.

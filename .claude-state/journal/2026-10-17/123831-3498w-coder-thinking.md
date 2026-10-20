---
ts: 2026-10-17T18:38:31.661Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
I'm trying to track down unk98's type, noting it's s16 at offset 152, and want to dump the schedule to confirm the mechanism. I'm also wondering if the pin's effect comes from the hard register $2 write interacting with the earlier call in the previous block.

Maybe the u16/s16 cast is just a macro for a pointer dereference at offset 0x76, so that's probably not the source of the discrepancy. I should dump sched to verify whether sched1 actually hoisted the lhu instruction or if the ordering is already baked into the RTL generation.

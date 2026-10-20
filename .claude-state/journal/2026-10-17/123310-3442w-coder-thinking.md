---
ts: 2026-10-17T18:33:10.172Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac81395c556dc97c0
model: claude-opus-5-5[1m]
effort: medium
turnId: 2749fb46-32ea-40ac-942d-d9e5fb5596d6
---
I'm tracing how the register copy ordering affects where the addition reads from — if puVar2 becomes the copy target before the offset addition, I need to check whether CSE would then substitute that computation elsewhere, keeping the original pseudo alive as a separate value.

I'm trying to figure out why combine merges the load-and-move in my version but not in the target: maybe t's use spans a basic block boundary, or the pinned hard register v0 blocks the merge, or there's a volatile access forcing the copy to persist.

Then I consider whether the long-lived variable across both call sites is actually a different pseudo entirely, and how gcc 2.x would naturally generate the `lw v0; move s1,v0` pattern for a value living across a call.

I'm wondering if cse1 is collapsing the copy by propagating the temp into puVar2's later uses, leaving puVar2 dead since the register gets reused for the addiu result right after the move. To preserve two distinct pseudos, I'd need the temp to have a use that survives past the copy point, maybe by introducing a mode or arithmetic difference that blocks the propagation.

I should check the cookbook's catalog for entries tagged "copy kept" to see what pattern actually preserves the separate move.

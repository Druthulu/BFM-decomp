---
ts: 2026-10-17T18:39:29.450Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac81395c556dc97c0
model: claude-opus-5-5[1m]
effort: medium
turnId: 2749fb46-32ea-40ac-942d-d9e5fb5596d6
---
I'm working through local-alloc's register priority ordering: the short-lived -4 temp has fewer references and a shorter life, giving it higher priority to claim v0, which forces t2 (with its longer live range) into v1 to match the target.

Actually, wait -- if t2 is live across basic blocks, it wouldn't be handled by local-alloc at all but by global-alloc afterward, which could explain why temp grabs v0 first and t2 ends up assigned later to v1.

So maybe I should make t2 global by giving it a use in both blocks -- but that's the e1 scenario where it ended up as a1 due to conflicts with v1's live range. Let me check if puVar4 could serve as the temp instead, since it's already global across both blocks and the conditional.

Actually, maybe reorg fills the beqz delay slot by stealing the store from the join target block, since it executes on both paths regardless of the branch — that would make t2 a global spanning both blocks without reordering the asm. But then I need to check whether the store uses v1 or s1, since puVar2's copy still seems necessary for the later calls.

Wait — that just makes puVar2 global, not t2. Maybe block 1 has an analogous pattern where a HImode temp gets assigned twice to the same variable, which would force that variable global and push it ahead of locals in register priority, the opposite of what I want. I need the temp to claim v0 first, then have t2 claim v1 only if v1 stays free across t2's live range.

I'm trying to figure out why greg chose a1 instead of v0 or v1 for that temp — tracing whether v1's pseudo is set within block 1 at some point that creates a conflict, since its live range should otherwise be short and free.

Given the time budget running low, I'm considering a different approach: restructuring block 1 so the store to the 0xcc offset happens between the load and copy, hoping that forces CSE to merge the temp the way the target expects.

That doesn't work either since the target stores the value directly in a delay slot, not through my temp register. I suspect block 1 is hitting some kind of compiler merge pattern that I can't easily replicate, so I'll shift focus to block 2 instead -- maybe making a local variable global so it survives across the call boundary, similar to what worked in a previous case.

---
ts: 2026-10-17T10:51:24.702Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm considering whether a `while(0)` loop still leaves behind loop notes even though gcc can fold away the body as unreachable, since the loop-start/exit machinery still gets emitted before the constant-false test triggers the jump.

I'm not finding a path without a barrier, so I'm re-examining exactly where the target's barrier could sit instead — testing hypotheses about whether it's tied to a specific instruction like the zero-register move, or whether it falls within the prologue sequence. If the prologue is emitted as fixed, unscheduled text rather than RTL, that would explain why my instruction ordering (sw ra before sw s0) differs from the target's (sw s0, la, sw ra).

Comparing the two orderings, it seems the target genuinely has no barrier at the top, meaning a0/a1 placements come from a sequence where the base pointer stays unknown to the scheduler throughout, and cse isn't folding blocks 2 and 3. That leads me to reconsider cse's folding rule — specifically whether it gets undone when a live register already holds base+k, which could be happening with a1 holding base+4 as a call argument pointing into the record.

Then I recall cse's `use_related_value` mechanism: when folding a symbolic constant like sym+8, cse doesn't need a register holding that exact value — it can search for any register holding sym+M for some other M and adjust from there, since they share the same base symbol. That's the piece I think explains why block 2 isn't folding the way I expected.

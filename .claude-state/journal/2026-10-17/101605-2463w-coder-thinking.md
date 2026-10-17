---
ts: 2026-10-17T16:16:05.293Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb4a08fa100d7feb
model: claude-opus-5-5[1m]
effort: medium
turnId: dd20a3af-7bad-4cc5-bdfe-eb40b857c079
---
I'm tracing how combine merged the bx, by, and ang loads into a single a0 register assignment, with the ang load relocated to the position of insn 105 where the combined copy now lives.

Trying to reorder so a0 comes before bx/by doesn't work since the a0 copy is always emitted right before the call, after the bx/by loads — unless I move bx/by after the call entirely, but that changes the block structure. I'm also considering giving ang a second use so combine can't merge it, though that would alter the code itself.

I've spent a while on this specific angle; let me try a different track — maybe changing bx/by to a different type, or restructuring the call argument so the ordering naturally comes out right.

Actually, I'm realizing combine might refuse to move the ang load past intervening memory stores to p[]. So instead I should place the ang assignment earlier, before those p[] stores happen — that way the load stays put and still gets copy-propagated into a0 via local-alloc.

Maybe moving the ang assignment between the last two stores would shift its load earlier than the final sb, giving a different instruction order worth testing against the target.

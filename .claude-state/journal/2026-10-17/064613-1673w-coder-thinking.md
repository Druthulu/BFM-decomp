---
ts: 2026-10-17T12:46:13.333Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm trying to trace through a case where a value gets set via one instruction and then referenced in another, questioning whether CSE would simplify away the intermediate symbol or keep it alive, depending on relative cost of register versus symbol operands.

Then I'm considering whether the REG_EQUAL note really lives on the instruction that's dropped when combine merges the two patterns — if the destination's set survives into a split PARALLEL because it's still needed afterward, that could be where the note gets preserved or lost.

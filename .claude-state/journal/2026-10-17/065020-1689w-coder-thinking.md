---
ts: 2026-10-17T12:50:20.592Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm noticing no other jumps reach that inner branch, so only fallthrough remains, which means cse shouldn't have folded this since gcc couldn't have known t equaled 5. My hypothesis is that the beq originally targeted the inner merge test, and got redirected in a later pass like jump threading after reload, rather than during the earlier cse1 jump-following stage.

I need to figure out why cse would follow that jump at all — with flag_cse_follow_jumps, cse follows when the target label's use count is exactly one, treating the subsequent block as part of the same path, so if the inner compare resolves as known equal to 3, cse redirects the jump and the fallthrough also collapses since the label loses its other uses. To block this, the label needs at least two jump references, which makes me wonder if reordering the conditions or changing how the OR expression is evaluated during jump generation would prevent cse from treating it as a single-use target. I should check cse.c's basic block end conditions to see exactly what triggers the jump-following behavior.

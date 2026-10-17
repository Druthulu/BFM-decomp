---
ts: 2026-10-17T11:22:12.872Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm tracing register allocation: the result pseudo should map to v0 since it crosses blocks globally, while v stays local within its own block, which explains why the tied allocation differs from what I expected.

Thinking about ways to break that tie — maybe v becomes global itself if it's used in a later block, or maybe the call result feeds the condition directly without an intermediate variable. I'm testing whether moving the return variable earlier, or having it live across the call, would force it into a callee-saved register instead, but that seems like a worse match for the target's plain move instruction.

Actually, I recall gcc's combine_regs logic: a pseudo ties to hard v0 only if v0 dies at that point and doesn't conflict later. So if v0 is set again (hard reg) while v is still live, v can't reuse it and has to get its own pseudo. I'm wondering if this happens through expand_return's special handling of `return a && b` type expressions, which might jump-expand directly into the return register rather than going through a normal pseudo-to-pseudo copy.

I'm wondering whether the frame_offset==0 condition actually held in this case, since the function likely has local stack frame, which would mean that tail-recursion-of-&& optimization path didn't trigger here. Maybe the && gets wrapped in a type-conversion node that blocks the check — I should look at stmt.c to verify.

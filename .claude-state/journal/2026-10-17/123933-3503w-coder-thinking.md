---
ts: 2026-10-17T18:39:33.622Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
Tracing the scheduling order, I need instruction 60 to still be unscheduled right after 73 is placed, which means 93 must not have been scheduled before that point, constraining the dependency ordering further.

Thinking about why: gcc's `schedule_block` sometimes assigns a special priority (like 0x7f000001) to instructions that "birth" a register that dies immediately, pushing them to be scheduled first to reduce register pressure. That could explain why certain li instructions jump the queue ahead of others that are otherwise ready.

So maybe the fix is to give `one`'s pseudo a second assignment elsewhere so it no longer qualifies as a single-use birth, denying it the priority boost — perhaps by reusing `one`'s register slot for another variable like `k`, which is callee-saved and crosses a function call, in a way that doesn't change the generated code but changes the dependency graph enough to alter scheduling order.

I should check what register the target code actually assigns to ent in the i==0 block to confirm this hypothesis.

---
ts: 2026-10-17T11:55:36.121Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
The param reuse pattern confirms the move sequence matches target, which assigned v0 to the param pseudo. I'm trying to figure out why mine picked a2 instead — likely because v0 conflicts with the call result and block-2 locals in my allocation, whereas target's local-alloc avoided assigning v0 to those block-2 temps, freeing it up for the param.

Unless local-alloc only handles single-block pseudos, so maybe the live-across-blocks value is actually a hard register tied to v0 directly — perhaps from a return-value setup where `return f(...)` leaves the result in v0 before jumping to a shared return/null-check label, making v0 live across the branch without ever being a cross-block pseudo at all.

Tracing it further: a parameter pseudo P gets moved into v0 before a call, then reassigned from v0 after the call returns — since P isn't live across the call itself, global allocation can legally give P the hard register v0, but only if block 2's local allocator didn't already claim v0 for some local pseudo there. That depends on whether local-alloc avoids hard regs already live in the block, which would explain why the target's version differs from mine in which block grabs v0 first.

Maybe I should check how similar functions were cracked before—there might be crack notes in neighbours.txt for related functions marked with @crack.

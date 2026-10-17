---
ts: 2026-10-17T13:37:54.601Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I'm thinking through the global allocation priority ordering—since w gets scheduled first, ot would need either more references or a shorter live range to gain higher priority, or w would need fewer references or a longer live range to lose it; the register allocator sorts pseudos by this priority and picks hard registers like s1 accordingly.

Both pseudos cross calls, so I'm counting their reference patterns: ot is set from a parameter and four call results plus used as call arguments, while w accumulates many field loads. I'm trying variants—using w0 directly instead of a local copy of w, splitting field accesses between w0 and w so CSE doesn't just merge them back, introducing an intermediate pointer p to shift some loads off of w and see if that changes the instruction scheduling at the relevant offsets.

That approach hits a snag though: since p would end up sharing the callee-saved register with w anyway, the generated move instruction wouldn't match the target. So I'm shifting focus to GCC 2.7's register allocation priority formula, which weights allocno priority by reference count, loop depth, live range length, and size—meaning w's heavier use inside the loop body would score differently than ot's.

Counting references per iteration for both w and ot, I'm comparing which variable accumulates more weighted refs inside the loop versus before it, since that determines which gets prioritized by the allocator. To shift that balance, I could either stretch w's live range to lower its priority, or pad ot's reference count by introducing extra reads/writes, possibly through how the function's return value is handled.

Looking at the parameter copies again, I'm thinking of several variants to try: renaming the param to remove the local duplicate, returning through the ot assignment, restructuring the loop call, or narrowing ot's scope with a separate declaration. I'll write these out by hand as test files to compare.

---
ts: 2026-10-17T19:01:50.771Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm trying to figure out why rot gets staged into a pseudo register before the call rather than going directly into a0 like sv does — maybe it's related to how gcc orders argument evaluation, possibly computing args right-to-left or treating one differently because of the function's prototype with a mixed pointer/short signature.

I'm wondering if expand_call's logic about expensive values or short loops forces certain args into pseudos, and considering whether reusing the same variable for `rot` across both calls would make CSE treat it consistently across the loop.

I'm tracing how gcc's expand_call precomputes arguments into pseudo registers when later argument evaluation could clobber hard registers, and considering whether a variable holding `rot` gets reused across calls in a way that matches the target's behavior — trying to design a minimal reproduction where `q` stores the rot pointer and is passed into f1 then reused for f2.

Maybe q gets reassigned to the struct base for the three loads, letting cse fold the addresses and drop q's old binding to fp+24 — then q is reset to rot for f2, so by the time f3 is called with q and mtx, q still needs to hold fp+24 across that span.

Mapping out variable reuse...

So maybe it's about evaluation order: args get evaluated last-to-first, and only the last-evaluated argument (which ends up being the first logical arg) avoids getting a pseudo, since nothing after it could clobber it. That matches sv being first arg and going direct, while mtx as second arg needs a pseudo since rot gets evaluated after it.

Since args are evaluated last-to-first, mtx's pseudo gets computed before q is reassigned, so it can still reference the old value. Writing q as a separate statement before the call means it gets killed early, but the target likely reuses an earlier s1 pseudo from func_80017DC4's arg0+0x38 computation via cse, making q just a copy of that register. There are a lot of moving pieces here, so I'll just try this approach and see what happens.

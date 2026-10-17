---
ts: 2026-10-17T16:37:37.570Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac8178896d2313b85
model: claude-opus-5-5[1m]
effort: medium
turnId: 589d16b4-5a62-4ce6-8a45-63d170f3cb6e
---
This affects register allocation across the whole function since it's one large unit, so I need to budget real time here—maybe 30 minutes. I'm considering whether gcc 2.7's CSE respects the no-follow-jumps flag, and whether the straight-line code between case groups offers any natural label boundary to break CSE scope, before turning to look at func_80189250 as an alternative approach.

Rather than a pointer-indirect call, the target uses a direct load address instruction, so that path's out. I'm digging into how gcc 2.7's CSE handles symbol replacement: it likely finds the cheapest equivalent and substitutes the register for the symbol unless that register's class entry gets invalidated by a later reassignment. That gives me an idea—reusing the variable for something else after the call, like storing a return value into it, would break the CSE equivalence naturally.

Then I consider reusing the same variable as both the address argument and later as a derived pointer offset, which would invalidate its symbol-class membership and force the next group's variable to reload the constant fresh, matching the remat pattern I'm trying to explain.

But the ref-count requirement for rematerialization (needing exactly two references) breaks down if the pseudo gets reused across multiple statements, since its total reference count climbs past two and local-alloc would just allocate it a register instead. So I'm now wondering if the two groups actually pass subtly different forms of the same symbol — like a zero-offset array index versus a plain cast — that fold to the same value but are expressed differently enough in the IL to get separate CSE treatment.

This mostly looks like a case where CSE substitutes a constant address for a register holding that address, keeping the compiled output tied to specific access patterns rather than a clean base-relative scheme — which may just be a structural wall for this item.

Let me also check whether the call argument order or pointer-type casting around D_801C8344 could shift things, and quickly test the reuse-variable approach on group 1 to see if it causes rematerialization.

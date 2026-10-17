---
ts: 2026-10-17T11:32:03.703Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm tracing through the backward scheduling order to figure out whether instruction 40 (the fp load) ends up placed before or after store 27, since 27 uses the hard register holding the call's return value directly.

If fp is pinned to v0, then 40 and 27 form an anti-dependency where 40 writing v0 must come after 27 reads it, which would explain the target ordering with store 27 appearing between the lhu and sll instructions. I'm now wondering if there's instead a memory aliasing dependency between the load at 40 and the store at 27, since both touch the same symbolic address, which could also force this ordering.

I'm checking whether `memrefs_conflict_p` in 2.7.2's scheduler can actually distinguish a plain symbol from a `(plus reg symbol)` form, since it lacks the base-term logic from later alias.c versions. It seems odd that it decided there was no conflict—maybe this comes down to some MEM_IN_STRUCT_P heuristic treating a fixed-address scalar specially rather than true alias analysis.

I'm recalling that `true_dependence` in 2.7 has a rule where a fixed-address scalar not marked MEM_IN_STRUCT_P can't alias a varying-address struct or array reference that is marked MEM_IN_STRUCT_P. The array element D_80182668[i] would get that struct flag while the scalar store doesn't, which explains why the scheduler sees no conflict—so I'm wondering what happens if the array access instead goes through raw pointer arithmetic without the struct flag set.

Checking GCC 2.7.2's expr.c logic, the MEM_IN_STRUCT_P flag for an INDIRECT_REF on a pointer gets set based on whether the dereferenced type is an aggregate, so pointer arithmetic on an array could still trigger the same flag depending on how the type resolves.

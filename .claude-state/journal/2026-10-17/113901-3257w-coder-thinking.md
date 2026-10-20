---
ts: 2026-10-17T17:39:01.391Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm checking the operand order in the addu instruction — it looks like my register assignment has pathBase and offCopy swapped relative to the target, so offCopy should come first as the second operand.

I recall my source used pointer arithmetic with `offCopy + pathBase`, and in gcc 2.7's c-typeck, pointer_int_sum always builds the expression as pointer-op-plus-int-op, which fixes the operand order at the tree level rather than leaving it to RTL canonicalization. That means the ordering discrepancy likely traces back to how the original expression was written in the source, not how the compiler reorders commutative operands.

I'm considering whether forcing both operands to be plain ints — by casting pathBase to int or declaring it as int rather than a pointer — would let me control which operand ends up first, since type-driven pointer arithmetic rules would no longer apply. I'll try casting approaches and also test declaring pathBase as a plain integer type to see which produces the matching `addu a0,s0,s2` ordering.

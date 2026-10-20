---
ts: 2026-10-17T17:20:39.969Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm recalling GCC's local-alloc quality comparison formula, which weights a pseudo-register's priority by its log2 reference count multiplied by the reference count and some quality factor.

Then it breaks ties by qty number order (lower qty assigned first, based on birth order during insn scanning). Trying to reconcile my memory of r73/r76/r75/r78's births and deaths against the table's observed live ranges, I'm wondering if insn luids are counted including notes, which could shift the birth-death arithmetic enough to flip p1 ahead of p2 in priority. Rather than keep theorizing, I think I need to work empirically from the actual priority numbers to see what ordering would make p1 win.

Maybe shortening p1's life by reordering the stores — putting p1's store before p2's load — would change the outcome, so I'm comparing that hypothetical instruction order against the target listing to see if it matches.

---
ts: 2026-10-17T17:35:37.869Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm tracing how luids get assigned based on instruction priority, which in turn depends on the dependency chains from LOG_LINKS — checking how the scheduler walks the preceding instructions each one depends on.

Priority reflects the longest path from block start, so for backward scheduling a high priority means an instruction sits deep in the chain and gets scheduled early, while low-priority leaves (like a standalone lui with no predecessors) end up placed last unless "birthing" boosts them. That explains why most lui instructions float to the top of the block, except cases where the lui's destination register only has a single set — those behave like birthing instructions and get pulled down to sit right before their use, which matches the target scheduling I'm comparing against.

Now I'm wondering whether this single-set behavior actually comes from the MIPS "li" assembler macro expanding large constants into lui/ori pairs at output time rather than at RTL split time — meaning the scheduler sees just one instruction (the li) with one set, so it's treated as birthing and placed late, unlike my version where the split already happened earlier into two separate RTL insns.

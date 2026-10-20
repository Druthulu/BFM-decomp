---
ts: 2026-10-17T17:34:00.706Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm comparing register allocation between versions — noticing many constants get hoisted into fixed registers, and the mlo/mhi/q assignment order differs, with t2/t3 apparently unavailable in mine due to some priority ordering around "qty_phys_sugg."

I should check whether these constant pseudos have REG_EQUIV const entries that get moved during sched1, or whether this is actually a global-alloc issue with block crossing. I need to look at the lreg output for "Register 79" and "80" to see the hard register ordering.

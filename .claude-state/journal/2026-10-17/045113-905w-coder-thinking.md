---
ts: 2026-10-17T10:51:13.496Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm noting that combine generally doesn't adjust ref counts except in rare cases, so an eliminated ref still counts there. But local-alloc's optimize_reg_copy_1/2 does adjust refs when rewriting copy insns—specifically when a copy's source dies, it tries to replace the destination with the source in subsequent instructions and updates the ref counts accordingly.

Combine doesn't adjust `reg_n_refs` when deleting refs, so deleted jump refs still get counted; local-alloc.c also shifts refs between registers during copy rewriting. I'll look at those locations in local-alloc.c next.

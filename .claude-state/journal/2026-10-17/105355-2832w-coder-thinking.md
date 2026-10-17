---
ts: 2026-10-17T16:53:55.054Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'm sketching a natural PSY-Q style rewrite, setting up pointers into the OT table and writing initial packet fields.

Now I'm checking whether gcc 2.7's scheduler would reorder these stores based on alias analysis of offsets from the same base pointer, comparing against the target's actual store order (tag byte, then flags, size fields, position, color bytes, then the final OT link pointers) to see if the original source order in the C code matches.

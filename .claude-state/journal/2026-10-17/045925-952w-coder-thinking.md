---
ts: 2026-10-17T10:59:25.285Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm working out the O-battery variant for v_callsz.c, comparing how the initialization order of t3v, k, and j differs between the O1 "jtk" and O2a "inx_k" variants and how the x-store indexing changes between them.

More O2 variants follow using m and i instead of k, plus an O2d version where k is set before j and t3v stays inline. Then an O3 "allin_k" variant moves pb, m24, and mhi into the common block before use with t3v as an inline expression, and I'm preparing to write these all out as replacements.

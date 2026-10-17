---
ts: 2026-10-17T13:52:04.333Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
This matches without needing a lever—no asm, no pin required. The trick is reusing one pointer local for the matrix address and then for the RotTransPers input vector, which is a legitimate variable reuse rather than a dead store since r4=v actually feeds into RotTransPers. I want to double-check there's no asm in s3a and that the structure holds up before calling this a win.

Found the issue: a pointer local holding `&D_800AF648` gets reused as the `RotTransPers` input, and reassigning it before the second call breaks CSE's address equivalence, causing `&D_800AF648` to be rematerialized.

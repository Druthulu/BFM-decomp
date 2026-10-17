---
ts: 2026-10-17T16:12:00.503Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm weighing whether this comes down to a local allocation tie between the field reference and the adjacent value, since the field only wins if its priority beats the adjacent one—perhaps by having the field variable directly become the destination register rather than a separate pseudo.

But that approach seems to produce the wrong register scheme, so instead I'm considering making the adjacent value span multiple blocks by computing it as a shifted product variable, which gave correct registers in one variant but had the scheduling order wrong—now I need to check how the first scheduling pass orders instructions in that variant's second block compared to the working version.

---
ts: 2026-10-17T16:08:29.858Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I should look into the dump tools for non-header translation units—cc1_dumps_tu.sh paired with alloc_table.py seems to be the right approach for TU dumps. I need a TU with the body spliced in, so let me check how cc1_dumps_tu.sh is actually used before writing my own splicer script.

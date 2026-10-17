---
ts: 2026-10-17T12:05:01.069Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I notice func_801833F0 in SC02_016 and SC03_104 has no asm, meaning lever-free versions already exist. I want to check if these are byte-identical by trying SC02_016's function body renamed to func_801813B4 against my target, accounting for possible type name suffix differences across translation units, then seeing what compile errors surface.

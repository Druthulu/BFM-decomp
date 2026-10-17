---
ts: 2026-10-17T05:15:10.169Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f214c1b8ceabcd8
model: claude-opus-5-5[1m]
effort: medium
turnId: edd2b196-9038-4e7d-9ca7-b103d9ac818f
---
I'm examining func_80150480, which uses inline assembly to set v0 but is declared with an s32 return type without an explicit return statement — checking whether this mismatch, or the similar pattern in func_801504D8 where a void function's v0 is stored after the jal, is the actual signature lie I'm looking for among the legacy-T7 functions.

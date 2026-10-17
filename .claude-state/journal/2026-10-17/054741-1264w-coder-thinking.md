---
ts: 2026-10-17T11:47:41.087Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm trying to recall how gcc 2.7.2 handles small struct returns on MIPS—specifically whether a 4-byte struct gets returned in memory or in a register, checking how RETURN_IN_MEMORY is defined in mips.h and whether it's tied to the ABI_64 condition.

Also with -fpcc-struct-return, aggregate_value_p forces all structs into memory regardless of size, so I'm checking whether that flag changes the behavior for the MIPS target.

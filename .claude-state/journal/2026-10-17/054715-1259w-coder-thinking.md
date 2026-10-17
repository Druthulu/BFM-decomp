---
ts: 2026-10-17T11:47:15.003Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm wondering if this is a small struct return case, like a 4-byte struct of packed shorts, and whether the MIPS gcc 2.7.2 toolchain used for the PSX returns such structs via hidden pointer or in registers depending on its struct-return convention.

Looking at the target assembly would clarify this, but I also need to check how the caller passes the struct address, since with a struct-return convention the caller typically supplies a pointer to a temporary rather than the explicit argument I assumed earlier.

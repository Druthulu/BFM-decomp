---
ts: 2026-10-17T18:44:42.084Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
I'm thinking through why the asm output operands landed in registers t4-t6 instead — it comes down to how the register allocator orders candidates for MIPS, and GCC's allocation order seems to be picking a1, a0, a2 rather than the expected sequence.

Actually, getting t4-t6 without explicit pins seems unlikely since the allocator would grab t0-t3 first if they're free. This points to the source using one of the standard PsyQ GTE macros that hardcode $12-$14 directly in the asm string with clobbers — like gte_SetRotMatrix, which explicitly loads into $12/$13/$14 and issues ctc2 instructions. That would explain the fixed registers without needing a manual pin, since it's just how the SDK macro is written.

I confirmed t4-t6 feed GTE inline-asm macros matching PsyQ's `gte_SetRotMatrix`/`gte_stflg` which hardcode $12-$14. Now checking whether the headers already define these.

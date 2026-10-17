---
ts: 2026-10-17T05:19:13.177Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f214c1b8ceabcd8
model: claude-opus-5-5[1m]
effort: medium
turnId: edd2b196-9038-4e7d-9ca7-b103d9ac818f
---
I'm noting that func_8017E3D0 is a zero-arg caller with void return, so it never sets v0, and its live a0 register is undefined since it takes no parameter — this is the same "lying callee" pattern seen elsewhere where zero-arg callers still pass a live a0.

I'm considering unaliasing the conflicting definitions: renaming the aliased copy back to func_8017E3F0, dropping the asm wrapper, and fixing the external declarations so the def and every caller's decl agree on the real return type, since param arity doesn't matter for these return-type lies.

For 80180B68 I need to change its `extern s32 func_8017E3F0(int)` declaration to `extern void func_8017E3F0(int)`, while leaving the K&R zero-arg case in 8017E3D0 alone since that's not a return-type lie. I'm now walking through the remaining copies — SC03_111, SC04_009, SC06_015, SC06_018 — checking whether each definition's signature and body actually match void returns or if they're hiding a live return value.

Rather than reading full disassembly, I'll just scan the tail instructions of each function to see if v0 gets written on the return path without a following jal, which would indicate a real return value being discarded.

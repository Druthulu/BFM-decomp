---
ts: 2026-10-17T11:48:07.685Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm trying to work out why a 4-byte struct with two 16-bit fields would get SImode in gcc 2.7.2's return value handling, checking whether struct layout mode assignment depends on alignment matching the mode's required alignment in stor-layout.c.

Since MIPS has STRICT_ALIGNMENT set, that struct would actually fall to BLKmode and get returned in memory with v0 as the address, and its 4-byte copy would normally use halfword moves rather than a single word move — so I'm questioning whether a struct of two shorts even matches the observed word-copy behavior, and considering alternatives like a plain int field or a union that would naturally get SImode and avoid memory return altogether.

Maybe the return type is actually a pointer, with the function changed to take and return `s32 *a0`, directly returning the pointer itself rather than a struct. That would change how sched2 treats the final register-to-register move—since the return value copy into v0 happens after the store, I'm wondering whether scheduling could still pull that copy into the load delay slot or whether it stays unfilled, matching the observed nop.

Rather than reasoning further, I should just test this: modifying the extern declarations to match the new signature will conflict with the real header, so I'll make a scratch copy of the translation unit with the changed decls, splice in the simplified `return a0` version of the function body, and see if it actually matches through the matching tool.

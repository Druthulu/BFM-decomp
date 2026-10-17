---
ts: 2026-10-17T12:40:33.899Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm digging into why cse2 recognized the register as a known constant but didn't fold it into the memory address expression — tracing through fold_rtx's handling of the PLUS case to see whether it correctly substitutes the equivalent constant for the register before simplifying.

I notice free.c's version cast the symbol to an int before adding the offset, unlike f2's direct pointer form, so I'm checking whether that cast changed how the address was represented at expand time — specifically, whether the constant plus-expression was already baked in before cse ever ran, by looking at the pre-cse jump dump around insn 12.

To test this, I want to compile p0 with its plain `base = D_800A5E94` usage and check whether the resulting addresses come out absolute, which would clarify how cse1 is actually handling this case.

---
ts: 2026-10-17T17:15:15.116Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm comparing how the target assigns arg0 reloaded into a0 with c=3 into v0, versus mine where arg0 gets reassigned directly into v0 -- wondering if GCC 2.x would actually split the arg0 parameter pseudo that way, since local-alloc typically treats it as a single pseudo.

I should try different variants: introducing a new variable for the second pointer, declaring p1 as a pointer type, reordering statements, and using an s16 type for c to see if that changes the register allocation pattern.

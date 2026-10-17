---
ts: 2026-10-17T16:48:52.269Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm thinking that CSE's forwarding only happens within a single block, so reload after store might need the store and test separated by a label into different basic blocks to reproduce the pattern — sketching an example with a conditional modifying `*p` to test this.

But testing that version still shows the same forwarded behavior, suggesting jump threading (via -fthread-jumps) merges the branches back into one extended block before CSE runs again, defeating the separation. I'm now considering whether a different addressing scheme — like referencing the symbol directly instead of through the pointer — might break the equivalence CSE relies on, though direct addressing still seems to canonicalize to the same thing.

I'm wondering if the stored value in `*p = *p - 0x10` is re-read from memory rather than kept as the register value, since old gcc's assignment expressions return the lhs reloaded from the target when the value is needed — that reload could be exactly what prevents CSE from forwarding the register.

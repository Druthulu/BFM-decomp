---
ts: 2026-10-17T16:33:31.871Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm comparing instruction ordering between my output and the target: mine has bx, ang, by, jal while the target wants ang, bx, by, jal, since the backward scheduler picks from the jal and works its way up based on priority and dependencies.

The key difference seems to come from whether the a0 load gets combined into the hard-register set near the call site, versus staying as a separate pseudo load that gets copied into a0 right before the call — that placement choice likely determines whether ang ends up early or late in the final order.

I'm now wondering if an intervening memory store between the loads and the call could block combine from merging the pseudo set into a0, which would explain why reordering the source (putting the ang load before some store) changes the output ordering.

I'm questioning whether the byte store to p[0x16] truly must precede the ang load given aliasing rules, since a QImode store to a varying address could conflict with any memory read, forcing that ordering — but that doesn't match the target sequence either. Trying another angle: maybe ang's pseudo gets reused elsewhere so combine can't fold it away, but I don't see a second use in the target code.

Combine also refuses to merge across insns with volatile references, so I'm wondering if the bx/by reads go through a declared-volatile pointer like bidx, which would block combine from relocating a memory load past that volatile access.

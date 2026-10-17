---
ts: 2026-10-17T16:50:22.719Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm looking at redundant register moves in the compiled output, like a value being copied from v0 to v1 then decremented, and trying to figure out why copy-propagation isn't eliminating it—checking whether v1 actually gets used again later in a way that justifies keeping the move alive.

I'm wondering if the source structure is different — maybe it's something like loading a short field and decrementing it, with the original value possibly reused later, which would explain why the copy survives instead of being folded by combine. I'm also considering whether combine's rules about pseudo liveness between pattern insns explain why this particular copy can't be merged.

Actually the move could be scheduled into the delay slot from code before the branch entirely, meaning v1=v0 happens prior to the test, in a separate basic block from the subtraction. That would explain why combine never sees them together — they're split across the branch boundary, with the test itself possibly checking v0 directly rather than v1.

I'm going to search the target asm file for this pattern.

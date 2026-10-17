---
ts: 2026-10-17T13:35:25.420Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I'm wondering if the register allocation priority differs because the original compiler ordered the pseudo-variables differently, perhaps due to how the CSE'd address variables were created, rather than an actual tie in lifetimes.

Alternatively, I'm considering whether bumping p's reference count to 16 would push its priority above r79's — this would require three additional counted uses of p, but refs are tallied during the flow pass before local-alloc, so any extra reference would need to come from an insn that doesn't get deleted as dead code later.

I'm also weighing whether reducing r79's refs by routing some aB9A02 loads through the scalar declaration or a second pointer variable could work, but CSE would likely just merge duplicate pointers back together, and the scalar form wouldn't change the ref count anyway. I keep coming back to the fact that p is referenced throughout the whole function body, so splitting its live range isn't really an option, and the original address computation for p might have combined the base and offset differently than what the disassembly shows.

Now I'm counting p's actual reference count in the target block — thirteen uses, all within the single basic block — which makes me wonder whether local-alloc simply can't apply here since everything's confined to one block, pushing this into global allocation territory where priority is computed from reference frequency, live range length, and pseudo size instead.

I'm now considering whether a label could split the function into multiple basic blocks without changing the emitted assembly — since a bare label emits no instructions — and whether a goto that's later optimized away could leave behind just the block boundary, forcing r79 to be treated as live across blocks for global allocation purposes.

With a single-block function everything is handled by local-alloc, so I'm wondering if changing where p's set insn occurs — like a2's attempt to move it after the store at 7877 — actually shifted anything, since the score stayed the same. It's possible cse is already propagating the constant symbol into p's uses, leaving the pseudo and its load-address instruction intact regardless. I should just dump a2's allocation output to check directly.

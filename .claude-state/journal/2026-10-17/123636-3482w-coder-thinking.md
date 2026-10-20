---
ts: 2026-10-17T18:36:36.246Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm recalling how local-alloc's update_equiv_regs pass handles registers with a REG_EQUAL constant that are set once and used once—it can relocate the setting instruction closer to its use, though I'm trying to pin down whether that relocation requires the set and use to be in the same basic block.

Given that s3 occupies a pinned hard register ($19) yet still got moved, I'm thinking about how to break this behavior: either make s3 referenced more than once, or make its value non-constant so REG_EQUAL doesn't apply, mirroring what "Launder" seemed to do. I'm now considering what the original C source might have actually looked like—maybe a pointer load used elsewhere—to explain why `la s3` ended up positioned before the call with its use appearing after the branch.

I'm digging into how GCC 2.7's update_equiv_regs pass decides to relocate such an instruction, specifically the rule that single-set registers with a constant REG_EQUAL note become REG_EQUIV and get moved if their one use lies in the same basic block. The complication is that s3 is a hard register from a `register asm` local variable, which in GCC 2.x RTL is represented directly as a hard reg rather than a pseudo, so I need to check whether the move logic's regno threshold check even applies to it.

---
ts: 2026-10-17T18:51:06.699Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm wondering if that addiu computing s0 as arg0+5 could actually sit before the branch entirely, with scheduling moving it later — that would explain why it shows up in the fallthrough path despite being pinned to register $16.

Then I consider cse's basic-block boundary logic: if the extended basic block covers the whole loop, the "last use outside the block" condition for a pseudo could become false, keeping the canonical register intact for the pointer load rather than substituting the laundered copy. That would mean the target's first load genuinely needs to go through the opaque alias while s0 still derives from the original argument register, which is the asymmetry I need to reproduce.

I'm now exploring whether reassigning arg0 mid-function before computing s0 could break it out of the same equivalence class as s2, so cse treats them as distinct expressions. I'm also considering whether the initial move into the pseudo is from a hard register like a0, since cse's canonicalization rule prefers pseudos over hard registers once FIRST_PSEUDO_REGISTER is crossed, which could explain why s2 ends up as the canonical form that later loads reference.

Maybe addiu references the hard a0 directly because parameters aren't copied into pseudos when unoptimized that way, or combine merges the entry copy into one use — but if that pseudo P has two uses (s2=P and s0=P+5), combine can't eliminate P entirely, so something else must explain the hard-reg reference.

I recall combine has a specific check against substituting argument hard registers to avoid extending their lifetimes across the function, which might be what's blocking or allowing this pattern.

Rather than keep reasoning theoretically, I should just try variants empirically: skip the separate cursor variable and use arg0 directly, compute the offset before the register copy, or reorder the load relative to the copy, and see which one actually produces the desired codegen.

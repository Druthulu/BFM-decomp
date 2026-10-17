---
ts: 2026-10-17T16:44:05.851Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'm noticing that my scheduler reorders the argument moves differently than the target, likely because when col is a hard register the division expansion pins it, whereas with a pseudo register the arg setup moves get scheduled into an earlier block.

I'm trying to figure out why move a0,s0 ends up scheduled before the division in my version rather than after like the target — possibly region scheduling moving it up, or a hard-register pinning difference. I think I should try alternate C expressions for the column computation, like separating the division into its own statement or restructuring the function call argument, to see if that nudges the compiler's scheduler to match the target's instruction order.

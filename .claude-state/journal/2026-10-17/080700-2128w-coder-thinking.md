---
ts: 2026-10-17T14:07:00.894Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm working through how qty_n_refs weights each pseudo-register by usage count and loop depth, trying to trace how a value like val plus its incremented temp gets counted separately in the reference tally.

I'm reconsidering the comparison priority logic—since qty_compare sorts ascending by priority difference, the higher-priority pseudo gets allocated first, which means I need to figure out whether val's two sets (prior to combine merging val = val+1 into a single definition) actually survive to the local-alloc stage where life length and quantity are computed.

But if const1's lifespan from the early load to the late store is just as long as val's, const1 shouldn't actually win priority unless there's some other factor—maybe register allocation order processes v0 first regardless of quantity ranking, or val's quantity has a suggested register binding that changes how the comparison resolves.

I should dump the register allocation table directly to see how pseudos map to hard regs instead of reasoning it out further.

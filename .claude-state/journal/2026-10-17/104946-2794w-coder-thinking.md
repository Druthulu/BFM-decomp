---
ts: 2026-10-17T16:49:46.733Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
D_80115118 being at address 0 is odd, possibly an inlined extern defined as a macro to an absolute address. The jump dump also seems to be missing part of the comparison, likely truncated by my regex, and it looks like cse1 followed the jump with label 24 possibly removed by threading.

To stop cse from forwarding the store to the load, the load needs to sit in a separate extended basic block — one preceded by a label with multiple predecessors where the value could differ. In this case, label 24 is reached both from the beqz branch (value 0) and the fallthrough path, which should make cse treat it as a new EBB and forget the value. Yet the dump still shows forwarding at insn 27, suggesting jump1 already threaded the jump before cse ran, possibly retargeting label 24 so cse1 sees a merged single-predecessor block instead.

I'm now wondering whether restructuring the conditional so the zero-path doesn't carry known information about the second test would prevent this threading, but variations like inverting the condition don't change the underlying shape. I should look more closely at how D_80115118 is declared in the header to understand why reg72 is being set to a constant zero.

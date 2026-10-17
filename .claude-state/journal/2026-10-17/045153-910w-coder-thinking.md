---
ts: 2026-10-17T10:51:53.325Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm thinking about whether these are used as SET source values for computing addresses rather than direct memory addresses, and working through MIPS address costing to figure out why CSE would fold a constant offset into a base register addition when the cost comparison seems ambiguous.

I'm now tracing through find_best_addr's logic for when it folds an address like (plus base const) into its constant equivalent versus keeping the original reg+offset form, comparing costs (1 for reg+const vs 2 for a pure constant address) and checking whether the class lookup finds the folded or original expression cheaper depending on what's hashed in that equivalence class.

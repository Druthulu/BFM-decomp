---
ts: 2026-10-17T13:44:38.462Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm noticing the address for pin4 got CSE'd into s0, which seems natural since the calls share the same address expression. The second scope without a pin gets rematerialized since the first address wasn't pooled into a pseudo, and since the first is unpinned, CSE links them together. I'm wondering if making the functions take the address through a differently-typed expression could break that sharing.

I'm now considering whether CSE still unifies the two calls' symbol constants even with a type cast, since gcc 2.7 treats symbol_ref constants for the la macro or HIGH/LO_SUM split specially. CSE normally operates across extended basic blocks, so inserting a label or jump target between the two calls might break that equivalence — but that would require adding real code rather than dead code. I'm also wondering if the two addresses differ in form, like one being passed as an array versus a pointer to the same symbol.

Actually, maybe the real explanation is rematerialization: if the address pseudo is REG_EQUIV to a constant and crosses a call without being spilled, gcc's reload can rematerialize it into a free hard register like s0 rather than keeping it live across the call. That would explain why s0 shows up only where it's actually free in the target's register allocation, depending on what else is live at that point.

But I should also consider whether the two calls actually reference the same symbol at all—maybe the target uses two different labels (like D_800AF648 vs something else) that happen to resolve to the same address post-link, which would explain divergent codegen without needing a different allocation theory. I want to check the actual target assembly relocations for those two calls in the ov_SC02_035 file to settle this.

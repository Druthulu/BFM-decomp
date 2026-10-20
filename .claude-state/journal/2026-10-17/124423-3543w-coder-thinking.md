---
ts: 2026-10-17T18:44:23.852Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I'm wondering if the load and store are actually accessing overlapping memory through a struct field, which could explain why D_801F8744 and D_801F8747 look like separate symbols — maybe splat is auto-naming based on byte offsets within the same structure rather than distinct relocations.

The reloc symbols come from compiling the original source, and the bank judge seems to require these relocations to match exactly, so the dependency issue must come from somewhere other than symbol naming. I'm now considering whether a varying index into the store address could create the dependency, or whether reordering which store instruction gets selected during codegen might force the needed overlap.

I should look at the scheduler's trace to see what priority ordering is actually being used, especially around where the sb instruction appears relative to the lw in the target versus mine.

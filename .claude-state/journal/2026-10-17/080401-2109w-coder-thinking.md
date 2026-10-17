---
ts: 2026-10-17T14:04:01.230Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm noticing the shift difference between signed and unsigned versions seems small, but comparing the 'l' pattern (shift then mask in two steps) versus 'e' pattern (copy, shift, mask) shows a much bigger instruction count gap—likely because the extra copy adds a reference that propagates through the count.

I'm tracing whether dead copy instructions get counted before flow deletes them, since that timing matters for whether CSE-replaced uses still register. For the combine pass, I'm checking whether the shift-then-mask sequence collapses into fewer instructions, and whether chained copies like `s1 = fld` followed by redundant self-assignments get dropped as no-ops, which would explain the discrepancy in reference counts between the two forms.

Trying variant 'q' with a redundant double mask doesn't quite work since it's semantically a no-op that feels artificially inserted just to steer the pass count. I'm wondering if a more natural explanation is that the field is actually a bitfield, which would make gcc generate extraction code naturally rather than through contrived redundant masking.

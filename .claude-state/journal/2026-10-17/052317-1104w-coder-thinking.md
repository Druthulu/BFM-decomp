---
ts: 2026-10-17T11:23:17.643Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm noticing that in md_MAIN_011, the global variable gets re-read multiple times rather than cached, which differs from our target where the load happens once and the result gets reused for comparison, storage, and masking—suggesting the source re-read the global while CSE forwarded the load within the same block.

Checking the field offsets in md_MAIN_011 versus our function, both follow the same cur/trig/prev/cnt layout with 4-byte spacing, just at different absolute addresses. I'm now wondering whether GCC's handling of absolute symbol addresses versus base-relative access is the real source of the discrepancy—specifically whether MIPS codegen forces every global symbol reference through a register before the memory access, which would explain why the instruction pattern looks different despite identical logic.

Actually, I'm probably overanalyzing this edge case. Let me just check the timestamp to get a sense of how long I've been on this.

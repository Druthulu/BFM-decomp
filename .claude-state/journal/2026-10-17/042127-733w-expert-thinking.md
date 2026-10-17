---
ts: 2026-10-17T10:21:27.565Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a28afe298c346ad4e
model: claude-opus-5-5[1m]
effort: medium
turnId: 19fadc38-27f9-43cf-8450-c53af22fd50b
---
The MEM_IN_STRUCT finding is already covered by existing cookbook entries, and the address-taken slot order case is close enough to an existing one too, so I'll note both as already covered rather than adding new entries. I'm logging this and recording baseline counts at HEAD before the gate finishes running.

After the gate: pins rose to 1711, asm dropped to 1355, gte-levers hit 0, defs down to 1, and residue collapsed to 2042 rows across 3067 sites — I'm verifying the per-kind breakdown adds up correctly against both before and after totals. The pin increase of 22 traces back to macro expansion converting nine one-off asm macros into inline pins, consistent with the 48-site removal noted earlier. I'm also flagging that the plan's stale 808/205 figures don't match the live 543/198 counts, with a small discrepancy from refused rows appearing post-rewrite.

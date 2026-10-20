---
ts: 2026-10-17T17:49:34.192Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af8c379eaae6cf6ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 4f5d1d7b-243b-4976-9079-51d9b9c05b4b
---
I should rename "levers" to "Shape notes" and revise the bullets: the goto loop point should note it replaces the `$7` pin and the nine `__asm__("")` pads, and since there's no do-while there's no NOTE_INSN_LOOP_BEG, so loop.c never runs and D_80073140[i] is never made a giv nor does it hoist the D_800C6DD0 address. The a1v bullet should reference move_movables.

The NOTE_INSN_LOOP_BEG mention doesn't strictly apply anymore but it's still a useful shape fact, so I'll leave it as-is rather than treating it as a lever to adjust.

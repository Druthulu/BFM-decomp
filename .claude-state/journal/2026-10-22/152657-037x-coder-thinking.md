---
ts: 2026-10-22T21:26:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YLECfwKflCrwCGLHAZbP
---
Now the only mismatch is in the arm4 region (index 82 ≈ 1388+82*4 = 14d0). Hmm, 82*4 = 328 = 0x148 → 1388+148 = 14d0. That's arm3's zero stores region.

Wait for v12: mine has at 82 (14d0) something else and sh zero,36 at 83. Target has sh zero,36 at 82.

Arm3 in target: 14c0 sh32, 14c4 li1536, 14c8 sh34, 14cc li-80, 14d0 sh0-36, 14d4 sh0-46, 14d8 j, 14dc sh48.

So in v12, arm3's sh0-36 is one slot later. Since v12's source order is unk20, unk22, unk2E, unk24, unk30 — sched1 must reorder.

Hmm, both v12 and v17 differ in arm3's schedule by one slot.

Let me look at the full arm3 disassembly of v12 and v17. Let me dump with --keep for v12.

Actually, better: the difference is the position of the sh0-36 relative to something. Let me get the full disassembly of v12's arm3.

---
ts: 2026-11-06T17:21:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8r4bOryL6EHO8B6pxAqW
---
15.9 min. Let me run 2-3 more batches (~2 min), then record at ~18-19... I need 20. Let me do a slightly bigger final batch and then finalize.

Ideas:
- Try `m24` with different declaration orders relative to ot/otAddr.
- Try making the mask a `u32` but with the `and` expressions using `m24 & 0xFFFFFF`? adds.
- Try changing the 0xFF000000 constant's spelling (it's in a1) — irrelevant.

Actually, let me test whether the mask's allocation changes if the 0x8E constant store is removed entirely (an experiment to confirm the conflict). If removing the p2 constant store moves the mask to t6, then the conflict is confirmed and maybe a different p2 store form could work. But removing a store changes bytes anyway.

Let me do a couple of these diagnostic runs (they count as tries) and then finalize.

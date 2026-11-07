---
ts: 2026-11-06T10:18:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BLNznHIIlmLr7ATbJ85J
---
d15 is score 2: just one store `sw v0,28(s2)` moved from position 120 to 123. That's the `((Unkstruct_800B5CB8 *)a0)->unk28 = q;` store, reordered relative to something.

So close! Let me see the surrounding code at 115-130 in both. Let me dump d15.

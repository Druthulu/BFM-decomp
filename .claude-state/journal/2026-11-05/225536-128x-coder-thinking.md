---
ts: 2026-11-06T05:55:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9h3bMixFXbAxROiY10JE
---
k10 (`if ((cc & 0xFFFF) != one)`) = 10 with 96 ins! Interesting — it's close. That's the "mask makes the value less known" idea: gcc adds an `andi` (96 vs 95 = 1 extra) but the second test survives!

Let me look at k10's diff. If we can remove the extra andi somehow, we might get 0.

Actually wait: 96 ins vs target 95 = 1 extra instruction. Score 10. Hmm.

Hmm, but this is interesting: masking cc with 0xFFFF makes gcc unsure. Since cc is s32 holding a sign-extended s16, `cc & 0xFFFF` == cc only if cc >= 0. gcc's range analysis should know cc ∈ [-32768, 32767]... but apparently it doesn't fold the AND, and the second test survives.

Let me see the diff.

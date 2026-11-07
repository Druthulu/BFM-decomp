---
ts: 2026-11-06T15:21:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dkrX4aTvRNt2NruodmBd
---
Item 1: best real-C = 14 (a1), best overall 2 (b4 identity). 22 candidates + earlier distinct ones (a2, b3, b6, c?, d2, d3, d5, e1-e4, h2, h4, i*, j2, j5, k4, k7, k8, l2, l3) = well over 30 tries.

Hmm, wait. a1 scored 14 (237 ins!). Earlier I measured a1 = 14 too. a1 keeps 237 ins (the count matches!) but score 14. Let me look at a1's diff — maybe a1 is closer than I thought and a small tweak cracks it. a1 = split vol: `vol = (0xA0-av)*0x7F; vol = vol/0xA0;`. Score 14 with 237 ins. Let me look.

Actually earlier I dismissed it. But 237 ins and score 14 — let me see the diff. If the issue is the multiply result going into vol's reg, maybe a different split point fixes it. Let me look at a1's diff.

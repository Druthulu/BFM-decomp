---
ts: 2026-11-06T11:33:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_F9P8moYu3YOl4IMqNAP1
---
Baseline good: 120 insns.

Now write v0: strip barriers and launders, keep pins.

Let me create v0.c from orig with sed deletions of lines. Lines to remove in the body: 2455 barrier, 2457,2458 launders, 2465 barrier, 2471 barrier, 2478 barrier. In body coordinates (body line 1 = 2432): 2455→24, 2457→26, 2458→27, 2465→34, 2471→40, 2478→47.

Let me write v0.c manually via Write, based on the body. I have it in context.

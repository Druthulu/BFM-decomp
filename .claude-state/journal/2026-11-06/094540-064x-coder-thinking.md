---
ts: 2026-11-06T16:45:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fQZN50dAhkg2VSDnkaRu
---
Item 2: launder. The launder is `{ s32 m = (s32)D_8018E2DC; __asm__ __volatile__("" : "=r"(m) : "0"(m)); ... }` — an asm that forces the global load into a register (to prevent cse from... something). There are 9 of them.

Baseline: let me score orig first. Then remove all asm and see the score.

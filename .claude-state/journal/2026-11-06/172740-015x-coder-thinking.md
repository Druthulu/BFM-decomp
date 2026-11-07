---
ts: 2026-11-07T00:27:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ENstkAAeWwMpQUJg5Trh
---
Line 21: the target is the run's baseline object under `build/`. So the target is the built object of the whole TU from build/ (the banked match). So the target listing = objdump of build/<something>.o for that function. Let me find the build object for this TU and objdump it — that's read-only and lets me see the whole target function.

Let me look at how delever_search finds it (function to extract).

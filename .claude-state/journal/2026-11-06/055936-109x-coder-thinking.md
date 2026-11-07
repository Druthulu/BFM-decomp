---
ts: 2026-11-06T12:59:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xZDhFUWEpZYuvHxIEl4J
---
Only 7 points, all from:
1. The missing `move v1,a0` (iv2c copy) — 2 diffs.
2. `sw v0,-4(t0)` placement (mine at 40, target at 39) — a scheduling/order diff of 1 insn.
3. Branch offsets.

So two issues. Let me get mine's asm to see the region. Let me use hdump.sh on includer 0.

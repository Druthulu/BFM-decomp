---
ts: 2026-11-06T05:32:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JPE1ZAQi0lVGhu282GDf
---
Combining fences adds insns (46). f2 remains the best at 3/44.

I'm at ~35 min on item 3. Let me record the WALL with best 3 and note the near-miss.

Actually, hold on: f2's score 3 means only 3 mismatched positions. The wall tag: this is a flow dead-store issue. `flow-dead-store` (new tag). Evidence: flow.c insn_dead_p (last_mem_set, rtx_equal_p) deletes repeated stores to the same frame-relative slot; the barrier's memory clobber clears last_mem_set. Best lever-free 3 (f2, 44 ins, one fence deleted by cse, one store still short).

Let me clean up the dumps and write the notes + results row + moves line.

Item 3 wall tag: `flow-dead-store` — new tag `<pass>-<what>`: flow-dead-store. Good.

Let me do it:
1. rm dumps.
2. notes.md.
3. results row.
4. moves line.

Then items 4 and 5.

Time check: ~22:52. Items 4 and 5 remain; ~20-30 min each. Total would be ~1 hour more. That's fine.

Let me write item 3's records.

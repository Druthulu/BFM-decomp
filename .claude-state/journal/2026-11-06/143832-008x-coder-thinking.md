---
ts: 2026-11-06T21:38:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tSYAhiiBGDxc0TpoYBml
---
The src function begins at line 4053 with `void func_8017E050(void) {` and ends at 4150. Let me extract lines 4053-4150 into orig.c. Actually the notes said 4054-4150; now 4053 due to changes? Let me extract by brace matching with python to be safe. But scratch scripts go under .run/. Let me use a python script under the shard dir.

Actually simpler: sed -n '4053,4150p' > orig.c. Verify the end brace at 4150.

Also need the typedef Rec20_8017DF18_8017E050 — it's function-local per comments? Let's check the body includes it. Let me see the first lines.

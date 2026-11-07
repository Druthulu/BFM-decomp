---
ts: 2026-11-06T21:36:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OYaYkvyOUmTIvfleA4jb
---
All 4 items have exactly one row. Each MATCH/PARTIAL win.c scores 0 (item 2). WALLs have win.c at best.

Wait — item 1's win.c scores 4, item 3's win.c scores 46, item 4's win.c scores 12. Let me verify item 1 and item 4 win.c are the best lever-free bodies. Item 1 win.c = score 4 (best). Item 3 win.c = f1 = score 46 (best). Item 4 win.c = score 12 (best). Item 2 win.c = score 0 (MATCH). Good.

Now let me double-check item 1's win.c still scores 4 (it should). And item 3's win.c = f1 scores 46. Item 4's win.c = 12. Let me verify quickly in one command? sc.sh for all four. But item 2 win.c is MATCH.

Actually, the DONE WHEN: "each MATCH/PARTIAL has its win.c scoring 0". Only item 2 is MATCH; verify it scores 0 (already did). WALLs just need best recorded.

Let me verify item 1 and 4 win.c quickly (sanity), then write the log.

Let me run sc.sh on all four win.c.

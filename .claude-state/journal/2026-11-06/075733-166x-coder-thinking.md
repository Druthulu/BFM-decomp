---
ts: 2026-11-06T14:57:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AhAGtqk3uJurLpiNP8yt
---
Now let me verify the DONE WHEN: every item of O02x/list.tsv has exactly one results.tsv row; each MATCH/PARTIAL has its win.c scoring 0.

Items:
1. func_8013D53C__ov_SC01_084 — MATCH, win.c scores 0 ✓
2. func_8013D53C__ov_SC02_005 — MATCH, win.c scores 0 ✓
3. func_80183130__ov_SC04_004 — WALL ✓
4. func_8013D53C__ov_SC05_008 — MATCH, win.c scores 0 ✓
5. func_8017EB30__ov_SC01_004 — WALL ✓

Let me do a final verification: re-score the three win.c files to confirm they still score 0 (FRESH check — the src may have moved). And verify the results rows match the list.

Let me run the three win.c scores again and check the results.tsv covers all 5 items.

Also, I should verify that the win.c files don't have any levers (asm/pin). I checked earlier. Let me re-verify quickly.

Let me also double-check that the three MATCH win.c files are the lever-free bodies (no keepalive). And the WALL win.c = best lever-free body.

Let me run the final checks.

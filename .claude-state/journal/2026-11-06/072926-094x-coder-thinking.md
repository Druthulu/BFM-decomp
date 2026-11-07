---
ts: 2026-11-06T14:29:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_umSYqTA8wHvu8u3iS6YZ
---
Now let me regenerate orig.c for the three TUs (FRESH: diff against current src), then apply the transform, and score each.

Wait — I should verify the orig.c files are still current. The src may have moved since I extracted them (earlier batches banking). Let me re-extract and diff. The line numbers: SC01 1308-1412, SC02 1308-1412, SC05 1305-1409. Let me re-locate and re-extract with a script that finds the function boundaries.

Actually, let me write a script to extract the function by finding `void func_8013D53C(void *arg0v) {` and the matching closing brace at col 0. That's robust to line shifts.

Let me write extract.py.

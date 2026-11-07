---
ts: 2026-11-06T14:31:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3Caw8cnktSli7eOhOY6Y
---
Wait, 216K? That seems too small — the item dirs have many .c files. Actually .run/P40/T11/O02x is the shard dir; 216K total. Fine.

Hmm, but I removed _tu which contained mk_tu.py? No, mk_tu.py was in _tu. Let me check: I wrote mk_tu.py to .run/P40/T11/O02x/_tu/mk_tu.py. Removing _tu deleted it. That's fine, I don't need it now (or I can rewrite). But xform.py and extract.py are in .run/P40/T11/O02x/ (not _tu). Good.

Now let me write notes.md for each of the three dirs. Let me write concise notes.

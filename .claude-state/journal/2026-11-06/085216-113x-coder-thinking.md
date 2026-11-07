---
ts: 2026-11-06T15:52:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CW94Np4UhJSYhjKYMsWu
---
These are all from my --keep runs. Let me remove them. Also the dumps dirs and *_tu.c in item dirs. And the candidate files a*.c etc. — the brief says scratch stays under my shard (fine to keep, but disk). The item dir should keep orig.c, win.c, notes.md, fn, kinds, tu. Extra candidates are small (few KB each) — fine, but let me keep a couple. The shard dir must stay < 200 MB — it's tiny.

Actually the dumps are the big ones (a full TU cse dump ~37k lines ≈ few MB each; I made ~7 dumps). Let me check and remove.

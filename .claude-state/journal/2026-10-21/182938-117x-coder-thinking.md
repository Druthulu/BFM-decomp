---
ts: 2026-10-22T00:29:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_2TCPKS9h7o7VNUi5jn1v
---
`tools/restruct.py --try TU FN` — it might score a body on all recipes. Let me look at what `--try TU FN` does (line 909 uses recs_for(tu) — all recipes ✓). Let me check the code around line 900-950 and see if it accepts a body file.

Let me look at the `--try` handling in restruct.py.

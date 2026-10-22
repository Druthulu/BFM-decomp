---
ts: 2026-10-22T00:29:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_5eG3Fu8NlorN0T8h7O6L
---
`restruct.py --try TU FN` works on the TREE's body (not a candidate file) and uses recs[0] too (classify_residual uses recs[0]).

Hmm. But maybe restruct.py has a `--body BODY` option (I saw `--body BODY` in the CLI!) — "--body BODY" — maybe it points to a body file to try! Let me check what --body does in restruct.py.

Also "--try-file TU_OR_FN [TU_OR_FN ...]".

Let me grep for the --body argumenthandling.

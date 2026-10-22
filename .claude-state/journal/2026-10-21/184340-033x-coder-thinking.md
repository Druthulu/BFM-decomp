---
ts: 2026-10-22T00:43:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8UcLWyBjZagn5oyiKHzU
---
There's a whole permuter infrastructure (tools/permuter_ils.py) that does exactly the sweep I need: starts from a lever-free body and randomizes statement order etc., scoring for a match. That's the automated way to hit ≥30 tries per item.

`tools/delever_permute.py --prepare TU FN` / `--run` — but that uses the ledger exemplars, and writes to .run/P36/permuter. Running it writes outside my shard dir (constraint: write only under G08b). Hmm. But it's a shared tool writing its own scratch under .run/P36. The constraint says "never ... other shards, shared helpers" — running a shared tool that writes its own scratch is probably acceptable? Risky though: it might also write the tree (only --bank does that).

Better: `tools/permuter_ils.py` might be runnable directly on a body I supply. Let me check its CLI.

Let me look at permuter_ils.py's CLI and how delever_permute prepares a draft from an exemplar.

Actually, let me first check: does permuter_ils.py accept a body file + TU + fn?

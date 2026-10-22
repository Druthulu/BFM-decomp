---
ts: 2026-10-22T00:12:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_z5G3JHnC0fwYClKkgT3c
---
masked_diff.py has a CLI: `masked_diff.py <a.o> <b.o|.s> [fn]`. Let me use it to dump the target function's instructions: pass the baseline object twice? It compares two objects and prints the diff. If a == b, the diff is empty. Hmm.

Let me look at masked_diff.py's main to see what it prints.

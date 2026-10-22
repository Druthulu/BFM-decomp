---
ts: 2026-10-21T23:44:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_3AElzsRBwY3siPlJF0V3
---
There's a rich R-rule catalog in tools/delever.py. The search sweeps families. The delever_search has a "--plan"/"--run" mode over a bank, and a "--try" mode for a single body.

Can I run the sweep on my body? Looking at delever_search: `--explain TU FN` with `--path` applies moves. And `--try TU FN FILE --body` scores one body.

Maybe there's a mode: score a body with all families applied (a beam search). Let me look at delever_search's main to see the options and whether there's a "sweep over a body" mode.

Let me look at the structure of delever_search.py around the argument parsing and the search loop.

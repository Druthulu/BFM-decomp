---
ts: 2026-10-22T08:11:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Q457NndVdyhcl6PlSRCf
---
The build uses cc1 directly. Let me find how a TU is compiled (the actual flags). Let me look in the Makefile for the overlay build rule.

Actually, I recall `.run/P40/T11/bin/dt.sh` uses delever_search which compiles the candidate body. Let me find the compile function in delever_search.py.

Let me grep for "cc1" in delever_search.py.

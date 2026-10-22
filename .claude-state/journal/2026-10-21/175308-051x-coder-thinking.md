---
ts: 2026-10-21T23:53:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_wdFSWkj1TBAh04yksfUJ
---
Let me find the allocno priority computation in global.c: "allocno_size", "allocno_n_refs", and the sort function `qsort` with `qty_compare`? In gcc 2.7's global.c, the allocnos are sorted by `allocno_compare`? Let me grep "allocno_compare" and "live_length".

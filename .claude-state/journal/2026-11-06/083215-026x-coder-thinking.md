---
ts: 2026-11-06T15:32:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Jyj6MsWQWdCbAVBC4xmp
---
Item 1 done: MATCH, 1 try, wall -. Let me append the row to results.tsv and the moves line. Also notes.md.

But first, note the format: `dir file func kinds result best tries wall evidence`. dir — I used basename. The list.tsv's first column is the dir name (basename). Good.

Let me append to results.tsv with a script (one action per command). I'll use a python script or printf append. Appending via >> is fine.

---
ts: 2026-11-06T11:42:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yAkkJj1KdOpnLAa9gyJR
---
Oops, I left `TAIL` and a stray line in emit: `s += TAIL` where TAIL was defined... I removed TAIL in the rewrite? Let me check: the new file defines HEAD then TAIL? I removed the TAIL constant but still use it. Yes, in the new file I dropped TAIL. Let me fix emit to use TAIL — I need to re-add TAIL. Let me edit.

Also note: the trailing "tag2 = 0xE1000200; ... pmask;" then TAIL. Fine.

2*2*3*2*3 = 72 candidates. Too many (~5 min). Reduce masks to ("", "2") → 48. Hmm, still 48*4s=3min. Acceptable maybe. But dt/sc each compiles the 18k-line TU; earlier dt.sh took a few seconds. Let me test timing on one.

Actually let me cut to 36: g1s 2 × add 2 × tagpos 3 × tagstore 1 (plain) × masks 3 = 36. Then a second round on the best.

Let me fix the file.

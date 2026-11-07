---
ts: 2026-11-06T15:29:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MbrUtPX1Tizl3a4y1M0w
---
So the body file contains the full function definition (bare definition) — the "body" includes signature and local externs. Note that in the example, the whole definition is copied.

Now, how does delever_search --body work? It presumably substitutes the function body into the TU and compiles, compares to target. Let me check its help.

Let me just start item 1: copy the function text from src into <dir>/orig.c, then run dt.sh on orig.c to establish the baseline score (should be 0 with launder present, or close).

Let me extract the function precisely from src lines 3057-3257. I'll write it via sed to a file. But careful: I must write only under .run/P40/T11/O05/. Good.

Let me use sed to extract 3057,3257 into orig.c.

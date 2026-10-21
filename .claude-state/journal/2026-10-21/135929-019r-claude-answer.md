---
ts: 2026-10-21T19:59:29.180Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 4039d6bd-bb15-459c-beb1-c522af57e3c5
usage: {input: 6, cacheRead: 238389, cacheWrite: 1970, output: 696}
---

Partly. The expert decides when to bank and writes the instructions, but a coder does the banking itself. For batch 1, the expert filled in its banking template (`.run/P40/T11/bank_brief.txt`) and spawned a coder, T11.c101, which made commit 8408af290c. Batch 2 went the same way, as T11.c102.

The reason is a house rule: an expert does a job itself only when it fits in about 10 tool calls, and anything with an edit, build and test loop goes to a coder. Banking is well beyond that:
- swap each cracked body into its source file;
- rewrite the matching residue rows;
- re-run the type census and the cast check;
- run the full 218/218 build check, which takes about half an hour;
- commit.

It also keeps the expert's own context small for the many hours of the wave.

A coder also doesn't bank each time it returns a match. Matches wait in scratch, already byte-checked one function at a time, and the expert banks a few batches' worth together. That way, one 218/218 run covers many wins.

So my earlier advice stands. The coder the expert sends to bank stays on in-house Opus, and the expert could bank every 6 to 8 batches to save gate runs. T11 is still stopped until you say go.

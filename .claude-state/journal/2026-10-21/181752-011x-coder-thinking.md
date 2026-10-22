---
ts: 2026-10-22T00:17:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YsWvvnxnrQ8NSnrFtqcA
---
Let me try a first attempt with the smallest item: func_8018656C. First, let me see the target asm to understand what the launder accomplishes. Where's the target? Probably in build/ or some asm dir. Let me check what delever_search compares.

Let me look at the delever_search.py source briefly (it's a tool; but the rules say an expert learns a tool from the card's Tools table and --help, never from its source. But I need to know the scoring). Actually let me just run dt.sh with a candidate.

First, create the item dir files: orig.c and win.c. The win.c holds a bare definition of func (no #include? "bare definition"). In the worked example win.c has `extern u16 aB9A02[1] __asm__("D_800B9A02");` etc. inside the function body. So win.c contains the function definition with externs inside the body.

Let me check the T10 example orig.c to see the format, and how delever_search --try --body works (does it splice the body into the TU?).

Let me look at the delever_search source for --body handling... rules say don't read source; but I need practical understanding. Let me just try it: write a candidate and run dt.sh.

First copy orig: I'll extract the function from the TU into orig.c.

For func_8018656C: the body is lines 8759-8812 approximately. Let me write orig.c with the def only.

Let me first test the machinery with a trivial candidate: take the original body verbatim and see the score (should be some baseline). Actually orig should score 0 presumably (it's the current def, and the target presumably was matched... no, the current def has levers, so it may not score 0). Hmm, the current def in src includes the launder asm — the "current def" may already score 0? The delever_search score presumably measures diff from target asm. If current def scores 0, then removing the launder must keep score 0.

Actually, "score 0 = MATCH" and the delever task: find lever-free body that still matches the target. The current def with levers presumably scores 0 too (it's the accepted decomp). So my job: remove the lever, keep score 0.

Let me test. Create item dir files.

Let me extract the function text. I'll use python to extract from the TU by brace matching. Write a helper script under .run/P40/T11/G14/ (my shard dir) — allowed since I write only under my shard dir.

Actually, simpler: use sed with line ranges I determine manually. But writing a small extractor is more reliable. Let me write .run/P40/T11/G14/extract.py.

Wait — constraint: "write only under .run/P40/T11/G14/ plus appends to .run/P40/T11/moves.md". So a script under G14/ is fine.

Let me write the extractor.

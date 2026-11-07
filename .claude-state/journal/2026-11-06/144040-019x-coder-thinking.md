---
ts: 2026-11-06T21:40:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h2HsWj5sfCUesyKsTJHm
---
Ah — the `--explain` without --path shows the lever-free-body residual (score 68, the w0 case). So the lever-free body as the tool sees it is the current src? No — explain reads "one body's residual" maybe from the current TU src with pins removed? It says score 68, which matches w0 (both pins dropped, launder kept?). Wait w0 was 68. Hmm, explain uses the source TU and applies delever? Actually the "site pin" lines show pins at 6736-6737, so it's reading src with pins and reports residual if pins were removed? It lists sites. Whatever.

I got what I needed though: the target has the div block before the packet stores (line 72-85 target), while lever-free mine hoists... yes matches notes.

But for the v0.c body (score 13) the structure matched except the register swap. Good — the s16 w2 fixed the div hoisting (interesting). So the residual is just the v1/a0 swap.

Now let me get the full disassembly of v0.c vs target to reason about the qty. Use --keep.

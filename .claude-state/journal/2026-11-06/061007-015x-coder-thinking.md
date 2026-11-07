---
ts: 2026-11-06T13:10:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1AQPAjg2Is2mt8ZtqdP5
---
Item 5 continues. Let me see the end.

Now, all 5 have barriers. Item 1: one `__asm__ __volatile__("")` barrier (cross-jump). Item 2: one memory barrier inside the do loop. Item 3: one `__asm__ __volatile__("")` barrier. Item 4: three memory barriers. Item 5: three `__asm__ __volatile__("")` barriers.

The task: write a lever-free body (barrier removed, pins may stay since they're another kind) that scores 0. That's the "crack the shard" task: find real-C replacements for the barriers.

Per the moves table, for barrier items the typical crack is:
- do{}while(0) around a statement to split cse1 EBB (C0535) — a real C construct (loop) that acts as barrier but is legitimate? Wait, is do-while considered a lever? The constraint says `do{}while(0)` only with `// !FAKE: do-while`. Hmm, that suggests do-while must be annotated. But is do-while counted as a barrier kind? In the census, AB_KINDS = {"pin","barrier","launder","keepalive","instruction","gte-lever","asm-body"} — do-while is not a lever kind. And in the moves table, MANY MATCHes used do{}while(0). So do-while is legitimate real C (a loop). But the constraint says annotate with `// !FAKE: do-while`. Hmm... maybe because a `do{}while(0)` is a "fake loop" that reads oddly; the marker documents it. Actually wait, looking at the worked example win.c from T10, the do-while has no comment. But this brief explicitly says to add `// !FAKE: do-while`. Let me follow the brief: any do{}while(0) gets `// !FAKE: do-while` comment.

Hmm, but wait. Actually re-reading: "`do{}while(0)` only with `// !FAKE: do-while`". Maybe means it's allowed as a real-C move but must be marked as a known-fake construct so the expert can see it. Fine.

Let me check the moves.md for the exact barrier→do-while mechanisms and also look at cookbook C0535 and C0414 as directed.

Let me grep the cookbook.

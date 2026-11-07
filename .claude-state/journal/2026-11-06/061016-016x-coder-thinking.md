---
ts: 2026-11-06T13:10:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xhMPym0V3RdJgoAw5o7C
---
C0535 confirms: do{}while(0) with `// !FAKE: do-while` comment. Good, that's the intended move.

Now let me read C0414 briefly (dead-reset cse-breaker) — it's a lever? "dead-reset `v0=0`" is real C. Fine.

Now let me set up the workflow. First I need orig.c for each item (from src), then a win.c candidate. The brief says: "Start from the current def in src (copy to <dir>/orig.c)". Also FRESH says diff orig.c against src at each item start; since no orig.c exists, create it.

I need to extract the def range from src. The `--body` option splices body text replacing the def span (body_span). So my candidate file must be a bare definition of the function. I can copy the def text.

Let me write a small script to extract the def? Actually body_span finds the def in the TU. For extraction, I need exact line ranges:
- item1: 3228-3348 (need to verify end line)
- item2: 4153-4292?
- item3: 3469-3591?
- item4: 4071-4239?
- item5: 8041-8145?

Let me get exact braces. Use awk to find matching braces from the def start. Simpler: use python script under my shard dir that extracts a function by brace matching. Let me write .run/P40/T11/O02/extract.py.

Actually careful: brief says scratch scripts under .run/. Fine.

Let me write extract.py: read file, find line with `void func_XXX(`, then count braces until balanced (accounting for strings/comments minimally; these functions have comments with braces? e.g. "/* ... */" might contain braces. Risk. Better use tools' body_span from delever_search. Let me just use python import of the module? body_span(raw, tu, fn) is in delever_search. I can call it: `python3 -c` is discouraged; write a script that imports. Actually delever_search imports delever etc. That's fine.

Simpler: use /usr/bin/python3 with a script that imports sys.path tools and calls delever_search.body_span. Let me check its signature.

Actually let me just use awk with brace counting ignoring comment lines that start with * or /* ... */ — the doc comments before the def are not included anyway. Within the def there are comments; do they contain braces? item1 has `/* §5a ... */` no braces. Item5 has comments inside? Let me be safe and use body_span.

Let me write extract.py.

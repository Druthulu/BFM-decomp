---
ts: 2026-11-06T07:47:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H3bzN6ofWkGXWUhABwYX
---
--explain applies moves to the lever-free text and prints the score/diff, not the text. But I can modify a scratch copy of delever to print the text? That's tool modification — not allowed. But I can import the modules in a scratch script under my shard and do the same, printing text. That's allowed (scratch script, not editing tools). Let me write a scratch script that:
1. loads recipes, gets lever-free text (dl.lever_free_body),
2. applies the move path via dl.recipe_candidates,
3. prints the resulting text.

Then I can see the score-1 candidate's source and adapt it to a static win.c.

Let me write .run/P40/T11/G24/explain_text.py using the same imports.

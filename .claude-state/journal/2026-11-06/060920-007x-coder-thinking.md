---
ts: 2026-11-06T13:09:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NUX5tgZksihN4MLJdw8m
---
Interesting: the win.c in that example has do-while with no `// !FAKE: do-while` comment. Hmm, but the brief says `do{}while(0)` only with `// !FAKE: do-while`. Wait, maybe the constraint means the comment marks it as a known lever... Actually re-read: "no `register` vars, no `__asm__`; `do{}while(0)` only with `// !FAKE: do-while`". Hmm, the example win.c uses do-while without comment. But that's a T10 example, maybe different rules. Actually in orig.c the pin has `// !FAKE: pin $8 — ...`. So `!FAKE` marks lever lines that are intentionally kept (a pin), documented. For do-while, maybe the delever checker flags do-while as a fake lever? Let me check how delever_search works — search for "fake" or "lever" detection.

Let me grep more broadly.

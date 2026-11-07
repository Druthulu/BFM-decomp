---
ts: 2026-11-06T04:41:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IyZypTgxC3LWnqXfHzUb
---
Now let me understand the tooling: delever_search.py --try <TU> <fn> <file> --body. For a header item, TU is src/shared/ov/func_XXX.h. How does --try handle a header TU? Let me check delever_search.py's help/usage and tryinc.py.

Also, the brief says: "header item (src/shared/ov/*.h): MATCH only if score 0 on every includer (tryinc.py k = 0..n-1)". And POINTERS: .run/P40/T10/tryinc.py <k> <header> <fn> <body> (header item: k-th includer).

Let me read tryinc.py and check delever_search help.
